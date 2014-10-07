/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_TOGGLE_BUTTON_H_
#define _FG_GUI_TOGGLE_BUTTON_H_

#include "fgGuiButton.h"
#include "fgGuiWidgetFactoryTypes.h"

#define FG_GUI_TOGGLE_BUTTON		0x00000008
#define FG_GUI_TOGGLE_BUTTON_NAME	"ToggleButton"

/*
 *
 */
class fgGuiToggleButton : public fgGuiButton
{
private:
protected:

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiToggleButton();
	// 
	virtual ~fgGuiToggleButton();

	FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiToggleButton);

	// 
	virtual fgBoundingBox3Df& updateSize(void);
	// 
	virtual void refresh(void);

};

#endif /* _FG_GUI_TOGGLE_BUTTON_H_ */
