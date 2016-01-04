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
 * File:   fgGameEntityMesh.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 8:04 PM
 */

#ifndef FG_INC_GAME_ENTITY_MESH
    #define FG_INC_GAME_ENTITY_MESH
    #define FG_INC_GAME_ENTITY_MESH_BLOCK

    #include "GFX/Scene/fgGfxSceneNodeMesh.h"
    #include "fgGameEntityType.h"
    #include "Physics/fgPhysical.h"
    #include "GFX/fgGfxMesh.h"
    #include "GFX/fgGfxSkinnedMesh.h"

namespace fg {
    namespace gfx {
        class CSceneNode;
        class CSceneNodeMesh;
        struct SMeshBase;
        struct SMeshAoS;
        struct SMeshSoA;
        struct SSkinnedMesh;
    } // namespace gfx

    namespace game {
        class CEntity;

        /**
         *
         */
        class CEntityMesh :
        public gfx::CSceneNodeMesh,
        public fg::physics::traits::CPhysical {
        public:
            typedef gfx::CSceneNodeMesh base_type;
            typedef fg::physics::traits::CPhysical physical_type;
            typedef CEntityMesh self_type;
            typedef CEntityMesh type;

        public:
            static const GameEntityType SELF_ENTITY_TYPE = GAME_ENTITY_MESH;
            static const gfx::SceneNodeType SELF_NODE_TYPE = GAME_ENTITY_MESH;

        public:
            /**
             *
             * @param pMesh
             * @param pParent
             */
            CEntityMesh(gfx::SMeshBase* pMesh = NULL, gfx::CSceneNode* pParent = NULL);
            /**
             *
             * @param orig
             */
            CEntityMesh(const self_type& orig);
            /**
             * 
             */
            virtual ~CEntityMesh();

        public:
            virtual fgBool queryTrait(const fg::traits::SceneNode trait, void **pObj);

            virtual void setScale(const Vector3f& scale);

            virtual void setMesh(gfx::SMeshBase* pMesh);

            virtual void updateAABB(void);

        private:

        }; // class CEntityMesh

    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_ENTITY_MESH_BLOCK
#endif	/* FG_INC_GAME_ENTITY_MESH */
