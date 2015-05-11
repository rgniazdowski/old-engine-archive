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
 * File:   fgGfxBspResource.h
 * Author: vigilant
 *
 * Created on May 10, 2015, 7:23 PM
 */

#ifndef FG_INC_GFX_BSP_RESOURCE
    #define FG_INC_GFX_BSP_RESOURCE
    #define FG_INC_GFX_BSP_RESOURCE_BLOCK

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CBspResource {
        public:
            typedef CBspResource self_type;
            typedef CBspResource type;

        public:
            /**
             *
             */
            CBspResource();
            /**
             *
             * @param orig
             */
            CBspResource(const CBspResource& orig);
            /**
             * 
             */
            virtual ~CBspResource();
        private:

        };
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_BSP_RESOURCE_BLOCK
#endif	/* FG_INC_GFX_BSP_RESOURCE */
