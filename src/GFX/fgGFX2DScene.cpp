/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFX2DScene.h"

/**
 * 
 */
fgGfx2DScene::fgGfx2DScene() {
    getMVP()->setOrtho(0.0f, 1024.0f, 768.0f, 0.0f);
}

/**
 * 
 */
fgGfx2DScene::~fgGfx2DScene() {
    
}
