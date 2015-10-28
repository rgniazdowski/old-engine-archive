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
 * File:   fgCollisionRagdollBody.h
 * Author: vigilant
 *
 * Created on October 10, 2015, 12:47 AM
 */

#ifndef FG_INC_RAGDOLL_COLLISION_BODY
    #define FG_INC_RAGDOLL_COLLISION_BODY
    #define FG_INC_RAGDOLL_COLLISION_BODY_BLOCK

    #include "Math/fgUniversalTransform.h"
    #include "fgBulletUniversalTransform.h"
    #include "Util/fgBTreeMap.h"

    #include "fgAbstractCollisionBody.h"
    #include "fgRagdollBoneType.h"
    #include "fgBoneSmallInfo.h"
    #include "fgCollisionBody.h"

namespace fg {
    namespace physics {

        /**
         *
         */
        struct SJointID : public std::pair<RagdollBoneType, RagdollBoneType> {
            typedef SJointID self_type;
            typedef std::pair<RagdollBoneType, RagdollBoneType> base_type;
            typedef RagdollBoneType bone_type;

        public:
            /**
             *
             */
            SJointID() {
                this->first = BONE_INVALID;
                this->second = BONE_INVALID;
            }
            /**
             *
             * @param a
             * @param b
             */
            SJointID(RagdollBoneType a, RagdollBoneType b) :
            base_type(a, b) { }
            SJointID(const self_type& orig) : base_type(orig) { }
            virtual ~SJointID() {
                this->first = BONE_INVALID;
                this->second = BONE_INVALID;
            }
            /**
             *
             */
            void flip(void) {
                bone_type tmp = this->first;
                this->first = this->second;
                this->second = tmp;
            }
            /**
             *
             * @param a
             * @param b
             * @return
             */
            fgBool check(RagdollBoneType a, RagdollBoneType b) const {
                return (fgBool)((this->first == a && this->second == b) ||
                        (this->first == b && this->second == a));
            }
            /**
             *
             * @param a
             * @param b
             * @param isFlipped
             * @return
             */
            fgBool check(RagdollBoneType a, RagdollBoneType b, fgBool* isFlipped) const {
                const fgBool status = (fgBool)(this->first == a && this->second == b);
                const fgBool flipped = (fgBool)(this->first == b && this->second == a);
                if(isFlipped)
                    *isFlipped = flipped;
                return (status || flipped);
            }
            /**
             * 
             * @return
             */
            fgBool isValid(void) const {
                return (fgBool)(this->first != BONE_INVALID && this->second != BONE_INVALID);
            }
        }; // struct SJointID
        inline _GLIBCXX_CONSTEXPR bool
        operator ==(const SJointID& __x, const SJointID& __y) {
            return ((__x.first == __y.first && __x.second == __y.second) ||
                    (__x.first == __y.second && __x.second == __y.first));
        }
        typedef SJointID JointID;

        /**
         *
         */
        struct SRagdollJointsInfo {
            typedef SRagdollJointsInfo self_type;
            typedef CVector<btTypedConstraint*> ConstraintsVec;
            typedef util::btree_map<JointID, ConstraintsVec> JointsMap;

