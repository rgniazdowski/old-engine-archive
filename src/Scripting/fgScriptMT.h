/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgScriptMT.h
 * Author: vigilant
 *
 * Created on November 6, 2014, 4:49 PM
 */

#ifndef _FG_SCRIPT_MT_H_
    #define _FG_SCRIPT_MT_H_
    #define _FG_SCRIPT_MT_H_BLOCK_

    #ifndef _FG_TYPES_H_
        #include "fgTypes.h"
    #endif

class fgScriptSubsystem;

/**
 * 
 */
class fgScriptMT {
    friend class fgScriptSubsystem;
public:

    enum METAID {
        EMPTY_MT_ID = 0,

        //
        // Vectors / Color
        //
        VECTOR2I_MT_ID = 1, // #used
        VECTOR2F_MT_ID = 2, // #used
        VECTOR3I_MT_ID = 3, // #used
        VECTOR3F_MT_ID = 4, // #used
        VECTOR4I_MT_ID = 5, // #used
        VECTOR4F_MT_ID = 6, // #used

        ERROR_MT_ID = 7,

        //
        // Main managers
        //
        EVENT_MANAGER_MT_ID = 8,
        RESOURCE_MANAGER_MT_ID = 9, // #used
        SHADER_MANAGER_MT_ID = 10,
        SCENE2D_MANAGER_MT_ID = 11,
        SCENE3D_MANAGER_MT_ID = 12,
        PARTICLE_SYSTEM_MT_ID = 13,
        WIDGET_MANAGER_MT_ID = 14, // #used
        STYLE_MANAGER_MT_ID = 15,
        SOUND_MANAGER_MT_ID = 16,

        //
        // Resources 
        //
        RESOURCE_MT_ID = 17, // #used
        TEXTURE_RESOURCE_MT_ID = 18, // #used
        FONT_RESOURCE_MT_ID = 19, // #used
        GFX_MODEL_RESOURCE_MT_ID = 20, // #used
        PARTICLE_EFFECT_RESOURCE_MT_ID = 21, // #used
        SOUND_RESOURCE_MT_ID = 22,
        MUSIC_RESOURCE_MT_ID = 23,
        PLUGIN_RESOURCE_MT_ID = 24,
        SAVE_FILE_RESOURCE_MT_ID = 25,

        //
        // Settings / Config
        //

        CONFIG_MT_ID = 26,
        SETTINGS_MT_ID = 27,

        //
        // GUI Objects/Widgets
        //
        GUI_WIDGET_MT_ID = 28, // #used
        GUI_BUTTON_MT_ID = 29, // #used
        GUI_CONSOLE_MT_ID = 30, // #used
        GUI_CONTAINER_MT_ID = 31, // #used
        GUI_FRAME_MT_ID = 32, // #used
        GUI_LABEL_MT_ID = 33, // #used
        GUI_LOADER_MT_ID = 34, // #used
        GUI_MENU_MT_ID = 35, // #used
        GUI_MESSAGE_BOX_MT_ID = 36, // #used
        GUI_POPUP_MT_ID = 37, // #used
        GUI_PROGRESS_BAR_MT_ID = 38, // #used
        GUI_SCROLL_AREA_MT_ID = 39, // #used
        GUI_TABLE_MT_ID = 48, // #used
        GUI_TEXT_AREA_MT_ID = 49, // #used
        GUI_TOGGLE_BUTTON_MT_ID = 50, // #used
        GUI_WINDOW_MT_ID = 51, // #used

        //
        // GUI Style / Style Content
        //

        GUI_STYLE_MT_ID = 40, // base style meta
        GUI_STYLE_CONTENT_MT_ID = 41,
        GUI_STYLE_SIZE_MT_ID = 42,
        GUI_STYLE_BACKGROUND_MT_ID = 43,
        GUI_STYLE_FOREGROUND_MT_ID = 44,
        GUI_STYLE_MARGIN_MT_ID = 45,
        //GUI_STYLE_PADDING_MT_ID = 45, // this is the same as margin
        GUI_STYLE_BORDER_INFO_MT_ID = 46,
        GUI_STYLE_BORDER_MT_ID = 46,
        GUI_STYLE_POSITION_MT_ID = 47,
        //GUI_STYLE_ALIGN_MT_ID = XX, // this is enum ...

        //
        // Event structures
        //

        EVENT_BASE_MT_ID = 52, // fgEventbase
        EVENT_CONTROLLER_DEVICE_MT_ID = 53, // fgControllerDeviceEvent
        EVENT_CONTROLLER_BUTTON_MT_ID = 54, // fgControllerButtonEvent
        EVENT_CONTROLLER_AXIS_MT_ID = 55, // fgControllerAxisEvent
        EVENT_TOUCH_MT_ID = 56, // fgTouchEvent
        EVENT_MOUSE_MT_ID = 57, // fgMouseEvent
        EVENT_SWIPE_MT_ID = 58, // fgSwipeEvent
        EVENT_SWIPE_PINCH_MT_ID = 59, // fgSwipePinch
        EVENT_SWIPE_ROTATE_MT_ID = 60, // fgSwipeRotate
        EVENT_KEY_MT_ID = 61, // fgKeyEvent
        EVENT_RESOURCE_MT_ID = 62, // fgResourceEvent
        EVENT_VERTEX_STREAM_MT_ID = 63, // fgVertexStream
        EVENT_CAMERA_MT_ID = 64, // fgCameraEvent
        EVENT_SOUND_MT_ID = 65, // fgSoundEvent
        EVENT_MENU_CHANGED_MT_ID = 66, // fgMenuChangedEvent
        EVENT_WIDGET_MT_ID = 67, // fgWidgetEvent
        EVENT_SENSORS_MT_ID = 68, // fgSensorsEvent
        EVENT_MAIN_MT_ID = 69, // union struct: fgEvent

