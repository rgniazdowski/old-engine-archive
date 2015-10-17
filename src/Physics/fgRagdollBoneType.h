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
 * File:   fgRagdollBoneType.h
 * Author: vigilant
 *
 * Created on October 11, 2015, 10:14 PM
 */

#ifndef FG_INC_RAGDOLL_BONE_TYPE
    #define FG_INC_RAGDOLL_BONE_TYPE
    #define FG_INC_RAGDOLL_BONE_TYPE_BLOCK

namespace fg {
    namespace physics {

        /**
         *
         */
        enum RagdollBoneType {
            BONE_INVALID = 0,

            BONE_HEAD,
            BONE_NECK,

            BONE_ARM_LEFT,
            BONE_ARM_RIGHT,

            BONE_FOREARM_LEFT,
            BONE_FOREARM_RIGHT,

            BONE_HAND_LEFT,
            BONE_HAND_RIGHT,

            BONE_HAND_LEFT_THUMB,
            BONE_HAND_LEFT_FINGER1 = BONE_HAND_LEFT_THUMB,
            BONE_HAND_LEFT_FINGER2,
            BONE_HAND_LEFT_FINGER3,
            BONE_HAND_LEFT_FINGER4,
            BONE_HAND_LEFT_FINGER5,

            BONE_HAND_RIGHT_THUMB,
            BONE_HAND_RIGHT_FINGER1 = BONE_HAND_RIGHT_THUMB,
            BONE_HAND_RIGHT_FINGER2,
            BONE_HAND_RIGHT_FINGER3,
            BONE_HAND_RIGHT_FINGER4,
            BONE_HAND_RIGHT_FINGER5,

            BONE_SPINE,
            BONE_PELVIS,
            BONE_THIGH_LEFT,
            BONE_THIGH_RIGHT,
            BONE_LEG_LEFT,
            BONE_LEG_RIGHT,
            BONE_FOOT_LEFT,
            BONE_FOOT_RIGHT,

            BONE_FOOT_LEFT_TOE_BIG,
            BONE_FOOT_LEFT_TOE_HALLUX = BONE_FOOT_LEFT_TOE_BIG,
            BONE_FOOT_LEFT_TOE1 = BONE_FOOT_LEFT_TOE_BIG,
            BONE_FOOT_LEFT_TOE2,
            BONE_FOOT_LEFT_TOE3,
            BONE_FOOT_LEFT_TOE4,
            BONE_FOOT_LEFT_TOE5,

            BONE_FOOT_RIGHT_TOE_BIG,
            BONE_FOOT_RIGHT_TOE_HALLUX = BONE_FOOT_RIGHT_TOE_BIG,
            BONE_FOOT_RIGHT_TOE1 = BONE_FOOT_RIGHT_TOE_BIG,
            BONE_FOOT_RIGHT_TOE2,
            BONE_FOOT_RIGHT_TOE3,
            BONE_FOOT_RIGHT_TOE4,
            BONE_FOOT_RIGHT_TOE5,

            BONE_FACE_EXTRA,
            BONE_BACK_EXTRA,
            BONE_FRONT_EXTRA,
            BONE_LEFT_EXTRA,
            BONE_RIGHT_EXTRA,
            BONE_UP_EXTRA,
            BONE_DOWN_EXTRA,

            NUM_BONE_TYPES
        }; // enum RagdollBoneType

    } // namespace physics
} // namespace fg

    #undef FG_INC_RAGDOLL_BONE_TYPE_BLOCK
#endif	/* FG_INC_RAGDOLL_BONE_TYPE */
