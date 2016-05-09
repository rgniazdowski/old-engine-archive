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
 * File:   fgGfxSkinnedMesh.h
 * Author: vigilant
 *
 * Created on September 3, 2015, 9:16 PM
 */

#ifndef FG_INC_GFX_SKINNED_MESH
    #define FG_INC_GFX_SKINNED_MESH
    #define FG_INC_GFX_SKINNED_MESH_BLOCK

    #include "fgGfxMesh.h"
    #include "Animation/fgGfxBone.h"
    #include "Animation/fgGfxBlendingInfo.h"

namespace fg {
    namespace gfx {

        namespace anim {
            class CAnimation;
            struct SAnimationFrameInfo;
            struct SAnimationInfo;
        } // namespace anim

        struct SSkinnedMesh {
            typedef SSkinnedMesh self_type;
            typedef SSkinnedMesh type;

            typedef Vector4f blend_vec_element_type;

            typedef CVector<Matrix4f> MatrixVec;
            typedef CVector<DualQuaternionf> DualQuatsVec;

            typedef CVector<Vector4f> BlendVec;
            typedef BlendVec::iterator BlendVecItor;
            typedef BlendVec::const_iterator BlendVecConstItor;

            typedef CVector<anim::SBone*> BonesVec;
            typedef BonesVec::iterator BonesVecItor;
            typedef BonesVec::const_iterator BonesVecConstItor;

            typedef CVector<AABoundingBox3Df> BoneBoxesVec;
            typedef BoneBoxesVec::iterator BoneBoxesVecItor;
            typedef BoneBoxesVec::const_iterator BoneBoxesVecConstItor;

            /**
             * This is not a bounding box.
             * Structure holds information about two points that are
             * closest to mesh AABB edges; Values are exact.
             * While merging the length is compared.
             */
            struct SEdgeInfo {

                enum {
                    /// Positive X (max)
                    PX = 0,
                    /// Negative X (min)
                    NX = 1,
                    /// Positive Y (max)
                    PY = 2,
                    /// Negative Y (min)
                    NY = 3,
                    /// Positive Z (max)
                    PZ = 4,
                    /// Negative Z (min)
                    NZ = 5
                };

                /**
                 * Structure for edge point of the bone
                 */
                struct SEdgePoint {
                    /// index of the point (vertex) in this mesh
                    int index;
                    ///
                    float length;
                    /// Position of the edge point (value))
                    Vector3f value;
                    /**
                     * Default constructor
                     */
                    SEdgePoint() : index(-1), length(0.0f), value() { }
                } points[6];
                /**
                 * Default constructor
                 */
                SEdgeInfo() {
                    invalidate();
                }
                /**
                 * Copy constructor
                 * @param orig
                 */
                SEdgeInfo(const SEdgeInfo& orig) {
                    for(unsigned int i = 0; i < 6; i++) {
                        points[i].index = orig.points[i].index;
                        points[i].length = orig.points[i].length;
                        points[i].value = orig.points[i].value;
                    }
                }
                /**
                 * Merge given point with this edge info.
                 * @param index Index of the point/vertex
                 * @param value Position of the point to merge
                 */
                void merge(int index, const Vector3f& value);
                /**
                 * Reset all data.
                 */
                void invalidate(void);
                /**
                 * Transform this edge info based on the given transformation matrices.
                 * @param pMesh         Pointer to the skinned mesh structure that owns this edge information
                 * @param matrices      Vector with transformation matrices - indexing with local bones
                 * @param outputMin     Reference to the transformed output value (minimum point of aabb)
                 * @param outputMax     Reference to the transformed output value (maximum point of aabb)
                 */
                void transform(SSkinnedMesh* pMesh,
                               const MatrixVec& matrices,
                               Vector3f& outputMin,
                               Vector3f& outputMax);

