/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_DEFS_H_
#define _FG_GFX_SHADER_DEFS_H_

#ifdef _FG_GFX_STD_INC_BLOCK__
#error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderDefs inside of Gfx Standard Include header."
#endif

#include "GFX/fgGFXStdInc.h"
#include <string>

//GLSL Version      OpenGL Version
//1.10				2.0
//1.20				2.1
//1.30				3.0
//1.40				3.1
//1.50				3.2
//3.30				3.3
//4.00				4.0
//4.10				4.1
//4.20				4.2
//4.30				4.3
//4.40				4.4

enum fgGfxShadingLanguageVersion
{
	FG_GFX_SHADING_LANGUAGE_INVALID	= 0,
	FG_GFX_ESSL_100		=	100,
	FG_GFX_ESSL_300		=	300,
	FG_GFX_GLSL_110		=	110,
	FG_GFX_GLSL_120		=	120,
	FG_GFX_GLSL_130		=	130,
	FG_GFX_GLSL_140		=	140,
	FG_GFX_GLSL_150		=	150,
	FG_GFX_GLSL_330		=	330,
	FG_GFX_GLSL_400		=	400,
	FG_GFX_GLSL_410		=	410,
	FG_GFX_GLSL_420		=	420,
	FG_GFX_GLSL_430		=	430,
	FG_GFX_GLSL_440		=	440,
};

//
enum fgGfxShaderType {
	FG_GFX_SHADER_FRAGMENT			=	GL_FRAGMENT_SHADER,
	FG_GFX_SHADER_VERTEX			=	GL_VERTEX_SHADER,
#if defined FG_USING_OPENGL
	FG_GFX_SHADER_TESS_CONTROL		=	GL_TESS_CONTROL_SHADER,
	FG_GFX_SHADER_TESS_EVALUATION	=	GL_TESS_EVALUATION_SHADER,
	FG_GFX_SHADER_GEOMETRY			=	GL_GEOMETRY_SHADER,
	// GL_COMPUTE_SHADER is available only if the GL version is 4.3 or higher.
	FG_GFX_SHADER_COMPUTE			=	GL_COMPUTE_SHADER,
#endif
	FG_GFX_SHADER_INVALID			=	FG_NONE
};

const fgGfxShaderType g_fgGfxSupportedShaderTypes[] = {
	FG_GFX_SHADER_FRAGMENT,
	FG_GFX_SHADER_VERTEX
#if defined FG_USING_OPENGL
	,
	FG_GFX_SHADER_TESS_CONTROL,
	FG_GFX_SHADER_TESS_EVALUATION,
	FG_GFX_SHADER_GEOMETRY,
	FG_GFX_SHADER_COMPUTE
#endif
};

#define FG_GFX_SHADER_FRAGMENT_TEXT					"FragmentShader"
#define FG_GFX_SHADER_VERTEX_TEXT					"VertexShader"
#define FG_GFX_SHADER_TESS_CONTROL_TEXT				"TessellationControlShader"
#define FG_GFX_SHADER_TESS_EVALUATION_TEXT			"TessellationEvaluationShader"
#define FG_GFX_SHADER_GEOMETRY_TEXT					"GeometryShader"
#define FG_GFX_SHADER_COMPUTE_TEXT					"ComputeShader"

const char * const g_fgGfxSupportedShaderTypesText[] = {
	FG_GFX_SHADER_FRAGMENT_TEXT,
	FG_GFX_SHADER_VERTEX_TEXT
#if defined FG_USING_OPENGL
	,
	FG_GFX_SHADER_TESS_CONTROL,
	FG_GFX_SHADER_TESS_EVALUATION,
	FG_GFX_SHADER_GEOMETRY,
	FG_GFX_SHADER_COMPUTE
#endif
};

// Convert text (literal) to corresponding enum value
inline fgGfxShaderType _FG_GFX_SHADER_TYPE_FROM_TEXT(const char* text) {
	if(!text)
		return FG_GFX_SHADER_INVALID;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SHADER_FRAGMENT);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SHADER_VERTEX);
#if defined FG_USING_OPENGL
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SHADER_TESS_CONTROL);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SHADER_TESS_EVALUATION);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SHADER_GEOMETRY);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SHADER_COMPUTE);
#endif
	return FG_GFX_SHADER_INVALID;
}

