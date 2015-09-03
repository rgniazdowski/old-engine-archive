/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfx3DScene.h"
#include "fgGfxSceneNode.h"
#include "fgGfxSceneEvent.h"
#include "fgGfxLooseOctree.h"
#include "fgGfxQuadtree.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/Textures/fgTextureResource.h"

#include "Util/fgMemory.h"
#include "Resource/fgResourceManager.h"
#include "Physics/fgWorld.h"

#include "fgDebugConfig.h"
#if defined(FG_DEBUG)
#include "Util/fgProfiling.h"
#endif

using namespace fg;

//------------------------------------------------------------------------------

gfx::CScene3D::CScene3D() :
CSceneManager(),
m_physicsWorld(NULL),
m_octree(NULL),
m_octNodes() {
    getMVP()->setPerspective(45.0f, 4.0f / 3.0f);
    m_octree = new CLooseOctree();
    m_basetree = (CBasetree *)m_octree;
    m_physicsWorld = new physics::CWorld(256);
    m_octNodes.reserve(64);
    setWorldSize(COctree::DEFAULT_WORLD_SIZE, COctree::DEFAULT_WORLD_SIZE, COctree::DEFAULT_WORLD_SIZE);
}
//------------------------------------------------------------------------------

gfx::CScene3D::~CScene3D() {
    if(m_octree) {
        delete m_octree;
    }
    m_octree = NULL;
    m_octNodes.clear();
    m_basetree = NULL;
    if(m_physicsWorld) {
        delete m_physicsWorld;
    }
    m_physicsWorld = NULL;
}
//------------------------------------------------------------------------------

void gfx::CScene3D::sortCalls(void) {
    if(!getShaderManager()) {
        return;
    }
    if(isLinearTraverse()) {
        CSceneManager::sortCalls();
        return;
    }
    if(m_physicsWorld) {
        m_physicsWorld->startFrame();
    }
    // Update the MVP based on the main camera properties
    getMVP()->setCamera((CCamera *)(getCamera()));
    CFrustum &frustum = getMVP()->getFrustum();
    // Remove from the queue any remaining nodes (CSceneNode)
    getNodeQueue().clear();
    //
    // Pick selection init
    //
    m_pickSelection.init(*getMVP(), *getCamera(), getStateFlags());
    if(m_pickSelection.shouldCheck) {
        fgBool groundStatus = getGroundGrid().rayIntersect(m_pickSelection.rayEye,
                                                            m_pickSelection.rayDir,
                                                            m_pickSelection.groundIntersectionPoint[1],
                                                            FG_TRUE);
        if(!groundStatus) {
            m_pickSelection.groundIntersectionPoint[1] = Vector3f();
        }
    }
    const fgBool checkPickSelectionAABB = isPickSelectionAABBTriangles();
    ////////////////////////////////////////////////////////////////////////////
    // PHASE I: Iterate through all objects, animate, update AABB, collisions...
    ////////////////////////////////////////////////////////////////////////////
    m_traverse.rewind();
    while(m_traverse.next(getActiveRootNode())) {
        CSceneNode *pSceneNode = m_traverse.current;
        if(!pSceneNode)
            continue;
        if(pSceneNode->getNodeType() == SCENE_NODE_ROOT) {
            continue; // skip root nodes
        }
        if(!pSceneNode->isActive()) {
            continue; // skip not active node
        }
        SOctreeNode *pTreeNode = static_cast<SOctreeNode *>(pSceneNode->getTreeNode());
        pSceneNode->setVisible(FG_FALSE);
        // There is a problem because the bounding box needs to be modified by
        // the model matrix; maybe some operator ?
        pSceneNode->update(timesys::elapsed());

        if(pTreeNode) {
            float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << pTreeNode->depth);
            // Check bounds of this scene node - if does not fit - reinsert to different tree node - slow...
            if(m_octree->fitsInBox(pSceneNode, pTreeNode->center, halfSize)) {
            } else if(pTreeNode->removeObject(pSceneNode)) {
                m_octree->insert(pSceneNode);
            }
        }
        // checkCollisions rewinds the octree/quadtree
        // should not be called within the tree traversal
        if(!isIgnoreCollisions()) {
            // broadphase - this uses loose octree - more fast would be dynamic AABBtree ?
            checkCollisions(pSceneNode);
        }
    }
    ////////////////////////////////////////////////////////////////////////////
    // PHASE II: Traverse the tree, check visibility, update nodes
    ////////////////////////////////////////////////////////////////////////////
    m_octree->rewind();
    m_octNodes.resize(0);
    while(m_octree->next()) {
        SOctreeNode *pTreeNode = static_cast<SOctreeNode *>(m_octree->current());
        unsigned int objCount = pTreeNode->objects.size();
        float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << pTreeNode->depth);
        if(frustum.testVolume(pTreeNode->center, halfSize) == CFrustum::OUTSIDE) {
            // Skip this tree node - it's completely outside of the frustum
            // Octree traverse functions needs to have special func for skipping
            m_octree->skip();
            continue;
        }
        m_octNodes.push_back(pTreeNode);
        for(unsigned int objIdx = 0; objIdx < objCount; objIdx++) {
            CSceneNode *pSceneNode = (CSceneNode *)pTreeNode->objects[objIdx];
            if(!pSceneNode) {
                continue;
            }
            if(pSceneNode->isVisible()) {
                continue;
            }

            CDrawCall *pDrawCall = pSceneNode->getDrawCall();
#if defined(FG_DEBUG)
            if(g_DebugConfig.isDebugProfiling) {
                profile::g_debugProfiling->begin("GFX::Scene::FrustumCheck");
            }
#endif
            int visibilityResult = 1;
            if(isFrustumCheck()) {
                visibilityResult = frustum.testVolume(pSceneNode->getBoundingVolume());
            } else if(isFrustumCheckSphere()) {
                visibilityResult = frustum.testSphere(pSceneNode->getBoundingVolume());
            }
            pSceneNode->setVisible(!!visibilityResult);

#if defined(FG_DEBUG)
            if(g_DebugConfig.isDebugProfiling) {
                profile::g_debugProfiling->end("GFX::Scene::FrustumCheck");
            }
#endif
            // #FIXME #TREE_TRAVERSE - tree needs also to contain child nodes
            // of scene nodes (like meshes of the object)
            // #OCTREE/#QUADTREE for now contains only main nodes (objects) not meshes
            if(pSceneNode->isVisible()) {
                // Checking for pick selection only when node is visible
                if(m_pickSelection.shouldCheck) {
                    if(!visibilityResult) {
                        m_pickSelection.pickedNodesInfo[pSceneNode->getHandle()].clear();
                    } else {
                        m_pickSelection.fullCheck(this, pSceneNode, checkPickSelectionAABB);
                    }
                }
                getNodeQueue().push(pSceneNode);
            }
            if(pDrawCall) {
                if(!pDrawCall->getShaderProgram())
                    pDrawCall->setShaderProgram(((gfx::CShaderManager *)getShaderManager())->getCurrentProgram());
                // getRefPriorityQueue().push(pDrawCall);
            }
        }
    }
    if(m_physicsWorld) {
        m_physicsWorld->finishFrame();
    }
    m_pickSelection.end(getStateFlags());
}
//------------------------------------------------------------------------------

