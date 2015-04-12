/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGFXShaderProgram.h"
#include "GFX/fgGFXErrorCodes.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"
#include "fgLog.h"

#ifndef FG_INC_GFX_SHADER_MANAGER
#include "fgGFXShaderManager.h"
#endif

using namespace fg;

/**
 * 
 */
gfx::CShaderProgram::CShaderProgram() :
m_config(NULL),
m_isPreLoaded(FG_FALSE),
m_isCompiled(FG_FALSE),
m_isLinked(FG_FALSE),
m_manager(NULL) {
    // this needs to depend on some global array GFX config #FIXME
    m_shaders.reserve(6);
    for(int i = 0; i < (int)m_shaders.capacity(); i++) {
        m_shaders.push_back(NULL);
    }
    m_params[FG_GFX_PROGRAM_DELETE_STATUS] = 0;
    m_params[FG_GFX_PROGRAM_LINK_STATUS] = 0;
    m_params[FG_GFX_PROGRAM_VALIDATE_STATUS] = 0;
    m_params[FG_GFX_PROGRAM_INFO_LOG_LENGTH] = 0;
    m_params[FG_GFX_PROGRAM_ATTACHED_SHADERS] = 0;
    m_params[FG_GFX_PROGRAM_ACTIVE_ATTRIBUTES] = 0;
    m_params[FG_GFX_PROGRAM_ACTIVE_ATTRIBUTE_MAX_LENGTH] = 0;
    m_params[FG_GFX_PROGRAM_ACTIVE_UNIFORMS] = 0;
    m_baseType = FG_GFX_BASE_TYPE_PROGRAM;
}

/**
 * 
 */
gfx::CShaderProgram::~CShaderProgram() {
    gfx::CShaderProgram::clearAll();
}

/**
 * 
 */
void gfx::CShaderProgram::clearAll(void) {
    if(m_config)
        delete m_config;
    m_config = NULL;

    for(int i = 0; i < (int)m_shaders.size(); i++) {
        if(m_shaders[i]) {
            m_shaders[i]->detach(m_gfxID);
            CShader *shader = m_shaders[i];
            m_shaders[i] = NULL;
            delete shader;
        }
    }
    m_uniformBinds.clear_optimised();
    m_attrBinds.clear_optimised();
    m_shaders.clear_optimised();
    deleteProgram();
    m_isLinked = FG_FALSE;
    m_isCompiled = FG_FALSE;
    m_isPreLoaded = FG_FALSE;
}

/**
 * 
 * @param path
 * @return 
 */
