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
 * File:   fgScriptCD.h
 * Author: vigilant
 *
 * Created on November 6, 2014, 4:45 PM
 */

#ifndef FG_INC_SCRIPT_CD
    #define FG_INC_SCRIPT_CD
    #define FG_INC_SCRIPT_CD_BLOCK  

    #if defined(FG_INC_SCRIPT_MT_BLOCK)
        #error "FG_SCRIPT_MTBLOCK is defined: Do not include ScriptCD header inside of ScriptMetatables header"
    #endif

    #if defined(FG_INC_EVENT_DEFINITIONS_BLOCK)
        #error "FG_EVENT_DEFINITIONSBLOCK is defined: Do not include ScriptCD header inside of EventDefinitions header"
    #endif

    #include "fgBuildConfig.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif

    #ifndef FG_INC_GFX_TYPES
        #include "GFX/fgGFXTypes.h"
    #endif

    #ifndef FG_INC_GFX_SCENE_NODE
        #include "GFX/Scene/fgGFXSceneNode.h"
    #endif

    #ifndef FG_INC_GFX_SCENE_NODE_TRIGGER
        #include "GFX/Scene/fgGFXSceneNodeTrigger.h"
    #endif
    
    #ifndef FG_INC_GFX_SCENE_EVENT
        #include "GFX/Scene/fgGFXSceneEvent.h"
    #endif

    #ifndef FG_INC_GFX_MODEL_RESOURCE
        #include "GFX/fgGFXModelResource.h"
    #endif

    #ifndef FG_INC_SCRIPT_MT
        #include "fgScriptMT.h"
    #endif

    #ifndef FG_INC_GUI_WIDGET
        #include "GUI/fgGuiWidget.h"
    #endif

    #ifndef FG_INC_EVENT_DEFINITIONS
        #include "Event/fgEventDefinitions.h"
    #endif

    #ifndef FG_INC_SFX_AUDIO_BASE
        #include "Audio/fgSFXAudioBase.h"
    #endif

    #ifndef FG_INC_SFX_MUSIC_RESOURCE
        #include "Audio/fgSFXMusicResource.h"
    #endif

    #ifndef FG_INC_SFX_SOUND_RESOURCE
        #include "Audio/fgSFXSoundResource.h"
    #endif

    #include "fgLog.h"

namespace fg {
    namespace script {
        class CScriptSubsystem;

        /**
         * 
         */
        class CCallbackDispatchHelper {
            friend class fg::script::CScriptSubsystem;
        private:
            /**
             * 
             */
            CCallbackDispatchHelper() { }
            /**
             *
             */
            ~CCallbackDispatchHelper() { }

        private:

        };
    };
};

////////////////////////////////////////////////////////////////////////////////

    #if defined(FG_USING_LUA_PLUS)

namespace LPCD {

    /***************************************************************************
     * FG VECTOR 2I
     **************************************************************************/

    template<> struct Type<fg::Vector2i> {
        static inline void Push(lua_State* L, const fg::Vector2i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector2i]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR2I_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR2I_MT_ID)];
        }
        static inline fg::Vector2i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::Vector2i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::Vector2i&> : public Type<fg::Vector2i> {
    };

    template<> struct Type<const fg::Vector2i&> : public Type<fg::Vector2i> {
    };

    /***************************************************************************
     * FG VECTOR 2F
     **************************************************************************/

    template<> struct Type<fg::Vector2f> {
        static inline void Push(lua_State* L, const fg::Vector2f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector2f]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR2F_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR2F_MT_ID)];
        }
        static inline fg::Vector2f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::Vector2f* ptr = (fg::Vector2f *)state->UnBoxPointer(idx);
            return *ptr;
        }
    };

    template<> struct Type<fg::Vector2f&> : public Type<fg::Vector2f> {
    };

    template<> struct Type<const fg::Vector2f&> : public Type<fg::Vector2f> {
    };

    /***************************************************************************
     * FG VECTOR 3I
     **************************************************************************/

    template<> struct Type<fg::Vector3i> {
        static inline void Push(lua_State* L, const fg::Vector3i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector3i]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR3I_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR3I_MT_ID)];
        }
        static inline fg::Vector3i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::Vector3i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::Vector3i&> : public Type<fg::Vector3i> {
    };

    template<> struct Type<const fg::Vector3i&> : public Type<fg::Vector3i> {
    };

    /***************************************************************************
     * FG VECTOR 3F
     **************************************************************************/

    template<> struct Type<fg::Vector3f> {
        static inline void Push(lua_State* L, const fg::Vector3f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector3f]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR3F_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR3F_MT_ID)];
        }
        static inline fg::Vector3f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::Vector3f*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::Vector3f&> : public Type<fg::Vector3f> {
    };

    template<> struct Type<const fg::Vector3f&> : public Type<fg::Vector3f> {
    };

    /***************************************************************************
     * FG VECTOR 4I
     **************************************************************************/

    template<> struct Type<fg::Vector4i> {
        static inline void Push(lua_State* L, const fg::Vector4i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector4i]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR4I_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR4I_MT_ID)];
        }
        static inline fg::Vector4i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::Vector4i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::Vector4i&> : public Type<fg::Vector4i> {
    };

    template<> struct Type<const fg::Vector4i&> : public Type<fg::Vector4i> {
    };

    /***************************************************************************
     * FG VECTOR 4F
     **************************************************************************/

    template<> struct Type<fg::Vector4f> {
        static inline void Push(lua_State* L, const fg::Vector4f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector4f]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR4F_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::VECTOR4F_MT_ID)];
        }
        static inline fg::Vector4f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::Vector4f*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::Vector4f&> : public Type<fg::Vector4f> {
    };

    template<> struct Type<const fg::Vector4f&> : public Type<fg::Vector4f> {
    };
}

