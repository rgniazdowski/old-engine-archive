/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_WINDOW
    #define FG_INC_GUI_WINDOW
    #define FG_INC_GUI_WINDOW_BLOCK

    #include "fgGuiContainer.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CWindow : public CContainer {
        public:
            ///
            typedef CWindow self_type;
            ///
            typedef CWindow type;
            ///
            typedef CContainer base_type;

        public:
            /**
             * 
             */
            CWindow();
            /**
             * 
             */
            virtual ~CWindow();

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             */
            virtual void refresh(void);

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);
        }; // class CWindow
        
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_WINDOW_BLOCK
#endif /* FG_INC_GUI_WINDOW */
