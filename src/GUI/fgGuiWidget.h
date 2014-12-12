/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_WIDGET
    #define FG_INC_GUI_WIDGET
    #define FG_INC_GUI_WIDGET_BLOCK

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #ifndef FG_INC_TYPES
        #include "fgTypes.h"
    #endif

    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

    #include "fgGuiWidgetTypes.h"

    #include "Util/fgTag.h"
    #include "Util/fgHandle.h"
    #include "Resource/fgManagedObjectBase.h"

    #include "fgGuiStyleContent.h"
    #include "fgGuiCallback.h"

    #include <string>

    #ifndef FG_INC_GFX_LAYER
        #include "GFX/fgGFXLayer.h"
    #endif

    #include "GFX/fgGFXBoundingBox.h"

    #ifndef FG_INC_POINTER_DATA
        #include "Input/fgPointerData.h"
    #endif

    #define FG_GUI_WIDGET_STATE_NONE		0	// main
    #define FG_GUI_WIDGET_STATE_FOCUS		1	// focus
    #define FG_GUI_WIDGET_STATE_PRESSED		2	// pressed
    #define FG_GUI_WIDGET_STATE_ACTIVATED	3	// activated
    #define FG_GUI_WIDGET_STATE_DEACTIVATED	4	// deactivated
    #define FG_GUI_WIDGET_STATE_COUNT		5
typedef unsigned int fgGuiWidgetState;

class fgFontDrawer;
class fgGuiDrawer;
class fgGuiMain;
class fgGuiWidgetManager;
class fgGuiStructureSheetParser;

class fgGuiWidget;

    #define FG_TAG_GUI_WIDGET_NAME	"GuiWidget"
    #define FG_TAG_GUI_WIDGET		FG_TAG_TYPE(fgGuiWidget)

FG_TAG_TEMPLATE_ID_AUTO(fgGuiWidget, FG_TAG_GUI_WIDGET_NAME);
typedef FG_TAG_GUI_WIDGET fgGuiWidgetTag;

// Special handle type for gui widget (used mainly for widget manager)
typedef fgHandle<fgGuiWidgetTag> fgGuiWidgetHandle;

    #define FG_GUI_WIDGET_DEFAULT_STYLE "DefaultStyle"

/// Invalid callback
    #define FG_GUI_WIDGET_CALLBACK_INVALID          0
/// This callback will be executed when widget is focused
    #define FG_GUI_WIDGET_CALLBACK_ON_FOCUS         1
    #define FG_GUI_WIDGET_CALLBACK_ON_FOCUS_GAIN    FG_GUI_WIDGET_CALLBACK_ON_FOCUS

/// Callback to call when the focus is lost
    #define FG_GUI_WIDGET_CALLBACK_ON_FOCUS_LOST    2
/// Callback to call when widgets state changes to 'pressed'
    #define FG_GUI_WIDGET_CALLBACK_ON_CLICK         3
/// Callback to call on widgets activation
    #define FG_GUI_WIDGET_CALLBACK_ON_ACTIVATE      4
/// Callback to call when widget is deactivated (once)
    #define FG_GUI_WIDGET_CALLBACK_ON_DEACTIVATE    5
/// Callback for handling any keyboard related events
    #define FG_GUI_WIDGET_CALLBACK_ON_KEY           6
/// Callback for handling any mouse specific events 
/// - mouse motion, press and hold, swipe, etc
    #define FG_GUI_WIDGET_CALLBACK_ON_MOUSE         7
/// This callback will be called anytime the widgets 
/// state has changed (there are 5 states defined currently)
    #define FG_GUI_WIDGET_CALLBACK_ON_CHANGE_STATE  8
/// number of callback types
    #define FG_GUI_WIDGET_CALLBACK_NUM              9
    #define FG_GUI_WIDGET_CALLBACK_MAX_ID           FG_GUI_WIDGET_CALLBACK_NUM

typedef unsigned int fgGuiWidgetCallbackType;

/**
 *
 * @see fgManagedObjectBase
 */
class fgGuiWidget : public fgManagedObjectBase<fgGuiWidgetHandle> {
    friend class fgGuiMain;
    friend class fgGuiWidgetManager;
    friend class fgGuiStructureSheetParser;

public:
    ///
    typedef fgManagedObjectBase<fgGuiWidgetHandle> base_type;

private:

protected:
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
    /// Current text size, this is updated automatically via appendText functions
    fgVector2f m_textSize;

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
    /// Standard callback for handling goto menu action - set from guiMain
    fgGuiCallback *m_onLink;

    /// Pointer to the widget in which this one resides
    fgGuiWidget *m_fatherPtr;

    /// Holds single value indicating the main type of the widget
    fgGuiWidgetType m_type;
    /// Holds OR'd value indicating all types which currently are 
    /// used to create the widget. For example: WINDOW | FRAME | WIDGET
    fgGuiWidgetType m_typeTraits;

