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
 * Implementation file for the fine grained collision detector.
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
#include "fgCollisionFine.h"

#include <memory.h>
#include <assert.h>
#include <cstdlib>
#include <cstdio>

using namespace fg;

//------------------------------------------------------------------------------

void physics::CCollisionPrimitive::calculateInternals(void) {
    if(body) {        
        transform = body->getTransform() * offset;
        //transform = offset * body->getTransform();
        
        //transform = physics::transform(body->getTransform(), offset);
    }
}
//------------------------------------------------------------------------------

bool physics::CIntersectionTest::sphereAndHalfSpace(const CCollisionSphere &sphere,
                                                    const CCollisionPlane &plane) {
    // Find the distance from the origin
    real ballDistance =
            math::dot(plane.direction, sphere.getAxis(3)) - sphere.radius;

    // Check for the intersection
    return ballDistance <= plane.offset;
}
//------------------------------------------------------------------------------

bool physics::CIntersectionTest::sphereAndSphere(const CCollisionSphere &one,
                                                 const CCollisionSphere &two) {
    // Find the vector between the objects
    Vector3f midline = one.getAxis(3) - two.getAxis(3);

    // See if it is large enough.
    return math::squareLength(midline) <
            (one.radius + two.radius)*(one.radius + two.radius);
}
//------------------------------------------------------------------------------

static inline physics::real transformToAxis(const physics::CCollisionBox &box,
                                            const Vector3f &axis) {
    return box.halfSize.x * real_abs(math::dot(axis, box.getAxis(0))) +
            box.halfSize.y * real_abs(math::dot(axis, box.getAxis(1))) +
            box.halfSize.z * real_abs(math::dot(axis, box.getAxis(2)));
}
//------------------------------------------------------------------------------

/**
 * This function checks if the two boxes overlap
 * along the given axis. The final parameter toCentre
 * is used to pass in the vector between the boxes centre
 * points, to avoid having to recalculate it each time.
 */
static inline bool overlapOnAxis(const physics::CCollisionBox &one,
                                 const physics::CCollisionBox &two,
                                 const Vector3f &axis,
                                 const Vector3f &toCentre) {
    // Project the half-size of one onto axis
    physics::real oneProject = transformToAxis(one, axis);
    physics::real twoProject = transformToAxis(two, axis);

    // Project this onto the axis
    physics::real distance = real_abs(math::dot(toCentre, axis));

    // Check for overlap
    return (distance < oneProject + twoProject);
}
//------------------------------------------------------------------------------

// This preprocessor definition is only used as a convenience
// in the boxAndBox intersection  method.
#define TEST_OVERLAP(axis) overlapOnAxis(one, two, (axis), toCentre)

bool physics::CIntersectionTest::boxAndBox(const CCollisionBox &one,
                                           const CCollisionBox &two) {
    // Find the vector between the two centres
    Vector3f toCentre = two.getAxis(3) - one.getAxis(3);

    return (
            // Check on box one's axes first
            TEST_OVERLAP(one.getAxis(0)) &&
            TEST_OVERLAP(one.getAxis(1)) &&
            TEST_OVERLAP(one.getAxis(2)) &&

            // And on two's
            TEST_OVERLAP(two.getAxis(0)) &&
            TEST_OVERLAP(two.getAxis(1)) &&
            TEST_OVERLAP(two.getAxis(2)) &&

            // Now on the cross products
            TEST_OVERLAP(math::cross(one.getAxis(0), two.getAxis(0))) &&
            TEST_OVERLAP(math::cross(one.getAxis(0), two.getAxis(1))) &&
            TEST_OVERLAP(math::cross(one.getAxis(0), two.getAxis(2))) &&
            TEST_OVERLAP(math::cross(one.getAxis(1), two.getAxis(0))) &&
            TEST_OVERLAP(math::cross(one.getAxis(1), two.getAxis(1))) &&
            TEST_OVERLAP(math::cross(one.getAxis(1), two.getAxis(2))) &&
            TEST_OVERLAP(math::cross(one.getAxis(2), two.getAxis(0))) &&
            TEST_OVERLAP(math::cross(one.getAxis(2), two.getAxis(1))) &&
            TEST_OVERLAP(math::cross(one.getAxis(2), two.getAxis(2)))
            );
}
#undef TEST_OVERLAP
//------------------------------------------------------------------------------

