/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_LOADER
    #define FG_INC_GUI_LOADER
    #define FG_INC_GUI_LOADER_BLOCK

    #include "fgGuiWidget.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CLoaderSub : public CWidget {
        public:
            ///
            typedef CLoaderSub self_type;
            ///
            typedef CLoaderSub type;
            ///
            typedef ::fg::gui::CWidget base_type;

        protected:
            /// 
            std::string m_text;

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);

        public:
            /**
             * 
             */
            CLoaderSub();
            /**
             * 
             */
            virtual ~CLoaderSub();

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             */
            virtual void refresh(void);
        }; // class CLoaderSub
        
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_LOADER_BLOCK
#endif /* FG_INC_GUI_LOADER */
