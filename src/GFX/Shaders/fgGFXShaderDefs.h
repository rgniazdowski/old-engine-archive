/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_SHADER_DEFS
    #define FG_INC_GFX_SHADER_DEFS
    #define FG_INC_GFX_SHADER_DEFS_BLOCK

    #ifdef FG_INC_GFX_STD_INC_BLOCK
        #error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderDefs inside of Gfx Standard Include header."
    #endif

    #include "GFX/fgGFXStdInc.h"
    #include <string>

    #ifndef FG_GFX_ATTRIB_POS_LOCATION
        #define FG_GFX_ATTRIB_POS_LOCATION	0
    #endif

    #ifndef FG_GFX_ATTRIB_NORM_LOCATION
        #define FG_GFX_ATTRIB_NORM_LOCATION	1
    #endif

    #ifndef FG_GFX_ATTRIB_UVS_LOCATION
        #define FG_GFX_ATTRIB_UVS_LOCATION	2
    #endif

    #ifndef FG_GFX_ATTRIB_COLOR_LOCATION
        #define FG_GFX_ATTRIB_COLOR_LOCATION	3
    #endif

    #ifndef FG_GFX_ATTRIB_TANGENT_LOCATION
        #define FG_GFX_ATTRIB_TANGENT_LOCATION	4
    #endif

    #ifndef FG_GFX_POSITION_BIT
        #define FG_GFX_POSITION_BIT		0x0001
    #endif

    #ifndef FG_GFX_NORMAL_BIT
        #define FG_GFX_NORMAL_BIT		0x0002
    #endif 

    #ifndef FG_GFX_UVS_BIT
        #define FG_GFX_UVS_BIT                  0x0004
    #endif 

    #ifndef FG_GFX_COLOR_BIT
        #define FG_GFX_COLOR_BIT		0x0008
    #endif 

    #ifndef FG_GFX_TANGENT_BIT
        #define FG_GFX_TANGENT_BIT		0x0020
    #endif 

/**
 *
 */
enum class ShaderType {
    ///
    FG_GFX_SHADER_FRAGMENT = (fgGFXenum)GL_FRAGMENT_SHADER,
    ///
    FG_GFX_SHADER_VERTEX = (fgGFXenum)GL_VERTEX_SHADER,
    #if defined FG_USING_OPENGL
    ///
    FG_GFX_SHADER_TESS_CONTROL = (fgGFXenum)GL_TESS_CONTROL_SHADER,
    ///
    FG_GFX_SHADER_TESS_EVALUATION = (fgGFXenum)GL_TESS_EVALUATION_SHADER,
    ///
    FG_GFX_SHADER_GEOMETRY = (fgGFXenum)GL_GEOMETRY_SHADER,
    /// GL_COMPUTE_SHADER is available only if the GL version is 4.3 or higher.
    ///
    FG_GFX_SHADER_COMPUTE = (fgGFXenum)GL_COMPUTE_SHADER,
    #endif
    ///
    FG_GFX_SHADER_INVALID = FG_NONE
};

const ShaderType g_fgGfxSupportedShaderTypes[] = {ShaderType::FG_GFX_SHADER_FRAGMENT,
                                                  ShaderType::FG_GFX_SHADER_VERTEX
    #if defined FG_USING_OPENGL
    ,
                                                  ShaderType::FG_GFX_SHADER_TESS_CONTROL,
                                                  ShaderType::FG_GFX_SHADER_TESS_EVALUATION,
                                                  ShaderType::FG_GFX_SHADER_GEOMETRY,
                                                  ShaderType::FG_GFX_SHADER_COMPUTE
    #endif
};

    #define FG_GFX_SHADER_FRAGMENT_TEXT         "FragmentShader"
    #define FG_GFX_SHADER_VERTEX_TEXT           "VertexShader"
    #define FG_GFX_SHADER_TESS_CONTROL_TEXT     "TessellationControlShader"
    #define FG_GFX_SHADER_TESS_EVALUATION_TEXT  "TessellationEvaluationShader"
    #define FG_GFX_SHADER_GEOMETRY_TEXT         "GeometryShader"
    #define FG_GFX_SHADER_COMPUTE_TEXT          "ComputeShader"

