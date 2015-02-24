/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_XML_PARSER
    #define FG_INC_XML_PARSER
    #define FG_INC_XML_PARSER_BLOCK

    #ifndef FG_INC_XML_TYPES_WRAP
        #include "fgXMLTypesWrap.h"
    #endif 

    #include <string>
    #include <cstring>
    #include <stack>

    #include "fgStatus.h"
    #include "Util/fgFile.h"

    #include "fgXMLDefaultHandler.h"

namespace fg {
    namespace xml {
        class CParser;
    };
};

    #define FG_TAG_XML_PARSER_NAME	"XMLParser"
    #define FG_TAG_XML_PARSER		FG_TAG_TYPE(fg::xml::CParser)
FG_TAG_TEMPLATE_ID_AUTO(fg::xml::CParser, FG_TAG_XML_PARSER_NAME);

/** TiXmlBase is a base class for every class in TinyXml.
        It does little except to establish that TinyXml classes
        can be printed and provide some utility functions.

        In XML, the document and elements can contain
        other elements and other types of nodes.

        A Document can contain:	Element	(container or leaf)
                                                        Comment (leaf)
                                                        Unknown (leaf)
                                                        Declaration( leaf )

        An Element can contain:	Element (container or leaf)
                                                        Text	(leaf)
                                                        Attributes (not on tree)
                                                        Comment (leaf)
                                                        Unknown (leaf)

        A Declaration contains: Attributes (not on tree)
 */

namespace fg {
    namespace xml {
        
        ///
        typedef FG_TAG_XML_PARSER XMLParserTag;

        /**
         * This class extends the fgFile, so it can load the proper XML file
         * fgXMLParser contains  specialized functions for  parsing/interpreting the  data inside the XML file, its
         * a kind of a XML functions wrapper to make it easier and more intuitive to interpret and extract the data
         */
        class CParser : protected util::DataFile {
        public:
            ///
            typedef fg::util::DataFile base_type;
            ///
            typedef XMLParserTag tag_type;
            
        protected:
            /// Loaded file size
            unsigned int m_fileSize;
            /// Data buffer
            char *m_fileBuffer;
            /// Structure for holding info about the whole document
            fgXMLDocument m_xmlDocument;
            /// Pointer to XML files' root node
            fgXMLElement *m_rootXMLElement;
            /// Pointer to the current node (seek position)
            fgXMLNode *m_currentXMLNode;
            /// Pointer to the current attribute (seek position)
            fgXMLAttribute *m_currentXMLAttribute;
            /// On this stack current nodes are being placed before the parser goes deeper (into the nodes children)
            std::stack<fgXMLNode *> m_parsingStack;
            /// Pointer to the interface object used for automatic parsing of the XML file (handler)
            CDefaultHandler *m_contentHandler;

        public:
            /**
             * Default empty constructor
             */
            CParser() : m_fileSize(0), m_fileBuffer(NULL), m_xmlDocument(),
            m_rootXMLElement(NULL), m_currentXMLNode(NULL),
            m_currentXMLAttribute(NULL), m_parsingStack(), m_contentHandler(NULL) { }
            /**
             * Constructor with file path parameter - loads the xml file
             * @param filePath
             */
            CParser(const char *filePath) : fg::util::DataFile(filePath), m_fileSize(0), m_fileBuffer(NULL), m_xmlDocument(),
            m_rootXMLElement(NULL), m_currentXMLNode(NULL),
            m_currentXMLAttribute(NULL), m_parsingStack(),
            m_contentHandler(NULL) {
                loadXML(filePath);
            }
            /*
             * Destructor - frees all data
             */
            virtual ~CParser() {
                freeXML();
            }

            /**
             * 
             * @param filePath
             * @return 
             */
            fgBool loadXML(const char *filePath);

            /**
             * Frees the structures holding all of the xml data
             */
            void freeXML(void);
            /**
             * Stores the pointer to the object for content event handling.
             * This handler is managed outside of this class.
             */
            fgBool setContentHandler(fg::xml::CDefaultHandler *contentHandler) {
                if(contentHandler)
                    m_contentHandler = contentHandler;
                else
                    return FG_FALSE;
                return FG_TRUE;
            }
            /**
             * Returns the pointer to content handler (used for automatic parsing).
             * NULL if not set - no automatic parsing possible.
             * @return 
             */
            fg::xml::CDefaultHandler *getContentHandler(void) const {
                return m_contentHandler;
            }

