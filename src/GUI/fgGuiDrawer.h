/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_DRAWER
    #define FG_INC_GUI_DRAWER

    #ifndef FG_INC_FONT_DRAWER
        #include "Font/fgFontDrawer.h"
    #endif

    #ifndef FG_INC_GFX_DRAWING_BATCH
        #include "GFX/fgGFXDrawingBatch.h"
    #endif 

    #ifndef FG_INC_GUI_STYLE_CONTENT
        #include "fgGuiStyleContent.h"
    #endif

    #ifndef FG_INC_MANAGER_BASE
        #include "fgManagerBase.h"
    #endif

/*
 *
 */
class fgGuiDrawer : public fgFontDrawer, public virtual fg::gfx::CDrawingBatch {
    friend class fgGuiMain;
    friend class fgGuiWidgetManager;
private:
    /// Pointer to the external resource manager
    /// Required for fast font/texture lookup
    /// #FIXME - should this be replaced with texture manager?
    fg::base::CManager *m_pResourceMgr;

public:
    //
    fgGuiDrawer();
    //
    virtual ~fgGuiDrawer();

public:
    /**
     * 
     * @return 
     */
    fg::base::CManager *getResourceManager(void) const {
        return m_pResourceMgr;
    }
    
    /**
     * 
     * @param pResourceMgr
     */
    virtual void setResourceManager(fg::base::CManager *pResourceMgr);
    
    /**
     * 
     */
    virtual void flush(void);
    /**
     * 
     */
    virtual void sortCalls(void);
    /**
     * 
     */
    virtual void render(void);

    /**
     * 
     * @param outTextSize
     * @param blockPos
     * @param blockSize
     * @param style
     * @param fmt
     */
    virtual void appendText2D(fgVec2f& outTextSize, const fgVec2f &blockPos, const fgVec2f &blockSize, fgGuiStyleContent& style, const char *fmt, ...);

    /**
     * 
     * @param pos
     * @param size
     * @param style
     */
    virtual void appendBackground2D(const fgVec2f &pos, const fgVec2f &size, fgGuiStyleContent& style);

    /**
     * 
     * @param pos
     * @param size
     * @param style
     */
    virtual void appendBorder2D(const fgVec2f &pos, const fgVec2f &size, fgGuiStyleContent& style);
    
};

#endif /* FG_INC_GUI_DRAWER */
