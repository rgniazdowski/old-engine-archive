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
 * File:   fgGfxNodeFactory.h
 * Author: vigilant
 *
 * Created on September 21, 2015, 10:30 PM
 */

#ifndef FG_INC_GFX_NODE_FACTORY
    #define FG_INC_GFX_NODE_FACTORY
    #define FG_INC_GFX_NODE_FACTORY_BLOCK

    #include "fgGfxSceneNode.h"
    #include "Util/fgAbstractFactory.h"

namespace fg {
    namespace gfx {

        class CSceneNode;

        /**
         *
         */
        class CNodeFactory : public util::CAbstractFactory<SceneNodeType, CSceneNode> {
        public:
            typedef util::CAbstractFactory<SceneNodeType, CSceneNode> base_type;
            typedef CNodeFactory self_type;
            typedef CNodeFactory type;

        public:
            /**
             *
             */
            CNodeFactory();
            /**
             *
             */
            virtual ~CNodeFactory();        

        }; // class CNodeFactory
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_NODE_FACTORY_BLOCK
#endif	/* FG_INC_GFX_NODE_FACTORY */
