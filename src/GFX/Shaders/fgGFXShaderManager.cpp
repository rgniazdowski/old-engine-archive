/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGFXShaderManager.h"
#include "GFX/fgGFXErrorCodes.h"
#include "Util/fgRegularFile.h"
#include "Util/fgDirent.h"
#include "Util/fgStrings.h"
#include "Util/fgMemory.h"

using namespace fg;

/**
 * 
 */
gfx::CShaderManager::CShaderManager() :
m_currentProgram(NULL),
m_shadersDir(NULL),
m_shadersPath(),
m_isPreloadDone(FG_FALSE) {
    m_shadersDir = new util::CDirent();
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_init = FG_FALSE;
}

/**
 * 
 */
gfx::CShaderManager::~CShaderManager() {
    destroy();
}

/**
 * 
 */
void gfx::CShaderManager::clear(void) {
    m_currentProgram = NULL;
    m_shadersPath.clear();
    releaseAllHandles();
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_shadersDir = NULL;
    m_init = FG_FALSE;
    m_isPreloadDone = FG_FALSE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderManager::destroy(void) {
    ProgramVec & data = getRefDataVector();
    DataVecItor begin = data.begin(), end = data.end(), itor = begin;
    for(; itor != end; ++itor) {
        if((*itor).data == NULL)
            continue;
        delete (*itor).data;
        (*itor).clear();
    }
    if(m_shadersDir)
        delete m_shadersDir;
    CShaderManager::clear();
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderManager::initialize(void) {
    if(m_init) {
        FG_LOG_DEBUG("GFX: Shader Manager is already initialized");
        return FG_TRUE;
    }
    FG_LOG_DEBUG("GFX: Initializing Shader Manager...");

    // Will now initialize the builtin default shader program - it is not loaded
    // from configs or source file on disk/ROM
    ShadingLangVersion slVersion = context::getSLVersion();
    CShaderProgram *defaultProgram = new CShaderProgram();
    defaultProgram->setName("DefaultShader"); // #FIXME - const name
    defaultProgram->setFilePath("DefaultShader");
    CShaderProgram::attributeBindVec &attrBinds = defaultProgram->getRefAttrBinds();
    CShaderProgram::uniformBindVec &uniformBinds = defaultProgram->getRefUniformBinds();
    CShaderProgram::shaderVec & shaderVec = defaultProgram->getRefShaderVec();
    char *sourceFragment = fgMalloc<char>(2048);
    char *sourceVertex = fgMalloc<char>(2048);

    // DEFAULT FRAGMENT SHADER SOURCE BUFFER
    strcpy(sourceFragment, "#ifdef FG_GFX_ESSL_PRECISION_DEF\n"
           "precision highp float;\n"
           "varying highp vec3 v_position;\n"
           "varying highp vec2 v_texCoord;\n"
           "varying highp vec4 v_color;\n"
           "uniform mediump vec4  u_CustomColor;\n"
           "#else\n"
           "varying vec3 v_position;\n"
           "varying vec2 v_texCoord;\n"
           "varying vec4 v_color;\n"
           "uniform vec4  u_CustomColor;\n"
           "#endif\n"
           "uniform sampler2D s_texture;\n"
           "uniform float u_useTexture;\n"
           "void main() {\n"
           "	vec4 texel;\n"
           "	if(u_useTexture > 0.5) {\n"
           "		texel = texture2D(s_texture, v_texCoord);\n"
           "	} else {\n"
           "		texel = vec4(1.0, 1.0, 1.0, 1.0);\n"
           "	}\n"
           "	gl_FragColor = texel; \n"
           "}\n\0");

    // DEFAULT VERTEX SHADER SOURCE BUFFER
    strcpy(sourceVertex, "#ifdef FG_GFX_ESSL_PRECISION_DEF\n"
           "precision highp float;\n"
           "varying highp vec3 v_position;\n"
           "varying highp vec2 v_texCoord;\n"
           "varying highp vec4 v_color;\n"
           "#else\n"
           "varying vec3 v_position;\n"
           "varying vec2 v_texCoord;\n"
           "varying vec4 v_color;\n"
           "#endif\n"
           "uniform mat4 u_mvpMatrix;\n"
           "attribute vec4 a_position; \n"
           "attribute vec2 a_texCoord;\n"
           "attribute vec4 a_color;\n"
           "void main() {\n"
           "	gl_Position = u_mvpMatrix * a_position;\n"
           "	v_position = a_position.xyz;\n"
           "	v_texCoord = a_texCoord;\n"
           "	v_color = a_color;\n"
           "}\n\0");

    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID] = new CShader(ShaderType::FG_GFX_SHADER_FRAGMENT);
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID] = new CShader(ShaderType::FG_GFX_SHADER_VERTEX);

    ////////////////////////////////////////////////////////////////////////////
    // FRAGMENT SHADER
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setVersion(slVersion);
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setName("DefaultShader");
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setFilePath("no_path");
    if(slVersion == FG_GFX_ESSL_100 || slVersion == FG_GFX_ESSL_300) {
        shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->appendDefine(SShaderConstantDef("FG_GFX_ESSL_PRECISION_DEF", FG_TRUE));
    }
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setSourceBuffer(sourceFragment);

    ////////////////////////////////////////////////////////////////////////////
    // VERTEX SHADER
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setVersion(slVersion);
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setName("DefaultShader");
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setFilePath("no_path");
    if(slVersion == FG_GFX_ESSL_100 || slVersion == FG_GFX_ESSL_300) {
        shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->appendDefine(SShaderConstantDef("FG_GFX_ESSL_PRECISION_DEF", FG_TRUE));
    }
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setSourceBuffer(sourceVertex);

    attrBinds.push_back(SAttributeBind("a_position", AttributeType::FG_GFX_POSITION));
    attrBinds.push_back(SAttributeBind("a_texCoord", AttributeType::FG_GFX_TEXTURE_COORD));
    attrBinds.push_back(SAttributeBind("a_color", AttributeType::FG_GFX_COLOR));

    uniformBinds.push_back(SUniformBind("u_mvpMatrix", UniformType::FG_GFX_MVP_MATRIX));
    uniformBinds.push_back(SUniformBind("u_CustomColor", UniformType::FG_GFX_CUSTOM_COLOR));
    uniformBinds.push_back(SUniformBind("u_useTexture", UniformType::FG_GFX_USE_TEXTURE));
    uniformBinds.push_back(SUniformBind("s_texture", UniformType::FG_GFX_PLAIN_TEXTURE));

    defaultProgram->m_isPreLoaded = FG_TRUE;

    if(!defaultProgram->compile()) {
        FG_LOG_ERROR("GFX: Unable to compile default built-in shader program");
    }

    if(!defaultProgram->link()) {
        FG_LOG_ERROR("GFX: Unable to link default built-in shader program");
    }

    if(!insertProgram(defaultProgram)) {
        releaseHandle(defaultProgram->getHandle());
        delete defaultProgram;
        defaultProgram = NULL;
        FG_LOG_ERROR("GFX: Unable to insert default built-in shader program into the Manager");
    } else {
        useProgram(defaultProgram);
        defaultProgram->setUniform(UniformType::FG_GFX_USE_TEXTURE, 1.0f);
        defaultProgram->setUniform(UniformType::FG_GFX_PLAIN_TEXTURE, 0);
    }

    m_init = FG_TRUE;
    return m_init; //preLoadShaders(); // ?
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderManager::preLoadShaders(void) {
    if(!m_init)
        return FG_FALSE;
    if(m_isPreloadDone)
        return FG_TRUE;
    if(m_shadersPath.empty()) {
        FG_LOG_ERROR("GFX: Shaders path is not set");
        return FG_FALSE;
    }
    if(!m_shadersDir) {
        m_shadersDir = new util::CDirent();
    }
    FG_LOG_DEBUG("GFX: Pre-loading any required/available shader programs");
    m_shadersDir->clearList();
    m_shadersDir->readDir(m_shadersPath, FG_TRUE);
    m_shadersDir->rewind();

    std::string filePath;
    std::string pattern;
    pattern = "*";
    pattern.append(FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX);

    CStringVector shProgramCfgs;
    m_shadersDir->rewind();
    while(m_shadersDir->searchForFile(filePath, m_shadersPath, pattern, FG_FALSE).length()) {
        shProgramCfgs.push_back(filePath);
    }
    /*while((filename = m_shadersDir->getNextFile()) != NULL) {
        const char *ext = fgPath::fileExt(filename, FG_TRUE);
        if(!ext)
            continue;
        if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX) == 0) {
            shProgramCfgs.push_back(fgPath::join(m_shadersPath, std::string(filename)));
        }
    }*/    
    unsigned short int count = 0;
    CStringVector::iterator begin, end, itor;
    begin = shProgramCfgs.begin();
    end = shProgramCfgs.end();
    itor = begin;
    for(; itor != end; itor++) {
        CShaderProgram *pProgram = new CShaderProgram();
        if(!pProgram->preLoadConfig(*itor)) {
            delete pProgram;
            pProgram = NULL;
            continue;
        }
        if(!insertProgram(pProgram)) {
            releaseHandle(pProgram->getHandle());
            delete pProgram;
            pProgram = NULL;
            continue;
        }
        count++;
    }
    shProgramCfgs.clear_optimised();
    m_isPreloadDone = FG_TRUE;
    FG_LOG_DEBUG("GFX: ShaderManager: cached %d shader programs", count);
    if(!count) {
        FG_LOG_DEBUG("GFX: ShaderManager: no shader programs found - is there a problem with assets?");
        return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * 
 * @param pProgram
 * @param nameTag
 * @return 
 */
fgBool gfx::CShaderManager::insert(CShaderProgram *pProgram, const std::string& nameTag) {
    if(!pProgram)
        return FG_FALSE;
    if(base_type::insert(pProgram, nameTag)) {
        pProgram->setName(nameTag); // ?
        pProgram->setManaged(FG_TRUE);
        pProgram->setManager(this);
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @param pProgram
 * @return 
 */
fgBool gfx::CShaderManager::insertProgram(CShaderProgram *pProgram) {
    return insert(pProgram, pProgram->getName());
}

/**
 * 
 * @param info
 * @return 
 */
gfx::CShaderProgram *gfx::CShaderManager::request(const std::string& info) {
    if(!m_shadersDir || !m_init || info.empty())
        return NULL;
    CShaderProgram *shaderPtr = NULL;
    // This is a fallback
    shaderPtr = CShaderManager::get(info);
    if(shaderPtr) {
        return shaderPtr;
    }
    // info cannot be a path, it has to be resource name or config name
    // required file will be found
    if(strings::containsChars(info, std::string("/\\"))) {
        FG_LOG_ERROR("GFX: ShaderManager: Request cannot contain full path: '%s'", info.c_str());
        return NULL;
    }

    std::string pattern;
    std::string filePath;
    fgBool infoAsName = FG_FALSE;
    fgBool isFound = FG_FALSE;
    fgBool isConfig = FG_FALSE;

    const char *iext = path::fileExt(info.c_str(), FG_TRUE);
    if(!iext) { // no extension given so... search all
        infoAsName = FG_TRUE;
        pattern.append(info).append(".*;");
    } else { // extension is given, search for exact file
        pattern.append(info);
    }

    // Search file names of shaders already in cache
    if(!infoAsName && iext) {
        // This is special search for filename within already loaded shaders
        ProgramVecItor it = getRefDataVector().begin(), end = getRefDataVector().end();
        for(; it != end; it++) {
            CShaderProgram *program = (*it).data;
            if(!program)
                continue;
            CShaderProgram::FileMapping &files = program->getFileMapping();
            CShaderProgram::FileMappingItor fit = files.begin(), fend = files.end();
            for(; fit != fend; fit++) {
                // Comparing using endsWith - resource contains relative file paths
                // not just file name - this request function takes in just file names
                // resource names or patterns (wildcards for extensions)
                if(strings::stristr(fit->second, pattern)) {
                    const char *shext = path::fileExt(fit->second.c_str(), FG_TRUE);
                    if(strings::isEqual(shext, iext, FG_FALSE)) {
                        //if(fit->second.compare(pattern) == 0) {
                        // Found shader prox containing specified file
                        return program;
                    }
                }
            }
        }
    }

    m_shadersDir->rewind();
    while(m_shadersDir->searchForFile(filePath, "./", pattern, FG_TRUE).length()) {
        const char *fext = NULL;
        if(iext) {
            fext = iext;
        } else {
            fext = path::fileExt(filePath.c_str(), FG_TRUE);
        }

        if(strings::endsWith(fext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX, FG_TRUE)) {
            isConfig = FG_TRUE;
        }

        if(isConfig) {
            isFound = FG_TRUE;
            break;
        }
    };

    if(!isFound)
        return NULL;
    if(isConfig) {
        shaderPtr = new CShaderProgram();
        if(!shaderPtr->preLoadConfig(filePath)) {
            delete shaderPtr;
            shaderPtr = NULL;
            return NULL;
        }
    }
    if(shaderPtr) {
        if(!insertProgram(shaderPtr)) {
            releaseHandle(shaderPtr->getHandle());
            delete shaderPtr;
            shaderPtr = NULL;
            return NULL;
        }
    }

    return shaderPtr;
}

/**
 * 
 * @param info
 * @return 
 */
gfx::CShaderProgram *gfx::CShaderManager::request(const char *info) {
    return request(std::string(info));
}

/**
 * 
 * @param pProgram
 */
void gfx::CShaderManager::setInternalCurrentProgram(CShaderProgram* pProgram) {
    if(!pProgram)
        return;
    m_currentProgram = pProgram;
}


/**
 * 
 * @return 
 */
gfx::CShaderProgram *gfx::CShaderManager::getCurrentProgram(void) const {
    return m_currentProgram;
}

/**
 * 
 * @param path
 */
void gfx::CShaderManager::setShadersPath(const std::string &path) {
    m_shadersPath = path;
    if(m_shadersPath.empty()) {
        m_shadersPath = "./";
        return;
    }
    if(m_shadersPath[0] != '.') {
        if(m_shadersPath[0] == '/' || m_shadersPath[0] == '\\')
            m_shadersPath.insert(m_shadersPath.begin(), 1, '.');
        else
            m_shadersPath.insert(0, "./");
    }
}

/**
 * 
 * @param path
 */
void gfx::CShaderManager::setShadersPath(const char *path) {
    if(!path) {
        m_shadersPath = "./";
        return;
    }
    m_shadersPath = path;
    if(m_shadersPath[0] != '.') {
        if(m_shadersPath[0] == '/' || m_shadersPath[0] == '\\')
            m_shadersPath.insert(m_shadersPath.begin(), 1, '.');
        else
            m_shadersPath.insert(0, "./");
    }
    FG_LOG_DEBUG("GFX:%s: Set shaders path to: '%s'", tag_type::name(), m_shadersPath.c_str());
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderManager::compileShaders(void) {
    if(!m_init) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    ProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        CShaderProgram *pProgram = (*itor).data;
        if(!pProgram)
            continue;
        if(!pProgram->compile()) {
            status = FG_FALSE;
        }
    }
    if(status)
        FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "All shader programs compiled successfully");
    else
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_OK, "Problem occurred when compiling shader programs");
    return status;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderManager::linkShaders(void) {
    if(!m_init) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    ProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        CShaderProgram *pProgram = (*itor).data;
        if(!pProgram)
            continue;
        if(!pProgram->link()) {
            status = FG_FALSE;
        }
    }
    if(status)
        FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "All shader programs linked successfully");
    else
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_OK, "Problem occurred when linking shader programs");
    return status;
}

/**
 * 
 * @return 
 */
fgBool gfx::CShaderManager::allReleaseGFX(void) {
    if(!m_init) {
        return FG_FALSE; // ERROR ?
    }
    fgBool status = FG_TRUE;
    ProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        CShaderProgram *pProgram = (*itor).data;
        if(!pProgram)
            continue;
        if(!pProgram->releaseGFX()) {
            status = FG_FALSE;
        }
    }
    if(status)
        FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "All shader programs released successfully");
    else
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_OK, "Problem occurred when releasing shader programs");
    return status;
}

