/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiMenu.h"

/*
 *
 */
fgGuiMenu::fgGuiMenu()
{
	fgGuiMenu::setDefaults();
}

/*
 *
 */
fgGuiMenu::~fgGuiMenu()
{
}

/*
 *
 */
void fgGuiMenu::setDefaults(void)
{
	m_type = FG_GUI_MENU;
	m_typeName = FG_GUI_MENU_NAME;
	m_typeTraits = FG_GUI_MENU | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df& fgGuiMenu::updateSize(void)
{
	return fgGuiContainer::updateSize();
}

/*
 *
 */
void fgGuiMenu::refresh(void)
{
}

/////////////////////////////////////////////////////////////////////

/**
 *
 */
void Menu::getSignals(void)
{
	/*
	std::map<int, Widget*>::iterator childIt;

	for(childIt = m_children.begin(); childIt != m_children.end(); childIt++)
	{
		childIt->second->getSignals(this);
	}
	*/
}

/**
 *
 */
void Menu::draw(void)
{
	/*
	std::map<int, Widget*>::iterator childIt;

	for(childIt = m_children.begin(); childIt != m_children.end(); childIt++)
	{
		childIt->second->show();
	}
	*/
}

/**
 *
 */
void Menu::releaseAllWidgets(void)
{
	/*
	std::map<int, Widget*>::iterator childIt;

	for(childIt = m_children.begin(); childIt != m_children.end(); childIt++)
	{
		delete childIt->second;
		m_children[childIt->first] = NULL;
	}
	m_children.clear();
	*/
}
