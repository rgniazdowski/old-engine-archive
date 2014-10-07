/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_MAIN_H_
#define _FG_GUI_MAIN_H_

#include "fgGuiBase.h"
#include "fgGuiWidget.h"
#include "fgGuiMenu.h"

#include "fgGuiStyleManager.h"
#include "fgGuiWidgetManager.h"
#include "fgGuiWidgetFactory.h"

#include "Event/fgEventManager.h"
#include "Input/fgPointerInputReceiver.h"
#ifndef _FG_RESOURCE_MANAGER_H_
#include "Resource/fgResourceManager.h"
#endif

#include "fgGuiDrawer.h"
#include "fgGuiCallback.h"

class fgGuiMain;

//FG_EVENT_TOUCH_PRESSED		=	1,
//FG_EVENT_TOUCH_RELEASED		=	2,
//FG_EVENT_TOUCH_MOTION		=	3,
//FG_EVENT_TOUCH_TAP_FINISHED	=	4,

//FG_EVENT_MOUSE_PRESSED		=	5,
//FG_EVENT_MOUSE_RELEASED		=	6,
//FG_EVENT_MOUSE_MOTION		=	7,

/*
 *
 */
class fgGuiMain : public fgGuiBase
{
private:
	///
	fgGuiStyleManager *m_styleMgr;
	///
	fgGuiWidgetManager *m_widgetMgr;
	///
	fgGuiWidgetFactory *m_widgetFactory;
	///
	fgEventManager *m_eventMgr;
	///
	fgResourceManager *m_resourceMgr;
	///
	fgGuiDrawer		*m_guiDrawer;
	///
	fgManagerBase *m_shaderMgr;
	///
	fgPointerInputReceiver *m_pointerInputReceiver;

	///
	fgFunctionCallback *m_guiTouchCallback;
	///
	fgFunctionCallback *m_guiMouseCallback;

protected:
	// 
	void registerGuiCallbacks(void);
	//
	void unregisterGuiCallbacks(void);

public:
	//
	fgGuiMain(fgEventManager *eventMgr = NULL, fgResourceManager *resourceMgr = NULL);
	//
	virtual ~fgGuiMain();

	//
	fgGuiWidgetManager *getWidgetManager(void) const;
	//
	fgGuiWidgetFactory *getWidgetFactory(void) const;
	//
	fgGuiStyleManager *getStyleManager(void) const;
	//
	fgEventManager *getEventManager(void) const;
	//
	fgResourceManager *getResourceManager(void) const;
	//
	fgManagerBase *getShaderManager(void) const;
	//
	fgPointerInputReceiver *getPointerInputReceiver(void) const;

	//
	void setEventManager(fgEventManager *eventMgr);
	//
	void setResourceManager(fgResourceManager *resourceMgr);
	//
	void setShaderManager(fgManagerBase *shaderMgr);
	//
	void setPointerInputReceiver(fgPointerInputReceiver *pointerInputReceiver);

	//
	virtual void updateState(void);

	// This generates the buffers to draw
	virtual void display(void);

	// This calls proper drawing functions. The screen will be updated
	virtual void render(void); // #FIXME, just testing

	//
	fgBool guiTouchHandler(fgArgumentList *argv);
	//
	fgBool guiMouseHandler(fgArgumentList *argv);
};

#endif /* _FG_GUI_MAIN_H_ */
