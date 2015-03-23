/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiScrollArea.h"
#include "fgGuiDrawer.h"
#include "Util/fgStrings.h"

using namespace fg;

/**
 * 
 */
gui::CScrollArea::CScrollArea() :
base_type(),
m_hSlider(NULL),
m_vSlider(NULL),
m_relMove(),
m_sliderSwitch(SLIDER_NONE) {
    gui::CScrollArea::setDefaults();
    m_hSlider = new CSlider();
    m_hSlider->setName("hslider");
    m_hSlider->setAlignment(CSlider::SLIDER_HORIZONTAL);
    
    m_vSlider = new CSlider();
    m_vSlider->setName("vslider");
    m_vSlider->setAlignment(CSlider::SLIDER_VERTICAL);
}

/**
 * 
 */
gui::CScrollArea::~CScrollArea() {
    if(m_hSlider) {
        delete m_hSlider;
    }
    m_hSlider = NULL;
    if(m_vSlider) {
        delete m_vSlider;
    }
    m_vSlider = NULL;
}

/**
 * 
 */
void gui::CScrollArea::setDefaults(void) {
    m_type = SCROLL_AREA;
    m_typeName = FG_GUI_SCROLL_AREA_NAME;
    m_typeTraits = SCROLL_AREA | CONTAINER | WIDGET;
}

/**
 * 
 * @param flags
 */
void gui::CScrollArea::setFlags(const std::string& flags) {
    if(flags.empty() || flags.length() < 3)
        return;
    // This is important - always call setFlags for the base class
    base_type::setFlags(flags);
    fg::CStringVector flagsVec;
    strings::split(flags, ' ', flagsVec);
    if(flagsVec.empty())
        return;
    unsigned int n = (unsigned int)flagsVec.size();
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(flagsVec[i].c_str(), "slidervertical", FG_FALSE) ||
           strings::isEqual(flagsVec[i].c_str(), "vslider", FG_FALSE)) {
            m_sliderSwitch |= SLIDER_VERTICAL;
        } else if(strings::isEqual(flagsVec[i].c_str(), "sliderhorizontal", FG_FALSE) ||
                  strings::isEqual(flagsVec[i].c_str(), "hslider", FG_FALSE)) {
            m_sliderSwitch |= SLIDER_HORIZONTAL;
        } else if(strings::isEqual(flagsVec[i].c_str(), "sliderboth", FG_FALSE)) {
            m_sliderSwitch |= SLIDER_BOTH;
        }
    }
    flagsVec.clear();
}

/**
 * 
 * @param guiLayer
 */
void gui::CScrollArea::display(CDrawer* guiLayer) {
    // Now before drawing the guiLayer needs to set the relative move
    // relative move is based on inner container size and current state of the
    // sliders - later on the sliders will be fixed to have adaptive size (toggle? anyone?)
    // Spare some change?
    if(!guiLayer) {
        return;
    }
    SPadding &padding = m_styles[(int)m_state].getPadding();
    Vector3f oldRelMove = guiLayer->getRelMove();
    Vector3f newRelMove = oldRelMove + Vector3f(m_relMove.x, m_relMove.y, 0.0f); // #FIXME

    // Draw current widget without the children and relative move
    fgBool drawChildren = isDrawChildren();
    setDrawChildren(FG_FALSE);
    base_type::display(guiLayer);
    setDrawChildren(drawChildren);

    // Get the current screen size
    Vector2i const &screenSize = guiLayer->getScreenSize();

    // Set the relative move for drawing
    // Draw base (container) children with relative position
    // relative position is based on the sliders position (value)
    guiLayer->setRelMove(newRelMove);
    // Set scissor box ! For the GL the scissor box has different alignment
    // position is for lower left corner (not upper), size goes in different direction
    //guiLayer->setScissorBox(m_bbox.pos.x, m_bbox.pos.y, m_bbox.size.x, m_bbox.size.y);

    guiLayer->setScissorBox(m_bbox.pos.x + padding.left,
                            screenSize.y - m_bbox.pos.y - m_bbox.size.y + padding.top,
                            m_bbox.size.x - padding.left - padding.right,
                            m_bbox.size.y - padding.top - padding.bottom);

    fgBool isVisible = m_isVisible; // remember current visibility switch
    m_isVisible = FG_FALSE;
    base_type::display(guiLayer);
    m_isVisible = isVisible;
    guiLayer->setScissorBox(0, 0, 0, 0); // No scissor box option... need to reset it however
    guiLayer->setRelMove(oldRelMove);

    guiLayer->downZIndex();
    if(m_hSlider && (m_sliderSwitch & SLIDER_HORIZONTAL)) {
        m_hSlider->display(guiLayer);
    }
    guiLayer->upZIndex();
    if(m_vSlider && (m_sliderSwitch & SLIDER_VERTICAL)) {
        m_vSlider->display(guiLayer);
    }
}