////////////////////////////////////////////////////////////////////////////////

namespace LPCD {

    template<> struct Type<std::string> {
        static inline void Push(lua_State* L, const std::string& value) {
            lua_pushstring(L, value.c_str());
        }
        static inline bool Match(lua_State* L, int idx) {
            return lua_type(L, idx) == LUA_TSTRING;
        }
        static inline std::string Get(lua_State* L, int idx) {
            return lua_tostring(L, idx);
        }
    };

    template<> struct Type<std::string&> : public Type<std::string> {
    };

    template<> struct Type<const std::string&> : public Type<std::string> {
    };

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fgResource pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::resource::CResource *> {
        static inline void Push(lua_State* L, const fg::resource::CResource * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            // #FIXME - some checking if the pointer isn't null (!)
            fg::script::CMetatables::METAID metaID = fgScriptMT->getMetatableIDFromResourceType(value->getResourceType());
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s]", value, (uintptr_t)value, value->getNameStr());
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result; // = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WIDGET_MT_ID)]);
            // This is fubar. No, really fucked up
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fg::resource::CResource * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::resource::CResource *pResource = (fg::resource::CResource *)state->UnBoxPointer(idx);
            return pResource;
        }
    };

    template<> struct Type<fg::resource::CResource *&> : public Type<fg::resource::CResource *> {
    };

    template<> struct Type<const fg::resource::CResource *&> : public Type<fg::resource::CResource *> {
    };

    /***************************************************************************
     * fgGuiWidget pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::gui::CWidget *> {
        static inline void Push(lua_State* L, const fg::gui::CWidget * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fg::script::CMetatables::METAID metaID = fgScriptMT->getMetatableIDFromWidgetType(value->getType());
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[%s]", value, (uintptr_t)value, value->getNameStr(), value->getTypeNameStr());
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result; // = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WIDGET_MT_ID)]);
            // This is fubar
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fg::gui::CWidget * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::gui::CWidget *pWidget = (fg::gui::CWidget *)state->UnBoxPointer(idx);
            return pWidget;
        }
    };

    template<> struct Type<fg::gui::CWidget *&> : public Type<fg::gui::CWidget *> {
    };

    template<> struct Type<const fg::gui::CWidget *&> : public Type<fg::gui::CWidget *> {
    };

    ////////////////////////////////////////////////////////////////////////////
    // FG GUI STYLE STRUCTURES
    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fgGuiStyleContent pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::gui::CStyleContent *> {
        static inline void Push(lua_State* L, const fg::gui::CStyleContent * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::GUI_STYLE_CONTENT_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiStyleContent]", value, (uintptr_t)value);
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_CONTENT_MT_ID)]);
            // This is fubar
            //result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fg::gui::CStyleContent * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::gui::CStyleContent *pStyleContent = (fg::gui::CStyleContent *)state->UnBoxPointer(idx);
            return pStyleContent;
        }
    };

    template<> struct Type<fg::gui::CStyleContent *&> : public Type<fg::gui::CStyleContent *> {
    };

    template<> struct Type<const fg::gui::CStyleContent *&> : public Type<fg::gui::CStyleContent *> {
    };

    /***************************************************************************
     * FG GUI SIZE STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SSize> {
        static inline void Push(lua_State* L, const fg::gui::SSize& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiSize]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_SIZE_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_SIZE_MT_ID)];
        }
        static inline fg::gui::SSize Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SSize*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SSize&> : public Type<fg::gui::SSize> {
    };

    template<> struct Type<const fg::gui::SSize&> : public Type<fg::gui::SSize> {
    };

    /***************************************************************************
     * FG GUI BACKGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SBackground> {
        static inline void Push(lua_State* L, const fg::gui::SBackground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiBackground]", ptr, (uintptr_t)ptr);
            //FG_LOG_DEBUG("Script: LPCD Push: type[fgGuiBackground], color[%.2f %.2f %.2f %.2f]", value.color.r, value.color.g, value.color.b, value.color.a);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_BACKGROUND_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_BACKGROUND_MT_ID)];
        }
        static inline fg::gui::SBackground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SBackground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SBackground&> : public Type<fg::gui::SBackground> {
    };

    template<> struct Type<const fg::gui::SBackground&> : public Type<fg::gui::SBackground> {
    };

    /***************************************************************************
     * FG GUI FOREGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SForeground> {
        static inline void Push(lua_State* L, const fg::gui::SForeground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiForeground]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_FOREGROUND_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_FOREGROUND_MT_ID)];
        }
        static inline fg::gui::SForeground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SForeground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SForeground&> : public Type<fg::gui::SForeground> {
    };

    template<> struct Type<const fg::gui::SForeground&> : public Type<fg::gui::SForeground> {
    };

    /***************************************************************************
     * FG GUI MARGIN STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SMargin> {
        static inline void Push(lua_State* L, const fg::gui::SMargin& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiMargin]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_MARGIN_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_MARGIN_MT_ID)];
        }
        static inline fg::gui::SMargin Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SMargin*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SMargin&> : public Type<fg::gui::SMargin> {
    };

    template<> struct Type<const fg::gui::SMargin&> : public Type<fg::gui::SMargin> {
    };

    /***************************************************************************
     * FG GUI PADDING STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SPadding> {
        static inline void Push(lua_State* L, const fg::gui::SPadding& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiPadding]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_PADDING_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_PADDING_MT_ID)];
        }
        static inline fg::gui::SPadding Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SPadding*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SPadding&> : public Type<fg::gui::SPadding> {
    };

    template<> struct Type<const fg::gui::SPadding&> : public Type<fg::gui::SPadding> {
    };

    /***************************************************************************
     * FG GUI BORDER INFO STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SBorderGroup> {
        static inline void Push(lua_State* L, const fg::gui::SBorderGroup& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiBorderInfo]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_BORDER_INFO_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_BORDER_INFO_MT_ID)];
        }
        static inline fg::gui::SBorderGroup Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SBorderGroup*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SBorderGroup&> : public Type<fg::gui::SBorderGroup> {
    };

    template<> struct Type<const fg::gui::SBorderGroup&> : public Type<fg::gui::SBorderGroup> {
    };

    /***************************************************************************
     * FG GUI BORDER STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SBorder> {
        static inline void Push(lua_State* L, const fg::gui::SBorder& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiBorder]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_BORDER_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_BORDER_MT_ID)];
        }
        static inline fg::gui::SBorder Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SBorder*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SBorder&> : public Type<fg::gui::SBorder> {
    };

    template<> struct Type<const fg::gui::SBorder&> : public Type<fg::gui::SBorder> {
    };

    /***************************************************************************
     * FG GUI POSITION STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SPosition> {
        static inline void Push(lua_State* L, const fg::gui::SPosition& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgGuiPosition]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_POSITION_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::GUI_STYLE_POSITION_MT_ID)];
        }
        static inline fg::gui::SPosition Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SPosition*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SPosition&> : public Type<fg::gui::SPosition> {
    };

    template<> struct Type<const fg::gui::SPosition&> : public Type<fg::gui::SPosition> {
    };

    /***************************************************************************
     * FG GUI ENUMERATION TYPES -> INT
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::gui::CWidget::State

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned int> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned int>::Push(L, static_cast<unsigned int>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned int>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::Unit

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE
    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::SBorder::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::SBorder::Which

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::SBackground::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::SMargin::Which

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::SPadding::Which

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::Align

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::SPosition::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gui::SSize::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * FG GUI ENUMERATION TYPES -> INT
     **************************************************************************/

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::event::SSwipe::Direction

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<int> {
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::event::SSwipePinch::Direction

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<int> {
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::event::SResource::Status

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<int> {
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * fgEvent pointer parameter * (this is union parameter) - only passed as *
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SEvent

    template<> struct Type<FG_CONV_CD_TYPE *> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_MAIN_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SEvent].union", value, (uintptr_t)value);
        #endif
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_MAIN_MT_ID)]);
            // This is fubar
            //result = (bool) obj.IsUserdata();
            return result;
        }
        static inline FG_CONV_CD_TYPE* Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            FG_CONV_CD_TYPE *pEventUnion = (FG_CONV_CD_TYPE *)state->UnBoxPointer(idx);
            return pEventUnion;
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE *&> : public Type<FG_CONV_CD_TYPE *> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE *&> : public Type<FG_CONV_CD_TYPE *> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * EVENT: fgTouchEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::STouch

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::STouch]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_TOUCH_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_TOUCH_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgMouseEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SMouse

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgMouseEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_MOUSE_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_MOUSE_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgSwipeEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSwipe

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgSwipeEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_SWIPE_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SWIPE_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgSwipePinchEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSwipePinch

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgSwipePinchEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_SWIPE_PINCH_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SWIPE_PINCH_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgSwipeRotateEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSwipeRotate

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgSwipeRotateEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_SWIPE_ROTATE_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SWIPE_ROTATE_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgKeyEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SKey

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgKeyEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_KEY_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_KEY_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgResourceEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SResource

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgResourceEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_RESOURCE_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_RESOURCE_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgVertexStreamEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SVertexStream

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgVertexStreamEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_VERTEX_STREAM_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_VERTEX_STREAM_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgCameraEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SCamera

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgCameraEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_CAMERA_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_CAMERA_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgSoundEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSound

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgSoundEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_SOUND_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SOUND_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgMenuChangedEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SMenuChanged

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgMenuChangedEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_MENU_CHANGED_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_MENU_CHANGED_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgWidgetEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SWidget

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgWidgetEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_WIDGET_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_WIDGET_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgSensorsEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSensors

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgSensorsEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_SENSORS_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SENSORS_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgControllerDeviceEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SControllerDevice

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgControllerDeviceEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_CONTROLLER_DEVICE_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_CONTROLLER_DEVICE_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgControllerButtonEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SControllerButton

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgControllerButtonEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_CONTROLLER_BUTTON_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_CONTROLLER_BUTTON_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    /***************************************************************************
     * EVENT: fgControllerAxisEvent - structure
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SControllerAxis

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fgControllerAxisEvent]", ptr, (uintptr_t)ptr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::EVENT_CONTROLLER_AXIS_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_CONTROLLER_AXIS_MT_ID)];
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////
    // FG GFX SPECIAL TYPES
    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fgGfxSceneNode pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::gfx::CSceneNode *> {
        static inline void Push(lua_State* L, const fg::gfx::CSceneNode * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[fg::gfx::CSceneNode]", value, (uintptr_t)value, value->getNameStr());
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::SCENE_NODE_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::SCENE_NODE_MT_ID)]);
            FG_LOG_DEBUG("Script: LPCD Match: type[fg::gfx::CSceneNode] -> result[%d]", (int)result);
            // This is fubar
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fg::gfx::CSceneNode * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::gfx::CSceneNode *pSceneNode = (fg::gfx::CSceneNode *)state->UnBoxPointer(idx);
            return pSceneNode;
        }
    };

    template<> struct Type<fg::gfx::CSceneNode *&> : public Type<fg::gfx::CSceneNode *> {
    };

    template<> struct Type<const fg::gfx::CSceneNode *&> : public Type<fg::gfx::CSceneNode *> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fg::gfx::CSceneNodeTrigger *> {
        static inline void Push(lua_State* L, const fg::gfx::CSceneNodeTrigger * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[fg::gfx::CSceneNodeTrigger]", value, (uintptr_t)value, value->getNameStr());
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::SCENE_NODE_TRIGGER_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result; // = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WIDGET_MT_ID)]);
            // This is fubar
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fg::gfx::CSceneNodeTrigger * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::gfx::CSceneNodeTrigger *pSceneNodeTrigger = (fg::gfx::CSceneNodeTrigger *)state->UnBoxPointer(idx);
            return pSceneNodeTrigger;
        }
    };

    template<> struct Type<fg::gfx::CSceneNodeTrigger *&> : public Type<fg::gfx::CSceneNodeTrigger *> {
    };

    template<> struct Type<const fg::gfx::CSceneNodeTrigger *&> : public Type<fg::gfx::CSceneNodeTrigger *> {
    };

    ////////////////////////////////////////////////////////////////////////////
    // SCENE MANAGER EVENT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fg::event::SSceneNode pointer parameter
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSceneNode

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void *)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fg::script::CMetatables::METAID metaID =
                    fg::script::CMetatables::EVENT_SCENE_NODE_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneNode]",
                         ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() ==
                    state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SCENE_NODE_MT_ID)]);
            //bool result = (bool) obj.IsUserdata();
            return result;
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE *)state->UnBoxPointer(idx);            
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fg::event::SSceneNodeCollision pointer parameter
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSceneNodeCollision

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void *)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fg::script::CMetatables::METAID metaID =
                    fg::script::CMetatables::EVENT_SCENE_NODE_COLLISION_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneNodeCollision]",
                         ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() ==
                    state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SCENE_NODE_COLLISION_MT_ID)]);
            //bool result = (bool) obj.IsUserdata();
            return result;
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE *)state->UnBoxPointer(idx);            
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fg::event::SSceneNodeTrigger pointer parameter
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSceneNodeTrigger

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void *)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fg::script::CMetatables::METAID metaID =
                    fg::script::CMetatables::EVENT_SCENE_NODE_TRIGGER_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneNodeTrigger]",
                         ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() ==
                    state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SCENE_NODE_TRIGGER_MT_ID)]);
            //bool result = (bool) obj.IsUserdata();
            return result;
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(FG_CONV_CD_TYPE *)state->UnBoxPointer(idx);            
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fg::event::SSceneEvent pointer parameter - union
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSceneEvent

    template<> struct Type<FG_CONV_CD_TYPE *> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fg::script::CMetatables::METAID metaID =
                    fg::script::CMetatables::EVENT_SCENE_MAIN_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneEvent].union",
                         value, (uintptr_t)value);
        #endif
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() ==
                    state->GetRegistry()[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_SCENE_MAIN_MT_ID)]);
            //bool result = (bool) obj.IsUserdata();
            return result;
        }
        static inline FG_CONV_CD_TYPE* Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            FG_CONV_CD_TYPE *pEventUnion = (FG_CONV_CD_TYPE *)state->UnBoxPointer(idx);
            return pEventUnion;
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE *&> : public Type<FG_CONV_CD_TYPE *> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE *&> : public Type<FG_CONV_CD_TYPE *> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////

        #define FG_CONV_CD_TYPE fg::gfx::ModelType

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned int> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned int>::Push(L, static_cast<unsigned int>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned int>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    ////////////////////////////////////////////////////////////////////////////
    // FG SFX SPECIAL TYPES
    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fg::sfx::base::CAudio pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::sfx::base::CAudio *> {
        static inline void Push(lua_State* L, const fg::sfx::base::CAudio * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj;
            const fg::sfx::CMusic *pMusic = NULL;
            const fg::sfx::CSound *pSound = NULL;
            const char *nameStr = NULL;
            if(value->getAudioBaseType() == fg::sfx::base::T_MUSIC) {
                pMusic = static_cast<const fg::sfx::CMusic *>(value);
                nameStr = pMusic->getNameStr();
                obj = state->BoxPointer((void*)pMusic);
            } else if(value->getAudioBaseType() == fg::sfx::base::T_SOUND) {
                pSound = static_cast<const fg::sfx::CSound *>(value);
                nameStr = pSound->getNameStr();
                obj = state->BoxPointer((void*)pSound);
            }

        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[fg::sfx::base::CAudio]", value, (uintptr_t)value, nameStr);
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::AUDIO_BASE_RES_MT_ID;
            const char *metatableName = fgScriptMT->getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result; // = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WIDGET_MT_ID)]);
            // This is fubar
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fg::sfx::base::CAudio * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::sfx::base::CAudio *pAudio = (fg::sfx::base::CAudio *)state->UnBoxPointer(idx);
            return pAudio;
        }
    };

    template<> struct Type<fg::sfx::base::CAudio *&> : public Type<fg::sfx::base::CAudio *> {
    };

    template<> struct Type<const fg::sfx::base::CAudio *&> : public Type<fg::sfx::base::CAudio *> {
    };

    ////////////////////////////////////////////////////////////////////////////
    
    /***************************************************************************
     * FG PHYSICS / COLLISION BODY ENUMERATION TYPES -> INT / UNSIGNED
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::physics::CCollisionBody::BodyType

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned int> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned int>::Push(L, static_cast<unsigned int>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned int>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE
    
    ////////////////////////////////////////////////////////////////////////////
}

    #endif /* FG_USING_LUA_PLUS */

////////////////////////////////////////////////////////////////////////////////

    #undef FG_INC_SCRIPT_CD_BLOCK
#endif	/* FG_INC_SCRIPT_CD */

