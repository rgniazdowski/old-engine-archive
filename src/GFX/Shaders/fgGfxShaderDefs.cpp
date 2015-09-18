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

#define FG_GFX_USAGE_EMPTY_TEXT                        "Empty"
#define FG_GFX_USAGE_FALLBACK_TEXT                     "Fallback"
#define FG_GFX_USAGE_DEFAULT_TEXT                      "Default"
#define FG_GFX_USAGE_LOW_QUALITY_TEXT                  "LowQuality"
#define FG_GFX_USAGE_MEDIUM_QUALITY_TEXT               "MediumQuality"
#define FG_GFX_USAGE_HIGH_QUALITY_TEXT                 "HighQuality"
#define FG_GFX_USAGE_VERTEX_LIGHTING_TEXT              "VertexLighting"
#define FG_GFX_USAGE_FRAGMENT_LIGHTING_TEXT            "FragmentLighting"
#define FG_GFX_USAGE_FRAGMENT_LIGHTING_MUTLTIPLE_TEXT  "FragmentLightingMultiple"
#define FG_GFX_USAGE_ENVIRONMENT_MAPPING_TEXT          "EnvironmentMapping"
#define FG_GFX_USAGE_BUMP_MAPPING_TEXT                 "BumpMapping"
#define FG_GFX_USAGE_MESH_SKINNING_TEXT                "MeshSkinning"
#define FG_GFX_USAGE_MOTION_BLUR_TEXT                  "MotionBlur"
#define FG_GFX_USAGE_ANTIALIASING_TEXT                 "AntiAliasing"
#define FG_GFX_USAGE_GAUSSIAN_BLUR_TEXT                "GaussianBlur"
#define FG_GFX_USAGE_CARTOON_EFFECT_TEXT               "CartoonEffect"
#define FG_GFX_USAGE_PARTICLE_RENDER_TEXT              "ParticleRender"
#define FG_GFX_USAGE_SKYBOX_RENDER_TEXT                "SkyboxRender"
#define FG_GFX_USAGE_GUI_RENDER_TEXT                   "GuiRender"
#define FG_GFX_USAGE_2D_RENDER_TEXT                    "2DRender"
#define FG_GFX_USAGE_FLAT_RENDER_TEXT                  "FlatRender"

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
#define FG_GFX_AMBIENT_MAP_TEXT         "AmbientMap"
#define FG_GFX_SPECULAR_MAP_TEXT        "SpecularMap"
#define FG_GFX_NORMAL_MAP_TEXT          "NormalMap"
#define FG_GFX_BUMP_MAP_TEXT            "BumpMap"
#define FG_GFX_PLAIN_TEXTURE_TEXT       "PlainTexture"
#define FG_GFX_CUBE_TEXTURE_TEXT        "CubeTexture"
#define FG_GFX_DIRECTIONAL_LIGHT_TEXT   "DirectionalLight"
#define FG_GFX_DIRECTIONAL_LIGHT_DIRECTION_TEXT   "direction"
#define FG_GFX_DIRECTIONAL_LIGHT_AMBIENT_TEXT     "ambient"
#define FG_GFX_DIRECTIONAL_LIGHT_DIFFUSE_TEXT     "diffuse"
#define FG_GFX_DIRECTIONAL_LIGHT_SPECULAR_TEXT    "specular"
#define FG_GFX_MATERIAL_TEXT            "Material"
#define FG_GFX_MATERIAL_AMBIENT_TEXT            "ambient"
#define FG_GFX_MATERIAL_DIFFUSE_TEXT            "diffuse"
#define FG_GFX_MATERIAL_SPECULAR_TEXT           "specular"
#define FG_GFX_MATERIAL_SHININESS_TEXT          "shininess"
#define FG_GFX_PHASE_TEXT               "Phase"
#define FG_GFX_DELTA_TIME_TEXT          "DeltaTime"
#define FG_GFX_TIMESTAMP_TEXT           "Timestamp"
#define FG_GFX_CUSTOM_COLOR_TEXT        "CustomColor"
#define FG_GFX_ATTRIB_MASK_TEXT         "AttribMask"
#define FG_GFX_USE_TEXTURE_TEXT         "UseTexture"
#define FG_GFX_DRAW_SKYBOX_TEXT         "DrawSkyBox"
#define FG_GFX_BONE_MATRICES_TEXT       "BoneMatrices"
#define FG_GFX_BONE_DUAL_QUATS_TEXT     "BoneDualQuats"
#define FG_GFX_CUSTOM_TEXT              "Custom"

