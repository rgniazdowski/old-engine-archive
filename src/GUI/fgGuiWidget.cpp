/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgDebugConfig.h"
#include "fgGuiWidget.h"
#include "fgGuiDrawer.h"
#include "Resource/fgResource.h"

using namespace fg;

//------------------------------------------------------------------------------

gui::CWidget::CWidget() :
CManagedObject(),
m_typeName(),
m_styleName(FG_GUI_WIDGET_DEFAULT_STYLE),
m_link(),
m_action(),
m_script(),
m_config(),
m_text(),
m_relPos(),
m_bbox(),
m_textSize(0.0f, 0.0f),
m_onFocus(NULL),
m_onFocusLost(NULL),
m_onClick(NULL),
m_onActivate(NULL),
m_onDeactivate(NULL),
m_onKey(NULL),
m_onMouse(NULL),
m_onChangeState(NULL),
m_onLink(NULL),
m_pFather(NULL),
m_type(WIDGET_UNKNOWN),
m_typeTraits(WIDGET_UNKNOWN),
m_state(STATE_NONE),
m_stateFlags(VISIBLE | ACTIVE) {
    m_bbox.pos.x = -1.0f;
    m_bbox.pos.y = -1.0f;
    m_bbox.pos.z = -1.0f;
    m_bbox.size.x = -1.0f;
    m_bbox.size.y = -1.0f;
    m_bbox.size.z = -1.0f;
}
//------------------------------------------------------------------------------

gui::CWidget::~CWidget() { }
//------------------------------------------------------------------------------

void gui::CWidget::setSize(const Vector3f& size, Unit unit) {
    m_bbox.size = size;

    m_styles[STATE_NONE].getSize().style = (SSize::Style)unit;
    m_styles[STATE_NONE].getSize().set(size);
    m_styles[STATE_FOCUS].getSize().style = (SSize::Style)unit;
    m_styles[STATE_FOCUS].getSize().set(size);
    m_styles[STATE_PRESSED].getSize().style = (SSize::Style)unit;
    m_styles[STATE_PRESSED].getSize().set(size);
    m_styles[STATE_ACTIVATED].getSize().style = (SSize::Style)unit;
    m_styles[STATE_ACTIVATED].getSize().set(size);
    m_styles[STATE_DEACTIVATED].getSize().style = (SSize::Style)unit;
    m_styles[STATE_DEACTIVATED].getSize().set(size);
}
//------------------------------------------------------------------------------

