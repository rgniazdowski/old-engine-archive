/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_XML_PARSER_H
#define _FG_XML_PARSER_H

#include "fgCommon.h"
#include "fgFileStream.h"

#include "tinyxml.h"

#include <string>
#include <cstring>

#include <stack>

/* Simple wrappers for tiny xml structure types */
typedef TiXmlAttribute		fgXMLAttribute;
typedef TiXmlAttributeSet	fgXMLAttributeSet;
typedef TiXmlBase			fgXMLBase;
typedef TiXmlComment		fgXMLComment;
typedef TiXmlCursor			fgXMLCursor;
typedef TiXmlDeclaration	fgXMLDeclaration;
typedef TiXmlDocument		fgXMLDocument;
typedef TiXmlElement		fgXMLElement;
typedef TiXmlHandle			fgXMLHandle;
typedef TiXmlNode			fgXMLNode;
typedef TiXmlOutStream		fgXMLOutStream;
typedef TiXmlParsingData	fgXMLParsingData;
typedef TiXmlPrinter		fgXMLPrinter;
typedef TiXmlString			fgXMLString;
typedef TiXmlText			fgXMLText;
typedef TiXmlUnknown		fgXMLUnknown;
typedef TiXmlVisitor		fgXMLVisitor;

// This class extends the fgFileStream, so it can load the proper XML file
// fgXMLParser contains  specialized functions for  parsing/interpreting the  data inside the XML file, its 
// a kind of a XML functions wrapper to make it easier and more intuitive to interpret and extract the data

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

	A Decleration contains: Attributes (not on tree)
*/

#define SETT_FILENAME "test.xml"

#define FG_XML_PARSER_ERROR_LENGTH		512

class fgXMLParser : private fgFileStream
{
protected:
	// FIXME
	bool			m_isError;
	char			m_errorMessage[FG_XML_PARSER_ERROR_LENGTH];
	unsigned int	m_fileSize;
	char			*m_fileBuffer;
	fgXMLDocument	m_xmlDocument;
	fgXMLElement	*m_rootXMLElement;
	fgXMLNode		*m_currentXMLNode;
	fgXMLAttribute	*m_currentXMLAttribute;
	// On this stack are being placed current nodes before the parser goes deeper (into the nodes children ROTFL)
	std::stack<fgXMLNode *> m_parsingStack;
public:
	fgXMLParser() : m_isError(false), m_fileSize(0), m_fileBuffer(NULL), m_rootXMLElement(NULL), m_currentXMLNode(NULL), m_currentXMLAttribute(NULL)
	{
		memset(m_errorMessage, 0, FG_XML_PARSER_ERROR_LENGTH);
	}

	fgXMLParser(const char *filePath) : m_isError(false), m_fileSize(0), m_fileBuffer(NULL), m_rootXMLElement(NULL), m_currentXMLNode(NULL), m_currentXMLAttribute(NULL)
	{
		memset(m_errorMessage, 0, FG_XML_PARSER_ERROR_LENGTH);
		loadXML(filePath);
	}

	~fgXMLParser() {
		freeXML();
	}

	/*
	 *
	 */
	bool loadXML(const char *filePath);

	/*
	 *
	 */
	void freeXML(void);

	/*
	 *
	 */
	bool isXMLLoaded(void) const {
		if(m_rootXMLElement)
			return true;
		else
			return false;
	}

	/*
	 *
	 */
	fgXMLElement *getRootElement(void) const {
		return m_rootXMLElement;
	}

	/*
	 *
	 */
	const char *getRootElementValue(void) const {
		if(!m_rootXMLElement)
			return NULL;
		return m_rootXMLElement->Value();
	}

	/*
	 *
	 */
	fgXMLNode *getCurrentNode(void) const {
		return m_currentXMLNode;
	}

	/*
	 *
	 */
	fgXMLAttribute *getCurrentAttribute(void) const {
		return m_currentXMLAttribute;
	}

	/*
	 *
	 */
	const char *getCurrentAttributeName(void) const {
		if(!m_currentXMLAttribute)
			return NULL;
		return m_currentXMLAttribute->Name();
	}

	/*
	 *
	 */
	const char *getCurrentAttributeValue(void) const {
		if(!m_currentXMLAttribute)
			return NULL;
		return m_currentXMLAttribute->Value();
	}

