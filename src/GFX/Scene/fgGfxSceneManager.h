/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SCENE_MANAGER
    #define FG_INC_GFX_SCENE_MANAGER
    #define FG_INC_GFX_SCENE_MANAGER_BLOCK

    #ifndef FG_INC_HANDLE_MANAGER
        #include "Util/fgHandleManager.h"
    #endif

    #ifndef FG_INC_EVENT_MANAGER
        #include "Event/fgEventManager.h"
    #endif

    #ifndef FG_INC_GFX_DRAWING_BATCH
        #include "GFX/fgGfxDrawingBatch.h"
    #endif 

    #ifndef FG_INC_GFX_CAMERA_ANIMATION
        #include "GFX/fgGfxCameraAnimation.h"
    #endif


    #include "fgGfxBasetree.h"

    #include "fgGfxSceneCallback.h"
    #include "fgGfxSceneNode.h"
    #include "fgGfxSceneNodeTrigger.h"
    #include "fgGfxSceneNodeMesh.h"
    #include "fgGfxSceneNodeObject.h"
    #include "fgGfxSceneSkyBox.h"    

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
        protected CDrawingBatch,
        protected fg::util::CHandleManager<CSceneNode *, SceneNodeHandle> {
        public:
            ///
            typedef CSceneManager self_type;
            ///
            typedef fg::base::CManager base_type;
            ///
            typedef fg::util::CHandleManager<CSceneNode *, SceneNodeHandle> handle_mgr_type;
            ///
            typedef CSceneNode node_type;
            ///
            typedef SceneNodeHandle handle_type;
            ///
            typedef std::priority_queue<CSceneNode*, std::deque<CSceneNode*>, fgPtrLessEq<CSceneNode*> > NodePriorityQueue;
            ///
            typedef CVector<CSceneNode *> ObjectVec;
            ///
            typedef ObjectVec::iterator ObjectVecItor;

        public:

            /**
             * Maximum is: 0x10 00 00 00
             */
            enum StateFlags {
                /// No special scene state flags specified
                NONE = 0x0000,
                /// Linear traverse forced - no spatial trees are used (octree/quadtree)
                LINEAR_TRAVERSE = 0x0001,
                /// Ignore collisions between nodes (coarse and fine), no events thrown
                IGNORE_COLLISIONS = 0x0002,
                /// Hide all nodes
                HIDE_NODES = 0x0004,
                /// Hide just the skybox
                HIDE_SKYBOX = 0x0008,
                /// No additional shadows for scene objects
                HIDE_SHADOWS = 0x0010, // 16 
                /// Hide everything - nodes, skybox, additional drawcalls
                HIDE_ALL = 0x001C, // 4 + 8 + 16 = 28
                /// Frustum check will be performed (AABB)
                FRUSTUM_CHECK = 0x0020, // 32
                /// Frustum check will be performed (AABB)
                FRUSTUM_CHECK_BOX = 0x0020, // 32
                /// Frustum check will be performed based on bounding spheres
                FRUSTUM_CHECK_SPHERE = 0x0040, // 64
                /// Occlusion check will be performed
                OCCLUSION_CHECK = 0x0080, // 128
                /// single pick selection active (on click actions)
                PICK_SELECTION_ON_CLICK = 0x0100, // 256
                /// Continuous pick selection active (mouse movement / hover)
                PICK_SELECTION_ON_HOVER = 0x0200, // 512
                /// Should pick selection be more accurate
                PICK_SELECTION_AABB_TRIANGLES = 0x0400, // 1024
                /// The state of pick selection (mouse/picker state)
                /// When active the picker is currently selecting, used only
                /// when pick selection is in click mode
                /// Pick selection does not care what mouse button (or anything)
                /// is used, picker state is reported from outside
                PICK_SELECTION_PICKER_ACTIVE = 0x0800 // 2048
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

            /**
             * 
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
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
            //------------------------------------------------------------------
            /**
             *
             * @param position
             */
            inline void reportSelectionMove(const Vector2i& position) {
                m_pickSelection.pickPosition = position;
            }
            /**
             *
             * @param x
             * @param y
             */
            inline void reportSelectionMove(int x, int y) {
                m_pickSelection.pickPosition.x = x;
                m_pickSelection.pickPosition.y = y;
            }
            /**
             *
             * @param state
             */
            inline void reportSelectionClick(const fgBool state = FG_TRUE) {
                setFlag(PICK_SELECTION_PICKER_ACTIVE, state);
            }
            /**
             *
             */
            inline void reportSelectionUnclick(void) {
                setFlag(PICK_SELECTION_PICKER_ACTIVE, FG_FALSE);
            }
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
                return m_pickSelection.h_currentlySelectedNode;
            }
            /**
             *
             */
            CSceneNode *getCurrentPickedNode(void) {
                return get(m_pickSelection.h_currentlySelectedNode);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isPickSelectionPickerActive(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_PICKER_ACTIVE);
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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

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
            virtual fgBool addNode(SceneNodeHandle& nodeUniqueID,
                                   CSceneNode *pNode,
                                   const SceneNodeHandle& nodeParentUniqueID);
            /**
             * 
             * @param nodeUniqueID
             * @param pNode
             * @param nodeParentNameTag
             * @return 
             */
            virtual fgBool addNode(SceneNodeHandle& nodeUniqueID,
                                   CSceneNode *pNode,
                                   const std::string& nodeParentNameTag);
            /**
             * 
             * @param nodeUniqueID
             * @param pNode
             * @param nodeParentNameTag
             * @return 
             */
            virtual fgBool addNode(SceneNodeHandle& nodeUniqueID,
                                   CSceneNode *pNode,
                                   const char* nodeParentNameTag);

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

            /**
             * This function clears the scene, removes all nodes, tree nodes,
             * releases all handles, resets the scene basically
             */
            virtual void clearScene(void);

            ////////////////////////////////////////////////////////////////////
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

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////
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
                return &m_MVP;
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

            ////////////////////////////////////////////////////////////////////
            /**
             * 
             * @return 
             */
            inline NodePriorityQueue& getNodeQueue(void) {
                return m_nodeQueue;
            }
            /**
             * 
             * @return 
             */
            inline NodePriorityQueue const& getNodeQueue(void) const {
                return m_nodeQueue;
            }
            /**
             * 
             * @return 
             */
            inline CBasetree *getBasetree(void) const {
                return m_basetree;
            }

            ////////////////////////////////////////////////////////////////////

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
                typedef CVector<ObjectVec> ContactsVec;
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

            ////////////////////////////////////////////////////////////////////

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
            };

            ///
            typedef CVector<STriggerInfo> TriggerInfoVec;
            ///
            typedef TriggerInfoVec::iterator TriggerInfoVecItor;

            TriggerInfoVec m_triggers;

            ////////////////////////////////////////////////////////////////////

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
                Vector2i pickPosition;
                /// Current position of the ray origin
                Vector3f rayEye;
                /// Current direction of the ray
                Vector3f rayDir;
                ///
                Result goodPickResult;
                ///
                fgBool shouldUnselect;
                ///
                fgBool shouldCheck;
                ///
                SceneNodeHandle h_lastSelectedNode;
                ///
                SceneNodeHandle h_currentlySelectedNode;

                /**
                 * 
                 */
                SPickSelection();
                /**
                 * 
                 */
                ~SPickSelection() { }

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

            ////////////////////////////////////////////////////////////////////
        private:
            /// Internal flags, changing the default behavior of the Scene Manager
            StateFlags m_stateFlags;
            /// Internal MVP matrix to use, this will set the perspective view
            CMVPMatrix m_MVP;
            /// Internal camera
            CCameraAnimation m_camera;
            /// Internal skybox
            CSceneSkyBox m_skybox;
            /// Queue containing scene node (sorted) ready to render
            NodePriorityQueue m_nodeQueue;
            /// Pointer to the external resource manager - don't know if this is necessary
            fg::base::CManager* m_pResourceMgr;
            /// This is special manager for scene based events
            event::CEventManager* m_sceneEventMgr;

        protected:
            ///
            CBasetree *m_basetree;
        };

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
    };
};

    #undef FG_INC_GFX_SCENE_MANAGER_BLOCK
#endif /* FG_INC_GFX_SCENE_MANAGER */
