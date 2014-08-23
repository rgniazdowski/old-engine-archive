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
#include "fgSingleton.h"

#include <map>
#if __cplusplus > 199711L
using fgCreateResourceFn = fgResource* (*)(void);
#else
typedef fgResource* (*fgCreateResourceFn)(void);
#endif

#ifndef FG_FACTORY_CREATE_FUNCTION
#define FG_FACTORY_CREATE_FUNCTION(RETURNTYPE, CREATETYPE) \
static RETURNTYPE * createResource(void) { return new CREATETYPE(); }
#endif

#ifndef FG_RESOURCE_FACTORY_CREATE_FUNCTION
#define FG_RESOURCE_FACTORY_CREATE_FUNCTION(CREATETYPE) \
static fgResource * createResource(void) { return new CREATETYPE(); }
#endif

class fgResourceFactory : public fgSingleton<fgResourceFactory>
{
	friend class fgSingleton<fgResourceFactory>;
public:
	typedef std::map<fgResourceType, fgCreateResourceFn> rfFactoryMap;
	typedef std::pair<fgResourceType, fgCreateResourceFn> rfFactoryPair;
	typedef rfFactoryMap::iterator rfFactoryMapItor;
	typedef rfFactoryMap::const_iterator rfFactoryMapConstItor;
protected:
	// Default empty constructor for Resource Factory object
	fgResourceFactory();
	// Default destructor for Resource Factory object
	~fgResourceFactory();
public:

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

#define FG_ResourceFactory fgResourceFactory::getInstance()

#endif /* _FG_RESOURCE_FACTORY_H_ */
