/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxShaderConfig.h"
#include "GFX/fgGfxErrorCodes.h"
#include "fgMessageSubsystem.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"

#define FG_GFX_SHADER_CONFIG_PROGRAM_SECTION_NAME   "ShaderProgramConfig"
#define FG_GFX_SHADER_CONFIG_BASIC_SECTION_NAME     "ShaderConfig"

#define FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX         "program.ini"
#define FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX        "frag.shader.ini"
#define FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX          "vert.shader.ini"
#define FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX    "tesc.shader.ini"
#define FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX "tese.shader.ini"
#define FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX        "geom.shader.ini"
#define FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX         "comp.shader.ini"

#define FG_GFX_SHADER_CONFIG_STD_SUFFIX                 "shader.ini"

namespace fg {
    namespace gfx {
        const ShaderConfigType g_ShaderConfigTypes[] = {
                                                        SHADER_CONFIG_PROGRAM,
                                                        SHADER_CONFIG_FRAGMENT,
                                                        SHADER_CONFIG_VERTEX
#if defined FG_USING_OPENGL
            ,
                                                        SHADER_CONFIG_TESS_CONTROL,
                                                        SHADER_CONFIG_TESS_EVALUATION,
                                                        SHADER_CONFIG_GEOMETRY,
                                                        SHADER_CONFIG_COMPUTE
#endif
        };

