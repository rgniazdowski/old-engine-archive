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
        } else if(flagsVec[i].compare("packhorizontal") == 0) {
            m_packMethod = FG_GUI_CONTAINER_PACK_HORIZONTAL;
        } else if(flagsVec[i].compare("packvertical") == 0) {
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
}

/**
 * 
 * @return 
 */
fgBoundingBox3Df& fgGuiContainer::updateSize(void) {
    if(m_children.empty()) {
        return fgGuiWidget::updateSize();
    }
    fgBoundingBox3Df area = m_bbox;
    fgBoundingBox3Df tmpArea = m_bbox;
    fgBoundingBox3Df positionAndSize;
    positionAndSize.zero();
    int nChildren = m_children.size();
    int nStaticChildren = nChildren;
    for(int i = 0; i < nStaticChildren; i++) {
        if(m_children[i]->getStyleContent().getPosition().style != FG_GUI_POS_STATIC) {
            nStaticChildren--;
        }
    }
    fgVector3f step = m_bbox.size / (float)nStaticChildren;

    for(int i = 0, j = 0; i < nChildren; i++, j++) {
        fgGuiWidget *child = m_children[i];
        if(!child)
            continue;
        fgBool skip = FG_FALSE;
        if(child->getStyleContent().getPosition().style != FG_GUI_POS_STATIC) {
            j--;
            skip = FG_TRUE;
        }
        //tmpArea.pos = m_bbox.pos;
        //tmpArea.size = m_bbox.size;
        if(this->m_packMethod == FG_GUI_CONTAINER_PACK_HORIZONTAL && !skip) {
            if(j > 0 && this->m_bbox.pos.x + step.x * j < positionAndSize.pos.x + positionAndSize.size.x)
                tmpArea.pos.x = positionAndSize.pos.x + positionAndSize.size.x;
            else
                tmpArea.pos.x = this->m_bbox.pos.x + step.x * j;

            tmpArea.pos.y = this->m_bbox.pos.y; //FIXME
            tmpArea.size.x = step.x;
            tmpArea.size.y = this->m_bbox.size.y; //FIXME
        } else if(this->m_packMethod == FG_GUI_CONTAINER_PACK_VERTICAL && !skip) {
            if(j > 0 && this->m_bbox.pos.y + step.y * j < positionAndSize.pos.y + positionAndSize.size.y)
                tmpArea.pos.y = positionAndSize.pos.y + positionAndSize.size.y;
            else
                tmpArea.pos.y = this->m_bbox.pos.y + step.y * j;

            tmpArea.pos.x = this->m_bbox.pos.x; //FIXME                    
            tmpArea.size.x = this->m_bbox.size.x;
            tmpArea.size.y = step.y; //FIXME
        } else {
            // #FIXME !
            tmpArea.pos = m_bbox.pos;
            tmpArea.size = m_bbox.size;
        }
        positionAndSize = child->updateSize(tmpArea);

        area.merge(positionAndSize);
        area.merge(tmpArea);

#if 0
        positionAndSize = oneChild.UpdateSize(tmpPosition, tmpSize);
        Vector4 returnArea = GameGUI.MergeArea(area, positionAndSize);
        returnArea = GameGUI.MergeArea(returnArea, GameGUI.MergeVector2D(tmpPosition, tmpSize));

        area.X = returnArea.X; area.Y = returnArea.Y; 
        area.Z = returnArea.Z; area.W = returnArea.W;
        /*  if (this.pos.X + this.size.X < positionAndSize.X + positionAndSize.Z)
              this.size.X = positionAndSize.X + positionAndSize.Z - this.pos.X;
          if (this.pos.Y + this.size.Y < positionAndSize.Y + positionAndSize.W)
              this.size.Y = positionAndSize.Y + positionAndSize.W - this.pos.Y;*/
        this.Position.X = area.X;
        this.Position.Y = area.Y;
        this.Size.X = area.Z;
        this.Size.Y = area.W;
#endif 
    }
    m_bbox = area;
    return m_bbox;
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
    fgGuiWidget *pWidget = itor->second;
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
    fgGuiWidget *pWidget = itor->second;
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
