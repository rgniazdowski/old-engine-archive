/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXDrawable.h
 * Author: vigilant
 *
 * Created on November 14, 2014, 11:01 AM
 */

#ifndef FG_INC_GFX_DRAWABLE
    #define FG_INC_GFX_DRAWABLE
    #define FG_INC_GFX_DRAWABLE_BLOCK

    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

typedef unsigned int fgGfxDrawableType;

    #define FG_GFX_DRAWABLE_INVALID     0


/**
 * 
 */
class fgGfxDrawable {
public:
    /**
     * 
     */
    fgGfxDrawable(const fgGfxDrawableType drawableType = FG_GFX_DRAWABLE_INVALID) : m_drawableType(drawableType) { }
    /**
     * 
     */
    virtual ~fgGfxDrawable() { }
    
public:
    
    virtual void draw(void) = 0;
    // Draw with relative 2D position
    virtual void draw(const fgVec2f& relPos) = 0;
    // Draw with relative 3D position
    virtual void draw(const fgVec3f& relPos) = 0;
    // Draw with given model matrix
    virtual void draw(const fgMatrix4f& modelMat) = 0;
    
public:
    /**
     * 
     * @return 
     */
    fgGfxDrawableType getDrawableType(void) const {
        return m_drawableType;
    }
    
protected:
    /**
     * 
     * @param drawableType
     */
    void setDrawableType(const fgGfxDrawableType drawableType) {
        m_drawableType = drawableType;
    }
    
private:
    fgGfxDrawableType m_drawableType;
};



    #undef FG_INC_GFX_DRAWABLE_BLOCK
#endif	/* FG_INC_GFX_DRAWABLE */

