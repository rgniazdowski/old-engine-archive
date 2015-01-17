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
#include "fgGFXLooseOctree.h"
#include "fgDebugConfig.h"

#if defined(FG_DEBUG)
#include "Util/fgProfiling.h"
#include "fgGFXQuadtree.h"
#endif

using namespace fg;

/**
 *  
 */
gfx::CScene3D::CScene3D() :
CSceneManager(),
m_octree(NULL) {
    getMVP()->setPerspective(45.0f, 4.0f / 3.0f);
    m_octree = new CLooseOctree();
}

/**
 * 
 */
gfx::CScene3D::~CScene3D() {
    if(m_octree)
        delete m_octree;
    m_octree = NULL;
    while(m_octNodes.size())
        m_octNodes.pop();
}

/**
 * 
 */
void gfx::CScene3D::sortCalls(void) {
    if(!getShaderManager())
        return;
    getMVP()->setCamera((CCamera *)(getCamera()));
    CFrustum &frustum = getMVP()->getRefFrustum();

    // Remove from the queue any remaining nodes (SceneNode)
    while(!getNodeQueue().empty())
        getNodeQueue().pop();

    ////////////////////////////////////////////////////////////////////////////
    // PHASE I: Iterate through all objects, animate, update AABB, collisions...
    ////////////////////////////////////////////////////////////////////////////
    DataVecItor itor = getRefDataVector().begin(), end = getRefDataVector().end();
    for(; itor != end; itor++) {
        if(!(*itor))
            continue;
        CSceneNode *sceneNode = (*itor);
        SOctreeNode *treeNode = static_cast<SOctreeNode *>(sceneNode->getTreeNode());
        sceneNode->setVisible(FG_FALSE);
        // There is a problem because the bounding box needs to be modified by
        // the model matrix; maybe some operator ?
        sceneNode->updateAABB();
        checkCollisions(sceneNode);
        if(treeNode) {
            unsigned int objCount = treeNode->objects.size();
            float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << treeNode->depth);
            // Check bounds of this scene node - if does not fit - reinsert to different tree node - slow...
            if(m_octree->fitsInBox(sceneNode, treeNode->center, halfSize)) {
                printf("%s fits in box depth %d\n", sceneNode->getNameStr(), treeNode->depth);
            } else {
                int objIdx = treeNode->objects.find(sceneNode);
                if(objIdx != -1) {
                    sceneNode->setTreeNode(NULL);
                    treeNode->objects[objIdx] = treeNode->objects[objCount - 1];
                    treeNode->objects[objCount - 1] = NULL;
                    treeNode->objects.resize(objCount - 1);
                    m_octree->insert(sceneNode);
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // PHASE II: Traverse the tree, check visibility, update nodes
    ////////////////////////////////////////////////////////////////////////////
    m_octree->rewind();
    printf(".......................\n");
    while(m_octree->next()) {
        SOctreeNode *treeNode = static_cast<SOctreeNode *>(m_octree->current());
        unsigned int objCount = treeNode->objects.size();
        float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << treeNode->depth);
        m_octNodes.push(treeNode);
        if(frustum.testVolume(treeNode->center, halfSize) == CFrustum::OUTSIDE) {
            // Skip this tree node - it's completely outside of the frustum
            // Octree traverse functions needs to have special func for skipping
            m_octree->skip();
            continue;
        }
        for(unsigned int objIdx = 0; objIdx < objCount; objIdx++) {
            CSceneNode *sceneNode = treeNode->objects[objIdx];
            if(!sceneNode) {
                continue;
            }
            if(sceneNode->isVisible()) {
                continue;
            }

            CDrawCall *pDrawCall = sceneNode->getDrawCall();
#if defined(FG_DEBUG)
            if(g_fgDebugConfig.isDebugProfiling) {
                profile::g_debugProfiling->begin("GFX::Scene::FrustumCheck");
            }
#endif
            int boxtest = frustum.testVolume(sceneNode->getRefBoundingVolume());
            //int spheretest = (int)m_MVP.getRefFrustum().testSphere(fgVector3f(pNode->getRefModelMatrix()[3]), 30.0f);
            if(!boxtest)
                sceneNode->setVisible(FG_FALSE);
            else
                sceneNode->setVisible(FG_TRUE);
#if defined(FG_DEBUG)
            if(g_fgDebugConfig.isDebugProfiling) {
                profile::g_debugProfiling->end("GFX::Scene::FrustumCheck");
            }
#endif
            g_fgDebugConfig.gfxBBoxShow = true;
            // ? also need to push to queue more than one draw call
            // And i mean... wait wut? All children are registered
            // This is a tree - that needs to be traversed
            // There is no need to go through all (linear) objects through the scene
            // The aabb for each object is updated based on the children
            // Need some standard for manipulating this objects, and also for traversing
            // the tree. Also one would need some standard for special kind of tree - loose octrees? bitch?
            if(sceneNode->isVisible()) {
                getNodeQueue().push(sceneNode);
                printf("going to draw %s\n", sceneNode->getNameStr());
            }
            if(pDrawCall) {
                if(!pDrawCall->getShaderProgram())
                    pDrawCall->setShaderProgram(((gfx::CShaderManager *)getShaderManager())->getCurrentProgram());
                //pDrawCall->setModelMatrix(pObj->getRefModelMatrix());
                // getRefPriorityQueue().push(pDrawCall);
            }
        }
    }
}

/**
 * 
 */
void gfx::CScene3D::render(void) {

    CSceneManager::render();
    CShaderProgram *pProgram = static_cast<gfx::CShaderManager *>(m_pShaderMgr)->getCurrentProgram();
    pProgram->setUniform(FG_GFX_USE_TEXTURE, 0.0f);
    while(!m_octNodes.empty()) {
        SOctreeNode *treeNode = m_octNodes.top();
#if defined(FG_DEBUG)

        float d = ((float)treeNode->depth / (float)m_octree->getMaxDepth()) + 0.2f;
        if(d > 1) d = 1.0f;
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
            getMVP()->resetModelMatrix();
            pProgram->setUniform(getMVP());
            AABoundingBox3Df aabb;
            float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << treeNode->depth);
            Vec3f extent = Vec3f(halfSize, halfSize, halfSize);
            aabb.min = treeNode->center - extent;
            aabb.max = treeNode->center + extent;
            CPrimitives::drawAABBLines(aabb, fgColor4f(0.2f, d, 1.0f - d, 1.0f));
        }
#endif
        m_octNodes.pop();
    }
}

