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
 * File:   fgGfxBlendingInfo.h
 * Author: vigilant
 *
 * Created on September 16, 2015, 6:12 PM
 */

#ifndef FG_INC_GFX_ANIM_BLENDING_INFO
    #define FG_INC_GFX_ANIM_BLENDING_INFO
    #define FG_INC_GFX_ANIM_BLENDING_INFO_BLOCK

    #include "fgTypes.h"

namespace fg {
    namespace gfx {
        namespace anim {

            class CAnimation;
            class CBoneAnimation;

            /**
             *
             */
            struct SWeightPair : public std::pair<float, float> {
                typedef SWeightPair self_type;
                typedef std::pair<float, float> base_type;

                /**
                 *
                 */
                SWeightPair();
                /**
                 *
                 * @param _first
                 * @param _second
                 */
                SWeightPair(float _first, float _second);
                /**
                 *
                 * @param other
                 */
                SWeightPair(const SWeightPair& other);
                /**
                 *
                 * @param other
                 * @return
                 */
                SWeightPair& operator =(const SWeightPair& other);

                /**
                 *
                 * @param _first
                 * @param _second
                 */
                void getFlipped(float& _first, float& _second) const;
                /**
                 *
                 * @param _first
                 * @param _second
                 */
                void get(float& _first, float& _second) const;
                /**
                 *
                 * @param _first
                 * @param _second
                 */
                void getFlipped(float* _first, float* _second) const;
                /**
                 * 
                 * @param _first
                 * @param _second
                 */
                void get(float* _first, float* _second) const;
            }; // struct SPairWeight
            //------------------------------------------------------------------

            /**
             *
             */
            struct SBlendingPair {
                typedef SBlendingPair self_type;
                typedef std::pair<CAnimation*, CAnimation*> AnimationPair;
                typedef CVector<SWeightPair> WeightsVec;

                ///
                AnimationPair animation;
                ///
                WeightsVec weights;
                //--------------------------------------------------------------

                /**
                 *
                 */
                SBlendingPair();
                /**
                 *
                 * @param orig
                 */
                SBlendingPair(const self_type& orig);
                /**
                 *
                 */
                ~SBlendingPair();

                /**
                 *
                 * @param pFirst
                 * @param pSecond
                 * @return
                 */
                fgBool isFlipped(const CAnimation* pFirst, const CAnimation* pSecond);
                /**
                 *
                 * @param pair
                 * @return
                 */
                fgBool isFlipped(const AnimationPair& pair);
            }; // struct SBlendingPair
            //------------------------------------------------------------------

            /**
             *
             */
            struct SBlendingInfo : public CVector<SBlendingPair> {
                typedef SBlendingInfo self_type;
                typedef SBlendingInfo type;
                typedef CVector<SBlendingPair> base_type;

                typedef std::pair<CAnimation*, CAnimation*> AnimationPair;
                typedef CVector<SWeightPair> WeightsVec;

                //--------------------------------------------------------------
                /**
                 *
                 */
                SBlendingInfo();
                /**
                 *
                 * @param orig
                 */
                SBlendingInfo(const SBlendingInfo& orig);
                /**
                 *
                 */
                virtual ~SBlendingInfo();

                //--------------------------------------------------------------
                /**
                 *
                 * @param pFirst
                 * @param pSecond
                 * @return
                 */
                fgBool hasPair(CAnimation* pFirst,
                               CAnimation* pSecond) const;
                /**
                 *
                 * @param pair
                 * @return
                 */
                fgBool hasPair(const AnimationPair& pair) const;

                using base_type::find;
                /**
                 *
                 * @param pFirst
                 * @param pSecond
                 * @return
                 */
                int find(CAnimation* pFirst,
                         CAnimation* pSecond) const;
                /**
                 *
                 * @param pair
                 * @return
                 */
                int find(const AnimationPair& pair) const;

                //--------------------------------------------------------------
                /**
                 *
                 * @param pair
                 * @return
                 */
                SBlendingPair* get(const AnimationPair& pair);
                /**
                 *
                 * @param pair
                 * @return
                 */
                SBlendingPair const* get(const AnimationPair& pair) const;
                /**
                 *
                 * @param pFirst
                 * @param pSecond
                 * @return
                 */
                SBlendingPair* get(CAnimation* pFirst,
                                   CAnimation* pSecond);
                /**
                 * 
                 * @param pFirst
                 * @param pSecond
                 * @return
                 */
                SBlendingPair const* get(CAnimation* pFirst, CAnimation* pSecond) const;

            }; // struct SBlendingInfo

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIM_BLENDING_INFO_BLOCK
#endif	/* FG_INC_GFX_ANIM_BLENDING_INFO */
