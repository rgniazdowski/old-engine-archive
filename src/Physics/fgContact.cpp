/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/*
 * Implementation file for the contact resolution system.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgPrecision.h"
#include "fgContact.h"
#include "fgCycloneCoreMath.h"
#include "fgLog.h"
#include "GFX/fgGfxTypes.h"

#include <memory.h>
#include <assert.h>

using namespace fg;

//------------------------------------------------------------------------------

void physics::CContact::setBodyData(CRigidBody* one, CRigidBody *two,
                                    real friction, real restitution) {
    physics::CContact::body[0] = one;
    physics::CContact::body[1] = two;
    physics::CContact::friction = friction;
    physics::CContact::restitution = restitution;
}
//------------------------------------------------------------------------------

void physics::CContact::matchAwakeState() {
    // Collisions with the world never cause a body to wake up.
    if(!body[1]) return;

    bool body0awake = body[0]->getAwake();
    bool body1awake = body[1]->getAwake();

    // Wake up only the sleeping one
    if(body0awake ^ body1awake) {
        if(body0awake) body[1]->setAwake();
        else body[0]->setAwake();
    }
}
//------------------------------------------------------------------------------

/*
 * Swaps the bodies in the current contact, so body 0 is at body 1 and
 * vice versa. This also changes the direction of the contact normal,
 * but doesn't update any calculated internal data. If you are calling
 * this method manually, then call calculateInternals afterwards to
 * make sure the internal data is up to date.
 */
void physics::CContact::swapBodies() {
    contactNormal *= -1;

    CRigidBody *temp = body[0];
    body[0] = body[1];
    body[1] = temp;
}
//------------------------------------------------------------------------------

/*
 * Constructs an arbitrary orthonormal basis for the contact.  This is
 * stored as a 3x3 matrix, where each vector is a column (in other
 * words the matrix transforms contact space into world space). The x
 * direction is generated from the contact normal, and the y and z
 * directionss are set so they are at right angles to it.
 */
inline
void physics::CContact::calculateContactBasis() {
    Vector3f contactTangent[2];

    // Check whether the Z-axis is nearer to the X or Y axis
    if(real_abs(contactNormal.x) > real_abs(contactNormal.y)) {
        // Scaling factor to ensure the results are normalised
        const real s = (real)1.0f / real_sqrt(contactNormal.z * contactNormal.z +
                                              contactNormal.x * contactNormal.x);

        // The new X-axis is at right angles to the world Y-axis
        contactTangent[0].x = contactNormal.z*s;
        contactTangent[0].y = 0;
        contactTangent[0].z = -contactNormal.x*s;

        // The new Y-axis is at right angles to the new X- and Z- axes
        contactTangent[1].x = contactNormal.y * contactTangent[0].x;
        contactTangent[1].y = contactNormal.z * contactTangent[0].x -
                contactNormal.x * contactTangent[0].z;
        contactTangent[1].z = -contactNormal.y * contactTangent[0].x;
    } else {
        // Scaling factor to ensure the results are normalised
        const real s = (real)1.0 / real_sqrt(contactNormal.z * contactNormal.z +
                                             contactNormal.y * contactNormal.y);

        // The new X-axis is at right angles to the world X-axis
        contactTangent[0].x = 0;
        contactTangent[0].y = -contactNormal.z*s;
        contactTangent[0].z = contactNormal.y*s;

        // The new Y-axis is at right angles to the new X- and Z- axes
        contactTangent[1].x = contactNormal.y * contactTangent[0].z -
                contactNormal.z * contactTangent[0].y;
        contactTangent[1].y = -contactNormal.x * contactTangent[0].z;
        contactTangent[1].z = contactNormal.x * contactTangent[0].y;
    }

    // Make a matrix from the three vectors.
    m_contactToWorld = physics::setComponents(
            //Matrix3f(
                     contactNormal,
                     contactTangent[0],
                     contactTangent[1]);
}
//------------------------------------------------------------------------------

