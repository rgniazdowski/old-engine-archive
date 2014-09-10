/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_BUTTON_H_
#define _FG_GUI_BUTTON_H_

#include "fgGuiWidget.h"
#include "fgGuiLabel.h"

#define FG_GUI_BUTTON		2
#define FG_GUI_BUTTON_NAME	"Button"

/*
 *
 */
class fgGuiButton : public fgGuiWidget
{
private:
protected:
	/// 
	fgGuiLabel *m_label;

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiButton();
	// 
	virtual ~fgGuiButton();

	// 
	virtual fgVector4f updateSize(void);
	//
	virtual void refresh(void);
};

#endif /* _FG_GUI_BUTTON_H_ */ 
