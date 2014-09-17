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

#define FG_GFX_ATTRIB_POS_LOCATION		0
#define FG_GFX_ATTRIB_NORM_LOCATION		1
#define FG_GFX_ATTRIB_UVS_LOCATION		2
#define FG_GFX_ATTRIB_COLOR_LOCATION	3
#define FG_GFX_ATTRIB_TANGENT_LOCATION	4

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

#if defined FG_USING_OPENGL_ES
#define FG_GFX_SHADING_LANG_VERSION_DEFAULT FG_GFX_ESSL_100
#else
#define FG_GFX_SHADING_LANG_VERSION_DEFAULT FG_GFX_GLSL_330 // ?
#endif

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

const char * const g_fgGfxShaderCfgSuffixes[] = {
	FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX,
	FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX
#if defined FG_USING_OPENGL
	,
	FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX,
	FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX,
	FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX,
	FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX
#endif
};

inline const char * _FG_GFX_SHADER_CFG_STD_SUFFIX(fgGfxShaderType _type) {
	FG_RETURN_VAL_IF_EQUAL(_type, FG_GFX_SHADER_FRAGMENT, FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX);
	FG_RETURN_VAL_IF_EQUAL(_type, FG_GFX_SHADER_VERTEX, FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX);
#if defined FG_USING_OPENGL
	FG_RETURN_VAL_IF_EQUAL(_type, FG_GFX_SHADER_TESS_CONTROL, FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX);
	FG_RETURN_VAL_IF_EQUAL(_type, FG_GFX_SHADER_TESS_EVALUATION, FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX);
	FG_RETURN_VAL_IF_EQUAL(_type, FG_GFX_SHADER_GEOMETRY, FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX);
	FG_RETURN_VAL_IF_EQUAL(_type, FG_GFX_SHADER_COMPUTE, FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX);
#endif
	return NULL;
};

#define FG_GFX_SHADER_CFG_STD_SUFFIX(type) _FG_GFX_SHADER_CFG_STD_SUFFIX(type)

//
enum fgGfxUniformType {
	FG_GFX_UNIFORM_INVALID,			// Invalid uniform type
	FG_GFX_MV_MATRIX,				// ModelView matrix
	FG_GFX_MVP_MATRIX,				// ModelViewProjection matrix
	FG_GFX_ENVIRONMENT_MAP,			// Environment map
	FG_GFX_NORMAL_MAP,				// Normal map
	FG_GFX_BUMP_MAP,				// Bump map
	FG_GFX_PLAIN_TEXTURE,			// First (plain) texture
	FG_GFX_DIRECTIONAL_LIGHT,		// Directional light (need probably a little more of those)
	FG_GFX_MATERIAL,				// Material to be used
	FG_GFX_PHASE,
	FG_GFX_DELTA_TIME,
	FG_GFX_TIMESTAMP,
	FG_GFX_CUSTOM_COLOR,			// global color
	FG_GFX_CUSTOM,					// Custom uniform - can be any type (only one per shader program)

};

#define FG_GFX_MV_MATRIX_TEXT			"ModelViewMatrix"
#define FG_GFX_MVP_MATRIX_TEXT			"ModelViewProjectionMatrix"
#define FG_GFX_ENVIRONMENT_MAP_TEXT		"EnvironmentMap"
#define FG_GFX_NORMAL_MAP_TEXT			"NormalMap"
#define FG_GFX_BUMP_MAP_TEXT			"BumpMap"
#define FG_GFX_PLAIN_TEXTURE_TEXT		"PlainTexture"
#define FG_GFX_DIRECTIONAL_LIGHT_TEXT	"DirectionalLight"
#define FG_GFX_MATERIAL_TEXT			"Material"
#define FG_GFX_PHASE_TEXT				"Phase"
#define FG_GFX_DELTA_TIME_TEXT			"DeltaTime"
#define FG_GFX_TIMESTAMP_TEXT			"Timestamp"
#define FG_GFX_CUSTOM_COLOR_TEXT		"CustomColor"
#define FG_GFX_CUSTOM_TEXT				"Custom"

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
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PHASE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_DELTA_TIME);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_TIMESTAMP);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_CUSTOM_COLOR);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_CUSTOM);
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
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PHASE,				FG_TEXT(FG_GFX_PHASE));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_DELTA_TIME,		FG_TEXT(FG_GFX_DELTA_TIME));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TIMESTAMP,			FG_TEXT(FG_GFX_TIMESTAMP));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_CUSTOM_COLOR,		FG_TEXT(FG_GFX_CUSTOM_COLOR));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_CUSTOM,			FG_TEXT(FG_GFX_CUSTOM));
	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_UNIFORM_TYPE_FROM_TEXT(text)	_FG_GFX_UNIFORM_TYPE_FROM_TEXT(text)
