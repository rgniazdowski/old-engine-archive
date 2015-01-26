/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXSkyBox.h
 * Author: vigilant
 *
 * Created on January 26, 2015, 7:16 PM
 */

#ifndef FG_INC_GFX_SKYBOX
    #define FG_INC_GFX_SKYBOX
    #define FG_INC_GFX_SKYBOX_BLOCK

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CSceneSkyBox {
        public:
            /**
             * 
             */
            CSceneSkyBox();
            /**
             * 
             * @param orig
             */
            CSceneSkyBox(const CSceneSkyBox& orig);
            /**
             * 
             */
            virtual ~CSceneSkyBox();
            
        private:
            
            
        };

    };
};

    #undef FG_INC_GFX_SKYBOX_BLOCK
#endif	/* FG_INC_GFX_SKYBOX */
