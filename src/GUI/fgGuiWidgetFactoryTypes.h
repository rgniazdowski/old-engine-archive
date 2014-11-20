/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_WIDGET_FACTORY_TYPES
    #define FG_INC_GUI_WIDGET_FACTORY_TYPES

class fgGuiWidget;

    #if __cplusplus > 199711L
using fgCreateGuiWidgetFn = fgGuiWidget* (*)(void);
    #else
typedef fgGuiWidget* (*fgCreateGuiWidgetFn)(void);
    #endif

    #ifndef FG_GUI_FACTORY_CREATE_FUNCTION
        #define FG_GUI_FACTORY_CREATE_FUNCTION(RETURNTYPE, CREATETYPE) \
static RETURNTYPE * createWidget(void) { return new CREATETYPE(); }
    #endif

    #ifndef FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION
        #define FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CREATETYPE) \
static fgGuiWidget * createWidget(void) { return new CREATETYPE(); }
    #endif

#endif /* FG_INC_GUI_WIDGET_FACTORY_TYPES */