const char * const g_fgGfxSupportedShaderTypesText[] = {
                                                        FG_GFX_SHADER_FRAGMENT_TEXT,
                                                        FG_GFX_SHADER_VERTEX_TEXT
    #if defined FG_USING_OPENGL
    ,
                                                        FG_GFX_SHADER_TESS_CONTROL_TEXT,
                                                        FG_GFX_SHADER_TESS_EVALUATION_TEXT,
                                                        FG_GFX_SHADER_GEOMETRY_TEXT,
                                                        FG_GFX_SHADER_COMPUTE_TEXT
    #endif
};

// Convert text (literal) to corresponding enum value
inline ShaderType _FG_GFX_SHADER_TYPE_FROM_TEXT(const char* text) {
    if(!text)
        return ShaderType::FG_GFX_SHADER_INVALID;
    FG_RETURN_VAL_IF_TEXT_EQ(FG_TEXT(FG_GFX_SHADER_FRAGMENT), ShaderType::FG_GFX_SHADER_FRAGMENT);
    //FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SHADER_FRAGMENT);
    FG_RETURN_VAL_IF_TEXT_EQ(FG_TEXT(FG_GFX_SHADER_VERTEX), ShaderType::FG_GFX_SHADER_VERTEX);
    //FG_RETURN_ENUM_IF_TEXT_EQ(fgGfxShaderType::FG_GFX_SHADER_VERTEX);
    #if defined FG_USING_OPENGL
    FG_RETURN_VAL_IF_TEXT_EQ(FG_TEXT(FG_GFX_SHADER_TESS_CONTROL), ShaderType::FG_GFX_SHADER_TESS_CONTROL);
    //FG_RETURN_ENUM_IF_TEXT_EQ(fgGfxShaderType::FG_GFX_SHADER_TESS_CONTROL);
    FG_RETURN_VAL_IF_TEXT_EQ(FG_TEXT(FG_GFX_SHADER_TESS_EVALUATION), ShaderType::FG_GFX_SHADER_TESS_EVALUATION);
    //FG_RETURN_ENUM_IF_TEXT_EQ(fgGfxShaderType::FG_GFX_SHADER_TESS_EVALUATION);
    FG_RETURN_VAL_IF_TEXT_EQ(FG_TEXT(FG_GFX_SHADER_GEOMETRY), ShaderType::FG_GFX_SHADER_GEOMETRY);
    //FG_RETURN_ENUM_IF_TEXT_EQ(fgGfxShaderType::FG_GFX_SHADER_GEOMETRY);
    FG_RETURN_VAL_IF_TEXT_EQ(FG_TEXT(FG_GFX_SHADER_COMPUTE), ShaderType::FG_GFX_SHADER_COMPUTE);
    //FG_RETURN_ENUM_IF_TEXT_EQ(fgGfxShaderType::FG_GFX_SHADER_COMPUTE);
    #endif
    return ShaderType::FG_GFX_SHADER_INVALID;
}
inline const char * _FG_GFX_SHADER_TYPE_TO_TEXT(ShaderType value) {
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_FRAGMENT, FG_TEXT(FG_GFX_SHADER_FRAGMENT));
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_VERTEX, FG_TEXT(FG_GFX_SHADER_VERTEX));
    #if defined FG_USING_OPENGL
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_TESS_CONTROL, FG_TEXT(FG_GFX_SHADER_TESS_CONTROL));
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_TESS_EVALUATION, FG_TEXT(FG_GFX_SHADER_TESS_EVALUATION));
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_GEOMETRY, FG_TEXT(FG_GFX_SHADER_GEOMETRY));
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_COMPUTE, FG_TEXT(FG_GFX_SHADER_COMPUTE));
    #endif
    return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
    #define FG_GFX_SHADER_TYPE_FROM_TEXT(text)	_FG_GFX_SHADER_TYPE_FROM_TEXT(text)
    #define FG_GFX_SHADER_TYPE_TO_TEXT(value)	_FG_GFX_SHADER_TYPE_TO_TEXT(value)
