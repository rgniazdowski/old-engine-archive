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
    #include "Math/fgDualQuaternion.h"
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

                time_type elapsed;
                value_type value;
                SVectorKeyT() : elapsed(0.0f), value() { }
                SVectorKeyT(const self_type& orig) {
                    this->elapsed = orig.elapsed;
                    this->value = orig.value;
                }
                SVectorKeyT(time_type _elapsed, const value_type& _value) :
                elapsed(_elapsed),
                value(_value) { }
                virtual ~SVectorKeyT() {
                    value = value_type();
                    elapsed = (time_type)0;
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

                time_type elapsed;
                value_type value;
                SQuatKeyT() : elapsed(0.0f), value() { }
                SQuatKeyT(time_type _elapsed, const value_type& _value) : elapsed(_elapsed), value(_value) { }
                virtual ~SQuatKeyT() {
                    value = value_type();
                    elapsed = (time_type)0;
                }
            }; // struct SQuatKeyT<T>

            typedef SQuatKeyT<float> SQuatKeyf;
            typedef SQuatKeyf SRotationKeyf;

            template<typename T>
            struct SMatrixKeyT {
                typedef SMatrixKeyT<T> self_type;
                typedef float time_type;
                typedef typename Matrix4T<T>::type value_type;

                time_type elapsed;
                value_type value;
                SMatrixKeyT() : elapsed(0.0f), value() { }
                SMatrixKeyT(time_type _elapsed, const value_type& _value) : elapsed(_elapsed), value(_value) { }
                virtual ~SMatrixKeyT() {
                    value = value_type();
                    elapsed = (time_type)0;
                }
            }; // struct SMatrixKeyT<T>

            typedef SMatrixKeyT<float> SMatrixKeyf;

            template<typename T>
            struct SDualQuatKeyT {
                typedef SDualQuatKeyT<T> self_type;
                typedef float time_type;
                typedef typename DualQuaternionT<T, math::precision::defaultp>::type value_type;

                time_type elapsed;
                value_type value;
                SDualQuatKeyT() : elapsed(0.0f), value() { }
                SDualQuatKeyT(time_type _elapsed, const value_type& _value) :
                elapsed(_elapsed), value(_value) { }
                virtual ~SDualQuatKeyT() {
                    value = value_type();
                    elapsed = (time_type)0;
                }
            }; // struct SDualQuatKeyT<T>

            typedef SDualQuatKeyT<float> SDualQuatKeyf;

            /**
             *
             */
            struct SAnimationChannel {
                typedef SAnimationChannel self_type;
                typedef SAnimationChannel type;

                typedef CVector<SVectorKeyf> PositionKeys;
                typedef CVector<SQuatKeyf> RotationKeys;
                typedef CVector<SVectorKeyf> ScalingKeys;
                typedef CVector<SMatrixKeyf> MatrixKeys;
                typedef CVector<SDualQuatKeyf> DualQuatKeys;

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
                void getPositionInterpolated(Vector3f& result,
                                             float currentTime = 0.0f);
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
                void getScaleInterpolated(Vector3f& result,
                                          float currentTime = 0.0f);
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
                void getRotationInterpolated(Quaternionf& result,
                                             float currentTime = 0.0f);
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
                void getMatrixInterpolated(Matrix4f& result,
                                           float currentTime = 0.0f);
                /**
                 *
                 * @param currentTime
                 * @return
                 */
                Matrix4f getMatrixInterpolated(float currentTime = 0.0f);

                //--------------------------------------------------------------

                void getDualQuaternion(DualQuaternionf& result,
                                       float currentTime = 0.0f);

                DualQuaternionf getDualQuaternion(float currentTime = 0.0f);

                //--------------------------------------------------------------

                void getDualQuaternionInterpolated(DualQuaternionf& result,
                                                   float currentTime = 0.0f);

                /**
                 *
                 * @param currentTime
                 * @return
                 */
                DualQuaternionf getDualQuaternionInterpolated(float currentTime = 0.0f);

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
                inline void get(Matrix4f& outMatrix,
                                float currentTime = 0.0f) {
                    getMatrix(outMatrix, currentTime);
                }
                inline void get(DualQuaternionf& outDQ,
                                float currentTime = 0.0f) {
                    getDualQuaternion(outDQ, currentTime);
                }

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
                inline void getInterpolated(Matrix4f& outMatrix,
                                            float currentTime = 0.0f) {
                    getMatrixInterpolated(outMatrix, currentTime);
                }
                inline void getInterpolated(DualQuaternionf& outDQ,
                                            float currentTime = 0.0f) {
                    getDualQuaternionInterpolated(outDQ, currentTime);
                }

                //--------------------------------------------------------------

                /**
                 *
                 */
                void clearKeys(void);

                /**
                 *
                 */
                void bake(fgBool force = FG_FALSE);
                fgBool isBaked(void) const {
                    return m_isBaked;
                }
                fgBool shouldBakeDQ(void) const {
                    return m_shouldBakeDQ;
                }
                void setBakeDQ(const fgBool toggle) {
                    m_shouldBakeDQ = toggle;
                }

            public:
                ///
                std::string targetName;
                ///
                PositionKeys positionKeys;
                ///
                RotationKeys rotationKeys;
                ///
                ScalingKeys scalingKeys;
                /// special matrix keys (pre-baked)
                MatrixKeys matrixKeys;
                /// special dual quaternion keys (pre-baked - for faster retrieval)
                /// to have it accessible - need to call bake()
                DualQuatKeys dualQuatKeys;

            protected:
                fgBool m_isBaked;
                fgBool m_shouldBakeDQ;

            }; // struct SAnimationChannel

        } // namespace anim
    } // namespace gfx
} // namespace fg
    #undef FG_INC_GFX_ANIMATION_CHANNEL_BLOCK
#endif /* FG_INC_GFX_ANIMATION_CHANNEL */
