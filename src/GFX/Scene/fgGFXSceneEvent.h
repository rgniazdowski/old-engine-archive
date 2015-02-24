/*******************************************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgGFXSceneEvent.h
 * Author: vigilant
 *
 * Created on February 19, 2015, 12:26 AM
 */

#ifndef FG_INC_GFX_SCENE_EVENT
    #define FG_INC_GFX_SCENE_EVENT
    #define FG_INC_GFX_SCENE_EVENT_BLOCK

    #include "Event/fgEventDefinitions.h"

namespace fg {

    namespace gfx {
        class CSceneNode;
        class CSceneNodeTrigger;
    }

    namespace event {

        const EventType SCENE_NODE_COLLISION = LAST_STANDARD_EVENT_CODE + 100;
        const EventType SCENE_NODE_TRIGGER_FIRED = LAST_STANDARD_EVENT_CODE + 101;
        const EventType SCENE_NODE_INSERTED = LAST_STANDARD_EVENT_CODE + 102;
        const EventType SCENE_NODE_REMOVED = LAST_STANDARD_EVENT_CODE + 103;
        const EventType SCENE_NODE_DESTROYED = LAST_STANDARD_EVENT_CODE + 104;

        const EventType SCENE_CLEARED = LAST_STANDARD_EVENT_CODE + 105;

        const EventType SCENE_DUMMY = LAST_STANDARD_EVENT_CODE + 106;

        const EventType LAST_SCENE_EVENT_CODE = LAST_STANDARD_EVENT_CODE + 106;

        /*
         *
         */
        struct SSceneNode : SEventBase {
            gfx::CSceneNode* pNodeA;
            gfx::CSceneNode* pNodeB;
        };

        /*
         *
         */
        struct SSceneNodeCollision : SSceneNode {
            //gfx::CollisionType collisionType;
            //Vector3f center;
        };

        /**
         *
         */
        struct SSceneNodeTrigger : SEventBase {

            union {
                gfx::CSceneNodeTrigger* pNodeTrigger;
                gfx::CSceneNodeTrigger* pNodeA;
            };
            gfx::CSceneNode* pNodeB;
        };

        /**
         *
         */
        struct SSceneEvent {

            union {
                EventType code;

                SSceneNode node;
                SSceneNodeCollision collision;
                SSceneNodeTrigger trigger;

                SReserved reserved;
            };
        };

    }
}

    #undef FG_INC_GFX_SCENE_EVENT_BLOCK
#endif	/* FG_INC_GFX_SCENE_EVENT */
