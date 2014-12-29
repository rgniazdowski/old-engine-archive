/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SHADER
    #define FG_INC_GFX_SHADER

    #include "fgGFXShaderDefs.h"
    #include "fgGFXShaderBase.h"
    #include "Util/fgFile.h"
    #include <map>

typedef fgGFXuint fgGfxShaderObjParamType;

    #define FG_GFX_SHADER_TYPE              GL_SHADER_TYPE
    #define FG_GFX_SHADER_DELETE_STATUS     GL_DELETE_STATUS
    #define FG_GFX_SHADER_COMPILE_STATUS    GL_COMPILE_STATUS
    #define FG_GFX_SHADER_INFO_LOG_LENGTH   GL_INFO_LOG_LENGTH
    #define FG_GFX_SHADER_SOURCE_LENGTH     GL_SHADER_SOURCE_LENGTH

/**
 *
 */
class fgGfxShader : public fgGfxShaderBase, protected fg::util::DataFile {
    friend class fgGfxShaderProgram;
public:
    ///
    typedef fgGfxShaderBase base_type;
    ///
    typedef fgGfxShaderBase::tag_type tag_type;
    ///
    typedef fgVector<std::string> defineStrVec;
    ///
    typedef defineStrVec::iterator defineStrVecItor;
    ///
    typedef fgVector<std::string> includeStrVec;
    ///
    typedef includeStrVec::iterator includeStrVecItor;

protected:
    ///
    fgGfxShaderType m_type;
    ///
    defineStrVec m_defineStrVec;
    ///
    includeStrVec m_includeStrVec;
    ///
    fgGfxSLVersion m_version;
    ///
    int m_numSources;
    ///
    unsigned int m_sourceSize;
    ///
    char const ** m_sources;
    ///
    char * m_fileSource;
    ///
    fgGfxShaderPrecision m_precision;
    ///
    fgBool m_isSourceLoaded;
    ///
    fgBool m_isAttached;

public:
    /**
     * 
     * @param type
     */
    fgGfxShader(fgGfxShaderType type);
    /**
     * 
     */
    virtual ~fgGfxShader();

    /**
     * 
     * @param slVer
     * @return 
     */
    fgBool setVersion(fgGfxSLVersion slVer);
    /**
     * 
     * @param constantDef
     */
    void appendDefine(fgGfxShaderConstantDef constantDef);
    /**
     * 
     * @param includeName
     */
    void appendInclude(std::string & includeName);

    /**
     * 
     * @return 
     */
    fgBool loadSource(void);
    /**
     * 
     * @param path
     * @return 
     */
    fgBool loadSource(const char *path);
    /**
     * 
     * @param path
     * @return 
     */
    fgBool loadSource(std::string & path);
    /**
     * 
     */
    void freeSource(void);

    /**
     * 
     * @return 
     */
    fgGFXuint create(void);
    /**
     * 
     * @return 
     */
    fgBool compile(void);
    /**
     * 
     * @param path
     * @return 
     */
    fgBool compile(const char *path);
    /**
     * 
     * @param path
     * @return 
     */
    fgBool compile(std::string & path);
    /**
     * 
     * @return 
     */
    fgBool deleteShader(void);

    /**
     * 
     */
    void clearAll(void);

protected:
    /**
     * 
     * @param program
     * @return 
     */
    fgBool attach(fgGFXuint program);
    /**
     * 
     * @param program
     * @return 
     */
    fgBool detach(fgGFXuint program);

public:
    /**
     * 
     * @param precision
     */
    void setPrecision(fgGfxShaderPrecision precision) {
        m_precision = precision;
    }
    /**
     * 
     * @return 
     */
    fgGfxShaderPrecision getPrecision(void) const {
        return m_precision;
    }
    /**
     * 
     * @return 
     */
    const char *getSource(void) const {
        return (const char *)m_fileSource;
    }
};

#endif /* FG_INC_GFX_SHADER */
