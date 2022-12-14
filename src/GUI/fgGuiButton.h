/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_BUTTON
    #define FG_INC_GUI_BUTTON
    #define FG_INC_GUI_BUTTON_BLOCK

    #include "fgGuiWidget.h"
    #include "fgGuiLabel.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CButton : public CWidget {
        public:
            ///
            typedef CButton self_type;
            ///
            typedef CButton type;
            ///
            typedef CWidget base_type;

        protected:
            /// 
            CLabel *m_label;

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);

        public:
            /**
             * 
             */
            CButton();
            /**
             * 
             */
            virtual ~CButton();

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             */
            virtual void refresh(void);
        }; // class CButton

    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_BUTTON_BLOCK
#endif /* FG_INC_GUI_BUTTON */ 
