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
 * File:   fgGfxBone.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 3:52 PM
 */

#ifndef FG_INC_GFX_BONE
    #define FG_INC_GFX_BONE
    #define FG_INC_GFX_BONE_BLOCK

    #include "Math/fgMathLib.h"
    #include "fgVector.h"

namespace fg {
    namespace gfx {
        namespace anim {

            /**
             *
             */
            struct SVertexWeight {
                typedef SVertexWeight self_type;
                typedef SVertexWeight type;

                ///
                int meshIdx;
                ///
                int vertexIdx;
                ///
                float weight;
                /**
                 *
                 */
                SVertexWeight() : meshIdx(0), vertexIdx(0), weight(0.0f) { }
                /**
                 * 
                 * @param _vertexIdx
                 * @param _weight
                 */
                SVertexWeight(int _vertexIdx, float _weight) :
                meshIdx(0), vertexIdx(_vertexIdx), weight(_weight) { }
                SVertexWeight(int _meshIdx, int _vertexIdx, float _weight) :
                meshIdx(_meshIdx), vertexIdx(_vertexIdx), weight(_weight) { }
                /**
                 *
                 * @param other
                 */
                SVertexWeight(const self_type& other) {
                    meshIdx = other.meshIdx;
                    vertexIdx = other.vertexIdx;
                    weight = other.weight;
                }
                /**
                 *
                 */
                virtual ~SVertexWeight() {
                    meshIdx = 0;
                    vertexIdx = 0;
                    weight = 0.0f;
                }
            }; // struct SVertexWeight

            /**
             *
             */
            enum BoneType {
                BONE_INVALID = 0,
                
                BONE_HEAD,
                BONE_NECK,

                BONE_ARM_LEFT,
                BONE_ARM_RIGHT,

                BONE_FOREARM_LEFT,
                BONE_FOREARM_RIGHT,

                BONE_HAND_LEFT,
                BONE_HAND_RIGHT,

                BONE_HAND_LEFT_THUMB,
                BONE_HAND_LEFT_FINGER1 = BONE_HAND_LEFT_THUMB,
                BONE_HAND_LEFT_FINGER2,
                BONE_HAND_LEFT_FINGER3,
                BONE_HAND_LEFT_FINGER4,
                BONE_HAND_LEFT_FINGER5,

                BONE_HAND_RIGHT_THUMB,
                BONE_HAND_RIGHT_FINGER1 = BONE_HAND_RIGHT_THUMB,
                BONE_HAND_RIGHT_FINGER2,
                BONE_HAND_RIGHT_FINGER3,
                BONE_HAND_RIGHT_FINGER4,
                BONE_HAND_RIGHT_FINGER5,

                BONE_SPINE,
                BONE_PELVIS,
                BONE_THIGH_LEFT,
                BONE_THIGH_RIGHT,
                BONE_LEG_LEFT,
                BONE_LEG_RIGHT,
                BONE_FOOT_LEFT,
                BONE_FOOT_RIGHT,

                BONE_FOOT_LEFT_TOE_BIG,
                BONE_FOOT_LEFT_TOE_HALLUX = BONE_FOOT_LEFT_TOE_BIG,
                BONE_FOOT_LEFT_TOE1 = BONE_FOOT_LEFT_TOE_BIG,
                BONE_FOOT_LEFT_TOE2,
                BONE_FOOT_LEFT_TOE3,
                BONE_FOOT_LEFT_TOE4,
                BONE_FOOT_LEFT_TOE5,

                BONE_FOOT_RIGHT_TOE_BIG,
                BONE_FOOT_RIGHT_TOE_HALLUX = BONE_FOOT_RIGHT_TOE_BIG,
                BONE_FOOT_RIGHT_TOE1 = BONE_FOOT_RIGHT_TOE_BIG,
                BONE_FOOT_RIGHT_TOE2,
                BONE_FOOT_RIGHT_TOE3,
                BONE_FOOT_RIGHT_TOE4,
                BONE_FOOT_RIGHT_TOE5,

                BONE_FACE_EXTRA,
                BONE_BACK_EXTRA,
                BONE_FRONT_EXTRA,
                BONE_LEFT_EXTRA,
                BONE_RIGHT_EXTRA,
                BONE_UP_EXTRA,
                BONE_DOWN_EXTRA,

                NUM_BONE_TYPES
            }; // enum BoneType

            /**
             *
             * @param text
             * @return
             */
            BoneType getBoneTypeFromText(const std::string& text);
            /**
             * 
             * @param text
             * @return
             */
            BoneType getBoneTypeFromText(const char* text);
            /**
             *
             * @param boneType
             * @return
             */
            const char* getTextFromBoneType(BoneType boneType);

            /**
             *
             */
            struct SBone {
                typedef SBone self_type;
                typedef SBone type;
                typedef CVector<SVertexWeight> WeightsVec;
                typedef WeightsVec::iterator WeightsVecItor;

                typedef CVector<SBone*> BonesVec;
                typedef BonesVec::iterator BonesVecItor;
                typedef BonesVec::const_iterator BonesVecConstItor;

                /**
                 *
                 */
                SBone();
                /**
                 *
                 * @param orig
                 */
                SBone(const SBone& orig);
                /**
                 *
                 */
                virtual ~SBone();

                //--------------------------------------------------------------

                /**
                 *
                 */
                void clear(void);

                /**
                 *
                 */
                void destroyChildren(void);

                /**
                 *
                 * @param name
                 * @return
                 */
                SBone* findBone(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                SBone* findBone(const char* name);

                /**
                 *
                 * @param pBone
                 * @return
                 */
                fgBool hasChild(SBone* pBone);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool hasChild(const std::string& name);
                /**
                 * 
                 * @param name
                 * @return
                 */
                fgBool hasChild(const char* name);

                /**
                 * 
                 * @param pBone
                 * @return
                 */
                fgBool removeChild(SBone* pBone);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool removeChild(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool removeChild(const char* name);

            public:
                ///
                BoneType mType;
                ///
                std::string name;
                ///
                self_type* pParent;
                ///
                int parentIdx;
                ///
                int index;
                ///
                Matrix4f bindPoseMatrix;
                ///
                Matrix4f offset;
                ///
                WeightsVec weights;
                ///
                BonesVec children;
            }; // struct SBone

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_BONE_BLOCK
#endif	/* FG_INC_GFX_BONE */