fgBool gfx::CShaderProgram::preLoadConfig(const char *path) {
    if(m_isPreLoaded) {
        return FG_FALSE;
    }
    setFilePath(path);
    const char *ext = path::fileExt(path, FG_TRUE);
    if(!ext) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_WRONG_PATH);
        return FG_FALSE;
    }

    if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX) != 0) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_WRONG_PATH);
        return FG_FALSE;
    }

    if(!m_config) {
        m_config = new CShaderConfig();
    }

    //const char *fileName = fgPath::fileName(path);
    std::string fullPath = path;
    std::string filePathNoExt = fullPath.substr(0, fullPath.length() - 1 - strlen(ext));

    // First load the main shader program config
    if(!m_config->load(path, context::getSLVersion())) {
        return FG_FALSE;
    }
    CShaderConfig::ShaderTypeVec shaderTypes = m_config->getRefShaderTypes();
    m_nameTag = m_config->getProgramName();

    CShaderConfig::ConstantVec shaderConstants = m_config->getRefConstants();

    for(int i = 0; i < (int)shaderTypes.size(); i++) {
        std::string newPath;
        newPath.append(filePathNoExt).append(".").append(FG_GFX_SHADER_CFG_STD_SUFFIX(shaderTypes[i]));

        if(!m_config->load(newPath.c_str(), context::getSLVersion())) {
            FG_LOG_ERROR("GFX: Failed to load shader program config: '%s'", newPath.c_str());
            return FG_FALSE;
        }
        ShaderType shaderType = shaderTypes[i];
        int spID = shaderTypeToSpID(shaderType);
        if(m_shaders[spID]) {
            // ?? shader already initialized lol
        }
        m_shaders[spID] = new gfx::CShader(shaderType);
        gfx::CShader *shader = m_shaders[spID];
        // File quality mapping omg
        // Need to find a way :D for now supporting only one file / quality universal
        // #TODO #FILEMAPPING
        newPath = path::dirName(fullPath);
        newPath.append(m_config->getRefFiles()[0]);
        shader->setFilePath(newPath);
        newPath.clear();
        shader->setVersion(FG_GFX_ESSL_100);
        {
            CShaderConfig::ConstantVec & _vec = m_config->getRefConstants();
            for(int i = 0; i < (int)_vec.size(); i++)
                shader->appendDefine(_vec[i]);
            for(int i = 0; i < (int)shaderConstants.size(); i++)
                shader->appendDefine(shaderConstants[i]);
        }
        {
            CShaderConfig::IncludeNameVec & _vec = m_config->getRefIncludes();
            for(int i = 0; i < (int)_vec.size(); i++) {
                shader->appendInclude(_vec[i]);
            }
        }
        appendAttributeBinds(m_config->getRefAttributeBinds());
        appendUniformBinds(m_config->getRefUniformBinds());
    }
    delete m_config;
    m_config = NULL;
    m_isPreLoaded = FG_TRUE;
    FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "Shader program loaded successfully: '%s'", m_nameTag.c_str());
    FG_LOG_DEBUG("GFX: Shader program loaded: name[%s], config[%s]", m_nameTag.c_str(), path);
    ////////////////////////////////////////////////////////////////////////////
    return FG_TRUE;
}

/**
 * 
 * @param path
 * @return 
 */
fgBool gfx::CShaderProgram::preLoadConfig(std::string &path) {
    return preLoadConfig(path.c_str());
}

/**
 * 
 * @return 
 */
