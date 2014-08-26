/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiMenu.h"

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
