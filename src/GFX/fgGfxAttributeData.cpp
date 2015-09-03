/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxAttributeData.h"
#include "Util/fgStrings.h"

#define FG_GFX_POSITION_TEXT        "Position"      // Position (vec3)
#define FG_GFX_NORMAL_TEXT          "Normal"        // Normal (vec3)
#define FG_GFX_TEXTURE_COORD_TEXT   "TextureCoord"  // UV - tex coord (vec2)
#define FG_GFX_COLOR_TEXT           "Color"         // Color (vec4)
#define FG_GFX_TANGENT_TEXT         "Tangent"       // Tangent ?
#define FG_GFX_BITANGENT_TEXT       "Bitangent"
#define FG_GFX_BLEND_WEIGHTS_TEXT   "BlendWeights"
#define FG_GFX_BLEND_INDICES_TEXT   "BlendIndices"

namespace fg {
    namespace gfx {
        const AttributeType g_AttributeTypes[] = {
                                                  ATTRIBUTE_POSITION,
                                                  ATTRIBUTE_NORMAL,
                                                  ATTRIBUTE_TEXTURE_COORD,
                                                  ATTRIBUTE_COLOR,
                                                  ATTRIBUTE_TANGENT,
                                                  ATTRIBUTE_BITANGENT,
                                                  ATTRIBUTE_BLEND_WEIGHTS,
                                                  ATTRIBUTE_BLEND_INDICES
        };

        const AttributeLocation g_AttributeLocations[] = {
                                                          ATTRIBUTE_POSITION_LOCATION,
                                                          ATTRIBUTE_NORMAL_LOCATION,
                                                          ATTRIBUTE_TEXTURE_COORD_LOCATION,
                                                          ATTRIBUTE_COLOR_LOCATION,
                                                          ATTRIBUTE_TANGENT_LOCATION,
                                                          ATTRIBUTE_BITANGENT_LOCATION,
                                                          ATTRIBUTE_BLEND_WEIGHTS_LOCATION,
                                                          ATTRIBUTE_BLEND_INDICES_LOCATION
        };

        const char * const g_AttributeTypesText[] = {
                                                     FG_GFX_POSITION_TEXT,
                                                     FG_GFX_NORMAL_TEXT,
                                                     FG_GFX_TEXTURE_COORD_TEXT,
                                                     FG_GFX_COLOR_TEXT,
                                                     FG_GFX_TANGENT_TEXT,
                                                     FG_GFX_BITANGENT_TEXT,
                                                     FG_GFX_BLEND_WEIGHTS_TEXT,
                                                     FG_GFX_BLEND_INDICES_TEXT
        };
    } // namespace gfx
} // namespace fg

using namespace fg;
//------------------------------------------------------------------------------


