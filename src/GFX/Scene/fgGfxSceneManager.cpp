/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxSceneManager.h"
#include "fgGfxSceneEvent.h"

#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/Textures/fgTextureResource.h"
#include "GFX/fgGfxFrustum.h"
#include "GFX/fgGfxPrimitives.h"

#include "Resource/fgResourceManager.h"
#include "Util/fgStrings.h"

#include "fgDebugConfig.h"
#if defined(FG_DEBUG)
#include "Util/fgProfiling.h"
#endif

using namespace fg;

/**
 * 
 */
gfx::CSceneManager::CSceneManager() :
CDrawingBatch(),
m_collisionsInfo(),
m_triggers(),
m_stateFlags(NONE | FRUSTUM_CHECK),
m_MVP(),
m_camera(CCameraAnimation::FREE),
m_skybox(),
m_nodeQueue(),
m_pResourceMgr(NULL),
m_eventMgr(NULL),
m_basetree(NULL) {
    m_managerType = FG_MANAGER_SCENE;
    m_skybox.setScale(FG_GFX_PERSPECTIVE_ZFAR_DEFAULT * 1.1f); // #FIXME #SKYBOX scale
    m_skybox.setMVP(&m_MVP);
    m_eventMgr = new event::CEventManager(sizeof (event::SSceneEvent));
    m_triggers.reserve(4);
}

/**
 * 
 */
gfx::CSceneManager::~CSceneManager() {
    CSceneManager::destroy();
    if(m_eventMgr) {
        delete m_eventMgr;
        m_eventMgr = NULL;
    }
}

/**
 *
 */
void gfx::CSceneManager::clear(void) {
    releaseAllHandles();
    m_managerType = FG_MANAGER_SCENE;
    m_pResourceMgr = NULL;
    m_basetree = NULL;
}

/**
 * 
 * @return 
 */
fgBool gfx::CSceneManager::destroy(void) {
    CDrawingBatch::flush();
    if(m_basetree) {
        m_basetree->deleteRoot();
    }
    m_collisionsInfo.clear();
    // The piece of code seems to repeat itself #FIXME #CODEREPEAT
    // Maybe even the handle manager can have this piece of code?
    // Delete all gfx objects in the scene
    DataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        CSceneNode* pObj = (*itor).data;
        if(pObj == NULL)
            continue;
        if(m_basetree) {
            // need to have functions for scene node removal
        }
        if(pObj->isManaged())
            delete pObj;
        (*itor).clear();
    }
    m_triggers.clear_optimised();
    CSceneManager::clear();
    return FG_TRUE;
}

/**
 * #FIXME
 */
void gfx::CSceneManager::clearScene(void) {
    CDrawingBatch::flush();
    if(m_basetree) {
        m_basetree->deleteRoot();
    }
    m_collisionsInfo.clear();
    // Delete all gfx objects in the scene
    DataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        CSceneNode* pObj = (*itor).data;
        if(pObj == NULL)
            continue;
        if(m_basetree) {
            // need to have functions for scene node removal
        }
        if(pObj->isManaged())
            delete pObj;
        (*itor).clear();
    }
    m_triggers.clear_optimised();
    releaseAllHandles();
    if(m_eventMgr) {
        event::SSceneEvent* clearEvent = (event::SSceneEvent*) m_eventMgr->requestEventStruct();
        clearEvent->code = event::SCENE_CLEARED;

        event::CArgumentList *argList = m_eventMgr->requestArgumentList();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)clearEvent);
        m_eventMgr->throwEvent(event::SCENE_CLEARED, argList);
    }
}

/**
 * 
 * @return 
 */
fgBool gfx::CSceneManager::initialize(void) {
    m_eventMgr->initialize();
    return FG_TRUE;
}

////////////////////////////////////////////////////////////////////////////////

/**
 * 
 */
gfx::CSceneManager::SCollisionsInfo::SCollisionsInfo() : contacts() { }

/**
 * 
 */
gfx::CSceneManager::SCollisionsInfo::~SCollisionsInfo() {
    clear();
}

/**
 * 
 * @param maxObjects
 */
void gfx::CSceneManager::SCollisionsInfo::reserve(const unsigned int maxObjects) {
    contacts.reserve(maxObjects);
    contacts.resize(maxObjects);
}

/**
 * 
 * @param numObjects
 */
void gfx::CSceneManager::SCollisionsInfo::resize(const unsigned int numObjects) {
    contacts.resize(numObjects);
    contacts.reserve(numObjects);
}

/**
 * 
 * @param nodeA
 * @param nodeB
 */
