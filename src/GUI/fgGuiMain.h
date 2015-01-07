/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_MAIN
    #define FG_INC_GUI_MAIN
    #define FG_INC_GUI_MAIN_BLOCK

    #if defined(FG_INC_SCRIPT_SUBSYSTEM_BLOCK)
        #error "FG_SCRIPT_SUBSYSTEMBLOCK is defined: Do not include GuiMain inside of ScriptSubsystem header"
    #endif

    #if defined(FG_INC_GUI_WIDGET_BLOCK)
        #error "FG_GUI_WIDGETBLOCK is defined: Do not include GuiMain inside of Widget header"
    #endif

    #include "fgManagerBase.h"

    #include "fgGuiBase.h"
    #include "fgGuiWidget.h"
    #include "fgGuiMenu.h"
    #include "fgGuiConsole.h"

    #include "fgGuiStyleManager.h"
    #include "fgGuiWidgetManager.h"
    #include "fgGuiWidgetFactory.h"

    #include "Event/fgEventManager.h"
    #include "Input/fgPointerInputReceiver.h"
    #ifndef FG_INC_RESOURCE_MANAGER
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
class fgGuiMain : public fg::base::CManager, public fgGuiBase {
private:
    typedef fgVector<fgGuiCallback *> guiCallbackVec;
    typedef guiCallbackVec::iterator guiCallbackVecItor;

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
    fg::base::CManager *m_pShaderMgr;
    /// Pointer to external input receiver - touch/mouse/keyboard
    fgPointerInputReceiver *m_pPointerInputReceiver;

    /// Special callback for receiving touch events
    fgFunctionCallback *m_guiTouchCallback;
    /// Special callback for receiving mouse events
    fgFunctionCallback *m_guiMouseCallback;
    /// Special callback for handling link events (menu navigation)
    fgGuiCallback *m_guiLinkCallback;

    /// Next menu link (can be null if no menu change is required)
    fgGuiMenu *m_changeToMenu;
    /// Currently displayed menu screen
    fgGuiMenu *m_currentMenu;
    /// Special console widget
    fgGuiConsole *m_console;
    /// Whether there is some kind of shifting / animation
    /// If so - no state updating will occur
    fgBool m_isMenuChanging;

    /// Special vector for holding gui callbacks
    /// It's used for easy free/deletion process
    guiCallbackVec m_guiCallbacks;

    /// Special bounding box describing current screen/window
    /// 3D float/double type box is used for compatibility 
    /// with widget functions
    fgBoundingBox3Df m_screenBox;

protected:
    /**
     * 
     */
    void registerGuiCallbacks(void);
    /**
     * 
     */
    void unregisterGuiCallbacks(void);
    /**
     * 
     * @param eventMgr
     * @param resourceMgr
     */
    virtual void clear(void);

public:
    /**
     * 
     * @param pEventMgr
     * @param pResourceMgr
     */
    fgGuiMain(const std::string& stylesPath,
              const std::string& widgetsPath,
              fgEventManager *pEventMgr = NULL,
              fgResourceManager *pResourceMgr = NULL);
    /**
     * 
     */
    virtual ~fgGuiMain();
    /**
     * 
     * @param w
     * @param h
     */
    void setScreenSize(const int w, const int h) {
        m_screenBox.size.x = (float)w;
        m_screenBox.size.y = (float)h;
    }

    /**
     * 
     * @return 
     */
    virtual fgBool destroy(void);
    /**
     * 
     * @return 
     */
    virtual fgBool initialize(void);

public:
    /**
     * 
     * @param pWidget
     * @param pCallback
     * @param callbackType
     * @return 
     */
    fgBool addWidgetCallback(fgGuiWidget *pWidget,
                             fgGuiCallback *pCallback,
                             const fgGuiWidgetCallbackType callbackType);

    /**
     * 
     * @param widgetName
     * @param pCallback
     * @param callbackType
     * @return 
     */
    fgBool addWidgetCallback(const char *widgetName,
                             fgGuiCallback *pCallback,
                             const fgGuiWidgetCallbackType callbackType);

    /**
     * 
     * @param widgetName
     * @param pCallback
     * @param callbackType
     * @return 
     */
    fgBool addWidgetCallback(const std::string& widgetName,
                             fgGuiCallback *pCallback,
                             const fgGuiWidgetCallbackType callbackType);

public:
    /**
     * 
     * @return 
     */
    fgGuiWidgetManager *getWidgetManager(void) const;
    /**
     * 
     * @return 
     */
    fgGuiWidgetFactory *getWidgetFactory(void) const;
    /**
     * 
     * @return 
     */
    fgGuiStyleManager *getStyleManager(void) const;
    /**
     * 
     * @return 
     */
    fgEventManager *getEventManager(void) const;
    /**
     * 
     * @return 
     */
    fgResourceManager *getResourceManager(void) const;
    /**
     * 
     * @return 
     */
    fg::base::CManager *getShaderManager(void) const;
    /**
     * 
     * @return 
     */
    fgPointerInputReceiver *getPointerInputReceiver(void) const;

    /**
     * 
     * @param pEventMgr
     */
    void setEventManager(fgEventManager *pEventMgr);
    /**
     * 
     * @param pResourceMgr
     */
    void setResourceManager(fgResourceManager *pResourceMgr);
    /**
     * 
     * @param pShaderMgr
     */
    void setShaderManager(fg::base::CManager *pShaderMgr);
    /**
     * 
     * @param pointerInputReceiver
     */
    void setPointerInputReceiver(fgPointerInputReceiver *pointerInputReceiver);

    /**
     * Update state of all widgets (called only when needed)
     */
    virtual void updateState(void);

    /**
     * This generates the buffers to draw
     */
    virtual void display(void);

    /**
     * This calls proper drawing functions. The screen will be updated
     */
    virtual void render(void); // #FIXME, just testing

    /**
     * 
     * @param argv
     * @return 
     */
    fgBool guiTouchHandler(fgArgumentList *argv);
    /**
     * 
     * @param argv
     * @return 
     */
    fgBool guiMouseHandler(fgArgumentList *argv);
    /**
     * 
     * @param pGuiMain
     * @param pWidget
     * @return 
     */
    fgBool guiLinkHandler(fgGuiMain *pGuiMain, fgGuiWidget *pWidget);
};

    #undef FG_INC_GUI_MAIN_BLOCK

#endif /* FG_INC_GUI_MAIN */
