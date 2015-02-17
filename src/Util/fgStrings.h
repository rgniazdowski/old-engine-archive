/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_STRINGS
    #define FG_INC_STRINGS
    #define FG_INC_STRINGS_BLOCK

    #include "fgVector.h"
    #include "fgBool.h"

    #include <string>
    #include <cstring>
    #include <sstream>

namespace fg {

    /**
     *
     */
    namespace strings {
        /**
         * 
         * @param str
         * @param whitespace
         * @return 
         */
        std::string trim(const std::string& str,
                         const std::string& whitespace = " \t\r");
        /**
         * 
         * @param str
         * @param whitespace
         * @return 
         */
        std::string trim(const std::string& str,
                         const char *whitespace);
        /**
         * 
         * @param str
         * @param whitespace
         * @return 
         */
        std::string trim(const char *str,
                         const char *whitespace);
        /**
         * 
         * @param str
         * @param fill
         * @param whitespace
         * @return 
         */
        std::string reduce(const std::string& str,
                           const std::string& fill = " ",
                           const std::string& whitespace = " \t\r");
        /**
         * 
         * @param s
         * @param delim
         * @param elems
         * @return 
         */
        CVector<std::string>& split(const std::string &s,
                                    char delim,
                                    CVector<std::string> &elems);
        /**
         * 
         * @param s
         * @param delim
         * @return 
         */
        CVector<std::string> split(const std::string &s,
                                   char delim);
        /**
         * 
         * @param string
         * @return 
         */
        fgBool isFloat(const std::string& string);
        /**
         * 
         * @param string
         * @return 
         */
        fgBool isNumber(const std::string& string);
        /**
         * 
         * @param input
         * @param pattern
         * @param caseSensitive
         * @return 
         */
        fgBool isEqual(const std::string& input,
                       const std::string& pattern,
                       const fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param input
         * @param pattern
         * @param caseSensitive
         * @return 
         */
        fgBool isEqual(const char *input,
                       const char *pattern,
                       const fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param input
         * @param pattern
         * @param caseSensitive
         * @return 
         */
        fgBool startsWith(const std::string& input,
                          const std::string& pattern,
                          const fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param input
         * @param pattern
         * @param caseSensitive
         * @return 
         */
        fgBool startsWith(const char *input,
                          const char *pattern,
                          fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param input
         * @param pattern
         * @param caseSensitive
         * @return 
         */
        fgBool endsWith(const std::string& input,
                        const std::string& pattern,
                        fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param input
         * @param pattern
         * @param caseSensitive
         * @return 
         */
        fgBool endsWith(const char *input,
                        const char *pattern,
                        fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param input
         * @param chars
         * @return 
         */
        fgBool containsChars(const std::string& input, const std::string& chars);
        /**
         * 
         * @param input
         * @param chars
         * @param caseSensitive
         * @return 
         */
        fgBool containsChars(const char *input,
                             const char *chars,
                             const fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char *strstr(const char *str, const char *needle);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char *strstr(const std::string& str, const std::string& needle);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char *stristr(const char *str, const char *needle);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char *stristr(const std::string& str, const std::string& needle);
    };
};

    #undef FG_INC_STRINGS_BLOCK
#endif /* FG_INC_STRINGS */
