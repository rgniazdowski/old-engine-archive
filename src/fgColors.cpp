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
 * File:   fgColors.cpp
 * Author: vigilant
 * 
 * Created on October 20, 2014, 4:25 PM
 */

#include "fgBuildConfig.h"
#include "fgColors.h"
#include "fgBool.h"
#include "Util/fgStrings.h"

#if defined(FG_USING_PLATFORM_ANDROID)
#include <cstdlib>
#endif

namespace fg {
    namespace colors {
        ///
        const unsigned int NUM_COLORS = 141;
        ///
        static fgBool s_isInit = FG_FALSE;

    };
};

struct SColorName
{
    ///
    fgColor4f color;
    ///
    std::string name;

    SColorName() { }

    /**
     * 
     * @param _color
     * @param _name
     */
    SColorName(const std::string& _name,
              const fgColor4f& _color) :
    color(_color),
    name(_name) { }

    /**
     * 
     * @param _name
     * @param _hexColor
     * @param _comp
     */
    SColorName(const std::string& _name,
              const unsigned long _hexColor,
              const unsigned char _comp) :
    name(_name) {
        color = fg::colors::parseHEX(_hexColor, _comp);
    }

    /**
     * 
     * @param _name
     * @param _hexStr
     */
    SColorName(const std::string& _name, const std::string& _hexStr) :
    name(_name) {
        color = fg::colors::parseHEX(_hexStr);
    }
};

/// Special array containing 140 standard colors and human readable names
fg::CVector<SColorName> g_colorNames;

