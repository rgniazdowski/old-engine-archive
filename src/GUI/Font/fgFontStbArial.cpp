/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFontStbArial.h"
#include "StbArial/stb_font_arial_50_usascii.inl"
#include "StbArial/stb_font_arial_32_usascii.inl"
#include "StbArial/stb_font_arial_16_usascii.inl"
#include "StbArial/stb_font_arial_8_usascii.inl"

fg::gui::SFontBuiltInRawData fg::gui::font::StbArial::m_stbFontRawData;

/*
 *
 */
fg::gui::SFontBuiltInRawData* fg::gui::font::StbArial::getRawData(const int size) {
    if(size > 0 && size <= 8) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(arial_8, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(arial_8, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(arial_8, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(arial_8, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(arial_8, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(arial_8, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(arial_8, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(arial_8, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(arial_8, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(arial_8, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(arial_8, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(arial_8, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(arial_8, NUM_CHARS);
    } else if(size > 8 && size <= 16) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(arial_16, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(arial_16, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(arial_16, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(arial_16, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(arial_16, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(arial_16, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(arial_16, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(arial_16, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(arial_16, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(arial_16, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(arial_16, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(arial_16, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(arial_16, NUM_CHARS);
    } else if(size > 16 && size <= 32) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(arial_32, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(arial_32, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(arial_32, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(arial_32, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(arial_32, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(arial_32, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(arial_32, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(arial_32, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(arial_32, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(arial_32, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(arial_32, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(arial_32, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(arial_32, NUM_CHARS);
    } else if(size > 32) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(arial_50, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(arial_50, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(arial_50, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(arial_50, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(arial_50, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(arial_50, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(arial_50, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(arial_50, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(arial_50, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(arial_50, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(arial_50, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(arial_50, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(arial_50, NUM_CHARS);
    }
    return &m_stbFontRawData;
}
