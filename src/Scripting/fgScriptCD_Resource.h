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
 * File:   fgScriptCD_Resource.h
 * Author: vigilant
 *
 * Created on October 6, 2015, 9:20 PM
 */

#ifndef FG_INC_SCRIPT_CD_RESOURCE
    #define FG_INC_SCRIPT_CD_RESOURCE
    #define FG_INC_SCRIPT_CD_RESOURCE_BLOCK

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
        #include "Resource/fgResource.h"
        #include "GFX/fgGfxModelResource.h"

namespace LPCD {

    /***************************************************************************
     * resource::CResource pointer parameter *
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
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s]",
                         value,
                         (uintptr_t)value,
                         value->getNameStr());
        #endif
            // This wont work - this simply packs resource that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            //obj.SetMetatable(state->GetRegistry()[metatableName]);
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            unsigned int resourceType = fgScriptMT->getResourceTypeFromMetatableID(metaEnum);
            bool result = (resourceType != fg::resource::INVALID);            
            return result;
        }
        static inline fg::resource::CResource* Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::resource::CResource *pResource = (fg::resource::CResource *)state->UnBoxPointer(idx);
            return pResource;
        }
    };

    template<> struct Type<fg::resource::CResource *&> : public Type<fg::resource::CResource *> {
    };

    template<> struct Type<const fg::resource::CResource *&> : public Type<fg::resource::CResource *> {
    };

    //--------------------------------------------------------------------------

} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_RESOURCE_BLOCK
#endif	/* FG_INC_SCRIPT_CD_RESOURCE */