/**
 * 
 * @param pModelRes
 * @param nameTag
 * @return 
 */
gfx::CSceneNode *gfx::CScene3D::addFromModel(CModelResource* pModelRes,
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
    m_octree->insert(pNode);
    FG_LOG_DEBUG("GFX: Scene3D: Inserted object: '%s'", nameTag.c_str());
    return pNode;
}

/**
 * 
 * @param modelNameTag
 * @param nameTag
 * @return 
 */
gfx::CSceneNode *gfx::CScene3D::addFromModel(const std::string& modelNameTag,
                                             const std::string& nameTag) {
    if(modelNameTag.empty() || nameTag.empty()) {
        return NULL;
    }
    resource::CResourceManager *pResourceManager = static_cast<resource::CResourceManager *>(getResourceManager());
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
gfx::CSceneNode *gfx::CScene3D::addFromModel(const char *modelNameTag,
                                             const char *nameTag) {
    if(!modelNameTag || !nameTag) {
        return NULL;
    }
    resource::CResourceManager *pResourceManager = static_cast<resource::CResourceManager *>(getResourceManager());
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

void gfx::CScene3D::checkCollisions(const CSceneNode* sceneNode) {
    if(!sceneNode)
        return;
    
    m_octree->rewind();
    while(m_octree->next()) {
        SOctreeNode *treeNode = static_cast<SOctreeNode *>(m_octree->current());
        unsigned int objCount = treeNode->objects.size();
        float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << treeNode->depth);
        
        // First check to see if the object is completely outside the boundary
	// of this node.
        const Vector3f delta = treeNode->center - sceneNode->getRefBoundingVolume().center;
        const float radius = sceneNode->getRefBoundingVolume().radius;
        const Vector3f diff = delta - radius;
        if(diff.x > halfSize || diff.y > halfSize || diff.z > halfSize) {
            	// Object is completely outside the boundary of this
		// node; don't bother checking contents.
            m_octree->skip();
            continue;
        }
        
        for(unsigned int objIdx = 0; objIdx < objCount; objIdx++) {
            CSceneNode *childNode = treeNode->objects[objIdx];
            if(!childNode || childNode == sceneNode) {
                continue;
            }
            const fgBool isCollision = childNode->checkCollisionSphere(sceneNode);
            if(isCollision) {
                printf("*YES*  Collision occurred between: '%s'--'%s'\n", sceneNode->getNameStr(), childNode->getNameStr());
            } else {
                //printf("*NOPE* Collision occurred between: '%s'--'%s'\n", sceneNode->getNameStr(), childNode->getNameStr());
            }
        }                
    }        
}