#if 0
static const SColorName s_colorNames[140]; // = {
SColorName(std::string("AliceBlue"), std::string("F0F8FF")),
SColorName(std::string("AntiqueWhite"), std::string("FAEBD7")),
SColorName(std::string("Aqua"), std::string("00FFFF")),
SColorName(std::string("Aquamarine"), std::string("7FFFD4")),
SColorName(std::string("Azure"), std::string("F0FFFF")),
SColorName(std::string("Beige"), std::string("F5F5DC")),
SColorName(std::string("Bisque"), std::string("FFE4C4")),
SColorName(std::string("Black"), std::string("000000")),
SColorName(std::string("BlanchedAlmond"), std::string("FFEBCD")),
SColorName(std::string("Blue"), std::string("0000FF")),
SColorName(std::string("BlueViolet"), std::string("8A2BE2")),
SColorName(std::string("Brown"), std::string("A52A2A")),
SColorName(std::string("BurlyWood"), std::string("DEB887")),
SColorName(std::string("CadetBlue"), std::string("5F9EA0")),
SColorName(std::string("Chartreuse"), std::string("7FFF00")),
SColorName(std::string("Chocolate"), std::string("D2691E")),
SColorName(std::string("Coral"), std::string("FF7F50")),
SColorName(std::string("CornflowerBlue"), std::string("6495ED")),
SColorName(std::string("Cornsilk"), std::string("FFF8DC")),
SColorName(std::string("Crimson"), std::string("DC143C")),
SColorName(std::string("Cyan"), std::string("00FFFF")),
SColorName(std::string("DarkBlue"), std::string("00008B")),
SColorName(std::string("DarkCyan"), std::string("008B8B")),
SColorName(std::string("DarkGoldenRod"), std::string("B8860B")),
SColorName(std::string("DarkGray"), std::string("A9A9A9")),
SColorName(std::string("DarkGreen"), std::string("006400")),
SColorName(std::string("DarkKhaki"), std::string("BDB76B")),
SColorName(std::string("DarkMagenta"), std::string("8B008B")),
SColorName(std::string("DarkOliveGreen"), std::string("556B2F")),
SColorName(std::string("DarkOrange"), std::string("FF8C00")),
SColorName(std::string("DarkOrchid"), std::string("9932CC")),
SColorName(std::string("DarkRed"), std::string("8B0000")),
SColorName(std::string("DarkSalmon"), std::string("E9967A")),
SColorName(std::string("DarkSeaGreen"), std::string("8FBC8F")),
SColorName(std::string("DarkSlateBlue"), std::string("483D8B")),
SColorName(std::string("DarkSlateGray"), std::string("2F4F4F")),
SColorName(std::string("DarkTurquoise"), std::string("00CED1")),
SColorName(std::string("DarkViolet"), std::string("9400D3")),
SColorName(std::string("DeepPink"), std::string("FF1493")),
SColorName(std::string("DeepSkyBlue"), std::string("00BFFF")),
SColorName(std::string("DimGray"), std::string("696969")),
SColorName(std::string("DodgerBlue"), std::string("1E90FF")),
SColorName(std::string("FireBrick"), std::string("B22222")),
SColorName(std::string("FloralWhite"), std::string("FFFAF0")),
SColorName(std::string("ForestGreen"), std::string("228B22")),
SColorName(std::string("Fuchsia"), std::string("FF00FF")),
SColorName(std::string("Gainsboro"), std::string("DCDCDC")),
SColorName(std::string("GhostWhite"), std::string("F8F8FF")),
SColorName(std::string("Gold"), std::string("FFD700")),
SColorName(std::string("GoldenRod"), std::string("DAA520")),
SColorName(std::string("Gray"), std::string("808080")),
SColorName(std::string("Green"), std::string("008000")),
SColorName(std::string("GreenYellow"), std::string("ADFF2F")),
SColorName(std::string("HoneyDew"), std::string("F0FFF0")),
SColorName(std::string("HotPink"), std::string("FF69B4")),
SColorName(std::string("IndianRed"), std::string("CD5C5C")),
SColorName(std::string("Indigo"), std::string("4B0082")),
SColorName(std::string("Ivory"), std::string("FFFFF0")),
SColorName(std::string("Khaki"), std::string("F0E68C")),
SColorName(std::string("Lavender"), std::string("E6E6FA")),
SColorName(std::string("LavenderBlush"), std::string("FFF0F5")),
SColorName(std::string("LawnGreen"), std::string("7CFC00")),
SColorName(std::string("LemonChiffon"), std::string("FFFACD")),
SColorName(std::string("LightBlue"), std::string("ADD8E6")),
SColorName(std::string("LightCoral"), std::string("F08080")),
SColorName(std::string("LightCyan"), std::string("E0FFFF")),
SColorName(std::string("LightGoldenRodYellow"), std::string("FAFAD2")),
SColorName(std::string("LightGray"), std::string("D3D3D3")),
SColorName(std::string("LightGreen"), std::string("90EE90")),
SColorName(std::string("LightPink"), std::string("FFB6C1")),
SColorName(std::string("LightSalmon"), std::string("FFA07A")),
SColorName(std::string("LightSeaGreen"), std::string("20B2AA")),
SColorName(std::string("LightSkyBlue"), std::string("87CEFA")),
SColorName(std::string("LightSlateGray"), std::string("778899")),
SColorName(std::string("LightSteelBlue"), std::string("B0C4DE")),
SColorName(std::string("LightYellow"), std::string("FFFFE0")),
SColorName(std::string("Lime"), std::string("00FF00")),
SColorName(std::string("LimeGreen"), std::string("32CD32")),
SColorName(std::string("Linen"), std::string("FAF0E6")),
SColorName(std::string("Magenta"), std::string("FF00FF")),
SColorName(std::string("Maroon"), std::string("800000")),
SColorName(std::string("MediumAquaMarine"), std::string("66CDAA")),
SColorName(std::string("MediumBlue"), std::string("0000CD")),
SColorName(std::string("MediumOrchid"), std::string("BA55D3")),
SColorName(std::string("MediumPurple"), std::string("9370DB")),
SColorName(std::string("MediumSeaGreen"), std::string("3CB371")),
SColorName(std::string("MediumSlateBlue"), std::string("7B68EE")),
SColorName(std::string("MediumSpringGreen"), std::string("00FA9A")),
SColorName(std::string("MediumTurquoise"), std::string("48D1CC")),
SColorName(std::string("MediumVioletRed"), std::string("C71585")),
SColorName(std::string("MidnightBlue"), std::string("191970")),
SColorName(std::string("MintCream"), std::string("F5FFFA")),
SColorName(std::string("MistyRose"), std::string("FFE4E1")),
SColorName(std::string("Moccasin"), std::string("FFE4B5")),
SColorName(std::string("NavajoWhite"), std::string("FFDEAD")),
SColorName(std::string("Navy"), std::string("000080")),
SColorName(std::string("OldLace"), std::string("FDF5E6")),
SColorName(std::string("Olive"), std::string("808000")),
SColorName(std::string("OliveDrab"), std::string("6B8E23")),
SColorName(std::string("Orange"), std::string("FFA500")),
SColorName(std::string("OrangeRed"), std::string("FF4500")),
SColorName(std::string("Orchid"), std::string("DA70D6")),
SColorName(std::string("PaleGoldenRod"), std::string("EEE8AA")),
SColorName(std::string("PaleGreen"), std::string("98FB98")),
SColorName(std::string("PaleTurquoise"), std::string("AFEEEE")),
SColorName(std::string("PaleVioletRed"), std::string("DB7093")),
SColorName(std::string("PapayaWhip"), std::string("FFEFD5")),
SColorName(std::string("PeachPuff"), std::string("FFDAB9")),
SColorName(std::string("Peru"), std::string("CD853F")),
SColorName(std::string("Pink"), std::string("FFC0CB")),
SColorName(std::string("Plum"), std::string("DDA0DD")),
SColorName(std::string("PowderBlue"), std::string("B0E0E6")),
SColorName(std::string("Purple"), std::string("800080")),
SColorName(std::string("Red"), std::string("FF0000")),
SColorName(std::string("RosyBrown"), std::string("BC8F8F")),
SColorName(std::string("RoyalBlue"), std::string("4169E1")),
SColorName(std::string("SaddleBrown"), std::string("8B4513")),
SColorName(std::string("Salmon"), std::string("FA8072")),
SColorName(std::string("SandyBrown"), std::string("F4A460")),
SColorName(std::string("SeaGreen"), std::string("2E8B57")),
SColorName(std::string("SeaShell"), std::string("FFF5EE")),
SColorName(std::string("Sienna"), std::string("A0522D")),
SColorName(std::string("Silver"), std::string("C0C0C0")),
SColorName(std::string("SkyBlue"), std::string("87CEEB")),
SColorName(std::string("SlateBlue"), std::string("6A5ACD")),
SColorName(std::string("SlateGray"), std::string("708090")),
SColorName(std::string("Snow"), std::string("FFFAFA")),
SColorName(std::string("SpringGreen"), std::string("00FF7F")),
SColorName(std::string("SteelBlue"), std::string("4682B4")),
SColorName(std::string("Tan"), std::string("D2B48C")),
SColorName(std::string("Teal"), std::string("008080")),
SColorName(std::string("Thistle"), std::string("D8BFD8")),
SColorName(std::string("Tomato"), std::string("FF6347")),
SColorName(std::string("Turquoise"), std::string("40E0D0")),
SColorName(std::string("Violet"), std::string("EE82EE")),
SColorName(std::string("Wheat"), std::string("F5DEB3")),
SColorName(std::string("White"), std::string("FFFFFF")),
SColorName(std::string("WhiteSmoke"), std::string("F5F5F5")),
SColorName(std::string("Yellow"), std::string("FFFF00")),
SColorName(std::string("YellowGreen"), std::string("9ACD32"))
};
#endif

