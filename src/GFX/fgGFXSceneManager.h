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

    #define FG_MANAGER_SCENE        0x00001000

/**
 *
 */
class fgGfxSceneManager :
public fg::base::CManager,
protected fgGfxDrawingBatch,
protected fgHandleManager<fgGfxSceneNode *, fgGfxSceneNodeHandle> {
public:
    ///
    typedef fg::base::CManager base_type;
    ///
    typedef fgGfxSceneNode node_type;
    ///
    typedef fgGfxSceneNodeHandle handle_type;
    ///
    typedef std::priority_queue<fgGfxSceneNode*, std::deque<fgGfxSceneNode*>, fgPtrLessEq<fgGfxSceneNode*> > nodePriorityQueue;
    ///
    typedef fgVector<fgGfxSceneNode *> objectVec;
    ///
    typedef objectVec::iterator objectVecItor;

protected:
    /**
     * 
     */
    virtual void clear(void);

public:
    /**
     * 
     */
    fgGfxSceneManager();
    /**
     * 
     */
    virtual ~fgGfxSceneManager();

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

    /**
     * 
     * @param pShaderMgr
     */
    virtual void setShaderManager(fg::base::CManager *pShaderMgr);

    /**
     * Set internal pointer to the main resource manager
     * @param pResourceMgr
     */
    void setResourceManager(fg::base::CManager *pResourceMgr);
    /**
     * Get internal pointer to the main resource manager
     * @return 
     */
    inline fg::base::CManager *getResourceManager(void) const {
        return m_pResourceMgr;
    }
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
     * @param nodeUniqueID
     * @param pNode
     * @param pFatherNode
     * @return 
     */
    virtual fgBool addNode(fgGfxSceneNodeHandle& nodeUniqueID,
                           fgGfxSceneNode *pNode,
                           fgGfxSceneNode *pFatherNode = NULL);
    /**
     * 
     * @param nodeUniqueID
     * @param pNode
     * @param nodeParentUniqueID
     * @return 
     */
    virtual fgBool addNode(fgGfxSceneNodeHandle& nodeUniqueID,
                           fgGfxSceneNode *pNode,
                           const fgGfxSceneNodeHandle& nodeParentUniqueID);
    /**
     * 
     * @param nodeUniqueID
     * @param pNode
     * @param nodeParentNameTag
     * @return 
     */
    virtual fgBool addNode(fgGfxSceneNodeHandle& nodeUniqueID,
                           fgGfxSceneNode *pNode,
                           const std::string& nodeParentNameTag);
    /**
     * 
     * @param nodeUniqueID
     * @param pNode
     * @param nodeParentNameTag
     * @return 
     */
    virtual fgBool addNode(fgGfxSceneNodeHandle& nodeUniqueID,
                           fgGfxSceneNode *pNode,
                           const char* nodeParentNameTag);

    /**
     * 
     * @param pNode
     * @return 
     */
    virtual fgBool remove(fgGfxSceneNode *pNode);
    /**
     * 
     * @param nodeUniqueID
     * @return 
     */
    virtual fgBool remove(const fgGfxSceneNodeHandle& nodeUniqueID);
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

    /**
     * 
     * @param pNode
     * @return 
     */
    virtual fgBool destroyNode(fgGfxSceneNode*& pNode);
    /**
     * 
     * @param nodeUniqueID
     * @return 
     */
    virtual fgBool destroyNode(const fgGfxSceneNodeHandle& nodeUniqueID);
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

    /**
     * 
     * @param nodeUniqueID
     * @return 
     */
    virtual fgGfxSceneNode* get(const fgGfxSceneNodeHandle& nodeUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgGfxSceneNode* get(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgGfxSceneNode* get(const char *nameTag);

    /**
     * 
     * @param pNode
     * @return 
     */
    virtual fgBool isManaged(const fgGfxSceneNode *pNode);
    /**
     * 
     * @param nodeUniqueID
     * @return 
     */
    virtual fgBool isManaged(const fgGfxSceneNodeHandle& nodeUniqueID);
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
    /**
     * 
     * @param index
     * @return 
     */
    inline fgGfxSceneNode *get(const int index) {
        if(index < 0 || index >= (int)fgHandleManager::getRefDataVector().size())
            return NULL;
        return fgHandleManager::getRefDataVector()[index];
    }

    // This is special array like operator
    // Note that there is no boundaries checking
    fgGfxSceneNode *operator [](size_t n) {
        return fgHandleManager::getRefDataVector()[n];
    }

    // This is special array like operator
    // Note that there is no boundaries checking
    const fgGfxSceneNode *operator [](size_t n) const {
        return fgHandleManager::getRefDataVector()[n];
    }

    // Returns the number of valid handles used within the handle 
    // manager. This value should not be used for any kind of iteration
    // through the internal data vector
    unsigned int count(void) const {
        return fgHandleManager::getUsedHandleCount();
    }

    // This will return the size of the internal data vector
    // Returned value takes into account also empty slots, so
    // this is the real size of the internal data array
    unsigned int size(void) const {
        return fgHandleManager::getRefDataVector().size();
    }
    /**
     * 
     */
    inline fgGfxCameraAnimation *getCamera(void) {
        return &m_camera;
    }
    /**
     * 
     * @param pCamera
     */
    inline void applyCamera(const fgGfxCamera* pCamera) {
        m_camera.setEye(pCamera->getRefEye());
        m_camera.setCenter(pCamera->getRefCenter());
        m_camera.setUp(pCamera->getRefUp());
    }
    /**
     * 
     * @return 
     */
    inline fgGfxMVPMatrix *getMVP(void) {
        return &m_MVP;
    }

private:
    /// Internal MVP matrix to use, this will set the perspective view
    fgGfxMVPMatrix m_MVP;
    /// Internal camera
    fgGfxCameraAnimation m_camera;
    ///
    nodePriorityQueue m_nodeQueue;
    /// Pointer to the external resource manager - dont know if this is necessary
    fg::base::CManager *m_pResourceMgr;
};

    #undef FG_INC_GFX_SCENE_MANAGER_BLOCK
#endif /* FG_INC_GFX_SCENE_MANAGER */
