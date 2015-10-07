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
 * File:   fgGameWorld.cpp
 * Author: vigilant
 * 
 * Created on September 24, 2015, 4:59 PM
 */

#include "fgGameWorld.h"
#include "GFX/Scene/fgGfxSceneManager.h"
#include "Physics/fgPhysical.h"

using namespace fg;
//------------------------------------------------------------------------------

game::CGameWorld::CGameWorld(gfx::CSceneManager* pSceneMgr) :
base_type(),
physical_world(),
m_pSceneMgr(pSceneMgr),
m_sceneNodeInsertedCallback(NULL) {
}
//------------------------------------------------------------------------------

game::CGameWorld::CGameWorld(const CGameWorld& orig) : self_type(orig.m_pSceneMgr) {
    // #FIXME
}
//------------------------------------------------------------------------------

game::CGameWorld::~CGameWorld() { }
//------------------------------------------------------------------------------

fgBool game::CGameWorld::initialize(void) {
    fgBool status = base_type::initialize();
    status = (fgBool)(physical_world::initialize() && status);
    registerCallbacks();
    return status;
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld::destroy(void) {
    fgBool status = base_type::destroy();
    status = (fgBool)(physical_world::destroy() && status);
    unregisterCallbacks();
    m_pSceneMgr = NULL;
    return status;
}
//------------------------------------------------------------------------------

void game::CGameWorld::update(float delta) {
    base_type::update(delta); // intelligent world

    physical_world::update(delta);
}
//------------------------------------------------------------------------------

gfx::CSceneManager* game::CGameWorld::getSceneManager(void) const {
    return m_pSceneMgr;
}
//------------------------------------------------------------------------------

void game::CGameWorld::registerCallbacks(void) {
    if(!m_pSceneMgr)
        return;

    if(!m_sceneNodeInsertedCallback) {
        m_sceneNodeInsertedCallback =
                new event::CMethodCallback<self_type>(this,
                                                      &self_type::sceneNodeInsertedHandler);
    }

    m_pSceneMgr->getInternalEventManager()->addCallback(event::SCENE_NODE_INSERTED,
                                                        m_sceneNodeInsertedCallback);

    //m_pSceneMgr->getInternalEventManager()->addCallback(event::SCENE_NODE_DESTROYED)
}
//------------------------------------------------------------------------------

void game::CGameWorld::unregisterCallbacks(void) {
    if(!m_pSceneMgr)
        return;

}
//------------------------------------------------------------------------------

fgBool game::CGameWorld::sceneNodeInsertedHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SSceneEvent* pEventStruct = (event::SSceneEvent*)argv->getValueByID(0);
    gfx::CSceneManager* pSceneManager = (gfx::CSceneManager*)argv->getValueByID(1);
    if(!pEventStruct)
        return FG_FALSE;
    event::EventType type = pEventStruct->code;
    if(type != event::SCENE_NODE_INSERTED)
        return FG_FALSE;
    if(!pSceneManager) {
        return FG_FALSE;
    }
    if(!pSceneManager->isManaged(pEventStruct->node.handleNodeA)) {
        return FG_FALSE;
    }
    if(!pEventStruct->node.pNodeA) {
        return FG_FALSE;
    }
    // Now this callback is for automated adding nodes with physical traits
    // to the physical world
    physics::traits::CPhysical* pPhysical = NULL;
    fgBool status = FG_FALSE;
    if(pEventStruct->node.pNodeA->queryTrait(fg::traits::PHYSICAL, (void**)&pPhysical)) {
        if(pPhysical->hasCollisionBody()) {
            physical_world::add(pPhysical->getCollisionBody());
            status = FG_TRUE;
        }
    }
    return status;
}
//------------------------------------------------------------------------------