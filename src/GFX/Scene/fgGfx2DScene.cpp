/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGfx2DScene.h"

/**
 * 
 */
fg::gfx::CScene2D::CScene2D() {
    getMVP()->setOrtho(0.0f, 1024.0f, 768.0f, 0.0f);
}

/**
 * 
 */
fg::gfx::CScene2D::~CScene2D() {
    
}
