/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiDrawer.h"
#include "GFX/Shaders/fgGFXShaderManager.h"

/*
 *
 */
fgGuiDrawer::fgGuiDrawer() :
m_fontDrawer(NULL),
m_resourceMgr(NULL),
m_color(1.0f, 1.0f, 1.0f, 1.0f) {
    m_fontDrawer = new fgFontDrawer();
}

/*
 *
 */
fgGuiDrawer::~fgGuiDrawer() {
    if(m_fontDrawer)
        delete m_fontDrawer;
    m_fontDrawer = NULL;
    m_resourceMgr = NULL;
}

/*
 *
 */
fgFontDrawer *fgGuiDrawer::getFontDrawer(void) const {
    return m_fontDrawer;
}

/*
 *
 */
fgResourceManager *fgGuiDrawer::getResourceManager(void) const {
    return m_resourceMgr;
}

/*
 *
 */
void fgGuiDrawer::setResourceManager(fgResourceManager *resourceMgr) {
    m_resourceMgr = resourceMgr;
}

/*
 *
 */
void fgGuiDrawer::setShaderManager(fgManagerBase *shaderMgr) {
    fgGfxDrawingBatch::setShaderManager(shaderMgr);
    if(m_fontDrawer)
        m_fontDrawer->setShaderManager(shaderMgr);
}

/*
 * Set active color for the next data
 */
void fgGuiDrawer::setColor(const fgColor3f& color) {
    m_fontDrawer->setColor(color);
    m_color = fgColor4f(color.r, color.g, color.b, 1.0f);
}

/*
 * Set active color for the next data
 */
void fgGuiDrawer::setColor(const fgColor4f& color) {
    m_fontDrawer->setColor(color);
    m_color = color;
}

/*
 * This will reset used color
 */
void fgGuiDrawer::resetColor(void) {
    m_color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/*
 *
 */
void fgGuiDrawer::flush(void) {
    m_fontDrawer->flush();
    fgGfxDrawingBatch::flush();
}

/*
 *
 */
void fgGuiDrawer::sortCalls(void) {
    fgGfxDrawingBatch::sortCalls();
}

/*
 *
 */
void fgGuiDrawer::render(void) {
    fgGfxDrawingBatch::render();
    m_fontDrawer->render();
}

/*
 *
 */
void fgGuiDrawer::appendText2D(fgVec2f& outTextSize, const fgVec2f &blockPos, const fgVec2f &blockSize, fgGuiStyleContent& style, const char *fmt, ...) {
    if(!m_resourceMgr || !fmt)
        return;
    char buf[FG_FONT_DRAW_STRING_BUF_MAX];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX - 1, fmt, args);
    va_end(args);
    buf[FG_FONT_DRAW_STRING_BUF_MAX - 1] = '\0';

    fgGuiForeground &fg = style.getForeground();
    fgResource *resFont = m_resourceMgr->get(fg.font);
    if(!resFont)
        return;
    if(resFont->getResourceType() != FG_RESOURCE_FONT)
        return;
    fgFontResource *fontResProper = (fgFontResource *)resFont;
    m_fontDrawer->setFont(fontResProper);
    m_fontDrawer->setColor(fg.color);
    fgGuiAlign textAlign = style.getTextAlign();
    fgGuiPadding &padding = style.getPadding();
    fgVector2f outPos = blockPos;
    outTextSize = fgFontDrawer::size(fontResProper, buf, fg.textSize);
    style.applyPosAlign(style.getTextAlign(), outPos, outTextSize, blockSize);
    m_fontDrawer->print(outPos.x, outPos.y, buf, fg.textSize);
}

/*
 *
 */
void fgGuiDrawer::appendBackground2D(const fgVec2f &pos, const fgVec2f &size, fgGuiStyleContent& style) {
    if(!m_resourceMgr)
        return;
    int index;
    fgGfxDrawCall *drawCall = createDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT);
    if(m_resourceMgr && !style.getBackground().texture.empty()) {
        fgResource *pResource = m_resourceMgr->get(style.getBackground().texture);
        if(pResource) {
            if(pResource->getResourceType() == FG_RESOURCE_TEXTURE) {
                fgTextureResource *pTexture = (fgTextureResource *)pResource;
                drawCall->setTexture(pTexture->getRefGfxID());
            }
        }
    }
    drawCall->setColor(style.getBackground().color);
    drawCall->appendRect2D(pos, size, fgVec2f(0, 1), fgVec2f(1, 0), FG_FALSE);
}

/*
 *
 */
void fgGuiDrawer::appendBorder2D(const fgVec2f &pos, const fgVec2f &size, fgGuiStyleContent& style) {
    if(!m_resourceMgr)
        return;
    fgGuiBorderInfo &border = style.getBorder();
    if(border.left.style == FG_GUI_BORDER_NONE &&
       border.right.style == FG_GUI_BORDER_NONE &&
       border.top.style == FG_GUI_BORDER_NONE &&
       border.bottom.style == FG_GUI_BORDER_NONE) {
        return;
    }
    int index;
    float lwidth = 0.0f, rwidth = 0.0f, twidth = 0.0f, bwidth = 0.0f;
    fgGfxDrawCall *drawCall = createDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
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
