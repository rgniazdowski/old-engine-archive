/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_MAIN
    #define FG_INC_GUI_MAIN
    #define FG_INC_GUI_MAIN_BLOCK

    #if defined(FG_INC_SCRIPT_SUBSYSTEM_BLOCK)
        #error "FG_SCRIPT_SUBSYSTEMBLOCK is defined: Do not include GuiMain inside of ScriptSubsystem header"
    #endif

    #if defined(FG_INC_GUI_WIDGET_BLOCK)
        #error "FG_GUI_WIDGETBLOCK is defined: Do not include GuiMain inside of Widget header"
    #endif

    #include "fgManagerBase.h"

    #include "fgGuiBase.h"
    #include "fgGuiWidget.h"
    #include "fgGuiMenu.h"
    #include "fgGuiConsole.h"

    #include "fgGuiStyleManager.h"
    #include "fgGuiWidgetManager.h"
    #include "fgGuiWidgetFactory.h"

    #include "Event/fgEventManager.h"
    #include "Event/fgInputHandler.h"
    #ifndef FG_INC_RESOURCE_MANAGER
        #include "Resource/fgResourceManager.h"
    #endif

    #include "fgGuiDrawer.h"
    #include "fgGuiCallback.h"

namespace fg {
    namespace gui {
        class CGuiMain;
    };
};

//FG_EVENT_TOUCH_PRESSED	=	1,
//FG_EVENT_TOUCH_RELEASED	=	2,
//FG_EVENT_TOUCH_MOTION		=	3,
//FG_EVENT_TOUCH_TAP_FINISHED	=	4,

//FG_EVENT_MOUSE_PRESSED	=	5,
//FG_EVENT_MOUSE_RELEASED	=	6,
//FG_EVENT_MOUSE_MOTION		=	7,

    #define FG_MANAGER_GUI_MAIN     0x00000400

namespace fg {
    namespace gui {

        /**
         *
         */
        class CGuiMain : public fg::base::CManager, public CGuiBase {
        private:
            ///
            typedef fg::CVector<CGuiCallback *> guiCallbackVec;
            ///
            typedef guiCallbackVec::iterator guiCallbackVecItor;

        private:
            /// GUI style manager - loads and manages styles
            CStyleManager *m_styleMgr;
            /// Widget manager - loads structure sheets, holds handles
            /// to widgets. Every widget can be referenced from handle
            /// or special name
            fg::gui::CWidgetManager *m_widgetMgr;
            /// Widget factory 
            CWidgetFactory *m_widgetFactory;
            /// Pointer to external event manager class
            fg::event::CEventManager *m_pEventMgr;
            /// Pointer to external resource manager
            fg::resource::CResourceManager *m_pResourceMgr;
            /// GUI drawer special drawing batch
            CDrawer *m_guiDrawer;
            /// Pointer to external shader manager class
            fg::base::CManager *m_pShaderMgr;
            /// Pointer to external input receiver - touch/mouse/keyboard
            fg::event::CInputHandler *m_pPointerInputReceiver;

            /// Special callback for receiving touch events
            fg::event::CFunctionCallback *m_guiTouchCallback;
            /// Special callback for receiving mouse events
            fg::event::CFunctionCallback *m_guiMouseCallback;
            /// Special callback for handling link events (menu navigation)
            fg::gui::CGuiCallback *m_guiLinkCallback;

            /// Next menu link (can be null if no menu change is required)
            CMenu *m_changeToMenu;
            /// Currently displayed menu screen
            CMenu *m_currentMenu;
            /// Special console widget
            CConsole *m_console;
            /// Whether there is some kind of shifting / animation
            /// If so - no state updating will occur
            fgBool m_isMenuChanging;

            /// Special vector for holding gui callbacks
            /// It's used for easy free/deletion process
            guiCallbackVec m_guiCallbacks;

            /// Special bounding box describing current screen/window
            /// 3D float/double type box is used for compatibility 
            /// with widget functions
            gfx::BoundingBox3Df m_screenBox;

