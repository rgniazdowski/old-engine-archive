/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiTextArea.h"
#include "fgGuiDrawer.h"

/*
 *
 */
fgGuiTextArea::fgGuiTextArea() :
fgGuiScrollArea(),
m_textData(),
m_textAreaSize() {
    fgGuiTextArea::setDefaults();
}

/*
 *
 */
fgGuiTextArea::~fgGuiTextArea() { }

/*
 *
 */
void fgGuiTextArea::setDefaults(void) {
    m_type = FG_GUI_TEXT_AREA;
    m_typeName = FG_GUI_TEXT_AREA_NAME;
    m_typeTraits = FG_GUI_TEXT_AREA | FG_GUI_SCROLL_AREA | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiTextArea::updateBounds(void) {
    float textSize = m_styles[m_state].getForeground().textSize;
    fgGuiPadding &padding = m_styles[m_state].getPadding();
    m_textAreaSize.cols = (m_bbox.size.x - padding.left - padding.right) / textSize;
    m_textAreaSize.rows = (m_bbox.size.y - padding.bottom - padding.top) / textSize; // ? refresh ?
    fgBoundingBox3Df scrollAreaSize = base_type::updateBounds();
    int n = m_textData.size();
    if(m_vSlider) {
        m_vSlider->setRatio(scrollAreaSize.size.y / (textSize * n));
        m_relMove.y = (-1.0f) * (textSize * n - scrollAreaSize.size.y) * m_vSlider->getCurrentValue().y / m_vSlider->getMaxValue();
    }
    return scrollAreaSize;
}

/*
 *
 */
void fgGuiTextArea::refresh(void) {
    base_type::refresh(); // #FIXME
}

/**
 * 
 * @param guiLayer
 */
void fgGuiTextArea::display(fgGuiDrawer* guiLayer) {
    if(!guiLayer)
        return;
    if(!m_isVisible)
        return;

    base_type::display(guiLayer);

    fgGuiDrawer *guiDrawer = (fgGuiDrawer *)guiLayer;
    fgVec2f blockPos, blockSize, textSize;

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
            float charSizeY = m_styles[m_state].getForeground().textSize;
            float newPos = m_bbox.pos.y + (m_textAreaSize.rows - 1 - i) * charSizeY;
            blockPos = fgVec2f(m_bbox.pos.x, newPos);
            blockSize = fgVec2f(m_bbox.size.x, charSizeY);
            guiDrawer->appendText2D(m_textSize, blockPos, blockSize, m_styles[m_state], m_textData[j].c_str());
            guiDrawer->upZIndex();
        }
    }
}
