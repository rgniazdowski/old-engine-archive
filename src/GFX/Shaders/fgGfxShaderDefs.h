/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_SHADER_DEFS
    #define FG_INC_GFX_SHADER_DEFS
    #define FG_INC_GFX_SHADER_DEFS_BLOCK

    #ifdef FG_INC_GFX_STD_INC_BLOCK
        #error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderDefs inside of Gfx Standard Include header."
    #endif

    #include "GFX/fgGfxStdInc.h"
    #include "GFX/fgGfxAttribBits.h"
    #include "GFX/fgGfxAttributeData.h"

namespace fg {
    namespace gfx {
        namespace shaders {

            /**
             *
             */
            enum UsageMask {
                USAGE_EMPTY_BIT = 0,
                USAGE_FALLBACK_BIT = (1 << 0),
                USAGE_DEFAULT_BIT = (1 << 1),
                USAGE_LOW_QUALITY_BIT = (1 << 2),
                USAGE_MEDIUM_QUALITY_BIT = (1 << 3),
                USAGE_HIGH_QUALITY_BIT = (1 << 4),
                USAGE_VERTEX_LIGHTING_BIT = (1 << 5),
                USAGE_FRAGMENT_LIGHTING_BIT = (1 << 6),
                USAGE_FRAGMENT_LIGHTING_MUTLTIPLE_BIT = (1 << 7),
                USAGE_ENVIRONMENT_MAPPING_BIT = (1 << 8),
                USAGE_BUMP_MAPPING_BIT = (1 << 9),
                USAGE_MESH_SKINNING_BIT = (1 << 10),
                USAGE_MOTION_BLUR_BIT = (1 << 11),
                USAGE_ANTIALIASING_BIT = (1 << 12),
                USAGE_GAUSSIAN_BLUR_BIT = (1 << 13),
                USAGE_CARTOON_EFFECT_BIT = (1 << 14),
                USAGE_PARTICLE_RENDER_BIT = (1 << 15),
                USAGE_SKYBOX_RENDER_BIT = (1 << 16)
            }; // enum CategoryMask
            FG_ENUM_FLAGS(UsageMask);

            /**
             *
             */
            enum ShaderType {
                ///
                SHADER_FRAGMENT = (fgGFXenum)GL_FRAGMENT_SHADER,
                ///
                SHADER_VERTEX = (fgGFXenum)GL_VERTEX_SHADER,
    #if defined(FG_USING_OPENGL)
                ///
                SHADER_TESS_CONTROL = (fgGFXenum)GL_TESS_CONTROL_SHADER,
                ///
                SHADER_TESS_EVALUATION = (fgGFXenum)GL_TESS_EVALUATION_SHADER,
                ///
                SHADER_GEOMETRY = (fgGFXenum)GL_GEOMETRY_SHADER,
                /// GL_COMPUTE_SHADER is available only if the GL version is 4.3 or higher.
                ///
                SHADER_COMPUTE = (fgGFXenum)GL_COMPUTE_SHADER,
    #endif
                ///
                SHADER_INVALID = FG_NONE
            }; // enum ShaderType

            /**
             *
             */
            enum ShaderPrecision {
                ///
                SHADER_PRECISION_LOW,
                ///
                SHADER_PRECISION_MEDIUM,
                ///
                SHADER_PRECISION_HIGH,
                ///
                SHADER_PRECISION_DEFAULT
            }; // enum ShaderPrecision

            /**
             *
             */
            enum Precision {
                ///
                PRECISION_LOW,
                ///
                PRECISION_MEDIUM,
                ///
                PRECISION_HIGH,
                ///
                PRECISION_DEFAULT
            }; // enum Precision

            /**
             *
             */
            enum class PrecisionDataType {
                ///
                LOW_INT = (fgGFXenum)GL_LOW_INT,
                ///
                MEDIUM_INT = (fgGFXenum)GL_MEDIUM_INT,
                ///
                HIGH_INT = (fgGFXenum)GL_HIGH_INT,
                ///
                LOW_FLOAT = (fgGFXenum)GL_LOW_FLOAT,
                ///
                MEDIUM_FLOAT = (fgGFXenum)GL_MEDIUM_FLOAT,
                ///
                HIGH_FLOAT = (fgGFXenum)GL_HIGH_FLOAT
            }; // enum class PrecisionDataType

