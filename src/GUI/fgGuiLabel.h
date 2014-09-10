/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_LABEL_H_
#define _FG_GUI_LABEL_H_

#include "fgGuiWidget.h"

#define FG_GUI_LABEL		5
#define FG_GUI_LABEL_NAME	"Label"

/*
 *
 */
class fgGuiLabel : public fgGuiWidget
{
private:
protected:
	/// 
	std::string m_text;

protected:
	// 
	virtual void setDefaults(void);

public:
	// 
	fgGuiLabel();
	// 
	virtual ~fgGuiLabel();

	// 
	virtual fgVector4f updateSize(void);
};

#endif /* _FG_GUI_LABEL_H_ */
