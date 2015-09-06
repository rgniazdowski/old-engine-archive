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
 * File:   fgGfxAnimationInfo.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 3:51 PM
 */

#ifndef FG_INC_GFX_ANIMATION_INFO
    #define FG_INC_GFX_ANIMATION_INFO
    #define FG_INC_GFX_ANIMATION_INFO_BLOCK

    #include "fgVector.h"
    #include "Math/fgMathLib.h"

namespace fg {
    namespace gfx {
        namespace anim {

            class CAnimation;

            /**
             *
             */
            struct SAnimationFrameInfo {
                typedef SAnimationFrameInfo self_type;
                typedef SAnimationFrameInfo type;

                typedef CVector<Matrix4f> MatricesVec;
                typedef MatricesVec::iterator MatricesVecItor;
                typedef MatricesVec::const_iterator MatricesVecConstItor;

                /// Current frame index 
                int index;
                /// Current elapsed time
                float elapsed;
                /// Array of up-to-date transformations;
                /// each matrix represents bone or node transformation matrix.
                MatricesVec transformations;

                //--------------------------------------------------------------

                /**
                 *
                 */
                SAnimationFrameInfo();
                /**
                 *
                 * @param other
                 */
                SAnimationFrameInfo(const self_type& other);
                /**
                 *
                 */
                virtual ~SAnimationFrameInfo();
                /**
                 *
                 */
                inline void clear(void) {
                    transformations.clear();
                }
                /**
                 * 
                 */
                inline void reset(void) {
                    index = 0;
                    elapsed = 0.0f;
                    clear();
                }
                /**
                 *
                 * @return
                 */
                inline unsigned int count(void) const {
                    return transformations.size();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool isEmpty(void) const {
                    return (fgBool)transformations.empty();
                }
            }; // struct SAnimationFrameInfo

            /**
             *
             */
            struct SAnimationInfo {
                typedef SAnimationInfo self_type;
                typedef SAnimationInfo type;

            public:
                /// External pointer to the currently used animation
                CAnimation* pAnimation;
                /// Information on currently calculated frame
                SAnimationFrameInfo currentFrame;

            public:
                /**
                 *
                 */
                SAnimationInfo(CAnimation* _pAnimation = NULL);
                /**
                 *
                 * @param orig
                 */
                SAnimationInfo(const SAnimationInfo& orig);
                /**
                 *
                 */
                virtual ~SAnimationInfo();

                /**
                 *
                 */
                void clear(void);
                /**
                 *
                 * @param elapsed
                 */
                void calculate(float elapsed = 0.0f);

            }; // struct SAnimationInfo

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIMATION_INFO_BLOCK
#endif	/* FG_INC_GFX_ANIMATION_INFO */
