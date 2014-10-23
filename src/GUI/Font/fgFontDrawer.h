/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_FONT_DRAWER_H_
    #define _FG_FONT_DRAWER_H_

    #include "fgFontResource.h"
    #include "GFX/fgGFXTypes.h"

    #define FG_FONT_DEFAULT_CHAR_SIZE_PX	-1.0f
    #define FG_FONT_DRAW_STRING_BUF_MAX		1024

    #define FG_FONT_BUFFER_MAX				4096

// Maybe this class should extend some other class
// we'll see later, maybe this kind of thing (done via this class)
// is kinda generic
typedef unsigned int fgFontPrintMode;

    #define FG_FONT_PRINT_MODE_ABSOLUTE		0
    #define FG_FONT_PRINT_MODE_RELATIVE		1

    #ifndef _FG_GFX_DRAWING_BATCH_H_
        #include "GFX/fgGFXDrawingBatch.h"
    #endif 

/*
 *
 */
class fgFontDrawer : protected fgGfxDrawingBatch {
public:
    /**
     *
     */
    fgFontDrawer();
    /**
     * 
     */
    virtual ~fgFontDrawer();

protected:
    /**
     * 
     * @param texture
     * @return 
     */
    fgGfxDrawCall *setupDrawCall(fgTextureResource *texture);

public:
    /**
     */
    virtual void setShaderManager(fgManagerBase *shaderMgr);
    
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
     * @return 
     */
    virtual int getZIndex(void) const {
        return fgGfxDrawingBatch::getZIndex();
    }
    /**
     * 
     * @param zIndex
     */
    virtual void setZIndex(const int zIndex) {
        fgGfxDrawingBatch::setZIndex(zIndex);
    }
    /**
     * 
     */
    virtual void upZIndex(void) {
        fgGfxDrawingBatch::upZIndex();
    }
    /**
     * 
     */
    virtual void downZIndex(void) {
        fgGfxDrawingBatch::downZIndex();
    }

    /**
     * 
     * @param color
     */
    virtual void setColor(const fgColor4f &color);
    /**
     * 
     * @param color
     */
    virtual void setColor(const fgColor3f &color);
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
    fgVector2f size(float charSize, const char *fmt, ...);
    /**
     * 
     * @param string
     * @param charSize
     * @return 
     */
    fgVector2f size(const char *string, float charSize);

    /**
     * 
     * @param font
     * @param charSize
     * @param fmt
     * @return 
     */
    static float width(fgFontResource *font, float charSize, const char *fmt, ...);
    /**
     * 
     * @param font
     * @param string
     * @param charSize
     * @return 
     */
    static float width(fgFontResource *font, const char *string, float charSize);
    /**
     * 
     * @param font
     * @param charSize
     * @param fmt
     * @return 
     */
    static float height(fgFontResource *font, float charSize, const char *fmt, ...);
    /**
     * 
     * @param font
     * @param string
     * @param charSize
     * @return 
     */
    static float height(fgFontResource *font, const char *string, float charSize);
    /**
     * 
     * @param font
     * @param charSize
     * @param fmt
     * @return 
     */
    static fgVector2f size(fgFontResource *font, float charSize, const char *fmt, ...);

    /**
     * 
     * @param font
     * @param string
     * @param charSize
     * @return 
     */
    static fgVector2f size(fgFontResource *font, const char *string, float charSize);

    /**
     * Set current font used for drawing
     * @param font
     * @return 
     */
    fgBool setFont(fgFontResource *font);

    /**
     * 
     * @return 
     */
    fgFontResource *getFont(void) const;

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
    fgFontResource *m_currentFont;
    /// Currently used color for drawing
    fgColor4f m_color;
    /// Internal relative move of the font
    fgVector3f m_relMove;
    /// Font printing mode
    fgFontPrintMode m_printMode;
};

#endif /* _FG_FONT_DRAWER_H_ */
