/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyleManager.h"
#include "Util/fgDirent.h"

using namespace fg;

gui::CStyleManager::CStyleManager() {
    m_managerType = FG_MANAGER_GUI_STYLE;
}

gui::CStyleManager::~CStyleManager() {
    gui::CStyleManager::destroy();
}

void gui::CStyleManager::clear(void) {
    releaseAllHandles();
}

fgBool gui::CStyleManager::destroy(void) {
    StyleVecItor begin = getRefDataVector().begin();
    StyleVecItor end = getRefDataVector().end();
    for(StyleVecItor itor = begin; itor != end; ++itor) {
        if((*itor).data == NULL)
            continue;
        delete (*itor).data;
        (*itor).clear();
    }
    gui::CStyleManager::clear();
    return FG_TRUE;
}

fgBool gui::CStyleManager::initialize(void) {
    FG_LOG_DEBUG("GUI: Initializing Style manager...");
    if(m_stylesPath.empty()) {
        FG_LOG_ERROR("GUI: Default path for styles directory is not set");
        return FG_FALSE;
    }
    // Will now preload all required styles
    util::CDirent stylesDir;
    const char *filename;
    fgBool status = stylesDir.readDir(m_stylesPath, FG_TRUE, FG_TRUE);
    if(!status) {
        FG_LOG_ERROR("GUI: Unable to read directory (styles): '%s'", m_stylesPath.c_str());
    }
    while((filename = stylesDir.getNextFile()) != NULL) {
        const char *ext = fg::path::fileExt(filename, FG_TRUE);
        if(!ext)
            continue;
        if(strcasecmp(ext, "style.ini") == 0) {
            CStyle *style = new CStyle();
            FG_LOG_DEBUG("GUI: Loading gui style file: '%s'", filename);
            if(!style->load(filename)) {
                log::PrintError("GUI: Failed to load gui style: '%s'", filename);
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

fgBool gui::CStyleManager::insert(CStyle *pStyle, const std::string& nameTag) {
    if(!pStyle)
        return FG_FALSE;
    if(base_type::insert(pStyle, nameTag)) {
        pStyle->setName(nameTag);
        pStyle->setManaged(FG_TRUE);
        return FG_TRUE;
    }
    return FG_FALSE;
}

fgBool gui::CStyleManager::insertStyle(CStyle *pStyle) {
    if(!pStyle) {
        return FG_FALSE;
    }
    if(!insert(pStyle, pStyle->getName())) {
        return FG_FALSE;
    }
    pStyle->setManaged(FG_TRUE);
    return FG_TRUE;
}

gui::CStyle* gui::CStyleManager::request(const std::string& info) {
    // #FIXME
    return NULL;
}

gui::CStyle* gui::CStyleManager::request(const char *info) {
    // #FIXME
    return NULL;
}

void gui::CStyleManager::setStylesPath(const std::string &path) {
    m_stylesPath = path;
}

void gui::CStyleManager::setStylesPath(const char *path) {
    m_stylesPath = path;
}
