/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgXMLParser.h"
#include "fgMemory.h"

/*
 *
 */
bool fgXMLParser::loadXML(const char *filePath)
{
	if(filePath == NULL) {
		// #FIXME proper error message
		return false;
	}

	if(!fileExists(filePath)) {
		// #FIXME proper error message
		return false;
	}
	
	// Clear previously parsed XML document
	m_xmlDocument.ClearError();
	m_xmlDocument.Clear();

	if(!openFile(filePath, "r")) {
		return false;
	}

	if(!isFileLoaded()) {
		return false;
	}

	// Get the XML file size in bytes
	m_fileSize = getSize();
	if(m_fileSize < 4) { // it could be any number basically, just checking if the file isnt too small
		closeFile();
		return false;
	}

	// Read the XML data
	m_fileBuffer = (char *) fgMalloc(sizeof(char)*(m_fileSize+1));
	if(m_fileBuffer == NULL) {
		// ERROR
		return false;
	}
	int bytesRead = readFile(m_fileBuffer, 1, m_fileSize);
	m_fileBuffer[m_fileSize] = '\0';
	if(bytesRead != m_fileSize) {
		fgFree(m_fileBuffer);
		m_fileBuffer = NULL;
		m_fileSize = 0;
		closeFile();
		return false;
	}

	// Close the file
	closeFile();

	// Process the XML raw data
	m_xmlDocument.Parse(m_fileBuffer);
	fgFree(m_fileBuffer);
	m_fileBuffer = NULL;

	// Set the root element
	m_rootXMLElement = m_xmlDocument.FirstChildElement();
	if(m_rootXMLElement == NULL) {
		// FIXME this should get some error from TinyXML if it's possible
		m_xmlDocument.Clear();
		return false;
	}
	return true;
}

/*
 * Frees all data stored
 */
void fgXMLParser::freeXML(void)
{
	if(m_fileBuffer) {
		fgFree(m_fileBuffer);
	}
	m_fileBuffer = false;
	m_fileSize = false;
	m_xmlDocument.ClearError();
	m_xmlDocument.Clear();
	m_rootXMLElement = NULL;
	m_currentXMLNode = NULL;
	m_contentHandler = NULL;
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
bool fgXMLParser::_parseDeep(fgXMLNode *cnode, int depth)
{	
	if(!cnode) {
		fgXMLAttribute *firstAttribute = NULL;
		fgXMLElement *elementPtr = NULL;
		// Retrieve the root's node name
		const char *rootName = this->getRootElementValue();
		if(!rootName)
			return false;
		if(this->setFirstAttribute())
			firstAttribute = this->getCurrentAttribute();
		elementPtr = this->getRootElement();
		// Call start element for the very first element in the XML tree - root node
		this->m_contentHandler->startElement(rootName, elementPtr, (fgXMLNodeType)elementPtr->Type(), firstAttribute);
	}
	// Parsing children nodes
	if(this->getCurrentNodeChildrenPresence()) {
		fgXMLAttribute *firstAttribute = NULL;
		fgXMLElement *elementPtr = NULL;
		this->goDeeper();
		do {
			if(this->setFirstAttribute())
				firstAttribute = this->getCurrentAttribute();
			const char *currentNodeValue = this->getCurrentNodeValue();
			elementPtr = this->getCurrentNode()->ToElement();
			if(this->isCurrentElement()) {
				// Handlers function for properly handling begining of the element
				this->m_contentHandler->startElement(currentNodeValue, elementPtr, (fgXMLNodeType)elementPtr->Type(), firstAttribute);
				// Go deeper in the parsing tree
				this->_parseDeep(this->getCurrentNode(), depth++);
				// Handle end of the element
				this->m_contentHandler->endElement(currentNodeValue, elementPtr, (fgXMLNodeType)elementPtr->Type());
			} else if(this->isCurrentText() || this->isCurrentComment()) {
				// This will be probably comment element or text between tags (start / end)
				this->m_contentHandler->characters(currentNodeValue, 0, strlen(currentNodeValue));
			}
		} while(this->goToNextNode());
		this->goHigher();
	} else {
		// #FIXME
	}
	if(!cnode) {
		fgXMLElement *elementPtr = NULL;
		// Retrieve the root's node name
		const char *rootName = this->getRootElementValue();
		if(!rootName)
			return false;
		elementPtr = this->getRootElement();
		this->m_contentHandler->endElement(rootName, elementPtr, (fgXMLNodeType)elementPtr->Type());
	}
	return true;
}

/*
 * Parse (analyze) the xml file using predefined content handler.
 */
fgStatus fgXMLParser::parseWithHandler(void)
{
	fgStatus status;
	if(!m_contentHandler) {
		status.isFailure = true;
		status.isError = true;
		status.message = NULL;
		return status;
	}
	std::stack<fgXMLNode *> toVisitStack;

	// Parsing XML using content handler class
	if(!this->isXMLLoaded()) {
		status.isError = true;
		return status;
	}
	// Start document parsing
	m_contentHandler->startDocument(&this->m_xmlDocument);
	// Start deep parsing #FIXME
	bool pstatus = _parseDeep();
	if(!pstatus) {
		status.isError = true;
		return status;
	}
	m_contentHandler->endDocument(&this->m_xmlDocument);
	status.isSuccess = true;
	return status;
}

