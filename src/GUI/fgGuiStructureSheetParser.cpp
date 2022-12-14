/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
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
#include "Util/fgHashFunc.h"

using namespace fg;

gui::CStructureSheetParser::CStructureSheetParser() :
m_elemStack(),
m_widgetStack(),
m_widgetFactory(NULL),
m_widgetMgr(NULL),
m_isFailure(FG_FALSE),
m_count(0) { }

gui::CStructureSheetParser::~CStructureSheetParser() {
    while(!m_elemStack.empty())
        m_elemStack.pop();
    while(!m_widgetStack.empty())
        m_widgetStack.pop();
    m_widgetFactory = NULL;
    m_widgetMgr = NULL;
}

void gui::CStructureSheetParser::setWidgetFactory(CWidgetFactory *widgetFactory) {
    m_widgetFactory = widgetFactory;
}

gui::CWidgetFactory *gui::CStructureSheetParser::getWidgetFactory(void) const {
    return m_widgetFactory;
}

void gui::CStructureSheetParser::setWidgetManager(CWidgetManager *widgetMgr) {
    m_widgetMgr = widgetMgr;
}

gui::CWidgetManager *gui::CStructureSheetParser::getWidgetManager(void) const {
    return m_widgetMgr;
}

void gui::CStructureSheetParser::startDocument(fgXMLDocument *document) { }

Vector3f gui::CStructureSheetParser::parseSpatialData(const char *data,
                                                      gui::Unit& unit) {
    Vector3f out;
    if(!data)
        return out;

    unit = Unit::PIXELS;
    Unit tmpUnit = unit;
    fg::CStringVector parts;
    strings::split(std::string(data), ',', parts);

    if(parts.empty())
        return out;
    for(int i = 0; i < (int)parts.size(); i++) {
        float value = CStyleContent::parseLength(parts[i].c_str(), tmpUnit);
        if(tmpUnit != Unit::PIXELS)
            unit = tmpUnit;
        //float value = (float)atoi(parts[i].c_str());
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

fgBool gui::CStructureSheetParser::parseWidgetAttributes(CWidget *pWidget,
                                                         fgXMLAttribute *attribute) {
    if(!pWidget)
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
            Unit unit = Unit::PIXELS;
            Vector3f pos = parseSpatialData(attrvalue, unit);
            pWidget->setPosition(pos);
            if(unit != Unit::PERCENTS && unit != Unit::INVALID_UNIT) {
                pWidget->setRelativePos(pos);
            }
            /**
             * NONE,
             * FOCUS,
             * PRESSED,
             * ACTIVATED,
             * DEACTIVATED,
             * COUNT
             */
            pWidget->getStyleContent(CWidget::STATE_NONE).getPosition().unit = unit;
            pWidget->getStyleContent(CWidget::STATE_NONE).getPosition().set(pos);
            pWidget->getStyleContent(CWidget::STATE_FOCUS).getPosition().unit = unit;
            pWidget->getStyleContent(CWidget::STATE_FOCUS).getPosition().set(pos);
            pWidget->getStyleContent(CWidget::STATE_PRESSED).getPosition().unit = unit;
            pWidget->getStyleContent(CWidget::STATE_PRESSED).getPosition().set(pos);
            pWidget->getStyleContent(CWidget::STATE_ACTIVATED).getPosition().unit = unit;
            pWidget->getStyleContent(CWidget::STATE_ACTIVATED).getPosition().set(pos);
            pWidget->getStyleContent(CWidget::STATE_DEACTIVATED).getPosition().unit = unit;
            pWidget->getStyleContent(CWidget::STATE_DEACTIVATED).getPosition().set(pos);
        } else if(strcasecmp(attrname, "size") == 0) {
            Unit unit = Unit::PIXELS;
            Vector3f size = parseSpatialData(attrvalue, unit);
            pWidget->setSize(size, unit);            
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
        snprintf(_tmp, 23, "%d", m_count + rand() % 9000 + (m_count / rand() % 10));
        autoName.append("_").append(_tmp);

        snprintf(_tmp, 23, "%d", util::hash::SDBM(autoName.c_str()) % 200000 + util::hash::DEK(autoName.c_str()) % 30000); // #FIXME
        autoName.append("_").append(_tmp);
        pWidget->setName(autoName);
    }

    return FG_TRUE;
}

void gui::CStructureSheetParser::startElement(const char *localName,
                                              fgXMLElement *elementPtr,
                                              fgXMLNodeType nodeType,
                                              fgXMLAttribute *firstAttribute,
                                              int depth) {
    m_count++;
    m_elemStack.push(elementPtr);
    //printf("GUI ELEMENT START: %s | text: %s\n", localName, elementPtr->GetText());
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
    WidgetType widgetType = m_widgetMgr->widgetTypeFromName(localName);
    if(widgetType == WIDGET_UNKNOWN) {
        m_widgetStack.push(NULL);
        return;
    }
    if(!m_widgetFactory->isRegistered(widgetType)) {
        m_widgetStack.push(NULL);
        return;
    }

    CWidget *pWidget = m_widgetFactory->create(widgetType);
    if(!pWidget) {
        m_widgetStack.push(NULL);
        return;
    }
    if(!parseWidgetAttributes(pWidget, firstAttribute)) {
        delete pWidget;
        m_widgetStack.push(NULL);
        return;
    }
    CWidget *pFatherWidget = NULL;
    CContainer *pFatherContainer = NULL;
    if(m_widgetStack.size() >= 1) {
        pFatherWidget = m_widgetStack.top();
        if(pFatherWidget) {
            if(pFatherWidget->getTypeTraits() & CONTAINER) {
                pFatherContainer = (CContainer *)pFatherWidget;
                pFatherContainer->addChild(pWidget);
                pWidget->setFather(pFatherWidget);
            }
        }
    }
    // Adding widget to the manager updates it's style
    if(!m_widgetMgr->addWidget(pWidget, pFatherWidget)) {
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

void gui::CStructureSheetParser::endElement(const char *localName,
                                            fgXMLElement *elementPtr,
                                            fgXMLNodeType nodeType,
                                            int depth) {
    m_elemStack.pop();
    if(m_isFailure)
        return;
    //printf("GUI ELEMENT END: %s\n", localName);
    if(!m_widgetStack.empty()) {
        fg::gui::CWidget *pWidget = m_widgetStack.top();
        if(pWidget) {
            // Is this really necessary?
            pWidget->updateBounds();
        }
        m_widgetStack.pop();
    }
}

void gui::CStructureSheetParser::characters(const char *ch,
                                            int start,
                                            int length,
                                            fgXMLNodeType nodeType,
                                            int depth) {
    if(m_isFailure || !ch)
        return;
    if(nodeType == fgXMLNode::TINYXML_TEXT && !m_widgetStack.empty()) {
        fg::gui::CWidget *pWidget = m_widgetStack.top();
        if(!pWidget)
            return;
        //printf("characters: This node is a text: %s\n", ch);
        pWidget->setText(ch);
    }
}

void gui::CStructureSheetParser::endDocument(fgXMLDocument *document) { }
