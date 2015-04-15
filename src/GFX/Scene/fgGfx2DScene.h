/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_2D_SCENE
    #define FG_INC_GFX_2D_SCENE
    #define FG_INC_GFX_2D_SCENE_BLOCK

    #include "fgGfxSceneManager.h"
    
namespace fg {

    namespace gfx {

        /**
         *
         */
        class CScene2D : public CSceneManager {
        public:
            ///
            typedef CSceneManager base_type;

        private:

        public:
            /**
             * 
             */
            CScene2D();
            /**
             * 
             */
            virtual ~CScene2D();

        public:
            //    #THAFUCK?
            //    virtual void flush(void);
            //    virtual void sortCalls(void);
            //    virtual void render(void);

        };
    };
};

    #undef FG_INC_GFX_2D_SCENE_BLOCK
#endif /* FG_INC_GFX_2D_SCENE */

