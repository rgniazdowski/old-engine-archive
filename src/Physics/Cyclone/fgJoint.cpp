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
 * Implementation file for joints.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgBuildConfig.h"
#if !defined(FG_USING_BULLET) && defined(FG_USING_CYCLONE)
#include "fgPrecision.h"
#include "fgJoint.h"
#include "Math/fgMathLib.h"

using namespace fg;
//------------------------------------------------------------------------------

unsigned physics::CJoint::addContact(CContact *contact, unsigned limit) const {
    // Calculate the position of each connection point in world coordinates
    Vector3f a_pos_world = body[0]->getPointInWorldSpace(position[0]);
    Vector3f b_pos_world = body[1]->getPointInWorldSpace(position[1]);

    // Calculate the length of the joint
    Vector3f a_to_b = b_pos_world - a_pos_world;
    Vector3f normal = a_to_b;
    //normal.normalise();
    normal = math::normalize(normal);
    real length = math::length(a_to_b); //a_to_b.magnitude();

    // Check if it is violated
    if(real_abs(length) > error) {
        contact->body[0] = body[0];
        contact->body[1] = body[1];
        contact->contactNormal = normal;
        contact->contactPoint = (a_pos_world + b_pos_world) * 0.5f;
        contact->penetration = length - error;
        contact->friction = 1.0f;
        contact->restitution = 0;
        return 1;
    }

    return 0;
}
//------------------------------------------------------------------------------

void physics::CJoint::set(CRigidBody *a, const Vector3f& a_pos,
                          CRigidBody *b, const Vector3f& b_pos,
                          real error) {
    body[0] = a;
    body[1] = b;

    position[0] = a_pos;
    position[1] = b_pos;

    physics::CJoint::error = error;
}
//------------------------------------------------------------------------------
#endif /* FG_USING_BULLET */
