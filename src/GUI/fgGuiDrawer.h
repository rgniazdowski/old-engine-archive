/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_DRAWER
    #define FG_INC_GUI_DRAWER
    #define FG_INC_GUI_DRAWER_BLOCK

    #ifndef FG_INC_FONT_DRAWER
        #include "Font/fgFontDrawer.h"
    #endif

    #ifndef FG_INC_GFX_DRAWING_BATCH
        #include "GFX/fgGfxDrawingBatch.h"
    #endif 

    #ifndef FG_INC_GUI_STYLE_CONTENT
        #include "fgGuiStyleContent.h"
    #endif

    #ifndef FG_INC_MANAGER_BASE
        #include "fgManagerBase.h"
    #endif

namespace fg {
    namespace gui {
        class CWidgetManager;
        class CGuiMain;

        /**
         *
         */
        class CDrawer : public CFontDrawer, public virtual gfx::CDrawingBatch {
            friend class fg::gui::CGuiMain;
            friend class fg::gui::CWidgetManager;

        private:
            /// Pointer to the external resource manager
            /// Required for fast font/texture lookup
            /// #FIXME - should this be replaced with texture manager?
            fg::base::CManager *m_pResourceMgr;

        public:
            /**
             * 
             */
            CDrawer();
            /**
             * 
             */
            virtual ~CDrawer();

        public:
            /**
             * 
             * @return 
             */
            fg::base::CManager *getResourceManager(void) const {
                return m_pResourceMgr;
            }

            /**
             * 
             * @param pResourceMgr
             */
            virtual void setResourceManager(fg::base::CManager *pResourceMgr);

            /**
             * 
             * @param outTextSize
             * @param blockPos
             * @param blockSize
             * @param style
             * @param fmt
             */
            virtual void appendText2D(Vec2f& outTextSize, const Vec2f &blockPos, const Vec2f &blockSize, CStyleContent& style, const char *fmt, ...);

            /**
             * 
             * @param pos
             * @param size
             * @param style
             */
            virtual void appendBackground2D(const Vec2f &pos, const Vec2f &size, CStyleContent& style);

            /**
             * 
             * @param pos
             * @param size
             * @param style
             */
            virtual void appendBorder2D(const Vec2f &pos, const Vec2f &size, CStyleContent& style);
            /**
             * 
             * @param pos
             * @param radius
             * @param style
             */
            virtual void appendCircleBorder2D(const Vec2f& pos, float radius, CStyleContent& style);

        };
    };
};

    #undef FG_INC_GUI_DRAWER_BLOCK
#endif /* FG_INC_GUI_DRAWER */
