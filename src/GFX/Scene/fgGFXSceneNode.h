/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SCENE_NODE
    #define FG_INC_GFX_SCENE_NODE
    #define FG_INC_GFX_SCENE_NODE_BLOCK

    #include "Math/fgMathLib.h"
    #include "Util/fgTag.h"
    #include "GFX/fgGFXAABoundingBox.h"
    #include "GFX/fgGFXBoundingVolume.h"

    #ifndef FG_INC_GFX_DRAWABLE
        #include "GFX/fgGFXDrawable.h"
    #endif
    #ifndef FG_INC_GFX_DRAW_CALL
        #include "GFX/fgGFXDrawCall.h"
    #endif
    #ifndef FG_INC_GFX_TREE_NODE
        #include "fgGFXTreeNode.h"
    #endif

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
        /// Custom scene node - it is still drawable but relies on custom
        /// draw call type to draw something - meaning that this utilizes
        /// custom vertex data
        const SceneNodeType SCENE_NODE_CUSTOM = 1;
        /// Node mesh is based on GfxMesh/Shape - Model is made of Shapes
        /// Every shape is made of one mesh. This will be mostly child node.
        const SceneNodeType SCENE_NODE_MESH = 2;
        /// This is special type of mesh node - based on GfxModel
        /// this will contain multiple children (mesh/shapes) with
        /// configured draw calls and updated bounding boxes
        const SceneNodeType SCENE_NODE_OBJECT = 3;
        /// Trigger is a special node type - when collision occurs with it
        /// the special event is thrown - registered callbacks will be called
        const SceneNodeType SCENE_NODE_TRIGGER = 4;

        ///
        class CSceneManager;
        ///
        struct STreeNode;

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
        public CDrawable {
        public:
            /// Scene node tag type
            typedef SceneNodeTag tag_type;
            /// Drawable object type
            typedef CDrawable drawable_type;
            /// Base type for scene node
            typedef CManagedObject<SceneNodeHandle> base_type;
            /// Handle type for scene node
            typedef SceneNodeHandle handle_type;
            /// SceneNode type - self
            typedef CSceneNode self_type;
            /// Special set containing children
            typedef std::set<self_type *> ChildrenSet;
            /// Bidirectional iterator through children set
            typedef ChildrenSet::iterator ChildrenSetItor;
            /// Bounding box type - axis-aligned
            typedef AABoundingBox3Df box_type;

        private:
            ///
            SceneNodeType m_nodeType;
            ///
            STreeNode *m_pTreeNode;
            /// Scene node father/parent node pointer
            self_type *m_pParent;
            ///
            ChildrenSet m_children;
            ///
            fgBool m_isVisible;

        protected:
            /// Internal object specific model matrix
            Matrix4f m_modelMat;
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
             */
            virtual ~CSceneNode();

        public:

            /**
             * 
             */
            virtual void draw(void);
            /**
             * Draw with relative 2D position
             * @param relPos
             */
            virtual void draw(const Vec2f& relPos);
            /**
             * Draw with relative 3D position
             * @param relPos
             */
            virtual void draw(const Vec3f& relPos);
            /**
             * Draw with given model matrix
             * @param modelMat
             */
            virtual void draw(const Matrix4f& modelMat);

        public:
            /**
             * 
             * @param pNode
             * @return 
             */
            fgBool checkCollisionSphere(const CSceneNode* pNode);

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
            /**
             * 
             * @return 
             */
            inline ChildrenSet & getChildren(void) {
                return m_children;
            }
            /**
             * 
             * @return 
             */
            inline ChildrenSet const & getChildren(void) const {
                return m_children;
            }
            /**
             * 
             * @return 
             */
            inline unsigned int getChildrenCount(void) const {
                return m_children.size();
            }
            /**
             * 
             * @param pTreeNode
             */
            inline void setTreeNode(STreeNode *pTreeNode) {
                m_pTreeNode = pTreeNode;
            }
            /**
             * 
             * @return 
             */
            inline STreeNode* getTreeNode(void) const {
                return m_pTreeNode;
            }
            /**
             * 
             * @param pParent
             */
            inline void setParent(self_type *pParent) {
                m_pParent = pParent;
            }
            /**
             * 
             * @return 
             */
            inline self_type *getParent(void) const {
                return m_pParent;
            }
            /**
             * 
             * @return 
             */
            inline CDrawCall *getDrawCall(void) const {
                return m_drawCall;
            }
            /**
             * 
             * @return 
             */
            inline SceneNodeType getNodeType(void) const {
                return m_nodeType;
            }
            /**
             * 
             * @return 
             */
            inline Matrix4f& getRefModelMatrix(void) {
                return m_modelMat;
            }
            /**
             * 
             * @return 
             */
            inline Matrix4f const & getRefModelMatrix(void) const {
                return m_modelMat;
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
            inline BoundingVolume3Df& getRefBoundingVolume(void) {
                return m_aabb;
            }
            /**
             * 
             * @return 
             */
            inline BoundingVolume3Df const& getRefBoundingVolume(void) const {
                return m_aabb;
            }
            /**
             * 
             */
            virtual inline void updateAABB(void) {
                // #FUBAR - no reset
                m_aabb.transform(m_modelMat);
            }
            /**
             * 
             * @param modelMat
             */
            virtual inline void updateAABB(const Matrix4f& modelMat) {
                // #FUBAR - no reset performed
                m_aabb.transform(modelMat);
            }
            /**
             * 
             * @return 
             */
            fgBool isVisible(void) const {
                return m_isVisible;
            }
            /**
             * 
             * @param toggle
             */
            void setVisible(const fgBool toggle = FG_TRUE) {
                m_isVisible = toggle;
            }

            ////////////////////////////////////////////////////////////////////////////
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
             * @param objectType
             */
            inline void setNodeType(const SceneNodeType nodeType) {
                m_nodeType = nodeType;
            }
        };
    };
};

    #undef FG_INC_GFX_SCENE_NODE_BLOCK
#endif /* FG_INC_GFX_SCENE_NODE */