            /**
             *
             */
            enum UniformType {
                /// Invalid uniform type
                UNIFORM_INVALID,
                /// Model matrix
                UNIFORM_M_MATRIX,
                /// Model matrix
                UNIFORM_MODEL_MATRIX = UNIFORM_M_MATRIX,
                /// ModelView matrix
                UNIFORM_MV_MATRIX,
                /// ModelView matrix
                UNIFORM_MODEL_VIEW_MATRIX = UNIFORM_MV_MATRIX,
                /// ModelViewProjection matrix
                UNIFORM_MVP_MATRIX,
                /// ModelViewProjection matrix
                UNFIROM_MODEL_VIEW_PROJECTION_MATRIX = UNIFORM_MVP_MATRIX,
                /// Environment map (texture)
                UNIFORM_ENVIRONMENT_MAP,
                /// Ambient map (texture)
                UNIFORM_AMBIENT_MAP,
                /// Special specular map
                UNIFORM_SPECULAR_MAP,
                /// Normal map
                UNIFORM_NORMAL_MAP,
                /// Bump map
                UNIFORM_BUMP_MAP,
                /// First (plain) texture // diffuse
                UNIFORM_PLAIN_TEXTURE,
                /// First (plain) texture
                UNIFORM_DIFFUSE_TEXTURE = UNIFORM_PLAIN_TEXTURE,
                /// Some cube texture
                UNIFORM_CUBE_TEXTURE,
                /// Directional light (need probably a little more of those)
                UNIFORM_DIRECTIONAL_LIGHT,
                /// Material to be used
                UNIFORM_MATERIAL,
                /// Phase shift (custom parameter)
                UNIFORM_PHASE,
                /// Delta time (in milliseconds)
                UNIFORM_DELTA_TIME,
                /// Current timestamp
                UNIFORM_TIMESTAMP,
                /// Global custom color override
                UNIFORM_CUSTOM_COLOR,
                /// Attribute mask
                UNIFORM_ATTRIB_MASK,
                /// Whether the texture is used, >0.5 texture used (true), <0.5 false
                UNIFORM_USE_TEXTURE,
                /// Whether the skybox is being drawn (#FIXME)
                UNIFORM_DRAW_SKYBOX,
                /// Special array with bone matrices - used for mesh skinning
                UNIFORM_BONE_MATRICES,
                /// Special array with bone rigid transformations (less space, it's like mat2x4)
                UNIFORM_BONE_DUAL_QUATERNIONS,
                /// Shorter name for UNIFORM_BONE_DUAL_QUATERNIONS
                UNIFORM_BONE_DQUATS = UNIFORM_BONE_DUAL_QUATERNIONS,
                /// Custom uniform - can be any type (only one per shader program)
                UNIFORM_CUSTOM,

                NUM_UNIFORM_TYPES = 22
            }; // enum UniformType

            //------------------------------------------------------------------

            enum UniformBlockType {
                /// Invalid uniform block
                UNIFORM_BLOCK_INVALID,
                /// Block containing various transformation matrices
                /// like MVP, MV, M; plus scale, FOV, dual quaternions
                UNIFORM_BLOCK_TRANSFORM,
                /// Block containing information about current scene lighting
                /// including model of lighting, number of directional lights,
                /// spot lights etc.
                UNIFORM_BLOCK_LIGHTING_INFO,
                /// Block containing information about currently used material
                UNIFORM_BLOCK_MATERIAL_INFO

            }; // enum UniformBlockType

            //------------------------------------------------------------------
            const char* getShaderProgramConfigSuffix(void);

            //------------------------------------------------------------------

            /**
             * 
             * @param mask
             * @return 
             */
            unsigned int getUsageMaskCount(UsageMask mask);
            /**
             *
             * @param text
             * @return
             */
            UsageMask getUsageMaskFromText(const char* text);
            /**
             *
             * @param text
             * @return
             */
            UsageMask getUsageMaskFromText(const std::string& text);
            /**
             *
             * @param mask
             * @return
             */
            const char* getTextFromUsageMask(UsageMask mask);
            /**
             * 
             * @param mask
             * @param text
             */
            void getTextFromUsageMask(UsageMask mask, std::string& text);

            //------------------------------------------------------------------

            /**
             *
             * @param text
             * @return
             */
            ShaderType getShaderTypeFromText(const char* text);
            /**
             *
             * @param text
             * @return
             */
            ShaderType getShaderTypeFromText(const std::string& text);
            /**
             *
             * @param value
             * @return
             */
            const char* getTextFromShaderType(ShaderType value);
            /**
             * 
             * @param value
             * @return
             */
            const char* getShaderShortPrefix(ShaderType value);

            //------------------------------------------------------------------

            /**
             *
             * @param text
             * @return
             */
            Precision getPrecisionFromText(const char* text);
            /**
             *
             * @param text
             * @return
             */
            Precision getPrecisionFromText(const std::string& text);
            /**
             *
             * @param value
             * @return
             */
            const char* getTextFromPrecision(Precision value);

