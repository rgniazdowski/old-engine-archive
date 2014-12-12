/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_MVP_MATRIX
    #define FG_INC_GFX_MVP_MATRIX

    #include "fgGFXMVMatrix.h"
    #include "fgGFXProjection.h"

/**
 *
 */
class fgGfxMVPMatrix : public fgGfxMVMatrix, public fgGfxProjection {
public:
    typedef fgGfxMVMatrix base_type;
    typedef fgGfxProjection projection_type;

public:
    /**
     * 
     */
    fgGfxMVPMatrix() : fgGfxMVMatrix(),
    fgGfxProjection(),
    m_modelViewProjMatrix() { }
    /**
     * 
     */
    virtual ~fgGfxMVPMatrix() { }
    /**
     * 
     * @param fovY
     * @param aspect
     * @param zNear
     * @param zFar
     */
    virtual inline void setPerspective(float fovY,
                                       float aspect,
                                       float zNear = FG_GFX_PERSPECTIVE_ZNEAR_DEFAULT,
                                       float zFar = FG_GFX_PERSPECTIVE_ZFAR_DEFAULT) {
        fgGfxProjection::setPerspective(fovY, aspect, zNear, zFar);
        m_frustum.setCamera(fovY, aspect, zNear, zFar);
        m_viewProjMatrix = m_projMatrix * m_viewMatrix;
        m_frustum.set(m_viewProjMatrix);
    }
    /**
     * 
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param zNear
     * @param zFar
     */
    virtual inline void setOrtho(float left,
                                 float right,
                                 float bottom,
                                 float top,
                                 float zNear = FG_GFX_ORTHO_ZNEAR_DEFAULT,
                                 float zFar = FG_GFX_ORTHO_ZFAR_DEFAULT) {
        m_projMatrix = fgMath::ortho(left, right, bottom, top, zNear, zFar);
        m_frustum.setCamera(0.0f, right / bottom, zNear, zFar);
        m_viewProjMatrix = m_projMatrix * m_viewMatrix;
        m_frustum.set(m_viewProjMatrix);
    }
    /**
     * 
     * @param modelMatrix
     * @return 
     */
    virtual float *calculate(const fgMatrix4f & modelMatrix) {
        fgGfxMVMatrix::calculate(modelMatrix);
        m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
        //m_frustum.set(m_modelViewProjMatrix);
        return getModelViewProjMatPtr();
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
        fgGfxMVMatrix::calculate(camera, modelMatrix);
        // argument updateMatrix is ignored, MVP matrix will be always updated
        // m_modelViewProjMatrix = m_projMatrix * m_viewMatrix * modelMatrix;
        m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
        //m_viewProjMatrix = m_projMatrix * m_viewMatrix;
        //m_frustum.set(m_viewProjMatrix);
        return getModelViewProjMatPtr();
    }
    /**
     * 
     */
    virtual void resetModelMatrix(void) {
        fgGfxMVMatrix::calculate(fgMatrix4f());
        m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
    }
    /**
     * 
     * @param camera
     */
    virtual void setCamera(fgGfxCamera *camera) {
        this->m_eye = camera->getRefEye();
        this->m_center = camera->getRefCenter();
        this->m_up = camera->getRefUp();
        this->m_viewMatrix = camera->getRefViewMatrix();
    }
    /*
     * Getters for MVP raw matrix
     */
    /**
     * 
     * @return 
     */
    inline fgMatrix4f & getRefModelViewProjMatrix(void) {
        return m_modelViewProjMatrix;
    }
    /**
     * 
     * @return 
     */
    inline fgMatrix4f const & getRefModelViewProjMatrix(void) const {
        return m_modelViewProjMatrix;
    }
    /**
     * 
     * @return 
     */
    inline const float * getModelViewProjMatPtr(void) const {
        return fgMath::value_ptr(m_modelViewProjMatrix);
    }
    /**
     * 
     * @return 
     */
    inline float * getModelViewProjMatPtr(void) {
        return fgMath::value_ptr(m_modelViewProjMatrix);
    }
    /*
     * Getters for VP raw matrix (view * projection)
     */
    /**
     * 
     * @return 
     */
    inline fgMatrix4f & getRefViewProjMatrix(void) {
        return m_viewProjMatrix;
    }
    /**
     * 
     * @return 
     */
    inline fgMatrix4f const & getRefViewProjMatrix(void) const {
        return m_viewProjMatrix;
    }
    /**
     * 
     * @return 
     */
    inline const float * getViewProjMatPtr(void) const {
        return fgMath::value_ptr(m_viewProjMatrix);
    }
    /**
     * 
     * @return 
     */
    inline float * getViewProjMatPtr(void) {
        return fgMath::value_ptr(m_viewProjMatrix);
    }
    /**
     * 
     */
    virtual inline void identity(void) {
        fgGfxMVMatrix::identity();
        fgGfxProjection::identity();
        m_modelViewProjMatrix = fgMatrix4f();
        m_viewProjMatrix = fgMatrix4f();
    }

protected:
    /// 
    fgMatrix4f m_modelViewProjMatrix;
    ///
    fgMatrix4f m_viewProjMatrix;
};

#endif /* FG_INC_GFX_MVP_MATRIX */