Vector3f physics::CContact::calculateLocalVelocity(unsigned bodyIndex, real duration) {
    CRigidBody *thisBody = body[bodyIndex];

    // Work out the velocity of the contact point.
    Vector3f velocity = math::cross(thisBody->getRotation(), m_relativeContactPosition[bodyIndex]); // %
    velocity += thisBody->getVelocity();

    // Turn the velocity into contact-coordinates.
    Vector3f contactVelocity = physics::transformTranspose(m_contactToWorld, velocity);

    // Calculate the ammount of velocity that is due to forces without
    // reactions.
    Vector3f accVelocity = thisBody->getLastFrameAcceleration() * duration;

    // Calculate the velocity in contact-coordinates.
    accVelocity = physics::transformTranspose(m_contactToWorld, accVelocity);

    // We ignore any component of acceleration in the contact normal
    // direction, we are only interested in planar acceleration
    accVelocity.x = 0;

    // Add the planar velocities - if there's enough friction they will
    // be removed during velocity resolution
    contactVelocity += accVelocity;

    // And return it
    return contactVelocity;
}
//------------------------------------------------------------------------------

void physics::CContact::calculateDesiredDeltaVelocity(real duration) {
    const static real velocityLimit = (real)0.25f;

    // Calculate the acceleration induced velocity accumulated this frame
    real velocityFromAcc = 0;

    if(body[0]->getAwake()) {
        velocityFromAcc += math::dot(body[0]->getLastFrameAcceleration(), contactNormal) * duration;
    }

    if(body[1] && body[1]->getAwake()) {
        velocityFromAcc -= math::dot(body[1]->getLastFrameAcceleration(), contactNormal) * duration;
    }
    
    // If the velocity is very slow, limit the restitution
    real thisRestitution = restitution;
    if(real_abs(m_contactVelocity.x) < velocityLimit) {
        thisRestitution = (real)0.0f;
    }

    // Combine the bounce velocity with the removed
    // acceleration velocity.
    m_desiredDeltaVelocity =
            -m_contactVelocity.x
            - thisRestitution * (m_contactVelocity.x - velocityFromAcc);
}
//------------------------------------------------------------------------------

void physics::CContact::calculateInternals(real duration) {
    // Check if the first object is NULL, and swap if it is.
    if(!body[0]) swapBodies();
    assert(body[0]);

    // Calculate an set of axis at the contact point.
    calculateContactBasis();

    // Store the relative position of the contact relative to each body
    m_relativeContactPosition[0] = contactPoint - body[0]->getPosition();
    if(body[1]) {
        m_relativeContactPosition[1] = contactPoint - body[1]->getPosition();
    }

    // Find the relative velocity of the bodies at the contact point.
    m_contactVelocity = calculateLocalVelocity(0, duration);
    if(body[1]) {
        m_contactVelocity -= calculateLocalVelocity(1, duration);
    }

    // Calculate the desired change in velocity for resolution
    calculateDesiredDeltaVelocity(duration);
}
//------------------------------------------------------------------------------

void physics::CContact::applyVelocityChange(Vector3f velocityChange[2],
                                            Vector3f rotationChange[2]) {

    // Get hold of the inverse mass and inverse inertia tensor, both in
    // world coordinates.
    Matrix3f inverseInertiaTensor[2];
    body[0]->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
    if(body[1])
        body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

    // We will calculate the impulse for each contact axis
    Vector3f impulseContact;

    if(friction == (real)0.0) {
        // Use the short format for frictionless contacts
        impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
    } else {
        // Otherwise we may have impulses that aren't in the direction of the
        // contact, so we need the more complex version.
        impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
    }

    // Convert impulse to world coordinates
    Vector3f impulse = physics::transform(m_contactToWorld, impulseContact);

    // Split in the impulse into linear and rotational components
    Vector3f impulsiveTorque = math::cross(m_relativeContactPosition[0], impulse);
    rotationChange[0] = physics::transform(inverseInertiaTensor[0], impulsiveTorque);
    velocityChange[0] = Vector3f();
    velocityChange[0] += impulse * body[0]->getInverseMass();

    // Apply the changes
    body[0]->addVelocity(velocityChange[0]);
    body[0]->addRotation(rotationChange[0]);

    if(body[1]) {
        // Work out body one's linear and angular changes
        Vector3f impulsiveTorque = math::cross(impulse, m_relativeContactPosition[1]); // %
        rotationChange[1] = physics::transform(inverseInertiaTensor[1], impulsiveTorque);
        velocityChange[1] = Vector3f();
        velocityChange[1] += impulse * -body[1]->getInverseMass();

        // And apply them.
        body[1]->addVelocity(velocityChange[1]);
        body[1]->addRotation(rotationChange[1]);
    }
}
//------------------------------------------------------------------------------

