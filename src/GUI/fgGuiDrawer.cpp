/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGuiDrawer.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
#include "Resource/fgResourceManager.h"

using namespace fg;

//------------------------------------------------------------------------------

gui::CDrawer::CDrawer() :
m_pResourceMgr(NULL) { }
//------------------------------------------------------------------------------

gui::CDrawer::~CDrawer() {
    m_pResourceMgr = NULL;
}
//------------------------------------------------------------------------------

void gui::CDrawer::setResourceManager(fg::base::CManager *pResourceMgr) {
    m_pResourceMgr = pResourceMgr;
}
//------------------------------------------------------------------------------

void gui::CDrawer::appendText2D(Vec2f& outTextSize,
                                const Vec2f &blockPos,
                                const Vec2f &blockSize,
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
    resource::CResource *resFont = static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(fg.font);
    if(!resFont)
        return;
    if(resFont->getResourceType() != resource::FONT)
        return;
    CFontResource *fontResProper = (CFontResource *)resFont;
    this->setFont(fontResProper);
    this->setColor(fg.color);
    Align textAlign = style.getTextAlign();
    SPadding &padding = style.getPadding();
    Vector2f outPos = blockPos;
    float realTextSize = fg.textSize;
    if(fg.unit == Unit::PERCENTS)
        realTextSize = fg.textSize / 100.0f * getScreenSize().y;
    outTextSize = CFontDrawer::size(fontResProper, buf, /*fg.textSize*/realTextSize);
    style.applyPosAlign(style.getTextAlign(), outPos, outTextSize, blockPos, blockSize, FG_TRUE);
    this->print(outPos.x, outPos.y, buf, /*fg.textSize*/realTextSize);
}
//------------------------------------------------------------------------------

void gui::CDrawer::appendBackground2D(const Vec2f &pos,
                                      const Vec2f &size,
                                      CStyleContent& style) {
    if(!m_pResourceMgr)
        return;
    int index = 0;
    gfx::CTexture *pTexture = NULL;
    SBackground &background = style.getBackground();
    gfx::CDrawCall *drawCall = requestDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT);
    if(m_pResourceMgr && !background.texture.empty()) {
        // Get or request ?
        resource::CResource *pResource = static_cast<resource::CResourceManager *>(m_pResourceMgr)->request(background.texture);
        if(pResource) {
            if(pResource->getResourceType() == resource::TEXTURE) {
                pTexture = (gfx::CTexture *)pResource;
                drawCall->setTexture(pTexture->getRefGfxID());
            }
        }
    }
    //union {T x, r, s;};
    //union {T y, g, t;};
    Vec2f uv1(0, 1); // upper left corner
    Vec2f uv2(1, 0); // lower right corner
    if(background.style == SBackground::Style::TILED) {
        Vec2f ratio(1.0f, 1.0f);
        if(pTexture) {
            ratio.x = size.x / (float)pTexture->getWidth();
            ratio.y = size.y / (float)pTexture->getHeight();
            uv1.y = ratio.y; // upper left corner (t/y coordinate)
            uv2.x = ratio.x; // lower right corner (s/x coordinate)
            // centered tiling test #FIXME
            if(ratio.x > 1.0f) {
                uv2.y = -(ratio.x - 1.0f) / 2.0f;
                uv2.x += uv2.y;
            }
            if(ratio.y > 1.0f) {
                uv1.x = -(ratio.y - 1.0f) / 2.0f;
                uv1.y += uv1.x;
            }
        }
    }
    drawCall->setColor(background.color);
    drawCall->appendRect2D(pos, size, uv1, uv2, FG_FALSE);
}
//------------------------------------------------------------------------------

void gui::CDrawer::appendBorder2D(const Vec2f &pos,
                                  const Vec2f &size,
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
    gfx::CDrawCall *drawCall = requestDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT);

    lwidth = border.left.width;
    rwidth = border.right.width;
    twidth = border.top.width;
    bwidth = border.bottom.width;
    // Left
    Vec2f pos1(pos.x - lwidth, pos.y - twidth);
    Vec2f size1(lwidth, size.y + twidth + bwidth);
    // Top
    Vec2f pos2(pos.x, pos.y - twidth);
    Vec2f size2(size.x, twidth);
    // Right
    Vec2f pos3(pos.x + size.x, pos.y - twidth);
    Vec2f size3(rwidth, size.y + twidth + bwidth);
    // Bottom
    Vec2f pos4(pos.x, pos.y + size.y);
    Vec2f size4(size.x, bwidth);

    drawCall->setColor(border.left.color);
    drawCall->appendRect2D(pos1, size1, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.top.color);
    drawCall->appendRect2D(pos2, size2, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.right.color);
    drawCall->appendRect2D(pos3, size3, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.bottom.color);
    drawCall->appendRect2D(pos4, size4, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
}
//------------------------------------------------------------------------------

