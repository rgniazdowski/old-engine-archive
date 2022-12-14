/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgXMLParser.h"
#include "fgXMLErrorCodes.h"
#include "Util/fgFileErrorCodes.h"
#include "Util/fgMemory.h"
#include "fgMessageSubsystem.h"

using namespace fg;

/*
 *
 */
fgBool xml::CParser::loadXML(const char *filePath) {
    if(filePath == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return FG_FALSE;
    }

    // Clear previously parsed XML document
    m_xmlDocument.ClearError();
    m_xmlDocument.Clear();

    m_fileBuffer = load(filePath);

    if(!m_fileBuffer) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_XML_LOAD);
        return FG_FALSE;
    }

    // Close the file
    close();
    //FG_LOG_DEBUG("XMLParser: FileBuffer: '%s'", m_fileBuffer);
    // Process the XML raw data
    if(!m_xmlDocument.Parse(m_fileBuffer)) {
        if(m_xmlDocument.Error()) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_XML_PARSE, "id: %d - %s in line (%d,%d)",
                        m_xmlDocument.ErrorId(), m_xmlDocument.ErrorDesc(),
                        m_xmlDocument.ErrorRow(), m_xmlDocument.ErrorCol());
        } else {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_XML_PARSE);
        }
        return FG_FALSE;
    }
    fgFree(m_fileBuffer);
    m_fileBuffer = NULL;

    // Set the root element
    m_rootXMLElement = m_xmlDocument.FirstChildElement();
    if(!m_rootXMLElement) {
        FG_LOG_DEBUG("XMLParser: Root XML element is NULL");
    }
    return FG_TRUE;
}

/*
 * Frees all data stored
 */
void xml::CParser::freeXML(void) {
    if(m_fileBuffer) {
        fgFree(m_fileBuffer);
    }
    m_fileBuffer = NULL;
    m_fileSize = FG_FALSE;
    m_xmlDocument.ClearError();
    m_xmlDocument.Clear();
    m_rootXMLElement = NULL;
    m_currentXMLNode = NULL;
    m_contentHandler = NULL;
    m_currentXMLAttribute = NULL;
    while(!m_parsingStack.empty()) {
        m_parsingStack.pop();
    }
}

/*
 * Helper function (private) used for deep xml parsing with content handler.
 * Well its used in recursive way, in the future this should be avoided
 * For now however (because of the XMLParser function) it is almost impossible
 * to make such function without recursion. #FIXME #TODO #P4
 */
fgBool xml::CParser::private_parseDeep(fgXMLNode *cnode, int depth) {
    if(!cnode) {
        fgXMLAttribute *firstAttribute = NULL;
        fgXMLElement *elementPtr = NULL;
        // Retrieve the root's node name
        const char *rootName = this->getRootElementValue();
        if(!rootName)
            return FG_FALSE;
        if(this->setFirstAttribute())
            firstAttribute = this->getCurrentAttribute();
        elementPtr = this->getRootElement();
        // Call start element for the very first element in the XML tree - root node
        this->m_contentHandler->startElement(rootName, elementPtr, (fgXMLNodeType)elementPtr->Type(), firstAttribute, depth);
    }
    // Parsing children nodes
    if(this->getCurrentNodeChildrenPresence()) {
        fgXMLAttribute *firstAttribute = NULL;
        fgXMLElement *elementPtr = NULL;
        this->goDeeper();
        depth++;
        do {
            if(this->setFirstAttribute())
                firstAttribute = this->getCurrentAttribute();
            const char *currentNodeValue = this->getCurrentNodeValue();
            elementPtr = this->getCurrentNode()->ToElement();
            if(this->isCurrentElement()) {
                // Handlers function for properly handling begining of the element
                this->m_contentHandler->startElement(currentNodeValue, elementPtr, (fgXMLNodeType)elementPtr->Type(), firstAttribute, depth);
                // Go deeper in the parsing tree
                this->private_parseDeep(this->getCurrentNode(), (depth));
                // Handle end of the element
                this->m_contentHandler->endElement(currentNodeValue, elementPtr, (fgXMLNodeType)elementPtr->Type(), depth);
            } else if(this->isCurrentText() || this->isCurrentComment()) {
                // This will be probably comment element or text between tags (start / end)
                this->m_contentHandler->characters(currentNodeValue, 0, strlen(currentNodeValue), (fgXMLNodeType)m_currentXMLNode->Type(), depth);
            }
        } while(this->goToNextNode());
        this->goHigher();
        depth--;
    } else {
        // #FIXME
    }
    if(!cnode) {
        fgXMLElement *elementPtr = NULL;
        // Retrieve the root's node name
        const char *rootName = this->getRootElementValue();
        if(!rootName)
            return FG_FALSE;
        elementPtr = this->getRootElement();
        this->m_contentHandler->endElement(rootName, elementPtr, (fgXMLNodeType)elementPtr->Type(), depth);
    }
    return FG_TRUE;
}

/*
 * Parse (analyze) the xml file using predefined content handler.
 */
fgBool xml::CParser::parseWithHandler(void) {
    if(!m_contentHandler) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_XML_NO_CONTENT_HANDLER);
        return FG_FALSE;
    }
    std::stack<fgXMLNode *> toVisitStack;

    // Parsing XML using content handler class
    if(!this->isXMLLoaded()) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_XML_NOT_LOADED);
        return FG_FALSE;
    }
    // Start document parsing
    m_contentHandler->startDocument(&this->m_xmlDocument);
    // Start deep parsing #FIXME
    fgBool pstatus = private_parseDeep(NULL, 0);
    if(!pstatus) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_XML_PARSE_DEEP);
        return FG_FALSE;
    }
    m_contentHandler->endDocument(&this->m_xmlDocument);
    return FG_TRUE;
}