bool physics::CIntersectionTest::boxAndHalfSpace(const CCollisionBox &box,
                                                 const CCollisionPlane &plane
                                                 ) {
    // Work out the projected radius of the box onto the plane direction
    real projectedRadius = transformToAxis(box, plane.direction);

    // Work out how far the box is from the origin
    real boxDistance =
            math::dot(plane.direction, box.getAxis(3)) - projectedRadius;

    // Check for the intersection
    return boxDistance <= plane.offset;
}
//------------------------------------------------------------------------------

unsigned physics::CCollisionDetector::sphereAndTruePlane(const CCollisionSphere &sphere,
                                                         const CCollisionPlane &plane,
                                                         SCollisionData *data) {
    if(!data) return 0;
    // Make sure we have contacts
    if(data->contactsLeft <= 0) return 0;

    // Cache the sphere position
    Vector3f position = sphere.getAxis(3);

    // Find the distance from the plane
    real centreDistance = math::dot(plane.direction, position) - plane.offset;

    // Check if we're within radius
    if(centreDistance * centreDistance > sphere.radius * sphere.radius) {
        return 0;
    }

    // Check which side of the plane we're on
    Vector3f normal = plane.direction;
    real penetration = -centreDistance;
    if(centreDistance < 0) {
        normal *= -1;
        penetration = -penetration;
    }
    penetration += sphere.radius;

    // Create the contact - it has a normal in the plane direction.
    CContact* contact = data->contacts;
    contact->contactNormal = normal;
    contact->penetration = penetration;
    contact->contactPoint = position - plane.direction * centreDistance;
    contact->setBodyData(sphere.body, NULL,
                         data->friction, data->restitution);

    data->addContacts(1);
    return 1;
}
//------------------------------------------------------------------------------

unsigned physics::CCollisionDetector::sphereAndHalfSpace(const CCollisionSphere &sphere,
                                                         const CCollisionPlane &plane,
                                                         SCollisionData *data) {
    if(!data) return 0;
    // Make sure we have contacts
    if(data->contactsLeft <= 0) return 0;

    // Cache the sphere position
    Vector3f position = sphere.getAxis(3);

    // Find the distance from the plane
    real ballDistance = math::dot(plane.direction, position) - sphere.radius - plane.offset;

    if(ballDistance >= 0) return 0;

    // Create the contact - it has a normal in the plane direction.
    CContact* contact = data->contacts;
    contact->contactNormal = plane.direction;
    contact->penetration = -ballDistance;
    contact->contactPoint =
            position - plane.direction * (ballDistance + sphere.radius);
    contact->setBodyData(sphere.body, NULL,
                         data->friction, data->restitution);

    data->addContacts(1);
    return 1;
}
//------------------------------------------------------------------------------

unsigned physics::CCollisionDetector::sphereAndSphere(const CCollisionSphere &one,
                                                      const CCollisionSphere &two,
                                                      SCollisionData *data) {
    if(!data) return 0;
    // Make sure we have contacts
    if(data->contactsLeft <= 0) return 0;

    // Cache the sphere positions
    Vector3f positionOne = one.getAxis(3);
    Vector3f positionTwo = two.getAxis(3);

    // Find the vector between the objects
    Vector3f midline = positionOne - positionTwo;
    real size = math::length(midline); //midline.magnitude();

    // See if it is large enough.
    if(size <= 0.0f || size >= one.radius + two.radius) {
        return 0;
    }

    // We manually create the normal, because we have the
    // size to hand.
    Vector3f normal = midline * (((real)1.0) / size);

    CContact* contact = data->contacts;
    contact->contactNormal = normal;
    contact->contactPoint = positionOne + midline * (real)0.5;
    contact->penetration = (one.radius + two.radius - size);
    contact->setBodyData(one.body, two.body,
                         data->friction, data->restitution);

    data->addContacts(1);
    return 1;
}
//------------------------------------------------------------------------------

