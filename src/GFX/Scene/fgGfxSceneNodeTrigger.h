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
 * File:   fgGFXSceneNodeTrigger.h
 * Author: vigilant
 *
 * Created on February 18, 2015, 10:34 PM
 */

#ifndef FG_INC_GFX_SCENE_NODE_TRIGGER
    #define FG_INC_GFX_SCENE_NODE_TRIGGER
    #define FG_INC_GFX_SCENE_NODE_TRIGGER_BLOCK

    #include "fgGfxSceneNode.h"
    #include "fgGfxSceneCallback.h"
    #include "fgGfxTriggerable.h"

namespace fg {
    namespace gfx {

        class CSceneCallback;
        class CSceneManager;

        /**
         *
         */
        class CSceneNodeTrigger : public CSceneNode,
        public traits::CTriggerable {
            friend CSceneManager;
        public:
            ///
            typedef CSceneNode base_type;
            ///
            typedef CSceneNodeTrigger self_type;
            ///
            typedef CSceneNodeTrigger type;
            ///
            typedef traits::CTriggerable triggerable_type;
            ///
            static const SceneNodeType SELF_NODE_TYPE = SCENE_NODE_TRIGGER;

        public:
            /**
             * 
             */
            CSceneNodeTrigger();
            /**
             * 
             * @param orig
             */
            CSceneNodeTrigger(const CSceneNodeTrigger& orig);
            /**
             * 
             */
            virtual ~CSceneNodeTrigger();

            /**
             * 
             * @param trait
             * @param pObj
             * @return
             */
            virtual fgBool queryTrait(const fg::traits::SceneNode trait, void **pObj);

            //------------------------------------------------------------------

        }; // class CSceneNodeTrigger

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_NODE_TRIGGER_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_TRIGGER */