gfx::AttributeType gfx::getAttributeTypeFromText(const char* text) {
    AttributeType result = AttributeType::ATTRIBUTE_INVALID;
    if(!text)
        return result;
    if(!text[0])
        return result;
    const unsigned int n = sizeof (g_AttributeTypes) / sizeof (AttributeType);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(g_AttributeTypesText[i], text, FG_FALSE)) {
            result = g_AttributeTypes[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::AttributeType gfx::getAttributeTypeFromText(const std::string& text) {
    return getAttributeTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

const char* gfx::getTextFromAttributeType(AttributeType value) {
    const char* result = NULL;
    if(value == ATTRIBUTE_INVALID)
        return result;
    const unsigned int n = sizeof (g_AttributeTypes) / sizeof (AttributeType);
    for(unsigned int i = 0; i < n; i++) {
        if(g_AttributeTypes[i] == value) {
            result = g_AttributeTypesText[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::AttributeLocation gfx::getAttributeLocationFromType(AttributeType value) {
    AttributeLocation result = static_cast<AttributeLocation>(value);
    return result;
}
//------------------------------------------------------------------------------

void gfx::getAttributeLocationFromType(unsigned int& location, AttributeType value) {
    if(value == ATTRIBUTE_INVALID) {
        location = 0;
    } else {
        location = static_cast<unsigned int>(value);
    }
}
//------------------------------------------------------------------------------

gfx::AttributeType gfx::getAttributeTypeFromLocation(AttributeLocation location) {
    AttributeType result = static_cast<AttributeType>(location);
    return result;
}
//------------------------------------------------------------------------------

gfx::AttributeType gfx::getAttributeTypeFromLocation(unsigned int location) { 
    AttributeType result = ATTRIBUTE_INVALID;
    if(location >= static_cast<unsigned int>(NUM_ATTRIBUTE_TYPES))
        return result;
    result = static_cast<AttributeType>(location);
    return result;
}
//------------------------------------------------------------------------------

fgGFXenum gfx::getDataTypeFromAttributeType(AttributeType value) {
    fgGFXenum result = FG_GFX_FALSE;
    switch(value) {
        case ATTRIBUTE_POSITION:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4; // 3?
            break;
        case ATTRIBUTE_NORMAL:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC3;
            break;
        case ATTRIBUTE_COLOR:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4;
            break;
        case ATTRIBUTE_TEXTURE_COORD:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC2;
            break;
        case ATTRIBUTE_TANGENT:
        case ATTRIBUTE_BITANGENT:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC3;
            break;
        case ATTRIBUTE_BLEND_WEIGHTS:
        case ATTRIBUTE_BLEND_INDICES:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4;
            break;
        default:
            break;
    }
    return result;
}
//------------------------------------------------------------------------------

fgGFXenum gfx::getDataTypeFromAttributeLocation(AttributeLocation location) {
    fgGFXenum result = FG_GFX_FALSE;
    switch(location) {
        case ATTRIBUTE_POSITION_LOCATION:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4; // 3?
            break;
        case ATTRIBUTE_NORMAL_LOCATION:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC3;
            break;
        case ATTRIBUTE_COLOR_LOCATION:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4;
            break;
        case ATTRIBUTE_TEXTURE_COORD_LOCATION:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC2;
            break;
        case ATTRIBUTE_TANGENT_LOCATION:
        case ATTRIBUTE_BITANGENT_LOCATION:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC3;
            break;
        case ATTRIBUTE_BLEND_WEIGHTS_LOCATION:
        case ATTRIBUTE_BLEND_INDICES_LOCATION:
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4;
            break;
        default:
            break;
    }
    return result;
}
//------------------------------------------------------------------------------

fgGFXenum gfx::getDataTypeFromAttributeLocation(unsigned int location) {
    fgGFXenum result = FG_GFX_FALSE;
    switch(location) {
        case static_cast<unsigned int>(ATTRIBUTE_POSITION_LOCATION):
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4; // 3?
            break;
        case static_cast<unsigned int>(ATTRIBUTE_NORMAL_LOCATION):
            result = (fgGFXenum)FG_GFX_FLOAT_VEC3;
            break;
        case static_cast<unsigned int>(ATTRIBUTE_COLOR_LOCATION):
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4;
            break;
        case static_cast<unsigned int>(ATTRIBUTE_TEXTURE_COORD_LOCATION):
            result = (fgGFXenum)FG_GFX_FLOAT_VEC2;
            break;
        case static_cast<unsigned int>(ATTRIBUTE_TANGENT_LOCATION):
        case static_cast<unsigned int>(ATTRIBUTE_BITANGENT_LOCATION):
            result = (fgGFXenum)FG_GFX_FLOAT_VEC3;
            break;
        case static_cast<unsigned int>(ATTRIBUTE_BLEND_WEIGHTS_LOCATION):
        case static_cast<unsigned int>(ATTRIBUTE_BLEND_INDICES_LOCATION):
            result = (fgGFXenum)FG_GFX_FLOAT_VEC4;
            break;
        default:
            break;
    }
    return result;
}
//------------------------------------------------------------------------------