fgGFXuint gfx::CShaderProgram::create(void) {
    if(!m_isPreLoaded)
        return 0;
    if(!m_gfxID || FG_GFX_FALSE == glIsProgram(m_gfxID)) {
        m_gfxID = glCreateProgram();
        GLCheckError("glCreateShader");
        FG_LOG_DEBUG("GFX: Created shader program '%s', gfxID: %d [is shader program? = %d]", getNameStr(), m_gfxID, glIsProgram(m_gfxID));
    }
    return m_gfxID;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::compile(void) {
    if(!m_isPreLoaded) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_EPERM, "Compile function called without loaded shader configuration");
        return FG_FALSE;
    }
    if(m_isCompiled && FG_GFX_TRUE == glIsProgram(m_gfxID)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_EPERM, "Shader program is already compiled. Use option for forced recompilation.");
        return FG_FALSE;
    }
    if(!create()) {
        FG_LOG_ERROR("GFX: Failed to create shader program: name[%s], path[%s]", getNameStr(), getFilePathStr());
        return FG_FALSE;
    }
    shaderVecItor begin, end, itor;
    begin = m_shaders.begin(), end = m_shaders.end();
    itor = begin;
    for(; itor != end; itor++) {
        if(!(*itor))
            continue;
        gfx::CShader *shader = *itor;
        FG_LOG_DEBUG("GFX: Attempting to compile shader: '%s'", shader->getFilePathStr());
        if(!shader->compile()) {
            updateParams();
            updateLog();
            const char *log = shader->getLog();
            if(!log) log = "No message";
            FG_LOG_ERROR("GFX: Failed to compile shader: '%s' (%s)", shader->getNameStr(), log);
            return FG_FALSE;
        }
    }
    attachShaders(); // status ?
    m_isCompiled = FG_TRUE;
    FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "Shaders for '%s' compiled successfully", getNameStr());
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::link(void) {
    if(m_isLinked || !m_isPreLoaded) {
        FG_LOG_ERROR("GFX: Shader is already linked / is not pre-loaded on link() for program '%s'", getNameStr());
        return FG_FALSE;
    }
    if(!m_isCompiled) {
        if(!compile()) {
            FG_LOG_ERROR("GFX: Failed to compile shaders for program '%s'", getNameStr());
            return FG_FALSE;
        }
    }
    if(!bindAttributes()) {
        FG_LOG_ERROR("GFX: Failed to bind attributes for program '%s'", getNameStr());
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    glLinkProgram(m_gfxID);
    GLCheckError("glLinkProgram");
    updateLinkStatus();
    if(!m_params[FG_GFX_PROGRAM_LINK_STATUS]) {
        updateLog();
        FG_LOG_ERROR("GFX: Error linking program '%s': %s\n", getNameStr(), getLog());
        return FG_FALSE;
    }
    glValidateProgram(m_gfxID);
    GLCheckError("glValidateProgram");
    //s3eDeviceYield(0);
    updateValidateStatus();
    if(!m_params[FG_GFX_PROGRAM_VALIDATE_STATUS]) {
        FG_LOG_WARNING("GFX: The program '%s' did not validate successfully", getNameStr());
        status = FG_FALSE;
    }
    updateParams();
    updateLog();
    if(status) {
        FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "GFX: Shader program '%s' linked with no errors", getNameStr());
    }
    m_isLinked = FG_TRUE;
    if(!bindUniforms()) {
        // ERROR CODES ! ! !
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_EINVAL, "GFX: Failed to bind all uniforms in shader program '%s'", getNameStr());
        status = FG_FALSE;
    }
    {
        FG_LOG_DEBUG("GFX: Validating bound locations of attributes...");
        attributeBindVecItor begin, end, itor;
        begin = m_attrBinds.begin();
        end = m_attrBinds.end();
        itor = begin;
        for(; itor != end; itor++) {
            SAttributeBind & bind = *itor;
            if(bind.location == -1 || bind.type == FG_GFX_ATTRIBUTE_INVALID)
                continue;
            int boundLoc = glGetAttribLocation(m_gfxID, bind.variableName.c_str());
            FG_LOG_DEBUG("GFX: Bound attribute '%s' to location %d (should be %d)",
                         bind.variableName.c_str(), boundLoc, (int)bind.type);
            GLCheckError("glGetAttribLocation");
        }
    }
    {
        detachShaders();
    }
    return status;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::isUsed(void) {
    if(FG_GFX_FALSE == glIsProgram(m_gfxID) || !m_isPreLoaded)
        return FG_FALSE;
    if(m_manager) {
        CShaderManager *shaderMgr = (CShaderManager *)m_manager;
        if(shaderMgr->isProgramUsed(this))
            return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::use(void) {
    // call to glIsProgram may be a slowdown, this shouldn't be necessary at some point
    if(FG_GFX_FALSE == glIsProgram(m_gfxID) || !m_isPreLoaded)
        return FG_FALSE;
    if(m_manager) {
        CShaderManager *shaderMgr = static_cast<CShaderManager *>(m_manager);
        if(shaderMgr->isProgramUsed(this))
            return FG_FALSE;
        shaderMgr->setInternalCurrentProgram(this); // ?
    }
    fgGFXuint last = context::activeProgram();
    context::useProgram(m_gfxID);
    GLCheckError("glUseProgram"); // #FIXME - GL error reporting - rtard?
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::deleteProgram(void) {
    if(FG_GFX_TRUE == glIsProgram(m_gfxID)) {
        // #FIXME
        //detachShaders(); // status?
        glDeleteProgram(m_gfxID);
        m_gfxID = 0;
        m_isLinked = FG_FALSE;
        m_isCompiled = FG_FALSE;
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @param binds
 * @return 
 */
fgBool gfx::CShaderProgram::appendUniformBinds(uniformBindVec & binds) {
    if(binds.empty())
        return FG_FALSE;
    const int imax = binds.size();
    for(int i = 0; i < imax; i++) {
        if(m_uniformBinds.contains(binds[i]))
            continue;
        m_uniformBinds.push_back(binds[i]);
    }
    return FG_TRUE;
}

/**
 * 
 * @param binds
 * @return 
 */
fgBool gfx::CShaderProgram::appendAttributeBinds(attributeBindVec & binds) {
    if(binds.empty())
        return FG_FALSE;
    const int imax = binds.size();
    for(int i = 0; i < imax; i++) {
        if(m_attrBinds.contains(binds[i]))
            continue;
        m_attrBinds.push_back(binds[i]);
    }
    unsigned int pos = 1;
    while(pos < m_attrBinds.size()) {
        if(m_attrBinds[pos] >= m_attrBinds[pos - 1]) {
            pos = pos + 1;
        } else {
            std::swap<SAttributeBind>(m_attrBinds[pos], m_attrBinds[pos - 1]);
            if(pos > 1) {
                pos = pos - 1;
            }
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @param shader
 * @return 
 */
fgBool gfx::CShaderProgram::attachShader(gfx::CShader *shader) {
    if(!shader) {
        return FG_FALSE;
    }
    fgBool status = shader->attach(m_gfxID);
    updateParams();
    return status;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::attachShaders(void) {
    if(!m_isPreLoaded) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    shaderVecItor begin, end, itor;
    begin = m_shaders.begin(), end = m_shaders.end();
    itor = begin;
    for(; itor != end; itor++) {
        if(!(*itor))
            continue;
        if(!attachShader(*itor))
            status = FG_FALSE;
    }
    return status;
}

/**
 * 
 * @param shader
 * @return 
 */
fgBool gfx::CShaderProgram::deleteShader(gfx::CShader *shader) {
    if(!shader) {
        return FG_FALSE;
    }
    fgBool status = shader->deleteShader();
    updateParams();
    return status;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::deleteShaders(void) {
    fgBool status = FG_TRUE;
    shaderVecItor begin, end, itor;
    begin = m_shaders.begin(), end = m_shaders.end();
    itor = begin;
    for(; itor != end; itor++) {
        if(!(*itor))
            continue;
        if(!deleteShader(*itor))
            status = FG_FALSE;
    }
    return status;
}

/**
 * 
 * @param shader
 * @return 
 */
fgBool gfx::CShaderProgram::detachShader(gfx::CShader *shader) {
    if(!shader) {
        return FG_FALSE;
    }
    fgBool status = shader->detach(m_gfxID);
    updateParams();
    return status;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::detachShaders(void) {
    if(!m_isPreLoaded) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    shaderVecItor begin, end, itor;
    begin = m_shaders.begin(), end = m_shaders.end();
    itor = begin;
    for(; itor != end; itor++) {
        if(!(*itor))
            continue;
        if(!detachShader(*itor))
            status = FG_FALSE;
    }
    return status;

}

/**
 * 
 * @return 
 */
fgGFXint gfx::CShaderProgram::updateLinkStatus(void) {
    return updateParam(FG_GFX_PROGRAM_LINK_STATUS);
}

/**
 * 
 * @return 
 */
fgGFXint gfx::CShaderProgram::updateValidateStatus(void) {
    return updateParam(FG_GFX_PROGRAM_VALIDATE_STATUS);
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::releaseGFX(void) {
    //fgStatusReporter anyone?
    fgBool status = FG_TRUE;
    if(!deleteProgram())
        status = FG_FALSE; // errors? meh
    if(!deleteShaders())
        status = FG_FALSE;
    // There is a downside to it
    // for now it's screwed up because if shader (for example, fragment) is used
    // in two shader programs it exists in two separate copies (fgGfxShader* object)
    // Need to manage it properly
    // if two shader programs use the same shader it should exist in one copy
    // now it's impossible to achieve, there's no code to support this
    // - identify shaders
    // - mantain database for shaders
    // - separate array
    // - when shader program is given a shader pointer, it does not own it
    // - this should be done in shader program manager
    //
    // also what is needed:
    // - be able to load shaders/programs without config files
    // - search for active attributes
    // - search for available uniforms
    // - regex (or not) shader attrib/uniform variable names, search for matching patterns
    // - automatic binding attribs
    //
    // this could be faster then loading and traversing config files 
    // P3
    return status;
}

/**
 * 
 * @param pManager
 * @return 
 */
fgBool gfx::CShaderProgram::setManager(fg::base::CManager *pManager) {
    if(!pManager)
        return FG_FALSE;
    setManaged(FG_TRUE);
    m_manager = pManager;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::bindAttributes(void) {
    if(!m_isPreLoaded || !m_isCompiled) {
        return FG_FALSE;
    }
    if(FG_GFX_FALSE == glIsProgram(m_gfxID)) {
        FG_LOG_ERROR("GFX: Bind attributes: current program gfxID(%d) is invalid.", m_gfxID);
        return FG_FALSE;
    }
    attributeBindVecItor begin, end, itor;
    begin = m_attrBinds.begin();
    end = m_attrBinds.end();
    itor = begin;
    for(; itor != end; itor++) {
        SAttributeBind & bind = *itor;
        // ? NEED STANDARD LOCATIONS
        if(bind.location == -1 || bind.type == FG_GFX_ATTRIBUTE_INVALID)
            continue;
        FG_LOG_DEBUG("GFX: Binding attribute '%s' of type: '%s'(%d), in shader program: '%s' to location: %d",
                     bind.variableName.c_str(),
                     FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(bind.type),
                     (int)bind.type,
                     getNameStr(),
                     (int)bind.location);

        glBindAttribLocation(m_gfxID, (fgGFXuint)bind.location, bind.variableName.c_str());
        GLCheckError("glBindAttribLocation");
        bind.isBound = FG_GFX_TRUE;
    }
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderProgram::bindUniforms(void) {
    if(!m_isPreLoaded || !m_isCompiled) {
        return FG_FALSE;
    }
    if(FG_GFX_FALSE == glIsProgram(m_gfxID)) {
        return FG_FALSE;
    }
    uniformBindVecItor begin, end, itor;
    begin = m_uniformBinds.begin();
    end = m_uniformBinds.end();
    itor = begin;
    for(; itor != end; itor++) {
        SUniformBind & bind = *itor;
        if(bind.type == FG_GFX_UNIFORM_INVALID)
            continue;
        FG_LOG_DEBUG("GFX: Preparing for binding uniform '%s' of type: '%s' (%d)", bind.variableName.c_str(), FG_GFX_UNIFORM_TYPE_TO_TEXT(bind.type), (int)bind.type);
        bind.location = glGetUniformLocation(m_gfxID, bind.variableName.c_str());
        FG_LOG_DEBUG("GFX: Bound uniform '%s' to location: %d", bind.variableName.c_str(), bind.location);
        GLCheckError("glGetUniformLocation");
    }
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @return 
 */
fgGFXint gfx::CShaderProgram::getUniformBindIndex(UniformType type) {
    if(type == FG_GFX_UNIFORM_INVALID)
        return -1;
    fgGFXint foundIndex = -1;
    int i, n = (int)m_uniformBinds.size();
    for(i = 0; i < n; i++) {
        SUniformBind & bind = m_uniformBinds.at(i);
        if(bind.type == FG_GFX_UNIFORM_INVALID)
            continue;
        if(bind.type == type) {
            foundIndex = i;
            break;
        }
    }
    return foundIndex;
}

/**
 * 
 * @param type
 * @return 
 */
gfx::SUniformBind *gfx::CShaderProgram::getUniformBind(UniformType type) {
    int index = getUniformBindIndex(type);
    if(index < 0)
        return NULL;
    return &m_uniformBinds[index];
}

/**
 * 
 * @param type
 * @return 
 */
fgGFXint gfx::CShaderProgram::getUniformLocation(UniformType type) {
    SUniformBind * bind = getUniformBind(type);
    if(!bind)
        return -1;
    return bind->location;
}

/**
 * 
 * @param variableName
 * @return 
 */
fgGFXint gfx::CShaderProgram::getUniformLocation(std::string variableName) {
    if(!m_gfxID || variableName.empty())
        return -1;
    return glGetUniformLocation(m_gfxID, variableName.c_str());
}

////////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @param matrix
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(CMVPMatrix *matrix) {
    if(!matrix)
        return FG_FALSE;
    SUniformBind * bind = getUniformBind(FG_GFX_MVP_MATRIX);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix4fv(bind->location, 1, GL_FALSE, matrix->getModelViewProjMatPtr());
    GLCheckError("glUniformMatrix4fv");
    return FG_TRUE;
}

/**
 * 
 * @param matrix
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(CMVMatrix *matrix) {
    SUniformBind * bind = getUniformBind(FG_GFX_MV_MATRIX);
    if(!bind || !matrix)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix4fv(bind->location, 1, GL_FALSE, matrix->getModelViewMatPtr());
    GLCheckError("glUniformMatrix4fv");
    return FG_TRUE;
}

////////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @param type
 * @param v0
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXfloat v0) {
    SUniformBind * bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform1f(bind->location, v0);
    GLCheckError("glUniform1f");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param v0
 * @param v1
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXfloat v0,
                                      fgGFXfloat v1) {
    SUniformBind * bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform2f(bind->location, v0, v1);
    GLCheckError("glUniform2f");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param v0
 * @param v1
 * @param v2
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXfloat v0,
                                      fgGFXfloat v1,
                                      fgGFXfloat v2) {
    SUniformBind * bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform3f(bind->location, v0, v1, v2);
    GLCheckError("glUniform3f");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param v0
 * @param v1
 * @param v2
 * @param v3
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXfloat v0,
                                      fgGFXfloat v1,
                                      fgGFXfloat v2,
                                      fgGFXfloat v3) {
    SUniformBind *bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform4f(bind->location, v0, v1, v2, v3);
    GLCheckError("glUniform4f");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param v0
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXint v0) {
    SUniformBind *bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform1i(bind->location, v0);
    GLCheckError("glUniform1i");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param v0
 * @param v1
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXint v0,
                                      fgGFXint v1) {
    SUniformBind *bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform2i(bind->location, v0, v1);
    GLCheckError("glUniform2i");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param v0
 * @param v1
 * @param v2
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXint v0,
                                      fgGFXint v1,
                                      fgGFXint v2) {
    SUniformBind *bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform3i(bind->location, v0, v1, v2);
    GLCheckError("glUniform3i");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param v0
 * @param v1
 * @param v2
 * @param v3
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXint v0,
                                      fgGFXint v1,
                                      fgGFXint v2,
                                      fgGFXint v3) {
    SUniformBind *bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniform4i(bind->location, v0, v1, v2, v3);
    GLCheckError("glUniform4i");
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param count
 * @param value
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXsizei count,
                                      const fgGFXfloat *value) {
    SUniformBind *bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    // NEED MORE IFS :D
    return FG_TRUE;
}

/**
 * 
 * @param type
 * @param count
 * @param value
 * @return 
 */
fgBool gfx::CShaderProgram::setUniform(UniformType type,
                                      fgGFXsizei count,
                                      const fgGFXint *value) {
    SUniformBind *bind = getUniformBind(type);
    if(!bind)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    // NEED MORE IFS :D
    return FG_TRUE;
}
