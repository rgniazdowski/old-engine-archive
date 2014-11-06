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
    #define _FG_GUI_MAIN_H_BLOCK_

    #if defined(_FG_SCRIPT_SUBSYSTEM_H_BLOCK_)
        #error "FG_SCRIPT_SUBSYSTEM_H_BLOCK is defined: Do not include GuiMain inside of ScriptSubsystem header"
    #endif
    
    #if defined(_FG_GUI_WIDGET_H_BLOCK_)
        #error "FG_GUI_WIDGET_H_BLOCK is defined: Do not include GuiMain inside of Widget header"
    #endif

    #include "fgManagerBase.h"

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

//FG_EVENT_TOUCH_PRESSED	=	1,
//FG_EVENT_TOUCH_RELEASED	=	2,
//FG_EVENT_TOUCH_MOTION		=	3,
//FG_EVENT_TOUCH_TAP_FINISHED	=	4,

//FG_EVENT_MOUSE_PRESSED	=	5,
//FG_EVENT_MOUSE_RELEASED	=	6,
//FG_EVENT_MOUSE_MOTION		=	7,

    #define FG_MANAGER_GUI_MAIN     0x00000400

/**
 *
 */
class fgGuiMain : public fgManagerBase, public fgGuiBase {
private:
    /// GUI style manager - loads and manages styles
    fgGuiStyleManager *m_styleMgr;
    /// Widget manager - loads structure sheets, holds handles
    /// to widgets. Every widget can be referenced from handle
    /// or special name
    fgGuiWidgetManager *m_widgetMgr;
    /// Widget factory 
    fgGuiWidgetFactory *m_widgetFactory;
    /// Pointer to external event manager class
    fgEventManager *m_pEventMgr;
    /// Pointer to external resource manager
    fgResourceManager *m_pResourceMgr;
    /// GUI drawer special drawing batch
    fgGuiDrawer *m_guiDrawer;
    /// Pointer to external shader manager class
    fgManagerBase *m_pShaderMgr;
    /// Pointer to external input receiver - touch/mouse/keyboard
    fgPointerInputReceiver *m_pPointerInputReceiver;

    /// Special callback for receiving touch events
    fgFunctionCallback *m_guiTouchCallback;
    /// Special callback for receiving mouse events
    fgFunctionCallback *m_guiMouseCallback;
    
    /// Special bounding box describing current screen/window
    /// 3D float/double type box is used for compatibility 
    /// with widget functions
    fgBoundingBox3Df m_screenBox;

protected:
    // 
    void registerGuiCallbacks(void);
    //
    void unregisterGuiCallbacks(void);
    //
    virtual void clear(void);
    
public:
    //
    fgGuiMain(fgEventManager *eventMgr = NULL, fgResourceManager *resourceMgr = NULL);
    //
    virtual ~fgGuiMain();
    
    //
    void setScreenSize(const int w, const int h) {
        m_screenBox.size.x = (float)w;
        m_screenBox.size.y = (float)h;
    }
    
    //
    virtual fgBool destroy(void);
    //
    virtual fgBool initialize(void);

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
    void setEventManager(fgEventManager *pEventMgr);
    //
    void setResourceManager(fgResourceManager *pResourceMgr);
    //
    void setShaderManager(fgManagerBase *pShaderMgr);
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

    #undef _FG_GUI_MAIN_H_BLOCK_

#endif /* _FG_GUI_MAIN_H_ */
