/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXBufferID.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:39 PM
 */

#ifndef _FG_GFX_BUFFERID_H_
    #define	_FG_GFX_BUFFERID_H_

#ifndef _FG_GFX_GL_H_
#include "fgGFXGL.h"
#endif

/*
 *
 */
struct fgGfxBufferID {
    fgGFXuint id;
    fgGFXenum target;
    fgGFXenum usage;
    operator fgGFXint() const {
        return (fgGFXint) id;
    }
    operator fgGFXuint() const {
        return id;
    }
    fgGFXuint& refID(void) {
        return id;
    }
    fgGFXuint* ptrID(void) {
        return &id;
    }
    fgGfxBufferID(fgGFXuint _id = 0, fgGFXenum _target = (fgGFXenum) 0) :
    id(_id), target(_target) {
    }
};

#endif	/* _FG_GFX_BUFFERID_H_ */

