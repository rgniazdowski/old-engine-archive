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
#include "GFX/fgGfxModelResource.h"

#include "Resource/fgResourceManager.h"
#include "Util/fgStrings.h"

#include "fgDebugConfig.h"
#if defined(FG_DEBUG)
#include "Util/fgProfiling.h"
#endif

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneManager::CSceneManager() :
base_type(),
drawing_batch_type(),
handle_mgr_type(),
m_collisionsInfo(),
m_triggers(),
m_pickSelection(),
m_traverse(),
m_stateFlags(NONE | FRUSTUM_CHECK),
m_groundGrid(),
m_worldSize(),
m_camera(CCameraAnimation::FREE),
m_skybox(),
m_rootNodes(),
m_activeRootNode(NULL),
m_visibleNodes(),
m_pResourceMgr(NULL),
m_sceneEventMgr(NULL),
m_pNodeFactory(NULL),
m_basetree(NULL) {
    m_groundGrid.set(Planef::Y, 0.0f);
    m_groundGrid.cellSize = 50.0f;
    m_managerType = FG_MANAGER_SCENE;
    m_skybox.setScale(FG_GFX_PERSPECTIVE_ZFAR_DEFAULT * 1.1f); // #FIXME #SKYBOX scale
    m_skybox.setMVP(getMVP());
    m_sceneEventMgr = new event::CEventManager(sizeof (event::SSceneEvent));
    m_triggers.reserve(4);
    m_traverse.rewind();
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
    m_pNodeFactory = NULL;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::destroy(void) {
    batch_type::flush();
    if(m_basetree) {
        m_basetree->deleteRoot();
    }
    m_collisionsInfo.clear();
    unsigned int nRoots = m_rootNodes.size();
    for(unsigned int i = 0; i < nRoots; i++) {
        destroyNode(m_rootNodes[i]);
        m_rootNodes[i] = NULL;
    }
    m_rootNodes.clear();
    // Delete all gfx objects remaining in the scene
    DataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        CSceneNode* pObj = (*itor).data;
        if(pObj == NULL)
            continue;
        destroyNode(pObj);
        (*itor).clear();
    }
    m_triggers.clear_optimised();
    self_type::clear();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::clearScene(void) {
    batch_type::flush();
    if(m_basetree) {
        m_basetree->deleteRoot();
    }
    m_collisionsInfo.clear();
    unsigned int nRoots = m_rootNodes.size();
    for(unsigned int i = 0; i < nRoots; i++) {
        destroyNode(m_rootNodes[i]);
        m_rootNodes[i] = NULL;
    }
    m_rootNodes.clear();
    // Delete all gfx objects in the scene
    DataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        CSceneNode* pObj = (*itor).data;
        if(pObj == NULL)
            continue;
        destroyNode(pObj);
        (*itor).clear();
    }
    m_triggers.clear_optimised();
    releaseAllHandles();
    if(m_sceneEventMgr) {
        event::SSceneEvent* clearEvent = (event::SSceneEvent*) m_sceneEventMgr->requestEventStruct();
        clearEvent->code = event::SCENE_CLEARED;
        clearEvent->node.reset();

        event::CArgumentList *argList = m_sceneEventMgr->requestArgumentList();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)clearEvent);
        argList->push(event::SArgument::Type::ARG_POINTER, (void *)this); // pointer to the manager
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
    batch_type::setShaderManager(pShaderMgr);
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

