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

/*
 *
 */
fgGuiMain::fgGuiMain(fgEventManager *eventMgr, fgResourceManager *resourceMgr) :
m_styleMgr(NULL),
m_widgetMgr(NULL),
m_widgetFactory(NULL),
m_eventMgr(eventMgr),
m_resourceMgr(resourceMgr),
m_guiDrawer(NULL),
m_shaderMgr(NULL),
m_pointerInputReceiver(NULL),
m_guiTouchCallback(NULL),
m_guiMouseCallback(NULL) {
    m_widgetFactory = new fgGuiWidgetFactory();
    m_styleMgr = new fgGuiStyleManager();
    m_widgetMgr = new fgGuiWidgetManager(m_widgetFactory, m_styleMgr);
    m_guiDrawer = new fgGuiDrawer();
    m_guiDrawer->setResourceManager(resourceMgr);

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

    if(m_eventMgr)
        registerGuiCallbacks();
}

/*
 *
 */
fgGuiMain::~fgGuiMain() {
    unregisterGuiCallbacks();

    if(m_widgetMgr)
        delete m_widgetMgr;
    m_widgetMgr = NULL;

    if(m_widgetFactory)
        delete m_widgetFactory;
    m_widgetFactory = NULL;

    if(m_styleMgr)
        delete m_styleMgr;

    if(m_guiDrawer)
        delete m_guiDrawer;

    m_styleMgr = NULL;
    m_eventMgr = NULL;
    m_resourceMgr = NULL;
    m_guiDrawer = NULL;

    if(m_guiMouseCallback)
        delete m_guiMouseCallback;
    m_guiMouseCallback = NULL;

    if(m_guiTouchCallback)
        delete m_guiTouchCallback;
    m_guiTouchCallback = NULL;

    m_pointerInputReceiver = NULL;
    m_shaderMgr = NULL;
}

/*
 *
 */
void fgGuiMain::registerGuiCallbacks(void) {
    if(!m_eventMgr)
        return;

    if(!m_guiTouchCallback)
        m_guiTouchCallback = new fgClassCallback<fgGuiMain>(this, &fgGuiMain::guiTouchHandler);

    m_eventMgr->addEventCallback(FG_EVENT_TOUCH_PRESSED, m_guiTouchCallback);
    m_eventMgr->addEventCallback(FG_EVENT_TOUCH_RELEASED, m_guiTouchCallback);
    m_eventMgr->addEventCallback(FG_EVENT_TOUCH_MOTION, m_guiTouchCallback);
    m_eventMgr->addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_guiTouchCallback);

    if(!m_guiMouseCallback)
        m_guiMouseCallback = new fgClassCallback<fgGuiMain>(this, &fgGuiMain::guiMouseHandler);

    m_eventMgr->addEventCallback(FG_EVENT_MOUSE_PRESSED, m_guiMouseCallback);
    m_eventMgr->addEventCallback(FG_EVENT_MOUSE_RELEASED, m_guiMouseCallback);
    m_eventMgr->addEventCallback(FG_EVENT_MOUSE_MOTION, m_guiMouseCallback);
}

/*
 *
 */
void fgGuiMain::unregisterGuiCallbacks(void) {
    if(!m_eventMgr)
        return;

    m_eventMgr->removeEventCallback(FG_EVENT_TOUCH_PRESSED, m_guiTouchCallback);
    m_eventMgr->removeEventCallback(FG_EVENT_TOUCH_RELEASED, m_guiTouchCallback);
    m_eventMgr->removeEventCallback(FG_EVENT_TOUCH_MOTION, m_guiTouchCallback);
    m_eventMgr->removeEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_guiTouchCallback);
    m_eventMgr->removeEventCallback(FG_EVENT_MOUSE_PRESSED, m_guiMouseCallback);
    m_eventMgr->removeEventCallback(FG_EVENT_MOUSE_RELEASED, m_guiMouseCallback);
    m_eventMgr->removeEventCallback(FG_EVENT_MOUSE_MOTION, m_guiMouseCallback);
}

/**
 * 
 */
void fgGuiMain::updateState(void) {
    if(!m_widgetMgr || !m_resourceMgr || !m_pointerInputReceiver)
        return;
    fgGuiWidgetManager::widgetVec & roots = m_widgetMgr->getRefRootWidgets();
    if(roots.empty())
        return;
    fgGuiWidget *mainMenu = m_widgetMgr->get("MainMenu");
    if(!mainMenu)
        return;
    if(!(mainMenu->getTypeTraits() & FG_GUI_CONTAINER))
        return;
    mainMenu->updateState(m_pointerInputReceiver->getPointerData());
}

/*
 *
 */
void fgGuiMain::display(void) {
    if(!m_widgetMgr || !m_resourceMgr)
        return;
    fgGuiWidgetManager::widgetVec & roots = m_widgetMgr->getRefRootWidgets();
    if(roots.empty())
        return;
    fgGuiWidget *mainMenu = m_widgetMgr->get("MainMenu");
    if(!mainMenu)
        return;
    if(!(mainMenu->getTypeTraits() & FG_GUI_CONTAINER))
        return;
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
    return m_eventMgr;
}

/*
 *
 */
fgResourceManager *fgGuiMain::getResourceManager(void) const {
    return m_resourceMgr;
}

/*
 *
 */
fgManagerBase *fgGuiMain::getShaderManager(void) const {
    return m_shaderMgr;
}

/*
 *
 */
fgPointerInputReceiver *fgGuiMain::getPointerInputReceiver(void) const {
    return m_pointerInputReceiver;
}

/*
 *
 */
void fgGuiMain::setEventManager(fgEventManager *eventMgr) {
    if(!eventMgr) {
        unregisterGuiCallbacks();
    } else if(m_eventMgr && m_eventMgr != eventMgr) {
        unregisterGuiCallbacks();
    }
    m_eventMgr = eventMgr;
    if(m_eventMgr)
        registerGuiCallbacks();
}

/*
 *
 */
void fgGuiMain::setResourceManager(fgResourceManager *resourceMgr) {
    m_resourceMgr = resourceMgr;
    if(m_guiDrawer)
        m_guiDrawer->setResourceManager(resourceMgr);
}

/*
 *
 */
void fgGuiMain::setShaderManager(fgManagerBase *shaderMgr) {
    if(shaderMgr) {
        if(shaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
            return;
    }
    m_shaderMgr = shaderMgr;
    if(m_guiDrawer)
        m_guiDrawer->setShaderManager(m_shaderMgr);
}

/*
 *
 */
void fgGuiMain::setPointerInputReceiver(fgPointerInputReceiver *pointerInputReceiver) {
    m_pointerInputReceiver = pointerInputReceiver;
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
