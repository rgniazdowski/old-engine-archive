/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_FACTORY_H_
#define _FG_RESOURCE_FACTORY_H_

#include "fgCommon.h"
#include "fgResource.h"
#include "fgResourceFactoryTypes.h"

#include <map>

/*
 *
 */
class fgResourceFactory
{
public:
	typedef std::map<fgResourceType, fgCreateResourceFn> rfFactoryMap;
	typedef std::pair<fgResourceType, fgCreateResourceFn> rfFactoryPair;
	typedef rfFactoryMap::iterator rfFactoryMapItor;
	typedef rfFactoryMap::const_iterator rfFactoryMapConstItor;

public:
	// Default empty constructor for Resource Factory object
	fgResourceFactory();
	// Default destructor for Resource Factory object
	~fgResourceFactory();

	// Clear all registered resource creators
	void clear(void);

	// Register resource create function based on resource type
	fgBool registerResource(fgResourceType type, fgCreateResourceFn function);
	
	// Call specific create function for given resource
	fgResource* createResource(fgResourceType type);
	
	// Check if given resource type constructor/create function is registered in factory
	fgBool isRegistered(fgResourceType type);

private:
	// Map storing create functions for given resource types
	rfFactoryMap m_factoryMap;
};

#endif /* _FG_RESOURCE_FACTORY_H_ */
