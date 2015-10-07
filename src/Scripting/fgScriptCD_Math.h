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
 * File:   fgScriptCD_Math.h
 * Author: vigilant
 *
 * Created on October 6, 2015, 9:20 PM
 */

#ifndef FG_INC_SCRIPT_CD_MATH
    #define FG_INC_SCRIPT_CD_MATH
    #define FG_INC_SCRIPT_CD_MATH_BLOCK

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
        #include "Math/fgMathLib.h"

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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector2i]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::VECTOR2I_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::VECTOR2I_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector2f]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::VECTOR2F_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::VECTOR2F_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector3i]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::VECTOR3I_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::VECTOR3I_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector3f]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::VECTOR3F_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::VECTOR3F_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector4i]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::VECTOR4I_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::VECTOR4I_MT_ID);
            return result;
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
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[fg::Vector4f]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::VECTOR4F_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::VECTOR4F_MT_ID);
            return result;
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
} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_MATH_BLOCK
#endif	/* FG_INC_SCRIPT_CD_MATH */