void gfx::CScene3D::render(void) {
    // Calling underlying render function of the scene manager
    // This uses the special node queue, which contains only visible scene nodes
    // at the current render frame
    // This node queue was updated in CScene3D::sortCalls
    CSceneManager::render();
    CShaderProgram *pProgram = static_cast<gfx::CShaderManager *>(m_pShaderMgr)->getCurrentProgram();
    pProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, 0.0f);
    pProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR, 1.0f, 1.0f, 1.0f, 1.0f);
    const unsigned int n = m_octNodes.size();
    unsigned int i = 0;
    while(i < n) {
        SOctreeNode *pTreeNode = m_octNodes.at(i);
        i++;
        if(!pTreeNode)
            continue;
#if defined(FG_DEBUG)
        float d = ((float)pTreeNode->depth / (float)m_octree->getMaxDepth()) + 0.2f;
        if(d > 1.0f) d = 1.0f;
        if(FG_DEBUG_CFG_OPTION(gfxTreeBBoxShow)) {
            getMVP()->resetModelMatrix();
            pProgram->setUniform(getMVP());
            AABoundingBox3Df aabb;
            float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << pTreeNode->depth);
            Vec3f extent = Vec3f(halfSize, halfSize, halfSize);
            aabb.min = pTreeNode->center - extent;
            aabb.max = pTreeNode->center + extent;
            primitives::drawAABBLines(aabb, Color4f(0.2f, d, 1.0f - d, 1.0f));
        }
#endif        
    }
    pProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR, 1.0f, 1.0f, 1.0f, 1.0f);
}
//------------------------------------------------------------------------------

