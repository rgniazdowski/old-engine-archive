/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStructureSheetParser.h"
#include "fgGuiWidgetFactory.h"
#include "fgGuiWidget.h"
#include "fgGuiContainer.h"

#include "Util/fgStrings.h"

/*
 *
 */
fgGuiStructureSheetParser::fgGuiStructureSheetParser() :
m_elemStack(),
m_widgetStack(),
m_widgetFactory(NULL),
m_widgetMgr(NULL),
m_isFailure(FG_FALSE),
m_count(0) { }

/*
 *
 */
fgGuiStructureSheetParser::~fgGuiStructureSheetParser() {
    while(!m_elemStack.empty())
        m_elemStack.pop();
    while(!m_widgetStack.empty())
        m_widgetStack.pop();
    m_widgetFactory = NULL;
    m_widgetMgr = NULL;
}

/*
 *
 */
void fgGuiStructureSheetParser::setWidgetFactory(fgGuiWidgetFactory *widgetFactory) {
    m_widgetFactory = widgetFactory;
}

/*
 *
 */
fgGuiWidgetFactory *fgGuiStructureSheetParser::getWidgetFactory(void) const {
    return m_widgetFactory;
}

/*
 *
 */
void fgGuiStructureSheetParser::setWidgetManager(fgGuiWidgetManager *widgetMgr) {
    m_widgetMgr = widgetMgr;
}

/*
 *
 */
fgGuiWidgetManager *fgGuiStructureSheetParser::getWidgetManager(void) const {
    return m_widgetMgr;
}

/*
 *
 */
void fgGuiStructureSheetParser::startDocument(fgXMLDocument *document) { }

/*
 *
 */
fgVector3f fgGuiStructureSheetParser::parseSpatialData(const char *data) {
    fgVector3f out;
    if(!data)
        return out;

    fgStringVector parts;
    fgStrings::split(std::string(data), ',', parts);

    if(parts.empty())
        return out;
    for(int i = 0; i < (int)parts.size(); i++) {
        float value = (float)atoi(parts[i].c_str());
        switch(i) {
            case 0:
                out.x = value;
                break;
            case 1:
                out.y = value;
                break;
            case 2:
                out.z = value;
                break;
        };
    }
    return out;
}

/*
 *
 */
fgBool fgGuiStructureSheetParser::parseWidgetAttributes(fgGuiWidget *pWidget, fgXMLAttribute *attribute) {
    if(!pWidget || !attribute)
        return FG_FALSE;

    fgBool hasName = FG_FALSE;

    while(attribute) {
        const char *attrname = attribute->Name();
        const char *attrvalue = attribute->Value();
        if(strcasecmp(attrname, "name") == 0) {
            pWidget->setName(attrvalue);
            hasName = FG_TRUE;
        } else if(strcasecmp(attrname, "flags") == 0) {
            // This can be special field, it'll be a string
            // which cointains widget specific parameters
            // Given widget will parse it properly
            pWidget->setFlags(attrvalue);
        } else if(strcasecmp(attrname, "active") == 0) {
            pWidget->setActive(FG_BOOL_FROM_TEXT(attrvalue));
        } else if(strcasecmp(attrname, "visible") == 0) {
            pWidget->setVisible(FG_BOOL_FROM_TEXT(attrvalue));
        } else if(strcasecmp(attrname, "ignoreState") == 0) {
            pWidget->setIgnoreState(FG_BOOL_FROM_TEXT(attrvalue));
        } else if(strcasecmp(attrname, "pos") == 0 || strcasecmp(attrname, "position") == 0) {
            fgVector3f pos = parseSpatialData(attrvalue);
            pWidget->setPosition(pos);
            pWidget->setRelativePos(pos);
        } else if(strcasecmp(attrname, "size") == 0) {
            fgVector3f size = parseSpatialData(attrvalue);
            pWidget->setSize(size);
        } else if(strcasecmp(attrname, "link") == 0) {
            pWidget->setLink(attrvalue);
        } else if(strcasecmp(attrname, "action") == 0) {
            pWidget->setAction(attrvalue);
        } else if(strcasecmp(attrname, "script") == 0) {
            pWidget->setScript(attrvalue);
        } else if(strcasecmp(attrname, "config") == 0) {
            pWidget->setConfig(attrvalue);
        } else if(strcasecmp(attrname, "style") == 0) {
            pWidget->setStyleName(attrvalue);
        }
        attribute = attribute->Next();
    }

    if(!hasName) {
        std::string autoName = pWidget->getTypeName();
        char _tmp[24];
        memset(_tmp, 0, 24);
        snprintf(_tmp, 23, "%d", m_count + rand() % 3);
        autoName.append("_").append(_tmp);
        snprintf(_tmp, 23, "%d", __FG_TAG::_fg_tag_s_hashfn(autoName.c_str())); // #FIXME
        autoName.append("_").append(_tmp);
    }

    return FG_TRUE;
}