        //
        // Special Callback type 
        //
        SCRIPT_CALLBACK_MT_ID = 70,

        METATABLE_SIZE
    };
private:

    /**
     * 
     */
    struct metatableInfo {
        ///
        static const unsigned char NAME_MAX_LENGTH = 24;
        ///
        unsigned short int id;
        ///
        char name[NAME_MAX_LENGTH];
        /**
         * 
         */
        metatableInfo() : id(0) {
            randomizeName();
            //FG_LOG_DEBUG("Script: metatableInfo: name: '%s'", name);
        }
        /**
         * 
         * @param _id
         * @param _name
         */
        metatableInfo(const int _id, const char *_name) : id(_id) {
            if(_name)
                strncpy(name, _name, (int)NAME_MAX_LENGTH);
            else
                memset(name, 0, (int)NAME_MAX_LENGTH);
        }
        /**
         * 
         * @param _name
         */
        metatableInfo(const char *_name) : id(0) {
            if(_name)
                strncpy(name, _name, (int)NAME_MAX_LENGTH);
            else
                memset(name, 0, (int)NAME_MAX_LENGTH);
        }
        /**
         * 
         * @param prefix
         * @param suffix
         */
        metatableInfo(const char *prefix, const char *suffix) : id(0) {
            randomizeName(prefix, suffix);
            //FG_LOG_DEBUG("Script: metatableInfo: name: '%s'", name);

        }
        /**
         * 
         * @param _id
         * @param prefix
         * @param suffix
         */
        metatableInfo(const unsigned short int _id, const char *prefix, const char *suffix) : id(_id) {
            randomizeName(prefix, suffix);
        }
        /**
         * 
         * @param prefix
         * @param suffix
         */
        char* randomizeName(const char *prefix = NULL, const char *suffix = NULL) {
            if(!name)
                return name;
            memset(name, 0, (int)NAME_MAX_LENGTH);
            int i = 0, j = 0, suflen = 0, limit = NAME_MAX_LENGTH - 1;
            // Numbers 0 - 9 ASCII 48 to 57
            // Uppercase letters A - Z ASCII 65 - 90
            // Lowercase letters a - z ASCII 97 to 122
            int _n[2] = {48, 57};
            int _u[2] = {65, 90};
            int _l[2] = {97, 122};
            int *_c[3] = {_n, _u, _l};
            if(prefix) {
                sprintf(name, "%s", prefix);
                i = strlen(name);
            } else {
                // without prefix need to ensure that beginning is alpha
                for(; i < 3; i++) {
                    j = 1;
                    name[i] = (char)FG_RAND(_c[j][0], _c[j][1]);
                }
            }
            name[i] = '_', i++;
            if(suffix) {
                suflen = (int)strlen(suffix);
                limit -= suflen;
            } else {
                limit++;
            }
            for(; i < limit - 1; i++) {
                j = FG_RAND(0, 2);
                name[i] = (char)FG_RAND(_c[j][0], _c[j][1]);
            }
            if(suffix) {
                name[i] = '_', i++;
                for(j = 0; i < NAME_MAX_LENGTH - 1 && j < suflen; i++, j++) {
                    name[i] = suffix[j];
                }
            }
            return name;
        }
    };

    ///
    typedef fgVector<metatableInfo> metatableInfoVec;
    ///
    typedef metatableInfoVec::iterator metatableInfoVecItor;

private:
    ///
    static metatableInfoVec m_metatableInfoVec;

private:
    /**
     * 
     */
    fgScriptMT();
    /**
     * 
     * @param orig
     */
    fgScriptMT(const fgScriptMT& orig);
    /**
     * 
     */
    virtual ~fgScriptMT();

private:
    /**
     * 
     */
    static void generateMetatableNames(void);

    /**
     * 
     * @param widgetType
     * @return 
     */
    static void clearMetatableNames(void);

public:
    /**
     * 
     * @param metatableID
     * @return 
     */
    static inline const char *getMetatableName(const unsigned short int metatableID) {
        const char *failedName = "__NO_B33F_";
        if(m_metatableInfoVec.empty())
            return failedName; // #FIXME
        if(metatableID >= m_metatableInfoVec.size())
            return failedName;
        return m_metatableInfoVec[metatableID].name;
    }

    /**
     * 
     * @param widgetType
     * @return 
     */
    static METAID getMetatableIDFromWidgetType(const unsigned int widgetType);
    
    /**
     * 
     * @param widgetType
     * @return 
     */
    static inline const char *getMetatableNameFromWidgetType(const unsigned int widgetType) {
        return getMetatableName(getMetatableIDFromWidgetType(widgetType));
    }
    
    /**
     * 
     * @param resourceType
     * @return 
     */    
    static METAID getMetatableIDFromResourceType(const unsigned int resourceType);
    
    /**
     * 
     * @param resourceType
     * @return 
     */
    static inline const char *getMetatableNameFromResourceType(const unsigned int resourceType) {
        return getMetatableName(getMetatableIDFromResourceType(resourceType));
    }

};

    #undef _FG_SCRIPT_MT_H_BLOCK_
#endif	/* _FG_SCRIPT_MT_H_ */