void gfx::CSceneManager::refreshGfxInternals(void) {
    m_traverse.rewind();
    while(m_traverse.next(getActiveRootNode())) {
        CSceneNode *pSceneNode = m_traverse.current;
        if(!pSceneNode)
            continue;
        if(pSceneNode->getNodeType() == SCENE_NODE_ROOT) {
            continue; // for now skip the root nodes in linear traversal
        }
        pSceneNode->refreshGfxInternals();
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::flush(void) {
    batch_type::flush();
    m_visibleNodes.clear();
    m_drawableQueue.clear();
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
        m_pickSelection.init(m_MVP, m_camera, m_stateFlags);
        // Calculate initial ray intersection (on click)
        fgBool groundStatus = m_groundGrid.rayIntersect(m_pickSelection.rayEye,
                                                        m_pickSelection.rayDir,
                                                        m_pickSelection.groundIntersectionPoint[0],
                                                        FG_TRUE);
        if(!groundStatus)
            m_pickSelection.groundIntersectionPoint[0] = Vector3f();

    }

}
//------------------------------------------------------------------------------

void gfx::CSceneManager::clearSelection(void) {
    unsigned int n = m_pickSelection.h_selectedNodes.size();
    for(unsigned int i = 0; i < n; i++) {
        m_pickSelection.h_selectedNodes[i].reset();
    }
    m_pickSelection.h_selectedNodes.clear_optimised();
    m_pickSelection.pickedNodesInfo.clear();
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
pickedNodesInfo() {
    h_selectedNodes.reserve(16);
    for(int i = 0; i < 16; i++) {
        h_selectedNodes[i].reset();
    }
    pickBegin = timesys::exact();
}
//------------------------------------------------------------------------------

gfx::CSceneManager::SPickSelection::~SPickSelection() {
    const unsigned int n = h_selectedNodes.capacity();
    for(unsigned int i = 0; i < n; i++) {
        h_selectedNodes[i].reset();
    }
    h_selectedNodes.clear();
    pickedNodesInfo.clear();
    h_lastSelectedNode.reset();
    shouldUnselect = FG_FALSE;
    shouldCheck = FG_FALSE;
    isToggle = FG_FALSE;
    isGroup = FG_FALSE;
    checkBox = FG_FALSE;

    pickBegin = 0.0f;
    goodPickResult = Result::NOT_PICKED;
    memset(&groundIntersectionPoint[0], 0, sizeof (Vector3f));
    memset(&groundIntersectionPoint[1], 0, sizeof (Vector3f));
    memset(&rayDir, 0, sizeof (Vector3f));
    memset(&rayEye, 0, sizeof (Vector3f));
    memset(&pickBox, 0, sizeof (AABB2Di));
    memset(&pickPosBegin, 0, sizeof (Vector2i));
    memset(&pickPos, 0, sizeof (Vector2i));
    memset(&aabbPoints[0], 0, sizeof (aabbPoints));
    memset(&aabbTrisIdx[0][0], 0, sizeof (aabbTrisIdx));
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
    } else if((fgBool)!!(stateFlags & PICK_SELECTION_ON_HOVER)) {

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

gfx::CSceneManager::SPickSelection::Result
gfx::CSceneManager::SPickSelection::isPicked(const CSceneNode* pNode,
                                             SPickedNodeInfo& pickInfo,
                                             const CMVPMatrix& mvp,
                                             const fgBool checkAABBTriangles) {
    pickInfo.result = (SPickedNodeInfo::Result)NOT_PICKED;
    if(!pNode)
        return NOT_PICKED;
    const BoundingVolume3Df& volume = pNode->getBoundingVolume();
    if(volume.radius < std::numeric_limits<float>::epsilon())
        return NOT_PICKED;
    const Vec3f& center = volume.center;
    const Vec3f& extent = volume.extent;
    const Vector4i& viewport = context::getViewport();
    const Vector2i& screensize = context::getScreenSize();
    bool triangleStatus = false;
    bool status = math::intersectRaySphere(rayEye, rayDir,
                                           center,
                                           volume.radius,
                                           pickInfo.intersectionPos,
                                           pickInfo.intersectionNorm);
    if(status) {
        pickInfo.result = (SPickedNodeInfo::Result)PICKED_SPHERE;
    }
    {
        Vec3f screenCenter = math::project(center, mvp.getRefViewProjMatrix(), viewport);
        float d = math::distance(center, rayEye);
        float r = volume.radius;
        float fov = mvp.getFrustum().getTangent();
        float pr = 1.0f / math::tan(fov) * r / math::sqrt(d * d - r * r); // Right
        pickInfo.onScreen.radius = pr * gfx::context::getScreenSize().y / 2.0f;
        pickInfo.onScreen.center.x = screenCenter.x;
        pickInfo.onScreen.center.y = screenCenter.y;
    }

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
                                                        pickInfo.baryPosition);
            if(triangleStatus) {
                pickInfo.result = (SPickedNodeInfo::Result)PICKED_AABB;
                break;
            }
        }
#undef v_i
    }
    if((!pickInfo.result && checkBox) || checkBox) {
        // if we need to check the picker selection box against the node        
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
        pickInfo.onScreen.box.min = pos;
        pickInfo.onScreen.box.setWidth(size.x);
        pickInfo.onScreen.box.setHeight(size.y);
        // is box2d completely inside of pickBox?
        fgBool boxStatus = pickBox.test(pickInfo.onScreen.box);
        if(boxStatus) {
            pickInfo.result = (SPickedNodeInfo::Result)goodPickResult;
        }
    }
    return (Result)pickInfo.result;
}
//------------------------------------------------------------------------------

