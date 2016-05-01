/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxMVPMatrix.h"
#include "Math/fgMatrixOperations.h"

using namespace fg;
//------------------------------------------------------------------------------

void gfx::CMVPMatrix::setPerspective(float fovY,
                                     float aspect,
                                     float zNear,
                                     float zFar) {
    CProjection::setPerspective(fovY, aspect, zNear, zFar);
    m_frustum.setCamera(fovY, aspect, zNear, zFar);
    m_viewProjMatrix = m_projMatrix * m_viewMatrix;
    m_frustum.set(m_viewProjMatrix);
}
//------------------------------------------------------------------------------

void gfx::CMVPMatrix::setOrtho(float left,
                               float right,
                               float bottom,
                               float top,
                               float zNear,
                               float zFar) {
    m_projMatrix = math::ortho(left, right, bottom, top, zNear, zFar);
    m_frustum.setCamera(0.0f, right / bottom, zNear, zFar);
    m_viewProjMatrix = m_projMatrix * m_viewMatrix;
    m_frustum.set(m_viewProjMatrix);
}
//------------------------------------------------------------------------------

float* gfx::CMVPMatrix::calculate(const Matrix4f& modelMatrix) {
    CMVMatrix::calculate(modelMatrix);
    m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
    //m_frustum.set(m_modelViewProjMatrix);
    return getModelViewProjMatPtr();
}
//------------------------------------------------------------------------------

float* gfx::CMVPMatrix::calculate(CCamera* camera,
                                  const Matrix4f& modelMatrix,
                                  fgBool updateMatrix) {
    CMVMatrix::calculate(camera, modelMatrix);
    // argument updateMatrix is ignored, MVP matrix will be always updated
    // m_modelViewProjMatrix = m_projMatrix * m_viewMatrix * modelMatrix;
    m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
    //m_viewProjMatrix = m_projMatrix * m_viewMatrix;
    //m_frustum.set(m_viewProjMatrix);
    return getModelViewProjMatPtr();
}
//------------------------------------------------------------------------------

void gfx::CMVPMatrix::resetModelMatrix(void) {
    CMVMatrix::calculate(Matrix4f());
    m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
}
//------------------------------------------------------------------------------

void gfx::CMVPMatrix::setCamera(CCamera *camera) {
    this->m_eye = camera->getEye();
    this->m_center = camera->getCenter();
    this->m_up = camera->getUp();
    this->m_viewMatrix = camera->getViewMatrix();
    this->m_viewProjMatrix = m_projMatrix * m_viewMatrix;
    this->m_frustum.set(m_viewProjMatrix);
}
//------------------------------------------------------------------------------

void gfx::CMVPMatrix::identity(void) {
    CMVMatrix::identity();
    CProjection::identity();
    m_modelViewProjMatrix = Matrix4f();
    m_viewProjMatrix = Matrix4f();
}
//------------------------------------------------------------------------------
