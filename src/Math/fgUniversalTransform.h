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
 * File:   fgUniversalTransform.h
 * Author: vigilant
 *
 * Created on October 11, 2015, 10:39 PM
 */

#ifndef FG_INC_UNIVERSAL_TRANSFORM
    #define FG_INC_UNIVERSAL_TRANSFORM
    #define FG_INC_UNIVERSAL_TRANSFORM_BLOCK

    #include "fgVector3.h"
    #include "fgMatrix4.h"
    
namespace fg {
    namespace math {
        
        struct SUniversalTransform {

            SUniversalTransform() { }
            virtual ~SUniversalTransform() { }

            virtual void setTransform(const Matrix4f& inMatrix) = 0;
            virtual void getTransform(Matrix4f& outMatrix) const = 0;

            virtual void getTranslation(Vector3f& outTranslation) const = 0;

        }; // struct SUniversalTransform
    } // namespace math
} // namespace fg

    #undef FG_INC_UNIVERSAL_TRANSFORM_BLOCK
#endif	/* FG_INC_UNIVERSAL_TRANSFORM */
