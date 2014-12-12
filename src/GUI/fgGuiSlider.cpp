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
m_currentValue(0.0f),
m_sliderType(SLIDER_VERTICAL) {
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

    float borderTB = borderInfo.top.width + borderInfo.bottom.width;
    float paddingTB = padding.top + padding.bottom;

    base_type::display(guiLayer);
    fgVec2f ratio = fgVec2f(0.2f, 0.95f /* ?? */);
    fgVec2f blockSize = 
            fgVec2f(m_bbox.size.x * ratio.x,
                    (m_bbox.size.y - borderTB - paddingTB));
    fgVec2f blockPos = 
            fgVec2f(m_bbox.pos.x - blockSize.x / 2.0f + (m_currentValue / m_maxValue) * m_bbox.size.x,
                    m_bbox.pos.y + (m_bbox.size.y - blockSize.y)/2.0f);
    if(blockPos.x - padding.left < m_bbox.pos.x)
        blockPos.x = m_bbox.pos.x + padding.left;
    if(blockPos.x + blockSize.x + padding.right > m_bbox.pos.x+m_bbox.size.x)
        blockPos.x = m_bbox.pos.x+m_bbox.size.x - blockSize.x - padding.right;
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
        m_sliderType = SLIDER_VERTICAL;
    } else {
        m_sliderType = SLIDER_HORIZONTAL;
    }

    float ratio = 0.0f;

    if(m_state == FG_GUI_WIDGET_STATE_PRESSED || m_state == FG_GUI_WIDGET_STATE_ACTIVATED) {
        // Need to update the slider value 
        // Can use focus?

        if(m_sliderType == SLIDER_HORIZONTAL) {
            ptrRelPos.x = (float)pointerData->m_x - m_bbox.pos.x;
            if(ptrRelPos.x > m_bbox.size.x)
                ptrRelPos.x = m_bbox.size.x;
            ratio = ptrRelPos.x / m_bbox.size.x;
        } else {
            // Vertical
            ptrRelPos.y = (float)pointerData->m_y - m_bbox.pos.y;
            if(ptrRelPos.y > m_bbox.size.y)
                ptrRelPos.y = m_bbox.size.y;
            ratio = ptrRelPos.y / m_bbox.size.y;
        }
        // magic... nope!
        m_currentValue = m_maxValue * ratio;
    }

    m_ignoreState = ignoreStateTmp;
    if(m_ignoreState)
        m_state = FG_GUI_WIDGET_STATE_NONE;

    return m_state;
}
