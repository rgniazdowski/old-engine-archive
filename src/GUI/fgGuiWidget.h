/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

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
    #include "Resource/fgManagedObject.h"

    #include "fgGuiStyleContent.h"
    #include "fgGuiCallback.h"

    #ifndef FG_INC_GFX_LAYER
        #include "GFX/fgGfxLayer.h"
    #endif

    #include "GFX/fgGfxBoundingBox.h"

    #ifndef FG_INC_POINTER_DATA
        #include "Event/fgPointerData.h"
    #endif

namespace fg {
    namespace gui {
        class CWidget;
        class CWidgetManager;
        class CFontDrawer;
        class CDrawer;
        class CGuiMain;
        class CStructureSheetParser;
    };
};

    #define FG_TAG_GUI_WIDGET_NAME	"GuiWidget"
    #define FG_TAG_GUI_WIDGET		FG_TAG_TYPE(fg::gui::CWidget)
FG_TAG_TEMPLATE_ID_AUTO(fg::gui::CWidget, FG_TAG_GUI_WIDGET_NAME);

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

namespace fg {
    namespace resource {
        template<typename THandleType> class CManagedObject;
    };
};

namespace fg {
    namespace gui {

        /// Tag type for Gui Widget
        typedef FG_TAG_GUI_WIDGET WidgetTag;
        /// Special handle type for gui widget (used mainly for widget manager)
        typedef fg::util::CHandle<WidgetTag> WidgetHandle;

        /**
         *
         * @see CManagedObject
         */
        class CWidget : public fg::resource::CManagedObject<WidgetHandle> {
            ///
            friend class CGuiMain;
            ///
            friend class CWidgetManager;
            ///
            friend class CStructureSheetParser;

        public:
            ///
            typedef CWidget self_type;
            ///
            typedef CWidget type;
            ///
            typedef CManagedObject<WidgetHandle> base_type;

            /**
             *
             */
            enum EventState {
                STATE_NONE,
                STATE_FOCUS,
                STATE_PRESSED,
                STATE_ACTIVATED,
                STATE_DEACTIVATED,
                STATE_COUNT
            };

            /**
             *
             */
            enum StateFlags {
                /// Empty state flags - nothing activated
                NO_FLAGS = 0x0000,
                /// Whether or not the widget is visible (will be displayed)
                VISIBLE = 0x0001,
                /// If widget is not active it cannot be clicked, activated,
                /// does not call callbacks nor check for changed event states.
                /// When deactivated (isActive==false) state will be set to
                /// WIDGET_STATE_DEACTIVATED and proper style for that state will be applied
                ACTIVE = 0x0002,
                /// If selected the widget will ignore state changes  based on external events
                /// so the style of the widget will not change (will be static). However any
                /// event callbacks set for this widget will fire (event handlers will execute
                /// anyway). Default: false.
                IGNORE_STATE = 0x0004
            };

        protected:
            /// Human readable name of the widget type
            std::string m_typeName;
            /// The name of the currently used style. May be empty.
            std::string m_styleName;
            /// Specifies a menu to which GUI will jump after given widget activation. 
            /// The name is case sensitive. If in the whole GUI subsystem there is no 
            /// such menu then this link will be silently ignored.
            std::string m_link;
            /// Specifies the name of the standard action to be executed on widgets activation
            std::string m_action;
            /// Specifies the name of the script to execute on widgets activation. 
            /// Can also to be the name of the function � this will require 
            /// parentheses after the name with parameters if needed.
            std::string m_script;
            /// Specifies which main configurations section/parameter 
            /// will be changed if the value of this widget changes
            std::string m_config;
            /// Specifies text value, it can be used in many ways. It's mainly for automation
            /// when reading XML struct file. If between tags there is a plain text, it will
            /// be put into this variable. Some of widgets may completely ignore this.
            std::string m_text;
            /// Array storing current style modifications for the widget
            CStyleContent m_styles[(int)STATE_COUNT];

            /// Relative position in pixels
            Vector3f m_relPos;
            /// Position (this is where the widget is currently drawn) and size of the widget
            gfx::BoundingBox3Df m_bbox;
            /// Current text size, this is updated automatically via appendText functions
            Vector2f m_textSize;

            /// This callback will be executed when widget is focused
            CGuiCallback *m_onFocus;
            /// Callback to call when the focus is lost
            CGuiCallback *m_onFocusLost;
            /// Callback to call when widgets state changes to 'pressed'
            CGuiCallback *m_onClick;
            /// Callback to call on widgets activation
            CGuiCallback *m_onActivate;
            /// Callback to call when widget is deactivated (once)
            CGuiCallback *m_onDeactivate;
            /// Callback for handling any keyboard related events
            CGuiCallback *m_onKey;
            /// Callback for handling any mouse specific events 
            /// - mouse motion, press and hold, swipe, etc
            CGuiCallback *m_onMouse;
            /// This callback will be called anytime the widgets 
            /// state has changed (there are 5 states defined currently)
            CGuiCallback *m_onChangeState;
            /// Standard callback for handling goto menu action - set from guiMain
            CGuiCallback *m_onLink;

