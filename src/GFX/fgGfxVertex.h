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
        #include "fgGfxColor.h"
    #endif

    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

    #ifndef FG_INC_GFX_ATTRIB_BITS
        #include "fgGfxAttribBits.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         * Vertex4v - pos, norm, uv, color
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
                return sizeof (self_type);
            }
        };

        /**
         * Vertex3v - pos, norm, uv
         */
        struct Vertex3v {
            ///
            typedef Vertex3v type;
            ///
            typedef Vertex3v self_type;

            ///
            fg::Vector3f position; // 0
            ///
            fg::Vector3f normal; // 1
            ///
            fg::Vector2f uv; // 2
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
                return sizeof (self_type);
            }
        };

        /**
         * Vertex2v - pos, uv
         */
        struct Vertex2v {
            ///
            typedef Vertex2v type;
            ///
            typedef Vertex2v self_type;

            ///
            fg::Vector3f position; // 0
            ///
            fg::Vector2f uv; // 2
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
                return sizeof (self_type);
            }
        };

        ////////////////////////////////////////////////////////////////////////
        // Vertex lists

        /**
         * Vertex4vl - pos, norm, uv, color
         */
        struct Vertex4vl {
            ///
            typedef Vertex4vl type;
            ///
            typedef Vertex4vl self_type;

            ///
            fg::Vector3f position; // location 0
            ///
            fg::Vector3f normal; // location 1
            ///
            fg::Vector2f uv; // location 2
            ///
            fgColor4f color; // location 3
            ///
            self_type *vnext;
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
                return sizeof (self_type);
            }
        };

        /**
         * Vertex3vl - pos, norm, uv
         */
        struct Vertex3vl {
            ///
            typedef Vertex3vl type;
            ///
            typedef Vertex3vl self_type;

            ///
            fg::Vector3f position; // 0
            ///
            fg::Vector3f normal; // 1
            ///
            fg::Vector2f uv; // 2
            ///
            self_type *vnext;
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
                return sizeof (self_type);
            }
        };

        /**
         * Vertex2vl - pos, uv
         */
        struct Vertex2vl {
            ///
            typedef Vertex2vl type;
            ///
            typedef Vertex2vl self_type;

            ///
            fg::Vector3f position; // 0
            ///
            fg::Vector2f uv; // 2
            ///
            self_type *vnext;
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
                return sizeof (self_type);
            }
        };
    };
};

    #undef FG_INC_GFX_VERTEX_BLOCK
#endif	/* FG_INC_GFX_VERTEX */