void gui::CWidget::preRender(CDrawer* guiLayer) {
    if(!guiLayer)
        return;
    if(!isVisible())
        return;
    CDrawer *guiDrawer = (CDrawer*)guiLayer;
    guiDrawer->downZIndex();
    Vec2f tmpTextSize;
    Vec2f blockPos = Vec2f(m_bbox.pos.x, m_bbox.pos.y);
    Vec2f blockSize = Vec2f(m_bbox.size.x, m_bbox.size.y);
    Color4f &bgColor = m_styles[m_state].getBackground().color;
    if(bgColor.a > FG_EPSILON)
        guiDrawer->appendBackground2D(blockPos, blockSize, m_styles[m_state]);
    guiDrawer->appendBorder2D(blockPos, blockSize, m_styles[m_state]);
#if defined(FG_DEBUG)
    // BLOCK SIZE / POS DEBUG PRINT
    if(g_DebugConfig.guiBBoxShow) {
        guiDrawer->downZIndex();
        char buf[256];
        snprintf(buf, 255, "%s >> %.1fx%.1f [%.1fx%.1f]", m_nameTag.c_str(), blockPos.x, blockPos.y, blockSize.x, blockSize.y);
        float tSize = m_styles[m_state].getForeground().textSize;
        Color4f tColor = m_styles[m_state].getForeground().color;
        std::string tFont = m_styles[m_state].getForeground().font;
        m_styles[m_state].getForeground().textSize = 2.0f;
        m_styles[m_state].getForeground().unit = Unit::PERCENTS;
        m_styles[m_state].getForeground().font = "StbConsolasBold";
        m_styles[m_state].getForeground().color = Color4f(.8f, .2f, .1f, 1.0f);
        blockSize.y = 10.0f;
        guiDrawer->appendText2D(tmpTextSize, blockPos, blockSize, m_styles[m_state], buf);
        m_styles[m_state].getForeground().textSize = tSize;
        m_styles[m_state].getForeground().font = tFont;
        m_styles[m_state].getForeground().color = tColor;
        guiDrawer->upZIndex();
    }
#endif
    if(m_text.length()) {
        // #FIXME
        guiDrawer->downZIndex();
        blockPos = Vec2f(m_bbox.pos.x, m_bbox.pos.y);
        blockSize = Vec2f(m_bbox.size.x, m_bbox.size.y);
        guiDrawer->appendText2D(m_textSize, blockPos, blockSize, m_styles[m_state], getTextStr());
        guiDrawer->upZIndex();
    }
#if defined(FG_DEBUG)
    // PADDING DEBUG - INNER BORDER
    if(g_DebugConfig.guiBBoxShow) {
        blockPos = Vec2f(m_bbox.pos.x, m_bbox.pos.y);
        blockSize = Vec2f(m_bbox.size.x, m_bbox.size.y);
        blockPos.x += m_styles[m_state].getPadding().left;
        blockPos.y += m_styles[m_state].getPadding().top;
        blockSize.x -= m_styles[m_state].getPadding().right + m_styles[m_state].getPadding().left;
        blockSize.y -= m_styles[m_state].getPadding().bottom + m_styles[m_state].getPadding().top;
        guiDrawer->appendBorder2D(blockPos, blockSize, m_styles[0]);
    }
    // MARGIN DEBUG - OUTER BORDER
    if(g_DebugConfig.guiBBoxShow) {
        blockPos = Vec2f(m_bbox.pos.x, m_bbox.pos.y);
        blockSize = Vec2f(m_bbox.size.x, m_bbox.size.y);
        blockPos.x -= m_styles[m_state].getMargin().left;
        blockPos.y -= m_styles[m_state].getMargin().top;
        blockSize.x += m_styles[m_state].getMargin().right + m_styles[m_state].getMargin().left;
        blockSize.y += m_styles[m_state].getMargin().bottom + m_styles[m_state].getMargin().top;
        guiDrawer->appendBorder2D(blockPos, blockSize, m_styles[0]);
    }
#endif
}
//------------------------------------------------------------------------------

gfx::BoundingBox3Df gui::CWidget::updateBounds(void) {
    CStyleContent &style = m_styles[m_state];
    SPadding &padding = style.getPadding();
    // Padding is inside of the border - it applies to the contents inside
    // of the widget, in this case the lowest (most deep) content is initial
    // text / label 
    Vector3f minSize;
    minSize.x = m_textSize.x + padding.left + padding.right;
    minSize.y = m_textSize.y + padding.top + padding.bottom;
    if(m_bbox.size.x < minSize.x) {
        m_bbox.size.x = minSize.x;
    }
    if(m_bbox.size.y < minSize.y) {
        m_bbox.size.y = minSize.y;
    }
    gfx::BoundingBox3Df positionAndSize = m_bbox;
    positionAndSize.pos.x -= style.getMargin().left;
    positionAndSize.pos.y -= style.getMargin().top;
    positionAndSize.size.x += style.getMargin().right + style.getMargin().left;
    positionAndSize.size.y += style.getMargin().bottom + style.getMargin().top;
    return positionAndSize;
}
//------------------------------------------------------------------------------

