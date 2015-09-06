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
 * File:   fgGfxBone.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 3:52 PM
 */

#ifndef FG_INC_GFX_BONE
    #define FG_INC_GFX_BONE
    #define FG_INC_GFX_BONE_BLOCK

    #include "Math/fgMathLib.h"
    #include "fgVector.h"

namespace fg {
    namespace gfx {
        namespace anim {

            /**
             *
             */
            struct SVertexWeight {
                typedef SVertexWeight self_type;
                typedef SVertexWeight type;

                ///
                int vertexIdx;
                ///
                float weight;
                /**
                 *
                 */
                SVertexWeight() : vertexIdx(0), weight(0.0f) { }
                /**
                 * 
                 * @param _vertexIdx
                 * @param _weight
                 */
                SVertexWeight(int _vertexIdx, float _weight) :
                vertexIdx(_vertexIdx), weight(_weight) { }
                /**
                 *
                 * @param other
                 */
                SVertexWeight(const self_type& other) {
                    vertexIdx = other.vertexIdx;
                    weight = other.weight;
                }
                /**
                 *
                 */
                virtual ~SVertexWeight() {
                    vertexIdx = 0;
                    weight = 0.0f;
                }
            }; // struct SVertexWeight

            /**
             *
             */
            struct SBone {
                typedef SBone self_type;
                typedef SBone type;
                typedef CVector<SVertexWeight> WeightsVec;
                typedef WeightsVec::iterator WeightsVecItor;

                typedef CVector<SBone*> BonesVec;
                typedef BonesVec::iterator BonesVecItor;
                typedef BonesVec::const_iterator BonesVecConstItor;

                /**
                 *
                 */
                SBone();
                /**
                 *
                 * @param orig
                 */
                SBone(const SBone& orig);
                /**
                 *
                 */
                virtual ~SBone();

                /**
                 *
                 */
                void clear(void);

                /**
                 *
                 */
                void destroyChildren(void);

                /**
                 *
                 * @param name
                 * @return
                 */
                SBone* findBone(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                SBone* findBone(const char* name);

                /**
                 *
                 * @param pBone
                 * @return
                 */
                fgBool hasChild(SBone* pBone);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool hasChild(const std::string& name);
                /**
                 * 
                 * @param name
                 * @return
                 */
                fgBool hasChild(const char* name);

                /**
                 * 
                 * @param pBone
                 * @return
                 */
                fgBool removeChild(SBone* pBone);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool removeChild(const std::string& name);
                /**
                 *
                 * @param name
                 * @return
                 */
                fgBool removeChild(const char* name);

            public:
                ///
                std::string name;
                ///
                self_type* pParent;
                ///
                int parentIdx;
                ///
                int index;
                ///
                Matrix4f bindPoseMatrix;
                ///
                Matrix4f offset;
                ///
                WeightsVec weights;
                ///
                BonesVec children;
            }; // struct SBone

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_BONE_BLOCK
#endif	/* FG_INC_GFX_BONE */