/**
 * 
 * @param pProgram
 * @return 
 */
fgBool gfx::CShaderManager::useProgram(CShaderProgram *pProgram) {
    if(!pProgram)
        return FG_FALSE;
    if(pProgram->use()) {
        m_currentProgram = pProgram;
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @param spUniqueID
 * @return 
 */
fgBool gfx::CShaderManager::useProgram(ShaderHandle spUniqueID) {
    gfx::CShaderProgram *pProgram = dereference(spUniqueID);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(pProgram == m_currentProgram)
        return FG_FALSE;
    m_currentProgram = pProgram;
    return pProgram->use();
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CShaderManager::useProgram(const std::string &nameTag) {
    gfx::CShaderProgram *pProgram = dereference(nameTag);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(pProgram == m_currentProgram)
        return FG_FALSE;
    m_currentProgram = pProgram;
    return pProgram->use();
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CShaderManager::useProgram(const char *nameTag) {
    gfx::CShaderProgram *pProgram = dereference(nameTag);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(pProgram == m_currentProgram)
        return FG_FALSE;
    m_currentProgram = pProgram;
    return pProgram->use();
}

/**
 * 
 * @param pProgram
 * @return 
 */
fgBool gfx::CShaderManager::isProgramUsed(gfx::CShaderProgram *pProgram) {
    if(m_currentProgram && m_currentProgram == pProgram) {
        //if(m_currentProgram->getGfxID() == pProgram->getGfxID())
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @param spUniqueID
 * @return 
 */
fgBool gfx::CShaderManager::isProgramUsed(ShaderHandle spUniqueID) {
    gfx::CShaderProgram *pProgram = dereference(spUniqueID);
    return CShaderManager::isProgramUsed(pProgram);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CShaderManager::isProgramUsed(const std::string &nameTag) {
    CShaderProgram *pProgram = dereference(nameTag);
    return CShaderManager::isProgramUsed(pProgram);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CShaderManager::isProgramUsed(const char *nameTag) {
    CShaderProgram *pProgram = dereference(nameTag);
    return CShaderManager::isProgramUsed(pProgram);
}
