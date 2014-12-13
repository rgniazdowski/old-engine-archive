/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGuiSlider.h
 * Author: vigilant
 *
 * Created on December 12, 2014, 10:12 PM
 */

#ifndef FG_INC_GUI_SLIDER
    #define FG_INC_GUI_SLIDER
    #define FG_INC_GUI_SLIDER_BLOCK

    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactoryTypes.h"

/**
 * 
 */
class fgGuiSlider : public fgGuiWidget {
public:
    ///
    typedef fgGuiWidget base_type;

    enum SliderAlign {
        SLIDER_UNDEFINED = 0,
        SLIDER_HORIZONTAL = 1,
        SLIDER_VERTICAL = 2,
        SLIDER_UNIVERSAL = 3
    };

protected:
    ///
    float m_maxValue;
    ///
    fgVec2f m_currentValue;
    /// This is special ratio - it's based on the position of the pointer over slider
    fgVec2f m_pointerRatio;
    /// This is ratio of the slider - determines size of the slider
    fgVec2f m_ratio;
    ///
    SliderAlign m_sliderAlign;

protected:
    /**
     * 
     */
    virtual void setDefaults(void);

public:
    /**
     * 
     */
    fgGuiSlider();
    /**
     * 
     */
    virtual ~fgGuiSlider();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiSlider);


    /**
     * 
     * @param guiLayer
     */
    virtual void display(fgGuiDrawer *guiLayer);

    /**
     * 
     * @param pointerData
     * @return 
     */
    virtual int updateState(const fgPointerData *pointerData);

public:
    /**
     * 
     * @param sliderAlign
     */
    void setAlignment(SliderAlign sliderAlign) {
        m_sliderAlign = sliderAlign;
        // alignment
    }
    /**
     * 
     * @return 
     */
    SliderAlign getAlignment(void) const {
        return m_sliderAlign;

    }
    /**
     * 
     * @return 
     */
    fgVec2f const & getRatio(void) const {
        return m_ratio;
    }
    /**
     * 
     * @param ratio
     */
    void setRatio(float ratio) {
        if(ratio > 1.0f)
            ratio = 1.0f;
        if(ratio < 0.15f)
            ratio = 0.15f;
        if(m_sliderAlign & SLIDER_HORIZONTAL)
            m_ratio.x = ratio;
        if(m_sliderAlign & SLIDER_VERTICAL)
            m_ratio.y = ratio;
    }
    /**
     * 
     * @param x
     * @param y
     */
    void setRatio(float x, float y) {
        if(x > 1.0f)
            x = 1.0f;
        if(y > 1.0f)
            y = 1.0f;
        if(x < 0.15f)
            x = 0.15f;
        if(y < 0.15f)
            y = 0.15f;
        m_ratio.x = x;
        m_ratio.y = y;
    }
    /**
     * 
     * @param currentValue
     */
    void setRatio(const fgVector2f& ratio) {
        m_ratio = ratio;
    }
    /**
     * 
     * @return 
     */
    fgVec2f const & getCurrentValue(void) const {
        return m_currentValue;
    }
    /**
     * 
     * @param x
     * @param y
     */
    void setCurrentValue(float x, float y) {
        m_currentValue.x = x;
        m_currentValue.y = y;
    }
    /**
     * 
     * @param currentValue
     */
    void setCurrentValue(const fgVector2f& currentValue) {
        m_currentValue = currentValue;
    }
    /**
     * 
     * @return 
     */
    float getMaxValue(void) const {
        return m_maxValue;
    }
    /**
     * 
     * @param maxValue
     */
    void setMaxValue(float maxValue) {
        m_maxValue = maxValue;
    }

};

FG_ENUM_FLAGS(fgGuiSlider::SliderAlign);

    #undef FG_INC_GUI_SLIDER_BLOCK
#endif	/* FG_INC_GUI_SLIDER */