inline
Vector3f physics::CContact::calculateFrictionlessImpulse(Matrix3f * inverseInertiaTensor) {
    Vector3f impulseContact;

    // Build a vector that shows the change in velocity in
    // world space for a unit impulse in the direction of the contact
    // normal.
    Vector3f deltaVelWorld = math::cross(m_relativeContactPosition[0], contactNormal); // %
    deltaVelWorld = physics::transform(inverseInertiaTensor[0], (deltaVelWorld));
    deltaVelWorld = math::cross(deltaVelWorld, m_relativeContactPosition[0]); // %

    // Work out the change in velocity in contact coordinates.
    real deltaVelocity = math::dot(deltaVelWorld, contactNormal);

    // Add the linear component of velocity change
    deltaVelocity += body[0]->getInverseMass();

    // Check if we need to the second body's data
    if(body[1]) {
        // Go through the same transformation sequence again
        Vector3f deltaVelWorld = math::cross(m_relativeContactPosition[1], contactNormal); // %
        deltaVelWorld = physics::transform(inverseInertiaTensor[1], (deltaVelWorld));
        deltaVelWorld = math::cross(deltaVelWorld, m_relativeContactPosition[1]); // %

        // Add the change in velocity due to rotation
        deltaVelocity += math::dot(deltaVelWorld, contactNormal);

        // Add the change in velocity due to linear motion
        deltaVelocity += body[1]->getInverseMass();
    }

    // Calculate the required size of the impulse
    impulseContact.x = m_desiredDeltaVelocity / deltaVelocity;
    impulseContact.y = 0;
    impulseContact.z = 0;
    return impulseContact;
}
#include <cstdio>

inline void dumpMatrix3x3(const float *mat, const char *title) {
    if(title)
        printf("%s MATRIX:\n", title);
    printf("{ %.2f %.2f %.2f }\n", mat[0], mat[1], mat[2]);
    printf("{ %.2f %.2f %.2f }\n", mat[3], mat[4], mat[5]);
    printf("{ %.2f %.2f %.2f }\n", mat[6], mat[7], mat[8]);

}

