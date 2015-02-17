/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SCENE_MANAGER
    #define FG_INC_GFX_SCENE_MANAGER
    #define FG_INC_GFX_SCENE_MANAGER_BLOCK

    #include "Util/fgHandleManager.h"

    #ifndef FG_INC_GFX_DRAWING_BATCH
        #include "GFX/fgGFXDrawingBatch.h"
    #endif 

    #ifndef FG_INC_GFX_CAMERA_ANIMATION
        #include "GFX/fgGFXCameraAnimation.h"
    #endif

    #include "fgGFXSceneNodeObject.h"

    #include "fgManagerBase.h"
    #include "fgGFXSceneSkyBox.h"    
    #include "fgGFXBasetree.h"

    #define FG_MANAGER_SCENE        0x00001000

namespace fg {
    
    namespace gfx {

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

        protected:
            /**
             * This should be called something like resetInternals?
             */
            virtual void clear(void);
            

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
                m_camera.setEye(pCamera->getRefEye());
                m_camera.setCenter(pCamera->getRefCenter());
                m_camera.setUp(pCamera->getRefUp());
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
                m_skyboxProgram = pProgram;
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

        private:            
            /// Internal MVP matrix to use, this will set the perspective view
            CMVPMatrix m_MVP;
            /// Internal camera
            CCameraAnimation m_camera;
            /// Internal skybox
            CSceneSkyBox m_skybox;
            ///
            CShaderProgram* m_skyboxProgram;
            /// Queue containing scene node (sorted) ready to render
            NodePriorityQueue m_nodeQueue;
            /// Pointer to the external resource manager - don't know if this is necessary
            fg::base::CManager *m_pResourceMgr;
            
        protected:
            ///
            CBasetree *m_basetree;
        };
    };
};

    #undef FG_INC_GFX_SCENE_MANAGER_BLOCK
#endif /* FG_INC_GFX_SCENE_MANAGER */
