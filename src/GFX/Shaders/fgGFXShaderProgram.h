/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SHADER_PROGRAM
    #define FG_INC_GFX_SHADER_PROGRAM
    #define FG_INC_GFX_SHADER_PROGRAM_BLOCK

    #include "fgGFXShaderDefs.h"
    #include "fgGFXShader.h"
    #include "fgGFXShaderBase.h"
    #include "fgGFXShaderConfig.h"

    #include "Util/fgHandle.h"
    #include "Util/fgTag.h"
    #include "fgVector.h"

    #include "GFX/fgGFXMVPMatrix.h"

    #ifndef FG_INC_MANAGER_BASE
        #include "fgManagerBase.h"
    #endif

class fgGfxShaderProgram;

    #define FG_TAG_GFX_SHADER_PROGRAM_NAME      "GfxShaderProgram"
    #define FG_TAG_GFX_SHADER_PROGRAM           FG_TAG_TYPE(fgGfxShaderProgram)

FG_TAG_TEMPLATE_ID_AUTO(fgGfxShaderProgram, FG_TAG_GFX_SHADER_PROGRAM_NAME);
typedef FG_TAG_GFX_SHADER_PROGRAM fgGfxShaderProgramTag;

//
typedef fgGFXuint fgGfxProgramObjParamType;

// #FIXME
// GL_TRUE if program is currently flagged for deletion, and GL_FALSE otherwise.
    #define	FG_GFX_PROGRAM_DELETE_STATUS                GL_DELETE_STATUS
// GL_TRUE if the last link operation on program was successful, and GL_FALSE otherwise.
    #define	FG_GFX_PROGRAM_LINK_STATUS                  GL_LINK_STATUS
// GL_TRUE or if the last validation operation on program was successful, and GL_FALSE otherwise.
    #define FG_GFX_PROGRAM_VALIDATE_STATUS                  GL_VALIDATE_STATUS
// the number of characters in the information log for program including the null termination
// character (i.e., the size of the character buffer required to store the information log). 
// If program has no information log, a value of 0 is returned.
    #define FG_GFX_PROGRAM_INFO_LOG_LENGTH                  GL_INFO_LOG_LENGTH
// the number of shader objects attached to program.
    #define FG_GFX_PROGRAM_ATTACHED_SHADERS                 GL_ATTACHED_SHADERS
// number of active attribute variables for program
    #define FG_GFX_PROGRAM_ACTIVE_ATTRIBUTES                GL_ACTIVE_ATTRIBUTES
// the length of the longest active attribute name for program, including the null termination character
    #define FG_GFX_PROGRAM_ACTIVE_ATTRIBUTE_MAX_LENGTH      GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
// the number of active uniform variables
    #define FG_GFX_PROGRAM_ACTIVE_UNIFORMS                  GL_ACTIVE_UNIFORMS

/*
 *
 */
class fgGfxShaderProgram : public fgGfxShaderBase {
    friend class fgGfxShaderManager;
public:
    typedef fgGfxShaderBase base_type;
    typedef fgGfxShaderProgramTag tag_type;
    
protected:

    enum {
        SP_FRAGMENT_SHADER_ID = 0,
        SP_VERTEX_SHADER_ID = 1,
    #if defined FG_USING_OPENGL
        SP_TESS_CONTROL_SHADER_ID = 2,
        SP_TESS_EVALUATION_SHADER_ID = 3,
        SP_GEOMETRY_SHADER_ID = 4,
        // GL_COMPUTE_SHADER is available only if the GL version is 4.3 or higher.
        SP_COMPUTE_SHADER_ID = 5
    #endif
    };

protected:
    static fgGFXint _shaderTypeToSpID(fgGfxShaderType _type) {
        fgGFXint spID = 0;
        switch(_type) {
            case fgGfxShaderType::FG_GFX_SHADER_FRAGMENT:
                spID = SP_FRAGMENT_SHADER_ID;
                break;
            case fgGfxShaderType::FG_GFX_SHADER_VERTEX:
                spID = SP_VERTEX_SHADER_ID;
                break;
    #if defined FG_USING_OPENGL
            case fgGfxShaderType::FG_GFX_SHADER_TESS_CONTROL:
                spID = SP_TESS_CONTROL_SHADER_ID;
                break;
            case fgGfxShaderType::FG_GFX_SHADER_TESS_EVALUATION:
                spID = SP_TESS_EVALUATION_SHADER_ID;
                break;
            case fgGfxShaderType::FG_GFX_SHADER_GEOMETRY:
                spID = SP_GEOMETRY_SHADER_ID;
                break;
            case fgGfxShaderType::FG_GFX_SHADER_COMPUTE:
                spID = SP_COMPUTE_SHADER_ID;
                break;
    #endif
            default:
                spID = -1;
                break;
        };
        return spID;
    }

public:
    typedef fgVector<fgGfxShader *> shaderVec;
    typedef shaderVec::iterator shaderVecItor;
    typedef fgGfxShaderConfig::shaderUniformBindVec uniformBindVec;
    typedef uniformBindVec::iterator uniformBindVecItor;
    typedef fgGfxShaderConfig::shaderAttributeBindVec attributeBindVec;
    typedef attributeBindVec::iterator attributeBindVecItor;

protected:
    /// Vector holding shaders (vertex/fragment/etc..) that 
    /// will be used to link the shader program
    shaderVec m_shaders;
    /// Special vector with uniforms binds for this shader program
    uniformBindVec m_uniformBinds;
    /// Vector with attribute binds for this shader program
    attributeBindVec m_attrBinds;
    /// Helper class for loading special shader configs
    fgGfxShaderConfig* m_config;
    /// Are the special config files loaded?
    fgBool m_isPreLoaded;
    /// Did compilation for this shader program ended successfully
    fgBool m_isCompiled;
    /// Is the shader program linked and ready to use
    fgBool m_isLinked;
    /// Pointer to the managing class
    fg::base::CManager *m_manager;

public:
    /**
     * 
     */
    fgGfxShaderProgram();
    /**
     * 
     */
    virtual ~fgGfxShaderProgram();

