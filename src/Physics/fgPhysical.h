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
                /**
                 *
                 */
                CPhysical();
                /**
                 *
                 * @param orig
                 */
                CPhysical(const self_type& orig);
                /**
                 *
                 */
                virtual ~CPhysical();

            public:
                /**
                 *
                 * @return
                 */
                CCollisionBody* getCollisionBody(void);
                /**
                 *
                 * @return
                 */
                CCollisionBody const* getCollisionBody(void) const;
                /**
                 *
                 * @return
                 */
                /**
                 *
                 * @return
                 */
                CAbstractCollisionBody* getAbstractCollisionBody(void);
                /**
                 * 
                 * @return
                 */
                CAbstractCollisionBody const* getAbstractCollisionBody(void) const;
                /**
                 *
                 * @return
                 */
                BodyType getBodyType(void) const;
                /**
                 * 
                 * @return
                 */
                fgBool hasCollisionBody(void) const;

            public:
                /**
                 *
                 * @return
                 */
                inline fgBool isBox(void) const {
                    if(!hasCollisionBody())
                        return FG_FALSE;
                    return m_collisionBody->isBox();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isSphere(void) const {
                    if(!hasCollisionBody())
                        return FG_FALSE;
                    return m_collisionBody->isSphere();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isCapsule(void) const {
                    if(!hasCollisionBody())
                        return FG_FALSE;
                    return m_collisionBody->isCapsule();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isTriangleMesh(void) const {
                    if(!hasCollisionBody())
                        return FG_FALSE;
                    return m_collisionBody->isTriangleMesh();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isComplex(void) const {
                    if(!hasCollisionBody())
                        return FG_FALSE;
                    return m_collisionBody->isComplex();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isRagdoll(void) const {
                    if(!hasCollisionBody())
                        return FG_FALSE;
                    return m_collisionBody->isRagdoll();
                }

                //--------------------------------------------------------------
            protected:
                virtual fgBool setupCollisionBody(BodyType bodyType);

            private:
                CAbstractCollisionBody* m_collisionBody;

            }; // class CPhysical

        } // namespace traits
    } // namespace physics
} // namespace fg

    #undef FG_INC_PHYSICS_TRAIT_PHYSICAL_BLOCK
#endif	/* FG_INC_PHYSICS_TRAIT_PHYSICAL */
