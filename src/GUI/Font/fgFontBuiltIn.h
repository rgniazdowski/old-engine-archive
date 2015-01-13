/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FONT_BUILT_IN
    #define FG_INC_FONT_BUILT_IN
    #define FG_INC_FONT_BUILT_IN_BLOCK

    #include "fgFontResource.h"
    #include "fgFontBuiltInTypes.h"

namespace fg {
    namespace gui {

        /**
         *
         */
        class CFontBuiltInResource : public CFontResource {
        public:
            /**
             * 
             */
            CFontBuiltInResource();
            /**
             * 
             * @param rawFontData
             */
            CFontBuiltInResource(SFontBuiltInRawData *rawFontData);
            /**
             * 
             */
            virtual ~CFontBuiltInResource() {
                CFontBuiltInResource::destroy();
            }

        protected:
            /**
             * 
             */
            virtual void clear(void);

        public:
            /**
             * 
             * @return 
             */
            virtual fgBool create(void);
            /**
             * 
             */
            virtual void destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool recreate(void);
            /**
             * 
             */
            virtual void dispose(void);
            /**
             * 
             * @return 
             */
            virtual fgBool isDisposed(void) const;
            /**
             * 
             * @param rawFontData
             */
            void setBuiltInRawFontData(SFontBuiltInRawData *rawFontData);
            /**
             * 
             * @return 
             */
            SFontBuiltInRawData *getRawFontData(void) const {
                return m_rawFontData;
            }

        private:
            /// 
            SFontBuiltInRawData *m_rawFontData;
        };
        ///
        typedef CFontBuiltInResource CFontBuiltIn;
    };
};
    #define FG_FONT_TYPE_STB_BUILTIN	0x0040

    #undef FG_INC_FONT_BUILT_IN_BLOCK
#endif /* FG_INC_FONT_BUILT_IN */