#define FG_GFX_UNIFORM_TYPE_TO_TEXT(value)	_FG_GFX_UNIFORM_TYPE_TO_TEXT(value)

// Attribute type also corresponds to bound attribute location
enum fgGfxAttributeType {
	FG_GFX_ATTRIBUTE_INVALID = -1,
	FG_GFX_POSITION		=	FG_GFX_ATTRIB_POS_LOCATION,
	FG_GFX_NORMAL		=	FG_GFX_ATTRIB_NORM_LOCATION,
	FG_GFX_TEXTURE_COORD=	FG_GFX_ATTRIB_UVS_LOCATION,
	FG_GFX_COLOR		=	FG_GFX_ATTRIB_COLOR_LOCATION,
	FG_GFX_TANGENT		=	FG_GFX_ATTRIB_TANGENT_LOCATION
};

#define FG_GFX_POSITION_TEXT		"Position"			// Position (vec3)
#define FG_GFX_NORMAL_TEXT			"Normal"			// Normal (vec3)
#define FG_GFX_TEXTURE_COORD_TEXT	"TextureCoord"		// UV - tex coord (vec2)
#define FG_GFX_COLOR_TEXT			"Color"				// Color (vec4)
#define FG_GFX_TANGENT_TEXT			"Tangent"			// Tangent ?

// Convert text (literal) to corresponding enum value
inline fgGfxAttributeType _FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(const char* text) {
	if(!text)
		return FG_GFX_ATTRIBUTE_INVALID;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_POSITION);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_NORMAL);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_TEXTURE_COORD);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_COLOR);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_TANGENT);
	return FG_GFX_ATTRIBUTE_INVALID;
}

inline const char * _FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(fgGfxAttributeType value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_POSITION,		FG_TEXT(FG_GFX_POSITION));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_NORMAL,		FG_TEXT(FG_GFX_NORMAL));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TEXTURE_COORD,	FG_TEXT(FG_GFX_TEXTURE_COORD));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_COLOR,			FG_TEXT(FG_GFX_COLOR));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TANGENT,		FG_TEXT(FG_GFX_TANGENT));
	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(text)	_FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(text)
#define FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(value)	_FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(value)

inline fgGFXint _FG_GFX_ATTRIB_LOCATION_FROM_TYPE(fgGfxAttributeType value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_POSITION,		(fgGFXint)FG_GFX_ATTRIB_POS_LOCATION);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_NORMAL,		(fgGFXint)FG_GFX_ATTRIB_NORM_LOCATION);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TEXTURE_COORD,	(fgGFXint)FG_GFX_ATTRIB_UVS_LOCATION);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_COLOR,			(fgGFXint)FG_GFX_ATTRIB_COLOR_LOCATION);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TANGENT,		(fgGFXint)FG_GFX_ATTRIB_TANGENT_LOCATION);
	return -1;
}

#define FG_GFX_ATTRIB_LOCATION_FROM_TYPE(value) _FG_GFX_ATTRIB_LOCATION_FROM_TYPE(value)

