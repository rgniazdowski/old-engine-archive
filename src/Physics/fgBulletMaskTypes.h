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
 * File:   fgBulletMaskTypes.h
 * Author: vigilant
 *
 * Created on September 24, 2015, 12:22 PM
 */

#ifndef FG_INC_BULLET_MASK_TYPES
    #define FG_INC_BULLET_MASK_TYPES
    #define FG_INC_BULLET_MASK_TYPES_BLOCK

    #include "fgBuildConfig.h"

    #if defined(FG_USING_BULLET)
class btRigidBody;
class btCollisionShape;
class btSphereShape;
class btBoxShape;
class btBvhTriangleMeshShape;
class btCapsuleShape;

class btCollisionConfiguration;
class btDefaultCollisionConfiguration;
class btDynamicsWorld;
class btDiscreteDynamicsWorld;
//class btMultiBodyDynamicsWorld;
class btBroadphaseInterface;
class btDbvtBroadphase;
class btCollisionDispatcher;
class btConstraintSolver;
//class btMultiBodyConstraintSolver;
class btMotionState;
class btTypedConstraint;

namespace fg {
    namespace physics {
        typedef btRigidBody CRigidBody;
        typedef btCollisionShape CCollisionPrimitive;
        typedef btSphereShape CCollisionSphere;
        typedef btBoxShape CCollisionBox;
        typedef btBvhTriangleMeshShape CCollisionTriangleMesh;
        typedef btCapsuleShape CCollisionCapsule;
    } // namespace physics
} // namespace fg

    #else
        #include "fgMaskTypes.h"
    #endif /* not using Bullet && not using Cyclone */

    #undef FG_INC_BULLET_MASK_TYPES_BLOCK
#endif /* FG_INC_BULLET_MASK_TYPES */
