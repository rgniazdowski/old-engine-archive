/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_WIDGET_H_
#define _FG_GUI_WIDGET_H_

#include "Math/fgMathLib.h"
#include "fgTypes.h"

// some other base class would be useful for that ... hmmm
// i mean additional functions / interfaces, like hmmm  nameable ? stringify? heh
// serializable? readable?
// XML element? lol? Attribute?

// need automation for xml reading - xml auto parser would be very useful
// changes for auto parser --- need to specify custom body function / external 
// instead of just putting blindly those macros for every structure element/member.

// First of all, in XML structure when there's text inside of a tag - it always
// means that this text is a LABEL - elements inside (tags) - are children,
// therefore widget containing them must be... extending fgGuiContainer

// well if widget is TextArea then text inside the tag is... a VALUE, oh...
// how to unify this?

// when it's element of an array... well it's like textArea
// so... now hwat?
//
// wat?

// -- for some widgets text inside tag means : LABEL
// -- for other : VALUE / TEXT
// #BORT
class fgGuiStyleable
{
protected:
	//fgGuiStyle * m_currentStyle;
	//fgGuiStyle * m_defaultStyle;
public:
};
// #BORT
class fgGuiDrawable
{
protected:
	fgVector2f m_pos;
	fgVector2f m_relPos;
	fgVector2f m_size;
public:
	fgGuiDrawable();
	virtual ~fgGuiDrawable();

	virtual fgVector4f updateSize(void) = 0;
	virtual fgVector4f updateSize(const fgVector2f & boundPos, const fgVector2f & boundSize) = 0;
	virtual void refresh(void) = 0;
};



#define FG_GUI_WIDGET_STATE_NONE		0
#define FG_GUI_WIDGET_STATE_FOCUS		1
#define FG_GUI_WIDGET_STATE_PRESSED		2
#define FG_GUI_WIDGET_STATE_ACTIVATED	3
#define FG_GUI_WIDGET_STATE_DEACTIVATED	4
#define FG_GUI_WIDGET_STATE_COUNT		5

class fgGuiWidget;

typedef fgBool (*fgGuiWidgetEventHandlerFunc) (fgGuiWidget *widget);
// Whatever, this will be hooked to universal fgCallbackFunction - need to create new class
// fgGuiCallbackFunction ^^

#include <string>

#define FG_GUI_WIDGET		1
#define FG_GUI_WIDGET_NAME	"Widget"

// #FIXME - just testing
class fgGuiEventHandleable {
protected:
	fgGuiWidgetEventHandlerFunc m_onFocus;
	fgGuiWidgetEventHandlerFunc m_onClick;
	fgGuiWidgetEventHandlerFunc m_onActivate;
	fgGuiWidgetEventHandlerFunc m_onDeactivate;
	fgGuiWidgetEventHandlerFunc m_onKey;
	fgGuiWidgetEventHandlerFunc m_onFocusLost;
	fgGuiWidgetEventHandlerFunc m_onMouse;
public:
	fgGuiEventHandleable() {}
	~fgGuiEventHandleable() {}
};

/*
 *
 */
class fgGuiWidget
{
private:
protected:
	// #FIXME - different type
	int m_type;
	std::string m_typeName;
	// Position
	fgVector2f m_pos;
	// Relative position
	fgVector2f m_relPos;
	// Size
	fgVector2f m_size;

	// #FIXME 
	int m_state;

	// bind them ? oh may, HANDLE ?
	// name is universal
	std::string m_name;
	//int m_numID;

	fgBool m_isVisible;
	fgBool m_isActive;
	fgBool m_ignoreState;

	// ? Pointer to style ?
	// ? Holder for editable style ?

	// ? Pointer to gui main ?
	// ? pointer to father ? 

	// Event handlers ?
	// Event handler standard?
protected:
	//
	virtual void setDefaults(void);

public:
	//
	fgGuiWidget();
	//
	virtual ~fgGuiWidget();

	//
	virtual fgVector4f updateSize(void);
	//
	virtual fgVector4f updateSize(const fgVector2f & boundPos, const fgVector2f & boundSize);
	//
	virtual void refresh(void);

	//
	virtual int updateState(void);
};

#endif /* _FG_GUI_WIDGET_H_ */
