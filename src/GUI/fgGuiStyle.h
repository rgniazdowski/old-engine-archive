/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

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
    };
};

    #define FG_TAG_GUI_STYLE_NAME	"GuiStyle"
    #define FG_TAG_GUI_STYLE		FG_TAG_TYPE(fg::gui::CStyle)
FG_TAG_TEMPLATE_ID_AUTO(fg::gui::CStyle, FG_TAG_GUI_STYLE_NAME);

    #ifdef FG_USING_MARMALADE
        #include <hash_map>

        #ifndef FG_HASH_STD_STRING_TEMPLATE_DEFINED_
            #define FG_HASH_STD_STRING_TEMPLATE_DEFINED_

namespace std {

    template<> struct hash<std::string> {
        size_t operator ()(const std::string& x) const {
            return hash<const char*>()(x.c_str());
        }
    };
};

        #endif /* FG_HASH_STD_STRING_TEMPLATE_DEFINED_ */
    #else
        #include <unordered_map>
    #endif /* FG_USING_MARMALADE */

namespace fg {
    namespace resource {
        template<typename THandleType, typename TMapKeyType> class CManagedDataFile;
    };

    namespace gui {

        /// Tag type for Gui Style
        typedef FG_TAG_GUI_STYLE StyleTag;
        /// Special handle type for Gui Style
        typedef fg::util::CHandle<StyleTag> StyleHandle;

        /*
         *
         */
        class CStyle : public fg::resource::CManagedDataFile<StyleHandle, fgQuality> {
            friend class fg::gui::CStyleManager;
    #ifdef FG_USING_MARMALADE
        protected:

            struct smEqualTo {
                bool operator ()(const char* s1, const char* s2) const {
                    return strcmp(s1, s2) == 0;
                }
                bool operator ()(const std::string& s1, const std::string& s2) const {
                    return s1.compare(s2) == 0;
                }
            };
    #endif
        public:
            typedef fg::resource::CManagedDataFile<StyleHandle, fgQuality> base_type;
            typedef std::string HashKey;
    #ifdef FG_USING_MARMALADE	
            typedef std::hash<std::string> hashFunc;
            // Type for map, assigning style content value to string ID (case sensitive)
            typedef std::hash_map <HashKey, CStyleContent, hashFunc, smEqualTo> StyleNameMap;
    #else
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

        };
    };
};

    #undef FG_INC_GUI_STYLE_BLOCK
#endif /* FG_INC_GUI_STYLE */
