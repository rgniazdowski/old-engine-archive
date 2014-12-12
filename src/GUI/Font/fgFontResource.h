/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FONT_RESOURCE
    #define FG_INC_FONT_RESOURCE

    #include "Resource/fgResource.h"
    #include "Resource/fgResourceFactoryTypes.h"
    #include "GFX/Textures/fgTextureResource.h"
    #include "fgFontBuiltInTypes.h"

// This is standard grid size (used for fonts based on textures)
    #define FG_FONT_STANDARD_GRID_SIZE	16
    #define FG_FONT_STANDARD_ASCII_SIZE	(FG_FONT_STANDARD_GRID_SIZE*FG_FONT_STANDARD_GRID_SIZE)

    #define FG_FONT_TYPE_INVALID	0x0000
    #define FG_FONT_TYPE_TEXTURE	0x0001

typedef unsigned int fgFontType;

/*
 * Class definition for Font Resource - extends the Texture Resource
 */
class fgFontResource : public fgTextureResource {
public:
    // Base constructor of the font resource object
    fgFontResource();
    // Constructor with additional parameter (path)
    fgFontResource(const char *path);
    // Constructor with additional parameter (path)
    fgFontResource(std::string& path);
    // Base destructor of the font resource object
    virtual ~fgFontResource() {
        fgFontResource::destroy();
    }

    FG_RESOURCE_FACTORY_CREATE_FUNCTION(fgFontResource)

protected:
    // Clears the class data, this actually does not free allocated memory, 
    // just resets base class attributes
    virtual void clear(void);

public:
    // Create function loads/interprets data from file in ROM and place it in RAM memory.
    virtual fgBool create(void);
    // Destroy all loaded data including additional metadata (called with deconstructor)
    virtual void destroy(void);
    // Reloads any data, recreates the resource (refresh)
    virtual fgBool recreate(void);
    // Dispose completely of the all loaded data, free all memory
    virtual void dispose(void);
    // Check if resource is disposed (not loaded yet or disposed after)
    virtual fgBool isDisposed(void) const;
    /**
     * 
     * @return 
     */
    virtual int getStep(void) const {
        return m_step;
    }
    /**
     * 
     * @return 
     */
    fgFontType getFontType(void) const {
        return m_fontType;
    }
    /**
     * 
     * @return 
     */
    fgFontDataInfo &getDataInfo(void) {
        return m_info;
    }

protected:
    /// 
    fgFontType m_fontType;
    ///
    fgFontDataInfo m_info;
    /// 
    int m_step;
};

#endif /* FG_INC_FONT_RESOURCE */
