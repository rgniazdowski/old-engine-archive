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
    return status;
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld::destroy(void) {
    fgBool status = base_type::destroy();
    status = (fgBool)(physical_world::destroy() && status);
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