/*
 * This function checks if the two boxes overlap
 * along the given axis, returning the ammount of overlap.
 * The final parameter toCentre
 * is used to pass in the vector between the boxes centre
 * points, to avoid having to recalculate it each time.
 */
static inline physics::real penetrationOnAxis(const physics::CCollisionBox &one,
                                              const physics::CCollisionBox &two,
                                              const Vector3f &axis,
                                              const Vector3f &toCentre) {
    // Project the half-size of one onto axis
    physics::real oneProject = transformToAxis(one, axis);
    physics::real twoProject = transformToAxis(two, axis);

    // Project this onto the axis
    physics::real distance = real_abs(math::dot(toCentre, axis));

    // Return the overlap (i.e. positive indicates
    // overlap, negative indicates separation).
    return oneProject + twoProject - distance;
}
//------------------------------------------------------------------------------

static inline bool tryAxis(const physics::CCollisionBox &one,
                           const physics::CCollisionBox &two,
                           Vector3f axis,
                           const Vector3f& toCentre,
                           unsigned index,
                           // These values may be updated
                           physics::real& smallestPenetration,
                           unsigned &smallestCase) {
    // Make sure we have a normalized axis, and don't check almost parallel axes
    if(math::squareLength(axis) < 0.0001f) return true;
    //axis.normalise();
    axis = math::normalize(axis);

    physics::real penetration = penetrationOnAxis(one, two, axis, toCentre);

    if(penetration < 0) return false;
    if(penetration < smallestPenetration) {
        smallestPenetration = penetration;
        smallestCase = index;
    }
    return true;
}
//------------------------------------------------------------------------------

void fillPointFaceBoxBox(const physics::CCollisionBox &one,
                         const physics::CCollisionBox &two,
                         const Vector3f &toCentre,
                         physics::SCollisionData *data,
                         unsigned best,
                         physics::real pen) {
    // This method is called when we know that a vertex from
    // box two is in contact with box one.

    physics::CContact* contact = data->contacts;

    // We know which axis the collision is on (i.e. best),
    // but we need to work out which of the two faces on
    // this axis.
    Vector3f normal = one.getAxis(best);
    if(math::dot(one.getAxis(best), toCentre) > 0) {
        normal = normal * -1.0f;
    }

    // Work out which vertex of box two we're colliding with.
    // Using toCentre doesn't work!
    Vector3f vertex = two.halfSize;
    if(math::dot(two.getAxis(0), normal) < 0) vertex.x = -vertex.x;
    if(math::dot(two.getAxis(1), normal) < 0) vertex.y = -vertex.y;
    if(math::dot(two.getAxis(2), normal) < 0) vertex.z = -vertex.z;

    // Create the contact data
    contact->contactNormal = normal;
    contact->penetration = pen;
    contact->contactPoint = physics::transform(two.getTransform(), vertex);
    contact->setBodyData(one.body, two.body, data->friction, data->restitution);
}
//------------------------------------------------------------------------------

static inline Vector3f contactPoint(const Vector3f &pOne,
                                    const Vector3f &dOne,
                                    physics::real oneSize,
                                    const Vector3f &pTwo,
                                    const Vector3f &dTwo,
                                    physics::real twoSize,

                                    // If this is true, and the contact point is outside
                                    // the edge (in the case of an edge-face contact) then
                                    // we use one's midpoint, otherwise we use two's.
                                    bool useOne) {
    Vector3f toSt, cOne, cTwo;
    physics::real dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
    physics::real denom, mua, mub;

    smOne = math::squareLength(dOne);
    smTwo = math::squareLength(dTwo);
    dpOneTwo = math::dot(dTwo, dOne);

    toSt = pOne - pTwo;
    dpStaOne = math::dot(dOne, toSt);
    dpStaTwo = math::dot(dTwo, toSt);

    denom = smOne * smTwo - dpOneTwo * dpOneTwo;

    // Zero denominator indicates parallel lines
    if(real_abs(denom) < 0.0001f) {
        return useOne ? pOne : pTwo;
    }

    mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
    mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

    // If either of the edges has the nearest point out
    // of bounds, then the edges aren't crossed, we have
    // an edge-face contact. Our point is on the edge, which
    // we know from the useOne parameter.
    if(mua > oneSize ||
       mua < -oneSize ||
       mub > twoSize ||
       mub < -twoSize) {
        return useOne ? pOne : pTwo;
    } else {
        cOne = pOne + dOne * mua;
        cTwo = pTwo + dTwo * mub;

        return cOne * ((physics::real)0.5) + cTwo * ((physics::real)0.5);
    }
}
//------------------------------------------------------------------------------

