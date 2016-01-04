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
 * File:   fgGameEntityActor.h
 * Author: vigilant
 *
 * Created on October 12, 2015, 11:13 PM
 */

#ifndef FG_INC_GAME_ENTITY_ACTOR
    #define FG_INC_GAME_ENTITY_ACTOR
    #define FG_INC_GAME_ENTITY_ACTOR_BLOCK

// #include "game/CEntity.h"
// #include "Game/CEntity.h"

    #include "fgGameEntity.h"
    #include "GFX/fgGfxMesh.h"
    #include "GFX/fgGfxSkinnedMesh.h"
    #include "Physics/fgPhysical.h"

namespace fg {
    namespace gfx {
        namespace anim {
            class CRagdollBoneAnimation;
            class CBoneAnimation;
            class CAnimation;
            struct SAnimationInfo;
            struct SAnimationFrameInfo;
        }
    }
    namespace game {

        /**
         * CEntityActor is used mostly for animated objects with some physical properties.
         * For full physics activate ragdolling.
         * Standard CEntityMesh will treat model/mesh as one block. Animations will still
         * work, but physics will behave completely unnaturally.
         *
         * CEntityActor is also base class for any animated/rigged object (player, enemies,
         * creatures, monsters, animals and so on...). Any other class must base on this one.
         */
        class CEntityActor : public CEntity,
        public fg::physics::traits::CPhysical {
        public:
            typedef CEntityActor self_type;
            typedef CEntityActor type;
            typedef CEntity base_type;
            typedef fg::physics::traits::CPhysical physical_type;

        public:
            static const GameEntityType SELF_ENTITY_TYPE = GAME_ENTITY_ACTOR;
            static const gfx::SceneNodeType SELF_NODE_TYPE = GAME_ENTITY_ACTOR;

        public:
            /**
             *
             */
            CEntityActor(gfx::CModelResource* pModel = NULL,
                         gfx::CSceneNode* pParent = NULL);
            /**
             *
             * @param orig
             */
            CEntityActor(const self_type& orig);
            /**
             * 
             */
            virtual ~CEntityActor();

        public:
            /**
             *
             * @param trait
             * @param pObj
             * @return
             */
            virtual fgBool queryTrait(const fg::traits::SceneNode trait, void **pObj);

            using base_type::setModel;
            /**
             * 
             * @param pModel
             */
            virtual void setModel(gfx::CModelResource *pModel);

            void startRagdolling(void);
            void stopRagdolling(void);
            fgBool isRagdolling(void) const;
            gfx::anim::CRagdollBoneAnimation* getRagdollBoneAnimation(void) {
                return m_ragdollAnimation;
            }
            gfx::anim::CRagdollBoneAnimation const* getRagdollBoneAnimation(void) const {
                return m_ragdollAnimation;
            }

            virtual void updateAABB(void);
        protected:
            virtual fgBool setupCollisionBody(physics::BodyType bodyType);

            fgBool copyAnimationToRagdoll(gfx::anim::SAnimationInfo* pInfo,
                                          const gfx::SSkinnedMesh::BonesVec& bones);

        private:
            ///
            gfx::anim::CRagdollBoneAnimation* m_ragdollAnimation;
        }; // class CEntityActor

    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_ENTITY_ACTOR_BLOCK
#endif /* FG_INC_GAME_ENTITY_ACTOR */
