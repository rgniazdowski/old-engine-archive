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
 * File:   fgIntelligentWorld.cpp
 * Author: vigilant
 * 
 * Created on September 23, 2015, 9:46 PM
 */

#include "fgIntelligentWorld.h"

using namespace fg;
//------------------------------------------------------------------------------

game::CIntelligentWorld::CIntelligentWorld() { }
//------------------------------------------------------------------------------

game::CIntelligentWorld::CIntelligentWorld(const CIntelligentWorld& orig) { }
//------------------------------------------------------------------------------

game::CIntelligentWorld::~CIntelligentWorld() { }
//------------------------------------------------------------------------------

fgBool game::CIntelligentWorld::initialize(void) {
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool game::CIntelligentWorld::destroy(void) {
    return FG_TRUE;
}
//------------------------------------------------------------------------------
