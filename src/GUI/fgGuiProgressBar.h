/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_PROGRESS_BAR_H_
#define _FG_GUI_PROGRESS_BAR_H_

#include "fgGuiWidget.h"
#include "fgGuiWidgetFactoryTypes.h"

#define FG_GUI_PROGRESS_BAR			0x00040000
#define FG_GUI_PROGRESS_BAR_NAME	"ProgressBar"

/*
 *
 */
class fgGuiProgressBar : public fgGuiWidget
{
private:
protected:

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiProgressBar();
	// 
	virtual ~fgGuiProgressBar();

	FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiProgressBar);
	
	// 
	virtual fgBoundingBox3Df& updateSize(void);
	// 
	virtual void refresh(void);

};

#endif /* _FG_GUI_PROGRESS_BAR_H_ */
