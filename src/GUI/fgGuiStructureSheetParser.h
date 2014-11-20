/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_STRUCTURE_SHEET_PARSER
    #define FG_INC_GUI_STRUCTURE_SHEET_PARSER

    #include "XML/fgXMLParser.h"
    #include "XML/fgXMLDefaultHandler.h"

    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactory.h"
    #include "fgGuiWidgetManager.h"

    #define FG_GUI_STRUCTURE_SHEET_ROOT_NODE "GUIStructure"

/*
 *
 */
class fgGuiStructureSheetParser : public fgXMLDefaultHandler {
    friend class fgGuiWidgetManager;
    friend class fgGuiMain;

private:
    ///
    std::stack<fgXMLElement *> m_elemStack;
    ///
    std::stack<fgGuiWidget *> m_widgetStack;
    ///
    fgGuiWidgetFactory *m_widgetFactory;
    ///
    fgGuiWidgetManager *m_widgetMgr;
    ///
    fgBool m_isFailure;
    ///
    int m_count;
protected:
    // Base constructor of the resource group content handler object
    fgGuiStructureSheetParser();
    // Base destructor of the resource group content handler object
    virtual ~fgGuiStructureSheetParser();

protected:
    //
    void setWidgetFactory(fgGuiWidgetFactory *widgetFactory);
    //
    fgGuiWidgetFactory *getWidgetFactory(void) const;
    //
    void setWidgetManager(fgGuiWidgetManager *widgetMgr);
    //
    fgGuiWidgetManager *getWidgetManager(void) const;
    //
    fgBool parseWidgetAttributes(fgGuiWidget *pWidget, fgXMLAttribute *attribute);
    //
    static fgVector3f parseSpatialData(const char *data);
public:
    // Receive notification of the end of the document.
    virtual void endDocument(fgXMLDocument *document);

    // Receive notification of the end of an element.
    virtual void endElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, int depth = 0);

    // Receive notification of the beginning of the document.
    virtual void startDocument(fgXMLDocument *document);

    // Receive notification of the start of an element.
    virtual void startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth = 0);

    // Receive notification of character data inside an element or comment
    virtual void characters(const char *ch, int start, int length, fgXMLNodeType nodeType, int depth = 0);
};

#endif /* FG_INC_GUI_STRUCTURE_SHEET_PARSER */