gfx::CSceneManager::SPickSelection::Result
gfx::CSceneManager::SPickSelection::fullCheck(CSceneManager* pSceneMgr,
                                              CSceneNode* pNode,
                                              const fgBool checkAABBTriangles) {
    if(!pSceneMgr || !pNode) {
        return NOT_PICKED;
    }
    SceneNodeHandle nodeHandle = pNode->getHandle();
    pickedNodesInfo[nodeHandle].handle = nodeHandle;
    Result pickResult = isPicked(pNode,
                                 pickedNodesInfo[nodeHandle],
                                 (*pSceneMgr->getMVP()),
                                 checkAABBTriangles);
    fgBool shouldThrow = FG_TRUE;
    fgBool shouldRemove = FG_FALSE;
    const float exact = timesys::exact();
    int idx = h_selectedNodes.find(nodeHandle);
    if(pickResult == goodPickResult) {
        CSceneNode* pLastNode = pSceneMgr->getLastPickedNode();
        const float ts = pickedNodesInfo[nodeHandle].timeStamp;
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
            h_selectedNodes[0] = nodeHandle;
            if(shouldThrow) {
                pickedNodesInfo[nodeHandle].timeStamp = exact;
            }
        }
        if(isGroup && !shouldRemove && pNode->isSelected()) {
            if(-1 == h_selectedNodes.find(nodeHandle)) {
                h_selectedNodes.push_back(nodeHandle);
                pickedNodesInfo[nodeHandle].timeStamp = exact;
            }
        }

        if(pNode->isSelected())
            h_lastSelectedNode = nodeHandle;
        if(shouldThrow) {
            // Throw proper event
            event::CArgumentList *argList = pSceneMgr->getInternalEventManager()->requestArgumentList();
            event::SSceneNode* nodeEvent = (event::SSceneNode*) pSceneMgr->getInternalEventManager()->requestEventStruct();
            nodeEvent->eventType = event::SCENE_NODE_SELECTED;
            nodeEvent->setFirstNode(pNode);
            nodeEvent->setSecondNode(NULL);
            argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)nodeEvent);
            argList->push(event::SArgument::Type::ARG_POINTER, (void *)this); // pointer to the manager
            pSceneMgr->getInternalEventManager()->throwEvent(event::SCENE_NODE_SELECTED, argList);
        }
    } else {
        if(shouldUnselect) {
            pNode->unselect();
            shouldRemove = FG_TRUE;
        }
    }
    if(shouldRemove && h_selectedNodes.size() && idx >= 0) {
        unsigned int size = h_selectedNodes.size();
        h_selectedNodes[idx] = h_selectedNodes[size - 1];
        h_selectedNodes[size - 1].reset();
        h_selectedNodes.resize(size - 1);
        pickedNodesInfo[nodeHandle].timeStamp = exact;
    }
    return pickResult;
}
//------------------------------------------------------------------------------