// This preprocessor definition is only used as a convenience
// in the boxAndBox contact generation method.
#define CHECK_OVERLAP(axis, index) \
    if (!tryAxis(one, two, (axis), toCentre, (index), pen, best)) return 0;

unsigned physics::CCollisionDetector::boxAndBox(const CCollisionBox &one,
                                                const CCollisionBox &two,
                                                SCollisionData *data) {
    //if (!IntersectionTests::boxAndBox(one, two)) return 0;

    if(!data) return 0;

    // Find the vector between the two centres
    Vector3f toCentre = two.getAxis(3) - one.getAxis(3);

    // We start assuming there is no contact
    real pen = REAL_MAX;
    unsigned best = 0xffffff;

    // Now we check each axes, returning if it gives us
    // a separating axis, and keeping track of the axis with
    // the smallest penetration otherwise.
    CHECK_OVERLAP(one.getAxis(0), 0);
    CHECK_OVERLAP(one.getAxis(1), 1);
    CHECK_OVERLAP(one.getAxis(2), 2);

    CHECK_OVERLAP(two.getAxis(0), 3);
    CHECK_OVERLAP(two.getAxis(1), 4);
    CHECK_OVERLAP(two.getAxis(2), 5);

    // Store the best axis-major, in case we run into almost
    // parallel edge collisions later
    unsigned bestSingleAxis = best;

    // Now on the cross products
    CHECK_OVERLAP(math::cross(one.getAxis(0), two.getAxis(0)), 6);
    CHECK_OVERLAP(math::cross(one.getAxis(0), two.getAxis(1)), 7);
    CHECK_OVERLAP(math::cross(one.getAxis(0), two.getAxis(2)), 8);
    CHECK_OVERLAP(math::cross(one.getAxis(1), two.getAxis(0)), 9);
    CHECK_OVERLAP(math::cross(one.getAxis(1), two.getAxis(1)), 10);
    CHECK_OVERLAP(math::cross(one.getAxis(1), two.getAxis(2)), 11);
    CHECK_OVERLAP(math::cross(one.getAxis(2), two.getAxis(0)), 12);
    CHECK_OVERLAP(math::cross(one.getAxis(2), two.getAxis(1)), 13);
    CHECK_OVERLAP(math::cross(one.getAxis(2), two.getAxis(2)), 14);

    // Make sure we've got a result.
    //assert(best != 0xffffff);
    if(best == 0xffffff)
        return 0;

    // We now know there's a collision, and we know which
    // of the axes gave the smallest penetration. We now
    // can deal with it in different ways depending on
    // the case.
    if(best < 3) {
        // We've got a vertex of box two on a face of box one.
        fillPointFaceBoxBox(one, two, toCentre, data, best, pen);
        data->addContacts(1);
        return 1;
    } else if(best < 6) {
        // We've got a vertex of box one on a face of box two.
        // We use the same algorithm as above, but swap around
        // one and two (and therefore also the vector between their
        // centres).
        fillPointFaceBoxBox(two, one, toCentre*-1.0f, data, best - 3, pen);
        data->addContacts(1);
        return 1;
    } else {
        // We've got an edge-edge contact. Find out which axes
        best -= 6;
        unsigned oneAxisIndex = best / 3;
        unsigned twoAxisIndex = best % 3;
        Vector3f oneAxis = one.getAxis(oneAxisIndex);
        Vector3f twoAxis = two.getAxis(twoAxisIndex);
        Vector3f axis = math::cross(oneAxis, twoAxis);
        //axis.normalise();
        axis = math::normalize(axis);

        // The axis should point from box one to box two.
        if(math::dot(axis, toCentre) > 0) axis = axis * -1.0f;

        // We have the axes, but not the edges: each axis has 4 edges parallel
        // to it, we need to find which of the 4 for each object. We do
        // that by finding the point in the centre of the edge. We know
        // its component in the direction of the box's collision axis is zero
        // (its a mid-point) and we determine which of the extremes in each
        // of the other axes is closest.
        Vector3f ptOnOneEdge = one.halfSize;
        Vector3f ptOnTwoEdge = two.halfSize;
        for(unsigned i = 0; i < 3; i++) {
            if(i == oneAxisIndex) ptOnOneEdge[i] = 0;
            else if(math::dot(one.getAxis(i), axis) > 0) ptOnOneEdge[i] = -ptOnOneEdge[i];

            if(i == twoAxisIndex) ptOnTwoEdge[i] = 0;
            else if(math::dot(two.getAxis(i), axis) < 0) ptOnTwoEdge[i] = -ptOnTwoEdge[i];
        }

        // Move them into world coordinates (they are already oriented
        // correctly, since they have been derived from the axes).
        ptOnOneEdge = physics::transform(one.transform, ptOnOneEdge);
        ptOnTwoEdge = physics::transform(two.transform, ptOnTwoEdge);

        // So we have a point and a direction for the colliding edges.
        // We need to find out point of closest approach of the two
        // line-segments.
        Vector3f vertex = contactPoint(ptOnOneEdge, oneAxis, one.halfSize[oneAxisIndex],
                                       ptOnTwoEdge, twoAxis, two.halfSize[twoAxisIndex],
                                       bestSingleAxis > 2);

        // We can fill the contact.
        CContact* contact = data->contacts;

        contact->penetration = pen;
        contact->contactNormal = axis;
        contact->contactPoint = vertex;
        contact->setBodyData(one.body, two.body,
                             data->friction, data->restitution);
        data->addContacts(1);
        return 1;
    }
    return 0;
}
#undef CHECK_OVERLAP
//------------------------------------------------------------------------------

