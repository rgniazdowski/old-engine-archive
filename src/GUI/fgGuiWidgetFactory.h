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
    #include "fgGuiWidgetFactoryTypes.h"

    #include <map>

namespace fg {
    namespace gui {

        /**
         *
         */
        class CWidgetFactory {
        public:
            ///
            typedef CWidgetFactory self_type;
            ///
            typedef CWidgetFactory type;
            ///
            typedef std::map<WidgetType, fgCreateGuiWidgetFn> FactoryMap;
            ///
            typedef std::pair<WidgetType, fgCreateGuiWidgetFn> FactoryPair;
            ///
            typedef FactoryMap::iterator FactoryMapItor;
            ///
            typedef FactoryMap::const_iterator FactoryMapConstItor;

        public:
            /**
             * Default empty constructor for Widget Factory object
             */
            CWidgetFactory();
            /**
             * Destructor for Widget Factory object
             */
            virtual ~CWidgetFactory();

            /**
             * Clear all registered Widget creators
             */
            void clear(void);

            /**
             * Register Widget create function based on resource type
             * @param type
             * @param function
             * @return 
             */
            fgBool registerWidget(const WidgetType type, fgCreateGuiWidgetFn function);

            /**
             * Call specific create function for given Widget
             * @param type
             * @return 
             */
            CWidget* createWidget(const WidgetType type);

            /**
             * Check if given resource type constructor/create function is registered in factory
             * @param type
             * @return 
             */
            fgBool isRegistered(const WidgetType type);

        private:
            /// Map storing create functions for given widget types
            FactoryMap m_factoryMap;
        };
    };
};

    #undef FG_INC_GUI_WIDGET_FACTORY_BLOCK
#endif /* FG_INC_GUI_WIDGET_FACTORY */