            /// Pointer to the widget in which this one resides
            CWidget *m_pFather;

            /// Holds single value indicating the main type of the widget
            WidgetType m_type;
            /// Holds OR'd value indicating all types which currently are 
            /// used to create the widget. For example: WINDOW | FRAME | WIDGET
            WidgetType m_typeTraits;

            /// Current event state of the widget
            EventState m_state;
            ///
            StateFlags m_stateFlags;            

        protected:
            /**
             * 
             */
            virtual void setDefaults(void) = 0;
            /**
             * 
             * @param widget
             */
            void setFather(fg::gui::CWidget *widget) {
                m_pFather = widget;
            }

        public:
            /**
             * 
             */
            CWidget();
            /**
             * 
             */
            virtual ~CWidget();

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param guiLayer
             */
            virtual void preRender(CDrawer *guiLayer);
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
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             * @param bbox
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(const gfx::BoundingBox3Df &bbox);
            /**
             * 
             */
            virtual void refresh(void);

            /**
             * 
             * @param pointerData
             * @return 
             */
            virtual EventState updateState(const event::SPointerData *pointerData);

            ////////////////////////////////////////////////////////////////////
            /**
             * 
             * @return 
             */
            inline CWidget* getFather(void) const {
                return m_pFather;
            }
            /**
             * 
             * @return 
             */
            inline WidgetType getType(void) const {
                return m_type;
            }
            /**
             * 
             * @return 
             */
            inline WidgetType getTypeTraits(void) const {
                return m_typeTraits;
            }
            /**
             * 
             * @return 
             */
            inline std::string& getTypeName(void) {
                return m_typeName;
            }
            /**
             * 
             * @return 
             */
            inline const char* getTypeNameStr(void) const {
                return m_typeName.c_str();
            }

            ////////////////////////////////////////////////////////////////////

