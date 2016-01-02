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
 * File:   fgMaskTypes.h
 * Author: vigilant
 *
 * Created on October 28, 2015, 2:51 PM
 */

#ifndef FG_INC_PHYSICS_MASK_TYPES
    #define FG_INC_PHYSICS_MASK_TYPES
    #define FG_INC_PHYSICS_MASK_TYPES_BLOCK
    
    #include "fgBuildConfig.h"

    #if !defined(FG_USING_BULLET)
namespace fg {
    namespace physics {

        class CRigidBody {
        public:
            CRigidBody() { }
            virtual ~CRigidBody() { }
        }; // class CRigidBody

        class CCollisionPrimitive {
        public:
            CCollisionPrimitive() { }
            virtual ~CCollisionPrimitive() { }
        }; // class CCollisionPrimitive

        class CCollisionSphere : public CCollisionPrimitive {
        public:
            CCollisionSphere() { }
            virtual ~CCollisionSphere() { }
        }; // class CCollisionSphere

        class CCollisionBox : public CCollisionPrimitive {
        public:
            CCollisionBox() { }
            virtual ~CCollisionBox() { }
        }; // class CCollisionBox

        class CCollisionTriangleMesh : public CCollisionPrimitive {
        public:
            CCollisionTriangleMesh() { }
            virtual ~CCollisionTriangleMesh() { }
        }; // class CCollisionTriangleMesh

        class CCollisionCapsule : public CCollisionPrimitive {
            CCollisionCapsule() { }
            virtual ~CCollisionCapsule() { }
        }; // class CCollisionCapsule

    } // namespace physics
} // namespace fg

    #endif /* not using Bullet && not using Cyclone */

    #undef FG_INC_PHYSICS_MASK_TYPES_BLOCK
#endif	/* FG_INC_PHYSICS_MASK_TYPES */
