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

//------------------------------------------------------------------------------

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
m_sceneEventMgr(NULL),
m_basetree(NULL) {
    m_managerType = FG_MANAGER_SCENE;
    m_skybox.setScale(FG_GFX_PERSPECTIVE_ZFAR_DEFAULT * 1.1f); // #FIXME #SKYBOX scale
    m_skybox.setMVP(&m_MVP);
    m_sceneEventMgr = new event::CEventManager(sizeof (event::SSceneEvent));
    m_triggers.reserve(4);

}
//------------------------------------------------------------------------------

gfx::CSceneManager::~CSceneManager() {
    CSceneManager::destroy();
    if(m_sceneEventMgr) {
        delete m_sceneEventMgr;
        m_sceneEventMgr = NULL;
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::clear(void) {
    releaseAllHandles();
    m_managerType = FG_MANAGER_SCENE;
    m_pResourceMgr = NULL;
    m_basetree = NULL;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
    if(m_sceneEventMgr) {
        event::SSceneEvent* clearEvent = (event::SSceneEvent*) m_sceneEventMgr->requestEventStruct();
        clearEvent->code = event::SCENE_CLEARED;

        event::CArgumentList *argList = m_sceneEventMgr->requestArgumentList();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)clearEvent);
        m_sceneEventMgr->throwEvent(event::SCENE_CLEARED, argList);
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::initialize(void) {
    m_sceneEventMgr->initialize();
    return FG_TRUE;
}

////////////////////////////////////////////////////////////////////////////////

gfx::CSceneManager::SCollisionsInfo::SCollisionsInfo() : contacts() { }
//------------------------------------------------------------------------------

gfx::CSceneManager::SCollisionsInfo::~SCollisionsInfo() {
    clear();
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::SCollisionsInfo::reserve(const unsigned int maxObjects) {
    contacts.reserve(maxObjects);
    contacts.resize(maxObjects);
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::SCollisionsInfo::resize(const unsigned int numObjects) {
    contacts.resize(numObjects);
    contacts.reserve(numObjects);
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

void gfx::CSceneManager::SCollisionsInfo::remove(const CSceneNode* nodeA,
                                                 const CSceneNode* nodeB) {
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
//------------------------------------------------------------------------------

void gfx::CSceneManager::SCollisionsInfo::clear(void) {
    const unsigned int n = contacts.capacity();
    for(unsigned int i = 0; i < n; i++) {
        contacts[i].clear();
    }
    contacts.clear();
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::SCollisionsInfo::check(const CSceneNode*nodeA,
                                                  const CSceneNode*nodeB) const {
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
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::SCollisionsInfo::empty(void) const {
    return contacts.empty();
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::SCollisionsInfo::empty(CSceneNode*pNode) const {
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
//------------------------------------------------------------------------------

unsigned int gfx::CSceneManager::SCollisionsInfo::count(CSceneNode*pNode) const {
    if(!pNode) {
        return FG_FALSE;
    }

    const unsigned int index = pNode->getRefHandle().getIndex();
    if(index > contacts.capacity()) {
        return FG_FALSE;
    }
    return (fgBool)contacts[index].size();
}
//------------------------------------------------------------------------------

unsigned int gfx::CSceneManager::SCollisionsInfo::count(void) const {
    return contacts.size();
}
//------------------------------------------------------------------------------

unsigned int gfx::CSceneManager::SCollisionsInfo::size(void) const {
    return contacts.size();
}
//------------------------------------------------------------------------------

unsigned int gfx::CSceneManager::SCollisionsInfo::capacity(void) const {
    return contacts.capacity();
}

////////////////////////////////////////////////////////////////////////////////

void gfx::CSceneManager::setShaderManager(fg::base::CManager* pShaderMgr) {
    CDrawingBatch::setShaderManager(pShaderMgr);
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::setResourceManager(fg::base::CManager* pResourceMgr) {
    if(!pResourceMgr)
        return;
    if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
        m_pResourceMgr = pResourceMgr;
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::setSkyBoxShader(const char* shaderName) {
    if(shaderName && m_pShaderMgr) {
        m_skybox.setShaderProgram(static_cast<gfx::CShaderManager*>(m_pShaderMgr)->get(shaderName));
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::setSkyBoxShader(const std::string& shaderName) {
    if(shaderName.size() && m_pShaderMgr) {
        m_skybox.setShaderProgram(static_cast<gfx::CShaderManager*>(m_pShaderMgr)->get(shaderName));
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::flush(void) {
    CDrawingBatch::flush();
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::reportSelectionClick(const fgBool state) {
    setFlag(PICK_SELECTION_PICKER_ACTIVE, state);
    // if the mode is on click + toggle - do nothing?
    // if the mode is on click + toggle off - clear selection
    // if the mode is on click + group selection + toggle off- clear selection
    // if the mode is on click + group selection + toggle - do nothing
    if(isPickSelectionOnClick() && state) {
        m_pickSelection.pickPosBegin = m_pickSelection.pickPos;
        m_pickSelection.pickBegin = timesys::exact();
        if(!isPickSelectionToggle()) {
            clearSelection();
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::clearSelection(void) {
    unsigned int n = m_pickSelection.h_selectedNodes.size();
    for(unsigned int i = 0; i < n; i++) {
        m_pickSelection.h_selectedNodes[i].reset();
    }
    m_pickSelection.h_selectedNodes.clear_optimised();
    m_pickSelection.h_selectionTimeStamps.clear();
}
//------------------------------------------------------------------------------

gfx::CSceneManager::SPickSelection::SPickSelection() :
aabbTrisIdx {
    {
        1, 2, 4
    }, // 0: front:   124 | 234
    {
        2, 3, 4
    }, // 1
    {
        8, 1, 5
    }, // 2: left:    815 | 145
    {
        1, 4, 5
    }, // 3
    {
        2, 7, 3
    }, // 4: right:   273 | 763
    {
        7, 6, 3
    }, // 5
    {
        4, 3, 5
    }, // 6: top:     435 | 365
    {
        3, 6, 5
    }, // 7
    {
        8, 7, 1
    }, // 8: bottom:  871 | 721
    {
        7, 2, 1
    }, // 9
    {
        7, 8, 6
    }, // 10: back:    786 | 856
    {
        8, 5, 6
    } //  11
}

,
pickPos(0, 0),
pickPosBegin(0, 0),
pickBox(),
rayEye(),
rayDir(),
pickBegin(-1.0f),
goodPickResult(NOT_PICKED),
shouldUnselect(FG_FALSE),
shouldCheck(FG_FALSE),
isToggle(FG_FALSE),
isGroup(FG_FALSE),
checkBox(FG_FALSE),
h_lastSelectedNode(),
h_selectedNodes(),
h_selectionTimeStamps() {
    h_selectedNodes.reserve(16);
    for(int i = 0; i < 16; i++) {
        h_selectedNodes[i].reset();
    }
    pickBegin = timesys::exact();
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::SPickSelection::init(const CMVPMatrix& mvp,
                                              const CCamera& camera,
                                              StateFlags stateFlags) {
    //
    // Pick selection init
    //
    shouldCheck = FG_FALSE;
    shouldUnselect = FG_FALSE;
    isToggle = FG_FALSE;
    isGroup = FG_FALSE;
    goodPickResult = NOT_PICKED;

    Vector2i size;
    Vector2i pos = pickPosBegin;
    size.x = pickPos.x - pickPosBegin.x;
    size.y = pickPos.y - pickPosBegin.y;

    if(size.x < 0) {
        pos.x = pos.x + size.x;
        size.x = -1 * size.x;
    }
    if(size.y < 0) {
        pos.y = pos.y + size.y;
        size.y = -1 * size.y;
    }
    pickBox.min = pos;
    pickBox.setWidth(size.x);
    pickBox.setHeight(size.y);

    if((fgBool)!!(stateFlags & PICK_SELECTION_ON_CLICK)) {
        shouldCheck = (fgBool)!!(stateFlags & PICK_SELECTION_PICKER_ACTIVE) || !h_lastSelectedNode.isNull();
        isToggle = (fgBool)!!(stateFlags & PICK_SELECTION_TOGGLE) && shouldCheck;
        isGroup = (fgBool)!!(stateFlags & PICK_SELECTION_GROUP);
        checkBox = (fgBool)!!(stateFlags & PICK_SELECTION_BOX);
    } else if((fgBool)!!(stateFlags & PICK_SELECTION_ON_HOVER)) {
        shouldCheck = FG_TRUE;
        shouldUnselect = FG_TRUE;
        isGroup = (fgBool)!!(stateFlags & PICK_SELECTION_GROUP);
    }
    if(shouldCheck) {
        goodPickResult = PICKED_SPHERE;
        updateRay(mvp, camera);
    }
    if((fgBool)!!(stateFlags & PICK_SELECTION_AABB_TRIANGLES))
        goodPickResult = PICKED_AABB;
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::SPickSelection::end(StateFlags stateFlags) {
    if((fgBool)!!(stateFlags & PICK_SELECTION_ON_CLICK)) {
        if((fgBool)!!(stateFlags & PICK_SELECTION_PICKER_ACTIVE) == 0) {
            h_lastSelectedNode.reset();
            pickBegin = -1.0f;
            pickBox.invalidate();
            //printf("%.3f: Removing last selected node\n", timesys::exact());
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::SPickSelection::updateRay(const CMVPMatrix& mvp,
                                                   const CCamera& camera) {
    const Vector2i& screenSize = context::getScreenSize();
    //if(screenCoord.x >= 0 && screenCoord.y >= 0) {
    //    pickPosition = screenCoord;
    //}
    // Step1: 3d normalised device coords
    float x = (2.0f * pickPos.x) / (float)screenSize.x - 1.0f;
    float y = 1.0f - (2.0f * pickPos.y) / (float)screenSize.y;
    //float z = -1.0f; // -1.0f?

    rayEye = camera.getEye();
    // Step 2: 4d Homogeneous Clip Coordinates
    Vector4f rayClip = Vector4f(x, y, -1.0f, 1.0f);
    // Step 3: 4d Eye (Camera) Coordinates
    Vector4f ray4dEye = math::inverse(mvp.getRefProjMatrix()) * rayClip;
    ray4dEye.z = -1.0f;
    ray4dEye.w = 0.0f;
    // Step 4: 4d World Coordinates
    Vector4f ray4d = (math::inverse(mvp.getViewMatrix()) * ray4dEye);
    // don't forget to normalize the vector at some point
    rayDir = math::normalize(Vector3f(ray4d.x, ray4d.y, ray4d.z));
}
//------------------------------------------------------------------------------

gfx::CSceneManager::SPickSelection::Result gfx::CSceneManager::SPickSelection::isPicked(const CSceneNode* pNode,
                                                                                        const CMVPMatrix& mvp,
                                                                                        const fgBool checkAABBTriangles) {
    if(!pNode)
        return NOT_PICKED;
    Result result = NOT_PICKED;
    Vector3f intersectionPos, intersectionNorm, baryPosition;
    const BoundingVolume3Df& volume = pNode->getBoundingVolume();
    const Vec3f& center = volume.center;
    const Vec3f& extent = volume.extent;
    if(volume.radius < std::numeric_limits<float>::epsilon())
        return NOT_PICKED;
    bool triangleStatus = false;
    bool status = math::intersectRaySphere(rayEye, rayDir,
                                           center,
                                           volume.radius,
                                           intersectionPos,
                                           intersectionNorm);
    if(status)
        result = PICKED_SPHERE;

    if(status && checkAABBTriangles) {
        aabbPoints[0] = Vec3f(center.x - extent.x, center.y - extent.y, center.z + extent.z); // 1 -x, -y, +z
        aabbPoints[1] = Vec3f(center.x + extent.x, center.y - extent.y, center.z + extent.z); // 2 +x, -y, +z
        aabbPoints[2] = Vec3f(center.x + extent.x, center.y + extent.y, center.z + extent.z); // 3 +x, +y, +z
        aabbPoints[3] = Vec3f(center.x - extent.x, center.y + extent.y, center.z + extent.z); // 4 -x, +y, +z

        aabbPoints[4] = Vec3f(center.x - extent.x, center.y + extent.y, center.z - extent.z); // 5 -x, +y, -z
        aabbPoints[5] = Vec3f(center.x + extent.x, center.y + extent.y, center.z - extent.z); // 6 +x, +y, -z
        aabbPoints[6] = Vec3f(center.x + extent.x, center.y - extent.y, center.z - extent.z); // 7 +x, -y, -z
        aabbPoints[7] = Vec3f(center.x - extent.x, center.y - extent.y, center.z - extent.z); //  8 -x, -y, -z
#define v_i(_X) aabbPoints[(_X-1)]
        // now check all the walls of the AABB
        // 12 triangles
        for(unsigned int i = 0; i < 12; i++) {
            triangleStatus = math::intersectRayTriangle(rayEye,
                                                        rayDir,
                                                        v_i(aabbTrisIdx[i][0]),
                                                        v_i(aabbTrisIdx[i][1]),
                                                        v_i(aabbTrisIdx[i][2]),
                                                        baryPosition);
            if(triangleStatus) {
                result = PICKED_AABB;
                break;
            }
        }
#undef v_i
    }
    if(!result && checkBox) {
        // if we need to check the picker selection box against the node
        const Vector4i& viewport = context::getViewport();
        const Vector2i& screensize = context::getScreenSize();
        AABB3Df aabb;
        aabb.invalidate();
        aabbPoints[0] = math::project(Vec3f(center.x - extent.x, center.y - extent.y, center.z + extent.z), mvp.getRefViewProjMatrix(), viewport); // 1 -x, -y, +z
        aabbPoints[1] = math::project(Vec3f(center.x + extent.x, center.y - extent.y, center.z + extent.z), mvp.getRefViewProjMatrix(), viewport); // 2 +x, -y, +z
        aabbPoints[2] = math::project(Vec3f(center.x + extent.x, center.y + extent.y, center.z + extent.z), mvp.getRefViewProjMatrix(), viewport); // 3 +x, +y, +z
        aabbPoints[3] = math::project(Vec3f(center.x - extent.x, center.y + extent.y, center.z + extent.z), mvp.getRefViewProjMatrix(), viewport); // 4 -x, +y, +z

        aabbPoints[4] = math::project(Vec3f(center.x - extent.x, center.y + extent.y, center.z - extent.z), mvp.getRefViewProjMatrix(), viewport); // 5 -x, +y, -z
        aabbPoints[5] = math::project(Vec3f(center.x + extent.x, center.y + extent.y, center.z - extent.z), mvp.getRefViewProjMatrix(), viewport); // 6 +x, +y, -z
        aabbPoints[6] = math::project(Vec3f(center.x + extent.x, center.y - extent.y, center.z - extent.z), mvp.getRefViewProjMatrix(), viewport); // 7 +x, -y, -z
        aabbPoints[7] = math::project(Vec3f(center.x - extent.x, center.y - extent.y, center.z - extent.z), mvp.getRefViewProjMatrix(), viewport);
        for(int i = 0; i < 8; i++)
            aabb.merge(aabbPoints[i]);
        AABB2Di box2d;
        Vector2i pos, size;
        pos.x = aabb.min.x;
        pos.y = screensize.y - aabb.max.y;
        size.x = aabb.max.x - aabb.min.x;
        size.y = aabb.max.y - aabb.min.y;
        if(size.x < 0) {
            pos.x = pos.x + size.x;
            size.x = -1 * size.x;
        }
        if(size.y < 0) {
            pos.y = pos.y + size.y;
            size.y = -1 * size.y;
        }
        box2d.min = pos;
        box2d.setWidth(size.x);
        box2d.setHeight(size.y);
        // is box2d completly inside of pickBox?
        fgBool boxStatus = pickBox.test(box2d);
        if(boxStatus) {
            result = goodPickResult;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::CSceneManager::SPickSelection::Result gfx::CSceneManager::SPickSelection::fullCheck(CSceneManager* pSceneMgr,
                                                                                         CSceneNode* pNode,
                                                                                         const fgBool checkAABBTriangles) {
    if(!pSceneMgr || !pNode) {
        return NOT_PICKED;
    }
    Result pickResult = isPicked(pNode, (*pSceneMgr->getMVP()), checkAABBTriangles);
    fgBool shouldThrow = FG_TRUE;
    fgBool shouldRemove = FG_FALSE;
    const float exact = timesys::exact();
    int idx = -1;
    if(pickResult == goodPickResult) {
        CSceneNode*pLastNode = pSceneMgr->getLastPickedNode();
        SceneNodeHandle handle = pNode->getHandle();
        idx = h_selectedNodes.find(handle);
        const float ts = h_selectionTimeStamps[handle];
        if(isToggle && ts < pickBegin) {
            pNode->setSelected(!pNode->isSelected());
            if(!pNode->isSelected()) {
                shouldThrow = FG_FALSE;
                shouldRemove = FG_TRUE; // remove from the list
            }
        } else if(pNode->isSelected()) {
            // no toggle mode - already selected, no event?
            shouldThrow = FG_FALSE;
        } else if(!isToggle) {
            pNode->setSelected(FG_TRUE);
        }
        if(pLastNode && pLastNode != pNode && !isGroup) {
            // if the last node is not as the current one
            // group selection is off so...
            pLastNode->unselect();
            // no need to check for more // unless multi select?
            shouldCheck = FG_FALSE;
        }
        if(!isGroup && !shouldRemove) {
            h_selectedNodes.clear_optimised();
            h_selectedNodes.resize(1);
            h_selectedNodes[0] = handle;
            if(shouldThrow) {
                h_selectionTimeStamps[handle] = exact;
            }
        }
        if(isGroup && !shouldRemove && pNode->isSelected()) {
            if(-1 == h_selectedNodes.find(handle)) {
                h_selectedNodes.push_back(handle);
                h_selectionTimeStamps[handle] = exact;
            }
        }
        if(shouldRemove && h_selectedNodes.size()) {
            unsigned int size = h_selectedNodes.size();
            h_selectedNodes[idx] = h_selectedNodes[size - 1];
            h_selectedNodes[size - 1].reset();
            h_selectedNodes.resize(size - 1);
            h_selectionTimeStamps[handle] = exact;
        }
        if(pNode->isSelected())
            h_lastSelectedNode = handle;
        if(shouldThrow) {
            // Throw proper event
            event::CArgumentList *argList = pSceneMgr->getInternalEventManager()->requestArgumentList();
            event::SSceneNode* nodeEvent = (event::SSceneNode*) pSceneMgr->getInternalEventManager()->requestEventStruct();
            nodeEvent->eventType = event::SCENE_NODE_SELECTED;
            nodeEvent->pNodeA = pNode;
            argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)nodeEvent);
            pSceneMgr->getInternalEventManager()->throwEvent(event::SCENE_NODE_SELECTED, argList);
        }
    } else {
        if(shouldUnselect) {
            pNode->unselect();
        }
    }

    return pickResult;
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::update(void) {
    while(m_triggers.size()) {
        STriggerInfo &info = m_triggers.back();
        CSceneNodeTrigger::TriggerActivation activation;
        if(info.isBegin)
            activation = CSceneNodeTrigger::ON_COLLISION_BEGIN;
        else
            activation = CSceneNodeTrigger::ON_COLLISION_END;
        if(info.pTrigger) {
            info.pTrigger->trigger(activation, info.pNodeB);
        }

        if(info.isBegin && m_sceneEventMgr) {
            event::SSceneNodeTrigger* triggerEvent = (event::SSceneNodeTrigger*) m_sceneEventMgr->requestEventStruct();
            triggerEvent->eventType = event::SCENE_NODE_TRIGGER_FIRED;
            triggerEvent->pNodeTrigger = info.pTrigger;
            triggerEvent->pNodeB = info.pNodeB;

            event::CArgumentList* argList = m_sceneEventMgr->requestArgumentList();
            argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)triggerEvent);
            m_sceneEventMgr->throwEvent(event::SCENE_NODE_TRIGGER_FIRED, argList);
        }
        m_triggers.pop_back();
    }
    if(m_sceneEventMgr) {
        m_sceneEventMgr->executeEvents();
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::sortCalls(void) {
    if(!getShaderManager())
        return;
    m_MVP.setCamera((CCamera*)(&m_camera));
    if(getRefPriorityQueue().empty())
        CDrawingBatch::sortCalls(); // NOPE
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();

    //
    // Pick selection init // function maybe?
    //
    m_pickSelection.init(m_MVP, m_camera, m_stateFlags);
    const fgBool checkPickSelectionAABB = isPickSelectionAABBTriangles();

    DataVecItor itor = getRefDataVector().begin(), end = getRefDataVector().end();
#if 1
    for(; itor != end; itor++) {
        if(!(*itor).data)
            continue;
        CSceneNode* pNode = (*itor).data;
        if(!pNode->isActive()) {

        }
        CDrawCall* pDrawCall = pNode->getDrawCall();
#if defined(FG_DEBUG)
        if(g_DebugConfig.isDebugProfiling) {
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
        pNode->setVisible(!!visibilityResult);
#if defined(FG_DEBUG)
        if(g_DebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->end("GFX::Scene::FrustumCheck");
        }
#endif

        // Pick selection // #FIXME
        if(m_pickSelection.shouldCheck && visibilityResult) {
            m_pickSelection.fullCheck(this, pNode, checkPickSelectionAABB);
        }

        g_DebugConfig.gfxBBoxShow = true;
        // ? also need to push to queue more than one draw call
        // And i mean... wait wut? All children are registered
        // This is a tree - that needs to be traversed
        // There is no need to go through all (linear) objects through the scene
        // The aabb for each object is updated based on the children
        // Need some standard for manipulating this objects, and also for traversing
        // the tree. Also one would need some standard for special kind of tree - loose octrees?
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
    m_pickSelection.end(getStateFlags());
}
//------------------------------------------------------------------------------

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
        if(g_DebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::Scene::DrawNode");
        }
#endif
        CSceneNode*pSceneNode = m_nodeQueue.top();
        //printf("SCENENODE: %s\n", pSceneNode->getNameStr());
        pSceneNode->draw();
#if defined(FG_DEBUG)
        if(g_DebugConfig.isDebugProfiling) {
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
                CPrimitives::drawAABBLines(modelBox, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
                // Draw transformed bounding box #FIXME - colors FUBAR
            }
        }
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
            m_MVP.resetModelMatrix();
            pProgram->setUniform(&m_MVP);
            CPrimitives::drawAABBLines(pSceneNode->getBoundingVolume(), Color4f(0.5f, 0.5f, 1.0f, 1.0f));
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
//------------------------------------------------------------------------------

#if 0

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

CSceneNode* gfx::CSceneManager::appendModel(int& index,
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

gfx::CSceneCallback* gfx::CSceneManager::addCallback(event::EventType eventCode,
                                                     CSceneCallback* pCallback) {
    if(!pCallback || !m_sceneEventMgr)
        return NULL;
    if(m_sceneEventMgr->addCallback(eventCode, pCallback)) {
        return pCallback;
    } else {
        return NULL;
    }
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
        CSceneNodeTrigger* pNodeTrigger = static_cast<CSceneNodeTrigger*>(pNode);
        pNodeTrigger->addCallback(pCallback, activation);
    }
    return status;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addTrigger(const std::string& name,
                                                const Vector3f& position) {
    if(name.empty()) {
        return NULL;
    }
    CSceneNodeTrigger* pNodeTrigger = new CSceneNodeTrigger();
    pNodeTrigger->setName(name);
    pNodeTrigger->setPosition(position);
    if(!addNode(pNodeTrigger->getRefHandle(), pNodeTrigger)) {
        remove(pNodeTrigger);
        delete pNodeTrigger;
        pNodeTrigger = NULL;
    }
    return pNodeTrigger;
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addTrigger(const std::string& name,
                                                const Vector3f& position,
                                                const Vector3f& halfExtent) {
    CSceneNode* pNode = addTrigger(name, position);
    if(pNode) {
        pNode->setHalfSize(halfExtent);
    }
    return pNode;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addTrigger(const char* name,
                                                float x, float y, float z) {
    if(!name)
        return NULL;
    return addTrigger(std::string(name), Vector3f(x, y, z));
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addTrigger(const char* name,
                                                float x, float y, float z,
                                                float extX, float extY, float extZ) {
    if(!name)
        return NULL;
    return addTrigger(std::string(name), Vector3f(x, y, z), Vector3f(extX, extY, extZ));
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::initializeNode(CSceneNode* pNode) {
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
//------------------------------------------------------------------------------

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

    if(m_sceneEventMgr) {
        event::SSceneNode* nodeEvent = (event::SSceneNode*) m_sceneEventMgr->requestEventStruct();
        nodeEvent->eventType = event::SCENE_NODE_INSERTED;
        nodeEvent->pNodeA = pNode;
        nodeEvent->pNodeB = NULL;

        event::CArgumentList *argList = m_sceneEventMgr->requestArgumentList();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)nodeEvent);
        m_sceneEventMgr->throwEvent(event::SCENE_NODE_INSERTED, argList);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::addNode(SceneNodeHandle& oUniqueID,
                                   CSceneNode* pObj,
                                   const SceneNodeHandle& oFatherUniqueID) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherUniqueID));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::addNode(SceneNodeHandle& oUniqueID,
                                   CSceneNode* pObj,
                                   const std::string& oFatherNameTag) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherNameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::addNode(SceneNodeHandle& oUniqueID,
                                   CSceneNode* pObj,
                                   const char* oFatherNameTag) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherNameTag));
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addDuplicate(CSceneNode* pSourceNode,
                                                  const std::string& newNodeNameTag) {
    if(!pSourceNode || newNodeNameTag.empty())
        return NULL;
    if(pSourceNode->getManager() != this || !pSourceNode->isManaged())
        return NULL;
    CSceneNode* pNewNode = get(newNodeNameTag);
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
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addDuplicate(CSceneNode* pSourceNode,
                                                  const char* newNodeNameTag) {
    if(!pSourceNode || !newNodeNameTag)
        return NULL;
    return addDuplicate(pSourceNode, std::string(newNodeNameTag));
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addDuplicate(const SceneNodeHandle& nodeUniqueID,
                                                  const std::string& newNodeNameTag) {
    CSceneNode* pSourceNode = get(nodeUniqueID);
    if(!pSourceNode)
        return NULL;
    return addDuplicate(pSourceNode, newNodeNameTag);
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addDuplicate(const SceneNodeHandle& nodeUniqueID,
                                                  const char* newNodeNameTag) {
    if(!newNodeNameTag)
        return NULL;
    CSceneNode* pSourceNode = get(nodeUniqueID);
    if(!pSourceNode)
        return NULL;
    return addDuplicate(pSourceNode, std::string(newNodeNameTag));
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addDuplicate(const std::string& sourceNodeNameTag,
                                                  const std::string& newNodeNameTag) {
    if(newNodeNameTag.empty() || sourceNodeNameTag.empty())
        return NULL;
    CSceneNode* pSourceNode = get(sourceNodeNameTag);
    if(!pSourceNode)
        return NULL;
    return addDuplicate(pSourceNode, newNodeNameTag);
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::remove(const SceneNodeHandle& oUniqueID) {
    return remove(handle_mgr_type::dereference(oUniqueID));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::remove(const std::string& nameTag) {
    return remove(handle_mgr_type::dereference(nameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::remove(const char* nameTag) {
    return remove(handle_mgr_type::dereference(nameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::destroyNode(CSceneNode*& pObj) {
    if(!gfx::CSceneManager::remove(pObj)) {
        return FG_FALSE;
    }
    delete pObj;
    pObj = NULL;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::destroyNode(const SceneNodeHandle& oUniqueID) {
    CSceneNode *pObj = handle_mgr_type::dereference(oUniqueID);
    return destroyNode(pObj);
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::destroyNode(const std::string& nameTag) {
    CSceneNode *pObj = handle_mgr_type::dereference(nameTag);
    return destroyNode(pObj);
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::destroyNode(const char* nameTag) {
    CSceneNode* pObj = handle_mgr_type::dereference(nameTag);
    return destroyNode(pObj);
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::get(const SceneNodeHandle& oUniqueID) {
    return handle_mgr_type::dereference(oUniqueID);
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::get(const std::string& nameTag) {
    return handle_mgr_type::dereference(nameTag);
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::get(const char* nameTag) {
    return handle_mgr_type::dereference(nameTag);
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::isManaged(const SceneNodeHandle& oUniqueID) {
    CSceneNode* pObj = get(oUniqueID);
    return (fgBool)(pObj != NULL);
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::isManaged(const std::string& nameTag) {
    CSceneNode* pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::isManaged(const char *nameTag) {
    CSceneNode* pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}
//------------------------------------------------------------------------------
