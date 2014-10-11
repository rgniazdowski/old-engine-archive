/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_WIDGET_MANAGER_H_
#define _FG_GUI_WIDGET_MANAGER_H_

#include "fgGuiWidget.h"
#include "Util/fgHandleManager.h"
#include "fgGuiWidgetFactory.h"

#ifndef _FG_GUI_STYLE_MANAGER_H_
#include "fgGuiStyleManager.h"
#endif

/* 
 *
 */
class fgGuiWidgetManager : protected fgHandleManager<fgGuiWidget *, fgGuiWidgetHandle>
{
public:
	typedef fgVector<fgGuiWidget *>		widgetVec;
	typedef widgetVec::iterator			widgetVecItor;

public:
	//
	fgGuiWidgetManager(fgGuiWidgetFactory *widgetFactory = NULL, fgGuiStyleManager *styleMgr = NULL);
	//
	virtual ~fgGuiWidgetManager();

	//
	static fgGuiWidgetType widgetTypeFromName(const char *typeName);
	//
	static fgGuiWidgetType widgetTypeFromName(const std::string& typeName);

	//
	void setWidgetFactory(fgGuiWidgetFactory *widgetFactory);
	//
	fgGuiWidgetFactory *getWidgetFactory(void) const;

	//
	void setStyleManager(fgGuiStyleManager *styleMgr);
	//
	fgGuiStyleManager *getStyleManager(void) const;

	//
	fgBool loadStructureSheet(const std::string& filePath);
	//
	fgBool loadStructureSheet(const char *filePath);

	// 
	virtual fgBool addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, fgGuiWidget *pFatherWidget);
	//
	virtual fgBool addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, const fgGuiWidgetHandle& wFatherUniqueID);
	//
	virtual fgBool addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, const std::string& wFatherNameTag);
	//
	virtual fgBool addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, const char* wFatherNameTag);

	// 
	virtual fgBool remove(fgGuiWidget *pWidget);
	// 
	virtual fgBool remove(const fgGuiWidgetHandle& wUniqueID);
	// 
	virtual fgBool remove(const std::string& nameTag);
	//
	virtual fgBool remove(const char *nameTag);

	// 
	virtual fgBool destroyWidget(fgGuiWidget*& pWidget);
	// 
	virtual fgBool destroyWidget(const fgGuiWidgetHandle& wUniqueID);
	// 
	virtual fgBool destroyWidget(const std::string& nameTag);
	// 
	virtual fgBool destroyWidget(const char *nameTag);

	// 
	virtual fgGuiWidget* get(const fgGuiWidgetHandle& wUniqueID);
	// 
	virtual fgGuiWidget* get(const std::string& nameTag);
	// 
	virtual fgGuiWidget* get(const char *nameTag);

	// 
	virtual fgBool isManaged(fgGuiWidget *pWidget);
	// 
	virtual fgBool isManaged(const fgGuiWidgetHandle& wUniqueID);
	// 
	virtual fgBool isManaged(const std::string& nameTag);
	// 
	virtual fgBool isManaged(const char *nameTag);

	//
	widgetVec& getRefRootWidgets(void);

private:
	/// Pointer to the external widget factory
	fgGuiWidgetFactory *m_widgetFactory;
	/// Pointer to the external style manager
	fgGuiStyleManager *m_styleMgr;
	/// Widgets that have no fathers. For example a main screen, window, menu, etc
	widgetVec		m_rootWidgets;
};

#endif /* _FG_GUI_WIDGET_MANAGER_H_ */