unsigned physics::CCollisionDetector::boxAndPoint(const CCollisionBox &box,
                                                  const Vector3f &point,
                                                  SCollisionData *data) {
    // Transform the point into box coordinates
    Vector3f relPt = physics::transformInverse(box.transform, point);

    Vector3f normal;

    // Check each axis, looking for the axis on which the
    // penetration is least deep.
    real min_depth = box.halfSize.x - real_abs(relPt.x);
    if(min_depth < 0) return 0;
    normal = box.getAxis(0) * (real)((relPt.x < 0) ? -1 : 1);

    real depth = box.halfSize.y - real_abs(relPt.y);
    if(depth < 0) return 0;
    else if(depth < min_depth) {
        min_depth = depth;
        normal = box.getAxis(1) * (real)((relPt.y < 0) ? -1 : 1);
    }

    depth = box.halfSize.z - real_abs(relPt.z);
    if(depth < 0) return 0;
    else if(depth < min_depth) {
        min_depth = depth;
        normal = box.getAxis(2) * (real)((relPt.z < 0) ? -1 : 1);
    }

    // Compile the contact
    CContact* contact = data->contacts;
    contact->contactNormal = normal;
    contact->contactPoint = point;
    contact->penetration = min_depth;

    // Note that we don't know what rigid body the point
    // belongs to, so we just use NULL. Where this is called
    // this value can be left, or filled in.
    contact->setBodyData(box.body, NULL,
                         data->friction, data->restitution);

    data->addContacts(1);
    return 1;
}
//------------------------------------------------------------------------------

