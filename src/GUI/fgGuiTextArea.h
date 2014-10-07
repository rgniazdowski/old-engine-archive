/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_TEXT_AREA_H_
#define _FG_GUI_TEXT_AREA_H_

#include "fgGuiScrollArea.h"
#include "fgGuiWidgetFactoryTypes.h"

#define FG_GUI_TEXT_AREA		0x00000400
#define FG_GUI_TEXT_AREA_NAME	"TextArea"

class fgGuiTextArea : public fgGuiScrollArea
{
private:
protected:

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiTextArea();
	// 
	virtual ~fgGuiTextArea();
	
	FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiTextArea);

	// 
	virtual fgBoundingBox3Df& updateSize(void);
	// 
	virtual void refresh(void);

};

#endif /* _FG_GUI_TEXT_AREA_H_ */