void gfx::CSceneManager::SCollisionsInfo::insert(const CSceneNode* nodeA, const CSceneNode* nodeB) {
    if(!nodeA || !nodeB) {
        return;
    }

    if(nodeA->getRefHandle().getIndex() > contacts.capacity() ||
       nodeB->getRefHandle().getIndex() > contacts.capacity()) {
        return;
    }
    // A -> B
    {
        const unsigned int index = nodeA->getRefHandle().getIndex();
        const int findIndex = contacts[index].find(const_cast<CSceneNode*>(nodeB));
        if(findIndex == -1) {
            contacts[index].push_back(const_cast<CSceneNode*>(nodeB));
        }
    }
    // B -> A
    {
        const unsigned int index = nodeB->getRefHandle().getIndex();
        const int findIndex = contacts[index].find(const_cast<CSceneNode*>(nodeA));
        if(findIndex == -1) {
            contacts[index].push_back(const_cast<CSceneNode*>(nodeA));
        }
    }
}

/**
 * 
 * @param pNode
 */
void gfx::CSceneManager::SCollisionsInfo::removeAll(const CSceneNode* pNode) {
    if(!pNode) {
        clear();
    }
    const unsigned int index = pNode->getRefHandle().getIndex();
    if(index > contacts.capacity()) {
        return;
    }
    contacts[index].clear_optimised();
    //contacts[index].clear();
    // #FIXME
}

/**
 * 
 * @param nodeA
 * @param nodeB
 */
void gfx::CSceneManager::SCollisionsInfo::remove(const CSceneNode* nodeA, const CSceneNode* nodeB) {
    if(!nodeA || !nodeB) {
        return;
    }
    if(nodeA->getRefHandle().getIndex() > contacts.capacity() ||
       nodeB->getRefHandle().getIndex() > contacts.capacity()) {
        return;
    }
    // A -> B
    {
        const unsigned int index = nodeA->getRefHandle().getIndex();
        const int findIndex = contacts[index].find(const_cast<CSceneNode*>(nodeB));
        const unsigned int n = contacts[index].size();
        if(findIndex != -1) {
            contacts[index][findIndex] = contacts[index][n - 1];
            contacts[index][n - 1] = NULL;
            contacts[index].resize(n - 1);
        }
    }
    // B -> A
    {
        const unsigned int index = nodeB->getRefHandle().getIndex();
        const int findIndex = contacts[index].find(const_cast<CSceneNode*>(nodeA));
        const unsigned int n = contacts[index].size();
        if(findIndex != -1) {
            contacts[index][findIndex] = contacts[index][n - 1];
            contacts[index][n - 1] = NULL;
            contacts[index].resize(n - 1);
        }
    }
}

/**
 * 
 */
void gfx::CSceneManager::SCollisionsInfo::clear(void) {
    const unsigned int n = contacts.capacity();
    for(unsigned int i = 0; i < n; i++) {
        contacts[i].clear();
    }
    contacts.clear();
}

/**
 * 
 * @param nodeA
 * @param nodeB
 * @return 
 */
