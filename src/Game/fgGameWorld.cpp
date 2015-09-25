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

using namespace fg;
//------------------------------------------------------------------------------

game::CGameWorld::CGameWorld() :
base_type(),
physical_world() { }
//------------------------------------------------------------------------------

game::CGameWorld::CGameWorld(const CGameWorld& orig) {
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

    return status;
}
//------------------------------------------------------------------------------

void game::CGameWorld::update(float delta) {
    base_type::update(delta); // intelligent world

    physical_world::update(delta);
}
//------------------------------------------------------------------------------