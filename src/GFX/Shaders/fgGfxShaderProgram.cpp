/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxShaderProgram.h"
#include "GFX/fgGfxErrorCodes.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"
#include "fgLog.h"

#ifndef FG_INC_GFX_SHADER_MANAGER
#include "fgGfxShaderManager.h"
#include "GFX/Textures/fgTextureTypes.h"
#endif

using namespace fg;
//------------------------------------------------------------------------------

gfx::CShaderProgram::CShaderProgram() : base_type(),
m_stateFlags(NO_FLAGS),
m_shaders(),
m_uniformBinds(),
m_attrBinds(),
m_config(NULL) {
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
    m_baseType = BASE_TYPE_PROGRAM;

    m_uniformBinds.resize(shaders::NUM_UNIFORM_TYPES + 1);
    for(unsigned int i = 0; i <= (unsigned int)shaders::NUM_UNIFORM_TYPES; i++) {
        m_uniformBinds[i].type = (shaders::UniformType)i;
    }
}
//------------------------------------------------------------------------------

gfx::CShaderProgram::~CShaderProgram() {
    self_type::clearAll();
}
//------------------------------------------------------------------------------

void gfx::CShaderProgram::clearAll(void) {
    if(m_config)
        delete m_config;
    m_config = NULL;

    for(int i = 0; i < (int)m_shaders.size(); i++) {
        if(m_shaders[i]) {
            m_shaders[i]->detach(m_gfxID);
            CShader *pShader = m_shaders[i];
            m_shaders[i] = NULL;
            if(!pShader->isManaged() || !pShader->getManager()) {
                // destroy the shader if it is not managed
                // should not cause leaks
                delete pShader;
            }
        }
    }
    m_uniformBinds.clear_optimised();
    m_attrBinds.clear_optimised();
    m_shaders.clear_optimised();
    m_stateFlags = NO_FLAGS;
    deleteProgram();
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::preLoadConfig(const char *path) {
    if(isPreloaded()) {
        return FG_FALSE;
    }
    setFilePath(path);
    const char *ext = path::fileExt(path, FG_TRUE);
    if(!ext) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_WRONG_PATH);
        return FG_FALSE;
    }
    if(strcasecmp(ext, shaders::getShaderProgramConfigSuffix()) != 0) {
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
    CShaderConfig::ShaderTypeVec shaderTypes = m_config->getShaderTypes();
    CShaderConfig::FileNameVec fileNames = m_config->getFiles();
    CShaderConfig::ConstantVec shaderConstants = m_config->getRefConstants();
    m_nameTag = m_config->getProgramName();

    for(int i = 0; i < (int)shaderTypes.size(); i++) {
        std::string newPath;
        if(!m_config->load(fileNames[i].c_str(), context::getSLVersion())) {
            FG_LOG_ERROR("GFX: Failed to load shader program config: '%s'", fileNames[i].c_str());
            return FG_FALSE;
        }
        shaders::ShaderType shaderType = shaderTypes[i];
        int spID = shaderTypeToSpID(shaderType);
        gfx::CShader *pShader = NULL;
        //fgBool isNew = FG_FALSE;
        if(m_shaders[spID]) {
            // ?? shader already initialized ?
            if(m_shaders[spID]->getType() == shaderType) {
                // the same, proper type
                // need to check whether or not it has the same name
                if(m_shaders[spID]->getName().compare(m_config->getShaderName()) == 0) {
                    // the same name - need to skip it
                    continue; // ?
                }
            } else {
                // need to do here something...
            }
        }

        if(this->isManaged() && this->getManager()) {
            // now check if the requested shader object is already present and managed
            CShaderManager* pShaderMgr = static_cast<CShaderManager*>(this->getManager());
            pShader = pShaderMgr->getShader(m_config->getShaderName());
            if(pShader) {
                // found already existing shader object
                // name fits, it will be used
                //isNew = FG_FALSE;
            } else {
                // could not find such, try again
                pShader = pShaderMgr->getShaderByPath(path::fileName(m_config->getFiles()[0].c_str()));
            }
        }
        if(!pShader) {
            m_shaders[spID] = new gfx::CShader(shaderType);
            pShader = m_shaders[spID];
            pShader->setName(m_config->getShaderName());
            pShader->setVersion(context::getSLVersion());
            // File quality mapping
            // Need to find a way :D for now supporting only one file / quality universal
            newPath = path::dirName(fullPath);
            newPath.append(m_config->getFiles()[0]);
            pShader->setFilePath(newPath);
            newPath.clear();

            {
                CShaderConfig::ConstantVec& _vec = m_config->getRefConstants();
                for(int i = 0; i < (int)_vec.size(); i++)
                    pShader->appendDefine(_vec[i]);
                for(int i = 0; i < (int)shaderConstants.size(); i++)
                    pShader->appendDefine(shaderConstants[i]);
            }
            {
                CShaderConfig::IncludeNameVec& _vec = m_config->getIncludes();
                for(int i = 0; i < (int)_vec.size(); i++) {
                    pShader->appendInclude(_vec[i]);
                }
            }
            appendAttributeBinds(m_config->getAttributeBinds());
            appendUniformBinds(m_config->getUniformBinds());

            // the shader is new - force add it to shader manager (parent)
            if(this->isManaged() && this->getManager()) {
                CShaderManager* pShaderMgr = static_cast<CShaderManager*>(this->getManager());
                pShaderMgr->insertShader(pShader);
            }
        }
    }
    delete m_config;
    m_config = NULL;
    setPreloaded(FG_TRUE);
    FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "Shader program loaded successfully: '%s'", m_nameTag.c_str());
    FG_LOG_DEBUG("GFX: Shader program loaded: name[%s], config[%s]", m_nameTag.c_str(), path);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::preLoadConfig(std::string &path) {
    return preLoadConfig(path.c_str());
}
//------------------------------------------------------------------------------

