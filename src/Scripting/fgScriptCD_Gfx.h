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
 * File:   fgScriptCD_Gfx.h
 * Author: vigilant
 *
 * Created on October 6, 2015, 9:18 PM
 */

#ifndef FG_INC_SCRIPT_CD_GFX
    #define FG_INC_SCRIPT_CD_GFX
    #define FG_INC_SCRIPT_CD_GFX_BLOCK

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
        #include "GFX/Shaders/fgGfxShaderProgram.h"
        #include "GFX/fgGfxModelResource.h"

namespace LPCD {

    //--------------------------------------------------------------------------
    // FG GFX SHADER PROGRAM TYPE
    //--------------------------------------------------------------------------

    template<> struct Type<fg::gfx::CShaderProgram *> {
        static inline void Push(lua_State* L, const fg::gfx::CShaderProgram * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[gfx::CShaderProgram]",
                         value,
                         (uintptr_t)value,
                         value != NULL ? value->getNameStr() : "nil");
        #endif
            const unsigned short int metaID = fg::script::CMetatables::SHADER_PROGRAM_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::SHADER_PROGRAM_MT_ID);
        }
        static inline fg::gfx::CShaderProgram * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::gfx::CShaderProgram *pShaderProgram =
                    (fg::gfx::CShaderProgram *)state->UnBoxPointer(idx);
            return pShaderProgram;
        }
    };

    template<> struct Type<fg::gfx::CShaderProgram *&> : public Type<fg::gfx::CShaderProgram *> {
    };

    template<> struct Type<const fg::gfx::CShaderProgram *&> : public Type<fg::gfx::CShaderProgram *> {
    };

    //--------------------------------------------------------------------------


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

    //--------------------------------------------------------------------------


} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_GFX_BLOCK
#endif	/* FG_INC_SCRIPT_CD_GFX */
