/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiMenu.h"
#include "Util/fgStrings.h"

/*
 *
 */
fgGuiMenu::fgGuiMenu() : m_isMainMenu(FG_FALSE) {
    fgGuiMenu::setDefaults();
}

/*
 *
 */
fgGuiMenu::~fgGuiMenu() { }

/**
 * 
 * @param flags
 */
void fgGuiMenu::setFlags(const std::string& flags) {
    if(flags.empty() || flags.length() < 5)
        return;
    // This is important - always call setFlags for the base class
    fgGuiContainer::setFlags(flags);
    m_isMainMenu = FG_FALSE;
    fgStringVector flagsVec;
    fgStrings::split(flags, ' ', flagsVec);
    if(flagsVec.empty())
        return;
    unsigned int n = (unsigned int)flagsVec.size();
    for(unsigned int i = 0; i < n; i++) {
        if(flagsVec[i].compare("mainmenu") == 0) {
            m_isMainMenu = FG_TRUE;
        } 
    }
    flagsVec.clear();
}

/*
 *
 */
void fgGuiMenu::setDefaults(void) {
    m_type = FG_GUI_MENU;
    m_typeName = FG_GUI_MENU_NAME;
    m_typeTraits = FG_GUI_MENU | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiMenu::updateSize(void) {
    return fgGuiContainer::updateSize();
}

/*
 *
 */
void fgGuiMenu::refresh(void) {
    fgGuiContainer::refresh();
}