inline const char * _FG_GFX_SHADER_TYPE_TO_TEXT(fgGfxShaderType value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_FRAGMENT, FG_TEXT(FG_GFX_SHADER_FRAGMENT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_VERTEX, FG_TEXT(FG_GFX_SHADER_VERTEX));
#if defined FG_USING_OPENGL
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_TESS_CONTROL, FG_TEXT(FG_GFX_SHADER_TESS_CONTROL));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_TESS_EVALUATION_TEXT, FG_TEXT(FG_GFX_SHADER_TESS_EVALUATION_TEXT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_GEOMETRY_TEXT, FG_TEXT(FG_GFX_SHADER_GEOMETRY_TEXT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_COMPUTE_TEXT, FG_TEXT(FG_GFX_SHADER_COMPUTE_TEXT));
#endif
	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_SHADER_TYPE_FROM_TEXT(text)	_FG_GFX_SHADER_TYPE_FROM_TEXT(text)
#define FG_GFX_SHADER_TYPE_TO_TEXT(value)	_FG_GFX_SHADER_TYPE_TO_TEXT(value)

inline const char * _FG_GFX_SHADER_SHORT_PREFIX(fgGfxShaderType value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_FRAGMENT, "FS");
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_VERTEX, "VS");
#if defined FG_USING_OPENGL
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_TESS_CONTROL, "TCS");
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_TESS_EVALUATION_TEXT, "TES");
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_GEOMETRY_TEXT, "GS");
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SHADER_COMPUTE_TEXT, "CS");
#endif
	return NULL;
}

#define FG_GFX_SHADER_SHORT_PREFIX(value)	_FG_GFX_SHADER_SHORT_PREFIX(value)

//
enum fgGfxShaderPrecision {
	FG_GFX_SHADER_PRECISION_LOW,
	FG_GFX_SHADER_PRECISION_MEDIUM,
	FG_GFX_SHADER_PRECISION_HIGH,
	FG_GFX_SHADER_PRECISION_DEFAULT
};

//
enum fgGfxPrecision {
	FG_GFX_PRECISION_LOW,
	FG_GFX_PRECISION_MEDIUM,
	FG_GFX_PRECISION_HIGH,
	FG_GFX_PRECISION_DEFAULT
};

#define FG_GFX_PRECISION_LOW_TEXT		"low"
#define FG_GFX_PRECISION_MEDIUM_TEXT	"medium"
#define FG_GFX_PRECISION_HIGH_TEXT		"high"
#define FG_GFX_PRECISION_DEFAULT_TEXT	"default"

// Convert text (literal) to corresponding enum value
inline fgGfxPrecision _FG_GFX_PRECISION_FROM_TEXT(const char* text) {
	if(!text)
		return FG_GFX_PRECISION_DEFAULT;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PRECISION_LOW);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PRECISION_MEDIUM);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PRECISION_HIGH);
	return FG_GFX_PRECISION_DEFAULT;
}

inline const char * _FG_GFX_PRECISION_TYPE_TO_TEXT(fgGfxPrecision value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PRECISION_LOW,		FG_TEXT(FG_GFX_PRECISION_LOW));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PRECISION_MEDIUM,	FG_TEXT(FG_GFX_PRECISION_MEDIUM));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PRECISION_HIGH,	FG_TEXT(FG_GFX_PRECISION_HIGH));
	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_PRECISION_FROM_TEXT(text)		_FG_GFX_PRECISION_FROM_TEXT(text)
#define FG_GFX_PRECISION_TYPE_TO_TEXT(value)	_FG_GFX_PRECISION_TYPE_TO_TEXT(value)

//
// Data types
//

//	bool	-	a conditional type, taking on values of true or false
//	int		-	a signed integer
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
//	mat2	-	a 2×2 floating-point matrix
//	mat3	-	a 3×3 floating-point matrix
//	mat4	-	a 4×4 floating-point matrix
//	sampler2D	-	a handle for accessing a 2D texture
//	samplerCube	-	a handle for accessing a cube mapped texture

#define	FG_GFX_FLOAT			GL_FLOAT
#define	FG_GFX_FLOAT_VEC2		GL_FLOAT_VEC2
#define	FG_GFX_FLOAT_VEC3		GL_FLOAT_VEC3
#define	FG_GFX_FLOAT_VEC4		GL_FLOAT_VEC4
#define FG_GFX_INT				GL_INT
#define	FG_GFX_INT_VEC2			GL_INT_VEC2
#define	FG_GFX_INT_VEC3			GL_INT_VEC3
#define	FG_GFX_INT_VEC4			GL_INT_VEC4
#define	FG_GFX_BOOL				GL_BOOL
#define	FG_GFX_BOOL_VEC2		GL_BOOL_VEC2
#define	FG_GFX_BOOL_VEC3		GL_BOOL_VEC3
#define	FG_GFX_BOOL_VEC4		GL_BOOL_VEC4
#define	FG_GFX_FLOAT_MAT2		GL_FLOAT_MAT2
#define	FG_GFX_FLOAT_MAT3		GL_FLOAT_MAT3
#define	FG_GFX_FLOAT_MAT4		GL_FLOAT_MAT4	
#define	FG_GFX_SAMPLER_2D		GL_SAMPLER_2D
#define	FG_GFX_SAMPLER_CUBE		GL_SAMPLER_CUBE

