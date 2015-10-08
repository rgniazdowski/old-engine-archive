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
 * File:   fgScriptCD_TypeBoxPtrEasy.h
 * Author: vigilant
 *
 * Created on October 7, 2015, 11:23 PM
 */

#ifndef FG_INC_SCRIPT_CD_TYPE_BOXPTR_EASY
    #define FG_INC_SCRIPT_CD_TYPE_BOXPTR_EASY
    #define FG_INC_SCRIPT_CD_TYPE_BOXPTR_EASY_BLOCK

    #if defined(FG_INC_SCRIPT_MT_BLOCK)
        #error "FG_INC_SCRIPT_MT_BLOCK is defined: Do not include ScriptCD header inside of ScriptMetatables header"
    #endif

    #if defined(FG_INC_EVENT_DEFINITIONS_BLOCK)
        #error "FG_INC_EVENT_DEFINITIONS_BLOCK is defined: Do not include ScriptCD header inside of EventDefinitions header"
    #endif

    #include "fgBuildConfig.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
        #include "fgScriptMT.h"

namespace LPCD {

    template<typename TYPE, fg::script::CMetatables::METAID METATABLE_ID>
    struct TypeBoxPtrEasy {
    public:
        static inline void Push(lua_State* L, const TYPE value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            obj.SetMetatable(fgScriptMT->getMetatable(METATABLE_ID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)METATABLE_ID);
        }
        static inline TYPE Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return (TYPE)state->UnBoxPointer(idx);
        }
    };
} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_TYPE_BOXPTR_EASY_BLOCK
#endif	/* FG_INC_SCRIPT_CD_TYPE_BOXPTR_EASY */
