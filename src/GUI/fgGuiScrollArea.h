/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_SCROLL_AREA
    #define FG_INC_GUI_SCROLL_AREA
    #define FG_INC_GUI_SCROLL_AREA_BLOCK

    #if defined(FG_INC_GUI_SLIDER_BLOCK)
        #error "FG_INC_GUI_SLIDER_BLOCK is defined: Do not include GuiScrollArea header inside of GuiSlider header"
    #endif

    #include "fgGuiSlider.h"
    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

/**
 *
 */
class fgGuiScrollArea : public fgGuiContainer {
public:
    ///
    typedef fgGuiContainer base_type;

public:
    enum SliderSwitch {
        SLIDER_NONE = 0,
        SLIDER_HORIZONTAL = 1,
        SLIDER_VERTICAL = 2,
        SLIDER_BOTH = 3
    };
    
protected:
    /// Horizontal slider
    fgGuiSlider *m_hSlider;
    /// Vertical slider
    fgGuiSlider *m_vSlider;
    /// Relative move of the content based on the w/h sliders
    fgVector2f m_relMove;
    /// Which slider to show?
    SliderSwitch m_sliderSwitch;
    /// Special bounding box describing the inner content (container)
    fgBoundingBox3Df m_contentBBox;
    
protected:
    /**
     * 
     */
    virtual void setDefaults(void);

public:
    /**
     * 
     */
    fgGuiScrollArea();
    /**
     * 
     */
    virtual ~fgGuiScrollArea();

    /**
     * 
     * @return 
     */
    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiScrollArea);

    /**
     * 
     * @return 
     */
    virtual void setFlags(const std::string& flags);
    
    /**
     * 
     * @param guiLayer
     */
    virtual void display(fgGuiDrawer *guiLayer);
    
    /**
     * 
     * @return 
     */
    virtual fgBoundingBox3Df updateBounds(void);
    
    /**
     * 
     * @param bbox
     * @return 
     */
    virtual fgBoundingBox3Df updateBounds(const fgBoundingBox3Df &bbox);
    
    /**
     * 
     */
    virtual void refresh(void);
    
    /**
     * 
     * @param pointerData
     * @return 
     */
    virtual int updateState(const fgPointerData *pointerData);

};

FG_ENUM_FLAGS(fgGuiScrollArea::SliderSwitch);

    #undef FG_INC_GUI_SCROLL_AREA_BLOCK
#endif /* FG_INC_GUI_SCROLL_AREA */
