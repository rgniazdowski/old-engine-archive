/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_XML_AUTO_HANDLER
    #define FG_INC_XML_AUTO_HANDLER

    #include "fgXMLDefaultHandler.h"
    #include <cstdlib>
    #include "fgLog.h"

template<class _type> struct fgXMLAutoRoot {
};

template<class _type> struct fgXMLAutoElement {
};

template<class _type> struct fgXMLAutoCharacters {
};

template<class _type> struct fgXMLAutoAttribute {
};

// This will be used for auto conversion

template<class _type> struct fgXMLAutoConvert {
};

    #define FG_XML_AUTO_TYPE_INT	0	// integer
    #define FG_XML_AUTO_TYPE_FLOAT	1	// float
    #define FG_XML_AUTO_TYPE_LONG	2	// long
    #define FG_XML_AUTO_TYPE_STRING 3	// string - const char *

    #define FG_XML_AUTO_CONVERT_TEMPLATE(_type, _function) \
template<> struct fgXMLAutoConvert<_type> { \
	static _type convert(const char *_in) { \
		if(!_in) return (_type)0; \
		return (_type)_function(_in); \
	} \
}

    #define FG_XML_AUTO_EMPTY

// Define template for conversion from const char * to int
FG_XML_AUTO_CONVERT_TEMPLATE(int, atoi);
FG_XML_AUTO_CONVERT_TEMPLATE(float, atof);
FG_XML_AUTO_CONVERT_TEMPLATE(long, atol);
FG_XML_AUTO_CONVERT_TEMPLATE(const char*, FG_XML_AUTO_EMPTY);
FG_XML_AUTO_CONVERT_TEMPLATE(fgBool, FG_BOOL_FROM_TEXT);

// Standard static function for returning the name
    #define FG_XML_AUTO_FUNCTION_NAME(_name) static const char *name(void) { return _name; }
// Standard static function checking for right name
    #define FG_XML_AUTO_FUNCTION_CHECK_NAME(_name) static int checkName(const char *cname) { return strcasecmp(cname, _name); }

// Special macro for defining template describing root XML element
    #define FG_XML_AUTO_TEMPLATE_ROOT(_type, _name) \
template <> struct fgXMLAutoRoot<_type> { \
	typedef _type type; \
	FG_XML_AUTO_FUNCTION_NAME(_name) \
	FG_XML_AUTO_FUNCTION_CHECK_NAME(_name) \
}

/**********************************************************
 * Templates for handling xml elements with various names,
 * storing data to proper place in the Target structure/class
 */

    #define FG_XML_AUTO_TEMPLATE_ELEMENT_BEGIN(_type) \
template <> struct fgXMLAutoElement<_type> { \
	typedef _type type; \
	static void onElement(const char *localName, type *_target, fgXMLElement *_elemPtr) { \
		if(!localName || !_target || !_elemPtr) return

    #define FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(_elemType, _target_member, _name) \
	do { \
	if(strncasecmp(localName, _name, strlen(_name)) == 0) { \
		const char *_e_txt = _elemPtr->GetText(); \
		if(_e_txt != NULL) \
			_target->_target_member = fgXMLAutoConvert<_elemType>::convert(_e_txt); \
	} \
	} while(0)

    #define FG_XML_AUTO_TEMPLATE_ELEMENT_END() } }

/**********************************************************
 * Templates for handling actions with characters between
 * start and end tag, this will also get the XML comments
 */

    #define FG_XML_AUTO_TEMPLATE_CHARACTERS_BEGIN(_type) \
template <> struct fgXMLAutoCharacters<_type> { \
	typedef _type type; \
	static void characters(const char ch[], int start, int length, fgXMLNodeType nodeType, type *_target, fgXMLElement *_elemPtr) { \
		if(!_target || !_elemPtr || !length) return; \
		const char  *localName = _elemPtr->Value(); \
                if(!localName) \
                    return

    #define FG_XML_AUTO_TEMPLATE_CHARACTERS_CHECK_NAME(_elemType, _target_member, _name) \
	do { \
	if(strncasecmp(localName, _name, strlen(_name)) == 0) { \
		_target->_target_member = fgXMLAutoConvert<_elemType>::convert(ch); \
	} \
	} while(0)

    #define FG_XML_AUTO_TEMPLATE_CHARACTERS_EMPTY

    #define FG_XML_AUTO_TEMPLATE_CHARACTERS_END() } }

/**********************************************************
 * Templates for handling attributes
 */

    #define FG_XML_AUTO_TEMPLATE_ATTRIBUTE_BEGIN(_type) \
template <> struct fgXMLAutoAttribute<_type> { \
	typedef _type type; \
	static void onAttribute(const char *localName, type *_target, fgXMLElement *_elemPtr, fgXMLAttribute *_attrPtr) { \
		if(!localName || !_target || !_elemPtr || !_attrPtr) return; // #FIXME

    #define FG_XML_AUTO_TEMPLATE_ATTRIBUTE_EMPTY

    #define FG_XML_AUTO_TEMPLATE_ATTRIBUTE_END() } }

    #include <stack>

template<typename Target>
class fgXMLAutoHandler : public fg::xml::CDefaultHandler {
public:
    fgXMLAutoHandler() : m_target(NULL), m_isFailure(FG_FALSE) { }
    virtual ~fgXMLAutoHandler() {
        while(!m_elemStack.empty())
            m_elemStack.pop();
    }
public:
    // Receive notification of the end of the document.
    virtual void endDocument(fgXMLDocument *document) {
        //FG_LOG_DEBUG("XMLAutoHandler: endDocument(); failure[%d]", m_isFailure);
        if(m_isFailure)
            return;
    }

    // Receive notification of the end of an element.
    virtual void endElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, int depth = 0) {
        //FG_LOG_DEBUG("XMLAutoHandler: endElement('%s'); failure[%d]", localName, m_isFailure);
        if(m_isFailure)
            return;
        m_elemStack.pop();
    }

    // Receive notification of the beginning of the document.
    virtual void startDocument(fgXMLDocument *document) { 
        //FG_LOG_DEBUG("XMLAutoHandler: startDocument()");
    }

    // Receive notification of the start of an element.
    virtual void startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth = 0) {
        //FG_LOG_DEBUG("XMLAutoHandler: startElement('%s'); failure[%d]", localName, m_isFailure);
        if(fgXMLAutoRoot<Target>::checkName(localName) != 0 && depth == 0) {
            m_isFailure = FG_TRUE;
            return;
        }
        if(m_isFailure)
            return;
        m_elemStack.push(elementPtr);

        fgXMLAutoElement<Target>::onElement(localName, m_target, elementPtr);
    }

    // Receive notification of character data inside an element or comment
    virtual void characters(const char *ch, int start, int length, fgXMLNodeType nodeType, int depth = 0) {
        if(m_isFailure)
            return;
        fgXMLElement *elementPtr = NULL;
        if(!m_elemStack.empty())
            elementPtr = m_elemStack.top();
        //FG_LOG_DEBUG("XMLAutoHandler: characters('%s', %d, %d); failure[%d]", ch, start, length, m_isFailure);
        fgXMLAutoCharacters<Target>::characters(ch, start, length, nodeType, m_target, elementPtr);
    }
    virtual void setTarget(Target *target) {
        m_target = target;
    }

protected:
    fgBool m_isFailure;
    Target *m_target;
    std::stack<fgXMLElement *> m_elemStack;
};

#endif /* FG_INC_XML_AUTO_HANDLER */