fgBool gfx::CSceneManager::SCollisionsInfo::check(const CSceneNode *nodeA, const CSceneNode *nodeB) const {
    if(!nodeA || !nodeB)
        return FG_FALSE;
    if(nodeA->getRefHandle().getIndex() > contacts.capacity() ||
       nodeB->getRefHandle().getIndex() > contacts.capacity()) {
        return FG_FALSE;
    }
    // A -> B
    {
        const unsigned int index = nodeA->getRefHandle().getIndex();
        const int findIndex = contacts[index].find(const_cast<CSceneNode*>(nodeB));

        if(findIndex != -1) {
            return FG_TRUE;
        }
    }
    // B -> A
    {
        const unsigned int index = nodeB->getRefHandle().getIndex();
        const int findIndex = contacts[index].find(const_cast<CSceneNode*>(nodeA));
        if(findIndex != -1) {
            return FG_TRUE;
        }
    }
    return FG_FALSE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CSceneManager::SCollisionsInfo::empty(void) const {
    return contacts.empty();
}

/**
 * 
 * @param pNode
 * @return 
 */
fgBool gfx::CSceneManager::SCollisionsInfo::empty(CSceneNode *pNode) const {
    if(!pNode) {
        return FG_FALSE;
    }

    const unsigned int index = pNode->getRefHandle().getIndex();
    if(index > contacts.capacity()) {
        return FG_FALSE;
    }
    return (fgBool)contacts[index].empty();
    //m_MVP.getPtrCenter();
}

/**
 * 
 * @param pNode
 * @return 
 */
unsigned int gfx::CSceneManager::SCollisionsInfo::count(CSceneNode *pNode) const {
    if(!pNode) {
        return FG_FALSE;
    }

    const unsigned int index = pNode->getRefHandle().getIndex();
    if(index > contacts.capacity()) {
        return FG_FALSE;
    }
    return (fgBool)contacts[index].size();
}

/**
 * 
 * @return 
 */
unsigned int gfx::CSceneManager::SCollisionsInfo::count(void) const {
    return contacts.size();
}

/**
 * 
 * @return 
 */
unsigned int gfx::CSceneManager::SCollisionsInfo::size(void) const {
    return contacts.size();
}

/**
 * 
 * @return 
 */
unsigned int gfx::CSceneManager::SCollisionsInfo::capacity(void) const {
    return contacts.capacity();
}

////////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @param shaderMgr
 */
void gfx::CSceneManager::setShaderManager(fg::base::CManager* pShaderMgr) {
    CDrawingBatch::setShaderManager(pShaderMgr);
}

/**
 * 
 * @param pResourceMgr
 */
void gfx::CSceneManager::setResourceManager(fg::base::CManager* pResourceMgr) {
    if(!pResourceMgr)
        return;
    if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
        m_pResourceMgr = pResourceMgr;
}

/**
 * 
 * @param shaderName
 */
void gfx::CSceneManager::setSkyBoxShader(const char* shaderName) {
    if(shaderName && m_pShaderMgr) {
        m_skybox.setShaderProgram(static_cast<gfx::CShaderManager*>(m_pShaderMgr)->get(shaderName));
    }
}

/**
 * 
 * @param shaderName
 */
void gfx::CSceneManager::setSkyBoxShader(const std::string& shaderName) {
    if(shaderName.size() && m_pShaderMgr) {
        m_skybox.setShaderProgram(static_cast<gfx::CShaderManager*>(m_pShaderMgr)->get(shaderName));
    }
}

/**
 * 
 */
void gfx::CSceneManager::flush(void) {
    CDrawingBatch::flush();
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();
}

/**
 * 
 */
void gfx::CSceneManager::update(void) {
    while(m_triggers.size()) {
        TriggerInfo &info = m_triggers.back();
        CSceneNodeTrigger::TriggerActivation activation;
        if(info.isBegin)
            activation = CSceneNodeTrigger::ON_COLLISION_BEGIN;
        else
            activation = CSceneNodeTrigger::ON_COLLISION_END;
        if(info.pTrigger) {
            info.pTrigger->trigger(activation, info.pNodeB);
        }

        if(info.isBegin && m_eventMgr) {
            event::SSceneNodeTrigger* triggerEvent = (event::SSceneNodeTrigger*) m_eventMgr->requestEventStruct();
            triggerEvent->eventType = event::SCENE_NODE_TRIGGER_FIRED;
            triggerEvent->pNodeTrigger = info.pTrigger;
            triggerEvent->pNodeB = info.pNodeB;

            event::CArgumentList *argList = m_eventMgr->requestArgumentList();
            argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)triggerEvent);
            m_eventMgr->throwEvent(event::SCENE_NODE_TRIGGER_FIRED, argList);
        }
        m_triggers.pop_back();
    }
    if(m_eventMgr) {
        m_eventMgr->executeEvents();
    }
}

/**
 * 
 */
void gfx::CSceneManager::sortCalls(void) {
    if(!getShaderManager())
        return;
    m_MVP.setCamera((CCamera*)(&m_camera));
    if(getRefPriorityQueue().empty())
        CDrawingBatch::sortCalls(); // NOPE
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();
    DataVecItor itor = getRefDataVector().begin(), end = getRefDataVector().end();
#if 1
    for(; itor != end; itor++) {
        if(!(*itor).data)
            continue;
        CSceneNode* pNode = (*itor).data;
        CDrawCall* pDrawCall = pNode->getDrawCall();
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::Scene::FrustumCheck");
        }
#endif
        // There is a problem because the bounding box needs to be modified by
        // the model matrix; maybe some operator ?
        pNode->update(timesys::elapsed()); // updateAABB

        int visibilityResult = 1;
        if(isFrustumCheck()) {
            visibilityResult = m_MVP.getFrustum().testVolume(pNode->getBoundingVolume());
        } else if(isFrustumCheckSphere()) {
            visibilityResult = m_MVP.getFrustum().testSphere(pNode->getBoundingVolume());
        }
        if(!visibilityResult) {
            pNode->setVisible(FG_FALSE);
        } else {
            pNode->setVisible(FG_TRUE);
        }
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
        if(pNode->isVisible()) {
            m_nodeQueue.push(pNode);
        }
        // #FIXME - srsly?
        if(pDrawCall) {
            if(!pDrawCall->getShaderProgram())
                pDrawCall->setShaderProgram(((gfx::CShaderManager*)getShaderManager())->getCurrentProgram());
            // getRefPriorityQueue().push(pDrawCall);
        }
    }