#define FG_GFX_BLOCK_INVALID_TEXT       "Invalid"
#define FG_GFX_BLOCK_TRANSFORM_TEXT     "Transform"
#define FG_GFX_BLOCK_LIGHTING_INFO_TEXT "LightingInfo"
#define FG_GFX_BLOCK_MATERIAL_INFO_TEXT "MaterialInfo"

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
                                                  UNIFORM_AMBIENT_MAP,
                                                  UNIFORM_SPECULAR_MAP,
                                                  UNIFORM_NORMAL_MAP,
                                                  UNIFORM_BUMP_MAP,
                                                  UNIFORM_PLAIN_TEXTURE,
                                                  UNIFORM_CUBE_TEXTURE,
                                                  UNIFORM_DIRECTIONAL_LIGHT,
                                                  UNIFORM_DIRECTIONAL_LIGHT_DIRECTION,
                                                  UNIFORM_DIRECTIONAL_LIGHT_AMBIENT,
                                                  UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE,
                                                  UNIFORM_DIRECTIONAL_LIGHT_SPECULAR,
                                                  UNIFORM_MATERIAL,
                                                  UNIFORM_MATERIAL_AMBIENT,
                                                  UNIFORM_MATERIAL_DIFFUSE,
                                                  UNIFORM_MATERIAL_SPECULAR,
                                                  UNIFORM_MATERIAL_SHININESS,
                                                  UNIFORM_PHASE,
                                                  UNIFORM_DELTA_TIME,
                                                  UNIFORM_TIMESTAMP,
                                                  UNIFORM_CUSTOM_COLOR,
                                                  UNIFORM_ATTRIB_MASK,
                                                  UNIFORM_USE_TEXTURE,
                                                  UNIFORM_DRAW_SKYBOX,
                                                  UNIFORM_BONE_MATRICES,
                                                  UNIFORM_BONE_DUAL_QUATERNIONS,
                                                  UNIFORM_CUSTOM
            };

            const char * const g_UniformTypesText[] = {
                                                       FG_GFX_M_MATRIX_TEXT,
                                                       FG_GFX_MV_MATRIX_TEXT,
                                                       FG_GFX_MVP_MATRIX_TEXT,
                                                       FG_GFX_ENVIRONMENT_MAP_TEXT,
                                                       FG_GFX_AMBIENT_MAP_TEXT,
                                                       FG_GFX_SPECULAR_MAP_TEXT,
                                                       FG_GFX_NORMAL_MAP_TEXT,
                                                       FG_GFX_BUMP_MAP_TEXT,
                                                       FG_GFX_PLAIN_TEXTURE_TEXT,
                                                       FG_GFX_CUBE_TEXTURE_TEXT,
                                                       FG_GFX_DIRECTIONAL_LIGHT_TEXT,
                                                       FG_GFX_DIRECTIONAL_LIGHT_DIRECTION_TEXT,
                                                       FG_GFX_DIRECTIONAL_LIGHT_AMBIENT_TEXT,
                                                       FG_GFX_DIRECTIONAL_LIGHT_DIFFUSE_TEXT,
                                                       FG_GFX_DIRECTIONAL_LIGHT_SPECULAR_TEXT,
                                                       FG_GFX_MATERIAL_TEXT,
                                                       FG_GFX_MATERIAL_AMBIENT_TEXT,
                                                       FG_GFX_MATERIAL_DIFFUSE_TEXT,
                                                       FG_GFX_MATERIAL_SPECULAR_TEXT,
                                                       FG_GFX_MATERIAL_SHININESS_TEXT,
                                                       FG_GFX_PHASE_TEXT,
                                                       FG_GFX_DELTA_TIME_TEXT,
                                                       FG_GFX_TIMESTAMP_TEXT,
                                                       FG_GFX_CUSTOM_COLOR_TEXT,
                                                       FG_GFX_ATTRIB_MASK_TEXT,
                                                       FG_GFX_USE_TEXTURE_TEXT,
                                                       FG_GFX_DRAW_SKYBOX_TEXT,
                                                       FG_GFX_BONE_MATRICES_TEXT,
                                                       FG_GFX_BONE_DUAL_QUATS_TEXT,
                                                       FG_GFX_CUSTOM_TEXT
            };

            const UniformBlockType g_UniformBlockTypes[] = {
                                                            UNIFORM_BLOCK_TRANSFORM,
                                                            UNIFORM_BLOCK_LIGHTING_INFO,
                                                            UNIFORM_BLOCK_MATERIAL_INFO
            };

            const char * const g_UniformBlockTypesText[] = {
                                                            FG_GFX_BLOCK_TRANSFORM_TEXT,
                                                            FG_GFX_BLOCK_LIGHTING_INFO_TEXT,
                                                            FG_GFX_BLOCK_MATERIAL_INFO_TEXT
            };

            const UsageMask g_UsageMaskTypes[] = {
                                                  USAGE_EMPTY_BIT,
                                                  USAGE_FALLBACK_BIT,
                                                  USAGE_DEFAULT_BIT,
                                                  USAGE_LOW_QUALITY_BIT,
                                                  USAGE_MEDIUM_QUALITY_BIT,
                                                  USAGE_HIGH_QUALITY_BIT,
                                                  USAGE_VERTEX_LIGHTING_BIT,
                                                  USAGE_FRAGMENT_LIGHTING_BIT,
                                                  USAGE_FRAGMENT_LIGHTING_MUTLTIPLE_BIT,
                                                  USAGE_ENVIRONMENT_MAPPING_BIT,
                                                  USAGE_BUMP_MAPPING_BIT,
                                                  USAGE_MESH_SKINNING_BIT,
                                                  USAGE_MOTION_BLUR_BIT,
                                                  USAGE_ANTIALIASING_BIT,
                                                  USAGE_GAUSSIAN_BLUR_BIT,
                                                  USAGE_CARTOON_EFFECT_BIT,
                                                  USAGE_PARTICLE_RENDER_BIT,
                                                  USAGE_SKYBOX_RENDER_BIT,
                                                  USAGE_GUI_RENDER_BIT,
                                                  USAGE_2D_RENDER_BIT,
                                                  USAGE_FLAT_RENDER_BIT
            };

            const char * const g_UsageMaskTypesText[] = {
                                                         FG_GFX_USAGE_EMPTY_TEXT,
                                                         FG_GFX_USAGE_FALLBACK_TEXT,
                                                         FG_GFX_USAGE_DEFAULT_TEXT,
                                                         FG_GFX_USAGE_LOW_QUALITY_TEXT,
                                                         FG_GFX_USAGE_MEDIUM_QUALITY_TEXT,
                                                         FG_GFX_USAGE_HIGH_QUALITY_TEXT,
                                                         FG_GFX_USAGE_VERTEX_LIGHTING_TEXT,
                                                         FG_GFX_USAGE_FRAGMENT_LIGHTING_TEXT,
                                                         FG_GFX_USAGE_FRAGMENT_LIGHTING_MUTLTIPLE_TEXT,
                                                         FG_GFX_USAGE_ENVIRONMENT_MAPPING_TEXT,
                                                         FG_GFX_USAGE_BUMP_MAPPING_TEXT,
                                                         FG_GFX_USAGE_MESH_SKINNING_TEXT,
                                                         FG_GFX_USAGE_MOTION_BLUR_TEXT,
                                                         FG_GFX_USAGE_ANTIALIASING_TEXT,
                                                         FG_GFX_USAGE_GAUSSIAN_BLUR_TEXT,
                                                         FG_GFX_USAGE_CARTOON_EFFECT_TEXT,
                                                         FG_GFX_USAGE_PARTICLE_RENDER_TEXT,
                                                         FG_GFX_USAGE_SKYBOX_RENDER_TEXT,
                                                         FG_GFX_USAGE_GUI_RENDER_TEXT,
                                                         FG_GFX_USAGE_2D_RENDER_TEXT,
                                                         FG_GFX_USAGE_FLAT_RENDER_TEXT
            };

        } // namespace shaders
    } // namespace gfx
} // namespace fg

