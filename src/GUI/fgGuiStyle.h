/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_STYLE_H_
    #define _FG_GUI_STYLE_H_

    #include "fgBuildConfig.h"
    #include "fgGuiStyleContent.h"
    #include "Resource/fgManagedDataFileBase.h"
    #include "Util/fgHandle.h"
    #include "Util/fgTag.h"
    #include "Hardware/fgQualityTypes.h" // #FIXME

    #define FG_GUI_STYLE_SHEET_NAME "StyleSheet" // #FIXME - string obfuscation

class fgGuiStyle;

    #define FG_TAG_GUI_STYLE_NAME	"GuiStyle"
    #define FG_TAG_GUI_STYLE		FG_TAG_TYPE(fgGuiStyle)

FG_TAG_TEMPLATE_ID_AUTO(fgGuiStyle, FG_TAG_GUI_STYLE_NAME);
typedef FG_TAG_GUI_STYLE fgGuiStyleTag;

// Special handle type for shader program
typedef fgHandle<fgGuiStyleTag> fgGuiStyleHandle;

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

/*
 *
 */
class fgGuiStyle : public fgManagedDataFileBase<fgGuiStyleHandle, fgQuality> {
    friend class fgGuiStyleManager;
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
    typedef fgManagedDataFileBase<fgGuiStyleHandle, fgQuality> base_type;
    typedef std::string hashKey;
    #ifdef FG_USING_MARMALADE	
    typedef std::hash<std::string> hashFunc;
    // Type for map, assigning style content value to string ID (case sensitive)
    typedef std::hash_map <hashKey, fgGuiStyleContent, hashFunc, smEqualTo> styleNameMap;
    #else
    typedef std::unordered_map <hashKey, fgGuiStyleContent> styleNameMap;
    #endif
private:
    // 
    styleNameMap m_styleContent;

public:
    /**
     * 
     */
    fgGuiStyle();
    /**
     * 
     */
    virtual ~fgGuiStyle();

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
    fgGuiStyleContent &getContent(const std::string& info);
    /**
     * 
     * @param info
     * @return 
     */
    fgGuiStyleContent &getContent(const char *info);
    /**
     * 
     * @param info
     * @return 
     */
    fgGuiStyleContent *getContentPtr(const std::string& info) {
        return &getContent(info);
    }
    /**
     * 
     * @param info
     * @return 
     */
    fgGuiStyleContent *getContentPtr(const char *info) {
        return &getContent(info);
    }
    
    /**
     * 
     * @param contents
     * @param num
     * @param info
     * @return 
     */
    fgBool copyFullContent(fgGuiStyleContent *contents, int num, const std::string& info);
    /**
     * 
     * @param contents
     * @param num
     * @param info
     * @return 
     */
    fgBool copyFullContent(fgGuiStyleContent *contents, int num, const char *info);

};

#endif /* _FG_GUI_STYLE_H_ */
