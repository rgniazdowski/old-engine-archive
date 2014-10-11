/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_POPUP_H_
#define _FG_GUI_POPUP_H_

#include "fgGuiWindow.h"
#include "fgGuiWidgetFactoryTypes.h"

#define FG_GUI_POPUP		0x00020000
#define FG_GUI_POPUP_NAME	"Popup"

/*
 *
 */
class fgGuiPopup : public fgGuiWindow
{
private:
protected:

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiPopup();
	// 
	virtual ~fgGuiPopup();

	FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiPopup);
	
	// 
	virtual fgBoundingBox3Df& updateSize(void);
	// 
	virtual void refresh(void);

};

#endif /* _FG_GUI_POPUP_H_ */
