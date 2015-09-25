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
 * File:   fgPhysics.h
 * Author: vigilant
 *
 * Created on September 24, 2015, 12:23 PM
 */

#ifndef FG_INC_PHYSICS
    #define FG_INC_PHYSICS
    #define FG_INC_PHYSICS_BLOCK

    #include "fgBuildConfig.h"

    #if defined(FG_USING_BULLET)
        #include "fgBulletMaskTypes.h"
        #include "fgBulletHelper.h"
        #include "fgCollisionBody.h"
        #include "fgPhysicalWorld.h"
    #endif


    #if !defined(FG_USING_BULLET) && defined(FG_USING_CYCLONE_INTERNAL)
        #include "Cyclone/fgCollisionBody.h"
        #include "Cyclone/fgWorld.h"
        //#include "Cyclone/fgPhysicalWorld.h"
    #endif

    #undef FG_INC_PHYSICS_BLOCK
#endif	/* FG_INC_PHYSICS */
