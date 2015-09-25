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
 * File:   fgPhysical.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 9:21 PM
 */

#ifndef FG_INC_PHYSICS_TRAIT_PHYSICAL
    #define FG_INC_PHYSICS_TRAIT_PHYSICAL
    #define FG_INC_PHYSICS_TRAIT_PHYSICAL_BLOCK

    #include "fgTraits.h"
    #include "Physics/fgCollisionBody.h"

namespace fg {
    namespace physics {
        namespace traits {

            /**
             *
             */
            class CPhysical {
            public:
                typedef CPhysical self_type;
                typedef CPhysical type;

            public:
                static const fg::traits::SceneNode SELF_TRAIT = fg::traits::PHYSICAL;

            public:
                CPhysical();
                CPhysical(const self_type& orig);
                virtual ~CPhysical();
                
            public:
                CCollisionBody* getCollisionBody(void);
                CCollisionBody const* getCollisionBody(void) const;
                
                CCollisionBody::BodyType getBodyType(void) const;

            private:
                CCollisionBody* m_collisionBody;

            }; // class CPhysical

        } // namespace traits
    } // namespace physics
} // namespace fg

    #undef FG_INC_PHYSICS_TRAIT_PHYSICAL_BLOCK
#endif	/* FG_INC_PHYSICS_TRAIT_PHYSICAL */
