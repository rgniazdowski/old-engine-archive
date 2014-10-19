/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_H_
    #define _FG_GFX_SHADER_H_

    #include "fgGFXShaderDefs.h"
    #include "fgGFXShaderBase.h"
    #include "Util/fgFile.h"
    #include <map>

typedef fgGFXuint fgGfxShaderObjParamType;

    #define	FG_GFX_SHADER_TYPE				GL_SHADER_TYPE
    #define	FG_GFX_SHADER_DELETE_STATUS		GL_DELETE_STATUS
    #define	FG_GFX_SHADER_COMPILE_STATUS	GL_COMPILE_STATUS
    #define	FG_GFX_SHADER_INFO_LOG_LENGTH	GL_INFO_LOG_LENGTH
    #define	FG_GFX_SHADER_SOURCE_LENGTH		GL_SHADER_SOURCE_LENGTH

/*
 *
 */
class fgGfxShader : public fgGfxShaderBase, protected fgFile {
    friend class fgGfxShaderProgram;
public:
    typedef fgVector<std::string> defineStrVec;
    typedef defineStrVec::iterator defineStrVecItor;
    typedef fgVector<std::string> includeStrVec;
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
    // 
    fgGfxShader(fgGfxShaderType type);
    //
    virtual ~fgGfxShader();

    //
    fgBool setVersion(fgGfxSLVersion slVer);
    //
    void appendDefine(fgGfxShaderConstantDef constantDef);
    //
    void appendInclude(std::string & includeName);

    //
    fgBool loadSource(void);
    //
    fgBool loadSource(const char *path);
    //
    fgBool loadSource(std::string & path);
    //
    void freeSource(void);

    //
    fgGFXuint create(void);
    //
    fgBool compile(void);
    //
    fgBool compile(const char *path);
    //
    fgBool compile(std::string & path);
    //
    fgBool deleteShader(void);
    //
    void clearAll(void);

protected:
    //
    fgBool attach(fgGFXuint program);
    //
    fgBool detach(fgGFXuint program);

public:
    //
    void setPrecision(fgGfxShaderPrecision precision) {
        m_precision = precision;
    }
    //
    fgGfxShaderPrecision getPrecision(void) const {
        return m_precision;
    }

    //
    const char *getSource(void) const {
        return (const char *)m_fileSource;
    }
};

#endif /* _FG_GFX_SHADER_H_ */
