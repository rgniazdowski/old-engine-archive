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
 * File:   fgGfxAnimated.h
 * Author: vigilant
 *
 * Created on September 9, 2015, 12:35 PM
 */

#ifndef FG_INC_GFX_ANIMATED
    #define FG_INC_GFX_ANIMATED
    #define FG_INC_GFX_ANIMATED_BLOCK

    #include "GFX/Animation/fgGfxAnimationInfo.h"

namespace fg {
    namespace gfx {

        namespace anim {
            class CAnimation;
            class CNodeAnimation;
            class CBoneAnimation;

        } // namespace anim

        namespace traits {

            /**
             *
             */
            class CAnimated {
            public:
                typedef CAnimated self_type;
                typedef CAnimated type;

                typedef CVector<anim::SAnimationInfo> AnimationsVec;
                typedef AnimationsVec::iterator AnimationsVecItor;
                typedef AnimationsVec::const_iterator AnimationsVecConstItor;

            public:
                /**
                 *
                 */
                CAnimated();
                /**
                 *
                 */
                virtual ~CAnimated() { }

                //--------------------------------------------------------------

                /**
                 *
                 * @param pAnimation
                 * @param slot
                 * @return
                 */
                fgBool setAnimation(anim::CAnimation* pAnimation, unsigned int slot = 0);
                /**
                 *
                 * @param pAnimationInfo
                 * @param slot
                 * @return
                 */
                fgBool setAnimation(anim::SAnimationInfo* pAnimationInfo, unsigned int slot = 0);
                /**
                 *
                 * @param pAnimation
                 * @return
                 */
                int pushAnimation(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param pAnimationInfo
                 * @return
                 */
                int pushAnimation(anim::SAnimationInfo* pAnimationInfo);

                //--------------------------------------------------------------

                /**
                 *
                 * @param name
                 * @return
                 */
                anim::CAnimation* getAnimation(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                anim::CAnimation* getAnimation(const char* name);
                /**
                 *
                 * @param slot
                 * @return
                 */
                anim::CAnimation* getAnimation(unsigned int slot);

                /**
                 *
                 * @param pAnimation
                 * @return
                 */
                anim::SAnimationInfo* getAnimationInfo(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param name
                 * @return
                 */
                anim::SAnimationInfo* getAnimationInfo(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                anim::SAnimationInfo* getAnimationInfo(const char* name);
                /**
                 *
                 * @param slot
                 * @return
                 */
                anim::SAnimationInfo* getAnimationInfo(unsigned int slot);

                /**
                 *
                 * @param pAnimation
                 * @return
                 */
                int getAnimationSlot(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param name
                 * @return
                 */
                int getAnimationSlot(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                int getAnimationSlot(const char* name);

                //--------------------------------------------------------------

                /**
                 *
                 * @param pAnimation
                 * @return
                 */
                fgBool hasAnimation(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool hasAnimation(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool hasAnimation(const char* name);

                //--------------------------------------------------------------

                /**
                 *
                 * @param pAnimation
                 */
                void removeAnimation(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param name
                 */
                void removeAnimation(const std::string& name);
                /**
                 *
                 * @param name
                 */
                void removeAnimation(const char* name);

                //--------------------------------------------------------------

                /**
                 *
                 * @param pAnimation
                 */
                void pauseAnimation(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param name
                 */
                void pauseAnimation(const std::string& name);
                /**
                 *
                 * @param name
                 */
                void pauseAnimation(const char* name);

                //--------------------------------------------------------------

                /**
                 *
                 * @param pAnimation
                 */
                void resumeAnimation(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param name
                 */
                void resumeAnimation(const std::string& name);
                /**
                 *
                 * @param name
                 */
                void resumeAnimation(const char* name);

                //--------------------------------------------------------------

                /**
                 *
                 * @param pAnimation
                 */
                void restartAnimation(anim::CAnimation* pAnimation);
                /**
                 *
                 * @param name
                 */
                void restartAnimation(const std::string& name);
                /**
                 *
                 * @param name
                 */
                void restartAnimation(const char* name);

                //--------------------------------------------------------------

                /**
                 *
                 * @param elapsed
                 * @return
                 */
                virtual void animate(float delta = 0.0f) = 0;

                //--------------------------------------------------------------
                /**
                 * 
                 * @return 
                 */
                AnimationsVec& getAnimations(void) {
                    return m_animations;
                }
                /**
                 * 
                 * @return 
                 */
                AnimationsVec const& getAnimations(void) const {
                    return m_animations;
                }
                /**
                 * 
                 * @return 
                 */
                unsigned int getAnimationsCount(void) const {
                    return m_animations.size();
                }

                //--------------------------------------------------------------

            protected:
                /// Vector holding currently used animations.
                /// Order is significant.
                AnimationsVec m_animations;

            }; // abstract class CAnimated

        } // namespace traits
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIMATED_BLOCK
#endif	/* FG_INC_GFX_ANIMATED */