            //------------------------------------------------------------------

            /**
             *
             * @param text
             * @return
             */
            ShaderPrecision getShaderPrecisionFromText(const char* text);
            /**
             *
             * @param text
             * @return
             */
            ShaderPrecision getShaderPrecisionFromText(const std::string& text);
            /**
             *
             * @param value
             * @return
             */
            const char* getTextFromShaderPrecision(ShaderPrecision value);

            //------------------------------------------------------------------

            /**
             *
             * @param value
             * @return
             */
            Precision convertShaderPrecisionToPrecision(ShaderPrecision value);
            /**
             *
             * @param value
             * @return
             */
            ShaderPrecision convertPrecisionToShaderPrecision(Precision value);

            //------------------------------------------------------------------

            /**
             *
             * @param value
             * @return
             */
            const char* getShaderConfigSuffix(ShaderType value);

            //------------------------------------------------------------------

            /**
             *
             * @param text
             * @return
             */
            UniformType getUniformTypeFromText(const char* text);
            /**
             *
             * @param text
             * @return
             */
            UniformType getUniformTypeFromText(const std::string& text);
            /**
             *
             * @param value
             * @return
             */
            const char* getTextFromUniformType(UniformType value);

            //------------------------------------------------------------------

            /**
             *
             * @param text
             * @return
             */
            UniformBlockType getUniformBlockTypeFromText(const char* text);
            /**
             *
             * @param text
             * @return
             */
            UniformBlockType getUniformBlockTypeFromText(const std::string& text);
            /**
             * 
             * @param value
             * @return
             */
            const char* getTextFromUniformBlockType(UniformBlockType value);

            //------------------------------------------------------------------
    #if defined(FG_USING_OPENGL)
            const unsigned int NUM_SHADER_TYPES = 6;
    #elif defined(FG_USING_OPENGL_ES)
            const unsigned int NUM_SHADER_TYPES = 2;
    #endif

            ///
            extern const ShaderType g_SupportedShaderTypes[NUM_SHADER_TYPES];
            ///
            extern const char * const g_SupportedShaderTypesText[NUM_SHADER_TYPES];
            /// Array holding text representations of shader short prefixes
            extern const char * const g_ShaderShortPrefixesText[NUM_SHADER_TYPES];

            //------------------------------------------------------------------

            /// Array with all available Precision enum values
            extern const Precision g_PrecisionTypes[4];
            /// Special global constant array with text representations of
            /// corresponding precision enumeration value
            extern const char * const g_PrecisionTypesText[4];
            /// Special array with all available ShaderPrecision enum values
            extern const ShaderPrecision g_ShaderPrecisionTypes[4];

            //------------------------------------------------------------------

            /// Special global array with shader config suffixes
            /// Indexes in this array correspond with g_SupportedShaderTypes/Text[] 
            extern const char * const g_ShaderCfgSuffixes[NUM_SHADER_TYPES];

            //------------------------------------------------------------------

            /// Global constant array holding all available enum Uniform types
            extern const UniformType g_UniformTypes[NUM_UNIFORM_TYPES];
            /// Global constant array holding text representations of corresponding
            /// Uniform variable types.)
            extern const char * const g_UniformTypesText[NUM_UNIFORM_TYPES];

