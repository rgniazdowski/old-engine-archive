/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_XML_DEFAULT_HANDLER
    #define FG_INC_XML_DEFAULT_HANDLER
    #define FG_INC_XML_DEFAULT_HANDLER_BLOCK

    #include "fgXMLTypesWrap.h"

namespace fg {
    namespace xml {

        /**
         *
         */
        class CDefaultHandler {
        protected:
            /**
             * 
             */
            CDefaultHandler() { }
            /**
             * 
             */
            virtual ~CDefaultHandler() { }

        public:
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
                                    int depth = 0) { }

            /**
             * Receive notification of the end of the document.
             * @param document
             */
            virtual void endDocument(fgXMLDocument *document) = 0;

            /**
             * Receive notification of the end of an element
             * @param localName
             * @param elementPtr
             * @param nodeType
             * @param depth
             */
            virtual void endElement(const char *localName,
                                    fgXMLElement *elementPtr,
                                    fgXMLNodeType nodeType,
                                    int depth = 0) = 0;
            // Receive notification of a recoverable parser error.
            //void error(exception e)
            // Report a fatal XML parsing error.
            //void fatalError(exception e)
            /**
             * Receive notification of ignorable whitespace in element content.
             * @param ch
             * @param start
             * @param length
             */
            virtual void ignorableWhitespace(char *ch,
                                             int start,
                                             int length) { }

            /**
             * Receive notification of the beginning of the document.
             * @param document
             */
            virtual void startDocument(fgXMLDocument *document) = 0;

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
                                      int depth = 0) = 0;
            // Receive notification of a parser warning.
            //void warning(exception e); // #FIXME - the whole error reporting system...
        };
    };
};

    #undef FG_INC_XML_DEFAULT_HANDLER_BLOCK
#endif /* FG_INC_XML_DEFAULT_HANDLER */
