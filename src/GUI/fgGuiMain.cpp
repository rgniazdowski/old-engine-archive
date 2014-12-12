/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "GFX/fgGFXPrimitives.h"
#include "GFX/Shaders/fgGFXShaderManager.h"
#include "fgLog.h"
#include "fgGuiMain.h"

#include "fgGuiWidget.h"
#include "fgGuiLabel.h"
#include "fgGuiButton.h"
#include "fgGuiToggleButton.h"
#include "fgGuiContainer.h"
#include "fgGuiMenu.h"
#include "fgGuiFrame.h"
#include "fgGuiScrollArea.h"
#include "fgGuiTextArea.h"
#include "fgGuiEditableText.h"
#include "fgGuiConsole.h"
#include "fgGuiWindow.h"
#include "fgGuiMessageBox.h"
#include "fgGuiPopup.h"
#include "fgGuiProgressBar.h"
#include "fgGuiTable.h"
#include "fgGuiLoader.h"
#include "fgGuiSlider.h"

#include "GUI/Font/fgFontStbConsolasBold.h"
#include "GUI/Font/fgFontStbCourier.h"
#include "GUI/Font/fgFontStbCourierBold.h"
#include "GUI/Font/fgFontStbTimes.h"
#include "GUI/Font/fgFontStbArial.h"
#include "GUI/Font/fgFontStbArialBold.h"
#include "GUI/Font/fgFontBuiltIn.h"

#include "fgColors.h"

#include "fgDebugConfig.h"

/*
 *
 */
fgGuiMain::fgGuiMain(fgEventManager *eventMgr, fgResourceManager *resourceMgr) :
m_styleMgr(NULL),
m_widgetMgr(NULL),
m_widgetFactory(NULL),
m_pEventMgr(eventMgr),
m_pResourceMgr(resourceMgr),
m_guiDrawer(NULL),
m_pShaderMgr(NULL),
m_pPointerInputReceiver(NULL),
m_guiTouchCallback(NULL),
m_guiMouseCallback(NULL),
m_guiLinkCallback(NULL),
m_changeToMenu(NULL),
m_currentMenu(NULL),
m_console(NULL),
m_isMenuChanging(FG_FALSE),
m_guiCallbacks(),
m_screenBox() {
    m_widgetFactory = new fgGuiWidgetFactory();
    m_styleMgr = new fgGuiStyleManager();
    m_widgetMgr = new fgGuiWidgetManager(m_widgetFactory, m_styleMgr);
    m_guiDrawer = new fgGuiDrawer();
    m_guiDrawer->setResourceManager(resourceMgr);

    if(m_pEventMgr)
        registerGuiCallbacks();

    // #FIXME
    m_styleMgr->setStylesPath("gui");
    m_widgetMgr->setWidgetsPath("gui");

    m_guiCallbacks.reserve(8);

    m_managerType = FG_MANAGER_GUI_MAIN;

    m_guiLinkCallback = new fgGuiClassCallback<fgGuiMain>(this, this, &fgGuiMain::guiLinkHandler);

    m_console = new fgGuiConsole();
    m_console->setVisible(FG_FALSE); // #FIXME :o
}

/*
 *
 */
fgGuiMain::~fgGuiMain() {
    fgGuiMain::destroy();
}

/**
 * 
 */
void fgGuiMain::clear(void) {
    m_managerType = FG_MANAGER_GUI_MAIN;

}

/**
 * 
 */
fgBool fgGuiMain::destroy(void) {
    unregisterGuiCallbacks();

    if(m_console)
        delete m_console;
    m_console = NULL;

    int n = m_guiCallbacks.size();
    for(int i = 0; i < n; i++) {
        if(m_guiCallbacks[i]) {
            delete m_guiCallbacks[i];
            m_guiCallbacks[i] = NULL;
        }
    }
    m_guiCallbacks.clear_optimised();

    if(m_widgetMgr)
        delete m_widgetMgr;
    m_widgetMgr = NULL;

    if(m_widgetFactory)
        delete m_widgetFactory;
    m_widgetFactory = NULL;

    if(m_styleMgr)
        delete m_styleMgr;
    m_styleMgr = NULL;

    if(m_guiDrawer)
        delete m_guiDrawer;
    m_guiDrawer = NULL;

    if(m_guiMouseCallback)
        delete m_guiMouseCallback;
    m_guiMouseCallback = NULL;

    if(m_guiTouchCallback)
        delete m_guiTouchCallback;
    m_guiTouchCallback = NULL;

    if(m_guiLinkCallback)
        delete m_guiLinkCallback;
    m_guiLinkCallback = NULL;

    m_pPointerInputReceiver = NULL;
    m_pShaderMgr = NULL;
    m_pEventMgr = NULL;
    m_pResourceMgr = NULL;
    m_managerType = FG_MANAGER_GUI_MAIN;

    return FG_TRUE;
}

