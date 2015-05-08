/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgResourceFactory.h"
#include "fgLog.h"

using namespace fg;

//------------------------------------------------------------------------------

resource::CResourceFactory::CResourceFactory() {
    ///FG_LOG_DEBUG("fgResourceFactory: allocation");
}
//------------------------------------------------------------------------------

resource::CResourceFactory::~CResourceFactory() {
    ///FG_LOG_DEBUG("fgResourceFactory: destroy");
    clear();
}
//------------------------------------------------------------------------------

void resource::CResourceFactory::clear(void) {
    m_factoryMap.clear();
}
//------------------------------------------------------------------------------

fgBool resource::CResourceFactory::registerResource(const ResourceType type, CreateResourceFunction function) {
    if(!function)
        return FG_FALSE;
    factoryPair query_pair;
    query_pair.first = type;
    query_pair.second = function;
    std::pair<factoryMapItor, bool> result = m_factoryMap.insert(query_pair);
    //rfFactoryMapItor it = result.first;
    if(result.second == false) {
        // Existed
        return FG_FALSE;
    } else {
        // New insertion
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceFactory::createResource(const ResourceType type) {
    factoryMapItor it = m_factoryMap.find(type);
    if(it != m_factoryMap.end()) {
        if(it->second != NULL)
            return it->second();
    }
    return NULL;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceFactory::isRegistered(const ResourceType type) {
    factoryMapItor it = m_factoryMap.find(type);
    if(it != m_factoryMap.end()) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------
