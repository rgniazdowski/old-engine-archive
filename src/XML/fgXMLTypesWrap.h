/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_XML_TYPES_WRAP
    #define FG_INC_XML_TYPES_WRAP

    #include "fgCommon.h"

    #if defined(FG_USING_TINYXML)
        #if !defined(TINYXML_INCLUDED)
            #include "tinyxml.h"
        #endif

/* Simple wrappers for tiny xml structure types */
typedef TiXmlAttribute fgXMLAttribute;
typedef TiXmlAttributeSet fgXMLAttributeSet;
typedef TiXmlBase fgXMLBase;
typedef TiXmlComment fgXMLComment;
typedef TiXmlCursor fgXMLCursor;
typedef TiXmlDeclaration fgXMLDeclaration;
typedef TiXmlDocument fgXMLDocument;
typedef TiXmlElement fgXMLElement;
typedef TiXmlHandle fgXMLHandle;
typedef TiXmlNode fgXMLNode;
        #ifdef TIXML_USE_STL
        #else
typedef TiXmlOutStream fgXMLOutStream;
        #endif
typedef TiXmlParsingData fgXMLParsingData;
typedef TiXmlPrinter fgXMLPrinter;
        #ifdef TIXML_USE_STL
typedef std::string fgXMLString;
        #else
typedef TiXmlString fgXMLString;
        #endif
typedef TiXmlText fgXMLText;
typedef TiXmlUnknown fgXMLUnknown;
typedef TiXmlVisitor fgXMLVisitor;
typedef TiXmlNode::NodeType fgXMLNodeType;

    #endif /* FG_USING_TINYXML */

#endif /* FG_INC_XML_TYPES_WRAP */
