/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiWidget.h"
#include "fgGuiDrawer.h"
#include "Resource/fgResource.h"

/*
 *
 */
fgGuiWidget::fgGuiWidget() :
m_nameTag(),
m_typeName(),
m_styleName(FG_GUI_WIDGET_DEFAULT_STYLE),
m_link(),
m_action(),
m_script(),
m_config(),
m_text(),
m_relPos(),
m_bbox(),
m_textSize(),
m_onFocus(NULL),
m_onFocusLost(NULL),
m_onClick(NULL),
m_onActivate(NULL),
m_onDeactivate(NULL),
m_onKey(NULL),
m_onMouse(NULL),
m_onChangeState(NULL),
m_fatherPtr(),
m_type(FG_GUI_WIDGET_UNKNOWN),
m_typeTraits(FG_GUI_WIDGET_UNKNOWN),
m_state(FG_GUI_WIDGET_STATE_NONE),
m_isManaged(FG_FALSE),
m_isVisible(FG_TRUE),
m_isActive(FG_TRUE),
m_ignoreState(FG_FALSE) {
    m_bbox.pos.x = -1.0f;
    m_bbox.pos.y = -1.0f;
    m_bbox.pos.z = -1.0f;
    m_bbox.size.x = -1.0f;
    m_bbox.size.y = -1.0f;
    m_bbox.size.z = -1.0f;
}

/*
 *
 */
fgGuiWidget::~fgGuiWidget() { }

/**
 * 
 * @param guiLayer
 */
void fgGuiWidget::display(fgGfxLayer *guiLayer) {
    if(!guiLayer)
        return;
    fgGuiDrawer *guiDrawer = (fgGuiDrawer *)guiLayer;
    //if(!guiDrawer->getResourceManager())
    //return;
    guiDrawer->downZIndex();
    fgVec2f blockPos = fgVec2f(m_bbox.pos.x, m_bbox.pos.y);
    fgVec2f blockSize = fgVec2f(m_bbox.size.x, m_bbox.size.y);
    guiDrawer->appendBackground2D(blockPos, blockSize, m_styles[m_state]);
    guiDrawer->appendBorder2D(blockPos, blockSize, m_styles[m_state]);
    if(m_text.length()) {
        guiDrawer->appendText2D(m_textSize, blockPos, blockSize, m_styles[m_state], getTextStr());
    }
}

/**
 * 
 * @return 
 */
fgBoundingBox3Df& fgGuiWidget::updateSize(void) {
    fgGuiPadding &padding = m_styles[m_state].getPadding();
    if(m_bbox.size.x < m_textSize.x) {
        m_bbox.size.x = m_textSize.x + padding.left + padding.right;
    }
    if(m_bbox.size.y < m_textSize.y) {
        m_bbox.size.y = m_textSize.y + padding.top + padding.bottom;
    }
    return m_bbox;
}

/**
 * 
 * @param bounds
 * @return 
 */
fgBoundingBox3Df& fgGuiWidget::updateSize(const fgBoundingBox3Df &bounds) {
    fgGuiStyleContent &style = m_styles[m_state];
    fgGuiPositionStyle posStyle = style.getPosition().style;
    fgGuiSize &size = style.getSize();
    if(size.style == FG_GUI_SIZE_MAX) {
        m_bbox.size.x = bounds.size.x;
        m_bbox.size.y = bounds.size.y;
    } else if(size.style == FG_GUI_SIZE_PERCENTS) {
        m_bbox.size.x = size.x / 100.0f * bounds.size.x;
        m_bbox.size.y = size.y / 100.0f * bounds.size.y;
    }
    updateSize();


    // Margin?
    if(posStyle == FG_GUI_POS_STATIC) {
        m_bbox.pos = bounds.pos;
        style.applyPosAlign(style.getAlign(), m_bbox.pos, m_bbox.size, bounds.size);
        style.applyPosAlign(style.getVAlign(), m_bbox.pos, m_bbox.size, bounds.size);
    } else if(posStyle == FG_GUI_POS_FIXED) {
        // nothing to change
    } else if(posStyle == FG_GUI_POS_RELATIVE) {
        m_bbox.pos.x = bounds.pos.x + style.getMargin().left + m_relPos.x;
        m_bbox.pos.y = bounds.pos.y + style.getMargin().top + m_relPos.y;
    } else if(posStyle == FG_GUI_POS_ABSOLUTE) {

    }

#if 0
    if(this.Position.X - bound_pos.X < this.EditableStyle.CurrentStyle.Spacing)
        this.Position.X += this.EditableStyle.CurrentStyle.Spacing - (this.Position.X - bound_pos.X);
    if(this.Position.Y - bound_pos.Y < this.EditableStyle.CurrentStyle.Spacing)
        this.Position.Y += this.EditableStyle.CurrentStyle.Spacing - (this.Position.Y - bound_pos.Y);

    if((bound_pos.X + bound_size.X) - (this.Position.X + this.Size.X) < this.EditableStyle.CurrentStyle.Spacing)
        positionAndSize.Z += this.EditableStyle.CurrentStyle.Spacing;
    if((bound_pos.Y + bound_size.Y) - (this.Position.Y + this.Size.Y) < this.EditableStyle.CurrentStyle.Spacing)
        positionAndSize.W += this.EditableStyle.CurrentStyle.Spacing/*- 0 * ((bound_pos.Y + bound_size.Y) - (this.pos.Y + this.size.Y))*/;
#endif
    return m_bbox;
}

/*
 *
 */
void fgGuiWidget::refresh(void) { }

/**
 * 
 * @param pointerData
 * @return 
 */
int fgGuiWidget::updateState(const fgPointerData *pointerData) {
    if(!pointerData)
        return m_state;
    if(!m_isActive) {
        m_state = FG_GUI_WIDGET_STATE_DEACTIVATED;
        return m_state;
    }
    m_state = FG_GUI_WIDGET_STATE_NONE;
    if(m_bbox.test((float)pointerData->m_x, (float)pointerData->m_y)) {
        m_state = FG_GUI_WIDGET_STATE_FOCUS;
        //this.TriggerEventName("onFocus");
    }

    if(m_state == FG_GUI_WIDGET_STATE_FOCUS) {

        if(pointerData->m_state & FG_POINTER_STATE_PRESSED)//|| pointerData->m_state & FG_POINTER_STATE_DOWN) 
        {
            m_state = FG_GUI_WIDGET_STATE_PRESSED;
        } else if(pointerData->m_state == FG_POINTER_STATE_RELEASED && pointerData->m_pointerTap) {
            m_state = FG_GUI_WIDGET_STATE_ACTIVATED;
        } else {
        }
    }

    if(m_ignoreState)
        m_state = FG_GUI_WIDGET_STATE_NONE;
    return m_state;
}
