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
 * File:   fgScriptMT.h
 * Author: vigilant
 *
 * Created on November 6, 2014, 4:49 PM
 */

#ifndef FG_INC_SCRIPT_MT
    #define FG_INC_SCRIPT_MT
    #define FG_INC_SCRIPT_MT_BLOCK

    #include "fgBuildConfig.h"
    #include "fgTypes.h"
    #include "fgSingleton.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif /* FG_USING_LUA_PLUS */

namespace fg {
    namespace script {
        class CScriptSubsystem;

        /**
         * 
         */
        class CMetatables : public CSingleton<CMetatables> {
            ///
            friend class CSingleton<CMetatables>;
            ///
            friend class fg::script::CScriptSubsystem;
        public:

            enum METAID {
                EMPTY_MT_ID = 0,

                //
                // FG main namespaces
                //
                FG_NAMESPACE_MT_ID, // #used
                FG_GFX_NAMESPACE_MT_ID,
                FG_GUI_NAMESPACE_MT_ID,
                FG_SFX_NAMESPACE_MT_ID,
                //
                // Main managers
                //
                EVENT_MANAGER_MT_ID,
                RESOURCE_MANAGER_MT_ID, // #used
                SHADER_MANAGER_MT_ID,
                SCENE2D_MANAGER_MT_ID,
                SCENE3D_MANAGER_MT_ID,
                PARTICLE_SYSTEM_MT_ID,
                GUI_MAIN_MT_ID,
                WIDGET_MANAGER_MT_ID, // #used
                STYLE_MANAGER_MT_ID,
                SOUND_MANAGER_MT_ID,
                GAME_MAIN_MGR_MT_ID,

                USER_DATA_MT_ID, // base metatable type 

                //
                // Vectors / Color
                //
                VECTOR2I_MT_ID, // #used
                VECTOR2F_MT_ID, // #used
                VECTOR3I_MT_ID, // #used
                VECTOR3F_MT_ID, // #used
                VECTOR4I_MT_ID, // #used
                VECTOR4F_MT_ID, // #used

                ERROR_MT_ID,

                //
                // Resources 
                //
                RESOURCE_MT_ID, // #used
                TEXTURE_RESOURCE_MT_ID, // #used
                FONT_RESOURCE_MT_ID, // #used
                GFX_MODEL_RESOURCE_MT_ID, // #used
                PARTICLE_EFFECT_RESOURCE_MT_ID, // #used
                AUDIO_BASE_RES_MT_ID,
                SOUND_RESOURCE_MT_ID,
                MUSIC_RESOURCE_MT_ID,
                PLUGIN_RESOURCE_MT_ID,
                SAVE_FILE_RESOURCE_MT_ID,

                //
                // Settings / Config
                //

                CONFIG_MT_ID,
                SETTINGS_MT_ID,

                //
                // GUI Objects/Widgets
                //
                GUI_WIDGET_MT_ID, // #used
                GUI_BUTTON_MT_ID, // #used
                GUI_CONSOLE_MT_ID, // #used
                GUI_CONTAINER_MT_ID, // #used
                GUI_FRAME_MT_ID, // #used
                GUI_LABEL_MT_ID, // #used
                GUI_LOADER_MT_ID, // #used
                GUI_MENU_MT_ID, // #used
                GUI_MESSAGE_BOX_MT_ID, // #used
                GUI_POPUP_MT_ID, // #used
                GUI_PROGRESS_BAR_MT_ID, // #used
                GUI_SCROLL_AREA_MT_ID, // #used
                GUI_TABLE_MT_ID, // #used
                GUI_TEXT_AREA_MT_ID, // #used
                GUI_TOGGLE_BUTTON_MT_ID, // #used
                GUI_WINDOW_MT_ID, // #used

                //
                // GUI Style / Style Content
                //

