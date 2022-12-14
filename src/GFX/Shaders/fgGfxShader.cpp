/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxShader.h"
#include "GFX/fgGfxErrorCodes.h"
#include "Util/fgMemory.h"
#include "fgMessageSubsystem.h"
#include "fgDebugConfig.h"

using namespace fg;
//------------------------------------------------------------------------------

const char* gfx::CShader::s_includeSources[gfx::CShader::INCLUDE_COUNT] = {
                                                                           "struct SMaterial {\nvec4 ambient;\nvec4 diffuse;\nfloat shininess;\nvec4 specular;\n};\n",
                                                                           "struct SLight {\nvec4 ambient;\nvec4 diffuse;\nvec4 specular;\n};\n",
                                                                           "struct SDirectionalLight {\n/*vec3 halfPlane;*/\nvec4 ambient;\nvec4 diffuse;\nvec3 direction;\nvec4 specular;\n};\n"
};

gfx::CShader::CShader(shaders::ShaderType type) :
m_type(type),
m_version(FG_GFX_SHADING_LANGUAGE_INVALID),
m_numSources(0),
m_sourceSize(0),
m_sources(NULL),
m_fileSource(NULL),
m_precision(shaders::SHADER_PRECISION_DEFAULT),
m_isSourceLoaded(FG_FALSE) {
    if(m_type == shaders::SHADER_INVALID)
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_WRONG_TYPE);
    m_params[FG_GFX_SHADER_TYPE] = (int)m_type;
    m_params[FG_GFX_SHADER_DELETE_STATUS] = 0;
    m_params[FG_GFX_SHADER_COMPILE_STATUS] = 0;
    m_params[FG_GFX_SHADER_INFO_LOG_LENGTH] = 0;
    m_params[FG_GFX_SHADER_SOURCE_LENGTH] = 0;
    m_baseType = BASE_TYPE_SHADER;
}
//------------------------------------------------------------------------------

gfx::CShader::~CShader() {
    gfx::CShader::clearAll();
}
//------------------------------------------------------------------------------

void gfx::CShader::clearAll(void) {
    freeSource();
    m_defineStrVec.clear_optimised();
    m_includeStrVec.clear_optimised();
    m_params.clear();
    deleteShader();
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::setVersion(ShadingLangVersion slVer) {
    if(slVer != FG_GFX_SHADING_LANGUAGE_INVALID)
        m_version = slVer;
    else
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CShader::appendDefine(SShaderConstantDef constantDef) {
    std::string defStr;
    constantDef.toString(defStr);
    defStr.append("\n");
    m_defineStrVec.push_back(defStr);
}
//------------------------------------------------------------------------------

void gfx::CShader::appendInclude(std::string & includeName) {
    if(!includeName.empty())
        m_includeStrVec.push_back(includeName);
}
//------------------------------------------------------------------------------

// #FIXME
#define _FG_GFX_SL_VERSION_ES_100 "#version 100 es\n"
#define _FG_GFX_SL_VERSION_EMPTY "\n"

fgBool gfx::CShader::loadSource(void) {
    if(getFilePath().empty()) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_WRONG_PATH, "path[%s]", getFilePathStr());
        return FG_FALSE;
    }
    if(m_version == FG_GFX_SHADING_LANGUAGE_INVALID) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_GFX_SHADER_INVALID_SLVER);
        return FG_FALSE;
    }
    // do not reload the source (will need to attach again the rest of the defines / sources)
    if(m_isSourceLoaded || m_sources) {
        FG_LOG_DEBUG("GFX:Shader: Shader source is already loaded: '%s'", getFilePathStr());
        return FG_TRUE;
    }

    if(!m_fileSource) {
        m_fileSource = util::DataFile::load();
    }
    if(!m_fileSource) {
        FG_LOG_ERROR("GFX:Shader: Unable to load shader source: '%s'", getFilePathStr());
        return FG_FALSE; // PROPER ERROR CODE
    }

    m_numSources = (int)m_includeStrVec.size() + m_defineStrVec.size() + 2;
    m_sources = (char const **)fgMalloc<char *>(m_numSources);
    if(!m_sources) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_ENOMEM);
        return FG_FALSE;
    }

    if(m_version == FG_GFX_ESSL_100) {
        m_sources[0] = _FG_GFX_SL_VERSION_EMPTY;
    } else {
        m_sources[0] = _FG_GFX_SL_VERSION_EMPTY;
    }

    //m_sources[0] = _version.c_str();
    int n = 1;
    // include constant definitions (#define) into the shader source
    for(int i = 0; i < (int)m_defineStrVec.size(); i++, n++) {
        m_sources[n] = m_defineStrVec[i].c_str();
    }
    // append additional includes (these are structure definitions)
    for(int i = 0; i < (int)m_includeStrVec.size(); i++, n++) {
        //m_sources[n] = "\n"; // #FIXME
        const std::string& includeName = m_includeStrVec.at(i);
        if(includeName.compare("fgGfxMaterial") == 0) {
            m_sources[n] = s_includeSources[INCLUDE_MATERIAL];
        } else if(includeName.compare("fgGfxLight") == 0) {
            m_sources[n] = s_includeSources[INCLUDE_LIGHT];
        } else if(includeName.compare("fgGfxDirectionalLight") == 0) {
            m_sources[n] = s_includeSources[INCLUDE_DIRECTIONAL_LIGHT];
        } else {
            m_sources[n] = "\n\0";
        }
    }
    m_sources[n] = m_fileSource;
