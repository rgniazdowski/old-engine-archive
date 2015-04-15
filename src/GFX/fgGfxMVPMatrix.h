/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_MVP_MATRIX
    #define FG_INC_GFX_MVP_MATRIX
    #define FG_INC_GFX_MVP_MATRIX_BLOCK

    #include "fgGfxMVMatrix.h"
    #include "fgGfxProjection.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CMVPMatrix : public CMVMatrix, public CProjection {
        public:
            ///
            typedef CMVMatrix base_type;
            ///
            typedef CProjection projection_type;

        public:
            /**
             * 
             */
            CMVPMatrix() :
            CMVMatrix(),
            CProjection(),
            m_modelViewProjMatrix() { }
            /**
             * 
             */
            virtual ~CMVPMatrix() { }
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
                CProjection::setPerspective(fovY, aspect, zNear, zFar);
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
                m_projMatrix = math::ortho(left, right, bottom, top, zNear, zFar);
                m_frustum.setCamera(0.0f, right / bottom, zNear, zFar);
                m_viewProjMatrix = m_projMatrix * m_viewMatrix;
                m_frustum.set(m_viewProjMatrix);
            }
            /**
             * 
             * @param modelMatrix
             * @return 
             */
            virtual float *calculate(const Matrix4f & modelMatrix) {
                CMVMatrix::calculate(modelMatrix);
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
            virtual float *calculate(CCamera *camera,
                                     const Matrix4f & modelMatrix,
                                     fgBool updateMatrix = FG_TRUE) {
                CMVMatrix::calculate(camera, modelMatrix);
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
                CMVMatrix::calculate(Matrix4f());
                m_modelViewProjMatrix = m_projMatrix * m_modelViewMatrix;
            }
            /**
             * 
             * @param camera
             */
            virtual void setCamera(CCamera *camera) {
                this->m_eye = camera->getEye();
                this->m_center = camera->getCenter();
                this->m_up = camera->getUp();
                this->m_viewMatrix = camera->getViewMatrix();
            }
            /*
             * Getters for MVP raw matrix
             */
            /**
             * 
             * @return 
             */
            inline Matrix4f & getRefModelViewProjMatrix(void) {
                return m_modelViewProjMatrix;
            }
            /**
             * 
             * @return 
             */
            inline Matrix4f const & getRefModelViewProjMatrix(void) const {
                return m_modelViewProjMatrix;
            }
            /**
             * 
             * @return 
             */
            inline const float * getModelViewProjMatPtr(void) const {
                return math::value_ptr(m_modelViewProjMatrix);
            }
            /**
             * 
             * @return 
             */
            inline float * getModelViewProjMatPtr(void) {
                return math::value_ptr(m_modelViewProjMatrix);
            }
            /*
             * Getters for VP raw matrix (view * projection)
             */
            /**
             * 
             * @return 
             */
            inline Matrix4f & getRefViewProjMatrix(void) {
                return m_viewProjMatrix;
            }
            /**
             * 
             * @return 
             */
            inline Matrix4f const & getRefViewProjMatrix(void) const {
                return m_viewProjMatrix;
            }
            /**
             * 
             * @return 
             */
            inline const float * getViewProjMatPtr(void) const {
                return math::value_ptr(m_viewProjMatrix);
            }
            /**
             * 
             * @return 
             */
            inline float * getViewProjMatPtr(void) {
                return math::value_ptr(m_viewProjMatrix);
            }
            /**
             * 
             */
            virtual inline void identity(void) {
                CMVMatrix::identity();
                CProjection::identity();
                m_modelViewProjMatrix = Matrix4f();
                m_viewProjMatrix = Matrix4f();
            }

        protected:
            /// 
            Matrix4f m_modelViewProjMatrix;
            ///
            Matrix4f m_viewProjMatrix;
        };
    };
};

    #undef FG_INC_GFX_MVP_MATRIX_BLOCK
#endif /* FG_INC_GFX_MVP_MATRIX */
