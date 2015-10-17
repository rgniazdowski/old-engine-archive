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
 * File:   fgGfxRagdollBoneAnimation.h
 * Author: vigilant
 *
 * Created on October 10, 2015, 2:04 AM
 */

#ifndef FG_INC_GFX_RAGDOLL_BONE_ANIMATION
    #define FG_INC_GFX_RAGDOLL_BONE_ANIMATION
    #define FG_INC_GFX_RAGDOLL_BONE_ANIMATION_BLOCK

    #include "fgGfxBoneAnimation.h"
    #include "Math/fgUniversalTransform.h"

namespace fg {
    namespace gfx {
        namespace anim {

            /**
             *
             */
            class CRagdollBoneAnimation : public CBoneAnimation {
            public:
                typedef CRagdollBoneAnimation self_type;
                typedef CRagdollBoneAnimation type;
                typedef CBoneAnimation base_type;

                typedef CVector<Matrix4f> MatricesVec;
                typedef CVector<math::SUniversalTransform*> UniversalTransformsVec;

            public:
                /**
                 *
                 */
                CRagdollBoneAnimation(CArmature* pArmature = NULL);
                /**
                 *
                 */
                CRagdollBoneAnimation(const CRagdollBoneAnimation& orig);
                /**
                 *
                 */
                virtual ~CRagdollBoneAnimation();

                /**
                 *
                 * @param pArmature
                 */
                virtual void calculate(SAnimationInfo& animationInfo,
                                       float delta = 0.0f);
                /**
                 *
                 * @param frameInfo
                 * @param elapsed
                 */
                virtual void calculate(SAnimationInfo& animationInfo,
                                       const BonesVec& bones,
                                       float delta = 0.0f);

            public:
                /**
                 *
                 * @return
                 */
                UniversalTransformsVec& getUniversalTransforms(void) {
                    return m_transforms;
                }
                /**
                 *
                 * @return
                 */
                UniversalTransformsVec const& getUniversalTransforms(void) const {
                    return m_transforms;
                }
                /**
                 *
                 * @param index
                 * @param pTransform
                 */
                void setTransform(unsigned int index,
                                  math::SUniversalTransform* pTransform);
                /**
                 *
                 * @param index
                 * @return
                 */
                math::SUniversalTransform* getTransform(unsigned int index);
                /**
                 *
                 * @param index
                 * @return
                 */
                math::SUniversalTransform const* getTransform(unsigned int index) const;
                /**
                 *
                 * @param pModelMat
                 */
                void setModelMatrix(Matrix4f* pModelMat) {
                    m_pModelMat = pModelMat;
                }
                /**
                 *
                 * @return
                 */
                Matrix4f* getModelMatrix(void) {
                    return m_pModelMat;
                }
                /**
                 *
                 * @return
                 */
                Matrix4f const* getModelMatrix(void) const {
                    return m_pModelMat;
                }
                /**
                 * 
                 * @param modelMatrix
                 */
                void getModelMatrix(Matrix4f& modelMatrix) const {
                    if(m_pModelMat) {
                        modelMatrix = *m_pModelMat;
                    }
                }

            private:
                /// Special vector containing abstract objects for universal matrix
                /// manipulation. It's used for getting rigid bone transformations
                /// which are already calculated by the physics engine - just need 
                /// to copy bone world transformations and convert them to model/bone space.
                /// This array has always the same size as total number of bones
                /// in armature. Some pointer may be NULL (when not used).
                UniversalTransformsVec m_transforms;
                ///
                Matrix4f* m_pModelMat;
            }; // class CRagdollBoneAnimation

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_RAGDOLL_BONE_ANIMATION_BLOCK
#endif	/* FG_INC_GFX_RAGDOLL_BONE_ANIMATION */