fgGFXuint gfx::CShaderProgram::create(void) {
    if(!isPreloaded())
        return 0;
    if(!m_gfxID || FG_GFX_FALSE == glIsProgram(m_gfxID)) {
        m_gfxID = glCreateProgram();
        GLCheckError("glCreateShader");
        FG_LOG_DEBUG("GFX: Created shader program '%s', gfxID: %d [is shader program? = %d]", getNameStr(), m_gfxID, glIsProgram(m_gfxID));
    }
    return m_gfxID;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::compile(void) {
    if(!isPreloaded()) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_EPERM, "Compile function called without loaded shader configuration");
        return FG_FALSE;
    }
    if(isCompiled() && FG_GFX_TRUE == glIsProgram(m_gfxID)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_EPERM, "Shader program is already compiled. Use option for forced recompilation.");
        return FG_FALSE;
    }
    if(!create()) {
        FG_LOG_ERROR("GFX: Failed to create shader program: name[%s], path[%s]", getNameStr(), getFilePathStr());
        return FG_FALSE;
    }
    ShaderVecItor begin, end, itor;
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
    setCompiled(FG_TRUE);
    FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "Shaders for '%s' compiled successfully", getNameStr());
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::link(void) {
    if(isLinked() || !isPreloaded()) {
        FG_LOG_ERROR("GFX: Shader is already linked / is not pre-loaded on link() for program '%s'", getNameStr());
        return FG_FALSE;
    }
    if(!isCompiled()) {
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
    setLinked(FG_TRUE);
    if(!bindUniforms()) {
        // ERROR CODES ! ! !
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_EINVAL, "GFX: Failed to bind all uniforms in shader program '%s'", getNameStr());
        status = FG_FALSE;
    }
    {
        FG_LOG_DEBUG("GFX: Validating bound locations of attributes...");
        AttributeBindVecItor begin, end, itor;
        begin = m_attrBinds.begin();
        end = m_attrBinds.end();
        itor = begin;
        for(; itor != end; itor++) {
            SAttributeBind & bind = *itor;
            if(bind.location == -1 || bind.type == ATTRIBUTE_INVALID)
                continue;
            int boundLoc = glGetAttribLocation(m_gfxID, bind.variableName.c_str());
            FG_LOG_DEBUG("GFX: Bound attribute '%s' to location %d (should be %d)",
                         bind.variableName.c_str(), boundLoc, (int)bind.type);
            GLCheckError("glGetAttribLocation");
        }
    }
    detachShaders();
    this->use();
    // Set default texture unit's for various uniform variables
    this->setUniform(shaders::UNIFORM_PLAIN_TEXTURE, texture::UNIT_DIFFUSE);
    this->setUniform(shaders::UNIFORM_AMBIENT_MAP, texture::UNIT_AMBIENT);
    this->setUniform(shaders::UNIFORM_SPECULAR_MAP, texture::UNIT_SPECULAR);
    this->setUniform(shaders::UNIFORM_NORMAL_MAP, texture::UNIT_NORMAL);
    this->setUniform(shaders::UNIFORM_BUMP_MAP, texture::UNIT_BUMP);
    this->setUniform(shaders::UNIFORM_ENVIRONMENT_MAP, texture::UNIT_ENVIRONMENT);
    this->setUniform(shaders::UNIFORM_CUBE_TEXTURE, texture::UNIT_CUBE);
    //this->setUniform(shaders::UNIFORM_3D_TEXTURE, texture::UNIT_3D);
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::isUsed(void) {
    if(FG_GFX_FALSE == glIsProgram(m_gfxID) || !isPreloaded())
        return FG_FALSE;
    if(m_pManager) {
        CShaderManager *shaderMgr = (CShaderManager *)m_pManager;
        if(shaderMgr->isProgramUsed(this))
            return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::use(void) {
    // call to glIsProgram may be a slowdown, this shouldn't be necessary at some point
    if(FG_GFX_FALSE == glIsProgram(m_gfxID) || !isPreloaded())
        return FG_FALSE;
    if(m_pManager) {
        CShaderManager *shaderMgr = static_cast<CShaderManager *>(m_pManager);
        if(shaderMgr->isProgramUsed(this))
            return FG_FALSE;
        shaderMgr->setInternalCurrentProgram(this);
    }
    //fgGFXuint last = context::activeProgram();
    context::useProgram(m_gfxID);
    this->setRecentlyUsed(FG_TRUE);
    GLCheckError("glUseProgram");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::deleteProgram(void) {
    if(FG_GFX_TRUE == glIsProgram(m_gfxID)) {
        // #FIXME
        //detachShaders(); // status?
        glDeleteProgram(m_gfxID);
        m_gfxID = 0;
        setLinked(FG_FALSE);
        setCompiled(FG_FALSE);
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::appendUniformBinds(UniformBindVec& binds) {
    if(binds.empty())
        return FG_FALSE;
    const int imax = binds.size();
    const int tmax = m_uniformBinds.size();
    for(int i = 0; i < imax; i++) {
        int bIdx = (int)binds[i].type;
        if(bIdx >= tmax)
            continue;
        if(binds[i].variableName.empty())
            continue;
        m_uniformBinds[bIdx] = binds[i];
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::appendAttributeBinds(AttributeBindVec & binds) {
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
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::attachShader(gfx::CShader *shader) {
    if(!shader) {
        return FG_FALSE;
    }
    fgBool status = shader->attach(m_gfxID);
    updateParams();
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::attachShaders(void) {
    if(!isPreloaded()) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    ShaderVecItor begin, end, itor;
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
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::deleteShader(gfx::CShader *shader) {
    if(!shader) {
        return FG_FALSE;
    }
    fgBool status = shader->deleteShader();
    updateParams();
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::deleteShaders(void) {
    fgBool status = FG_TRUE;
    ShaderVecItor begin, end, itor;
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
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::detachShader(gfx::CShader *shader) {
    if(!shader) {
        return FG_FALSE;
    }
    fgBool status = shader->detach(m_gfxID);
    updateParams();
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::detachShaders(void) {
    if(!isPreloaded()) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    ShaderVecItor begin, end, itor;
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
//------------------------------------------------------------------------------

fgGFXint gfx::CShaderProgram::updateLinkStatus(void) {
    return updateParam(FG_GFX_PROGRAM_LINK_STATUS);
}
//------------------------------------------------------------------------------

fgGFXint gfx::CShaderProgram::updateValidateStatus(void) {
    return updateParam(FG_GFX_PROGRAM_VALIDATE_STATUS);
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::releaseGFX(void) {
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
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setManager(::fg::base::CManager *pManager) {
    if(!pManager)
        return FG_FALSE;
    setManaged(FG_TRUE);
    m_pManager = pManager;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::bindAttributes(void) {
    if(!isPreloaded() || !isCompiled()) {
        return FG_FALSE;
    }
    if(FG_GFX_FALSE == glIsProgram(m_gfxID)) {
        FG_LOG_ERROR("GFX: Bind attributes: current program gfxID(%d) is invalid.", m_gfxID);
        return FG_FALSE;
    }
    AttributeBindVecItor begin, end, itor;
    begin = m_attrBinds.begin();
    end = m_attrBinds.end();
    itor = begin;
    for(; itor != end; itor++) {
        SAttributeBind & bind = *itor;
        // ? NEED STANDARD LOCATIONS
        if(bind.location == -1 || bind.type == ATTRIBUTE_INVALID)
            continue;
        FG_LOG_DEBUG("GFX: Binding attribute '%s' of type: '%s'(%d), in shader program: '%s' to location: %d",
                     bind.variableName.c_str(),
                     getTextFromAttributeType(bind.type),
                     (int)bind.type,
                     getNameStr(),
                     (int)bind.location);

        glBindAttribLocation(m_gfxID, (fgGFXuint)bind.location, bind.variableName.c_str());
        GLCheckError("glBindAttribLocation");
        bind.isBound = FG_GFX_TRUE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::bindUniforms(void) {
    if(!isPreloaded() || !isCompiled()) {
        return FG_FALSE;
    }
    if(FG_GFX_FALSE == glIsProgram(m_gfxID)) {
        return FG_FALSE;
    }
    UniformBindVecItor begin, end, itor;
    begin = m_uniformBinds.begin();
    end = m_uniformBinds.end();
    itor = begin;
    for(; itor != end; itor++) {
        SUniformBind & bind = *itor;
        if(bind.type == shaders::UNIFORM_INVALID || bind.variableName.empty())
            continue;
        std::string variableName;
        variableName.append(bind.variableName);
        if(bind.type == shaders::UNIFORM_DIRECTIONAL_LIGHT) {
            // cant bind to just a variable name
            // need to find... first item in struct;
            //variableName.append(".direction");
            variableName.append(".ambient");
            // #FIXME - if this is an array (need to have info on that
            // need also to add [N], array access)
            //printf("SDirLight.direction: %d\n", getUniformLocation(std::string("u_directionalLight.direction")));
            //printf("SDirLight.ambient: %d\n", getUniformLocation(std::string("u_directionalLight.ambient")));
            //printf("SDirLight.diffuse: %d\n", getUniformLocation(std::string("u_directionalLight.diffuse")));
            //printf("SDirLight.specular: %d\n", getUniformLocation(std::string("u_directionalLight.specular")));
        } else if(bind.type == shaders::UNIFORM_MATERIAL) {
            variableName.append(".ambient"); // 4f
            //printf("SMaterial.ambient: %d\n", getUniformLocation(std::string("u_material.ambient")));
            //printf("SMaterial.diffuse: %d\n", getUniformLocation(std::string("u_material.diffuse")));
            //printf("SMaterial.specular: %d\n", getUniformLocation(std::string("u_material.specular")));
            //printf("SMaterial.shininess: %d\n", getUniformLocation(std::string("u_material.shininess")));
        }
        bind.location = getUniformLocation(variableName);
        FG_LOG_DEBUG("GFX: Bound uniform '%s' of type: '%s'(%d) to location: %d",
                     bind.variableName.c_str(),
                     getTextFromUniformType(bind.type),
                     (int)bind.type,
                     bind.location);
        GLCheckError("glGetUniformLocation");
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgGFXint gfx::CShaderProgram::getUniformBindIndex(shaders::UniformType type) {
    int n = (int)m_uniformBinds.size();
    if(n <= (int)type)
        return 0;
    if(m_uniformBinds[(int)type].type == type)
        return (int)type;
    return 0;
}
//------------------------------------------------------------------------------

gfx::SUniformBind *gfx::CShaderProgram::getUniformBind(shaders::UniformType type) {
    int index = getUniformBindIndex(type);
    return &m_uniformBinds[index];
}
//------------------------------------------------------------------------------

fgGFXint gfx::CShaderProgram::getUniformLocation(shaders::UniformType type) {
    SUniformBind* bind = getUniformBind(type);
    return bind->location;
}
//------------------------------------------------------------------------------

fgGFXint gfx::CShaderProgram::getUniformLocation(std::string variableName) {
    if(!m_gfxID || variableName.empty())
        return -1;
    return glGetUniformLocation(m_gfxID, variableName.c_str());
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(CMVPMatrix* matrix) {
    if(!matrix)
        return FG_FALSE;
    SUniformBind* bind = &m_uniformBinds[shaders::UNIFORM_MVP_MATRIX];
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix4fv(bind->location, 1, GL_FALSE, matrix->getModelViewProjMatPtr());
    GLCheckError("glUniformMatrix4fv");

    // MVP also contains MV matrix, can set it also
    bind = &m_uniformBinds[shaders::UNIFORM_MV_MATRIX];
    if(bind->location != -1) {
        glUniformMatrix4fv(bind->location, 1, GL_FALSE, matrix->getModelViewMatPtr());
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(CMVMatrix* matrix) {
    SUniformBind* bind = &m_uniformBinds[shaders::UNIFORM_MV_MATRIX];
    if(!matrix)
        return FG_FALSE;
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix4fv(bind->location, 1, GL_FALSE, matrix->getModelViewMatPtr());
    GLCheckError("glUniformMatrix4fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(const SDirectionalLight& light) {
    SUniformBind* bind = &m_uniformBinds[shaders::UNIFORM_DIRECTIONAL_LIGHT];
    if(bind->location == -1)
        return FG_FALSE;

    //glUniform3fv(bind->location + 1, 1, math::value_ptr(light.halfPlane));
    glUniform4fv(bind->location + 0, 1, math::value_ptr(light.ambient));
    glUniform4fv(bind->location + 1, 1, math::value_ptr(light.diffuse));
    glUniform3fv(bind->location + 2, 1, math::value_ptr(light.direction));
    glUniform4fv(bind->location + 3, 1, math::value_ptr(light.specular));

    //SDirLight.ambient: 1 | 0
    //SDirLight.diffuse: 2 | 1
    //SDirLight.direction: 3 | 2
    //SDirLight.specular: 4 | 3

    GLCheckError("glUniform4fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(const SMaterial& material) {
    SUniformBind* bind = &m_uniformBinds[shaders::UNIFORM_MATERIAL];
    if(bind->location == -1)
        return FG_FALSE;

    //SMaterial.ambient : 5 | 0
    //SMaterial.diffuse : 6 | 1
    //SMaterial.shininess : 7 | 2
    //SMaterial.specular : 8 | 3

    glUniform4fv(bind->location + 0, 1, math::value_ptr(material.ambient));
    glUniform4fv(bind->location + 1, 1, math::value_ptr(material.diffuse));
    glUniform1f(bind->location + 2, material.shininess);
    glUniform4fv(bind->location + 3, 1, math::value_ptr(material.specular));
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const Matrix4f& matrix) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;

    math::rotate(matrix, 0.0f, Vec3f(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(bind->location, 1, GL_FALSE, math::value_ptr(matrix));
    GLCheckError("glUniformMatrix4fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const Matrix4f* matrices,
                                       const unsigned int count) {
    if(!matrices || !count)
        return FG_FALSE;
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix4fv(bind->location, count,
                       GL_FALSE, (const float*)matrices);
    GLCheckError("glUniformMatrix4fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const CVector<Matrix4f>& matrices) {
    if(matrices.empty())
        return FG_FALSE;
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix4fv(bind->location,
                       matrices.size(),
                       GL_FALSE,
                       (const fgGFXfloat*)&matrices.front());
    GLCheckError("glUniformMatrix4fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const Matrix3f& matrix) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix3fv(bind->location, 1, GL_FALSE, math::value_ptr(matrix));
    GLCheckError("glUniformMatrix3fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const Matrix3f* matrices,
                                       const unsigned int count) {
    if(!matrices || !count)
        return FG_FALSE;
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix3fv(bind->location, count,
                       GL_FALSE, (const fgGFXfloat*)matrices);
    GLCheckError("glUniformMatrix3fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const CVector<Matrix3f>& matrices) {
    if(matrices.empty())
        return FG_FALSE;
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniformMatrix3fv(bind->location,
                       matrices.size(),
                       GL_FALSE,
                       (const fgGFXfloat*)&matrices.front());
    GLCheckError("glUniformMatrix3fv");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const DualQuaternionf& dualquat) {
    return setUniform(type, dualquat.length(), math::value_ptr(dualquat));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const DualQuaternionf* dquats,
                                       const unsigned int count) {
    return setUniform(type, dquats[0].length() * count,
                      (const fgGFXfloat*)&dquats[0][0]);
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       const CVector<DualQuaternionf>& dquats) {
    return setUniform(type, dquats[0].length() * dquats.size(),
                      (const fgGFXfloat*)&dquats.front());
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(const CVector<DualQuaternionf>& dquats) {
    return setUniform(shaders::UNIFORM_BONE_DUAL_QUATERNIONS,
                      dquats[0].length() * dquats.size(),
                      (const fgGFXfloat*)&dquats.front());
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXfloat v0) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform1f(bind->location, v0);
    GLCheckError("glUniform1f");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXfloat v0,
                                       fgGFXfloat v1) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform2f(bind->location, v0, v1);
    GLCheckError("glUniform2f");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXfloat v0,
                                       fgGFXfloat v1,
                                       fgGFXfloat v2) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform3f(bind->location, v0, v1, v2);
    GLCheckError("glUniform3f");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXfloat v0,
                                       fgGFXfloat v1,
                                       fgGFXfloat v2,
                                       fgGFXfloat v3) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform4f(bind->location, v0, v1, v2, v3);
    GLCheckError("glUniform4f");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXint v0) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform1i(bind->location, v0);
    GLCheckError("glUniform1i");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXint v0,
                                       fgGFXint v1) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform2i(bind->location, v0, v1);
    GLCheckError("glUniform2i");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXint v0,
                                       fgGFXint v1,
                                       fgGFXint v2) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform3i(bind->location, v0, v1, v2);
    GLCheckError("glUniform3i");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXint v0,
                                       fgGFXint v1,
                                       fgGFXint v2,
                                       fgGFXint v3) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    glUniform4i(bind->location, v0, v1, v2, v3);
    GLCheckError("glUniform4i");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXsizei count,
                                       const fgGFXfloat *value) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    if(bind->dataType == FG_GFX_FLOAT_VEC4) {
        glUniform4fv(bind->location, count / 4, value);
        GLCheckError("glUniform4fv");
    } else if(bind->dataType == FG_GFX_FLOAT_VEC3) {
        glUniform3fv(bind->location, count / 3, value);
        GLCheckError("glUniform3fv");
    } else if(bind->dataType == FG_GFX_FLOAT_VEC2) {
        glUniform2fv(bind->location, count / 2, value);
        GLCheckError("glUniform2fv");
    } else if(bind->dataType == FG_GFX_FLOAT) {
        glUniform1fv(bind->location, count, value);
        GLCheckError("glUniform1fv");
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderProgram::setUniform(shaders::UniformType type,
                                       fgGFXsizei count,
                                       const fgGFXint *value) {
    SUniformBind* bind = &m_uniformBinds[type];
    if(bind->location == -1)
        return FG_FALSE;
    if(bind->dataType == FG_GFX_INT_VEC4) {
        glUniform4iv(bind->location, count / 4, value);
        GLCheckError("glUniform4iv");
    } else if(bind->dataType == FG_GFX_INT_VEC3) {
        glUniform3iv(bind->location, count / 3, value);
        GLCheckError("glUniform3iv");
    } else if(bind->dataType == FG_GFX_INT_VEC2) {
        glUniform2iv(bind->location, count / 2, value);
        GLCheckError("glUniform2iv");
    } else if(bind->dataType == FG_GFX_INT) {
        glUniform1iv(bind->location, count, value);
        GLCheckError("glUniform1iv");
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------
