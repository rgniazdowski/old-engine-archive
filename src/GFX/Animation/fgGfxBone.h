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
    #include "Math/fgDualQuaternion.h"
    #include "fgVector.h"
    #include "Physics/fgRagdollBoneType.h"
    #include "Physics/fgBoneSmallInfo.h"

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

            // mapping physics ragdoll bone type to standard animation bone type
            // this can be used even with physics turned off
            typedef physics::RagdollBoneType BoneType;

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
            struct SBone : public physics::SBoneSmallInfo {
                typedef physics::SBoneSmallInfo base_type;
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
                SBone(const self_type& orig);
                /**
                 *
                 */
                virtual ~SBone();

                //--------------------------------------------------------------
                /**
                 * 
                 * @return
                 */
                base_type& getBoneSmallInfo(void) {
                    return (*this);
                }
                /**
                 *
                 * @return
                 */
                base_type const& getBoneSmallInfo(void) const {
                    return (*this);
                }
                /**
                 *
                 * @param outBoneInfo
                 */
                void getBoneSmallInfo(base_type& outBoneInfo) const {
                    outBoneInfo = *((base_type*)this);
                }
                /**
                 *
                 * @param inBoneInfo
                 */
                void setBoneSmallInfo(const base_type& inBoneInfo) {
                    this->boneType = inBoneInfo.boneType;
                    this->name.clear();
                    this->name.append(inBoneInfo.name);
                    this->parentIdx = inBoneInfo.parentIdx;
                    this->index = inBoneInfo.index;
                    this->length = inBoneInfo.length;
                    this->startPoint = inBoneInfo.startPoint;
                    this->endPoint = inBoneInfo.endPoint;
                }
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

                /**
                 *
                 * @param outMatrix
                 */
                void getFinalBindPose(Matrix4f& outMatrix) const;
                /**
                 *
                 * @param outDQuat
                 */
                void getFinalBindPose(DualQuaternionf& outDQuat) const;

                /**
                 *
                 * @param outMatrix
                 */
                inline void getFinalRestPose(Matrix4f& outMatrix) const {
                    outMatrix = math::inverse(this->offset);
                }
                /**
                 *
                 * @param outDQuat
                 */
                inline void getFinalRestPose(DualQuaternionf& outDQuat) const {
                    // what about scaling? dual quaternion is just for rigid transformations
                    outDQuat.initializeFrom(math::inverse(this->offset));
                }
                /**
                 * 
                 * @param outMatrix
                 * @param outScale
                 */
                inline void getFinalRestPose(Matrix4f& outMatrix, Vector3f& outScale) const {
                    outMatrix = math::inverse(this->offset);
                    this->getOffsetScale(outScale);
                }
                /**
                 *
                 * @param outDQuat
                 * @param outScale
                 */
                inline void getFinalRestPose(DualQuaternionf& outDQuat, Vector3f& outScale) const {
                    this->getFinalRestPose(outDQuat);
                    this->getOffsetScale(outScale);
                }
                /**
                 *
                 * @return
                 */
                Vector3f getOffsetScale(void) const;
                /**
                 * 
                 * @param outScale
                 */
                void getOffsetScale(Vector3f& outScale) const;
                /**
                 *
                 * @return
                 */
                inline fgBool isLeaf(void) const {
                    return (fgBool)children.empty();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isFirstChild(void) const {
                    if(!pParent)
                        return FG_FALSE;
                    if(!pParent->hasChildren())
                        return FG_FALSE;
                    if(pParent->children[0] == this)
                        return FG_TRUE;
                    return FG_FALSE;
                }
                /**
                 *
                 * @param direction
                 */
                void getDirectionFromParent(Vector3f& direction) const;
                /**
                 * 
                 * @return
                 */
                Vector3f getDirectionFromParent(void) const;

                /**
                 *
                 */
                void refreshLength(void);
                /**
                 * 
                 * @return
                 */
                fgBool hasLength(void) const;
                /**
                 * 
                 * @return 
                 */
                unsigned int count(void) const {
                    return children.size();
                }
                /**
                 * 
                 * @return 
                 */
                fgBool hasChildren(void) const {
                    return (fgBool)!children.empty();
                }

            public:
                /// Pointer to parent bone
                self_type* pParent;
                /// Initial node transformation
                Matrix4f bindPoseMatrix;
                /// Offset matrix, which converts from the local mesh space, back to bone-space.
                Matrix4f offset;
                /// Weights vector (also for more than one mesh)
                WeightsVec weights;
                /// List of children bones
                BonesVec children;
            }; // struct SBone

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_BONE_BLOCK
#endif	/* FG_INC_GFX_BONE */
