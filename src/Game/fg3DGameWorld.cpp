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
 * File:   fg3DGameWorld.cpp
 * Author: vigilant
 * 
 * Created on September 23, 2015, 8:00 PM
 */

#include "fg3DGameWorld.h"

using namespace fg;
//------------------------------------------------------------------------------

game::CGameWorld3D::CGameWorld3D() :
base_type(),
scene_type() { }
//------------------------------------------------------------------------------

game::CGameWorld3D::CGameWorld3D(const CGameWorld3D& orig) {
    // #FIXME
}
//------------------------------------------------------------------------------

game::CGameWorld3D::~CGameWorld3D() {
    self_type::destroy();
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld3D::initialize(void) {
    fgBool status = base_type::initialize();
    status = (fgBool)(scene_type::initialize() && status);

    return status;
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld3D::destroy(void) {
    fgBool status = base_type::destroy();
    status = (fgBool)(scene_type::destroy() && status);

    return status;
}
//------------------------------------------------------------------------------
