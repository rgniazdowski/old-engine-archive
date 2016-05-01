/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

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
            virtual void setPerspective(float fovY,
                                               float aspect,
                                               float zNear = FG_GFX_PERSPECTIVE_ZNEAR_DEFAULT,
                                               float zFar = FG_GFX_PERSPECTIVE_ZFAR_DEFAULT);
            /**
             * 
             * @param left
             * @param right
             * @param bottom
             * @param top
             * @param zNear
             * @param zFar
             */
            virtual void setOrtho(float left,
                                         float right,
                                         float bottom,
                                         float top,
                                         float zNear = FG_GFX_ORTHO_ZNEAR_DEFAULT,
                                         float zFar = FG_GFX_ORTHO_ZFAR_DEFAULT);
            
            /**
             * 
             * @param modelMatrix
             * @return 
             */
            virtual float *calculate(const Matrix4f& modelMatrix);
            /**
             * 
             * @param camera
             * @param modelMatrix
             * @param updateMatrix
             * @return 
             */
            virtual float *calculate(CCamera *camera,
                                     const Matrix4f & modelMatrix,
                                     fgBool updateMatrix = FG_TRUE);
            /**
             * 
             */
            virtual void resetModelMatrix(void);
            /**
             * 
             * @param camera
             */
            virtual void setCamera(CCamera *camera);
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
            inline const float* getModelViewProjMatPtr(void) const {
                //return math::value_ptr(m_modelViewProjMatrix);
                return (const float*)&(m_modelViewProjMatrix[0].x);
            }
            /**
             * 
             * @return 
             */
            inline float* getModelViewProjMatPtr(void) {
                //return math::value_ptr(m_modelViewProjMatrix);
                return &(m_modelViewProjMatrix[0].x);
            }
            /*
             * Getters for VP raw matrix (view * projection)
             */
            /**
             * 
             * @return 
             */
            inline Matrix4f& getRefViewProjMatrix(void) {
                return m_viewProjMatrix;
            }
            /**
             * 
             * @return 
             */
            inline Matrix4f const& getRefViewProjMatrix(void) const {
                return m_viewProjMatrix;
            }
            /**
             * 
             * @return 
             */
            inline const float* getViewProjMatPtr(void) const {
                //return math::value_ptr(m_viewProjMatrix);
                return &(m_viewProjMatrix[0].x);
            }
            /**
             * 
             * @return 
             */
            inline float* getViewProjMatPtr(void) {
                //return math::value_ptr(m_viewProjMatrix);
                return &(m_viewProjMatrix[0].x);
            }
            /**
             * 
             */
            virtual void identity(void);

        protected:
            /// 
            Matrix4f m_modelViewProjMatrix;
            ///
            Matrix4f m_viewProjMatrix;
        }; // class CMVPMatrix

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_MVP_MATRIX_BLOCK
#endif /* FG_INC_GFX_MVP_MATRIX */