inline
Vector3f physics::CContact::calculateFrictionImpulse(Matrix3f * inverseInertiaTensor) {
    Vector3f impulseContact;
    real inverseMass = body[0]->getInverseMass();

    // The equivalent of a cross product in matrices is multiplication
    // by a skew symmetric matrix - we build the matrix for converting
    // between linear and angular quantities.
    Matrix3f impulseToTorque = physics::skewSymmetric(m_relativeContactPosition[0]);
    //dumpMatrix3x3(impulseToTorque.data, "impulseToTorque");
    // Build the matrix to convert contact impulse to change in velocity
    // in world coordinates.
    //Matrix3f deltaVelWorld = impulseToTorque;
    //deltaVelWorld *= inverseInertiaTensor[0];
    //deltaVelWorld *= impulseToTorque;
    Matrix3f deltaVelWorld = physics::multiply(impulseToTorque, inverseInertiaTensor[0]);
    deltaVelWorld = physics::multiply(deltaVelWorld, impulseToTorque);
    deltaVelWorld *= -1.0f;
    //dumpMatrix3x3(deltaVelWorld.data, "deltaVelWorld");
    // Check if we need to add body two's data
    if(body[1]) {
        // Set the cross product matrix
        impulseToTorque = physics::skewSymmetric(m_relativeContactPosition[1]);

        // Calculate the velocity change matrix
        //Matrix3f deltaVelWorld2 = impulseToTorque;
        //deltaVelWorld2 *= inverseInertiaTensor[1];
        //deltaVelWorld2 *= impulseToTorque;
        Matrix3f deltaVelWorld2 = physics::multiply(impulseToTorque, inverseInertiaTensor[0]);
        deltaVelWorld2 = physics::multiply(deltaVelWorld2, impulseToTorque);
        deltaVelWorld2 *= -1.0f;
        //dumpMatrix3x3(deltaVelWorld2.data, "deltaVelWorld2");
        // Add to the total delta velocity.
        deltaVelWorld += deltaVelWorld2;

        // Add to the inverse mass
        inverseMass += body[1]->getInverseMass();
    }
    
    // Do a change of basis to convert into contact coordinates.
    Matrix3f deltaVelocity = /*math::transpose*/math::transpose(m_contactToWorld);
    float *deltaVelocity_data = math::value_ptr(deltaVelocity);
    //deltaVelocity *= deltaVelWorld;
    //deltaVelocity *= contactToWorld;
    deltaVelocity = physics::multiply(deltaVelocity, deltaVelWorld);
    deltaVelocity = physics::multiply(deltaVelocity, m_contactToWorld);
    //dumpMatrix3x3(deltaVelocity.data, "deltaVelocity");
    // Add in the linear velocity change
    //deltaVelocity[0][0] += inverseMass; //0
    //deltaVelocity[1][0] += inverseMass; //4
    //deltaVelocity[2][0] += inverseMass; //8
    deltaVelocity_data[0] += inverseMass; //0
    deltaVelocity_data[4] += inverseMass; //4
    deltaVelocity_data[8] += inverseMass; //8

    // Invert to get the impulse needed per unit velocity
    Matrix3f impulseMatrix = math::inverse(deltaVelocity);//physics::setInverse(deltaVelocity);
    //dumpMatrix3x3(impulseMatrix.data, "impulseMatrix");
    // Find the target velocities to kill
    Vector3f velKill(m_desiredDeltaVelocity,
                     -m_contactVelocity.y,
                     -m_contactVelocity.z);

    // Find the impulse to kill target velocities
    impulseContact = physics::transform(impulseMatrix, (velKill));
    //printf("CFI: %.2f %.2f %.2f | velKill: %.2f %.2f %.2f | inverseMass: %f\n",
    //       impulseContact.x, impulseContact.y, impulseContact.z,
    //       velKill.x, velKill.y, velKill.z, inverseMass);
    // Check for exceeding friction
    real planarImpulse = math::sqrt(impulseContact.y * impulseContact.y +
                                    impulseContact.z * impulseContact.z);
    if(planarImpulse > impulseContact.x * friction) {
        // We need to use dynamic friction
        impulseContact.y /= planarImpulse;
        impulseContact.z /= planarImpulse;

        impulseContact.x =
                deltaVelocity_data[0] +
                deltaVelocity_data[1] * friction * impulseContact.y +
                deltaVelocity_data[2] * friction * impulseContact.z;
        impulseContact.x = m_desiredDeltaVelocity / impulseContact.x;
        impulseContact.y *= friction * impulseContact.x;
        impulseContact.z *= friction * impulseContact.x;
    }
    //printf("CFI: %.2f %.2f %.2f | friction:%.2f | planarImpulse:%.2f\n", impulseContact.x, impulseContact.y, impulseContact.z, friction, planarImpulse);
    return impulseContact;
}
//------------------------------------------------------------------------------

