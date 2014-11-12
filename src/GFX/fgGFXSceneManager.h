/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SCENE_MANAGER_H_
    #define _FG_GFX_SCENE_MANAGER_H_

    #include "Util/fgHandleManager.h"

    #ifndef _FG_GFX_DRAWING_BATCH_H_
        #include "GFX/fgGFXDrawingBatch.h"
    #endif 

    #ifndef _FG_GFX_CAMERA_ANIMATION_H_
        #include "GFX/fgGFXCameraAnimation.h"
    #endif

    #include "fgGFXDrawableObject.h"

    #include "fgManagerBase.h"

    #define FG_MANAGER_SCENE        0x00001000

/* 
 *
 */
class fgGfxSceneManager : public fgManagerBase,
        protected fgGfxDrawingBatch,
        protected fgHandleManager<fgGfxObject *, fgGfxObjectHandle> {
public:
    typedef std::priority_queue<fgGfxDrawableObject*, std::deque<fgGfxDrawableObject*>, fgPtrLessEq<fgGfxDrawableObject*> > drawablePriorityQueue;
    typedef fgVector<fgGfxObject *> objectVec;
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
    virtual void setShaderManager(fgManagerBase *pShaderMgr);

    // Set internal pointer to the main resource manager
    void setResourceManager(fgManagerBase *pResourceMgr);

    // Get internal pointer to the main resource manager
    fgManagerBase *getResourceManager(void) const {
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
     * @param oUniqueID
     * @param pObj
     * @param oFatherObj
     * @return 
     */
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, fgGfxObject *oFatherObj = NULL);
    /**
     * 
     * @param oUniqueID
     * @param pObj
     * @param oFatherUniqueID
     * @return 
     */
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, const fgGfxObjectHandle& oFatherUniqueID);
    /**
     * 
     * @param oUniqueID
     * @param pObj
     * @param oFatherNameTag
     * @return 
     */
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, const std::string& oFatherNameTag);
    /**
     * 
     * @param oUniqueID
     * @param pObj
     * @param oFatherNameTag
     * @return 
     */
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, const char* oFatherNameTag);

    /**
     * 
     * @param pObj
     * @return 
     */
    virtual fgBool remove(fgGfxObject *pObj);
    /**
     * 
     * @param oUniqueID
     * @return 
     */
    virtual fgBool remove(const fgGfxObjectHandle& oUniqueID);
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
     * @param pObj
     * @return 
     */
    virtual fgBool destroyObject(fgGfxObject*& pObj);
    /**
     * 
     * @param oUniqueID
     * @return 
     */
    virtual fgBool destroyObject(const fgGfxObjectHandle& oUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool destroyObject(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool destroyObject(const char *nameTag);

    /**
     * 
     * @param oUniqueID
     * @return 
     */
    virtual fgGfxObject* get(const fgGfxObjectHandle& oUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgGfxObject* get(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgGfxObject* get(const char *nameTag);

    /**
     * 
     * @param pObj
     * @return 
     */
    virtual fgBool isManaged(const fgGfxObject *pObj);
    /**
     * 
     * @param oUniqueID
     * @return 
     */
    virtual fgBool isManaged(const fgGfxObjectHandle& oUniqueID);
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
    inline fgGfxObject *get(const int index) {
        if(index < 0 || index >= (int)fgHandleManager::getRefDataVector().size())
            return NULL;
        return fgHandleManager::getRefDataVector()[index];
    }

    /**
     * 
     */
    fgGfxDrawCall *getDrawCall(const fgGfxObject* pObj);
    /**
     * 
     * @param oUniqueID
     * @return 
     */
    fgGfxDrawCall *getDrawCall(const fgGfxObjectHandle& oUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    fgGfxDrawCall *getDrawCall(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    fgGfxDrawCall *getDrawCall(const char *nameTag);

    // This is special array like operator
    // Note that there is no boundaries checking
    fgGfxObject *operator [](size_t n) {
        return fgHandleManager::getRefDataVector()[n];
    }

    // This is special array like operator
    // Note that there is no boundaries checking
    const fgGfxObject *operator [](size_t n) const {
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
    drawablePriorityQueue m_drawableQueue;
    /// This needs fixing - probably this won't be needed - need
    /// to overload more methods from drawing batch.... P3
    /// #FIXME - redundancy 
    drawCallVec m_objDrawCalls;
    /// Pointer to the external resource manager - dont know if this is necessary
    fgManagerBase *m_pResourceMgr;
};

#endif /* _FG_GFX_SCENE_MANAGER_H_ */
