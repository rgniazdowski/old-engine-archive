/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_DRAWER_H_
    #define _FG_GUI_DRAWER_H_

    #ifndef _FG_FONT_DRAWER_H_
        #include "Font/fgFontDrawer.h"
    #endif

    #ifndef _FG_GFX_DRAWING_BATCH_H_
        #include "GFX/fgGFXDrawingBatch.h"
    #endif 

    #ifndef _FG_GUI_STYLE_CONTENT_H_
        #include "fgGuiStyleContent.h"
    #endif

    #ifndef _FG_MANAGER_BASE_H_
        #include "fgManagerBase.h"
    #endif

/*
 *
 */
class fgGuiDrawer : public fgFontDrawer, protected virtual fgGfxDrawingBatch {
    friend class fgGuiMain;
    friend class fgGuiWidgetManager;
private:
    /// Pointer to the external resource manager
    /// Required for fast font/texture lookup
    /// #FIXME - should this be replaced with texture manager?
    fgManagerBase *m_pResourceMgr;

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
    fgManagerBase *getResourceManager(void) const {
        return m_pResourceMgr;
    }
    
    /**
     * 
     * @param pResourceMgr
     */
    virtual void setResourceManager(fgManagerBase *pResourceMgr);
    /**
     * 
     * @param pShaderMgr
     */
    virtual void setShaderManager(fgManagerBase *pShaderMgr);

    /**
     * 
     * @return 
     */
    virtual int getZIndex(void) const {
        return m_zIndex;
    }
    /**
     * 
     * @param zIndex
     */
    virtual void setZIndex(const int zIndex) {
        m_zIndex = zIndex;
    }
    /**
     * 
     */
    virtual void upZIndex(void) {
        m_zIndex++;
    }
    /**
     * 
     */
    virtual void downZIndex(void) {
        m_zIndex--;
    }

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

#endif /* _FG_GUI_DRAWER_H_ */
