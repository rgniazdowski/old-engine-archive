/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_STRINGS_H_
#define _FG_STRINGS_H_

#include <fgVector.h>
#include <string>
#include <sstream>

class fgStrings
{
protected:
	fgStrings() { }
	~fgStrings() { }

public:
	/*
	 *
	 */
	static std::string trim(const std::string& str,
					 const std::string& whitespace = " \t")
	{
		const unsigned int strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos || strBegin > str.length())
			return ""; // no content

		const unsigned int strEnd = str.find_last_not_of(whitespace);
		const unsigned int strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}

	/*
	 *
	 */
	static std::string reduce(const std::string& str,
					   const std::string& fill = " ",
					   const std::string& whitespace = " \t")
	{
		// trim first
		std::string result = fgStrings::trim(str, whitespace);

		// replace sub ranges
		unsigned int beginSpace = result.find_first_of(whitespace);
		while (beginSpace != std::string::npos)
		{
			const unsigned int endSpace = result.find_first_not_of(whitespace, beginSpace);
			const unsigned int range = endSpace - beginSpace;

			result.replace(beginSpace, range, fill);

			const unsigned int newStart = beginSpace + fill.length();
			beginSpace = result.find_first_of(whitespace, newStart);
		}

		return result;
	}

	/*
	 *
	 */
	static fgVector<std::string> &split(const std::string &s, char delim, fgVector<std::string> &elems) 
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			if(!item.empty())
				elems.push_back(item);
		}
		return elems;
	}

	/*
	 *
	 */
	static fgVector<std::string> split(const std::string &s, char delim) 
	{
		fgVector<std::string> elems;
		fgStrings::split(s, delim, elems);
		return elems;
	}

	/*
	 *
	 */
	static fgBool isFloat(const std::string& string) 
	{
		std::string::const_iterator it = string.begin();
		fgBool decimalPoint = FG_FALSE;
		int minSize = 0;
		if(string.size()>0 && (string[0] == '-' || string[0] == '+')){
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
			} else if(!std::isdigit(*it) && (it+1 != string.end() || !decimalPoint)) {
				break;
			}
			++it;
		}
		return (fgBool)(((int)string.size()>minSize) && it == string.end() && decimalPoint);
	}
        
        /*
         *
         */
        static fgBool isNumber(const std::string& string) 
        {
            std::string::const_iterator it = string.begin();
            fgBool decimalPoint = FG_FALSE;
            int minSize = 0;
            if(string.size()>0 && (string[0] == '-' || string[0] == '+')){
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
            return (fgBool)(((int)string.size()>minSize) && it == string.end());
        }
        
	static fgBool startsWith(const std::string& input,
		const std::string& pattern,
		fgBool caseSensitive = FG_TRUE)
	{
		if(input.length() < pattern.length() || pattern.empty() || input.empty())
			return FG_FALSE;
		int plen = pattern.length();
		for(int i=0;i<plen;i++) {
			if( (caseSensitive && input[i] != pattern[i]) ||
				(!caseSensitive && tolower(input[i]) != tolower(pattern[i])) ) {
				return FG_FALSE;
			}
		}
		return FG_TRUE;
	}

	static fgBool startsWith(const char *input,
		const char *pattern,
		fgBool caseSensitive = FG_TRUE)
	{
		if(!input || !pattern)
			return FG_FALSE;
		int plen = strlen(pattern);
		int ilen = strlen(input);
		if(ilen < plen || !ilen || !plen
			)
			return FG_FALSE;
		for(int i=0;i<plen;i++) {
			if( (caseSensitive && input[i] != pattern[i]) ||
				(!caseSensitive && tolower(input[i]) != tolower(pattern[i])) ) {
				return FG_FALSE;
			}
		}
		return FG_TRUE;
	}

	static fgBool endsWith(const std::string& input,
		const std::string& pattern,
		fgBool caseSensitive = FG_TRUE)
	{
		if(input.length() < pattern.length() || pattern.empty() || input.empty())
			return FG_FALSE;
		int plen = pattern.length();
		int ilen = input.length();
		for(int i=ilen-1, p=plen-1;i>=0 && p>=0;i--,p--) {
			if( (caseSensitive && input[i] != pattern[p]) ||
				(!caseSensitive && tolower(input[i]) != tolower(pattern[p])) ) {
				return FG_FALSE;
			}
		}
		return FG_TRUE;
	}

	static fgBool endsWith(const char *input,
		const char *pattern,
		fgBool caseSensitive = FG_TRUE)
	{
		if(!input || !pattern)
			return FG_FALSE;
		int plen = strlen(pattern);
		int ilen = strlen(input);
		if(ilen < plen || !plen || !ilen)
			return FG_FALSE;
		for(int i=ilen-1, p=plen-1;i>=0 && p>=0;i--,p--) {
			if( (caseSensitive && input[i] != pattern[p]) ||
				(!caseSensitive && tolower(input[i]) != tolower(pattern[p])) ) {
				return FG_FALSE;
			}
		}
		return FG_TRUE;
	}

	static fgBool contains(const std::string& input, const std::string& chars)
	{
		return (input.find_first_of(chars) != std::string::npos);
	}
};

#endif /* _FG_STRINGS_H_ */
