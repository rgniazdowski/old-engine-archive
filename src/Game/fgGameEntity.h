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
 * File:   fgGameEntity.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 8:04 PM
 */

#ifndef FG_INC_GAME_ENTITY
    #define FG_INC_GAME_ENTITY
    #define FG_INC_GAME_ENTITY_BLOCK

    #include "GFX/Scene/fgGfxSceneNodeObject.h"
    #include "fgGameEntityType.h"
    #include "fgIntelligent.h"
    
namespace fg {
    namespace gfx {
        class CSceneNode;
        class CSceneNodeObject;
        class CModelResource;
        struct SShape;
        struct SMeshBase;
    } // namespace gfx

    namespace game {
        class CEntityMesh;

        /**
         *
         */
        class CEntity : 
        public gfx::CSceneNodeObject,
        public fg::game::traits::CIntelligent {
        public:
            typedef gfx::CSceneNodeObject base_type;
            typedef fg::game::traits::CIntelligent intelligent_type;
            typedef CEntity self_type;
            typedef CEntity type;

        public:
            static const GameEntityType SELF_ENTITY_TYPE = GAME_ENTITY;
            static const gfx::SceneNodeType SELF_NODE_TYPE = GAME_ENTITY;

        public:
            /**
             *
             * @param pModel
             * @param pParent
             */
            CEntity(gfx::CModelResource* pModel = NULL, gfx::CSceneNode* pParent = NULL);
            /**
             *
             * @param orig
             */
            CEntity(const self_type& orig);
            /**
             * 
             */
            virtual ~CEntity();

        public:
            /**
             * 
             * @param trait
             * @param pObj
             * @return
             */
            virtual fgBool queryTrait(const fg::traits::SceneNode trait, void **pObj);

        private:

        }; // class CEntity
        
    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_ENTITY_BLOCK
#endif	/* FG_INC_GAME_ENTITY */
