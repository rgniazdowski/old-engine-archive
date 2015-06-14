/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_STRINGS
    #define FG_INC_STRINGS
    #define FG_INC_STRINGS_BLOCK

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #include "fgVector.h"
    #include "fgBool.h"

    #if defined(FG_USING_GLM)
        #include "glm/vec3.hpp"
        #include "glm/vec4.hpp"

namespace fg {
        #ifndef FG_MATH_GLM_COLOR_MASK
            #define FG_MATH_GLM_COLOR_MASK
    typedef ::glm::vec3 Color3f;
    typedef ::glm::vec4 Color4f;

    typedef ::glm::ivec3 Color3i;
    typedef ::glm::ivec4 Color4i;

    typedef ::glm::uvec3 Color3u;
    typedef ::glm::uvec4 Color4u;

        #endif /* FG_MATH_GLM_COLOR_MASK */
}
    #endif /* FG_USING_GLM */

    #include <cstdlib>

namespace fg {

    namespace strings {
        /**
         *
         * @param output
         * @param input
         */
        void toLower(std::string& output, const std::string& input);
        /**
         *
         * @param input
         * @return
         */
        std::string toLower(const std::string& input);
        /**
         *
         * @param output
         * @param input
         */
        void toLower(char* output, const char* input);
        /**
         *
         * @param input
         * @return
         */
        char* toLower(const char* input);

        /**
         *
         * @param output
         * @param input
         */
        void toUpper(std::string& output, const std::string& input);
        /**
         *
         * @param input
         */
        std::string toUpper(const std::string& input);
        /**
         *
         * @param output
         * @param input
         */
        void toUpper(char* output, const char* input);
        /**
         * 
         * @param input
         * @return
         */
        char* toUpper(const char* input);
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
                         const char* whitespace);
        /**
         * 
         * @param str
         * @param whitespace
         * @return 
         */
        std::string trim(const char* str,
                         const char* whitespace);
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
        CVector<std::string>& split(const std::string& s,
                                    char delim,
                                    CVector<std::string> &elems);
        /**
         * 
         * @param s
         * @param delim
         * @return 
         */
        CVector<std::string> split(const std::string& s,
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
        fgBool isEqual(const char* input,
                       const char* pattern,
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
        fgBool startsWith(const char* input,
                          const char* pattern,
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
        fgBool endsWith(const char* input,
                        const char* pattern,
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
        fgBool containsChars(const char* input,
                             const char* chars,
                             const fgBool caseSensitive = FG_TRUE);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char* strstr(const char* str, const char* needle);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char* strstr(const std::string& str, const std::string& needle);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char* stristr(const char* str, const char* needle);
        /**
         * 
         * @param str
         * @param needle
         * @return 
         */
        const char* stristr(const std::string& str, const std::string& needle);
        /**
         *
         * @param value
         * @return
         */
        Color4f parseColor(const char *value);
        /**
         *
         * @param value
         * @return
         */
        Color4f parseColor(const std::string& value);

        /**
         *
         * @param retVector
         * @param value
         */
        template <class VectorType>
        void parseVector(VectorType& retVector, const std::string& value);
        /**
         *
         * @param retVector
         * @param value
         */
        template <class VectorType>
        void parseVector(VectorType& retVector, const char *value);
    } // namespace strings

    namespace strings {

        //----------------------------------------------------------------------
        template <class VectorType>
        void parseVector(VectorType& retVector, const std::string& value) {
            if(value.empty()) {
                retVector = VectorType();
                return;
            }
            retVector = VectorType();
            std::string vectorStr = trim(value, std::string(" \t\n\r()[]"));
            fg::CStringVector parts;
            split(vectorStr, ',', parts);
            if(parts.empty()) {
                return;
            }
            int n = parts.size();
            if(n > (int)retVector.length()) {
                n = retVector.length();
            } else {
            }
            // 0 1 2  3 4 5
            // 0 1    2 3
            for(int i = 0, j = 0; i < n; i++, j++) {
                // BBOX FIX #
                if(n == 4 && retVector.length() == 6 && i == 2)
                    j++;
                retVector[j] = (typename VectorType::value_type) std::atof(parts[i].c_str());
            }
        }

        //----------------------------------------------------------------------
        template <class VectorType>
        void parseVector(VectorType& retVector, const char *value) {
            if(!value) {
                retVector = VectorType();
                return;
            }
            strings::parseVector<VectorType>(retVector, std::string(value));
        }
        //----------------------------------------------------------------------
    }
} // namespace fg

    #undef FG_INC_STRINGS_BLOCK
#endif /* FG_INC_STRINGS */
