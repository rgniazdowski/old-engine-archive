/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FONT_BUILT_IN
    #define FG_INC_FONT_BUILT_IN
    #define FG_INC_FONT_BUILT_IN_BLOCK

    #include "fgFontResource.h"
    #include "fgFontBuiltInTypes.h"

/**
 *
 */
class fgFontBuiltInResource : public fgFontResource {
public:
    /**
     * 
     */
    fgFontBuiltInResource();
    /**
     * 
     * @param rawFontData
     */
    fgFontBuiltInResource(fgFontBuiltInRawData *rawFontData);
    /**
     * 
     */
    virtual ~fgFontBuiltInResource() {
        fgFontBuiltInResource::destroy();
    }

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
    virtual fgBool create(void);
    /**
     * 
     */
    virtual void destroy(void);
    /**
     * 
     * @return 
     */
    virtual fgBool recreate(void);
    /**
     * 
     */
    virtual void dispose(void);
    /**
     * 
     * @return 
     */
    virtual fgBool isDisposed(void) const;
    /**
     * 
     * @param rawFontData
     */
    void setBuiltInRawFontData(fgFontBuiltInRawData *rawFontData);
    /**
     * 
     * @return 
     */
    fgFontBuiltInRawData *getRawFontData(void) const {
        return m_rawFontData;
    }

private:
    /// 
    fgFontBuiltInRawData *m_rawFontData;
};

    #define FG_FONT_TYPE_STB_BUILTIN	0x0040

    #undef FG_INC_FONT_BUILT_IN_BLOCK
#endif /* FG_INC_FONT_BUILT_IN */