                void transform(SSkinnedMesh* pMesh,
                               const DualQuatsVec& dquats,
                               Vector3f& outputMin,
                               Vector3f& outputMax);

                void transform(SSkinnedMesh* pMesh,
                               const MatrixVec& matrices,
                               Vector3f* output);

                void transform(SSkinnedMesh* pMesh,
                               const DualQuatsVec& dquats,
                               Vector3f* output);
            }; // struct SEdgePointInfo

            typedef CVector<SEdgeInfo> BoneEdgesVec;
            typedef BoneEdgesVec::iterator BoneEdgesVecItor;
            typedef BoneEdgesVec::const_iterator BoneEdgesVecConstItor;

        protected:
            virtual unsigned short internal_getBlendWeightsVboArrayIdx(void) const;
            virtual unsigned short internal_getBlendIndicesVboArrayIdx(void) const;

        public:
            /// Global mesh index (based on meshes inside the model)
            unsigned int meshIndex;
            /// Local bone list for this skinned mesh.
            /// Not every bone from the armature need to affect this mesh.
            BonesVec bones;            
            /// Vector with blending weights (for each vertex - 4 floats)
            BlendVec blendWeights;
            /// Vector with blending indices (for each vertex - 4 floats)
            BlendVec blendIndices;
            /// Bones' AABB boxes for this mesh.
            BoneBoxesVec boneBoxes;
            /// Bones' edge information
            BoneEdgesVec boneEdges;
            /// Custom blending info for bones attached to this mesh.
            /// Blending info is an array with special structures. Each contains
            /// animation pair and a list of weights (proportions for each bone).
            /// This blending info instance will contain weights indexed locally.
            anim::SBlendingInfo blendingInfo;

            /**
             * Default constructor.
             */
            SSkinnedMesh();

            /**
             * Default destructor.
             */
            virtual ~SSkinnedMesh();

            /**
             * 
             * @return 
             */
            virtual SMeshSoA* getMeshSoA(void) = 0;
            /**
             *
             * @return
             */
            virtual SMeshAoS* getMeshAoS(void) = 0;
            /**
             *
             * @return
             */
            virtual SMeshBase* getMeshBase(void) = 0;

            /**
             *
             * @return
             */
            virtual const SMeshSoA* getMeshSoA(void) const = 0;
            /**
             *
             * @return
             */
            virtual const SMeshAoS* getMeshAoS(void) const = 0;
            /**
             *
             * @return
             */
            virtual const SMeshBase* getMeshBase(void) const = 0;

            /**
             *
             */
            void clearSkinningInfo(void);

            /**
             *
             * @param armatureInfo
             */
            virtual void initSkinningInfo(const anim::SBlendingInfo& armatureInfo) = 0;

            /**
             * Helper function for calculating current animation frame             
             * @param frameInfo     Reference to special animation info structure
             * @param elapsed       Elapsed time (since app init) - not animation time
             */
            void calculate(anim::SAnimationInfo& animationInfo,
                           float delta = 0.0f);

            fgBool isAnimationCompatible(const anim::CAnimation* pAnimation) const;

            /**
             * This function matches bones to given axis-aligned bounding box.
             * Returns only the bones that are fully inside.
             * Matching is based on the mesh (and bones) in bind-pose.
             * @param aabb          AABB to which match the bones.
             * @param matchedBones  Vector with pointers to matched bones. It will
             *                      be cleared before first insertion.
             * @param fuzzyEdge     Fraction from 0.0 to 1.0 telling how much
             *                      error is allowed (where 1.0 is 100%)
             * @return              Number of found bones.
             */
            unsigned int matchBones(const AABoundingBox3Df& aabb,
                                    BonesVec& matchedBones,
                                    float fuzzyEdge = 0.0f) const;
            /**
             *
             * @param aabb
             * @param matchedBones
             * @param fuzzyEdge
             * @return
             */
            unsigned int matchBones(const AABoundingBox3Df& aabb,
                                    CVector<unsigned int>& matchedBones,
                                    float fuzzyEdge = 0.0f) const;


