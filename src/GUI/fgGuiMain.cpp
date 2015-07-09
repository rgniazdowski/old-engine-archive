/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGuiMain.h"
#include "fgDebugConfig.h"

#include "Resource/fgResourceManager.h"

#include "GFX/fgGfxPrimitives.h"
#include "GFX/Shaders/fgGfxShaderManager.h"

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

#include "GUI/Font/fgFontStbConsolas.h"
#include "GUI/Font/fgFontStbConsolasBold.h"
#include "GUI/Font/fgFontStbCourier.h"
#include "GUI/Font/fgFontStbCourierBold.h"
#include "GUI/Font/fgFontStbTimes.h"
#include "GUI/Font/fgFontStbTimesBold.h"
#include "GUI/Font/fgFontStbArial.h"
#include "GUI/Font/fgFontStbArialBold.h"
#include "GUI/Font/fgFontBuiltIn.h"

#include "fgColors.h"
#include "fgLog.h"

using namespace fg;

//------------------------------------------------------------------------------

gui::CGuiMain::CGuiMain(const std::string& stylesPath,
                        const std::string& widgetsPath,
                        event::CEventManager *eventMgr,
                        resource::CResourceManager *resourceMgr) :
m_styleMgr(NULL),
m_widgetMgr(NULL),
m_widgetFactory(NULL),
m_pEventMgr(eventMgr),
m_pResourceMgr(resourceMgr),
m_guiDrawer(NULL),
m_pShaderMgr(NULL),
m_pInputHandler(NULL),
m_guiTouchCallback(NULL),
m_guiMouseCallback(NULL),
m_guiKeyboardCallback(NULL),
m_guiLinkCallback(NULL),
m_changeToMenu(NULL),
m_currentMenu(NULL),
m_console(NULL),
m_isMenuChanging(FG_FALSE),
m_guiCallbacks(),
m_screenBox() {
    m_widgetFactory = new CWidgetFactory();
    m_styleMgr = new CStyleManager();
    m_widgetMgr = new gui::CWidgetManager(m_widgetFactory, m_styleMgr);
    m_guiDrawer = new CDrawer();
    m_guiDrawer->setResourceManager(resourceMgr);

    if(m_pEventMgr)
        registerGuiCallbacks();

    // #FIXME - styles/widgets path - package/zip #ZIP #MOD
    if(stylesPath.length())
        m_styleMgr->setStylesPath(stylesPath);
    else
        m_styleMgr->setStylesPath("gui");
    if(widgetsPath.length())
        m_widgetMgr->setWidgetsPath(widgetsPath);
    else
        m_widgetMgr->setWidgetsPath(widgetsPath);

    m_guiCallbacks.reserve(8);

    m_managerType = FG_MANAGER_GUI_MAIN;

    m_guiLinkCallback = new CGuiMethodCallback<CGuiMain>(this, this, &CGuiMain::guiLinkHandler);

    m_console = new CConsole();
    m_console->setVisible(FG_FALSE);
}
//------------------------------------------------------------------------------

gui::CGuiMain::~CGuiMain() {
    gui::CGuiMain::destroy();
}
//------------------------------------------------------------------------------

