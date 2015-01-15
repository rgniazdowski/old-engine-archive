/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgScriptMetatables.cpp
 * Author: vigilant
 * 
 * Created on November 6, 2014, 4:49 PM
 */

#include "fgScriptMT.h"
#include "GUI/fgGuiWidgetTypes.h"
#include "Resource/fgResource.h"

template <>
bool CSingleton<fg::script::CMetatables>::instanceFlag = false;

template <>
fg::script::CMetatables *CSingleton<fg::script::CMetatables>::instance = NULL;

using namespace fg;

/**
 * 
 */
script::CMetatables::CMetatables() { }

/**
 * 
 */
script::CMetatables::~CMetatables() {
    clearMetatableNames();
}

/**
 * 
 * @param widgetType
 * @return 
 */
script::CMetatables::METAID script::CMetatables::getMetatableIDFromWidgetType(const unsigned int widgetType) {
    METAID metaID;
    if(widgetType == gui::BUTTON) {
        metaID = CMetatables::GUI_BUTTON_MT_ID;
    } else if(widgetType == gui::CONSOLE) {
        metaID = CMetatables::GUI_CONSOLE_MT_ID;
    } else if(widgetType == gui::CONTAINER) {
        metaID = CMetatables::GUI_CONTAINER_MT_ID;
    } else if(widgetType == gui::FRAME) {
        metaID = CMetatables::GUI_FRAME_MT_ID;
    } else if(widgetType == gui::LABEL) {
        metaID = CMetatables::GUI_FRAME_MT_ID;
    } else if(widgetType == gui::LOADER) {
        metaID = CMetatables::GUI_LOADER_MT_ID;
    } else if(widgetType == gui::MENU) {
        metaID = CMetatables::GUI_MENU_MT_ID;
    } else if(widgetType == gui::MESSAGE_BOX) {
        metaID = CMetatables::GUI_MESSAGE_BOX_MT_ID;
    } else if(widgetType == gui::POPUP) {
        metaID = CMetatables::GUI_POPUP_MT_ID;
    } else if(widgetType == gui::PROGRESS_BAR) {
        metaID = CMetatables::GUI_PROGRESS_BAR_MT_ID;
    } else if(widgetType == gui::SCROLL_AREA) {
        metaID = CMetatables::GUI_SCROLL_AREA_MT_ID;
    } else if(widgetType == gui::TABLE) {
        metaID = CMetatables::GUI_TABLE_MT_ID;
    } else if(widgetType == gui::TEXT_AREA) {
        metaID = CMetatables::GUI_TEXT_AREA_MT_ID;
    } else if(widgetType == gui::TOGGLE_BUTTON) {
        metaID = CMetatables::GUI_TOGGLE_BUTTON_MT_ID;
    } else if(widgetType == gui::WINDOW) {
        metaID = CMetatables::GUI_WINDOW_MT_ID;
    } else {
        metaID = CMetatables::EMPTY_MT_ID;
    }
    return metaID;
}

/**
 * 
 * @param resourceType
 * @return 
 */
script::CMetatables::METAID script::CMetatables::getMetatableIDFromResourceType(const unsigned int resourceType) {
    METAID metaID;
    if(resourceType == resource::TEXTURE) {
        metaID = CMetatables::TEXTURE_RESOURCE_MT_ID;
    } else if(resourceType == resource::FONT) {
        metaID = CMetatables::FONT_RESOURCE_MT_ID;
    } else if(resourceType == resource::MODEL3D) {
        metaID = CMetatables::GFX_MODEL_RESOURCE_MT_ID;
    } else if(resourceType == resource::PARTICLE_EFFECT) {
        metaID = CMetatables::PARTICLE_EFFECT_RESOURCE_MT_ID;
    } else if(resourceType == resource::MUSIC) {
        metaID = CMetatables::MUSIC_RESOURCE_MT_ID;
    } else if(resourceType == resource::SOUND) {
        metaID = CMetatables::SOUND_RESOURCE_MT_ID;
    } else {
        metaID = CMetatables::EMPTY_MT_ID;
    }
    return metaID;
}