            /**
             * Parse (analyze) the xml file using predefined content handler.
             * @return 
             */
            fgBool parseWithHandler(void);

        private:
            /**
             * 
             * @param cnode
             * @param depth
             * @return 
             */
            fgBool private_parseDeep(fgXMLNode *cnode = NULL, int depth = 0);

        public:
            /**
             * Check if XML is loaded
             * @return
             */
            fgBool isXMLLoaded(void) const {
                if(m_rootXMLElement)
                    return FG_TRUE;
                else
                    return FG_FALSE;
            }
            /**
             * Returns the root node of the xml file
             * @return 
             */
            fgXMLElement *getRootElement(void) const {
                return m_rootXMLElement;
            }
            /**
             * Returns the root element value (string)
             * @return 
             */
            const char *getRootElementValue(void) const {
                if(!m_rootXMLElement)
                    return NULL;
                return m_rootXMLElement->Value();
            }
            /**
             * Returns the current node (seek position)
             * @return 
             */
            fgXMLNode *getCurrentNode(void) const {
                return m_currentXMLNode;
            }
            /**
             * Returns the current attribute (seek position)
             * @return 
             */
            fgXMLAttribute *getCurrentAttribute(void) const {
                return m_currentXMLAttribute;
            }
            /**
             * Returns the current attribute name
             * @return 
             */
            const char *getCurrentAttributeName(void) const {
                if(!m_currentXMLAttribute)
                    return NULL;
                return m_currentXMLAttribute->Name();
            }
            /*
             * Returns the current attribute value
             */
            const char *getCurrentAttributeValue(void) const {
                if(!m_currentXMLAttribute)
                    return NULL;
                return m_currentXMLAttribute->Value();
            }
            /**
             * Checks for the nodes children
             * @return
             */
            fgBool getCurrentNodeChildrenPresence(void) const {
                if(!m_currentXMLNode) {
                    if(m_rootXMLElement)
                        return !m_rootXMLElement->NoChildren();
                    return FG_FALSE;
                }
                return !m_currentXMLNode->NoChildren();
            }
            /**
             * Returns the current node value
             * @return
             */
            const char *getCurrentNodeValue(void) const {
                if(!m_currentXMLNode)
                    return NULL;
                if(m_currentXMLNode->Type() != fgXMLNode::TINYXML_TEXT)
                    return m_currentXMLNode->Value();
                else
                    return getCurrentTextNodeValue();
            }
            /**
             * 
             * @return 
             */
            const char *getCurrentTextNodeValue(void) const {
                if(!m_currentXMLNode)
                    return NULL;
                if(m_currentXMLNode->Type() != fgXMLNode::TINYXML_TEXT)
                    return NULL;
                fgXMLText *textNode = m_currentXMLNode->ToText();
                if(!textNode)
                    return NULL;
                return textNode->Value();
            }
            /**
             * Checks is there any current node/element in the seek position
             * @return
             */
            fgBool isCurrent(void) const {
                if(!m_currentXMLNode)
                    return FG_FALSE;
                else
                    return FG_TRUE;
            }
            /**
             * Checks if the current pointer points to XML Element
             * @return
             */
            fgBool isCurrentElement(void) const {
                if(!m_currentXMLNode)
                    return FG_FALSE;
                return (m_currentXMLNode->Type() == fgXMLNode::TINYXML_ELEMENT);
            }
            /**
             * Checks if the current pointer points to XML Text
             * @return
             */
            fgBool isCurrentText(void) const {
                if(!m_currentXMLNode)
                    return FG_FALSE;
                return (m_currentXMLNode->Type() == fgXMLNode::TINYXML_TEXT);
            }
            /**
             * Checks if the current pointer points to XML Comment
             * @return
             */
            fgBool isCurrentComment(void) const {
                if(!m_currentXMLNode)
                    return FG_FALSE;
                return (m_currentXMLNode->Type() == fgXMLNode::TINYXML_COMMENT);
            }
            /**
             * Checks if the current pointer points to unknown xml node type
             * @return
             */
            fgBool isCurrentUnknown(void) const {
                if(!m_currentXMLNode)
                    return FG_FALSE;
                return (m_currentXMLNode->Type() == fgXMLNode::TINYXML_UNKNOWN);
            }
            /**
             * Sets the attribute pointer to the first possible attribute in the current node
             * @return
             */
            fgBool setFirstAttribute(void) {
                if(!m_currentXMLNode) {
                    if(!m_rootXMLElement)
                        return FG_FALSE;
                    m_currentXMLAttribute = m_rootXMLElement->FirstAttribute();
                    if(m_currentXMLAttribute == NULL)
                        return FG_FALSE;
                    return FG_TRUE;
                }
                if(!isCurrentElement()) {
                    return FG_FALSE;
                }
                fgXMLElement *xmlElement = m_currentXMLNode->ToElement();
                if(!xmlElement) {
                    return FG_FALSE;
                }
                m_currentXMLAttribute = xmlElement->FirstAttribute();
                if(m_currentXMLAttribute == NULL) {
                    return FG_FALSE;
                }
                return FG_TRUE;
            }
            /**
             * Parser goes deeper into the xml document structure, setting proper value for the current pointer
             * @return
             */
            fgBool goDeeper(void) {
                if(!m_currentXMLNode) {
                    if(!m_rootXMLElement)
                        return FG_FALSE;
                    m_currentXMLNode = m_rootXMLElement->FirstChild();
                    if(!m_currentXMLNode) {
                        return FG_FALSE;
                    } else {
                        m_currentXMLAttribute = NULL;
                        return FG_TRUE;
                    }
                }

                if(m_currentXMLNode->NoChildren()) {
                    return FG_FALSE;
                }

                m_parsingStack.push(m_currentXMLNode);
                m_currentXMLNode = m_currentXMLNode->FirstChild();
                m_currentXMLAttribute = NULL;
                return FG_TRUE;
            }
            /**
             * Parser goes higher (back) in the xml document structure
             * @return
             */
            fgBool goHigher(void) {
                if(m_parsingStack.empty())
                    return FG_FALSE;
                m_currentXMLNode = m_parsingStack.top();
                m_parsingStack.pop();
                if(!m_currentXMLNode)
                    return FG_FALSE;
                m_currentXMLAttribute = NULL;
                return FG_TRUE;
            }
            /**
             * Parser goes to the next node (next sibling)
             * @return
             */
            fgBool goToNextNode(void) {
                if(!m_currentXMLNode)
                    return FG_FALSE;
                m_currentXMLNode = m_currentXMLNode->NextSibling();
                if(m_currentXMLNode)
                    return FG_TRUE;
                else
                    return FG_FALSE;
            }
            /**
             * Parser goes to the previous node (previous sibling)
             * @return
             */
            fgBool goToPreviousNode(void) {
                if(!m_currentXMLNode)
                    return FG_FALSE;
                m_currentXMLNode = m_currentXMLNode->PreviousSibling();
                if(m_currentXMLNode)
                    return FG_TRUE;
                else
                    return FG_FALSE;
            }
            /**
             * Parser goes to the next attribute
             * @return
             */
            fgBool goToNextAttribute(void) {
                if(!m_currentXMLAttribute)
                    return FG_FALSE;
                m_currentXMLAttribute = m_currentXMLAttribute->Next();
                if(m_currentXMLAttribute)
                    return FG_TRUE;
                else
                    return FG_FALSE;
            }
            /**
             * Parser goes to the previous attribute
             * @return
             */
            fgBool goToPreviousAttribute(void) {
                if(!m_currentXMLAttribute)
                    return FG_FALSE;
                m_currentXMLAttribute = m_currentXMLAttribute->Previous();
                if(m_currentXMLAttribute)
                    return FG_TRUE;
                else
                    return FG_FALSE;
            }
        };
    };
};

    #undef FG_INC_XML_PARSER_BLOCK
#endif /* FG_INC_XML_PARSER */
