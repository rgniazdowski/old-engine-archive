/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_SCENE_MANAGER
    #define FG_INC_GFX_SCENE_MANAGER
    #define FG_INC_GFX_SCENE_MANAGER_BLOCK

    #include "Util/fgHandleManager.h"
    #include "Event/fgEventManager.h"
    #include "GFX/fgGfxDrawingBatch.h"
    #include "GFX/fgGfxCameraAnimation.h"

    #include "Util/fgBTreeMap.h"

    #include "fgGfxBasetree.h"
    #include "fgGfxSceneCallback.h"
    #include "fgGfxSceneNode.h"
    #include "fgGfxSceneNodeTrigger.h"
    #include "fgGfxSceneNodeMesh.h"
    #include "fgGfxSceneNodeObject.h"
    #include "fgGfxSceneSkyBox.h"    

    #include "GFX/fgGfxPlaneGrid.h"
    #include "fgGfxNodeFactory.h"

    #define FG_MANAGER_SCENE        0x00001000

namespace fg {

    namespace gfx {

        class CSceneCallback;
        class CSceneNodeTrigger;

        /**
         *
         */
        class CSceneManager :
        public fg::base::CManager,
        public CDrawingBatch,
        protected fg::util::CHandleManager<CSceneNode *, SceneNodeHandle> {
        public:
            ///
            typedef CSceneManager self_type;
            ///
            typedef fg::base::CManager base_type;
            ///
            typedef CDrawingBatch batch_type;
            ///
            typedef CDrawingBatch drawing_batch_type;
            ///
            typedef fg::util::CHandleManager<CSceneNode *, SceneNodeHandle> handle_mgr_type;
            ///
            typedef CSceneNode node_type;
            ///
            typedef SceneNodeHandle handle_type;
            ///
            typedef CVector<CSceneNode*> VisibleNodesVec;
            ///
            typedef VisibleNodesVec::const_iterator VisibleNodesVecConstItor;
            ///
            typedef VisibleNodesVec::iterator VisibleNodesVecItor;
            typedef CPriorityQueue<traits::CDrawable*, std::deque<traits::CDrawable*>, fgPtrLessEq<traits::CDrawable*> > DrawablePriorityQueue;
            typedef DrawablePriorityQueue::const_iterator DrawablePriorityQueueConstItor;
            typedef DrawablePriorityQueue::iterator DrawablePriorityQueueItor;
            ///
            typedef CVector<CSceneNode *> ObjectsVec;
            ///
            typedef ObjectsVec::iterator ObjectsVecItor;

        public:

            /**
             * Maximum is: 0x10 00 00 00
             */
            enum StateFlags {
                /// No special scene state flags specified
                NONE = 0x00000,
                /// Linear traverse forced - no spatial trees are used (octree/quadtree)
                LINEAR_TRAVERSE = 0x00001,
                /// Ignore collisions between nodes (coarse and fine), no events thrown
                IGNORE_COLLISIONS = 0x00002,
                /// Hide all nodes
                HIDE_NODES = 0x00004,
                /// Hide just the skybox
                HIDE_SKYBOX = 0x00008,
                /// No additional shadows for scene objects
                HIDE_SHADOWS = 0x00010, // 16
                /// Hide everything - nodes, skybox, additional drawcalls
                HIDE_ALL = 0x0001C, // 4 + 8 + 16 = 28
                /// Frustum check will be performed (AABB)
                FRUSTUM_CHECK = 0x00020, // 32
                /// Frustum check will be performed (AABB)
                FRUSTUM_CHECK_BOX = 0x00020, // 32
                /// Frustum check will be performed based on bounding spheres
                FRUSTUM_CHECK_SPHERE = 0x00040, // 64
                /// Occlusion check will be performed
                OCCLUSION_CHECK = 0x00080, // 128
                /// single pick selection active (on click actions)
                PICK_SELECTION_ON_CLICK = 0x00100, // 256
                /// Continuous pick selection active (mouse movement / hover)
                PICK_SELECTION_ON_HOVER = 0x00200, // 512
                /// Should pick selection be more accurate
                PICK_SELECTION_AABB_TRIANGLES = 0x00400, // 1024
                /// The state of pick selection (mouse/picker state)
                /// When active the picker is currently selecting, used only
                /// when pick selection is in click mode
                /// Pick selection does not care what mouse button (or anything)
                /// is used, picker state is reported from outside
                PICK_SELECTION_PICKER_ACTIVE = 0x00800, // 2048
                /// Is group selection active? If yes, then multiple nodes can
                /// be selected by clicking or holding mouse button down and
                /// drawing a selection rectangle, ignored in hover mode
                PICK_SELECTION_GROUP = 0x01000, // 4096
                /// Pick selection toggle mode?
                /// The second click deselects the node (if already selected)
                /// Ignored in hover mode; Works also with rectangle selection
                PICK_SELECTION_TOGGLE = 0x02000, // 8192
                /// Whether or not the group selection uses selection box
                /// valid only with on click selection
                PICK_SELECTION_BOX = 0x04000, // 16384
                ///
                SHOW_GROUND_GRID = 0x08000, // 32768
                ///
                SKYBOX_FOLLOWS_CAMERA = 0x10000 // 65536
            };

        protected:
            /**
             * This should be called something like resetInternals?
             */
            virtual void clear(void);

            /**
             * 
             * @param pNode
             */
            virtual void initializeNode(CSceneNode* pNode);

        public:
            /**
             * 
             */
            CSceneManager();
            /**
             * 
             */
            virtual ~CSceneManager();

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param pShaderMgr
             */
            virtual void setShaderManager(fg::base::CManager* pShaderMgr);
            /**
             * 
             * @param pNodeFactory
             */
            void setNodeFactory(CNodeFactory* pNodeFactory) {
                m_pNodeFactory = pNodeFactory;
            }
            /**
             * 
             * @return 
             */
            inline event::CEventManager* getInternalEventManager(void) const {
                return m_sceneEventMgr;
            }
            /**
             * 
             * @return 
             */
            inline fg::base::CManager* getShaderManager(void) const {
                return m_pShaderMgr;
            }
            /**
             * 
             * @return
             */
            inline CNodeFactory* getNodeFactory(void) const {
                return m_pNodeFactory;
            }
            /**
             * Set internal pointer to the main resource manager
             * @param pResourceMgr
             */
            void setResourceManager(fg::base::CManager* pResourceMgr);
            /**
             * Get internal pointer to the main resource manager
             * @return 
             */
            inline fg::base::CManager* getResourceManager(void) const {
                return m_pResourceMgr;
            }

            ////////////////////////////////////////////////////////////////////
        protected:
            /**
             * 
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);

        public:
            /**
             * 
             * @return 
             */
            StateFlags getStateFlags(void) const {
                return m_stateFlags;
            }
            /**
             * 
             * @param toggle
             */
            inline void setLinearTraverse(const fgBool toggle = FG_TRUE) {
                setFlag(LINEAR_TRAVERSE, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isLinearTraverse(void) const {
                return (fgBool)!!(m_stateFlags & LINEAR_TRAVERSE);
            }
            /**
             * 
             * @param toggle
             */
            inline void setIgnoreCollisions(const fgBool toggle = FG_TRUE) {
                setFlag(IGNORE_COLLISIONS, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isIgnoreCollisions(void) const {
                return (fgBool)!!(m_stateFlags & IGNORE_COLLISIONS);
            }
            /**
             * 
             * @param toggle
             */
            inline void setHideNodes(const fgBool toggle = FG_TRUE) {
                setFlag(HIDE_NODES, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isHideNodes(void) const {
                return (fgBool)!!(m_stateFlags & HIDE_NODES);
            }
            /**
             * 
             * @param toggle
             */
            inline void setHideSkyBox(const fgBool toggle = FG_TRUE) {
                setFlag(HIDE_SKYBOX, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isHideSkyBox(void) const {
                return (fgBool)!!(m_stateFlags & HIDE_SKYBOX);
            }
            /**
             * 
             * @param toggle
             */
            inline void setHideShadows(const fgBool toggle = FG_TRUE) {
                setFlag(HIDE_SHADOWS, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isHideShadows(void) const {
                return (fgBool)!!(m_stateFlags & HIDE_SHADOWS);
            }
            /**
             * 
             * @param toggle
             */
            inline void setHideAll(const fgBool toggle = FG_TRUE) {
                setFlag(HIDE_ALL, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isHideAll(void) const {
                return (fgBool)((m_stateFlags & HIDE_ALL) == HIDE_ALL);
            }
            /**
             * 
             * @param toggle
             */
            inline void setFrustumCheck(const fgBool toggle = FG_TRUE) {
                if(toggle)
                    setFlag(FRUSTUM_CHECK_SPHERE, FG_FALSE);
                setFlag(FRUSTUM_CHECK, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isFrustumCheck(void) const {
                return (fgBool)!!(m_stateFlags & FRUSTUM_CHECK);
            }
            /**
             * 
             * @param toggle
             */
            inline void setFrustumCheckSphere(const fgBool toggle = FG_TRUE) {
                setFlag(FRUSTUM_CHECK, !toggle);
                setFlag(FRUSTUM_CHECK_SPHERE, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isFrustumCheckSphere(void) const {
                return (fgBool)!!(m_stateFlags & FRUSTUM_CHECK_SPHERE);
            }
            /**
             * 
             * @param toggle
             */
            inline void setOcclusionCheck(const fgBool toggle = FG_TRUE) {
                setFlag(OCCLUSION_CHECK, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isOcclusionCheck(void) const {
                return (fgBool)!!(m_stateFlags & OCCLUSION_CHECK);
            }
            /**
             *
             * @param toggle
             */
            inline void setPickSelectionOnClick(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_ON_HOVER, FG_FALSE);
                setFlag(PICK_SELECTION_ON_CLICK, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isPickSelectionOnClick(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_ON_CLICK);
            }
            /**
             *
             * @param toggle
             */
            inline void setPickSelectionOnHover(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_ON_CLICK, FG_FALSE);
                setFlag(PICK_SELECTION_ON_HOVER, toggle);
            }
            /**
             * 
             * @return
             */
            inline fgBool isPickSelectionOnHover(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_ON_HOVER);
            }
            /**
             *
             * @param toggle
             */
            inline void setPickSelectionAABBTriangles(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_AABB_TRIANGLES, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isPickSelectionAABBTriangles(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_AABB_TRIANGLES);
            }
            /**
             *
             * @param toggle
             */
            inline void setPickSelectionGroup(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_GROUP, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isPickSelectionGroup(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_GROUP);
            }
            /**
             * 
             * @param toggle
             */
            inline void setPickSelectionToggle(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_TOGGLE, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isPickSelectionToggle(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_TOGGLE);
            }
            /**
             * 
             * @param toggle
             */
            inline void setPickSelectionBox(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_BOX, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isPickSelectionBox(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_BOX);
            }
            /**
             * 
             * @param toggle
             */
            inline void setShowGroundGrid(const fgBool toggle = FG_TRUE) {
                setFlag(SHOW_GROUND_GRID, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isShowGroundGrid(void) const {
                return (fgBool)!!(m_stateFlags & SHOW_GROUND_GRID);
            }
            /**
             *
             * @param toggle
             */
            inline void setSkyBoxFollowsCamera(const fgBool toggle = FG_TRUE) {
                setFlag(SKYBOX_FOLLOWS_CAMERA, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isSkyBoxFollowsCamera(void) const {
                return (fgBool)!!(m_stateFlags & SKYBOX_FOLLOWS_CAMERA);
            }
            /**
             *
             * @return
             */
            inline fgBool doesSkyBoxFollowCamera(void) const {
                return (fgBool)!!(m_stateFlags & SKYBOX_FOLLOWS_CAMERA);
            }

            //------------------------------------------------------------------
            /**
             *
             * @param position
             */
            inline void reportSelectionMove(const Vector2i& position) {
                m_pickSelection.pickPos = position;
            }
            /**
             *
             * @param x
             * @param y
             */
            inline void reportSelectionMove(int x, int y) {
                m_pickSelection.pickPos.x = x;
                m_pickSelection.pickPos.y = y;
            }
            /**
             *
             * @param state
             */
            void reportSelectionClick(const fgBool state = FG_TRUE);
            /**
             *
             */
            inline void reportSelectionUnclick(void) {
                reportSelectionClick(FG_FALSE);
            }
            /**
             * 
             */
            void clearSelection(void);
            /**
             * 
             * @return
             */
            SceneNodeHandle getLastPickedNodeHandle(void) const {
                return m_pickSelection.h_lastSelectedNode;
            }
            /**
             *
             */
            CSceneNode *getLastPickedNode(void) {
                return get(m_pickSelection.h_lastSelectedNode);
            }
            /**
             *
             * @return
             */
            SceneNodeHandle getCurrentPickedNodeHandle(void) const {
                return m_pickSelection.h_selectedNodes[0];
            }
            /**
             *
             */
            CSceneNode *getCurrentPickedNode(void) {
                return get(m_pickSelection.h_selectedNodes[0]);
            }
            /**
             *
             * @param count
             * @return
             */
            CVector<SceneNodeHandle>& getCurrentPickedNodeHandles(unsigned int* count) {
                if(count)
                    *count = (unsigned int)m_pickSelection.h_selectedNodes.size();
                return m_pickSelection.h_selectedNodes;
            }
            /**
             * 
             * @param count
             * @return 
             */
            CVector<SceneNodeHandle> const& getCurrentPickedNodeHandles(unsigned int* count) const {
                if(count)
                    *count = (unsigned int)m_pickSelection.h_selectedNodes.size();
                return m_pickSelection.h_selectedNodes;
            }
            /**
             * 
             * @return 
             */
            inline fgBool isPickSelectionPickerActive(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_PICKER_ACTIVE);
            }
            /**
             * 
             * @param rayEye
             * @param rayDir
             */
            inline void getPickSelectionRayInfo(Vec3f& rayEye, Vec3f& rayDir) {
                rayDir = m_pickSelection.rayDir;
                rayEye = m_pickSelection.rayEye;
            }
            /**
             * 
             * @return 
             */
            Vector2i& getPickSelectionPos(void) {
                return m_pickSelection.pickPos;
            }
            /**
             *
             * @return
             */
            Vector2i const& getPickSelectionPos(void) const {
                return m_pickSelection.pickPos;
            }
            /**
             *
             * @return
             */
            Vector2i& getPickSelectionPosStart(void) {
                return m_pickSelection.pickPosBegin;
            }
            /**
             * 
             * @return
             */
            Vector2i const& getPickSelectionPosStart(void) const {
                return m_pickSelection.pickPosBegin;
            }
            /**
             *
             * @return
             */
            AABoundingBox2Di& getPickSelectionBox(void) {
                return m_pickSelection.pickBox;
            }
            /**
             * 
             * @return
             */
            AABoundingBox2Di const& getPickSelectionBox(void) const {
                return m_pickSelection.pickBox;
            }
        public:
            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            virtual int getZIndex(void) const {
                return m_zIndex;
            }
            /**
             * 
             * @param zIndex
             */
            virtual void setZIndex(const int zIndex) {
                m_zIndex = zIndex;
            }
            /**
             * 
             */
            virtual void upZIndex(void) {
                m_zIndex++;
            }
            /**
             * 
             */
            virtual void downZIndex(void) {
                m_zIndex--;
            }

            //------------------------------------------------------------------

            void refreshGfxInternals(void);

            /**
             * 
             */
            virtual void flush(void);
            /**
             * 
             */
            virtual void sortCalls(void);
            /**
             * 
             */
            virtual void render(void);
            /**
             *
             */
            virtual void update(void);

            //------------------------------------------------------------------

            /**
             * 
             * @param eventCode
             * @param pCallback
             * @return 
             */
            CSceneCallback* addCallback(event::EventType eventCode,
                                        CSceneCallback* pCallback);

            /**
             * 
             * @param pTrigger
             * @param pCallback
             * @return 
             */
            fgBool addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                      CSceneNodeTrigger* pTrigger,
                                      CSceneCallback* pCallback);

            /**
             * 
             * @param nodeUniqueID
             * @param pCallback
             * @return 
             */
            fgBool addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                      const SceneNodeHandle& nodeUniqueID,
                                      CSceneCallback* pCallback);

            /**
             * 
             * @param nameTag
             * @param pCallback
             * @return 
             */
            fgBool addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                      const std::string& nameTag,
                                      CSceneCallback* pCallback);

            /**
             * 
             * @param nameTag
             * @param pCallback
             * @return 
             */
            fgBool addTriggerCallback(CSceneNodeTrigger::TriggerActivation activation,
                                      const char* nameTag,
                                      CSceneCallback* pCallback);

            //------------------------------------------------------------------

            /**
             * 
             * @param name
             * @param position
             * @return 
             */
            CSceneNode* addTrigger(const std::string& name,
                                   const Vector3f& position);

            /**
             * 
             * @param name
             * @param position
             * @param halfExtent
             * @return 
             */
            CSceneNode* addTrigger(const std::string& name,
                                   const Vector3f& position,
                                   const Vector3f& halfExtent);

            /**
             * 
             * @param name
             * @param position
             * @return 
             */
            CSceneNode* addTrigger(const char* name,
                                   const Vector3f& position);

            /**
             * 
             * @param name
             * @param position
             * @param halfExtent
             * @return 
             */
            CSceneNode* addTrigger(const char* name,
                                   const Vector3f& position,
                                   const Vector3f& halfExtent);

            /**
             * 
             * @param name
             * @param x
             * @param y
             * @param z
             * @return 
             */
            CSceneNode* addTrigger(const char* name,
                                   float x, float y, float z);

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
            CSceneNode* addTrigger(const char* name,
                                   float x, float y, float z,
                                   float extX, float extY, float extZ);

            //------------------------------------------------------------------
            /**
             *
             * @param name
             * @return
             */
            inline CSceneNode* createRootNode(const char* name) {
                if(!name) {
                    name = "fgMainNode";
                }
                return createRootNode(std::string(name));
            }
            /**
             *
             * @param name
             * @return
             */
            virtual CSceneNode* createRootNode(const std::string& name);

            /**
             *
             * @param pNode
             * @return
             */
            virtual fgBool selectActiveRootNode(CSceneNode* pNode);
            /**
             *
             * @param nodeUniqueID
             * @return
             */
            fgBool selectActiveRootNode(SceneNodeHandle& nodeUniqueID);
            /**
             * 
             * @param name
             * @return
             */
            fgBool selectActiveRootNode(const std::string& name);
            /**
             *
             * @param name
             * @return
             */
            fgBool selectActiveRootNode(const char* name);
            /**
             *
             * @return
             */
            CSceneNode* getActiveRootNode(void) const {
                return m_activeRootNode;
            }

            //------------------------------------------------------------------

            /**
             * 
             * @param nodeUniqueID
             * @param pNode
             * @param pFatherNode
             * @return 
             */
            virtual fgBool addNode(SceneNodeHandle& nodeUniqueID,
                                   CSceneNode *pNode,
                                   CSceneNode *pFatherNode = NULL);
            /**
             * 
             * @param nodeUniqueID
             * @param pNode
             * @param nodeParentUniqueID
             * @return 
             */
            fgBool addNode(SceneNodeHandle& nodeUniqueID,
                           CSceneNode *pNode,
                           const SceneNodeHandle& nodeParentUniqueID);
            /**
             * 
             * @param nodeUniqueID
             * @param pNode
             * @param nodeParentNameTag
             * @return 
             */
            fgBool addNode(SceneNodeHandle& nodeUniqueID,
                           CSceneNode *pNode,
                           const std::string& nodeParentNameTag);
            /**
             * 
             * @param nodeUniqueID
             * @param pNode
             * @param nodeParentNameTag
             * @return 
             */
            fgBool addNode(SceneNodeHandle& nodeUniqueID,
                           CSceneNode *pNode,
                           const char* nodeParentNameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param pSourceNode
             * @param newNodeNameTag
             * @return 
             */
            CSceneNode* addDuplicate(CSceneNode* pSourceNode,
                                     const std::string& newNodeNameTag);

            /**
             * 
             * @param pSourceNode
             * @param newNodeNameTag
             * @return 
             */
            CSceneNode* addDuplicate(CSceneNode* pSourceNode,
                                     const char* newNodeNameTag);

            /**
             * 
             * @param nodeUniqueID
             * @param newNodeNameTag
             * @return 
             */
            CSceneNode* addDuplicate(const SceneNodeHandle& nodeUniqueID,
                                     const std::string& newNodeNameTag);

            /**
             * 
             * @param nodeUniqueID
             * @param newNodeNameTag
             * @return 
             */
            CSceneNode* addDuplicate(const SceneNodeHandle& nodeUniqueID,
                                     const char* newNodeNameTag);

            /**
             * 
             * @param sourceNodeNameTag
             * @param newNodeNameTag
             * @return 
             */
            CSceneNode* addDuplicate(const std::string& sourceNodeNameTag,
                                     const std::string& newNodeNameTag);

            /**
             * 
             * @param sourceNodeNameTag
             * @param newNodeNameTag
             * @return 
             */
            CSceneNode* addDuplicate(const char* sourceNodeNameTag,
                                     const char* newNodeNameTag);

            //------------------------------------------------------------------

            /**
             *
             * @param pModelRes
             * @param nameTag
             * @return
             */
            CSceneNode *addFromModel(CModelResource *pModelRes,
                                     const std::string& nameTag);
            /**
             *
             * @param modelNameTag
             * @param nameTag
             * @return
             */
            CSceneNode *addFromModel(const std::string& modelNameTag,
                                     const std::string& nameTag);
            /**
             *
             * @param modelNameTag
             * @param nameTag
             * @return
             */
            CSceneNode *addFromModel(const char *modelNameTag,
                                     const char *nameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param pNode
             * @return 
             */
            virtual fgBool remove(CSceneNode *pNode);
            /**
             * 
             * @param nodeUniqueID
             * @return 
             */
            virtual fgBool remove(const SceneNodeHandle& nodeUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool remove(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool remove(const char *nameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param pNode
             * @return 
             */
            virtual fgBool destroyNode(CSceneNode*& pNode);
            /**
             * 
             * @param nodeUniqueID
             * @return 
             */
            virtual fgBool destroyNode(const SceneNodeHandle& nodeUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool destroyNode(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool destroyNode(const char *nameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param nodeUniqueID
             * @return 
             */
            virtual CSceneNode* get(const SceneNodeHandle& nodeUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual CSceneNode* get(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual CSceneNode* get(const char *nameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param pNode
             * @return 
             */
            virtual fgBool isManaged(const CSceneNode *pNode);
            /**
             * 
             * @param nodeUniqueID
             * @return 
             */
            virtual fgBool isManaged(const SceneNodeHandle& nodeUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool isManaged(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool isManaged(const char *nameTag);

            //------------------------------------------------------------------

            /**
             * This function clears the scene, removes all nodes, tree nodes,
             * releases all handles, resets the scene basically
             */
            virtual void clearScene(void);

            //------------------------------------------------------------------
            /**
             * 
             * @param index
             * @return 
             */
            inline CSceneNode *get(const int index) {
                if(index < 0 || index >= (int)handle_mgr_type::getRefDataVector().size())
                    return NULL;
                return handle_mgr_type::getRefDataVector()[index].data;
            }

            // This is special array like operator
            // Note that there is no boundaries checking
            CSceneNode *operator [](size_t n) {
                return handle_mgr_type::getRefDataVector()[n].data;
            }

            // This is special array like operator
            // Note that there is no boundaries checking
            const CSceneNode *operator [](size_t n) const {
                return handle_mgr_type::getRefDataVector()[n].data;
            }

            //------------------------------------------------------------------

            // Returns the number of valid handles used within the handle 
            // manager. This value should not be used for any kind of iteration
            // through the internal data vector
            unsigned int count(void) const {
                return handle_mgr_type::getUsedHandleCount();
            }

            // This will return the size of the internal data vector
            // Returned value takes into account also empty slots, so
            // this is the real size of the internal data array
            unsigned int size(void) const {
                return handle_mgr_type::getRefDataVector().size();
            }

            //------------------------------------------------------------------
            /**
             * 
             */
            inline CCameraAnimation *getCamera(void) {
                return &m_camera;
            }
            /**
             * 
             * @param pCamera
             */
            inline void applyCamera(const CCamera* pCamera) {
                m_camera.setEye(pCamera->getEye());
                m_camera.setCenter(pCamera->getCenter());
                m_camera.setUp(pCamera->getUp());
            }
            /**
             * 
             * @return 
             */
            inline CMVPMatrix *getMVP(void) {
                // this function is repeated here because CDrawingBatch
                // is protected
                return &m_MVP;
            }
            inline int getLayerID(void) const {
                return drawing_batch_type::getLayerID();
            }
            inline std::string& getLayerName(void) {
                return drawing_batch_type::getLayerName();
            }
            inline std::string const& getLayerName(void) const {
                return drawing_batch_type::getLayerName();
            }
            /**
             * 
             * @return 
             */
            inline CSceneSkyBox *getSkyBox(void) {
                return &m_skybox;
            }
            /**
             * 
             * @param shaderName
             */
            void setSkyBoxShader(const char* shaderName);
            /**
             * 
             * @param shaderName
             */
            void setSkyBoxShader(const std::string& shaderName);
            /**
             * 
             * @param pProgram
             */
            inline void setSkyBoxShader(CShaderProgram* pProgram) {
                m_skybox.setShaderProgram(pProgram);
            }

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline VisibleNodesVec& getVisibleNodes(void) {
                return m_visibleNodes;
            }
            /**
             * 
             * @return 
             */
            inline VisibleNodesVec const& getVisibleNodes(void) const {
                return m_visibleNodes;
            }
            /**
             *
             * @return
             */
            inline DrawablePriorityQueue& getDrawableQueue(void) {
                return m_drawableQueue;
            }
            /**
             * 
             * @return
             */
            inline DrawablePriorityQueue const& getDrawableQueue(void) const {
                return m_drawableQueue;
            }
            /**
             * 
             * @return 
             */
            inline CBasetree *getBasetree(void) const {
                return m_basetree;
            }
            /**
             *
             * @param worldSize
             */
            inline void setWorldSize(const Vector3f& worldSize) {
                m_worldSize = worldSize;
                if(m_basetree)
                    m_basetree->setWorldSize(m_worldSize);
                m_groundGrid.dimensions.x = m_worldSize.x; // X
                m_groundGrid.dimensions.y = m_worldSize.z; // Z
            }
            /**
             *
             * @param x
             * @param y
             * @param z
             */
            void setWorldSize(float x, float y, float z) {
                m_worldSize = Vector3f(x, y, z);
                if(m_basetree)
                    m_basetree->setWorldSize(m_worldSize);
                m_groundGrid.dimensions.x = m_worldSize.x; // X
                m_groundGrid.dimensions.y = m_worldSize.z; // Z
            }
            /**
             *
             * @return
             */
            inline Vector3f& getWorldSize(void) {
                return m_worldSize;
            }
            /**
             * 
             * @return
             */
            inline Vector3f const& getWorldSize(void) const {
                return m_worldSize;
            }
            /**
             * 
             * @param groundLevel
             */
            inline void setGroundLevel(float groundLevel) {
                m_groundGrid.set(Planef::Y, groundLevel);
            }
            /**
             *
             * @param groundPlane
             */
            inline void setGroundPlane(const Planef& groundPlane) {
                m_groundGrid.n = groundPlane.n;
                m_groundGrid.axis = groundPlane.axis;
                m_groundGrid.d = groundPlane.d;
                m_groundGrid.determineAxis();
            }
            /**
             *
             * @param axis
             * @param level
             */
            inline void setGroundPlane(Planef::Axis axis, float level) {
                m_groundGrid.set(axis, level);
            }
            /**
             * 
             * @return
             */
            inline float getGroundLevel(void) const {
                return m_groundGrid.d;
            }
            /**
             *
             * @return
             */
            inline SPlaneGridf& getGroundGrid(void) {
                return m_groundGrid;
            }
            /**
             * 
             * @return
             */
            inline SPlaneGridf const& getGroundGrid(void) const {
                return m_groundGrid;
            }
            /**
             *
             * @param groundGridCellSize
             */
            inline void setGroundGridCellSize(float groundGridCellSize) {
                m_groundGrid.cellSize = groundGridCellSize;
            }
            /**
             * 
             * @return
             */
            inline float getGroundGridCellSize(void) const {
                return m_groundGrid.cellSize;
            }
            /**
             *
             * @param id
             * @return
             */
            Vector3f& getGroundIntersectionPoint(unsigned int id = 0) {
                if(id > 1)
                    id = 1;
                return m_pickSelection.groundIntersectionPoint[id];
            }
            /**
             *
             * @param id
             * @return
             */
            Vector3f const& getGroundIntersectionPoint(unsigned int id = 0) const {
                if(id > 1)
                    id = 1;
                return m_pickSelection.groundIntersectionPoint[id];
            }
            //------------------------------------------------------------------

        protected:

            /**
             * This special structure is for internal usage in SceneManager
             * It's protected
             * This should be used only in SceneManagers (2D/3D/Custom)
             * It provides information about colliding objects, the info is simple
             * Which scene nodes are colliding based on nodes radius.
             * No further information is required. If nodeA is colliding with nodeB,
             * then nodeB is colliding with nodeA.
             * 
             * This structure will be useful also for checking collisions between
             * frames and reporting collision event just a single time.
             */
            struct SCollisionsInfo {
                ///
                typedef CVector<ObjectsVec> ContactsVec;
                ///
                typedef ContactsVec::iterator ContactsVecItor;

                ///
                ContactsVec contacts;

                /**
                 * 
                 * @return 
                 */
                SCollisionsInfo();
                /**
                 * 
                 * @param maxObjects
                 */
                ~SCollisionsInfo();

                /**
                 * 
                 * @param maxObjects
                 */
                void reserve(const unsigned int maxObjects);
                /**
                 * 
                 * @param numObjects
                 */
                void resize(const unsigned int numObjects);
                /**
                 * 
                 * @param nodeA
                 * @param nodeB
                 */
                void insert(const CSceneNode* nodeA, const CSceneNode* nodeB);
                /**
                 * 
                 * @param pNode
                 */
                void removeAll(const CSceneNode* pNode = NULL);
                /**
                 * 
                 * @param nodeA
                 * @param nodeB
                 */
                void remove(const CSceneNode* nodeA, const CSceneNode* nodeB);
                /**
                 * 
                 */
                void clear(void);

                /**
                 * 
                 * @param nodeA
                 * @param nodeB
                 * @return 
                 */
                fgBool check(const CSceneNode* nodeA, const CSceneNode* nodeB) const;

                /**
                 * 
                 * @return 
                 */
                fgBool empty(void) const;

                /**
                 * 
                 * @param pNode
                 * @return 
                 */
                fgBool empty(CSceneNode* pNode) const;

                /**
                 * 
                 * @return 
                 */
                unsigned int count(CSceneNode* pNode) const;

                /**
                 * 
                 * @return 
                 */
                unsigned int count(void) const;
                /**
                 * 
                 * @return 
                 */
                unsigned int size(void) const;
                /**
                 * 
                 * @return 
                 */
                unsigned int capacity(void) const;

            } m_collisionsInfo;

            //------------------------------------------------------------------

        protected:

            /**
             *
             */
            struct STriggerInfo {
                ///
                CSceneNodeTrigger* pTrigger;
                ///
                CSceneNode* pNodeB;
                ///
                fgBool isBegin;
                /**
                 * 
                 */
                STriggerInfo() : pTrigger(NULL), pNodeB(NULL), isBegin(FG_TRUE) { }
                /**
                 * 
                 * @param trigger
                 * @param node
                 * @param begin
                 */
                STriggerInfo(CSceneNodeTrigger *trigger, CSceneNode *node, fgBool begin) :
                pTrigger(trigger), pNodeB(node), isBegin(begin) { }
                /**
                 * 
                 */
                ~STriggerInfo() {
                    pTrigger = NULL;
                    pNodeB = NULL;
                    isBegin = FG_FALSE;
                };
            }; // struct STriggerInfo

            ///
            typedef CVector<STriggerInfo> TriggerInfoVec;
            ///
            typedef TriggerInfoVec::iterator TriggerInfoVecItor;

            ///
            TriggerInfoVec m_triggers;

            //------------------------------------------------------------------

        public:

            /**
             * Helper structure which contains more information about the selected
             * node (via pick selection). The result of the selection (whether
             * is picked or not). Additional information on the screenBox for the
             * selected scene node.
             */
            struct SPickedNodeInfo {

                /**
                 *
                 */
                enum Result {
                    /// This node was not picked
                    NOT_PICKED,
                    /// This node was picked via bounding sphere or circle if
                    /// the box selection is active
                    PICKED_SPHERE,
                    /// This node was picked via AABB or 2D on screen box if the
                    /// box/rectangle selection is active
                    PICKED_AABB
                };
                ///
                Result result;
                ///
                float timeStamp;
                ///
                SceneNodeHandle handle;
                ///
                Vector3f intersectionPos;
                ///
                Vector3f intersectionNorm;
                ///
                Vector3f baryPosition;

                /**
                 *
                 */
                struct SOnScreen {
                    /// bounding box/rectangle of the selected node
                    AABB2Di box;
                    /// center of the bounding 2d circle
                    Vector2i center;
                    /// radius of the 2d circle
                    int radius;
                    /**
                     *
                     */
                    SOnScreen() : box(), center(), radius() {
                        box.invalidate();
                    }
                } onScreen;
                /**
                 *
                 */
                SPickedNodeInfo() : result(NOT_PICKED),
                timeStamp(-1.0f),
                handle(),
                intersectionPos(),
                intersectionNorm(),
                baryPosition(),
                onScreen() {
                    onScreen.box.invalidate();
                }
                /**
                 *
                 */
                void clear(void) {
                    timeStamp = -1.0f;
                    handle.reset();
                    onScreen.box.invalidate();
                    onScreen.radius = 0;
                    onScreen.center.x = 0;
                    onScreen.center.y = 0;
                    intersectionPos = Vec3f();
                    intersectionNorm = Vec3f();
                    baryPosition = Vec3f();
                    result = NOT_PICKED;
                }
            };

            typedef util::btree_map<SceneNodeHandle, SPickedNodeInfo> PickedNodesInfoMap;
            typedef PickedNodesInfoMap::iterator PickedNodesInfoMapItor;

        protected:

            /**
             *
             */
            struct SPickSelection {

                enum Result {
                    NOT_PICKED,
                    PICKED_SPHERE,
                    PICKED_AABB
                };
                ///
                unsigned char aabbTrisIdx[12][3];
                ///
                Vector3f aabbPoints[8];
                /// Current pick position, the pick state (up/down) is in state flags
                Vector2i pickPos;
                /// The start position of the pick selection (picker activated)
                Vector2i pickPosBegin;
                /// Also the size of the picker box
                AABB2Di pickBox;
                /// Current position of the ray origin
                Vector3f rayEye;
                /// Current direction of the ray
                Vector3f rayDir;
                ///
                Vector3f groundIntersectionPoint[2];
                ///
                float pickBegin;
                ///
                Result goodPickResult;
                ///
                fgBool shouldUnselect;
                ///
                fgBool shouldCheck;
                ///
                fgBool isToggle;
                ///
                fgBool isGroup;
                ///
                fgBool checkBox;
                ///
                SceneNodeHandle h_lastSelectedNode;
                ///
                CVector<SceneNodeHandle> h_selectedNodes;
                ///
                PickedNodesInfoMap pickedNodesInfo;

                /**
                 * 
                 */
                SPickSelection();
                /**
                 * 
                 */
                ~SPickSelection();

                /**
                 *
                 * @param mvp
                 * @param camera
                 */
                void init(const CMVPMatrix& mvp,
                          const CCamera& camera,
                          StateFlags stateFlags);

                /**
                 * 
                 * @param stateFlags
                 */
                void end(StateFlags stateFlags);

                /**
                 *
                 * @param mvp
                 * @param camera
                 * @param screenCoord
                 */
                void updateRay(const CMVPMatrix& mvp,
                               const CCamera& camera);

                /**
                 *
                 * @param pNode
                 * @param checkAABBTriangles
                 * @return
                 */
                Result isPicked(const CSceneNode* pNode,
                                SPickedNodeInfo& pickInfo,
                                const CMVPMatrix& mvp,
                                const fgBool checkAABBTriangles = FG_TRUE);

                /**
                 *
                 * @param pEventMgr
                 * @param pNode
                 * @param checkAABBTriangles
                 * @return
                 */
                Result fullCheck(CSceneManager* pSceneMgr,
                                 CSceneNode* pNode,
                                 const fgBool checkAABBTriangles = FG_TRUE);
            } m_pickSelection;

            /**
             *
             */
            struct STraverse {
                ///
                typedef CSceneNode node_type;
                ///
                typedef std::stack<int> IdStack;
                ///
                typedef std::stack<CSceneNode*> NodeStack;

                /// Stack containing child ids
                IdStack idStack;
                /// Stack for containing nodes
                NodeStack nodeStack;
                /// Current node pointer
                CSceneNode *current;
                /// Index of the child to read
                int idx;
                /// Number of objects traversed
                int count;
                /**
                 *
                 */
                STraverse() :
                idStack(),
                nodeStack(),
                current(NULL),
                idx(0),
                count(0) { }
                /**
                 *
                 */
                ~STraverse();
                /**
                 *
                 */
                void rewind(void);
                /**
                 *
                 * @param pRoot
                 */
                void skip(CSceneNode* pRoot);

                /**
                 *
                 * @return
                 */
                CSceneNode* next(CSceneNode* pRoot);
            } m_traverse;

        public:
            /**
             * 
             * @return
             */
            PickedNodesInfoMap& getPickedNodesInfo(void) {
                return m_pickSelection.pickedNodesInfo;
            }
            /**
             *
             * @return
             */
            PickedNodesInfoMap const& getPickedNodesInfo(void) const {
                return m_pickSelection.pickedNodesInfo;
            }

            //------------------------------------------------------------------
        private:
            /// Internal flags, changing the default behavior of the Scene Manager
            StateFlags m_stateFlags;
            ///
            SPlaneGridf m_groundGrid;
            ///
            Vector3f m_worldSize;
            /// Internal camera
            CCameraAnimation m_camera;
            /// Internal skybox
            CSceneSkyBox m_skybox;
            /// Root nodes of this scene manager. Single root node is a common
            /// father for other nodes which are added later - root node creates
            /// separate scene, level, map, etc. Root node will be created if
            /// there isn't any
            ObjectsVec m_rootNodes;
            /// Currently active root node - separate scene
            CSceneNode* m_activeRootNode;
            /// Vector containing scene nodes that are visible
            VisibleNodesVec m_visibleNodes;
            /// Drawable priority queue - special purpose for rendering in order
            DrawablePriorityQueue m_drawableQueue;
            /// Pointer to the external resource manager - don't know if this is necessary
            fg::base::CManager* m_pResourceMgr;
            /// This is special manager for scene based events
            event::CEventManager* m_sceneEventMgr;
            /// External pointer to the Scene Node Factory
            CNodeFactory* m_pNodeFactory;

        protected:
            ///
            CBasetree *m_basetree;
        }; // class CSceneManager

        FG_ENUM_FLAGS(CSceneManager::StateFlags);
        /**
         * 
         * @param flags
         * @param toggle
         */
        inline void CSceneManager::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_stateFlags |= flags;
            } else {
                m_stateFlags |= flags;
                m_stateFlags ^= flags;
            }
        }
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_MANAGER_BLOCK
#endif /* FG_INC_GFX_SCENE_MANAGER */
