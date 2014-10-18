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

    #ifndef _FG_GFX_ATTRIB_BITS_H_
        #include "fgGFXAttribBits.h"
    #endif

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
// Conversion from string->enum,  enum->string for data types (GFX)
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

// Convert from enum to text
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

    #ifndef _FG_GFX_ATTRIBUTE_DATA_H_
        #include "fgGFXAttributeData.h"
    #endif

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

/*
 * This is quick drawing info, it's a helper, needs refactoring
 * It provides info for direct drawing functions (like DrawElements
 * or DrawArrays from gl). Because of the parameters it's easy to
 * check what drawing function to use.
 * #FIXME plox...
 */
struct fgGfxDrawingInfo {
    union {
        ///
        fgGFXvoid *pointer;
        ///
        fgGFXvoid *offset;
    } indices;
    ///
    fgGFXuint buffer;
    ///
    fgGFXuint count;
    
    //
    fgGfxDrawingInfo() {
        indices.pointer = 0;
        indices.offset = 0;
        buffer = 0;
        count = 0;
    }
};

    #undef _FG_GFX_TYPES_BLOCK__
#endif /* _FG_GFX_TYPES_H_ */
