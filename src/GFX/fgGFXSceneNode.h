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
    #include "fgGFXAABoundingBox.h"
    #ifndef FG_INC_GFX_DRAWABLE
        #include "fgGFXDrawable.h"
    #endif
    #ifndef FG_INC_GFX_DRAW_CALL
        #include "fgGFXDrawCall.h"
    #endif
namespace fg {
    namespace gfx {
        class CSceneNode;
    }
}


    #define FG_TAG_GFX_OBJECT_NAME	"GfxSceneNode"
    #define FG_TAG_GFX_OBJECT		FG_TAG_TYPE(fg::gfx::CSceneNode)

FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CSceneNode, FG_TAG_GFX_OBJECT_NAME);
typedef FG_TAG_GFX_OBJECT fgGfxSceneNodeTag;

// Special handle type for gfx object (scene object)
typedef fgHandle<fgGfxSceneNodeTag> fgGfxSceneNodeHandle;

typedef unsigned int fgGfxSceneNodeType;

    #define FG_GFX_SCENE_NODE_INVALID   0
/// Custom scene node - it is still drawable but relies on custom
/// draw call type to draw something - meaning that this utilizes
/// custom vertex data
    #define FG_GFX_SCENE_NODE_CUSTOM    1
/// Node mesh is based on GfxMesh/Shape - Model is made of Shapes
/// Every shape is made of one mesh. This will be mostly child node.
    #define FG_GFX_SCENE_NODE_MESH      2
/// This is special type of mesh node - based on GfxModel
/// this will contain multiple children (mesh/shapes) with
/// configured draw calls and updated bounding boxes
    #define FG_GFX_SCENE_NODE_OBJECT    3
/// Trigger is a special node type - when collision occurs with it
/// the special event is thrown - registered callbacks will be called
    #define FG_GFX_SCENE_NODE_TRIGGER   4

/// Drawable type for scene node
    #define FG_GFX_DRAWABLE_SCENENODE   5

    #include <set>

namespace fg {
    namespace resource {
        template<typename THandleType> class CManagedObject;
    };

    namespace gfx {

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
        public fg::resource::CManagedObject<fgGfxSceneNodeHandle>,
        public CDrawable {
        public:
            /// Scene node tag type
            typedef fgGfxSceneNodeTag tag_type;
            /// Drawable object type
            typedef CDrawable drawable_type;
            /// Base type for scene node
            typedef CManagedObject<fgGfxSceneNodeHandle> base_type;
            /// Handle type for scene node
            typedef fgGfxSceneNodeHandle handle_type;
            /// SceneNode type - self
            typedef CSceneNode self_type;
            /// Special set containing children
            typedef std::set<self_type *> childrenSet;
            /// Bidirectional iterator through children set
            typedef childrenSet::iterator childrenSetItor;
            /// Bounding box type - axis-aligned
            typedef fgAABoundingBox3Df box_type;

        private:
            ///
            fgGfxSceneNodeType m_nodeType;
            /// Scene node father/parent node pointer
            self_type *m_pParent;
            ///
            childrenSet m_children;
            ///
            fgBool m_isVisible;

        protected:
            /// Internal object specific model matrix
            fgMatrix4f m_modelMat;
            /// This is updated bounding box - it's transformed
            fgAABoundingBox3Df m_aabb;
            /// Because the Scene Node is drawable it will contain inside required
            /// draw call - pre-configured properly will draw what is needed
            CDrawCall *m_drawCall;

        public:
            /**
             * 
             * @param nodeType
             * @param pParent
             */
            CSceneNode(fgGfxSceneNodeType nodeType = FG_GFX_SCENE_NODE_INVALID, self_type *pParent = NULL);
            /**
             * 
             */
            virtual ~CSceneNode();

            /**
             * 
             */
            virtual void draw(void);
            /**
             * Draw with relative 2D position
             * @param relPos
             */
            virtual void draw(const fgVec2f& relPos);
            /**
             * Draw with relative 3D position
             * @param relPos
             */
            virtual void draw(const fgVec3f& relPos);
            /**
             * Draw with given model matrix
             * @param modelMat
             */
            virtual void draw(const fgMatrix4f& modelMat);

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
            inline childrenSet & getChildren(void) {
                return m_children;
            }
            /**
             * 
             * @return 
             */
            inline childrenSet const & getChildren(void) const {
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
            inline fgGfxSceneNodeType getNodeType(void) const {
                return m_nodeType;
            }
            /**
             * 
             * @return 
             */
            inline fgMatrix4f& getRefModelMatrix(void) {
                return m_modelMat;
            }
            /**
             * 
             * @return 
             */
            inline fgMatrix4f const & getRefModelMatrix(void) const {
                return m_modelMat;
            }
            /**
             * 
             * @param modelMat
             */
            inline void setModelMatrix(const fgMatrix4f& modelMat) {
                m_modelMat = modelMat;
            }
            /**
             * 
             * @param aabb
             */
            inline void setAABB(const fgAABoundingBox3Df& aabb) {
                m_aabb = aabb;
            }
            /**
             * 
             * @return 
             */
            inline fgAABoundingBox3Df& getRefAABB(void) {
                return m_aabb;
            }
            /**
             * 
             * @return 
             */
            inline fgAABoundingBox3Df const & getRefAABB(void) const {
                return m_aabb;
            }
            /**
             * 
             */
            virtual inline void updateAABB(void) {
                // #FUBAR
                m_aabb.transform(m_modelMat);
            }
            /**
             * 
             * @param modelMat
             */
            virtual inline void updateAABB(const fgMatrix4f& modelMat) {
                // #FUBAR
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
            inline void setNodeType(const fgGfxSceneNodeType nodeType) {
                m_nodeType = nodeType;
            }
        };
    };
};

    #undef FG_INC_GFX_SCENE_NODE_BLOCK
#endif /* FG_INC_GFX_SCENE_NODE */
