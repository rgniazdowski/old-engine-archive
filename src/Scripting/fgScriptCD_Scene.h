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
 * File:   fgScriptCD_Scene.h
 * Author: vigilant
 *
 * Created on October 7, 2015, 1:18 AM
 */

#ifndef FG_INC_SCRIPT_CD_SCENE
    #define FG_INC_SCRIPT_CD_SCENE
    #define FG_INC_SCRIPT_CD_SCENE_BLOCK

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
        #include "GFX/Scene/fgGfxSceneNode.h"
        #include "GFX/Scene/fgGfxSceneNodeTrigger.h"
        #include "GFX/Scene/fgGfxSceneEvent.h"

namespace LPCD {

    //--------------------------------------------------------------------------
    // FG GFX SCENE TYPES
    //--------------------------------------------------------------------------

    /***************************************************************************
     * fgGfxSceneNode pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::gfx::CSceneNode *> {
        static inline void Push(lua_State* L, const fg::gfx::CSceneNode * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[gfx::CSceneNode]",
                         value,
                         (uintptr_t)value,
                         value->getNameStr());
        #endif
            fg::script::CMetatables::METAID metaID = fg::script::CMetatables::SCENE_NODE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::SCENE_NODE_MT_ID);
            //FG_LOG_DEBUG("Script: LPCD Match: type[gfx::CSceneNode] -> result[%d]", (int)result);
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

    //--------------------------------------------------------------------------

    template<> struct Type<fg::gfx::CSceneNodeTrigger *> {
        static inline void Push(lua_State* L, const fg::gfx::CSceneNodeTrigger * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[gfx::CSceneNodeTrigger]",
                         value,
                         (uintptr_t)value,
                         value->getNameStr());
        #endif
            const unsigned short int metaID = fg::script::CMetatables::SCENE_NODE_TRIGGER_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::SCENE_NODE_TRIGGER_MT_ID);
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

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    // SCENE MANAGER EVENT DEFINITIONS
    //--------------------------------------------------------------------------

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
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneNode]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::EVENT_SCENE_NODE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SCENE_NODE_MT_ID);
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

    //--------------------------------------------------------------------------

    /***************************************************************************
     * fg::event::SSceneNodeCollision pointer parameter
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSceneNodeCollision

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void *)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneNodeCollision]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::EVENT_SCENE_NODE_COLLISION_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SCENE_NODE_COLLISION_MT_ID);
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

    //--------------------------------------------------------------------------

    /***************************************************************************
     * fg::event::SSceneNodeTrigger pointer parameter
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSceneNodeTrigger

    template<> struct Type<FG_CONV_CD_TYPE> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE & value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void *)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneNodeTrigger]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::EVENT_SCENE_NODE_TRIGGER_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SCENE_NODE_TRIGGER_MT_ID);
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

    //--------------------------------------------------------------------------

    /***************************************************************************
     * fg::event::SSceneEvent pointer parameter - union
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::event::SSceneEvent

    template<> struct Type<FG_CONV_CD_TYPE *> {
        static inline void Push(lua_State* L, const FG_CONV_CD_TYPE * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[event::SSceneEvent].union",
                         value, (uintptr_t)value);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::EVENT_SCENE_MAIN_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            bool result = (metaEnum == (int)fg::script::CMetatables::EVENT_SCENE_MAIN_MT_ID);
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

} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_SCENE_BLOCK
#endif	/* FG_INC_SCRIPT_CD_SCENE */
