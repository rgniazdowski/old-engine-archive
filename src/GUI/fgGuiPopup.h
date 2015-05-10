/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_POPUP
    #define FG_INC_GUI_POPUP
    #define FG_INC_GUI_POPUP_BLOCK

    #include "fgGuiWindow.h"
    #include "fgGuiWidgetFactoryTypes.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CPopup : public CWindow {
        public:
            ///
            typedef CPopup self_type;
            ///
            typedef CPopup type;
            ///
            typedef CWindow base_type;

        public:
            /**
             * 
             */
            CPopup();
            /**
             * 
             */
            virtual ~CPopup();

            /**
             * 
             * @return 
             */
            FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CPopup)

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
        };
    };
};

    #undef FG_INC_GUI_POPUP_BLOCK
#endif /* FG_INC_GUI_POPUP */