	/*
	 *
	 */
	bool getCurrentNodeChildrenPresence(void) const {
		if(!m_currentXMLNode)
			return false;
		return !m_currentXMLNode->NoChildren();
	}

	/*
	 *
	 */
	const char *getCurrentNodeValue(void) const {
		if(!m_currentXMLNode)
			return NULL;
		if( m_currentXMLNode->Type() != fgXMLNode::TEXT )
			return m_currentXMLNode->Value();
		else
			return getCurrentTextNodeValue();
	}

	/*
	 *
	 */
	const char *getCurrentTextNodeValue(void) const {
		if(!m_currentXMLNode)
			return NULL;
		if( m_currentXMLNode->Type() != fgXMLNode::TEXT )
			return NULL;
		fgXMLText *textNode = m_currentXMLNode->ToText();
		if(!textNode)
			return NULL;
		return textNode->Value();
	}

	/*
	 *
	 */
	bool isCurrent(void) const {
		if(!m_currentXMLNode)
			return false;
		else 
			return true;
	}

	/*
	 *
	 */
	bool isCurrentElement(void) const {
		if(!m_currentXMLNode)
			return false;
		return (m_currentXMLNode->Type() == fgXMLNode::ELEMENT);
	}

	/*
	 *
	 */
	bool isCurrentText(void) const {
		if(!m_currentXMLNode)
			return false;
		return (m_currentXMLNode->Type() == fgXMLNode::TEXT);
	}

	/*
	 *
	 */
	bool isCurrentComment(void) const {
		if(!m_currentXMLNode)
			return false;
		return (m_currentXMLNode->Type() == fgXMLNode::COMMENT);
	}

	/*
	 *
	 */
	bool isCurrentUnknown(void) const {
		if(!m_currentXMLNode)
			return false;
		return (m_currentXMLNode->Type() == fgXMLNode::UNKNOWN);
	}

	/*
	 *
	 */
	bool setFirstAttribute(void) 
	{
		if(!m_currentXMLNode)
			return false;
		if(!isCurrentElement())
			return false;
		fgXMLElement *xmlElement = m_currentXMLNode->ToElement();
		if(!xmlElement)
			return false;
		m_currentXMLAttribute = xmlElement->FirstAttribute();
		if(m_currentXMLAttribute == NULL)
			return false;
		return true;
	}

	/*
	 *
	 */
	bool goDeeper(void)
	{
		if(!m_currentXMLNode)
		{
			if(!m_rootXMLElement)
				return false;
			m_currentXMLNode = m_rootXMLElement->FirstChild();
			if(!m_currentXMLNode) {
				return false;
			} else {
				m_currentXMLAttribute = NULL;
				return true;
			}
		}

		if(m_currentXMLNode->NoChildren())
			return false;

		m_parsingStack.push(m_currentXMLNode);
		m_currentXMLNode = m_currentXMLNode->FirstChild();
		m_currentXMLAttribute = NULL;
		return true;
	}

	/*
	 *
	 */
	bool goHigher(void)
	{
		if(m_parsingStack.empty())
			return false;
		m_currentXMLNode = m_parsingStack.top();
		m_parsingStack.pop();
		if(!m_currentXMLNode)
			return false;
		m_currentXMLAttribute = NULL;
		return true;
	}

	/*
	 *
	 */
	bool goToNextNode(void)
	{
		if(!m_currentXMLNode)
			return false;
		m_currentXMLNode = m_currentXMLNode->NextSibling();
		if(m_currentXMLNode)
			return true;
		else
			return false;
	}

	/*
	 *
	 */
	bool goToPreviousNode(void)
	{
		if(!m_currentXMLNode)
			return false;
		m_currentXMLNode = m_currentXMLNode->PreviousSibling();
		if(m_currentXMLNode)
			return true;
		else
			return false;
	}

	/*
	 *
	 */
	bool goToNextAttribute(void)
	{
		if(!m_currentXMLAttribute)
			return false;
		m_currentXMLAttribute = m_currentXMLAttribute->Next();
		if(m_currentXMLAttribute)
			return true;
		else
			return false;
	}

	/*
	 *
	 */
	bool goToPreviousAttribute(void)
	{
		if(!m_currentXMLAttribute)
			return false;
		m_currentXMLAttribute = m_currentXMLAttribute->Previous();
		if(m_currentXMLAttribute)
			return true;
		else
			return false;
	}
};

#endif