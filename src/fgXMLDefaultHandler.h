/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_XML_DEFAULT_HANDLER_H_
#define _FG_XML_DEFAULT_HANDLER_H_

#include "fgXMLTypesWrap.h"

/*
 *
 */
class fgXMLDefaultHandler {
private:
protected:
	fgXMLDefaultHandler() {}
	virtual ~fgXMLDefaultHandler() {}
public:
	// Receive notification of character data inside an element or comment
	virtual void characters(const char ch[], int start, int length) {}
	// Receive notification of the end of the document.
	virtual void endDocument(fgXMLDocument *document) = 0;
    // Receive notification of the end of an element.
	virtual void endElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, int depth = -1) = 0;
	// Receive notification of a recoverable parser error.
	//void error(exception e)
	// Report a fatal XML parsing error.
	//void fatalError(exception e)
	// Receive notification of ignorable whitespace in element content.
	virtual void ignorableWhitespace(char ch[], int start, int length) {}
	// Receive notification of the beginning of the document.
	virtual void startDocument(fgXMLDocument *document) = 0;
	// Receive notification of the start of an element.
	virtual void startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth = -1) = 0;
	// Receive notification of a parser warning.
	//void warning(exception e); // #FIXME - the whole error reporting system...
};

#endif /* _FG_XML_DEFAULT_HANDLER_H_ */
