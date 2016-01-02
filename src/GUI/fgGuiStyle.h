/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_STYLE
    #define FG_INC_GUI_STYLE
    #define FG_INC_GUI_STYLE_BLOCK

    #include "fgBuildConfig.h"
    #include "fgGuiStyleContent.h"
    #include "Resource/fgManagedDataFile.h"
    #include "Util/fgHandle.h"
    #include "Util/fgTag.h"
    #include "Hardware/fgQualityTypes.h" // #FIXME

    #define FG_GUI_STYLE_SHEET_NAME "StyleSheet" // #FIXME - string obfuscation

namespace fg {
    namespace gui {
        class CStyle;
        class CStyleManager;
    } // namespace gui
} // namespace fg

    #define FG_TAG_GUI_STYLE_NAME "GuiStyle"
    #define FG_TAG_GUI_STYLE  FG_TAG_TYPE(fg::gui::CStyle)
FG_TAG_TEMPLATE_ID_AUTO(fg::gui::CStyle, FG_TAG_GUI_STYLE_NAME);

    #if 1
        #include <unordered_map>
    #endif

namespace fg {
    namespace resource {
        template<typename THandleType, typename TMapKeyType> class CManagedDataFile;
    } // namespace resource

    namespace gui {

        /// Tag type for Gui Style
        typedef FG_TAG_GUI_STYLE StyleTag;
        /// Special handle type for Gui Style
        typedef fg::util::CHandle<StyleTag> StyleHandle;

        /*
         *
         */
        class CStyle : public fg::resource::CManagedDataFile<StyleHandle, Quality> {
            friend class fg::gui::CStyleManager;
        public:
            typedef CStyle self_type;
            typedef CStyle type;
            typedef fg::resource::CManagedDataFile<StyleHandle, Quality> base_type;
            typedef std::string HashKey;
    #if 1
            typedef std::unordered_map <HashKey, CStyleContent> StyleNameMap;
    #endif
        private:
            // 
            StyleNameMap m_styleContent;

        public:
            /**
             * 
             */
            CStyle();
            /**
             * 
             */
            virtual ~CStyle();

            /**
             * 
             * @return 
             */
            fgBool load(void);
            /**
             * 
             * @param path
             * @return 
             */
            fgBool load(const std::string& path);
            /**
             * 
             * @param path
             * @return 
             */
            fgBool load(const char *path);

            /**
             * 
             * @param info
             * @return 
             */
            CStyleContent &getContent(const std::string& info);
            /**
             * 
             * @param info
             * @return 
             */
            CStyleContent &getContent(const char *info);
            /**
             * 
             * @param info
             * @return 
             */
            CStyleContent *getContentPtr(const std::string& info) {
                return &getContent(info);
            }
            /**
             * 
             * @param info
             * @return 
             */
            CStyleContent *getContentPtr(const char *info) {
                return &getContent(info);
            }

            /**
             * 
             * @param contents
             * @param num
             * @param info
             * @return 
             */
            fgBool copyFullContent(CStyleContent *contents, int num, const std::string& info);
            /**
             * 
             * @param contents
             * @param num
             * @param info
             * @return 
             */
            fgBool copyFullContent(CStyleContent *contents, int num, const char *info);

        }; // class CStyle
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_STYLE_BLOCK
#endif /* FG_INC_GUI_STYLE */
