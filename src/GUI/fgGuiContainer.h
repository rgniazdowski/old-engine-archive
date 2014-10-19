/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_CONTAINER_H_
    #define _FG_GUI_CONTAINER_H_

    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_CONTAINER		0x00000020
    #define FG_GUI_CONTAINER_NAME	"Container"

/* horizontal, vertical */
    #define FG_GUI_CONTAINER_PACK_METHOD
/* left, center, right, top, bottom | combined */
    #define FG_GUI_CONTAINER_PACK_ALIGN

enum fgGuiContainerPackMethod {
    FG_GUI_CONTAINER_PACK_HORIZONTAL,
    FG_GUI_CONTAINER_PACK_VERTICAL
};

enum fgGuiContainerPackAlign {
    FG_GUI_CONTAINER_PACK_ALIGN_NONE = 0,
    FG_GUI_CONTAINER_PACK_ALIGN_LEFT = 1 << 0,
    FG_GUI_CONTAINER_PACK_ALIGN_RIGHT = 1 << 1,
    FG_GUI_CONTAINER_PACK_ALIGN_TOP = 1 << 2,
    FG_GUI_CONTAINER_PACK_ALIGN_BOTTOM = 1 << 3,
    FG_GUI_CONTAINER_PACK_ALIGN_VCENTER = 1 << 4,
    FG_GUI_CONTAINER_PACK_ALIGN_HCENTER = 1 << 5,
    FG_GUI_CONTAINER_PACK_ALIGN_CENTER = FG_GUI_CONTAINER_PACK_ALIGN_HCENTER,
    FG_GUI_CONTAINER_PACK_ALIGN_MIDDLE = FG_GUI_CONTAINER_PACK_ALIGN_VCENTER + FG_GUI_CONTAINER_PACK_ALIGN_HCENTER
};
FG_ENUM_FLAGS(fgGuiContainerPackAlign);

    #include <map>

/*
 *
 */
class fgGuiContainer : public fgGuiWidget {
public:
    typedef std::map<std::string, fgGuiWidget*> childrenMap;
    typedef childrenMap::iterator childrenMapItor;

    typedef fgVector<fgGuiWidget *> childrenVec;
    typedef childrenVec::iterator childrenVecItor;
protected:
    /// 
    childrenMap m_childrenMap;
    childrenVec m_children;

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiContainer();
    // 
    virtual ~fgGuiContainer();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiContainer);

    //
    virtual void display(fgGfxLayer *guiLayer);

    // 
    virtual fgBoundingBox3Df& updateSize(void);
    // 
    virtual void refresh(void);

    // 
    virtual int updateState(const fgPointerData *pointerData);

    //
    fgGuiWidget *getChild(const std::string& nameTag);
    //
    fgGuiWidget *getChild(const char *nameTag);
    //
    childrenVec& getChildren(void);
    //
    childrenMap& getChildrenMap(void);
    //
    fgBool addChild(fgGuiWidget *pWidget);
    //
    fgBool removeChild(fgGuiWidget *pWidget);
    //
    fgBool removeChild(const std::string& nameTag);
    //
    fgBool removeChild(const char *nameTag);
};

#endif /* _FG_GUI_CONTAINER_H_ */
