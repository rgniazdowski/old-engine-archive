/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgWidgetTypes.h
 * Author: vigilant
 *
 * Created on November 6, 2014, 5:03 PM
 */

#ifndef FG_GUI_WIDGET_TYPES
    #define FG_GUI_WIDGET_TYPES
    #define FG_GUI_WIDGET_TYPES_BLOCK

    #ifndef FG_GUI_WIDGET_TYPES_DEFINED
        #define FG_GUI_WIDGET_TYPES_DEFINED

namespace fg {
    namespace gui {
        typedef unsigned int WidgetType;

        const WidgetType WIDGET_UNKNOWN = 0x00000000;
        /// Constant for Widget
        const WidgetType WIDGET = 0x00000001;
        const WidgetType LABEL = 0x00000002;
        const WidgetType BUTTON = 0x00000004;
        const WidgetType TOGGLE_BUTTON = 0x00000008;
        const WidgetType CONTAINER = 0x00000020;
        const WidgetType MENU = 0x00000040;
        const WidgetType FRAME = 0x00000080;
        const WidgetType SCROLL_AREA = 0x00000200;
        const WidgetType TEXT_AREA = 0x00000400;
        const WidgetType EDITABLE_TEXT = 0x00000800;
        const WidgetType CONSOLE = 0x00002000;
        const WidgetType WINDOW = 0x00004000;
        const WidgetType MESSAGE_BOX = 0x00008000;
        const WidgetType POPUP = 0x00020000;
        const WidgetType PROGRESS_BAR = 0x00040000;
        const WidgetType TABLE = 0x00080000;
        const WidgetType LOADER = 0x00200000;
        const WidgetType SLIDER = 0x00400000;

    };
};

    #endif

    #ifndef FG_GUI_WIDGET_TYPE_NAMES_DEFINED
        #define FG_GUI_WIDGET_TYPE_NAMES_DEFINED

//#define FG_GUI_WIDGET_UNKNOWN_NAME "Unknown"
        #define FG_GUI_WIDGET_NAME          "Widget"
        #define FG_GUI_LABEL_NAME           "Label"
        #define FG_GUI_BUTTON_NAME          "Button"
        #define FG_GUI_TOGGLE_BUTTON_NAME   "ToggleButton"
        #define FG_GUI_CONTAINER_NAME       "Container"
        #define FG_GUI_MENU_NAME            "Menu"
        #define FG_GUI_FRAME_NAME           "Frame"
        #define FG_GUI_SCROLL_AREA_NAME     "ScrollArea"
        #define FG_GUI_TEXT_AREA_NAME       "TextArea"
        #define FG_GUI_EDITABLE_TEXT_NAME   "EditableText"
        #define FG_GUI_CONSOLE_NAME         "Console"
        #define FG_GUI_WINDOW_NAME          "Window"
        #define FG_GUI_MESSAGE_BOX_NAME     "MessageBox"
        #define FG_GUI_POPUP_NAME           "Popup"
        #define FG_GUI_PROGRESS_BAR_NAME    "ProgressBar"
        #define FG_GUI_TABLE_NAME           "Table"
        #define FG_GUI_LOADER_NAME          "Loader"
        #define FG_GUI_SLIDER_NAME          "Slider"
    #endif

//#define FG_GUI_STYLE_SHEET_NAME     "StyleSheet" // #FIXME - string obfuscation
    #undef FG_GUI_WIDGET_TYPES_BLOCK
#endif	/* FG_GUI_WIDGET_TYPES */

