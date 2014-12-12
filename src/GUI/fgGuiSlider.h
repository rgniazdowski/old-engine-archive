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

    enum SliderType {
        SLIDER_HORIZONTAL,
        SLIDER_VERTICAL
    };

protected:
    ///
    float m_maxValue;
    ///
    float m_currentValue;
    ///
    SliderType m_sliderType;

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

};

    #undef FG_INC_GUI_SLIDER_BLOCK
#endif	/* FG_INC_GUI_SLIDER */