    /**
     * 
     * @param path
     * @return 
     */
    fgBool preLoadConfig(const char *path);
    /**
     * 
     * @param path
     * @return 
     */
    fgBool preLoadConfig(std::string &path);

protected:
    //
    fgBool _appendUniformBinds(uniformBindVec & binds);
    //
    fgBool _appendAttributeBinds(attributeBindVec & binds);

    //
    fgBool _attachShader(fgGfxShader *shader);
    //
    fgBool _attachShaders(void);

    //
    fgBool _deleteShader(fgGfxShader *shader);
    //
    fgBool _deleteShaders(void);

    //
    fgBool _detachShader(fgGfxShader *shader);
    //
    fgBool _detachShaders(void);

    //
    /**
     * 
     * @return 
     */
    fgGFXint updateLinkStatus(void);
    /**
     * 
     * @return 
     */
    fgGFXint updateValidateStatus(void);

    /**
     * 
     * @return 
     */
    fgBool releaseGFX(void);

    /**
     * 
     * @param pManager
     * @return 
     */
    fgBool setManager(fg::base::CManager *pManager);

public:
    // Create the shader program with direct GL calls
    // Gfx ID will become valid if this function is successful
    fgGFXuint create(void);
    // Try to compile the shaders for this shader program
    // If needed the source code files will be loaded
    fgBool compile(void);
    //
    fgBool link(void);
    //
    fgBool use(void);
    //
    fgBool bindAttributes(void);
    //
    fgBool bindUniforms(void);
    //
    fgBool deleteProgram(void);
    //
    void clearAll(void);

    //
    fgBool isUsed(void);

public:
    //
    inline shaderVec & getRefShaderVec(void) {
        return m_shaders;
    }

    //
    inline attributeBindVec & getRefAttrBinds(void) {
        return m_attrBinds;
    }

    //
    inline uniformBindVec & getRefUniformBinds(void) {
        return m_uniformBinds;
    }

    // 
    inline fgGfxShader *getShader(fgGfxShaderType type) const {
        fgGFXint id = _shaderTypeToSpID(type);
        if(id != -1)
            return m_shaders[id];
        else
            return NULL;
    }

    ///////////////////////////////////////////////////////

    //
    fgGFXint getUniformLocation(fgGfxUniformType type);
    //
    fgGFXint getUniformLocation(std::string variableName);

    //
    fgGFXint getUniformBindIndex(fgGfxUniformType type);
    //
    fgGfxUniformBind *getUniformBind(fgGfxUniformType type);

    //
    fgBool setUniform(fgGfxMVPMatrix *matrix);
    //
    fgBool setUniform(fgGfxMVMatrix *matrix);

    //
    fgBool setUniform(fgGfxUniformType type, fgGFXfloat v0);
    //
    fgBool setUniform(fgGfxUniformType type, fgGFXfloat v0, fgGFXfloat v1);
    //
    fgBool setUniform(fgGfxUniformType type, fgGFXfloat v0, fgGFXfloat v1, fgGFXfloat v2);
    //
    fgBool setUniform(fgGfxUniformType type, fgGFXfloat v0, fgGFXfloat v1, fgGFXfloat v2, fgGFXfloat v3);

    //
    fgBool setUniform(fgGfxUniformType type, fgGFXint v0);
    //
    fgBool setUniform(fgGfxUniformType type, fgGFXint v0, fgGFXint v1);
    //
    fgBool setUniform(fgGfxUniformType type, fgGFXint v0, fgGFXint v1, fgGFXint v2);
    //
    fgBool setUniform(fgGfxUniformType type, fgGFXint v0, fgGFXint v1, fgGFXint v2, fgGFXint v3);

    //
    fgBool setUniform(fgGfxUniformType type, fgGFXsizei count, const fgGFXfloat *value);
    //
    fgBool setUniform(fgGfxUniformType type, fgGFXsizei count, const fgGFXint *value);

    ///////////////////////////////////////////////////////

    //
    inline fgGfxShader *getFragmentShader(void) const {
        return m_shaders[SP_FRAGMENT_SHADER_ID];
    }

    //
    inline fgGfxShader *getVertexShader(void) const {
        return m_shaders[SP_VERTEX_SHADER_ID];
    }
    #if defined FG_USING_OPENGL
    //
    inline fgGfxShader *getTessControlShader(void) const {
        return m_shaders[SP_TESS_CONTROL_SHADER_ID];
    }

    //
    inline fgGfxShader *getTessEvaluationShader(void) const {
        return m_shaders[SP_TESS_EVALUATION_SHADER_ID];
    }

    //
    inline fgGfxShader *getGeometryShader(void) const {
        return m_shaders[SP_GEOMETRY_SHADER_ID];
    }

    //
    inline fgGfxShader *getComputeShader(void) const {
        return m_shaders[SP_COMPUTE_SHADER_ID];
    }
    #endif
};

    #undef FG_INC_GFX_SHADER_PROGRAM_BLOCK
#endif /* FG_INC_GFX_SHADER_PROGRAM */