void physics::CContact::applyPositionChange(Vector3f linearChange[2],
                                            Vector3f angularChange[2],
                                            real penetration) {
    const real angularLimit = (real)0.2f;
    real angularMove[2];
    real linearMove[2];

    real totalInertia = 0;
    real linearInertia[2];
    real angularInertia[2];

    // We need to work out the inertia of each object in the direction
    // of the contact normal, due to angular inertia only.
    for(unsigned i = 0; i < 2; i++) if(body[i]) {
            Matrix3f inverseInertiaTensor;
            body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

            // Use the same procedure as for calculating frictionless
            // velocity change to work out the angular inertia.
            Vector3f angularInertiaWorld = math::cross(m_relativeContactPosition[i], contactNormal);
            angularInertiaWorld =
                    physics::transform(inverseInertiaTensor, (angularInertiaWorld));
            angularInertiaWorld =
                    math::cross(angularInertiaWorld, m_relativeContactPosition[i]); // %
            angularInertia[i] =
                    math::dot(angularInertiaWorld, contactNormal);

            // The linear component is simply the inverse mass
            linearInertia[i] = body[i]->getInverseMass();

            // Keep track of the total inertia from all components
            totalInertia += linearInertia[i] + angularInertia[i];

            // We break the loop here so that the totalInertia value is
            // completely calculated (by both iterations) before
            // continuing.
        }

    // Loop through again calculating and applying the changes
    for(unsigned i = 0; i < 2; i++) if(body[i]) {
            // The linear and angular movements required are in proportion to
            // the two inverse inertias.
            real sign = (i == 0) ? 1 : -1;
            angularMove[i] =
                    sign * penetration * (angularInertia[i] / totalInertia);
            linearMove[i] =
                    sign * penetration * (linearInertia[i] / totalInertia);

            // To avoid angular projections that are too great (when mass is large
            // but inertia tensor is small) limit the angular move.
            Vector3f projection = m_relativeContactPosition[i];
            projection += (contactNormal * -math::dot(m_relativeContactPosition[i], (contactNormal)));

            // Use the small angle approximation for the sine of the angle (i.e.
            // the magnitude would be sine(angularLimit) * projection.magnitude
            // but we approximate sine(angularLimit) to angularLimit).
            real maxMagnitude = angularLimit * math::length(projection);

            if(angularMove[i] < -maxMagnitude) {
                real totalMove = angularMove[i] + linearMove[i];
                angularMove[i] = -maxMagnitude;
                linearMove[i] = totalMove - angularMove[i];
            } else if(angularMove[i] > maxMagnitude) {
                real totalMove = angularMove[i] + linearMove[i];
                angularMove[i] = maxMagnitude;
                linearMove[i] = totalMove - angularMove[i];
            }

            // We have the linear amount of movement required by turning
            // the rigid body (in angularMove[i]). We now need to
            // calculate the desired rotation to achieve that.
            if(angularMove[i] == 0) {
                // Easy case - no angular movement means no rotation.
                //angularChange[i].clear();
                angularChange[i] = Vector3f();
            } else {
                // Work out the direction we'd like to rotate in.
                Vector3f targetAngularDirection = math::cross(m_relativeContactPosition[i], contactNormal);

                Matrix3f inverseInertiaTensor;
                body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

                // Work out the direction we'd need to rotate to achieve that
                angularChange[i] = (physics::transform(inverseInertiaTensor,(targetAngularDirection))) *
                        (angularMove[i] / angularInertia[i]);
            }

            // Velocity change is easier - it is just the linear movement
            // along the contact normal.
            linearChange[i] = contactNormal * linearMove[i];

            // Now we can start to apply the values we've calculated.
            // Apply the linear movement
            Vector3f pos;
            body[i]->getPosition(&pos);
            pos += (contactNormal * linearMove[i]);
            body[i]->setPosition(pos);

            // And the change in orientation
            Quaternionf q;
            body[i]->getOrientation(&q);
            
            //q.addScaledVector(angularChange[i], ((real)1.0));
            //orientation.addScaledVector(rotation, duration);
            //orientation += (Quaternionf(0, rotation * duration) * orientation) * 0.5f;    

            //q += (Quaternionf(0, angularChange[i] * ((real)1.0)) * q) * ((real)0.5);
            q = physics::addScaledVector(q, angularChange[i], 1.0f);
            body[i]->setOrientation(q);

            // We need to calculate the derived data for any body that is
            // asleep, so that the changes are reflected in the object's
            // data. Otherwise the resolution will not change the position
            // of the object, and the next collision detection round will
            // have the same penetration.
            if(!body[i]->getAwake()) body[i]->calculateDerivedData();
        }
}
//------------------------------------------------------------------------------
