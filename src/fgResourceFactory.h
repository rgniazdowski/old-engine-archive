/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_FACTORY_H_
#define _FG_RESOURCE_FACTORY_H_

#include "fgCommon.h"
#include "fgResource.h"

#include <map>

typedef fgResource* (__stdcall *fgCreateResourceFn)(void);

#ifndef FG_FACTORY_CREATE_FUNCTION
#define FG_FACTORY_CREATE_FUNCTION(RETURNTYPE, CREATETYPE) \
static RETURNTYPE * __stdcall createResource(void) { return new CREATETYPE(); }
#endif

#ifndef FG_RESOURCE_FACTORY_CREATE_FUNCTION
#define FG_RESOURCE_FACTORY_CREATE_FUNCTION(CREATETYPE) \
static fgResource * __stdcall createResource(void) { return new CREATETYPE(); }
#endif

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
	static void clear(void);

	// Register resource create function based on resource type
	static fgBool registerResource(fgResourceType type, fgCreateResourceFn function);
	// Call specific create function for given resource
	static fgResource* createResource(fgResourceType type);
	// Check if given resource type constructor/create function is registered in factory
	static fgBool isRegistered(fgResourceType type);
	
private:
	static rfFactoryMap m_factoryMap;
};

#endif /* _FG_RESOURCE_FACTORY_H_ */
