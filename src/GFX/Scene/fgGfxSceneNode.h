/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_SCENE_NODE
    #define FG_INC_GFX_SCENE_NODE
    #define FG_INC_GFX_SCENE_NODE_BLOCK

    #include "Math/fgMathLib.h"
    #include "Util/fgTag.h"
    #include "GFX/fgGfxAABoundingBox.h"
    #include "GFX/fgGfxBoundingVolume.h"

    #include "GFX/fgGfxDrawable.h"
    #include "GFX/fgGfxAnimated.h"
    #include "GFX/fgGfxDrawCall.h"
    #include "fgGfxTreeNodeObject.h"

    #include "Physics/fgCollisionBody.h"

    #include <set>

namespace fg {
    namespace gfx {
        class CSceneNode;
    }
}

    #define FG_TAG_GFX_SCENE_NODE_NAME  "GfxSceneNode"
    #define FG_TAG_GFX_SCENE_NODE       FG_TAG_TYPE(fg::gfx::CSceneNode)
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CSceneNode, FG_TAG_GFX_SCENE_NODE_NAME);

namespace fg {

    namespace resource {
        template<typename THandleType> class CManagedObject;
    };

    namespace gfx {

        /// Tag type for the Scene Node
        typedef FG_TAG_GFX_SCENE_NODE SceneNodeTag;
        /// Special handle type for gfx object (scene object)
        typedef fg::util::CHandle<SceneNodeTag> SceneNodeHandle;

        ///
        typedef unsigned int SceneNodeType;

        /// Invalid scene node - initial value
        const SceneNodeType SCENE_NODE_INVALID = 0;
        /// This is a special SceneNode type - it's for specifying root nodes
        const SceneNodeType SCENE_NODE_ROOT = 1;
        /// Custom scene node - it is still drawable but relies on custom
        /// draw call type to draw something - meaning that this utilizes
        /// custom vertex data
        const SceneNodeType SCENE_NODE_CUSTOM = 2;
        /// Node mesh is based on GfxMesh/Shape - Model is made of Shapes
        /// Every shape is made of one mesh. This will be mostly child node.
        const SceneNodeType SCENE_NODE_MESH = 3;
        /// This is special type of mesh node - based on GfxModel
        /// this will contain multiple children (mesh/shapes) with
        /// configured draw calls and updated bounding boxes
        const SceneNodeType SCENE_NODE_OBJECT = 4;
        /// Trigger is a special node type - when collision occurs with it
        /// the special event is thrown - registered callbacks will be called
        const SceneNodeType SCENE_NODE_TRIGGER = 5;

        ///
        class CGfxMain;
        ///
        class CSceneManager;
        ///
        class CScene3D;
        ///
        class CScene2D;
        ///
        class CSceneNodeMesh;
        ///
        class CSceneNodeObject;
        ///
        struct STreeNode;
        ///
        class CTreeNodeObject;

