/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_SHADER_CONFIG
    #define FG_INC_GFX_SHADER_CONFIG
    #define FG_INC_GFX_SHADER_CONFIG_BLOCK

    #ifdef FG_INC_GFX_STD_INC_BLOCK
        #error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderConfig inside of Gfx Standard Include header."
    #endif

    #include "fgGfxShaderDefs.h"
    #include "Hardware/fgQualityTypes.h"
    #include "Util/fgConfig.h"
    #include "Util/fgTag.h"    

namespace fg {
    namespace gfx {
        class CShaderConfig;
    }
};
    #define FG_TAG_GFX_SHADER_CONFIG_NAME       "GfxShaderConfig"
    #define FG_TAG_GFX_SHADER_CONFIG            FG_TAG_TYPE(fg::gfx::CShaderConfig)
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CShaderConfig, FG_TAG_GFX_SHADER_CONFIG_NAME);

namespace fg {
    namespace gfx {

        /// Tag type for Shader Config
        typedef FG_TAG_GFX_SHADER_CONFIG ShaderConfigTag;

        enum ShaderConfigType {
            SHADER_CONFIG_INVALID = 0,
            SHADER_CONFIG_PROGRAM = 1,
            SHADER_CONFIG_FRAGMENT = 2,
            SHADER_CONFIG_VERTEX = 3
    #if defined FG_USING_OPENGL
            ,
            SHADER_CONFIG_TESS_CONTROL = 4,
            SHADER_CONFIG_TESS_EVALUATION = 5,
            SHADER_CONFIG_GEOMETRY = 6,
            SHADER_CONFIG_COMPUTE = 7
    #endif
        };

        /**
         *
         * @param suffix
         * @return
         */
        ShaderConfigType getShaderConfigTypeFromSuffix(const char* suffix);
        /**
         * 
         * @param suffix
         * @return
         */
        ShaderConfigType getShaderConfigTypeFromSuffix(const std::string& suffix);

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
        class CShaderConfig : protected fg::util::CConfig {
        public:
            typedef fg::util::CConfig base_type;
            typedef CShaderConfig self_type;
            typedef CShaderConfig type;
            typedef ShaderConfigTag tag_type;

            typedef CVector<shaders::ShaderType> ShaderTypeVec;
            typedef CVector<SUniformBind> UniformBindVec;
            typedef CVector<SAttributeBind> AttributeBindVec;
            typedef CVector<std::string> IncludeNameVec;
            typedef CVector<std::string> FileNameVec;
            typedef CVector<Quality> QualityVec;
            typedef CVector<SShaderConstantDef> ConstantVec;

        protected:
            ///
            ShaderConfigType m_configType;
            ///
            ShaderTypeVec m_shaderTypes;

            /// 
            UniformBindVec m_uniformBinds;
            ///
            AttributeBindVec m_attributeBinds;
            ///
            IncludeNameVec m_includes;
            ///
            FileNameVec m_files;
            ///
            QualityVec m_qualities;
            ///
            ConstantVec m_constants;

            ///
            std::string m_selectedConfigName;
            ///
            std::string m_programName;

            ShadingLangVersion m_preferredSLVersion; // FIXME - this sould be probably somewhere else

            ///
            shaders::ShaderPrecision m_defaultPrecision;

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
            fgBool load(const char *filePath = NULL,
                        ShadingLangVersion SLver = FG_GFX_SHADING_LANGUAGE_INVALID);
            /**
             * 
             * @return 
             */
            inline ShaderConfigType getType(void) const {
                return m_configType;
            }
            /**
             * 
             * @return 
             */
            inline ShaderTypeVec& getShaderTypes(void) {
                return m_shaderTypes;
            }
            /**
             * 
             * @return 
             */
            inline ShaderTypeVec const& getShaderTypes(void) const {
                return m_shaderTypes;
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
            /**
             * 
             * @return 
             */
            inline AttributeBindVec& getAttributeBinds(void) {
                return m_attributeBinds;
            }
            /**
             * 
             * @return 
             */
            inline AttributeBindVec const& getAttributeBinds(void) const {
                return m_attributeBinds;
            }
            /**
             * 
             * @return 
             */
            inline IncludeNameVec& getIncludes(void) {
                return m_includes;
            }
            /**
             * 
             * @return 
             */
            inline IncludeNameVec const& getIncludes(void) const {
                return m_includes;
            }
            /**
             * 
             * @return 
             */
            inline FileNameVec& getFiles(void) {
                return m_files;
            }
            /**
             * 
             * @return 
             */
            inline FileNameVec const& getFiles(void) const {
                return m_files;
            }
            /**
             * 
             * @return 
             */
            inline QualityVec& getQualities(void) {
                return m_qualities;
            }
            /**
             * 
             * @return 
             */
            inline QualityVec const& getQualities(void) const {
                return m_qualities;
            }
            /**
             * 
             * @return 
             */
            inline ConstantVec& getRefConstants(void) {
                return m_constants;
            }
            /**
             * 
             * @return 
             */
            inline ConstantVec const& getRefConstants(void) const {
                return m_constants;
            }
            /**
             * 
             * @return 
             */
            inline std::string& getProgramName(void) {
                return m_programName;
            }
            /**
             * 
             * @return 
             */
            inline std::string const& getProgramName(void) const {
                return m_programName;
            }
            /**
             * 
             * @return 
             */
            inline const char* getProgramNameStr(void) const {
                return m_programName.c_str();
            }
            /**
             * 
             * @return 
             */
            inline std::string& getSelectedConfigName(void) {
                return m_selectedConfigName;
            }
            /**
             * 
             * @return 
             */
            inline std::string const& getSelectedConfigName(void) const {
                return m_selectedConfigName;
            }
            /**
             * 
             * @return 
             */
            inline const char* getSelectedConfigNameStr(void) const {
                return m_selectedConfigName.c_str();
            }
            /**
             * 
             * @param _ver
             */
            inline void setPreferredSLVersion(ShadingLangVersion version) {
                m_preferredSLVersion = version;
            }

        private:
            /**
             * 
             * @param SLver
             * @return 
             */
            fgBool private_parseData(ShadingLangVersion SLver);
            /**
             * 
             * @param _definesSection
             * @return 
             */
            fgBool private_parseDefines(util::SCfgSection *definesSection);
            /**
             * 
             * @param includeSection
             * @return 
             */
            fgBool private_parseInclude(util::SCfgSection *includeSection);

        }; // class CShaderConfig
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SHADER_CONFIG_BLOCK
#endif /* FG_INC_GFX_SHADER_CONFIG */
