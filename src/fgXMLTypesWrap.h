/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_XML_TYPES_WRAP_H_
#define _FG_XML_TYPES_WRAP_H_

#include "fgCommon.h"

#ifdef FG_USING_TINYXML
#include "tinyxml.h"

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
typedef TiXmlNode::NodeType fgXMLNodeType;

#endif

#endif /* _FG_XML_TYPES_WRAP_H_ */