            ///
            JointsMap jointsMap;
            /**
             * 
             */
            SRagdollJointsInfo() { }
            virtual ~SRagdollJointsInfo() { }
            JointsMap::iterator begin(void) {
                return jointsMap.begin();
            }
            JointsMap::const_iterator begin(void) const {
                return jointsMap.begin();
            }
            JointsMap::iterator end(void) {
                return jointsMap.end();
            }
            JointsMap::const_iterator end(void) const {
                return jointsMap.end();
            }
            void clear(void) {
                jointsMap.clear();
            }
            /**
             * 
             * @param jointID
             * @param pConstraint
             */
            void addConstraint(const JointID& jointID, btTypedConstraint* pConstraint) {
                JointsMap::iterator found = jointsMap.find(jointID);
                if(found != jointsMap.end()) {
                    if(!found->second.contains(pConstraint)) {
                        found->second.push_back(pConstraint);
                    }
                } else {
                    jointsMap[jointID].push_back(pConstraint);
                }
            }
            /**
             * 
             * @param jointID
             * @return
             */
            fgBool hasConstraint(const JointID& jointID) const {
                const JointID mirrorJointID(jointID.second, jointID.first);
                JointsMap::const_iterator found = jointsMap.find(jointID);
                if(found != jointsMap.end()) {
                    return FG_TRUE;
                } else {
                    found = jointsMap.find(mirrorJointID);
                    if(found != jointsMap.end())
                        return FG_TRUE;
                }
                return FG_FALSE;
            }
            /**
             * 
             * @return
             */
            unsigned int count(void) const {
                return jointsMap.size();
            }
            /**
             * 
             * @param jointID
             * @return
             */
            unsigned int count(const JointID& jointID) const {
                const JointID mirrorJointID(jointID.second, jointID.first);
                JointsMap::const_iterator found = jointsMap.find(jointID);
                if(found != jointsMap.end()) {
                    return found->second.size();
                } else {
                    found = jointsMap.find(mirrorJointID);
                    if(found != jointsMap.end())
                        return found->second.size();
                }
                return 0;
            }
            /**
             * 
             * @return
             */
            fgBool isEmpty(void) const {
                return (fgBool)jointsMap.empty();
            }
            /**
             * 
             * @param jointID
             * @param pConstraints
             */
            void getJoints(const JointID& jointID, ConstraintsVec* pConstraints) {
                if(!pConstraints)
                    return;
                const JointID mirrorJointID(jointID.second, jointID.first);
                JointsMap::const_iterator found = jointsMap.find(jointID);
                if(found != jointsMap.end()) {
                    pConstraints = &jointsMap[jointID];
                } else {
                    found = jointsMap.find(mirrorJointID);
                    if(found != jointsMap.end())
                        pConstraints = &jointsMap[mirrorJointID];
                }
            }
        }; // struct SRagdollJointsInfo
        //----------------------------------------------------------------------

        /**
         *
         */
        class CRagdollCollisionBody : public CAbstractCollisionBody {
        public:
            typedef CAbstractCollisionBody base_type;
            typedef CRagdollCollisionBody self_type;
            typedef CRagdollCollisionBody type;

            typedef CVector<SBoneSmallInfo> BonesInfoVec;
            typedef CVector<math::SUniversalTransform*> UniversalTransformsVec;
            typedef CVector<int> QuickBoneMapping;
            typedef CVector<CCollisionBody*> CollisionBodiesVec;

        protected:
            typedef CVector<unsigned int> BonesIdxVec;
            typedef util::btree_map<RagdollBoneType, BonesIdxVec> BonesTypeMap;
            typedef CVector<Matrix4f> MatricesVec;
            typedef CVector<btTypedConstraint*> ConstraintsVec;
            typedef util::btree_map<JointID, ConstraintsVec> JointsMap;

        public:
            /**
             *
             */
            CRagdollCollisionBody();
            /**
             *
             * @param orig
             */
            CRagdollCollisionBody(const CRagdollCollisionBody& orig);
            /**
             *
             */
            virtual ~CRagdollCollisionBody();

        public:
            static self_type* upcast(base_type* pBase) {
                if(!pBase)
                    return NULL;
                if(pBase->isRagdoll()) {
                    return static_cast<self_type*>(pBase);
                }
                return NULL;
            }
            static self_type const* upcast(base_type const* pBase) {
                if(!pBase)
                    return NULL;
                if(pBase->isRagdoll()) {
                    return static_cast<self_type const*>(pBase);
                }
                return NULL;
            }