using namespace fg;

//------------------------------------------------------------------------------

void colors::initialize(void) {
    if(colors::s_isInit)
        return;

    colors::s_isInit = FG_TRUE;

    g_colorNames.clear_optimised();
    g_colorNames.reserve(NUM_COLORS);

    g_colorNames.push_back(SColorName(std::string("AliceBlue"), std::string("F0F8FF")));
    g_colorNames.push_back(SColorName(std::string("AntiqueWhite"), std::string("FAEBD7")));
    g_colorNames.push_back(SColorName(std::string("Aqua"), std::string("00FFFF")));
    g_colorNames.push_back(SColorName(std::string("Aquamarine"), std::string("7FFFD4")));
    g_colorNames.push_back(SColorName(std::string("Azure"), std::string("F0FFFF")));
    g_colorNames.push_back(SColorName(std::string("Beige"), std::string("F5F5DC")));
    g_colorNames.push_back(SColorName(std::string("Bisque"), std::string("FFE4C4")));
    g_colorNames.push_back(SColorName(std::string("Black"), std::string("000000")));
    g_colorNames.push_back(SColorName(std::string("BlanchedAlmond"), std::string("FFEBCD")));
    g_colorNames.push_back(SColorName(std::string("Blue"), std::string("0000FF")));
    g_colorNames.push_back(SColorName(std::string("BlueViolet"), std::string("8A2BE2")));
    g_colorNames.push_back(SColorName(std::string("Brown"), std::string("A52A2A")));
    g_colorNames.push_back(SColorName(std::string("BurlyWood"), std::string("DEB887")));
    g_colorNames.push_back(SColorName(std::string("CadetBlue"), std::string("5F9EA0")));
    g_colorNames.push_back(SColorName(std::string("Chartreuse"), std::string("7FFF00")));
    g_colorNames.push_back(SColorName(std::string("Chocolate"), std::string("D2691E")));
    g_colorNames.push_back(SColorName(std::string("Coral"), std::string("FF7F50")));
    g_colorNames.push_back(SColorName(std::string("CornflowerBlue"), std::string("6495ED")));
    g_colorNames.push_back(SColorName(std::string("Cornsilk"), std::string("FFF8DC")));
    g_colorNames.push_back(SColorName(std::string("Crimson"), std::string("DC143C")));
    g_colorNames.push_back(SColorName(std::string("Cyan"), std::string("00FFFF")));
    g_colorNames.push_back(SColorName(std::string("DarkBlue"), std::string("00008B")));
    g_colorNames.push_back(SColorName(std::string("DarkCyan"), std::string("008B8B")));
    g_colorNames.push_back(SColorName(std::string("DarkGoldenRod"), std::string("B8860B")));
    g_colorNames.push_back(SColorName(std::string("DarkGray"), std::string("A9A9A9")));
    g_colorNames.push_back(SColorName(std::string("DarkGreen"), std::string("006400")));
    g_colorNames.push_back(SColorName(std::string("DarkKhaki"), std::string("BDB76B")));
    g_colorNames.push_back(SColorName(std::string("DarkMagenta"), std::string("8B008B")));
    g_colorNames.push_back(SColorName(std::string("DarkOliveGreen"), std::string("556B2F")));
    g_colorNames.push_back(SColorName(std::string("DarkOrange"), std::string("FF8C00")));
    g_colorNames.push_back(SColorName(std::string("DarkOrchid"), std::string("9932CC")));
    g_colorNames.push_back(SColorName(std::string("DarkRed"), std::string("8B0000")));
    g_colorNames.push_back(SColorName(std::string("DarkSalmon"), std::string("E9967A")));
    g_colorNames.push_back(SColorName(std::string("DarkSeaGreen"), std::string("8FBC8F")));
    g_colorNames.push_back(SColorName(std::string("DarkSlateBlue"), std::string("483D8B")));
    g_colorNames.push_back(SColorName(std::string("DarkSlateGray"), std::string("2F4F4F")));
    g_colorNames.push_back(SColorName(std::string("DarkTurquoise"), std::string("00CED1")));
    g_colorNames.push_back(SColorName(std::string("DarkViolet"), std::string("9400D3")));
    g_colorNames.push_back(SColorName(std::string("DeepPink"), std::string("FF1493")));
    g_colorNames.push_back(SColorName(std::string("DeepSkyBlue"), std::string("00BFFF")));
    g_colorNames.push_back(SColorName(std::string("DimGray"), std::string("696969")));
    g_colorNames.push_back(SColorName(std::string("DodgerBlue"), std::string("1E90FF")));
    g_colorNames.push_back(SColorName(std::string("FireBrick"), std::string("B22222")));
    g_colorNames.push_back(SColorName(std::string("FloralWhite"), std::string("FFFAF0")));
    g_colorNames.push_back(SColorName(std::string("ForestGreen"), std::string("228B22")));
    g_colorNames.push_back(SColorName(std::string("Fuchsia"), std::string("FF00FF")));
    g_colorNames.push_back(SColorName(std::string("Gainsboro"), std::string("DCDCDC")));
    g_colorNames.push_back(SColorName(std::string("GhostWhite"), std::string("F8F8FF")));
    g_colorNames.push_back(SColorName(std::string("Gold"), std::string("FFD700")));
    g_colorNames.push_back(SColorName(std::string("GoldenRod"), std::string("DAA520")));
    g_colorNames.push_back(SColorName(std::string("Gray"), std::string("808080")));
    g_colorNames.push_back(SColorName(std::string("Green"), std::string("008000")));
    g_colorNames.push_back(SColorName(std::string("GreenYellow"), std::string("ADFF2F")));
    g_colorNames.push_back(SColorName(std::string("HoneyDew"), std::string("F0FFF0")));
    g_colorNames.push_back(SColorName(std::string("HotPink"), std::string("FF69B4")));
    g_colorNames.push_back(SColorName(std::string("IndianRed"), std::string("CD5C5C")));
    g_colorNames.push_back(SColorName(std::string("Indigo"), std::string("4B0082")));
    g_colorNames.push_back(SColorName(std::string("Ivory"), std::string("FFFFF0")));
    g_colorNames.push_back(SColorName(std::string("Khaki"), std::string("F0E68C")));
    g_colorNames.push_back(SColorName(std::string("Lavender"), std::string("E6E6FA")));
    g_colorNames.push_back(SColorName(std::string("LavenderBlush"), std::string("FFF0F5")));
    g_colorNames.push_back(SColorName(std::string("LawnGreen"), std::string("7CFC00")));
    g_colorNames.push_back(SColorName(std::string("LemonChiffon"), std::string("FFFACD")));
    g_colorNames.push_back(SColorName(std::string("LightBlue"), std::string("ADD8E6")));
    g_colorNames.push_back(SColorName(std::string("LightCoral"), std::string("F08080")));
    g_colorNames.push_back(SColorName(std::string("LightCyan"), std::string("E0FFFF")));
    g_colorNames.push_back(SColorName(std::string("LightGoldenRodYellow"), std::string("FAFAD2")));
    g_colorNames.push_back(SColorName(std::string("LightGray"), std::string("D3D3D3")));
    g_colorNames.push_back(SColorName(std::string("LightGreen"), std::string("90EE90")));
    g_colorNames.push_back(SColorName(std::string("LightPink"), std::string("FFB6C1")));
    g_colorNames.push_back(SColorName(std::string("LightSalmon"), std::string("FFA07A")));
    g_colorNames.push_back(SColorName(std::string("LightSeaGreen"), std::string("20B2AA")));
    g_colorNames.push_back(SColorName(std::string("LightSkyBlue"), std::string("87CEFA")));
    g_colorNames.push_back(SColorName(std::string("LightSlateGray"), std::string("778899")));
    g_colorNames.push_back(SColorName(std::string("LightSteelBlue"), std::string("B0C4DE")));
    g_colorNames.push_back(SColorName(std::string("LightYellow"), std::string("FFFFE0")));
    g_colorNames.push_back(SColorName(std::string("Lime"), std::string("00FF00")));
    g_colorNames.push_back(SColorName(std::string("LimeGreen"), std::string("32CD32")));
    g_colorNames.push_back(SColorName(std::string("Linen"), std::string("FAF0E6")));
    g_colorNames.push_back(SColorName(std::string("Magenta"), std::string("FF00FF")));
    g_colorNames.push_back(SColorName(std::string("Maroon"), std::string("800000")));
    g_colorNames.push_back(SColorName(std::string("MediumAquaMarine"), std::string("66CDAA")));
    g_colorNames.push_back(SColorName(std::string("MediumBlue"), std::string("0000CD")));
    g_colorNames.push_back(SColorName(std::string("MediumOrchid"), std::string("BA55D3")));
    g_colorNames.push_back(SColorName(std::string("MediumPurple"), std::string("9370DB")));
    g_colorNames.push_back(SColorName(std::string("MediumSeaGreen"), std::string("3CB371")));
    g_colorNames.push_back(SColorName(std::string("MediumSlateBlue"), std::string("7B68EE")));
    g_colorNames.push_back(SColorName(std::string("MediumSpringGreen"), std::string("00FA9A")));
    g_colorNames.push_back(SColorName(std::string("MediumTurquoise"), std::string("48D1CC")));
    g_colorNames.push_back(SColorName(std::string("MediumVioletRed"), std::string("C71585")));
    g_colorNames.push_back(SColorName(std::string("MidnightBlue"), std::string("191970")));
    g_colorNames.push_back(SColorName(std::string("MintCream"), std::string("F5FFFA")));
    g_colorNames.push_back(SColorName(std::string("MistyRose"), std::string("FFE4E1")));
    g_colorNames.push_back(SColorName(std::string("Moccasin"), std::string("FFE4B5")));
    g_colorNames.push_back(SColorName(std::string("NavajoWhite"), std::string("FFDEAD")));
    g_colorNames.push_back(SColorName(std::string("Navy"), std::string("000080")));
    g_colorNames.push_back(SColorName(std::string("OldLace"), std::string("FDF5E6")));
    g_colorNames.push_back(SColorName(std::string("Olive"), std::string("808000")));
    g_colorNames.push_back(SColorName(std::string("OliveDrab"), std::string("6B8E23")));
    g_colorNames.push_back(SColorName(std::string("Orange"), std::string("FFA500")));
    g_colorNames.push_back(SColorName(std::string("OrangeRed"), std::string("FF4500")));
    g_colorNames.push_back(SColorName(std::string("Orchid"), std::string("DA70D6")));
    g_colorNames.push_back(SColorName(std::string("PaleGoldenRod"), std::string("EEE8AA")));
    g_colorNames.push_back(SColorName(std::string("PaleGreen"), std::string("98FB98")));
    g_colorNames.push_back(SColorName(std::string("PaleTurquoise"), std::string("AFEEEE")));
    g_colorNames.push_back(SColorName(std::string("PaleVioletRed"), std::string("DB7093")));
    g_colorNames.push_back(SColorName(std::string("PapayaWhip"), std::string("FFEFD5")));
    g_colorNames.push_back(SColorName(std::string("PeachPuff"), std::string("FFDAB9")));
    g_colorNames.push_back(SColorName(std::string("Peru"), std::string("CD853F")));
    g_colorNames.push_back(SColorName(std::string("Pink"), std::string("FFC0CB")));
    g_colorNames.push_back(SColorName(std::string("Plum"), std::string("DDA0DD")));
    g_colorNames.push_back(SColorName(std::string("PowderBlue"), std::string("B0E0E6")));
    g_colorNames.push_back(SColorName(std::string("Purple"), std::string("800080")));
    g_colorNames.push_back(SColorName(std::string("RebeccaPurple"), std::string("663399")));
    g_colorNames.push_back(SColorName(std::string("Red"), std::string("FF0000")));
    g_colorNames.push_back(SColorName(std::string("RosyBrown"), std::string("BC8F8F")));
    g_colorNames.push_back(SColorName(std::string("RoyalBlue"), std::string("4169E1")));
    g_colorNames.push_back(SColorName(std::string("SaddleBrown"), std::string("8B4513")));
    g_colorNames.push_back(SColorName(std::string("Salmon"), std::string("FA8072")));
    g_colorNames.push_back(SColorName(std::string("SandyBrown"), std::string("F4A460")));
    g_colorNames.push_back(SColorName(std::string("SeaGreen"), std::string("2E8B57")));
    g_colorNames.push_back(SColorName(std::string("SeaShell"), std::string("FFF5EE")));
    g_colorNames.push_back(SColorName(std::string("Sienna"), std::string("A0522D")));
    g_colorNames.push_back(SColorName(std::string("Silver"), std::string("C0C0C0")));
    g_colorNames.push_back(SColorName(std::string("SkyBlue"), std::string("87CEEB")));
    g_colorNames.push_back(SColorName(std::string("SlateBlue"), std::string("6A5ACD")));
    g_colorNames.push_back(SColorName(std::string("SlateGray"), std::string("708090")));
    g_colorNames.push_back(SColorName(std::string("Snow"), std::string("FFFAFA")));
    g_colorNames.push_back(SColorName(std::string("SpringGreen"), std::string("00FF7F")));
    g_colorNames.push_back(SColorName(std::string("SteelBlue"), std::string("4682B4")));
    g_colorNames.push_back(SColorName(std::string("Tan"), std::string("D2B48C")));
    g_colorNames.push_back(SColorName(std::string("Teal"), std::string("008080")));
    g_colorNames.push_back(SColorName(std::string("Thistle"), std::string("D8BFD8")));
    g_colorNames.push_back(SColorName(std::string("Tomato"), std::string("FF6347")));
    g_colorNames.push_back(SColorName(std::string("Turquoise"), std::string("40E0D0")));
    g_colorNames.push_back(SColorName(std::string("Violet"), std::string("EE82EE")));
    g_colorNames.push_back(SColorName(std::string("Wheat"), std::string("F5DEB3")));
    g_colorNames.push_back(SColorName(std::string("White"), std::string("FFFFFF")));
    g_colorNames.push_back(SColorName(std::string("WhiteSmoke"), std::string("F5F5F5")));
    g_colorNames.push_back(SColorName(std::string("Yellow"), std::string("FFFF00")));
    g_colorNames.push_back(SColorName(std::string("YellowGreen"), std::string("9ACD32")));
}
//------------------------------------------------------------------------------

