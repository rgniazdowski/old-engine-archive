/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiDrawer.h"
#include "GFX/Shaders/fgGFXShaderManager.h"
#include "Resource/fgResourceManager.h"

/*
 *
 */
fg::gui::CDrawer::CDrawer() :
m_pResourceMgr(NULL) { }

/*
 *
 */
fg::gui::CDrawer::~CDrawer() {
    m_pResourceMgr = NULL;
}

/*
 *
 */
void fg::gui::CDrawer::setResourceManager(fg::base::CManager *pResourceMgr) {
    m_pResourceMgr = pResourceMgr;
}

/*
 *
 */
void fg::gui::CDrawer::flush(void) {
    CDrawingBatch::flush();
}

/*
 *
 */
void fg::gui::CDrawer::sortCalls(void) {
    CDrawingBatch::sortCalls();
}

/*
 *
 */
void fg::gui::CDrawer::render(void) {
    CDrawingBatch::render();
}

/**
 * 
 * @param outTextSize
 * @param blockPos
 * @param blockSize
 * @param style
 * @param fmt
 */
void fg::gui::CDrawer::appendText2D(fgVec2f& outTextSize,
                                    const fgVec2f &blockPos,
                                    const fgVec2f &blockSize,
                                    CStyleContent& style,
                                    const char *fmt, ...) {
    if(!m_pResourceMgr || !fmt)
        return;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';

    SForeground &fg = style.getForeground();
    fg::resource::CResource *resFont = static_cast<fg::resource::CResourceManager *>(m_pResourceMgr)->get(fg.font);
    if(!resFont)
        return;
    if(resFont->getResourceType() != FG_RESOURCE_FONT)
        return;
    CFontResource *fontResProper = (CFontResource *)resFont;
    this->setFont(fontResProper);
    this->setColor(fg.color);
    Align textAlign = style.getTextAlign();
    SPadding &padding = style.getPadding();
    fgVector2f outPos = blockPos;
    float realTextSize = fg.textSize;
    if(fg.unit == Unit::PERCENTS)
        realTextSize = fg.textSize / 100.0f * getScreenSize().y;
    outTextSize = CFontDrawer::size(fontResProper, buf, /*fg.textSize*/realTextSize);
    style.applyPosAlign(style.getTextAlign(), outPos, outTextSize, blockPos, blockSize, FG_TRUE);
    this->print(outPos.x, outPos.y, buf, /*fg.textSize*/realTextSize);
}

/**
 * 
 * @param pos
 * @param size
 * @param style
 */
void fg::gui::CDrawer::appendBackground2D(const fgVec2f &pos,
                                          const fgVec2f &size,
                                          CStyleContent& style) {
    if(!m_pResourceMgr)
        return;
    int index = 0;
    fg::gfx::CTexture *pTexture = NULL;
    SBackground &background = style.getBackground();
    fg::gfx::CDrawCall *drawCall = requestDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT);
    if(m_pResourceMgr && !background.texture.empty()) {
        // Get or request ?
        fg::resource::CResource *pResource = static_cast<fg::resource::CResourceManager *>(m_pResourceMgr)->request(background.texture);
        if(pResource) {
            if(pResource->getResourceType() == FG_RESOURCE_TEXTURE) {
                pTexture = (fg::gfx::CTexture *)pResource;
                drawCall->setTexture(pTexture->getRefGfxID());
            }
        }
    }
    fgVec2f uv1(0, 1); // upper left corner
    fgVec2f uv2(1, 0); // lower right corner
    if(background.style == SBackground::Style::TILED) {
        fgVec2f ratio(1.0f, 1.0f);
        if(pTexture) {
            ratio.x = size.x / (float)pTexture->getWidth();
            ratio.y = size.y / (float)pTexture->getHeight();
            uv1.y = ratio.y;
            uv2.x = ratio.x;
        }
    }
    drawCall->setColor(background.color);
    drawCall->appendRect2D(pos, size, uv1, uv2, FG_FALSE);
}

/**
 * 
 * @param pos
 * @param size
 * @param style
 */
void fg::gui::CDrawer::appendBorder2D(const fgVec2f &pos,
                                      const fgVec2f &size,
                                      CStyleContent& style) {
    if(!m_pResourceMgr)
        return;
    SBorderGroup &border = style.getBorder();
    if(border.left.style == SBorder::Style::NONE &&
       border.right.style == SBorder::Style::NONE &&
       border.top.style == SBorder::Style::NONE &&
       border.bottom.style == SBorder::Style::NONE) {
        return;
    }
    int index;
    float lwidth = 0.0f, rwidth = 0.0f, twidth = 0.0f, bwidth = 0.0f;
    fg::gfx::CDrawCall *drawCall = requestDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT);

    lwidth = style.getBorder().left.width;
    rwidth = style.getBorder().right.width;
    twidth = style.getBorder().top.width;
    bwidth = style.getBorder().bottom.width;
    // Left
    fgVec2f pos1(pos.x - lwidth, pos.y - twidth);
    fgVec2f size1(lwidth, size.y + twidth + bwidth);

    // Top
    fgVec2f pos2(pos.x, pos.y - twidth);
    fgVec2f size2(size.x, twidth);

    // Right
    fgVec2f pos3(pos.x + size.x, pos.y - twidth);
    fgVec2f size3(rwidth, size.y + twidth + bwidth);

    // Bottom
    fgVec2f pos4(pos.x, pos.y + size.y);
    fgVec2f size4(size.x, bwidth);

    drawCall->setColor(style.getBorder().left.color);
    drawCall->appendRect2D(pos1, size1, fgVec2f(0, 1), fgVec2f(1, 0), FG_FALSE);
    drawCall->setColor(style.getBorder().top.color);
    drawCall->appendRect2D(pos2, size2, fgVec2f(0, 1), fgVec2f(1, 0), FG_FALSE);
    drawCall->setColor(style.getBorder().right.color);
    drawCall->appendRect2D(pos3, size3, fgVec2f(0, 1), fgVec2f(1, 0), FG_FALSE);
    drawCall->setColor(style.getBorder().bottom.color);
    drawCall->appendRect2D(pos4, size4, fgVec2f(0, 1), fgVec2f(1, 0), FG_FALSE);
}
