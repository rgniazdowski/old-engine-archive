/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_TABLE
    #define FG_INC_GUI_TABLE
    #define FG_INC_GUI_TABLE_BLOCK

    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CTable : public CContainer {
        public:
            ///
            typedef CContainer base_type;

        public:
            /**
             * 
             */
            CTable();
            /**
             * 
             */
            virtual ~CTable();

            /**
             * 
             * @return 
             */
            FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CTable)

            /**
             * 
             * @return 
             */
            virtual fgBoundingBox3Df updateBounds(void);
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

    #undef FG_INC_GUI_TABLE_BLOCK
#endif /* FG_INC_GUI_TABLE */
