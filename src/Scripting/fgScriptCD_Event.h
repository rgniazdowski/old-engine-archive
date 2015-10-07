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
 * File:   fgScriptCD_Event.h
 * Author: vigilant
 *
 * Created on October 6, 2015, 9:19 PM
 */

#ifndef FG_INC_SCRIPT_CD_EVENT
    #define FG_INC_SCRIPT_CD_EVENT
    #define FG_INC_SCRIPT_CD_EVENT_BLOCK

    #if defined(FG_INC_SCRIPT_MT_BLOCK)
        #error "FG_INC_SCRIPT_MT_BLOCK is defined: Do not include ScriptCD header inside of ScriptMetatables header"
    #endif

    #if defined(FG_INC_EVENT_DEFINITIONS_BLOCK)
        #error "FG_INC_EVENT_DEFINITIONS_BLOCK is defined: Do not include ScriptCD header inside of EventDefinitions header"
    #endif

    #include "fgBuildConfig.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
        #if defined(FG_DEBUG)
            #include "fgLog.h"
        #endif
        #include "fgScriptMT.h"
        #include "Event/fgEventDefinitions.h"

namespace LPCD {

    /***************************************************************************
     * FG EVENT ENUMERATION TYPES -> INT
     **************************************************************************/

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::event::KeyVirtualCode

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

    //--------------------------------------------------------------------------

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

    //--------------------------------------------------------------------------

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

    //--------------------------------------------------------------------------

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
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SEvent].union",
                         value,
                         (uintptr_t)value);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_MAIN_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_MAIN_MT_ID);
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

    //--------------------------------------------------------------------------

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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::STouch]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_TOUCH_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_TOUCH_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SMouse]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_MOUSE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_MOUSE_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSwipe]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_SWIPE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SWIPE_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSwipePinch]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_SWIPE_PINCH_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SWIPE_PINCH_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSwipeRotate]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_SWIPE_ROTATE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SWIPE_ROTATE_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SKey]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_KEY_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_KEY_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SResource]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_RESOURCE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_RESOURCE_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SVertexStream]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_VERTEX_STREAM_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_VERTEX_STREAM_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SCamera]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_CAMERA_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_CAMERA_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSound]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_SOUND_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SOUND_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SMenuChanged]", ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_MENU_CHANGED_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_MENU_CHANGED_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SWidget]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_WIDGET_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_WIDGET_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSensors]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_SENSORS_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SENSORS_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SControllerDevice]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_CONTROLLER_DEVICE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_CONTROLLER_DEVICE_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SControllerButton]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_CONTROLLER_BUTTON_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_CONTROLLER_BUTTON_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SControllerAxis]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::EVENT_CONTROLLER_AXIS_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_CONTROLLER_AXIS_MT_ID);
            return result;
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

    //--------------------------------------------------------------------------

} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_EVENT_BLOCK
#endif	/* FG_INC_SCRIPT_CD_EVENT */