#endif
}

/**
 * 
 */
void gfx::CSceneManager::render(void) {
    if(isHideAll()) {
        return;
    }
    CShaderManager* pShaderMgr = static_cast<gfx::CShaderManager*>(m_pShaderMgr);
    CShaderProgram* pProgram = pShaderMgr->getCurrentProgram();
    //pProgram->setUniform(FG_GFX_USE_TEXTURE, 1.0f);
    //printf("fgGfxSceneManager::render(void)\n");
    // Will now render main skybox
    if(!isHideSkyBox()) {
        CShaderProgram* pSkyboxProgram = m_skybox.getShaderProgram();
        if(pSkyboxProgram) {
            pShaderMgr->useProgram(pSkyboxProgram);
            m_skybox.setPosition(m_camera.getEye());
            m_skybox.draw();
            pShaderMgr->useProgram(pProgram);
        }
    }
    // Calling underlying DrawingBatch render procedure
    // This will contain drawcalls not associated with scene/octree/quadtree structure
    CDrawingBatch::render();
    while(!m_nodeQueue.empty()) {
        if(isHideNodes()) {
            m_nodeQueue.pop();
            continue;
        }
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::Scene::DrawNode");
        }
#endif
        CSceneNode *pSceneNode = m_nodeQueue.top();
        //printf("SCENENODE: %s\n", pSceneNode->getNameStr());        
        pSceneNode->draw();
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->end("GFX::Scene::DrawNode");
        }
#endif

#if defined(FG_DEBUG)
        CModel* sphereModel = (CModel*)static_cast<resource::CResourceManager*>(m_pResourceMgr)->get("builtinSphere");
        SMeshBase* sphereMesh = sphereModel->getRefShapes()[0]->mesh;
        pProgram->setUniform(FG_GFX_USE_TEXTURE, 0.0f);
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow) && pSceneNode->getNodeType() == SCENE_NODE_OBJECT) {
            CSceneNodeObject* pSceneObj = static_cast<CSceneNodeObject*>(pSceneNode);
            if(pSceneObj->getModel()) {
                // Current aabb - it's in model space (local)
                AABB3Df& modelBox = pSceneObj->getModel()->getRefAABB();
                // Initial Bounding box
                CPrimitives::drawAABBLines(modelBox, fgColor4f(1.0f, 0.0f, 0.0f, 1.0f));
                // Draw transformed bounding box #FIXME - colors FUBAR
            }
        }
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
            m_MVP.resetModelMatrix();
            pProgram->setUniform(&m_MVP);
            CPrimitives::drawAABBLines(pSceneNode->getBoundingVolume(), fgColor4f(0.5f, 0.5f, 1.0f, 1.0f));
        }

        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
            Matrix4f mat = math::translate(Matrix4f(), pSceneNode->getBoundingVolume().center);
            const float radius = pSceneNode->getBoundingVolume().radius;
            mat = math::scale(mat, Vec3f(radius, radius, radius));
            m_MVP.calculate(mat);
            pProgram->setUniform(&m_MVP);
            CPrimitives::drawVertexData(sphereMesh, FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT, PrimitiveMode::LINES);
        }
#endif
        //g_fgDebugConfig.physicsBBoxShow = true; // #FIXME
        if(FG_DEBUG_CFG_OPTION(physicsBBoxShow)) {
            physics::CCollisionBody* body = pSceneNode->getCollisionBody();
            if(body) {
                if(body->getBodyType() == physics::CCollisionBody::BOX) {
                } else if(body->getBodyType() == physics::CCollisionBody::SPHERE) {
                }
            }
        }
        //#endif // defined(FG_DEBUG)
        m_nodeQueue.pop();
    }
}

#if 0

/**
 * 
 * @param pObj
 * @param manage
 * @return 
 */
int gfx::CSceneManager::appendObject(CSceneNode *pObj, fgBool manage) {
    if(!pObj)
        return -1;
    if(m_objects.find(pObj) != -1)
        return -1;
    if(!pObj->getModel())
        return -1;

    CDrawCall *call = new CDrawCall(FG_GFX_DRAW_CALL_MODEL);
    call->setupFromModel(pObj->getModel());
    if(getShaderManager())
        call->setShaderProgram(((CShaderManager *)getShaderManager())->getCurrentProgram());
    if(m_resourceMgr) {
        SMaterial *pMainMaterial = pObj->getModel()->getMainMaterial();
        if(pMainMaterial) {
            CTextureResource *pTexRes = (CTextureResource *)((CResourceManager *)m_resourceMgr)->get(pMainMaterial->ambientTexHandle);
            if(pTexRes)
                call->setTexture(pTexRes->getRefGfxID());
        }
    }
    call->setMVP(&m_MVP);
    call->setModelMatrix(pObj->getRefModelMatrix());
    pObj->setManaged(manage);
    m_objects.push_back(pObj);
    m_objDrawCalls.push_back(call);
    // 2nd argument tells that this draw call should not be managed
    // meaning: destructor wont be called on flush()
    CDrawingBatch::appendDrawCall(call, FG_FALSE);

    return ((int)m_objects.size() - 1);
}

