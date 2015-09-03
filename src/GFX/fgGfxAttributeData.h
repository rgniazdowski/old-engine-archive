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



namespace fg {
    namespace gfx {
    #ifndef FG_GFX_ATTRIBUTE_TYPE_DEFINED
        #define FG_GFX_ATTRIBUTE_TYPE_DEFINED

        /**
         * Attribute type also corresponds to bound attribute location
         */
        enum AttributeType {
            ///
            ATTRIBUTE_INVALID = -1,
            ///
            ATTRIBUTE_POSITION = FG_GFX_ATTRIB_POS_LOCATION,
            ///
            ATTRIBUTE_NORMAL = FG_GFX_ATTRIB_NORM_LOCATION,
            ///
            ATTRIBUTE_TEXTURE_COORD = FG_GFX_ATTRIB_UVS_LOCATION,
            ///
            ATTRIBUTE_COLOR = FG_GFX_ATTRIB_COLOR_LOCATION,
            ///
            ATTRIBUTE_TANGENT = FG_GFX_ATTRIB_TANGENT_LOCATION,
            ///
            ATTRIBUTE_BITANGENT = FG_GFX_ATTRIB_BITANGENT_LOCATION,
            ///
            ATTRIBUTE_BLEND_WEIGHTS = FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION,
            ///
            ATTRIBUTE_BLEND_INDICES = FG_GFX_ATTRIB_BLEND_INDICES_LOCATION,
            ///
            NUM_ATTRIBUTE_TYPES
        };
    #endif

        //----------------------------------------------------------------------

        /**
         *
         * @param text
         * @return
         */
        AttributeType getAttributeTypeFromText(const char* text);
        /**
         *
         * @param text
         * @return
         */
        AttributeType getAttributeTypeFromText(const std::string& text);
        /**
         *
         * @param value
         * @return
         */
        const char* getTextFromAttributeType(AttributeType value);

        AttributeLocation getAttributeLocationFromType(AttributeType value);
        void getAttributeLocationFromType(unsigned int& location, AttributeType value);
        AttributeType getAttributeTypeFromLocation(AttributeLocation location);
        AttributeType getAttributeTypeFromLocation(unsigned int location);

        fgGFXenum getDataTypeFromAttributeType(AttributeType value);
        fgGFXenum getDataTypeFromAttributeLocation(AttributeLocation location);
        fgGFXenum getDataTypeFromAttributeLocation(unsigned int location);
        //----------------------------------------------------------------------

        ///
        //extern const AttributeType g_AttributeTypes[];
        ///
        //extern const AttributeLocation g_AttributeLocations[];
        ///
        //extern const char * const g_AttributeTypesText[];
    }
}

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
            SAttributeData(const AttributeType _type = ATTRIBUTE_POSITION) :
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

        }; // struct SAttributeData
    } // namespace gfx
} // namespace fg

    #ifndef FG_GFX_ATTRIBUTE_DATA_MAX
        #define FG_GFX_ATTRIBUTE_DATA_MAX 12 // #FIXME
    #endif

    #undef FG_INC_GFX_ATTRIBUTE_DATA_BLOCK
#endif	/* FG_INC_GFX_ATTRIBUTE_DATA */
