/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
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
        #include "fgGFXSceneNode.h"
    #endif

    #ifndef FG_INC_GFX_MODEL_TYPES
        #include "fgGFXModelTypes.h"
    #endif
namespace fg {
    namespace gfx {

        /**
         * 
         */
        class CSceneNodeMesh : public CSceneNode {
        public:
            /**
             * 
             */
            CSceneNodeMesh(fgGfxMeshBase *pMesh = NULL, CSceneNode *pParent = NULL);
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
            fgGfxMeshBase *getMesh(void) const {
                return m_pMesh;
            }
            /**
             * 
             * @param pMesh
             */
            virtual void setMesh(fgGfxMeshBase *pMesh);

        private:
            /// Pointer to external mesh that this object represents
            fgGfxMeshBase *m_pMesh;

        };
    };
};

    #undef FG_INC_GFX_SCENE_NODE_MESH_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_MESH */
