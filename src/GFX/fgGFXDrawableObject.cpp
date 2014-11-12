/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXDrawableObject.cpp
 * Author: vigilant
 * 
 * Created on November 12, 2014, 6:08 PM
 */

#include "fgGFXDrawableObject.h"

/**
 * 
 */
fgGfxDrawableObject::fgGfxDrawableObject() :
fgGfxObject(),
fgGfxDrawCall() { 
    fgGfxObject::setType(FG_GFX_OBJECT_DRAWABLE_PLAIN);
}

/**
 * 
 * @param orig
 */
fgGfxDrawableObject::fgGfxDrawableObject(const fgGfxDrawableObject& orig) { }

/**
 * 
 */
fgGfxDrawableObject::~fgGfxDrawableObject() { }

