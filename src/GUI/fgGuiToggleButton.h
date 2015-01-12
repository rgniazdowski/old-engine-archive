/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_TOGGLE_BUTTON
    #define FG_INC_GUI_TOGGLE_BUTTON
    #define FG_INC_GUI_TOGGLE_BUTTON_BLOCK

    #include "fgGuiButton.h"
    #include "fgGuiWidgetFactoryTypes.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CToggleButton : public CButton {
        public:
            ///
            typedef CButton base_type;

        public:
            /**
             * 
             */
            CToggleButton();
            /**
             * 
             */
            virtual ~CToggleButton();

            /**
             * 
             * @return 
             */
            FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CToggleButton)

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);
        };
    };
};

    #undef FG_INC_GUI_TOGGLE_BUTTON_BLOCK
#endif /* FG_INC_GUI_TOGGLE_BUTTON */
