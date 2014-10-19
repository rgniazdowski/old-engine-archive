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

// BULLSHIT
typedef unsigned int fgGfxObjectType;

    #define FG_GFX_OBJECT_MODEL 0 // BULLSHIT

/*
 *
 */
class fgGfxObject {
private:
    /// Name of the gfx object (used mainly for the scene representation)
    std::string m_nameTag;
    /// Internal object specific model matrix
    fgMatrix4f m_modelMat;
    ///
    fgGfxObjectType m_type;
    ///
    fgGfxModelResource *m_model;
    ///
    fgGfxObjectHandle m_handle;
    ///
    fgBool m_isManaged;

public:
    //
    fgGfxObject() : m_nameTag(),
    m_modelMat(),
    m_type(0),
    m_model(NULL),
    m_isManaged(FG_FALSE) { }

    //
    virtual ~fgGfxObject() { }

    // Set object name (string TAG/ID)
    inline void setName(const char *name) {
        m_nameTag = name;
    }
    // Set object name (string TAG/ID)
    inline void setName(const std::string& name) {
        m_nameTag = name;
    }
    // Get object name string
    inline std::string getName(void) const {
        return m_nameTag;
    }
    // Get reference to object name string
    inline std::string& getName(void) {
        return m_nameTag;
    }
    // Get object name (TAG/string ID) as C-like string (char array)
    inline const char* getNameStr(void) const {
        return m_nameTag.c_str();
    }

    // Return the object handle ID
    inline fgGfxObjectHandle getHandle(void) const {
        return m_handle;
    }

    // Set the object handle ID 
    inline void setHandle(const fgGfxObjectHandle& handle) {
        m_handle = handle;
    }

    //
    inline fgGfxObjectHandle& getRefHandle(void) {
        return m_handle;
    }

    //
    inline const fgGfxObjectHandle& getRefHandle(void) const {
        return m_handle;
    }

    //
    inline void setManaged(const fgBool toggle = FG_TRUE) {
        m_isManaged = toggle;
    }

    //
    inline fgBool isManaged(void) const {
        return m_isManaged;
    }

    //
    inline fgGfxModelResource* getModel(void) const {
        return m_model;
    }

    //
    inline void setModel(fgGfxModelResource *model) {
        m_model = model;
    }

    //
    inline fgMatrix4f& getRefModelMatrix(void) {
        return m_modelMat;
    }

    //
    inline const fgMatrix4f& getRefModelMatrix(void) const {
        return m_modelMat;
    }

    //
    inline void setModelMatrix(const fgMatrix4f& modelMat) {
        m_modelMat = modelMat;
    }

protected:

};

#endif /* _FG_GFX_OBJECT_H_ */
