/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_STYLE_MANAGER_H_
#define _FG_GUI_STYLE_MANAGER_H_

#include "Resource/fgDataManagerBase.h"
#include "fgGuiStyle.h"

#define FG_MANAGER_GUI_STYLE	0x00000040


/*
 *
 */
class fgGuiStyleManager : public fgDataManagerBase<fgGuiStyle*, fgGuiStyleHandle, fgGuiStyleTag>
{
protected:
	typedef hmDataVec		smStyleVec;
	typedef hmDataVecItor	smStyleVecItor;
public:
	//
	fgGuiStyleManager();
	//
	virtual ~fgGuiStyleManager();

protected:
	//
	virtual void clear(void);

public:
	//
	virtual fgBool destroy(void);
	//
	virtual fgBool initialize(void);

	//
	virtual fgBool insertStyle(fgGuiStyleHandle& shUniqueID, fgGuiStyle *pStyle);

	//
	virtual fgGuiStyle* request(const std::string& info);
	//
	virtual fgGuiStyle* request(const char *info);

	//
	void setStylesPath(const std::string &path);
	//
	void setStylesPath(const char *path);

private:
	std::string m_stylesPath;

};
#endif /* _FG_GUI_STYLE_MANAGER_H_ */
