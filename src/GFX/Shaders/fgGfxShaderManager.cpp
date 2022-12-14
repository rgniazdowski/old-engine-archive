/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxShaderManager.h"
#include "GFX/fgGfxErrorCodes.h"
#include "Util/fgRegularFile.h"
#include "Util/fgDirent.h"
#include "Util/fgStrings.h"
#include "Util/fgMemory.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CShaderManager::CShaderManager() :
base_type(),
m_shaderObjectsHolder(this),
m_uniformUpdater(),
m_currentProgram(NULL),
m_shadersDir(NULL),
m_shadersPath(),
m_stateFlags(NO_FLAGS) {
    m_shadersDir = new util::CDirent();
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_init = FG_FALSE;
}
//------------------------------------------------------------------------------

gfx::CShaderManager::~CShaderManager() {
    destroy();
}
//------------------------------------------------------------------------------

void gfx::CShaderManager::clear(void) {
    m_currentProgram = NULL;
    m_shadersPath.clear();
    releaseAllHandles();
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_shadersDir = NULL;
    m_init = FG_FALSE;
    setFlag(PRELOAD_DONE, FG_FALSE);
    m_shaderObjectsHolder.clear();
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::destroy(void) {
    ProgramVec& data = getRefDataVector();
    DataVecItor begin = data.begin(), end = data.end(), itor = begin;
    for(; itor != end; ++itor) {
        if((*itor).data == NULL)
            continue;
        delete (*itor).data;
        (*itor).clear();
    }
    if(m_shadersDir)
        delete m_shadersDir;
    m_shaderObjectsHolder.destroy();
    self_type::clear();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

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
    defaultProgram->setUsage(shaders::USAGE_FALLBACK_BIT | shaders::USAGE_DEFAULT_BIT);
    defaultProgram->setFilePath("DefaultShader");
    CShaderProgram::AttributeBindVec attrBinds;
    CShaderProgram::UniformBindVec uniformBinds;
    CShaderProgram::ShaderVec& shaderVec = defaultProgram->getShaders();
    char *sourceFragment = fgMalloc<char>(2048);
    char *sourceVertex = fgMalloc<char>(2048);
    attrBinds.reserve(4);
    uniformBinds.reserve(4);

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
           "		texel = v_color;\n"
           "	}\n"
           "	gl_FragColor = texel * u_CustomColor; \n"
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

    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID] = new CShader(shaders::SHADER_FRAGMENT);
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID] = new CShader(shaders::SHADER_VERTEX);

    ////////////////////////////////////////////////////////////////////////////
    // FRAGMENT SHADER
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setVersion(slVersion);
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setUsage(shaders::USAGE_FALLBACK_BIT | shaders::USAGE_DEFAULT_BIT);
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setName("DefaultShader.Fragment");
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setFilePath("no_path");
    if(slVersion == FG_GFX_ESSL_100 || slVersion == FG_GFX_ESSL_300) {
        shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->appendDefine(SShaderConstantDef("FG_GFX_ESSL_PRECISION_DEF", FG_TRUE));
    }
    shaderVec[CShaderProgram::SP_FRAGMENT_SHADER_ID]->setSourceBuffer(sourceFragment);

    ////////////////////////////////////////////////////////////////////////////
    // VERTEX SHADER
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setVersion(slVersion);
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setUsage(shaders::USAGE_FALLBACK_BIT | shaders::USAGE_DEFAULT_BIT);
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setName("DefaultShader.Vertex");
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setFilePath("no_path");
    if(slVersion == FG_GFX_ESSL_100 || slVersion == FG_GFX_ESSL_300) {
        shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->appendDefine(SShaderConstantDef("FG_GFX_ESSL_PRECISION_DEF", FG_TRUE));
    }
    shaderVec[CShaderProgram::SP_VERTEX_SHADER_ID]->setSourceBuffer(sourceVertex);

    attrBinds.push_back(SAttributeBind("a_position", AttributeType::ATTRIBUTE_POSITION));
    attrBinds.push_back(SAttributeBind("a_texCoord", AttributeType::ATTRIBUTE_TEXTURE_COORD));
    attrBinds.push_back(SAttributeBind("a_color", AttributeType::ATTRIBUTE_COLOR));
    defaultProgram->appendAttributeBinds(attrBinds);

    uniformBinds.push_back(SUniformBind("u_mvpMatrix", shaders::UNIFORM_MVP_MATRIX));
    uniformBinds.push_back(SUniformBind("u_CustomColor", shaders::UNIFORM_CUSTOM_COLOR));
    uniformBinds.push_back(SUniformBind("u_useTexture", shaders::UNIFORM_USE_TEXTURE));
    uniformBinds.push_back(SUniformBind("s_texture", shaders::UNIFORM_PLAIN_TEXTURE));
    defaultProgram->appendUniformBinds(uniformBinds);

    defaultProgram->setPreloaded(FG_TRUE);

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
        defaultProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, 1.0f);
        defaultProgram->setUniform(shaders::UNIFORM_PLAIN_TEXTURE, 0);
    }

    m_init = FG_TRUE;
    m_shaderObjectsHolder.initialize();
    return m_init;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::preLoadShaders(void) {
    if(!m_init)
        return FG_FALSE;
    if(isPreloadDone())
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
    pattern.append(shaders::getShaderProgramConfigSuffix());

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
        // force manage flags - for pushing CShader* objects
        pProgram->setManaged(FG_TRUE);
        pProgram->setManager(this);
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
        {
            // special operation so that shader program will check
            // if it can push it's shader objects into the manager
        }
        count++;
    }
    shProgramCfgs.clear_optimised();
    setFlag(PRELOAD_DONE, FG_TRUE);
    FG_LOG_DEBUG("GFX: ShaderManager: cached %d shader programs", count);
    if(!count) {
        FG_LOG_DEBUG("GFX: ShaderManager: no shader programs found - is there a problem with assets?");
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::insert(CShaderProgram *pProgram, const std::string& nameTag) {
    if(!pProgram)
        return FG_FALSE;
    if(base_type::insert(pProgram, nameTag)) {
        pProgram->setManaged(FG_TRUE);
        pProgram->setManager(this);
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::insertProgram(CShaderProgram *pProgram) {
    if(!pProgram)
        return FG_FALSE;
    return insert(pProgram, pProgram->getName());
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::remove(const ShaderHandle& rhUniqueID) {
    return remove(base_type::get(rhUniqueID));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::remove(const std::string& nameTag) {
    return remove(base_type::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::remove(const char *nameTag) {
    return remove(base_type::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::remove(CShaderProgram* pProgram) {
    if(!base_type::isManaged(pProgram))
        return FG_FALSE;
    releaseHandle(pProgram->getHandle());
    pProgram->setManaged(FG_FALSE);
    pProgram->setManager(NULL);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

gfx::CShaderManager::CShaderObjectManager::CShaderObjectManager(CShaderManager* pShaderMgr) :
base_type(),
m_pShaderMgr(pShaderMgr) {
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_init = FG_FALSE;
}
//------------------------------------------------------------------------------

gfx::CShaderManager::CShaderObjectManager::~CShaderObjectManager() {
    destroy();
}
//------------------------------------------------------------------------------

void gfx::CShaderManager::CShaderObjectManager::clear(void) {
    releaseAllHandles();
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_init = FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::destroy(void) {
    ShaderVec& data = getRefDataVector();
    ShaderVecItor begin = data.begin(), end = data.end(), itor = begin;
    for(; itor != end; ++itor) {
        if((*itor).data == NULL)
            continue;
        delete (*itor).data;
        (*itor).clear();
    }
    self_type::clear();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::initialize(void) {
    // nothing to initialize here
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::insert(CShader* pShader, const std::string& nameTag) {
    if(!pShader)
        return FG_FALSE;
    if(nameTag.empty())
        return FG_FALSE;
    if(base_type::insert(pShader, nameTag)) {
        pShader->setManaged(FG_TRUE);
        pShader->setManager(this);
        return FG_TRUE;
    }
    return FG_FALSE;

}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::insertShader(CShader* pShader) {
    if(!pShader)
        return FG_FALSE;
    return insert(pShader, pShader->getName());
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::remove(const ShaderHandle& rhUniqueID) {
    return remove(base_type::get(rhUniqueID));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::remove(const std::string& nameTag) {
    return remove(base_type::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::remove(const char *nameTag) {
    return remove(base_type::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::CShaderObjectManager::remove(CShader* pShader) {
    if(!base_type::isManaged(pShader))
        return FG_FALSE;
    releaseHandle(pShader->getHandle());
    pShader->setManaged(FG_FALSE);
    pShader->setManager(NULL);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::CShaderObjectManager::request(const std::string& info) {
    // #TODO - implementation
    // here will be specific code that normally is in shader program pre load config
    // need to merge this stuff up!
    // #TODO:2 - also now with special UsageMask flags for shader/shader programs
    // need to check whether the info contains specific usage mask string names
    // which can be separated by ' '(space) or ';', '|', ','
    return NULL;
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::CShaderObjectManager::request(const char* info) {
    if(!info)
        return NULL;
    if(!info[0])
        return NULL;
    return this->request(std::string(info));
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::CShaderObjectManager::request(shaders::UsageMask usageMask) {
    // #TODO - implementation of shader object request feature
    return NULL;
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::CShaderObjectManager::getShaderByPath(const std::string& filePath) {
    if(filePath.empty())
        return NULL;
    CShader* pResult = NULL;
    const char *iext = path::fileExt(filePath.c_str(), FG_TRUE);
    ShaderVec& data = getRefDataVector();
    ShaderVecItor begin = data.begin(), end = data.end(), itor = begin;
    for(; itor != end; ++itor) {
        if((*itor).data == NULL)
            continue;

        CShader* pShader = (*itor).data;
        if(pShader->getFilePath().compare(filePath) == 0) {
            pResult = pShader;
            break;
        }
        const char* pFileName = path::fileName(filePath.c_str());
        if(!pFileName)
            continue;
        if(strings::endsWith(pShader->getFilePath(), pFileName)) {
            pResult = pShader;
            break;
        }
        CShader::FileMapping &files = pShader->getFileMapping();
        CShader::FileMappingItor fit = files.begin(), fend = files.end();
        for(; fit != fend; fit++) {
            // Comparing using endsWith - resource contains relative file paths
            // not just file name - this request function takes in just file names
            // resource names or patterns (wildcards for extensions)
            if(strings::stristr(fit->second, pFileName)) {
                const char *shext = path::fileExt(fit->second.c_str(), FG_TRUE);
                if(strings::isEqual(shext, iext, FG_FALSE)) {
                    //if(fit->second.compare(pattern) == 0) {
                    // Found shader prox containing specified file
                    pResult = pShader;
                    break;
                }
            }
        }
        if(pResult)
            break;
    }

    return pResult;
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::CShaderObjectManager::getShaderByPath(const char* filePath) {
    if(!filePath)
        return NULL;
    return getShaderByPath(std::string(filePath));
}

fgBool gfx::CShaderManager::insertShader(CShader* pShader) {
    if(m_shaderObjectsHolder.isManaged(pShader)) {
        return FG_FALSE;
    }
    if(pShader->getName().empty()) {
        return FG_FALSE;
    }
    return m_shaderObjectsHolder.insert(pShader, pShader->getName());
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::getShaderByPath(const std::string& filePath) {
    return m_shaderObjectsHolder.getShaderByPath(filePath);
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::getShaderByPath(const char* filePath) {
    if(!filePath)
        return NULL;
    return m_shaderObjectsHolder.getShaderByPath(std::string(filePath));
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::isManaged(CShader* pShader) {
    return m_shaderObjectsHolder.isManaged(pShader);
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::remove(CShader* pShader) {
    return m_shaderObjectsHolder.remove(pShader);
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::destroyData(CShader*& pShader) {
    return m_shaderObjectsHolder.destroyData(pShader);
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::getShader(const ShaderHandle& dhUniqueID) {
    return m_shaderObjectsHolder.get(dhUniqueID);
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::getShader(const std::string& nameTag) {
    return m_shaderObjectsHolder.get(nameTag);
}
//------------------------------------------------------------------------------

gfx::CShader* gfx::CShaderManager::getShader(const char* nameTag) {
    return m_shaderObjectsHolder.get(nameTag);
}
//------------------------------------------------------------------------------

gfx::CShaderProgram* gfx::CShaderManager::request(const std::string& info) {
    if(!m_shadersDir || !m_init || info.empty())
        return NULL;
    CShaderProgram *pRequestedShader = CShaderManager::get(info);
    // info cannot be a path, it has to be resource name or config name
    // required file will be found
    if(strings::containsChars(info, std::string("/\\"))) {
        FG_LOG_ERROR("GFX: ShaderManager: Request cannot contain full path: '%s'", info.c_str());
        return NULL;
    }
    std::string pattern;
    std::string filePath;
    fgBool infoAsName = FG_FALSE;
    fgBool isFound = (fgBool)(pRequestedShader != NULL);
    fgBool isConfig = FG_FALSE;
    const char *iext = NULL;

    if(!pRequestedShader) {
        iext = path::fileExt(info.c_str(), FG_TRUE);
        if(!iext) { // no extension given so... search all
            infoAsName = FG_TRUE;
            pattern.append(info).append(".*;");
        } else { // extension is given, search for exact file
            pattern.append(info);
        }
    }
    // Search file names of shaders already in cache
    if(!infoAsName && iext && !pRequestedShader) {
        // This is special search for filename within already loaded shaders
        ProgramVecItor it = getRefDataVector().begin(), end = getRefDataVector().end();
        for(; it != end; it++) {
            CShaderProgram *pProgram = (*it).data;
            if(!pProgram)
                continue;
            CShaderProgram::FileMapping &files = pProgram->getFileMapping();
            CShaderProgram::FileMappingItor fit = files.begin(), fend = files.end();
            for(; fit != fend; fit++) {
                // Comparing using endsWith - resource contains relative file paths
                // not just file name - this request function takes in just file names
                // resource names or patterns (wildcards for extensions)
                if(!strings::stristr(fit->second, pattern)) {
                    continue;
                }
                const char *shext = path::fileExt(fit->second.c_str(), FG_TRUE);
                if(strings::isEqual(shext, iext, FG_FALSE)) {
                    //if(fit->second.compare(pattern) == 0) {
                    // Found shader prox containing specified file
                    pRequestedShader = pProgram;
                    isFound = FG_TRUE;
                    break;
                }
            }
        }
    }
    if(!isFound) {
        m_shadersDir->rewind();
        while(m_shadersDir->searchForFile(filePath, "./", pattern, FG_TRUE).length()) {
            const char *fext = NULL;
            if(iext) {
                fext = iext;
            } else {
                fext = path::fileExt(filePath.c_str(), FG_TRUE);
            }
            if(strings::endsWith(fext, shaders::getShaderProgramConfigSuffix(), FG_TRUE)) {
                isConfig = FG_TRUE;
            }
            if(isConfig) {
                isFound = FG_TRUE;
                break;
            }
        }
        if(!isFound)
            return NULL;
    }
    if(!pRequestedShader) {
        if(isConfig) {
            pRequestedShader = new CShaderProgram();
            pRequestedShader->setManaged(FG_TRUE);
            pRequestedShader->setManager(this);
            if(!pRequestedShader->preLoadConfig(filePath)) {
                delete pRequestedShader;
                pRequestedShader = NULL;
                return NULL;
            }
        }
        if(pRequestedShader && !insertProgram(pRequestedShader)) {
            releaseHandle(pRequestedShader->getHandle());
            delete pRequestedShader;
            pRequestedShader = NULL;
            return NULL;
        }
    }
    if(pRequestedShader) {
        // #FIXME - link on request/use/get should maybe throw some kind of event
        // this is for the future - compiling/linking should be done in special
        // place - can also throw proper event SHADER_LINK(?) to react properly
        if(isLinkOnRequest()) {
            // link will also call compile() if needed
            pRequestedShader->link();
        }
        if(isUseOnRequest()) {
            useProgram(pRequestedShader);
        }
    }
    return pRequestedShader;
}
//------------------------------------------------------------------------------

gfx::CShaderProgram* gfx::CShaderManager::request(const char* info) {
    if(!info)
        return NULL;
    if(!info[0])
        return NULL;
    return request(std::string(info));
}
//------------------------------------------------------------------------------

gfx::CShaderProgram* gfx::CShaderManager::request(shaders::UsageMask usageMask) {
    CShaderProgram* pResultShader = NULL;
    CShaderProgram* pSecondaryShader = NULL;
    if(usageMask == shaders::USAGE_EMPTY_BIT)
        return NULL;
    ProgramVecItor it = getRefDataVector().begin(), end = getRefDataVector().end();
    for(; it != end; it++) {
        CShaderProgram *pProgram = (*it).data;
        if(!pProgram)
            continue;
        // now simply need to check the andMask
        shaders::UsageMask andMask = usageMask & pProgram->getUsageMask();
        if(andMask == usageMask) {
            // found shader program has all needed usage mask flags
            // the best possible option, can stop search now
            pResultShader = pProgram;
            break;
        } else if(andMask != shaders::USAGE_EMPTY_BIT) {
            // this is secondary option, will try to find later
            // a better secondary option (with higher flag number)
            if(!pSecondaryShader) {
                pSecondaryShader = pProgram;
            } else {
                // already set, need to check flags
                shaders::UsageMask secondAndMask = pSecondaryShader->getUsageMask() & usageMask;
                if(shaders::getUsageMaskCount(secondAndMask) < shaders::getUsageMaskCount(andMask)) {
                    // currently visited program has better usage flags
                    // difference is lower so flags are more close to 'usageMask' value
                    // this is not accurate because values are not spread equally.
                    // Which flag is better? 1 + 2 + 32 OR 1 + 2 + 4 + 8 + 16
                    // Obviously the second one in this example, more flags by number
                    // can add counter function...
                    pSecondaryShader = pProgram;
                }
            }
        }
    }
    if(!pResultShader) {
        pResultShader = pSecondaryShader;
    }
    if(pResultShader && isLinkOnRequest()) {
        pResultShader->link();
    }
    return pResultShader;
}
//------------------------------------------------------------------------------

void gfx::CShaderManager::setInternalCurrentProgram(CShaderProgram* pProgram) {
    if(!pProgram)
        return;
    m_currentProgram = pProgram;
}
//------------------------------------------------------------------------------

gfx::CShaderProgram* gfx::CShaderManager::getCurrentProgram(void) const {
    return m_currentProgram;
}
//------------------------------------------------------------------------------

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
    FG_LOG_DEBUG("GFX:%s: Set shaders path to: '%s'", tag_type::name(), m_shadersPath.c_str());
}
//------------------------------------------------------------------------------

void gfx::CShaderManager::setShadersPath(const char* path) {
    if(!path) {
        m_shadersPath = "./";
        return;
    }
    m_shadersPath = path;
    if(m_shadersPath[0] != '.') {
        if(m_shadersPath[0] == '/' || m_shadersPath[0] == '\\') {
            m_shadersPath.insert(m_shadersPath.begin(), 1, '.');
        } else {
            m_shadersPath.insert(0, "./");
        }
    }
    FG_LOG_DEBUG("GFX:%s: Set shaders path to: '%s'", tag_type::name(), m_shadersPath.c_str());
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::compileShaders(fgBool recentOnly) {
    if(!m_init) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    int nCompiled = 0;
    ProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        CShaderProgram *pProgram = (*itor).data;
        if(!pProgram)
            continue;
        if(recentOnly && !(pProgram->wasRecentlyUsed() || pProgram->wasRecentlyLinked()))
            continue; // skip the ones that never were linked nor used
        if(!pProgram->compile()) {
            status = FG_FALSE;
        } else {
            nCompiled++;
        }
    }
    if(status) {
        FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "All shader programs compiled successfully");
    } else {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_OK, "Problem occurred when compiling shader programs");
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::linkShaders(fgBool recentOnly) {
    if(!m_init) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    int nLinked = 0;
    ProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        CShaderProgram *pProgram = (*itor).data;
        if(!pProgram)
            continue;
        if(recentOnly && !(pProgram->wasRecentlyUsed() || pProgram->wasRecentlyLinked()))
            continue; // skip the ones that never were compiled nor used
        if(!pProgram->link()) {
            status = FG_FALSE;
        } else {
            nLinked++;
        }
    }
    if(status) {
        FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "All shader programs linked successfully");
    } else {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_OK, "Problem occurred when linking shader programs");
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::getShaderNames(CStringVector& strVec) {
    strVec.clear();
    unsigned int nFound = 0;
    ProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        CShaderProgram *pProgram = (*itor).data;
        if(!pProgram) {
            continue;
        }
        strVec.push_back(pProgram->getName());
        nFound++;
    }
    return (fgBool)!!(nFound > 0);
}
//------------------------------------------------------------------------------

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
    if(status) {
        FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_GFX_OK, "All shader programs released successfully");
    } else {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_GFX_OK, "Problem occurred when releasing shader programs");
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::useProgram(CShaderProgram* pProgram) {
    if(!pProgram) {
        return FG_FALSE;
    }
    if(m_currentProgram == pProgram) {
        return FG_FALSE;
    }
    if(isLinkOnUse() && !pProgram->isLinked()) {
        if(!pProgram->compile()) {
            return FG_FALSE;
        }
        pProgram->link();
    }
    context::useProgram(pProgram->getGfxID());
    pProgram->setRecentlyUsed(FG_TRUE);
    m_currentProgram = pProgram;
    if(isUniformAutoUpdate())
        m_uniformUpdater.updateUniforms(m_currentProgram);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::useProgram(ShaderHandle spUniqueID) {
    gfx::CShaderProgram *pProgram = dereference(spUniqueID);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(m_currentProgram == pProgram) {
        return FG_FALSE;
    }
    if(isLinkOnUse() && !pProgram->isLinked()) {
        if(!pProgram->compile()) {
            return FG_FALSE;
        }
        pProgram->link();
    }
    context::useProgram(pProgram->getGfxID());
    pProgram->setRecentlyUsed(FG_TRUE);
    m_currentProgram = pProgram;
    if(isUniformAutoUpdate())
        m_uniformUpdater.updateUniforms(m_currentProgram);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::useProgram(const std::string &nameTag) {
    gfx::CShaderProgram *pProgram = dereference(nameTag);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(m_currentProgram == pProgram) {
        return FG_FALSE;
    }
    if(isLinkOnUse() && !pProgram->isLinked()) {
        if(!pProgram->compile()) {
            return FG_FALSE;
        }
        pProgram->link();
    }
    context::useProgram(pProgram->getGfxID());
    pProgram->setRecentlyUsed(FG_TRUE);
    m_currentProgram = pProgram;
    if(isUniformAutoUpdate())
        m_uniformUpdater.updateUniforms(m_currentProgram);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::useProgram(const char *nameTag) {
    gfx::CShaderProgram *pProgram = dereference(nameTag);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(m_currentProgram == pProgram) {
        return FG_FALSE;
    }
    if(isLinkOnUse() && !pProgram->isLinked()) {
        if(!pProgram->compile()) {
            return FG_FALSE;
        }
        pProgram->link();
    }
    context::useProgram(pProgram->getGfxID());
    pProgram->setRecentlyUsed(FG_TRUE);
    m_currentProgram = pProgram;
    if(isUniformAutoUpdate())
        m_uniformUpdater.updateUniforms(m_currentProgram);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::isProgramUsed(gfx::CShaderProgram *pProgram) {
    if(m_currentProgram && m_currentProgram == pProgram) {
        //if(m_currentProgram->getGfxID() == pProgram->getGfxID())
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::isProgramUsed(ShaderHandle spUniqueID) {
    gfx::CShaderProgram *pProgram = dereference(spUniqueID);
    return CShaderManager::isProgramUsed(pProgram);
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::isProgramUsed(const std::string &nameTag) {
    CShaderProgram *pProgram = dereference(nameTag);
    return CShaderManager::isProgramUsed(pProgram);
}
//------------------------------------------------------------------------------

fgBool gfx::CShaderManager::isProgramUsed(const char *nameTag) {
    CShaderProgram *pProgram = dereference(nameTag);
    return CShaderManager::isProgramUsed(pProgram);
}
//------------------------------------------------------------------------------
