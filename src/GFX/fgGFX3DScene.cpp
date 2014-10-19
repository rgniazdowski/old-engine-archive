/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFX3DScene.h"
#include "Shaders/fgGFXShaderManager.h"
#include "Textures/fgTextureResource.h"
#include "Resource/fgResourceManager.h"

/**
 * 
 */
fgGfx3DScene::fgGfx3DScene() :
fgGfxSceneManager() {
    getMVP()->setPerspective(45.0f, 4.0f / 3.0f);
}

/**
 * 
 */
fgGfx3DScene::~fgGfx3DScene() { 
}

/**
 * 
 */
void fgGfx3DScene::flush(void) { 
    fgGfxSceneManager::flush();
}

/**
 * 
 */
void fgGfx3DScene::sortCalls(void) {
    fgGfxSceneManager::sortCalls();
}

/**
 * 
 */
void fgGfx3DScene::render(void) {
    fgGfxSceneManager::render();
}

/**
 * 
 * @param pModelRes
 * @param nameTag
 * @return 
 */
fgGfxObject *fgGfx3DScene::addFromModel(fgGfxModelResource* pModelRes,
                                        const std::string& nameTag) {
    if(!pModelRes) {
        return NULL;
    }
    fgGfxObject *pObj = new fgGfxObject();
    pObj->setName(nameTag);
    pObj->setModel(pModelRes);
    if(!addObject(pObj->getRefHandle(), pObj)) {
        delete pObj;
        pObj = NULL;
    }
    return pObj;
}