using namespace fg;
//------------------------------------------------------------------------------

void gfx::shaders::splitVariableName(const char* input,
                                     char* outVariable,
                                     char* outMember,
                                     fgGFXint* subIndex) {
    if(!input)
        return;
    std::string inputStr = input;
    fgGFXint subIndexTmp;
    std::string outVariableStr, outMemberStr;
    splitVariableName(inputStr, outVariableStr, outMemberStr, subIndexTmp);
    if(subIndex)
        *subIndex = subIndexTmp;
    if(outVariable) {
        memcpy(outVariable, outVariableStr.c_str(), outVariableStr.length());
    }
    if(outMember) {
        memcpy(outMember, outMemberStr.c_str(), outMemberStr.length());
    }
}
//------------------------------------------------------------------------------

void gfx::shaders::splitVariableName(const std::string& input,
                                     std::string& outVariable,
                                     std::string& outMember,
                                     fgGFXint& subIndex) {
    CStringVector dotSplits;
    CStringVector vecSplits;
    strings::split(input, '.', dotSplits);
    // assuming only one dot
    if(dotSplits.size() > 1)
        outMember = dotSplits[1];
    else
        outMember.clear();
    strings::split(dotSplits[0], '[', vecSplits);
    outVariable.clear();
    outVariable.append(vecSplits[0]);
    if(vecSplits.size() > 1) {
        // has index
        std::string vec = strings::trim(vecSplits[1], "[]{}");
        subIndex = (unsigned int)std::atoi(vec.c_str());
    } else {
        subIndex = 0;
    }
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getShaderProgramConfigSuffix(void) {
    return FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX;
}
//------------------------------------------------------------------------------

unsigned int gfx::shaders::getUsageMaskCount(UsageMask mask) {
    unsigned int count = 0;
    if(mask == UsageMask::USAGE_EMPTY_BIT)
        return 0;
    const unsigned int n = sizeof (shaders::g_UsageMaskTypes) / sizeof (shaders::UsageMask);
    for(unsigned int i = 0; i < n; i++) {
        UsageMask andMask = g_UsageMaskTypes[i] & mask;
        if(g_UsageMaskTypes[i] == andMask) {
            count++;
        }
    }
    return count;
}
//------------------------------------------------------------------------------

gfx::shaders::UsageMask gfx::shaders::getUsageMaskFromText(const char* text) {
    if(!text)
        return UsageMask::USAGE_EMPTY_BIT;
    if(!text[0])
        return UsageMask::USAGE_EMPTY_BIT;
    return getUsageMaskFromText(std::string(text));
}
//------------------------------------------------------------------------------

gfx::shaders::UsageMask gfx::shaders::getUsageMaskFromText(const std::string& text) {
    if(text.empty())
        return UsageMask::USAGE_EMPTY_BIT;
    UsageMask mask = USAGE_EMPTY_BIT;
    CStringVector parts;
    strings::split(text, ',', parts);
    if(parts.size() == 1) {
        parts.clear();
        strings::split(text, '|', parts);
    }
    if(parts.size() == 1) {
        parts.clear();
        strings::split(text, ';', parts);
    }
    if(parts.size() == 1) {
        parts.clear();
        strings::split(text, ' ', parts);
    }
    const unsigned int n = parts.size();
    const unsigned int nUsages = sizeof (g_UsageMaskTypes) / sizeof (UsageMask);
    for(unsigned int i = 0; i < n; i++) {
        std::string usage = strings::trim(parts[i]);
        for(unsigned int usageId = 0; usageId < nUsages; usageId++) {
            if(strings::isEqual(g_UsageMaskTypesText[usageId], usage, FG_FALSE)) {
                mask |= g_UsageMaskTypes[usageId];
                break;
            }
        }
    }
    return mask;
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getTextFromUsageMask(UsageMask mask) {
    const unsigned int n = sizeof (shaders::g_UsageMaskTypes) / sizeof (shaders::UsageMask);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(shaders::g_UsageMaskTypes[i] == mask) {
            result = shaders::g_UsageMaskTypesText[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

void gfx::shaders::getTextFromUsageMask(UsageMask mask, std::string& text) {
    const unsigned int n = sizeof (shaders::g_UsageMaskTypes) / sizeof (shaders::UsageMask);
    text.clear();
    for(unsigned int i = 0; i < n; i++) {
        UsageMask andMask = g_UsageMaskTypes[i] & mask;
        if(shaders::g_UsageMaskTypes[i] == andMask) {
            text.append(g_UsageMaskTypesText[i]);
            text.append(",");
        }
    }
    if(text.length()) {
        text.erase(text.length() - 1); // remove the last separator
    }
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
    const unsigned int n = sizeof (g_SupportedShaderTypes) / sizeof (ShaderType);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(g_SupportedShaderTypes[i] == value) {
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
    if(text.empty())
        return UniformType::UNIFORM_INVALID;
    return getUniformTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

fgGFXenum gfx::shaders::getUniformDataTypeFromText(const char* text) {
    UniformType uniformType = getUniformTypeFromText(text);
    if(uniformType == UniformType::UNIFORM_INVALID)
        return 0;
    return getUniformDataTypeFromUniformType(uniformType);
}
//------------------------------------------------------------------------------

fgGFXenum gfx::shaders::getUniformDataTypeFromText(const std::string& text) {
    if(text.empty())
        return 0;
    return getUniformDataTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

fgGFXenum gfx::shaders::getUniformDataTypeFromUniformType(UniformType uniformType) {
    fgGFXenum result = 0;
    switch(uniformType) {
        case UNIFORM_INVALID:
            result = 0;
            break;
        case UNIFORM_MODEL_MATRIX:
        case UNIFORM_MODEL_VIEW_MATRIX:
        case UNIFORM_MVP_MATRIX:
            result = FG_GFX_FLOAT_MAT4;
            break;
        case UNIFORM_AMBIENT_MAP:
        case UNIFORM_SPECULAR_MAP:
        case UNIFORM_NORMAL_MAP:
        case UNIFORM_BUMP_MAP:
        case UNIFORM_PLAIN_TEXTURE:
            result = FG_GFX_SAMPLER_2D;
            break;

        case UNIFORM_CUBE_TEXTURE:
            result = FG_GFX_SAMPLER_CUBE;
            break;

        case UNIFORM_ENVIRONMENT_MAP:
            break;

        case UNIFORM_DIRECTIONAL_LIGHT:
            break;
        case UNIFORM_DIRECTIONAL_LIGHT_DIRECTION:
            result = FG_GFX_FLOAT_VEC3;
            break;

        case UNIFORM_DIRECTIONAL_LIGHT_AMBIENT:
        case UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE:
        case UNIFORM_DIRECTIONAL_LIGHT_SPECULAR:
            result = FG_GFX_FLOAT_VEC4;
            break;

        case UNIFORM_MATERIAL:
            break;

        case UNIFORM_MATERIAL_AMBIENT:
        case UNIFORM_MATERIAL_DIFFUSE:
        case UNIFORM_MATERIAL_SPECULAR:
            result = FG_GFX_FLOAT_VEC4;
            break;

        case UNIFORM_MATERIAL_SHININESS:
            result = FG_GFX_FLOAT;
            break;

        case UNIFORM_PHASE:
            result = FG_GFX_FLOAT;
            break;
        case UNIFORM_DELTA_TIME:
            result = FG_GFX_FLOAT;
            break;
        case UNIFORM_TIMESTAMP:
            break;
        case UNIFORM_CUSTOM_COLOR:
            result = FG_GFX_FLOAT_VEC4;
            break;
        case UNIFORM_ATTRIB_MASK:
            result = FG_GFX_FLOAT;
            break;
        case UNIFORM_USE_TEXTURE:
            result = FG_GFX_FLOAT;
            break;
        case UNIFORM_DRAW_SKYBOX:
            result = FG_GFX_FLOAT;
            break;

        case UNIFORM_BONE_MATRICES:
            // array of mat4 (not even close to optimal)
            result = FG_GFX_FLOAT_MAT4;
            break;

        case UNIFORM_BONE_DUAL_QUATERNIONS:
            // array of vec4
            result = FG_GFX_FLOAT_VEC4;
            break;
        case UNIFORM_CUSTOM:
            break;
        default:
            result = FG_GFX_FLOAT_VEC4;
            break;
    };
    return result;
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

gfx::shaders::UniformBlockType gfx::shaders::getUniformBlockTypeFromText(const char* text) {
    UniformBlockType result = shaders::UNIFORM_BLOCK_INVALID;
    if(!text)
        return result;
    if(!text[0])
        return result;
    const unsigned int n = sizeof (g_UniformBlockTypes) / sizeof (UniformBlockType);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(g_UniformBlockTypesText[i], text, FG_FALSE)) {
            result = g_UniformBlockTypes[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::shaders::UniformBlockType gfx::shaders::getUniformBlockTypeFromText(const std::string& text) {
    if(text.empty())
        return UniformBlockType::UNIFORM_BLOCK_INVALID;
    return getUniformBlockTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

const char* gfx::shaders::getTextFromUniformBlockType(UniformBlockType value) {
    const char* result = NULL;
    if(value == shaders::UNIFORM_BLOCK_INVALID)
        return result;
    const unsigned int n = sizeof (g_UniformBlockTypes) / sizeof (UniformBlockType);
    for(unsigned int i = 0; i < n; i++) {
        if(g_UniformBlockTypes[i] == value) {
            result = g_UniformBlockTypesText[i];
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
size(1),
stride(0),
precision(shaders::PRECISION_DEFAULT) { }
//------------------------------------------------------------------------------

gfx::SUniformBind::SUniformBind(const self_type& orig) {
    this->variableName.append(orig.variableName);
    this->location = orig.location;
    this->type = orig.type;
    this->dataType = orig.dataType;
    this->size = orig.size;
    this->stride = orig.stride;
    this->precision = orig.precision;
    this->nestedLocations.append(orig.nestedLocations);
}
//------------------------------------------------------------------------------

gfx::SUniformBind::SUniformBind(const char *_variableName,
                                shaders::UniformType _type) :
variableName(),
location(-1),
type(_type),
dataType(FG_GFX_FLOAT_VEC4),
size(1),
stride(0),
precision(shaders::PRECISION_DEFAULT) {
    if(_variableName)
        variableName = _variableName;
    this->dataType = shaders::getUniformDataTypeFromUniformType(this->type);

}
//------------------------------------------------------------------------------

gfx::SUniformBind::~SUniformBind() {
    variableName.clear();
}
//------------------------------------------------------------------------------

gfx::SUniformBlockBind::SUniformBlockBind() :
blockName(),
index(-1),
bindingIndex(-1),
type(shaders::UNIFORM_BLOCK_INVALID),
uniforms() { }
//------------------------------------------------------------------------------

gfx::SUniformBlockBind::SUniformBlockBind(const self_type& orig) {
    this->blockName.append(orig.blockName);
    this->index = orig.index;
    this->bindingIndex = orig.bindingIndex;
    this->type = orig.type;
    this->uniforms.append(orig.uniforms);
}
//------------------------------------------------------------------------------

gfx::SUniformBlockBind::SUniformBlockBind(const char *_blockName,
                                          shaders::UniformBlockType _type) :
blockName(_blockName),
index(-1),
bindingIndex(-1),
type(_type),
uniforms() {
    // should this type of constructor append standard uniforms based on
    // uniform block type? Is this is a place for this kind of stuff?
    // shaders::appendStandardUniformsToUniformBlock(this->type, this->uniforms);
}
//------------------------------------------------------------------------------

gfx::SUniformBlockBind::~SUniformBlockBind() {
    blockName.clear();
}
//------------------------------------------------------------------------------

int gfx::SUniformBlockBind::addUniformBind(const SUniformBind& uniformBind) {
    // this method will overwrite data
    int index = uniforms.find(uniformBind);
    if(index >= 0) {
        // found
        uniforms[index] = uniformBind;
    } else {
        // new
        uniforms.push_back(uniformBind);
        index = uniforms.size() - 1;
    }
    return index;
}
//------------------------------------------------------------------------------

fgBool gfx::SUniformBlockBind::hasUniform(const char* name) const {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    fgBool found = FG_FALSE;
    const unsigned int n = this->count();
    for(unsigned int i = 0; i < n; i++) {
        const SUniformBind& bind = uniforms[i];
        if(bind.variableName.compare(name) == 0) {
            found = FG_TRUE;
            break;
        }
    }
    return found;
}
//------------------------------------------------------------------------------

fgBool gfx::SUniformBlockBind::hasUniform(const std::string& name) const {
    if(name.empty())
        return FG_FALSE;
    return hasUniform(name.c_str());
}
//------------------------------------------------------------------------------

fgBool gfx::SUniformBlockBind::hasUniform(const SUniformBind& uniformBind) const {
    return (fgBool)uniforms.contains(uniformBind);
}
//------------------------------------------------------------------------------

fgBool gfx::SUniformBlockBind::isEmpty(void) const {
    return (fgBool)uniforms.empty();
}
//------------------------------------------------------------------------------

unsigned int gfx::SUniformBlockBind::count(void) const {
    return (unsigned int)uniforms.size();
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

fgBool gfx::shaders::appendStandardUniformsToUniformBlock(UniformBlockType blockType,
                                                          UniformBindVec& uniforms) {
    if(blockType == shaders::UNIFORM_BLOCK_INVALID) {
        return FG_FALSE;
    }
    SUniformBind bind;
    int index;
    UniformBindVec newUniforms;
    // this function wont clear this uniform vec
    if(blockType == shaders::UNIFORM_BLOCK_TRANSFORM) {
        bind.variableName = "modelMatrix";
        bind.dataType = FG_GFX_FLOAT_MAT4;
        bind.type = shaders::UNIFORM_MODEL_MATRIX;
        newUniforms.push_back(bind);

        bind.variableName = "mvMatrix";
        bind.dataType = FG_GFX_FLOAT_MAT4;
        bind.type = shaders::UNIFORM_MODEL_VIEW_MATRIX;
        newUniforms.push_back(bind);

        bind.variableName = "mvpMatrix";
        bind.dataType = FG_GFX_FLOAT_MAT4;
        bind.type = shaders::UNIFORM_MVP_MATRIX;
        newUniforms.push_back(bind);

        //bind.variableName = "scale";
        //bind.type = shaders::UNIFORM_SCALE;
        //newUniforms.append(bind);

        //bind.variableName = "mvpDQuat";
        //bind.type = shaders::UNIFORM_MVP_DQUAT
        //bind.size = 2;
        //bind.dataType = FG_GFX_FLOAT_VEC4;
    } else if(blockType == shaders::UNIFORM_BLOCK_LIGHTING_INFO) {
        bind.variableName = FG_GFX_DIRECTIONAL_LIGHT_DIRECTION_TEXT;
        //bind.size = 8; // maximum number of directional lights per scene
        //bind.dataType = ?;
        bind.dataType = FG_GFX_FLOAT_VEC3;
        bind.type = shaders::UNIFORM_DIRECTIONAL_LIGHT_DIRECTION;
        bind.size = 1;
        bind.stride = 0;
        //? better to define uniform block the same way the structure (one uniform)
        // need additional shader types
        newUniforms.push_back(bind);

        bind.variableName = FG_GFX_DIRECTIONAL_LIGHT_AMBIENT_TEXT;
        bind.dataType = FG_GFX_FLOAT_VEC4;
        bind.type = shaders::UNIFORM_DIRECTIONAL_LIGHT_AMBIENT;
        newUniforms.push_back(bind);

        bind.variableName = FG_GFX_DIRECTIONAL_LIGHT_DIFFUSE_TEXT;
        bind.dataType = FG_GFX_FLOAT_VEC4;
        bind.type = shaders::UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE;
        newUniforms.push_back(bind);

        bind.variableName = FG_GFX_DIRECTIONAL_LIGHT_SPECULAR_TEXT;
        bind.dataType = FG_GFX_FLOAT_VEC4;
        bind.type = shaders::UNIFORM_DIRECTIONAL_LIGHT_SPECULAR;
        newUniforms.push_back(bind);
    } else if(blockType == shaders::UNIFORM_BLOCK_MATERIAL_INFO) {
        bind.variableName = FG_GFX_MATERIAL_AMBIENT_TEXT;
        bind.dataType = FG_GFX_FLOAT_VEC4;
        bind.type = shaders::UNIFORM_MATERIAL_AMBIENT;
        bind.size = 1;
        bind.stride = 0;
        newUniforms.push_back(bind);

        bind.variableName = FG_GFX_MATERIAL_DIFFUSE_TEXT;
        bind.dataType = FG_GFX_FLOAT_VEC4;
        bind.type = shaders::UNIFORM_MATERIAL_DIFFUSE;
        newUniforms.push_back(bind);

        bind.variableName = FG_GFX_MATERIAL_SPECULAR_TEXT;
        bind.dataType = FG_GFX_FLOAT_VEC4;
        bind.type = shaders::UNIFORM_MATERIAL_SPECULAR;
        newUniforms.push_back(bind);

        bind.variableName = FG_GFX_MATERIAL_SHININESS_TEXT;
        bind.dataType = FG_GFX_FLOAT;
        bind.type = shaders::UNIFORM_MATERIAL_SHININESS;
        newUniforms.push_back(bind);
    }

    uniforms.append(newUniforms);
    return FG_TRUE;
}
//------------------------------------------------------------------------------
