/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGuiSlider.cpp
 * Author: vigilant
 * 
 * Created on December 12, 2014, 10:12 PM
 */

#include "fgGuiSlider.h"
#include "fgGuiDrawer.h"

/**
 * 
 */
fgGuiSlider::fgGuiSlider() :
base_type(),
m_maxValue(100.0f),
m_currentValue(),
m_pointerRatio(),
m_ratio(0.2f, 0.2f),
m_sliderAlign(SLIDER_VERTICAL) {
    fgGuiSlider::setDefaults();
}

/**
 * 
 */
fgGuiSlider::~fgGuiSlider() { }

/**
 * 
 */
void fgGuiSlider::setDefaults(void) {
    m_type = FG_GUI_SLIDER;
    m_typeTraits = FG_GUI_SLIDER | FG_GUI_WIDGET;
    m_typeName = FG_GUI_SLIDER_NAME;
}

/**
 * 
 * @param guiLayer
 */
void fgGuiSlider::display(fgGuiDrawer* guiLayer) {
    if(!guiLayer)
        return;
    if(!m_isVisible)
        return;
    fgGuiDrawer *guiDrawer = (fgGuiDrawer *)guiLayer; // wut?
    fgGuiPadding &padding = m_styles[m_state].getPadding();
    fgGuiBorderInfo &borderInfo = m_styles[m_state].getBorder();
    fgColor4f &bgColor = m_styles[m_state].getBackground().color;
    fgColor4f &fgColor = m_styles[m_state].getForeground().color;
    /// need to normally draw Slider from base_type::display
    /// and also provide additional drawing (slider hook ?)

    fgVec2f borderXY, paddingXY;
    borderXY.x = borderInfo.left.width + borderInfo.right.width;
    borderXY.y = borderInfo.top.width + borderInfo.bottom.width;
    paddingXY.y = padding.top + padding.bottom;
    paddingXY.x = padding.left + padding.right;

    base_type::display(guiLayer);

    fgVec2f blockSize;
    fgVec2f blockPos;

    if(m_sliderAlign == SLIDER_HORIZONTAL) {
        blockSize.x = m_bbox.size.x * m_ratio.x;
        blockSize.y = m_bbox.size.y - borderXY.y - paddingXY.y;

        if(blockSize.x > m_bbox.size.x - borderXY.x - paddingXY.x)
            blockSize.x = m_bbox.size.x - borderXY.x - paddingXY.x;
        
        blockPos.x = m_bbox.pos.x - blockSize.x / 2.0f + m_pointerRatio.x * m_bbox.size.x;
        blockPos.y = m_bbox.pos.y + (m_bbox.size.y - blockSize.y) / 2.0f;
    } else if(m_sliderAlign == SLIDER_VERTICAL) {
        blockSize.x = m_bbox.size.x - borderXY.x - paddingXY.x;
        blockSize.y = m_bbox.size.y * m_ratio.y;
        
        if(blockSize.y > m_bbox.size.y - borderXY.y - paddingXY.y)
            blockSize.y = m_bbox.size.y - borderXY.y - paddingXY.y;

        blockPos.x = m_bbox.pos.x + (m_bbox.size.x - blockSize.x) / 2.0f;
        blockPos.y = m_bbox.pos.y - blockSize.y / 2.0f + m_pointerRatio.y * m_bbox.size.y;
    } else {
        blockSize.x = m_bbox.size.x * m_ratio.x;
        blockSize.y = m_bbox.size.y * m_ratio.y;

        blockPos.x = m_bbox.pos.x - blockSize.x / 2.0f + m_pointerRatio.x * m_bbox.size.x;
        blockPos.y = m_bbox.pos.y - blockSize.y / 2.0f + m_pointerRatio.y * m_bbox.size.y;
    }
    
    if(blockPos.x - padding.left < m_bbox.pos.x)
        blockPos.x = m_bbox.pos.x + padding.left;
    if(blockPos.x + blockSize.x + padding.right > m_bbox.pos.x + m_bbox.size.x)
        blockPos.x = m_bbox.pos.x + m_bbox.size.x - blockSize.x - padding.right;

    if(blockPos.y - padding.top < m_bbox.pos.y)
        blockPos.y = m_bbox.pos.y + padding.top;
    if(blockPos.y + blockSize.y + padding.bottom > m_bbox.pos.y + m_bbox.size.y)
        blockPos.y = m_bbox.pos.y + m_bbox.size.y - blockSize.y - padding.bottom;

    // magic... nope!
    m_currentValue.x = m_maxValue * ((blockPos.x - padding.left - m_bbox.pos.x) / (m_bbox.size.x - paddingXY.x - blockSize.x));
    m_currentValue.y = m_maxValue * ((blockPos.y - padding.top - m_bbox.pos.y) / (m_bbox.size.y - paddingXY.y - blockSize.y));

    if(bgColor.a > FG_EPSILON) {
        guiDrawer->appendBackground2D(blockPos, blockSize, m_styles[m_state]);
    }
    guiDrawer->appendBorder2D(blockPos, blockSize, m_styles[m_state]);
}

/**
 *
 */
int fgGuiSlider::updateState(const fgPointerData* pointerData) {
    if(!pointerData) {
        return m_state;
    }
    fgGuiWidgetState lastState = m_state;
    fgBool ignoreStateTmp = m_ignoreState;
    // So base_type::updateState does not reset m_state
    m_ignoreState = FG_FALSE;
    fgVec2f ptrRelPos;

    // This will update the state to the new value
    base_type::updateState(pointerData);

    if(m_bbox.size.x < m_bbox.size.y) {
        m_sliderAlign = SLIDER_VERTICAL;
    } else if(m_bbox.size.x > m_bbox.size.y) {
        m_sliderAlign = SLIDER_HORIZONTAL;
    } else {
        m_sliderAlign = SLIDER_UNIVERSAL;
    }

    if(m_state == FG_GUI_WIDGET_STATE_PRESSED || m_state == FG_GUI_WIDGET_STATE_ACTIVATED) {
        // Need to update the slider value 
        // Can use focus?

        // Horizontal
        ptrRelPos.x = (float)pointerData->m_x - m_bbox.pos.x;
        if(ptrRelPos.x > m_bbox.size.x)
            ptrRelPos.x = m_bbox.size.x;
        m_pointerRatio.x = ptrRelPos.x / m_bbox.size.x;
        // Vertical
        ptrRelPos.y = (float)pointerData->m_y - m_bbox.pos.y;
        if(ptrRelPos.y > m_bbox.size.y)
            ptrRelPos.y = m_bbox.size.y;
        m_pointerRatio.y = ptrRelPos.y / m_bbox.size.y;
    }

    m_ignoreState = ignoreStateTmp;
    if(m_ignoreState)
        m_state = FG_GUI_WIDGET_STATE_NONE;

    return m_state;
}
