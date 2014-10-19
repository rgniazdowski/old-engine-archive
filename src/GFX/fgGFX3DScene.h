/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_3D_SCENE_H_
#define _FG_GFX_3D_SCENE_H_

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
class fgGfx3DScene : protected fgGfxDrawingBatch {
public:
    typedef fgVector<fgGfxObject *>     objectVec;
    typedef objectVec::iterator         objectVecItor;
        
private:
    /// Internal MVP matrix to use, this will set the perspective view
    fgGfxMVPMatrix m_MVP;
    /// Internal camera
    fgGfxCameraAnimation m_camera;
    ///
    objectVec m_objects;
    ///
    drawCallVec m_objDrawCalls;
    /// ?
    fgManagerBase *m_resourceMgr;
    
public:
    //
    fgGfx3DScene();
    //
    virtual ~fgGfx3DScene();

public:
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
    inline fgGfxObject *getObject(const int index) {
        if(index < 0 || index >= (int)m_objects.size())
            return NULL;
        return m_objects[index];
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
    
    //
    int appendObject(fgGfxObject *pObj, fgBool manage = FG_TRUE);
    //
    fgGfxObject *appendModel(int &index, fgGfxModelResource *pModelRes, fgBool manage = FG_TRUE);
};

#endif /* _FG_GFX_3D_SCENE_H_ */
