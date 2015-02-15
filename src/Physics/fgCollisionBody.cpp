/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
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
            if(orig.m_collisionPrim)
                *(this->m_collisionPrim) = *(orig.m_collisionPrim);
            this->m_collisionPrim->body = this;
            // #TODO
        }
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
        return false;
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
    return collide;
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
