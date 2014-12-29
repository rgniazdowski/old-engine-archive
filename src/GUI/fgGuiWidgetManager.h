/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

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

/**
 *
 */
class fgGuiWidgetManager : public fg::base::Manager, protected fgHandleManager<fgGuiWidget *, fgGuiWidgetHandle> {
public:
    ///
    typedef fgHandleManager<fgGuiWidget *, fgGuiWidgetHandle> base_type;
    ///
    typedef fgGuiWidgetHandle handle_type;
    ///
    typedef fgVector<fgGuiWidget *> widgetVec;
    ///
    typedef widgetVec::iterator widgetVecItor;
    
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
    fgGuiWidgetManager(fgGuiWidgetFactory *widgetFactory = NULL, fgGuiStyleManager *styleMgr = NULL);
    /**
     * 
     */
    virtual ~fgGuiWidgetManager();
    
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
    static fgGuiWidgetType widgetTypeFromName(const char *typeName);
    /**
     * 
     * @param typeName
     * @return 
     */
    static fgGuiWidgetType widgetTypeFromName(const std::string& typeName);

    /**
     * 
     * @param pLinkHandlerCallback
     */
    void setLinkHandler(fgGuiCallback *pLinkHandlerCallback) {
        m_pGuiLinkCallback = pLinkHandlerCallback;
    }
    /**
     * 
     * @param widgetFactory
     */
    void setWidgetFactory(fgGuiWidgetFactory *widgetFactory);
    /**
     * 
     * @return 
     */
    fgGuiWidgetFactory *getWidgetFactory(void) const;

    /**
     * 
     * @param styleMgr
     */
    void setStyleManager(fgGuiStyleManager *styleMgr);
    /**
     * 
     * @return 
     */
    fgGuiStyleManager *getStyleManager(void) const;

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
    fgBool loadStructureSheet(const char *filePath);

    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool addWidget(fgGuiWidget *pWidget);
    /**
     * 
     * @param pWidget
     * @param pFatherWidget
     * @return 
     */
    virtual fgBool addWidget(fgGuiWidget *pWidget, fgGuiWidget *pFatherWidget);
    /**
     * 
     * @param pWidget
     * @param wFatherUniqueID
     * @return 
     */
    virtual fgBool addWidget(fgGuiWidget *pWidget, const fgGuiWidgetHandle& wFatherUniqueID);
    /**
     * 
     * @param pWidget
     * @param wFatherNameTag
     * @return 
     */
    virtual fgBool addWidget(fgGuiWidget *pWidget, const std::string& wFatherNameTag);
    /**
     * 
     * @param pWidget
     * @param wFatherNameTag
     * @return 
     */
    virtual fgBool addWidget(fgGuiWidget *pWidget, const char* wFatherNameTag);

    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool remove(fgGuiWidget *pWidget);
    /**
     * 
     * @param wUniqueID
     * @return 
     */
    virtual fgBool remove(const fgGuiWidgetHandle& wUniqueID);
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
    virtual fgBool remove(const char *nameTag);

    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool destroyWidget(fgGuiWidget*& pWidget);
    /**
     * 
     * @param wUniqueID
     * @return 
     */
    virtual fgBool destroyWidget(const fgGuiWidgetHandle& wUniqueID);
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
    virtual fgBool destroyWidget(const char *nameTag);

    /**
     * 
     * @param wUniqueID
     * @return 
     */
    virtual fgGuiWidget* get(const fgGuiWidgetHandle& wUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgGuiWidget* get(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgGuiWidget* get(const char *nameTag);

    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool isManaged(fgGuiWidget *pWidget);
    /**
     * 
     * @param wUniqueID
     * @return 
     */
    virtual fgBool isManaged(const fgGuiWidgetHandle& wUniqueID);
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
    virtual fgBool isManaged(const char *nameTag);

    /**
     * 
     * @return 
     */
    widgetVec& getRefRootWidgets(void);

    /**
     * 
     * @param path
     */
    void setWidgetsPath(const std::string &path);
    /**
     * 
     * @param path
     */
    void setWidgetsPath(const char *path);
    
private:
    /// Pointer to the external widget factory
    fgGuiWidgetFactory *m_pWidgetFactory;
    /// Pointer to the external style manager
    fgGuiStyleManager *m_pStyleMgr;
    /// Pointer to the external link handler callback
    /// Declared in GuiMain
    fgGuiCallback *m_pGuiLinkCallback;

    /// Widgets that have no fathers. For example a main screen, window, menu, etc
    widgetVec m_rootWidgets;
    /// Widgets structure files base path
    std::string m_widgetsPath;
};

#endif /* FG_INC_GUI_WIDGET_MANAGER */
