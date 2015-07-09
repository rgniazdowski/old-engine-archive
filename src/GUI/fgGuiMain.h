/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

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

    #include "fgGuiWidgetManager.h"
    #include "fgGuiWidgetFactory.h"

    #include "Event/fgEventManager.h"
    #include "Event/fgInputHandler.h"    

    #include "fgGuiDrawer.h"
    #include "fgGuiCallback.h"

namespace fg {
    namespace gui {
        class CGuiMain;
        class CWidget;
        class CMenu;
        class CConsole;
        class CWidgetManager;
        class CWidgetFactory;
        class CStyleManager;
    }
    namespace resource {
        class CResourceManager;
        class CResource;
        class CResourceGroup;
    }
}

    #define FG_MANAGER_GUI_MAIN     0x00000400

namespace fg {
    namespace gui {

        /**
         *
         */
        class CGuiMain : public fg::base::CManager, public CGuiBase {
        private:
            ///
            typedef CVector<CGuiCallback*> GuiCallbackVec;
            ///
            typedef GuiCallbackVec::iterator GuiCallbackVecItor;

        private:
            /// GUI style manager - loads and manages styles
            CStyleManager* m_styleMgr;
            /// Widget manager - loads structure sheets, holds handles
            /// to widgets. Every widget can be referenced from handle
            /// or special name
            CWidgetManager* m_widgetMgr;
            /// Widget factory 
            CWidgetFactory* m_widgetFactory;
            /// Pointer to external event manager class
            event::CEventManager* m_pEventMgr;
            /// Pointer to external resource manager
            resource::CResourceManager* m_pResourceMgr;
            /// GUI drawer special drawing batch
            CDrawer* m_guiDrawer;
            /// Pointer to external shader manager class
            base::CManager* m_pShaderMgr;
            /// Pointer to external input receiver - touch/mouse/keyboard
            event::CInputHandler* m_pInputHandler;

            /// Special callback for receiving touch events
            event::CFunctionCallback* m_guiTouchCallback;
            /// Special callback for receiving mouse events
            event::CFunctionCallback* m_guiMouseCallback;
            ///
            event::CFunctionCallback* m_guiKeyboardCallback;
            /// Special callback for handling link events (menu navigation)
            CGuiCallback* m_guiLinkCallback;

            /// Next menu link (can be null if no menu change is required)
            CMenu* m_changeToMenu;
            /// Currently displayed menu screen
            CMenu* m_currentMenu;
            /// Special console widget
            CConsole* m_console;
            /// Whether there is some kind of shifting / animation
            /// If so - no state updating will occur
            fgBool m_isMenuChanging;

