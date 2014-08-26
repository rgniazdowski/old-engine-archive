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

#include <fgArrayVector.h>
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
		const auto strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos)
			return ""; // no content

		const auto strEnd = str.find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;

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
		auto result = fgStrings::trim(str, whitespace);

		// replace sub ranges
		auto beginSpace = result.find_first_of(whitespace);
		while (beginSpace != std::string::npos)
		{
			const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
			const auto range = endSpace - beginSpace;

			result.replace(beginSpace, range, fill);

			const auto newStart = beginSpace + fill.length();
			beginSpace = result.find_first_of(whitespace, newStart);
		}

		return result;
	}

	/*
	 *
	 */
	static fgArrayVector<std::string> &split(const std::string &s, char delim, fgArrayVector<std::string> &elems) 
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
	static fgArrayVector<std::string> split(const std::string &s, char delim) 
	{
		fgArrayVector<std::string> elems;
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
			} else if(!std::isdigit(*it) && ((*it!='f') || it+1 != string.end() || !decimalPoint)) {
				break;
			}
			++it;
		}
		return (fgBool)(((int)string.size()>minSize) && it == string.end() && decimalPoint);
	}
};

#endif /* _FG_STRINGS_H_ */
