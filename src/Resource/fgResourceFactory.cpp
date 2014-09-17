/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgResourceFactory.h"
#include "fgLog.h"

/*
 * Default empty constructor for Resource Factory object
 */
fgResourceFactory::fgResourceFactory()
{
	FG_LOG::PrintError("fgResourceFactory::fgResourceFactory()");
}

/*
 * Default destructor for Resource Factory object
 */
fgResourceFactory::~fgResourceFactory()
{
	FG_LOG::PrintError("fgResourceFactory::~fgResourceFactory()");
	clear();
}

/*
 * Clear all registered resource creators
 */
void fgResourceFactory::clear(void) 
{
	FG_LOG::PrintError("fgResourceFactory::clear()");
	m_factoryMap.clear(); 
}

/*
 * Register resource create function based on resource type
 */
fgBool fgResourceFactory::registerResource(fgResourceType type, fgCreateResourceFn function)
{
	if(!function)
		return FG_FALSE;
	rfFactoryPair query_pair;
	query_pair.first = type;
	query_pair.second = function;
	std::pair<rfFactoryMapItor, bool> result = m_factoryMap.insert(query_pair);
	//rfFactoryMapItor it = result.first;
	if(result.second == false) {
		// Existed
		return FG_FALSE;
	} else {
		// New insertion
	}
	return FG_TRUE;
}

/*
 * Call specific create function for given resource
 */
fgResource* fgResourceFactory::createResource(fgResourceType type)
{
	rfFactoryMapItor it = m_factoryMap.find(type);
	if(it != m_factoryMap.end()) {
		if(it->second != NULL)
			return it->second();
	}
	return NULL;
}

/*
 * Check if given resource type constructor/create function is registered in factory
 */
fgBool fgResourceFactory::isRegistered(fgResourceType type)
{
	rfFactoryMapItor it = m_factoryMap.find(type);
	if(it != m_factoryMap.end()) {
		return FG_TRUE;
	}
	return FG_FALSE;
}
