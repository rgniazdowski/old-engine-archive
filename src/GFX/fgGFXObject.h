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
    
    #include "fgGFXModelResource.h"

// BULLSHIT
typedef unsigned int fgGfxObjectType;

    #define FG_GFX_OBJECT_MODEL 0 // BULLSHIT

/*
 *
 */
class fgGfxObject {
private:
    std::string m_name;
    /// Internal object specific model matrix
    fgMatrix4f m_modelMat;
    ///
    fgGfxObjectType m_type;
    ///
    fgGfxModelResource *m_model;
    ///
    fgBool m_isManaged;
    
public:
    //
    fgGfxObject() : m_name(), 
    m_modelMat(),
    m_type(0),
    m_model(NULL),
    m_isManaged(FG_FALSE) { }
    
    //
    virtual ~fgGfxObject() { }
    
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
