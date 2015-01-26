/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiWidgetManager.h"

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

#include "XML/fgXMLParser.h"
#include "fgGuiStructureSheetParser.h"
#include "Util/fgDirent.h"

using namespace fg;

/**
 * 
 * @param widgetFactory
 * @param styleMgr
 */
gui::CWidgetManager::CWidgetManager(CWidgetFactory *widgetFactory, CStyleManager *styleMgr) :
m_pWidgetFactory(widgetFactory),
m_pStyleMgr(styleMgr),
m_pGuiLinkCallback(NULL) {
    m_managerType = FG_MANAGER_GUI_WIDGET;
}

/**
 * 
 */
gui::CWidgetManager::~CWidgetManager() {
    gui::CWidgetManager::destroy();
}

/**
 * 
 * @return 
 */
fgBool gui::CWidgetManager::destroy(void) {
    DataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        if((*itor).data == NULL)
            continue;

        delete (*itor).data;
        (*itor).clear();
    }
    handle_mgr_type::clear();
    m_pStyleMgr = NULL;
    m_pWidgetFactory = NULL;
    m_pGuiLinkCallback = NULL;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gui::CWidgetManager::initialize(void) {
    FG_LOG_DEBUG("GUI: Initializing Widget manager...");
    if(!m_pWidgetFactory || !m_pStyleMgr) {
        FG_LOG_ERROR("GUI: Failed to initialize widget manager - not all external pointers are set");
        return FG_FALSE;
    }
    if(m_widgetsPath.empty()) {
        FG_LOG_ERROR("GUI: Default path for widgets directory is not set");
        return FG_FALSE;
    }
    // Will now preload all required styles
    util::CDirent widgetsDir;
    const char *filename = NULL;
    fgBool status = widgetsDir.readDir(m_widgetsPath, FG_TRUE, FG_TRUE);
    if(!status) {
        FG_LOG_ERROR("GUI: Unable to read directory (widgets): '%s'", m_widgetsPath.c_str());
    }

    while((filename = widgetsDir.getNextFile()) != NULL) {
        const char *ext = fg::path::fileExt(filename, FG_TRUE);
        if(!ext)
            continue;
        if(strcasecmp(ext, "gui.xml") == 0) {
            FG_LOG_DEBUG("GUI: Loading gui widget struct file: '%s'", filename);
            if(!loadStructureSheet(filename)) {
                FG_LOG_ERROR("GUI: Failed to load gui widget struct: '%s'", filename);
                continue;
            }
            FG_LOG_DEBUG("GUI: Successfully loaded structure file '%s' to the database", filename);
        }
    }
    widgetsDir.clearList();
    m_init = FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 */
void gui::CWidgetManager::clear(void) {
    handle_mgr_type::clear();
}

/**
 * 
 * @param typeName
 * @return 
 */
gui::WidgetType gui::CWidgetManager::widgetTypeFromName(const char *typeName) {
    if(!typeName)
        return WIDGET_UNKNOWN;
    return widgetTypeFromName(std::string(typeName));
}

/**
 * 
 * @param typeName
 * @return 
 */
gui::WidgetType gui::CWidgetManager::widgetTypeFromName(const std::string& typeName) {
    if(typeName.empty())
        return WIDGET_UNKNOWN;

    if(typeName.compare(FG_GUI_LABEL_NAME) == 0) {
        return LABEL;
    } else if(typeName.compare(FG_GUI_BUTTON_NAME) == 0) {
        return BUTTON;
    } else if(typeName.compare(FG_GUI_TOGGLE_BUTTON_NAME) == 0) {
        return TOGGLE_BUTTON;
    } else if(typeName.compare(FG_GUI_CONTAINER_NAME) == 0) {
        return CONTAINER;
    } else if(typeName.compare(FG_GUI_MENU_NAME) == 0) {
        return MENU;
    } else if(typeName.compare(FG_GUI_FRAME_NAME) == 0) {
        return FRAME;
    } else if(typeName.compare(FG_GUI_SCROLL_AREA_NAME) == 0) {
        return SCROLL_AREA;
    } else if(typeName.compare(FG_GUI_TEXT_AREA_NAME) == 0) {
        return TEXT_AREA;
    } else if(typeName.compare(FG_GUI_EDITABLE_TEXT_NAME) == 0) {
        return EDITABLE_TEXT;
    } else if(typeName.compare(FG_GUI_CONSOLE_NAME) == 0) {
        return CONSOLE;
    } else if(typeName.compare(FG_GUI_WINDOW_NAME) == 0) {
        return WINDOW;
    } else if(typeName.compare(FG_GUI_MESSAGE_BOX_NAME) == 0) {
        return MESSAGE_BOX;
    } else if(typeName.compare(FG_GUI_POPUP_NAME) == 0) {
        return POPUP;
    } else if(typeName.compare(FG_GUI_PROGRESS_BAR_NAME) == 0) {
        return PROGRESS_BAR;
    } else if(typeName.compare(FG_GUI_TABLE_NAME) == 0) {
        return TABLE;
    } else if(typeName.compare(FG_GUI_LOADER_NAME) == 0) {
        return LOADER;
    } else if(typeName.compare(FG_GUI_SLIDER_NAME) == 0) {
        return SLIDER;
    }

    return WIDGET_UNKNOWN;
}

/**
 * 
 * @param path
 */
void gui::CWidgetManager::setWidgetsPath(const std::string& path) {
    m_widgetsPath = path;
}

/**
 * 
 * @param path
 */
void gui::CWidgetManager::setWidgetsPath(const char* path) {
    m_widgetsPath = path;
}

/**
 * 
 * @return 
 */
gui::CWidgetManager::WidgetVec& gui::CWidgetManager::getRefRootWidgets(void) {
    return m_rootWidgets;
}

/**
 * 
 * @param widgetFactory
 */
void gui::CWidgetManager::setWidgetFactory(CWidgetFactory *widgetFactory) {
    m_pWidgetFactory = widgetFactory;
}

/**
 * 
 * @return 
 */
gui::CWidgetFactory *gui::CWidgetManager::getWidgetFactory(void) const {
    return m_pWidgetFactory;
}

/**
 * 
 * @param styleMgr
 */
void gui::CWidgetManager::setStyleManager(CStyleManager *styleMgr) {
    m_pStyleMgr = styleMgr;
}

/**
 * 
 * @return 
 */
gui::CStyleManager *gui::CWidgetManager::getStyleManager(void) const {
    return m_pStyleMgr;
}

/**
 * 
 * @param filePath
 * @return 
 */
fgBool gui::CWidgetManager::loadStructureSheet(const std::string& filePath) {
    if(filePath.empty()) {
        return FG_FALSE;
    }
    return gui::CWidgetManager::loadStructureSheet(filePath.c_str());
}

/**
 * 
 * @param filePath
 * @return 
 */
fgBool gui::CWidgetManager::loadStructureSheet(const char *filePath) {
    if(!filePath) {
        return FG_FALSE;
    }
    xml::CParser *xmlParser = new xml::CParser();
    CStructureSheetParser *contentHandler = new CStructureSheetParser();

    contentHandler->setWidgetFactory(m_pWidgetFactory);
    contentHandler->setWidgetManager(this);

    xmlParser->setContentHandler(contentHandler);

    if(!xmlParser->loadXML(filePath)) {
        delete xmlParser;
        delete contentHandler;
        return FG_FALSE;
    }
    xmlParser->parseWithHandler();

    delete xmlParser;
    delete contentHandler;
    xmlParser = NULL;
    return FG_TRUE;
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool gui::CWidgetManager::addWidget(CWidget *pWidget) {
    return addWidget(pWidget, (CWidget *)NULL);
}

/**
 * 
 * @param wUniqueID
 * @param pWidget
 * @param pFatherWidget
 * @return 
 */
fgBool gui::CWidgetManager::addWidget(CWidget *pWidget, CWidget *pFatherWidget) {
    if(!pWidget) {
        // Empty pointer - return
        log::PrintError("WidgetManager: // Empty pointer - exit... no addition made");
        return FG_FALSE;
    }
    WidgetHandle wUniqueID;
    if(handle_mgr_type::isDataManaged(pWidget)) {
        // Widget is already managed in the handle manager
        log::PrintError("WidgetManager: // Widget is already managed in the handle manager: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
        return FG_FALSE;
    }

    if(!pWidget->getHandle().isNull()) {
        // Widget has already initialized handle
        FG_LOG_ERROR("WidgetManager: // Widget has already initialized handle: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
        return FG_FALSE;
    }

    if(!handle_mgr_type::acquireHandle(wUniqueID, pWidget)) {
        // Could not aquire handle for the widget
        FG_LOG_ERROR("WidgetManager: // Could not aquire handle for the widget: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
        return FG_FALSE;
    }
    pWidget->setHandle(wUniqueID);

    if(!handle_mgr_type::setupName(pWidget->getName(), wUniqueID)) {
        // Could not setup handle string tag/name for the widget
        FG_LOG_ERROR("WidgetManager: // Could not setup handle string tag/name for the widget: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
    }

    if(!pFatherWidget) {
        // There is no father widget so this widget will be one of the roots
        // No additional checking made
        // #FIXME - need to hold this in different struct, need to make
        // erasing root widgets easier
        m_rootWidgets.push_back(pWidget);
    } else {
        if(!gui::CWidgetManager::isManaged(pFatherWidget)) {
            // father widget is not managed - illegal insert
            // ignore the widget #FIXME ?
            m_rootWidgets.push_back(pWidget);
            pWidget->setFather(NULL); // #FIXME
        } else {
            pWidget->setFather(pFatherWidget);
            if(pFatherWidget->getTypeTraits() & CONTAINER) {
                //static_cast<fgGuiContainer *>(pFatherWidget)->addChild(pWidget);    
            }
            FG_LOG_DEBUG("Widget '%s' of type '%s', has a father '%s' of type '%s'",
                         pWidget->getNameStr(),
                         pWidget->getTypeNameStr(),
                         pFatherWidget->getNameStr(),
                         pFatherWidget->getTypeNameStr());
        }
    }
    // Update and set widget style content
    if(m_pStyleMgr) {
        std::string styleName = pWidget->getStyleName();
        CStyle *style = m_pStyleMgr->get(styleName);
        if(style) {
            FG_LOG_DEBUG("WidgetManager: Copying style to widget: '%s' of type: '%s'",
                         pWidget->getNameStr(),
                         pWidget->getTypeNameStr());

            style->copyFullContent(pWidget->getStyleContents(),
                                   (int)CWidget::State::COUNT,
                                   pWidget->getTypeName());
            pWidget->refresh();
            pWidget->updateBounds();
        }
    }
    // Mark widget as managed
    pWidget->setManaged(FG_TRUE);
    if(pFatherWidget) {
        pFatherWidget->setManaged(FG_TRUE);
        // Update size of the parent widget
        pFatherWidget->updateBounds();
    }
    if(m_pGuiLinkCallback)
        pWidget->setOnLinkCallback(m_pGuiLinkCallback);
    return FG_TRUE;
}

/**
 * 
 * @param wUniqueID
 * @param pWidget
 * @param wFatherUniqueID
 * @return 
 */
fgBool gui::CWidgetManager::addWidget(CWidget *pWidget, const WidgetHandle& wFatherUniqueID) {
    return addWidget(pWidget, handle_mgr_type::dereference(wFatherUniqueID));
}

/**
 * 
 * @param wUniqueID
 * @param pWidget
 * @param wFatherNameTag
 * @return 
 */
fgBool gui::CWidgetManager::addWidget(CWidget *pWidget, const std::string& wFatherNameTag) {
    return addWidget(pWidget, handle_mgr_type::dereference(wFatherNameTag));
}

/**
 * 
 * @param wUniqueID
 * @param pWidget
 * @param wFatherNameTag
 * @return 
 */
fgBool gui::CWidgetManager::addWidget(CWidget *pWidget, const char* wFatherNameTag) {
    return addWidget(pWidget, handle_mgr_type::dereference(wFatherNameTag));
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool gui::CWidgetManager::remove(CWidget *pWidget) {
    if(!gui::CWidgetManager::isManaged(pWidget)) {
        return FG_FALSE;
    }
    if(handle_mgr_type::releaseHandle(pWidget->getHandle())) {
        pWidget->setManaged(FG_FALSE);
        return FG_TRUE;
    } else {
        return FG_FALSE;
    }
}

/**
 * 
 * @param wUniqueID
 * @return 
 */
fgBool gui::CWidgetManager::remove(const WidgetHandle& wUniqueID) {
    CWidget *pWidget = dereference(wUniqueID);
    if(!pWidget)
        return FG_FALSE;
    if(handle_mgr_type::releaseHandle(pWidget->getHandle())) {
        pWidget->setManaged(FG_FALSE);
        return FG_TRUE;
    } else {
        return FG_FALSE;
    }
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gui::CWidgetManager::remove(const std::string& nameTag) {
    CWidget *pWidget = dereference(nameTag);
    if(!pWidget)
        return FG_FALSE;
    if(handle_mgr_type::releaseHandle(pWidget->getHandle())) {
        pWidget->setManaged(FG_FALSE);
        return FG_TRUE;
    } else {
        return FG_FALSE;
    }
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gui::CWidgetManager::remove(const char *nameTag) {
    CWidget *pWidget = dereference(nameTag);
    if(!pWidget)
        return FG_FALSE;
    if(handle_mgr_type::releaseHandle(pWidget->getHandle())) {
        pWidget->setManaged(FG_FALSE);
        return FG_TRUE;
    } else {
        return FG_FALSE;
    }
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool gui::CWidgetManager::destroyWidget(CWidget* & pWidget) {
    if(!gui::CWidgetManager::remove(pWidget)) {
        return FG_FALSE;
    }
    delete pWidget;
    pWidget = NULL;
    return FG_TRUE;
}

/**
 * 
 * @param wUniqueID
 * @return 
 */
fgBool gui::CWidgetManager::destroyWidget(const WidgetHandle& wUniqueID) {
    CWidget *pWidget = dereference(wUniqueID);
    return destroyWidget(pWidget);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gui::CWidgetManager::destroyWidget(const std::string& nameTag) {
    CWidget *pWidget = dereference(nameTag);
    return destroyWidget(pWidget);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gui::CWidgetManager::destroyWidget(const char *nameTag) {
    CWidget *pWidget = dereference(nameTag);
    return destroyWidget(pWidget);
}

/**
 * 
 * @param wUniqueID
 * @return 
 */
gui::CWidget* gui::CWidgetManager::get(const WidgetHandle& wUniqueID) {
    return handle_mgr_type::dereference(wUniqueID);
}

/**
 * 
 * @param nameTag
 * @return 
 */
gui::CWidget* gui::CWidgetManager::get(const std::string& nameTag) {
    return handle_mgr_type::dereference(nameTag);
}

/**
 * 
 * @param nameTag
 * @return 
 */
gui::CWidget* gui::CWidgetManager::get(const char *nameTag) {
    return handle_mgr_type::dereference(nameTag);
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool gui::CWidgetManager::isManaged(CWidget *pWidget) {
    if(!pWidget) {
        return FG_FALSE;
    }
    if(FG_IS_INVALID_HANDLE(pWidget->getHandle()) ||
       !handle_mgr_type::isHandleValid(pWidget->getHandle())) {
        return FG_FALSE;
    }
    if(!handle_mgr_type::isDataManaged(pWidget)) {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * 
 * @param wUniqueID
 * @return 
 */
fgBool gui::CWidgetManager::isManaged(const WidgetHandle& wUniqueID) {
    CWidget *pWidget = get(wUniqueID);
    return (fgBool)(pWidget != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gui::CWidgetManager::isManaged(const std::string& nameTag) {
    CWidget *pWidget = get(nameTag);
    return (fgBool)(pWidget != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gui::CWidgetManager::isManaged(const char *nameTag) {
    CWidget *pWidget = get(nameTag);
    return (fgBool)(pWidget != NULL);
}