            //------------------------------------------------------------------

        } // namespace shaders

    } // namespace gfx
} // namespace fg

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SUniformBind {
            /// Name of the variable to bind
            std::string variableName;
            /// Location of the variable
            fgGFXint location;
            /// Type of the uniform variable to bind
            shaders::UniformType type;
            /// Data type of the uniform variable
            fgGFXenum dataType;
            /// Precision of the uniform
            shaders::Precision precision;
            /**
             * 
             */
            SUniformBind();
            /**
             * 
             * @param _variableName
             * @param _type
             */
            SUniformBind(const char *_variableName,
                         shaders::UniformType _type);
            /**
             * 
             */
            virtual ~SUniformBind();

            /**
             *
             * @param b
             * @return
             */
            inline int operator ==(const SUniformBind &b) const {
                return (b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
            /**
             *
             * @param b
             * @return
             */
            inline int operator !=(const SUniformBind &b) const {
                return !(b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
        }; // struct SUniformBind

        /**
         * This is special purpose structure for storing information about
         * uniform block. Basic information is retrieved from shader config files.
         * More information is taken from runtime (like offsets, validity).
         *
         */
        struct SUniformBlockBind {
            typedef SUniformBlockBind self_type;
            typedef CVector<SUniformBind> UniformBindVec;

            /// Name of the block
            std::string blockName;
            /// Index of the uniform block (it's like location for normal uniform)
            fgGFXint index;
            /// Index of the uniform block binding
            fgGFXint bindingIndex;
            /// Type of the uniform block
            shaders::UniformBlockType type;
            /// List of uniforms in this uniform block
            /// Member 'location' of SUniformBind structure contains now offset
            /// that tells position of given uniform in the buffer.
            UniformBindVec uniforms;

            /**
             *
             */
            SUniformBlockBind();
            /**
             * 
             * @param orig
             */
            SUniformBlockBind(const self_type& orig);
            /**
             *
             * @param _variableName
             * @param _type
             */
            SUniformBlockBind(const char *_blockName,
                              shaders::UniformBlockType _type);
            /**
             *
             */
            virtual ~SUniformBlockBind();

            //------------------------------------------------------------------

            /**
             *
             * @param uniformBind
             * @return
             */
            int addUniformBind(const SUniformBind& uniformBind);
            /**
             *
             * @param name
             * @return
             */
            fgBool hasUniform(const char* name) const;
            /**
             *
             * @param name
             * @return
             */
            fgBool hasUniform(const std::string& name) const;
            /**
             *
             * @param uniformBind
             * @return
             */
            fgBool hasUniform(const SUniformBind& uniformBind) const;
            /**
             *
             * @return
             */
            fgBool isEmpty(void) const;
            /**
             *
             * @return
             */
            unsigned int count(void) const;

            //------------------------------------------------------------------
            /**
             *
             * @param b
             * @return
             */
            inline int operator ==(const SUniformBlockBind &b) const {
                return (b.blockName.compare(this->blockName) == 0 && b.type == this->type);
            }
            /**
             *
             * @param b
             * @return
             */
            inline int operator !=(const SUniformBlockBind &b) const {
                return !(b.blockName.compare(this->blockName) == 0 && b.type == this->type);
            }
        }; // struct SUniformBlock;

        // The attribute qualifier can be used only with the data types:
        // float, vec2, vec3, vec4, mat2, mat3, and mat4.
        // Attribute variables cannot be declared as arrays or structures.

        /**
         *
         */
        struct SAttributeBind {
            /// Name of the variable to bind
            std::string variableName;
            /// Location to which given attribute will be bound (must not equal -1)
            fgGFXint location;
            /// The engine specific attribute type
            AttributeType type;
            /// Specifies the data type of a single element.
            /// Can be float, vec2, vec3, vec4, mat2, mat3, and mat4.
            fgGFXenum dataType;
            /// Currently used precision for this attribute
            shaders::Precision precision;
            /// Is the attribute bound?
            fgGFXboolean isBound;
            /**
             * 
             */
            SAttributeBind();
            /**
             * 
             * @param _variableName
             * @param _type
             */
            SAttributeBind(const char *_variableName,
                           AttributeType _type);
            /**
             * 
             */
            virtual ~SAttributeBind();
            /**
             * This will not only set the type but also location and dataType 
             * @param _type
             */
            void setType(AttributeType _type);


            inline int operator ==(const SAttributeBind &b) const {
                return (b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
            inline int operator !=(const SAttributeBind &b) const {
                return !(b.variableName.compare(this->variableName) == 0 && b.type == this->type);
            }
            inline bool operator >(const SAttributeBind& a) const {
                return (int)(this->type) > (int)(a.type);
            }
            inline bool operator <(const SAttributeBind& a) const {
                return (int)(this->type) < (int)(a.type);
            }
            inline bool operator >=(const SAttributeBind& a) const {
                return (int)(this->type) >= (int)(a.type);
            }
            inline bool operator <=(const SAttributeBind& a) const {
                return (int)(this->type) <= (int)(a.type);
            }
        }; // struct SAttributeBind

        /**
         *
         */
        struct SShaderConstantDef {
            ///
            std::string name;
            ///
            fgBool value;
            /**
             * 
             */
            SShaderConstantDef();
            /**
             * 
             * @param _name
             * @param _value
             */
            SShaderConstantDef(const char *_name, fgBool _value);
            /**
             * 
             */
            virtual ~SShaderConstantDef();

            // #FIXME - need some standard abstract class for that kind of operations
            /**
             * 
             * @param buf
             * @param maxlen
             */
            void toString(char *buf, unsigned int maxlen = 128);
            /**
             * 
             * @param buf
             * @return 
             */
            std::string& toString(std::string & buf);
        }; // struct SShaderConstantDef
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SHADER_DEFS_BLOCK
#endif /* FG_INC_GFX_SHADER_DEFS */