void gfx::CScene3D::checkCollisions(const CSceneNode* sceneNode) {
    if(!sceneNode)
        return;

    if(m_physicsWorld) {
        if(m_physicsWorld->hasMoreContacts() && m_physicsWorld->isGroundPlane()) {
            // Create the ground plane data
            const physics::CCollisionPlane& plane = m_physicsWorld->getGroundPlane();
            // check collision with ground plane ?
            physics::CCollisionBody *collisionBody = sceneNode->getCollisionBody();
            if(collisionBody) {
                collisionBody->checkCollision(plane, &m_physicsWorld->getCollisionData());
            }
        }
    }

    m_octree->rewind();
    while(m_octree->next()) {
        SOctreeNode *treeNode = static_cast<SOctreeNode *>(m_octree->current());
        unsigned int objCount = treeNode->objects.size();
        float halfSize = static_cast<CLooseOctree *>(m_octree)->getLooseK() * m_octree->getWorldSize().x / (2 << treeNode->depth);

        // First check to see if the object is completely outside the boundary
        // of this node.
        const Vector3f delta = treeNode->center - sceneNode->getBoundingVolume().center;
        const float radius = sceneNode->getBoundingVolume().radius;
        const Vector3f diff = delta - radius;
        if(diff.x > halfSize || diff.y > halfSize || diff.z > halfSize) {
            // Object is completely outside the boundary of this
            // node; don't bother checking contents.
            m_octree->skip();
            continue;
        }

        for(unsigned int objIdx = 0; objIdx < objCount; objIdx++) {
            const CSceneNode *childNode = (const CSceneNode *)treeNode->objects[objIdx];
            if(!childNode || childNode == sceneNode) {
                continue;
            }
            const SceneNodeType childType = childNode->getNodeType();
            const SceneNodeType nodeType = sceneNode->getNodeType();
            // Fast check for collision - checking nodes large sphere
            const fgBool isCollision = childNode->checkCollisionSphere(sceneNode);
            const fgBool isLastFrameCollision = m_collisionsInfo.check(childNode, sceneNode);
            // Update the internal collision info arrays
            if(isCollision) {
                if(!isLastFrameCollision) {

                    // Check for special trigger nodes - two trigger nodes cannot collide
                    // It should not be reported
                    if(childType == gfx::SCENE_NODE_TRIGGER &&
                       nodeType != gfx::SCENE_NODE_TRIGGER) {
                        STriggerInfo info(NULL, NULL, FG_TRUE);
                        info.pTrigger = static_cast<CSceneNodeTrigger*>(const_cast<CSceneNode*>(childNode));
                        info.pNodeB = const_cast<CSceneNode*>(sceneNode);
                        m_triggers.push_back(info);
                    } else if(childType != gfx::SCENE_NODE_TRIGGER &&
                              nodeType == gfx::SCENE_NODE_TRIGGER) {
                        STriggerInfo info(NULL, NULL, FG_TRUE);
                        info.pTrigger = static_cast<CSceneNodeTrigger*>(const_cast<CSceneNode*>(sceneNode));
                        info.pNodeB = const_cast<CSceneNode*>(childNode);
                        m_triggers.push_back(info);
                    }
                    m_collisionsInfo.insert(childNode, sceneNode);
                    if(nodeType != gfx::SCENE_NODE_TRIGGER && childType != gfx::SCENE_NODE_TRIGGER) {
                        FG_LOG_DEBUG("*INSERTING*  Collision BEGUN between: '%s'--'%s'", sceneNode->getNameStr(), childNode->getNameStr());
                        event::SSceneNodeCollision* collisionEvent = (event::SSceneNodeCollision*) getInternalEventManager()->requestEventStruct();
                        collisionEvent->eventType = event::SCENE_NODE_COLLISION;
                        collisionEvent->setFirstNode(const_cast<CSceneNode*>(sceneNode));
                        collisionEvent->setSecondNode(const_cast<CSceneNode*>(childNode));

                        event::CArgumentList *argList = getInternalEventManager()->requestArgumentList();
                        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)collisionEvent);
                        argList->push(event::SArgument::Type::ARG_POINTER, (void *)this); // pointer to the manager
                        getInternalEventManager()->throwEvent(event::SCENE_NODE_COLLISION, argList);
                    }
                } else {
                    // this collision is already occurring - based on last frame info
                }
            } else if(isLastFrameCollision) {
                // Check for special trigger nodes - two trigger nodes cannot collide                
                if(childType == gfx::SCENE_NODE_TRIGGER &&
                   nodeType != gfx::SCENE_NODE_TRIGGER) {
                    STriggerInfo info(NULL, NULL, FG_FALSE);
                    info.pTrigger = static_cast<CSceneNodeTrigger*>(const_cast<CSceneNode*>(childNode));
                    info.pNodeB = const_cast<CSceneNode*>(sceneNode);
                    m_triggers.push_back(info);
                } else if(childType != gfx::SCENE_NODE_TRIGGER &&
                          nodeType == gfx::SCENE_NODE_TRIGGER) {
                    STriggerInfo info(NULL, NULL, FG_FALSE);
                    info.pTrigger = static_cast<CSceneNodeTrigger*>(const_cast<CSceneNode*>(sceneNode));
                    info.pNodeB = const_cast<CSceneNode*>(childNode);
                    m_triggers.push_back(info);
                }
                // the collision is not occurring in this frame
                m_collisionsInfo.remove(childNode, sceneNode);
                FG_LOG_DEBUG("*REMOVING*  Collision ENDED between: '%s'--'%s'", sceneNode->getNameStr(), childNode->getNameStr());
            }

            if(isCollision && m_physicsWorld->hasMoreContacts()) {
                //FG_LOG_DEBUG("*YES*  Collision occurred between: '%s'--'%s'", sceneNode->getNameStr(), childNode->getNameStr());
                {
                    // #FIXME - physics fine collision detect / update
                    physics::CCollisionBody *b1 = sceneNode->getCollisionBody();
                    physics::CCollisionBody *b2 = childNode->getCollisionBody();
                    if(b1 && b2) {
                        // now can check fine collisions
                        const fgBool isFineCollision = b1->checkCollision(b2, &m_physicsWorld->getCollisionData());
                        // ? Now hwat? Another event? For fine collision detection?
                    }
                }
            }
        }
    }
} // gfx::CScene3D::checkCollisions()
//------------------------------------------------------------------------------