        public:
            virtual CCollisionBox* getCollisionBox(void) const {
                return NULL;
            }
            virtual CCollisionSphere* getCollisionSphere(void) const {
                return NULL;
            }
            virtual CCollisionCapsule* getCollisionCapsule(void) const {
                return NULL;
            }
            //CCollisionComplex* getCollisionComplex(void) const;
            virtual CCollisionTriangleMesh* getCollisionTriangleMesh(void) const {
                return NULL;
            }
            virtual CRigidBody* getRigidBody(void) {
                return NULL; // there is no single rigid body -- need to get the array
            }
            virtual CRigidBody const* getRigidBody(void) const {
                return NULL;
            }
            virtual fgBool hasCollisionShape(void) const {
                return FG_FALSE;
            }
            virtual fgBool hasRigidBody(void) const {
                // this collision body does not have collision body
                return FG_FALSE;
            }
            virtual fgBool hasRigidBodies(void) const {
                return (fgBool)(!m_bones.empty()); // !!!!!!!!!!!!
            }
            virtual fgBool isBodyTypeCompatible(const BodyType bodyType) const {
                return (fgBool)(bodyType == BODY_RAGDOLL);
            }

        public:
            using base_type::setHalfSize;
            virtual void setHalfSize(const Vector3f& halfExtent);
            virtual void setRadius(const float radius);
            virtual void setHeight(const float height);
            virtual void setMass(float mass);

            using base_type::setLocalScaling;
            virtual void setLocalScaling(const Vector3f& scale);

        public:
            CollisionBodiesVec& getBoneBodies(void) {
                return m_bones;
            }
            CollisionBodiesVec const& getBoneBodies(void) const {
                return m_bones;
            }

            CCollisionBody* getBoneBody(unsigned int armatureBoneIndex, int* outIndex = NULL);
            CCollisionBody* getBoneBody(const char *name, int* outIndex = NULL);
            CCollisionBody* getBoneBody(RagdollBoneType boneType);

            CCollisionBody* getParentBoneBody(CCollisionBody* pBoneBody);
            CCollisionBody* getParentBoneBody(unsigned int armatureBoneIndex);
            CCollisionBody* getParentBoneBody(const char* name, int* outIndex = NULL);

        public:
            /**
             * 
             * @param bonesInfo         Vector containing list of bones to use for this ragdoll.
             *                          Uses special structure (SBoneSmallInfo) which contains
             *                          index, index of parent, start/end point, type, name, length...
             * @param armatureSize      Total armature size (not size of bonesInfo vector).
             *                          Used for mapping external bone indexes to bone rigid bodies.
             * @param initInRestPose    Whether or not should initialize bones and constraints
             *                          in rest pose. If set to FALSE (default) the ragdoll
             *                          will be initialized in generic T pose. This may not work
             *                          as expected for alien-like creatures that have more than
             *                          two legs or arms.
             * @return                  FG_TRUE if ragdoll was successfully initialized and is ready to use.
             *                          FG_FALSE otherwise.
             */
            fgBool initializeFrom(const BonesInfoVec& bonesInfo,
                                  unsigned int armatureSize,
                                  fgBool initInRestPose = FG_FALSE);

            void startRagdolling(void);
            void stopRagdolling(void);
            fgBool isRagdolling(void) const;

            void alignBone(unsigned int armatureBoneIndex,
                           const Vector3f& direction);
            void rotateBone(unsigned int armatureBoneIndex,
                            const Quaternionf& rotation);
            void rotateBone(unsigned int armatureBoneIndex,
                            const Vector3f& direction);

