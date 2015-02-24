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

#include "fgColors.h"
#include "fgBool.h"
#include "Util/fgStrings.h"


namespace fg {
    namespace colors {
        ///
        const unsigned int NUM_COLORS = 140;
        ///
        static fgBool s_isInit = FG_FALSE;

    };
};

struct ColorName
{
    ///
    fgColor4f color;
    ///
    std::string name;

    ColorName() { }

    /**
     * 
     * @param _color
     * @param _name
     */
    ColorName(const std::string& _name,
              const fgColor4f& _color) :
    color(_color),
    name(_name) { }

    /**
     * 
     * @param _name
     * @param _hexColor
     * @param _comp
     */
    ColorName(const std::string& _name,
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
    ColorName(const std::string& _name, const std::string& _hexStr) :
    name(_name) {
        color = fg::colors::parseHEX(_hexStr);
    }
};

/// Special array containing 140 standard colors and human readable names
fg::CVector<ColorName> g_colorNames;

#if 0
static const ColorName s_colorNames[140]; // = { 
ColorName(std::string("AliceBlue"), std::string("F0F8FF")),
ColorName(std::string("AntiqueWhite"), std::string("FAEBD7")),
ColorName(std::string("Aqua"), std::string("00FFFF")),
ColorName(std::string("Aquamarine"), std::string("7FFFD4")),
ColorName(std::string("Azure"), std::string("F0FFFF")),
ColorName(std::string("Beige"), std::string("F5F5DC")),
ColorName(std::string("Bisque"), std::string("FFE4C4")),
ColorName(std::string("Black"), std::string("000000")),
ColorName(std::string("BlanchedAlmond"), std::string("FFEBCD")),
ColorName(std::string("Blue"), std::string("0000FF")),
ColorName(std::string("BlueViolet"), std::string("8A2BE2")),
ColorName(std::string("Brown"), std::string("A52A2A")),
ColorName(std::string("BurlyWood"), std::string("DEB887")),
ColorName(std::string("CadetBlue"), std::string("5F9EA0")),
ColorName(std::string("Chartreuse"), std::string("7FFF00")),
ColorName(std::string("Chocolate"), std::string("D2691E")),
ColorName(std::string("Coral"), std::string("FF7F50")),
ColorName(std::string("CornflowerBlue"), std::string("6495ED")),
ColorName(std::string("Cornsilk"), std::string("FFF8DC")),
ColorName(std::string("Crimson"), std::string("DC143C")),
ColorName(std::string("Cyan"), std::string("00FFFF")),
ColorName(std::string("DarkBlue"), std::string("00008B")),
ColorName(std::string("DarkCyan"), std::string("008B8B")),
ColorName(std::string("DarkGoldenRod"), std::string("B8860B")),
ColorName(std::string("DarkGray"), std::string("A9A9A9")),
ColorName(std::string("DarkGreen"), std::string("006400")),
ColorName(std::string("DarkKhaki"), std::string("BDB76B")),
ColorName(std::string("DarkMagenta"), std::string("8B008B")),
ColorName(std::string("DarkOliveGreen"), std::string("556B2F")),
ColorName(std::string("DarkOrange"), std::string("FF8C00")),
ColorName(std::string("DarkOrchid"), std::string("9932CC")),
ColorName(std::string("DarkRed"), std::string("8B0000")),
ColorName(std::string("DarkSalmon"), std::string("E9967A")),
ColorName(std::string("DarkSeaGreen"), std::string("8FBC8F")),
ColorName(std::string("DarkSlateBlue"), std::string("483D8B")),
ColorName(std::string("DarkSlateGray"), std::string("2F4F4F")),
ColorName(std::string("DarkTurquoise"), std::string("00CED1")),
ColorName(std::string("DarkViolet"), std::string("9400D3")),
ColorName(std::string("DeepPink"), std::string("FF1493")),
ColorName(std::string("DeepSkyBlue"), std::string("00BFFF")),
ColorName(std::string("DimGray"), std::string("696969")),
ColorName(std::string("DodgerBlue"), std::string("1E90FF")),
ColorName(std::string("FireBrick"), std::string("B22222")),
ColorName(std::string("FloralWhite"), std::string("FFFAF0")),
ColorName(std::string("ForestGreen"), std::string("228B22")),
ColorName(std::string("Fuchsia"), std::string("FF00FF")),
ColorName(std::string("Gainsboro"), std::string("DCDCDC")),
ColorName(std::string("GhostWhite"), std::string("F8F8FF")),
ColorName(std::string("Gold"), std::string("FFD700")),
ColorName(std::string("GoldenRod"), std::string("DAA520")),
ColorName(std::string("Gray"), std::string("808080")),
ColorName(std::string("Green"), std::string("008000")),
ColorName(std::string("GreenYellow"), std::string("ADFF2F")),
ColorName(std::string("HoneyDew"), std::string("F0FFF0")),
ColorName(std::string("HotPink"), std::string("FF69B4")),
ColorName(std::string("IndianRed"), std::string("CD5C5C")),
ColorName(std::string("Indigo"), std::string("4B0082")),
ColorName(std::string("Ivory"), std::string("FFFFF0")),
ColorName(std::string("Khaki"), std::string("F0E68C")),
ColorName(std::string("Lavender"), std::string("E6E6FA")),
ColorName(std::string("LavenderBlush"), std::string("FFF0F5")),
ColorName(std::string("LawnGreen"), std::string("7CFC00")),
ColorName(std::string("LemonChiffon"), std::string("FFFACD")),
ColorName(std::string("LightBlue"), std::string("ADD8E6")),
ColorName(std::string("LightCoral"), std::string("F08080")),
ColorName(std::string("LightCyan"), std::string("E0FFFF")),
ColorName(std::string("LightGoldenRodYellow"), std::string("FAFAD2")),
ColorName(std::string("LightGray"), std::string("D3D3D3")),
ColorName(std::string("LightGreen"), std::string("90EE90")),
ColorName(std::string("LightPink"), std::string("FFB6C1")),
ColorName(std::string("LightSalmon"), std::string("FFA07A")),
ColorName(std::string("LightSeaGreen"), std::string("20B2AA")),
ColorName(std::string("LightSkyBlue"), std::string("87CEFA")),
ColorName(std::string("LightSlateGray"), std::string("778899")),
ColorName(std::string("LightSteelBlue"), std::string("B0C4DE")),
ColorName(std::string("LightYellow"), std::string("FFFFE0")),
ColorName(std::string("Lime"), std::string("00FF00")),
ColorName(std::string("LimeGreen"), std::string("32CD32")),
ColorName(std::string("Linen"), std::string("FAF0E6")),
ColorName(std::string("Magenta"), std::string("FF00FF")),
ColorName(std::string("Maroon"), std::string("800000")),
ColorName(std::string("MediumAquaMarine"), std::string("66CDAA")),
ColorName(std::string("MediumBlue"), std::string("0000CD")),
ColorName(std::string("MediumOrchid"), std::string("BA55D3")),
ColorName(std::string("MediumPurple"), std::string("9370DB")),
ColorName(std::string("MediumSeaGreen"), std::string("3CB371")),
ColorName(std::string("MediumSlateBlue"), std::string("7B68EE")),
ColorName(std::string("MediumSpringGreen"), std::string("00FA9A")),
ColorName(std::string("MediumTurquoise"), std::string("48D1CC")),
ColorName(std::string("MediumVioletRed"), std::string("C71585")),
ColorName(std::string("MidnightBlue"), std::string("191970")),
ColorName(std::string("MintCream"), std::string("F5FFFA")),
ColorName(std::string("MistyRose"), std::string("FFE4E1")),
ColorName(std::string("Moccasin"), std::string("FFE4B5")),
ColorName(std::string("NavajoWhite"), std::string("FFDEAD")),
ColorName(std::string("Navy"), std::string("000080")),
ColorName(std::string("OldLace"), std::string("FDF5E6")),
ColorName(std::string("Olive"), std::string("808000")),
ColorName(std::string("OliveDrab"), std::string("6B8E23")),
ColorName(std::string("Orange"), std::string("FFA500")),
ColorName(std::string("OrangeRed"), std::string("FF4500")),
ColorName(std::string("Orchid"), std::string("DA70D6")),
ColorName(std::string("PaleGoldenRod"), std::string("EEE8AA")),
ColorName(std::string("PaleGreen"), std::string("98FB98")),
ColorName(std::string("PaleTurquoise"), std::string("AFEEEE")),
ColorName(std::string("PaleVioletRed"), std::string("DB7093")),
ColorName(std::string("PapayaWhip"), std::string("FFEFD5")),
ColorName(std::string("PeachPuff"), std::string("FFDAB9")),
ColorName(std::string("Peru"), std::string("CD853F")),
ColorName(std::string("Pink"), std::string("FFC0CB")),
ColorName(std::string("Plum"), std::string("DDA0DD")),
ColorName(std::string("PowderBlue"), std::string("B0E0E6")),
ColorName(std::string("Purple"), std::string("800080")),
ColorName(std::string("Red"), std::string("FF0000")),
ColorName(std::string("RosyBrown"), std::string("BC8F8F")),
ColorName(std::string("RoyalBlue"), std::string("4169E1")),
ColorName(std::string("SaddleBrown"), std::string("8B4513")),
ColorName(std::string("Salmon"), std::string("FA8072")),
ColorName(std::string("SandyBrown"), std::string("F4A460")),
ColorName(std::string("SeaGreen"), std::string("2E8B57")),
ColorName(std::string("SeaShell"), std::string("FFF5EE")),
ColorName(std::string("Sienna"), std::string("A0522D")),
ColorName(std::string("Silver"), std::string("C0C0C0")),
ColorName(std::string("SkyBlue"), std::string("87CEEB")),
ColorName(std::string("SlateBlue"), std::string("6A5ACD")),
ColorName(std::string("SlateGray"), std::string("708090")),
ColorName(std::string("Snow"), std::string("FFFAFA")),
ColorName(std::string("SpringGreen"), std::string("00FF7F")),
ColorName(std::string("SteelBlue"), std::string("4682B4")),
ColorName(std::string("Tan"), std::string("D2B48C")),
ColorName(std::string("Teal"), std::string("008080")),
ColorName(std::string("Thistle"), std::string("D8BFD8")),
ColorName(std::string("Tomato"), std::string("FF6347")),
ColorName(std::string("Turquoise"), std::string("40E0D0")),
ColorName(std::string("Violet"), std::string("EE82EE")),
ColorName(std::string("Wheat"), std::string("F5DEB3")),
ColorName(std::string("White"), std::string("FFFFFF")),
ColorName(std::string("WhiteSmoke"), std::string("F5F5F5")),
ColorName(std::string("Yellow"), std::string("FFFF00")),
ColorName(std::string("YellowGreen"), std::string("9ACD32"))
};
#endif

