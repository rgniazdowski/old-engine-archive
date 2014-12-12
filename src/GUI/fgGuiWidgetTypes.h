/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
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

typedef unsigned int fgGuiWidgetType;

        #define FG_GUI_WIDGET_UNKNOWN   0x00000000
        #define FG_GUI_WIDGET           0x00000001
        #define FG_GUI_LABEL            0x00000002
        #define FG_GUI_BUTTON           0x00000004
        #define FG_GUI_TOGGLE_BUTTON    0x00000008
        #define FG_GUI_CONTAINER        0x00000020
        #define FG_GUI_MENU             0x00000040
        #define FG_GUI_FRAME            0x00000080
        #define FG_GUI_SCROLL_AREA      0x00000200
        #define FG_GUI_TEXT_AREA        0x00000400
        #define FG_GUI_EDITABLE_TEXT    0x00000800
        #define FG_GUI_CONSOLE          0x00002000
        #define FG_GUI_WINDOW           0x00004000
        #define FG_GUI_MESSAGE_BOX      0x00008000
        #define FG_GUI_POPUP            0x00020000
        #define FG_GUI_PROGRESS_BAR     0x00040000
        #define FG_GUI_TABLE            0x00080000
        #define FG_GUI_LOADER           0x00200000

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
    #endif

//#define FG_GUI_STYLE_SHEET_NAME     "StyleSheet" // #FIXME - string obfuscation
    #undef FG_GUI_WIDGET_TYPES_BLOCK
#endif	/* FG_GUI_WIDGET_TYPES */

