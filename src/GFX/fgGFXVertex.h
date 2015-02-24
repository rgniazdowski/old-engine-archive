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
 * File:   fgGFXVertex.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:24 PM
 */

#ifndef FG_INC_GFX_VERTEX
    #define FG_INC_GFX_VERTEX
    #define FG_INC_GFX_VERTEX_BLOCK

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #ifndef FG_INC_GFX_COLOR
        #include "fgGFXColor.h"
    #endif

    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

    #ifndef FG_INC_GFX_ATTRIB_BITS
        #include "fgGFXAttribBits.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         * Vertex4 - pos, norm, uv, color
         */
        struct Vertex4v {
            ///
            typedef Vertex4v type;
            ///
            typedef Vertex4v self_type;

            ///
            fg::Vector3f position; // location 0
            ///
            fg::Vector3f normal; // location 1
            ///
            fg::Vector2f uv; // location 2
            ///
            fgColor4f color; // location 3
            /**
             * 
             * @return 
             */
            static unsigned int size(void) {
                return 4;
            }
            /**
             * 
             * @return 
             */
            static unsigned int attribMask(void) {
                return FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT;
            }
            /**
             * 
             * @return 
             */
            static unsigned int stride(void) {
                return sizeof (type);
            }
        };

        /**
         * Vertex3 - pos, norm, uv
         */
        struct Vertex3v {
            ///
            typedef Vertex3v type;
            ///
            typedef Vertex3v self_type;

            ///
            fg::Vector3f position;
            ///
            fg::Vector3f normal;
            ///
            fg::Vector2f uv;
            /**
             * 
             * @return 
             */
            static unsigned int size(void) {
                return 3;
            }
            /**
             * 
             * @return 
             */
            static unsigned int attribMask(void) {
                return FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT;
            }
            /**
             * 
             * @return 
             */
            static unsigned int stride(void) {
                return sizeof (type);
            }
        };

        /**
         * Vertex2 - pos, uv
         */
        struct Vertex2v {
            ///
            typedef Vertex2v type;
            ///
            typedef Vertex2v self_type;

            ///
            fg::Vector3f position;
            ///
            fg::Vector2f uv;
            /**
             * 
             * @return 
             */
            static unsigned int size(void) {
                return 2;
            }
            /**
             * 
             * @return 
             */
            static unsigned int attribMask(void) {
                return FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT;
            }
            /**
             * 
             * @return 
             */
            static unsigned int stride(void) {
                return sizeof (type);
            }
        };
    };
};
    #include <cstdio>
inline void dumpVector(const fg::Vector3f & vec, const char *title) {
    printf("%s = { %.2f %.2f %.2f }\n", (title ? title : "X"), vec.x, vec.y, vec.z);
}


    #undef FG_INC_GFX_VERTEX_BLOCK
#endif	/* FG_INC_GFX_VERTEX */
