/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiWidgetFactory.h"
#include "fgLog.h"

using namespace fg;

gui::CWidgetFactory::CWidgetFactory() { }

gui::CWidgetFactory::~CWidgetFactory() {
    clear();
}

void gui::CWidgetFactory::clear(void) {
    m_factoryMap.clear();
}

fgBool gui::CWidgetFactory::registerWidget(const WidgetType type,
                                           fgCreateGuiWidgetFn function) {
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

gui::CWidget* gui::CWidgetFactory::createWidget(const WidgetType type) {
    factoryMapItor it = m_factoryMap.find(type);
    if(it != m_factoryMap.end()) {
        if(it->second != NULL)
            return it->second();
    }
    return NULL;
}

fgBool gui::CWidgetFactory::isRegistered(const WidgetType type) {
    factoryMapItor it = m_factoryMap.find(type);
    if(it != m_factoryMap.end()) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