/**
 * 
 * @param value
 * @return 
 */
inline const char * _FG_GFX_SHADER_SHORT_PREFIX(ShaderType value) {
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_FRAGMENT, "FS");
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_VERTEX, "VS");
    #if defined FG_USING_OPENGL
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_TESS_CONTROL, "TCS");
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_TESS_EVALUATION, "TES");
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_GEOMETRY, "GS");
    FG_RETURN_VAL_IF_EQUAL(value, ShaderType::FG_GFX_SHADER_COMPUTE, "CS");
    #endif
    return NULL;
}

    #define FG_GFX_SHADER_SHORT_PREFIX(value)	_FG_GFX_SHADER_SHORT_PREFIX(value)

/**
 *
 */
enum ShaderPrecision {
    FG_GFX_SHADER_PRECISION_LOW,
    FG_GFX_SHADER_PRECISION_MEDIUM,
    FG_GFX_SHADER_PRECISION_HIGH,
    FG_GFX_SHADER_PRECISION_DEFAULT
};

/**
 *
 */
enum fgGfxPrecision {
    FG_GFX_PRECISION_LOW,
    FG_GFX_PRECISION_MEDIUM,
    FG_GFX_PRECISION_HIGH,
    FG_GFX_PRECISION_DEFAULT
};

    #define FG_GFX_PRECISION_LOW_TEXT       "low"
    #define FG_GFX_PRECISION_MEDIUM_TEXT    "medium"
    #define FG_GFX_PRECISION_HIGH_TEXT      "high"
    #define FG_GFX_PRECISION_DEFAULT_TEXT   "default"
/**
 * Convert text (literal) to corresponding enum value
 * @param text
 * @return 
 */
inline fgGfxPrecision _FG_GFX_PRECISION_FROM_TEXT(const char* text) {
    if(!text)
        return FG_GFX_PRECISION_DEFAULT;
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PRECISION_LOW);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PRECISION_MEDIUM);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_PRECISION_HIGH);
    return FG_GFX_PRECISION_DEFAULT;
}
/**
 * 
 * @param value
 * @return 
 */
inline const char * _FG_GFX_PRECISION_TYPE_TO_TEXT(fgGfxPrecision value) {
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PRECISION_LOW, FG_TEXT(FG_GFX_PRECISION_LOW));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PRECISION_MEDIUM, FG_TEXT(FG_GFX_PRECISION_MEDIUM));
    FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_PRECISION_HIGH, FG_TEXT(FG_GFX_PRECISION_HIGH));
    return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
    #define FG_GFX_PRECISION_FROM_TEXT(text)        _FG_GFX_PRECISION_FROM_TEXT(text)
    #define FG_GFX_PRECISION_TYPE_TO_TEXT(value)    _FG_GFX_PRECISION_TYPE_TO_TEXT(value)

/**
 *
 */
enum class ShaderPrecisionType {
    FG_GFX_LOW_INT = (fgGFXenum)GL_LOW_INT,
    FG_GFX_MEDIUM_INT = (fgGFXenum)GL_MEDIUM_INT,
    FG_GFX_HIGH_INT = (fgGFXenum)GL_HIGH_INT,
    FG_GFX_LOW_FLOAT = (fgGFXenum)GL_LOW_FLOAT,
    FG_GFX_MEDIUM_FLOAT = (fgGFXenum)GL_MEDIUM_FLOAT,
    FG_GFX_HIGH_FLOAT = (fgGFXenum)GL_HIGH_FLOAT
};

