/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_OBJECT_H_
    #define _FG_GFX_OBJECT_H_

    #include "Math/fgMathLib.h"
    #include "Util/fgTag.h"

    #include "fgGFXModelResource.h"

class fgGfxObject;

    #define FG_TAG_GFX_OBJECT_NAME	"GfxObject"
    #define FG_TAG_GFX_OBJECT		FG_TAG_TYPE(fgGfxObject)

FG_TAG_TEMPLATE_ID_AUTO(fgGfxObject, FG_TAG_GFX_OBJECT_NAME);
typedef FG_TAG_GFX_OBJECT fgGfxObjectTag;

// Special handle type for gfx object (scene object)
typedef fgHandle<fgGfxObjectTag> fgGfxObjectHandle;

typedef unsigned int fgGfxObjectType;

    #define FG_GFX_OBJECT_PLAIN 0
    #define FG_GFX_OBJECT_MODEL 1 
    //#define FG_GFX_OBJECT_DRAWABLE_PLAIN 2
    //#define FG_GFX_OBJECT_DRAWABLE_MODEL 3

/*
 *
 */
class fgGfxObject : public fgManagedObjectBase<fgGfxObjectHandle> {
private:
    /// Internal object specific model matrix
    fgMatrix4f m_modelMat;
    ///
    fgGfxObjectType m_type;
    /// #FIXME
    fgGfxModelResource *m_model;

public:
    /**
     * 
     */
    fgGfxObject() : m_modelMat(),
    m_type(FG_GFX_OBJECT_PLAIN),
    m_model(NULL) { }

    /**
     * 
     */
    virtual ~fgGfxObject() { }

    /**
     * 
     * @return 
     */
    inline fgGfxObjectType getType(void) const {
        return m_type;
    }
    /**
     * 
     * @return 
     */
    inline fgGfxModelResource* getModel(void) const {
        return m_model;
    }

    /**
     * 
     * @param model
     */
    virtual inline void setModel(fgGfxModelResource *pModel) {
        m_model = pModel;
        m_type = FG_GFX_OBJECT_MODEL;
    }

    /**
     * 
     * @return 
     */
    inline fgMatrix4f& getRefModelMatrix(void) {
        return m_modelMat;
    }

    /**
     * 
     * @return 
     */
    inline const fgMatrix4f& getRefModelMatrix(void) const {
        return m_modelMat;
    }

    /**
     * 
     * @param modelMat
     */
    inline void setModelMatrix(const fgMatrix4f& modelMat) {
        m_modelMat = modelMat;
    }

protected:
    /**
     * 
     * @param objectType
     */
    inline void setType(const fgGfxObjectType objectType) {
        m_type = objectType;
    }
};

#endif /* _FG_GFX_OBJECT_H_ */