unsigned physics::CCollisionDetector::boxAndSphere(const CCollisionBox &box,
                                                   const CCollisionSphere &sphere,
                                                   SCollisionData *data) {
    if(!data) return 0;
    // Transform the centre of the sphere into box coordinates
    Vector3f centre = sphere.getAxis(3);
    Vector3f relCentre = physics::transformInverse(box.transform, centre);

    // Early out check to see if we can exclude the contact
    if(real_abs(relCentre.x) - sphere.radius > box.halfSize.x ||
       real_abs(relCentre.y) - sphere.radius > box.halfSize.y ||
       real_abs(relCentre.z) - sphere.radius > box.halfSize.z) {
        return 0;
    }

    Vector3f closestPt(0, 0, 0);
    real dist;

    // Clamp each coordinate to the box.
    dist = relCentre.x;
    if(dist > box.halfSize.x) dist = box.halfSize.x;
    if(dist < -box.halfSize.x) dist = -box.halfSize.x;
    closestPt.x = dist;

    dist = relCentre.y;
    if(dist > box.halfSize.y) dist = box.halfSize.y;
    if(dist < -box.halfSize.y) dist = -box.halfSize.y;
    closestPt.y = dist;

    dist = relCentre.z;
    if(dist > box.halfSize.z) dist = box.halfSize.z;
    if(dist < -box.halfSize.z) dist = -box.halfSize.z;
    closestPt.z = dist;

    // Check we're in contact
    dist = math::squareLength(closestPt - relCentre);
    if(dist > sphere.radius * sphere.radius) return 0;

    // Compile the contact
    Vector3f closestPtWorld = physics::transform(box.transform, closestPt);

    CContact* contact = data->contacts;
    contact->contactNormal = math::normalize(closestPtWorld - centre);
    //contact->contactNormal.normalise();
    contact->contactPoint = closestPtWorld;
    contact->penetration = sphere.radius - real_sqrt(dist);
    contact->setBodyData(box.body, sphere.body,
                         data->friction, data->restitution);

    data->addContacts(1);
    return 1;
}
//------------------------------------------------------------------------------

unsigned physics::CCollisionDetector::boxAndHalfSpace(const CCollisionBox &box,
                                                      const CCollisionPlane &plane,
                                                      SCollisionData *data) {
    if(!data || !data->contacts) return 0;

    // Make sure we have contacts
    if(data->contactsLeft <= 0) return 0;

    // Check for intersection
    if(!CIntersectionTest::boxAndHalfSpace(box, plane)) {
        return 0;
    }

    // We have an intersection, so find the intersection points. We can make
    // do with only checking vertices. If the box is resting on a plane
    // or on an edge, it will be reported as four or two contact points.

    // Go through each combination of + and - for each half-size
    static real mults[8][3] = {
        {1, 1, 1},
        {-1, 1, 1},
        {1, -1, 1},
        {-1, -1, 1},
        {1, 1, -1},
        {-1, 1, -1},
        {1, -1, -1},
        {-1, -1, -1}
    };

    CContact* contact = data->contacts;
    unsigned contactsUsed = 0;
    for(unsigned i = 0; i < 8; i++) {

        // Calculate the position of each vertex
        Vector3f vertexPos(mults[i][0], mults[i][1], mults[i][2]);
        //vertexPos.componentProductUpdate(box.halfSize);
        vertexPos = math::componentProduct(vertexPos, box.halfSize);
        //vertexPos = box.transform.transform(vertexPos);
        vertexPos = physics::transform(box.transform, vertexPos);

        // Calculate the distance from the plane
        real vertexDistance = math::dot(vertexPos, plane.direction);

        // Compare this to the plane's distance
        if(vertexDistance <= plane.offset) {
            // Create the contact data.

            // The contact point is halfway between the vertex and the
            // plane - we multiply the direction by half the separation
            // distance and add the vertex location.
            contact->contactPoint = plane.direction;
            contact->contactPoint *= (vertexDistance - plane.offset);
            contact->contactPoint += vertexPos;
            contact->contactNormal = plane.direction;
            contact->penetration = plane.offset - vertexDistance;

            // Write the appropriate data
            contact->setBodyData(box.body, NULL,
                                 data->friction, data->restitution);

            // Move onto the next contact
            contact++;
            contactsUsed++;
            if(contactsUsed == (unsigned)data->contactsLeft) return contactsUsed;
        }
    }

    data->addContacts(contactsUsed);
    return contactsUsed;
}
//------------------------------------------------------------------------------
