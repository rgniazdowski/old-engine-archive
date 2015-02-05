/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgStrings.cpp
 * Author: vigilant
 * 
 * Created on January 13, 2015, 8:56 PM
 */

#include "fgStrings.h"

using namespace fg;

/**
 * 
 * @param str
 * @param whitespace
 * @return 
 */
std::string strings::trim(const std::string& str,
                          const std::string& whitespace) {
    const unsigned int strBegin = str.find_first_not_of(whitespace);
    if(strBegin == std::string::npos || strBegin > str.length())
        return ""; // no content

    const unsigned int strEnd = str.find_last_not_of(whitespace);
    const unsigned int strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

/**
 * 
 * @param str
 * @param whitespace
 * @return 
 */
std::string strings::trim(const std::string& str,
                          const char *whitespace) {
    std::string whitespaceStr;
    if(!whitespace)
        whitespaceStr = " \t";
    return strings::trim(str, whitespaceStr);
}

/**
 * 
 * @param str
 * @param whitespace
 * @return 
 */
std::string strings::trim(const char *str,
                          const char *whitespace) {
    if(!str)
        return std::string();
    std::string whitespaceStr;
    if(!whitespace)
        whitespaceStr = " \t";
    return strings::trim(std::string(str), whitespaceStr);
}

/**
 * 
 * @param str
 * @param fill
 * @param whitespace
 * @return 
 */
std::string strings::reduce(const std::string& str,
                            const std::string& fill,
                            const std::string& whitespace) {
    // trim first
    std::string result = strings::trim(str, whitespace);

    // replace sub ranges
    unsigned int beginSpace = result.find_first_of(whitespace);
    while(beginSpace != std::string::npos) {
        const unsigned int endSpace = result.find_first_not_of(whitespace, beginSpace);
        const unsigned int range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const unsigned int newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

/**
 * 
 * @param s
 * @param delim
 * @param elems
 * @return 
 */
CVector<std::string>& strings::split(const std::string& s,
                                     char delim,
                                     CVector<std::string>& elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        if(!item.empty())
            elems.push_back(item);
    }
    return elems;
}

/**
 * 
 * @param s
 * @param delim
 * @return 
 */
CVector<std::string> strings::split(const std::string &s,
                                    char delim) {
    CVector<std::string> elems;
    strings::split(s, delim, elems);
    return elems;
}

/**
 * 
 * @param string
 * @return 
 */
fgBool strings::isFloat(const std::string& string) {
    std::string::const_iterator it = string.begin();
    fgBool decimalPoint = FG_FALSE;
    int minSize = 0;
    if(string.size() > 0 && (string[0] == '-' || string[0] == '+')) {
        it++;
        minSize++;
    }
    //
    // If you don't want to recognize floating point numbers in 
    // the format X.XXf, just remove the condition:
    // && ((*it!='f') || it+1 != string.end() || !decimalPoint)
    //
    // If you don't want to recognize numbers without '.' as 
    // float (i.e. not '1', only '1.', '1.0', '1.0f'...) 
    // then change the last line to:
    // return string.size()>minSize && it == string.end() && decimalPoint;
    //
    while(it != string.end()) {
        if(*it == '.') {
            if(!decimalPoint) decimalPoint = FG_TRUE;
            else break;
        } else if(!std::isdigit(*it) && (it + 1 != string.end() || !decimalPoint)) {
            break;
        }
        ++it;
    }
    return (fgBool)(((int)string.size() > minSize) && it == string.end() && decimalPoint);
}

/**
 * 
 * @param string
 * @return 
 */
fgBool strings::isNumber(const std::string& string) {
    std::string::const_iterator it = string.begin();
    fgBool decimalPoint = FG_FALSE;
    int minSize = 0;
    if(string.size() > 0 && (string[0] == '-' || string[0] == '+')) {
        it++;
        minSize++;
    }
    while(it != string.end()) {
        if(*it == '.') {
            if(!decimalPoint) decimalPoint = FG_TRUE;
            else break;
        } else if(!std::isdigit(*it)) {
            break;
        }
        ++it;
    }
    return (fgBool)(((int)string.size() > minSize) && it == string.end());
}

/**
 * 
 * @param input
 * @param pattern
 * @param caseSensitive
 * @return 
 */
fgBool strings::isEqual(const std::string& input,
                        const std::string& pattern,
                        const fgBool caseSensitive) {
    if(pattern.length() != input.length())
        return FG_FALSE;
    return strings::startsWith(input, pattern, caseSensitive);
}

/**
 * 
 * @param input
 * @param pattern
 * @param caseSensitive
 * @return 
 */
fgBool strings::isEqual(const char *input,
                        const char *pattern,
                        const fgBool caseSensitive) {
    if(strlen(pattern) != strlen(input))
        return FG_FALSE;
    return strings::startsWith(input, pattern, caseSensitive);
}

/**
 * 
 * @param input
 * @param pattern
 * @param caseSensitive
 * @return 
 */
fgBool strings::startsWith(const std::string& input,
                           const std::string& pattern,
                           const fgBool caseSensitive) {
    if(input.length() < pattern.length() || pattern.empty() || input.empty())
        return FG_FALSE;
    int plen = pattern.length();
    for(int i = 0; i < plen; i++) {
        if((caseSensitive && input[i] != pattern[i]) ||
           (!caseSensitive && tolower(input[i]) != tolower(pattern[i]))) {
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @param input
 * @param pattern
 * @param caseSensitive
 * @return 
 */
fgBool strings::startsWith(const char *input,
                           const char *pattern,
                           fgBool caseSensitive) {
    if(!input || !pattern)
        return FG_FALSE;
    int plen = strlen(pattern);
    int ilen = strlen(input);
    if(ilen < plen || !ilen || !plen)
        return FG_FALSE;
    for(int i = 0; i < plen; i++) {
        if((caseSensitive && input[i] != pattern[i]) ||
           (!caseSensitive && tolower(input[i]) != tolower(pattern[i]))) {
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @param input
 * @param pattern
 * @param caseSensitive
 * @return 
 */
fgBool strings::endsWith(const std::string& input,
                         const std::string& pattern,
                         fgBool caseSensitive) {
    if(input.length() < pattern.length() || pattern.empty() || input.empty())
        return FG_FALSE;
    int plen = pattern.length();
    int ilen = input.length();
    for(int i = ilen - 1, p = plen - 1; i >= 0 && p >= 0; i--, p--) {
        if((caseSensitive && input[i] != pattern[p]) ||
           (!caseSensitive && tolower(input[i]) != tolower(pattern[p]))) {
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @param input
 * @param pattern
 * @param caseSensitive
 * @return 
 */
fgBool strings::endsWith(const char *input,
                         const char *pattern,
                         fgBool caseSensitive) {
    if(!input || !pattern)
        return FG_FALSE;
    int plen = strlen(pattern);
    int ilen = strlen(input);
    if(ilen < plen || !plen || !ilen)
        return FG_FALSE;
    for(int i = ilen - 1, p = plen - 1; i >= 0 && p >= 0; i--, p--) {
        if((caseSensitive && input[i] != pattern[p]) ||
           (!caseSensitive && tolower(input[i]) != tolower(pattern[p]))) {
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @param input
 * @param chars
 * @return 
 */
fgBool strings::containsChars(const std::string& input, const std::string& chars) {
    return (input.find_first_of(chars) != std::string::npos);
}

/**
 * 
 * @param input
 * @param chars
 * @param caseSensitive
 * @return 
 */
fgBool strings::containsChars(const char *input,
                              const char *chars,
                              const fgBool caseSensitive) {
    if(!input || !chars)
        return FG_FALSE;
    int i = 0, j = 0;
    int ilen = strlen(input), clen = strlen(chars);
    if(!ilen || !clen)
        return FG_FALSE;
    for(; i < ilen; i++) {
        for(j = 0; j < clen; j++) {
            if((caseSensitive && input[i] == chars[j]) ||
               (!caseSensitive && tolower(input[i]) == tolower(chars[j]))) {
                return FG_TRUE;
            }
        }
    }
    return FG_FALSE;
}

/**
 * 
 * @param str
 * @param needle
 * @return 
 */
const char *strings::strstr(const char *str, const char *needle) {
    if(!needle || !*needle || !str) return str;
    char *p1 = (char*)str, *p2 = (char*)needle;
    char *p1Adv = (char*)str;
    while(*++p2)
        p1Adv++;
    while(*p1Adv) {
        char *p1Begin = p1;
        p2 = (char*)needle;
        while(*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if(!*p2)
            return p1Begin;
        p1 = p1Begin + 1;
        p1Adv++;
    }
    return NULL;
}

/**
 * 
 * @param str
 * @param needle
 * @return 
 */
const char *strings::strstr(const std::string& str, const std::string& needle) {
    if(str.empty() || needle.empty())
        return NULL;
    return strings::strstr(str.c_str(), needle.c_str());
}

/**
 * 
 * @param str
 * @param needle
 * @return 
 */
const char *strings::stristr(const char *str, const char *needle) {
    if(!needle || !*needle || !str) return str;
    char *p1 = (char*)str, *p2 = (char*)needle;
    char *p1Adv = (char*)str;
    while(*++p2)
        p1Adv++;
    while(*p1Adv) {
        char *p1Begin = p1;
        p2 = (char*)needle;
        while(*p1 && *p2 && (tolower(*p1) == tolower(*p2))) {
            p1++;
            p2++;
        }
        if(!*p2)
            return p1Begin;
        p1 = p1Begin + 1;
        p1Adv++;
    }
    return NULL;
}

/**
 * 
 * @param str
 * @param needle
 * @return 
 */
const char *strings::stristr(const std::string& str, const std::string& needle) {
    if(str.empty() || needle.empty())
        return NULL;
    return strings::stristr(str.c_str(), needle.c_str());
}