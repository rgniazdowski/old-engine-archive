/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_MVP_MATRIX_H_
    #define _FG_GFX_MVP_MATRIX_H_

    #include "fgGFXMVMatrix.h"
    #include "fgGFXProjection.h"

/*
 *
 */
class fgGfxMVPMatrix : protected fgGfxMVMatrix, public fgGfxProjection {
public:
    // 
    fgGfxMVPMatrix() { }

    // 
    virtual ~fgGfxMVPMatrix() { }

    //
    virtual float *calculate(fgMatrix4f & modelMatrix) {
        fgGfxMVMatrix::calculate(modelMatrix);
        m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
        return getModelViewProjMatPtr();
    }

    //
    virtual float *calculate(fgGfxCamera *camera, fgMatrix4f & modelMatrix, fgBool updateMatrix = FG_TRUE) {
        fgGfxMVMatrix::calculate(camera, modelMatrix);
        // argument updateMatrix is ignored, MVP matrix will be always updated
        m_modelViewProjMatrix = m_projMatrix * m_viewMatrix * modelMatrix;
        m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
        return getModelViewProjMatPtr();
    }

    //
    inline fgMatrix4f & getRefModelViewProjMatrix(void) {
        return m_modelViewProjMatrix;
    }

    // 
    inline const float * getModelViewProjMatPtr(void) const {
        return glm::value_ptr(m_modelViewProjMatrix);
    }

    // 
    inline float * getModelViewProjMatPtr(void) {
        return glm::value_ptr(m_modelViewProjMatrix);
    }

    //
    inline void identity(void) {
        fgGfxMVMatrix::identity();
        fgGfxProjection::identity();
        m_modelViewProjMatrix = fgMatrix4f();
    }

protected:
    fgMatrix4f m_modelViewProjMatrix;
};

#endif /* _FG_GFX_MVP_MATRIX_H_ */