//.vert - a vertex shader
//.tesc - a tessellation control shader
//.tese - a tessellation evaluation shader
//.geom - a geometry shader
//.frag - a fragment shader
//.comp - a compute shader

    #define FG_GFX_SHADER_FRAGMENT_STD_SUFFIX		"frag"
    #define FG_GFX_SHADER_VERTEX_STD_SUFFIX		"vert"
    #define FG_GFX_SHADER_TESS_CONTROL_STD_SUFFIX	"tesc"
    #define FG_GFX_SHADER_TESS_EVALUATION_STD_SUFFIX	"tese"
    #define FG_GFX_SHADER_GEOMETRY_STD_SUFFIX		"geom"
    #define FG_GFX_SHADER_COMPUTE_STD_SUFFIX		"comp"

    #define FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX         "program.ini"
    #define FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX        "frag.shader.ini"
    #define FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX          "vert.shader.ini"
    #define FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX    "tesc.shader.ini"
    #define FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX "tese.shader.ini"
    #define FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX        "geom.shader.ini"
    #define FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX         "comp.shader.ini"

    #define FG_GFX_SHADER_CONFIG_STD_SUFFIX                 "shader.ini"

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
/**
 * 
 * @param _type
 * @return 
 */
inline const char * _FG_GFX_SHADER_CFG_STD_SUFFIX(ShaderType _type) {
    FG_RETURN_VAL_IF_EQUAL(_type, ShaderType::FG_GFX_SHADER_FRAGMENT, FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX);
    FG_RETURN_VAL_IF_EQUAL(_type, ShaderType::FG_GFX_SHADER_VERTEX, FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX);
    #if defined FG_USING_OPENGL
    FG_RETURN_VAL_IF_EQUAL(_type, ShaderType::FG_GFX_SHADER_TESS_CONTROL, FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX);
    FG_RETURN_VAL_IF_EQUAL(_type, ShaderType::FG_GFX_SHADER_TESS_EVALUATION, FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX);
    FG_RETURN_VAL_IF_EQUAL(_type, ShaderType::FG_GFX_SHADER_GEOMETRY, FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX);
    FG_RETURN_VAL_IF_EQUAL(_type, ShaderType::FG_GFX_SHADER_COMPUTE, FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX);
    #endif
    return NULL;
};

    #define FG_GFX_SHADER_CFG_STD_SUFFIX(type) _FG_GFX_SHADER_CFG_STD_SUFFIX(type)

namespace fg {
    namespace gfx {

        /**
         *
         */
        enum UniformType {
            FG_GFX_UNIFORM_INVALID, // Invalid uniform type
            FG_GFX_M_MATRIX, // Model matrix
            FG_GFX_MV_MATRIX, // ModelView matrix
            FG_GFX_MVP_MATRIX, // ModelViewProjection matrix
            FG_GFX_ENVIRONMENT_MAP, // Environment map
            FG_GFX_NORMAL_MAP, // Normal map
            FG_GFX_BUMP_MAP, // Bump map
            FG_GFX_PLAIN_TEXTURE, // First (plain) texture
            FG_GFX_CUBE_TEXTURE, // Some cube texture
            FG_GFX_DIRECTIONAL_LIGHT, // Directional light (need probably a little more of those)
            FG_GFX_MATERIAL, // Material to be used
            FG_GFX_PHASE,
            FG_GFX_DELTA_TIME,
            FG_GFX_TIMESTAMP,
            FG_GFX_CUSTOM_COLOR, // global color
            FG_GFX_ATTRIB_MASK, // attribute mask
            FG_GFX_USE_TEXTURE, // whether the texture is used, >0.5 texture used (true), <0.5 false
            FG_GFX_DRAW_SKYBOX, // whether the skybox is being drawn (#FIXME)
            FG_GFX_CUSTOM // Custom uniform - can be any type (only one per shader program)
        };
    };
};

    #define FG_GFX_M_MATRIX_TEXT		"ModelMatrix"
    #define FG_GFX_MV_MATRIX_TEXT		"ModelViewMatrix"
    #define FG_GFX_MVP_MATRIX_TEXT		"ModelViewProjectionMatrix"
    #define FG_GFX_ENVIRONMENT_MAP_TEXT		"EnvironmentMap"
    #define FG_GFX_NORMAL_MAP_TEXT		"NormalMap"
    #define FG_GFX_BUMP_MAP_TEXT		"BumpMap"
    #define FG_GFX_PLAIN_TEXTURE_TEXT		"PlainTexture"
    #define FG_GFX_CUBE_TEXTURE_TEXT            "CubeTexture"
    #define FG_GFX_DIRECTIONAL_LIGHT_TEXT       "DirectionalLight"
    #define FG_GFX_MATERIAL_TEXT		"Material"
    #define FG_GFX_PHASE_TEXT			"Phase"
    #define FG_GFX_DELTA_TIME_TEXT		"DeltaTime"
    #define FG_GFX_TIMESTAMP_TEXT		"Timestamp"
    #define FG_GFX_CUSTOM_COLOR_TEXT		"CustomColor"
    #define FG_GFX_ATTRIB_MASK_TEXT		"AttribMask"
    #define FG_GFX_USE_TEXTURE_TEXT		"UseTexture"
    #define FG_GFX_DRAW_SKYBOX_TEXT             "DrawSkyBox"
    #define FG_GFX_CUSTOM_TEXT			"Custom"