/**
 * 
 */
void script::CMetatables::generateMetatableNames(void) {
    // Initializing metatable map
    m_metatableInfoVec.clear();
    m_metatableInfoVec.reserve(METATABLE_SIZE);
    m_metatableInfoVec.resize(METATABLE_SIZE);

    // can generate random IDS? YEP :D
    // Numbers 0 - 9 ASCII 48 to 57
    // Lowercase letters a - z ASCII 97 to 122
    // Uppercase letters A - Z ASCII 65 - 90

#if !defined(FG_USING_MARMALADE)

    m_metatableInfoVec[EMPTY_MT_ID] = metatableInfo("FG", "X");

    m_metatableInfoVec[FG_NAMESPACE_MT_ID] = metatableInfo("FG", "NMSPC");

    m_metatableInfoVec[VECTOR2I_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[VECTOR2F_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[VECTOR3I_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[VECTOR3F_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[VECTOR4I_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[VECTOR4F_MT_ID] = metatableInfo("FGX", "T");

    m_metatableInfoVec[ERROR_MT_ID] = metatableInfo("FGX", "T");

    m_metatableInfoVec[EVENT_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[RESOURCE_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[SHADER_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[SCENE2D_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[SCENE3D_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[PARTICLE_SYSTEM_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_MAIN_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[WIDGET_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[STYLE_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[SOUND_MANAGER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[LOGIC_MANAGER_MT_ID] = metatableInfo("FGX", "T");

    m_metatableInfoVec[RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[TEXTURE_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[FONT_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GFX_MODEL_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[PARTICLE_EFFECT_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[AUDIO_BASE_RES_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[SOUND_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[MUSIC_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[PLUGIN_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[SAVE_FILE_RESOURCE_MT_ID] = metatableInfo("FGX", "T");

    // INI Config / Settings XML

    m_metatableInfoVec[CONFIG_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[SETTINGS_MT_ID] = metatableInfo("FGX", "T");

    // GUI Widget structure metatables

    m_metatableInfoVec[GUI_WIDGET_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_BUTTON_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_CONSOLE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_CONTAINER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_FRAME_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_LABEL_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_LOADER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_MENU_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_MESSAGE_BOX_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_POPUP_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_PROGRESS_BAR_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_SCROLL_AREA_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_TABLE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_TEXT_AREA_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_TOGGLE_BUTTON_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_WINDOW_MT_ID] = metatableInfo("FGX", "T");

    // GUI Style special structures

    m_metatableInfoVec[GUI_STYLE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_CONTENT_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_SIZE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_BACKGROUND_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_FOREGROUND_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_MARGIN_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_PADDING_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_BORDER_INFO_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_BORDER_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[GUI_STYLE_POSITION_MT_ID] = metatableInfo("FGX", "T");

    // Thrown Event info structures 

    m_metatableInfoVec[EVENT_BASE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_CONTROLLER_DEVICE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_CONTROLLER_BUTTON_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_CONTROLLER_AXIS_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_TOUCH_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_MOUSE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_SWIPE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_SWIPE_PINCH_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_SWIPE_ROTATE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_KEY_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_RESOURCE_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_VERTEX_STREAM_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_CAMERA_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_SOUND_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_MENU_CHANGED_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_WIDGET_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_SENSORS_MT_ID] = metatableInfo("FGX", "T");
    m_metatableInfoVec[EVENT_MAIN_MT_ID] = metatableInfo("FGX", "T");

    // Script callback type
    m_metatableInfoVec[SCRIPT_CALLBACK_MT_ID] = metatableInfo("FGX", "T");

    // GFX Scene Node type
    m_metatableInfoVec[SCENE_NODE_MT_ID] = metatableInfo("FGX", "T");

#endif

    for(int i = 0; i < (int)METATABLE_SIZE; i++) {
        m_metatableInfoVec[i].id = (unsigned short int)i;
    }
}

/**
 * 
 */
void script::CMetatables::clearMetatableNames() {
    m_metatableInfoVec.clear();
    metatableInfoVec smvec;
    m_metatableInfoVec.swap(smvec);
}
