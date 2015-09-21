/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_MENU
    #define FG_INC_GUI_MENU
    #define FG_INC_GUI_MENU_BLOCK

    #include "fgCommon.h"
    #include "fgGuiContainer.h"

namespace fg {
    namespace gui {

        /**
         * 
         */
        class CMenu : public CContainer {
        public:
            ///
            typedef CMenu self_type;
            ///
            typedef CMenu type;
            ///
            typedef CContainer base_type;

        private:
            ///
            fgBool m_isMainMenu;

        public:

            using CWidget::updateBounds;

            /**
             * 
             */
            CMenu();
            /**
             * 
             */
            virtual ~CMenu();

            /**
             * 
             * @param flags
             */
            virtual void setFlags(const std::string& flags);

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             */
            virtual void refresh(void);
            /**
             * 
             * @return 
             */
            fgBool isMainMenu(void) const {
                return m_isMainMenu;
            }

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);
        }; // class CMenu
        
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_MENU_BLOCK
#endif /* FG_INC_GUI_MENU */
