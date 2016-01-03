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
 * File:   fgGfxAnimation.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 3:47 PM
 */

#ifndef FG_INC_GFX_ANIMATION
    #define FG_INC_GFX_ANIMATION
    #define FG_INC_GFX_ANIMATION_BLOCK

    #if defined(FG_INC_GFX_ANIMATION_INFO_BLOCK)
        #error "FG_INC_GFX_ANIMATION_INFO_BLOCK defined; Do not include fgGfxAnimation.h inside of fgGfxAnimationInfo header!"
    #endif

    #include "fgGfxAnimationChannel.h"    
    #include "fgVector.h"    

namespace fg {
    namespace gfx {
        namespace anim {

            struct SAnimationFrameInfo;
            struct SAnimationInfo;
            
            enum class Type {
                INVALID = 0,
                NODE = 1,
                OBJECT = Type::NODE,
                BONE = 2,
                BONE_RAGDOLL = 3,
                CAMERA = 4
            };

            /**
             *
             */
            class CAnimation {
            public:
                typedef CAnimation self_type;
                typedef CAnimation type;

                typedef CVector<SAnimationChannel> ChannelsVec;
                typedef ChannelsVec::iterator ChannelsVecItor;
                typedef ChannelsVec::const_iterator ChannelsVecConstItor;

                typedef CVector<Matrix4f> MatricesVec;
                typedef MatricesVec::iterator MatricesVecItor;
                typedef MatricesVec::const_iterator MatricesVecConstItor;

            public:
                /**
                 *
                 */
                CAnimation();
                /**
                 *
                 * @param orig
                 */
                CAnimation(const CAnimation& orig);
                /**
                 *
                 */
                virtual ~CAnimation();

                /**
                 *
                 * @param frameInfo
                 * @param elapsed
                 */
                virtual void calculate(SAnimationInfo& animationInfo,
                                       float elapsed = 0.0f) = 0;

                /**
                 * 
                 */
                virtual void clear(void);

                virtual void bake(void);

            public:
                /**
                 *
                 * @param name
                 * @return
                 */
                SAnimationChannel* getChannel(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                SAnimationChannel* getChannel(const char* name);

                /**
                 * 
                 * @param name
                 * @return
                 */
                const SAnimationChannel* getChannel(const std::string& name) const;
                /**
                 *
                 * @param name
                 * @return
                 */
                const SAnimationChannel* getChannel(const char* name) const;

                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool hasChannel(const std::string& name) const;
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool hasChannel(const char* name) const;

                /**
                 *
                 * @param pChannel
                 * @return
                 */
                //fgBool addChannel(SAnimationChannel* pChannel);
                /**
                 *
                 * @param channel
                 * @return
                 */
                fgBool addChannel(const SAnimationChannel& channel);

                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool removeChannel(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool removeChannel(const char* name);

            public:
                /**
                 *
                 * @return
                 */
                Type getType(void) const {
                    return m_type;
                }
                /**
                 * 
                 * @return 
                 */
                std::string& getName(void) {
                    return m_name;
                }
                /**
                 * 
                 * @return 
                 */
                std::string const& getName(void) const {
                    return m_name;
                }
                /**
                 * 
                 * @return 
                 */
                const char* getNameStr(void) const {
                    return m_name.c_str();
                }
                /**
                 * 
                 * @param name
                 */
                void setName(const std::string& name) {
                    m_name.clear();
                    m_name.append(name);
                }
                /**
                 * 
                 * @param name
                 */
                void setName(const char* name) {
                    if(name) {
                        m_name.clear();
                        m_name.append(name);
                    } else {
                        m_name.clear();
                    }
                }
                /**
                 * 
                 * @return 
                 */
                float getTicksPerSecond(void) const {
                    return m_ticksPerSecond;
                }
                /**
                 * 
                 * @return 
                 */
                float getDurationInTicks(void) const {
                    return m_duration;
                }

                /**
                 *
                 * @param duration
                 * @param ticksPerSecond
                 */
                void setTimeData(float duration, float ticksPerSecond);
                /**
                 *
                 * @param ticksPerSecond
                 */
                void setTicksPerSecond(float ticksPerSecond);
                /**
                 * 
                 * @param duration
                 */
                void setDuration(float duration);
                /**
                 *
                 * @return
                 */
                float getDurationInMs(void) const {
                    return m_durationMs;
                }
                /**
                 *
                 * @return
                 */
                float getDurationInSeconds(void) const {
                    return m_durationS;
                }

                /**
                 * 
                 * @return 
                 */
                ChannelsVec& getChannels(void) {
                    return m_channels;
                }
                /**
                 * 
                 * @return 
                 */
                ChannelsVec const& getChannels(void) const {
                    return m_channels;
                }
                /**
                 * 
                 * @return 
                 */
                unsigned int count(void) const {
                    return m_channels.size();
                }
                /**
                 * 
                 * @return 
                 */
                fgBool isEmpty(void) const {
                    return (fgBool)(m_channels.empty());
                }
                /**
                 * 
                 * @return
                 */
                fgBool shouldInterpolate(void) const {
                    return m_shouldInterpolate;
                }
                /**
                 * 
                 * @param toggle
                 */
                void setInterpolation(fgBool toggle = FG_TRUE) {
                    m_shouldInterpolate = toggle;
                }

            public:
                fgBool isBoneAnimation(void) const {
                    return (fgBool)(m_type == Type::BONE || m_type == Type::BONE_RAGDOLL);
                }
                fgBool isRagdollAnimation(void) const {
                    return (fgBool)(m_type == Type::BONE_RAGDOLL);
                }
                fgBool isCameraAnimation(void) const {
                    return (fgBool)(m_type == Type::CAMERA);
                }
                fgBool isNodeAnimation(void) const {
                    return (fgBool)(m_type == Type::NODE);
                }

            protected:
                ///
                Type m_type;

            private:
                ///
                std::string m_name;
                ///
                ChannelsVec m_channels;
                ///
                float m_duration;
                ///
                float m_durationMs;
                ///
                float m_durationS;
                ///
                float m_ticksPerSecond;
                ///
                fgBool m_shouldInterpolate;
            }; // class CAnimation

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIMATION_BLOCK
#endif	/* FG_INC_GFX_ANIMATION */