/**
 * 
 * @param index
 * @param pModelRes
 * @param manage
 * @return 
 */
CSceneNode *gfx::CSceneManager::appendModel(int& index,
                                            CModelResource* pModelRes,
                                            fgBool manage) {
    if(!pModelRes) {
        index = -1;
        return NULL;
    }
    CSceneNode *pObj = new CSceneNode();
    //pObj->setName();
    pObj->setModel(pModelRes);
    index = appendObject(pObj, manage);
    return pObj;
}
#endif

/**
 * 
 * @param eventCode
 * @param pCallback
 * @return 
 */
gfx::CSceneCallback* gfx::CSceneManager::addCallback(event::EventType eventCode,
                                                     CSceneCallback *pCallback) {
    if(!pCallback || !m_eventMgr)
        return NULL;
    if(m_eventMgr->addCallback(eventCode, pCallback)) {
        return pCallback;
    } else {
        return NULL;
    }
}

/**
 * 
 * @param pTrigger
 * @param pCallback
 * @return 
 */
fgBool gfx::CSceneManager::addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                              CSceneNodeTrigger* pTrigger,
                                              CSceneCallback* pCallback) {
    fgBool status = FG_TRUE;
    if(!pTrigger || !pCallback) {
        status = FG_FALSE;
    }
    if(status) {
        status = isManaged(pTrigger);
    }
    if(status) {
        pTrigger->addCallback(pCallback, activation);
    }
    return status;
}

/**
 * 
 * @param nodeUniqueID
 * @param pCallback
 * @return 
 */
fgBool gfx::CSceneManager::addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                              const SceneNodeHandle& nodeUniqueID,
                                              CSceneCallback* pCallback) {
    fgBool status = FG_TRUE;
    CSceneNode* pNode = NULL;
    if(!pCallback) {
        status = FG_FALSE;
    }
    if(status) {
        pNode = get(nodeUniqueID);
        if(!pNode)
            status = FG_FALSE;
    }
    if(status) {
        status = (pNode->getNodeType() == gfx::SCENE_NODE_TRIGGER);
    }
    if(status) {
        CSceneNodeTrigger *pNodeTrigger = static_cast<CSceneNodeTrigger*>(pNode);
        pNodeTrigger->addCallback(pCallback, activation);
    }
    return status;
}

/**
 * 
 * @param nameTag
 * @param pCallback
 * @return 
 */
fgBool gfx::CSceneManager::addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                              const std::string& nameTag,
                                              CSceneCallback* pCallback) {
    fgBool status = FG_TRUE;
    CSceneNode* pNode = NULL;
    if(!pCallback) {
        status = FG_FALSE;
    }
    if(status) {
        pNode = get(nameTag);
        if(!pNode)
            status = FG_FALSE;
    }
    if(status) {
        status = (pNode->getNodeType() == gfx::SCENE_NODE_TRIGGER);
    }
    if(status) {
        CSceneNodeTrigger *pNodeTrigger = static_cast<CSceneNodeTrigger*>(pNode);
        pNodeTrigger->addCallback(pCallback, activation);
    }
    return status;
}

/**
 * 
 * @param nameTag
 * @param pCallback
 * @return 
 */
fgBool gfx::CSceneManager::addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                              const char* nameTag,
                                              CSceneCallback* pCallback) {
    fgBool status = FG_TRUE;
    CSceneNode* pNode = NULL;
    if(!pCallback || !nameTag) {
        status = FG_FALSE;
    }
    if(status) {
        pNode = get(nameTag);
        if(!pNode)
            status = FG_FALSE;
    }
    if(status) {
        status = (pNode->getNodeType() == gfx::SCENE_NODE_TRIGGER);
    }
    if(status) {
        CSceneNodeTrigger *pNodeTrigger = static_cast<CSceneNodeTrigger*>(pNode);
        pNodeTrigger->addCallback(pCallback, activation);
    }
    return status;
}

/*
 * @param name
 * @param position
 * @return
 */
