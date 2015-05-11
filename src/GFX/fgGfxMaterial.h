/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_MATERIAL
    #define FG_INC_GFX_MATERIAL
    #define FG_INC_GFX_MATERIAL_BLOCK

    #ifndef FG_INC_GFX_TYPES
        #include "fgGfxTypes.h"
    #endif

namespace fg {
    namespace gfx {

        class CShaderProgram;
        class CTextureResource;

        /**
         * Base structure describing material in graphics rendering
         * Used mainly for models (3d objects) - however at this point
         * it's usage is universal
         */
        struct SMaterial {
        public:
            ///
            typedef SMaterial self_type;
            ///
            typedef SMaterial type;

            /**
             *
             */
            enum StateFlags {
                NONE = 0x0000,
                FRONT_FACE_CCW = 0x0001,
                FRONT_FACE_CW = 0x0002,
                CULL_FACE = 0x0004,
                DEPTH_TEST = 0x0008,
                DEPTH_WRITE_MASK = 0x0010
            };

        public:
            /// Ambient color component
            Color4f ambient;
            /// Diffuse color component
            Color4f diffuse;
            /// Specular color component
            Color4f specular;
            /// Transmittance color component
            Color4f transmittance;
            /// Emission color component
            Color4f emission;
            /// The shininess parameter of the material
            float shininess;
            /// Index of refraction parameter
            float ior;
            /// The dissolve parameter of the material, works almost like alpha (transparency)
            float dissolve; // 1 == opaque; 0 == fully transparent
            /// Illumination model (see http://www.fileformat.info/format/material/)
            /// 0   Color on and Ambient off 
            /// 1   Color on and Ambient on 
            /// 2   Highlight on 
            /// 3   Reflection on and Ray trace on 
            /// 4   Transparency: Glass on 
            ///     Reflection: Ray trace on 
            ///
            /// 5   Reflection: Fresnel on and Ray trace on 
            /// 6   Transparency: Refraction on 
            ///     Reflection: Fresnel off and Ray trace on 
            ///
            /// 7   Transparency: Refraction on 
            ///     Reflection: Fresnel on and Ray trace on 
            ///
            /// 8   Reflection on and Ray trace off 
            /// 9   Transparency: Glass on 
            ///     Reflection: Ray trace off 
            ///
            /// 10  Casts shadows onto invisible surfaces 
            int illuminationModel;
            /// Special burn parameter smoothing between transparency and additive blending
            float burn;
            /// Blending mode
            BlendMode blendMode;
            /// Additional state flags (cull face, depth test, etc)
            StateFlags stateFlags;

            /// Pointer for the ambient texture
            CTextureResource* ambientTex;
            /// Pointer for the diffuse texture
            CTextureResource* diffuseTex;
            /// Pointer for the specular texture
            CTextureResource* specularTex;
            /// Pointer for the normal texture
            CTextureResource* normalTex;
            ///
            CShaderProgram *shaderProgram;
            /// Name of the material
            std::string name;
            ///
            std::string shaderName;
            /// Name of the ambient texture
            std::string ambientTexName;
            /// Name of the diffuse texture
            std::string diffuseTexName;
            /// Name of the specular texture
            std::string specularTexName;
            /// Name of the normal texture
            std::string normalTexName;
            /// Unknown parameters for the material are stored here
            std::map<std::string, std::string> unknownParam;

            /**
             *
             */
            SMaterial();

            /**
             * 
             * @return 
             */
            size_t getDataSize(void);
            /**
             * Get the size in bytes of the members in the beginning that are
             * trivially copy-able (struct of ints/floats, chars, double...)
             * @return
             */
            static size_t getDataStrideTrivial(void) {
                return sizeof (Color4f) * 5 + sizeof (float) * 4 + sizeof (int) +
                        sizeof (BlendMode) + sizeof (StateFlags);
            }

            /**
             * 
             * @param material
             */
            SMaterial(const SMaterial& material);
            /**
             * 
             */
            virtual ~SMaterial() {
                clear();
            }

            /**
             *
             * @param output
             * @param path
             * @return
             */
            static fgBool loadFromConfig(SMaterial& output, const std::string& path);
            /**
             *
             * @param path
             * @return
             */
            fgBool loadFromConfig(const std::string& path);
            /**
             *
             * @param path
             * @return
             */
            fgBool loadFromConfig(const char* path) {
                if(!path)
                    return FG_FALSE;
                return loadFromConfig(std::string(path));
            }

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            inline fgBool isBlend(void) const {
                return (fgBool)(blendMode != BlendMode::BLEND_OFF);
            }
            /**
             * 
             * @return 
             */
            inline StateFlags getFrontFace(void) const {
                if(isFrontFaceCCW()) {
                    return FRONT_FACE_CCW;
                } else if(isFrontFaceCW()) {
                    return FRONT_FACE_CW;
                }
            }
            /**
             * 
             * @return 
             */
            inline FrontFace getGfxFrontFace(void) const {
                if(isFrontFaceCCW()) {
                    return FrontFace::FACE_CCW;
                } else {
                    return FrontFace::FACE_CW;
                }
            }
            /**
             * 
             * @return 
             */
            inline fgBool isFrontFaceCCW(void) const {
                return (fgBool)((stateFlags & FRONT_FACE_CCW) && !(stateFlags & FRONT_FACE_CW));
            }
            /**
             * 
             * @return 
             */
            inline fgBool isFrontFaceCW(void) const {
                return (fgBool)((stateFlags & FRONT_FACE_CW) && !(stateFlags & FRONT_FACE_CCW));
            }
            /**
             * 
             * @return 
             */
            inline fgBool isCullFace(void) const {
                return (fgBool)!!(stateFlags & CULL_FACE);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isDepthTest(void) const {
                return (fgBool)!!(stateFlags & DEPTH_TEST);
            }
            /**
             * 
             * @return 
             */
            inline fgBool isDepthWriteMask(void) const {
                return (fgBool)!!(stateFlags & DEPTH_WRITE_MASK);
            }
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
            inline void setCullFace(const fgBool toggle = FG_TRUE) {
                setFlag(CULL_FACE, toggle);
            }
            /**
             * 
             * @param toggle
             */
            inline void setDepthTest(const fgBool toggle = FG_TRUE) {
                setFlag(DEPTH_TEST, toggle);
            }
            /**
             * 
             * @param toggle
             */
            inline void setDepthWriteMask(const fgBool toggle = FG_TRUE) {
                setFlag(DEPTH_WRITE_MASK, toggle);
            }
            /**
             * 
             * @param frontFace
             */
            inline void setFrontFace(const FrontFace frontFace) {
                if(frontFace == FACE_CCW) {
                    setFlag(FRONT_FACE_CW, FG_FALSE);
                    setFlag(FRONT_FACE_CCW, FG_TRUE);
                } else {
                    setFlag(FRONT_FACE_CW, FG_TRUE);
                    setFlag(FRONT_FACE_CCW, FG_FALSE);
                }
            }
            /**
             *
             */
            void clear(void);

            /**
             * 
             * @return 
             */
            unsigned int getSortingValue(const unsigned int maxValue = 255) const;
        };

        FG_ENUM_FLAGS(SMaterial::StateFlags);
        /**
         * 
         * @param flags
         * @param toggle
         */
        inline void SMaterial::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                stateFlags |= flags;
            } else {
                stateFlags |= flags;
                stateFlags ^= flags;
            }
        }

    };
};

    #undef FG_INC_GFX_MATERIAL_BLOCK
#endif /* FG_INC_GFX_MATERIAL */
