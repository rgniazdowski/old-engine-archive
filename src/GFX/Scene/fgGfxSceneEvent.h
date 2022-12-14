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
    #include "fgGfxSceneNode.h"

namespace fg {

    namespace gfx {
        class CSceneNode;
        class CSceneNodeTrigger;
    }

    namespace event {

        /// Event thrown when collision occurred between two nodes
        const EventType SCENE_NODE_COLLISION = LAST_STANDARD_EVENT_CODE + 100;
        /// Event thrown when scene node trigger is fired (collision occured)
        const EventType SCENE_NODE_TRIGGER_FIRED = LAST_STANDARD_EVENT_CODE + 101;
        /// Event thrown when scene node is inserted
        const EventType SCENE_NODE_INSERTED = LAST_STANDARD_EVENT_CODE + 102;
        /// Event thrown when scene node is removed
        const EventType SCENE_NODE_REMOVED = LAST_STANDARD_EVENT_CODE + 103;
        ///
        const EventType SCENE_NODE_DESTROYED = LAST_STANDARD_EVENT_CODE + 104;

        /// Event thrown when node is selected through pick selection
        const EventType SCENE_NODE_SELECTED = LAST_STANDARD_EVENT_CODE + 105;

        /// This event is thrown when scene was explicitly cleared, all nodes
        // removed or deleted
        const EventType SCENE_CLEARED = LAST_STANDARD_EVENT_CODE + 106;

        const EventType SCENE_DUMMY = LAST_STANDARD_EVENT_CODE + 107;

        const EventType LAST_SCENE_EVENT_CODE = LAST_STANDARD_EVENT_CODE + 107;

        /*
         *
         */
        struct SSceneNode : SEventBase {
            ///
            unsigned int handleNodeA;
            ///
            unsigned int handleNodeB;
            ///
            gfx::CSceneNode* pNodeA;
            ///
            gfx::CSceneNode* pNodeB;
            
            /**
             *
             */
            void reset(void);
            /**
             *
             * @return
             */
            fgBool isValid(void) {
                if(pNodeA == NULL)
                    return FG_FALSE;
                return FG_TRUE;
            }
            /**
             *
             * @param _pNodeA
             */
            void setFirstNode(gfx::CSceneNode* _pNodeA);
            /**
             *
             * @param _pNodeB
             */
            void setSecondNode(gfx::CSceneNode* _pNodeB);
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
                ///
                unsigned int handleNodeTrigger;
                ///
                unsigned int handleNodeA;
            };
            ///
            unsigned int handleNodeB;
            union {
                ///
                gfx::CSceneNodeTrigger* pNodeTrigger;
                ///
                gfx::CSceneNodeTrigger* pNodeA;
            };
            ///
            gfx::CSceneNode* pNodeB;

            /**
             *
             */
            void reset(void);

            /**
             *
             * @param _pNodeA
             */
            void setFirstNode(gfx::CSceneNode* _pNodeA);
            /**
             */
            inline void setTriggerNode(gfx::CSceneNode* _pNodeTrigger) {
                setFirstNode(_pNodeTrigger);
            }
            /**
             *
             * @param _pNodeB
             */
            void setSecondNode(gfx::CSceneNode* _pNodeB);
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
