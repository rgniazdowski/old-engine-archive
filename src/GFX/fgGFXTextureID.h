/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXTextureID.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:39 PM
 */

#ifndef _FG_GFX_TEXTUREID_H_
    #define	_FG_GFX_TEXTUREID_H_

#ifndef _FG_GFX_GL_H_
#include "fgGFXGL.h"
#endif

/*
 *
 */
struct fgGfxTextureID {
    /// Texture GFX ID - internal texture identifier
    fgGFXuint id;
    /// Texture target - 2D/3D
    fgGFXenum target;
    
    // Cast operator to GFX integer - will return texture internal ID
    operator fgGFXint() const {
        return (fgGFXint) id;
    }
    
    // Cast operator to GFX unsigned integer - will retrun texture internal ID
    operator fgGFXuint() const {
        return id;
    }
    
    // Returns the reference to the ID
    fgGFXuint& refID(void) {
        return id;
    }
    
    // Returns the const reference to the ID
    const fgGFXuint& refID(void) const {
        return id;
    }
    
    // Returns pointer to the ID
    fgGFXuint* ptrID(void) {
        return &id;
    }
    
    // Default constructor for the texture ID struct
    fgGfxTextureID(fgGFXuint _id = 0, fgGFXenum _target = GL_TEXTURE_2D) :
    id(_id), target(_target) {
    }
    
    // Comparison operator
    inline int operator ==(const fgGfxTextureID& b) const {
        if(b.id == this->id)
            return 1;
        return 0;
    }
    
    //
    inline int operator !=(const fgGfxTextureID& b) const {
        if(b.id != this->id)
            return 1;
        return 0;
    }
    
    //
    inline bool operator <(const fgGfxTextureID& a) const {
        return (bool)(this->id < a.id);
    }
    
    //
    inline bool operator >(const fgGfxTextureID& a) const {
        return (bool)(this->id > a.id);
    }
    
    //
    inline bool operator <=(const fgGfxTextureID& a) const {
        return (bool)(this->id <= a.id);
    }
    
    //
    inline bool operator >=(const fgGfxTextureID& a) const {
        return (bool)(this->id >= a.id);
    }
};

#endif	/* _FG_GFX_TEXTUREID_H_ */