/**
 * 
 */
fgBool fgGuiMain::initialize(void) {
    if(m_init)
        return FG_TRUE;
    if(!m_pEventMgr || !m_pResourceMgr || !m_pShaderMgr || !m_pPointerInputReceiver) {
        FG_LOG::PrintError("GUI: Initialization of main GUI module failed - not all external pointers are set");
        m_init = FG_FALSE;
        return FG_FALSE;
    }
    //m_widgetFactory->registerWidget(FG_GUI_WIDGET,		&fgGuiWidget::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_LABEL, &fgGuiLabel::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_BUTTON, &fgGuiButton::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_TOGGLE_BUTTON, &fgGuiToggleButton::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_CONTAINER, &fgGuiContainer::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_MENU, &fgGuiMenu::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_FRAME, &fgGuiFrame::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_SCROLL_AREA, &fgGuiScrollArea::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_TEXT_AREA, &fgGuiTextArea::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_EDITABLE_TEXT, &fgGuiEditableText::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_CONSOLE, &fgGuiConsole::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_WINDOW, &fgGuiWindow::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_MESSAGE_BOX, &fgGuiMessageBox::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_POPUP, &fgGuiPopup::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_PROGRESS_BAR, &fgGuiProgressBar::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_TABLE, &fgGuiTable::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_LOADER, &fgGuiLoader::createWidget);
    m_widgetFactory->registerWidget(FG_GUI_SLIDER, &fgGuiSlider::createWidget);

    FG_LOG_DEBUG("GUI: Initializing builtin fonts...");
    fgFontBuiltInResource *consolasBold = new fgFontBuiltInResource(fgFontBuiltIn::StbConsolasBold::getRawData(32));
    consolasBold->setName("StbConsolasBold");
    m_pResourceMgr->insertResource(consolasBold);
    // This will automatically create the resource and also throw event for GFX upload
    m_pResourceMgr->get(consolasBold->getRefHandle());

    fgFontBuiltInResource *courier = new fgFontBuiltInResource(fgFontBuiltIn::StbCourier::getRawData(50));
    courier->setName("StbCourier");
    m_pResourceMgr->insertResource(courier);
    m_pResourceMgr->get(courier->getRefHandle());

    //
    if(!m_styleMgr->initialize()) {
        FG_LOG::PrintError("GUI: Style manager not initialized");
    }
    m_widgetMgr->setLinkHandler(m_guiLinkCallback);
    //
    if(!m_widgetMgr->initialize()) {
        FG_LOG::PrintError("GUI: Widget manager not initialized");
    }

    // Initializing console style
    if(m_styleMgr && m_console) {
        std::string styleName = m_console->getStyleName();
        fgGuiStyle *style = m_styleMgr->get(styleName);
        if(style) {
            FG_LOG_DEBUG("WidgetManager: Copying style to widget: '%s' of type: '%s'",
                         m_console->getNameStr(),
                         m_console->getTypeNameStr());

            style->copyFullContent(m_console->getStyleContents(),
                                   FG_GUI_WIDGET_STATE_COUNT,
                                   m_console->getTypeName());
            m_console->refresh();
            m_console->updateBounds();
        }
    }

    m_init = FG_TRUE;
    m_managerType = FG_MANAGER_GUI_MAIN;
    updateState();
    return FG_TRUE;
}

/*
 *
 */
void fgGuiMain::registerGuiCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_guiTouchCallback)
        m_guiTouchCallback = new fgClassCallback<fgGuiMain>(this, &fgGuiMain::guiTouchHandler);

    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_PRESSED, m_guiTouchCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_RELEASED, m_guiTouchCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_MOTION, m_guiTouchCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_guiTouchCallback);

    if(!m_guiMouseCallback)
        m_guiMouseCallback = new fgClassCallback<fgGuiMain>(this, &fgGuiMain::guiMouseHandler);

    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_PRESSED, m_guiMouseCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_RELEASED, m_guiMouseCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_MOTION, m_guiMouseCallback);
}