        protected:
            /**
             * 
             */
            void registerGuiCallbacks(void);
            /**
             * 
             */
            void unregisterGuiCallbacks(void);
            /**
             * 
             * @param eventMgr
             * @param resourceMgr
             */
            virtual void clear(void);

        public:
            /**
             * 
             * @param pEventMgr
             * @param pResourceMgr
             */
            CGuiMain(const std::string& stylesPath,
                     const std::string& widgetsPath,
                     fg::event::CEventManager *pEventMgr = NULL,
                     fg::resource::CResourceManager *pResourceMgr = NULL);
            /**
             * 
             */
            virtual ~CGuiMain();
            /**
             * 
             * @param w
             * @param h
             */
            void setScreenSize(const int w, const int h) {
                m_screenBox.size.x = (float)w;
                m_screenBox.size.y = (float)h;
            }

            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void);

        public:
            /**
             * 
             * @param pWidget
             * @param pCallback
             * @param callbackType
             * @return 
             */
            fgBool addWidgetCallback(fg::gui::CWidget *pWidget,
                                     fg::gui::CGuiCallback *pCallback,
                                     const fgGuiWidgetCallbackType callbackType);

            /**
             * 
             * @param widgetName
             * @param pCallback
             * @param callbackType
             * @return 
             */
            fgBool addWidgetCallback(const char *widgetName,
                                     fg::gui::CGuiCallback *pCallback,
                                     const fgGuiWidgetCallbackType callbackType);

            /**
             * 
             * @param widgetName
             * @param pCallback
             * @param callbackType
             * @return 
             */
            fgBool addWidgetCallback(const std::string& widgetName,
                                     fg::gui::CGuiCallback *pCallback,
                                     const fgGuiWidgetCallbackType callbackType);

        public:
            /**
             * 
             * @return 
             */
            fg::gui::CWidgetManager *getWidgetManager(void) const;
            /**
             * 
             * @return 
             */
            CWidgetFactory *getWidgetFactory(void) const;
            /**
             * 
             * @return 
             */
            CStyleManager *getStyleManager(void) const;
            /**
             * 
             * @return 
             */
            fg::event::CEventManager *getEventManager(void) const;
            /**
             * 
             * @return 
             */
            fg::resource::CResourceManager *getResourceManager(void) const;
            /**
             * 
             * @return 
             */
            fg::base::CManager *getShaderManager(void) const;
            /**
             * 
             * @return 
             */
            fg::event::CInputHandler *getPointerInputReceiver(void) const;

            /**
             * 
             * @param pEventMgr
             */
            void setEventManager(fg::event::CEventManager *pEventMgr);
            /**
             * 
             * @param pResourceMgr
             */
            void setResourceManager(fg::resource::CResourceManager *pResourceMgr);
            /**
             * 
             * @param pShaderMgr
             */
            void setShaderManager(fg::base::CManager *pShaderMgr);
            /**
             * 
             * @param pointerInputReceiver
             */
            void setPointerInputReceiver(fg::event::CInputHandler *pointerInputReceiver);

            /**
             * Update state of all widgets (called only when needed)
             */
            virtual void updateState(void);

            /**
             * This generates the buffers to draw
             */
            virtual void display(void);

            /**
             * This calls proper drawing functions. The screen will be updated
             */
            virtual void render(void); // #FIXME, just testing

            /**
             * 
             * @param argv
             * @return 
             */
            fgBool guiTouchHandler(fg::event::CArgumentList *argv);
            /**
             * 
             * @param argv
             * @return 
             */
            fgBool guiMouseHandler(fg::event::CArgumentList *argv);
            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            fgBool guiLinkHandler(CGuiMain *pGuiMain, fg::gui::CWidget *pWidget);
        };
    };
};

    #undef FG_INC_GUI_MAIN_BLOCK
#endif /* FG_INC_GUI_MAIN */
