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

    #include "Math/fgVector3.h"
    #include "Math/fgMatrix4.h"
    #include "Math/fgQuaternion.h"
    #include "Math/fgDualQuaternion.h"
    #include "fgVector.h"
    #include "fgEnumFlags.h"

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
            public:
                typedef SAnimationChannel self_type;
                typedef SAnimationChannel type;

                typedef CVector<SVectorKeyf> PositionKeys;
                typedef CVector<SQuatKeyf> RotationKeys;
                typedef CVector<SVectorKeyf> ScalingKeys;
                typedef CVector<SMatrixKeyf> MatrixKeys;
                typedef CVector<SDualQuatKeyf> DualQuatKeys;

                enum StateFlags {
                    /// No current flags set
                    NO_FLAGS = 0x0000,
                    /// All keys are ready (faster lookup) and matrices and/or
                    /// dual quaternions are ready for really fast lookup.
                    BAKED = 0x0001,
                    /// Keys are ready for faster lookup (pre-baked).
                    KEYS_FASTER_LOOKUP = 0x0002,
                    /// Should bake matrices
                    BAKE_MATRICES = 0x0004,
                    /// Should bake dual quaternions
                    BAKE_DQS = 0x0008
                }; // enum StateFlags

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

                //--------------------------------------------------------------

                /**
                 *
                 * @param result
                 * @param currentTime
                 */
                void getMatrix(Matrix4f& result, float currentTime = 0.0f);

                //--------------------------------------------------------------

                /**
                 *
                 * @param result
                 * @param currentTime
                 */
                void getMatrixInterpolated(Matrix4f& result,
                                           float currentTime = 0.0f);                

                //--------------------------------------------------------------

                void getDualQuaternion(DualQuaternionf& result,
                                       float currentTime = 0.0f);

                //--------------------------------------------------------------

                void getDualQuaternionInterpolated(DualQuaternionf& result,
                                                   float currentTime = 0.0f);

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
                 * @param outMatrix
                 * @param currentTime
                 */
                inline void get(Matrix4f& outMatrix,
                                float currentTime = 0.0f) {
                    getMatrix(outMatrix, currentTime);
                }
                /**
                 *
                 * @param outDQ
                 * @param currentTime
                 */
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
                /**
                 * 
                 * @param outMatrix
                 * @param currentTime
                 */
                inline void getInterpolated(Matrix4f& outMatrix,
                                            float currentTime = 0.0f) {
                    getMatrixInterpolated(outMatrix, currentTime);
                }
                /**
                 *
                 * @param outDQ
                 * @param currentTime
                 */
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
                /**
                 *
                 * @return
                 */
                fgBool isBaked(void) const {
                    return (fgBool)!!(m_stateFlags & BAKED);
                }
                /**
                 *
                 * @param toggle
                 */
                void setBakeDQs(const fgBool toggle = FG_TRUE) {
                    setFlag(BAKE_DQS, toggle);
                }
                /**
                 * 
                 * @return
                 */
                fgBool shouldBakeDQs(void) const {
                    return (fgBool)!!(m_stateFlags & BAKE_DQS);
                }
                /**
                 * 
                 * @param toggle
                 */
                void setBakeMatrices(const fgBool toggle = FG_TRUE) {
                    setFlag(BAKE_MATRICES, toggle);
                }
                /**
                 * 
                 * @return
                 */
                fgBool shouldBakeMatrices(void) const {
                    return (fgBool)!!(m_stateFlags & BAKE_MATRICES);
                }
                /**
                 *
                 * @return
                 */
                fgBool isFasterLookup(void) const {
                    return (fgBool)!!(m_stateFlags & KEYS_FASTER_LOOKUP);
                }

            protected:
                void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);                

            public:
                /// Target node name - for reference.
                std::string targetName;
                /// All position keys (stored as float vectors)
                PositionKeys positionKeys;
                /// All rotation keys
                RotationKeys rotationKeys;
                /// All scaling keys
                ScalingKeys scalingKeys;
                /// Special matrix keys (pre-baked - for faster retrieval)
                MatrixKeys matrixKeys;
                /// Special dual quaternion keys (pre-baked - for faster retrieval)
                /// to have it accessible - need to call bake()
                DualQuatKeys dualQuatKeys;

            protected:
                /// Current state flags - various on/off options.
                StateFlags m_stateFlags;

            }; // struct SAnimationChannel

            FG_ENUM_FLAGS(SAnimationChannel::StateFlags);

            inline void SAnimationChannel::setFlag(const StateFlags flags, const fgBool toggle) {
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
    #undef FG_INC_GFX_ANIMATION_CHANNEL_BLOCK
#endif /* FG_INC_GFX_ANIMATION_CHANNEL */
