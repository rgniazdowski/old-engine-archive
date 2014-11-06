/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiContainer.h"
#include "Util/fgStrings.h"
#include "fgGuiDrawer.h"

/**
 *
 */
fgGuiContainer::fgGuiContainer() :
fgGuiWidget(),
m_packMethod(FG_GUI_CONTAINER_PACK_FREE),
m_packAlign(FG_GUI_CONTAINER_PACK_ALIGN_NONE) {
    fgGuiContainer::setDefaults();
}

/**
 *
 */
fgGuiContainer::~fgGuiContainer() {
    // What about freeing children widgets?
    // There should be some way to mark widgets for deletion (removal)
    // From the widget manager

    // Also if container has widgets that are not managed (not in manager)
    // Should container delete (call destructors) them? My guess... yes.
    m_children.clear_optimised();
    m_childrenMap.clear();
}

/**
 *
 */
void fgGuiContainer::setDefaults(void) {
    m_type = FG_GUI_CONTAINER;
    m_typeName = FG_GUI_CONTAINER_NAME;
    m_typeTraits = FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/**
 * 
 * @param flags
 */
void fgGuiContainer::setFlags(const std::string& flags) {
    if(flags.empty() || flags.length() < 5)
        return;
    // This is important - always call setFlags for the base class
    fgGuiWidget::setFlags(flags);
    m_packMethod = FG_GUI_CONTAINER_PACK_FREE;
    m_packAlign = FG_GUI_CONTAINER_PACK_ALIGN_NONE;
    fgStringVector flagsVec;
    fgStrings::split(flags, ' ', flagsVec);
    if(flagsVec.empty())
        return;
    unsigned int n = (unsigned int)flagsVec.size();
    for(unsigned int i = 0; i < n; i++) {
        if(flagsVec[i].compare("packfree") == 0) {
            m_packMethod = FG_GUI_CONTAINER_PACK_FREE;
        } else if(flagsVec[i].compare("packhorizontal") == 0 || flagsVec[i].compare("packh") == 0) {
            m_packMethod = FG_GUI_CONTAINER_PACK_HORIZONTAL;
        } else if(flagsVec[i].compare("packvertical") == 0 || flagsVec[i].compare("packv") == 0) {
            m_packMethod = FG_GUI_CONTAINER_PACK_VERTICAL;
        } else if(flagsVec[i].compare("none") == 0) {
            m_packAlign = FG_GUI_CONTAINER_PACK_ALIGN_NONE;
        } else if(flagsVec[i].compare("left") == 0) {
            m_packAlign |= FG_GUI_CONTAINER_PACK_ALIGN_LEFT;
        } else if(flagsVec[i].compare("right") == 0) {
            m_packAlign |= FG_GUI_CONTAINER_PACK_ALIGN_RIGHT;
        } else if(flagsVec[i].compare("top") == 0) {
            m_packAlign |= FG_GUI_CONTAINER_PACK_ALIGN_TOP;
        } else if(flagsVec[i].compare("bottom") == 0) {
            m_packAlign |= FG_GUI_CONTAINER_PACK_ALIGN_BOTTOM;
        } else if(flagsVec[i].compare("vcenter") == 0) {
            m_packAlign |= FG_GUI_CONTAINER_PACK_ALIGN_VCENTER;
        } else if(flagsVec[i].compare("hcenter") == 0) {
            m_packAlign |= FG_GUI_CONTAINER_PACK_ALIGN_HCENTER;
        } else if(flagsVec[i].compare("center") == 0) {
            m_packAlign |= FG_GUI_CONTAINER_PACK_ALIGN_CENTER;
        } else if(flagsVec[i].compare("middle") == 0) {
            m_packAlign = FG_GUI_CONTAINER_PACK_ALIGN_MIDDLE;
        }
    }
    flagsVec.clear();
}
fgGuiDrawer *yolo = NULL;

/**
 * 
 * @param guiLayer
 */
void fgGuiContainer::display(fgGfxLayer *guiLayer) {
    if(!guiLayer)
        return;
    fgGuiWidget::display(guiLayer);
    for(int i = 0; i < (int)m_children.size(); i++) {
        fgGuiWidget *child = m_children[i];
        if(!child)
            continue;
        child->display(guiLayer);
    }
    yolo = (fgGuiDrawer *)guiLayer;
}

/**
 * 
 * @return 
 */
fgBoundingBox3Df fgGuiContainer::updateBounds(void) {
    if(m_children.empty()) {
        return fgGuiWidget::updateBounds();
    }
    // Update this container size (#FIXME)
    // This is just for reference, it will
    // set the minimal size
    fgGuiWidget::updateBounds();
    // Current container style 
    fgGuiStyleContent &containerStyle = m_styles[m_state];
    // Current container padding (inner border)
    fgGuiPadding &containerPadding = containerStyle.getPadding();
    // Current container margins (outer border)
    fgGuiMargin &containerMargin = containerStyle.getMargin();
    // outerBox - this box takes into account current widget's margin
    fgBoundingBox3Df outerBox;
    // innerBox - this box is for the usable area inside of the widget
    // it's bbox without the inner paddings
    fgBoundingBox3Df innerBox;
    // widgetBox - this is special area just for one widget
    // It describes constraints for a given widget
    // Calculate from: childSize + spacing
    // childSize needs to take into account margins
    fgBoundingBox3Df widgetBox;
    // Size of the smallest widget
    fgVector3f minWidgetSize(FG_GUI_FLOAT_UNIT_INVALID,
                             FG_GUI_FLOAT_UNIT_INVALID,
                             FG_GUI_FLOAT_UNIT_INVALID);
    // Size of the largest widget
    fgVector3f maxWidgetSize;
    // Size of all children inside of this container
    // Be aware that this differs completely depending
    // on the packing method (vertical/horizontal)
    fgVector3f childrenSize;
    // Spacing describes the space before and after the widget
    // Equation: (InnerContainerSize - ChildrenSize) / ( ChildrenCount * 2 )
    fgVector3f spacing;
    // Stepping describes the average area size for a single widget #FIXME
    // Equation: (InnerContainerSize / ChildrenCount)
    fgVector3f stepping;
    // Number of all children
    int nChildren = m_children.size();
    // Number of all static children - these widgets are processed 
    // in the gui container flow
    int nStaticChildren = nChildren;
    // Pointer to the last static positioned widget
    fgGuiWidget *lastWidget = NULL;

    // Calculate the current innerBox for comparison
    innerBox.pos.x = m_bbox.pos.x + containerPadding.left;
    innerBox.pos.y = m_bbox.pos.y + containerPadding.top;
    innerBox.size.x = m_bbox.size.x - containerPadding.right - containerPadding.left;
    innerBox.size.y = m_bbox.size.y - containerPadding.bottom - containerPadding.top;

    // Calculate currently covered area by all children widgets
    // Ignore non static widgets (positioning)
    // Also calculate the max/min widget size
    for(int i = 0; i < nChildren; i++) {
        fgGuiWidget *child = m_children[i];
        if(!child)
            continue;
        fgVector3f childSize;

        if(child->getStyleContent().getPosition().style != FG_GUI_POS_STATIC) {
            nStaticChildren--;
            // If child has different than static positioning, update its size
            // and position with the main (container) innerBox constraint
            // #FIXME - this should be done before, relatively/fixed positioned
            // child widget can update bounds of the parent container differently
            fgBoundingBox3Df childBox = child->updateBounds(innerBox);
            // Now if this widget is relatively position it can exceed the boundaries
            // of this container - so we need to merge this innerbox with childsbox
            //if(innerBox.pos.x > childBox.pos.x)
            //    innerBox.pos.x = childBox.pos.x;
            //if(innerBox.pos.y > childBox.pos.y)
            //    innerBox.pos.y = childBox.pos.y;
            innerBox.merge(childBox);
            continue;
        } else {
            childSize = child->getSize();
            childSize.x += child->getStyleContent().getMargin().right + child->getStyleContent().getMargin().left;
            childSize.y += child->getStyleContent().getMargin().bottom + child->getStyleContent().getMargin().top;
        }

        // Update max/min widget X size
        if(childSize.x > maxWidgetSize.x)
            maxWidgetSize.x = childSize.x;
        if(childSize.x < minWidgetSize.x)
            minWidgetSize.x = childSize.x;
        // Update max/min widget Y size
        if(childSize.y > maxWidgetSize.y)
            maxWidgetSize.y = childSize.y;
        if(childSize.y < minWidgetSize.y)
            minWidgetSize.y = childSize.y;
        // Update calculated size of all widgets
        // This depends on currently chosen pack method
        // For free pack method, container size will be
        // updated to the size of the largest child widget
        // Everything else will be the same
        if(m_packMethod == FG_GUI_CONTAINER_PACK_HORIZONTAL) {
            childrenSize.x += childSize.x;
            childrenSize.y = maxWidgetSize.y;
        } else if(m_packMethod == FG_GUI_CONTAINER_PACK_VERTICAL) {
            childrenSize.x = maxWidgetSize.x;
            childrenSize.y += childSize.y;
        } else {
            childrenSize.x = maxWidgetSize.x;
            childrenSize.y = maxWidgetSize.y;
        }
    }
    // Now childrenSize contains the real size of all widgets
    // it's calculated with all valid margins, this is also 
    // the minimal size required for the innerBox of the container

    // Check for the minimal required size and update inner/outer/bbox
    if(innerBox.size.x < childrenSize.x) {
        innerBox.size.x = childrenSize.x;
    }
    if(innerBox.size.y < childrenSize.y) {
        innerBox.size.y = childrenSize.y;
    }
    //m_bbox.pos.x = innerBox.pos.x - containerPadding.left;
    //m_bbox.pos.y = innerBox.pos.y - containerPadding.top;
    m_bbox.size.x = innerBox.size.x + containerPadding.right + containerPadding.left;
    m_bbox.size.y = innerBox.size.y + containerPadding.bottom + containerPadding.top;
    outerBox.size.x = m_bbox.size.x + containerMargin.right + containerMargin.left;
    outerBox.size.y = m_bbox.size.y + containerMargin.bottom + containerMargin.top;
    //outerBox.pos.x = m_bbox.pos.x - containerMargin.left;
    //outerBox.pos.y = m_bbox.pos.y - containerMargin.top;
    // Update widgetBox position
    widgetBox.pos = innerBox.pos; // #FIXME - is this really necessary? MAYBE
    // Calculate spacingXY
    // Equation: (InnerContainerSize - ChildrenSize) / ( ChildrenCount * 2 )
    spacing = (innerBox.size - childrenSize) / ((float)nStaticChildren * 2.0f);
    // Calculate steppingXY
    // Equation: (InnerContainerSize / ChildrenCount)
    stepping = (innerBox.size / (float)nStaticChildren);
    // Helper vector - size of the last widget
    fgVector3f lastChildSize;

    // Iterate through all children widgets updating their
    // size and position with special area constraint
    for(int i = 0, j = 0; i < nChildren; i++, j++) {
        fgGuiWidget *child = m_children[i];
        if(!child)
            continue;
        if(child->getStyleContent().getPosition().style != FG_GUI_POS_STATIC) {
            j--;
            continue;
        }

        // Valid size of the current widget
        fgVector3f childSize = child->getSize();
        childSize.x += child->getStyleContent().getMargin().right + child->getStyleContent().getMargin().left;
        childSize.y += child->getStyleContent().getMargin().bottom + child->getStyleContent().getMargin().top;
        if(!lastWidget) {
            lastWidget = child;
            lastChildSize = childSize;
        }

        if(m_packMethod == FG_GUI_CONTAINER_PACK_HORIZONTAL) {
            widgetBox.pos.x += (lastChildSize.x + spacing.x * 2.0f) * (!!j);
            widgetBox.pos.y = innerBox.pos.y;
            widgetBox.size.x = childSize.x + (spacing.x * 2.0f);
            widgetBox.size.y = innerBox.size.y;
        } else if(m_packMethod == FG_GUI_CONTAINER_PACK_VERTICAL) {
            widgetBox.pos.x = innerBox.pos.x;
            widgetBox.pos.y += (lastChildSize.y + spacing.y * 2.0f) * (!!j);
            widgetBox.size.x = innerBox.size.x;
            widgetBox.size.y = childSize.y + (spacing.y * 2.0f);
        }

        // No need to update inner/outer area, just update position of the child
        fgBoundingBox3Df childBox = child->updateBounds(widgetBox);

        {
            fgVec2f blockPos = fgVec2f(widgetBox.pos.x, widgetBox.pos.y);
            fgVec2f blockSize = fgVec2f(widgetBox.size.x, widgetBox.size.y);
            int color = 1;
            if(i % 2 == 0)
                color = 2;
            if(yolo) {
                yolo->downZIndex();
                yolo->appendBorder2D(blockPos, blockSize, m_styles[color]);
            }
            if(yolo) {
                char buf[256];
                snprintf(buf, 255, "%s", child->getNameStr());
                float tSize = m_styles[color].getForeground().textSize;
                fgColor4f tColor = m_styles[color].getForeground().color;
                std::string tFont = m_styles[color].getForeground().font;
                m_styles[color].getForeground().textSize = 18.0f;
                m_styles[color].getForeground().font = "StbConsolasBold";
                m_styles[color].getForeground().color = m_styles[color].getBorder().all.color; //fgColor4f(.8f, .8f, .8f, 1.0f);
                blockSize.y = 10.0f;
                blockSize.x *= 0.4f;
                yolo->appendText2D(m_textSize, blockPos, blockSize, m_styles[color], buf);
                m_styles[color].getForeground().textSize = tSize;
                m_styles[color].getForeground().font = tFont;
                m_styles[color].getForeground().color = tColor;
            }
        }
        // Update last pointer
        lastWidget = child;
        lastChildSize = childSize;
    }
    // m_bbox is already updated properly
    // outerBox is the value to return
    // outerBox has containers margins
    return outerBox;
}

/*
 *
 */
void fgGuiContainer::refresh(void) {
    fgGuiWidget::refresh();
    for(int i = 0; i < (int)m_children.size(); i++) {
        fgGuiWidget *child = m_children[i];

        if(!child)
            continue;
        child->refresh();
    }
}

/**
 * 
 * @param pointerData
 * @return 
 */
int fgGuiContainer::updateState(const fgPointerData *pointerData) {
    if(fgGuiWidget::updateState(pointerData) == FG_GUI_WIDGET_STATE_NONE);
    //return m_state;
    for(int i = 0; i < (int)m_children.size(); i++) {
        fgGuiWidget *child = m_children[i];

        if(!child)
            continue;
        child->updateState(pointerData);
    }
    return m_state;
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGuiWidget *fgGuiContainer::getChild(const std::string& nameTag) {
    if(nameTag.empty())
        return NULL;
    childrenMapItor itor = m_childrenMap.find(nameTag);

    if(itor == m_childrenMap.end())
        return NULL;
    fgGuiWidget * pWidget = itor->second;
    return pWidget;
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGuiWidget *fgGuiContainer::getChild(const char *nameTag) {

    return getChild(std::string(nameTag));
}

/**
 * 
 * @return 
 */
fgGuiContainer::childrenVec& fgGuiContainer::getChildren(void) {
    return m_children;
}

/**
 * 
 * @return 
 */
fgGuiContainer::childrenMap& fgGuiContainer::getChildrenMap(void) {
    return m_childrenMap;
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool fgGuiContainer::addChild(fgGuiWidget *pWidget) {
    if(m_children.find(pWidget) == -1) {
        m_childrenMap[pWidget->getName()] = pWidget;
        m_children.push_back(pWidget);
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool fgGuiContainer::removeChild(fgGuiWidget *pWidget) {

    if(!pWidget)
        return FG_FALSE;
    return removeChild(pWidget->getName());
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGuiContainer::removeChild(const std::string& nameTag) {
    if(nameTag.empty())
        return FG_FALSE;
    childrenMapItor itor = m_childrenMap.find(nameTag);
    if(itor == m_childrenMap.end())
        return FG_FALSE;
    fgGuiWidget * pWidget = itor->second;
    m_childrenMap.erase(itor);
    childrenVecItor vit = m_children.begin(), end = m_children.end();
    for(; vit != end; vit++) {
        if(*vit == pWidget) {

            m_children.erase(vit);
            return FG_TRUE;
            break;
        }
    }
    return FG_FALSE;
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGuiContainer::removeChild(const char *nameTag) {
    if(!nameTag)
        return FG_FALSE;
    if(!strlen(nameTag))
        return FG_FALSE;
    return removeChild(std::string(nameTag));
}
