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
 * File:   fgScriptMetatables.cpp
 * Author: vigilant
 * 
 * Created on November 6, 2014, 4:49 PM
 */

#include "fgScriptMT.h"
#include "GUI/fgGuiWidgetTypes.h"
#include "Resource/fgResource.h"
#include "fgLog.h"
#include "GFX/Scene/fgGfxSceneNodeType.h"
#include "Game/fgGameEntityType.h"

template <>
bool CSingleton<fg::script::CMetatables>::instanceFlag = false;

template <>
fg::script::CMetatables *CSingleton<fg::script::CMetatables>::instance = NULL;

using namespace fg;

//------------------------------------------------------------------------------

script::CMetatables::CMetatables() { }
//------------------------------------------------------------------------------

script::CMetatables::~CMetatables() {
    clearMetatableNames();
}
//------------------------------------------------------------------------------

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
        metaID = CMetatables::GUI_LABEL_MT_ID;
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
//------------------------------------------------------------------------------

unsigned int script::CMetatables::getWidgetTypeFromMetatableID(const unsigned int metatableID) {
    gui::WidgetType widgetType = gui::WIDGET_UNKNOWN;

    switch((METAID)metatableID) {
#define meta CMetatables
        case meta::GUI_BUTTON_MT_ID:
            widgetType = gui::BUTTON;
            break;
        case meta::GUI_CONSOLE_MT_ID:
            widgetType = gui::CONSOLE;
            break;
        case meta::GUI_CONTAINER_MT_ID:
            widgetType = gui::CONTAINER;
            break;
        case meta::GUI_FRAME_MT_ID:
            widgetType = gui::FRAME;
            break;
        case meta::GUI_LABEL_MT_ID:
            widgetType = gui::LABEL;
            break;
        case meta::GUI_LOADER_MT_ID:
            widgetType = gui::LOADER;
            break;
        case meta::GUI_MENU_MT_ID:
            widgetType = gui::MENU;
            break;
        case meta::GUI_MESSAGE_BOX_MT_ID:
            widgetType = gui::MESSAGE_BOX;
            break;
        case meta::GUI_POPUP_MT_ID:
            widgetType = gui::POPUP;
            break;
        case meta::GUI_PROGRESS_BAR_MT_ID:
            widgetType = gui::PROGRESS_BAR;
            break;
        case meta::GUI_SCROLL_AREA_MT_ID:
            widgetType = gui::SCROLL_AREA;
            break;
        case meta::GUI_TABLE_MT_ID:
            widgetType = gui::TABLE;
            break;
        case meta::GUI_TEXT_AREA_MT_ID:
            widgetType = gui::TEXT_AREA;
            break;
        case meta::GUI_TOGGLE_BUTTON_MT_ID:
            widgetType = gui::TOGGLE_BUTTON;
            break;
        case meta::GUI_WINDOW_MT_ID:
            widgetType = gui::WINDOW;
            break;
        case meta::EMPTY_MT_ID:
            break;
        default:
            break;
#undef meta
    };
    return (unsigned int)widgetType;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

unsigned int script::CMetatables::getResourceTypeFromMetatableID(const unsigned short int metatableID) {
    resource::ResourceType resourceType = resource::INVALID;
    switch((METAID)metatableID) {
        case TEXTURE_RESOURCE_MT_ID:
            resourceType = resource::TEXTURE;
            break;
        case FONT_RESOURCE_MT_ID:
            resourceType = resource::FONT;
            break;
        case GFX_MODEL_RESOURCE_MT_ID:
            resourceType = resource::MODEL3D;
            break;
        case PARTICLE_EFFECT_RESOURCE_MT_ID:
            resourceType = resource::PARTICLE_EFFECT;
            break;
        case MUSIC_RESOURCE_MT_ID:
            resourceType = resource::MUSIC;
            break;
        case SOUND_RESOURCE_MT_ID:
            resourceType = resource::SOUND;
            break;
        default:
            break;
    };
    return (unsigned int)resourceType;
}
//------------------------------------------------------------------------------

script::CMetatables::METAID script::CMetatables::getMetatableIDFromNodeType(const unsigned int nodeType) {
    METAID metaID = CMetatables::EMPTY_MT_ID;
    if(nodeType == gfx::SCENE_NODE_ROOT) {
        metaID = CMetatables::SCENE_NODE_MT_ID; // #FIXME
    } else if(nodeType == gfx::SCENE_NODE_MESH) {
        metaID = CMetatables::SCENE_NODE_MESH_MT_ID;
    } else if(nodeType == gfx::SCENE_NODE_OBJECT) {
        metaID = CMetatables::SCENE_NODE_OBJECT_MT_ID;
    } else if(nodeType == gfx::SCENE_NODE_TRIGGER) {
        metaID = CMetatables::SCENE_NODE_TRIGGER_MT_ID;
    } else if(nodeType == gfx::SCENE_NODE_INTERIOR) {
        metaID = CMetatables::SCENE_NODE_MT_ID; // #FIXME
    } else if(nodeType == gfx::SCENE_NODE_LANDSCAPE) {
        metaID = CMetatables::SCENE_NODE_MT_ID; // #FIXME
    } else if(nodeType == gfx::SCENE_NODE_PARTICLE_EMITTER) {
        metaID = CMetatables::SCENE_NODE_MT_ID; // #FIXME
    } else if(nodeType == game::GAME_ENTITY) {
        metaID = CMetatables::GAME_ENTITY_MT_ID;
    } else if(nodeType == game::GAME_ENTITY_MESH) {
        metaID = CMetatables::GAME_ENTITY_MESH_MT_ID;
    } else if(nodeType == game::GAME_ENTITY_ACTOR) {
        metaID = CMetatables::GAME_ENTITY_MT_ID; // #FIXME
    }
    return metaID;
}

unsigned int script::CMetatables::getNodeTypeFromMetatableID(const unsigned short int metatableID) {
    gfx::SceneNodeType nodeType = gfx::SCENE_NODE_INVALID;
    switch((METAID)metatableID) {
        case SCENE_NODE_MT_ID:
            break;
        case SCENE_NODE_MESH_MT_ID:
            nodeType = gfx::SCENE_NODE_MESH;
            break;
        case SCENE_NODE_OBJECT_MT_ID:
            nodeType = gfx::SCENE_NODE_OBJECT;
            break;
        case SCENE_NODE_TRIGGER_MT_ID:
            nodeType = gfx::SCENE_NODE_TRIGGER;
            break;
        case GAME_ENTITY_MT_ID:
            nodeType = game::GAME_ENTITY;
            break;
        case GAME_ENTITY_MESH_MT_ID:
            nodeType = game::GAME_ENTITY_MESH;
            break;
            //case GAME_ENTITY_ACTOR_MT_ID:
            //    nodeType = game::GAME_ENTITY_ACTOR;
            //    break;
        default:
            break;
    };
    return (unsigned int)nodeType;
}

//------------------------------------------------------------------------------

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

    m_metatableInfoVec[EMPTY_MT_ID] = SMetatableInfo("FG_EMPTY", "X");

    m_metatableInfoVec[FG_NAMESPACE_MT_ID] = SMetatableInfo("FG", "N");
    m_metatableInfoVec[FG_GFX_NAMESPACE_MT_ID] = SMetatableInfo("FG_GFX", "N");
    m_metatableInfoVec[FG_GUI_NAMESPACE_MT_ID] = SMetatableInfo("FG_GUI", "N");
    m_metatableInfoVec[FG_SFX_NAMESPACE_MT_ID] = SMetatableInfo("FG_SFX", "N");

    m_metatableInfoVec[VECTOR2I_MT_ID] = SMetatableInfo("FG_VEC2I", "T");
    m_metatableInfoVec[VECTOR2F_MT_ID] = SMetatableInfo("FG_VEC2F", "T");
    m_metatableInfoVec[VECTOR3I_MT_ID] = SMetatableInfo("FG_VEC3I", "T");
    m_metatableInfoVec[VECTOR3F_MT_ID] = SMetatableInfo("FG_VEC3F", "T");
    m_metatableInfoVec[VECTOR4I_MT_ID] = SMetatableInfo("FG_VEC4I", "T");
    m_metatableInfoVec[VECTOR4F_MT_ID] = SMetatableInfo("FG_VEC4F", "T");

    m_metatableInfoVec[ERROR_MT_ID] = SMetatableInfo("FG_ERROR", "T");

    m_metatableInfoVec[EVENT_MANAGER_MT_ID] = SMetatableInfo("FG_EVT_MGR", "T");
    m_metatableInfoVec[RESOURCE_MANAGER_MT_ID] = SMetatableInfo("FG_RES_MGR", "T");
    m_metatableInfoVec[SHADER_MANAGER_MT_ID] = SMetatableInfo("FG_SHADER_MGR", "T");
    m_metatableInfoVec[SCENE2D_MANAGER_MT_ID] = SMetatableInfo("FG_2D_MGR", "T");
    m_metatableInfoVec[SCENE3D_MANAGER_MT_ID] = SMetatableInfo("FG_3D_MGR", "T");
    m_metatableInfoVec[PARTICLE_SYSTEM_MT_ID] = SMetatableInfo("FG_PARTICLE_SYS", "T");
    m_metatableInfoVec[GUI_MAIN_MT_ID] = SMetatableInfo("FG_GUI_MAIN", "T");
    m_metatableInfoVec[WIDGET_MANAGER_MT_ID] = SMetatableInfo("FG_WIDGET_MGR", "T");
    m_metatableInfoVec[STYLE_MANAGER_MT_ID] = SMetatableInfo("FG_STYLE_MGR", "T");
    m_metatableInfoVec[SOUND_MANAGER_MT_ID] = SMetatableInfo("FG_SOUND_MGR", "T");
    m_metatableInfoVec[GAME_MAIN_MGR_MT_ID] = SMetatableInfo("FG_GAME_MAIN", "T");

    m_metatableInfoVec[USER_DATA_MT_ID] = SMetatableInfo("FG_USER_DATA", "T");

    m_metatableInfoVec[RESOURCE_MT_ID] = SMetatableInfo("FG_RESOURCE", "T");
    m_metatableInfoVec[TEXTURE_RESOURCE_MT_ID] = SMetatableInfo("FG_TEXTURE", "T");
    m_metatableInfoVec[FONT_RESOURCE_MT_ID] = SMetatableInfo("FG_FONT", "T");
    m_metatableInfoVec[GFX_MODEL_RESOURCE_MT_ID] = SMetatableInfo("FG_MODEL", "T");
    m_metatableInfoVec[PARTICLE_EFFECT_RESOURCE_MT_ID] = SMetatableInfo("FG_PARTICLE", "T");
    m_metatableInfoVec[AUDIO_BASE_RES_MT_ID] = SMetatableInfo("FG_AUDIO_BASE", "T");
    m_metatableInfoVec[SOUND_RESOURCE_MT_ID] = SMetatableInfo("FG_SOUND", "T");
    m_metatableInfoVec[MUSIC_RESOURCE_MT_ID] = SMetatableInfo("FG_MUSIC", "T");
    m_metatableInfoVec[PLUGIN_RESOURCE_MT_ID] = SMetatableInfo("FG_PLUGIN", "T");
    m_metatableInfoVec[SAVE_FILE_RESOURCE_MT_ID] = SMetatableInfo("FG_SAVE_FILE", "T");

    // INI Config / Settings XML

    m_metatableInfoVec[CONFIG_MT_ID] = SMetatableInfo("FG_CONFIG", "T");
    m_metatableInfoVec[SETTINGS_MT_ID] = SMetatableInfo("FG_SETTINGS", "T");

    // GUI Widget structure metatables

    m_metatableInfoVec[GUI_WIDGET_MT_ID] = SMetatableInfo("FG_WIDGET", "T");
    m_metatableInfoVec[GUI_BUTTON_MT_ID] = SMetatableInfo("FG_BUTTON", "T");
    m_metatableInfoVec[GUI_CONSOLE_MT_ID] = SMetatableInfo("FG_CONSOLE", "T");
    m_metatableInfoVec[GUI_CONTAINER_MT_ID] = SMetatableInfo("FG_CONTAINER", "T");
    m_metatableInfoVec[GUI_FRAME_MT_ID] = SMetatableInfo("FG_FRAME", "T");
    m_metatableInfoVec[GUI_LABEL_MT_ID] = SMetatableInfo("FG_LABEL", "T");
    m_metatableInfoVec[GUI_LOADER_MT_ID] = SMetatableInfo("FG_LOADER", "T");
    m_metatableInfoVec[GUI_MENU_MT_ID] = SMetatableInfo("FG_MENU", "T");
    m_metatableInfoVec[GUI_MESSAGE_BOX_MT_ID] = SMetatableInfo("FG_MSG_BOX", "T");
    m_metatableInfoVec[GUI_POPUP_MT_ID] = SMetatableInfo("FG_POPUP", "T");
    m_metatableInfoVec[GUI_PROGRESS_BAR_MT_ID] = SMetatableInfo("FG_PROG_BAR", "T");
    m_metatableInfoVec[GUI_SCROLL_AREA_MT_ID] = SMetatableInfo("FG_SCROLL_AREA", "T");
    m_metatableInfoVec[GUI_TABLE_MT_ID] = SMetatableInfo("FG_GUI_TABLE", "T");
    m_metatableInfoVec[GUI_TEXT_AREA_MT_ID] = SMetatableInfo("FG_TEXT_AREA", "T");
    m_metatableInfoVec[GUI_TOGGLE_BUTTON_MT_ID] = SMetatableInfo("FG_TOGGLE", "T");
    m_metatableInfoVec[GUI_WINDOW_MT_ID] = SMetatableInfo("FG_GUI_WINDOW", "T");

    // GUI Style special structures

    m_metatableInfoVec[GUI_STYLE_MT_ID] = SMetatableInfo("FG_GUI_STYLE", "T");
    m_metatableInfoVec[GUI_STYLE_CONTENT_MT_ID] = SMetatableInfo("FG_STYLE_CONTENT", "T");
    m_metatableInfoVec[GUI_STYLE_SIZE_MT_ID] = SMetatableInfo("FG_ST_SIZE", "T");
    m_metatableInfoVec[GUI_STYLE_BACKGROUND_MT_ID] = SMetatableInfo("FG_ST_BG", "T");
    m_metatableInfoVec[GUI_STYLE_FOREGROUND_MT_ID] = SMetatableInfo("FG_ST_FG", "T");
    m_metatableInfoVec[GUI_STYLE_MARGIN_MT_ID] = SMetatableInfo("FG_ST_MARGIN", "T");
    m_metatableInfoVec[GUI_STYLE_PADDING_MT_ID] = SMetatableInfo("FG_ST_PADDING", "T");
    m_metatableInfoVec[GUI_STYLE_BORDER_INFO_MT_ID] = SMetatableInfo("FG_ST_BORDER_INFO", "T");
    m_metatableInfoVec[GUI_STYLE_BORDER_MT_ID] = SMetatableInfo("FG_ST_BORDER", "T");
    m_metatableInfoVec[GUI_STYLE_POSITION_MT_ID] = SMetatableInfo("FG_ST_POSITION", "T");

    // Thrown Event info structures 

    m_metatableInfoVec[EVENT_BASE_MT_ID] = SMetatableInfo("FG_EVENT_BASE", "T");
    m_metatableInfoVec[EVENT_CONTROLLER_DEVICE_MT_ID] = SMetatableInfo("FG_EVT_CTRL_DEVICE", "T");
    m_metatableInfoVec[EVENT_CONTROLLER_BUTTON_MT_ID] = SMetatableInfo("FG_EVT_CTRL_BUTTON", "T");
    m_metatableInfoVec[EVENT_CONTROLLER_AXIS_MT_ID] = SMetatableInfo("FG_EVT_CTRL_AXIS", "T");
    m_metatableInfoVec[EVENT_TOUCH_MT_ID] = SMetatableInfo("FG_EVT_TOUCH", "T");
    m_metatableInfoVec[EVENT_MOUSE_MT_ID] = SMetatableInfo("FG_EVT_MOUSE", "T");
    m_metatableInfoVec[EVENT_SWIPE_MT_ID] = SMetatableInfo("FG_EVT_SWIPE", "T");
    m_metatableInfoVec[EVENT_SWIPE_PINCH_MT_ID] = SMetatableInfo("FG_EVT_SWIPE_PINCH", "T");
    m_metatableInfoVec[EVENT_SWIPE_ROTATE_MT_ID] = SMetatableInfo("FG_EVT_SWIPE_ROTATE", "T");
    m_metatableInfoVec[EVENT_KEY_MT_ID] = SMetatableInfo("FG_EVT_KEY", "T");
    m_metatableInfoVec[EVENT_RESOURCE_MT_ID] = SMetatableInfo("FG_EVT_RESOURCE", "T");
    m_metatableInfoVec[EVENT_VERTEX_STREAM_MT_ID] = SMetatableInfo("FG_EVT_VERTEX_STREAM", "T");
    m_metatableInfoVec[EVENT_CAMERA_MT_ID] = SMetatableInfo("FG_EVT_CAMERA", "T");
    m_metatableInfoVec[EVENT_SOUND_MT_ID] = SMetatableInfo("FG_EVT_SOUND", "T");
    m_metatableInfoVec[EVENT_MENU_CHANGED_MT_ID] = SMetatableInfo("FG_EVT_MENU_CHANGED", "T");
    m_metatableInfoVec[EVENT_WIDGET_MT_ID] = SMetatableInfo("FG_EVT_WIDGET", "T");
    m_metatableInfoVec[EVENT_SENSORS_MT_ID] = SMetatableInfo("FG_EVT_SENSORS", "T");
    m_metatableInfoVec[EVENT_MAIN_MT_ID] = SMetatableInfo("FG_EVT_MAIN", "T");

    // Script callback type
    m_metatableInfoVec[SCRIPT_CALLBACK_MT_ID] = SMetatableInfo("FG_SCRIPT_CB", "T");

    // GFX Shader Program
    m_metatableInfoVec[SHADER_PROGRAM_MT_ID] = SMetatableInfo("FG_SHADER_PROG", "T");

    // Physics collision body
    m_metatableInfoVec[COLLISION_BODY_MT_ID] = SMetatableInfo("FG_COLLISION", "T");

    // Game objects
    m_metatableInfoVec[GAME_ENTITY_MT_ID] = SMetatableInfo("FG_GAME_ENT", "T");
    m_metatableInfoVec[GAME_ENTITY_MESH_MT_ID] = SMetatableInfo("FG_GAME_ENT_MESH", "T");

    // GFX Scene Node type
    m_metatableInfoVec[SCENE_NODE_MT_ID] = SMetatableInfo("FG_SCENE_NODE", "T");
    m_metatableInfoVec[SCENE_NODE_OBJECT_MT_ID] = SMetatableInfo("FG_SCENE_NODE_OBJ", "T");
    m_metatableInfoVec[SCENE_NODE_MESH_MT_ID] = SMetatableInfo("FG_SCENE_NODE_MESH", "T");
    m_metatableInfoVec[SCENE_NODE_TRIGGER_MT_ID] = SMetatableInfo("FG_SCENE_NODE_TRIGGER", "T");

    // GFX Scene Event types
    m_metatableInfoVec[EVENT_SCENE_NODE_MT_ID] = SMetatableInfo("FG_EVT_SCENE_NODE", "T");
    m_metatableInfoVec[EVENT_SCENE_NODE_COLLISION_MT_ID] = SMetatableInfo("FG_EVT_NODE_COLLIDE", "T");
    m_metatableInfoVec[EVENT_SCENE_NODE_TRIGGER_MT_ID] = SMetatableInfo("FG_EVT_NODE_TRIGGER", "T");
    m_metatableInfoVec[EVENT_SCENE_MAIN_MT_ID] = SMetatableInfo("FG_EVT_SCENE_MAIN", "T");

#endif

    for(int i = 0; i < (int)METATABLE_SIZE; i++) {
        m_metatableInfoVec[i].id = (unsigned short int)i;
        FG_LOG_DEBUG("ScriptMT: Generated metatable name id[%d], name[%s]", i, m_metatableInfoVec[i].name);
    }
}
//------------------------------------------------------------------------------

void script::CMetatables::clearMetatableNames(void) {
    m_metatableInfoVec.clear();
    MetatableInfoVec smvec;
    m_metatableInfoVec.swap(smvec);
}
//------------------------------------------------------------------------------