        const char * const g_ShaderCfgAllSuffixes[] = {
                                                       FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX,
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
    } // namespace gfx 
} // namespace fg

using namespace fg;
//------------------------------------------------------------------------------

gfx::ShaderConfigType gfx::getShaderConfigTypeFromSuffix(const char* suffix) {
    ShaderConfigType result = SHADER_CONFIG_INVALID;
    if(!suffix)
        return result;
    if(!suffix[0])
        return result;
    const unsigned int n = sizeof (g_ShaderConfigTypes) / sizeof (ShaderConfigType);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(g_ShaderCfgAllSuffixes[i], suffix, FG_FALSE)) {
            // shader config suffix (frag.shader.ini/vert.shader.ini)
            result = g_ShaderConfigTypes[i];
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::ShaderConfigType gfx::getShaderConfigTypeFromSuffix(const std::string& suffix) {
    return getShaderConfigTypeFromSuffix(suffix.c_str());
}
//------------------------------------------------------------------------------

gfx::CShaderConfig::CShaderConfig() :
m_configType(SHADER_CONFIG_INVALID),
m_shaderTypes(),
m_uniformBinds(),
m_attributeBinds(),
m_includes(),
m_files(),
m_qualities(),
m_constants(),
m_selectedConfigName(),
m_programName(),
m_shaderName(),
m_usageMask(shaders::USAGE_EMPTY_BIT),
m_preferredSLVersion(FG_GFX_SHADING_LANGUAGE_INVALID),
m_defaultPrecision(shaders::SHADER_PRECISION_DEFAULT) { }
//------------------------------------------------------------------------------

gfx::CShaderConfig::CShaderConfig(const char *filePath) : self_type() {
    gfx::CShaderConfig::load(filePath);
}
//------------------------------------------------------------------------------

gfx::CShaderConfig::~CShaderConfig() {
    clearAll();
}
//------------------------------------------------------------------------------

void gfx::CShaderConfig::clearAll(void) {
    base_type::clearAll();
    m_selectedConfigName.clear();
    m_programName.clear();
    m_preferredSLVersion = FG_GFX_SHADING_LANGUAGE_INVALID;
    m_configType = SHADER_CONFIG_INVALID;
    m_defaultPrecision = shaders::SHADER_PRECISION_DEFAULT;
    m_shaderTypes.clear_optimised();
    m_uniformBinds.clear_optimised();
    m_attributeBinds.clear_optimised();
    m_includes.clear_optimised();
    m_files.clear_optimised();
    m_qualities.clear_optimised();
    m_constants.clear_optimised();
    m_usageMask = shaders::USAGE_EMPTY_BIT;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderConfig::load(const char *filePath, ShadingLangVersion SLver) {
    gfx::CShaderConfig::clearAll();
    if(!base_type::load(filePath)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_FAIL_CFG_LOAD);
        return FG_FALSE;
    }
    return private_parseData(SLver);
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderConfig::private_parseDefines(util::SCfgSection *definesSection) {
    if(!definesSection)
        return FG_FALSE;
    unsigned short n = 0;
    util::config::ParameterVecItor paramsBegin, paramsEnd, paramsItor;
    // This section is optional
    paramsBegin = definesSection->parameters.begin();
    paramsEnd = definesSection->parameters.end();
    paramsItor = paramsBegin;
    for(; paramsItor != paramsEnd; paramsItor++) {
        util::SCfgParameter *param = *paramsItor;
        if(!param) continue;
        // for now only BOOL is supported
        if(param->type == util::SCfgParameter::BOOL && !param->name.empty()) {
            SShaderConstantDef constant;
            constant.name = param->name;
            constant.value = param->bool_val;
            m_constants.push_back(constant);
            n++;
        }
    }
    if(!n)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderConfig::private_parseInclude(util::SCfgSection *includeSection) {
    if(!includeSection)
        return FG_FALSE;
    unsigned short n = 0;
    util::SCfgParameter *param = includeSection->getParameter("list", util::SCfgParameter::STRING);
    if(!param) return FG_FALSE;
    CVector<std::string> incVec;
    std::string tmp = param->string;
    strings::split(tmp, ',', incVec);
    for(int i = 0; i < (int)incVec.size(); i++) {
        m_includes.push_back(incVec[i]);
        n++;
    }
    if(!n)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderConfig::private_parseData(ShadingLangVersion SLver) {
    if(SLver != FG_GFX_SHADING_LANGUAGE_INVALID) {
        m_preferredSLVersion = SLver;
    } else if(m_preferredSLVersion == FG_GFX_SHADING_LANGUAGE_INVALID) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_INVALID_SLVER);
        return FG_FALSE;
    }
    if(m_configPath.empty()) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_WRONG_PATH);
        return FG_FALSE;
    }

    const char *ext = path::fileExt(m_configPath.c_str(), FG_TRUE);
    if(!ext) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_WRONG_PATH);
        return FG_FALSE;
    }
    std::string filePathNoExt = m_configPath.substr(0, m_configPath.length() - 1 - strlen(ext));

    m_configType = getShaderConfigTypeFromSuffix(ext);
    if(m_configType == SHADER_CONFIG_INVALID) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_CFG_TYPE);
        return FG_FALSE;
    }

    util::SCfgSection *mainSection = NULL;
    if(m_configType == SHADER_CONFIG_PROGRAM) {
        mainSection = getSection(FG_GFX_SHADER_CONFIG_PROGRAM_SECTION_NAME);
    } else {
        mainSection = getSection(FG_GFX_SHADER_CONFIG_BASIC_SECTION_NAME);
    }

    if(!mainSection) {
        // No new section found, the ini config is malformed
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_MAIN_SECTION);
        return FG_FALSE;
    }
    {
        util::SCfgParameter *param = mainSection->getParameter("precision", util::SCfgParameter::STRING);
        if(param) {
            m_defaultPrecision = shaders::getShaderPrecisionFromText(param->string);
        }
    }

    char slVerSubSectionName[64];
    char _tmpStr[24];
    if(m_preferredSLVersion == FG_GFX_ESSL_100 || m_preferredSLVersion == FG_GFX_ESSL_300)
        strcpy(_tmpStr, "ESSL");
    else
        strcpy(_tmpStr, "GLSL");
    snprintf(slVerSubSectionName, 64, "Shader.Version.%s.%d", _tmpStr, (int)m_preferredSLVersion);
    // Check if the shader supports that shading language
    util::SCfgSection *slVersionSection = getSection(slVerSubSectionName);
    if(!slVersionSection) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NOT_SUPPORTED_SLVER, "path[%s]", m_configPath.c_str());
        return FG_FALSE;
    } else if(!slVersionSection->parametersMap.size()) {
        // there is such section but it does not provide the name of the valid configuration
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_PARAM);
        return FG_FALSE;
    }
    // Get the name of the configuration based on shading language version
    {
        util::SCfgParameter *param = slVersionSection->getParameter("configuration", util::SCfgParameter::STRING);
        if(!param) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_PARAM);
            return FG_FALSE;
        }
        m_selectedConfigName = param->string;
    }
    // Now populate list of defines (constant values / bool only)
    // Shader.Defines holds list of constants for all configurations (shading language version)
    // and all shader types (shader objects to link with shader program)
    util::SCfgSection *definesSection = getSection("Shader.Defines");
    private_parseDefines(definesSection);
    // Populate list of constants for selected configuration,
    // like before this section is optional
    {
        std::string _tmp = "Shader.Defines.";
        _tmp.append(m_selectedConfigName);
        definesSection = getSection(_tmp);
        private_parseDefines(definesSection);
    }
    {
        // parse usage flags
        util::SCfgParameter* param = mainSection->getParameter("usage", util::SCfgParameter::STRING);
        if(param) {
            m_usageMask |= shaders::getUsageMaskFromText(param->string);
        }
    }
    //
    // Parse more wide parameters from specific shader configuration (not program config)
    //
    if(m_configType != SHADER_CONFIG_PROGRAM) {
        util::SCfgParameter *param = mainSection->getParameter("shaderType", util::SCfgParameter::STRING);
        if(!param) {
            // no shader type specified - it has to be explicitly stated in config
            // even if the file extension points to shader type
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_TYPE);
            return FG_FALSE;
        }
        shaders::ShaderType _shadertype = shaders::getShaderTypeFromText(param->string);
        if(_shadertype == shaders::SHADER_INVALID) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_TYPE);
            return FG_FALSE;
        }

        m_shaderTypes.push_back(_shadertype);
        const char *shortPrefix = shaders::getShaderShortPrefix(_shadertype);

        // Find shader name (name-tag, used in handle/data manager)
        param = mainSection->getParameter("shaderName", util::SCfgParameter::STRING);
        if(param) {
            // found shader name
            m_shaderName.clear();
            m_shaderName.append(param->string);
        } else {
            // no shader name specified
            // will add it automatically
            m_shaderName.clear();
            m_shaderName.append(path::fileName(filePathNoExt.c_str())).append(".");
            m_shaderName.append(shaders::getTextFromShaderType(_shadertype));
        }

        // Parse defines
        std::string _tmp;
        _tmp.append(shortPrefix).append(".Defines");
        private_parseDefines(getSection(_tmp));
        _tmp.clear();
        _tmp.append(shortPrefix).append(".Defines.").append(m_selectedConfigName);
        private_parseDefines(getSection(_tmp));
        _tmp.clear();

        // parse includes
        _tmp.append(shortPrefix).append(".Include");
        private_parseInclude(getSection(_tmp));
        _tmp.clear();

        // Parse file / quality configuration specific for this shader
        // This depends on the selected configuration (sub config) based on
        // shading language version
        _tmp.append(shortPrefix).append(".Config.").append(m_selectedConfigName);
        util::SCfgSection *cfgSpecSection = getSection(_tmp);
        _tmp.clear();
        if(!cfgSpecSection) {
            // This is bad - specific config with file/quality list was not found
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_FILE_SECTION);
            return FG_FALSE;
        }
        CVector<std::string> _helperVec;
        fgBool foundQuality = FG_FALSE, foundFile = FG_FALSE;
        if((param = cfgSpecSection->getParameter("quality", util::SCfgParameter::STRING)) != NULL) {
            std::string _q_vec = param->string;
            strings::split(_q_vec, ',', _helperVec);
            m_qualities.clear_optimised();
            for(int i = 0; i < (int)_helperVec.size(); i++) {
                m_qualities.push_back(getQualityFromText(_helperVec[i].c_str()));
            }
            if(!m_qualities.empty()) {
                foundQuality = FG_TRUE;
            }
            _q_vec.clear();
            _helperVec.clear_optimised();
        }
        if((param = cfgSpecSection->getParameter("file", util::SCfgParameter::STRING)) != NULL) {
            std::string _f_vec = param->string;
            strings::split(_f_vec, ',', _helperVec);
            m_files.clear_optimised();
            for(int i = 0; i < (int)_helperVec.size(); i++) {
                m_files.push_back(_helperVec[i]);
            }
            if(!m_files.empty()) {
                foundFile = FG_TRUE;
            }
            _f_vec.clear();
            _helperVec.clear_optimised();
        }
        if(!foundFile || !foundQuality) {
            // Did not find parameters for quality or file
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_FILEQ_PARAMS);
            return FG_FALSE;
        }
        //
        // Loading attributes
        //
        if(_shadertype == shaders::SHADER_VERTEX) {
            // checking for attributes only for vertex shader 
            // (attributes in fragment shader are not allowed / needed)
            util::config::SectionVec _attributes;
            _tmp.append(shortPrefix).append(".").append("Attribute.");
            getSectionsWith(_attributes, _tmp.c_str());
            if(_attributes.empty()) {
                // error - attributes are required - minimum one
                FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_ATTRIBUTES);
                return FG_FALSE;
            }
            // !! data type for attribute (GL) possible values:
            // float, vec2, vec3, vec4, mat2, mat3, and mat4.
            unsigned short _nmax = (unsigned short)_attributes.size(), i;
            for(i = 0; i < _nmax; i++) {
                SAttributeBind _bind;
                _bind.type = getAttributeTypeFromText(_attributes[i]->subName.c_str());
                if(_bind.type == ATTRIBUTE_INVALID) {
                    FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_ATTRIBUTE);
                    continue;
                }
                // This will also set the proper location and data type
                _bind.setType(_bind.type);
                util::SCfgParameter *_aname = NULL, *_aprecision = NULL;
                _aname = _attributes[i]->getParameter("attributeName", util::SCfgParameter::STRING);
                _aprecision = _attributes[i]->getParameter("precision", util::SCfgParameter::STRING);
                if(!_aname) {
                    // This attribute definition section is malformed
                    FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_ATTRIBUTE);
                    continue;
                }
                _bind.precision = shaders::PRECISION_DEFAULT;
                if(_aprecision) {
                    _bind.precision = shaders::getPrecisionFromText(_aprecision->string);
                }
                _bind.variableName = _aname->string;
                //_bind.dataType = FG_GFX_DATA_TYPE_FROM_TEXT(_aDataType->string);
                m_attributeBinds.push_back(_bind);
            }
        }
        // Loading uniforms
        //
        // checking for attributes only for vertex shader 
        // (attributes in fragment shader are not allowed / needed)
        util::config::SectionVec _uniforms;
        _tmp.clear();
        _tmp.append(shortPrefix).append(".").append("Uniform.");
        getSectionsWith(_uniforms, _tmp.c_str());
        if(_uniforms.empty()) {
            // uniforms are not required...
        }
        unsigned short _nmax = (unsigned short)_uniforms.size(), i;
        for(i = 0; i < _nmax; i++) {
            SUniformBind _bind;
            _bind.type = shaders::getUniformTypeFromText(_uniforms[i]->subName.c_str());
            if(_bind.type == shaders::UNIFORM_INVALID) {
                // Not a valid / supported uniform type - can ignore it ? Pass empty data to it?
                // #FIXME
                FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_UNIFORM, "name=[%s]", _uniforms[i]->subName.c_str());
                continue;
            }
            util::SCfgParameter *_uname = NULL, *_uprecision = NULL;
            _uname = _uniforms[i]->getParameter("uniformName", util::SCfgParameter::STRING);
            //_uDataType = _uniforms[i]->getParameter("type", FG_CFG_PARAMETER_STRING);
            _uprecision = _uniforms[i]->getParameter("precision", util::SCfgParameter::STRING);
            if(!_uname) {
                // This uniform definition section is malformed
                FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_UNIFORM, "name=[%s]", _uniforms[i]->subName.c_str());
                continue;
            }
            _bind.precision = shaders::PRECISION_DEFAULT;
            if(_uprecision) {
                _bind.precision = shaders::getPrecisionFromText(_uprecision->string);
            }
            _bind.variableName = _uname->string;
            //_bind.dataType = FG_GFX_DATA_TYPE_FROM_TEXT(_uDataType->string);
            m_uniformBinds.push_back(_bind);
        }
    }
    // specific configuration procedures for main shader config (shader program)
    if(m_configType == SHADER_CONFIG_PROGRAM) {
        util::SCfgParameter *param = NULL;
        param = mainSection->getParameter("programName", util::SCfgParameter::STRING);
        if(!param) {
            // this is a big error, the program name (string handle ID) is not specified
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_PROG_NAME);
            return FG_FALSE;
        }
        m_programName = param->string;
        // for various runtime / etc info on GFX subsystem (no of shader types supported ?)
        int nmax = shaders::NUM_SHADER_TYPES;
        // Get file config names and types attached to this shader program
        for(int i = 0; i < nmax; i++) {
            fgBool _found = FG_FALSE;
            std::string qstr = "has";
            qstr.append(shaders::g_SupportedShaderTypesText[i]);
            param = mainSection->getParameter(qstr, util::SCfgParameter::BOOL);
            if(param) {
                if(param->bool_val == FG_TRUE) {
                    m_shaderTypes.push_back(shaders::g_SupportedShaderTypes[i]);
                    _found = FG_TRUE;
                }
            }
            qstr = qstr.substr(3);

            param = mainSection->getParameter(qstr, util::SCfgParameter::STRING);
            if(param) {
                if(param->string[0]) {
                    std::string newShaderPath;
                    newShaderPath.append(path::dirName(filePathNoExt));
                    if(newShaderPath[newShaderPath.length() - 1] != path::DELIMITER_CHAR)
                        newShaderPath.append(path::DELIMITER);
                    newShaderPath.append(param->string);
                    m_files.push_back(newShaderPath); // joined path
                    if(!_found) {
                        m_shaderTypes.push_back(shaders::g_SupportedShaderTypes[i]);
                    }
                }
            }
            // need to check file names and shadertypes vector
            // if for example hasVertexShader is true
            // but it's file path (config) is not in the array
            // the name will be chosen automatically
            // based on a program name
            if(!param && _found) {
                // the file path was not found
                // need to add it manually
                std::string newShaderPath;
                // automatic name, use shader program config name
                // and add config extension based on shader type
                newShaderPath.append(filePathNoExt).
                        append(".").
                        append(shaders::getShaderConfigSuffix(shaders::g_SupportedShaderTypes[i]));

                m_files.push_back(newShaderPath);
            }
        }

        // Check for valid number of shaders to bind into one shader program #FIXME
        if(m_shaderTypes.size() == 2 && 0) {
            // #TODO
        }
    } else if(m_configType == SHADER_CONFIG_FRAGMENT) {
        // specific configuration for fragment shader (pixel shader)
    } else if(m_configType == SHADER_CONFIG_VERTEX) {
        // configuration for vertex shader
#if defined(FG_USING_OPENGL)
    } else if(m_configType == SHADER_CONFIG_TESS_CONTROL) {
        // configuration for tessellation control shader
    } else if(m_configType == SHADER_CONFIG_TESS_EVALUATION) {
        // configuration for tessellation evaluation shader
    } else if(m_configType == SHADER_CONFIG_GEOMETRY) {
        // configuration for geometry shader
    } else if(m_configType == SHADER_CONFIG_COMPUTE) {
        // specific configuration procedures for compute shader
#endif
    }
    FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "GFX: Shader config loaded successfully: '%s'", fg::path::fileName(m_configPath.c_str()));
    if(m_configType == SHADER_CONFIG_PROGRAM) {
        FG_LOG_DEBUG("GFX: Shader config for program loaded; name[%s], file[%s]", m_programName.c_str(), fg::path::fileName(m_configPath.c_str()));
    } else {
        FG_LOG_DEBUG("GFX: Shader config loaded: file[%s]", fg::path::fileName(m_configPath.c_str()));
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------
