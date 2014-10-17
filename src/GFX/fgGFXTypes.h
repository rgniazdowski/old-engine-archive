/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_TYPES_H_
    #define _FG_GFX_TYPES_H_
    #define _FG_GFX_TYPES_BLOCK__

    #ifdef _FG_TYPES_BLOCK__
        #error "FG_TYPES_BLOCK constant is defined. Do not include fgGfxTypes header inside of fgTypes header."
    #endif

    #ifndef _FG_GFX_GL_H_
        #include "fgGFXGL.h"
    #endif

    #ifndef _FG_GFX_COLOR_H_
        #include "fgGFXColor.h"
    #endif

    #ifndef FG_GFX_NONE
        #define FG_GFX_NONE 0
    #endif

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

    #ifndef _FG_GFX_ATTRIB_BITS_H_
        #include "fgGFXAttribBits.h"
    #endif

//
// Data types
//

//	bool	-	a conditional type, taking on values of true or false
//	int	-	a signed integer
//	float	-	a single floating-point scalar
//	vec2	-	a two component floating-point vector
//	vec3	-	a three component floating-point vector
//	vec4	-	a four component floating-point vector
//	bvec2	-	a two component Boolean vector
//	bvec3	-	a three component Boolean vector
//	bvec4	-	a four component Boolean vector
//	ivec2	-	a two component integer vector
//	ivec3	-	a three component integer vector
//	ivec4	-	a four component integer vector
//	mat2	-	a 2x2 floating-point matrix
//	mat3	-	a 3x3 floating-point matrix
//	mat4	-	a 4x4 floating-point matrix
//	sampler2D	-	a handle for accessing a 2D texture
//	samplerCube	-	a handle for accessing a cube mapped texture

    #define FG_GFX_FLOAT                GL_FLOAT
    #define FG_GFX_FLOAT_VEC2           GL_FLOAT_VEC2
    #define FG_GFX_FLOAT_VEC3           GL_FLOAT_VEC3
    #define FG_GFX_FLOAT_VEC4           GL_FLOAT_VEC4
    #define FG_GFX_INT                  GL_INT
    #define FG_GFX_INT_VEC2             GL_INT_VEC2
    #define FG_GFX_INT_VEC3             GL_INT_VEC3
    #define FG_GFX_INT_VEC4             GL_INT_VEC4
    #define FG_GFX_BOOL                 GL_BOOL
    #define FG_GFX_BOOL_VEC2            GL_BOOL_VEC2
    #define FG_GFX_BOOL_VEC3            GL_BOOL_VEC3
    #define FG_GFX_BOOL_VEC4            GL_BOOL_VEC4
    #define FG_GFX_FLOAT_MAT2           GL_FLOAT_MAT2
    #define FG_GFX_FLOAT_MAT3           GL_FLOAT_MAT3
    #define FG_GFX_FLOAT_MAT4           GL_FLOAT_MAT4	
    #define FG_GFX_SAMPLER_2D           GL_SAMPLER_2D
    #define FG_GFX_SAMPLER_CUBE         GL_SAMPLER_CUBE

//
// String literals for uniform data types (GL)
//

    #define FG_GFX_FLOAT_TEXT		"float"
    #define FG_GFX_FLOAT_VEC2_TEXT	"vec2"
    #define FG_GFX_FLOAT_VEC3_TEXT	"vec3"
    #define FG_GFX_FLOAT_VEC4_TEXT	"vec4"
    #define FG_GFX_INT_TEXT		"int"
    #define FG_GFX_INT_VEC2_TEXT	"ivec2"
    #define FG_GFX_INT_VEC3_TEXT	"ivec3"
    #define FG_GFX_INT_VEC4_TEXT	"ivec4"
    #define FG_GFX_BOOL_TEXT		"bool"
    #define FG_GFX_BOOL_VEC2_TEXT	"bvec2"
    #define FG_GFX_BOOL_VEC3_TEXT	"bvec3"
    #define FG_GFX_BOOL_VEC4_TEXT	"bvec4"
    #define FG_GFX_FLOAT_MAT2_TEXT	"mat2"
    #define FG_GFX_FLOAT_MAT3_TEXT	"mat3"
    #define FG_GFX_FLOAT_MAT4_TEXT	"mat4"
    #define FG_GFX_SAMPLER_2D_TEXT	"sampler2D"
    #define FG_GFX_SAMPLER_CUBE_TEXT	"samplerCube"

//
// Convertion from string->enum,  enum->string for data types (GFX)
//