/**
 * Convert text (literal) to corresponding enum value
 * @param text
 * @return 
 */
inline fg::gfx::UniformType _FG_GFX_UNIFORM_TYPE_FROM_TEXT(const char* text) {
    if(!text)
        return fg::gfx::FG_GFX_UNIFORM_INVALID;
    
    if(strncasecmp(text, FG_GFX_M_MATRIX_TEXT, strlen(FG_GFX_M_MATRIX_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_M_MATRIX);
    }
    if(strncasecmp(text, FG_GFX_MV_MATRIX_TEXT, strlen(FG_GFX_MV_MATRIX_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_MV_MATRIX);
    }
    if(strncasecmp(text, FG_GFX_MVP_MATRIX_TEXT, strlen(FG_GFX_MVP_MATRIX_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_MVP_MATRIX);
    }
    if(strncasecmp(text, FG_GFX_ENVIRONMENT_MAP_TEXT, strlen(FG_GFX_ENVIRONMENT_MAP_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_ENVIRONMENT_MAP);
    }
    if(strncasecmp(text, FG_GFX_NORMAL_MAP_TEXT, strlen(FG_GFX_NORMAL_MAP_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_NORMAL_MAP);
    }
    if(strncasecmp(text, FG_GFX_BUMP_MAP_TEXT, strlen(FG_GFX_BUMP_MAP_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_BUMP_MAP);
    }
    if(strncasecmp(text, FG_GFX_PLAIN_TEXTURE_TEXT, strlen(FG_GFX_PLAIN_TEXTURE_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_PLAIN_TEXTURE);
    }
    if(strncasecmp(text, FG_GFX_CUBE_TEXTURE_TEXT, strlen(FG_GFX_CUBE_TEXTURE_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_CUBE_TEXTURE);
    }
    if(strncasecmp(text, FG_GFX_DIRECTIONAL_LIGHT_TEXT, strlen(FG_GFX_DIRECTIONAL_LIGHT_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_DIRECTIONAL_LIGHT);
    }
    if(strncasecmp(text, FG_GFX_MATERIAL_TEXT, strlen(FG_GFX_MATERIAL_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_MATERIAL);
    }
    if(strncasecmp(text, FG_GFX_PHASE_TEXT, strlen(FG_GFX_PHASE_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_PHASE);
    }
    if(strncasecmp(text, FG_GFX_DELTA_TIME_TEXT, strlen(FG_GFX_DELTA_TIME_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_DELTA_TIME);
    }
    if(strncasecmp(text, FG_GFX_TIMESTAMP_TEXT, strlen(FG_GFX_TIMESTAMP_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_TIMESTAMP);
    }
    if(strncasecmp(text, FG_GFX_CUSTOM_COLOR_TEXT, strlen(FG_GFX_CUSTOM_COLOR_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_CUSTOM_COLOR);
    }
    if(strncasecmp(text, FG_GFX_ATTRIB_MASK_TEXT, strlen(FG_GFX_ATTRIB_MASK_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_ATTRIB_MASK);
    }
    if(strncasecmp(text, FG_GFX_USE_TEXTURE_TEXT, strlen(FG_GFX_USE_TEXTURE_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_USE_TEXTURE);
    }
    if(strncasecmp(text, FG_GFX_DRAW_SKYBOX_TEXT, strlen(FG_GFX_DRAW_SKYBOX_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_DRAW_SKYBOX);
    }
    if(strncasecmp(text, FG_GFX_CUSTOM_TEXT, strlen(FG_GFX_CUSTOM_TEXT)) == 0) {
        return (fg::gfx::FG_GFX_CUSTOM);
    }

    return fg::gfx::FG_GFX_UNIFORM_INVALID;
}
/**
 * 
 * @param value
 * @return 
 */
inline const char * _FG_GFX_UNIFORM_TYPE_TO_TEXT(fg::gfx::UniformType value) {
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_M_MATRIX, FG_TEXT(FG_GFX_M_MATRIX));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_MV_MATRIX, FG_TEXT(FG_GFX_MV_MATRIX));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_MVP_MATRIX, FG_TEXT(FG_GFX_MVP_MATRIX));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_ENVIRONMENT_MAP, FG_TEXT(FG_GFX_ENVIRONMENT_MAP));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_NORMAL_MAP, FG_TEXT(FG_GFX_NORMAL_MAP));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_BUMP_MAP, FG_TEXT(FG_GFX_BUMP_MAP));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_PLAIN_TEXTURE, FG_TEXT(FG_GFX_PLAIN_TEXTURE));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_CUBE_TEXTURE, FG_TEXT(FG_GFX_CUBE_TEXTURE));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_DIRECTIONAL_LIGHT, FG_TEXT(FG_GFX_DIRECTIONAL_LIGHT));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_MATERIAL, FG_TEXT(FG_GFX_MATERIAL));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_PHASE, FG_TEXT(FG_GFX_PHASE));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_DELTA_TIME, FG_TEXT(FG_GFX_DELTA_TIME));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_TIMESTAMP, FG_TEXT(FG_GFX_TIMESTAMP));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_CUSTOM_COLOR, FG_TEXT(FG_GFX_CUSTOM_COLOR));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_ATTRIB_MASK, FG_TEXT(FG_GFX_ATTRIB_MASK));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_USE_TEXTURE, FG_TEXT(FG_GFX_USE_TEXTURE));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_DRAW_SKYBOX, FG_TEXT(FG_GFX_DRAW_SKYBOX));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_CUSTOM, FG_TEXT(FG_GFX_CUSTOM));
    return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
    #define FG_GFX_UNIFORM_TYPE_FROM_TEXT(text)	_FG_GFX_UNIFORM_TYPE_FROM_TEXT(text)
    #define FG_GFX_UNIFORM_TYPE_TO_TEXT(value)	_FG_GFX_UNIFORM_TYPE_TO_TEXT(value)

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

    #ifndef FG_GFX_ATTRIBUTE_COUNT
        #define FG_GFX_ATTRIBUTE_COUNT	5 // #FIXME
    #endif

    #define FG_GFX_POSITION_TEXT	"Position"      // Position (vec3)
    #define FG_GFX_NORMAL_TEXT		"Normal"        // Normal (vec3)
    #define FG_GFX_TEXTURE_COORD_TEXT	"TextureCoord"  // UV - tex coord (vec2)
    #define FG_GFX_COLOR_TEXT		"Color"         // Color (vec4)
    #define FG_GFX_TANGENT_TEXT		"Tangent"       // Tangent ?
