/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_TEXTURE_RESOURCE
    #define FG_INC_TEXTURE_RESOURCE
    #define FG_INC_TEXTURE_RESOURCE_BLOCK

    #include "fgBuildConfig.h"
    #include "Resource/fgResource.h"
    #include "Resource/fgResourceFactoryTypes.h"

    #include "fgTextureTypes.h"
    #include "GFX/fgGFXStdInc.h"

namespace fg {
    namespace gfx {

        class CTextureManager;

        /*
         *
         */
        class CTextureResource : public ::fg::resource::CResource {
            friend class fg::gfx::CTextureManager;

        public:
            /**
             * Base constructor of the texture resource object
             */
            CTextureResource();
            /**
             * Constructor with additional parameter (path)
             * @param path
             */
            CTextureResource(const char *path);
            /**
             * Constructor with additional parameter (path)
             * @param path
             */
            CTextureResource(std::string& path);
            /**
             * Destructor of the texture resource object
             */
            virtual ~CTextureResource() {
                CTextureResource::destroy();
            }
            
            /**
             * 
             * @return 
             */
            FG_RESOURCE_FACTORY_CREATE_FUNCTION(CTextureResource)
            
        protected:
            // Clears the class data, this actually does not free allocated memory,
            // just resets base class attributes
            virtual void clear(void);

        public:
            /**
             * Create function loads/interprets data from file in ROM and place it in RAM memory.
             * @return 
             */
            virtual fgBool create(void);
            /**
             * Destroy all loaded data including additional metadata (called with destructor)
             */
            virtual void destroy(void);
            /**
             * Reloads any data, recreates the resource (refresh)
             * @return 
             */
            virtual fgBool recreate(void);
            /**
             * Dispose completely of the all loaded data, free all memory
             */
            virtual void dispose(void);
            /**
             * Check if resource is disposed (not loaded yet or disposed after)
             * @return 
             */
            virtual fgBool isDisposed(void) const;

        protected:
            /**
             * 
             * @param path
             * @return 
             */
            fgBool setFileTypeFromFilePath(std::string &path);
            /**
             * 
             * @return 
             */
            fgBool setFileTypeFromFilePath(void) {
                if(getFilePath(m_quality).empty())
                    return FG_FALSE;
                return setFileTypeFromFilePath(getFilePath(m_quality));
            }

        public:
            /**
             * 
             * @param flags
             */
            virtual void setFlags(const std::string& flags);

            // Releases non-GPU side of resources – should be
            // used to free data after uploading into VRAM
            void releaseNonGFX(void);
            /**
             * Checks whether RAM is owned by the object
             * @return 
             */
            fgBool hasOwnedRAM(void) const {
                if(m_rawData == NULL) {
                    return FG_FALSE;
                }
                return FG_TRUE;
            }
            /**
             * Get reference tothe texture id used by the low level graphics system - handle in OpenGL
             * @return 
             */
            fgGfxTextureID& getRefGfxID() {
                return m_textureGfxID;
            }
            /**
             * 
             * @return 
             */
            fgGfxTextureID* getPtrGfxID() {
                return &m_textureGfxID;
            }
            /**
             * Set the texture id used by the low level graphics system
             * @param id
             */
            void setGfxID(fgGFXuint id) {
                m_textureGfxID.id = id;
            }
            /**
             * Get width of the texture in pixels
             * @return 
             */
            int getWidth() const {
                return m_width;
            }
            /**
             * Get height of the texture in pixels
             * @return 
             */
            int getHeight(void) const {
                return m_height;
            }
            /**
             * Get number of color components
             * @return 
             */
            int getComponents(void) const {
                return m_components;
            }
            /**
             * Return pointer to raw pixel data (unsigned char array)
             * @return 
             */
            unsigned char* getRawData(void) const {
                return m_rawData;
            }
            /**
             * 
             * @param id
             * @return 
             */
            unsigned char *getCubeData(const fgTextureCubeMapID id) const {
                if((int)id >= FG_NUM_TEXTURE_CUBE_MAPS || (int)id < 0)
                    return NULL;
                return m_cubeData[id];
            }
            /**
             * Get texture file type (determined from extension)
             * @return 
             */
            fgTextureFileType getFileType(void) const {
                return m_fileType;
            }
            /**
             * Get texture type
             * @return 
             */
            fgTextureType getTextureType(void) const {
                return m_textureType;
            }
            /**
             * Get texture pixel format
             * @return 
             */
            fgTexturePixelFormat getPixelFormat(void) const {
                return m_pixelFormat;
            }
            /**
             * Set the texture type (usage)
             * @param textureType
             */
            void setTextureType(fgTextureType textureType) {
                m_textureType = textureType;
            }
            /**
             * Set the final texture pixel format
             * @param pixelFormat
             */
            void setPixelFormat(fgTexturePixelFormat pixelFormat) {
                m_pixelFormat = pixelFormat;
            }
            /**
             * 
             * @return 
             */
            fgBool isInVRAM(void) const {
                return m_isInVRAM;
            }

        protected:
            /**
             * 
             * @param toggle
             */
            void setIsInVRAM(fgBool toggle) {
                m_isInVRAM = toggle;
            }

        protected:
            /// Texture file type (by extension)
            fgTextureFileType m_fileType;
            /// Texture type and possible usage
            fgTextureType m_textureType;
            /// Final texture pixel format (data pixel format)
            fgTexturePixelFormat m_pixelFormat;

            union {

                /**
                 *
                 */
                struct {
                    ///
                    unsigned char* px;
                    ///
                    unsigned char* nx;
                    ///
                    unsigned char* py;
                    ///
                    unsigned char* ny;
                    ///
                    unsigned char* pz;
                    ///
                    unsigned char* nz;
                } m_cube;
                /// Storage for raw pixel data
                unsigned char* m_rawData;
                ///
                unsigned char* m_cubeData[FG_NUM_TEXTURE_CUBE_MAPS];
                ///
                unsigned char* m_texelsVec[8]; // #FIXME
            };
            /// Width of the texture in pixels
            int m_width;
            /// Height of the texture in pixels
            int m_height;
            /// Number of color components (gray scale, RGB, RGBA)
            int m_components;
            /// OpenGL texture id handle
            fgGfxTextureID m_textureGfxID;

        private:
            /// This is special trigger, it tells if texture was uploaded to VRAM
            /// When set to TRUE, even if gfxID is invalid it tells that texture
            /// needs to be re-uploaded
            ///
            /// On GL suspend all gfx IDs (including shaders, vbo's and others become invalid)
            fgBool m_isInVRAM;
        };

        ///
        typedef CTextureResource CTexture;
    };
};

    #undef FG_INC_TEXTURE_RESOURCE_BLOCK
#endif /* FG_INC_TEXTURE_RESOURCE */