void gui::CDrawer::appendBorder2D(const gfx::AABB2Df& box, CStyleContent& style) {
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
    gfx::CDrawCall *drawCall = requestDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT);

    lwidth = border.left.width;
    rwidth = border.right.width;
    twidth = border.top.width;
    bwidth = border.bottom.width;

    Vec2f pos;
    pos.x = box.min.x;
    pos.y = box.min.y;
    Vec2f size;
    size.x = box.max.x - box.min.x;
    size.y = box.max.y - box.min.y;

    // Left
    Vec2f pos1(pos.x - lwidth, pos.y - twidth);
    Vec2f size1(lwidth, size.y + twidth + bwidth);
    // Top
    Vec2f pos2(pos.x, pos.y - twidth);
    Vec2f size2(size.x, twidth);
    // Right
    Vec2f pos3(pos.x + size.x, pos.y - twidth);
    Vec2f size3(rwidth, size.y + twidth + bwidth);
    // Bottom
    Vec2f pos4(pos.x, pos.y + size.y);
    Vec2f size4(size.x, bwidth);

    drawCall->setColor(border.left.color);
    drawCall->appendRect2D(pos1, size1, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.top.color);
    drawCall->appendRect2D(pos2, size2, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.right.color);
    drawCall->appendRect2D(pos3, size3, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.bottom.color);
    drawCall->appendRect2D(pos4, size4, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
}
//------------------------------------------------------------------------------

void gui::CDrawer::appendBorder2D(const gfx::BB2Df& box, CStyleContent& style) {
    if(!m_pResourceMgr)
        return;
    SBorderGroup &border = style.getBorder();
    if(border.left.style == SBorder::Style::NONE &&
       border.right.style == SBorder::Style::NONE &&
       border.top.style == SBorder::Style::NONE &&
       border.bottom.style == SBorder::Style::NONE) {
        return;
    }
    float lwidth = 0.0f, rwidth = 0.0f, twidth = 0.0f, bwidth = 0.0f;
    int index;
    gfx::CDrawCall *drawCall = requestDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT);

    lwidth = border.left.width;
    rwidth = border.right.width;
    twidth = border.top.width;
    bwidth = border.bottom.width;

    Vec2f pos;
    pos.x = box.pos.x;
    pos.y = box.pos.y;
    Vec2f size;
    size.x = box.size.x;
    size.y = box.size.y;

    // Left
    Vec2f pos1(pos.x - lwidth, pos.y - twidth);
    Vec2f size1(lwidth, size.y + twidth + bwidth);
    // Top
    Vec2f pos2(pos.x, pos.y - twidth);
    Vec2f size2(size.x, twidth);
    // Right
    Vec2f pos3(pos.x + size.x, pos.y - twidth);
    Vec2f size3(rwidth, size.y + twidth + bwidth);
    // Bottom
    Vec2f pos4(pos.x, pos.y + size.y);
    Vec2f size4(size.x, bwidth);

    drawCall->setColor(border.left.color);
    drawCall->appendRect2D(pos1, size1, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.top.color);
    drawCall->appendRect2D(pos2, size2, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.right.color);
    drawCall->appendRect2D(pos3, size3, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
    drawCall->setColor(border.bottom.color);
    drawCall->appendRect2D(pos4, size4, Vec2f(0, 1), Vec2f(1, 0), FG_FALSE);
}
//------------------------------------------------------------------------------

void gui::CDrawer::appendCircleBorder2D(const Vec2f &pos,
                                        float radius,
                                        CStyleContent& style) {
    if(!m_pResourceMgr)
        return;
    SBorderGroup &border = style.getBorder();
    int index;
    gfx::CDrawCall *drawCall = requestDrawCall(index, FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    drawCall->setComponentActive(0);
    drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT);
    drawCall->setPrimitiveMode(gfx::PrimitiveMode::LINE_STRIP);
    gfx::CVertexData *pVertexData = drawCall->getVertexData();
    drawCall->setColor(border.all.color);

    unsigned int nSlices = 24;
    float angle = 0.0f;
    for(unsigned int i = 0; i <= nSlices; i++) {
        angle = i * (float)2.0f * M_PIF / (float)nSlices;
        float x = pos.x + math::cos(angle) * radius;
        float y = pos.y + math::sin(angle) * radius;
        Vec3f point = Vec3f(x, y, 0);
        pVertexData->append(point, Vec3f(), Vec2f(), border.all.color);
    }
}
//------------------------------------------------------------------------------