/**
 * Convert text (literal) to corresponding enum value
 * @param text
 * @return 
 */
inline fg::gfx::AttributeType _FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(const char* text) {
    if(!text)
        return fg::gfx::FG_GFX_ATTRIBUTE_INVALID;

    if(strncasecmp(text, FG_GFX_POSITION_TEXT, strlen(FG_GFX_POSITION_TEXT)) == 0) {
        return fg::gfx::FG_GFX_POSITION;
    }
    if(strncasecmp(text, FG_GFX_NORMAL_TEXT, strlen(FG_GFX_NORMAL_TEXT)) == 0) {
        return fg::gfx::FG_GFX_NORMAL;
    }
    if(strncasecmp(text, FG_GFX_TEXTURE_COORD_TEXT, strlen(FG_GFX_TEXTURE_COORD_TEXT)) == 0) {
        return fg::gfx::FG_GFX_TEXTURE_COORD;
    }
    if(strncasecmp(text, FG_GFX_COLOR_TEXT, strlen(FG_GFX_COLOR_TEXT)) == 0) {
        return fg::gfx::FG_GFX_COLOR;
    }
    if(strncasecmp(text, FG_GFX_TANGENT_TEXT, strlen(FG_GFX_TANGENT_TEXT)) == 0) {
        return fg::gfx::FG_GFX_TANGENT;
    }

    return fg::gfx::FG_GFX_ATTRIBUTE_INVALID;
}
/**
 * 
 * @param value
 * @return 
 */
