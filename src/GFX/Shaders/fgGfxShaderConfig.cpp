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

using namespace fg;

//------------------------------------------------------------------------------

gfx::CShaderConfig::CShaderConfig() :
m_configType(FG_GFX_SHADER_CONFIG_INVALID),
m_preferredSLVersion(FG_GFX_SHADING_LANGUAGE_INVALID),
m_defaultPrecision(FG_GFX_SHADER_PRECISION_DEFAULT) { }
//------------------------------------------------------------------------------

gfx::CShaderConfig::CShaderConfig(const char *filePath) {
    gfx::CShaderConfig::load(filePath);
}
//------------------------------------------------------------------------------

gfx::CShaderConfig::~CShaderConfig() {
    clearAll();
}
//------------------------------------------------------------------------------

void gfx::CShaderConfig::clearAll(void) {
    CConfig::clearAll();
    m_selectedConfigName.clear();
    m_programName.clear();
    m_preferredSLVersion = FG_GFX_SHADING_LANGUAGE_INVALID;
    m_configType = FG_GFX_SHADER_CONFIG_INVALID;
    m_defaultPrecision = FG_GFX_SHADER_PRECISION_DEFAULT;
    m_shaderTypes.clear_optimised();
    m_uniformBinds.clear_optimised();
    m_attributeBinds.clear_optimised();
    m_includes.clear_optimised();
    m_files.clear_optimised();
    m_qualities.clear_optimised();
    m_constants.clear_optimised();
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderConfig::load(const char *filePath, ShadingLangVersion SLver) {
    gfx::CShaderConfig::clearAll();
    if(!CConfig::load(filePath)) {
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

    m_configType = FG_GFX_SHADER_CONFIG_INVALID;
    if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX) == 0) {
        m_configType = FG_GFX_SHADER_CONFIG_PROGRAM;
    } else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX) == 0) {
        m_configType = FG_GFX_SHADER_CONFIG_FRAGMENT;
    } else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX) == 0) {
        m_configType = FG_GFX_SHADER_CONFIG_VERTEX;
#if defined FG_USING_OPENGL
    } else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX) == 0) {
        m_configType = FG_GFX_SHADER_CONFIG_TESS_CONTROL;
    } else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX) == 0) {
        m_configType = FG_GFX_SHADER_CONFIG_TESS_EVALUATION;
    } else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX) == 0) {
        m_configType = FG_GFX_SHADER_CONFIG_VERTEX;
    } else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX) == 0) {
        m_configType = FG_GFX_SHADER_CONFIG_VERTEX;
#endif
    }

    if(m_configType == FG_GFX_SHADER_CONFIG_INVALID) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_CFG_TYPE);
        return FG_FALSE;
    }

    util::SCfgSection *mainSection = NULL;
    if(m_configType == FG_GFX_SHADER_CONFIG_PROGRAM) {
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
            m_defaultPrecision = (ShaderPrecision)FG_GFX_PRECISION_FROM_TEXT(param->string);
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
    //
    // Parse more wide parameters from specific shader configuration (not program config)
    //
    if(m_configType != FG_GFX_SHADER_CONFIG_PROGRAM) {
        util::SCfgParameter *param = mainSection->getParameter("shaderType", util::SCfgParameter::STRING);
        if(!param) {
            // no shader type specified - it has to be explicitly stated in config
            // even if the file extension points to shader type
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_TYPE);
            return FG_FALSE;
        }
        ShaderType _shadertype = FG_GFX_SHADER_TYPE_FROM_TEXT(param->string);
        if(_shadertype == ShaderType::FG_GFX_SHADER_INVALID) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_TYPE);
            return FG_FALSE;
        }
        m_shaderTypes.push_back(_shadertype);
        const char *shortPrefix = FG_GFX_SHADER_SHORT_PREFIX(_shadertype);

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
        if(_shadertype == ShaderType::FG_GFX_SHADER_VERTEX) {
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
                _bind.type = FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(_attributes[i]->subName.c_str());
                if(_bind.type == FG_GFX_ATTRIBUTE_INVALID) {
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
                _bind.precision = FG_GFX_PRECISION_DEFAULT;
                if(_aprecision) {
                    _bind.precision = FG_GFX_PRECISION_FROM_TEXT(_aprecision->string);
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
            _bind.type = FG_GFX_UNIFORM_TYPE_FROM_TEXT(_uniforms[i]->subName.c_str());
            if(_bind.type == FG_GFX_UNIFORM_INVALID) {
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
            _bind.precision = FG_GFX_PRECISION_DEFAULT;
            if(_uprecision) {
                _bind.precision = FG_GFX_PRECISION_FROM_TEXT(_uprecision->string);
            }
            _bind.variableName = _uname->string;
            //_bind.dataType = FG_GFX_DATA_TYPE_FROM_TEXT(_uDataType->string);
            m_uniformBinds.push_back(_bind);
        }
    }
    // specific configuration procedures for main shader config (shader program)
    if(m_configType == FG_GFX_SHADER_CONFIG_PROGRAM) {
        util::SCfgParameter *param = NULL;
        param = mainSection->getParameter("programName", util::SCfgParameter::STRING);
        if(!param) {
            // this is kinda big error, the program name (string handle ID) is not specified
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_NO_PROG_NAME);
            return FG_FALSE;
        }
        m_programName = param->string;
        int nmax = 0;
        if(FG_BUILD_CONFIG.usingOpenGLES)
            nmax = 2;
        else if(FG_BUILD_CONFIG.usingOpenGL)
            nmax = 6; // #FIXME - need global GFX config array (like with build config)
        // for various runtime / etc info on GFX subsystem (no of shader types supported ?)
        if(nmax > (int)sizeof (g_fgGfxSupportedShaderTypes) / (int)sizeof (g_fgGfxSupportedShaderTypes[0]))
            nmax = (int)sizeof (g_fgGfxSupportedShaderTypes) / (int)sizeof (g_fgGfxSupportedShaderTypes[0]); // #FIXME - ugly...
        for(int i = 0; i < nmax; i++) {
            std::string qstr = "has";
            qstr.append(g_fgGfxSupportedShaderTypesText[i]);
            param = mainSection->getParameter(qstr, util::SCfgParameter::BOOL);
            if(param) {
                if(param->bool_val == FG_TRUE) {
                    m_shaderTypes.push_back(g_fgGfxSupportedShaderTypes[i]);
                }
            }
        }
        // Check for valid number of shaders to bind into one shader program #FIXME
        if(m_shaderTypes.size() == 2 && 0) {
            // #TODO
        }
    } else if(m_configType == FG_GFX_SHADER_CONFIG_FRAGMENT) {
        // specific configuration for fragment shader (pixel shader)
    } else if(m_configType == FG_GFX_SHADER_CONFIG_VERTEX) {
        // configuration for vertex shader
#if defined FG_USING_OPENGL
    } else if(m_configType == FG_GFX_SHADER_CONFIG_TESS_CONTROL) {
        // configuration for tessellation control shader
    } else if(m_configType == FG_GFX_SHADER_CONFIG_TESS_EVALUATION) {
        // configuration for tessellation evaluation shader
    } else if(m_configType == FG_GFX_SHADER_CONFIG_GEOMETRY) {
        // configuration for geometry shader
    } else if(m_configType == FG_GFX_SHADER_CONFIG_COMPUTE) {
        // specific configuration procedures for compute shader
#endif
    }
    FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "GFX: Shader config loaded successfully: '%s'", fg::path::fileName(m_configPath.c_str()));
    if(m_configType == FG_GFX_SHADER_CONFIG_PROGRAM) {
        FG_LOG_DEBUG("GFX: Shader config for program loaded; name[%s], file[%s]", m_programName.c_str(), fg::path::fileName(m_configPath.c_str()));
    } else {
        FG_LOG_DEBUG("GFX: Shader config loaded: file[%s]", fg::path::fileName(m_configPath.c_str()));
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------
