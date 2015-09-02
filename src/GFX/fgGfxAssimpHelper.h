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
 * File:   fgAssimpHelper.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 11:39 AM
 */

#ifndef FG_INC_GFX_ASSIMP_HELPER
    #define FG_INC_GFX_ASSIMP_HELPER

    #include "fgBuildConfig.h"
    #include "Math/fgMathLib.h"
    #include "fgGfxMaterial.h"

    #if defined(FG_USING_ASSIMP) 
        #include "assimp/material.h"
        #include "assimp/quaternion.inl"
        #include "assimp/matrix4x4.inl"
        #include "assimp/vector2.inl"
        #include "assimp/vector3.inl"
    #endif

    #if defined(FG_USING_ASSIMP)
namespace fg {
    namespace gfx {
        namespace assimp_helper {

            /**
             *
             * @param pNewMaterial
             * @param pMaterial
             */
            void setupMaterial(struct SMaterial* pNewMaterial,
                               struct aiMaterial* pMaterial);
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyVector(Vector3f& dest, const aiVector3D& source) {
                dest.x = source.x;
                dest.y = source.y;
                dest.z = source.z;
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyVector(aiVector3D& dest, const Vector3f& source) {
                dest.x = source.x;
                dest.y = source.y;
                dest.z = source.z;
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyVector(Vector2f& dest, const aiVector2D& source) {
                dest.x = source.x;
                dest.y = source.y;
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyVector(aiVector2D& dest, const Vector2f& source) {
                dest.x = source.x;
                dest.y = source.y;
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyVector(Vector2f& dest, const aiVector3D& source) {
                dest.x = source.x;
                dest.y = source.y;
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyVector(aiVector2D& dest, const Vector3f& source) {
                dest.x = source.x;
                dest.y = source.y;
            }
            /**
             * 
             * @param dest
             * @param source
             */
            inline void copyQuat(Quaternionf& dest, const aiQuaternion& source) {
                dest.x = source.x;
                dest.y = source.y;
                dest.z = source.z;
                dest.w = source.w;
            }
            /**
             *
             * @param dest
             * @param source
             */
            inline void copyQuat(aiQuaternion& dest, const Quaternionf& source) {
                dest.x = source.x;
                dest.y = source.y;
                dest.z = source.z;
                dest.w = source.w;
            }

            //------------------------------------------------------------------

            /**
             *
             * @param dest
             * @param source
             */
            void copyMatrix4x4(Matrix4f& dest, const aiMatrix4x4& source);
            /**
             *
             * @param dest
             * @param source
             */
            void copyMatrix4x4(aiMatrix4x4& dest, const Matrix4f& source);

            /**
             *
             * @param source
             * @param scale
             * @param rotation
             * @param position
             */
            void decompose(const aiMatrix4x4& source,
                           Vector3f& scale,
                           Quaternionf& rotation,
                           Vector3f& position);



        } // namespace assimp_helper

    } // namespace gfx
} // namespace fg

    #endif

#endif	/* FG_INC_GFX_ASSIMP_HELPER */