inline const char * _FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(fg::gfx::AttributeType value) {
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_POSITION, FG_TEXT(FG_GFX_POSITION));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_NORMAL, FG_TEXT(FG_GFX_NORMAL));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_TEXTURE_COORD, FG_TEXT(FG_GFX_TEXTURE_COORD));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_COLOR, FG_TEXT(FG_GFX_COLOR));
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_TANGENT, FG_TEXT(FG_GFX_TANGENT));
    return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
    #define FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(text)   _FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(text)
    #define FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(value)    _FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(value)
/**
 * 
 * @param value
 * @return 
 */
inline fgGFXint _FG_GFX_ATTRIB_LOCATION_FROM_TYPE(fg::gfx::AttributeType value) {
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_POSITION, (fgGFXint)FG_GFX_ATTRIB_POS_LOCATION);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_NORMAL, (fgGFXint)FG_GFX_ATTRIB_NORM_LOCATION);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_TEXTURE_COORD, (fgGFXint)FG_GFX_ATTRIB_UVS_LOCATION);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_COLOR, (fgGFXint)FG_GFX_ATTRIB_COLOR_LOCATION);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_TANGENT, (fgGFXint)FG_GFX_ATTRIB_TANGENT_LOCATION);
    return 0;
}

    #define FG_GFX_ATTRIB_LOCATION_FROM_TYPE(value) _FG_GFX_ATTRIB_LOCATION_FROM_TYPE(value)

// #FIXME - this function is very sad because it has a retarded name :(
/**
 * 
 * @param value
 * @return 
 */
