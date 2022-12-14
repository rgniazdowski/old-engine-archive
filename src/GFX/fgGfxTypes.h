/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_TYPES
    #define FG_INC_GFX_TYPES
    #define FG_INC_GFX_TYPES_BLOCK

    #ifdef FG_INC_TYPES_BLOCK
        #error "FG_TYPES_BLOCK constant is defined. Do not include fgGfxTypes header inside of fgTypes header."
    #endif

    #include "fgTypes.h"

    #ifndef FG_GFX_NONE
        #define FG_GFX_NONE 0
    #endif

    #include "fgGfxColor.h"
    #include "fgGfxAttribBits.h"
    #include "fgGfxAttributeData.h"
    #include "fgGfxBufferID.h"
    #include "fgGfxTextureID.h"
    #include "fgGfxVertex.h"
    #include "fgGfxVertexData.h"

    #if !defined(FG_RAND)
        #define FG_RAND(_A, _B) (_A + (int)(((float)(_B - _A + 1)) * rand() / (((float)RAND_MAX) + 1.0f)))
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
    #define FG_GFX_DATA_TYPE_FROM_TEXT(text)    _FG_GFX_DATA_TYPE_FROM_TEXT(text)
    #define FG_GFX_DATA_TYPE_TO_TEXT(value)     _FG_GFX_DATA_TYPE_TO_TEXT(value)


//
// Buffer / Texture / ... binding helper structures
//

    #ifndef FG_EPSILON
        #define FG_EPSILON 1e-6f
    #endif

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

    #ifndef M_PIF
        #define M_PIF 3.14159265358979323846f
    #endif

    #ifndef M_PI2XF
        #define M_PI2XF 6.28318530717958647692f
    #endif

    #ifndef FG_DEG2RAD
        #define FG_DEG2RAD (M_PIF / 180.0f)
        #define FG_DEG2RAD_FUNC(_ANGLE) (_ANGLE * FG_DEG2RAD)
    #endif
    #ifndef FG_RAD2DEG
        #define FG_RAD2DEG (180.0f / M_PIF)
        #define FG_RAD2DEG_FUNC(_RADIANS) (_RADIANS * FG_RAD2DEG)
    #endif

namespace fg {
    namespace gfx {

        enum BlendMode {
            BLEND_OFF = 0,
            BLEND_ADDITIVE = 1,
            BLEND_TRANSPARENCY = 2
        };

    #if defined(FG_USING_OPENGL) || defined(FG_USING_OPENGL_ES)

        enum FrontFace {
            FACE_CCW = (unsigned int)GL_CCW,
            FACE_CW = (unsigned int)GL_CW
        };
    #else 

        enum FrontFace {
            FACE_CCW,
            FACE_CW
        };
    #endif

        /**
         * This is quick drawing info, it's a helper, needs refactoring
         * It provides info for direct drawing functions (like DrawElements
         * or DrawArrays from gl). Because of the parameters it's easy to
         * check what drawing function to use.
         * #FIXME plox...
         */
        struct SDrawingInfo {

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
            /**
             * 
             */
            SDrawingInfo() {
                indices.pointer = 0;
                indices.offset = 0;
                buffer = 0;
                count = 0;
            }
        }; // struct SDrawingInfo

        /**
         *
         */
        enum class PrimitiveMode {
            TRIANGLES = (fgGFXenum)GL_TRIANGLES,
            TRIANGLE_STRIP = (fgGFXenum)GL_TRIANGLE_STRIP,
            TRIANGLE_FAN = (fgGFXenum)GL_TRIANGLE_FAN,
            LINES = (fgGFXenum)GL_LINES,
            LINE_LOOP = (fgGFXenum)GL_LINE_LOOP,
            LINE_STRIP = (fgGFXenum)GL_LINE_STRIP
        };
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_TYPES_BLOCK
#endif /* FG_INC_GFX_TYPES */
