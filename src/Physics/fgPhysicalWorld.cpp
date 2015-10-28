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
 * File:   fgPhysicalWorld.cpp
 * Author: vigilant
 * 
 * Created on September 24, 2015, 12:15 PM
 */

#include "fgPhysicalWorld.h"
#if defined(FG_USING_BULLET)
#include "btBulletDynamicsCommon.h"
#endif /* FG_USING_BULLET */

#include "fgVector.h"

using namespace fg;
//------------------------------------------------------------------------------

physics::CPhysicalWorld::CPhysicalWorld() :
m_collisionBodies(),
#if defined(FG_USING_BULLET)
m_collisionConfig(NULL),
m_dynamicsWorld(NULL),
m_broadphase(NULL),
m_dispatcher(NULL),
m_solver(NULL),
#elif defined(FG_USING_CYCLONE)
        // cyclone internal
#else
        // not bullet nor cyclone - dummy
#endif
m_init(FG_FALSE) { }
//------------------------------------------------------------------------------

physics::CPhysicalWorld::CPhysicalWorld(const CPhysicalWorld& orig) { }
//------------------------------------------------------------------------------

physics::CPhysicalWorld::~CPhysicalWorld() {
    destroy();
}
//------------------------------------------------------------------------------

fgBool physics::CPhysicalWorld::initialize(void) {
#if defined(FG_USING_BULLET)
    if(m_init)
        return FG_FALSE;
    ///collision configuration contains default setup for memory, collision setup
    m_collisionConfig = new btDefaultCollisionConfiguration();
    //m_collisionConfiguration->setConvexConvexMultipointIterations();

    // Use the default collision dispatcher.
    // For parallel processing you can use a different dispatcher
    // (see Extras/BulletMultiThreaded)
    m_dispatcher = new btCollisionDispatcher(m_collisionConfig);
    m_broadphase = new btDbvtBroadphase();

    // The default constraint solver.
    // For parallel processing you can use a different solver
    // (see Extras/BulletMultiThreaded)
    m_solver = new btSequentialImpulseConstraintSolver();

    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,
                                                  m_broadphase,
                                                  m_solver,
                                                  m_collisionConfig);

    m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

#elif defined(FG_USING_CYCLONE)
    // cyclone internal
#else
    // not bullet nor cyclone
#endif

    m_init = FG_TRUE;
    return m_init;
}
//------------------------------------------------------------------------------

fgBool physics::CPhysicalWorld::destroy(void) {
#if defined(FG_USING_BULLET)
    if(!m_init)
        return FG_FALSE;
    int i = 0;
    if(m_dynamicsWorld) {
        for(i = m_dynamicsWorld->getNumConstraints() - 1; i >= 0; i--) {
            m_dynamicsWorld->removeConstraint(m_dynamicsWorld->getConstraint(i));
        }
        for(i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
            btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
            //CCollisionBody* body = CCollisionBody::upcast(obj);
            m_dynamicsWorld->removeCollisionObject(obj);
        }
    }
    m_collisionBodies.clear();
    if(m_dynamicsWorld)
        delete m_dynamicsWorld;
    m_dynamicsWorld = NULL;

    if(m_solver)
        delete m_solver;
    m_solver = NULL;

    if(m_broadphase)
        delete m_broadphase;
    m_broadphase = NULL;

    if(m_dispatcher)
        delete m_dispatcher;
    m_dispatcher = NULL;

    if(m_collisionConfig)
        delete m_collisionConfig;
    m_collisionConfig = NULL;

#elif defined(FG_USING_CYCLONE)
    // cyclone internal
#else
    // not bullet nor cyclone
#endif
    m_init = FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void physics::CPhysicalWorld::update(float delta) {
#if defined(FG_USING_BULLET)
    if(!m_init)
        return;
    if(m_dynamicsWorld)
        m_dynamicsWorld->stepSimulation(delta);
#elif defined(FG_USING_CYCLONE)
#else
#endif
}
//------------------------------------------------------------------------------

void physics::CPhysicalWorld::setupOwnerFor(CAbstractCollisionBody* pBody) {
#if defined(FG_USING_BULLET)
    pBody->setOwner(m_dynamicsWorld);
#elif defined(FG_USING_CYCLONE)
    pBody->setOwner(NULL);
#else
    pBody->setOwner(NULL);
#endif
}
//------------------------------------------------------------------------------

int physics::CPhysicalWorld::add(CCollisionBody* pBody) {
#if defined(FG_USING_BULLET)
    if(!pBody)
        return -1;
    int index = m_collisionBodies.find(pBody);
    if(index < 0) {
        m_collisionBodies.push_back(pBody);
        m_dynamicsWorld->addRigidBody(pBody);
        pBody->setOwner(m_dynamicsWorld);
        index = m_collisionBodies.size() - 1;
        return index;
    }
    if(!m_dynamicsWorld)
        return index;
    fgBool found = FG_FALSE;
    for(int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
        btCollisionObject* pObject = m_dynamicsWorld->getCollisionObjectArray()[i];
        CRigidBody* pRigidBody = CRigidBody::upcast(pObject);
        if(pRigidBody == static_cast<CRigidBody*>(pBody)) {
            found = FG_TRUE;
            pBody->setOwner(m_dynamicsWorld);
            break;
        }
    } // for every collision object
    if(!found) {
        m_dynamicsWorld->addRigidBody(pBody);
        m_dynamicsWorld->updateSingleAabb(pBody);
        pBody->setOwner(m_dynamicsWorld);
    }
    return index;
#elif defined(FG_USING_CYCLONE)
    return -1;
#else
    return -1;
#endif
}
//------------------------------------------------------------------------------

fgBool physics::CPhysicalWorld::remove(CCollisionBody* pBody) {
#if defined(FG_USING_BULLET)
    if(!pBody)
        return FG_FALSE;
    int index = m_collisionBodies.find(pBody);
    if(index >= 0) {
        m_collisionBodies.remove(index);

        if(m_dynamicsWorld) {
            //m_dynamicsWorld->removeCollisionObject(pBody);
            m_dynamicsWorld->removeRigidBody(pBody);
            pBody->setOwner(NULL);
        }
    }
    return (fgBool)(index >= 0);
#elif defined(FG_USING_CYCLONE)
    return FG_FALSE;
#else
    return FG_FALSE;
#endif
}
//------------------------------------------------------------------------------

fgBool physics::CPhysicalWorld::removeAllCollisionBodies(void) {
#if defined(FG_USING_BULLET)
    if(!m_dynamicsWorld)
        return FG_FALSE;
    const unsigned int n = m_collisionBodies.size();
    if(!n)
        return FG_FALSE;
    for(unsigned int i = 0; i < n; i++) {
        CCollisionBody* pBody = m_collisionBodies[i];
        if(!pBody)
            continue;
        m_dynamicsWorld->removeRigidBody(pBody);
        pBody->setOwner(NULL);
    }
    m_collisionBodies.clear();
    return FG_TRUE;
#elif defined(FG_USING_CYCLONE)
    return FG_TRUE;
#else
    return FG_TRUE;
#endif
}
//------------------------------------------------------------------------------
