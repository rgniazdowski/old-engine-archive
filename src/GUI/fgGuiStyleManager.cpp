/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyleManager.h"
#include "Util/fgDirent.h"

/*
 *
 */
fgGuiStyleManager::fgGuiStyleManager() {
    m_managerType = FG_MANAGER_GUI_STYLE;
}

/*
 *
 */
fgGuiStyleManager::~fgGuiStyleManager() {
    fgGuiStyleManager::destroy();
}

/*
 *
 */
void fgGuiStyleManager::clear(void) {
    releaseAllHandles();
}

/*
 *
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

/*
 *
 */
fgBool fgGuiStyleManager::initialize(void) {
    FG_LOG::PrintDebug("GUI: Initializing Style manager...");
    if(m_stylesPath.empty()) {
        FG_LOG::PrintError("GUI: Default path for styles directory is not set");
        return FG_FALSE;
    }
    // Will now preload all required styles
    fgDirent stylesDir;
    const char *filename;
    stylesDir.readDirectory(m_stylesPath, FG_TRUE);
    while((filename = stylesDir.getNextFile()) != NULL) {
        const char *ext = fgPath::fileExt(filename, FG_TRUE);
        if(!ext)
            continue;
        if(strcasecmp(ext, "style.ini") == 0) {
            fgGuiStyle *style = new fgGuiStyle();
            FG_LOG::PrintDebug("GUI: Loading gui style file: '%s'", filename);
            if(!style->load(filename)) {
                FG_LOG::PrintError("GUI: Failed to load gui style: '%s'", filename);
                delete style;
                continue;
            } else {
                if(!insertStyle(style->getRefHandle(), style)) {
                    FG_LOG::PrintError("GUI: Insertion to database failed for style: '%s'", style->getNameStr());
                    // # remember to ALWAYS try to release the handle after failed insertion
                    releaseHandle(style->getRefHandle());
                    delete style;
                    continue;
                }
                FG_LOG::PrintDebug("GUI: Successfully added style '%s' to the database", style->getNameStr());
            }
        }
    }
    stylesDir.clearList();
    m_init = FG_TRUE;
    return FG_TRUE;
}

/*
 *
 */
fgBool fgGuiStyleManager::insertStyle(fgGuiStyleHandle& shUniqueID, fgGuiStyle *pStyle) {
    if(!pStyle) {
        return FG_FALSE;
    }
    if(!insert(shUniqueID, pStyle, pStyle->getName())) {
        return FG_FALSE;
    }
    //style->setManaged(); // ?
    return FG_TRUE;
}

/*
 *
 */
fgGuiStyle* fgGuiStyleManager::request(const std::string& info) {
    return NULL;
}

/*
 *
 */
fgGuiStyle* fgGuiStyleManager::request(const char *info) {
    return NULL;
}

/*
 *
 */
void fgGuiStyleManager::setStylesPath(const std::string &path) {
    m_stylesPath = path;
}

/*
 *
 */
void fgGuiStyleManager::setStylesPath(const char *path) {
    m_stylesPath = path;
}