                GUI_STYLE_MT_ID, // base style meta
                GUI_STYLE_CONTENT_MT_ID,
                GUI_STYLE_SIZE_MT_ID,
                GUI_STYLE_BACKGROUND_MT_ID,
                GUI_STYLE_FOREGROUND_MT_ID,
                GUI_STYLE_MARGIN_MT_ID,
                GUI_STYLE_PADDING_MT_ID, // this is the same as margin
                GUI_STYLE_BORDER_INFO_MT_ID,
                GUI_STYLE_BORDER_MT_ID,
                GUI_STYLE_POSITION_MT_ID,
                //GUI_STYLE_ALIGN_MT_ID = XX, // this is enum ...

                //
                // Event structures
                //

                EVENT_BASE_MT_ID, // fgEventbase
                EVENT_CONTROLLER_DEVICE_MT_ID, // fgControllerDeviceEvent
                EVENT_CONTROLLER_BUTTON_MT_ID, // fgControllerButtonEvent
                EVENT_CONTROLLER_AXIS_MT_ID, // fgControllerAxisEvent
                EVENT_TOUCH_MT_ID, // fgTouchEvent
                EVENT_MOUSE_MT_ID, // fgMouseEvent
                EVENT_SWIPE_MT_ID, // fgSwipeEvent
                EVENT_SWIPE_PINCH_MT_ID, // fgSwipePinch
                EVENT_SWIPE_ROTATE_MT_ID, // fgSwipeRotate
                EVENT_KEY_MT_ID, // fgKeyEvent
                EVENT_RESOURCE_MT_ID, // fgResourceEvent
                EVENT_VERTEX_STREAM_MT_ID, // fgVertexStream
                EVENT_CAMERA_MT_ID, // fgCameraEvent
                EVENT_SOUND_MT_ID, // fgSoundEvent
                EVENT_MENU_CHANGED_MT_ID, // fgMenuChangedEvent
                EVENT_WIDGET_MT_ID, // fgWidgetEvent
                EVENT_SENSORS_MT_ID, // fgSensorsEvent
                EVENT_MAIN_MT_ID, // union struct: fgEvent

                //
                // Special Callback type 
                //
                SCRIPT_CALLBACK_MT_ID,

                //
                // GFX other
                //
                SHADER_PROGRAM_MT_ID,

                //
                // Physics
                //
                COLLISION_BODY_MT_ID,

                //
                // Game objects
                //
                GAME_ENTITY_MT_ID,
                GAME_ENTITY_MESH_MT_ID,
                GAME_ENTITY_ACTOR_MT_ID,

                //
                // 3D/2D GFX Scene Node & other types
                //
                SCENE_NODE_MT_ID, // gfx::CSceneNode
                SCENE_NODE_OBJECT_MT_ID, // gfx::CSceneNodeObject
                SCENE_NODE_MESH_MT_ID, // gfx::CSceneNodeMesh
                SCENE_NODE_TRIGGER_MT_ID, // gfx::CSceneNodeTrigger

                EVENT_SCENE_NODE_MT_ID, // event::SSceneNode
                EVENT_SCENE_NODE_COLLISION_MT_ID, // event::SSceneNodeCollision
                EVENT_SCENE_NODE_TRIGGER_MT_ID, // event::SSceneNodeTrigger
                EVENT_SCENE_MAIN_MT_ID, // event::SSceneEvent - union

                METATABLE_SIZE
            };
        private:

