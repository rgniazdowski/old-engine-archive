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
 * File:   fgGfxAnimationInfo.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 3:51 PM
 */

#ifndef FG_INC_GFX_ANIMATION_INFO
    #define FG_INC_GFX_ANIMATION_INFO
    #define FG_INC_GFX_ANIMATION_INFO_BLOCK

    #include "fgTypes.h"
    #include "Math/fgDualQuaternion.h"

namespace fg {
    namespace gfx {
        namespace anim {

            class CAnimation;

            /**
             *
             */
            struct SAnimationFrameInfo {
                typedef SAnimationFrameInfo self_type;
                typedef SAnimationFrameInfo type;

                typedef CVector<Matrix4f> MatricesVec;
                typedef MatricesVec::iterator MatricesVecItor;
                typedef MatricesVec::const_iterator MatricesVecConstItor;

                typedef CVector<DualQuaternionf> DualQuatsVec;
                typedef DualQuatsVec::iterator DualQuatsVecItor;
                typedef DualQuatsVec::const_iterator DualQuatsVecConstItor;

                /// Current frame index
                float index;
                /// Current elapsed time
                float elapsed;
                /// Array of up-to-date transformations;
                /// each matrix represents bone or node transformation matrix.
                MatricesVec transformations;
                ///
                DualQuatsVec dualQuaternions;

                //--------------------------------------------------------------

                /**
                 *
                 */
                SAnimationFrameInfo();
                /**
                 *
                 * @param other
                 */
                SAnimationFrameInfo(const self_type& other);
                /**
                 *
                 */
                virtual ~SAnimationFrameInfo();
                /**
                 *
                 */
                inline void clear(void) {
                    transformations.clear();
                    dualQuaternions.clear();
                }
                /**
                 *
                 */
                inline void reset(void) {
                    index = 0.0f;
                    elapsed = 0.0f;
                    clear();
                }
                /**
                 *
                 * @param n
                 */
                inline void reserve(unsigned int n) {
                    transformations.reserve(n);
                    dualQuaternions.reserve(n);
                }
                /**
                 *
                 * @param n
                 */
                inline void resize(unsigned int n) {
                    transformations.resize(n);
                    dualQuaternions.resize(n);
                }
                /**
                 *
                 * @return
                 */
                inline unsigned int count(void) const {
                    return transformations.size();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isEmpty(void) const {
                    return (fgBool)transformations.empty() && dualQuaternions.empty();
                }
                /**
                 *
                 * @return
                 */
                inline int getIndex(void) {
                    return (int)index;
                }
            }; // struct SAnimationFrameInfo

            /**
             *
             */
            struct SAnimationInfo {
                typedef SAnimationInfo self_type;
                typedef SAnimationInfo type;

            public:

                /**
                 *
                 */
                enum StateFlags {
                    NO_FLAGS = 0x0000,
                    PLAYING = 0x0001,
                    PAUSED = 0x0002,
                    STOPPED = 0x0004,
                    LOOPED = 0x0008,
                    REVERSE_LOOPED = 0x0010,
                    PLAYING_REVERSED = 0x0020
                }; // enum StateFlags

            public:
                /// External pointer to the currently used animation
                CAnimation* pAnimation;
                /// Information on currently calculated frame
                SAnimationFrameInfo curFrame;
                ///
                float tempo;

            private:
                ///
                StateFlags m_stateFlags;
                ///
                int m_loopCount;

                /**
                 * 
                 * @param flags
                 * @param toggle
                 */
                void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);

            public:
                /**
                 * 
                 * @param _pAnimation
                 */
                SAnimationInfo(CAnimation* _pAnimation = NULL);
                /**
                 *
                 * @param orig
                 */
                SAnimationInfo(const SAnimationInfo& orig);
                /**
                 *
                 */
                virtual ~SAnimationInfo();

                /**
                 *
                 */
                void clear(void);
                /**
                 *
                 * @param delta
                 */
                void calculate(float delta = 0.0f);
                /**
                 *
                 * @param delta
                 */
                void advanceTime(float delta = 0.0f);

                //--------------------------------------------------------------

                /**
                 *
                 */
                void play(void);
                /**
                 *
                 */
                void stop(fgBool shouldRewind = FG_TRUE);
                /**
                 *
                 */
                void pause(void);
                /**
                 *
                 */
                void togglePause(void);
                /**
                 *
                 */
                void resume(void);
                /**
                 *
                 */
                void rewind(void);
                /**
                 *
                 * @param counter
                 * @param shouldPlay
                 */
                void loop(int counter = -1, fgBool shouldPlay = FG_FALSE);
                /**
                 *
                 * @param counter
                 * @param shouldPlay
                 */
                void reloop(int counter = -1, fgBool shouldPlay = FG_FALSE);

                //--------------------------------------------------------------
                inline fgBool isPlaying(void) const {
                    return (fgBool)!!(m_stateFlags & PLAYING);
                }
                inline fgBool isPaused(void) const {
                    return (fgBool)!!(m_stateFlags & PAUSED);
                }
                inline fgBool isStopped(void) const {
                    return (fgBool)!!((m_stateFlags & STOPPED) || (m_stateFlags == NO_FLAGS));
                }
                inline fgBool isLooped(void) const {
                    return (fgBool)!!(m_stateFlags & LOOPED);
                }
                inline fgBool isReverseLooped(void) const {
                    return (fgBool)!!(m_stateFlags & REVERSE_LOOPED);
                }
                inline fgBool isPlayingReversed(void) const {
                    return (fgBool)!!(m_stateFlags & PLAYING_REVERSED);
                }

                //--------------------------------------------------------------
                inline int operator ==(const SAnimationInfo &b) const {
                    return (b.pAnimation == this->pAnimation);
                }
                inline int operator !=(const SAnimationInfo &b) const {
                    return !(b.pAnimation == this->pAnimation);
                }

            }; // struct SAnimationInfo

            // FG_ENUM_FLAGS(SAnimationInfo::StateFlags);
            FG_ENUM_FLAGS(SAnimationInfo::StateFlags);
            //------------------------------------------------------------------
            inline void SAnimationInfo::setFlag(const StateFlags flags, const fgBool toggle) {
                if(toggle) {
                    m_stateFlags |= flags;
                } else {
                    m_stateFlags |= flags;
                    m_stateFlags ^= flags;
                }
            }

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIMATION_INFO_BLOCK
#endif /* FG_INC_GFX_ANIMATION_INFO */
