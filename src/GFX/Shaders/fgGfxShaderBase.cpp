/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxShaderBase.h"
#include "Util/fgMemory.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::base::CShader::CShader() :
m_log(NULL),
m_gfxID(0),
m_baseType(BASE_TYPE_INVALID),
m_usageMask(shaders::USAGE_EMPTY_BIT) { }
//------------------------------------------------------------------------------

gfx::base::CShader::~CShader() {
    m_params.clear();
    if(m_log)
        fgFree(m_log);
    m_log = NULL;
}
//------------------------------------------------------------------------------

void gfx::base::CShader::updateLog(void) {
    if(!m_gfxID)
        return;
    if(m_baseType == BASE_TYPE_INVALID)
        return;
    fgGFXint length;
    if(m_baseType == BASE_TYPE_SHADER) {
        if(FG_GFX_FALSE == glIsShader(m_gfxID))
            return;
        glGetShaderiv(m_gfxID, GL_INFO_LOG_LENGTH, &length);
    } else if(m_baseType == BASE_TYPE_PROGRAM) {
        if(FG_GFX_FALSE == glIsProgram(m_gfxID))
            return;
        glGetProgramiv(m_gfxID, GL_INFO_LOG_LENGTH, &length);
        GLCheckError("glGetProgramiv");
    }
    if(length) {
        if(m_log)
            fgFree(m_log);
        char *buffer = fgMalloc<char>(length);
        if(m_baseType == BASE_TYPE_SHADER) {
            glGetShaderInfoLog(m_gfxID, length, NULL, buffer);
            GLCheckError("glGetShaderInfoLog"); // ?
        } else if(m_baseType == BASE_TYPE_PROGRAM) {
            glGetProgramInfoLog(m_gfxID, length, NULL, buffer);
            GLCheckError("glGetProgramInfoLog"); // ?
        }
        m_log = buffer;
    }
}
//------------------------------------------------------------------------------

void gfx::base::CShader::updateParams(void) {
    if(!m_gfxID)
        return;
    if(m_baseType == BASE_TYPE_INVALID) {
        return;
    }
    GLint value;
    ObjParamMapItor begin, end, itor;
    begin = m_params.begin();
    end = m_params.end();
    itor = begin;
    for(; itor != end; itor++) {
        const fgGFXenum pname = (fgGFXenum)itor->first;
        if(m_baseType == BASE_TYPE_SHADER) {
            glGetShaderiv(m_gfxID, pname, &value);
            GLCheckError("glGetShaderiv");
        } else if(m_baseType == BASE_TYPE_PROGRAM) {
            glGetProgramiv(m_gfxID, pname, &value);
            GLCheckError("glGetProgramiv");
        } else {
            continue;
        }
        itor->second = value;
    }
}
//------------------------------------------------------------------------------

fgGFXint gfx::base::CShader::updateParam(fgGFXenum pname) {
    if(!m_gfxID)
        return 0;
    if(m_baseType == BASE_TYPE_INVALID)
        return 0;
    fgGFXint value = 0;
    if(m_baseType == BASE_TYPE_SHADER && (FG_GFX_TRUE == glIsShader(m_gfxID))) {
        glGetShaderiv(m_gfxID, (fgGFXenum)pname, &value);
        GLCheckError("glGetShaderiv");
    } else if(m_baseType == BASE_TYPE_PROGRAM && (FG_GFX_TRUE == glIsProgram(m_gfxID))) {
        glGetProgramiv(m_gfxID, (fgGFXenum)pname, &value);
        GLCheckError("glGetProgramiv");
    }
    m_params[pname] = value;
    return value;
}
//------------------------------------------------------------------------------
