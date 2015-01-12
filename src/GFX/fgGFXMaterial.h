/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_MATERIAL
    #define FG_INC_GFX_MATERIAL
    #define FG_INC_GFX_MATERIAL_BLOCK

    #ifndef FG_INC_GFX_TYPES
        #include "fgGFXTypes.h"
    #endif

    #ifndef FG_INC_RESOURCE
        #include "Resource/fgResource.h"
    #endif

    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

    #include <string>

namespace fg {
    namespace gfx {

        /**
         * Base structure describing material in graphics rendering
         */
        struct SMaterial {
        public:
            ///
            std::string name;

            ///
            fgColor3f ambient;
            ///
            fgColor3f diffuse;
            ///
            fgColor3f specular;
            ///
            fgColor3f transmittance;
            ///
            fgColor3f emission;

            /// The shininess parameter of the material
            float shininess;
            /// Index of refraction parameter
            float ior;
            /// The dissolve parameter of the material
            float dissolve; // 1 == opaque; 0 == fully transparent
            /// Illumination model (see http://www.fileformat.info/format/material/)
            int illuminationModel;

            /// Name of the ambient texture
            std::string ambientTexName;
            /// Name of the diffuse texture
            std::string diffuseTexName;
            /// Name of the specular texture
            std::string specularTexName;
            /// Name of the normal texture
            std::string normalTexName;

            /// Handle for the ambient texture
            FG_RHANDLE ambientTexHandle;
            /// Handle for the diffuse texture
            FG_RHANDLE diffuseTexHandle;
            /// Handle for the specular texture
            FG_RHANDLE specularTexHandle;
            /// Handle for the normal texture
            FG_RHANDLE normalTexHandle;

            ///
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
             * 
             * @param material
             */
            SMaterial(const SMaterial & material);

    #if 0
            SMaterial(tinyobj::material_t & material) {
                name = material.name;
                for(int i = 0; i < 3; i++)
                    ambient[i] = material.ambient[i];
                for(int i = 0; i < 3; i++)
                    diffuse[i] = material.diffuse[i];
                for(int i = 0; i < 3; i++)
                    specular[i] = material.specular[i];
                for(int i = 0; i < 3; i++)
                    transmittance[i] = material.transmittance[i];
                for(int i = 0; i < 3; i++)
                    emission[i] = material.emission[i];
                shininess = material.shininess;
                ior = material.ior;
                dissolve = material.dissolve;
                illuminationModel = material.illum;
                ambientTexName = material.ambient_texname;
                diffuseTexName = material.diffuse_texname;
                specularTexName = material.specular_texname;
                normalTexName = material.normal_texname;
            }
    #endif
            /**
             * 
             */
            virtual ~SMaterial() {
                clear();
            }
            /**
             *
             */
            void clear(void) {
                // #TODO - here is the place to call resource manager and decrease reference count for the used textures
                //FG_ResourceManager->unlockResource(ambientTexHandle);
                //FG_ResourceManager->unlockResource(diffuseTexHandle);
                //FG_ResourceManager->unlockResource(specularTexHandle);
                //FG_ResourceManager->unlockResource(normalTexHandle);
                // #FIXME #PLOX
                ambientTexName.clear();
                diffuseTexName.clear();
                specularTexName.clear();
                normalTexName.clear();
            }
        };
    };
};

    #undef FG_INC_GFX_MATERIAL_BLOCK
#endif /* FG_INC_GFX_MATERIAL */