    /// Current event state of the widget
    fgGuiWidgetState m_state;

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
    /**
     * 
     */
    virtual void setDefaults(void) = 0;
    /**
     * 
     * @param widget
     */
    void setFather(fgGuiWidget *widget) {
        m_fatherPtr = widget;
    }
public:
    /**
     * 
     */
    fgGuiWidget();
    /**
     * 
     */
    virtual ~fgGuiWidget();
    /**
     * 
     * @param guiLayer
     */
    virtual void display(fgGuiDrawer *guiLayer);
    /**
     * 
     * @param flags
     */
    inline virtual void setFlags(const char *flags) {
        setFlags(std::string(flags));
    }
    /**
     * 
     * @param flags
     */
    inline virtual void setFlags(const std::string& flags) { }

    /**
     * 
     * @return 
     */
    virtual fgBoundingBox3Df updateBounds(void);
    /**
     * 
     * @param bbox
     * @return 
     */
    virtual fgBoundingBox3Df updateBounds(const fgBoundingBox3Df &bbox);
    /**
     * 
     */
    virtual void refresh(void);

    /**
     * 
     * @param pointerData
     * @return 
     */
    virtual int updateState(const fgPointerData *pointerData);
    /**
     * 
     * @return 
     */
    inline fgGuiWidget *getFather(void) const {
        return m_fatherPtr;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiWidgetType getType(void) const {
        return m_type;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiWidgetType getTypeTraits(void) const {
        return m_typeTraits;
    }
    /**
     * 
     * @return 
     */
    inline std::string &getTypeName(void) {
        return m_typeName;
    }
    /**
     * 
     * @return 
     */
    inline const char *getTypeNameStr(void) const {
        return m_typeName.c_str();
    }

public:
    /**
     * Sets the visibility flag of the widget
     * @param toggle
     */
    inline void setVisible(fgBool toggle = FG_TRUE) {
        m_isVisible = toggle;
    }
    /**
     * Returns whether widget is visible (should be displayed?)
     * @return 
     */
    inline fgBool isVisible(void) const {
        return m_isVisible;
    }
    /**
     * Sets the active flag of the widget
     * @param toggle
     */
    inline void setActive(fgBool toggle = FG_TRUE) {
        m_isActive = toggle;
        if(m_isActive) {
            m_state = FG_GUI_WIDGET_STATE_NONE;
        } else {
            m_state = FG_GUI_WIDGET_STATE_DEACTIVATED;
        }
    }
    /**
     * Returns whether widget is active
     * @return 
     */
    inline fgBool isActive(void) const {
        return m_isActive;
    }
    /**
     * Sets the ignoreState flag for the widget
     * @param toggle
     */
    inline void setIgnoreState(fgBool toggle = FG_TRUE) {
        m_ignoreState = toggle;
    }
    /**
     *
     */
    inline fgBool doesIgnoreState(void) const {
        return m_ignoreState;
    }
    /**
     * 
     * @return 
     */
    inline fgBool isIgnoreState(void) const {
        return m_ignoreState;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiWidgetState getState(void) const {
        return m_state;
    }
    /**
     * 
     * @param pos
     */
    virtual void setPosition(const fgVector3f& pos) {
        m_bbox.pos = pos;
    }
    /**
     * 
     * @return 
     */
    virtual fgVector3f& getPosition(void) {
        return m_bbox.pos;
    }
    /**
     * 
     * @return 
     */
    inline fgVector3f& getRelativePos(void) {
        return m_relPos;
    }
    /**
     * 
     * @param relPos
     */
    inline void setRelativePos(const fgVector3f& relPos) {
        m_relPos = relPos;
    }
    /**
     * 
     * @param size
     */
    inline void setSize(const fgVector3f& size) {
        m_bbox.size = size;
    }
    /**
     * Returns the reference to the vector holding widget size
     * @return 
     */
    inline fgVector3f& getSize(void) {
        return m_bbox.size;
    }
    /**
     * Returns the reference to the bounding box
     * @return 
     */
    inline fgBoundingBox3Df& getBBox(void) {
        return m_bbox;
    }
    /**
     * 
     * @return 
     */
    inline std::string& getLink(void) {
        return m_link;
    }
    /**
     * 
     * @return 
     */
    inline const char *getLinkStr(void) const {
        return m_link.c_str();
    }
    /**
     * 
     * @return 
     */
    inline std::string& getScript(void) {
        return m_script;
    }
    /**
     * 
     * @return 
     */
    inline const char *getScriptStr(void) const {
        return m_script.c_str();
    }
    /**
     * 
     * @return 
     */
    inline std::string& getAction(void) {
        return m_action;
    }
    /**
     * 
     * @return 
     */
    inline const char *getActionStr(void) const {
        return m_action.c_str();
    }
    /**
     * 
     * @return 
     */
    inline std::string& getConfig(void) {
        return m_config;
    }
    /**
     * 
     * @return 
     */
    inline const char *getConfigStr(void) const {
        return m_config.c_str();
    }
    /**
     * 
     * @return 
     */
    virtual std::string& getText(void) {
        return m_text;
    }
    /**
     * 
     * @return 
     */
    virtual const char *getTextStr(void) const {
        return m_text.c_str();
    }
    /**
     * 
     * @param link
     */
    inline void setLink(const std::string &link) {
        m_link = link;
    }
    /**
     * 
     * @param link
     */
    inline void setLink(const char *link) {
        if(link)
            m_link = link;
    }
    /**
     * 
     * @param script
     */
    inline void setScript(const std::string &script) {
        m_script = script;
    }
    /**
     * 
     * @param script
     */
    inline void setScript(const char *script) {
        if(script)
            m_script = script;
    }
    /**
     * 
     * @param action
     */
    inline void setAction(const std::string &action) {
        m_action = action;
    }
    /**
     * 
     * @param action
     */
    inline void setAction(const char *action) {
        if(action)
            m_action = action;
    }
    /**
     * 
     * @param config
     */
    inline void setConfig(const std::string &config) {
        m_config = config;
    }
    /**
     * 
     * @param config
     */
    inline void setConfig(const char *config) {
        if(config)
            m_config = config;
    }
    /**
     * 
     * @param text
     */
    virtual void setText(const std::string &text) {
        m_text = text;
    }
    /**
     * 
     */
    virtual void clearText(void) {
       m_text.clear();
    }
    /**
     * 
     * @param text
     */
    virtual void setText(const char *text) {
        if(text)
            m_text = text;
    }
    /**
     * 
     * @return 
     */
    inline std::string &getStyleName(void) {
        return m_styleName;
    }
    /**
     * 
     * @return 
     */
    inline const char *getStyleNameStr(void) const {
        return m_styleName.c_str();
    }
    /**
     * 
     * @param style
     */
    inline void setStyleName(const std::string &style) {
        m_styleName = style;
    }
    /**
     * 
     * @param style
     */
    inline void setStyleName(const char *style) {
        m_styleName = style; // #FIXME
    }
    /**
     * 
     * @return 
     */
    inline fgGuiStyleContent* getStyleContents(void) {
        return m_styles;
    }
    /**
     * 
     * @param state
     * @return 
     */
    inline fgGuiStyleContent& getStyleContent(fgGuiWidgetState state = FG_GUI_WIDGET_STATE_NONE) {
        if(state >= FG_GUI_WIDGET_STATE_COUNT || state < 0)
            return m_styles[FG_GUI_WIDGET_STATE_NONE];
        return m_styles[state];
    }
    /**
     * 
     * @param state
     * @return 
     */
    inline fgGuiStyleContent *getStyleContentPtr(fgGuiWidgetState state = FG_GUI_WIDGET_STATE_NONE) {
        if(state >= FG_GUI_WIDGET_STATE_COUNT || state < 0)
            return &m_styles[FG_GUI_WIDGET_STATE_NONE];
        return &m_styles[state];
    }
    /**
     * 
     * @param callback
     */
    inline void setOnFocusCallback(fgGuiCallback *callback) {
        m_onFocus = callback;
    }
    /**
     * 
     * @param callback
     */
    inline void setOnFocusLostCallback(fgGuiCallback *callback) {
        m_onFocusLost = callback;
    }
    /**
     * 
     * @param callback
     */
    inline void setOnClickCallback(fgGuiCallback *callback) {
        m_onClick = callback;
    }
    /**
     * 
     * @param callback
     */
    inline void setOnActivateCallback(fgGuiCallback *callback) {
        m_onActivate = callback;
    }
    /**
     * 
     * @param callback
     */
    inline void setOnDeactivateCallback(fgGuiCallback *callback) {
        m_onDeactivate = callback;
    }
    /**
     * 
     * @param callback
     */
    inline void setOnKeyCallback(fgGuiCallback *callback) {
        m_onKey = callback;
    }
    /**
     *
     */
    inline void setOnMouseCallback(fgGuiCallback *callback) {
        m_onMouse = callback;
    }
    /**
     * 
     * @param callback
     */
    inline void setOnChangeStateCallback(fgGuiCallback *callback) {
        m_onChangeState = callback;
    }
    /**
     * 
     * @return 
     */
    inline void setOnLinkCallback(fgGuiCallback *callback) {
        m_onLink = callback;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnFocusCallback(void) const {
        return m_onFocus;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnFocusLostCallback(void) const {
        return m_onFocusLost;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnClickCallback(void) const {
        return m_onClick;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnActivateCallback(void) const {
        return m_onActivate;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnDeactivateCallback(void) const {
        return m_onDeactivate;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnKeyCallback(void) const {
        return m_onKey;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnMouseCallback(void) const {
        return m_onMouse;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnChangeStateCallback(void) const {
        return m_onChangeState;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiCallback *getOnLinkCallback(void) const {
        return m_onLink;
    }
};
    #undef FG_INC_GUI_WIDGET_BLOCK
#endif /* FG_INC_GUI_WIDGET */
