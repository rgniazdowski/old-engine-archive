/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiWidgetFactory.h"
#include "fgLog.h"

/*
 * Default empty constructor for Resource Factory object
 */
fgGuiWidgetFactory::fgGuiWidgetFactory()
{
	FG_LOG::PrintError("fgGuiWidgetFactory::fgGuiWidgetFactory()");
}

/*
 * Default destructor for Resource Factory object
 */
fgGuiWidgetFactory::~fgGuiWidgetFactory()
{
	FG_LOG::PrintError("fgGuiWidgetFactory::~fgGuiWidgetFactory()");
	clear();
}

/*
 * Clear all registered resource creators
 */
void fgGuiWidgetFactory::clear(void) 
{
	FG_LOG::PrintError("fgGuiWidgetFactory::clear()");
	m_factoryMap.clear(); 
}

/*
 * Register resource create function based on resource type
 */
fgBool fgGuiWidgetFactory::registerWidget(const fgGuiWidgetType type, fgCreateGuiWidgetFn function)
{
	if(!function)
		return FG_FALSE;
	factoryPair query_pair;
	query_pair.first = type;
	query_pair.second = function;
	std::pair<factoryMapItor, bool> result = m_factoryMap.insert(query_pair);
	if(result.second == false) {
		// Existed
		return FG_FALSE;
	} else {
		// New insertion
	}
	return FG_TRUE;
}

/*
 * Call specific create function for given widget
 */
fgGuiWidget* fgGuiWidgetFactory::createWidget(const fgGuiWidgetType type)
{
	factoryMapItor it = m_factoryMap.find(type);
	if(it != m_factoryMap.end()) {
		if(it->second != NULL)
			return it->second();
	}
	return NULL;
}

/*
 * Check if given widget type constructor/create function is registered in factory
 */
fgBool fgGuiWidgetFactory::isRegistered(const fgGuiWidgetType type)
{
	factoryMapItor it = m_factoryMap.find(type);
	if(it != m_factoryMap.end()) {
		return FG_TRUE;
	}
	return FG_FALSE;
}