//
// String literals for uniform data types (GL)
//

#define	FG_GFX_FLOAT_TEXT			"float"
#define	FG_GFX_FLOAT_VEC2_TEXT		"vec2"
#define	FG_GFX_FLOAT_VEC3_TEXT		"vec3"
#define	FG_GFX_FLOAT_VEC4_TEXT		"vec4"
#define FG_GFX_INT_TEXT				"int"
#define	FG_GFX_INT_VEC2_TEXT		"ivec2"
#define	FG_GFX_INT_VEC3_TEXT		"ivec3"
#define	FG_GFX_INT_VEC4_TEXT		"ivec4"
#define	FG_GFX_BOOL_TEXT			"bool"
#define	FG_GFX_BOOL_VEC2_TEXT		"bvec2"
#define	FG_GFX_BOOL_VEC3_TEXT		"bvec3"
#define	FG_GFX_BOOL_VEC4_TEXT		"bvec4"
#define	FG_GFX_FLOAT_MAT2_TEXT		"mat2"
#define	FG_GFX_FLOAT_MAT3_TEXT		"mat3"
#define	FG_GFX_FLOAT_MAT4_TEXT		"mat4"
#define	FG_GFX_SAMPLER_2D_TEXT		"sampler2D"
#define	FG_GFX_SAMPLER_CUBE_TEXT	"samplerCube"

//
// Convertion from string->enum,  enum->string for data types (GFX)
//

// Convert text (literal) to corresponding enum value
inline fgGFXenum _FG_GFX_DATA_TYPE_FROM_TEXT(const char* text) {
	if(!text)
		return FG_GFX_NONE;
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
	return FG_GFX_NONE;
}