        public:
            /**
             *
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
            /**
             * Sets the visibility flag of the widget
             * @param toggle
             */
            inline void setVisible(fgBool toggle = FG_TRUE) {
                setFlag(VISIBLE, toggle);
            }
            /**
             * Returns whether widget is visible (should be displayed?)
             * @return 
             */
            inline fgBool isVisible(void) const {
                return (fgBool)!!(m_stateFlags & VISIBLE);
            }
            /**
             * Sets the active flag of the widget
             * @param toggle
             */
            inline void setActive(fgBool toggle = FG_TRUE) {
                setFlag(ACTIVE, toggle);
                if(toggle) {
                    m_state = STATE_NONE;
                } else {
                    m_state = STATE_DEACTIVATED;
                }
            }
            /**
             * Returns whether widget is active
             * @return 
             */
            inline fgBool isActive(void) const {
                return (fgBool)!!(m_stateFlags & ACTIVE);
            }
            /**
             * Sets the ignoreState flag for the widget
             * @param toggle
             */
            inline void setIgnoreState(fgBool toggle = FG_TRUE) {
                setFlag(IGNORE_STATE, toggle);
            }
            /**
             *
             */
            inline fgBool doesIgnoreState(void) const {
                return (fgBool)!!(m_stateFlags & IGNORE_STATE);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isIgnoreState(void) const {
                return (fgBool)!!(m_stateFlags & IGNORE_STATE);
            }
            /**
             * 
             * @return 
             */
            inline EventState getState(void) const {
                return m_state;
            }
            /**
             * 
             * @param pos
             */
            virtual void setPosition(const Vector3f& pos) {
                m_bbox.pos = pos;
            }
            /**
             * 
             * @return 
             */
            virtual Vector3f& getPosition(void) {
                return m_bbox.pos;
            }
            /**
             * 
             * @return 
             */
            inline Vector3f& getRelativePos(void) {
                return m_relPos;
            }
            /**
             * 
             * @param relPos
             */
            inline void setRelativePos(const Vector3f& relPos) {
                m_relPos = relPos;
            }
            /**
             * 
             * @param size
             */
            void setSize(const Vector3f& size, Unit unit = Unit::PIXELS);
            /**
             * Returns the reference to the vector holding widget size
             * @return 
             */
            inline Vector3f& getSize(void) {
                return m_bbox.size;
            }
            /**
             * Returns the reference to the bounding box
             * @return 
             */
            inline gfx::BoundingBox3Df& getBBox(void) {
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
            inline const char* getLinkStr(void) const {
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
            inline const char* getScriptStr(void) const {
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
            inline const char* getActionStr(void) const {
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
            inline const char* getConfigStr(void) const {
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
            virtual const char* getTextStr(void) const {
                return m_text.c_str();
            }
            /**
             * 
             * @param link
             */
            inline void setLink(const std::string& link) {
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
            inline void setScript(const std::string& script) {
                m_script = script;
            }
            /**
             * 
             * @param script
             */
            inline void setScript(const char* script) {
                if(script)
                    m_script = script;
            }
            /**
             * 
             * @param action
             */
            inline void setAction(const std::string& action) {
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
            inline void setConfig(const std::string& config) {
                m_config = config;
            }
            /**
             * 
             * @param config
             */
            inline void setConfig(const char* config) {
                if(config)
                    m_config = config;
            }
            /**
             * 
             * @param text
             */
            virtual void setText(const std::string& text) {
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
            virtual void setText(const char* text) {
                if(text)
                    m_text = text;
            }

            ////////////////////////////////////////////////////////////////////
            /**
             * 
             * @return 
             */
            inline std::string& getStyleName(void) {
                return m_styleName;
            }
            /**
             * 
             * @return 
             */
            inline const char* getStyleNameStr(void) const {
                return m_styleName.c_str();
            }
            /**
             * 
             * @param style
             */
            inline void setStyleName(const std::string& style) {
                m_styleName = style;
            }
            /**
             * 
             * @param style
             */
            inline void setStyleName(const char* style) {
                m_styleName = style; // #FIXME
            }
            /**
             * 
             * @return 
             */
            inline CStyleContent* getStyleContents(void) {
                return m_styles;
            }
            /**
             * 
             * @param state
             * @return 
             */
            inline CStyleContent& getStyleContent(EventState state = STATE_NONE) {
                if(state >= STATE_COUNT)
                    return m_styles[STATE_NONE];
                return m_styles[state];
            }
            /**
             * 
             * @param state
             * @return 
             */
            inline CStyleContent* getStyleContentPtr(EventState state = STATE_NONE) {
                if(state >= STATE_COUNT)
                    return &m_styles[STATE_NONE];
                return &m_styles[state];
            }

            ////////////////////////////////////////////////////////////////////
            /**
             * 
             * @param callback
             */
            inline void setOnFocusCallback(CGuiCallback* callback) {
                m_onFocus = callback;
            }
            /**
             * 
             * @param callback
             */
            inline void setOnFocusLostCallback(CGuiCallback* callback) {
                m_onFocusLost = callback;
            }
            /**
             * 
             * @param callback
             */
            inline void setOnClickCallback(CGuiCallback* callback) {
                m_onClick = callback;
            }
            /**
             * 
             * @param callback
             */
            inline void setOnActivateCallback(CGuiCallback* callback) {
                m_onActivate = callback;
            }
            /**
             * 
             * @param callback
             */
            inline void setOnDeactivateCallback(CGuiCallback* callback) {
                m_onDeactivate = callback;
            }
            /**
             * 
             * @param callback
             */
            inline void setOnKeyCallback(CGuiCallback* callback) {
                m_onKey = callback;
            }
            /**
             *
             */
            inline void setOnMouseCallback(CGuiCallback* callback) {
                m_onMouse = callback;
            }
            /**
             * 
             * @param callback
             */
            inline void setOnChangeStateCallback(CGuiCallback* callback) {
                m_onChangeState = callback;
            }
            /**
             * 
             * @return 
             */
            inline void setOnLinkCallback(CGuiCallback* callback) {
                m_onLink = callback;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnFocusCallback(void) const {
                return m_onFocus;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnFocusLostCallback(void) const {
                return m_onFocusLost;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnClickCallback(void) const {
                return m_onClick;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnActivateCallback(void) const {
                return m_onActivate;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnDeactivateCallback(void) const {
                return m_onDeactivate;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnKeyCallback(void) const {
                return m_onKey;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnMouseCallback(void) const {
                return m_onMouse;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnChangeStateCallback(void) const {
                return m_onChangeState;
            }
            /**
             * 
             * @return 
             */
            inline CGuiCallback* getOnLinkCallback(void) const {
                return m_onLink;
            }
        }; // class CWidget

        FG_ENUM_FLAGS(CWidget::StateFlags);
        /**
         *
         * @param flags
         * @param toggle
         */
        inline void CWidget::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_stateFlags |= flags;
            } else {
                m_stateFlags |= flags;
                m_stateFlags ^= flags;
            }
        }

    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_WIDGET_BLOCK
#endif /* FG_INC_GUI_WIDGET */