            /**
             * 
             */
            struct SMetatableInfo {
                ///
                static const unsigned char NAME_MAX_LENGTH = 24;
                ///
                unsigned short int id;
                ///
                char name[NAME_MAX_LENGTH];
                ///
    #if defined(FG_USING_LUA_PLUS)
                LuaPlus::LuaObject metaObj;
    #endif /* FG_USING_LUA_PLUS */
                /**
                 * 
                 */
                SMetatableInfo() : id(0) {
                    randomizeName();
                    //FG_LOG_DEBUG("Script: metatableInfo: name: '%s'", name);
                }
                /**
                 * 
                 * @param _id
                 * @param _name
                 */
                SMetatableInfo(const int _id, const char *_name) : id(_id) {
                    if(_name)
                        strncpy(name, _name, (int)NAME_MAX_LENGTH);
                    else
                        memset(name, 0, (int)NAME_MAX_LENGTH);
                }
                /**
                 * 
                 * @param _name
                 */
                SMetatableInfo(const char *_name) : id(0) {
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
                SMetatableInfo(const char *prefix, const char *suffix) : id(0) {
                    randomizeName(prefix, suffix);
                    //FG_LOG_DEBUG("Script: metatableInfo: name: '%s'", name);

                }
                /**
                 * 
                 * @param _id
                 * @param prefix
                 * @param suffix
                 */
                SMetatableInfo(const unsigned short int _id, const char *prefix, const char *suffix) : id(_id) {
                    randomizeName(prefix, suffix);
                }
                ~SMetatableInfo() {
    #if defined(FG_USING_LUA_PLUS)
                    // ?
    #endif
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
            }; // struct SMetatableInfo

            ///
            typedef fg::CVector<SMetatableInfo> MetatableInfoVec;
            ///
            typedef MetatableInfoVec::iterator MetatableInfoVecItor;

        private:
            ///
            MetatableInfoVec m_metatableInfoVec;

        protected:
            /**
             * 
             */
            CMetatables();
            /**
             * 
             */
            virtual ~CMetatables();

        private:
            /**
             * 
             */
            void generateMetatableNames(void);

            /**
             * 
             * @param widgetType
             * @return 
             */
            void clearMetatableNames(void);

        public:
            /**
             * 
             * @param metatableID
             * @return 
             */
            inline const char *getMetatableName(const unsigned short int metatableID) {
                //const char *failedName = "__NO_B33F_";
                const char *failedName = m_metatableInfoVec[EMPTY_MT_ID].name;
                if(m_metatableInfoVec.empty())
                    return failedName; // #FIXME
                if(metatableID >= m_metatableInfoVec.size())
                    return failedName;
                return m_metatableInfoVec[metatableID].name;
            }
            inline SMetatableInfo& getMetatable(const unsigned short int metatableID) {
                if(metatableID >= m_metatableInfoVec.size())
                    return m_metatableInfoVec[0];
                return m_metatableInfoVec[metatableID];
            }
            inline SMetatableInfo const& getMetatable(const unsigned short int metatableID) const {
                if(metatableID >= m_metatableInfoVec.size())
                    return m_metatableInfoVec[0];
                return m_metatableInfoVec[metatableID];
            }

            //------------------------------------------------------------------

            /**
             * 
             * @param widgetType
             * @return 
             */
            METAID getMetatableIDFromWidgetType(const unsigned int widgetType);

            unsigned int getWidgetTypeFromMetatableID(const unsigned int metatableID);
            /**
             * 
             * @param widgetType
             * @return 
             */
            inline const char *getMetatableNameFromWidgetType(const unsigned int widgetType) {
                return getMetatableName(getMetatableIDFromWidgetType(widgetType));
            }

            //------------------------------------------------------------------

            /**
             * 
             * @param resourceType
             * @return 
             */
            METAID getMetatableIDFromResourceType(const unsigned int resourceType);

            unsigned int getResourceTypeFromMetatableID(const unsigned short int metatableID);
            /**
             * 
             * @param resourceType
             * @return 
             */
            inline const char *getMetatableNameFromResourceType(const unsigned int resourceType) {
                return getMetatableName(getMetatableIDFromResourceType(resourceType));
            }

            //------------------------------------------------------------------

            METAID getMetatableIDFromNodeType(const unsigned int nodeType);
            unsigned int getNodeTypeFromMetatableID(const unsigned short int metatableID);
            inline const char *getMetatableNameFromNodeType(const unsigned int nodeType) {
                return getMetatableName(getMetatableIDFromNodeType(nodeType));
            }
            //------------------------------------------------------------------
        };

    } // namespace script
} // namespace fg

    #define fgScriptMT fg::script::CMetatables::getInstance()

    #undef FG_INC_SCRIPT_MT_BLOCK
#endif	/* FG_INC_SCRIPT_MT */
