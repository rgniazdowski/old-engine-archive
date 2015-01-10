/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_CONSOLE
    #define FG_INC_GUI_CONSOLE
    #define FG_INC_GUI_CONSOLE_BLOCK

    #include "fgGuiTextArea.h"
    #include "fgGuiWidgetFactoryTypes.h"
    
struct fgStatus;

/**
 *
 */
class fgGuiConsole : public fgGuiTextArea {
public:
    ///
    typedef fgGuiTextArea base_type;

protected:
    ///
    unsigned int m_numConsoleRecords;

protected:
    /**
     * 
     */
    virtual void setDefaults(void);

public:
    /**
     * 
     */
    fgGuiConsole();
    /**
     * 
     */
    virtual ~fgGuiConsole();

    /**
     * 
     * @param guiLayer
     */
    virtual void display(fgGuiDrawer *guiLayer);

    /**
     * 
     * @return 
     */
    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiConsole);

    using fgGuiWidget::updateBounds;

    /**
     * 
     * @return 
     */
    virtual fgBoundingBox3Df updateBounds(void);

    /**
     * 
     */
    virtual void refresh(void);

public:
    /**
     * 
     * @return 
     */
    unsigned int getNumConsoleRecords(void) const {
        return m_numConsoleRecords;
    }
    /**
     * 
     * @param statusVec
     */
    void updateFromStatusVec(const fg::CVector<fgStatus *> &statusVec);

public:
    /**
     * 
     * @param text
     */
    virtual void pushText(const char *text) {
        base_type::pushText(text);
        m_numConsoleRecords = m_textData.size();
    }
    /**
     * 
     * @param text
     */
    virtual void pushText(const std::string &text) {
        base_type::pushText(text);
        m_numConsoleRecords = m_textData.size();
    }
    /**
     * 
     * @param text
     */
    virtual void setText(const std::string &text) {
        base_type::setText(text);
        m_numConsoleRecords = m_textData.size();
    }
    /**
     * 
     * @param text
     */
    virtual void setText(const char *text) {
        base_type::setText(text);
        m_numConsoleRecords = m_textData.size();
    }
    /**
     * 
     */
    virtual void clearText(void) {
        base_type::clearText();
        m_numConsoleRecords = m_textData.size();
    }
};

    #undef FG_INC_GUI_CONSOLE_BLOCK

#endif /* FG_INC_GUI_CONSOLE */
