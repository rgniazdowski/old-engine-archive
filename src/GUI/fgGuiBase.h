/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_BASE
    #define FG_INC_GUI_BASE
    #define FG_INC_GUI_BASE_BLOCK

namespace fg {
    namespace gui {

        /**
         *
         */
        class CGuiBase {
        public:
            /**
             * 
             */
            CGuiBase() { }
            /**
             * 
             */
            virtual ~CGuiBase() { }

        };
    };
};

    #undef FG_INC_GUI_BASE_BLOCK
#endif /* FG_INC_GUI_BASE */
