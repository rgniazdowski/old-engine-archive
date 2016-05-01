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
 * File:   fgGfxSkinningInfo.h
 * Author: vigilant
 *
 * Created on September 16, 2015, 6:05 PM
 */

#ifndef FG_INC_GFX_ANIM_SKINNING_INFO
    #define FG_INC_GFX_ANIM_SKINNING_INFO
    #define FG_INC_GFX_ANIM_SKINNING_INFO_BLOCK

    #include "fgGfxBlendingInfo.h"    
    #include "fgGfxBoneAnimation.h"
    #include "Util/fgBTreeMap.h"


namespace fg {
    namespace gfx {
        namespace anim {

            /**
             * 
             */
            struct SSkinningInfo {
                typedef SSkinningInfo self_type;
                typedef SSkinningInfo type;

                typedef CVector<SBone*> BonesVec;

                typedef util::btree_map<BoneType, BonesVec> BoneTypesMap;
                typedef BoneTypesMap::iterator BoneTypesMapItor;
                typedef BoneTypesMap::const_iterator BoneTypesMapConstItor;

                typedef util::btree_map<StandardActionType, std::string> ActionsMap;
                typedef ActionsMap::iterator ActionsMapItor;
                typedef ActionsMap::const_iterator ActionsMapConstItor;

                typedef util::btree_map<StandardActionType, Vec3f> RootMotionsMap;
                typedef RootMotionsMap::iterator RootMotionsMapItor;
                typedef RootMotionsMap::const_iterator RootMotionsMapConstItor;

                /**
                 *
                 */
                SSkinningInfo();
                /**
                 *
                 * @param orig
                 */
                SSkinningInfo(const SSkinningInfo& orig);
                /**
                 *
                 */
                virtual ~SSkinningInfo();
                //--------------------------------------------------------------

                /**
                 *
                 * @param animationName
                 * @return
                 */
                StandardActionType getActionType(const std::string& animationName);
                /**
                 *
                 * @param animationName
                 * @return
                 */
                StandardActionType getActionType(const char* animationName);

                fgBool hasAction(StandardActionType actionType) const;

                fgBool hasRootMotion(StandardActionType actionType) const;

                fgBool hasBone(BoneType boneType) const;

                SBone* getBone(BoneType boneType, unsigned int index = 0);

                const SBone* getBone(BoneType boneType, unsigned int index = 0) const;

                //--------------------------------------------------------------
                ///
                SBlendingInfo armatureInfo;
                ///
                BoneTypesMap boneTypesMap;
                ///
                ActionsMap actionsMap;
                ///
                RootMotionsMap rootMotionsMap;
            }; // struct SSkinningInfo

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIM_SKINNING_INFO_BLOCK
#endif	/* FG_INC_GFX_ANIM_SKINNING_INFO */