inline fgGFXenum _FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(fg::gfx::AttributeType value) {
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_POSITION, (fgGFXenum)FG_GFX_FLOAT_VEC4);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_NORMAL, (fgGFXenum)FG_GFX_FLOAT_VEC3);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_COLOR, (fgGFXenum)FG_GFX_FLOAT_VEC4);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_TEXTURE_COORD, (fgGFXenum)FG_GFX_FLOAT_VEC2);
    FG_RETURN_VAL_IF_EQUAL(value, fg::gfx::FG_GFX_TANGENT, (fgGFXenum)FG_GFX_FLOAT_VEC3);
    return (fgGFXenum)0;
}

    #define FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(value) _FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(value)

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SUniformBind {
            /// Name of the variable to bind
            std::string variableName;
            /// Location of the variable
            fgGFXint location;
            /// Type of the uniform variable to bind
            UniformType type;
            /// Data type of the uniform variable
            fgGFXenum dataType;
            /// Precision of the uniform
            fgGfxPrecision precision;
            /**
             * 
             */
            SUniformBind() :
            variableName(""),
            location(-1),
            type(FG_GFX_UNIFORM_INVALID),
            dataType(FG_GFX_FLOAT_VEC4),
            precision(FG_GFX_PRECISION_DEFAULT) { }
            /**
             * 
             * @param _variableName
             * @param _type
             */
            SUniformBind(const char *_variableName,
                         UniformType _type) :
            variableName(),
            location(-1),
            type(_type),
            dataType(FG_GFX_FLOAT_VEC4),
            precision(FG_GFX_PRECISION_DEFAULT) {
                if(_variableName)
                    variableName = _variableName;
            }
            /**
             * 
             */
            ~SUniformBind() {
                variableName.clear();
            }
            inline int operator ==(const SUniformBind &b) const {
                return (b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
            inline int operator !=(const SUniformBind &b) const {
                return !(b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
        };

        // The attribute qualifier can be used only with the data types:
        // float, vec2, vec3, vec4, mat2, mat3, and mat4.
        // Attribute variables cannot be declared as arrays or structures.

        /**
         *
         */
        struct SAttributeBind {
            /// Name of the variable to bind
            std::string variableName;
            /// Location to which given attribute will be bound (must not equal -1)
            fgGFXint location;
            /// The engine specific attribute type
            AttributeType type;
            /// Specifies the data type of a single element.
            /// Can be float, vec2, vec3, vec4, mat2, mat3, and mat4.
            fgGFXenum dataType;
            /// Currently used precision for this attribute
            fgGfxPrecision precision;
            /// Is the attribute bound?
            fgGFXboolean isBound;
            /**
             * 
             */
            SAttributeBind() :
            variableName(""),
            location(-1),
            type(FG_GFX_ATTRIBUTE_INVALID),
            dataType(FG_GFX_FLOAT_VEC4),
            precision(FG_GFX_PRECISION_DEFAULT),
            isBound(FG_GFX_FALSE) { }
            /**
             * 
             * @param _variableName
             * @param _type
             */
            SAttributeBind(const char *_variableName,
                           AttributeType _type) :
            variableName(),
            location(-1),
            type(_type),
            dataType(FG_GFX_FLOAT_VEC4),
            precision(FG_GFX_PRECISION_DEFAULT),
            isBound(FG_GFX_FALSE) {
                if(_variableName)
                    variableName = _variableName;
                setType(_type);

            }
            /**
             * 
             */
            ~SAttributeBind() {
                variableName.clear();
            }
            /**
             * This will not only set the type but also location and dataType 
             * @param _type
             */
            void setType(AttributeType _type) {
                if(_type == FG_GFX_ATTRIBUTE_INVALID)
                    return;
                type = _type;
                location = FG_GFX_ATTRIB_LOCATION_FROM_TYPE(type);
                dataType = FG_GFX_ATTRIB_DATA_TYPE_FROM_TYPE(type);
            }
            inline int operator ==(const SAttributeBind &b) const {
                return (b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
            inline int operator !=(const SAttributeBind &b) const {
                return !(b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
            inline bool operator >(const SAttributeBind& a) const {
                return (int)(this->type) > (int)(a.type);
            }
            inline bool operator <(const SAttributeBind& a) const {
                return (int)(this->type) < (int)(a.type);
            }
            inline bool operator >=(const SAttributeBind& a) const {
                return (int)(this->type) >= (int)(a.type);
            }
            inline bool operator <=(const SAttributeBind& a) const {
                return (int)(this->type) <= (int)(a.type);
            }
        };

        /**
         *
         */
        struct SShaderConstantDef {
            ///
            std::string name;
            ///
            fgBool value;
            /**
             * 
             */
            SShaderConstantDef() : name(), value(FG_FALSE) { }
            /**
             * 
             * @param _name
             * @param _value
             */
            SShaderConstantDef(const char *_name, fgBool _value) : name(), value(_value) {
                if(_name)
                    name = _name;
            }
            /**
             * 
             */
            ~SShaderConstantDef() {
                name.clear();
            }

            // #FIXME - need some standard abstract class for that kind of operations
            /**
             * 
             * @param buf
             * @param maxlen
             */
            void toString(char *buf, unsigned int maxlen = 128) {
                if(!buf)
                    return;
                snprintf(buf, (size_t)maxlen, "#define %s %d", name.c_str(), value);
            }
            /**
             * 
             * @param buf
             * @return 
             */
            std::string & toString(std::string & buf) {
                buf.append("#define ").append(name);
                if(value)
                    buf.append(" 1");
                else
                    buf.append(" 0");
                return buf;
            }
        };
    };
};

    #undef FG_INC_GFX_SHADER_DEFS_BLOCK
#endif /* FG_INC_GFX_SHADER_DEFS */
