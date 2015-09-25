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
 * File:   fgPhysical.cpp
 * Author: vigilant
 * 
 * Created on September 23, 2015, 9:21 PM
 */

#include "fgPhysical.h"

#if defined(FG_USING_BULLET)
//#include "btBulletDynamicsCommon.h"
#include "Physics/fgPhysics.h"
#endif /* FG_USING_BULLET */

using namespace fg;
//------------------------------------------------------------------------------

physics::traits::CPhysical::CPhysical() :
m_collisionBody(NULL) {
    // m_collisionBody needs to be explicitely initialized by master class
}
//------------------------------------------------------------------------------

physics::traits::CPhysical::CPhysical(const CPhysical& orig) {
    // #FIXME
}
//------------------------------------------------------------------------------

physics::traits::CPhysical::~CPhysical() {
    // if m_collisionBody is initialized, it will be destroyed here
    if(m_collisionBody)
        delete m_collisionBody;
    // now CCollisionBody should have some kind of destruction callback set
    // similar to CManagedObject (however custom), so it will be removed from
    // physical world automatically.
    m_collisionBody = NULL;
}
//------------------------------------------------------------------------------

physics::CCollisionBody* physics::traits::CPhysical::getCollisionBody(void) {
    return m_collisionBody;
}
//------------------------------------------------------------------------------

physics::CCollisionBody const* physics::traits::CPhysical::getCollisionBody(void) const {
    return m_collisionBody;
}
//------------------------------------------------------------------------------

physics::CCollisionBody::BodyType physics::traits::CPhysical::getBodyType(void) const {
    if(!m_collisionBody)
        return CCollisionBody::INVALID;
    return m_collisionBody->getBodyType();
}
//------------------------------------------------------------------------------

fgBool physics::traits::CPhysical::hasCollisionBody(void) const {
    return (fgBool)!!(m_collisionBody != NULL);
}
//------------------------------------------------------------------------------

fgBool physics::traits::CPhysical::setupCollisionBody(CCollisionBody::BodyType bodyType) {
    if(bodyType == CCollisionBody::INVALID)
        return FG_FALSE;

    if(getBodyType() != bodyType) {
        if(!m_collisionBody) {
            m_collisionBody = new physics::CCollisionBody(bodyType);
        } else {
            m_collisionBody->setupBody(bodyType); // cause we friends...
        }
        // now we cannot setup collision body so easily,
        // just create a new one....
        // if the collision body is already inside of physical world,
        // it needs to be removed first and then reinserted smoothly
    }
}
//------------------------------------------------------------------------------