#if defined(FG_DEBUG)
    if(g_DebugConfig.gfxDumpShaders) {
        FG_LOG_DEBUG("GFX: Shader '%s' source code:\n", this->getNameStr());
        for(int i = 0; i < (int)m_numSources; i++) {
            // Dump sources
            FG_LOG_DEBUG("[%d] '%s'", i, m_sources[i]);
        }
    }
#endif
    m_isSourceLoaded = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::loadSource(const char *path) {
    setFilePath(path);
    util::DataFile::setPath(path);
    return loadSource();
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::loadSource(std::string & path) {
    setFilePath(path);
    util::DataFile::setPath(path);
    return loadSource();
}
//------------------------------------------------------------------------------

void gfx::CShader::freeSource(void) {
    if(m_fileSource)
        fgFree(m_fileSource);
    m_fileSource = NULL;
    if(m_sources)
        fgFree(m_sources);
    m_sources = NULL;
    m_isSourceLoaded = FG_FALSE;
    m_numSources = 0;
}
//------------------------------------------------------------------------------

fgGFXuint gfx::CShader::create(void) {
    if(m_type == shaders::SHADER_INVALID)
        return 0;
    if(!m_gfxID || (glIsShader(m_gfxID) == FG_GFX_FALSE)) {
        m_gfxID = glCreateShader((fgGFXenum)m_type);
        GLCheckError("glCreateShader");
        FG_LOG_DEBUG("GFX: Created shader: %s, gfxID: %d [is shader? = %d]", getTextFromShaderType(m_type), m_gfxID, (int)glIsShader(m_gfxID));
    }
    return m_gfxID;
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::compile(void) {
    if(!m_isSourceLoaded) {
        if(!loadSource()) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_EIO, "GFX: Failed to load shader source file.");
            // Failed to load shader source
            return FG_FALSE;
        }
    }
    if(m_gfxID && glIsShader(m_gfxID)) {
        return FG_TRUE; // no recompilation
    }
    if(!create()) {
        // Failed to create shader
        FG_LOG_ERROR("GFX: Failed to create shader '%s'", getNameStr());
        return FG_FALSE;
    }
    glShaderSource(m_gfxID, m_numSources, m_sources, NULL);
    GLCheckError("glShaderSource");
    glCompileShader(m_gfxID);
    GLCheckError("glCompileShader");
    updateLog();
    updateParams();
    if(!m_params[FG_GFX_SHADER_COMPILE_STATUS]) {
        FG_LOG_ERROR("GFX: compilation failed -  %s", getFilePath().c_str());
    } else {
        FG_LOG_DEBUG("GFX: Successfully compiled shader: '%s', type: '%s'", getFilePathStr(), getTextFromShaderType(m_type));
    }
    return (fgBool)m_params[FG_GFX_SHADER_COMPILE_STATUS];
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::compile(const char *path) {
    if(m_isSourceLoaded || m_fileSource) {
        return FG_FALSE;
    }
    setFilePath(path);
    util::DataFile::setPath(path);
    return compile();
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::compile(std::string & path) {
    if(m_isSourceLoaded || m_fileSource) {
        return FG_FALSE;
    }
    setFilePath(path);
    util::DataFile::setPath(path);
    return compile();
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::deleteShader(void) {
    if(glIsShader(m_gfxID) == FG_GFX_TRUE) {
        glDeleteShader(m_gfxID);
        GLCheckError("glDeleteShader");
        updateParams();
        m_gfxID = 0;
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::attach(fgGFXuint program) {
    if((FG_GFX_TRUE == glIsProgram(program)) && (FG_GFX_TRUE == glIsShader(m_gfxID))) {
        glAttachShader(program, m_gfxID);
        GLCheckError("glAttachShader");
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShader::detach(fgGFXuint program) {
    if((glIsProgram(program) == FG_GFX_TRUE) && (glIsShader(m_gfxID) == FG_GFX_TRUE)) {
        glDetachShader(program, m_gfxID);
        GLCheckError("glDetachShader");
        return FG_TRUE;
    }

    return FG_FALSE;
}
//------------------------------------------------------------------------------
