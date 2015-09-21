/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_PROGRESS_BAR
    #define FG_INC_GUI_PROGRESS_BAR
    #define FG_INC_GUI_PROGRESS_BAR_BLOCK

    #include "fgGuiWidget.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CProgressBar : public CWidget {
        public:
            ///
            typedef CProgressBar self_type;
            ///
            typedef CProgressBar type;
            ///
            typedef ::fg::gui::CWidget base_type;

        protected:
            /**
             *
             */
            virtual void setDefaults(void);

        public:
            /**
             *
             */
            CProgressBar();
            /**
             *
             */
            virtual ~CProgressBar();

            /**
             *
             * @return
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             *
             */
            virtual void refresh(void);

        }; // class CProgressBar

    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_PROGRESS_BAR_BLOCK
#endif /* FG_INC_GUI_PROGRESS_BAR */
