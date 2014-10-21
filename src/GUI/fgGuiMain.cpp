/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

#include "GUI/Font/fgFontStbConsolasBold.h"
#include "GUI/Font/fgFontStbCourier.h"
#include "GUI/Font/fgFontStbCourierBold.h"
#include "GUI/Font/fgFontStbTimes.h"
#include "GUI/Font/fgFontStbArial.h"
#include "GUI/Font/fgFontStbArialBold.h"
#include "GUI/Font/fgFontBuiltIn.h"

#include "fgColors.h"

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
void fgGuiMain::clear(void) { }

/**
 * 
 */
fgBool fgGuiMain::destroy(void) {
    unregisterGuiCallbacks();

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

    m_pPointerInputReceiver = NULL;
    m_pShaderMgr = NULL;
    m_pEventMgr = NULL;
    m_pResourceMgr = NULL;
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

    FG_LOG::PrintDebug("GUI: Initializing builtin fonts...");
    fgFontBuiltInResource *consolasBold = new fgFontBuiltInResource(fgFontBuiltIn::StbConsolasBold::getRawData(32));
    consolasBold->setName("StbConsolasBold");
    consolasBold->create();
    m_pResourceMgr->insertResource(consolasBold->getRefHandle(), consolasBold);
    //m_gfxMain->getTextureManager()->uploadToVRAM(consolasBold, FG_TRUE);

    fgFontBuiltInResource *courier = new fgFontBuiltInResource(fgFontBuiltIn::StbCourier::getRawData(50));
    courier->setName("StbCourier");
    courier->create();
    m_pResourceMgr->insertResource(courier->getRefHandle(), courier);
    //m_gfxMain->getTextureManager()->uploadToVRAM(courier, FG_TRUE);
    
    //
    if(!m_styleMgr->initialize()) {
        FG_LOG::PrintError("GUI: Style manager not initialized");
    }
    //
    if(!m_widgetMgr->initialize()) {
        FG_LOG::PrintError("GUI: Widget manager not initialized");
    }
    m_init = FG_TRUE;
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
 */
void fgGuiMain::updateState(void) {
    if(!m_widgetMgr || !m_pResourceMgr || !m_pPointerInputReceiver)
        return;
    fgGuiWidgetManager::widgetVec & roots = m_widgetMgr->getRefRootWidgets();
    if(roots.empty())
        return;
    fgGuiWidget *mainMenu = m_widgetMgr->get("MainMenu");
    if(!mainMenu)
        return;
    if(!(mainMenu->getTypeTraits() & FG_GUI_CONTAINER))
        return;
    mainMenu->updateState(m_pPointerInputReceiver->getPointerData());
}

/*
 *
 */
void fgGuiMain::display(void) {
    if(!m_widgetMgr || !m_pResourceMgr)
        return;
    fgGuiWidgetManager::widgetVec & roots = m_widgetMgr->getRefRootWidgets();
    if(roots.empty())
        return;
    fgGuiWidget *mainMenu = m_widgetMgr->get("MainMenu");
    if(!mainMenu)
        return;
    if(!(mainMenu->getTypeTraits() & FG_GUI_CONTAINER))
        return;
    mainMenu->updateSize(m_screenBox);
    mainMenu->display(m_guiDrawer);
}

/*
 *
 */
void fgGuiMain::render(void) {
    m_guiDrawer->render();
    m_guiDrawer->flush();

}

/*
 *
 */
fgGuiWidgetManager *fgGuiMain::getWidgetManager(void) const {
    return m_widgetMgr;
}

/*
 *
 */
fgGuiWidgetFactory *fgGuiMain::getWidgetFactory(void) const {
    return m_widgetFactory;
}

/*
 *
 */
fgGuiStyleManager *fgGuiMain::getStyleManager(void) const {
    return m_styleMgr;
}

/*
 *
 */
fgEventManager *fgGuiMain::getEventManager(void) const {
    return m_pEventMgr;
}

/*
 *
 */
fgResourceManager *fgGuiMain::getResourceManager(void) const {
    return m_pResourceMgr;
}

/*
 *
 */
fgManagerBase *fgGuiMain::getShaderManager(void) const {
    return m_pShaderMgr;
}

/*
 *
 */
fgPointerInputReceiver *fgGuiMain::getPointerInputReceiver(void) const {
    return m_pPointerInputReceiver;
}

/*
 *
 */
void fgGuiMain::setEventManager(fgEventManager *pEventMgr) {
    if(!pEventMgr) {
        unregisterGuiCallbacks();
    } else if(m_pEventMgr && m_pEventMgr != pEventMgr) {
        unregisterGuiCallbacks();
    }
    m_pEventMgr = pEventMgr;
    if(m_pEventMgr)
        registerGuiCallbacks();
}

/*
 *
 */
void fgGuiMain::setResourceManager(fgResourceManager *pResourceMgr) {
    m_pResourceMgr = pResourceMgr;
    if(m_guiDrawer)
        m_guiDrawer->setResourceManager(pResourceMgr);
}

/*
 *
 */
void fgGuiMain::setShaderManager(fgManagerBase *pShaderMgr) {
    if(pShaderMgr) {
        if(pShaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
            return;
    }
    m_pShaderMgr = pShaderMgr;
    if(m_guiDrawer)
        m_guiDrawer->setShaderManager(m_pShaderMgr);
}

/*
 *
 */
void fgGuiMain::setPointerInputReceiver(fgPointerInputReceiver *pointerInputReceiver) {
    m_pPointerInputReceiver = pointerInputReceiver;
}

/*
 *
 */
fgBool fgGuiMain::guiTouchHandler(fgArgumentList *argv) {
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
