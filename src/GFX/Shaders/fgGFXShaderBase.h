/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_BASE_H_
#define _FG_GFX_SHADER_BASE_H_

#include "fgGFXShaderDefs.h"

#include "Hardware/fgQualityTypes.h"
#include "Resource/fgDataObjectBase.h"
#include "Util/fgHandle.h"
#include "Util/fgTag.h"
#include <map>

class fgGfxShader;

#define FG_TAG_GFX_SHADER_NAME	"GfxShader"
#define FG_TAG_GFX_SHADER		FG_TAG_TYPE(fgGfxShader)

FG_TAG_TEMPLATE_ID_AUTO(fgGfxShader, FG_TAG_GFX_SHADER_NAME);
typedef FG_TAG_GFX_SHADER fgGfxShaderTag;

// Special handle type for shader program
typedef fgHandle<fgGfxShaderTag> fgGfxShaderHandle;

/*
 *
 */
class fgGfxShaderBase : public fgDataObjectBase<fgGfxShaderHandle, fgQuality> {
    friend class fgGfxShader;
    friend class fgGfxShaderProgram;
    friend class fgGfxShaderManager;
protected:
    typedef std::map<fgGFXenum, fgGFXint> objParamMap;
    typedef objParamMap::iterator objParamMapItor;

    enum shaderBaseType {
        FG_GFX_BASE_TYPE_INVALID = 0,
        FG_GFX_BASE_TYPE_SHADER = 1,
        FG_GFX_BASE_TYPE_PROGRAM = 2
    };

protected:
    ///
    objParamMap m_params;
    ///
    char *m_log;
    ///
    fgGFXuint m_gfxID;
    /// 
    shaderBaseType m_baseType;
    /// #FIXME ?
    fgBool m_isManaged;

protected:

    void setManaged(fgBool toggle = FG_TRUE) {
        m_isManaged = toggle;
    }

public:
    //
    fgGfxShaderBase();
    // 
    virtual ~fgGfxShaderBase();

    fgBool isManaged(void) const {
        return m_isManaged;
    }

    // 

    fgGFXuint getGfxID(void) const {
        return m_gfxID;
    }

    //

    fgGFXuint & getRefGfxID(void) {
        return m_gfxID;
    }

    //

    fgGFXint getParam(fgGFXenum pname) {
        return m_params[pname];
    }

    //

    const char *getLog(void) const {
        return m_log;
    }

    //
    virtual void clearAll(void) = 0;

protected:
    //
    void updateLog(void);
    //
    void updateParams(void);
    //
    fgGFXint updateParam(fgGFXenum pname);
};

#endif /*_FG_GFX_SHADER_BASE_H_ */
