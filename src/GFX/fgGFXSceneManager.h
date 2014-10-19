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

    #include "fgGFXObject.h"

/* 
 *
 */
class fgGfxSceneManager : protected fgGfxDrawingBatch, protected fgHandleManager<fgGfxObject *, fgGfxObjectHandle> {
public:
    typedef fgVector<fgGfxObject *> objectVec;
    typedef objectVec::iterator objectVecItor;

public:
    //
    fgGfxSceneManager();
    //
    virtual ~fgGfxSceneManager();

    //
    virtual void setShaderManager(fgManagerBase *pShaderMgr);
    
    // Set internal pointer to the main resource manager
    void setResourceManager(fgManagerBase *pResourceMgr);
    // Get internal pointer to the main resource manager
    fgManagerBase *getResourceManager(void) const;
    
    //
    virtual int getZIndex(void) const {
        return m_zIndex;
    }

    //
    virtual void setZIndex(const int zIndex) {
        m_zIndex = zIndex;
    }

    //
    virtual void upZIndex(void) {
        m_zIndex++;
    }

    //
    virtual void downZIndex(void) {
        m_zIndex--;
    }

    //
    virtual void flush(void);

    //
    virtual void sortCalls(void);

    //
    virtual void render(void);
        
    // 
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, fgGfxObject *oFatherObj = NULL);
    //
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, const fgGfxObjectHandle& oFatherUniqueID);
    //
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, const std::string& oFatherNameTag);
    //
    virtual fgBool addObject(fgGfxObjectHandle& oUniqueID, fgGfxObject *pObj, const char* oFatherNameTag);

    // 
    virtual fgBool remove(fgGfxObject *pObj);
    // 
    virtual fgBool remove(const fgGfxObjectHandle& oUniqueID);
    // 
    virtual fgBool remove(const std::string& nameTag);
    //
    virtual fgBool remove(const char *nameTag);

    // 
    virtual fgBool destroyObject(fgGfxObject*& pObj);
    // 
    virtual fgBool destroyObject(const fgGfxObjectHandle& oUniqueID);
    // 
    virtual fgBool destroyObject(const std::string& nameTag);
    // 
    virtual fgBool destroyObject(const char *nameTag);

    // 
    virtual fgGfxObject* get(const fgGfxObjectHandle& oUniqueID);
    // 
    virtual fgGfxObject* get(const std::string& nameTag);
    // 
    virtual fgGfxObject* get(const char *nameTag);

    // 
    virtual fgBool isManaged(const fgGfxObject *pObj);
    // 
    virtual fgBool isManaged(const fgGfxObjectHandle& oUniqueID);
    // 
    virtual fgBool isManaged(const std::string& nameTag);
    // 
    virtual fgBool isManaged(const char *nameTag);
    
    //
    inline fgGfxObject *get(const int index) {
        if(index < 0 || index >= (int)fgHandleManager::getRefDataVector().size())
            return NULL;
        return fgHandleManager::getRefDataVector()[index];
    }
    
    // 
    fgGfxDrawCall *getDrawCall(const fgGfxObject* pObj);
    // 
    fgGfxDrawCall *getDrawCall(const fgGfxObjectHandle& oUniqueID);
    // 
    fgGfxDrawCall *getDrawCall(const std::string& nameTag);
    // 
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
    
    //
    inline fgGfxCameraAnimation *getCamera(void) {
        return &m_camera;
    }
    
    //
    inline void applyCamera(const fgGfxCamera* pCamera) {
        m_camera.setEye(pCamera->getRefEye());
        m_camera.setCenter(pCamera->getRefCenter());
        m_camera.setUp(pCamera->getRefUp());
    }

    //
    inline fgGfxMVPMatrix *getMVP(void) {
        return &m_MVP;
    }

private:
    /// Internal MVP matrix to use, this will set the perspective view
    fgGfxMVPMatrix m_MVP;
    /// Internal camera
    fgGfxCameraAnimation m_camera;
    /// This needs fixing - probably this won't be needed - need
    /// to overload more methods from drawing batch.... P3
    /// #FIXME - redundancy 
    drawCallVec m_objDrawCalls;
    /// ?
    fgManagerBase *m_resourceMgr;
};


#endif /* _FG_GFX_SCENE_MANAGER_H_ */
