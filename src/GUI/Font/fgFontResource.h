/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FONT_RESOURCE
    #define FG_INC_FONT_RESOURCE
    #define FG_INC_FONT_RESOURCE_BLOCK

    #include "Resource/fgResource.h"
    #include "Resource/fgResourceFactoryTypes.h"
    #include "GFX/Textures/fgTextureResource.h"
    #include "fgFontBuiltInTypes.h"

namespace fg {
    namespace gui {
        ///
        typedef unsigned int FontType;
        
        ///
        const unsigned int STANDARD_GRID_SIZE = 16;
        ///
        const unsigned int STANDARD_GRID_WIDTH = 16;
        ///
        const unsigned int STANDARD_GRID_HEIGHT = 16;
        ///
        const unsigned int STANDARD_ASCII_SIZE = 256;
        
        /// Invalid font type - initial value
        const FontType FONT_INVALID = 0x0000;
        /// Font made from texture resource
        const FontType FONT_TEXTURE = 0x0001;

        /*
         * Class definition for Font Resource - extends the Texture Resource
         */
        class CFontResource : public fg::gfx::CTextureResource {
        public:
            ///
            typedef fg::gfx::CTextureResource base_type;
            ///
            typedef CFontResource type;
            ///
            typedef CFontResource self_type;

        public:
            /**
             * Base constructor of the font resource object
             */
            CFontResource();
            /**
             * Constructor with additional parameter (path)
             * @param path
             */
            CFontResource(const char *path);
            /**
             * Constructor with additional parameter (path)
             * @param path
             */
            CFontResource(std::string& path);
            /**
             * Destructor of the font resource object
             */
            virtual ~CFontResource() {
                CFontResource::destroy();
            }

            /**
             * 
             * @return 
             */
            FG_RESOURCE_FACTORY_CREATE_FUNCTION(CFontResource)

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
            /**
             * 
             * @return 
             */
            virtual int getStep(void) const {
                return m_step;
            }
            /**
             * 
             * @return 
             */
            FontType getFontType(void) const {
                return m_fontType;
            }
            /**
             * 
             * @return 
             */
            SFontDataInfo &getDataInfo(void) {
                return m_info;
            }

        protected:
            /// 
            FontType m_fontType;
            ///
            SFontDataInfo m_info;
            /// 
            int m_step;
        };

        ///
        typedef CFontResource CFont;
    };
};
    #undef FG_INC_FONT_RESOURCE_BLOCK
#endif /* FG_INC_FONT_RESOURCE */