gfx::CSceneManager::STraverse::~STraverse() {
    while(idStack.size()) {
        idStack.pop();
    }
    while(nodeStack.size()) {
        nodeStack.pop();
    }
    current = NULL;
    idx = 0;
    count = 0;
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::STraverse::rewind(void) {
    current = NULL;
    idx = 0;
    while(idStack.size()) {
        idStack.pop();
    }
    while(nodeStack.size()) {
        nodeStack.pop();
    }
    count = 0;
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::STraverse::skip(CSceneNode* pRoot) {
    if(pRoot && !idStack.empty()) {
        idx = idStack.top();
        idStack.pop();
        current = nodeStack.top();
        nodeStack.pop();
        if(current) {
        }
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::STraverse::next(CSceneNode* pRoot) {
    if(!current) {
        if(!pRoot)
            return NULL;
        rewind();
        current = pRoot;
        count++;
        return current;
    }
    const int nChildren = current->getChildrenCount();
    const CSceneNode::ChildrenVec &children = current->getChildren();
    for(int i = idx; i < nChildren; i++) {
        CSceneNode *pNode = children[i];
        if(pNode && pNode->getParent()) {
            idx = i + 1;
            nodeStack.push(current);
            idStack.push(idx);
            idx = 0;
            current = pNode;
            count++;
            return current;
        }
    }

    if(idStack.empty()) {
        current = NULL;
        return current;
    }

    idx = idStack.top();
    idStack.pop();
    current = nodeStack.top();
    nodeStack.pop();

    if(!current) {
        return current;
    }
    return next(pRoot);
}

//------------------------------------------------------------------------------

void gfx::CSceneManager::update(float delta) {
    while(m_triggers.size()) {
        STriggerInfo &info = m_triggers.back();
        CSceneNodeTrigger::TriggerActivation activation;
        if(info.isBegin)
            activation = CSceneNodeTrigger::ON_COLLISION_BEGIN;
        else
            activation = CSceneNodeTrigger::ON_COLLISION_END;
        if(info.pTrigger) {
            info.pTrigger->trigger(activation, info.pTrigger, info.pNodeB);
        }

        if(info.isBegin && m_sceneEventMgr) {
            event::SSceneNodeTrigger* triggerEvent = (event::SSceneNodeTrigger*) m_sceneEventMgr->requestEventStruct();
            triggerEvent->eventType = event::SCENE_NODE_TRIGGER_FIRED;
            triggerEvent->setTriggerNode(info.pTrigger);
            triggerEvent->setSecondNode(info.pNodeB);

            event::CArgumentList* argList = m_sceneEventMgr->requestArgumentList();
            argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)triggerEvent);
            argList->push(event::SArgument::Type::ARG_POINTER, (void *)this); // pointer to the manager
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
    CDrawingBatch::sortCalls();
    //
    // Pick selection init
    //
    m_pickSelection.init(m_MVP, m_camera, m_stateFlags);
    if(m_pickSelection.shouldCheck) {
        fgBool groundStatus = m_groundGrid.rayIntersect(m_pickSelection.rayEye,
                                                        m_pickSelection.rayDir,
                                                        m_pickSelection.groundIntersectionPoint[1],
                                                        FG_TRUE);
        if(!groundStatus)
            m_pickSelection.groundIntersectionPoint[1] = Vector3f();
    }
    const fgBool checkPickSelectionAABB = isPickSelectionAABBTriangles();
    int visibilityResult = 1;
    traits::CDrawable* pDrawable = NULL;
    CFrustum const& frustum = m_MVP.getFrustum();
    m_traverse.rewind();
    while(m_traverse.next(getActiveRootNode())) {
        CSceneNode *pSceneNode = m_traverse.current;
        if(!pSceneNode)
            continue;
        if(pSceneNode->getNodeType() == SCENE_NODE_ROOT) {
            continue; // for now skip the root nodes in linear traversal
        }
        visibilityResult = 0;
        if(pSceneNode->isActive()) {
            // There is a problem because the bounding box needs to be modified by
            // the model matrix; maybe some operator ?
            pSceneNode->update(timesys::elapsed()); // update nodes internals when active
        }
        // Ignore visibility check for node trigger
        if(!pSceneNode->checkNodeType(SCENE_NODE_TRIGGER)) {
#if defined(FG_DEBUG)
            if(g_DebugConfig.isDebugProfiling) {
                profile::g_debugProfiling->begin("GFX::Scene::FrustumCheck");
            }
#endif
            BoundingVolume3Df const& boundingVolume = pSceneNode->getBoundingVolume();
            if(isFrustumCheckSphere()) {
                visibilityResult = frustum.testSphere(boundingVolume);
            } else if(isFrustumCheck()) {
                visibilityResult = frustum.testVolume(boundingVolume);
            }
#if defined(FG_DEBUG)
            if(g_DebugConfig.isDebugProfiling) {
                profile::g_debugProfiling->end("GFX::Scene::FrustumCheck");
            }
#endif
        }
        // Set visibility (non-recursive)
        // The second flag is true by default.
        pSceneNode->setVisible(!!visibilityResult, FG_FALSE);

        // Each object is pushed to queue individually
        // Even if it contains children, single draw function should not draw
        // everyone - need specialized function for that
        // This is due to the fact that node queue sorts objects based on sorting
        // index (which is determined based on the data in the given draw call)
        // The aabb for each object is updated based on the children.
        if(pSceneNode->queryTrait(fg::traits::DRAWABLE, (void**)&pDrawable) &&
           visibilityResult > 0 &&
           !pSceneNode->getRefHandle().isNull()) {
            if(m_pickSelection.shouldCheck) {
                if(!visibilityResult) {
                    m_pickSelection.pickedNodesInfo[pSceneNode->getHandle()].clear();
                } else {
                    m_pickSelection.fullCheck(this, pSceneNode, checkPickSelectionAABB);
                }
            }
            // push to queue only nodes that have valid handle and are drawable
            m_drawableQueue.push(pDrawable);
            m_visibleNodes.push_back(pSceneNode);
        } else if(pSceneNode->checkNodeType(SCENE_NODE_OBJECT) && visibilityResult > 0) {
            m_visibleNodes.push_back(pSceneNode);
        }
    }
    m_pickSelection.end(getStateFlags());
}
//------------------------------------------------------------------------------

void gfx::CSceneManager::render(void) {
    CShaderManager* pShaderMgr = static_cast<gfx::CShaderManager*>(m_pShaderMgr);
    CShaderProgram* pProgram = pShaderMgr->getCurrentProgram();
    pProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, 1.0f);
    // Will now render main skybox
    if(!isHideSkyBox()) {
        CShaderProgram* pSkyboxProgram = m_skybox.getShaderProgram();
        if(pSkyboxProgram) {
            pShaderMgr->useProgram(pSkyboxProgram);
            if(doesSkyBoxFollowCamera()) {
                m_skybox.setPosition(m_camera.getEye());
            }
            m_skybox.draw();
            pShaderMgr->useProgram(pProgram);
        }
    }
    if(!isHideAll()) {
        // Calling underlying DrawingBatch render procedure
        // This will contain drawcalls not associated with scene/octree/quadtree structure
        CDrawingBatch::render();
        DrawablePriorityQueueItor drawItor, drawEnd;
        drawItor = m_drawableQueue.begin();
        drawEnd = m_drawableQueue.end();
        if(isHideNodes()) {
            drawItor = drawEnd;
        }
#if defined(FG_DEBUG)
        if(g_DebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::Scene::DrawNode");
        }
#endif
        for(; drawItor != drawEnd; drawItor++) {
            (*drawItor)->draw();
        }
#if defined(FG_DEBUG)
        if(g_DebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->end("GFX::Scene::DrawNode");
        }
#endif
        //----------------------------------------------------------------------
        VisibleNodesVecConstItor nodesItor, nodesEnd;
        nodesEnd = m_visibleNodes.end();
        nodesItor = m_visibleNodes.begin();
        if(isHideNodes())
            nodesItor = nodesEnd;
        //----------------------------------------------------------------------
        pShaderMgr->useProgram("DefaultShader");
        pProgram = pShaderMgr->getCurrentProgram();
        for(; nodesItor != nodesEnd; nodesItor++) {
            CSceneNode* pSceneNode = *nodesItor;
            if(!pSceneNode)
                continue;
            pProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, 0.0f);
            pProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR, 1.0f, 1.0f, 1.0f, 1.0f);
#if defined(FG_DEBUG)
            CModel* sphereModel = (CModel*)static_cast<resource::CResourceManager*>(m_pResourceMgr)->get("builtinSphere");
            SMeshBase* sphereMesh = sphereModel->getShapes()[0]->mesh;
            if(FG_DEBUG_CFG_OPTION(gfxBBoxShow) &&
               pSceneNode->checkNodeType(SCENE_NODE_OBJECT)) {
                CSceneNodeObject* pSceneObj = static_cast<CSceneNodeObject*>(pSceneNode);
                if(pSceneObj->getModel()) {
                    m_MVP.calculate(pSceneObj->getFinalModelMatrix());
                    pProgram->setUniform(&m_MVP);
                    // Current aabb - it's in model space (local)
                    AABB3Df& modelBox = pSceneObj->getModel()->getAABB();
                    // Initial Bounding box
                    primitives::drawAABBLines(modelBox, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
                    // Draw transformed bounding box #FIXME - colors FUBAR
                }
            }
            if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
                m_MVP.resetModelMatrix();
                pProgram->setUniform(&m_MVP);
                primitives::drawAABBLines(pSceneNode->getBoundingVolume(),
                                          Color4f(0.5f, 0.5f, 1.0f, 1.0f));
                if(pSceneNode->getParent()) {
                    primitives::drawLine(pSceneNode->getBoundingVolume().center,
                                         pSceneNode->getParent()->getBoundingVolume().center,
                                         Color4f(1.0f, 1.0f, 0.0f, 1.0f));
                }
            }
            if(FG_DEBUG_CFG_OPTION(gfxSphereShow)) {
                Matrix4f mat = math::translate(Matrix4f(), pSceneNode->getBoundingVolume().center);
                const float radius = pSceneNode->getBoundingVolume().radius;
                mat = math::scale(mat, Vec3f(radius, radius, radius));
                m_MVP.calculate(mat);
                pProgram->setUniform(&m_MVP);
                pProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR,
                                     1.0f, 0.8f, 0.15f, 1.0f);
                primitives::drawVertexData(sphereMesh,
                                           ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT,
                                           PrimitiveMode::LINES);
            }
#endif
            //g_fgDebugConfig.physicsBBoxShow = true; // #FIXME
#if 0
            if(FG_DEBUG_CFG_OPTION(physicsBBoxShow)) {
                physics::CCollisionBody* body = pSceneNode->getCollisionBody();
                if(body) {
                    if(body->getBodyType() == physics::CCollisionBody::BOX) {
                    } else if(body->getBodyType() == physics::CCollisionBody::SPHERE) {
                    }
                }
            }
#endif
        } // for(node queue iteration)
    }
    pProgram = pShaderMgr->getCurrentProgram();
    if(isShowGroundGrid()) {
        pProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, 0.0f);
        pProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR, 1.0f, 1.0f, 1.0f, 1.0f);
        m_groundGrid.render(pProgram, &m_MVP);
        CVertexData4v gridLines;
        Vector3f pos;
        Color3f color;
        gridLines.clear_optimised();
        m_MVP.calculate(Matrix4f());
        pProgram->setUniform(&m_MVP);
        color = Color3f(1.0f, 0.0f, 0.0f);

        pos = m_pickSelection.rayEye;
        gridLines.append(pos, Vec3f(), Vec2f(), color);
        pos = m_pickSelection.groundIntersectionPoint[1];
        gridLines.append(pos, Vec3f(), Vec2f(), color);
        primitives::drawVertexData(&gridLines,
                                   ATTRIBUTE_POSITION_BIT | ATTRIBUTE_COLOR_BIT,
                                   PrimitiveMode::LINES);
        {
            m_groundGrid.snapTo(m_pickSelection.groundIntersectionPoint[1], pos,
                                0.2f, FG_TRUE, FG_FALSE);
        }

        Matrix4f modelMat = math::translate(Matrix4f(), pos);
        m_MVP.calculate(modelMat);
        pProgram->setUniform(&m_MVP);
        primitives::drawAABBLines(AABB3Df(Vec3f(-1, -1, -1), Vec3f(1, 1, 1)), Color4f(1.0f, 1.0f, 0.0f, 1.0f));
    }
}
//------------------------------------------------------------------------------

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
        status = (pNode->checkNodeType(gfx::SCENE_NODE_TRIGGER));
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
        status = (pNode->checkNodeType(gfx::SCENE_NODE_TRIGGER));
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
        status = (pNode->checkNodeType(gfx::SCENE_NODE_TRIGGER));
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

    if(pNode->checkNodeType(SCENE_NODE_OBJECT)) {
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
    traits::CDrawable* pDrawable = NULL;
    if(pNode->queryTrait(fg::traits::DRAWABLE, (void**)&pDrawable)) {
        CDrawCall* pDrawCall = pDrawable->getDrawCall();
        if(pDrawCall) {
            pDrawCall->setMVP(&m_MVP);
            if(pShaderMgr && !pDrawCall->getShaderProgram()) {
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
        if(pChildNode->queryTrait(fg::traits::DRAWABLE, (void **)&pDrawable)) {
            CDrawCall* pDrawCall = pDrawable->getDrawCall();
            if(!pDrawCall) {
                continue;
            }
            pDrawCall->setMVP(&m_MVP);
            if(pShaderMgr && !pDrawCall->getShaderProgram()) {
                pDrawCall->setShaderProgram(pShaderMgr->getCurrentProgram());
            }
        }
    }
    pNode->update();
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::createRootNode(const std::string& name) {
    if(name.empty())
        return NULL;
    CSceneNode *pRootNode = get(name);
    if(!pRootNode) {
        pRootNode = new CSceneNode(SCENE_NODE_ROOT, NULL);
        pRootNode->setName(name);
        fgBool addStatus = addNode(pRootNode->getRefHandle(), pRootNode);
        if(!addStatus) {
            remove(pRootNode);
            delete pRootNode;
            return NULL;
        }
    }
    if(!m_activeRootNode)
        m_activeRootNode = pRootNode;
    return pRootNode;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::selectActiveRootNode(CSceneNode* pNode) {
    if(!pNode)
        return FG_FALSE;
    if(!isManaged(pNode))
        return FG_FALSE;
    int idx = m_rootNodes.find(pNode);
    if(idx < 0) {
        return FG_FALSE;
    }
    m_activeRootNode = pNode;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::selectActiveRootNode(SceneNodeHandle& nodeUniqueID) {
    return selectActiveRootNode(handle_mgr_type::dereference(nodeUniqueID));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::selectActiveRootNode(const std::string& name) {
    return selectActiveRootNode(handle_mgr_type::dereference(name));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::selectActiveRootNode(const char* name) {
    return selectActiveRootNode(handle_mgr_type::dereference(name));
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
    SceneNodeType nodeType = pNode->getNodeType();
    pNode->setHandle(nodeUniqueID);
    // By default object is set to be managed
    // However in some cases the 'managed' flag will
    // be set to FG_FALSE after addition
    pNode->setManaged(FG_TRUE);
    pNode->setManager(this); // Setup internal pointer to the manager
    if(pFatherNode != pNode && nodeType != SCENE_NODE_ROOT)
        pNode->setParent(pFatherNode); // Pointer to the parent (if any)

    if(nodeType != SCENE_NODE_ROOT && !pFatherNode) {
        // If this node is not root and does not have a father node
        // set as parent currently active root node
        if(!m_activeRootNode) {
            createRootNode(NULL); // create root node with standard name
        } // what if creating root node failed?
        pNode->setParent(m_activeRootNode);
    }

    if(pNode->getParent()) {
        pNode->getParent()->addChild(pNode);
    }

    if(!handle_mgr_type::setupName(pNode->getName().c_str(), nodeUniqueID)) {
        // Could not setup handle string tag/name for the scene node
        // The handle name tag can be empty - sometimes it is not needed
        FG_LOG_ERROR("GFX.SceneManager: Could not setup handle string tag/name for the object: '%s'", pNode->getNameStr());
    }
    //unsigned int index = pObj->getHandle().getIndex();

    initializeNode(pNode);

    if(m_basetree && nodeType != SCENE_NODE_ROOT) {
        // add to the spatial tree structure
        // it can be octree/quadtree or any other (bounding volume hierarchy)

        m_basetree->insert(pNode);
    }
    if(nodeType == SCENE_NODE_ROOT) {
        pNode->setCollidable(FG_FALSE);
        int idx = m_rootNodes.find(pNode);
        if(idx < 0) {
            // there is no such root node in the array
            m_rootNodes.push_back(pNode);
        }
    }
    // 2nd argument tells that this draw call should not be managed
    // meaning: destructor wont be called on flush()
    //fgGfxDrawingBatch::appendDrawCall(drawCall, FG_FALSE); // Don't know if needed...

    // Reserve more space for the internal collisions info structure
    // This vector stores information about nodes that are colliding in the
    // current frame
    if(handle_mgr_type::getRefDataVector().size() > m_collisionsInfo.capacity()) {
        m_collisionsInfo.reserve((unsigned int)((float)handle_mgr_type::getRefDataVector().size()*1.5f) + 32);
    }

    if(m_sceneEventMgr) {
        event::SSceneNode* nodeEvent = (event::SSceneNode*) m_sceneEventMgr->requestEventStruct();
        nodeEvent->eventType = event::SCENE_NODE_INSERTED;
        nodeEvent->setFirstNode(pNode);
        nodeEvent->setSecondNode(NULL);

        event::CArgumentList *argList = m_sceneEventMgr->requestArgumentList();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)nodeEvent);
        argList->push(event::SArgument::Type::ARG_POINTER, (void *)this); // pointer to the manager
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
    const SceneNodeType nodeType = pSourceNode->getNodeType();
    if(m_pNodeFactory) {
        if(m_pNodeFactory->isRegistered(nodeType)) {
            pNewNode = m_pNodeFactory->recreate(nodeType, pSourceNode);
        }
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

gfx::CSceneNode* gfx::CSceneManager::addFromModel(CModelResource* pModelRes,
                                                  const std::string& nameTag) {
    if(!pModelRes) {
        return NULL;
    }
    CSceneNode *pNode = new CSceneNodeObject(NULL, NULL);
    pNode->setName(nameTag);
    if(!addNode(pNode->getRefHandle(), pNode)) {
        delete pNode;
        pNode = NULL;
    }
    static_cast<CSceneNodeObject*>(pNode)->setModel(pModelRes);
    initializeNode(pNode);
    FG_LOG_DEBUG("GFX: SceneManager: Inserted object: '%s'", nameTag.c_str());
    return pNode;
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addFromModel(const std::string& modelNameTag,
                                                  const std::string& nameTag) {
    if(modelNameTag.empty() || nameTag.empty()) {
        return NULL;
    }
    resource::CResourceManager *pResourceManager = static_cast<resource::CResourceManager *>(getResourceManager());
    if(!pResourceManager) {
        return NULL;
    }
    CModelResource *pModelRes = static_cast<CModelResource *>(pResourceManager->request(modelNameTag));
    if(!pModelRes) {
        return NULL;
    }
    return addFromModel(pModelRes, nameTag);
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneManager::addFromModel(const char *modelNameTag,
                                                  const char *nameTag) {
    if(!modelNameTag || !nameTag) {
        return NULL;
    }
    resource::CResourceManager *pResourceManager = static_cast<resource::CResourceManager *>(getResourceManager());
    if(!pResourceManager) {
        return NULL;
    }
    CModelResource *pModelRes = static_cast<CModelResource *>(pResourceManager->request(modelNameTag));
    if(!pModelRes) {
        return NULL;
    }
    return addFromModel(pModelRes, std::string(nameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneManager::remove(CSceneNode* pNode) {
    if(!pNode || !isManaged(pNode)) {
        return FG_FALSE;
    }
    traits::CDrawable* pDrawable = NULL;
    if(!m_drawableQueue.empty() && pNode->queryTrait(fg::traits::DRAWABLE, (void**)&pDrawable)) {
        // need to check if the scene node
        // is already in the queue - if yes - remove
        DrawablePriorityQueueItor nodesItor, nodesEnd;
        fgBool found = FG_FALSE;
        nodesEnd = m_drawableQueue.end();
        nodesItor = m_drawableQueue.begin();
        for(; nodesItor != nodesEnd; nodesItor++) {
            traits::CDrawable* pDrawableQ = *nodesItor;
            if(!pDrawableQ)
                continue;
            if(pDrawableQ == pDrawable) {
                found = FG_TRUE;
                break;
            }
        }
        if(found) {
            // need to create new priority queue
            DrawablePriorityQueue newQueue;
            nodesItor = m_drawableQueue.begin();
            for(; nodesItor != nodesEnd; nodesItor++) {
                traits::CDrawable* pDrawableQ = *nodesItor;
                if(pDrawableQ != pDrawable) {
                    newQueue.push(pDrawableQ);
                }
            }
            m_drawableQueue.clear();
            m_drawableQueue.swap(newQueue);
        }
    }
    if(pNode->getTreeNode()) {
        pNode->getTreeNode()->removeObject(pNode);
        pNode->setTreeNode(NULL);
    }
    // Reset the manager pointer - object is not managed - it is no longer needed
    pNode->setManager(NULL); // #FIXME - what about children? they also need to be removed from the manager
    CSceneNode* parentObj = pNode->getParent();
    if(parentObj) {
        // This is also so that removeChild() wont call this function again
        parentObj->setManager(NULL);
        parentObj->removeChild(pNode);
        parentObj->setManager(this);
    }
    pNode->setManaged(FG_FALSE);
    return handle_mgr_type::releaseHandle(pNode->getHandle());
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
    if(pObj->getRefHandle().getHandle() == m_pickSelection.h_lastSelectedNode.getHandle()) {
        m_pickSelection.h_lastSelectedNode.reset();
    }
    int index = m_pickSelection.h_selectedNodes.find(pObj->getRefHandle());
    if(index >= 0) {
        m_pickSelection.h_selectedNodes[index].reset();
    }
    pObj->setManager(this); // This is so the children can also be destroyed
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
    //if(!handle_mgr_type::isDataManaged(pObj)) { }
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