inline const char * _FG_GFX_DATA_TYPE_TO_TEXT(fgGFXenum value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT,			FG_TEXT(FG_GFX_FLOAT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC2,	FG_TEXT(FG_GFX_FLOAT_VEC2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC3,	FG_TEXT(FG_GFX_FLOAT_VEC3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC4,	FG_TEXT(FG_GFX_FLOAT_VEC4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT,			FG_TEXT(FG_GFX_INT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC2,		FG_TEXT(FG_GFX_INT_VEC2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC3,		FG_TEXT(FG_GFX_INT_VEC3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC4,		FG_TEXT(FG_GFX_INT_VEC4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL,			FG_TEXT(FG_GFX_BOOL));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC2,		FG_TEXT(FG_GFX_BOOL_VEC2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC3,		FG_TEXT(FG_GFX_BOOL_VEC3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC4,		FG_TEXT(FG_GFX_BOOL_VEC4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT2,	FG_TEXT(FG_GFX_FLOAT_MAT2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT3,	FG_TEXT(FG_GFX_FLOAT_MAT3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT4,	FG_TEXT(FG_GFX_FLOAT_MAT4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SAMPLER_2D,	FG_TEXT(FG_GFX_SAMPLER_2D));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SAMPLER_CUBE,	FG_TEXT(FG_GFX_SAMPLER_CUBE));

	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_DATA_TYPE_FROM_TEXT(text)	_FG_GFX_DATA_TYPE_FROM_TEXT(text)
#define FG_GFX_DATA_TYPE_TO_TEXT(value)		_FG_GFX_DATA_TYPE_TO_TEXT(value)

//
enum fgGfxShaderPrecisionType {
	FG_GFX_LOW_INT		= GL_LOW_INT,
	FG_GFX_MEDIUM_INT	= GL_MEDIUM_INT,
	FG_GFX_HIGH_INT		= GL_HIGH_INT,
	FG_GFX_LOW_FLOAT	= GL_LOW_FLOAT,
	FG_GFX_MEDIUM_FLOAT = GL_MEDIUM_FLOAT,
	FG_GFX_HIGH_FLOAT	= GL_HIGH_FLOAT
};

//.vert - a vertex shader
//.tesc - a tessellation control shader
//.tese - a tessellation evaluation shader
//.geom - a geometry shader
//.frag - a fragment shader
//.comp - a compute shader

#define FG_GFX_SHADER_FRAGMENT_STD_SUFFIX				"frag"
#define FG_GFX_SHADER_VERTEX_STD_SUFFIX					"vert"
#define FG_GFX_SHADER_TESS_CONTROL_STD_SUFFIX			"tesc"
#define FG_GFX_SHADER_TESS_EVALUATION_STD_SUFFIX		"tese"
#define FG_GFX_SHADER_GEOMETRY_STD_SUFFIX				"geom"
#define FG_GFX_SHADER_COMPUTE_STD_SUFFIX				"comp"

#define FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX			"program.ini"
#define FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX		"frag.shader.ini"
#define FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX			"vert.shader.ini"
#define FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX	"tesc.shader.ini"
#define FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX	"tese.shader.ini"
#define FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX		"geom.shader.ini"
#define FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX			"comp.shader.ini"

#define FG_GFX_SHADER_CONFIG_STD_SUFFIX					"shader.ini"

//
enum fgGfxUniformType {
	FG_GFX_UNIFORM_INVALID,
	FG_GFX_MV_MATRIX,
	FG_GFX_MVP_MATRIX,
	FG_GFX_ENVIRONMENT_MAP,
	FG_GFX_NORMAL_MAP,
	FG_GFX_BUMP_MAP,
	FG_GFX_PLAIN_TEXTURE,
	FG_GFX_DIRECTIONAL_LIGHT,
	FG_GFX_MATERIAL
};

#define FG_GFX_MV_MATRIX_TEXT			"ModelViewMatrix"
#define FG_GFX_MVP_MATRIX_TEXT			"ModelViewProjectionMatrix"
#define FG_GFX_ENVIRONMENT_MAP_TEXT		"EnvironmentMap"
#define FG_GFX_NORMAL_MAP_TEXT			"NormalMap"
#define FG_GFX_BUMP_MAP_TEXT			"BumpMap"
#define FG_GFX_PLAIN_TEXTURE_TEXT		"PlainTexture"
#define FG_GFX_DIRECTIONAL_LIGHT_TEXT	"DirectionalLight"
#define FG_GFX_MATERIAL_TEXT			"Material"

// Convert text (literal) to corresponding enum value
inline fgGfxUniformType _FG_GFX_UNIFORM_TYPE_FROM_TEXT(const char* text) {
	if(!text)
		return FG_GFX_UNIFORM_INVALID;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_MV_MATRIX);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_MVP_MATRIX);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_ENVIRONMENT_MAP);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_NORMAL_MAP);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BUMP_MAP);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PLAIN_TEXTURE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_DIRECTIONAL_LIGHT);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_MATERIAL);
	return FG_GFX_UNIFORM_INVALID;
}

inline const char * _FG_GFX_UNIFORM_TYPE_TO_TEXT(fgGfxUniformType value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_MV_MATRIX,			FG_TEXT(FG_GFX_MV_MATRIX));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_MVP_MATRIX,		FG_TEXT(FG_GFX_MVP_MATRIX));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_ENVIRONMENT_MAP,	FG_TEXT(FG_GFX_ENVIRONMENT_MAP));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_NORMAL_MAP,		FG_TEXT(FG_GFX_NORMAL_MAP));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BUMP_MAP,			FG_TEXT(FG_GFX_BUMP_MAP));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PLAIN_TEXTURE,		FG_TEXT(FG_GFX_PLAIN_TEXTURE));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_DIRECTIONAL_LIGHT, FG_TEXT(FG_GFX_DIRECTIONAL_LIGHT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_MATERIAL,			FG_TEXT(FG_GFX_MATERIAL));
	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_UNIFORM_TYPE_FROM_TEXT(text)	_FG_GFX_UNIFORM_TYPE_FROM_TEXT(text)
#define FG_GFX_UNIFORM_TYPE_TO_TEXT(value)	_FG_GFX_UNIFORM_TYPE_TO_TEXT(value)

// 
enum fgGfxAttributeType {
	FG_GFX_ATTRIBUTE_INVALID,
	FG_GFX_POSITION,
	FG_GFX_NORMAL,
	FG_GFX_COLOR,
	FG_GFX_TEXTURE_COORD,
	FG_GFX_TANGENT
};

#define FG_GFX_POSITION_TEXT		"Position"
#define FG_GFX_NORMAL_TEXT			"Normal"
#define FG_GFX_COLOR_TEXT			"Color"
#define FG_GFX_TEXTURE_COORD_TEXT	"TextureCoord"
#define FG_GFX_TANGENT_TEXT			"Tangent"

