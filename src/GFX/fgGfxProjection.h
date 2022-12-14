/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_PROJECTION
    #define FG_INC_GFX_PROJECTION
    #define FG_INC_GFX_PROJECTION_BLOCK

    #include "Math/fgMatrix4.h"


    #define FG_GFX_PERSPECTIVE_ZNEAR_DEFAULT 0.01f
    #define FG_GFX_PERSPECTIVE_ZFAR_DEFAULT 4096.0f

    #define FG_GFX_PERSPECTIVE_FOVY_DEFAULT 45.0f
    #define FG_GFX_PERSPECTIVE_FOV_DEFAULT 45.0f

    #define FG_GFX_PERSPECTIVE_ASPECT_DEFAULT (1024.0f/768.0f)

    #define FG_GFX_ORTHO_ZNEAR_DEFAULT -512.0f
    #define FG_GFX_ORTHO_ZFAR_DEFAULT 2048.0f

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CProjection {
        public:
            ///
            typedef Matrix4f matrix_type;

        protected:
            ///
            Matrix4f m_projMatrix;

        public:
            /**
             * 
             */
            CProjection() : m_projMatrix() { }
            /**
             * 
             */
            virtual ~CProjection() { }
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
             * @return 
             */
            inline Matrix4f& getRefProjMatrix(void) {
                return m_projMatrix;
            }
            /**
             * 
             * @return 
             */
            inline Matrix4f const& getRefProjMatrix(void) const {
                return m_projMatrix;
            }
            /**
             * 
             * @return 
             */
            inline const float * getProjMatPtr(void) const {
                //return math::value_ptr(m_projMatrix);
                return (const float*)&(m_projMatrix[0].x);
            }
            /**
             * 
             * @return 
             */
            inline float * getProjMatPtr(void) {
                //return math::value_ptr(m_projMatrix);
                return (float *)&(m_projMatrix[0].x);
            }
            /**
             * 
             */
            virtual inline void identity(void) {
                m_projMatrix = Matrix4f();
            }
        }; // class CProjection

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_PROJECTION_BLOCK
#endif /* FG_INC_GFX_PROJECTION */