gfx::BoundingBox3Df gui::CWidget::updateBounds(const gfx::BoundingBox3Df &bounds) {
    CStyleContent &style = m_styles[m_state];
    SPosition::Style posStyle = style.getPosition().style;
    SSize &size = style.getSize();
    if(size.style == SSize::Style::MAX) {
        m_bbox.size.x = bounds.size.x - style.getMargin().left - style.getMargin().right;
        m_bbox.size.y = bounds.size.y - style.getMargin().bottom - style.getMargin().top;
    } else if(size.style == SSize::Style::PERCENTS) {
        m_bbox.size.x = size.x / 100.0f * bounds.size.x - style.getMargin().left - style.getMargin().right;
        m_bbox.size.y = size.y / 100.0f * bounds.size.y - style.getMargin().bottom - style.getMargin().top;
    }
    gfx::BoundingBox3Df positionAndSize = updateBounds(); // Call to the derived version
    // Margin?
    if(posStyle == SPosition::Style::STATICPOS) {
        m_bbox.pos = bounds.pos;
        // Padding is inside of the border
        // Margin is outside of the border
        m_bbox.pos.x += style.getMargin().left;
        m_bbox.pos.y += style.getMargin().top;
        style.applyPosAlign(style.getAlign(), m_bbox.pos, m_bbox.size, bounds.pos, bounds.size, FG_FALSE);
        style.applyPosAlign(style.getVAlign(), m_bbox.pos, m_bbox.size, bounds.pos, bounds.size, FG_FALSE);
    } else if(posStyle == SPosition::Style::FIXED) {
        // nothing to change
    } else if(posStyle == SPosition::Style::RELATIVE) {
        m_bbox.pos.x = bounds.pos.x + style.getMargin().left + m_relPos.x;
        m_bbox.pos.y = bounds.pos.y + style.getMargin().top + m_relPos.y;
    } else if(posStyle == SPosition::Style::ABSOLUTE) {

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


    //    if(m_bbox.pos.x - bounds.pos.x < style.getMargin().left + style.getMargin().right)
    //        m_bbox.pos.x += style.getMargin().left + style.getMargin().right - (m_bbox.pos.x - bounds.pos.x);
    //    if(m_bbox.pos.y - bounds.pos.y < style.getMargin().top + style.getMargin().bottom)
    //        m_bbox.pos.y += style.getMargin().top + style.getMargin().bottom - (m_bbox.pos.y - bounds.pos.y);

    //    if((bounds.pos.x + bounds.size.x) - (m_bbox.pos.x + m_bbox.size.x) < style.getMargin().left+style.getMargin().right)
    //positionAndSize.size.x += style.getMargin().left+style.getMargin().right;
    //    if((bounds.pos.y + bounds.size.y) - (m_bbox.pos.y + m_bbox.size.y) < style.getMargin().top+style.getMargin().bottom)
    //  positionAndSize.size.y += style.getMargin().top+style.getMargin().bottom;

    positionAndSize.pos = m_bbox.pos;
    positionAndSize.pos.x -= style.getMargin().left;
    positionAndSize.pos.y -= style.getMargin().top;
    //positionAndSize.size.x += style.getMargin().right + style.getMargin().left;
    //positionAndSize.size.y += style.getMargin().bottom + style.getMargin().top;
    return positionAndSize;
}
//------------------------------------------------------------------------------

void gui::CWidget::refresh(void) {
    if(m_styles[m_state].getPosition().style != SPosition::Style::STATICPOS) {
        if(FG_GUI_CHECK_FLOAT(m_styles[m_state].getPosition().left))
            m_relPos.x = m_styles[m_state].getPosition().left;
        if(FG_GUI_CHECK_FLOAT(m_styles[m_state].getPosition().top))
            m_relPos.y = m_styles[m_state].getPosition().top;
    }
}
//------------------------------------------------------------------------------

gui::CWidget::EventState gui::CWidget::updateState(const event::SPointerData *pointerData) {
    if(!pointerData)
        return m_state;
    if(!isActive()) {
        m_state = STATE_DEACTIVATED;
        // what about deactivate callback
        // maybe on deactivate should be called when isActive is set to false?
        return m_state;
    }
    EventState lastState = m_state;
    m_state = STATE_NONE;
    if(m_bbox.test((float)pointerData->m_x, (float)pointerData->m_y)) {
        m_state = STATE_FOCUS;
        //if(!m_ignoreState) FG_LOG_DEBUG("GUI: Widget name[%s] state[FOCUS]", getNameStr());
    }

    if(m_state == STATE_FOCUS) {
        if(lastState == STATE_NONE) {
            // Focus gained
            if(m_onFocus) {
                m_onFocus->Call(this);
            }
        }
        if(pointerData->m_state & FG_POINTER_STATE_PRESSED)//|| pointerData->m_state & FG_POINTER_STATE_DOWN) 
        {
            m_state = STATE_PRESSED;
            //if(!m_ignoreState) FG_LOG_DEBUG("GUI: Widget name[%s] state[PRESSED]", getNameStr());
        } else if(pointerData->m_state == FG_POINTER_STATE_RELEASED) {
            if(lastState == STATE_PRESSED) {
                // On click event - does not care about tap
                // when widget is tapped - on activate event is called
                if(m_onClick) {
                    m_onClick->Call(this);
                }
                //if(!m_ignoreState) FG_LOG_DEBUG("GUI: Widget name[%s] state[CLICK]", getNameStr());

                if(pointerData->m_pointerTap) {
                    m_state = STATE_ACTIVATED;
                    if(lastState != STATE_ACTIVATED) {
                        //if(!m_ignoreState) FG_LOG_DEBUG("GUI: Widget name[%s] state[ACTIVATED]", getNameStr());
                        if(m_onActivate && lastState != STATE_ACTIVATED) {
                            m_onActivate->Call(this);
                            FG_LOG_DEBUG("GUI: Widget name[%s] call:onActivate()", getNameStr());
                        }
                        if(m_onLink && m_link.length()) {
                            // This a special callback, designed for menu navigation
                            m_onLink->Call(this);
                            FG_LOG_DEBUG("GUI: Widget name[%s] call:onLink()", getNameStr());
                        }
                    }
                }
            }
            if(pointerData->m_pointerTap) {
                m_state = STATE_ACTIVATED;
            }
        } else {
            // que paso?
        }
    } else if(lastState == STATE_FOCUS) {
        // Focus lost
        // It may be required that this calls should be executed in a different
        // thread or place - for now this will occur "in place" - where the widget
        // is processed. Maybe it should be delegated up to GuiMain - put on
        // queue or something... Update state would require additional parameter
        // callback dispatcher ? hmm... throw callback pointer with additional params
        // #TODO - callback dispatcher base class P2/3
        if(m_onFocusLost)
            m_onFocusLost->Call(this);
        //if(!m_ignoreState) FG_LOG_DEBUG("GUI: Widget name[%s] state[FOCUS LOST]", getNameStr());
    }
    //if(!m_ignoreState && m_state != 0 && m_state != lastState) FG_LOG_DEBUG("GUI: Widget name[%s] state[%d] lastState[%d] -> 0-none, 1-focus, 2-pressed, 3-activated", getNameStr(), m_state, lastState);
    // key events!
    if(m_state != lastState) {
        if(m_onChangeState)
            m_onChangeState->Call(this);
    }
    if(isIgnoreState())
        m_state = STATE_NONE;
    // #FIXME - relative positioning refresh ? why?
    if(m_state != lastState && m_styles[m_state].getPosition().style == SPosition::Style::RELATIVE) {
        if(FG_GUI_CHECK_FLOAT(m_styles[m_state].getPosition().left)) {
            m_relPos.x = m_styles[m_state].getPosition().left;
        }
        if(FG_GUI_CHECK_FLOAT(m_styles[m_state].getPosition().top)) {
            m_relPos.y = m_styles[m_state].getPosition().top;
        }
    }
    return m_state;
}
//------------------------------------------------------------------------------