// #FIXME - this functions is very sad because it has a retarded name :(
inline fgGFXenum _FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(fgGfxAttributeType value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_POSITION,		(fgGFXenum)FG_GFX_FLOAT_VEC4);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_NORMAL,		(fgGFXenum)FG_GFX_FLOAT_VEC3);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_COLOR,			(fgGFXenum)FG_GFX_FLOAT_VEC4);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TEXTURE_COORD,	(fgGFXenum)FG_GFX_FLOAT_VEC2);
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_TANGENT,		(fgGFXenum)FG_GFX_FLOAT_VEC3);
	return -1;
}

#define FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(value) _FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(value)

//
struct fgGfxUniformBind {
	fgGFXint					location;
	fgGfxUniformType			type;
	fgGFXenum					dataType;
	fgGfxPrecision				precision;
	std::string					variableName;

	fgGfxUniformBind() : 
		location(-1),
		type(FG_GFX_UNIFORM_INVALID),
		dataType(FG_GFX_FLOAT_VEC4),
		precision(FG_GFX_PRECISION_DEFAULT)
	{
	}

	~fgGfxUniformBind()
	{
		variableName.clear();
	}

	inline int operator==(const fgGfxUniformBind &b) {
		return (b.variableName.compare(this->variableName) == 0 && b.type == this->type);
	}
	inline int operator!=(const fgGfxUniformBind &b) {
		return !(b.variableName.compare(this->variableName) == 0 && b.type == this->type);
	}
};

// The attribute qualifier can be used only with the data types:
// float, vec2, vec3, vec4, mat2, mat3, and mat4.
// Attribute variables cannot be declared as arrays or structures.

//
struct fgGfxAttributeBind
{
	// Name of the variable to bind
	std::string			variableName;
	// Location to which given attribute will be bound (must not equal -1)
	fgGFXint			location;
	// The engine specific attribute type
	fgGfxAttributeType	type;
	// Specifies the data type of a single element.
	// Can be float, vec2, vec3, vec4, mat2, mat3, and mat4.
	fgGFXenum			dataType;
	// Currently used precision for this attribute
	fgGfxPrecision		precision;
	//
	fgGFXboolean		isBound;

	fgGfxAttributeBind() : 
		variableName(""),
		location(-1),
		type(FG_GFX_ATTRIBUTE_INVALID),
		dataType(FG_GFX_FLOAT_VEC4),
		precision(FG_GFX_PRECISION_DEFAULT),
		isBound(FG_FALSE)
	{
	}

	~fgGfxAttributeBind()
	{
		variableName.clear();
	}

	// This will not only set the type but also location and dataType 
	void setType(fgGfxAttributeType _type) {
		if(_type == FG_GFX_ATTRIBUTE_INVALID)
			return;
		type = _type;
		location = FG_GFX_ATTRIB_LOCATION_FROM_TYPE(type);
		dataType = FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(type);
	}

	inline int operator==(const fgGfxAttributeBind &b) {
		return (b.variableName.compare(this->variableName) == 0 && b.type == this->type);
	}

	inline int operator!=(const fgGfxAttributeBind &b) {
		return !(b.variableName.compare(this->variableName) == 0 && b.type == this->type);
	}

	inline bool operator>(const fgGfxAttributeBind& a) const {
		return (int)(this->type) > (int)(a.type);
    }

	inline bool operator<(const fgGfxAttributeBind& a) const {
		return (int)(this->type) < (int)(a.type);
    }

	inline bool operator>=(const fgGfxAttributeBind& a) const {
		return (int)(this->type) >= (int)(a.type);
    }

	inline bool operator<=(const fgGfxAttributeBind& a) const {
		return (int)(this->type) <= (int)(a.type);
    }
};

// Attribute raw data parameters
// This is not to use within the shader / shader program structure
// This data is used for draw calls. Shader hold more general data
// about the attribute binds (location)
struct fgGfxAttributeData
{
	/// Index of the generic vertex attribute to be modifed.
	fgGFXint	index;
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
