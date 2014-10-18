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

    #ifndef _FG_RESOURCE_MANAGER_H_
        #include "Resource/fgResourceManager.h"
    #endif 

    #ifndef _FG_GUI_STYLE_CONTENT_H_
        #include "fgGuiStyleContent.h"
    #endif

/*
 *
 */
class fgGuiDrawer : protected fgGfxDrawingBatch {
    friend class fgGuiMain;
    friend class fgGuiWidgetManager;
private:
    ///
    fgFontDrawer *m_fontDrawer;
    ///
    fgResourceManager *m_resourceMgr;
    ///
    fgColor4f m_color;

public:
    //
    fgGuiDrawer();
    //
    virtual ~fgGuiDrawer();

public:
    //
    fgFontDrawer *getFontDrawer(void) const;
    //
    fgResourceManager *getResourceManager(void) const;
    //
    virtual void setResourceManager(fgResourceManager *resourceMgr);

    //
    virtual void setShaderManager(fgManagerBase *shaderMgr);

    //
    virtual int getZIndex(void) const {
        return m_zIndex;
    }

    //
    virtual void setZIndex(const int zIndex) {
        m_zIndex = zIndex;
        m_fontDrawer->setZIndex(zIndex);
    }

    //
    virtual void upZIndex(void) {
        m_zIndex++;
        m_fontDrawer->setZIndex(m_zIndex);
    }

    //
    virtual void downZIndex(void) {
        m_zIndex--;
        m_fontDrawer->setZIndex(m_zIndex);
    }

    // Set active color for the next data
    virtual void setColor(const fgColor3f& color);
    // Set active color for the next data
    virtual void setColor(const fgColor4f& color);
    // This will reset used color
    virtual void resetColor(void);

    //
    virtual void flush(void);

    //
    virtual void sortCalls(void);

    //
    virtual void render(void);

    //
    virtual void appendText2D(const fgVec2f &blockPos, const fgVec2f &blockSize, fgGuiStyleContent& style, const char *fmt, ...);

    //
    virtual void appendBackground2D(const fgVec2f &pos, const fgVec2f &size, fgGuiStyleContent& style);

    //
    virtual void appendBorder2D(const fgVec2f &pos, const fgVec2f &size, fgGuiStyleContent& style);
};

#endif /* _FG_GUI_DRAWER_H_ */
