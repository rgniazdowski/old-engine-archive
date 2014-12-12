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

/**
 * 
 * @param widgetFactory
 * @param styleMgr
 */
fgGuiWidgetManager::fgGuiWidgetManager(fgGuiWidgetFactory *widgetFactory, fgGuiStyleManager *styleMgr) :
m_pWidgetFactory(widgetFactory),
m_pStyleMgr(styleMgr),
m_pGuiLinkCallback(NULL) {
    m_managerType = FG_MANAGER_GUI_WIDGET;
}

/**
 * 
 */
fgGuiWidgetManager::~fgGuiWidgetManager() {
    fgGuiWidgetManager::destroy();
}

/**
 * 
 * @return 
 */
fgBool fgGuiWidgetManager::destroy(void) {
    hmDataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        if((*itor) == NULL)
            continue;

        delete (*itor);
        *itor = NULL;
    }
    fgHandleManager::clear();
    m_pStyleMgr = NULL;
    m_pWidgetFactory = NULL;
    m_pGuiLinkCallback = NULL;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgGuiWidgetManager::initialize(void) {
    FG_LOG_DEBUG("GUI: Initializing Widget manager...");
    if(!m_pWidgetFactory || !m_pStyleMgr) {
        FG_LOG::PrintError("GUI: Failed to initialize widget manager - not all external pointers are set");
        return FG_FALSE;
    }
    if(m_widgetsPath.empty()) {
        FG_LOG::PrintError("GUI: Default path for widgets directory is not set");
        return FG_FALSE;
    }
    // Will now preload all required styles
    fgDirent widgetsDir;
    const char *filename = NULL;
    widgetsDir.readDirectory(m_widgetsPath, FG_TRUE);
    while((filename = widgetsDir.getNextFile()) != NULL) {
        const char *ext = fgPath::fileExt(filename, FG_TRUE);
        if(!ext)
            continue;
        if(strcasecmp(ext, "gui.xml") == 0) {
            FG_LOG_DEBUG("GUI: Loading gui widget struct file: '%s'", filename);
            if(!loadStructureSheet(filename)) {
                FG_LOG::PrintError("GUI: Failed to load gui widget struct: '%s'", filename);
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
void fgGuiWidgetManager::clear(void) {
    fgHandleManager::clear();
}

/**
 * 
 * @param typeName
 * @return 
 */
fgGuiWidgetType fgGuiWidgetManager::widgetTypeFromName(const char *typeName) {
    if(!typeName)
        return FG_GUI_WIDGET_UNKNOWN;
    return widgetTypeFromName(std::string(typeName));
}

/**
 * 
 * @param typeName
 * @return 
 */
fgGuiWidgetType fgGuiWidgetManager::widgetTypeFromName(const std::string& typeName) {
    if(typeName.empty())
        return FG_GUI_WIDGET_UNKNOWN;

    if(typeName.compare(FG_GUI_LABEL_NAME) == 0) {
        return FG_GUI_LABEL;
    } else if(typeName.compare(FG_GUI_BUTTON_NAME) == 0) {
        return FG_GUI_BUTTON;
    } else if(typeName.compare(FG_GUI_TOGGLE_BUTTON_NAME) == 0) {
        return FG_GUI_TOGGLE_BUTTON;
    } else if(typeName.compare(FG_GUI_CONTAINER_NAME) == 0) {
        return FG_GUI_CONTAINER;
    } else if(typeName.compare(FG_GUI_MENU_NAME) == 0) {
        return FG_GUI_MENU;
    } else if(typeName.compare(FG_GUI_FRAME_NAME) == 0) {
        return FG_GUI_FRAME;
    } else if(typeName.compare(FG_GUI_SCROLL_AREA_NAME) == 0) {
        return FG_GUI_SCROLL_AREA;
    } else if(typeName.compare(FG_GUI_TEXT_AREA_NAME) == 0) {
        return FG_GUI_TEXT_AREA;
    } else if(typeName.compare(FG_GUI_EDITABLE_TEXT_NAME) == 0) {
        return FG_GUI_EDITABLE_TEXT;
    } else if(typeName.compare(FG_GUI_CONSOLE_NAME) == 0) {
        return FG_GUI_CONSOLE;
    } else if(typeName.compare(FG_GUI_WINDOW_NAME) == 0) {
        return FG_GUI_WINDOW;
    } else if(typeName.compare(FG_GUI_MESSAGE_BOX_NAME) == 0) {
        return FG_GUI_MESSAGE_BOX;
    } else if(typeName.compare(FG_GUI_POPUP_NAME) == 0) {
        return FG_GUI_POPUP;
    } else if(typeName.compare(FG_GUI_PROGRESS_BAR_NAME) == 0) {
        return FG_GUI_PROGRESS_BAR;
    } else if(typeName.compare(FG_GUI_TABLE_NAME) == 0) {
        return FG_GUI_TABLE;
    } else if(typeName.compare(FG_GUI_LOADER_NAME) == 0) {
        return FG_GUI_LOADER;
    } else if(typeName.compare(FG_GUI_SLIDER_NAME) == 0) {
        return FG_GUI_SLIDER;
    }

    return FG_GUI_WIDGET_UNKNOWN;
}

/**
 * 
 * @param path
 */
void fgGuiWidgetManager::setWidgetsPath(const std::string& path) {
    m_widgetsPath = path;
}

/**
 * 
 * @param path
 */
void fgGuiWidgetManager::setWidgetsPath(const char* path) {
    m_widgetsPath = path;
}

/**
 * 
 * @return 
 */
fgGuiWidgetManager::widgetVec& fgGuiWidgetManager::getRefRootWidgets(void) {
    return m_rootWidgets;
}

/**
 * 
 * @param widgetFactory
 */
void fgGuiWidgetManager::setWidgetFactory(fgGuiWidgetFactory *widgetFactory) {
    m_pWidgetFactory = widgetFactory;
}

/**
 * 
 * @return 
 */
fgGuiWidgetFactory *fgGuiWidgetManager::getWidgetFactory(void) const {
    return m_pWidgetFactory;
}

/**
 * 
 * @param styleMgr
 */
void fgGuiWidgetManager::setStyleManager(fgGuiStyleManager *styleMgr) {
    m_pStyleMgr = styleMgr;
}

/**
 * 
 * @return 
 */
fgGuiStyleManager *fgGuiWidgetManager::getStyleManager(void) const {
    return m_pStyleMgr;
}

/**
 * 
 * @param filePath
 * @return 
 */
fgBool fgGuiWidgetManager::loadStructureSheet(const std::string& filePath) {
    if(filePath.empty()) {
        return FG_FALSE;
    }
    return fgGuiWidgetManager::loadStructureSheet(filePath.c_str());
}

/**
 * 
 * @param filePath
 * @return 
 */
fgBool fgGuiWidgetManager::loadStructureSheet(const char *filePath) {
    if(!filePath) {
        return FG_FALSE;
    }
    fgXMLParser *xmlParser = new fgXMLParser();
    fgGuiStructureSheetParser *contentHandler = new fgGuiStructureSheetParser();

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
fgBool fgGuiWidgetManager::addWidget(fgGuiWidget *pWidget) {
    return addWidget(pWidget, (fgGuiWidget *)NULL);
}

/**
 * 
 * @param wUniqueID
 * @param pWidget
 * @param pFatherWidget
 * @return 
 */
fgBool fgGuiWidgetManager::addWidget(fgGuiWidget *pWidget, fgGuiWidget *pFatherWidget) {
    if(!pWidget) {
        // Empty pointer - return
        FG_LOG::PrintError("WidgetManager: // Empty pointer - exit... no addition made");
        return FG_FALSE;
    }
    fgGuiWidgetHandle wUniqueID;
    if(fgHandleManager::isDataManaged(pWidget)) {
        // Widget is already managed in the handle manager
        FG_LOG::PrintError("WidgetManager: // Widget is already managed in the handle manager: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
        return FG_FALSE;
    }

    if(!pWidget->getHandle().isNull()) {
        // Widget has already initialized handle
        FG_LOG::PrintError("WidgetManager: // Widget has already initialized handle: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
        return FG_FALSE;
    }

    if(!fgHandleManager::acquireHandle(wUniqueID, pWidget)) {
        // Could not aquire handle for the widget
        FG_LOG::PrintError("WidgetManager: // Could not aquire handle for the widget: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
        return FG_FALSE;
    }
    pWidget->setHandle(wUniqueID);

    if(!fgHandleManager::setupName(pWidget->getName(), wUniqueID)) {
        // Could not setup handle string tag/name for the widget
        FG_LOG::PrintError("WidgetManager: // Could not setup handle string tag/name for the widget: '%s' of type '%s'", pWidget->getNameStr(), pWidget->getTypeNameStr());
    }

    if(!pFatherWidget) {
        // There is no father widget so this widget will be one of the roots
        // No additional checking made
        // #FIXME - need to hold this in different struct, need to make
        // erasing root widgets easier
        m_rootWidgets.push_back(pWidget);
    } else {
        if(!fgGuiWidgetManager::isManaged(pFatherWidget)) {
            // father widget is not managed - illegal insert
            // ignore the widget #FIXME ?
            m_rootWidgets.push_back(pWidget);
            pWidget->setFather(NULL); // #FIXME
        } else {
            pWidget->setFather(pFatherWidget);
            if(pFatherWidget->getTypeTraits() & FG_GUI_CONTAINER) {
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
        fgGuiStyle *style = m_pStyleMgr->get(styleName);
        if(style) {
            FG_LOG_DEBUG("WidgetManager: Copying style to widget: '%s' of type: '%s'",
                               pWidget->getNameStr(),
                               pWidget->getTypeNameStr());

            style->copyFullContent(pWidget->getStyleContents(),
                                   FG_GUI_WIDGET_STATE_COUNT,
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
fgBool fgGuiWidgetManager::addWidget(fgGuiWidget *pWidget, const fgGuiWidgetHandle& wFatherUniqueID) {
    return addWidget(pWidget, fgHandleManager::dereference(wFatherUniqueID));
}

/**
 * 
 * @param wUniqueID
 * @param pWidget
 * @param wFatherNameTag
 * @return 
 */
fgBool fgGuiWidgetManager::addWidget(fgGuiWidget *pWidget, const std::string& wFatherNameTag) {
    return addWidget(pWidget, fgHandleManager::dereference(wFatherNameTag));
}

/**
 * 
 * @param wUniqueID
 * @param pWidget
 * @param wFatherNameTag
 * @return 
 */
fgBool fgGuiWidgetManager::addWidget(fgGuiWidget *pWidget, const char* wFatherNameTag) {
    return addWidget(pWidget, fgHandleManager::dereference(wFatherNameTag));
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool fgGuiWidgetManager::remove(fgGuiWidget *pWidget) {
    if(!fgGuiWidgetManager::isManaged(pWidget)) {
        return FG_FALSE;
    }
    if(fgHandleManager::releaseHandle(pWidget->getHandle())) {
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
fgBool fgGuiWidgetManager::remove(const fgGuiWidgetHandle& wUniqueID) {
    fgGuiWidget *pWidget = dereference(wUniqueID);
    if(!pWidget)
        return FG_FALSE;
    if(fgHandleManager::releaseHandle(pWidget->getHandle())) {
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
fgBool fgGuiWidgetManager::remove(const std::string& nameTag) {
    fgGuiWidget *pWidget = dereference(nameTag);
    if(!pWidget)
        return FG_FALSE;
    if(fgHandleManager::releaseHandle(pWidget->getHandle())) {
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
fgBool fgGuiWidgetManager::remove(const char *nameTag) {
    fgGuiWidget *pWidget = dereference(nameTag);
    if(!pWidget)
        return FG_FALSE;
    if(fgHandleManager::releaseHandle(pWidget->getHandle())) {
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
fgBool fgGuiWidgetManager::destroyWidget(fgGuiWidget* & pWidget) {
    if(!fgGuiWidgetManager::remove(pWidget)) {
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
fgBool fgGuiWidgetManager::destroyWidget(const fgGuiWidgetHandle& wUniqueID) {
    fgGuiWidget *pWidget = dereference(wUniqueID);
    return destroyWidget(pWidget);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGuiWidgetManager::destroyWidget(const std::string& nameTag) {
    fgGuiWidget *pWidget = dereference(nameTag);
    return destroyWidget(pWidget);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGuiWidgetManager::destroyWidget(const char *nameTag) {
    fgGuiWidget *pWidget = dereference(nameTag);
    return destroyWidget(pWidget);
}

/**
 * 
 * @param wUniqueID
 * @return 
 */
fgGuiWidget* fgGuiWidgetManager::get(const fgGuiWidgetHandle& wUniqueID) {
    return fgHandleManager::dereference(wUniqueID);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGuiWidget* fgGuiWidgetManager::get(const std::string& nameTag) {
    return fgHandleManager::dereference(nameTag);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGuiWidget* fgGuiWidgetManager::get(const char *nameTag) {
    return fgHandleManager::dereference(nameTag);
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool fgGuiWidgetManager::isManaged(fgGuiWidget *pWidget) {
    if(!pWidget) {
        return FG_FALSE;
    }
    if(FG_IS_INVALID_HANDLE(pWidget->getHandle()) ||
       !fgHandleManager::isHandleValid(pWidget->getHandle())) {
        return FG_FALSE;
    }
    if(!fgHandleManager::isDataManaged(pWidget)) {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * 
 * @param wUniqueID
 * @return 
 */
fgBool fgGuiWidgetManager::isManaged(const fgGuiWidgetHandle& wUniqueID) {
    fgGuiWidget *pWidget = get(wUniqueID);
    return (fgBool)(pWidget != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGuiWidgetManager::isManaged(const std::string& nameTag) {
    fgGuiWidget *pWidget = get(nameTag);
    return (fgBool)(pWidget != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGuiWidgetManager::isManaged(const char *nameTag) {
    fgGuiWidget *pWidget = get(nameTag);
    return (fgBool)(pWidget != NULL);
}
