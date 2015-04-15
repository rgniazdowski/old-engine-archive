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
 * File:   fgGFXTreeNode.cpp
 * Author: vigilant
 *
 * Created on February 18, 2015, 4:50 AM
 */

#include "fgGfxTreeNode.h"
#include "fgGfxSceneNode.h"

using namespace fg;

fgBool gfx::STreeNodeBase::removeObject(CTreeNodeObject* pObject) {
    if(!pObject || objects.empty())
        return FG_FALSE;
    const int index = objects.find(pObject);
    const unsigned int objCount = objects.size();
    if(index != -1) {
        pObject->setTreeNode(NULL);
        objects[index] = objects[objCount - 1];
        objects[objCount - 1] = NULL;
        objects.resize(objCount - 1);
        return FG_TRUE;
    } else {
        return FG_FALSE;
    }
}
