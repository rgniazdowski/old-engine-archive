/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFontStbCourier.h"
#include "StbCourier/stb_font_courier_50_usascii.inl"
#include "StbCourier/stb_font_courier_32_usascii.inl"
#include "StbCourier/stb_font_courier_16_usascii.inl"
#include "StbCourier/stb_font_courier_8_usascii.inl"

fgFontBuiltInRawData fgFontBuiltIn::StbCourier::m_stbFontRawData;

/*
 *
 */
fgFontBuiltInRawData* fgFontBuiltIn::StbCourier::getRawData(const int size) {
    if(size > 0 && size <= 8) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(courier_8, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(courier_8, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(courier_8, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(courier_8, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(courier_8, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(courier_8, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(courier_8, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(courier_8, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(courier_8, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(courier_8, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(courier_8, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(courier_8, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(courier_8, NUM_CHARS);
    } else if(size > 8 && size <= 16) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(courier_16, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(courier_16, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(courier_16, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(courier_16, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(courier_16, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(courier_16, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(courier_16, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(courier_16, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(courier_16, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(courier_16, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(courier_16, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(courier_16, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(courier_16, NUM_CHARS);
    } else if(size > 16 && size <= 32) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(courier_32, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(courier_32, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(courier_32, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(courier_32, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(courier_32, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(courier_32, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(courier_32, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(courier_32, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(courier_32, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(courier_32, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(courier_32, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(courier_32, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(courier_32, NUM_CHARS);
    } else if(size > 32) {
        m_stbFontRawData.xPtr = FG_STB_FONT_PTR(courier_50, x);
        m_stbFontRawData.yPtr = FG_STB_FONT_PTR(courier_50, y);
        m_stbFontRawData.wPtr = FG_STB_FONT_PTR(courier_50, w);
        m_stbFontRawData.hPtr = FG_STB_FONT_PTR(courier_50, h);
        m_stbFontRawData.sPtr = FG_STB_FONT_PTR(courier_50, s);
        m_stbFontRawData.tPtr = FG_STB_FONT_PTR(courier_50, t);
        m_stbFontRawData.aPtr = FG_STB_FONT_PTR(courier_50, a);
        m_stbFontRawData.bitsPtr = FG_STB_FONT_PTR(courier_50, pixels);
        m_stbFontRawData.width = FG_STB_FONT_CONST(courier_50, BITMAP_WIDTH);
        m_stbFontRawData.height = FG_STB_FONT_CONST(courier_50, BITMAP_HEIGHT);
        m_stbFontRawData.heightPOW2 = FG_STB_FONT_CONST(courier_50, BITMAP_HEIGHT_POW2);
        m_stbFontRawData.firstChar = FG_STB_FONT_CONST(courier_50, FIRST_CHAR);
        m_stbFontRawData.numChars = FG_STB_FONT_CONST(courier_50, NUM_CHARS);
    }
    return &m_stbFontRawData;
}
