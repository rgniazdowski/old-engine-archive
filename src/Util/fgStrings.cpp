/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgStrings.cpp
 * Author: vigilant
 * 
 * Created on January 13, 2015, 8:56 PM
 */

#include "fgStrings.h"
#include "fgColors.h"
#include <cstring>
#include <sstream>

using namespace fg;
//------------------------------------------------------------------------------

fgBool strings::doesMatch(const char* name, const char* query,
                          MatchMode mode) {
    if(!name || !query)
        return FG_FALSE;
    fgBool caseSensitive = FG_TRUE;
    fgBool result = FG_FALSE;
    if(!!(mode & MATCH_CASE_INSENSITIVE)) {
        caseSensitive = FG_FALSE;
    }
    fgBool exact = FG_FALSE;
    if(!!(mode & MATCH_EXACT) || mode == MATCH_DEFAULT) {
        exact = FG_TRUE;
    } else if(!!(mode & MATCH_SUBSTR)) {

    }
    if(exact) {
        result = isEqual(name, query, caseSensitive);
    } else if(caseSensitive) {
        result = (fgBool)!!(strstr(name, query));
    } else {
        result = (fgBool)!!(stristr(name, query));
    }
    return result;
}
//------------------------------------------------------------------------------

fgBool strings::doesMatch(const std::string& name,
                          const std::string& query,
                          MatchMode mode) {
    if(name.empty() || query.empty())
        return FG_FALSE;
    return doesMatch(name.c_str(), query.c_str(), mode);
}
//------------------------------------------------------------------------------

fgBool strings::doesMatch(const char* name, const char* query,
                          const char* mode) {
    if(!name || !query || !mode)
        return FG_FALSE;
    if(!name[0] || !query[0])
        return FG_FALSE;
    MatchMode modeEnum = strings::getMatchModeFromText(mode);
    return doesMatch(name, query, modeEnum);
}
//------------------------------------------------------------------------------

fgBool strings::doesMatch(const std::string& name,
                          const std::string& query,
                          const std::string& mode) {
    if(name.empty() || query.empty())
        return FG_FALSE;
    MatchMode modeEnum = strings::getMatchModeFromText(mode.c_str());
    return doesMatch(name.c_str(), query.c_str(), modeEnum);
}
//------------------------------------------------------------------------------

strings::MatchMode strings::getMatchModeFromText(const char* text) {
    if(!text)
        return MatchMode::MATCH_EXACT;
    return getMatchModeFromText(std::string(text));
}
//------------------------------------------------------------------------------

strings::MatchMode strings::getMatchModeFromText(const std::string& text) {
    if(text.empty())
        return MatchMode::MATCH_EXACT;
    MatchMode mode = MatchMode::MATCH_EXACT;
    CStringVector parts;
    split(text, ' ', parts);
    const unsigned int n = parts.size();
    for(unsigned int i = 0; i < n; i++) {
        if(isEqual(parts[i], "exact", FG_FALSE)) {
            mode |= MatchMode::MATCH_EXACT;
        } else if(isEqual(parts[i], "nocase", FG_FALSE) ||
                  isEqual(parts[i], "caseinsensitive", FG_FALSE)) {
            mode |= MatchMode::MATCH_CASE_INSENSITIVE;
        } else if(isEqual(parts[i], "substr", FG_FALSE) ||
                  isEqual(parts[i], "matchpart", FG_FALSE) ||
                  isEqual(parts[i], "partial", FG_FALSE)) {
            mode |= MatchMode::MATCH_SUBSTR;
        } else if(isEqual(parts[i], "all", FG_FALSE) ||
                  isEqual(parts[i], "alloccurrences", FG_FALSE)) {
            mode |= MatchMode::MATCH_ALL;
        } else if(isEqual(parts[i], "regex", FG_FALSE)) {
            mode |= MatchMode::MATCH_REGEX;
        }
    }
    return mode;
}
//------------------------------------------------------------------------------

void strings::toLower(std::string& output, const std::string & input) {
    if(input.empty())
        return;
    output.resize(input.length(), '\0');
    unsigned int n = input.length();
    for(unsigned int i = 0; i < n; i++) {
        output[i] = tolower(input[i]);
    }
}
//------------------------------------------------------------------------------

std::string strings::toLower(const std::string & input) {
    std::string output;
    if(input.empty())
        return output;
    output.resize(input.length(), '\0');
    unsigned int n = input.length();
    for(unsigned int i = 0; i < n; i++) {
        output[i] = tolower(input[i]);
    }
    return output;
}
//------------------------------------------------------------------------------

void strings::toLower(char* output, const char* input) {
    if(!output || !input)
        return;
    unsigned int n = strlen(input);
    if(!n)
        return;
    for(unsigned int i = 0; i < n; i++) {
        output[i] = tolower(input[i]);
    }
}
//------------------------------------------------------------------------------

char* strings::toLower(const char* input) {
    if(!input)
        return NULL;
    unsigned int n = strlen(input);
    char *output = strdup(input);
    if(!output)
        return NULL;
    for(unsigned int i = 0; i < n; i++) {
        output[i] = tolower(input[i]);
    }
    return output;
}
//------------------------------------------------------------------------------

void strings::toUpper(std::string& output, const std::string & input) {
    if(input.empty())
        return;
    output.resize(input.length(), '\0');
    unsigned int n = input.length();
    for(unsigned int i = 0; i < n; i++) {
        output[i] = toupper(input[i]);
    }
}
//------------------------------------------------------------------------------

std::string strings::toUpper(const std::string & input) {
    std::string output;
    if(input.empty())
        return output;
    output.resize(input.length(), '\0');
    unsigned int n = input.length();
    for(unsigned int i = 0; i < n; i++) {
        output[i] = toupper(input[i]);
    }
    return output;
}
//------------------------------------------------------------------------------

