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
 *
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
 *
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



	return status;
}

