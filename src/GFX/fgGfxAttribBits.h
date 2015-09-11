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
 * File:   fgGFXAttribBits.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:32 PM
 */

#ifndef FG_INC_GFX_ATTRIB_BITS
    #define FG_INC_GFX_ATTRIB_BITS
    #define FG_INC_GFX_ATTRIB_BITS_BLOCK

    #ifndef FG_INC_TYPES
        #include "fgTypes.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         *
         */
        enum AttributeLocation {
            ATTRIBUTE_POSITION_LOCATION = 0,
            ATTRIBUTE_NORMAL_LOCATION = 1,
            ATTRIBUTE_TEXTURE_COORD_LOCATION = 2,
            ATTRIBUTE_COLOR_LOCATION = 3,
            ATTRIBUTE_TANGENT_LOCATION = 4,
            ATTRIBUTE_BITANGENT_LOCATION = 5,
            ATTRIBUTE_BLEND_WEIGHTS_LOCATION = 6,
            ATTRIBUTE_BLEND_INDICES_LOCATION = 7
        }; // enum AttributeLocation

        enum AttributeMask {
            ATTRIBUTE_ZERO_BIT = 0x0000,
            ATTRIBUTE_POSITION_BIT = 0x0001,
            ATTRIBUTE_NORMAL_BIT = 0x0002,
            ATTRIBUTE_UVS_BIT = 0x0004,
            ATTRIBUTE_TEXTURE_COORD_BIT = ATTRIBUTE_UVS_BIT,
            ATTRIBUTE_COLOR_BIT = 0x0008,
            ATTRIBUTE_TANGENT_BIT = 0x0010,
            ATTRIBUTE_BITANGENT_BIT = 0x0020,
            ATTRIBUTE_BLEND_WEIGHTS_BIT = 0x0040,
            ATTRIBUTE_BLEND_INDICES_BIT = 0x0080,

            ///
            ATTRIBUTE_DEFAULT_MASK = ATTRIBUTE_POSITION_BIT +
            ATTRIBUTE_NORMAL_BIT +
            ATTRIBUTE_UVS_BIT,
            ///
            ATTRIBUTE_HIGH_QUALITY_MASK = ATTRIBUTE_POSITION_BIT +
            ATTRIBUTE_NORMAL_BIT +
            ATTRIBUTE_UVS_BIT +
            ATTRIBUTE_TANGENT_BIT +
            ATTRIBUTE_BITANGENT_BIT,
            ///
            ATTRIBUTE_SKINNED_MESH_MASK = ATTRIBUTE_POSITION_BIT +
            ATTRIBUTE_NORMAL_BIT +
            ATTRIBUTE_UVS_BIT +
            ATTRIBUTE_BLEND_WEIGHTS_BIT +
            ATTRIBUTE_BLEND_INDICES_BIT,
            ///
            ATTRIBUTE_HQ_SKINNED_MESK_MASK = ATTRIBUTE_POSITION_BIT +
            ATTRIBUTE_NORMAL_BIT +
            ATTRIBUTE_UVS_BIT +
            ATTRIBUTE_TANGENT_BIT +
            ATTRIBUTE_BITANGENT_BIT +
            ATTRIBUTE_BLEND_WEIGHTS_BIT +
            ATTRIBUTE_BLEND_INDICES_BIT
        }; // enum AttributeMask

        FG_ENUM_FLAGS(AttributeMask);

    } // namespace gfx
} // namespace fg

    #ifndef FG_GFX_ATTRIB_POS_LOCATION
        #define FG_GFX_ATTRIB_POS_LOCATION          0
    #endif

    #ifndef FG_GFX_ATTRIB_NORM_LOCATION
        #define FG_GFX_ATTRIB_NORM_LOCATION         1
    #endif

    #ifndef FG_GFX_ATTRIB_UVS_LOCATION
        #define FG_GFX_ATTRIB_UVS_LOCATION          2
    #endif

    #ifndef FG_GFX_ATTRIB_COLOR_LOCATION
        #define FG_GFX_ATTRIB_COLOR_LOCATION        3
    #endif

    #ifndef FG_GFX_ATTRIB_TANGENT_LOCATION
        #define FG_GFX_ATTRIB_TANGENT_LOCATION      4
    #endif

    #ifndef FG_GFX_ATTRIB_BITANGENT_LOCATION
        #define FG_GFX_ATTRIB_BITANGENT_LOCATION      5
    #endif

    #ifndef FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION
        #define FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION    6
    #endif

    #ifndef FG_GFX_ATTRIB_BLEND_INDICES_LOCATION
        #define FG_GFX_ATTRIB_BLEND_INDICES_LOCATION    7
    #endif

    #undef FG_INC_GFX_ATTRIB_BITS_BLOCK
#endif	/* FG_INC_GFX_ATTRIB_BITS */