        /**
         * Scene object/node can be anything, it requires model matrix for any kind of 
         * transformation to world space. AABB for boundaries, collision detection,
         * frustum culling. Object type to know how to deal with it.
         * It is also drawable - but abstract. There are needed more accurate class
         * representations for this data.
         * 
         * As a base scene node - this will be required to managing tree-like structure
         * in the future.
         * 
         * Also need template structs for managing safe down/up-casting (static)
         */
        class CSceneNode :
        public resource::CManagedObject<SceneNodeHandle>,
        public traits::CDrawable,
        public traits::CAnimated,
        public CTreeNodeObject {
            friend class CGfxMain;
            friend class CSceneManager;
            //friend class CScene3D;
            //friend class CScene2D;
            friend class CSceneNodeMesh;
            friend class CSceneNodeObject;

        public:

            /**
             *
             */
            enum StateFlags {
                /// No flags selected
                NO_FLAGS = 0x0000,
                /// Is the scene node visible? Will be set to FALSE when the scene node
                /// is not in the visible tree node (quadtree/octree/...)
                VISIBLE = 0x0001,
                /// This is for automatic scaling of the model matrix
                /// based on the collision body size (half extent)
                /// Used when the size of the rendered mesh/model is 1.0f
                /// This will only have effect when using with the collision body
                AUTO_SCALE = 0x0002,
                /// Should check for collisions? If no, internal check will
                /// always return FG_FALSE
                COLLIDABLE = 0x0004,
                /// Whether or not this node is active. Node is active by default
                ACTIVE = 0x0008,
                /// Whether or not this node is selected. False by default
                SELECTED = 0x0010
            };

        public:
            /// SceneNode type - self
            typedef CSceneNode self_type;
            /// Scene node tag type
            typedef SceneNodeTag tag_type;
            /// Drawable object type
            typedef traits::CDrawable drawable_type;
            /// Animated object type
            typedef traits::CAnimated animated_type;
            /// Base type for scene node
            typedef fg::resource::CManagedObject<SceneNodeHandle> base_type;
            /// Handle type for scene node
            typedef SceneNodeHandle handle_type;
            /// Bounding box type - axis-aligned
            typedef AABoundingBox3Df box_type;
            /// Special set containing children
            typedef CVector<self_type *> ChildrenVec;
            /// Bidirectional iterator through children set
            typedef ChildrenVec::iterator ChildrenVecItor;

        private:
            /// Current scene node type - set in the constructors
            SceneNodeType m_nodeType;
            /// Scene node father/parent node pointer
            self_type* m_pParent;
            /// Collision body used for physics, it can be BOX, SPHERE or more
            /// complex convex volume
            physics::CCollisionBody* m_collisionBody;
            /// Children of the current scene node
            /// Note that this is for more logical hierarchy (not spatial)
            ChildrenVec m_children;
            ///
            StateFlags m_stateFlags;

        protected:
            /// Current scale of the scene node - scale is automatically
            /// applied to the displayed data (mesh/shape/model/...)
            Vector3f m_scale;
            /// Internal object specific model matrix (local)
            Matrix4f m_modelMat;
            /// Final model matrix (chain transformation, world, based on parent)
            Matrix4f m_finalModelMat;
            /// This is updated bounding box - it's transformed by the model matrix
            BoundingVolume3Df m_aabb;
            /// Because the Scene Node is drawable it will contain inside required
            /// draw call - pre-configured properly will draw what is needed
            CDrawCall *m_drawCall;

        public:
            /**
             * 
             * @param nodeType
             * @param pParent
             */
            CSceneNode(SceneNodeType nodeType = SCENE_NODE_INVALID, self_type *pParent = NULL);
            /**
             * 
             * @param orig
             */
            CSceneNode(const CSceneNode& orig);
            /**
             * 
             */
            virtual ~CSceneNode();

        public:
            using drawable_type::draw;
            /**
             * 
             * @param modelMat
             */
            virtual void draw(const Matrix4f& modelMat);

            /**
             * 
             * @param delta
             */
            virtual void update(float delta = 0.0f);

        public:
            /**
             * 
             * @param velocity
             */
            inline void setVelocity(const Vector3f& velocity) {
                if(m_collisionBody)
                    m_collisionBody->setVelocity(velocity);
            }
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            inline void setVelocity(float x, float y, float z) {
                if(m_collisionBody)
                    m_collisionBody->setVelocity(x, y, z);
            }
            /**
             * 
             * @return 
             */
            inline Vector3f getVelocity(void) const {
                if(m_collisionBody)
                    return m_collisionBody->getVelocity();
                return Vector3f();
            }
            /**
             * 
             * @param acceleration
             */
            inline void setAcceleration(const Vector3f& acceleration) {
                if(m_collisionBody)
                    m_collisionBody->setAcceleration(acceleration);
            }
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            inline void setAcceleration(float x, float y, float z) {
                if(m_collisionBody)
                    m_collisionBody->setAcceleration(x, y, z);
            }
            /**
             * 
             * @return 
             */
            inline Vector3f getAcceleration(void) const {
                if(m_collisionBody)
                    return m_collisionBody->getAcceleration();
                return Vector3f();
            }
            /**
             * 
             * @param position
             */
            virtual void setPosition(const Vec3f& position);
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            virtual void setPosition(float x, float y, float z);
            /**
             * 
             * @return 
             */
            inline Vector4f& getPosition(void) {
                return m_modelMat[3];
            }
            /**
             * 
             * @return 
             */
            inline Vector4f const& getPosition(void) const {
                return m_modelMat[3];
            }
            /**
             * 
             * @return 
             */
            inline Vector3f getPosition3f(void) const {
                return Vector3f(m_modelMat[3].x, m_modelMat[3].y, m_modelMat[3].z);
            }
            /**
             * 
             * @param rotation
             */
            virtual void setRotation(const Vector3f& rotation);
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            virtual void setRotation(float x, float y, float z);
            /**
             * 
             * @return 
             */
            inline Vector3f getRotation(void) const {
                if(m_collisionBody) {
                    return m_collisionBody->getRotation();
                }
                return Vector3f();
            }
            /**
             * 
             * @param translation
             */
            inline virtual void translate(const Vec3f& translation) {
                //m_modelMat = math::translate(m_modelMat, translation);
                m_modelMat[3].x += translation.x;
                m_modelMat[3].y += translation.y;
                m_modelMat[3].z += translation.z;
            }
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            inline virtual void translate(float x, float y, float z) {
                m_modelMat[3].x += x;
                m_modelMat[3].y += y;
                m_modelMat[3].z += z;
            }
            /**
             * 
             * @param translateion
             */
            inline virtual void translateMatrix(const Vec3f& translation) {
                m_modelMat = math::translate(m_modelMat, translation);
            }
            /**
             *
             * @param x
             * @param y
             * @param z
             */
            inline virtual void translateMatrix(float x, float y, float z) {
                m_modelMat = math::translate(m_modelMat, Vec3f(x, y, z));
            }
            /**
             * 
             * @param angle
             * @param axis
             */
            inline virtual void rotate(float angle, const Vec3f& axis) {
                // should scale?
                Vec3f oldScale;
                if(!m_collisionBody) {
                    oldScale = m_scale;
                    this->setScale(1.0f, 1.0f, 1.0f);
                }
                m_modelMat = math::rotate(m_modelMat, angle, axis);
                if(!m_collisionBody)
                    this->setScale(oldScale);
            }
            /**
             * 
             * @param angle
             * @param x
             * @param y
             * @param z
             */
            inline virtual void rotate(float angle, float x, float y, float z) {
                Vec3f oldScale;
                if(!m_collisionBody) {
                    oldScale = m_scale;
                    this->setScale(1.0f, 1.0f, 1.0f);
                }
                m_modelMat = math::rotate(m_modelMat, angle, Vec3f(x, y, z));
                if(!m_collisionBody)
                    this->setScale(oldScale);
            }

            /**
             * 
             * @param halfSize
             */
            void setHalfSize(const Vector3f& halfSize);
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            inline void setHalfSize(float x, float y, float z) {
                setHalfSize(Vector3f(x, y, z));
            }
            /**
             * 
             * @param halfSize
             * @param mass
             */
            inline void setHalfSizeAndMass(const Vector3f& halfSize, float mass) {
                if(m_collisionBody) {
                    m_collisionBody->setHalfSizeAndMass(halfSize, mass);
                } else {
                    setHalfSize(halfSize);
                }
            }
            /**
             * 
             * @param x
             * @param y
             * @param z
             * @param mass
             */
            inline void setHalfSizeAndMass(float x, float y, float z, float mass) {
                if(m_collisionBody) {
                    m_collisionBody->setHalfSizeAndMass(Vector3f(x, y, z), mass);
                } else {
                    setHalfSize(Vector3f(x, y, z));
                }
            }

            /**
             * 
             * @param radius
             */
            void setRadius(float radius);
            /**
             * 
             * @return 
             */
            inline float getMass(void) const {
                if(m_collisionBody)
                    return m_collisionBody->getMass();
                return 0.0f;
            }
            /**
             * 
             */
            inline void setMass(float mass) const {
                if(m_collisionBody)
                    m_collisionBody->setMass(mass);
            }

            ////////////////////////////////////////////////////////////////////

        public:
            /**
             *
             */
            void activateCollisionBody(const physics::CCollisionBody::BodyType bodyType);
            /**
             * 
             */
            void removeCollisionBody(void);
            /**
             * 
             * @param bodyType
             */
            virtual void setCollisionBodyType(const physics::CCollisionBody::BodyType bodyType);
            /**
             * 
             * @return 
             */
            physics::CCollisionBody* getCollisionBody(void) const {
                return m_collisionBody;
            }

            ////////////////////////////////////////////////////////////////////

        protected:
            /**
             * 
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);

        public:
            /**
             * 
             * @return 
             */
            inline fgBool isAutoScale(void) const {
                return (fgBool)!!(m_stateFlags & AUTO_SCALE);
            }
            /**
             * 
             * @param toggle
             */
            inline void setAutoScale(fgBool toggle = FG_TRUE) {
                setFlag(AUTO_SCALE, toggle);
            }
            /**
             * 
             * @return 
             */
            inline Vector3f& getScale(void) {
                return m_scale;
            }
            /**
             * 
             * @return 
             */
            inline Vector3f const& getScale(void) const {
                return m_scale;
            }
            /**
             * 
             * @param scale
             */
            virtual void setScale(const Vector3f& scale);
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            inline virtual void setScale(float x, float y, float z) {
                setScale(Vector3f(x, y, z));
            }

        public:
            /**
             * 
             * @param pNode
             * @return 
             */
            fgBool checkCollisionSphere(const CSceneNode* pNode) const;

            /**
             * 
             * @param pNode
             * @return 
             */
            fgBool checkCollisionAABB(const CSceneNode* pNode) const;

        public:

            /**
             * 
             * @param pChild
             * @return 
             */
            fgBool addChild(self_type *pChild);

            /**
             * 
             * @param pChild
             * @return 
             */
            fgBool removeChild(self_type *pChild);
            /**
             * 
             * @param childName
             * @return 
             */
            self_type *removeChild(const std::string& childName);
            /**
             * 
             * @param childName
             * @return 
             */
            self_type *removeChild(const char *childName);

            /**
             * 
             * @param pChild
             * @return 
             */
            fgBool destroyChild(self_type *&pChild);
            /**
             * 
             * @param childName
             * @return 
             */
            fgBool destroyChild(const std::string& childName);
            /**
             * 
             * @param childName
             * @return 
             */
            fgBool destroyChild(const char *childName);

            /**
             * 
             * @param childHandle
             * @return 
             */
            self_type* getChild(const handle_type& childHandle);
            /**
             * 
             * @param childName
             * @return 
             */
            self_type* getChild(const std::string& childName);
            /**
             * 
             * @param childName
             * @return 
             */
            self_type* getChild(const char *childName);
            /**
             * 
             * @param index
             * @return
             */
            self_type* getChildByIndex(const unsigned int index = 0);

            /**
             * 
             * @param pChild
             * @return 
             */
            fgBool hasChild(self_type *pChild);
            /**
             * 
             * @param childHandle
             * @return 
             */
            fgBool hasChild(const handle_type& childHandle);
            /**
             * 
             * @param childName
             * @return 
             */
            fgBool hasChild(const std::string& childName);
            /**
             * 
             * @param childName
             * @return 
             */
            fgBool hasChild(const char* childName);

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline fgBool isEmpty(void) const {
                return (fgBool)m_children.empty();
            }
            /**
             * 
             * @return 
             */
            inline fgBool hasChildren(void) const {
                return !isEmpty();
            }

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline ChildrenVec& getChildren(void) {
                return m_children;
            }
            /**
             * 
             * @return 
             */
            inline ChildrenVec const& getChildren(void) const {
                return m_children;
            }
            /**
             * 
             * @return 
             */
            inline unsigned int getChildrenCount(void) const {
                return m_children.size();
            }

            //------------------------------------------------------------------
            /**
             * 
             * @param pParent
             */
            inline void setParent(self_type* pParent) {
                m_pParent = pParent;
            }
            /**
             * 
             * @return 
             */
            inline self_type* getParent(void) const {
                return m_pParent;
            }

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline CDrawCall* getDrawCall(void) const {
                return m_drawCall;
            }
            /**
             * 
             * @return 
             */
            inline SceneNodeType getNodeType(void) const {
                return m_nodeType;
            }

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline Matrix4f& getModelMatrix(void) {
                return m_modelMat;
            }
            /**
             * 
             * @return 
             */
            inline Matrix4f const& getModelMatrix(void) const {
                return m_modelMat;
            }
            /**
             *
             * @return
             */
            inline Matrix4f& getFinalModelMatrix(void) {
                return m_finalModelMat;
            }
            /**
             *
             * @return
             */
            inline Matrix4f const& getFinalModelMatrix(void) const {
                return m_finalModelMat;
            }
            /**
             * 
             * @param modelMat
             */
            inline void setModelMatrix(const Matrix4f& modelMat) {
                m_modelMat = modelMat;
            }
            /**
             * 
             * @param aabb
             */
            inline void setBoundingVolume(const AABoundingBox3Df& aabb) {
                m_aabb.invalidate();
                m_aabb.merge(aabb);
            }
            /**
             * 
             * @param aabb
             */
            inline void setBoundingVolume(const BoundingVolume3Df& aabb) {
                m_aabb = aabb;
            }
            /**
             * 
             * @return 
             */
            inline BoundingVolume3Df& getBoundingVolume(void) {
                return m_aabb;
            }
            /**
             * 
             * @return 
             */
            inline BoundingVolume3Df const& getBoundingVolume(void) const {
                return m_aabb;
            }

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline fgBool isVisible(void) const {
                return (fgBool)!!(m_stateFlags & VISIBLE);
            }
            /**
             * 
             * @param toggle
             */
            void setVisible(const fgBool toggle = FG_TRUE,
                            const fgBool recursive = FG_TRUE);
            /**
             * 
             * @return 
             */
            inline fgBool isCollidable(void) const {
                return (fgBool)!!(m_stateFlags & COLLIDABLE);
            }
            /**
             * 
             * @param toggle
             */
            inline void setCollidable(const fgBool toggle = FG_TRUE) {
                setFlag(COLLIDABLE, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isActive(void) const {
                return (fgBool)!!(m_stateFlags & ACTIVE);
            }
            /**
             * 
             * @param toggle
             */
            inline void setActive(const fgBool toggle = FG_TRUE) {
                setFlag(ACTIVE, toggle);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isSelected(void) const {
                return (fgBool)!!(m_stateFlags & SELECTED);
            }
            /**
             *
             * @param toggle
             */
            inline void setSelected(const fgBool toggle = FG_TRUE) {
                setFlag(SELECTED, toggle);
            }
            /**
             *
             */
            inline void unselect(void) {
                setFlag(SELECTED, FG_FALSE);
            }

            //------------------------------------------------------------------
            /**
             * 
             * @param b
             * @return 
             */
            inline int operator ==(const CSceneNode& b) const {
                return (this->getHandle() == b.getHandle());
            }
            /**
             * 
             * @param b
             * @return 
             */
            inline int operator !=(const CSceneNode& b) const {
                return (this->getHandle() != b.getHandle());
            }
            /**
             * 
             * @param a
             * @return 
             */
            inline bool operator <(const CSceneNode& a) const {
                if(!this->m_drawCall)
                    return true;
                else if(!a.getDrawCall())
                    return false;
                else {
                    return (*this->m_drawCall < *a.getDrawCall());
                }
                return false;
            }
            /**
             * 
             * @param a
             * @return 
             */
            inline bool operator >(const CSceneNode& a) const {
                if(!this->m_drawCall)
                    return false;
                else if(!a.getDrawCall())
                    return true;
                else {
                    return (*this->m_drawCall > *a.getDrawCall());
                }
                return false;
            }
            /**
             * 
             * @param a
             * @return 
             */
            inline bool operator <=(const CSceneNode& a) const {
                if(!this->m_drawCall)
                    return true;
                else if(!a.getDrawCall())
                    return false;
                else {
                    return (*this->m_drawCall <= *a.getDrawCall());
                }
                return true;
            }
            /**
             * 
             * @param a
             * @return 
             */
            inline bool operator >=(const CSceneNode& a) const {
                if(!this->m_drawCall)
                    return true;
                else if(!a.getDrawCall())
                    return false;
                else {
                    return (*this->m_drawCall >= *a.getDrawCall());
                }
                return true;
            }

        protected:
            /**
             *
             * @param delta
             * @return
             */
            virtual void animate(float delta = 0.0f);
            /**
             *
             */
            virtual void updateAABB(void);
            /**
             *
             */
            virtual void refreshGfxInternals(void);
            /**
             * 
             * @param objectType
             */
            inline void setNodeType(const SceneNodeType nodeType) {
                m_nodeType = nodeType;
            }
        }; // class CSceneNode

        FG_ENUM_FLAGS(CSceneNode::StateFlags);

        //----------------------------------------------------------------------
        inline void CSceneNode::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_stateFlags |= flags;
            } else {
                m_stateFlags |= flags;
                m_stateFlags ^= flags;
            }
        }
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_NODE_BLOCK
#endif /* FG_INC_GFX_SCENE_NODE */
