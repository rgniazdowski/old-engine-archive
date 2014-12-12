/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderBase.h"
#include "Util/fgMemory.h"
#include "fgLog.h"

/*
 *
 */
fgGfxShaderBase::fgGfxShaderBase() :
m_log(NULL),
m_gfxID(0),
m_baseType(FG_GFX_BASE_TYPE_INVALID) { }

/*
 *
 */
fgGfxShaderBase::~fgGfxShaderBase() {
    m_params.clear();
    if(m_log)
        fgFree(m_log);
    m_log = NULL;
}

/*
 *
 */
void fgGfxShaderBase::updateLog(void) {
    if(!m_gfxID)
        return;
    if(m_baseType == FG_GFX_BASE_TYPE_INVALID)
        return;
    fgGFXint length;
    if(m_baseType == FG_GFX_BASE_TYPE_SHADER) {
        if(FG_GFX_FALSE == glIsShader(m_gfxID))
            return;
        glGetShaderiv(m_gfxID, GL_INFO_LOG_LENGTH, &length);
    } else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM) {
        if(FG_GFX_FALSE == glIsProgram(m_gfxID))
            return;
        glGetProgramiv(m_gfxID, GL_INFO_LOG_LENGTH, &length);
        fgGLError("glGetProgramiv");
    }
    if(length) {
        if(m_log)
            fgFree(m_log);
        char *buffer = fgMalloc<char>(length);
        if(m_baseType == FG_GFX_BASE_TYPE_SHADER) {
            glGetShaderInfoLog(m_gfxID, length, NULL, buffer);
            fgGLError("glGetShaderInfoLog"); // ?
        } else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM) {
            glGetProgramInfoLog(m_gfxID, length, NULL, buffer);
            fgGLError("glGetProgramInfoLog"); // ?
        }
        m_log = buffer;
    }
}

/*
 *
 */
void fgGfxShaderBase::updateParams(void) {
    if(!m_gfxID)
        return;
    if(m_baseType == FG_GFX_BASE_TYPE_INVALID) {
        return;
    }
    GLint value;
    objParamMapItor begin, end, itor;
    begin = m_params.begin();
    end = m_params.end();
    itor = begin;
    for(; itor != end; itor++) {
        const fgGFXenum pname = (fgGFXenum)itor->first;
        if(m_baseType == FG_GFX_BASE_TYPE_SHADER) {
            glGetShaderiv(m_gfxID, pname, &value);
            fgGLError("glGetShaderiv");
        } else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM) {
            glGetProgramiv(m_gfxID, pname, &value);
            fgGLError("glGetProgramiv");
        } else {
            continue;
        }
        itor->second = value;
    }
}

/*
 *
 */
fgGFXint fgGfxShaderBase::updateParam(fgGFXenum pname) {
    if(!m_gfxID)
        return 0;
    if(m_baseType == FG_GFX_BASE_TYPE_INVALID)
        return 0;
    fgGFXint value = 0;
    if(m_baseType == FG_GFX_BASE_TYPE_SHADER && (FG_GFX_TRUE == glIsShader(m_gfxID))) {
        glGetShaderiv(m_gfxID, (fgGFXenum)pname, &value);
        fgGLError("glGetShaderiv");
    } else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM && (FG_GFX_TRUE == glIsProgram(m_gfxID))) {
        glGetProgramiv(m_gfxID, (fgGFXenum)pname, &value);
        fgGLError("glGetProgramiv");
    }
    m_params[pname] = value;
    return value;
}
