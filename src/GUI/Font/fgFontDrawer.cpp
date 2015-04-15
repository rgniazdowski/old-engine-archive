/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFontDrawer.h"
#include "GFX/fgGfxPrimitives.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/fgGfxAABoundingBox.h"

using namespace fg;

/**
 *
 */
gui::CFontDrawer::CFontDrawer() :
m_currentFont(NULL),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_printMode(FG_FONT_PRINT_MODE_ABSOLUTE) { }

/**
 *
 */
gui::CFontDrawer::~CFontDrawer() { }

/**
 * 
 * @param x0
 * @param y0
 * @param charSize
 * @param fmt
 * @return 
 */
int gui::CFontDrawer::print(float x0, float y0, float charSize, const char *fmt, ...) {
    if(!m_currentFont || !fmt)
        return 0;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';

    return print(x0, y0, buf, charSize);
}

/**
 * 
 * @param charSize
 * @param fmt
 * @param ...
 * @return 
 */
int gui::CFontDrawer::print(float charSize, const char *fmt, ...) {
    if(!m_currentFont || !fmt)
        return 0;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';

    return print(0.0f, 0.0f, buf, charSize);
}

/**
 * 
 * @param string
 * @param charSize
 * @return 
 */
int gui::CFontDrawer::print(const char *string, float charSize) {
    return print(0.0f, 0.0f, string, charSize);
}

/**
 * 
 * @param x0
 * @param y0
 * @param string
 * @param charSize
 * @return 
 */
int gui::CFontDrawer::print(float x0, float y0, const char *string, float charSize) {
    if(!m_currentFont || !string)
        return 0;
    // main
    //float scale;
    int n = 0;
    const char *s = NULL;
    float x = x0, y = y0;
    fgBool rewind = FG_FALSE;
    if(charSize <= 0.0f)
        charSize = (float)m_currentFont->getStep();
    //scale = charSize / (float)m_currentFont->getStep(); // ? is it needed?
    //x += m_relMove.x;
    //y += m_relMove.y;
    if(m_printMode == FG_FONT_PRINT_MODE_ABSOLUTE && 0) {
        m_relMove.x = -x0;
        m_relMove.y = -y0;
    } else {
        //m_relMove = Vector3f(0.0f, 0.0f, 0.0f);
    }
    setupDrawCall(m_currentFont);
    float w = 0.0f;
    for(s = string, n = 0; *s; s++) {
        n++;
        if(*s == '\n') {
            y += charSize / 16.0f;
            rewind = FG_TRUE;
            x = 0.0f;
        } else if(*s == ' ') {
            x += charSize / 3.0f;
            w += charSize / 3.0f;
        } else {
            float xMove = placeChar(x, y, *s, rewind, charSize);
            w += xMove;
            x += xMove;
            //x=0.0f; y=0.0f;
            rewind = FG_FALSE;
        }
    }
    if(m_printMode == FG_FONT_PRINT_MODE_ABSOLUTE) {
        //m_relMove.x -= w;
    }
    return n;
}

/**
 * Clears the buffer (no drawing is performed)
 */
void gui::CFontDrawer::flush(void) {
    fg::gfx::CDrawingBatch::flush();
    m_relMove = Vector3f(0.0f, 0.0f, 0.0f);
}

/**
 * 
 */
void gui::CFontDrawer::render(void) {
    gfx::CDrawingBatch::render();
}

/**
 * 
 * @param color
 */
void gui::CFontDrawer::setColor(const fgColor4f &color) {
    m_color = color;
    gfx::CDrawCall *drawCall = gfx::CDrawingBatch::getLastDrawCall();
    if(drawCall) {
        drawCall->setColor(m_color);
    }
}

/**
 * 
 * @param color
 */
void gui::CFontDrawer::setColor(const fgColor3f &color) {
    m_color = fgColor4f(color.r, color.g, color.g, 1.0f);
    gfx::CDrawCall *drawCall = gfx::CDrawingBatch::getLastDrawCall();
    if(drawCall) {
        drawCall->setColor(m_color);
    }
}

/**
 * 
 */
void fg::gui::CFontDrawer::setColor(void) {
    m_color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    gfx::CDrawCall *drawCall = gfx::CDrawingBatch::getLastDrawCall();
    if(drawCall) {
        drawCall->setColor(m_color);
    }
}