            unsigned int matchBonesPrecise(const AABoundingBox3Df& aabb,
                                            BonesVec& matchedBones) const;

            unsigned int matchBonesPrecise(const AABoundingBox3Df& aabb,
                                           CVector<unsigned int>& matchedBones) const;

            /**
             *
             * @param boneIdx   Bone index for this skinned mesh (not armature)
             * @param pointID   Point to transform. One of 6 edge points of given bone.
             * @param matrices  Transformation matrices corresponding to this mesh
             * @param output    Transformed point in 3D space.
             */
            void transformPoint(int boneIdx,
                                unsigned int pointID,
                                const MatrixVec& matrices,
                                Vector3f& output);

            inline void transformPoint(const anim::SBone* pBone,
                                       unsigned int pointID,
                                       const MatrixVec& matrices,
                                       Vector3f& output) {
                transformPoint(getBoneIndex(pBone), pointID,
                               matrices, output);
            }
            inline void transformPoint(const std::string& boneName,
                                       unsigned int pointID,
                                       const MatrixVec& matrices,
                                       Vector3f& output) {
                transformPoint(getBoneIndex(boneName), pointID,
                               matrices, output);
            }

            /**
             *
             * @param boneIdx   Bone index for this skinned mesh (not armature)
             * @param pointID   Point to transform. One of 6 edge points of given bone.
             * @param dquats    Transformations corresponding to this mesh
             * @param output    Transformed point in 3D space.
             */
            void transformPoint(int boneIdx,
                                unsigned int pointID,
                                const DualQuatsVec& dquats,
                                Vector3f& output);
            inline void transformPoint(const anim::SBone* pBone,
                                       unsigned int pointID,
                                       const DualQuatsVec& dquats,
                                       Vector3f& output) {
                transformPoint(getBoneIndex(pBone), pointID,
                               dquats, output);
            }
            inline void transformPoint(const std::string& boneName,
                                       unsigned int pointID,
                                       const DualQuatsVec& dquats,
                                       Vector3f& output) {
                transformPoint(getBoneIndex(boneName), pointID,
                               dquats, output);
            }

            int getBoneIndex(const std::string& boneName) const;
            int getBoneIndex(const anim::SBone* pBone) const;


        protected:
            /**
             *
             */
            void clear(SMeshBase* pMeshSuper);

            /**
             *
             */
            void initSkinningInfo(const anim::SBlendingInfo& armatureInfo,
                                  SMeshBase* pMeshSuper);
            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean refreshAttributes(const SMeshBase* pMeshSuper,
                                           SAttributeData* pDataArray) const;
            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean setupAttributes(const SMeshBase* pMeshSuper,
                                         SAttributeData* pDataArray) const;

            /**
             *
             * @return
             */
            fgGFXboolean genBuffers(SMeshBase* pMeshSuper);

        }; // struct SSkinnedMesh

        /**
         * Skinned Mesh Structure of Arrays version.
         * This structure extends base mesh SoA and SkinnedMesh base.
         */
        struct SSkinnedMeshSoA : public SMeshSoA, public SSkinnedMesh {
        public:
            typedef SSkinnedMeshSoA self_type;
            typedef SSkinnedMeshSoA type;
            typedef SMeshSoA base_type;
            typedef SSkinnedMesh skinned_base_type;

            /**
             *
             */
            SSkinnedMeshSoA();
            /**
             *
             */
            virtual ~SSkinnedMeshSoA();
            /**
             *
             * @return
             */
            virtual fgBool isSkinnedMesh(void) const {
                return FG_TRUE;
            }

            /**
             *
             * @return
             */
            virtual SMeshSoA* getMeshSoA(void);
            /**
             *
             * @return
             */
            virtual SMeshAoS* getMeshAoS(void);
            /**
             *
             * @return
             */
            virtual SMeshBase* getMeshBase(void);

