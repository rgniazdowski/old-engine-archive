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

    #ifndef _FG_BUILD_CONFIG_H_
        #include "fgBuildConfig.h"
    #endif

    #ifndef _FG_TYPES_H_
        #include "fgTypes.h"
    #endif

    #ifndef _FG_MATHLIB_H_
        #include "Math/fgMathLib.h"
    #endif

    #include "Util/fgTag.h"
    #include "Util/fgHandle.h"

    #include "fgGuiStyleContent.h"
    #include "fgGuiCallback.h"

    #include <string>

typedef unsigned int fgGuiWidgetType;

    #ifndef _FG_GFX_LAYER_H_
        #include "GFX/fgGFXLayer.h"
    #endif

    #ifndef _FG_GFX_BOUNDING_BOX_H_
        #include "GFX/fgGFXBoundingBox.h"
    #endif

    #ifndef _FG_POINTER_DATA_H_
        #include "Input/fgPointerData.h"
    #endif

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

    #define FG_GUI_WIDGET_STATE_NONE		0	// main
    #define FG_GUI_WIDGET_STATE_FOCUS		1	// focus
    #define FG_GUI_WIDGET_STATE_PRESSED		2	// pressed
    #define FG_GUI_WIDGET_STATE_ACTIVATED	3	// activated
    #define FG_GUI_WIDGET_STATE_DEACTIVATED	4	// deactivated
    #define FG_GUI_WIDGET_STATE_COUNT		5
typedef unsigned int fgGuiWidgetState;

    #define FG_GUI_WIDGET_UNKNOWN	0x00000000
    #define FG_GUI_WIDGET			0x00000001
    #define FG_GUI_WIDGET_NAME		"Widget"

class fgGuiWidget;

    #define FG_TAG_GUI_WIDGET_NAME	"GuiWidget"
    #define FG_TAG_GUI_WIDGET		FG_TAG_TYPE(fgGuiWidget)

FG_TAG_TEMPLATE_ID_AUTO(fgGuiWidget, FG_TAG_GUI_WIDGET_NAME);
typedef FG_TAG_GUI_WIDGET fgGuiWidgetTag;

// Special handle type for gui widget (used mainly for widget manager)
typedef fgHandle<fgGuiWidgetTag> fgGuiWidgetHandle;

    #define FG_GUI_WIDGET_DEFAULT_STYLE "DefaultStyle"

/*
 *
 */
class fgGuiWidget {
    friend class fgGuiMain;
    friend class fgGuiWidgetManager;
    friend class fgGuiStructureSheetParser;
private:
protected:
    /// Unique name for the current widget object. Used to identify
    // and find the exact widget object in the GUI flow
    std::string m_nameTag;
    /// Human readable name of the widget type
    std::string m_typeName;
    /// The name of the currently used style. May be empty.
    std::string m_styleName;
    /// Specifies a menu to which GUI will jump after given widget activation. 
    /// The name is case sensitive. If in the whole GUI subsystem there is no 
    /// such menu then this link will be silently ignored.
    std::string m_link;
    /// Specifies the name of the standard action to be executed on widgets' activation
    std::string m_action;
    /// Specifies the name of the script to execute on widgets' activation. 
    /// Can also to be the name of the function � this will require 
    /// parentheses after the name with parameters if needed.
    std::string m_script;
    /// Specifies which main configurations' section/parameter 
    /// will be changed if the value of this widget changes
    std::string m_config;
    /// Specifies text value, it can be used in many ways. It's maily for automation
    /// when reading XML struct file. If between tags there is a plain text, it will
    /// be put into this variable. Some of widgets may completely ignore this.
    std::string m_text;
    /// Array storing current style modifications for the widget
    fgGuiStyleContent m_styles[FG_GUI_WIDGET_STATE_COUNT];

    /// Relative position in pixels
    fgVector3f m_relPos;
    /// Position (this is where the widget is currently drawn) and size of the widget
    fgBoundingBox3Df m_bbox;

    /// This callback will be executed when widget is focused
    fgGuiCallback *m_onFocus;
    /// Callback to call when the focus is lost
    fgGuiCallback *m_onFocusLost;
    /// Callback to call when widgets state changes to 'pressed'
    fgGuiCallback *m_onClick;
    /// Callback to call on widgets activation
    fgGuiCallback *m_onActivate;
    /// Callback to call when widget is deactivated (once)
    fgGuiCallback *m_onDeactivate;
    /// Callback for handling any keyboard related events
    fgGuiCallback *m_onKey;
    /// Callback for handling any mouse specific events 
    /// - mouse motion, press and hold, swipe, etc
    fgGuiCallback *m_onMouse;
    /// This callback will be called anytime the widgets 
    /// state has changed (there are 5 states defined currently)
    fgGuiCallback *m_onChangeState;

    /// Pointer to the widget in which this one resides
    fgGuiWidget *m_fatherPtr;

