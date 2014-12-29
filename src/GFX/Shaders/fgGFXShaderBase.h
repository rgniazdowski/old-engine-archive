/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SHADER_BASE
    #define FG_INC_GFX_SHADER_BASE

    #include "fgGFXShaderDefs.h"

    #include "Hardware/fgQualityTypes.h"
    #include "Resource/fgManagedDataFileBase.h"
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

/**
 *
 */
class fgGfxShaderBase : public fgManagedDataFileBase<fgGfxShaderHandle, fgQuality> {
    friend class fgGfxShader;
    friend class fgGfxShaderProgram;
    friend class fgGfxShaderManager;
public:
    ///
    typedef fgManagedDataFileBase<fgGfxShaderHandle, fgQuality> base_type;
    ///
    typedef fgGfxShaderTag tag_type;
    
protected:
    ///
    typedef std::map<fgGFXenum, fgGFXint> objParamMap;
    ///
    typedef objParamMap::iterator objParamMapItor;

    /**
     *
     */
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

public:
    /**
     * 
     */
    fgGfxShaderBase();
    /**
     * 
     */
    virtual ~fgGfxShaderBase();
    /**
     * 
     * @return 
     */
    fgGFXuint getGfxID(void) const {
        return m_gfxID;
    }
    /**
     * 
     * @return 
     */
    fgGFXuint & getRefGfxID(void) {
        return m_gfxID;
    }
    /**
     * 
     * @param pname
     * @return 
     */
    fgGFXint getParam(fgGFXenum pname) {
        return m_params[pname];
    }
    /**
     * 
     * @return 
     */
    const char *getLog(void) const {
        return m_log;
    }
    /**
     * 
     */
    virtual void clearAll(void) = 0;

protected:
    /**
     * 
     */
    void updateLog(void);
    /**
     * 
     */
    void updateParams(void);
    /**
     * 
     * @param pname
     * @return 
     */
    fgGFXint updateParam(fgGFXenum pname);
};

#endif /*FG_INC_GFX_SHADER_BASE */
