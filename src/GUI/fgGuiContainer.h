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

#define FG_GUI_CONTAINER		4
#define FG_GUI_CONTAINER_NAME	"Container"

/* horizontal, vertical */
#define FG_GUI_CONTAINER_PACK_METHOD
/* left, center, right, top, bottom | combined */
#define FG_GUI_CONTAINER_PACK_ALIGN

enum fgGuiContainerPackMethod
{
	FG_GUI_CONTAINER_PACK_HORIZONTAL,
	FG_GUI_CONTAINER_PACK_VERTICAL
};

enum fgGuiContainerPackAlign
{
	FG_GUI_CONTAINER_PACK_ALIGN_NONE	=	0,
	FG_GUI_CONTAINER_PACK_ALIGN_LEFT	=	1 << 0,
	FG_GUI_CONTAINER_PACK_ALIGN_RIGHT	=	1 << 1,
	FG_GUI_CONTAINER_PACK_ALIGN_TOP		=	1 << 2,
	FG_GUI_CONTAINER_PACK_ALIGN_BOTTOM	=	1 << 3,
	FG_GUI_CONTAINER_PACK_ALIGN_VCENTER	=	1 << 4,
	FG_GUI_CONTAINER_PACK_ALIGN_HCENTER	=	1 << 5,
	FG_GUI_CONTAINER_PACK_ALIGN_CENTER = FG_GUI_CONTAINER_PACK_ALIGN_HCENTER,
	FG_GUI_CONTAINER_PACK_ALIGN_MIDDLE = FG_GUI_CONTAINER_PACK_ALIGN_VCENTER + FG_GUI_CONTAINER_PACK_ALIGN_HCENTER
};
FG_ENUM_FLAGS(fgGuiContainerPackAlign);

#include <map>

/*
 *
 */
class fgGuiContainer : public fgGuiWidget
{
private:
protected:
	// 
	std::map<std::string, fgGuiWidget *> m_childrenMap;
	//
	fgVector<fgGuiWidget *> m_children;

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiContainer();
	// 
	virtual ~fgGuiContainer();

	// 
	virtual fgVector4f updateSize(void);
	// 
	virtual void refresh(void);

	// 
	virtual int updateState(void);
};

#endif /* _FG_GUI_CONTAINER_H_ */
