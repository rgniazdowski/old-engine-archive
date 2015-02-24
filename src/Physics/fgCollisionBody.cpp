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
 * Interface file for the collision body class.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */
/* 
 * File:   fgCollisionBody.cpp
 * Author: vigilant
 * 
 * Created on February 7, 2015, 1:31 PM
 */

#include "fgCollisionBody.h"

using namespace fg;

/**
 * 
 * @param bodyType
 */
physics::CCollisionBody::CCollisionBody(const BodyType bodyType) :
m_collisionPrim(NULL),
m_bodyType(INVALID) {
    setBodyType(bodyType);
}

/**
 * 
 * @param orig
 */
physics::CCollisionBody::CCollisionBody(const CCollisionBody& orig) {
    if(&orig != this) {
        this->m_bodyType = orig.m_bodyType;
        if(this->m_bodyType == BOX) {
            this->m_collisionPrim = new CCollisionBox();
            if(orig.m_collisionPrim) {
                *(this->m_collisionPrim) = *(orig.m_collisionPrim);
            }
            this->m_collisionPrim->body = this;
            this->setHalfSize(orig.getHalfSize());
            // #TODO
        } else if(this->m_bodyType == SPHERE) {
            this->m_collisionPrim = new CCollisionSphere();
            if(orig.m_collisionPrim) {
                *(this->m_collisionPrim) = *(orig.m_collisionPrim);
            }
            this->m_collisionPrim->body = this;
            this->setRadius(orig.getRadius());
        }
        this->setMass(orig.getMass());
        this->setInverseInertiaTensor(orig.getInverseInertiaTensor());
        
        this->setDamping(orig.getLinearDamping(), orig.getAngularDamping());
        this->setAcceleration(orig.getAcceleration());
        this->setPosition(orig.getPosition());
        this->setOrientation(orig.getOrientation());
        this->setRotation(orig.getRotation());
        
        this->setAwake(orig.getAwake());
        this->setCanSleep(orig.getCanSleep());
        
        this->calculateDerivedData();
        this->integrate(0.0f);
    }
}

/**
 * 
 */
physics::CCollisionBody::~CCollisionBody() {
    if(m_collisionPrim) {
        m_collisionPrim->body = NULL;
        delete m_collisionPrim;
    }
}

/**
 * 
 */
void physics::CCollisionBody::setInertiaTensor(void) { 
    if(m_bodyType == BOX) {
        setInertiaTensor(getHalfSize(), getMass());
    } else if(m_bodyType == SPHERE) {
        setInertiaTensor(getRadius(), getMass());
    }
}

/**
 * 
 * @param halfSize
 * @param mass
 */
void physics::CCollisionBody::setInertiaTensor(const Vector3f& halfSize, float mass) {
    setMass(mass);
    setHalfSize(halfSize);
    setInertiaTensor(physics::setBlockInertiaTensor(halfSize, mass));
}

/**
 * 
 * @param radius
 * @param mass
 */
void physics::CCollisionBody::setInertiaTensor(float radius, float mass) {
    setMass(mass);
    setRadius(radius);
    //float volume = (4.0f)/3.0f * M_PIF * math::pow(radius, 3.0f); 
    // 2/5 * Mass * radius * radius
    float sphereI = 2.0f / 5.0f * mass * radius * radius;
    setInertiaTensor(physics::setInertiaTensorCoeffs(sphereI, sphereI, sphereI));
    //setInertiaTensor(physics::setBlockInertiaTensor(halfSize, mass));
}

/**
 * 
 * @param mass
 */
void physics::CCollisionBody::setMassPerUnit(float mass) {
    if(mass < FG_EPSILON)
        return;
    if(m_collisionPrim && m_bodyType == BOX) {
        const Vector3f& halfSize = getCollisionBox()->halfSize;
        setMass(mass * halfSize.x * halfSize.y * halfSize.z);
    } else if(m_collisionPrim && m_bodyType == SPHERE) {
        real a = (2.0f * getCollisionSphere()->radius) / M_SQRT2;
        setMass(mass * a * a * a);
    }
}

/**
 * 
 * @param halfSize
 */
