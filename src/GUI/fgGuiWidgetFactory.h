/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_WIDGET_FACTORY
    #define FG_INC_GUI_WIDGET_FACTORY
    #define FG_INC_GUI_WIDGET_FACTORY_BLOCK

    #include "fgTypes.h"
    #include "fgGuiWidget.h"
    #include "Util/fgAbstractFactory.h"
    
namespace fg {
    namespace gui {

        /**
         *
         */
        class CWidgetFactory : public util::CAbstractFactory<WidgetType, CWidget> {
        public:
            ///
            typedef util::CAbstractFactory<WidgetType, CWidget> base_type;
            ///
            typedef CWidgetFactory self_type;
            ///
            typedef CWidgetFactory type;
            
        public:
            /**
             * Default empty constructor for Widget Factory object
             */
            CWidgetFactory();
            /**
             * Destructor for Widget Factory object
             */
            virtual ~CWidgetFactory();
            
        }; // class CWidgetFactory
        
    } // gui
} // fg

    #undef FG_INC_GUI_WIDGET_FACTORY_BLOCK
#endif /* FG_INC_GUI_WIDGET_FACTORY */
