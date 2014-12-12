/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_TEXT_AREA
    #define FG_INC_GUI_TEXT_AREA

    #include "fgGuiScrollArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #include "fgVector.h"
    
/**
 * 
 */
class fgGuiTextArea : public fgGuiScrollArea {
public:
    ///
    typedef fgGuiScrollArea base_type;
    
protected:
    ///
    fgStringVector m_textData;
    ///
    struct TextAreaSize {
        ///
        unsigned short cols; // x
        ///
        unsigned short rows; // y
        
        TextAreaSize(unsigned short _cols = 32, unsigned short _rows = 1) :
        cols(_cols), rows(_rows) {            
        }
    } m_textAreaSize;

    
    
protected:
    /**
     * 
     */
    virtual void setDefaults(void);

public:
    /**
     * 
     */
    fgGuiTextArea();
    /**
     * 
     */
    virtual ~fgGuiTextArea();

    /**
     * 
     * @return 
     */
    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiTextArea);

    /**
     * 
     * @param guiLayer
     */
    virtual void display(fgGuiDrawer *guiLayer);
    
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
     * @param text
     */
    virtual void pushText(const char *text) {
        m_textData.push_back(std::string(text));
    }
    
    /**
     * 
     * @param text
     */
    virtual void pushText(const std::string &text) {
        m_textData.push_back(text);
    }
    
    /**
     * 
     * @param text
     */
    virtual void setText(const std::string &text) {
        m_text.clear();
        m_textData.clear_optimised();
        m_textData.resize(0);
        m_textData.push_back(text);
    }
    
    /**
     * 
     * @param text
     */
    virtual void setText(const char *text) {
        if(text) {
            m_textData.clear_optimised();
            m_textData.resize(0);
            m_textData.push_back(std::string(text));
        }
        m_text.clear();
    }
    /**
     * 
     */
    virtual void clearText(void) {
        m_text.clear();
        m_textData.clear_optimised();
        m_textData.resize(0);
    }

};

#endif /* FG_INC_GUI_TEXT_AREA */
