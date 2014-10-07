/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_MENU_H_
#define _FG_GUI_MENU_H_

#include <map>

#include "fgCommon.h"
#include "fgGuiContainer.h"
#include "fgGuiWidgetFactoryTypes.h"

#define FG_GUI_MENU			0x00000040
#define FG_GUI_MENU_NAME	"Menu"

class fgGuiMenu : public fgGuiContainer
{
private:
protected:

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiMenu();
	// 
	virtual ~fgGuiMenu();

	FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiMenu);

	// 
	virtual fgBoundingBox3Df& updateSize(void);
	// 
	virtual void refresh(void);

};

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

	virtual fgBool init(void) { return FG_TRUE; };
	virtual void getSignals(void);
	virtual void draw(void);
};

#endif /* _FG_GUI_MENU_H_ */

