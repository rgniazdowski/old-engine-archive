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
        #error "FG_INC_SCRIPT_MT_BLOCK is defined: Do not include ScriptCD header inside of ScriptMetatables header"
    #endif

    #if defined(FG_INC_EVENT_DEFINITIONS_BLOCK)
        #error "FG_INC_EVENT_DEFINITIONS_BLOCK is defined: Do not include ScriptCD header inside of EventDefinitions header"
    #endif

    #include "fgBuildConfig.h"

    #include "GFX/fgGfxTypes.h"

    #include "fgScriptCD_Event.h"
    #include "fgScriptCD_Game.h"
    #include "fgScriptCD_Gfx.h"
    #include "fgScriptCD_Gui.h"
    #include "fgScriptCD_Math.h"
    #include "fgScriptCD_Physics.h"
    #include "fgScriptCD_Resource.h"
    #include "fgScriptCD_Scene.h"

    #include "Audio/fgSFXAudioBase.h"
    #include "Audio/fgSFXMusicResource.h"
    #include "Audio/fgSFXSoundResource.h"

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
    } // namespace script
} // namespace fg

//------------------------------------------------------------------------------

    #if defined(FG_USING_LUA_PLUS)

namespace LPCD {

    //--------------------------------------------------------------------------

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

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    // FG SFX SPECIAL TYPES
    //--------------------------------------------------------------------------

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
            const unsigned short int metaID =
                    fg::script::CMetatables::AUDIO_BASE_RES_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::AUDIO_BASE_RES_MT_ID);
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

    //--------------------------------------------------------------------------

} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

//------------------------------------------------------------------------------

    #undef FG_INC_SCRIPT_CD_BLOCK
#endif /* FG_INC_SCRIPT_CD */
