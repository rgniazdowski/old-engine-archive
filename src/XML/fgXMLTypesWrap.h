/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
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
#ifdef TIXML_USE_STL
#else
typedef TiXmlOutStream		fgXMLOutStream;
#endif
typedef TiXmlParsingData	fgXMLParsingData;
typedef TiXmlPrinter		fgXMLPrinter;
#ifdef TIXML_USE_STL
typedef std::string         fgXMLString;
#else
typedef TiXmlString			fgXMLString;
#endif
typedef TiXmlText			fgXMLText;
typedef TiXmlUnknown		fgXMLUnknown;
typedef TiXmlVisitor		fgXMLVisitor;
typedef TiXmlNode::NodeType fgXMLNodeType;

#endif

#endif /* _FG_XML_TYPES_WRAP_H_ */