// Convert text (literal) to corresponding enum value
inline fgGFXenum _FG_GFX_DATA_TYPE_FROM_TEXT(const char* text) {
    if(!text)
        return (fgGFXenum)FG_GFX_NONE;
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_VEC2);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_VEC3);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_VEC4);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT_VEC2);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT_VEC3);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT_VEC4);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL_VEC2);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL_VEC3);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL_VEC4);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_MAT2);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_MAT3);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_MAT4);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SAMPLER_2D);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SAMPLER_CUBE);
    return (fgGFXenum)FG_GFX_NONE;
}
inline const char * _FG_GFX_DATA_TYPE_TO_TEXT(fgGFXenum value) {
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT, FG_TEXT(FG_GFX_FLOAT));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC2, FG_TEXT(FG_GFX_FLOAT_VEC2));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC3, FG_TEXT(FG_GFX_FLOAT_VEC3));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC4, FG_TEXT(FG_GFX_FLOAT_VEC4));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT, FG_TEXT(FG_GFX_INT));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC2, FG_TEXT(FG_GFX_INT_VEC2));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC3, FG_TEXT(FG_GFX_INT_VEC3));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC4, FG_TEXT(FG_GFX_INT_VEC4));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL, FG_TEXT(FG_GFX_BOOL));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC2, FG_TEXT(FG_GFX_BOOL_VEC2));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC3, FG_TEXT(FG_GFX_BOOL_VEC3));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC4, FG_TEXT(FG_GFX_BOOL_VEC4));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT2, FG_TEXT(FG_GFX_FLOAT_MAT2));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT3, FG_TEXT(FG_GFX_FLOAT_MAT3));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT4, FG_TEXT(FG_GFX_FLOAT_MAT4));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SAMPLER_2D, FG_TEXT(FG_GFX_SAMPLER_2D));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SAMPLER_CUBE, FG_TEXT(FG_GFX_SAMPLER_CUBE));

    return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
    #define FG_GFX_DATA_TYPE_FROM_TEXT(text)	_FG_GFX_DATA_TYPE_FROM_TEXT(text)
    #define FG_GFX_DATA_TYPE_TO_TEXT(value)		_FG_GFX_DATA_TYPE_TO_TEXT(value)

    #ifndef FG_GFX_ATTR_TYPE_DEFINED
        #define FG_GFX_ATTR_TYPE_DEFINED
// Attribute type also corresponds to bound attribute location

enum fgGfxAttributeType {
    FG_GFX_ATTRIBUTE_INVALID = -1,
    FG_GFX_POSITION = FG_GFX_ATTRIB_POS_LOCATION,
    FG_GFX_NORMAL = FG_GFX_ATTRIB_NORM_LOCATION,
    FG_GFX_TEXTURE_COORD = FG_GFX_ATTRIB_UVS_LOCATION,
    FG_GFX_COLOR = FG_GFX_ATTRIB_COLOR_LOCATION,
    FG_GFX_TANGENT = FG_GFX_ATTRIB_TANGENT_LOCATION
};
    #endif

/*
 *  Attribute raw data parameters
 * This is not to use within the shader / shader program structure
 * This data is used for draw calls. Shader hold more general data
 * about the attribute binds (location)
 */
struct fgGfxAttributeData {
    /// Index of the generic vertex attribute to be modifed.
    fgGFXint index;
    /// Number of components per generic vertex attribute. 
    /// Must be 1,2,3 or 4. (default is 3)
    fgGFXint size;
    // The engine specific attribute type
    fgGfxAttributeType type;
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
    fgGfxAttributeData() :
    index(0),
    size(3),
    type(FG_GFX_POSITION),
    dataType(FG_GFX_FLOAT),
    stride(0),
    pointer(NULL),
    isNormalized(FG_GFX_FALSE),
    isInterleaved(FG_GFX_TRUE),
    isBO(FG_GFX_FALSE),
    isEnabled(FG_GFX_FALSE),
    buffer(0) { }
    inline int operator ==(const fgGfxAttributeData& b) const {
        return (b.index == this->index);
    }
    inline int operator !=(const fgGfxAttributeData& b) const {
        return !(b.index == this->index);
    }
    inline bool operator >(const fgGfxAttributeData& a) const {
        return (int)(this->index) > (int)(a.index);
    }
    inline bool operator <(const fgGfxAttributeData& a) const {
        return (int)(this->index) < (int)(a.index);
    }
    inline bool operator >=(const fgGfxAttributeData& a) const {
        return (int)(this->index) >= (int)(a.index);
    }
    inline bool operator <=(const fgGfxAttributeData& a) const {
        return (int)(this->index) <= (int)(a.index);
    }
};

//
// Buffer / Texture / ... binding helper structures
//

    #ifndef _FG_GFX_BUFFERID_H_
        #include "fgGFXBufferID.h"
    #endif

    #ifndef _FG_GFX_TEXTUREID_H_
        #include "fgGFXTextureID.h"
    #endif

    #include <cmath>

    #ifndef FG_EPSILON
        #define FG_EPSILON 1e-6f
    #endif

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

    #ifndef M_PIF
        #define M_PIF 3.14159265358979323846f
    #endif

    #ifndef FG_DEG2RAD
        #define FG_DEG2RAD (M_PIF / 180.0f)
    #endif
    #ifndef FG_RAD2DEG
        #define FG_RAD2DEG (180.0f / M_PIF)
    #endif

struct fgArea {
    int x;
    int y;
    int w;
    int h;
    fgArea(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) { }
    fgArea() : x(0), y(0), w(0), h(0) { }
    int left() const {
        return x;
    }
    int right() const {
        return x + w;
    }
    int top() const {
        return y;
    }
    int bottom() const {
        return y + h;
    }
    int width() const {
        return w;
    }
    int height() const {
        return h;
    }
    void setLeft(int l) {
        x = l;
    }
    void setRight(int r) {
        w = r - x;
    }
    void setTop(int t) {
        y = t;
    }
    void setBottom(int b) {
        h = b - y;
    }
    void setWidth(int _w) {
        w = _w;
    }
    void setHeight(int _h) {
        h = _h;
    }
};

    #ifndef _FG_GFX_VERTEX_H_
        #include "fgGFXVertex.h"
    #endif


    #ifndef _FG_GFX_VERTEX_DATA_H_
        #include "fgGFXVertexData.h"
    #endif

    #undef _FG_GFX_TYPES_BLOCK__
#endif /* _FG_GFX_TYPES_H_ */
