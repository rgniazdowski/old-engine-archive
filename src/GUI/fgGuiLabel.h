/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_LABEL
    #define FG_INC_GUI_LABEL
    #define FG_INC_GUI_LABEL_BLOCK

    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactoryTypes.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CLabel : public CWidget {
        public:
            ///
            typedef CLabel self_type;
            ///
            typedef CLabel type;
            ///
            typedef CWidget base_type;

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
            CLabel();
            /**
             * 
             */
            virtual ~CLabel();

            /**
             * 
             * @return 
             */
            FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CLabel)

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
        };
    };
};

    #undef FG_INC_GUI_LABEL_BLOCK
#endif /* FG_INC_GUI_LABEL */