gfx::CSceneNode* gfx::CSceneManager::addTrigger(const std::string& name,
                                                const Vector3f& position) {
    if(name.empty()) {
        return NULL;
    }
    CSceneNodeTrigger *pNodeTrigger = new CSceneNodeTrigger();
    pNodeTrigger->setName(name);
    pNodeTrigger->setPosition(position);
    if(!addNode(pNodeTrigger->getRefHandle(), pNodeTrigger)) {
        remove(pNodeTrigger);
        delete pNodeTrigger;
        pNodeTrigger = NULL;
    }
    return pNodeTrigger;
}

/**
 * 
 * @param name
 * @param position
 * @param halfExtent
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addTrigger(const std::string& name,
                                                const Vector3f& position,
                                                const Vector3f& halfExtent) {
    CSceneNode *pNode = addTrigger(name, position);
    if(pNode) {
        pNode->setHalfSize(halfExtent);
    }
    return pNode;
}

/**
 * 
 * @param name
 * @param position
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addTrigger(const char* name,
                                                const Vector3f& position) {
    if(!name) {
        return NULL;
    }
    if(!name[0]) {
        return NULL;
    }
    return addTrigger(std::string(name), position);
}

/**
 * 
 * @param name
 * @param position
 * @param halfExtent
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addTrigger(const char* name,
                                                const Vector3f& position,
                                                const Vector3f& halfExtent) {
    if(!name) {
        return NULL;
    }
    if(!name[0]) {
        return NULL;
    }
    return addTrigger(std::string(name), position, halfExtent);
}

/**
 * 
 * @param name
 * @param x
 * @param y
 * @param z
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addTrigger(const char* name,
                                                float x, float y, float z) {
    if(!name)
        return NULL;
    return addTrigger(std::string(name), Vector3f(x, y, z));
}

/**
 * 
 * @param name
 * @param x
 * @param y
 * @param z
 * @param extX
 * @param extY
 * @param extZ
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addTrigger(const char* name,
                                                float x, float y, float z,
                                                float extX, float extY, float extZ) {
    if(!name)
        return NULL;
    return addTrigger(std::string(name), Vector3f(x, y, z), Vector3f(extX, extY, extZ));
}

/**
 * 
 * @param pNode
 */
void gfx::CSceneManager::initializeNode(CSceneNode *pNode) {
    if(!pNode) {
        return;
    }

    CShaderManager* pShaderMgr = static_cast<gfx::CShaderManager *>(getShaderManager());

    if(pNode->getNodeType() == SCENE_NODE_OBJECT) {
        CSceneNodeObject* pNodeObject = static_cast<CSceneNodeObject*>(pNode);
        /// This should be somewhere else - initialize shader program pointer from name
        /// for material structure
        CModel* pModel = pNodeObject->getModel();
        if(pModel) {
            if(!pModel->getMainMaterial()->shaderProgram) {
                pModel->getMainMaterial()->shaderProgram =
                        pShaderMgr->get(pModel->getMainMaterial()->shaderName);
            }
        }
    }

    {
        CDrawCall* pDrawCall = pNode->getDrawCall();
        if(pDrawCall) {
            pDrawCall->setMVP(&m_MVP);
            if(getShaderManager() && !pDrawCall->getShaderProgram()) {
                pDrawCall->setShaderProgram(pShaderMgr->getCurrentProgram());
            }
        }
        pNode->refreshGfxInternals();
    }

    CSceneNode::ChildrenVecItor it = pNode->getChildren().begin(),
            end = pNode->getChildren().end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        CSceneNode* pChildNode = (*it);

        CDrawCall* pDrawCall = pChildNode->getDrawCall();
        if(pDrawCall) {
            pDrawCall->setMVP(&m_MVP);
            if(getShaderManager() && !pDrawCall->getShaderProgram()) {
                pDrawCall->setShaderProgram(pShaderMgr->getCurrentProgram());
            }
        }
    }

    pNode->update();
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherObj
 * @return 
 */