        public:
            math::SUniversalTransform* getUniversalTransform(unsigned int armatureBoneIndex);
            void getUniversalTransform(unsigned int armatureBoneIndex,
                                       Matrix4f& outMatrix);
            void setUniversalTransform(unsigned int armatureBoneIndex,
                                       const Matrix4f& inMatrix);
            void setModelMatrix(const Matrix4f& inMatrix) {
                m_modelMat = inMatrix;
            }
            Matrix4f& getModelMatrix(void) {
                return m_modelMat;
            }
            Matrix4f const& getModelMatrix(void) const {
                return m_modelMat;
            }
            BonesInfoVec& getBonesInfo(void) {
                return m_bonesInfo;
            }
            BonesInfoVec const& getBonesInfo(void) const {
                return m_bonesInfo;
            }
            SRagdollJointsInfo& getJointsInfo(void) {
                return m_joints;
            }
            SRagdollJointsInfo const& getJointsInfo(void) const {
                return m_joints;
            }
            MatricesVec& getInitialTransforms(void) {
                return m_initialTransforms;
            }
            MatricesVec const& getInitialTransforms(void) const {
                return m_initialTransforms;
            }

            /**
             * Sets initial transform of bone rigid body based on local bone transformation.
             * @param armatureBoneIndex Index of the bone
             * @param inBoneMatrix      Local bone transformation matrix
             */
            void setInitialTransform(unsigned int armatureBoneIndex,
                                     const Matrix4f& inBoneMatrix);

            /**
             * This function will set the initial transformations to default.
             * In most cases this will mean rest pose of the model.
             */
            void setDefaultInitialTransforms(void);

        protected:
            fgBool helper_initializeJoint(const RagdollBoneType boneA,
                                          const RagdollBoneType boneB = BONE_INVALID);

            fgBool helper_initializeBone(unsigned int bodyBoneIndex,
                                         const Vec3f& position,
                                         const Quatf& rotation);
            inline fgBool helper_initializeBone(unsigned int bodyBoneIndex,
                                                const Vec3f& position,
                                                const Vec3f& direction) {
                return helper_initializeBone(bodyBoneIndex,
                                             position,
                                             math::rotation(Vec3f(0.0f, 1.0f, 0.0f),
                                                            math::normalize(direction)));
            }

        protected:
            virtual void setupBody(void) {
                setupBody(BODY_RAGDOLL);
            }
            virtual void setupBody(BodyType bodyType);

        protected:
            fgBool addRigidBodiesToOwner(void);
            fgBool removeRigidBodiesFromOwner(void);
            fgBool destroyBones(void);

            fgBool registerJoints(void);
            fgBool unregisterJoints(void);
            fgBool destroyJoints(void);

            fgBool destroyData(void);

        private:
            /// Vector containing collision bodies for all bones in this ragdoll.
            CollisionBodiesVec m_bones;
            /// Vector containing small info for every bone (length, end points, etc.).
            BonesInfoVec m_bonesInfo;
            /// Universal transforms for every bone.
            /// Note that indexing in this array is based on bone armature index.
            UniversalTransformsVec m_transforms;
            /// Contains indexes pointing to bone rigid bodies.
            /// boneGlobal(Armature)index => bone collision body index
            QuickBoneMapping m_boneMapping;
            /// Contains mapping of bone types to bone indexes within
            /// this collision body (meaning that index saved in the map points
            /// to 'm_bones' or 'm_bonesInfo' vector).
            BonesTypeMap m_typeMapping;
            /// Initial transformation matrices for each bone in this ragdoll body.
            MatricesVec m_initialTransforms;
            /// Initial rotations for each bone (rest pose in default)
            CVector<Vector3f> m_initialRotations;
            /// Model matrix - from which to start ragdolling
            Matrix4f m_modelMat;
            /// Complete joint information.
            SRagdollJointsInfo m_joints;
            /// Total mass of the ragdoll body. Mass of each bone body is
            /// proportional based on bone length and total length of all bones.
            float m_mass;
            /// Is currently ragdolling? (bodies and constraints/joints added
            /// to the owner world and activated).
            fgBool m_isRagdolling;
        }; // class CRagdollCollisionBody

    } // namespace physics
} // namespace fg

    #undef FG_INC_RAGDOLL_COLLISION_BODY_BLOCK
#endif	/* FG_INC_COLLISION_RAGDOLL_BODY */