/**
 * 
 * @return 
 */
gfx::BoundingBox3Df gui::CScrollArea::updateBounds(void) {

    SMargin &margin = m_styles[(int)m_state].getMargin();
    gfx::BoundingBox3Df scrollAreaSize = CWidget::updateBounds();
    m_contentBBox = base_type::updateBounds();
    m_bbox = scrollAreaSize;
    m_bbox.pos.x += margin.left;
    m_bbox.pos.y += margin.top;
    m_bbox.size.x -= margin.right + margin.left;
    m_bbox.size.y -= margin.bottom + margin.top;
    
    if(m_hSlider) {
        CStyleContent &style = m_hSlider->getStyleContent(m_hSlider->getState());
        SBorderGroup &border = style.getBorder();
        float w = m_bbox.size.x - border.left.width - border.right.width;
        float h = m_bbox.size.y * 0.1f;
        if(h > 15.0f)
            h = 15.0f; // #FIXME
        float x = m_bbox.pos.x + border.left.width;
        float y = m_bbox.pos.y + m_bbox.size.y - h - border.bottom.width - border.top.width + 1;

        if(m_sliderSwitch & SLIDER_VERTICAL)
            w -= m_vSlider->getSize().x + border.left.width;
        // It's ok to set size with this function as the slider widgets are not
        // treated as normal children widgets (inside of a container)
        //m_hSlider->setSize(Vector3f(w, h, 0.0f), Unit::PIXELS);
        m_hSlider->getBBox().size = Vector3f(w, h, 0.0f);
        m_hSlider->setPosition(Vector3f(x, y, 0.0f));
        m_hSlider->updateBounds();
        m_hSlider->setRatio(scrollAreaSize.size.x / m_contentBBox.size.x);
        m_relMove.x = (-1.0f) * (m_contentBBox.size.x - scrollAreaSize.size.x) * m_hSlider->getCurrentValue().x / m_hSlider->getMaxValue();
    }
    if(m_vSlider) {
        CStyleContent &style = m_vSlider->getStyleContent(m_vSlider->getState());
        SBorderGroup &border = style.getBorder();
        float w = m_bbox.size.x * 0.1f;
        float h = m_bbox.size.y - border.top.width - border.bottom.width;
        if(w > 15.0f)
            w = 15.0f; // #FIXME
        float x = m_bbox.pos.x + m_bbox.size.x - w - border.right.width;
        float y = m_bbox.pos.y + border.top.width;
        if(m_sliderSwitch & SLIDER_HORIZONTAL)
            h -= m_hSlider->getSize().y + border.bottom.width;

        m_vSlider->setSize(Vector3f(w, h, 0.0f), Unit::PIXELS);
        m_vSlider->getBBox().size = Vector3f(w, h, 0.0f);
        // LEFT ? This will need fixing - #slider / scroll box positioning / update bounds
        m_vSlider->setPosition(Vector3f(x, y, 0.0f));
        m_vSlider->updateBounds();
        m_vSlider->setRatio(scrollAreaSize.size.y / m_contentBBox.size.y);
        m_relMove.y = (-1.0f) * (m_contentBBox.size.y - scrollAreaSize.size.y) * m_vSlider->getCurrentValue().y / m_vSlider->getMaxValue();
    }
    return scrollAreaSize;
}

/**
 * 
 * @param bbox
 * @return 
 */
gfx::BoundingBox3Df gui::CScrollArea::updateBounds(const gfx::BoundingBox3Df& bbox) {
    return base_type::updateBounds(bbox);
}

/**
 * 
 */
void gui::CScrollArea::refresh(void) {
    base_type::refresh();
    if(m_hSlider && (m_sliderSwitch & SLIDER_HORIZONTAL)) {
        m_hSlider->setStyleName(m_styleName);     
    }
    if(m_vSlider && (m_sliderSwitch & SLIDER_VERTICAL)) {
        m_vSlider->setStyleName(m_styleName);
    }
}

/**
 * 
 */
gui::CWidget::State gui::CScrollArea::updateState(const fgPointerData* pointerData) {
    if(!pointerData)
        return State::NONE;

    if(m_hSlider && (m_sliderSwitch & SLIDER_HORIZONTAL)) {
        m_hSlider->updateState(pointerData);
    }
    if(m_vSlider && (m_sliderSwitch & SLIDER_VERTICAL)) {
        m_vSlider->updateState(pointerData);
    }
    // #HAXXOR!
    fgPointerData newPointerData = *pointerData;
    newPointerData.m_x -= m_relMove.x;
    newPointerData.m_y -= m_relMove.y;
    base_type::updateState(&newPointerData);
    return m_state;
}
