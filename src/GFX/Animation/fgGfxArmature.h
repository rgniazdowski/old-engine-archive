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
 * File:   fgGfxArmature.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 3:50 PM
 */

#ifndef FG_INC_GFX_ARMATURE
    #define FG_INC_GFX_ARMATURE
    #define FG_INC_GFX_ARMATURE_BLOCK

    #include "fgGfxBone.h"
    #include "fgVector.h"
    #include "Util/fgBTreeMap.h"

namespace fg {
    namespace gfx {
        namespace anim {

            /**
             *
             */
            class CArmature {
            public:
                typedef CArmature self_type;
                typedef CArmature type;

                typedef CVector<SBone *> BonesVec;
                typedef BonesVec::iterator BonesVecItor;
                typedef BonesVec::const_iterator BonesVecConstItor;

                typedef util::btree_map<std::string, SBone *> BonesMap;
                typedef BonesMap::iterator BonesMapItor;
                typedef BonesMap::const_iterator BonesMapConstItor;

            public:
                /**
                 *
                 */
                CArmature();
                /**
                 *
                 * @param orig
                 */
                CArmature(const CArmature& orig);
                /**
                 *
                 */
                virtual ~CArmature();

                //--------------------------------------------------------------

                /**
                 *
                 * @param index
                 * @return
                 */
                SBone* at(unsigned int index);
                /**
                 *
                 * @param index
                 * @return
                 */
                SBone const* at(unsigned int index) const;

                /**
                 *
                 * @param name
                 * @return
                 */
                SBone* get(const char* name);
                /**
                 *
                 * @param name
                 * @return
                 */
                SBone* get(const std::string& name);

                /**
                 * 
                 * @return
                 */
                fgBool add(const SBone& bone);

                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool remove(const char* name);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool remove(const std::string& name);
                /**
                 * 
                 * @return 
                 */
                unsigned int count(void) const {
                    return m_bones.size();
                }
                /**
                 * 
                 * @return 
                 */
                fgBool isEmpty(void) const {
                    return (fgBool)m_bones.empty();
                }
                /**
                 * 
                 * @return 
                 */
                BonesVec& getBones(void) {
                    return m_bones;
                }
                /**
                 * 
                 * @return 
                 */
                BonesVec const& getBones(void) const {
                    return m_bones;
                }

                /**
                 * 
                 */
                void clear(void);

            private:
                ///
                BonesVec m_bones;
                ///
                BonesMap m_bonesMap;
            }; // class CArmature

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ARMATURE_BLOCK
#endif	/* FG_INC_GFX_ARMATURE */
