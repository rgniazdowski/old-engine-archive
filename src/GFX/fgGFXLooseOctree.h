/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXLooseOctree.h
 * Author: vigilant
 *
 * Created on January 14, 2015, 9:58 PM
 */

#ifndef FG_INC_GFX_LOOSE_OCTREE
    #define FG_INC_GFX_LOOSE_OCTREE
    #define FG_INC_GFX_LOOSE_OCTREE_BLOCK

    #include "fgGFXOctree.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CLooseOctree : public COctree {
        public:
            /**
             * 
             */
            CLooseOctree();
            /**
             * 
             * @param orig
             */
            CLooseOctree(const CLooseOctree& orig);
            /**
             * 
             */
            virtual ~CLooseOctree();
            
        private:

        };
    };
};

    #undef FG_INC_GFX_LOOSE_OCTREE_BLOCK
#endif	/* FG_INC_GFX_LOOSE_OCTREE */

