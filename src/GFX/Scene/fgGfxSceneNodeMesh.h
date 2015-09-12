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
 * File:   fgGFXSceneNodeMesh.h
 * Author: vigilant
 *
 * Created on November 14, 2014, 11:30 PM
 */

#ifndef FG_INC_GFX_SCENE_NODE_MESH
    #define FG_INC_GFX_SCENE_NODE_MESH
    #define FG_INC_GFX_SCENE_NODE_MESH_BLOCK

    #ifndef FG_INC_GFX_SCENE_NODE
        #include "fgGfxSceneNode.h"
    #endif

    #ifndef FG_INC_GFX_MESH
        #include "fgGfxMesh.h"
    #endif
namespace fg {
    namespace gfx {

        struct SSkinnedMesh;

        /**
         * 
         */
        class CSceneNodeMesh : public CSceneNode {
        public:
            ///
            typedef CSceneNode base_type;
            ///
            typedef CSceneNodeMesh self_type;
            ///
            typedef CSceneNodeMesh type;
            
        public:
            /**
             * 
             */
            CSceneNodeMesh(SMeshBase *pMesh = NULL, CSceneNode *pParent = NULL);
            /**
             * 
             * @param orig
             */
            CSceneNodeMesh(const CSceneNodeMesh& orig);
            /**
             * 
             */
            virtual ~CSceneNodeMesh();

        public:
            /**
             * 
             * @return 
             */
            SMeshBase* getMesh(void) const {
                return m_pMesh;
            }
            /**
             *
             * @return
             */
            SSkinnedMesh* getSkinnedMesh(void) const;
            /**
             *
             * @return
             */
            fgBool isSkinnedMesh(void) const {
                if(!m_pMesh)
                    return FG_FALSE;
                return m_pMesh->isSkinnedMesh();
            }
            /**
             *
             * @return
             */
            SMaterial* getMaterial(void) const {
                return m_pMaterial;
            }
            /**
             * 
             * @param pMesh
             */
            virtual void setMesh(SMeshBase *pMesh);
            /**
             * 
             * @param pMaterial
             */
            void setMaterial(SMaterial *pMaterial);
            
            /**
             * 
             */
            virtual void refreshGfxInternals(void);
            
        public:
            using drawable_type::draw;
            /**
             * Draw with given model matrix
             * @param modelMat
             */
            virtual void draw(const Matrix4f& modelMat);
            /**
             * 
             */
            virtual void updateAABB(void);

        protected:
            /**
             *
             * @param delta
             */
            virtual void animate(float delta = 0.0f);

        private:
            /// Pointer to external mesh that this object represents
            SMeshBase *m_pMesh;
            ///
            SMaterial *m_pMaterial;
        }; // class CSceneNodeMesh

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_NODE_MESH_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_MESH */
