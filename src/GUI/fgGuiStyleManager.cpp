/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyleManager.h"

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
