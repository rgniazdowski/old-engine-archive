/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_TEXTURE_MANAGER
    #define FG_INC_TEXTURE_MANAGER
    #define FG_INC_TEXTURE_MANAGER_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include "fgManagerBase.h"
    #include "fgTextureResource.h"
    #include "fgTextureTypes.h"
    #include "Util/fgTag.h"
    #include "Event/fgArgumentList.h"
    #include "Event/fgCallback.h"

namespace fg {
    namespace gfx {
        class CTextureManager;
    };
};

    #define FG_TAG_TEXTURE_MANAGER_NAME     "GfxTextureManager"
//#define FG_TAG_MANAGER_BASE_ID            20 //#FIXME - something automatic maybe?
    #define FG_TAG_TEXTURE_MANAGER          FG_TAG_TYPE(fg::gfx::CTextureManager)
//FG_TAG_TEMPLATE(fgResourceManager, FG_TAG_MANAGER_BASE_NAME, FG_TAG_MANAGER_BASE_ID);
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CTextureManager, FG_TAG_TEXTURE_MANAGER_NAME);

    #define FG_MANAGER_TEXTURE      0x00000004

namespace fg {
    namespace gfx {

        /// Special tag type for Texture Manager
        typedef FG_TAG_TEXTURE_MANAGER TextureManagerTag;

        /**
         * Class that allows to perform GROUP OPERATIONS on all textures. 
         */
        class CTextureManager : public fg::base::CManager {
        public:
            ///
            typedef fg::base::CManager base_type;
            ///
            typedef TextureManagerTag tag_type;

        public:
            /**
             * Default constructor for Texture Manager object
             * @param pResourceMgr
             */
            CTextureManager(fg::base::CManager *pResourceMgr);
            /**
             * Destructor for Texture Manager object
             */
            virtual ~CTextureManager();

        protected:
            /**
             * 
             */
            virtual void clear(void);

            /**
             * 
             */
            void registerResourceCallbacks(void);
            /**
             * 
             */
            void unregisterResourceCallbacks(void);

        public:
            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void);

            /**
             * 
             * @param pResourceMgr
             */
            void setResourceManager(fg::base::CManager *pResourceMgr);
            /**
             * 
             * @return 
             */
            fg::base::CManager *getResourceManager(void) const;

            /**
             * RAM -> VRAM.
             * Update of VRAM is unconditional. 
             * Update of RAM is dependent on:
             * - no image being already loaded,
             * - force option given.
             */
            fgBool allToVRAM(fgBool reupload = FG_FALSE);

            /**
             * Releases all non GFX (i.e. non VRAM) data
             */
            void allReleaseNonGFX(void);

            /**
             * Releases all GFX (i.e. texture ids) data
             */
            void allReleaseGFX(void);

            // #FIXME #TODO #P2
    #if defined(FG_USING_OPENGL_ES) || defined(FG_USING_OPENGL)
            static GLint translatePixelFormat(texture::PixelFormat pixelFormat);
            static GLint translateInternalPixelFormat(texture::InternalPixelFormat internalPixelFormat);
    #endif

            /**
             * 
             * @param texture
             * @param force
             * @return 
             */
            fgBool uploadToVRAM(CTexture *texture, fgBool force = FG_FALSE);
            /**
             * 
             * @param nameTag
             * @param force
             * @return 
             */
            fgBool uploadToVRAM(const std::string& nameTag, fgBool force = FG_FALSE);
            /**
             * 
             * @param nameTag
             * @param force
             * @return 
             */
            fgBool uploadToVRAM(const char *nameTag, fgBool force = FG_FALSE);

            /**
             * 
             * @param pTexture
             */
            void releaseGFX(CTexture *pTexture);

            /**
             * 
             * @param texHandle
             * @return 
             */
            STextureID &getRefGfxID(const resource::ResourceHandle& texHandle);
            /**
             * 
             * @param nameTag
             * @return 
             */
            STextureID &getRefGfxID(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            STextureID &getRefGfxID(const char *nameTag);

        private:
            /**
             * Uploads texture given via ID into VRAM.
             *
             * No force is possible ??? i.e. it is impossible to delete
             * texture through glDeleteTextures() and recreate it through
             * glGenTextures(). This is because OpenGL can UPDATE already
             * existing textures (i.e. use already generated texture IDs)
             *
             * (Still, fgTexture is capable of doing that: releaseAll() will
             * leave filename intact. It is however not needed, and should not
             * be used).
             */
            fgBool makeTexture(CTextureResource *textureResource);

            /**
             * 
             * @param argv
             * @return 
             */
            fgBool resourceCreatedHandler(fg::event::CArgumentList *argv);

        private:
            ///
            fg::base::CManager *m_pResourceMgr;
            ///
            fg::base::CManager *m_pEventMgr;
            ///
            fg::event::CFunctionCallback *m_resourceCreatedCallback;
            ///
            fgBool m_allInVRAM;
            ///
            STextureID m_emptyGfxID;
        };
    };
};

    #undef FG_INC_TEXTURE_MANAGER_BLOCK
#endif /* FG_INC_TEXTURE_MANAGER */
