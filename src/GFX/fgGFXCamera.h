/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_CAMERA
    #define FG_INC_GFX_CAMERA
    #define FG_INC_GFX_CAMERA_BLOCK

// FIXME! #mathlib too big?
    #include "Math/fgMathLib.h"
    #ifndef FG_INC_GFX_FRUSTUM
        #include "fgGFXFrustum.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         * Simple wrapper class for functions regarding the View matrix
         * Contains special vectors (eye, center, up) and uses lookAt
         */
        class CCamera {
        public:
            /**
             * Default constructor for camera object
             */
            CCamera() :
            m_frustum(), /// Current camera frustum
            m_viewMatrix(), /// The view matrix of this camera
            m_eye(), /// Position of the camera in world space
            m_center(), /// Where the camera is looking?
            m_up(0.0f, 1.0f, 0.0f) /// Head by default will be up (0,1,0)
            { }
            /**
             * Default destructor for camera object
             */
            virtual ~CCamera() { }
            /**
             * Returns reference to the internal view matrix
             * @return 
             */
            inline Matrix4f & getRefViewMatrix(void) {
                return m_viewMatrix;
            }
            /**
             * Updates the view matrix based on the internal vector values
             * @return 
             */
            virtual float * update(void) {
                m_viewMatrix = math::lookAt(m_eye, m_center, m_up);
                //m_frustum.set(m_eye, m_center, m_up); // #SRSLY?
                return getViewMatPtr();
            }
            /**
             * Returns the pointer to the view matrix
             * @return 
             */
            inline const float * getViewMatPtr(void) const {
                return math::value_ptr(m_viewMatrix);
            }
            /**
             * Returns the pointer to the view matrix
             * @return 
             */
            inline float * getViewMatPtr(void) {
                return math::value_ptr(m_viewMatrix);
            }
            /**
             * 
             * @param eye
             */
            inline void setEye(const Vector3f& eye) {
                m_eye = eye;
            }
            /**
             * 
             * @param center
             */
            inline void setCenter(const Vector3f& center) {
                m_center = center;
            }
            /**
             * 
             * @param up
             */
            inline void setUp(const Vector3f& up) {
                m_up = up;
            }
            /**
             * Returns the reference to the eye vector
             * @return 
             */
            inline Vector3f & getRefEye(void) {
                return m_eye;
            }
            /**
             * Returns the reference to the center vector
             * @return 
             */
            inline Vector3f & getRefCenter(void) {
                return m_center;
            }
            /**
             * Returns the reference to the up vector
             * @return 
             */
            inline Vector3f & getRefUp(void) {
                return m_up;
            }
            /**
             * Returns the reference to the eye vector
             * @return 
             */
            inline Vector3f const & getRefEye(void) const {
                return m_eye;
            }
            /**
             * Returns the reference to the center vector
             * @return 
             */
            inline Vector3f const & getRefCenter(void) const {
                return m_center;
            }
            /**
             * Returns the reference to the up vector
             * @return 
             */
            inline Vector3f const & getRefUp(void) const {
                return m_up;
            }
            /**
             * Returns the pointer to the eye vector data
             * @return 
             */
            inline const float * getPtrEye(void) const {
                return math::value_ptr(m_eye);
            }
            /**
             * Returns the pointer to the eye vector data
             * @return 
             */
            inline float * getPtrEye(void) {
                return math::value_ptr(m_eye);
            }
            /**
             * Returns the pointer to the center vector data
             * @return 
             */
            inline const float * getPtrCenter(void) const {
                return math::value_ptr(m_center);
            }
            /**
             * Returns the pointer to the center vector data
             * @return 
             */
            inline float * getPtrCenter(void) {
                return math::value_ptr(m_center);
            }
            /**
             * Returns the pointer to the up vector data
             * @return 
             */
            inline const float * getPtrUp(void) const {
                return math::value_ptr(m_up);
            }
            /**
             * Returns the pointer to the up vector data
             * @return 
             */
            inline float * getPtrUp(void) {
                return math::value_ptr(m_up);
            }
            /**
             * Resets the internal view matrix
             * The internal vectors (eye,...) are unchanged
             */
            virtual inline void identity(void) {
                m_viewMatrix = Matrix4f();
                //m_frustum.invalidate();
            }
            /**
             * 
             * @return 
             */
            inline CFrustum & getRefFrustum(void) {
                return m_frustum;
            }
            /**
             * 
             * @return 
             */
            inline CFrustum const & getRefFrustum(void) const {
                return m_frustum;
            }

        protected:
            /// Current camera frustum
            CFrustum m_frustum;
            /// The view matrix of this camera
            Matrix4f m_viewMatrix;
            /// Position of the camera in world space
            Vector3f m_eye;
            /// Where the camera is looking?
            Vector3f m_center;
            /// Head by default will be up (0,1,0)
            Vector3f m_up;
        };
    };
};

    #undef FG_INC_GFX_CAMERA_BLOCK
#endif /* FG_INC_GFX_CAMERA */
