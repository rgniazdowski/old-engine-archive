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
 * File:   fgScriptCD_Game.h
 * Author: vigilant
 *
 * Created on October 7, 2015, 1:18 AM
 */

#ifndef FG_INC_SCRIPT_CD_GAME
    #define FG_INC_SCRIPT_CD_GAME
    #define FG_INC_SCRIPT_CD_GAME_BLOCK

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

namespace LPCD {

} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_GAME_BLOCK
#endif	/* FG_INC_SCRIPT_CD_GAME_BLOCK */
