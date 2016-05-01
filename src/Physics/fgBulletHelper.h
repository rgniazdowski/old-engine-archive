/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgBulletHelper.h
 * Author: vigilant
 *
 * Created on September 24, 2015, 12:16 PM
 */

#ifndef FG_INC_PHYSICS_BULLET_HELPER
    #define FG_INC_PHYSICS_BULLET_HELPER
    #define FG_INC_PHYSICS_BULLET_HELPER_BLOCK

    #include "fgBuildConfig.h"
    
    #if defined(FG_USING_BULLET)
        #include "Math/fgVector2.h"
        #include "Math/fgVector3.h"
        #include "Math/fgVector4.h"
        #include "Math/fgMatrix3.h"
        #include "Math/fgMatrix4.h"
        #include "Math/fgQuaternion.h"
        #include "LinearMath/btMatrix3x3.h"
        #include "LinearMath/btVector3.h"
        #include "LinearMath/btTransform.h"

namespace fg {
    namespace physics {
        namespace bullet_helper {
            inline void copyVector(Vector2f& dest, const btVector3& source) {
                dest.x = source.getX();
                dest.y = source.getY();
            }
            inline void copyVector(Vector2f& dest, const btVector4& source) {
                dest.x = source.getX();
                dest.y = source.getY();
            }
            inline void copyVector(Vector3f& dest, const btVector3& source) {
                dest.x = source.getX();
                dest.y = source.getY();
                dest.z = source.getZ();
            }
            inline void copyVector(Vector3f& dest, const btVector4& source) {
                dest.x = source.getX();
                dest.y = source.getY();
                dest.z = source.getZ();
            }
            inline void copyVector(Vector4f& dest, const btVector3& source) {
                dest.x = source.getX();
                dest.y = source.getY();
                dest.z = source.getZ();
            }
            inline void copyVector(Vector4f& dest, const btVector4& source) {
                dest.x = source.getX();
                dest.y = source.getY();
                dest.z = source.getZ();
                dest.w = source.getW();
            }
            //------------------------------------------------------------------
            inline void copyVector(btVector3& dest, const Vector2f& source) {
                dest.setValue(source.x, source.y, 0.0f);
            }
            inline void copyVector(btVector4& dest, const Vector2f& source) {
                dest.setValue(source.x, source.y, 0.0f, 0.0f);
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyVector(btVector3& dest, const Vector3f& source) {
                dest.setValue(source.x, source.y, source.z);
            }
            inline void copyVector(btVector4& dest, const Vector3f& source) {
                dest.setValue(source.x, source.y, source.z, 0.0f);
            }
            inline void copyVector(btVector3& dest, const Vector4f& source) {
                dest.setValue(source.x, source.y, source.z);
            }
            inline void copyVector(btVector4& dest, const Vector4f& source) {
                dest.setValue(source.x, source.y, source.z, source.w);
            }
            //------------------------------------------------------------------
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyQuat(Quaternionf& dest, const btQuaternion& source) {
                dest.x = source.getX();
                dest.y = source.getY();
                dest.z = source.getZ();
                dest.w = source.getW();
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyQuat(btQuaternion& dest, const Quaternionf& source) {
                dest.setValue(source.x, source.y, source.z, source.w);
            }
            //------------------------------------------------------------------

            /**
             * 
             * @param dest
             * @param source
             */
            void copyMatrix4x4(Matrix4f& dest, const btMatrix3x3& source);
            /**
             *
             * @param dest
             * @param source
             */
            void copyMatrix4x4(Matrix4f& dest, const btTransform& source);
            /**
             *
             * @param dest
             * @param source
             */
            void copyMatrix4x4(btTransform& dest, const Matrix4f& source);

            /**
             *
             * @param dest
             * @param source
             */
            void copyMatrix3x3(Matrix3f& dest, const btMatrix3x3& source);
            /**
             *
             * @param dest
             * @param source
             */
            void copyMatrix3x3(btMatrix3x3& dest, const Matrix3f& source);

            /**
             *
             * @param source
             * @param scale
             * @param rotation
             * @param position
             */
            void decompose(const btTransform& source,
                           Vector3f& scale,
                           Quaternionf& rotation,
                           Vector3f& position);

        } // namespace bullet_helper
    } // namespace physics
} // namespace fg

    #endif /* FG_USING_BULLET */
    #undef FG_INC_PHYSICS_BULLET_HELPER_BLOCK
#endif	/* FG_INC_PHYSICS_BULLET_HELPER */
