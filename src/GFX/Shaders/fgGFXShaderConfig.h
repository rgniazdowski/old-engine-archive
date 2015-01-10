/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SHADER_CONFIG
    #define FG_INC_GFX_SHADER_CONFIG
    #define FG_INC_GFX_SHADER_CONFIG_BLOCK

    #ifdef FG_INC_GFX_STD_INC_BLOCK
        #error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderConfig inside of Gfx Standard Include header."
    #endif
    #include "fgGFXShaderDefs.h"
    #include "Hardware/fgQualityTypes.h"
    #include "Util/fgConfig.h"
    #include "Util/fgTag.h"

enum fgGfxShaderConfigType {
    FG_GFX_SHADER_CONFIG_INVALID = 0,
    FG_GFX_SHADER_CONFIG_PROGRAM = 1,
    FG_GFX_SHADER_CONFIG_FRAGMENT = 2,
    FG_GFX_SHADER_CONFIG_VERTEX = 3
    #if defined FG_USING_OPENGL
    ,
    FG_GFX_SHADER_CONFIG_TESS_CONTROL = 4,
    FG_GFX_SHADER_CONFIG_TESS_EVALUATION = 5,
    FG_GFX_SHADER_CONFIG_GEOMETRY = 6,
    FG_GFX_SHADER_CONFIG_COMPUTE = 7
    #endif
};

    #define FG_GFX_SHADER_CONFIG_PROGRAM_SECTION_NAME   "ShaderProgramConfig"
    #define FG_GFX_SHADER_CONFIG_BASIC_SECTION_NAME     "ShaderConfig"

namespace fg {
    namespace gfx {
        class CShaderConfig;
    }
};
    #define FG_TAG_GFX_SHADER_CONFIG_NAME       "GfxShaderConfig"
    #define FG_TAG_GFX_SHADER_CONFIG            FG_TAG_TYPE(fg::gfx::CShaderConfig)

FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CShaderConfig, FG_TAG_GFX_SHADER_CONFIG_NAME);
typedef FG_TAG_GFX_SHADER_CONFIG fgGfxShaderConfigTag;

namespace fg {
    namespace gfx {

        /*
         * Shader config mission is to read special configs (INI) holding information
         * about shader program and respective shaders. It's universal for different kinds
         * of shaders. ShaderConfig will be used from ShaderProgram only. 
         * For shader objects information contained in config consists of:
         * - list of uniform variables and corresponding types in the engine,
         * - list of attribute variables,
         * - list of defined constants,
         * - list of configuration modes depending on supported api,
         * - names of the shader source files,
         * - supported versions of shading language,
         * and others. The goal is to make possible loading many different types of shaders
         * and different configurations (also depending on the build target) without the 
         * need to change or rebuild the executable (engine).
         *
         * This class can load and parse only one config at one time, and
         * will provide that data for only one config type.
         */
        class CShaderConfig : protected fgConfig {
        public:
            ///
            typedef fgConfig base_type;
            ///
            typedef fgGfxShaderConfigTag tag_type;
            ///
            typedef fg::CVector<fgGfxShaderType> shaderTypeVec;
            ///
            typedef fg::CVector<fgGfxUniformBind> shaderUniformBindVec;
            ///
            typedef fg::CVector<fgGfxAttributeBind> shaderAttributeBindVec;
            ///
            typedef fg::CVector<std::string> shaderIncludeNameVec;
            ///
            typedef fg::CVector<std::string> shaderFileVec;
            ///
            typedef fg::CVector<fgQuality> shaderQualityVec;
            ///
            typedef fg::CVector<fgGfxShaderConstantDef> shaderConstantVec;

        protected:
            ///
            fgGfxShaderConfigType m_configType;
            ///
            shaderTypeVec m_shaderTypes;

            /// 
            shaderUniformBindVec m_uniformBinds;
            ///
            shaderAttributeBindVec m_attributeBinds;
            ///
            shaderIncludeNameVec m_includes;
            ///
            shaderFileVec m_files;
            ///
            shaderQualityVec m_qualities;
            ///
            shaderConstantVec m_constants;

            ///
            std::string m_selectedConfigName;
            ///
            std::string m_programName;

            fgGfxSLVersion m_preferredSLVersion; // FIXME - this sould be probably somewhere else

            ///
            fgGfxShaderPrecision m_defaultPrecision;

        public:
            /**
             * 
             */
            CShaderConfig();
            /**
             * 
             * @param filePath
             */
            CShaderConfig(const char *filePath);
            /**
             * 
             */
            virtual ~CShaderConfig();
            /**
             * 
             */
            virtual void clearAll(void);

            /**
             * 
             * @param filePath
             * @param SLver
             * @return 
             */
            fgBool load(const char *filePath = NULL, fgGfxSLVersion SLver = FG_GFX_SHADING_LANGUAGE_INVALID);
            /**
             * 
             * @return 
             */
            fgGfxShaderConfigType getType(void) const {
                return m_configType;
            }
            /**
             * 
             * @return 
             */
            shaderTypeVec & getRefShaderTypes(void) {
                return m_shaderTypes;
            }
            /**
             * 
             * @return 
             */
            shaderUniformBindVec & getRefUniformBinds(void) {
                return m_uniformBinds;
            }
            /**
             * 
             * @return 
             */
            shaderAttributeBindVec & getRefAttributeBinds(void) {
                return m_attributeBinds;
            }
            /**
             * 
             * @return 
             */
            shaderIncludeNameVec & getRefIncludes(void) {
                return m_includes;
            }
            /**
             * 
             * @return 
             */
            shaderFileVec & getRefFiles(void) {
                return m_files;
            }
            /**
             * 
             * @return 
             */
            shaderQualityVec & getRefQualities(void) {
                return m_qualities;
            }
            /**
             * 
             * @return 
             */
            shaderConstantVec & getRefConstants(void) {
                return m_constants;
            }
            /**
             * 
             * @return 
             */
            std::string & getProgramName(void) {
                return m_programName;
            }
            /**
             * 
             * @return 
             */
            std::string & getSelectedConfigName(void) {
                return m_selectedConfigName;
            }
            /**
             * 
             * @param _ver
             */
            void setPreferredSLVersion(fgGfxSLVersion version) {
                m_preferredSLVersion = version;
            }

        private:
            /**
             * 
             * @param SLver
             * @return 
             */
            fgBool private_parseData(fgGfxSLVersion SLver);
            /**
             * 
             * @param _definesSection
             * @return 
             */
            fgBool private_parseDefines(fgCfgSection *definesSection);
            /**
             */
            fgBool private_parseInclude(fgCfgSection *includeSection);

        };
    };
};

    #undef FG_INC_GFX_SHADER_CONFIG_BLOCK
#endif /* FG_INC_GFX_SHADER_CONFIG */
