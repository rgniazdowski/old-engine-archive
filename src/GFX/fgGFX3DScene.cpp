/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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
#include "fgGFXSceneNode.h"

/**
 * 
 */
fg::gfx::CScene3D::CScene3D() :
CSceneManager() {
    getMVP()->setPerspective(45.0f, 4.0f / 3.0f);
}

/**
 * 
 */
fg::gfx::CScene3D::~CScene3D() { }

/**
 * 
 */
void fg::gfx::CScene3D::sortCalls(void) {
    CSceneManager::sortCalls();
}

/**
 * 
 */
void fg::gfx::CScene3D::render(void) {
    CSceneManager::render();
}

/**
 * 
 * @param pModelRes
 * @param nameTag
 * @return 
 */
fg::gfx::CSceneNode *fg::gfx::CScene3D::addFromModel(CModelResource* pModelRes,
                                           const std::string& nameTag) {
    if(!pModelRes) {
        return NULL;
    }
    CSceneNode *pNode = new CSceneNodeObject(pModelRes, NULL);
    //fgGfxSceneNodeObject *pNodeObject = static_cast<fgGfxSceneNodeObject *>(pNode);
    pNode->setName(nameTag);
    if(!addNode(pNode->getRefHandle(), pNode)) {
        delete pNode;
        pNode = NULL;
    }
    return pNode;
}

/**
 * 
 * @param modelNameTag
 * @param nameTag
 * @return 
 */
fg::gfx::CSceneNode *fg::gfx::CScene3D::addFromModel(const std::string& modelNameTag,
                                           const std::string& nameTag) {
    if(modelNameTag.empty() || nameTag.empty()) {
        return NULL;
    }
    fgResourceManager *pResourceManager = static_cast<fgResourceManager *>(getResourceManager());
    if(!pResourceManager) {
        return NULL;
    }
    CModelResource *pModelRes = static_cast<CModelResource *>(pResourceManager->get(modelNameTag));
    if(!pModelRes) {
        return NULL;
    }
    return addFromModel(pModelRes, nameTag);
}

/**
 * 
 * @param modelNameTag
 * @param nameTag
 * @return 
 */
fg::gfx::CSceneNode *fg::gfx::CScene3D::addFromModel(const char *modelNameTag,
                                           const char *nameTag) {
    if(!modelNameTag || !nameTag) {
        return NULL;
    }
    fgResourceManager *pResourceManager = static_cast<fgResourceManager *>(getResourceManager());
    if(!pResourceManager) {
        return NULL;
    }
    CModelResource *pModelRes = static_cast<CModelResource *>(pResourceManager->get(modelNameTag));
    if(!pModelRes) {
        return NULL;
    }
    // #FIXME char * / std::string !
    return addFromModel(pModelRes, std::string(nameTag));
}