/**
 * 
 * @param texture
 * @return 
 */
gfx::CDrawCall *gui::CFontDrawer::setupDrawCall(gfx::CTexture *texture) {
    int index;
    gfx::CDrawCall *drawCall = gfx::CDrawingBatch::requestDrawCall(index,
                                                                   FG_GFX_DRAW_CALL_CUSTOM_ARRAY,
                                                                   FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT);
    drawCall->setColor(m_color);
    drawCall->setTexture(texture->getRefGfxID());
    drawCall->setDrawAppendMode(gfx::DRAW_APPEND_ABSOLUTE);
    return drawCall;
}

/**
 * 
 * @param font
 * @return 
 */
fgBool gui::CFontDrawer::setFont(CFontResource *font) {
    if(!font)
        return FG_FALSE;
    if(m_currentFont != font) {
        m_currentFont = font;
        setupDrawCall(m_currentFont);
    }
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
gui::CFontResource *gui::CFontDrawer::getFont(void) const {
    return m_currentFont;
}

/*
 * This will flush the data, reset the fontHandle, clear cache etc
 */
void gui::CFontDrawer::reset(void) {
    gui::CFontDrawer::flush();
    m_currentFont = NULL;
    m_relMove = Vector3f(0.0f, 0.0f, 0.0f);
}

/**
 * 
 * @param letter
 * @param rewind
 * @param charSize
 * @return 
 */
float gui::CFontDrawer::placeChar(char letter, fgBool rewind, float charSize) {
    if(!m_currentFont)
        return 0.0f;
    return placeChar(0.0f, 0.0f, letter, charSize);
}

/**
 * 
 * @param xRel0
 * @param yRel0
 * @param letter
 * @param rewind
 * @param charSize
 * @return 
 */
float gui::CFontDrawer::placeChar(float xRel0,
                                  float yRel0,
                                  char letter,
                                  fgBool rewind,
                                  float charSize) {
    if(!m_currentFont)
        return 0.0f;
    int i = (int)letter - m_currentFont->getDataInfo().firstChar;
    if(charSize <= 0.0f)
        charSize = (float)m_currentFont->getStep();
    float scale = charSize / (float)m_currentFont->getStep();
    SFontCharInfo &charInfo = m_currentFont->getDataInfo().charInfo[i];
    Vector2f relPos(xRel0, yRel0);
    relPos.x += charInfo.p0f.x*scale;
    relPos.y += charInfo.p0f.y*scale;
    Vector2f rectSize = (charInfo.p1f - charInfo.p0f) * scale;
    fg::gfx::CDrawCall *drawCall = fg::gfx::CDrawingBatch::getLastDrawCall();
    if(!drawCall) {
        drawCall = setupDrawCall(m_currentFont);
    }
    drawCall->appendRect2D(relPos,
                           rectSize,
                           m_currentFont->getDataInfo().charInfo[i].uv1i,
                           m_currentFont->getDataInfo().charInfo[i].uv2i,
                           rewind);
    return m_currentFont->getDataInfo().charInfo[i].stepf*scale;
}

/**
 * 
 * @param font
 * @param charSize
 * @param fmt
 * @param ...
 * @return 
 */
float gui::CFontDrawer::width(CFontResource *font, float charSize, const char *fmt, ...) {
    if(!font)
        return 0.0f;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';
    return fg::gui::CFontDrawer::width(font, buf, charSize);
}

/**
 * 
 * @param font
 * @param string
 * @param charSize
 * @return 
 */
float gui::CFontDrawer::width(CFontResource *font, const char *string, float charSize) {
    if(!font)
        return 0.0f;
    float x = 0.0f;
    const char *s = NULL;
    if(charSize <= 0.0f)
        charSize = (float)font->getStep();
    float scale = charSize / (float)font->getStep();

    // Longest line seen
    float max_x = 0.0f;
    for(s = string; *s; s++) {
        int i = (int)(*s) - font->getDataInfo().firstChar;
        if(*s == ' ') {
            x += 1.0f;
            x += charSize / 3.0f;
        } else if(*s != '\n') {
            // Adds size of char
            x += 1.0f;
            x += font->getDataInfo().charInfo[i].p1f.x*scale;
        } else {
            x += 1.0f;
            // Processed a new line. Remember its length if long enough
            if(x > max_x) {
                max_x = x;
            }
            // Prepare for the new line!
            x = 0.0f;
        }
    }
    // Grabs x into max_x if there was no explicit '\n'
    if(x > max_x) {
        max_x = x;
    }
    return max_x;
}

/**
 * 
 * @param font
 * @param charSize
 * @param fmt
 * @param ...
 * @return 
 */
float gui::CFontDrawer::height(CFontResource *font,
                               float charSize,
                               const char *fmt,
                               ...) {
    if(!font)
        return 0.0f;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;
    if(charSize <= 0.0f)
        charSize = (float)font->getStep();

    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';

    return gui::CFontDrawer::height(font, buf, charSize);
}

/**
 * 
 * @param font
 * @param string
 * @param charSize
 * @return 
 */
float gui::CFontDrawer::height(CFontResource *font,
                               const char *string,
                               float charSize) {
    if(!font)
        return 0.0f;
    if(charSize <= 0.0f)
        charSize = (float)font->getStep();
    float scale = charSize / (float)font->getStep();
    float y = -1.0f;
    float maxY = 0.0f;
    const char *s = NULL;
    for(s = string; *s; s++) {
        int c = (int)(*s) - font->getDataInfo().firstChar;
        if(font->getDataInfo().charInfo[c].p1f.y > maxY)
            maxY = font->getDataInfo().charInfo[c].p1f.y;
        if(*s == '\n') {
            if(y < 0.0f)
                y = maxY;
            y += maxY;
            maxY = 0.0f;
        }
    }
    if(y < 0.0f)
        y = maxY;
    return y*scale;
}

/**
 * 
 * @param font
 * @param charSize
 * @param fmt
 * @return 
 */
Vector2f gui::CFontDrawer::size(CFontResource *font,
                                float charSize,
                                const char *fmt,
                                ...) {
    if(!font)
        return Vector2f();
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';
    return size(font, buf, charSize);
}

/**
 * 
 * @param font
 * @param string
 * @param charSize
 * @return 
 */
Vector2f gui::CFontDrawer::size(CFontResource *font,
                                const char *string,
                                float charSize) {
    if(!string)
        return Vector2f();
    Vector2f textSize;
    textSize.x = width(font, string, charSize);
    textSize.y = height(font, string, charSize);
    return textSize;
}

/**
 * 
 * @param charSize
 * @param fmt
 * @return 
 */
float gui::CFontDrawer::width(float charSize,
                              const char *fmt,
                              ...) {
    if(!m_currentFont)
        return 0.0f;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';
    return width(m_currentFont, buf, charSize);
}

/**
 * 
 * @param string
 * @param charSize
 * @return 
 */
float gui::CFontDrawer::width(const char *string,
                              float charSize) {
    if(!m_currentFont || !string)
        return 0.0f;
    if(charSize <= FG_EPSILON)
        return FG_EPSILON;
    return width(m_currentFont, string, charSize);
}

/**
 * 
 * @param charSize
 * @param fmt
 * @return 
 */
float gui::CFontDrawer::height(float charSize,
                               const char *fmt,
                               ...) {
    if(!m_currentFont || !fmt)
        return 0.0f;
    if(charSize <= FG_EPSILON)
        return FG_EPSILON;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';
    return height(m_currentFont, buf, charSize);
}

/**
 * 
 * @param height
 * @return 
 */
float gui::CFontDrawer::height(const char *string,
                               float charSize) {
    if(!m_currentFont || !string)
        return 0.0f;
    if(charSize <= FG_EPSILON)
        return FG_EPSILON;
    return height(m_currentFont, string, charSize);
}

/**
 * 
 * @param charSize
 * @param fmt
 * @return 
 */
Vector2f gui::CFontDrawer::size(float charSize,
                                const char *fmt,
                                ...) {
    if(!m_currentFont)
        return Vector2f();
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';
    return size(m_currentFont, buf, charSize);
}

/**
 * 
 * @param string
 * @param charSize
 * @return 
 */
Vector2f gui::CFontDrawer::size(const char *string,
                                float charSize) {
    if(!string)
        return Vector2f();
    Vector2f textSize;
    textSize.x = width(m_currentFont, string, charSize);
    textSize.y = height(m_currentFont, string, charSize);
    return textSize;
}
