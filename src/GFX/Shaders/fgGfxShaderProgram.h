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

    #ifdef FG_INC_GFX_MATERIAL_BLOCK
        #error "FG_INC_GFX_MATERIAL_BLOCK constant is defined. Do not include GfxShaderProgram inside of GfxMaterial header."
    #endif

    #include "fgGfxShaderDefs.h"
    #include "fgGfxShader.h"
    #include "fgGfxShaderBase.h"
    #include "fgGfxShaderConfig.h"

    #include "Util/fgHandle.h"
    #include "Util/fgTag.h"
    #include "fgVector.h"

    #include "GFX/fgGfxMVPMatrix.h"
    #include "GFX/fgGfxLight.h"
    #include "GFX/fgGfxMaterial.h"
    #include "Math/fgDualQuaternion.h"

    #ifndef FG_INC_MANAGER_BASE
        #include "fgManagerBase.h"
    #endif

namespace fg {
    namespace gfx {
        /// Forward declaration of class CShaderProgram
        class CShaderProgram;
        /// Forward declaration of class CShaderManager
        class CShaderManager;
    } // namespace gfx
} // namespace fg
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
        class CShaderProgram : public ::fg::gfx::base::CShader {
            friend class ::fg::gfx::CShaderManager;
        public:
            typedef gfx::base::CShader base_type;
            typedef CShaderProgram self_type;
            typedef CShaderProgram type;
            typedef ShaderProgramTag tag_type;

        public:

            /**
             *
             */
            enum StateFlags {
                /// Empty state flags - nothing activated
                NO_FLAGS = 0x0000,
                /// Whether or not the shader program is pre-loaded (from config)
                PRELOADED = 0x0001,
                /// Is the shader program compiled?
                COMPILED = 0x0002,
                /// Is the shader program successfully linked?
                LINKED = 0x0004,
                /// Was the shader program recently linked?
                RECENTLY_LINKED = 0x0010,
                /// Was the shader program recently used?
                RECENTLY_USED = 0x0020
            };

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
            static fgGFXint shaderTypeToSpID(shaders::ShaderType _type) {
                fgGFXint spID = 0;
                switch(_type) {
                    case shaders::SHADER_FRAGMENT:
                        spID = SP_FRAGMENT_SHADER_ID;
                        break;
                    case shaders::SHADER_VERTEX:
                        spID = SP_VERTEX_SHADER_ID;
                        break;
    #if defined(FG_USING_OPENGL)
                    case shaders::SHADER_TESS_CONTROL:
                        spID = SP_TESS_CONTROL_SHADER_ID;
                        break;
                    case shaders::SHADER_TESS_EVALUATION:
                        spID = SP_TESS_EVALUATION_SHADER_ID;
                        break;
                    case shaders::SHADER_GEOMETRY:
                        spID = SP_GEOMETRY_SHADER_ID;
                        break;
                    case shaders::SHADER_COMPUTE:
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
            typedef CVector<fg::gfx::CShader *> ShaderVec;
            ///
            typedef ShaderVec::iterator ShaderVecItor;
            ///
            typedef CShaderConfig::UniformBindVec UniformBindVec;
            ///
            typedef UniformBindVec::iterator UniformBindVecItor;
            ///
            typedef CShaderConfig::AttributeBindVec AttributeBindVec;
            ///
            typedef AttributeBindVec::iterator AttributeBindVecItor;

        protected:
            /// Current state flags for the shader program
            StateFlags m_stateFlags;
            /// Current attribute mask of the shader program.
            /// It tells which attributes are activated within the shader.
            AttributeMask m_attribMask;
            /// Vector holding shaders (vertex/fragment/etc..) that 
            /// will be used to link the shader program
            ShaderVec m_shaders;
            /// Special vector with uniforms binds for this shader program
            UniformBindVec m_uniformBinds;
            /// Vector with attribute binds for this shader program
            AttributeBindVec m_attribBinds;
            /// Helper class for loading special shader configs
            CShaderConfig* m_config;

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

        public:
            /**
             *
             * @return
             */
            inline fgBool isPreloaded(void) const {
                return (fgBool)!!(m_stateFlags & PRELOADED);
            }
            /**
             *
             * @return
             */
            inline fgBool isCompiled(void) const {
                return (fgBool)!!(m_stateFlags & COMPILED);
            }
            /**
             *
             * @return
             */
            inline fgBool isLinked(void) const {
                return (fgBool)!!(m_stateFlags & LINKED);
            }
            /**
             *
             * @return
             */
            inline fgBool wasRecentlyLinked(void) const {
                return (fgBool)!!(m_stateFlags & RECENTLY_LINKED);
            }
            /**
             *
             * @return
             */
            inline fgBool wasRecentlyUsed(void) const {
                return (fgBool)!!(m_stateFlags & RECENTLY_USED);
            }
            /**
             * 
             * @return
             */
            inline AttributeMask getAttribMask(void) const {
                return m_attribMask;
            }

        protected:
            /**
             *
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
            /**
             *
             * @param toggle
             */
            inline void setPreloaded(fgBool toggle = FG_TRUE) {
                setFlag(PRELOADED, toggle);
            }
            /**
             *
             * @param toggle
             */
            inline void setCompiled(fgBool toggle = FG_TRUE) {
                setFlag(COMPILED, toggle);
            }
            /**
             *
             * @param toggle
             */
            inline void setLinked(fgBool toggle = FG_TRUE) {
                setFlag(LINKED, toggle);
            }
            /**
             * 
             * @param toggle
             */
            inline void setRecentlyLinked(fgBool toggle = FG_TRUE) {
                setFlag(RECENTLY_LINKED, toggle);
            }
            /**
             *
             * @param toggle
             */
            inline void setRecentlyUsed(fgBool toggle = FG_TRUE) {
                setFlag(RECENTLY_USED, toggle);
            }

        protected:
            /**
             * 
             * @param binds
             * @return 
             */
            fgBool appendUniformBinds(UniformBindVec & binds);
            /**
             * 
             * @param binds
             * @return 
             */
            fgBool appendAttributeBinds(AttributeBindVec & binds);

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
            fgBool setManager(::fg::base::CManager *pManager);

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

        private:
            /**
             * 
             * @return 
             */
            inline ShaderVec& getShaders(void) {
                return m_shaders;
            }
            /**
             * 
             * @return 
             */
            inline ShaderVec const& getShaders(void) const {
                return m_shaders;
            }
            /**
             * 
             * @return 
             */
            inline AttributeBindVec& getAttributeBinds(void) {
                return m_attribBinds;
            }
            /**
             *
             * @return
             */
            inline AttributeBindVec const& getAttributeBinds(void) const {
                return m_attribBinds;
            }
            /**
             * 
             * @return 
             */
            inline UniformBindVec& getUniformBinds(void) {
                return m_uniformBinds;
            }
            /**
             * 
             * @return 
             */
            inline UniformBindVec const& getUniformBinds(void) const {
                return m_uniformBinds;
            }
        public:
            /**
             * 
             * @param type
             * @return 
             */
            inline CShader* getShader(shaders::ShaderType type) const {
                fgGFXint id = shaderTypeToSpID(type);
                if(id != -1)
                    return m_shaders[id];
                else
                    return NULL;
            }

            //------------------------------------------------------------------

            /**
             * 
             * @param type
             * @return 
             */
            fgGFXint getUniformLocation(shaders::UniformType uniformType);
            /**
             * 
             * @param variableName
             * @return 
             */
            fgGFXint getUniformLocation(const std::string& variableName);

            //------------------------------------------------------------------

            /**
             * 
             * @param type
             * @return 
             */
            fgGFXint getUniformBindIndex(shaders::UniformType uniformType) const;
            /**
             * 
             * @param type
             * @return 
             */
            SUniformBind* getUniformBind(shaders::UniformType type);
            /**
             *
             * @param variableName
             * @return
             */
            SUniformBind* getUniformBind(const std::string& variableName);
            /**
             *
             * @param variableName
             * @return
             */
            SUniformBind* getUniformBind(const char* variableName);

            //------------------------------------------------------------------

            /**
             * 
             * @param matrix
             * @return 
             */
            fgBool setUniform(CMVPMatrix* matrix);
            /**
             * 
             * @param matrix
             * @return 
             */
            fgBool setUniform(CMVMatrix* matrix);

            //------------------------------------------------------------------

            /**
             * 
             * @param light
             * @return
             */
            fgBool setUniform(const SDirectionalLight& light);
            /**
             *
             * @param material
             * @return
             */
            fgBool setUniform(const SMaterial& material);
            /**
             *
             * @param pMaterial
             * @return
             */
            inline fgBool setUniform(const SMaterial* pMaterial) {
                if(!pMaterial)
                    return FG_FALSE;
                return setUniform(*pMaterial);
            }

            //------------------------------------------------------------------

            /**
             *
             * @param type
             * @param matrix
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const Matrix4f& matrix);
            /**
             *
             * @param type
             * @param matrices
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const Matrix4f* matrices,
                              const unsigned int count);
            /**
             *
             * @param type
             * @param matrices
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const CVector<Matrix4f>& matrices);

            //------------------------------------------------------------------

            /**
             *
             * @param type
             * @param matrix
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const Matrix3f& matrix);
            /**
             *
             * @param type
             * @param matrices
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const Matrix3f* matrices,
                              const unsigned int count);
            /**
             *
             * @param type
             * @param matrices
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const CVector<Matrix3f>& matrices);

            //------------------------------------------------------------------

            /**
             *
             * @param type
             * @param dualquat
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const DualQuaternionf& dualquat);
            /**
             *
             * @param type
             * @param dquats
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const DualQuaternionf* dquats,
                              const unsigned int count);
            /**
             *
             * @param type
             * @param dquats
             * @return
             */
            fgBool setUniform(shaders::UniformType type,
                              const CVector<DualQuaternionf>& dquats);

            /**
             * 
             * @param dquats
             * @return
             */
            fgBool setUniform(const CVector<DualQuaternionf>& dquats);

            //------------------------------------------------------------------

            /**
             * 
             * @param type
             * @param v0
             * @return 
             */
            fgBool setUniform(shaders::UniformType type, fgGFXfloat v0);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @return 
             */
            fgBool setUniform(shaders::UniformType type, fgGFXfloat v0, fgGFXfloat v1);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @param v2
             * @return 
             */
            fgBool setUniform(shaders::UniformType type,
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
            fgBool setUniform(shaders::UniformType type,
                              fgGFXfloat v0,
                              fgGFXfloat v1,
                              fgGFXfloat v2,
                              fgGFXfloat v3);

            //------------------------------------------------------------------

            /**
             * 
             * @param type
             * @param v0
             * @return 
             */
            fgBool setUniform(shaders::UniformType type, fgGFXint v0);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @return 
             */
            fgBool setUniform(shaders::UniformType type, fgGFXint v0, fgGFXint v1);
            /**
             * 
             * @param type
             * @param v0
             * @param v1
             * @param v2
             * @return 
             */
            fgBool setUniform(shaders::UniformType type,
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
            fgBool setUniform(shaders::UniformType type,
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
            fgBool setUniform(shaders::UniformType type,
                              fgGFXsizei count,
                              const fgGFXfloat *value);
            /**
             * 
             * @param type
             * @param count
             * @param value
             * @return 
             */
            fgBool setUniform(shaders::UniformType type,
                              fgGFXsizei count,
                              const fgGFXint *value);

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline CShader* getFragmentShader(void) const {
                return m_shaders[SP_FRAGMENT_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader* getVertexShader(void) const {
                return m_shaders[SP_VERTEX_SHADER_ID];
            }
    #if defined FG_USING_OPENGL
            /**
             * 
             * @return 
             */
            inline CShader* getTessControlShader(void) const {
                return m_shaders[SP_TESS_CONTROL_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader* getTessEvaluationShader(void) const {
                return m_shaders[SP_TESS_EVALUATION_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader* getGeometryShader(void) const {
                return m_shaders[SP_GEOMETRY_SHADER_ID];
            }
            /**
             * 
             * @return 
             */
            inline CShader* getComputeShader(void) const {
                return m_shaders[SP_COMPUTE_SHADER_ID];
            }
    #endif
        }; // class CShaderProgram

        FG_ENUM_FLAGS(CShaderProgram::StateFlags);
        /**
         *
         * @param flags
         * @param toggle
         */
        inline void CShaderProgram::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_stateFlags |= flags;
            } else {
                m_stateFlags |= flags;
                m_stateFlags ^= flags;
            }
        }
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SHADER_PROGRAM_BLOCK
#endif /* FG_INC_GFX_SHADER_PROGRAM */
