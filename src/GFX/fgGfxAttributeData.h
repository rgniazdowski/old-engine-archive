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
 * File:   fgGFXAttributeData.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 7:04 PM
 */

#ifndef FG_INC_GFX_ATTRIBUTE_DATA
    #define FG_INC_GFX_ATTRIBUTE_DATA
    #define FG_INC_GFX_ATTRIBUTE_DATA_BLOCK

    #ifndef FG_INC_GFX_GL
        #include "fgGfxGL.h"
    #endif

    #ifndef FG_INC_GFX_ATTRIB_BITS
        #include "fgGfxAttribBits.h"
    #endif

    #ifndef FG_GFX_ATTR_TYPE_DEFINED
        #define FG_GFX_ATTR_TYPE_DEFINED
// Attribute type also corresponds to bound attribute location
namespace fg {
    namespace gfx {

        enum AttributeType {
            FG_GFX_ATTRIBUTE_INVALID = -1,
            FG_GFX_POSITION = FG_GFX_ATTRIB_POS_LOCATION,
            FG_GFX_NORMAL = FG_GFX_ATTRIB_NORM_LOCATION,
            FG_GFX_TEXTURE_COORD = FG_GFX_ATTRIB_UVS_LOCATION,
            FG_GFX_COLOR = FG_GFX_ATTRIB_COLOR_LOCATION,
            FG_GFX_TANGENT = FG_GFX_ATTRIB_TANGENT_LOCATION
        };
    };
};
    #endif

namespace fg {
    namespace gfx {

        /*
         * Attribute raw data parameters
         * This is not to use within the shader / shader program structure
         * This data is used for draw calls. Shader hold more general data
         * about the attribute binds (location)
         * #FIXME - needs different location
         */
        struct SAttributeData {
            /// Index of the generic vertex attribute to be modified.
            fgGFXint index;
            /// Number of components per generic vertex attribute. 
            /// Must be 1,2,3 or 4. (default is 3)
            fgGFXint size;
            // The engine specific attribute type
            AttributeType type;
            /// Specifies the data type of each component in the array.
            /// Possible values: BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, FIXED and FLOAT.
            fgGFXenum dataType;
            /// The byte offset between between consecutive generic vertex attributes.
            /// For structures and interleaved data this will be sizeof(struct/Vertex)
            fgGFXsizei stride;

            union {
                // Pointer to the vertex data
                fgGFXvoid *pointer;
                // Offset if vertex buffer object is used
                fgGFXvoid *offset;
            };
            /// Specifies whether data values should be normalized
            fgGFXboolean isNormalized;
            /// Is data interleaved? This is important, if data is not interleaved then
            /// it means that vertices, normals, UVS, colors etc are in separate arrays
            /// (Struct of arrays) and/or separate buffer objects (isBO).
            /// If true then Array of structs is used and one vertex buffer (additionally
            /// another buffer for indeces)
            fgGFXboolean isInterleaved;
            /// Is attribute data bound to vertex/index buffer?
            /// Note: attribute data used for index buffer cannot be bound to attribute in the shader
            /// It is used for indexed drawing - it's additional 3D data (glDrawElements)
            fgGFXboolean isBO;
            /// Is this attribute enabled?
            fgGFXboolean isEnabled;
            /// Bound buffer id
            fgGFXuint buffer;

            // Main constructor
            SAttributeData(const AttributeType _type = FG_GFX_POSITION) :
            index(_type),
            size(3),
            type(_type),
            dataType(FG_GFX_FLOAT),
            stride(0),
            pointer(NULL),
            isNormalized(FG_GFX_FALSE),
            isInterleaved(FG_GFX_TRUE),
            isBO(FG_GFX_FALSE),
            isEnabled(FG_GFX_FALSE),
            buffer(0) { }

            // Comparison operator
            inline int operator ==(const SAttributeData& b) const {
                return (b.index == this->index);
            }

            // Comparison not equal operator (this checks only for index)
            inline int operator !=(const SAttributeData& b) const {
                return !(b.index == this->index);
            }

            // Comparison operator - greater than
            inline bool operator >(const SAttributeData& a) const {
                return (int)(this->index) > (int)(a.index);
            }

            // Comparison operator - less than
            inline bool operator <(const SAttributeData& a) const {
                return (int)(this->index) < (int)(a.index);
            }

            // Comparison operator - greater/equal than
            inline bool operator >=(const SAttributeData& a) const {
                return (int)(this->index) >= (int)(a.index);
            }

            // Comparison operator - less/equal than
            inline bool operator <=(const SAttributeData& a) const {
                return (int)(this->index) <= (int)(a.index);
            }
        };
    };
};
    #ifndef FG_GFX_ATTRIBUTE_DATA_MAX
        #define FG_GFX_ATTRIBUTE_DATA_MAX 12 // #FIXME
    #endif

    #undef FG_INC_GFX_ATTRIBUTE_DATA_BLOCK
#endif	/* FG_INC_GFX_ATTRIBUTE_DATA */