using namespace fg;

/**
 * 
 */
void colors::initialize(void) {
    if(colors::s_isInit)
        return;

    colors::s_isInit = FG_TRUE;

    g_colorNames.clear_optimised();
    g_colorNames.reserve(NUM_COLORS);

    g_colorNames.push_back(ColorName(std::string("AliceBlue"), std::string("F0F8FF")));
    g_colorNames.push_back(ColorName(std::string("AntiqueWhite"), std::string("FAEBD7")));
    g_colorNames.push_back(ColorName(std::string("Aqua"), std::string("00FFFF")));
    g_colorNames.push_back(ColorName(std::string("Aquamarine"), std::string("7FFFD4")));
    g_colorNames.push_back(ColorName(std::string("Azure"), std::string("F0FFFF")));
    g_colorNames.push_back(ColorName(std::string("Beige"), std::string("F5F5DC")));
    g_colorNames.push_back(ColorName(std::string("Bisque"), std::string("FFE4C4")));
    g_colorNames.push_back(ColorName(std::string("Black"), std::string("000000")));
    g_colorNames.push_back(ColorName(std::string("BlanchedAlmond"), std::string("FFEBCD")));
    g_colorNames.push_back(ColorName(std::string("Blue"), std::string("0000FF")));
    g_colorNames.push_back(ColorName(std::string("BlueViolet"), std::string("8A2BE2")));
    g_colorNames.push_back(ColorName(std::string("Brown"), std::string("A52A2A")));
    g_colorNames.push_back(ColorName(std::string("BurlyWood"), std::string("DEB887")));
    g_colorNames.push_back(ColorName(std::string("CadetBlue"), std::string("5F9EA0")));
    g_colorNames.push_back(ColorName(std::string("Chartreuse"), std::string("7FFF00")));
    g_colorNames.push_back(ColorName(std::string("Chocolate"), std::string("D2691E")));
    g_colorNames.push_back(ColorName(std::string("Coral"), std::string("FF7F50")));
    g_colorNames.push_back(ColorName(std::string("CornflowerBlue"), std::string("6495ED")));
    g_colorNames.push_back(ColorName(std::string("Cornsilk"), std::string("FFF8DC")));
    g_colorNames.push_back(ColorName(std::string("Crimson"), std::string("DC143C")));
    g_colorNames.push_back(ColorName(std::string("Cyan"), std::string("00FFFF")));
    g_colorNames.push_back(ColorName(std::string("DarkBlue"), std::string("00008B")));
    g_colorNames.push_back(ColorName(std::string("DarkCyan"), std::string("008B8B")));
    g_colorNames.push_back(ColorName(std::string("DarkGoldenRod"), std::string("B8860B")));
    g_colorNames.push_back(ColorName(std::string("DarkGray"), std::string("A9A9A9")));
    g_colorNames.push_back(ColorName(std::string("DarkGreen"), std::string("006400")));
    g_colorNames.push_back(ColorName(std::string("DarkKhaki"), std::string("BDB76B")));
    g_colorNames.push_back(ColorName(std::string("DarkMagenta"), std::string("8B008B")));
    g_colorNames.push_back(ColorName(std::string("DarkOliveGreen"), std::string("556B2F")));
    g_colorNames.push_back(ColorName(std::string("DarkOrange"), std::string("FF8C00")));
    g_colorNames.push_back(ColorName(std::string("DarkOrchid"), std::string("9932CC")));
    g_colorNames.push_back(ColorName(std::string("DarkRed"), std::string("8B0000")));
    g_colorNames.push_back(ColorName(std::string("DarkSalmon"), std::string("E9967A")));
    g_colorNames.push_back(ColorName(std::string("DarkSeaGreen"), std::string("8FBC8F")));
    g_colorNames.push_back(ColorName(std::string("DarkSlateBlue"), std::string("483D8B")));
    g_colorNames.push_back(ColorName(std::string("DarkSlateGray"), std::string("2F4F4F")));
    g_colorNames.push_back(ColorName(std::string("DarkTurquoise"), std::string("00CED1")));
    g_colorNames.push_back(ColorName(std::string("DarkViolet"), std::string("9400D3")));
    g_colorNames.push_back(ColorName(std::string("DeepPink"), std::string("FF1493")));
    g_colorNames.push_back(ColorName(std::string("DeepSkyBlue"), std::string("00BFFF")));
    g_colorNames.push_back(ColorName(std::string("DimGray"), std::string("696969")));
    g_colorNames.push_back(ColorName(std::string("DodgerBlue"), std::string("1E90FF")));
    g_colorNames.push_back(ColorName(std::string("FireBrick"), std::string("B22222")));
    g_colorNames.push_back(ColorName(std::string("FloralWhite"), std::string("FFFAF0")));
    g_colorNames.push_back(ColorName(std::string("ForestGreen"), std::string("228B22")));
    g_colorNames.push_back(ColorName(std::string("Fuchsia"), std::string("FF00FF")));
    g_colorNames.push_back(ColorName(std::string("Gainsboro"), std::string("DCDCDC")));
    g_colorNames.push_back(ColorName(std::string("GhostWhite"), std::string("F8F8FF")));
    g_colorNames.push_back(ColorName(std::string("Gold"), std::string("FFD700")));
    g_colorNames.push_back(ColorName(std::string("GoldenRod"), std::string("DAA520")));
    g_colorNames.push_back(ColorName(std::string("Gray"), std::string("808080")));
    g_colorNames.push_back(ColorName(std::string("Green"), std::string("008000")));
    g_colorNames.push_back(ColorName(std::string("GreenYellow"), std::string("ADFF2F")));
    g_colorNames.push_back(ColorName(std::string("HoneyDew"), std::string("F0FFF0")));
    g_colorNames.push_back(ColorName(std::string("HotPink"), std::string("FF69B4")));
    g_colorNames.push_back(ColorName(std::string("IndianRed"), std::string("CD5C5C")));
    g_colorNames.push_back(ColorName(std::string("Indigo"), std::string("4B0082")));
    g_colorNames.push_back(ColorName(std::string("Ivory"), std::string("FFFFF0")));
    g_colorNames.push_back(ColorName(std::string("Khaki"), std::string("F0E68C")));
    g_colorNames.push_back(ColorName(std::string("Lavender"), std::string("E6E6FA")));
    g_colorNames.push_back(ColorName(std::string("LavenderBlush"), std::string("FFF0F5")));
    g_colorNames.push_back(ColorName(std::string("LawnGreen"), std::string("7CFC00")));
    g_colorNames.push_back(ColorName(std::string("LemonChiffon"), std::string("FFFACD")));
    g_colorNames.push_back(ColorName(std::string("LightBlue"), std::string("ADD8E6")));
    g_colorNames.push_back(ColorName(std::string("LightCoral"), std::string("F08080")));
    g_colorNames.push_back(ColorName(std::string("LightCyan"), std::string("E0FFFF")));
    g_colorNames.push_back(ColorName(std::string("LightGoldenRodYellow"), std::string("FAFAD2")));
    g_colorNames.push_back(ColorName(std::string("LightGray"), std::string("D3D3D3")));
    g_colorNames.push_back(ColorName(std::string("LightGreen"), std::string("90EE90")));
    g_colorNames.push_back(ColorName(std::string("LightPink"), std::string("FFB6C1")));
    g_colorNames.push_back(ColorName(std::string("LightSalmon"), std::string("FFA07A")));
    g_colorNames.push_back(ColorName(std::string("LightSeaGreen"), std::string("20B2AA")));
    g_colorNames.push_back(ColorName(std::string("LightSkyBlue"), std::string("87CEFA")));
    g_colorNames.push_back(ColorName(std::string("LightSlateGray"), std::string("778899")));
    g_colorNames.push_back(ColorName(std::string("LightSteelBlue"), std::string("B0C4DE")));
    g_colorNames.push_back(ColorName(std::string("LightYellow"), std::string("FFFFE0")));
    g_colorNames.push_back(ColorName(std::string("Lime"), std::string("00FF00")));
    g_colorNames.push_back(ColorName(std::string("LimeGreen"), std::string("32CD32")));
    g_colorNames.push_back(ColorName(std::string("Linen"), std::string("FAF0E6")));
    g_colorNames.push_back(ColorName(std::string("Magenta"), std::string("FF00FF")));
    g_colorNames.push_back(ColorName(std::string("Maroon"), std::string("800000")));
    g_colorNames.push_back(ColorName(std::string("MediumAquaMarine"), std::string("66CDAA")));
    g_colorNames.push_back(ColorName(std::string("MediumBlue"), std::string("0000CD")));
    g_colorNames.push_back(ColorName(std::string("MediumOrchid"), std::string("BA55D3")));
    g_colorNames.push_back(ColorName(std::string("MediumPurple"), std::string("9370DB")));
    g_colorNames.push_back(ColorName(std::string("MediumSeaGreen"), std::string("3CB371")));
    g_colorNames.push_back(ColorName(std::string("MediumSlateBlue"), std::string("7B68EE")));
    g_colorNames.push_back(ColorName(std::string("MediumSpringGreen"), std::string("00FA9A")));
    g_colorNames.push_back(ColorName(std::string("MediumTurquoise"), std::string("48D1CC")));
    g_colorNames.push_back(ColorName(std::string("MediumVioletRed"), std::string("C71585")));
    g_colorNames.push_back(ColorName(std::string("MidnightBlue"), std::string("191970")));
    g_colorNames.push_back(ColorName(std::string("MintCream"), std::string("F5FFFA")));
    g_colorNames.push_back(ColorName(std::string("MistyRose"), std::string("FFE4E1")));
    g_colorNames.push_back(ColorName(std::string("Moccasin"), std::string("FFE4B5")));
    g_colorNames.push_back(ColorName(std::string("NavajoWhite"), std::string("FFDEAD")));
    g_colorNames.push_back(ColorName(std::string("Navy"), std::string("000080")));
    g_colorNames.push_back(ColorName(std::string("OldLace"), std::string("FDF5E6")));
    g_colorNames.push_back(ColorName(std::string("Olive"), std::string("808000")));
    g_colorNames.push_back(ColorName(std::string("OliveDrab"), std::string("6B8E23")));
    g_colorNames.push_back(ColorName(std::string("Orange"), std::string("FFA500")));
    g_colorNames.push_back(ColorName(std::string("OrangeRed"), std::string("FF4500")));
    g_colorNames.push_back(ColorName(std::string("Orchid"), std::string("DA70D6")));
    g_colorNames.push_back(ColorName(std::string("PaleGoldenRod"), std::string("EEE8AA")));
    g_colorNames.push_back(ColorName(std::string("PaleGreen"), std::string("98FB98")));
    g_colorNames.push_back(ColorName(std::string("PaleTurquoise"), std::string("AFEEEE")));
    g_colorNames.push_back(ColorName(std::string("PaleVioletRed"), std::string("DB7093")));
    g_colorNames.push_back(ColorName(std::string("PapayaWhip"), std::string("FFEFD5")));
    g_colorNames.push_back(ColorName(std::string("PeachPuff"), std::string("FFDAB9")));
    g_colorNames.push_back(ColorName(std::string("Peru"), std::string("CD853F")));
    g_colorNames.push_back(ColorName(std::string("Pink"), std::string("FFC0CB")));
    g_colorNames.push_back(ColorName(std::string("Plum"), std::string("DDA0DD")));
    g_colorNames.push_back(ColorName(std::string("PowderBlue"), std::string("B0E0E6")));
    g_colorNames.push_back(ColorName(std::string("Purple"), std::string("800080")));
    g_colorNames.push_back(ColorName(std::string("Red"), std::string("FF0000")));
    g_colorNames.push_back(ColorName(std::string("RosyBrown"), std::string("BC8F8F")));
    g_colorNames.push_back(ColorName(std::string("RoyalBlue"), std::string("4169E1")));
    g_colorNames.push_back(ColorName(std::string("SaddleBrown"), std::string("8B4513")));
    g_colorNames.push_back(ColorName(std::string("Salmon"), std::string("FA8072")));
    g_colorNames.push_back(ColorName(std::string("SandyBrown"), std::string("F4A460")));
    g_colorNames.push_back(ColorName(std::string("SeaGreen"), std::string("2E8B57")));
    g_colorNames.push_back(ColorName(std::string("SeaShell"), std::string("FFF5EE")));
    g_colorNames.push_back(ColorName(std::string("Sienna"), std::string("A0522D")));
    g_colorNames.push_back(ColorName(std::string("Silver"), std::string("C0C0C0")));
    g_colorNames.push_back(ColorName(std::string("SkyBlue"), std::string("87CEEB")));
    g_colorNames.push_back(ColorName(std::string("SlateBlue"), std::string("6A5ACD")));
    g_colorNames.push_back(ColorName(std::string("SlateGray"), std::string("708090")));
    g_colorNames.push_back(ColorName(std::string("Snow"), std::string("FFFAFA")));
    g_colorNames.push_back(ColorName(std::string("SpringGreen"), std::string("00FF7F")));
    g_colorNames.push_back(ColorName(std::string("SteelBlue"), std::string("4682B4")));
    g_colorNames.push_back(ColorName(std::string("Tan"), std::string("D2B48C")));
    g_colorNames.push_back(ColorName(std::string("Teal"), std::string("008080")));
    g_colorNames.push_back(ColorName(std::string("Thistle"), std::string("D8BFD8")));
    g_colorNames.push_back(ColorName(std::string("Tomato"), std::string("FF6347")));
    g_colorNames.push_back(ColorName(std::string("Turquoise"), std::string("40E0D0")));
    g_colorNames.push_back(ColorName(std::string("Violet"), std::string("EE82EE")));
    g_colorNames.push_back(ColorName(std::string("Wheat"), std::string("F5DEB3")));
    g_colorNames.push_back(ColorName(std::string("White"), std::string("FFFFFF")));
    g_colorNames.push_back(ColorName(std::string("WhiteSmoke"), std::string("F5F5F5")));
    g_colorNames.push_back(ColorName(std::string("Yellow"), std::string("FFFF00")));
    g_colorNames.push_back(ColorName(std::string("YellowGreen"), std::string("9ACD32")));
}

/**
 * 
 * @return 
 */
fgBool colors::isInit(void) {
    return colors::s_isInit;
}

/**
 * 
 */
void colors::freeColors() {
    g_colorNames.clear_optimised();
    g_colorNames.resize(0);
    g_colorNames.reserve(0);
    colors::s_isInit = FG_FALSE;
}

/**
 * 
 * @param name
 * @return 
 */
fgColor4f colors::getColor(const char *name) {
    return getColor(std::string(name));
}

/**
 * 
 * @param name
 * @return 
 */
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

/**
 * 
 * @param value
 * @return 
 */
fgColor4f colors::parseHEX(const char *value) {
    return parseHEX(std::string(value));
}

/**
 * 
 * @param value
 * @return 
 */
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

/**
 * 
 * @param value
 * @param comp
 * @return 
 */
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