            /**
             *
             * @return
             */
            virtual const SMeshSoA* getMeshSoA(void) const;
            /**
             *
             * @return
             */
            virtual const SMeshAoS* getMeshAoS(void) const;
            /**
             *
             * @return
             */
            virtual const SMeshBase* getMeshBase(void) const;

            /**
             *
             */
            virtual void clear(void);

            /**
             *
             * @param pDataArray
             * @return
             */
            virtual fgGFXboolean refreshAttributes(SAttributeData* pDataArray) const;
            /**
             *
             * @param pDataArray
             * @return
             */
            virtual fgGFXboolean setupAttributes(SAttributeData* pDataArray) const;
            /**
             *
             * @return
             */
            virtual fgGFXboolean genBuffers(void);
            /**
             * 
             */
            virtual void initSkinningInfo(const anim::SBlendingInfo& armatureInfo);
            /**
             * 
             * @return
             */
            virtual AttributeMask attribMask(void) const {
                return base_type::attribMask() | ATTRIBUTE_BLEND_WEIGHTS_BIT | ATTRIBUTE_BLEND_INDICES_BIT;
            }

        protected:
            /**
             *
             * @return
             */
            virtual unsigned short internal_getBlendWeightsVboArrayIdx(void) const;
            /**
             * 
             * @return
             */
            virtual unsigned short internal_getBlendIndicesVboArrayIdx(void) const;

        }; // SSkinnedMeshSoA

        /**
         *
         */
        struct SSkinnedMeshAoS : public SMeshAoS, public SSkinnedMesh {
        public:
            typedef SSkinnedMeshAoS self_type;
            typedef SSkinnedMeshAoS type;
            typedef SMeshAoS base_type;
            typedef SSkinnedMesh skinned_base_type;

            /**
             *
             */
            SSkinnedMeshAoS();
            /**
             *
             * @param vertexType
             */
            SSkinnedMeshAoS(VertexType vertexType);
            /**
             *
             * @param attribMask
             */
            SSkinnedMeshAoS(AttributeMask attribMask);
            /**
             * 
             */
            virtual ~SSkinnedMeshAoS();
            /**
             *
             * @return
             */
            virtual fgBool isSkinnedMesh(void) const {
                return FG_TRUE;
            }

            /**
             *
             * @return
             */
            virtual SMeshSoA* getMeshSoA(void);
            /**
             *
             * @return
             */
            virtual SMeshAoS* getMeshAoS(void);
            /**
             *
             * @return
             */
            virtual SMeshBase* getMeshBase(void);

            /**
             *
             * @return
             */
            virtual const SMeshSoA* getMeshSoA(void) const;
            /**
             *
             * @return
             */
            virtual const SMeshAoS* getMeshAoS(void) const;
            /**
             *
             * @return
             */
            virtual const SMeshBase* getMeshBase(void) const;

            /**
             *
             */
            virtual void clear(void);

            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean refreshAttributes(SAttributeData* pDataArray) const;
            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean setupAttributes(SAttributeData* pDataArray) const;

            /**
             *
             * @return
             */
            fgGFXboolean genBuffers(void);

            /**
             *
             */
            virtual void initSkinningInfo(const anim::SBlendingInfo& armatureInfo);
            /**
             *
             * @return
             */
            virtual AttributeMask attribMask(void) const {
                return base_type::attribMask() | ATTRIBUTE_BLEND_WEIGHTS_BIT | ATTRIBUTE_BLEND_INDICES_BIT;
            }

        protected:
            virtual unsigned short internal_getBlendWeightsVboArrayIdx(void) const;
            virtual unsigned short internal_getBlendIndicesVboArrayIdx(void) const;

        }; // SSkinnedMeshAoS

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SKINNED_MESH_BLOCK
#endif /* FG_INC_GFX_SKINNED_MESH */
