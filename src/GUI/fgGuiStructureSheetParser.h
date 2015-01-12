/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_STRUCTURE_SHEET_PARSER
    #define FG_INC_GUI_STRUCTURE_SHEET_PARSER
    #define FG_INC_GUI_STRUCTURE_SHEET_PARSER_BLOCK

    #include "XML/fgXMLParser.h"
    #include "XML/fgXMLDefaultHandler.h"

    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactory.h"
    #include "fgGuiWidgetManager.h"

    #define FG_GUI_STRUCTURE_SHEET_ROOT_NODE "GUIStructure"

namespace fg {
    namespace gui {

        class CGuiMain;
        class CWidgetManager;

        /**
         *
         */
        class CStructureSheetParser : public fg::xml::CDefaultHandler {
            friend class fg::gui::CWidgetManager;
            friend class fg::gui::CGuiMain;

        private:
            ///
            std::stack<fgXMLElement *> m_elemStack;
            ///
            std::stack<CWidget *> m_widgetStack;
            ///
            CWidgetFactory *m_widgetFactory;
            ///
            CWidgetManager *m_widgetMgr;
            ///
            fgBool m_isFailure;
            ///
            int m_count;

        protected:
            /**
             * Base constructor of the resource group content handler object
             */
            CStructureSheetParser();
            /**
             * Destructor of the resource group content handler object
             */
            virtual ~CStructureSheetParser();

        protected:
            /**
             * 
             * @param widgetFactory
             */
            void setWidgetFactory(CWidgetFactory *widgetFactory);
            /**
             * 
             * @return 
             */
            CWidgetFactory *getWidgetFactory(void) const;
            /**
             * 
             * @param widgetMgr
             */
            void setWidgetManager(CWidgetManager *widgetMgr);
            /**
             * 
             * @return 
             */
            CWidgetManager *getWidgetManager(void) const;
            /**
             * 
             * @param pWidget
             * @param attribute
             * @return 
             */
            fgBool parseWidgetAttributes(CWidget *pWidget, fgXMLAttribute *attribute);
            /**
             * 
             * @param data
             * @return 
             */
            static Vector3f parseSpatialData(const char *data);

        public:
            /**
             * Receive notification of the end of the document.
             * @param document
             */
            virtual void endDocument(fgXMLDocument *document);

            /**
             * Receive notification of the end of an element.
             * @param localName
             * @param elementPtr
             * @param nodeType
             * @param depth
             */
            virtual void endElement(const char *localName,
                                    fgXMLElement *elementPtr,
                                    fgXMLNodeType nodeType,
                                    int depth = 0);

            /**
             * Receive notification of the beginning of the document.
             * @param document
             */
            virtual void startDocument(fgXMLDocument *document);

            /**
             * Receive notification of the start of an element.
             * @param localName
             * @param elementPtr
             * @param nodeType
             * @param firstAttribute
             * @param depth
             */
            virtual void startElement(const char *localName,
                                      fgXMLElement *elementPtr,
                                      fgXMLNodeType nodeType,
                                      fgXMLAttribute *firstAttribute,
                                      int depth = 0);

            /**
             * Receive notification of character data inside an element or comment
             * @param ch
             * @param start
             * @param length
             * @param nodeType
             * @param depth
             */
            virtual void characters(const char *ch,
                                    int start,
                                    int length,
                                    fgXMLNodeType nodeType,
                                    int depth = 0);
        };
    };
};

    #undef FG_INC_GUI_STRUCTURE_SHEET_PARSER_BLOCK
#endif /* FG_INC_GUI_STRUCTURE_SHEET_PARSER */
