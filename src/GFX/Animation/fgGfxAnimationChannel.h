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
 * File:   fgGfxAnimationChannel.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 3:49 PM
 */

#ifndef FG_INC_GFX_ANIMATION_CHANNEL
    #define FG_INC_GFX_ANIMATION_CHANNEL
    #define FG_INC_GFX_ANIMATION_CHANNEL_BLOCK

    #include "Math/fgMathLib.h"
    #include "fgVector.h"

namespace fg {
    namespace gfx {
        namespace anim {

            /**
             *
             */
            template<typename T>
            struct SVectorKeyT {
                typedef SVectorKeyT<T> self_type;
                typedef float time_type;
                typedef typename Vector3T<T>::type value_type;

                float elapsed;
                value_type value;
                SVectorKeyT() : elapsed(0.0f), value() { }
                SVectorKeyT(float _elapsed, const value_type& _value) : elapsed(_elapsed), value(_value) { }
                virtual ~SVectorKeyT() {
                    value = value_type();
                    elapsed = 0.0f;
                }
            }; // struct SVectorKeyT<T>

            typedef SVectorKeyT<float> SVectorKeyf;

            /**
             *
             */
            template<typename T>
            struct SQuatKeyT {
                typedef SQuatKeyT<T> self_type;
                typedef float time_type;
                typedef QuaternionT<T> value_type;

                float elapsed;
                value_type value;
                SQuatKeyT() : elapsed(0.0f), value() { }
                SQuatKeyT(float _elapsed, const value_type& _value) : elapsed(_elapsed), value(_value) { }
                virtual ~SQuatKeyT() {
                    value = value_type();
                    elapsed = 0.0f;
                }
            }; // struct SQuatKeyT<T>

            typedef SQuatKeyT<float> SQuatKeyf;
            typedef SQuatKeyf SRotationKeyf;

            /**
             *
             */
            struct SAnimationChannel {
                typedef SAnimationChannel self_type;
                typedef SAnimationChannel type;

                /**
                 *
                 */
                SAnimationChannel();
                /**
                 *
                 * @param orig
                 */
                SAnimationChannel(const SAnimationChannel& orig);
                /**
                 *
                 */
                virtual ~SAnimationChannel();

                //--------------------------------------------------------------

                /**
                 *
                 * @param currentTime
                 * @return
                 */
                const Vector3f& getPosition(float currentTime = 0.0f);
                /**
                 *
                 * @param result
                 * @param currentTime
                 */
                void getPositionInterpolated(Vector3f& result, float currentTime = 0.0f);
                /**
                 *
                 * @param currentTime
                 * @return
                 */
                Vector3f getPositionInterpolated(float currentTime = 0.0f);

                //--------------------------------------------------------------

                /**
                 *
                 * @param currentTime
                 * @return
                 */
                const Vector3f& getScale(float currentTime = 0.0f);
                /**
                 *
                 * @param result
                 * @param currentTime
                 */
                void getScaleInterpolated(Vector3f& result, float currentTime = 0.0f);
                /**
                 *
                 * @param currentTime
                 * @return
                 */
                Vector3f getScaleInterpolated(float currentTime = 0.0f);

                //--------------------------------------------------------------

                /**
                 *
                 * @param currentTime
                 * @return
                 */
                const Quaternionf& getRotation(float currentTime = 0.0f);
                /**
                 *
                 * @param result
                 * @param currentTime
                 */
                void getRotationInterpolated(Quaternionf& result, float currentTime = 0.0f);
                /**
                 *
                 * @param currentTime
                 * @return
                 */
                Quaternionf getRotationInterpolated(float currentTime = 0.0f);

                //--------------------------------------------------------------

                /**
                 *
                 * @param result
                 * @param currentTime
                 */
                void getMatrix(Matrix4f& result, float currentTime = 0.0f);
                /**
                 *
                 * @param currentTime
                 * @return
                 */
                Matrix4f getMatrix(float currentTime = 0.0f);

                //--------------------------------------------------------------

                /**
                 *
                 * @param result
                 * @param currentTime
                 */
                void getMatrixInterpolated(Matrix4f& result, float currentTime = 0.0f);
                /**
                 *
                 * @param currentTime
                 * @return
                 */
                Matrix4f getMatrixInterpolated(float currentTime = 0.0f);

                //--------------------------------------------------------------

                /**
                 *
                 * @param outPosition
                 * @param outRotation
                 * @param outScale
                 * @param currentTime
                 */
                void get(Vector3f& outPosition,
                         Quaternionf& outRotation,
                         Vector3f& outScale,
                         float currentTime = 0.0f);

                /**
                 * 
                 * @param outPosition
                 * @param outRotation
                 * @param outScale
                 * @param currentTime
                 */
                void getInterpolated(Vector3f& outPosition,
                                     Quaternionf& outRotation,
                                     Vector3f& outScale,
                                     float currentTime = 0.0f);

                //--------------------------------------------------------------

            public:
                ///
                std::string targetName;
                ///
                CVector<SVectorKeyf> positionKeys;
                ///
                CVector<SQuatKeyf> rotationKeys;
                ///
                CVector<SVectorKeyf> scalingKeys;

            }; // struct SAnimationChannel
        } // namespace anim
    } // namespace gfx
} // namespace fg
    #undef FG_INC_GFX_ANIMATION_CHANNEL_BLOCK
#endif	/* FG_INC_GFX_ANIMATION_CHANNEL */
