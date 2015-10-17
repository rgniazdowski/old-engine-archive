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
 * File:   fgBoneSmallInfo.h
 * Author: vigilant
 *
 * Created on October 11, 2015, 10:54 PM
 */

#ifndef FG_BONE_SMALL_INFO
    #define FG_BONE_SMALL_INFO
    #define FG_BONE_SMALL_INFO_BLOCK

    #include "fgRagdollBoneType.h"

namespace fg {
    namespace physics {

        /**
         *
         */
        struct SBoneSmallInfo {
            typedef SBoneSmallInfo self_type;
            /**
             * 
             */
            SBoneSmallInfo() :
            boneType(BONE_INVALID),
            name(),
            parentIdx(-1),
            index(0),
            length(0.0f),
            startPoint(),
            endPoint() { }
            /**
             * 
             * @param orig
             */
            SBoneSmallInfo(const self_type& orig) {
                this->boneType = orig.boneType;
                this->name.append(orig.name);
                this->parentIdx = orig.parentIdx;
                this->index = orig.index;
                this->length = orig.length;
                this->startPoint = orig.startPoint;
                this->endPoint = orig.endPoint;
            }
            /**
             * 
             */
            virtual ~SBoneSmallInfo() { }

            /// Ragdoll bone type
            RagdollBoneType boneType;
            /// Name of the bone
            std::string name;
            /// Parent index
            int parentIdx;
            /// Self index
            int index;
            /// Length in local(mesh) units
            float length;
            /// Start point of this bone (in rest pose)
            Vec3f startPoint;
            /// End point of this bone (in rest pose)
            Vec3f endPoint;
            
            /**
             * 
             */
            void getCenterPoint(Vec3f& centerPoint) {
                centerPoint = this->startPoint + (this->endPoint - this->startPoint) / 2.0f;
            }
        }; // struct SBoneSmallInfo
    }
} // namespace fg

    #undef FG_BONE_SMALL_INFO_BLOCK
#endif	/* FG_BONE_SMALL_INFO */
