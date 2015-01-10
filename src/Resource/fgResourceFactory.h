/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_RESOURCE_FACTORY
    #define FG_INC_RESOURCE_FACTORY

    #include "fgCommon.h"
    #include "fgResource.h"
    #include "fgResourceFactoryTypes.h"

    #include <map>
// Need general template ?

/*
 *
 */
class fgResourceFactory {
public:
    typedef std::map<fgResourceType, fgCreateResourceFn> factoryMap;
    typedef std::pair<fgResourceType, fgCreateResourceFn> factoryPair;
    typedef factoryMap::iterator factoryMapItor;
    typedef factoryMap::const_iterator factoryMapConstItor;

public:
    // Default empty constructor for Resource Factory object
    fgResourceFactory();
    // Default destructor for Resource Factory object
    ~fgResourceFactory();

    // Clear all registered resource creators
    void clear(void);

    // Register resource create function based on resource type
    fgBool registerResource(const fgResourceType type, fgCreateResourceFn function);

    // Call specific create function for given resource
    fg::resource::CResource* createResource(const fgResourceType type);

    // Check if given resource type constructor/create function is registered in factory
    fgBool isRegistered(const fgResourceType type);

private:
    // Map storing create functions for given resource types
    factoryMap m_factoryMap;
};

#endif /* FG_INC_RESOURCE_FACTORY */
