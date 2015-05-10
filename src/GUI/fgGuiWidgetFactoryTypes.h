/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_WIDGET_FACTORY_TYPES
    #define FG_INC_GUI_WIDGET_FACTORY_TYPES

namespace fg {
    namespace gui {
        class CWidget;
    };
};

    #if __cplusplus > 199711L
using fgCreateGuiWidgetFn = fg::gui::CWidget* (*)(void);
    #else
typedef fg::gui::CWidget* (*fgCreateGuiWidgetFn)(void);
    #endif

    #ifndef FG_GUI_FACTORY_CREATE_FUNCTION
        #define FG_GUI_FACTORY_CREATE_FUNCTION(RETURNTYPE, CREATETYPE) \
static RETURNTYPE * createWidget(void) { return new CREATETYPE(); }
    #endif

    #ifndef FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION
        #define FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CREATETYPE) \
static fg::gui::CWidget * createWidget(void) { return new CREATETYPE(); }
    #endif

#endif /* FG_INC_GUI_WIDGET_FACTORY_TYPES */
