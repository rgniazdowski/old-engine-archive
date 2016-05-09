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
 * File:   fgGFXSceneNodeObject.h
 * Author: vigilant
 *
 * Created on November 12, 2014, 6:08 PM
 */

#ifndef FG_INC_GFX_SCENE_NODE_OBJECT
    #define FG_INC_GFX_SCENE_NODE_OBJECT
    #define FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK

    #include "fgGfxSceneNode.h"    

namespace fg {
    namespace gfx {

        class CNodeFactory;
        class CModelResource;
        struct SMeshBase;
        struct SShape;
        struct SSkinnedMesh;

        /**
         * 
         */
        class CSceneNodeObject : public CSceneNode {
        public:
            ///
            typedef CSceneNode base_type;
            ///
            typedef CSceneNodeObject self_type;
            ///
            typedef CSceneNodeObject type;
            ///
            static const SceneNodeType SELF_NODE_TYPE = SCENE_NODE_OBJECT;

        public:
            /**
             * 
             */
            CSceneNodeObject(CModelResource *pModel = NULL,
                             CSceneNode *pParent = NULL);
            /**
             * 
             * @param orig
             */
            CSceneNodeObject(const CSceneNodeObject& orig);
            /**
             * 
             */
            virtual ~CSceneNodeObject();

        public:
            /**
             * 
             * @param pModel
             */
            virtual void setModel(CModelResource *pModel);
            /**
             * 
             * @return 
             */
            CModelResource *getModel(void) const {
                return m_pModel;
            }

            using animated_type::setAnimation;
            /**
             * 
             * @param name
             * @param slot
             * @return
             */
            virtual fgBool setAnimation(const char* name, unsigned int slot);

        protected:
            /**
             * 
             */
            virtual void updateAABB(void);

            /**
             * 
             */
            virtual void refreshGfxInternals(void);

            virtual void animate(float delta = 0.0f);

        public:
            /**
             * 
             * @return 
             */
            SceneNodeType getDefaultMeshChildType(void) const {
                return m_defaultMeshChildType;
            }

        protected:
            /**
             * 
             * @param childType
             */
            void setDefaultMeshChildType(const SceneNodeType childType) {
                m_defaultMeshChildType = childType;
            }

        private:
            /// Pointer to the external model on which this object is based
            CModelResource *m_pModel;
            /// Default managed child node type (needs to have MESH type trait)
            /// This is the node type that is being used when automatically
            /// adding children based on object model data;
            SceneNodeType m_defaultMeshChildType;
            CVector<anim::SAnimationFrameInfo> m_meshFramesVec;
        }; // class CSceneNodeObject

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_OBJECT */