void gui::CGuiMain::clear(void) {
    m_managerType = FG_MANAGER_GUI_MAIN;

}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::destroy(void) {
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

    m_pInputHandler = NULL;
    m_pShaderMgr = NULL;
    m_pEventMgr = NULL;
    m_pResourceMgr = NULL;
    m_managerType = FG_MANAGER_GUI_MAIN;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::initialize(void) {
    if(m_init)
        return FG_TRUE;
    if(!m_pEventMgr || !m_pResourceMgr || !m_pShaderMgr || !m_pInputHandler) {
        log::PrintError("GUI: Initialization of main GUI module failed - not all external pointers are set");
        m_init = FG_FALSE;
        return FG_FALSE;
    }
    //m_widgetFactory->registerWidget(FG_GUI_WIDGET,		&fgGuiWidget::createWidget);
    m_widgetFactory->registerWidget(LABEL, &CLabel::createWidget);
    m_widgetFactory->registerWidget(BUTTON, &CButton::createWidget);
    m_widgetFactory->registerWidget(TOGGLE_BUTTON, &CToggleButton::createWidget);
    m_widgetFactory->registerWidget(CONTAINER, &CContainer::createWidget);
    m_widgetFactory->registerWidget(MENU, &CMenu::createWidget);
    m_widgetFactory->registerWidget(FRAME, &CFrame::createWidget);
    m_widgetFactory->registerWidget(SCROLL_AREA, &CScrollArea::createWidget);
    m_widgetFactory->registerWidget(TEXT_AREA, &CTextArea::createWidget);
    m_widgetFactory->registerWidget(EDITABLE_TEXT, &CEditableText::createWidget);
    m_widgetFactory->registerWidget(CONSOLE, &CConsole::createWidget);
    m_widgetFactory->registerWidget(WINDOW, &CWindow::createWidget);
    m_widgetFactory->registerWidget(MESSAGE_BOX, &CMessageBox::createWidget);
    m_widgetFactory->registerWidget(POPUP, &CPopup::createWidget);
    m_widgetFactory->registerWidget(PROGRESS_BAR, &CProgressBar::createWidget);
    m_widgetFactory->registerWidget(TABLE, &CTable::createWidget);
    m_widgetFactory->registerWidget(LOADER, &CLoaderSub::createWidget);
    m_widgetFactory->registerWidget(SLIDER, &CSlider::createWidget);

    FG_LOG_DEBUG("GUI: Initializing builtin fonts...");
    /* List of builtin fonts:
     * * StbArial
     * * StbArialBold
     * * StbConsolas
     * * StbConsolasBold
     * * StbCourier
     * * StbCourierBold
     * * StbTimes
     * * StbTimesBold
     */
    // getRawData gets internal char size as parameter - valid values are:
    // 8, 16, 32, >32 (max 50) - four levels
    if(!createBuiltInFont("StbConsolasBold", 32)) {
        FG_LOG_ERROR("GUI: Failed to create built-in font (StbConsolasBold)");
    }
    unsigned int courierSize = 50;
    if(!createBuiltInFont("StbCourier", courierSize)) {
        FG_LOG_ERROR("GUI: Failed to create built-in font (StbCourier)");
    }
    if(!createBuiltInFont("StbCourierBold", courierSize)) {
        FG_LOG_ERROR("GUI: Failed to create built-in font (StbCourierBold)");
    }

    // Initializing style manager
    if(!m_styleMgr->initialize()) {
        FG_LOG_ERROR("GUI: Style manager not initialized");
    }
    // Setup link handler used in managed widgets - it's for menu navigation mostly
    m_widgetMgr->setLinkHandler(m_guiLinkCallback);
    // Initialize the widget manager - preload data
    if(!m_widgetMgr->initialize()) {
        FG_LOG_ERROR("GUI: Widget manager not initialized");
    }
    // Initializing console style #FIXME, this could use some optimizing
    if(m_styleMgr && m_console) {
        std::string styleName = m_console->getStyleName();
        CStyle *style = m_styleMgr->get(styleName);
        if(style) {
            FG_LOG_DEBUG("WidgetManager: Copying style to widget: '%s' of type: '%s'",
                         m_console->getNameStr(),
                         m_console->getTypeNameStr());

            style->copyFullContent(m_console->getStyleContents(),
                                   CWidget::STATE_COUNT,
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
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::createBuiltInFont(const char* name, unsigned int size) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    return createBuiltInFont(std::string(name), size);
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::createBuiltInFont(const std::string& name, unsigned int size) {
    if(name.empty() || !size || !m_pResourceMgr)
        return FG_FALSE;
    resource::CResource* pResource = m_pResourceMgr->get(name);
    gui::CFontResource* pFontBase = NULL;
    CFontBuiltInResource* pFontBuiltIn = NULL;
    SFontBuiltInRawData* pFontRawData = NULL;
    fgBool status = FG_FALSE;
    fgBool shouldInsert = FG_FALSE;
    if(!pResource) {
        pFontBuiltIn = new gui::CFontBuiltInResource();
        shouldInsert = FG_TRUE;
    } else if(pResource->getResourceType() == resource::FONT) {
        pFontBase = static_cast<gui::CFontResource*>(pResource);
        if(pFontBase->getFontType() == FONT_STB_BUILTIN) {
            // the font is already registered - need to update size, recreate
            m_pResourceMgr->dispose(pResource);
            pFontBuiltIn = static_cast<gui::CFontBuiltInResource*>(pFontBase);
        }
    }
    if(pFontBuiltIn) {
        if(name.compare("StbArial") == 0) {
            pFontRawData = font::StbArial::getRawData(size);
        } else if(name.compare("StbArialBold") == 0) {
            pFontRawData = font::StbArialBold::getRawData(size);
        } else if(name.compare("StbConsolas") == 0) {
            pFontRawData = font::StbConsolas::getRawData(size);
        } else if(name.compare("StbConsolasBold") == 0) {
            pFontRawData = font::StbConsolasBold::getRawData(size);
        } else if(name.compare("StbCourier") == 0) {
            pFontRawData = font::StbCourier::getRawData(size);
        } else if(name.compare("StbCourierBold") == 0) {
            pFontRawData = font::StbCourierBold::getRawData(size);
        } else if(name.compare("StbTimes") == 0) {
            pFontRawData = font::StbTimes::getRawData(size);
        } else if(name.compare("StbTimesBold") == 0) {
            pFontRawData = font::StbTimesBold::getRawData(size);
        }
        if(pFontRawData) {
            pFontBuiltIn->setBuiltInRawFontData(pFontRawData);
            if(shouldInsert) {
                pFontBuiltIn->setName(name);
                m_pResourceMgr->insert(pFontBuiltIn);
            }
            // This will automatically create the resource and also throw event for GFX upload
            if(m_pResourceMgr->get(pFontBuiltIn->getRefHandle()) != NULL) {
                status = FG_TRUE;
            }
        }
    }
    if(pFontBuiltIn && shouldInsert && !pFontRawData) {
        delete pFontBuiltIn;
        pFontBuiltIn = NULL;
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::disposeBuiltInFont(const char* name) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    return disposeBuiltInFont(std::string(name));
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::disposeBuiltInFont(const std::string& name) {
    if(name.empty() || !m_pResourceMgr)
        return FG_FALSE;
    resource::CResource* pResource = m_pResourceMgr->get(name);
    gui::CFontResource* pFontBase = NULL;
    fgBool status = FG_FALSE;
    if(!pResource)
        return status;
    if(pResource->getResourceType() == resource::FONT) {
        pFontBase = static_cast<gui::CFontResource*>(pResource);
        if(pFontBase->getFontType() == FONT_STB_BUILTIN) {
            m_pResourceMgr->dispose(pResource);
            status = FG_TRUE;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::destroyBuiltInFont(const char* name) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    return destroyBuiltInFont(std::string(name));
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::destroyBuiltInFont(const std::string& name) {
    if(name.empty() || !m_pResourceMgr)
        return FG_FALSE;
    resource::CResource* pResource = m_pResourceMgr->get(name);
    gui::CFontResource* pFontBase = NULL;
    fgBool status = FG_FALSE;
    if(!pResource)
        return status;
    if(pResource->getResourceType() == resource::FONT) {
        pFontBase = static_cast<gui::CFontResource*>(pResource);
        if(pFontBase->getFontType() == FONT_STB_BUILTIN) {
            m_pResourceMgr->dispose(pResource);
            m_pResourceMgr->remove(pResource);
            delete pResource;
            status = FG_TRUE;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

void gui::CGuiMain::registerGuiCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_guiTouchCallback)
        m_guiTouchCallback = new event::CMethodCallback<CGuiMain>(this, &CGuiMain::guiTouchHandler);

    m_pEventMgr->addCallback(event::TOUCH_PRESSED, m_guiTouchCallback);
    m_pEventMgr->addCallback(event::TOUCH_RELEASED, m_guiTouchCallback);
    m_pEventMgr->addCallback(event::TOUCH_MOTION, m_guiTouchCallback);
    m_pEventMgr->addCallback(event::TOUCH_TAP_FINISHED, m_guiTouchCallback);

    if(!m_guiMouseCallback)
        m_guiMouseCallback = new event::CMethodCallback<CGuiMain>(this, &CGuiMain::guiMouseHandler);

    m_pEventMgr->addCallback(event::MOUSE_PRESSED, m_guiMouseCallback);
    m_pEventMgr->addCallback(event::MOUSE_RELEASED, m_guiMouseCallback);
    m_pEventMgr->addCallback(event::MOUSE_MOTION, m_guiMouseCallback);

    if(!m_guiKeyboardCallback)
        m_guiKeyboardCallback = new event::CMethodCallback<CGuiMain>(this, &CGuiMain::guiKeyboardHandler);

    m_pEventMgr->addCallback(event::KEY_UP, m_guiKeyboardCallback);
    m_pEventMgr->addCallback(event::KEY_DOWN, m_guiKeyboardCallback);
    m_pEventMgr->addCallback(event::KEY_PRESSED, m_guiKeyboardCallback);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::unregisterGuiCallbacks(void) {
    if(!m_pEventMgr)
        return;

    m_pEventMgr->removeCallback(event::TOUCH_PRESSED, m_guiTouchCallback);
    m_pEventMgr->removeCallback(event::TOUCH_RELEASED, m_guiTouchCallback);
    m_pEventMgr->removeCallback(event::TOUCH_MOTION, m_guiTouchCallback);
    m_pEventMgr->removeCallback(event::TOUCH_TAP_FINISHED, m_guiTouchCallback);

    m_pEventMgr->removeCallback(event::MOUSE_PRESSED, m_guiMouseCallback);
    m_pEventMgr->removeCallback(event::MOUSE_RELEASED, m_guiMouseCallback);
    m_pEventMgr->removeCallback(event::MOUSE_MOTION, m_guiMouseCallback);

    m_pEventMgr->removeCallback(event::KEY_UP, m_guiKeyboardCallback);
    m_pEventMgr->removeCallback(event::KEY_DOWN, m_guiKeyboardCallback);
    m_pEventMgr->removeCallback(event::KEY_PRESSED, m_guiKeyboardCallback);
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::addWidgetCallback(CWidget *pWidget,
                                        CGuiCallback *pCallback,
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
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::addWidgetCallback(const char *widgetName,
                                        CGuiCallback *pCallback,
                                        const fgGuiWidgetCallbackType callbackType) {
    if(!widgetName || !pCallback || !callbackType)
        return FG_FALSE;
    if(!*widgetName)
        return FG_FALSE;
    return addWidgetCallback(m_widgetMgr->get(widgetName), pCallback, callbackType);
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::addWidgetCallback(const std::string& widgetName,
                                        CGuiCallback *pCallback,
                                        const fgGuiWidgetCallbackType callbackType) {
    if(!pCallback || !callbackType || widgetName.empty())
        return FG_FALSE;
    return addWidgetCallback(m_widgetMgr->get(widgetName), pCallback, callbackType);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::updateState(void) {
    if(!m_widgetMgr || !m_pResourceMgr || !m_pInputHandler)
        return;
    if(m_isMenuChanging) {
        if(m_changeToMenu) {
            // This will throw proper event (that the changing did finish)
            // second parameter is set to false to avoid recursion
            setCurrentMenu(m_changeToMenu, FG_FALSE);
        }
        m_isMenuChanging = FG_FALSE;
        //return;
    }
    if(!m_currentMenu) {
        // #FIXME - this needs to look a little bit differently
        gui::CWidgetManager::WidgetVec& roots = m_widgetMgr->getRefRootWidgets();
        if(roots.empty())
            return;
        gui::CWidget *mainMenu = m_widgetMgr->get("MainMenu");
        if(!mainMenu)
            return;
        if(!(mainMenu->getTypeTraits() & MENU))
            return;
        m_currentMenu = static_cast<CMenu *>(mainMenu);
    }
    event::SPointerData *pt = m_pInputHandler->getPointerData();
    //if(pt) {
    //    pt->m_x = (int)((float)pt->m_x * ((1.0f - guiScale) / guiScale + 1.0f));
    //    pt->m_y = (int)((float)pt->m_y * ((1.0f - guiScale) / guiScale + 1.0f));
    //}
    m_currentMenu->updateState(pt);

    if(m_console) {
        if(m_console->isVisible()) {
            m_console->updateState(pt);
        }
    }
}
//------------------------------------------------------------------------------

void gui::CGuiMain::preRender(void) {
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
    if(!(m_currentMenu->getTypeTraits() & CONTAINER))
        return;
    // clear the internal gui drawing batch (font & forms)
    m_guiDrawer->flush();

    // Maybe update bounds should be in update part? not display...
    m_currentMenu->updateBounds(m_screenBox);
    m_currentMenu->preRender(m_guiDrawer);

    // #FUBAR #MSG
    if(m_console) {
        int numMessages = FG_MessageSubsystem->getStatusVec().size();
        int consoleSize = m_console->getNumConsoleRecords();
        if(consoleSize < numMessages) {
            m_console->updateFromStatusVec(FG_MessageSubsystem->getStatusVec());
        }
        if(m_console->isVisible()) {
            m_console->updateBounds(m_screenBox);
            m_console->preRender(m_guiDrawer);
        }
    }
}
//------------------------------------------------------------------------------

void gui::CGuiMain::render(void) {
    m_guiDrawer->render();
}
//------------------------------------------------------------------------------

gui::CDrawer* gui::CGuiMain::getDrawer(void) const {
    return m_guiDrawer;
}
//------------------------------------------------------------------------------

gui::CWidgetManager *gui::CGuiMain::getWidgetManager(void) const {
    return m_widgetMgr;
}
//------------------------------------------------------------------------------

gui::CWidgetFactory *gui::CGuiMain::getWidgetFactory(void) const {
    return m_widgetFactory;
}
//------------------------------------------------------------------------------

gui::CStyleManager *gui::CGuiMain::getStyleManager(void) const {
    return m_styleMgr;
}
//------------------------------------------------------------------------------

event::CEventManager *gui::CGuiMain::getEventManager(void) const {
    return m_pEventMgr;
}
//------------------------------------------------------------------------------

resource::CResourceManager *gui::CGuiMain::getResourceManager(void) const {
    return m_pResourceMgr;
}
//------------------------------------------------------------------------------

base::CManager *gui::CGuiMain::getShaderManager(void) const {
    return m_pShaderMgr;
}
//------------------------------------------------------------------------------

event::CInputHandler *gui::CGuiMain::getInputHandler(void) const {
    return m_pInputHandler;
}
//------------------------------------------------------------------------------

void gui::CGuiMain::setEventManager(event::CEventManager * pEventMgr) {
    if(!pEventMgr) {
        unregisterGuiCallbacks();
    } else if(m_pEventMgr && m_pEventMgr != pEventMgr) {
        unregisterGuiCallbacks();
    }
    m_pEventMgr = pEventMgr;
    if(m_pEventMgr)
        registerGuiCallbacks();
}
//------------------------------------------------------------------------------

void gui::CGuiMain::setResourceManager(resource::CResourceManager * pResourceMgr) {
    m_pResourceMgr = pResourceMgr;
    if(m_guiDrawer)
        m_guiDrawer->setResourceManager(pResourceMgr);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::setShaderManager(base::CManager* pShaderMgr) {
    if(pShaderMgr) {
        if(pShaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
            return;
    }
    m_pShaderMgr = pShaderMgr;
    if(m_guiDrawer)
        m_guiDrawer->setShaderManager(m_pShaderMgr);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::setInputHandler(event::CInputHandler* pInputHandler) {
    m_pInputHandler = pInputHandler;
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::guiTouchHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent*)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    this->updateState();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::guiMouseHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent*)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    this->updateState();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::guiKeyboardHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent*)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    event::SKey* pKey = (event::SKey*)pEvent;
    if(pKey->eventType == event::KEY_PRESSED) {
        if(pKey->which == event::FG_KEY_TILDE && pKey->pressed) {
            m_console->setVisible(!m_console->isVisible());
            g_DebugConfig.consoleShow = (bool)m_console->isVisible();
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gui::CGuiMain::guiLinkHandler(CGuiMain* pGuiMain, CWidget* pWidget) {
    if(!pGuiMain || !pWidget || !m_widgetMgr)
        return FG_FALSE;
    if(pWidget->getLink().length()) {
        CWidget *goToWidget = m_widgetMgr->get(pWidget->getLink());
        if(!goToWidget)
            return FG_FALSE;
        if(goToWidget->getTypeTraits() & MENU) {
            changeMenu(goToWidget);
            return FG_TRUE;
        } else {
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gui::CGuiMain::changeMenu(const char *menuName) {
    if(!menuName) {
        return;
    }
    if(!m_widgetMgr) {
        return;
    }
    CWidget *pWidget = m_widgetMgr->get(menuName);
    changeMenu(pWidget);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::changeMenu(const std::string& menuName) {
    if(menuName.empty()) {
        return;
    }
    if(!m_widgetMgr) {
        return;
    }
    CWidget *pWidget = m_widgetMgr->get(menuName);
    changeMenu(pWidget);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::changeMenu(CWidget *pMenu) {
    if(!pMenu)
        return;
    if(m_widgetMgr && !m_widgetMgr->isManaged(pMenu)) {
        return;
    }
    if(pMenu->getTypeTraits() & MENU) {
        event::SMenuChanged* menuEvent = (event::SMenuChanged*)m_pEventMgr->requestEventStruct();
        event::CArgumentList* argList = m_pEventMgr->requestArgumentList();
        // menu will change later, animation is starting (if any)
        menuEvent->didChange = FG_FALSE;
        menuEvent->prevMenu = m_currentMenu;
        menuEvent->nextMenu = pMenu;
        if(m_currentMenu) {
            menuEvent->prevMenuName = m_currentMenu->getNameStr();
        } else {
            menuEvent->prevMenuName = "\0";
        }
        menuEvent->nextMenuName = pMenu->getNameStr();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)menuEvent);
        m_pEventMgr->throwEvent(event::MENU_CHANGED, argList);

        m_changeToMenu = static_cast<CMenu *>(pMenu);
        FG_LOG_DEBUG("GUI: Changing menu to: '%s'", m_changeToMenu->getNameStr());
        this->updateState();
        m_isMenuChanging = FG_TRUE;
    }
}
//------------------------------------------------------------------------------

void gui::CGuiMain::setCurrentMenu(const char *menuName, fgBool shouldUpdateState) {
    if(!menuName) {
        return;
    }
    if(!m_widgetMgr) {
        return;
    }
    CWidget *pWidget = m_widgetMgr->get(menuName);
    setCurrentMenu(pWidget, shouldUpdateState);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::setCurrentMenu(const std::string& menuName, fgBool shouldUpdateState) {
    if(menuName.empty()) {
        return;
    }
    if(!m_widgetMgr) {
        return;
    }
    CWidget *pWidget = m_widgetMgr->get(menuName);
    setCurrentMenu(pWidget, shouldUpdateState);
}
//------------------------------------------------------------------------------

void gui::CGuiMain::setCurrentMenu(CWidget *pMenu, fgBool shouldUpdateState) {
    if(!pMenu)
        return;
    if(m_widgetMgr && !m_widgetMgr->isManaged(pMenu)) {
        return;
    }
    if(pMenu->getTypeTraits() & MENU) {
        event::SMenuChanged* menuEvent = (event::SMenuChanged*)m_pEventMgr->requestEventStruct();
        event::CArgumentList* argList = m_pEventMgr->requestArgumentList();
        menuEvent->didChange = FG_TRUE; // menu did change, animation ended
        menuEvent->prevMenu = m_currentMenu;
        menuEvent->nextMenu = pMenu;
        if(m_currentMenu) {
            menuEvent->prevMenuName = m_currentMenu->getNameStr();
        } else {
            menuEvent->prevMenuName = "\0"; // empty name
        }
        menuEvent->nextMenuName = pMenu->getNameStr();
        argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)menuEvent);
        m_pEventMgr->throwEvent(event::MENU_CHANGED, argList);

        m_currentMenu = static_cast<CMenu *>(pMenu);
        FG_LOG_DEBUG("GUI: Setting current menu to: '%s'", m_currentMenu->getNameStr());
        m_isMenuChanging = FG_FALSE;
        if(shouldUpdateState) {
            this->updateState();
        }
    }
}
//------------------------------------------------------------------------------
