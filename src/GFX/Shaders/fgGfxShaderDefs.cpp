/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxShaderDefs.h"
#include "Util/fgStrings.h"

#define FG_GFX_SHADER_FRAGMENT_TEXT         "FragmentShader"
#define FG_GFX_SHADER_VERTEX_TEXT           "VertexShader"
#define FG_GFX_SHADER_TESS_CONTROL_TEXT     "TessellationControlShader"
#define FG_GFX_SHADER_TESS_EVALUATION_TEXT  "TessellationEvaluationShader"
#define FG_GFX_SHADER_GEOMETRY_TEXT         "GeometryShader"
#define FG_GFX_SHADER_COMPUTE_TEXT          "ComputeShader"

#define FG_GFX_PRECISION_LOW_TEXT       "low"
#define FG_GFX_PRECISION_MEDIUM_TEXT    "medium"
#define FG_GFX_PRECISION_HIGH_TEXT      "high"
#define FG_GFX_PRECISION_DEFAULT_TEXT   "default"

#define FG_GFX_SHADER_FRAGMENT_STD_SUFFIX       "frag"
#define FG_GFX_SHADER_VERTEX_STD_SUFFIX         "vert"
#define FG_GFX_SHADER_TESS_CONTROL_STD_SUFFIX       "tesc"
#define FG_GFX_SHADER_TESS_EVALUATION_STD_SUFFIX    "tese"
#define FG_GFX_SHADER_GEOMETRY_STD_SUFFIX           "geom"
#define FG_GFX_SHADER_COMPUTE_STD_SUFFIX            "comp"

#define FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX         "program.ini"
#define FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX        "frag.shader.ini"
#define FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX          "vert.shader.ini"
#define FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX    "tesc.shader.ini"
#define FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX "tese.shader.ini"
#define FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX        "geom.shader.ini"
#define FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX         "comp.shader.ini"

#define FG_GFX_SHADER_CONFIG_STD_SUFFIX                 "shader.ini"

#define FG_GFX_M_MATRIX_TEXT            "ModelMatrix"
#define FG_GFX_MV_MATRIX_TEXT           "ModelViewMatrix"
#define FG_GFX_MVP_MATRIX_TEXT          "ModelViewProjectionMatrix"
#define FG_GFX_ENVIRONMENT_MAP_TEXT     "EnvironmentMap"
#define FG_GFX_NORMAL_MAP_TEXT          "NormalMap"
#define FG_GFX_BUMP_MAP_TEXT            "BumpMap"
#define FG_GFX_PLAIN_TEXTURE_TEXT       "PlainTexture"
#define FG_GFX_CUBE_TEXTURE_TEXT        "CubeTexture"
#define FG_GFX_DIRECTIONAL_LIGHT_TEXT   "DirectionalLight"
#define FG_GFX_MATERIAL_TEXT            "Material"
#define FG_GFX_PHASE_TEXT               "Phase"
#define FG_GFX_DELTA_TIME_TEXT          "DeltaTime"
#define FG_GFX_TIMESTAMP_TEXT           "Timestamp"
#define FG_GFX_CUSTOM_COLOR_TEXT        "CustomColor"
#define FG_GFX_ATTRIB_MASK_TEXT         "AttribMask"
#define FG_GFX_USE_TEXTURE_TEXT         "UseTexture"
#define FG_GFX_DRAW_SKYBOX_TEXT         "DrawSkyBox"
#define FG_GFX_CUSTOM_TEXT              "Custom"

namespace fg {
    namespace gfx {
        namespace shaders {

            const ShaderType g_SupportedShaderTypes[] = {ShaderType::SHADER_FRAGMENT,
                                                         ShaderType::SHADER_VERTEX
#if defined(FG_USING_OPENGL)
                ,
                                                         ShaderType::SHADER_TESS_CONTROL,
                                                         ShaderType::SHADER_TESS_EVALUATION,
                                                         ShaderType::SHADER_GEOMETRY,
                                                         ShaderType::SHADER_COMPUTE
#endif
            };

