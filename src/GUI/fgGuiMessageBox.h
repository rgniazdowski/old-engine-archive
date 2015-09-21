/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_MESSAGE_BOX
    #define FG_INC_GUI_MESSAGE_BOX
    #define FG_INC_GUI_MESSAGE_BOX_BLOCK

    #include "fgGuiWindow.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CMessageBox : public CWindow {
        public:
            ///
            typedef CMessageBox self_type;
            ///
            typedef CMessageBox type;
            ///
            typedef CWindow base_type;


        public:
            /**
             * 
             */
            CMessageBox();
            /**
             * 
             */
            virtual ~CMessageBox();

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
        }; // class CMessageBox
        
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_MESSAGE_BOX_BLOCK
#endif /* FG_INC_GUI_MESSAGE_BOX */ 