fgBool colors::isInit(void) {
    return colors::s_isInit;
}
//------------------------------------------------------------------------------

void colors::freeColors() {
    g_colorNames.clear_optimised();
    g_colorNames.resize(0);
    g_colorNames.reserve(0);
    colors::s_isInit = FG_FALSE;
}
//------------------------------------------------------------------------------

fgColor4f colors::getColor(const char *name) {
    return getColor(std::string(name));
}
//------------------------------------------------------------------------------

fgColor4f colors::getColor(const std::string& name) {
    if(!colors::s_isInit)
        return fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    if(name.empty())
        return fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    int n = NUM_COLORS;

    std::string colorName = strings::trim(name, std::string(" \t\n\r."));

    for(int i = 0; i < n; i++) {
        if(strings::isEqual(g_colorNames[i].name, colorName, FG_FALSE)) {
            return g_colorNames[i].color;
        }
    }
    return fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
//------------------------------------------------------------------------------

fgColor4f colors::parseHEX(const char *value) {
    return parseHEX(std::string(value));
}
//------------------------------------------------------------------------------

fgColor4f colors::parseHEX(const std::string& value) {
    std::string hexStr = strings::trim(value, std::string(" \t\n\r;#x"));
    if(strings::startsWith(hexStr, std::string("0x"), FG_FALSE)) {
        hexStr = hexStr.substr(2);
    }
    unsigned char comp;
    if(hexStr.length() == 8) {
        comp = 4;
    } else if(hexStr.length() == 6) {
        comp = 3;
    } else {
        return fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
    char *p;
    unsigned long hexNum = strtoul(hexStr.c_str(), &p, 16);
    if(*p != 0) {
        return fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        return colors::parseHEX(hexNum, comp);
    }
}
//------------------------------------------------------------------------------

fgColor4f colors::parseHEX(unsigned long int value, const unsigned char comp) {
    fgColor4f color;
    color.b = (float)(value & 0xFF) / 255.0f;
    value >>= 8;
    color.g = (float)(value & 0xFF) / 255.0f;
    value >>= 8;
    color.r = (float)(value & 0xFF) / 255.0f;
    if(comp > 3) {
        value >>= 8;
        color.a = (float)(value & 0xFF) / 255.0f;
    } else {
        color.a = 1.0f;
    }
    return color;
}
//------------------------------------------------------------------------------
