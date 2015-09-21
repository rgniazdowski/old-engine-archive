/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_FRAME
    #define FG_INC_GUI_FRAME
    #define FG_INC_GUI_FRAME_BLOCK

    #include "fgGuiContainer.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CFrame : public CContainer {
        public:
            ///
            typedef CFrame self_type;
            ///
            typedef CFrame type;
            ///
            typedef CContainer base_type;

        public:
            /**
             * 
             * @return 
             */
            CFrame();
            /**
             * 
             */
            virtual ~CFrame();

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
        }; // class CFrame
        
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_FRAME_BLOCK
#endif /* FG_INC_GUI_FRAME */
