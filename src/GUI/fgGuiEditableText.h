/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_EDITABLE_TEXT
    #define FG_INC_GUI_EDITABLE_TEXT
    #define FG_INC_GUI_EDITABLE_TEXT_BLOCK

    #include "fgGuiTextArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CEditableText : public CTextArea {
        public:
            ///
            typedef CEditableText self_type;
            ///
            typedef CEditableText type;
            ///
            typedef CTextArea base_type;

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);

        public:
            /**
             * 
             */
            CEditableText();
            /**
             * 
             */
            virtual ~CEditableText();

            /**
             * 
             * @return 
             */
            FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CEditableText)

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             */
            virtual void refresh(void);

        };
    };
};

    #undef FG_INC_GUI_EDITABLE_TEXT_BLOCK
#endif /* FG_INC_GUI_EDITABLE_TEXT */
