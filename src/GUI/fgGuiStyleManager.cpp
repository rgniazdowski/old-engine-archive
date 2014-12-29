/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyleManager.h"
#include "Util/fgDirent.h"

/**
 * 
 */
fgGuiStyleManager::fgGuiStyleManager() {
    m_managerType = FG_MANAGER_GUI_STYLE;
}

/**
 * 
 */
fgGuiStyleManager::~fgGuiStyleManager() {
    fgGuiStyleManager::destroy();
}

/**
 * 
 */
void fgGuiStyleManager::clear(void) {
    releaseAllHandles();
}

/**
 * 
 * @return 
 */
fgBool fgGuiStyleManager::destroy(void) {
    hmDataVecItor begin = getRefDataVector().begin();
    hmDataVecItor end = getRefDataVector().end();
    for(hmDataVecItor itor = begin; itor != end; ++itor) {
        if((*itor) == NULL)
            continue;
        delete (*itor);
        *itor = NULL;
    }
    fgGuiStyleManager::clear();
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgGuiStyleManager::initialize(void) {
    FG_LOG_DEBUG("GUI: Initializing Style manager...");
    if(m_stylesPath.empty()) {
        FG_LOG_ERROR("GUI: Default path for styles directory is not set");
        return FG_FALSE;
    }
    // Will now preload all required styles
    fgDirent stylesDir;
    const char *filename;
    fgBool status = stylesDir.readDirectory(m_stylesPath, FG_TRUE, FG_TRUE);
    if(!status) {
        FG_LOG_ERROR("GUI: Unable to read directory (styles): '%s'", m_widgetsPath.c_str());
    }
    while((filename = stylesDir.getNextFile()) != NULL) {
        const char *ext = fgPath::fileExt(filename, FG_TRUE);
        if(!ext)
            continue;
        if(strcasecmp(ext, "style.ini") == 0) {
            fgGuiStyle *style = new fgGuiStyle();
            FG_LOG_DEBUG("GUI: Loading gui style file: '%s'", filename);
            if(!style->load(filename)) {
                FG_LOG::PrintError("GUI: Failed to load gui style: '%s'", filename);
                delete style;
                continue;
            } else {
                if(!insertStyle(style)) {
                    FG_LOG_ERROR("GUI: Insertion to database failed for style: '%s'", style->getNameStr());
                    // # remember to ALWAYS try to release the handle after failed insertion
                    releaseHandle(style->getRefHandle());
                    delete style;
                    continue;
                }
                FG_LOG_DEBUG("GUI: Successfully added style '%s' to the database", style->getNameStr());
            }
        }
    }
    stylesDir.clearList();
    m_init = FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @param pStyle
 * @param nameTag
 * @return 
 */
fgBool fgGuiStyleManager::insert(fgGuiStyle *pStyle, const std::string& nameTag) {
    if(!pStyle)
        return FG_FALSE;
    if(fgDataManagerBase::insert(pStyle, nameTag)) {
        pStyle->setName(nameTag);
        pStyle->setManaged(FG_TRUE);
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @param pStyle
 * @return 
 */
fgBool fgGuiStyleManager::insertStyle(fgGuiStyle *pStyle) {
    if(!pStyle) {
        return FG_FALSE;
    }
    if(!insert(pStyle, pStyle->getName())) {
        return FG_FALSE;
    }
    pStyle->setManaged(FG_TRUE);
    return FG_TRUE;
}

/**
 * 
 * @param info
 * @return 
 */
fgGuiStyle* fgGuiStyleManager::request(const std::string& info) {
    // #FIXME
    return NULL;
}

/**
 * 
 * @param info
 * @return 
 */
fgGuiStyle* fgGuiStyleManager::request(const char *info) {
    // #FIXME
    return NULL;
}

/**
 * 
 * @param path
 */
void fgGuiStyleManager::setStylesPath(const std::string &path) {
    m_stylesPath = path;
}

/**
 * 
 * @param path
 */
void fgGuiStyleManager::setStylesPath(const char *path) {
    m_stylesPath = path;
}