    /// Unique handle number for the widget
    fgGuiWidgetHandle m_handle;

    /// Holds single value indicating the main type of the widget
    fgGuiWidgetType m_type;
    /// Holds OR'd value indicating all types which currently are 
    /// used to create the widget. For example: WINDOW | FRAME | WIDGET
    fgGuiWidgetType m_typeTraits;

    /// Current event state of the widget
    fgGuiWidgetState m_state;

    /// Is widget managed inside of the widget manager?
    fgBool m_isManaged;

    ///  If 'false' the widget will not be drawn (however it could affect
    // size and position of other widgets nearby). Default: true.
    fgBool m_isVisible;
    /// If widget is not active it cannot be clicked, activated,
    /// does not call callbacks nor check for changed event states.
    /// When deactivated (isActive==false) state will be set to 
    /// WIDGET_STATE_DEACTIVATED and proper style for that state will be applied
    fgBool m_isActive;
    /// If 'true' the widget will ignore state changes � based on external events 
    /// � so the style of the widget will not change (will be static). However any 
    /// event callbacks set for this widget will fire (event handlers will execute 
    /// anyway). Default: false.
    fgBool m_ignoreState;

protected:
    //
    virtual void setDefaults(void) = 0;

    //
    void setFather(fgGuiWidget *widget) {
        m_fatherPtr = widget;
    }
public:
    //
    fgGuiWidget();
    //
    virtual ~fgGuiWidget();

    //
    virtual void display(fgGfxLayer *guiLayer);

    //
    virtual fgBoundingBox3Df& updateSize(void);
    //
    virtual fgBoundingBox3Df& updateSize(const fgBoundingBox3Df &bbox);
    //
    virtual void refresh(void);

    //
    virtual int updateState(const fgPointerData *pointerData);
    
    //
    inline fgGuiWidget *getFather(void) const {
        return m_fatherPtr;
    }

    //
    inline fgGuiWidgetType getType(void) const {
        return m_type;
    }

    //
    inline fgGuiWidgetType getTypeTraits(void) const {
        return m_typeTraits;
    }

    //
    inline std::string &getTypeName(void) {
        return m_typeName;
    }

    //
    inline const char *getTypeNameStr(void) const {
        return m_typeName.c_str();
    }

protected:
    // This will set the 'managed' flag to true if the widget
    // is managed inside of the widget manager (is not standalone)
    inline void setManaged(fgBool toggle = FG_TRUE) {
        m_isManaged = toggle;
    }

public:
    // Returns whether widget is managed in widget manager
    inline fgBool isManaged(void) const {
        return m_isManaged;
    }

    // Sets the visibility flag of the widget
    inline void setVisible(fgBool toggle = FG_TRUE) {
        m_isVisible = toggle;
    }

    // Returns whether widget is visible (should be displayed?)
    inline fgBool isVisible(void) const {
        return m_isVisible;
    }

    // Sets the active flag of the widget
    inline void setActive(fgBool toggle = FG_TRUE) {
        m_isActive = toggle;
        if(m_isActive) {
            m_state = FG_GUI_WIDGET_STATE_NONE;
        } else {
            m_state = FG_GUI_WIDGET_STATE_DEACTIVATED;
        }
    }

    // Returns whether widget is active
    inline fgBool isActive(void) const {
        return m_isActive;
    }

    // Sets the ignoreState flag for the widget
    inline void setIgnoreState(fgBool toggle = FG_TRUE) {
        m_ignoreState = toggle;
    }

    //
    inline fgBool doesIgnoreState(void) const {
        return m_ignoreState;
    }

    //
    inline fgBool isIgnoreState(void) const {
        return m_ignoreState;
    }

    //
    inline fgGuiWidgetState getState(void) const {
        return m_state;
    }

    //
    virtual void setPosition(const fgVector3f& pos) {
        m_bbox.pos = pos;
    }

    //
    virtual fgVector3f& getPosition(void) {
        return m_bbox.pos;
    }

    //
    inline fgVector3f& getRelativePos(void) {
        return m_relPos;
    }

    //
    inline void setSize(const fgVector3f& size) {
        m_bbox.size = size;
    }

    // Returns the reference to the vector holding widget size 
    inline fgVector3f& getSize(void) {
        return m_bbox.size;
    }

    //
    inline std::string& getLink(void) {
        return m_link;
    }

    //
    inline const char *getLinkStr(void) const {
        return m_link.c_str();
    }

    //
    inline std::string& getScript(void) {
        return m_script;
    }

    //
    inline const char *getScriptStr(void) const {
        return m_script.c_str();
    }

    //
    inline std::string& getAction(void) {
        return m_action;
    }

    //
    inline const char *getActionStr(void) const {
        return m_action.c_str();
    }

    //
    inline std::string& getConfig(void) {
        return m_config;
    }

    //
    inline const char *getConfigStr(void) const {
        return m_config.c_str();
    }

