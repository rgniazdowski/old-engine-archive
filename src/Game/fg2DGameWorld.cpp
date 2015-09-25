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
 * File:   fg2DGameWorld.cpp
 * Author: vigilant
 * 
 * Created on September 23, 2015, 8:00 PM
 */

#include "fg2DGameWorld.h"

using namespace fg;
//------------------------------------------------------------------------------

game::CGameWorld2D::CGameWorld2D() :
base_type(),
scene_type() {
    this->setLayerName("game::CGameWorld2D");
    this->setLayerID(16);
}
//------------------------------------------------------------------------------

game::CGameWorld2D::CGameWorld2D(const CGameWorld2D& orig) {
    //#FIXME
}
//------------------------------------------------------------------------------

game::CGameWorld2D::~CGameWorld2D() {
    self_type::destroy();
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld2D::initialize(void) {
    fgBool status = base_type::initialize();
    status = (fgBool)(scene_type::initialize() && status);

    return status;
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld2D::destroy(void) {
    fgBool status = base_type::destroy();
    status = (fgBool)(scene_type::destroy() && status);

    return status;
}
//------------------------------------------------------------------------------