/*
 *
 */
void fgGuiMain::unregisterGuiCallbacks(void) {
    if(!m_pEventMgr)
        return;

    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_PRESSED, m_guiTouchCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_RELEASED, m_guiTouchCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_MOTION, m_guiTouchCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_guiTouchCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_PRESSED, m_guiMouseCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_RELEASED, m_guiMouseCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_MOTION, m_guiMouseCallback);
}

/**
 * 
 * @param pWidget
 * @param pCallback
 * @param callbackType
 * @return 
 */
fgBool fgGuiMain::addWidgetCallback(fgGuiWidget *pWidget,
                                    fgGuiCallback *pCallback,
                                    const fgGuiWidgetCallbackType callbackType) {
    if(!pWidget || !pCallback || !callbackType)
        return FG_FALSE;
    if(!pWidget->isManaged())
        return FG_FALSE;
    if(!m_widgetMgr->isManaged(pWidget))
        return FG_FALSE;

    switch(callbackType) {
        case FG_GUI_WIDGET_CALLBACK_ON_FOCUS:
            pWidget->setOnFocusCallback(pCallback);
            break;
            /// Callback to call when the focus is lost
        case FG_GUI_WIDGET_CALLBACK_ON_FOCUS_LOST:
            pWidget->setOnFocusLostCallback(pCallback);
            break;
            /// Callback to call when widgets state changes to 'pressed'
        case FG_GUI_WIDGET_CALLBACK_ON_CLICK:
            pWidget->setOnClickCallback(pCallback);
            break;
            /// Callback to call on widgets activation
        case FG_GUI_WIDGET_CALLBACK_ON_ACTIVATE:
            pWidget->setOnActivateCallback(pCallback);
            break;
            /// Callback to call when widget is deactivated (once)
        case FG_GUI_WIDGET_CALLBACK_ON_DEACTIVATE:
            pWidget->setOnDeactivateCallback(pCallback);
            break;
            /// Callback for handling any keyboard related events
        case FG_GUI_WIDGET_CALLBACK_ON_KEY:
            pWidget->setOnMouseCallback(pCallback);
            break;
            /// Callback for handling any mouse specific events 
            /// - mouse motion, press and hold, swipe, etc
        case FG_GUI_WIDGET_CALLBACK_ON_MOUSE:
            pWidget->setOnMouseCallback(pCallback);
            break;
            /// This callback will be called anytime the widgets 
            /// state has changed (there are 5 states defined currently)
        case FG_GUI_WIDGET_CALLBACK_ON_CHANGE_STATE:
            pWidget->setOnChangeStateCallback(pCallback);
            break;
        default:
            FG_LOG_DEBUG("GUI: Invalid callback type");
            return FG_FALSE;
            break;
    };

    if(m_guiCallbacks.find(pCallback) < 0) {
        m_guiCallbacks.push_back(pCallback);
    }
    return FG_TRUE;
}

/**
 * 
 * @param widgetName
 * @param pCallback
 * @param callbackType
 * @return 
 */
fgBool fgGuiMain::addWidgetCallback(const char *widgetName,
                                    fgGuiCallback *pCallback,
                                    const fgGuiWidgetCallbackType callbackType) {
    if(!widgetName || !pCallback || !callbackType)
        return FG_FALSE;
    if(!*widgetName)
        return FG_FALSE;
    return addWidgetCallback(m_widgetMgr->get(widgetName), pCallback, callbackType);
}

/**
 * 
 * @param widgetName
 * @param pCallback
 * @param callbackType
 * @return 
 */
fgBool fgGuiMain::addWidgetCallback(const std::string& widgetName,
                                    fgGuiCallback *pCallback,
                                    const fgGuiWidgetCallbackType callbackType) {
    if(!pCallback || !callbackType || widgetName.empty())
        return FG_FALSE;
    return addWidgetCallback(m_widgetMgr->get(widgetName), pCallback, callbackType);
}

extern float guiScale;

/**
 * 
 */
