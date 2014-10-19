/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiContainer.h"

/*
 *
 */
fgGuiContainer::fgGuiContainer() :
fgGuiWidget() {
    fgGuiContainer::setDefaults();
}

/*
 *
 */
fgGuiContainer::~fgGuiContainer() {
    m_children.clear_optimised();
    m_childrenMap.clear();
}

/*
 *
 */
void fgGuiContainer::setDefaults(void) {
    m_type = FG_GUI_CONTAINER;
    m_typeName = FG_GUI_CONTAINER_NAME;
    m_typeTraits = FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
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

/*
 *
 */
fgBoundingBox3Df& fgGuiContainer::updateSize(void) {
    if(m_children.empty()) {
        return fgGuiWidget::updateSize();
    }
    fgBoundingBox3Df area = m_bbox;
    fgBoundingBox3Df tmpArea = m_bbox;
    fgVector3f step = m_bbox.size / (float)m_children.size();
    for(int i = 0; i < (int)m_children.size(); i++) {
        fgGuiWidget *child = m_children[i];
        if(!child)
            continue;

        tmpArea.pos = m_bbox.pos;
        tmpArea.size = m_bbox.size;
        fgBoundingBox3Df positionAndSize = child->updateSize(tmpArea);

        area.merge(positionAndSize);
        area.merge(tmpArea);
        m_bbox = area;
#if 0
        Vector4 area = new Vector4();

        area = GameGUI.MergeVector2D(this.Position, this.Size);
        Vector4 positionAndSize = Vector4.Zero;

        int i = 0;

        Vector2 tmpPosition = new Vector2();
        Vector2 tmpSize = new Vector2();

        float stepX;
        float stepY;
        stepX = this.Size.X / childsPool.Count;
        stepY = this.Size.Y / childsPool.Count;

        foreach(Widget oneChild in childsPool) {
            // Ustawianie rozmiaru kontenera na podstawie rozmiaru
            // oraz ustawienia 'dzieci'
            if(this.PackMethod == "none") {
                tmpPosition.X = this.Position.X;
                tmpPosition.Y = this.Position.Y;
                tmpSize.X = this.Size.X;
                tmpSize.Y = this.Size.Y;
            } else if(this.PackMethod == "horizontal") {
                if(i > 0 && this.Position.X + stepX * i < positionAndSize.X + positionAndSize.Z)
                    tmpPosition.X = positionAndSize.X + positionAndSize.Z;
                else
                    tmpPosition.X = this.Position.X + stepX * i;

                tmpPosition.Y = this.Position.Y; //FIXME
                tmpSize.X = stepX;
                tmpSize.Y = this.Size.Y; //FIXME
            } else if(this.PackMethod == "vertical") {
                /*tmp_pos.X = this.pos.X;
                tmp_pos.Y = this.pos.Y + stepy * i; //FIXME
                tmp_size.X = this.size.X;
                tmp_size.Y = stepy;//FIXME*/

                if(i > 0 && this.Position.Y + stepY * i < positionAndSize.Y + positionAndSize.W)
                    tmpPosition.Y = positionAndSize.Y + positionAndSize.W;
                else
                    tmpPosition.Y = this.Position.Y + stepY * i;

                tmpPosition.X = this.Position.X; //FIXME                    
                tmpSize.X = this.Size.X;
                tmpSize.Y = stepY; //FIXME
            }

            positionAndSize = oneChild.UpdateSize(tmpPosition, tmpSize);

            Vector4 returnArea = GameGUI.MergeArea(area, positionAndSize);
            returnArea = GameGUI.MergeArea(returnArea, GameGUI.MergeVector2D(tmpPosition, tmpSize));

            area.X = returnArea.X;
            area.Y = returnArea.Y;
            area.Z = returnArea.Z;
            area.W = returnArea.W;

            //this.gui.primBatch.DrawBorder(new Vector2(ret_val.X, ret_val.Y), new Vector2(ret_val.Z, ret_val.W), Color.Red, 1); 
            /*  if (this.pos.X + this.size.X < positionAndSize.X + positionAndSize.Z)
                  this.size.X = positionAndSize.X + positionAndSize.Z - this.pos.X;
              if (this.pos.Y + this.size.Y < positionAndSize.Y + positionAndSize.W)
                  this.size.Y = positionAndSize.Y + positionAndSize.W - this.pos.Y;*/
            i++;
        }
        this.Position.X = area.X;
        this.Position.Y = area.Y;
        this.Size.X = area.Z;
        this.Size.Y = area.W;

        /*area.X = pos.X;
        area.Y = pos.Y;
        area.Z = size.X;
        area.W = size.Y;*/

        return area;
#endif 
    }

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

/*
 *
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

/*
 *
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

/*
 *
 */
fgGuiWidget *fgGuiContainer::getChild(const char *nameTag) {
    return getChild(std::string(nameTag));
}

/*
 *
 */
fgGuiContainer::childrenVec& fgGuiContainer::getChildren(void) {
    return m_children;
}

/*
 *
 */
fgGuiContainer::childrenMap& fgGuiContainer::getChildrenMap(void) {
    return m_childrenMap;
}

/*
 *
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

/*
 *
 */
fgBool fgGuiContainer::removeChild(fgGuiWidget *pWidget) {
    if(!pWidget)
        return FG_FALSE;
    return removeChild(pWidget->getName());
}

/*
 *
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

/*
 *
 */
fgBool fgGuiContainer::removeChild(const char *nameTag) {
    if(!nameTag)
        return FG_FALSE;
    if(!strlen(nameTag))
        return FG_FALSE;
    return removeChild(std::string(nameTag));
}