fgBool gfx::CSceneManager::addNode(SceneNodeHandle& nodeUniqueID,
                                   CSceneNode* pNode,
                                   CSceneNode* pFatherNode) {
    if(!pNode) {
        // Empty pointer - return
        FG_LOG_ERROR("GFX.SceneManager: Empty pointer - exit... no addition made");
        return FG_FALSE;
    }

    if(handle_mgr_type::isDataManaged(pNode)) {
        // Widget is already managed in the handle manager
        FG_LOG_ERROR("GFX.SceneManager: Object is already managed in the handle manager: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }

    if(!pNode->getHandle().isNull()) {
        // Widget has already initialized handle
        FG_LOG_ERROR("GFX.SceneManager: Object has already initialized handle: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }

    if(!handle_mgr_type::acquireHandle(nodeUniqueID, pNode)) {
        // Could not aquire handle for the widget
        FG_LOG_ERROR("GFX.SceneManager: Could not aquire handle for the object: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }
    pNode->setHandle(nodeUniqueID);
    // By default object is set to be managed
    // However in some cases the 'managed' flag will
    // be set to FG_FALSE after addition
    pNode->setManaged(FG_TRUE);
    pNode->setManager(this); // Setup internal pointer to the manager
    pNode->setParent(pFatherNode); // Pointer to the parent (if any)

    if(!handle_mgr_type::setupName(pNode->getName().c_str(), nodeUniqueID)) {
        // Could not setup handle string tag/name for the scene node
        // The handle name tag can be empty - sometimes it is not needed
        FG_LOG_ERROR("GFX.SceneManager: Could not setup handle string tag/name for the object: '%s'", pNode->getNameStr());
    }
    //unsigned int index = pObj->getHandle().getIndex();

    initializeNode(pNode);

    if(m_basetree) {
        // add to the spatial tree structure
        // it can be octree/quadtree or any other (bounding volume hierarchy)
        m_basetree->insert(pNode); // #FIXME -- need some kind of removal functionality        
    }
    // 2nd argument tells that this draw call should not be managed
    // meaning: destructor wont be called on flush()
    //fgGfxDrawingBatch::appendDrawCall(drawCall, FG_FALSE); // Don't know if needed...

    if(handle_mgr_type::getRefDataVector().size() > m_collisionsInfo.capacity()) {
        m_collisionsInfo.reserve((unsigned int)((float)handle_mgr_type::getRefDataVector().size()*1.5f) + 32);
    }

    if(m_eventMgr) {
        event::SSceneNode* nodeEvent = (event::SSceneNode*) m_eventMgr->requestEventStruct();
        nodeEvent->eventType = event::SCENE_NODE_INSERTED;
        nodeEvent->pNodeA = pNode;
        nodeEvent->pNodeB = NULL;

        event::CArgumentList *argList = m_eventMgr->requestArgumentList();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)nodeEvent);
        m_eventMgr->throwEvent(event::SCENE_NODE_INSERTED, argList);
    }
    return FG_TRUE;
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::addNode(SceneNodeHandle& oUniqueID,
                                   CSceneNode* pObj,
                                   const SceneNodeHandle& oFatherUniqueID) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherUniqueID));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool gfx::CSceneManager::addNode(SceneNodeHandle& oUniqueID,
                                   CSceneNode* pObj,
                                   const std::string& oFatherNameTag) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherNameTag));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool gfx::CSceneManager::addNode(SceneNodeHandle& oUniqueID,
                                   CSceneNode* pObj,
                                   const char* oFatherNameTag) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherNameTag));
}

