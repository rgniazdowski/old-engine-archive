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
 * File:   fgScriptCD_Physics.h
 * Author: vigilant
 *
 * Created on October 7, 2015, 1:32 AM
 */

#ifndef FG_INC_SCRIPT_CD_PHYSICS
    #define FG_INC_SCRIPT_CD_PHYSICS
    #define FG_INC_SCRIPT_CD_PHYSICS_BLOCK

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
        #include "fgScriptCD_TypeBoxPtrEasy.h"
        #include "Physics/fgCollisionBody.h"


namespace LPCD {

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

    //template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    //};

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

    template<> struct Type<fg::physics::CCollisionBody*> :
    public TypeBoxPtrEasy<fg::physics::CCollisionBody*,
    fg::script::CMetatables::COLLISION_BODY_MT_ID> {
    };

    template<> struct Type<fg::physics::CCollisionBody*&> :
    public Type<fg::physics::CCollisionBody*> {
    };

    //template<> struct Type<const fg::physics::CCollisionBody*&> :
    //public Type<fg::physics::CCollisionBody*> {
    //};

    //--------------------------------------------------------------------------

} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_PHYSICS_BLOCK
#endif	/* FG_INC_SCRIPT_CD_PHYSICS */
