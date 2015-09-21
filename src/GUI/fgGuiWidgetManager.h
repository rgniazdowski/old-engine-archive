/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_WIDGET_MANAGER
    #define FG_INC_GUI_WIDGET_MANAGER

    #include "fgGuiWidget.h"
    #include "Util/fgHandleManager.h"
    #include "fgManagerBase.h"
    #include "fgGuiWidgetFactory.h"

    #ifndef FG_INC_GUI_STYLE_MANAGER
        #include "fgGuiStyleManager.h"
    #endif

    #define FG_MANAGER_GUI_WIDGET   0x00000200  

namespace fg {
    namespace gui {

        /**
         *
         */
        class CWidgetManager :
        public fg::base::CManager,
        protected fg::util::CHandleManager<CWidget *, WidgetHandle> {
        public:
            ///
            typedef CWidgetManager self_type;
            ///
            typedef CWidgetManager type;
            ///
            typedef fg::base::CManager base_type;
            ///
            typedef fg::util::CHandleManager<CWidget *, WidgetHandle> handle_mgr_type;
            ///
            typedef WidgetHandle handle_type;
            ///
            typedef fg::CVector<CWidget *> WidgetVec;
            ///
            typedef WidgetVec::iterator WidgetVecItor;

        protected:
            /**
             * 
             */
            virtual void clear(void);

        public:
            /**
             * 
             * @param widgetFactory
             * @param styleMgr
             */
            CWidgetManager(CWidgetFactory *widgetFactory = NULL, CStyleManager *styleMgr = NULL);
            /**
             * 
             */
            virtual ~CWidgetManager();

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

            /**
             * 
             * @param typeName
             * @return 
             */
            static WidgetType widgetTypeFromName(const char* typeName);
            /**
             * 
             * @param typeName
             * @return 
             */
            static WidgetType widgetTypeFromName(const std::string& typeName);
            /**
             * 
             * @param pLinkHandlerCallback
             */
            void setLinkHandler(CGuiCallback* pLinkHandlerCallback) {
                m_pGuiLinkCallback = pLinkHandlerCallback;
            }
            /**
             * 
             * @param widgetFactory
             */
            void setWidgetFactory(CWidgetFactory* widgetFactory);
            /**
             * 
             * @return 
             */
            CWidgetFactory* getWidgetFactory(void) const;

            /**
             * 
             * @param styleMgr
             */
            void setStyleManager(CStyleManager* styleMgr);
            /**
             * 
             * @return 
             */
            CStyleManager* getStyleManager(void) const;

            /**
             * 
             * @param filePath
             * @return 
             */
            fgBool loadStructureSheet(const std::string& filePath);
            /**
             * 
             * @param filePath
             * @return 
             */
            fgBool loadStructureSheet(const char* filePath);

            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool addWidget(CWidget* pWidget);
            /**
             * 
             * @param pWidget
             * @param pFatherWidget
             * @return 
             */
            virtual fgBool addWidget(CWidget* pWidget, CWidget* pFatherWidget);
            /**
             * 
             * @param pWidget
             * @param wFatherUniqueID
             * @return 
             */
            virtual fgBool addWidget(CWidget* pWidget, const WidgetHandle& wFatherUniqueID);
            /**
             * 
             * @param pWidget
             * @param wFatherNameTag
             * @return 
             */
            virtual fgBool addWidget(CWidget* pWidget, const std::string& wFatherNameTag);
            /**
             * 
             * @param pWidget
             * @param wFatherNameTag
             * @return 
             */
            virtual fgBool addWidget(CWidget* pWidget, const char* wFatherNameTag);

            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool remove(CWidget* pWidget);
            /**
             * 
             * @param wUniqueID
             * @return 
             */
            virtual fgBool remove(const WidgetHandle& wUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool remove(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool remove(const char* nameTag);

            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool destroyWidget(CWidget*& pWidget);
            /**
             * 
             * @param wUniqueID
             * @return 
             */
            virtual fgBool destroyWidget(const WidgetHandle& wUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool destroyWidget(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool destroyWidget(const char* nameTag);

            /**
             * 
             * @param wUniqueID
             * @return 
             */
            virtual CWidget* get(const WidgetHandle& wUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual CWidget* get(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual CWidget* get(const char* nameTag);

            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool isManaged(CWidget* pWidget);
            /**
             * 
             * @param wUniqueID
             * @return 
             */
            virtual fgBool isManaged(const WidgetHandle& wUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool isManaged(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool isManaged(const char* nameTag);

            /**
             * 
             * @return 
             */
            WidgetVec& getRootWidgets(void);

            /**
             * 
             * @param path
             */
            void setWidgetsPath(const std::string& path);
            /**
             * 
             * @param path
             */
            void setWidgetsPath(const char* path);

        private:
            /// Pointer to the external widget factory
            CWidgetFactory* m_pWidgetFactory;
            /// Pointer to the external style manager
            CStyleManager* m_pStyleMgr;
            /// Pointer to the external link handler callback
            /// Declared in GuiMain
            CGuiCallback* m_pGuiLinkCallback;

            /// Widgets that have no fathers. For example a main screen, window, menu, etc
            WidgetVec m_rootWidgets;
            /// Widgets structure files base path
            std::string m_widgetsPath;
        };

    };
};

#endif /* FG_INC_GUI_WIDGET_MANAGER */