/*
 *
 */
void fgGuiStructureSheetParser::startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth) {
    m_count++;
    m_elemStack.push(elementPtr);
    printf("GUI ELEMENT START: %s | text: %s\n", localName, elementPtr->GetText());
    if(strcasecmp(localName, FG_GUI_STRUCTURE_SHEET_ROOT_NODE) == 0 && depth == 0) {
        return;
    } else if(depth == 0) {
        m_isFailure = FG_TRUE;
        return;
    }
    if(m_isFailure) {
        return;
    }
    if(!m_widgetFactory || !m_widgetMgr) {
        m_widgetStack.push(NULL);
        return;
    }

    std::string widgetTypeName = localName;
    fgGuiWidgetType widgetType = m_widgetMgr->widgetTypeFromName(localName);
    if(widgetType == FG_GUI_WIDGET_UNKNOWN) {
        m_widgetStack.push(NULL);
        return;
    }
    if(!m_widgetFactory->isRegistered(widgetType)) {
        m_widgetStack.push(NULL);
        return;
    }

    fgGuiWidget *pWidget = m_widgetFactory->createWidget(widgetType);
    if(!pWidget) {
        m_widgetStack.push(NULL);
        return;
    }
    if(!parseWidgetAttributes(pWidget, firstAttribute)) {
        delete pWidget;
        m_widgetStack.push(NULL);
        return;
    }
    fgGuiWidget *pFatherWidget = NULL;
    fgGuiContainer *pFatherContainer = NULL;
    if(m_widgetStack.size() >= 1) {
        pFatherWidget = m_widgetStack.top();
        if(pFatherWidget) {
            if(pFatherWidget->getTypeTraits() & FG_GUI_CONTAINER) {
                pFatherContainer = (fgGuiContainer *)pFatherWidget;
                pFatherContainer->addChild(pWidget);
                pWidget->setFather(pFatherWidget);
            }
        }
    }
    if(!m_widgetMgr->addWidget(pWidget->getRefHandle(), pWidget, pFatherWidget)) {
        if(pFatherWidget && pFatherContainer) {
            pFatherContainer->removeChild(pWidget);
        }
        delete pWidget;
        pWidget = NULL;
    }
    // Update widgets style; there probably should be specific code for that in
    // widget manager; special function that will initialize widgets style after
    // adding in into the structure;
    // Also, widget maybe should have special tag if it is managed inside the
    // widget manager.  #DONE
    // If widget is managed then for example container in destructor 
    // should not delete children
    m_widgetStack.push(pWidget);
}

/*
 *
 */
void fgGuiStructureSheetParser::endElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, int depth) {
    m_elemStack.pop();
    if(m_isFailure)
        return;
    printf("GUI ELEMENT END: %s\n", localName);
    if(!m_widgetStack.empty()) {
        fgGuiWidget *pWidget = m_widgetStack.top();
        if(pWidget) {
            // Is this really necessary?
            pWidget->updateSize();
        }
        m_widgetStack.pop();
    }
}

/*
 *
 */
void fgGuiStructureSheetParser::characters(const char *ch, int start, int length, fgXMLNodeType nodeType, int depth) {
    if(m_isFailure || !ch)
        return;
    if(nodeType == fgXMLNode::TINYXML_TEXT && !m_widgetStack.empty()) {
        fgGuiWidget *pWidget = m_widgetStack.top();
        if(!pWidget)
            return;
        printf("characters: This node is a text: %s\n", ch);
        pWidget->setText(ch);
    }
}

/*
 *
 */
void fgGuiStructureSheetParser::endDocument(fgXMLDocument *document) { }