            const char * const g_SupportedShaderTypesText[] = {
                                                               FG_GFX_SHADER_FRAGMENT_TEXT,
                                                               FG_GFX_SHADER_VERTEX_TEXT
#if defined(FG_USING_OPENGL)
                ,
                                                               FG_GFX_SHADER_TESS_CONTROL_TEXT,
                                                               FG_GFX_SHADER_TESS_EVALUATION_TEXT,
                                                               FG_GFX_SHADER_GEOMETRY_TEXT,
                                                               FG_GFX_SHADER_COMPUTE_TEXT
#endif
            };

            const char * const g_ShaderShortPrefixesText[] = {
                                                              "FS",
                                                              "VS"
#if defined(FG_USING_OPENGL)
                ,
                                                              "TCS",
                                                              "TES",
                                                              "GS",
                                                              "CS"
#endif
            };

            const Precision g_PrecisionTypes[] = {
                                                  PRECISION_LOW,
                                                  PRECISION_MEDIUM,
                                                  PRECISION_HIGH,
                                                  PRECISION_DEFAULT
            };

            const char * const g_PrecisionTypesText[] {
                                                       "low",
                                                       "medium",
                                                       "high",
                                                       "default"
            };

            const ShaderPrecision g_ShaderPrecisionTypes[] = {
                                                              SHADER_PRECISION_LOW,
                                                              SHADER_PRECISION_MEDIUM,
                                                              SHADER_PRECISION_HIGH,
                                                              SHADER_PRECISION_DEFAULT
            };

            const char * const g_ShaderCfgSuffixes[] = {
                                                        FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX,
                                                        FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX
#if defined (FG_USING_OPENGL)
                ,
                                                        FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX,
                                                        FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX,
                                                        FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX,
                                                        FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX
#endif
            };

            const UniformType g_UniformTypes[] = {
                                                  UNIFORM_M_MATRIX,
                                                  UNIFORM_MV_MATRIX,
                                                  UNIFORM_MVP_MATRIX,
                                                  UNIFORM_ENVIRONMENT_MAP,
                                                  UNIFORM_NORMAL_MAP,
                                                  UNIFORM_BUMP_MAP,
                                                  UNIFORM_PLAIN_TEXTURE,
                                                  UNIFORM_CUBE_TEXTURE,
                                                  UNIFORM_DIRECTIONAL_LIGHT,
                                                  UNIFORM_MATERIAL,
                                                  UNIFORM_PHASE,
                                                  UNIFORM_DELTA_TIME,
                                                  UNIFORM_TIMESTAMP,
                                                  UNIFORM_CUSTOM_COLOR,
                                                  UNIFORM_ATTRIB_MASK,
                                                  UNIFORM_USE_TEXTURE,
                                                  UNIFORM_DRAW_SKYBOX,
                                                  UNIFORM_CUSTOM
            };

            const char * const g_UniformTypesText[] = {
                                                       FG_GFX_M_MATRIX_TEXT,
                                                       FG_GFX_MV_MATRIX_TEXT,
                                                       FG_GFX_MVP_MATRIX_TEXT,
                                                       FG_GFX_ENVIRONMENT_MAP_TEXT,
                                                       FG_GFX_NORMAL_MAP_TEXT,
                                                       FG_GFX_BUMP_MAP_TEXT,
                                                       FG_GFX_PLAIN_TEXTURE_TEXT,
                                                       FG_GFX_CUBE_TEXTURE_TEXT,
                                                       FG_GFX_DIRECTIONAL_LIGHT_TEXT,
                                                       FG_GFX_MATERIAL_TEXT,
                                                       FG_GFX_PHASE_TEXT,
                                                       FG_GFX_DELTA_TIME_TEXT,
                                                       FG_GFX_TIMESTAMP_TEXT,
                                                       FG_GFX_CUSTOM_COLOR_TEXT,
                                                       FG_GFX_ATTRIB_MASK_TEXT,
                                                       FG_GFX_USE_TEXTURE_TEXT,
                                                       FG_GFX_DRAW_SKYBOX_TEXT,
                                                       FG_GFX_CUSTOM_TEXT
            };

        } // namespace shaders
    } // namespace gfx
} // namespace fg

using namespace fg;
//------------------------------------------------------------------------------

const char* gfx::shaders::getShaderProgramConfigSuffix(void) {
    return FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX;
}
//------------------------------------------------------------------------------

