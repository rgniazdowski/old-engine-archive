/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_STYLE_MANAGER
    #define FG_INC_GUI_STYLE_MANAGER

    #include "Resource/fgDataManagerBase.h"
    #include "fgGuiStyle.h"

    #define FG_MANAGER_GUI_STYLE    0x00000040

/**
 *
 */
class fgGuiStyleManager : public fgDataManagerBase<fgGuiStyle*, fgGuiStyleHandle, fgGuiStyleTag> {
public:
    ///
    typedef fgDataManagerBase<fgGuiStyle*, fgGuiStyleHandle, fgGuiStyleTag> base_type;
    
protected:
    ///
    typedef hmDataVec smStyleVec;
    ///
    typedef hmDataVecItor smStyleVecItor;

public:
    /**
     * 
     */
    fgGuiStyleManager();
    /**
     * 
     */
    virtual ~fgGuiStyleManager();

protected:
    /**
     * 
     */
    virtual void clear(void);

public:
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
     * @param pStyle
     * @param nameTag
     * @return 
     */
    virtual fgBool insert(fgGuiStyle *pStyle, const std::string& nameTag);
    /**
     * 
     * @param shUniqueID
     * @param pStyle
     * @return 
     */
    virtual fgBool insertStyle(fgGuiStyle *pStyle);

    /**
     * 
     * @param info
     * @return 
     */
    virtual fgGuiStyle* request(const std::string& info);
    /**
     * 
     * @param info
     * @return 
     */
    virtual fgGuiStyle* request(const char *info);

    /**
     * 
     * @param path
     */
    void setStylesPath(const std::string &path);
    /**
     * 
     * @param path
     */
    void setStylesPath(const char *path);

private:
    /// Current path to GUIs style path
    std::string m_stylesPath;
};

#endif /* FG_INC_GUI_STYLE_MANAGER */
