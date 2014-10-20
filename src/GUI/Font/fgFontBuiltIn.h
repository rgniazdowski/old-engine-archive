/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_FONT_BUILT_IN_H_
    #define _FG_FONT_BUILT_IN_H_

    #include "fgFontResource.h"
    #include "fgFontBuiltInTypes.h"

/*
 *
 */
class fgFontBuiltInResource : public fgFontResource {
public:
    //
    fgFontBuiltInResource();
    //
    fgFontBuiltInResource(fgFontBuiltInRawData *rawFontData);
    //
    virtual ~fgFontBuiltInResource() {
        fgFontBuiltInResource::destroy();
    }

protected:
    //
    virtual void clear(void);

public:
    //
    virtual fgBool create(void);
    //
    virtual void destroy(void);
    //
    virtual fgBool recreate(void);
    //
    virtual void dispose(void);
    //
    virtual fgBool isDisposed(void) const;
    //
    void setBuiltInRawFontData(fgFontBuiltInRawData *rawFontData);

    //
    fgFontBuiltInRawData *getRawFontData(void) const {
        return m_rawFontData;
    }

private:
    fgFontBuiltInRawData *m_rawFontData;
};

    #define FG_FONT_TYPE_STB_BUILTIN	0x0040

#endif /* _FG_FONT_BUILT_IN_H_ */