/**
 * 
 * @param pSourceNode
 * @param newNodeNameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addDuplicate(CSceneNode* pSourceNode,
                                                  const std::string& newNodeNameTag) {
    if(!pSourceNode || newNodeNameTag.empty())
        return NULL;
    if(pSourceNode->getManager() != this || !pSourceNode->isManaged())
        return NULL;
    CSceneNode *pNewNode = get(newNodeNameTag);
    if(pNewNode) {
        // The node with this name already exists - should not add it, just return pointer to it
        // This is better than returning NULL
        // However with this approach there is no guarantee that this node has
        // the same type as the source node...
        return pNewNode;
    }
    SceneNodeType nodeType = pSourceNode->getNodeType();
    switch(nodeType) {
        case SCENE_NODE_CUSTOM:
            pNewNode = new CSceneNode(*pSourceNode);
            break;
        case SCENE_NODE_MESH:
            pNewNode = new CSceneNodeMesh(*(static_cast<CSceneNodeMesh*>(pSourceNode)));
            break;
        case SCENE_NODE_OBJECT:
            pNewNode = new CSceneNodeObject(*(static_cast<CSceneNodeObject*>(pSourceNode)));
            break;
        case SCENE_NODE_TRIGGER:
            pNewNode = new CSceneNodeTrigger(*(static_cast<CSceneNodeTrigger*>(pSourceNode)));
            break;
        default:
            break;
    }
    if(pNewNode) {
        pNewNode->setName(newNodeNameTag);
        fgBool status = addNode(pNewNode->getRefHandle(), pNewNode, pSourceNode->getParent());
        if(!status) {
            delete pNewNode;
            pNewNode = NULL;
        }
    }
    return pNewNode;
}

/**
 * 
 * @param pSourceNode
 * @param newNodeNameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addDuplicate(CSceneNode* pSourceNode,
                                                  const char* newNodeNameTag) {
    if(!pSourceNode || !newNodeNameTag)
        return NULL;
    return addDuplicate(pSourceNode, std::string(newNodeNameTag));
}

/**
 * 
 * @param nodeUniqueID
 * @param newNodeNameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addDuplicate(const SceneNodeHandle& nodeUniqueID,
                                                  const std::string& newNodeNameTag) {
    CSceneNode* pSourceNode = get(nodeUniqueID);
    if(!pSourceNode)
        return NULL;
    return addDuplicate(pSourceNode, newNodeNameTag);
}

/**
 * 
 * @param nodeUniqueID
 * @param newNodeNameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addDuplicate(const SceneNodeHandle& nodeUniqueID,
                                                  const char* newNodeNameTag) {
    if(!newNodeNameTag)
        return NULL;
    CSceneNode* pSourceNode = get(nodeUniqueID);
    if(!pSourceNode)
        return NULL;
    return addDuplicate(pSourceNode, std::string(newNodeNameTag));
}

/**
 * 
 * @param sourceNodeNameTag
 * @param newNodeNameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addDuplicate(const std::string& sourceNodeNameTag,
                                                  const std::string& newNodeNameTag) {
    if(newNodeNameTag.empty() || sourceNodeNameTag.empty())
        return NULL;
    CSceneNode* pSourceNode = get(sourceNodeNameTag);
    if(!pSourceNode)
        return NULL;
    return addDuplicate(pSourceNode, newNodeNameTag);
}

/**
 * 
 * @param sourceNodeNameTag
 * @param newNodeNameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::addDuplicate(const char* sourceNodeNameTag,
                                                  const char* newNodeNameTag) {
    if(!sourceNodeNameTag || !newNodeNameTag)
        return NULL;
    if(!sourceNodeNameTag[0] || !newNodeNameTag[0])
        return NULL;
    CSceneNode* pSourceNode = get(sourceNodeNameTag);
    if(!pSourceNode)
        return NULL;
    return addDuplicate(pSourceNode, std::string(newNodeNameTag));
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool gfx::CSceneManager::remove(CSceneNode* pObj) {
    if(!pObj || !isManaged(pObj)) {
        return FG_FALSE;
    }
    if(pObj->getTreeNode()) {
        pObj->getTreeNode()->removeObject(pObj);
        pObj->setTreeNode(NULL);
    }
    pObj->setManaged(FG_FALSE);
    // Reset the manager pointer - object is not managed - it is no longer needed
    pObj->setManager(NULL);
    return handle_mgr_type::releaseHandle(pObj->getHandle());
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::remove(const SceneNodeHandle& oUniqueID) {
    return remove(handle_mgr_type::dereference(oUniqueID));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::remove(const std::string& nameTag) {
    return remove(handle_mgr_type::dereference(nameTag));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::remove(const char* nameTag) {
    return remove(handle_mgr_type::dereference(nameTag));
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(CSceneNode*& pObj) {
    if(!gfx::CSceneManager::remove(pObj)) {
        return FG_FALSE;
    }
    delete pObj;
    pObj = NULL;
    return FG_TRUE;
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(const SceneNodeHandle& oUniqueID) {
    CSceneNode *pObj = handle_mgr_type::dereference(oUniqueID);
    return destroyNode(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(const std::string& nameTag) {
    CSceneNode *pObj = handle_mgr_type::dereference(nameTag);
    return destroyNode(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(const char* nameTag) {
    CSceneNode *pObj = handle_mgr_type::dereference(nameTag);
    return destroyNode(pObj);
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
gfx::CSceneNode * gfx::CSceneManager::get(const SceneNodeHandle& oUniqueID) {
    return handle_mgr_type::dereference(oUniqueID);
}

/**
 * 
 * @param nameTag
 * @return 
 */
gfx::CSceneNode * gfx::CSceneManager::get(const std::string& nameTag) {
    return handle_mgr_type::dereference(nameTag);
}

/**
 * 
 * @param nameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::get(const char* nameTag) {
    return handle_mgr_type::dereference(nameTag);
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const CSceneNode* pObj) {
    if(!pObj) {
        return FG_FALSE;
    }
    if(FG_IS_INVALID_HANDLE(pObj->getHandle()) ||
       !handle_mgr_type::isHandleValid(pObj->getHandle())) {
        return FG_FALSE;
    }
    // This last check is an overkill
    //if(!fgHandleManager::isDataManaged(pObj)) {
    //    return FG_FALSE;
    //}
    return FG_TRUE;
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const SceneNodeHandle& oUniqueID) {
    CSceneNode* pObj = get(oUniqueID);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const std::string& nameTag) {
    CSceneNode* pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const char *nameTag) {
    CSceneNode* pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}
