/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/* 
 * File:   fgGfxBoneAnimation.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 5:40 PM
 */

#ifndef FG_INC_GFX_BONE_ANIMATION
    #define FG_INC_GFX_BONE_ANIMATION
    #define FG_INC_GFX_BONE_ANIMATION_BLOCK

    #include "fgGfxAnimation.h"
    #include "fgGfxBone.h"

namespace fg {
    namespace gfx {
        namespace anim {

            struct SBone;
            class CArmature;

            /**
             *
             */
            enum StandardActionType {
                ACTION_NONE = 0,
                ACTION_IDLE,
                ACTION_ATTACK,
                ACTION_MELEE,
                ACTION_FIRE,
                ACTION_RELOAD,
                ACTION_RUN,
                ACTION_WALK,
                ACTION_CROUCH,

                ACTION_STRAFE_LEFT,
                ACTION_STRAFE_RIGHT,

                ACTION_LEAN_LEFT,
                ACTION_LEAN_RIGHT,

                ACTION_GRAB,
                ACTION_JUMP,
                ACTION_KICK,
                ACTION_USE,

                ACTION_DEATH,

                ACTION_OTHER,

                NUM_STANDARD_ACTIONS
            };

            StandardActionType getActionTypeFromText(const std::string& text);
            StandardActionType getActionTypeFromText(const char* name);
    #if 0

            int getBonesForStandardAction(StandardActionType action,
                                          CVector<BoneType>& boneTypes);
    #endif
            /**
             * 
             */
            class CBoneAnimation : public CAnimation {
            public:
                typedef CBoneAnimation self_type;
                typedef CBoneAnimation type;
                typedef CAnimation base_type;

                typedef CVector<SBone*> BonesVec;
                typedef BonesVec::iterator BonesVecItor;

            public:
                /**
                 *
                 */
                CBoneAnimation(CArmature* pArmature = NULL);
                /**
                 *
                 * @param orig
                 */
                CBoneAnimation(const CBoneAnimation& orig);
                /**
                 *
                 */
                virtual ~CBoneAnimation();

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
                 * @param pArmature
                 */
                void setArmature(CArmature* pArmature) {
                    m_pArmature = pArmature;
                }
                /**
                 *
                 * @return
                 */
                CArmature* getArmature(void) {
                    return m_pArmature;
                }
                /**
                 * 
                 * @return
                 */
                CArmature const* getArmature(void) const {
                    return m_pArmature;
                }

            private:
                /// Pointer to the external Armature object
                CArmature* m_pArmature;
            protected:
                /// Intermediate matrices vector (helper in calculations)
                MatricesVec m_intermediate;
            }; // class CBoneAnimation

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_BONE_ANIMATION_BLOCK
#endif	/* FG_INC_GFX_BONE_ANIMATION */