            /// Special vector for holding gui callbacks
            /// It's used for easy free/deletion process
            GuiCallbackVec m_guiCallbacks;

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
                     event::CEventManager* pEventMgr = NULL,
                     resource::CResourceManager* pResourceMgr = NULL);
            /**
             * 
             */
            virtual ~CGuiMain();
            /**
             * 
             * @param w
             * @param h
             */
            inline void setScreenSize(const int w, const int h) {
                m_screenBox.size.x = (float)w;
                m_screenBox.size.y = (float)h;
            }
            /**
             * 
             * @return
             */
            inline Vector3f& getScreenSize(void) {
                return m_screenBox.size;
            }
            /**
             *
             * @return
             */
            inline Vector3f const& getScreenSize(void) const {
                return m_screenBox.size;
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

            //------------------------------------------------------------------

        public:

            /**
             *
             * @param name
             * @param size
             * @return
             */
            fgBool createBuiltInFont(const char* name, unsigned int size = 32);
            /**
             *
             * @param name
             * @param size
             * @return
             */
            fgBool createBuiltInFont(const std::string& name, unsigned int size = 32);

            /**
             *
             * @param name
             * @return
             */
            fgBool disposeBuiltInFont(const char* name);
            /**
             * 
             * @param name
             * @return
             */
            fgBool disposeBuiltInFont(const std::string& name);


            /**
             *
             * @param name
             * @return
             */
            fgBool destroyBuiltInFont(const char* name);
            /**
             *
             * @param name
             * @return
             */
            fgBool destroyBuiltInFont(const std::string& name);

            /**
             * 
             * @param pWidget
             * @param pCallback
             * @param callbackType
             * @return 
             */
            fgBool addWidgetCallback(CWidget* pWidget,
                                     CGuiCallback* pCallback,
                                     const fgGuiWidgetCallbackType callbackType);

            /**
             * 
             * @param widgetName
             * @param pCallback
             * @param callbackType
             * @return 
             */
            fgBool addWidgetCallback(const char *widgetName,
                                     CGuiCallback* pCallback,
                                     const fgGuiWidgetCallbackType callbackType);

            /**
             * 
             * @param widgetName
             * @param pCallback
             * @param callbackType
             * @return 
             */
            fgBool addWidgetCallback(const std::string& widgetName,
                                     CGuiCallback* pCallback,
                                     const fgGuiWidgetCallbackType callbackType);

            ////////////////////////////////////////////////////////////////////////

        public:
            /**
             * 
             * @return 
             */
            CDrawer* getDrawer(void) const;
            /**
             * 
             * @return 
             */
            CWidgetManager* getWidgetManager(void) const;
            /**
             * 
             * @return 
             */
            CWidgetFactory* getWidgetFactory(void) const;
            /**
             * 
             * @return 
             */
            CStyleManager* getStyleManager(void) const;
            /**
             * 
             * @return 
             */
            event::CEventManager* getEventManager(void) const;
            /**
             * 
             * @return 
             */
            resource::CResourceManager* getResourceManager(void) const;
            /**
             * 
             * @return 
             */
            fg::base::CManager* getShaderManager(void) const;
            /**
             * 
             * @return 
             */
            event::CInputHandler* getInputHandler(void) const;

            /**
             * 
             * @param pEventMgr
             */
            void setEventManager(event::CEventManager* pEventMgr);
            /**
             * 
             * @param pResourceMgr
             */
            void setResourceManager(resource::CResourceManager* pResourceMgr);
            /**
             * 
             * @param pShaderMgr
             */
            void setShaderManager(fg::base::CManager* pShaderMgr);
            /**
             * 
             * @param pointerInputReceiver
             */
            void setInputHandler(event::CInputHandler* pointerInputReceiver);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param menuName
             */
            void changeMenu(const char *menuName);
            /**
             * 
             * @param menuName
             */
            void changeMenu(const std::string& menuName);
            /**
             * 
             * @param pMenu
             */
            void changeMenu(CWidget* pMenu);

            /**
             * 
             * @param menuName
             */
            void setCurrentMenu(const char *menuName, fgBool shouldUpdateState = FG_TRUE);
            /**
             * 
             * @param menuName
             */
            void setCurrentMenu(const std::string& menuName, fgBool shouldUpdateState = FG_TRUE);
            /**
             * 
             * @param pMenu
             */
            void setCurrentMenu(CWidget* pMenu, fgBool shouldUpdateState = FG_TRUE);
            /**
             *
             * @return
             */
            CMenu* getCurrentMenu(void) const {
                return m_currentMenu;
            }

            ////////////////////////////////////////////////////////////////////

            /**
             * Update state of all widgets (called only when needed)
             */
            virtual void updateState(void);

            /**
             * This generates the buffers to draw
             */
            virtual void preRender(void);

            /**
             * This calls proper drawing functions. The screen will be updated
             */
            virtual void render(void); // #FIXME, just testing

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param argv
             * @return 
             */
            fgBool guiTouchHandler(event::CArgumentList* argv);
            /**
             * 
             * @param argv
             * @return 
             */
            fgBool guiMouseHandler(event::CArgumentList* argv);
            /**
             * 
             * @param argv
             * @return
             */
            fgBool guiKeyboardHandler(event::CArgumentList* argv);
            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            fgBool guiLinkHandler(CGuiMain* pGuiMain, CWidget* pWidget);
        }; // class CGuiMain
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_MAIN_BLOCK
#endif /* FG_INC_GUI_MAIN */
