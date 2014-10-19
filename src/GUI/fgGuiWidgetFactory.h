/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_WIDGET_FACTORY_H_
    #define _FG_GUI_WIDGET_FACTORY_H_

    #include "fgTypes.h"
    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #include <map>

/*
 *
 */
class fgGuiWidgetFactory {
public:
    typedef std::map<fgGuiWidgetType, fgCreateGuiWidgetFn> factoryMap;
    typedef std::pair<fgGuiWidgetType, fgCreateGuiWidgetFn> factoryPair;
    typedef factoryMap::iterator factoryMapItor;
    typedef factoryMap::const_iterator factoryMapConstItor;

public:
    // Default empty constructor for Widget Factory object
    fgGuiWidgetFactory();
    // Default destructor for Widget Factory object
    ~fgGuiWidgetFactory();

    // Clear all registered Widget creators
    void clear(void);

    // Register Widget create function based on resource type
    fgBool registerWidget(const fgGuiWidgetType type, fgCreateGuiWidgetFn function);

    // Call specific create function for given Widget
    fgGuiWidget* createWidget(const fgGuiWidgetType type);

    // Check if given resource type constructor/create function is registered in factory
    fgBool isRegistered(const fgGuiWidgetType type);

private:
    // Map storing create functions for given widget types
    factoryMap m_factoryMap;
};

#endif /* _FG_GUI_WIDGET_FACTORY_H_ */
