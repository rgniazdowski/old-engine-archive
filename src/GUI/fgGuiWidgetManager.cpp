/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

/*
 *
 */
fgGuiWidgetManager::fgGuiWidgetManager(fgGuiWidgetFactory *widgetFactory, fgGuiStyleManager *styleMgr) :
	m_widgetFactory(widgetFactory),
	m_styleMgr(styleMgr)
{

}

/*
 *
 */
fgGuiWidgetManager::~fgGuiWidgetManager()
{
	hmDataVecItor begin, end, itor;
	begin = getRefDataVector().begin(); end = getRefDataVector().end();
	itor = begin;
	for(;itor!=end;itor++) {
		if((*itor) == NULL)
			continue;

		delete (*itor);
		*itor = NULL;
	}
	fgHandleManager::clear();
	m_styleMgr = NULL;
	m_widgetFactory = NULL;
}

/*
 *
 */
fgGuiWidgetType fgGuiWidgetManager::widgetTypeFromName(const char *typeName)
{
	if(!typeName)
		return FG_GUI_WIDGET_UNKNOWN;
	return widgetTypeFromName(std::string(typeName));
}

/*
 *
 */
fgGuiWidgetType fgGuiWidgetManager::widgetTypeFromName(const std::string& typeName)
{
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
	}

	return FG_GUI_WIDGET_UNKNOWN;
}

/*
 *
 */
fgGuiWidgetManager::widgetVec& fgGuiWidgetManager::getRefRootWidgets(void)
{
	return m_rootWidgets;
}


/*
 *
 */
void fgGuiWidgetManager::setWidgetFactory(fgGuiWidgetFactory *widgetFactory) {
	m_widgetFactory = widgetFactory;
}

/*
 *
 */
fgGuiWidgetFactory *fgGuiWidgetManager::getWidgetFactory(void) const {
	return m_widgetFactory;
}

/*
 *
 */
void fgGuiWidgetManager::setStyleManager(fgGuiStyleManager *styleMgr) {
	m_styleMgr = styleMgr;
}

/*
 *
 */
fgGuiStyleManager *fgGuiWidgetManager::getStyleManager(void) const {
	return m_styleMgr;
}

/*
 *
 */
fgBool fgGuiWidgetManager::loadStructureSheet(const std::string& filePath)
{
	if(filePath.empty()) {
		return FG_FALSE;
	}
	return fgGuiWidgetManager::loadStructureSheet(filePath.c_str());
}

/*
 *
 */
fgBool fgGuiWidgetManager::loadStructureSheet(const char *filePath)
{
	if(!filePath) {
		return FG_FALSE;
	}
	fgXMLParser *xmlParser = new fgXMLParser();
	fgGuiStructureSheetParser *contentHandler = new fgGuiStructureSheetParser();
	
	contentHandler->setWidgetFactory(m_widgetFactory);
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

/*
 *
 */
fgBool fgGuiWidgetManager::addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, fgGuiWidget *pFatherWidget)
{
	if(!pWidget) {
		// Empty pointer - return
		FG_LOG::PrintError("WidgetManager: // Empty pointer - exit... no addition made");
		return FG_FALSE;
	}

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
			FG_LOG::PrintDebug("Widget '%s' of type '%s', has a father '%s' of type '%s'",
				pWidget->getNameStr(),
				pWidget->getTypeNameStr(),
				pFatherWidget->getNameStr(),
				pFatherWidget->getTypeNameStr());
		}
	}
	pWidget->setManaged(FG_TRUE);
	if(pFatherWidget)
		pFatherWidget->setManaged(FG_TRUE);
	if(m_styleMgr) {
		std::string styleName = pWidget->getStyleName();
		fgGuiStyle *style = m_styleMgr->get(styleName);
		if(style) {
			FG_LOG::PrintDebug("WidgetManager: Copying style to widget: '%s' of type: '%s'",
				pWidget->getNameStr(),
				pWidget->getTypeNameStr());

			style->copyFullContent(pWidget->getStyleContents(), 
				FG_GUI_WIDGET_STATE_COUNT,
				pWidget->getTypeName());
		}
	}
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGuiWidgetManager::addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, const fgGuiWidgetHandle& wFatherUniqueID)
{
	return addWidget(wUniqueID, pWidget, fgHandleManager::dereference(wFatherUniqueID));
}

