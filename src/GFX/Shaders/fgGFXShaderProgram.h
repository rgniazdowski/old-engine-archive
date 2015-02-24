/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

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

namespace fg {
    namespace gfx {
        /// Forward declaration of class CShaderProgram
        class CShaderProgram;
        /// Forward declaration of class CShaderManager
        class CShaderManager;
    };
};
    #define FG_TAG_GFX_SHADER_PROGRAM_NAME      "GfxShaderProgram"
    #define FG_TAG_GFX_SHADER_PROGRAM           FG_TAG_TYPE(fg::gfx::CShaderProgram)
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CShaderProgram, FG_TAG_GFX_SHADER_PROGRAM_NAME);

///
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

namespace fg {
    namespace gfx {
        
        ///
        typedef FG_TAG_GFX_SHADER_PROGRAM ShaderProgramTag;
        
        /**
         *
         */
        class CShaderProgram : public fg::gfx::base::CShader {
            friend class fg::gfx::CShaderManager;
        public:
            ///
            typedef fg::gfx::base::CShader base_type;
            ///
            typedef ShaderProgramTag tag_type;

        public:

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
            /**
             * 
             * @param _type
             * @return 
             */
            static fgGFXint shaderTypeToSpID(ShaderType _type) {
                fgGFXint spID = 0;
                switch(_type) {
                    case ShaderType::FG_GFX_SHADER_FRAGMENT:
                        spID = SP_FRAGMENT_SHADER_ID;
                        break;
                    case ShaderType::FG_GFX_SHADER_VERTEX:
                        spID = SP_VERTEX_SHADER_ID;
                        break;
    #if defined FG_USING_OPENGL
                    case ShaderType::FG_GFX_SHADER_TESS_CONTROL:
                        spID = SP_TESS_CONTROL_SHADER_ID;
                        break;
                    case ShaderType::FG_GFX_SHADER_TESS_EVALUATION:
                        spID = SP_TESS_EVALUATION_SHADER_ID;
                        break;
                    case ShaderType::FG_GFX_SHADER_GEOMETRY:
                        spID = SP_GEOMETRY_SHADER_ID;
                        break;
                    case ShaderType::FG_GFX_SHADER_COMPUTE:
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
            ///
            typedef CVector<fg::gfx::CShader *> shaderVec;
            ///
            typedef shaderVec::iterator shaderVecItor;
            ///
            typedef CShaderConfig::UniformBindVec uniformBindVec;
            ///
            typedef uniformBindVec::iterator uniformBindVecItor;
            ///
            typedef CShaderConfig::AttributeBindVec attributeBindVec;
            ///
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
            CShaderConfig* m_config;
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
            CShaderProgram();
            /**
             * 
             */
            virtual ~CShaderProgram();

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
            /**
             * 
             * @param binds
             * @return 
             */
            fgBool appendUniformBinds(uniformBindVec & binds);
            /**
             * 
             * @param binds
             * @return 
             */
            fgBool appendAttributeBinds(attributeBindVec & binds);

            /**
             * 
             * @param shader
             * @return 
             */
            fgBool attachShader(fg::gfx::CShader *shader);
            /**
             * 
             * @return 
             */
            fgBool attachShaders(void);

            /**
             * 
             * @param shader
             * @return 
             */
            fgBool deleteShader(fg::gfx::CShader *shader);
            /**
             * 
             * @return 
             */
            fgBool deleteShaders(void);

            /**
             * 
             * @param shader
             * @return 
             */
            fgBool detachShader(fg::gfx::CShader *shader);
            /**
             * 
             * @return 
             */
            fgBool detachShaders(void);

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
            /**
             * 
             * @return 
             */
            fgBool link(void);
            /**
             * 
             * @return 
             */
            fgBool use(void);
            /**
             * 
             * @return 
             */
            fgBool bindAttributes(void);
            /**
             * 
             * @return 
             */
            fgBool bindUniforms(void);
            /**
             * 
             * @return 
             */
            fgBool deleteProgram(void);
            /**
             * 
             */
            void clearAll(void);

            /**
             * 
             * @return 
             */
            fgBool isUsed(void);
            /**
             * 
             * @return 
             */
            fgBool isLinked(void) const {
                return m_isLinked;
            }
            /**
             * 
             * @return 
             */
            fgBool isCompiled(void) const {
                return m_isCompiled;
            }

        public:
            /**
             * 
             * @return 
             */
            inline shaderVec & getRefShaderVec(void) {
                return m_shaders;
            }
            /**
             * 
             * @return 
             */
            inline attributeBindVec & getRefAttrBinds(void) {
                return m_attrBinds;
            }
            /**
             * 
             * @return 
             */
            inline uniformBindVec & getRefUniformBinds(void) {
                return m_uniformBinds;
            }
            /**
             * 
             * @param type
             * @return 
             */
            inline CShader *getShader(ShaderType type) const {
                fgGFXint id = shaderTypeToSpID(type);
                if(id != -1)
                    return m_shaders[id];
                else
                    return NULL;
            }

            ///////////////////////////////////////////////////////

            /**
             * 
             * @param type
             * @return 
             */
            fgGFXint getUniformLocation(UniformType type);
            /**
             * 
             * @param variableName
             * @return 
             */
            fgGFXint getUniformLocation(std::string variableName);

            /**
             * 
             * @param type
             * @return 
             */
            fgGFXint getUniformBindIndex(UniformType type);
            /**
             * 
             * @param type
             * @return 
             */
            SUniformBind *getUniformBind(UniformType type);

            /**
             * 
             * @param matrix
             * @return 
             */
            fgBool setUniform(CMVPMatrix *matrix);
            /**
             * 
             * @param matrix
             * @return 
             */
            fgBool setUniform(CMVMatrix *matrix);

            /**
             * 
             * @param type
             * @param v0
             * @return 
             */
            fgBool setUniform(UniformType type, fgGFXfloat v0);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @return 
             */
            fgBool setUniform(UniformType type, fgGFXfloat v0, fgGFXfloat v1);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @param v2
             * @return 
             */
            fgBool setUniform(UniformType type,
                              fgGFXfloat v0,
                              fgGFXfloat v1,
                              fgGFXfloat v2);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @param v2
             * @param v3
             * @return 
             */
            fgBool setUniform(UniformType type,
                              fgGFXfloat v0,
                              fgGFXfloat v1,
                              fgGFXfloat v2,
                              fgGFXfloat v3);

            /**
             * 
             * @param type
             * @param v0
             * @return 
             */
            fgBool setUniform(UniformType type, fgGFXint v0);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @return 
             */
            fgBool setUniform(UniformType type, fgGFXint v0, fgGFXint v1);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @param v2
             * @return 
             */
            fgBool setUniform(UniformType type,
                              fgGFXint v0,
                              fgGFXint v1,
                              fgGFXint v2);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @param v2
             * @param v3
             * @return 
             */
            fgBool setUniform(UniformType type,
                              fgGFXint v0,
                              fgGFXint v1,
                              fgGFXint v2,
                              fgGFXint v3);

            /**
             * 
             * @param type
             * @param count
             * @param value
             * @return 
             */
            fgBool setUniform(UniformType type,
                              fgGFXsizei count,
                              const fgGFXfloat *value);
            /**
             * 
             * @param type
             * @param count
             * @param value
             * @return 
             */
            fgBool setUniform(UniformType type,
                              fgGFXsizei count,
                              const fgGFXint *value);

            ////////////////////////////////////////////////////////////////////////////
            /**
             * 
             * @return 
             */
            inline CShader *getFragmentShader(void) const {
                return m_shaders[SP_FRAGMENT_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader *getVertexShader(void) const {
                return m_shaders[SP_VERTEX_SHADER_ID];
            }
    #if defined FG_USING_OPENGL
            /**
             * 
             * @return 
             */
            inline CShader *getTessControlShader(void) const {
                return m_shaders[SP_TESS_CONTROL_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader *getTessEvaluationShader(void) const {
                return m_shaders[SP_TESS_EVALUATION_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader *getGeometryShader(void) const {
                return m_shaders[SP_GEOMETRY_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader *getComputeShader(void) const {
                return m_shaders[SP_COMPUTE_SHADER_ID];
            }
    #endif
        };
    };
};

    #undef FG_INC_GFX_SHADER_PROGRAM_BLOCK
#endif /* FG_INC_GFX_SHADER_PROGRAM */
