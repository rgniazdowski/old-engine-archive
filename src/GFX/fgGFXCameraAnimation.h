/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_CAMERA_ANIMATION
    #define FG_INC_GFX_CAMERA_ANIMATION
    #define FG_INC_GFX_CAMERA_ANIMATION_BLOCK

    #include "fgGFXCamera.h"
    #include "fgGFXTypes.h"

namespace fg {
    namespace gfx {

        /*
         *
         */
        class CCameraAnimation : public CCamera {
        public:
            ///
            typedef CCamera base_type;
            ///
            typedef CCameraAnimation self_type;
            ///
            typedef CCameraAnimation type;
            
        public:
            /**
             *
             */
            enum Type {
                /// Fly mode (like in no-clip cheat)
                FREE,
                /// Locked/centered to some point, eye can change (rotate above the center point)
                CENTER_LOCKED,
                /// Locked to look at some object, follows it at the distance if it moves
                /// position of the eye changes automatically
                FOLLOW,
                /// Camera walks the specified path (checkpoints)
                PATH,
                /// Standard FPS camera, eye/center locked on XZ plane, Y set separately
                FPS_STANDARD
            };

        public:
            /**
             * 
             * @param type
             */
            CCameraAnimation(const Type cameraType = FREE);
            /**
             * 
             */
            virtual ~CCameraAnimation();

            /**
             * 
             * @return 
             */
            virtual float *update(void);
            /**
             * 
             * @param mouseXrel
             * @param mouseYrel
             * @return 
             */
            virtual float *update(fgGFXfloat mouseXrel, fgGFXfloat mouseYrel);
            /**
             * 
             */
            void moveLeft(void);
            /**
             * 
             */
            void moveRight(void);
            /**
             * 
             */
            void moveForward(void);
            /**
             * 
             */
            void moveBackward(void);
            /**
             * 
             */
            void moveUp(void);
            /**
             * 
             */
            void moveDown(void);
            /**
             * 
             * @param type
             */
            inline void setType(const Type cameraType) {
                m_type = cameraType;
                if(m_type == CENTER_LOCKED || m_type == FPS_STANDARD) {
                    m_up = Vector3f(0.0f, 1.0f, 0.0f);
                }
            }
            /**
             * 
             * @return 
             */
            inline Type getType(void) const {
                return m_type;
            }
            /**
             * 
             * @return 
             */
            inline Vec3f& getDirection(void) {
                return m_direction;
            }
            /**
             * 
             * @return 
             */
            inline Vec3f& getRight(void) {
                return m_right;
            }
            /**
             * 
             * @param angle
             */
            inline void setAngleH(fgGFXfloat angle) {
                m_hAngle = angle;
            }
            /**
             * 
             * @return 
             */
            inline fgGFXfloat getAngleH(void) const {
                return m_hAngle;
            }
            /**
             * 
             * @param angle
             */
            inline void setAngleV(fgGFXfloat angle) {
                m_vAngle = angle;
            }
            /**
             * 
             * @return 
             */
            inline fgGFXfloat getAngleV(void) const {
                return m_vAngle;
            }
            /**
             * 
             * @param speed
             */
            inline void setSpeed(fgGFXfloat speed) {
                m_speed = speed;
            }
            /**
             * 
             * @return 
             */
            inline fgGFXfloat getSpeed(void) const {
                return m_speed;
            }
            /**
             * 
             * @param mouseSpeed
             */
            inline void setMouseSpeed(fgGFXfloat mouseSpeed) {
                m_mouseSpeed = mouseSpeed;
            }
            /**
             * 
             * @return 
             */
            inline fgGFXfloat getMouseSpeed(void) const {
                return m_mouseSpeed;
            }
            /**
             * 
             * @param zoom
             */
            inline void setZoom(fgGFXfloat zoom) {
                m_zoom = zoom;
            }
            /**
             * 
             * @return 
             */
            inline fgGFXfloat getZoom(void) const {
                return m_zoom;
            }
            /**
             * 
             * @param groundLevel
             */
            inline void setGroundLevel(fgGFXfloat groundLevel) {
                m_groundLevel = groundLevel;
            }
            /**
             * 
             * @param distance
             */
            inline fgGFXfloat getGroundLevel(void) const {
                return m_groundLevel;
            }
            /**
             * 
             * @param distance
             */
            inline void setDistance(fgGFXfloat distance) {
                m_distance = distance;
            }
            /**
             * 
             * @return 
             */
            inline fgGFXfloat getDistance(void) const {
                return m_distance;
            }

        private:
            ///
            Type m_type;
            ///
            Vec3f m_direction;
            ///
            Vec3f m_right;
            ///
            fgGFXfloat m_hAngle;
            ///
            fgGFXfloat m_vAngle;
            ///
            fgGFXfloat m_speed;
            ///
            fgGFXfloat m_mouseSpeed;
            ///
            fgGFXfloat m_zoom;
            ///
            fgGFXfloat m_groundLevel;

            union {
                ///
                fgGFXfloat m_distance;
                ///
                fgGFXfloat m_radius;
            };
        };
    };
};

    #undef FG_INC_GFX_CAMERA_ANIMATION_BLOCK
#endif /* FG_INC_GFX_CAMERA_ANIMATION */
