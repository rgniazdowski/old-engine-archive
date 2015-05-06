/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FONT_DRAWER
    #define FG_INC_FONT_DRAWER

    #include "fgFontResource.h"
    #include "GFX/fgGfxTypes.h"

    #define FG_FONT_DEFAULT_CHAR_SIZE_PX	-1.0f
    #define FG_FONT_DRAW_STRING_BUF_MAX		1024

    #define FG_FONT_BUFFER_MAX				4096

// Maybe this class should extend some other class
// we'll see later, maybe this kind of thing (done via this class)
// is kinda generic
typedef unsigned int fgFontPrintMode;

    #define FG_FONT_PRINT_MODE_ABSOLUTE		0
    #define FG_FONT_PRINT_MODE_RELATIVE		1

    #ifndef FG_INC_GFX_DRAWING_BATCH
        #include "GFX/fgGfxDrawingBatch.h"
    #endif 

namespace fg {
    namespace gui {

        /**
         *
         */
        class CFontDrawer : public virtual fg::gfx::CDrawingBatch {
        public:
            /**
             *
             */
            CFontDrawer();
            /**
             * 
             */
            virtual ~CFontDrawer();

        protected:
            /**
             * 
             * @param texture
             * @return 
             */
            gfx::CDrawCall *setupDrawCall(gfx::CTexture *texture);

        public:
            /**
             * 
             * @param x0
             * @param y0
             * @param charSize
             * @param fmt
             * @return 
             */
            int print(float x0, float y0, float charSize, const char *fmt, ...);
            /**
             * 
             * @param x0
             * @param y0
             * @param string
             * @param charSize
             * @return 
             */
            int print(float x0, float y0, const char *string, float charSize = FG_FONT_DEFAULT_CHAR_SIZE_PX);
            /**
             * 
             * @param size
             * @param fmt
             * @param ...
             * @return 
             */
            int print(float size, const char *fmt, ...);
            /**
             * 
             * @param string
             * @param charSize
             * @return 
             */
            int print(const char *string, float charSize = FG_FONT_DEFAULT_CHAR_SIZE_PX);

            /**
             * 
             * @param color
             */
            virtual void setColor(const Color4f &color);
            /**
             * 
             * @param color
             */
            virtual void setColor(const Color3f &color);
            /**
             * 
             */
            virtual void setColor(void);

            /**
             * 
             */
            virtual void flush(void);
            /**
             * 
             */
            virtual void render(void);

            /**
             * 
             * @param charSize
             * @param fmt
             * @return 
             */
            float width(float charSize, const char *fmt, ...);
            /**
             * 
             * @param string
             * @param charSize
             * @return 
             */
            float width(const char *string, float charSize);
            /**
             * 
             * @param charSize
             * @param fmt
             * @return 
             */
            float height(float charSize, const char *fmt, ...);
            /**
             * 
             * @param string
             * @param charSize
             * @return 
             */
            float height(const char *string, float charSize);
            /**
             * 
             * @param charSize
             * @param fmt
             * @return 
             */
            Vector2f size(float charSize, const char *fmt, ...);
            /**
             * 
             * @param string
             * @param charSize
             * @return 
             */
            Vector2f size(const char *string, float charSize);

            /**
             * 
             * @param font
             * @param charSize
             * @param fmt
             * @return 
             */
            static float width(CFontResource *font, float charSize, const char *fmt, ...);
            /**
             * 
             * @param font
             * @param string
             * @param charSize
             * @return 
             */
            static float width(CFontResource *font, const char *string, float charSize);
            /**
             * 
             * @param font
             * @param charSize
             * @param fmt
             * @return 
             */
            static float height(CFontResource *font, float charSize, const char *fmt, ...);
            /**
             * 
             * @param font
             * @param string
             * @param charSize
             * @return 
             */
            static float height(CFontResource *font, const char *string, float charSize);
            /**
             * 
             * @param font
             * @param charSize
             * @param fmt
             * @return 
             */
            static Vector2f size(CFontResource *font, float charSize, const char *fmt, ...);

            /**
             * 
             * @param font
             * @param string
             * @param charSize
             * @return 
             */
            static Vector2f size(CFontResource *font, const char *string, float charSize);

            /**
             * Set current font used for drawing
             * @param font
             * @return 
             */
            fgBool setFont(CFontResource *font);

            /**
             * 
             * @return 
             */
            CFontResource *getFont(void) const;

            /**
             * 
             */
            virtual void reset(void);

        protected:
            /**
             * Place the char right after the last want. Rewind is for going back in the line (caret return)
             * @param letter
             * @param rewind
             * @param charSize
             * @return 
             */
            float placeChar(char letter, fgBool rewind = FG_FALSE, float charSize = FG_FONT_DEFAULT_CHAR_SIZE_PX);
            /**
             * Place the char after the last one + relative position transform
             * @param xRel0
             * @param yRel0
             * @param letter
             * @param rewind
             * @param charSize
             * @return 
             */
            float placeChar(float xRel0, float yRel0, char letter, fgBool rewind = FG_FALSE, float charSize = FG_FONT_DEFAULT_CHAR_SIZE_PX);

        private:
            /// Currently used font resource for drawing
            CFontResource *m_currentFont;
            /// Currently used color for drawing
            Color4f m_color;
            /// Font printing mode
            fgFontPrintMode m_printMode;
        };
    };
};

    #undef FG_INC_FONT_DRAWER_BLOCK
#endif /* FG_INC_FONT_DRAWER */
