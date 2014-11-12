/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXDrawableObject.h
 * Author: vigilant
 *
 * Created on November 12, 2014, 6:08 PM
 */

#ifndef _FG_GFX_DRAWABLE_OBJECT_H_
    #define	_FG_GFX_DRAWABLE_OBJECT_H_
    #define _FG_GFX_DRAWABLE_OBJECT_H_BLOCK_

    #include "fgGFXObject.h"
    #include "fgGFXDrawCall.h"

    #define FG_GFX_OBJECT_DRAWABLE_PLAIN 2 // #FIXME ?
    #define FG_GFX_OBJECT_DRAWABLE_MODEL 3 // #FIXME ?

/**
 * 
 */
class fgGfxDrawableObject : public fgGfxObject, public fgGfxDrawCall {
public:
    /**
     * 
     */
    fgGfxDrawableObject();
    /**
     * 
     * @param orig
     */
    fgGfxDrawableObject(const fgGfxDrawableObject& orig);
    /**
     * 
     */
    virtual ~fgGfxDrawableObject();

private:

public:
    /**
     * 
     * @param pModel
     */
    virtual inline void setModel(fgGfxModelResource *pModel) {
        if(pModel) {
            fgGfxObject::setModel(pModel);
            setupFromModel(pModel);
            fgGfxObject::setType(FG_GFX_OBJECT_DRAWABLE_MODEL);
        }
    }
    /**
     * 
     * @param toggle
     */
    inline void setManaged(fgBool toggle = FG_TRUE) {
        fgGfxObject::setManaged(toggle);
        fgGfxDrawCall::setManaged(toggle);
    }
    /**
     * 
     * @return 
     */
    inline fgBool isManaged(void) const {
        return fgGfxObject::m_isManaged;
    }
};

    #undef _FG_GFX_DRAWABLE_OBJECT_H_BLOCK_
#endif	/* _FG_GFX_DRAWABLE_OBJECT_H_ */