void fgGuiMain::updateState(void) {
    if(!m_widgetMgr || !m_pResourceMgr || !m_pPointerInputReceiver)
        return;
    if(m_isMenuChanging)
        return;
    if(!m_currentMenu) {
        // #FIXME - this needs to look a little bit differently
        fgGuiWidgetManager::widgetVec & roots = m_widgetMgr->getRefRootWidgets();
        if(roots.empty())
            return;
        fgGuiWidget *mainMenu = m_widgetMgr->get("MainMenu");
        if(!mainMenu)
            return;
        if(!(mainMenu->getTypeTraits() & FG_GUI_MENU))
            return;
        m_currentMenu = static_cast<fgGuiMenu *>(mainMenu);
    }
    fgPointerData *pt = m_pPointerInputReceiver->getPointerData();
    if(pt) {
        pt->m_x = (int)((float)pt->m_x * ((1.0f - guiScale) / guiScale + 1.0f));
        pt->m_y = (int)((float)pt->m_y * ((1.0f - guiScale) / guiScale + 1.0f));
    }
    m_currentMenu->updateState(pt);

    if(m_console) {
        if(m_console->isVisible()) {
            m_console->updateState(pt);
        }
    }
}

/*
 *
 */
void fgGuiMain::display(void) {
    if(!m_widgetMgr || !m_pResourceMgr)
        return;
    if(!m_currentMenu)
        return;
    //    fgGuiWidgetManager::widgetVec & roots = m_widgetMgr->getRefRootWidgets();
    //    if(roots.empty())
    //        return;
    //    fgGuiWidget *mainMenu = m_widgetMgr->get("MainMenu");
    //    if(!mainMenu)
    //        return;
    //    if(!(mainMenu->getTypeTraits() & FG_GUI_CONTAINER))
    //        return;
    if(!(m_currentMenu->getTypeTraits() & FG_GUI_CONTAINER))
        return;

    static float r = 0.0f;
    r += 0.0125f;
    if(r >= M_PI2XF) {
        r = 0.0f;
    }
    float toggle = 0.0f;
    m_currentMenu->getStyleContent().getPadding().right = 25 + 25 * fabs(sinf(r)) * toggle;
    m_currentMenu->getStyleContent().getPadding().top = 25 + 25 * fabs(sinf(r)) * toggle;
    m_currentMenu->getStyleContent().getPadding().left = 25 + 25 * fabs(sinf(r)) * toggle;
    m_currentMenu->getStyleContent().getPadding().bottom = 25 + 25 * fabs(sinf(r)) * toggle;
    //mainMenu->getRelativePos().y = 150.0f * sinf(r);
    m_currentMenu->updateBounds(m_screenBox);
    m_currentMenu->display(m_guiDrawer);

    fgGuiWidget *contextMenu = m_widgetMgr->get("ContextMenu");
    if(contextMenu) {
        if(contextMenu->isVisible()) {
            contextMenu->updateBounds(m_screenBox);
            contextMenu->display(m_guiDrawer);
        }
    }
#if defined(FG_USING_SDL2)
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    static int tylda = 0;
    if(state[SDL_SCANCODE_GRAVE] == SDL_PRESSED && !tylda) {
        tylda++;

        m_console->setVisible(!m_console->isVisible());
        g_fgDebugConfig.consoleShow = (bool)m_console->isVisible();
    } else if(state[SDL_SCANCODE_GRAVE] == SDL_RELEASED) {
        tylda = 0;
    }
#endif
    if(m_console) {
        int numMessages = FG_MessageSubsystem->getStatusVec().size();
        int consoleSize = m_console->getNumConsoleRecords();
        if(consoleSize < numMessages) {
            m_console->updateFromStatusVec(FG_MessageSubsystem->getStatusVec());
        }
        if(m_console->isVisible()) {
            m_console->updateBounds(m_screenBox);
            m_console->display(m_guiDrawer);
        }
    }
#endif /* FG_USING_SDL2 */
    m_widgetMgr->get("StartGameButton")->getRelativePos().x = posx;
    m_widgetMgr->get("StartGameButton")->getRelativePos().y = posy;
}

/*
 *
 */
void fgGuiMain::render(void) {
    m_guiDrawer->render();
    m_guiDrawer->flush();
}