    //
    virtual std::string& getText(void) {
        return m_text;
    }

    //
    virtual const char *getTextStr(void) const {
        return m_text.c_str();
    }

    //
    inline void setLink(const std::string &link) {
        m_link = link;
    }

    //
    inline void setLink(const char *link) {
        if(link)
            m_link = link;
    }

    //
    inline void setScript(const std::string &script) {
        m_script = script;
    }

    //
    inline void setScript(const char *script) {
        if(script)
            m_script = script;
    }

    //
    inline void setAction(const std::string &action) {
        m_action = action;
    }

    //
    inline void setAction(const char *action) {
        if(action)
            m_action = action;
    }

    //
    inline void setConfig(const std::string &config) {
        m_config = config;
    }

    //
    inline void setConfig(const char *config) {
        if(config)
            m_config = config;
    }

    //
    virtual void setText(const std::string &text) {
        m_text = text;
    }

    //
    virtual void setText(const char *text) {
        if(text)
            m_text = text;
    }

    //
    inline std::string &getStyleName(void) {
        return m_styleName;
    }

    //
    inline const char *getStyleNameStr(void) const {
        return m_styleName.c_str();
    }

    //
    inline void setStyleName(const std::string &style) {
        m_styleName = style;
    }

    //
    inline void setStyleName(const char *style) {
        m_styleName = style; // #FIXME
    }
    //
    inline fgGuiStyleContent* getStyleContents(void) {
        return m_styles;
    }

    //
    inline fgGuiStyleContent& getStyleContent(void) {
        if(m_state >= FG_GUI_WIDGET_STATE_COUNT || m_state < 0)
            return m_styles[0];
        return m_styles[m_state];
    }

    //
    inline fgGuiStyleContent& getStyleContent(fgGuiWidgetState state) {
        if(state >= FG_GUI_WIDGET_STATE_COUNT || state < 0)
            return m_styles[0];
        return m_styles[state];
    }

    //
    inline void setOnFocusCallback(fgGuiCallback *callback) {
        m_onFocus = callback;
    }

    //
    inline void setOnFocusLostCallback(fgGuiCallback *callback) {
        m_onFocusLost = callback;
    }

    //
    inline void setOnClickCallback(fgGuiCallback *callback) {
        m_onClick = callback;
    }

    //
    inline void setOnActivateCallback(fgGuiCallback *callback) {
        m_onActivate = callback;
    }

    //
    inline void setOnDeactivateCallback(fgGuiCallback *callback) {
        m_onDeactivate = callback;
    }

    //
    inline void setOnKeyCallback(fgGuiCallback *callback) {
        m_onKey = callback;
    }

    //
    inline void setOnMouseCallback(fgGuiCallback *callback) {
        m_onMouse = callback;
    }

    //
    inline void setOnChangeStateCallback(fgGuiCallback *callback) {
        m_onChangeState = callback;
    }

    //
    inline fgGuiCallback *getOnFocusCallback(void) const {
        return m_onFocus;
    }

    //
    inline fgGuiCallback *getOnFocusLostCallback(void) const {
        return m_onFocusLost;
    }

    //
    inline fgGuiCallback *getOnClickCallback(void) const {
        return m_onClick;
    }

    //
    inline fgGuiCallback *getOnActivateCallback(void) const {
        return m_onActivate;
    }

    //
    inline fgGuiCallback *getOnDeactivateCallback(void) const {
        return m_onDeactivate;
    }

    //
    inline fgGuiCallback *getOnKeyCallback(void) const {
        return m_onKey;
    }

    //
    inline fgGuiCallback *getOnMouseCallback(void) const {
        return m_onMouse;
    }

    //
    inline fgGuiCallback *getOnChangeStateCallback(void) const {
        return m_onChangeState;
    }

    // Set widget name (string TAG/ID)
    inline void setName(const char *name) {
        m_nameTag = name;
    }
    // Set widget name (string TAG/ID)
    inline void setName(const std::string& name) {
        m_nameTag = name;
    }

    // Get widget name string
    inline std::string getName(void) const {
        return m_nameTag;
    }
    // Get reference to resource name string
    inline std::string& getName(void) {
        return m_nameTag;
    }
    // Get resource name (TAG/string ID) as C-like string (char array)
    inline const char* getNameStr(void) const {
        return m_nameTag.c_str();
    }

    // Return the widget handle ID
    inline fgGuiWidgetHandle getHandle(void) const {
        return m_handle;
    }

    // Set the widget handle ID 
    inline void setHandle(const fgGuiWidgetHandle& handle) {
        m_handle = handle;
    }

    //
    inline fgGuiWidgetHandle& getRefHandle(void) {
        return m_handle;
    }
    
    //
    inline const fgGuiWidgetHandle& getRefHandle(void) const {
        return m_handle;
    }
};

#endif /* _FG_GUI_WIDGET_H_ */
