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
    #include "GFX/Animation/fgGfxAnimationType.h"
    #include "Util/fgStrings.h"
    #include "fgTraits.h"

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

                // This will be tricky
                typedef CVector<anim::SAnimationFrameInfo *> BlendedFramesMap;

                typedef anim::SAnimationFrameInfo::DualQuatsVec DualQuatsVec;
                typedef anim::SAnimationFrameInfo::MatricesVec MatricesVec;

            public:
                static const fg::traits::SceneNode SELF_TRAIT = fg::traits::ANIMATED;

            public:
                /**
                 *
                 */
                CAnimated();
                /**
                 *
                 */
                virtual ~CAnimated();

                //--------------------------------------------------------------
                
                /**
                 *
                 * @param pAnimation
                 * @param slot
                 * @return
                 */
                fgBool setAnimation(anim::CAnimation* pAnimation,
                                    unsigned int slot = 0);
                /**
                 *
                 * @param pAnimationInfo
                 * @param slot
                 * @return
                 */
                fgBool setAnimation(anim::SAnimationInfo* pAnimationInfo,
                                    unsigned int slot = 0);
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
                anim::CAnimation* getAnimation(const std::string& name,
                                               strings::MatchMode mode = strings::MATCH_EXACT);
                /**
                 *
                 * @param name
                 * @return
                 */
                anim::CAnimation* getAnimation(const char* name,
                                               strings::MatchMode mode = strings::MATCH_EXACT);
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
                anim::SAnimationInfo* getAnimationInfo(const std::string& name,
                                                       strings::MatchMode mode = strings::MATCH_EXACT);
                /**
                 *
                 * @param name
                 * @return
                 */
                anim::SAnimationInfo* getAnimationInfo(const char* name,
                                                       strings::MatchMode mode = strings::MATCH_EXACT);
                /**
                 *
                 * @param name
                 * @param mode
                 * @return
                 */
                anim::SAnimationInfo* getAnimationInfo(const std::string& name,
                                                       const std::string& mode);

                /**
                 * 
                 * @param name
                 * @param mode
                 * @return 
                 */
                anim::SAnimationInfo* getAnimationInfo(const char* name,
                                                       const char* mode);
                /**
                 *
                 * @param slot
                 * @return
                 */
                anim::SAnimationInfo* getAnimationInfoBySlot(unsigned int slot);

                //--------------------------------------------------------------
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
                int getAnimationSlot(const std::string& name,
                                     strings::MatchMode mode = strings::MATCH_EXACT);
                /**
                 *
                 * @param name
                 * @return
                 */
                int getAnimationSlot(const char* name,
                                     strings::MatchMode mode = strings::MATCH_EXACT);

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
                fgBool hasAnimation(const std::string& name,
                                    strings::MatchMode mode = strings::MATCH_EXACT);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool hasAnimation(const char* name,
                                    strings::MatchMode mode = strings::MATCH_EXACT);

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
                void removeAnimation(const std::string& name,
                                     strings::MatchMode mode = strings::MATCH_EXACT);
                /**
                 *
                 * @param name
                 */
                void removeAnimation(const char* name,
                                     strings::MatchMode mode = strings::MATCH_EXACT);
                /**
                 *
                 * @param name
                 * @param mode
                 */
                void removeAnimation(const std::string& name, const std::string& mode);
                /**
                 * 
                 * @param name
                 * @param mode
                 */
                void removeAnimation(const char* name, const char* mode);
                //--------------------------------------------------------------
                /**
                 * 
                 */
                virtual void removeAnimations(void);
                /**
                 *
                 */
                virtual void playAnimations(void);
                /**
                 *
                 */
                virtual void stopAnimations(void);
                /**
                 *
                 */
                virtual void pauseAnimations(fgBool toggle = FG_TRUE);
                /**
                 *
                 */
                virtual void resumeAnimations(void);
                /**
                 *
                 */
                virtual void rewindAnimations(void);

                //--------------------------------------------------------------
            protected:
                /**
                 *
                 * @param elapsed
                 * @return
                 */
                virtual void animate(float delta = 0.0f) = 0;

                //--------------------------------------------------------------
            protected:
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
                BlendedFramesMap& getBlendedFrames(void) {
                    return m_blendedFramesMap;
                }
                /**
                 *
                 * @return
                 */
                BlendedFramesMap const& getBlendedFrames(void) const {
                    return m_blendedFramesMap;
                }
                /**
                 *
                 * @param animType
                 * @return
                 */
                anim::SAnimationFrameInfo* getBlendedFrame(anim::Type animType);
                /**
                 *
                 * @param animType
                 * @return
                 */
                const anim::SAnimationFrameInfo* getBlendedFrame(anim::Type animType) const;

                /**
                 * 
                 * @param animType
                 * @return
                 */
                inline fgBool hasBlendedFrame(anim::Type animType) const {
                    return (fgBool)(getBlendedFrame(animType) != NULL);
                }
                /**
                 * 
                 * @param animType
                 * @return
                 */
                anim::SAnimationFrameInfo* prepareBlendedFrame(anim::Type animType);
                /**
                 *
                 * @param animType
                 */
                void clearBlendedFrame(anim::Type animType);
                /**
                 *
                 */
                void destroyBlendedFrames(void);

                //--------------------------------------------------------------

                void clearFinalTransformations(void);
                void setFinalDQs(DualQuatsVec* pFinalDQs);
                void setFinalMatrices(MatricesVec* pFinalMatrices);
                DualQuatsVec* getFinalDQs(void);
                MatricesVec* getFinalMatrices(void);
                
            public:
                /**
                 * 
                 * @return 
                 */
                unsigned int getAnimationsCount(void) const {
                    return m_animations.size();
                }
                /**
                 * 
                 * @return
                 */
                unsigned int getBlendedFramesCount(void) const {
                    unsigned int result = 0;
                    for(unsigned int i = 0; i < m_blendedFramesMap.size(); i++) {
                        if(m_blendedFramesMap[i]) {
                            result += !m_blendedFramesMap[i]->isEmpty();
                        }
                    }
                    return result;
                }
                //--------------------------------------------------------------                

            private:
                /// Vector holding currently used animations.
                /// Order is significant.
                AnimationsVec m_animations;
                ///
                BlendedFramesMap m_blendedFramesMap;
                ///
                DualQuatsVec* m_pFinalDQs;
                ///
                MatricesVec* m_pFinalMatrices;

            }; // abstract class CAnimated

        } // namespace traits
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIMATED_BLOCK
#endif /* FG_INC_GFX_ANIMATED */
