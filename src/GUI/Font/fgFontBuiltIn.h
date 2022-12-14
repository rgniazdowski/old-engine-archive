/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
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

        const FontType FONT_STB_BUILTIN = 0x0004;

        /**
         *
         */
        class CFontBuiltInResource : public CFontResource {
        public:
            typedef CFontResource base_type;
            typedef CFontBuiltInResource self_type;
            typedef CFontBuiltInResource type;

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
                self_type::destroy();
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
        }; // class CFontBuiltInResource
        ///
        typedef CFontBuiltInResource CFontBuiltIn;
    } // namespace gui
} // namespace fg
    
    #undef FG_INC_FONT_BUILT_IN_BLOCK
#endif /* FG_INC_FONT_BUILT_IN */