/*
 *
 */
fgBool fgGuiWidgetManager::addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, const std::string& wFatherNameTag)
{
	return addWidget(wUniqueID, pWidget, fgHandleManager::dereference(wFatherNameTag));
}

/*
 *
 */
fgBool fgGuiWidgetManager::addWidget(fgGuiWidgetHandle& wUniqueID, fgGuiWidget *pWidget, const char* wFatherNameTag)
{
	return addWidget(wUniqueID, pWidget, fgHandleManager::dereference(wFatherNameTag));
}

/*
 *
 */
fgBool fgGuiWidgetManager::remove(fgGuiWidget *pWidget)
{
	if(!fgGuiWidgetManager::isManaged(pWidget)) {
		return FG_FALSE;
	}
	return fgHandleManager::releaseHandle(pWidget->getHandle());
}

/*
 *
 */
fgBool fgGuiWidgetManager::remove(const fgGuiWidgetHandle& wUniqueID)
{
	fgGuiWidget *pWidget = dereference(wUniqueID);
	if(!pWidget)
		return FG_FALSE;
	return fgHandleManager::releaseHandle(pWidget->getHandle());
}

/*
 *
 */
fgBool fgGuiWidgetManager::remove(const std::string& nameTag)
{
	fgGuiWidget *pWidget = dereference(nameTag);
	if(!pWidget)
		return FG_FALSE;
	return fgHandleManager::releaseHandle(pWidget->getHandle());
}

/*
 *
 */
fgBool fgGuiWidgetManager::remove(const char *nameTag)
{
	fgGuiWidget *pWidget = dereference(nameTag);
	if(!pWidget)
		return FG_FALSE;
	return fgHandleManager::releaseHandle(pWidget->getHandle());
}

/*
 *
 */
fgBool fgGuiWidgetManager::destroyWidget(fgGuiWidget*& pWidget)
{
	if(!fgGuiWidgetManager::remove(pWidget)) {
		return FG_FALSE;
	}
	delete pWidget;
	pWidget = NULL;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGuiWidgetManager::destroyWidget(const fgGuiWidgetHandle& wUniqueID)
{
	fgGuiWidget *pWidget = dereference(wUniqueID);
	if(!fgGuiWidgetManager::remove(pWidget)) {
		return FG_FALSE;
	}
	delete pWidget;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGuiWidgetManager::destroyWidget(const std::string& nameTag)
{
	fgGuiWidget *pWidget = dereference(nameTag);
	if(!fgGuiWidgetManager::remove(pWidget)) {
		return FG_FALSE;
	}
	delete pWidget;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGuiWidgetManager::destroyWidget(const char *nameTag)
{
	fgGuiWidget *pWidget = dereference(nameTag);
	if(!fgGuiWidgetManager::remove(pWidget)) {
		return FG_FALSE;
	}
	delete pWidget;
	return FG_TRUE;
}

/*
 *
 */
fgGuiWidget* fgGuiWidgetManager::get(const fgGuiWidgetHandle& wUniqueID)
{
	return fgHandleManager::dereference(wUniqueID);
}

/*
 *
 */
fgGuiWidget* fgGuiWidgetManager::get(const std::string& nameTag)
{
	return fgHandleManager::dereference(nameTag);
}

/*
 *
 */
fgGuiWidget* fgGuiWidgetManager::get(const char *nameTag)
{
	return fgHandleManager::dereference(nameTag);
}

/*
 *
 */
fgBool fgGuiWidgetManager::isManaged(fgGuiWidget *pWidget)
{
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

/*
 *
 */ 
fgBool fgGuiWidgetManager::isManaged(const fgGuiWidgetHandle& wUniqueID)
{
	fgGuiWidget *pWidget = get(wUniqueID);
	return (fgBool)(pWidget != NULL);
}

/*
 *
 */
fgBool fgGuiWidgetManager::isManaged(const std::string& nameTag)
{
	fgGuiWidget *pWidget = get(nameTag);
	return (fgBool)(pWidget != NULL);
}

/*
 *
 */
fgBool fgGuiWidgetManager::isManaged(const char *nameTag)
{
	fgGuiWidget *pWidget = get(nameTag);
	return (fgBool)(pWidget != NULL);
}