/**
 * 
 * @return 
 */
fgGuiWidgetManager *fgGuiMain::getWidgetManager(void) const {
    return m_widgetMgr;
}

/**
 * 
 * @return 
 */
fgGuiWidgetFactory *fgGuiMain::getWidgetFactory(void) const {
    return m_widgetFactory;
}

/**
 * 
 * @return 
 */
fgGuiStyleManager *fgGuiMain::getStyleManager(void) const {
    return m_styleMgr;
}

/**
 * 
 * @return 
 */
fgEventManager *fgGuiMain::getEventManager(void) const {
    return m_pEventMgr;
}

/**
 * 
 * @return 
 */
fgResourceManager *fgGuiMain::getResourceManager(void) const {
    return m_pResourceMgr;
}

/**
 * 
 * @return 
 */
fg::base::Manager *fgGuiMain::getShaderManager(void) const {
    return m_pShaderMgr;
}

/*
 *
 */
fgPointerInputReceiver *fgGuiMain::getPointerInputReceiver(void) const {
    return m_pPointerInputReceiver;
}

/**
 * 
 * @param pEventMgr
 */
void fgGuiMain::setEventManager(fgEventManager * pEventMgr) {
    if(!pEventMgr) {
        unregisterGuiCallbacks();
    } else if(m_pEventMgr && m_pEventMgr != pEventMgr) {
        unregisterGuiCallbacks();
    }
    m_pEventMgr = pEventMgr;
    if(m_pEventMgr)
        registerGuiCallbacks();
}

/**
 * 
 * @param pResourceMgr
 */
void fgGuiMain::setResourceManager(fgResourceManager * pResourceMgr) {
    m_pResourceMgr = pResourceMgr;
    if(m_guiDrawer)
        m_guiDrawer->setResourceManager(pResourceMgr);
}

/**
 * 
 * @param pShaderMgr
 */
void fgGuiMain::setShaderManager(fg::base::Manager * pShaderMgr) {
    if(pShaderMgr) {
        if(pShaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
            return;
    }
    m_pShaderMgr = pShaderMgr;
    if(m_guiDrawer)
        m_guiDrawer->setShaderManager(m_pShaderMgr);
}

/**
 * 
 * @param pointerInputReceiver
 */
void fgGuiMain::setPointerInputReceiver(fgPointerInputReceiver * pointerInputReceiver) {
    m_pPointerInputReceiver = pointerInputReceiver;
}

/**
 * 
 * @param argv
 * @return 
 */
fgBool fgGuiMain::guiTouchHandler(fgArgumentList * argv) {
    if(!argv)
        return FG_FALSE;
    fgEventBase *event = (fgEventBase *)argv->getArgumentValueByID(0);
    if(!event)
        return FG_FALSE;
    //fgEventType type = event->eventType;
    //fgTouchEvent *touchEvent = (fgTouchEvent *)event;
    this->updateState();
    return FG_TRUE;
}

/*
 *
 */
fgBool fgGuiMain::guiMouseHandler(fgArgumentList *argv) {
    if(!argv)
        return FG_FALSE;
    fgEventBase *event = (fgEventBase *)argv->getArgumentValueByID(0);
    if(!event)
        return FG_FALSE;
    //fgEventType type = event->eventType;
    //fgMouseEvent *mouseEvent = (fgMouseEvent *)event;
    this->updateState();
    return FG_TRUE;
}

/**
 * 
 * @param pGuiMain
 * @param pWidget
 * @return 
 */
fgBool fgGuiMain::guiLinkHandler(fgGuiMain* pGuiMain, fgGuiWidget * pWidget) {
    if(!pGuiMain || !pWidget || !m_widgetMgr)
        return FG_FALSE;
    if(pWidget->getLink().length()) {
        fgGuiWidget *goToWidget = m_widgetMgr->get(pWidget->getLink());
        if(!goToWidget)
            return FG_FALSE;
        if(goToWidget->getTypeTraits() & FG_GUI_MENU) {
            // NOT YET - need animation ?
            //m_changeToMenu = static_cast<fgGuiMenu *>(goToWidget);
            m_currentMenu = static_cast<fgGuiMenu *>(goToWidget);
            m_isMenuChanging = FG_FALSE; // #FIXME
            return FG_TRUE;
        } else {
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}
