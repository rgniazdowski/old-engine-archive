/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderManager.h"
#include "GFX/fgGFXErrorCodes.h"
#include "Util/fgFile.h"
#include "Util/fgDirent.h"
#include "Util/fgStrings.h"

/*
 *
 */
fgGfxShaderManager::fgGfxShaderManager() :
m_currentProgram(NULL),
m_shadersDir(NULL),
m_shadersPath(),
m_isPreloadDone(FG_FALSE) {
    m_shadersDir = new fgDirent();
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_init = FG_FALSE;
}

/*
 *
 */
fgGfxShaderManager::~fgGfxShaderManager() {
    destroy();
}

/*
 *
 */
void fgGfxShaderManager::clear(void) {
    m_currentProgram = NULL;
    m_shadersPath.clear();
    releaseAllHandles();
    m_managerType = FG_MANAGER_GFX_SHADER;
    m_shadersDir = NULL;
    m_init = FG_FALSE;
    m_isPreloadDone = FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderManager::destroy(void) {
    smProgramVec & data = getRefDataVector();
    hmDataVecItor begin = data.begin(), end = data.end(), itor = begin;
    for(; itor != end; ++itor) {
        if((*itor) == NULL)
            continue;
        delete (*itor);
        *itor = NULL;
    }
    if(m_shadersDir)
        delete m_shadersDir;
    fgGfxShaderManager::clear();
    return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderManager::initialize(void) {
    if(m_init) {
        FG_LOG_DEBUG("GFX: Shader Manager is already initialized");
        return FG_TRUE;
    }
    FG_LOG_DEBUG("GFX: Initializing Shader Manager...");
    if(!m_shadersDir)
        m_shadersDir = new fgDirent();
    m_shadersDir->clearList();
    m_shadersDir->readDirectory(m_shadersPath, FG_TRUE);
    m_shadersDir->rewind();
    m_init = FG_TRUE;
    return m_init;//preLoadShaders(); // ?
}

/*
 *
 */
fgBool fgGfxShaderManager::preLoadShaders(void) {
    if(!m_init)
        return FG_FALSE;
    if(m_isPreloadDone)
        return FG_TRUE;
    if(m_shadersPath.empty()) {
        FG_LOG_ERROR("GFX: Shaders path is not set");
        return FG_FALSE;
    }
    if(!m_shadersDir) {
        FG_LOG_ERROR("GFX: Shaders directory reader is not ready");
        return FG_FALSE;
    }
    FG_LOG_DEBUG("GFX: Pre-loading any required/available shader programs");
    std::string filePath;
    std::string pattern;
    pattern = "*";
    pattern.append(FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX);

    fgStringVector shProgramCfgs;
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
    fgStringVector::iterator begin, end, itor;
    begin = shProgramCfgs.begin();
    end = shProgramCfgs.end();
    itor = begin;
    for(; itor != end; itor++) {
        fgGfxShaderProgram *pProgram = new fgGfxShaderProgram();
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
    if(!count)
        return FG_FALSE;
    return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderManager::insert(fgGfxShaderProgram *pProgram, const std::string& nameTag) {
    if(!pProgram)
        return FG_FALSE;
    if(fgDataManagerBase::insert(pProgram, nameTag)) {
        pProgram->setName(nameTag); // ?
        pProgram->setManaged(FG_TRUE);
        pProgram->setManager(this);
        return FG_TRUE;
    }
    return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderManager::insertProgram(fgGfxShaderProgram *pProgram) {
    return insert(pProgram, pProgram->getName());
}

/*
 *
 */
fgGfxShaderProgram *fgGfxShaderManager::request(const std::string& info) {
    if(!m_shadersDir || !m_init || info.empty())
        return NULL;
    fgGfxShaderProgram *shaderPtr = NULL;
    // This is a fallback
    shaderPtr = fgGfxShaderManager::get(info);
    if(shaderPtr) {
        return shaderPtr;
    }
    // info cannot be a path, it has to be resource name or config name
    // required file will be found
    if(fgStrings::containsChars(info, std::string("/\\"))) {
        FG_LOG_ERROR("GFX: ShaderManager: Request cannot contain full path: '%s'", info.c_str());
        return NULL;
    }

    std::string pattern;
    std::string filePath;
    fgBool infoAsName = FG_FALSE;
    fgBool isFound = FG_FALSE;
    fgBool isConfig = FG_FALSE;

    const char *iext = fgPath::fileExt(info.c_str(), FG_TRUE);
    if(!iext) { // no extension given so... search all
        infoAsName = FG_TRUE;
        pattern.append(info).append(".*;");
    } else { // extension is given, search for exact file
        pattern.append(info);
    }

    // Search file names of shaders already in cache
    if(!infoAsName && iext) {
        // This is special search for filename within already loaded shaders
        smProgramVecItor it = getRefDataVector().begin(), end = getRefDataVector().end();
        for(; it != end; it++) {
            fgGfxShaderProgram *program = (*it);
            if(!program)
                continue;
            fgGfxShaderProgram::fileMapping &files = program->getFileMapping();
            fgGfxShaderProgram::fileMappingItor fit = files.begin(), fend = files.end();
            for(; fit != fend; fit++) {
                // Comparing using endsWith - resource contains relative file paths
                // not just file name - this request function takes in just file names
                // resource names or patterns (wildcards for extensions)
                if(fgStrings::stristr(fit->second, pattern)) {
                    const char *shext = fgPath::fileExt(fit->second.c_str(), FG_TRUE);
                    if(fgStrings::isEqual(shext, iext, FG_FALSE)) {
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
            fext = fgPath::fileExt(filePath.c_str(), FG_TRUE);
        }

        if(fgStrings::endsWith(fext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX, FG_TRUE)) {
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
        shaderPtr = new fgGfxShaderProgram();
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

/*
 *
 */
fgGfxShaderProgram *fgGfxShaderManager::request(const char *info) {
    return request(std::string(info));
}

/*
 *
 */
fgGfxShaderProgram *fgGfxShaderManager::getCurrentProgram(void) const {
    return m_currentProgram;
}

/*
 *
 */
void fgGfxShaderManager::setShadersPath(const std::string &path) {
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

/*
 *
 */
void fgGfxShaderManager::setShadersPath(const char *path) {
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
}

/*
 *
 */
fgBool fgGfxShaderManager::compileShaders(void) {
    if(!m_init) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    smProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        fgGfxShaderProgram *pProgram = *itor;
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

/*
 *
 */
fgBool fgGfxShaderManager::linkShaders(void) {
    if(!m_init) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    smProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        fgGfxShaderProgram *pProgram = *itor;
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

/*
 *
 */
fgBool fgGfxShaderManager::allReleaseGFX(void) {
    if(!m_init) {
        return FG_FALSE; // ERROR ?
    }
    fgBool status = FG_TRUE;
    smProgramVecItor end, itor;
    end = getRefDataVector().end();
    itor = getRefDataVector().begin();
    for(; itor != end; itor++) {
        fgGfxShaderProgram *pProgram = *itor;
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

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(fgGfxShaderProgram *pProgram) {
    if(!pProgram)
        return FG_FALSE;
    if(pProgram->use()) {
        m_currentProgram = pProgram;
        return FG_TRUE;
    }
    return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(fgGfxShaderHandle spUniqueID) {
    fgGfxShaderProgram *pProgram = dereference(spUniqueID);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(pProgram == m_currentProgram)
        return FG_FALSE;
    m_currentProgram = pProgram;
    return pProgram->use();
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(const std::string &nameTag) {
    fgGfxShaderProgram *pProgram = dereference(nameTag);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(pProgram == m_currentProgram)
        return FG_FALSE;
    m_currentProgram = pProgram;
    return pProgram->use();
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(const char *nameTag) {
    fgGfxShaderProgram *pProgram = dereference(nameTag);
    if(!pProgram) {
        return FG_FALSE;
    }
    if(pProgram == m_currentProgram)
        return FG_FALSE;
    m_currentProgram = pProgram;
    return pProgram->use();
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(fgGfxShaderProgram *pProgram) {
    if(m_currentProgram && m_currentProgram == pProgram) {
        if(m_currentProgram->getGfxID() == pProgram->getGfxID())
            return FG_TRUE;
    }
    return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(fgGfxShaderHandle spUniqueID) {
    fgGfxShaderProgram *pProgram = dereference(spUniqueID);
    return fgGfxShaderManager::isProgramUsed(pProgram);
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(const std::string &nameTag) {
    fgGfxShaderProgram *pProgram = dereference(nameTag);
    return fgGfxShaderManager::isProgramUsed(pProgram);
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(const char *nameTag) {
    fgGfxShaderProgram *pProgram = dereference(nameTag);
    return fgGfxShaderManager::isProgramUsed(pProgram);
}