// Convert text (literal) to corresponding enum value
inline fgGfxAttributeType _FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(const char* text) {
	if(!text)
		return FG_GFX_ATTRIBUTE_INVALID;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_POSITION);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_NORMAL);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_COLOR);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_TEXTURE_COORD);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_TANGENT);
	return FG_GFX_ATTRIBUTE_INVALID;
}

inline const char * _FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(fgGfxAttributeType value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_POSITION,		FG_TEXT(FG_GFX_POSITION));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_NORMAL,		FG_TEXT(FG_GFX_NORMAL));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_COLOR,			FG_TEXT(FG_GFX_COLOR));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TEXTURE_COORD,	FG_TEXT(FG_GFX_TEXTURE_COORD));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TANGENT,		FG_TEXT(FG_GFX_TANGENT));
	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(text)	_FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(text)
#define FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(value)	_FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(value)

//
struct fgGfxUniformBind {
	fgGFXuint					location;
	fgGfxUniformType			type;
	fgGFXenum					dataType;
	fgGfxPrecision				precision;
	std::string					variableName;

	fgGfxUniformBind() : 
		location(0),
		type(FG_GFX_UNIFORM_INVALID),
		dataType(FG_GFX_FLOAT_VEC4),
		precision(FG_GFX_PRECISION_DEFAULT)
	{
	}

	~fgGfxUniformBind()
	{
		variableName.clear();
	}
};

// The attribute qualifier can be used only with the data types:
// float, vec2, vec3, vec4, mat2, mat3, and mat4.
// Attribute variables cannot be declared as arrays or structures.

//
struct fgGfxAttributeBind
{
	// Location to which given attribute will be bound (must not equal 0)
	fgGFXuint			location;
	// The engine specific attribute type
	fgGfxAttributeType	type;
	// Specifies the data type of a single element.
	// Can be float, vec2, vec3, vec4, mat2, mat3, and mat4.
	fgGFXenum			dataType;
	// Currently used precision for this attribute
	fgGfxPrecision		precision;
	// Name of the variable to bind
	std::string			variableName;

	fgGfxAttributeBind() : 
		location(0),
		type(FG_GFX_ATTRIBUTE_INVALID),
		dataType(FG_GFX_FLOAT_VEC4),
		precision(FG_GFX_PRECISION_DEFAULT)
	{
	}

	~fgGfxAttributeBind()
	{
		variableName.clear();
	}
};

// Attribute raw data parameters
// This is not to use within the shader / shader program structure
// This data is used for draw calls. Shader hold more general data
// about the attribute binds (location)
struct fgGfxAttributeData
{
	/// Index of the generic vertex attribute to be modifed.
	fgGFXuint	index;
	/// Number of components per generic vertex attribute. 
	/// Must be 1,2,3 or 4. (default is 4)
	fgGFXint	size;
	// The engine specific attribute type
	fgGfxAttributeType	type;
	/// Specifies the data type of each component in the array.
	/// Possible values: BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, FIXED and FLOAT.
	fgGFXenum	dataType;
	/// The byte offset between between consecutive generic vertex attributes.
	/// For structures and interleaved data this will be sizeof(struct/Vertex)
	fgGFXsizei	stride;
	union {
		// Pointer to the vertex data
		fgGFXvoid	*pointer;
		// Offset if vertex buffer object is used
		fgGFXvoid	*offset;
	};
	/// Specifies whether data values should be normalized
	fgGFXboolean normalized;
	/// Is data interleaved? This is important, if data is not interleaved then
	/// it means that vertices, normals, UVS, colors etc are in separate arrays
	/// (Struct of arrays) and/or separate buffer objects (isBO).
	/// If true then Array of structs is used and one vertex buffer (additionally
	/// another buffer for indeces)
	fgGFXboolean interleaved;
	/// Is attribute data bound to vertex/index buffer?
	/// Note: attribute data used for index buffer cannot be bound to attribute in the shader
	/// It is used for indexed drawing - it's additional 3D data (glDrawElements)
	fgGFXboolean isBO;
};

//
struct fgGfxShaderConstantDef
{
	std::string		name;
	fgBool			value;

	// #FIXME - need some standard abstract class for that kind of operations
	void toString(char *buf, unsigned int maxlen = 128)
	{
		if(!buf)
			return;
		snprintf(buf, (size_t)maxlen, "#define %s %d", name.c_str(), value);
	}

	std::string & toString(std::string & buf)
	{
		buf.append("#define ").append(name);
		if(value)
			buf.append(" 1");
		else
			buf.append(" 0");
		return buf;
	}
};

#endif /* _FG_GFX_SHADER_DEFS_H_ */
