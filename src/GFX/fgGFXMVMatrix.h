/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_MV_MATRIX
    #define FG_INC_GFX_MV_MATRIX

    #include "fgGFXCamera.h"
    #include "fgBool.h"

class fgGfxMVMatrix : public fgGfxCamera {
public:
    typedef fgGfxCamera base_type;

public:
    /**
     * 
     */
    fgGfxMVMatrix() : fgGfxCamera(), m_modelViewMatrix() { }
    /**
     * 
     */
    virtual ~fgGfxMVMatrix() { }
    /**
     * 
     * @param modelMatrix
     * @return 
     */
    virtual float *calculate(const fgMatrix4f & modelMatrix) {
        m_modelViewMatrix = m_viewMatrix * modelMatrix;
        return getModelViewMatPtr();
    }
    /**
     * 
     * @param camera
     * @param modelMatrix
     * @param updateMatrix
     * @return 
     */
    virtual float *calculate(fgGfxCamera *camera,
                             const fgMatrix4f & modelMatrix,
                             fgBool updateMatrix = FG_TRUE) {
        if(camera) {
            m_eye = camera->getRefEye();
            m_center = camera->getRefCenter();
            m_up = camera->getRefUp();
            fgGfxMVMatrix::update();
        }
        if(updateMatrix)
            m_modelViewMatrix = m_viewMatrix * modelMatrix;
        return getModelViewMatPtr();
    }
    /**
     * 
     * @return 
     */
    inline fgMatrix4f & getRefMVMatrix(void) {
        return m_modelViewMatrix;
    }
    /**
     * 
     * @return 
     */
    inline fgMatrix4f const & getRefMVMatrix(void) const {
        return m_modelViewMatrix;
    }
    /**
     * 
     * @return 
     */
    inline const float * getModelViewMatPtr(void) const {
        return fgMath::value_ptr(m_modelViewMatrix);
    }
    /**
     * 
     * @return 
     */
    inline float * getModelViewMatPtr(void) {
        return fgMath::value_ptr(m_modelViewMatrix);
    }
    /**
     * 
     */
    virtual inline void identity(void) {
        fgGfxCamera::identity();
        m_modelViewMatrix = fgMatrix4f();
    }

protected:
    /// 
    fgMatrix4f m_modelViewMatrix;
};

#endif /* FG_INC_GFX_MV_MATRIX */