gfx::shaders::ShaderType gfx::shaders::getShaderTypeFromText(const char* text) {
    ShaderType result = shaders::SHADER_INVALID;
    if(!text)
        return result;
    if(!text[0])
        return result;
    const unsigned int n = sizeof (g_SupportedShaderTypes) / sizeof (ShaderType);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(g_SupportedShaderTypesText[i], text, FG_FALSE)) {
            result = g_SupportedShaderTypes[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::ShaderType gfx::shaders::getShaderTypeFromText(const std::string& text) {
    return getShaderTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getTextFromShaderType(ShaderType value) {
    if(value == shaders::SHADER_INVALID)
        return NULL;
    const unsigned int n = sizeof (gfx::shaders::g_SupportedShaderTypes) / sizeof (gfx::shaders::ShaderType);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(gfx::shaders::g_SupportedShaderTypes[i] == value) {
            // shader type as text (VertexShader/FragmentShader/...)
            result = gfx::shaders::g_SupportedShaderTypesText[i];
        }
    }
    return result;
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getShaderShortPrefix(ShaderType value) {
    if(value == gfx::shaders::SHADER_INVALID)
        return NULL;
    const unsigned int n = sizeof (g_SupportedShaderTypes) / sizeof (ShaderType);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(g_SupportedShaderTypes[i] == value) {
            // short prefix (FS/VS/...)
            result = g_ShaderShortPrefixesText[i];
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::Precision gfx::shaders::getPrecisionFromText(const char* text) {
    Precision result = shaders::PRECISION_DEFAULT;
    if(!text)
        return result;
    if(!text[0])
        return result;
    const unsigned int n = sizeof (g_PrecisionTypes) / sizeof (Precision);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(g_PrecisionTypesText[i], text, FG_FALSE)) {
            // PRECISION_LOW/PRECISION_MEDIUM/...
            result = g_PrecisionTypes[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::Precision gfx::shaders::getPrecisionFromText(const std::string& text) {
    return getPrecisionFromText(text.c_str());
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getTextFromPrecision(Precision value) {
    const unsigned int n = sizeof (g_PrecisionTypes) / sizeof (Precision);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(g_PrecisionTypes[i] == value) {
            // low/medium/high/...
            result = g_PrecisionTypesText[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::ShaderPrecision gfx::shaders::getShaderPrecisionFromText(const char* text) {
    ShaderPrecision result = shaders::SHADER_PRECISION_DEFAULT;
    const unsigned int n = sizeof (g_ShaderPrecisionTypes) / sizeof (ShaderPrecision);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(g_PrecisionTypesText[i], text, FG_FALSE)) {
            // SHADER_PRECISION_LOW/SHADER_PRECISION_MEDIUM/...
            result = g_ShaderPrecisionTypes[i];
            break;
        }
    }
    return result;

}
//------------------------------------------------------------------------------

gfx::shaders::ShaderPrecision gfx::shaders::getShaderPrecisionFromText(const std::string& text) {
    return getShaderPrecisionFromText(text.c_str());
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getTextFromShaderPrecision(ShaderPrecision value) {
    const unsigned int n = sizeof (g_ShaderPrecisionTypes) / sizeof (ShaderPrecision);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(g_ShaderPrecisionTypes[i] == value) {
            // low/medium/high/...
            result = g_PrecisionTypesText[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::Precision gfx::shaders::convertShaderPrecisionToPrecision(ShaderPrecision value) {
    Precision result;
    const unsigned int n = sizeof (g_ShaderPrecisionTypes) / sizeof (ShaderPrecision);
    for(unsigned int i = 0; i < n; i++) {
        if(g_ShaderPrecisionTypes[i] == value) {
            // PRECISION_LOW/PRECISION_MEDIUM/...
            result = g_PrecisionTypes[i];
            break;
        }
    }

    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::ShaderPrecision gfx::shaders::convertPrecisionToShaderPrecision(Precision value) {
    ShaderPrecision result;
    const unsigned int n = sizeof (g_PrecisionTypes) / sizeof (Precision);
    for(unsigned int i = 0; i < n; i++) {
        if(g_PrecisionTypes[i] == value) {
            // SHADER_PRECISION_LOW/SHADER_PRECISION_MEDIUM/...
            result = g_ShaderPrecisionTypes[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getShaderConfigSuffix(ShaderType value) {
    if(value == shaders::SHADER_INVALID)
        return NULL;
    const unsigned int n = sizeof (g_SupportedShaderTypes) / sizeof (ShaderType);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(g_SupportedShaderTypes[i] == value) {
            // shader config suffix (frag.shader.ini/vert.shader.ini)
            result = g_ShaderCfgSuffixes[i];
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::UniformType gfx::shaders::getUniformTypeFromText(const char* text) {
    UniformType result = shaders::UNIFORM_INVALID;
    if(!text)
        return result;
    if(!text[0])
        return result;
    const unsigned int n = sizeof (g_UniformTypes) / sizeof (UniformType);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(g_UniformTypesText[i], text, FG_FALSE)) {
            result = g_UniformTypes[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::UniformType gfx::shaders::getUniformTypeFromText(const std::string& text) {
    return getUniformTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getTextFromUniformType(UniformType value) {
    const char* result = NULL;
    if(value == shaders::UNIFORM_INVALID)
        return result;
    const unsigned int n = sizeof (g_UniformTypes) / sizeof (UniformType);
    for(unsigned int i = 0; i < n; i++) {
        if(g_UniformTypes[i] == value) {
            result = g_UniformTypesText[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::SUniformBind::SUniformBind() :
variableName(""),
location(-1),
type(shaders::UNIFORM_INVALID),
dataType(FG_GFX_FLOAT_VEC4),
precision(shaders::PRECISION_DEFAULT) { }
//------------------------------------------------------------------------------

gfx::SUniformBind::SUniformBind(const char *_variableName,
                                shaders::UniformType _type) :
variableName(),
location(-1),
type(_type),
dataType(FG_GFX_FLOAT_VEC4),
precision(shaders::PRECISION_DEFAULT) {
    if(_variableName)
        variableName = _variableName;
}
//------------------------------------------------------------------------------

gfx::SUniformBind::~SUniformBind() {
    variableName.clear();
}
//------------------------------------------------------------------------------

gfx::SAttributeBind::SAttributeBind() :
variableName(""),
location(-1),
type(ATTRIBUTE_INVALID),
dataType(FG_GFX_FLOAT_VEC4),
precision(shaders::PRECISION_DEFAULT),
isBound(FG_GFX_FALSE) { }
//------------------------------------------------------------------------------

gfx::SAttributeBind::SAttributeBind(const char *_variableName,
                                    AttributeType _type) :
variableName(),
location(-1),
type(_type),
dataType(FG_GFX_FLOAT_VEC4),
precision(shaders::PRECISION_DEFAULT),
isBound(FG_GFX_FALSE) {
    if(_variableName)
        variableName = _variableName;
    setType(_type);

}
//------------------------------------------------------------------------------

gfx::SAttributeBind::~SAttributeBind() {
    variableName.clear();
}
//------------------------------------------------------------------------------

void gfx::SAttributeBind::setType(AttributeType _type) {
    if(_type == ATTRIBUTE_INVALID)
        return;
    type = _type;
    location = getAttributeLocationFromType(type);
    dataType = getDataTypeFromAttributeType(type);
}
//------------------------------------------------------------------------------

gfx::SShaderConstantDef::SShaderConstantDef() : name(), value(FG_FALSE) { }
//------------------------------------------------------------------------------

gfx::SShaderConstantDef::SShaderConstantDef(const char *_name, fgBool _value) :
name(),
value(_value) {
    if(_name)
        name = _name;
}
//------------------------------------------------------------------------------

gfx::SShaderConstantDef::~SShaderConstantDef() {
    name.clear();
}
//------------------------------------------------------------------------------

void gfx::SShaderConstantDef::toString(char *buf, unsigned int maxlen) {
    if(!buf)
        return;
    snprintf(buf, (size_t)maxlen, "#define %s %d", name.c_str(), value);
}
//------------------------------------------------------------------------------

std::string& gfx::SShaderConstantDef::toString(std::string & buf) {
    buf.append("#define ").append(name);
    if(value)
        buf.append(" 1");
    else
        buf.append(" 0");
    return buf;
}
//------------------------------------------------------------------------------