void strings::toUpper(char* output, const char* input) {
    if(!output || !input)
        return;
    unsigned int n = strlen(input);
    if(!n)
        return;
    for(unsigned int i = 0; i < n; i++) {
        output[i] = toupper(input[i]);
    }
}
//------------------------------------------------------------------------------

char* strings::toUpper(const char* input) {
    if(!input)
        return NULL;
    unsigned int n = strlen(input);
    char *output = strdup(input);
    if(!output)
        return NULL;
    for(unsigned int i = 0; i < n; i++) {
        output[i] = toupper(input[i]);
    }
    return output;
}
//------------------------------------------------------------------------------

std::string strings::trim(const std::string& str,
                          const std::string & whitespace) {
    const unsigned int strBegin = str.find_first_not_of(whitespace);
    if(strBegin == std::string::npos || strBegin > str.length())
        return ""; // no content

    const unsigned int strEnd = str.find_last_not_of(whitespace);
    const unsigned int strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}
//------------------------------------------------------------------------------

std::string strings::trim(const std::string& str,
                          const char *whitespace) {
    std::string whitespaceStr;
    if(!whitespace)
        whitespaceStr = " \t";
    else
        whitespaceStr = whitespace;
    return strings::trim(str, whitespaceStr);
}
//------------------------------------------------------------------------------

std::string strings::trim(const char *str,
                          const char *whitespace) {
    if(!str)
        return std::string();
    std::string whitespaceStr;
    if(!whitespace)
        whitespaceStr = " \t";
    else
        whitespaceStr = whitespace;
    return strings::trim(std::string(str), whitespaceStr);
}
//------------------------------------------------------------------------------

std::string strings::reduce(const std::string& str,
                            const std::string& fill,
                            const std::string & whitespace) {
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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

CVector<std::string> strings::split(const std::string &s,
                                    char delim) {
    CVector<std::string> elems;
    strings::split(s, delim, elems);
    return elems;
}
//------------------------------------------------------------------------------

fgBool strings::isFloat(const std::string & string) {
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
//------------------------------------------------------------------------------

fgBool strings::isNumber(const std::string & string) {
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
//------------------------------------------------------------------------------

fgBool strings::isEqual(const std::string& input,
                        const std::string& pattern,
                        const fgBool caseSensitive) {
    if(pattern.length() != input.length())
        return FG_FALSE;
    return strings::startsWith(input, pattern, caseSensitive);
}
//------------------------------------------------------------------------------

fgBool strings::isEqual(const char *input,
                        const char *pattern,
                        const fgBool caseSensitive) {
    if(strlen(pattern) != strlen(input))
        return FG_FALSE;
    return strings::startsWith(input, pattern, caseSensitive);
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

fgBool strings::containsChars(const std::string& input, const std::string & chars) {
    return (input.find_first_of(chars) != std::string::npos);
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

const char *strings::strstr(const std::string& str, const std::string & needle) {
    if(str.empty() || needle.empty())
        return NULL;
    return strings::strstr(str.c_str(), needle.c_str());
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

const char *strings::stristr(const std::string& str, const std::string & needle) {
    if(str.empty() || needle.empty())
        return NULL;
    return strings::stristr(str.c_str(), needle.c_str());
}
//------------------------------------------------------------------------------

Color4f strings::parseColor(const char *value) {
    if(!value)
        return Color4f(1.0f, 1.0f, 1.0f, 1.0f);
    return parseColor(std::string(value));
}
//------------------------------------------------------------------------------

Color4f strings::parseColor(const std::string & value) {
    if(value.empty())
        return Color4f(1.0f, 1.0f, 1.0f, 1.0f);
    int r = 255, g = 255, b = 255, a = 255;

    Color4f retColor;
    std::string colorStr = trim(value);
    if(startsWith(colorStr.c_str(), "rgbaf", FG_TRUE)) {
        sscanf(colorStr.c_str(), "rgbaf(%f,%f,%f,%f)", &retColor.r, &retColor.g, &retColor.b, &retColor.a);
    } else if(startsWith(colorStr.c_str(), "rgbf", FG_TRUE)) {
        sscanf(colorStr.c_str(), "rgbf(%f,%f,%f)", &retColor.r, &retColor.g, &retColor.b);
        retColor.a = 1.0f;
    } else if(startsWith(colorStr.c_str(), "rgba", FG_TRUE)) {
        sscanf(colorStr.c_str(), "rgba(%d,%d,%d,%d)", &r, &g, &b, &a);
        retColor.r = (float)r / 255.0f;
        retColor.g = (float)g / 255.0f;
        retColor.b = (float)b / 255.0f;
        retColor.a = (float)a / 255.0f;
    } else if(startsWith(colorStr.c_str(), "rgb", FG_TRUE)) {
        sscanf(colorStr.c_str(), "rgb(%d,%d,%d)", &r, &g, &b);
        retColor.r = (float)r / 255.0f;
        retColor.g = (float)g / 255.0f;
        retColor.b = (float)b / 255.0f;
        retColor.a = (float)a / 255.0f;
    } else if(startsWith(colorStr.c_str(), "#", FG_TRUE) || startsWith(colorStr.c_str(), "0x", FG_FALSE)) {
        // HEX!
        retColor = fg::colors::parseHEX(colorStr);
    } else if(startsWith(colorStr.c_str(), "(", FG_TRUE) || startsWith(colorStr.c_str(), "[", FG_TRUE)) {
        // ?
        parseVector(retColor, value);
    } else {
        // readable human name !
        retColor = fg::colors::getColor(colorStr);
    }

    return retColor;
}
//------------------------------------------------------------------------------
