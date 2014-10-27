/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgStringParser.h
 * Author: vigilant
 *
 * Created on October 25, 2014, 4:40 PM
 */

#ifndef _FG_STRING_PARSER_H_
    #define	_FG_STRING_PARSER_H_

///
/// #FIXME #PLOX
///

    #include "GFX/fgGFXColor.h"
    #include "GFX/fgGFXTypes.h"
    #include "Util/fgStrings.h"
    #include "fgColors.h"
    
/**
 * 
 */
class fgStringParser {
protected:
    /**
     * 
     */
    fgStringParser() { }
    /**
     * 
     */
    ~fgStringParser() { }

public:
    /**
     * 
     * @param value
     * @return 
     */
    static fgColor4f parseColor(const char *value) {
        if(!value)
            return fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        return parseColor(std::string(value));
    }
    
    /**
     * 
     * @param colorStr
     * @return 
     */
    static fgColor4f parseColor(const std::string& value) {
        if(value.empty())
            return fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        int r = 255, g = 255, b = 255, a = 255;
        fgColor4f retColor;
        std::string colorStr = fgStrings::trim(value);
        if(fgStrings::startsWith(colorStr.c_str(), "rgba", FG_TRUE)) {
            sscanf(colorStr.c_str(), "rgba(%d,%d,%d,%d)", &r, &g, &b, &a);
            retColor.r = (float)r / 255.0f;
            retColor.g = (float)g / 255.0f;
            retColor.b = (float)b / 255.0f;
            retColor.a = (float)a / 255.0f;
        } else if(fgStrings::startsWith(colorStr.c_str(), "rgb", FG_TRUE)) {
            sscanf(colorStr.c_str(), "rgb(%d,%d,%d)", &r, &g, &b);
            retColor.r = (float)r / 255.0f;
            retColor.g = (float)g / 255.0f;
            retColor.b = (float)b / 255.0f;
            retColor.a = (float)a / 255.0f;
        } else if(fgStrings::startsWith(colorStr.c_str(), "#", FG_TRUE) || fgStrings::startsWith(colorStr.c_str(), "0x", FG_FALSE)) {
            // HEX!
            retColor = fgColors::parseHEX(colorStr);
        } else {
            // readable human name !
            retColor = fgColors::getColorFromName(colorStr);
        }

        return retColor;
    }
    
    /**
     * 
     * @param retVector
     * @param value
     */
    template <class VectorType>
    static void parseVector(VectorType& retVector, const std::string& value) {
        if(value.empty()) {
            retVector = VectorType();
            return;
        }
        retVector = VectorType();
        std::string vectorStr = fgStrings::trim(value, std::string(" \t\n\r()[]"));
        fgStringVector parts;
        fgStrings::split(vectorStr, ',', parts);
        if(parts.empty()) {
            return;
        }
        int n = parts.size();
        if(n > retVector.length()) {
            n = retVector.length();
        } else {
        }
        // 0 1 2  3 4 5
        // 0 1    2 3
        for(int i=0,j=0; i < n; i++, j++) {
            // BBOX FIX #
            if(n == 4 && retVector.length() == 6 && i == 2)
                j++;
            retVector[j] = (typename VectorType::value_type) atof(parts[i].c_str());
        }
    }
    
    /**
     * 
     * @param retVector
     * @param value
     */
    template <class VectorType>
    static void parseVector(VectorType& retVector, const char *value) {
        if(!value) {
            retVector = VectorType();
            return;
        }
        fgStringParser::parseVector<VectorType>(retVector, std::string(value));
    }
};

#endif	/* _FG_STRING_PARSER_H_ */

