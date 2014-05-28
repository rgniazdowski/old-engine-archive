/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _GUI_MENU_H_
#define _GUI_MENU_H_

#include <map>

#include "fgGuiWidget.h"

#define MENU_TITLE_MAX 32

class Widget; // FIXME ! ! ! ! 

class Menu {

protected:
    std::map<int, Widget*> m_children;

	int m_menuID;
	char m_menuTitle[ MENU_TITLE_MAX+1 ];

public:
	Menu() : m_menuID(-1) {
        m_menuTitle[ 0 ] = '\0';
        m_menuTitle[ MENU_TITLE_MAX ] = '\0';
	}

    ~Menu() {
		releaseAllWidgets();
	}

	void releaseAllWidgets(void);

	int menuID(void) const {
		return m_menuID;
	}

	void setMenuID(int id) {
		m_menuID = id;
	}

	void addChildWidget(Widget *widget) {
		//m_children[widget->id()] = widget; // FIXME
	}

	void setMenuTitle(const char *title) {
		strncpy( m_menuTitle, title, MENU_TITLE_MAX );
        m_menuTitle[ MENU_TITLE_MAX ] = '\0';
	}

	const char *menuTitle(void) const {
		return m_menuTitle;
	}

	virtual bool init(void) { return true; };
	virtual void getSignals(void);
	virtual void draw(void);
};

#endif