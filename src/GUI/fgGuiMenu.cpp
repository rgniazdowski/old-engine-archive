/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiMenu.h"
#include "Util/fgStrings.h"

using namespace fg;

/*
 *
 */
gui::CMenu::CMenu() : m_isMainMenu(FG_FALSE) {
    gui::CMenu::setDefaults();
}

/*
 *
 */
gui::CMenu::~CMenu() { }

/**
 * 
 * @param flags
 */
void gui::CMenu::setFlags(const std::string& flags) {
    if(flags.empty() || flags.length() < 5)
        return;
    // This is important - always call setFlags for the base class
    CContainer::setFlags(flags);
    m_isMainMenu = FG_FALSE;
    fg::CStringVector flagsVec;
    strings::split(flags, ' ', flagsVec);
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
void gui::CMenu::setDefaults(void) {
    m_type = MENU;
    m_typeName = FG_GUI_MENU_NAME;
    m_typeTraits = MENU | CONTAINER | WIDGET;
}

/*
 *
 */
gfx::BoundingBox3Df gui::CMenu::updateBounds(void) {
    return CContainer::updateBounds();
}

/*
 *
 */
void gui::CMenu::refresh(void) {
    CContainer::refresh();
}
