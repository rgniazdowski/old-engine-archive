/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiTextArea.h"
#include "fgGuiDrawer.h"

using namespace fg;

gui::CTextArea::CTextArea() :
CScrollArea(),
m_textData(),
m_textAreaSize() {
    gui::CTextArea::setDefaults();
}

gui::CTextArea::~CTextArea() { }

void gui::CTextArea::setDefaults(void) {
    m_type = TEXT_AREA;
    m_typeName = FG_GUI_TEXT_AREA_NAME;
    m_typeTraits = TEXT_AREA | SCROLL_AREA | CONTAINER | WIDGET;
}

gfx::BoundingBox3Df gui::CTextArea::updateBounds(void) {
    float textSize = m_styles[(int)m_state].getForeground().textSize;
    SPadding &padding = m_styles[(int)m_state].getPadding();
    m_textAreaSize.cols = (m_bbox.size.x - padding.left - padding.right) / textSize;
    m_textAreaSize.rows = (m_bbox.size.y - padding.bottom - padding.top) / textSize; // ? refresh ?
    gfx::BoundingBox3Df scrollAreaSize = base_type::updateBounds();
    int n = m_textData.size();
    if(m_vSlider) {
        m_vSlider->setRatio(scrollAreaSize.size.y / (textSize * n));
        m_relMove.y = (-1.0f) * (textSize * n - scrollAreaSize.size.y) * m_vSlider->getCurrentValue().y / m_vSlider->getMaxValue();
    }
    return scrollAreaSize;
}

void gui::CTextArea::refresh(void) {
    base_type::refresh(); // #FIXME
}

void gui::CTextArea::display(CDrawer* guiLayer) {
    if(!guiLayer)
        return;
    if(!isVisible())
        return;

    base_type::display(guiLayer);

    CDrawer *guiDrawer = (CDrawer *)guiLayer;
    Vec2f blockPos, blockSize, textSize;

    int n = m_textData.size();
    //float sliderRatio = (float)m_textAreaSize.rows/(float)n;
    //m_vSlider->setRatio(sliderRatio);
    float ratio = m_vSlider->getCurrentValue().y / m_vSlider->getMaxValue();
    int begin = (int)(n - m_textAreaSize.rows - 1) * ratio;
    if(begin < 0)
        begin = 0;

    for(int i = 0, j = begin + m_textAreaSize.rows; j >= begin; j--, i++) {
        if(m_textData[j].length()) {
            // #FIXME
            guiDrawer->downZIndex();
            float charSizeY = m_styles[(int)m_state].getForeground().textSize;
            float newPos = m_bbox.pos.y + (m_textAreaSize.rows - 1 - i) * charSizeY;
            blockPos = Vec2f(m_bbox.pos.x, newPos);
            blockSize = Vec2f(m_bbox.size.x, charSizeY);
            guiDrawer->appendText2D(m_textSize, blockPos, blockSize, m_styles[(int)m_state], m_textData[j].c_str());
            guiDrawer->upZIndex();
        }
    }
}