void physics::CCollisionBody::setHalfSize(const Vector3f& halfSize) {
    if(m_collisionPrim && m_bodyType == BOX) {
        getCollisionBox()->halfSize = halfSize;
    } else if(m_collisionPrim && m_bodyType == SPHERE) {
        getCollisionSphere()->radius = math::length(halfSize);
    }
}

/**
 * 
 * @return 
 */
Vector3f physics::CCollisionBody::getHalfSize(void) const {
    if(m_collisionPrim && m_bodyType == BOX) {
        return getCollisionBox()->halfSize;
    } else if(m_collisionPrim && m_bodyType == SPHERE) {
        //float a = (2.0f * getCollisionSphere()->radius) / M_SQRT2;
        float a = math::sqrt((getCollisionSphere()->radius * getCollisionSphere()->radius) / 3.0f);
        return Vector3f(a, a, a);
    }
    return Vector3f();
}

/**
 * 
 * @param radius
 */
void physics::CCollisionBody::setRadius(real radius) {
    if(radius < 0.0f)
        radius *= -1.0f;
    if(m_collisionPrim && m_bodyType == BOX) {
        //real a = (2.0f * radius) / M_SQRT2;
        real a = math::sqrt((radius * radius) / 3.0f);
        getCollisionBox()->halfSize = Vector3f(a, a, a);
    } else if(m_collisionPrim && m_bodyType == SPHERE) {
        getCollisionSphere()->radius = radius;
    }
}

/**
 * 
 * @return 
 */
float physics::CCollisionBody::getRadius(void) const {
    if(m_collisionPrim && m_bodyType == BOX) {
        return math::length(getCollisionBox()->halfSize);
    } else if(m_collisionPrim && m_bodyType == SPHERE) {
        return getCollisionSphere()->radius;
    }
    return 0.0f;
}

/**
 * 
 * @param bodyType
 */
void physics::CCollisionBody::setBodyType(const BodyType bodyType) {
    if(m_collisionPrim && m_bodyType == bodyType)
        return;
    m_bodyType = bodyType;
    if(m_bodyType == BOX) {
        m_collisionPrim = new CCollisionBox();
        m_collisionPrim->body = this;
    } else {
        m_collisionPrim = new CCollisionSphere();
        m_collisionPrim->body = this;
    }
}

/**
 * 
 * @param body
 * @param cData
 * @return 
 */
fgBool physics::CCollisionBody::checkCollision(CCollisionBody* body,
                                               SCollisionData *cData) {
    if(!body || !cData) {
        return FG_FALSE;
    }
    bool collide = false;
    // #LOL
    if(m_bodyType == BOX) {
        if(body->getBodyType() == BOX) {
            collide = CCollisionDetector::boxAndBox(*getCollisionBox(),
                                                    *(body->getCollisionBox()), cData);
        } else if(body->getBodyType() == SPHERE) {
            collide = CCollisionDetector::boxAndSphere(*getCollisionBox(),
                                                       *(body->getCollisionSphere()), cData);
        }
    } else if(m_bodyType == SPHERE) {
        if(body->getBodyType() == BOX) {
            collide = CCollisionDetector::boxAndSphere(*(body->getCollisionBox()),
                                                       *getCollisionSphere(), cData);
        } else if(body->getBodyType() == SPHERE) {
            collide = CCollisionDetector::sphereAndSphere(*getCollisionSphere(),
                                                          *(body->getCollisionSphere()), cData);
        }
    } else {

    }
    return (fgBool)collide;
}

/**
 * 
 * @param plane
 * @param cData
 * @return 
 */
fgBool physics::CCollisionBody::checkCollision(const CCollisionPlane& plane,
                                               SCollisionData* cData) {
    if(!cData) {
        return false;
    }
    bool collide = false;
    if(m_bodyType == BOX) {
        collide = CCollisionDetector::boxAndHalfSpace(*getCollisionBox(), plane, cData);
    } else if(m_bodyType == SPHERE) {
        collide = CCollisionDetector::sphereAndTruePlane(*getCollisionSphere(), plane, cData);
    }
    return collide;
}
