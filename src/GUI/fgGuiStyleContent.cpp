/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyleContent.h"
#include "Util/fgStrings.h"
#include "fgColors.h"

using namespace fg;

/**
 *
 */
gui::CStyleContent::CStyleContent() { }

/**
 *
 */
gui::CStyleContent::~CStyleContent() { }

/**
 * 
 * @param align
 * @param pos
 * @param size
 * @param boundSize
 */
void gui::CStyleContent::applyPosAlign(const Align align,
                                       Vector3f& pos,
                                       const Vector3f& size,
                                       const Vector3f& boundPos,
                                       const Vector3f& boundSize,
                                       const fgBool isInside) {
    // Margin is outside of the border
    // Padding is inside of the border

    SMargin *offset = NULL;
    if(isInside) {
        offset = (SMargin *) & m_padding;
    } else {
        offset = (SMargin *) & m_margin;
    }

    if(align == Align::NONE) {
        pos.x = boundPos.x + offset->left;
        pos.y = boundPos.y + offset->top;
    }

    if(!!(align & Align::LEFT)) {
        pos.x = boundPos.x + offset->left;
    } else if(!!(align & Align::RIGHT)) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x - size.x - offset->right;
    } else if(!!(align & Align::CENTER)) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x / 2.0f - size.x / 2.0f;
    }
    if(!!(align & Align::MIDDLE)) {
        if(boundSize.y >= size.y)
            pos.y = boundPos.y + boundSize.y / 2.0f - size.y / 2.0f;
    } else if(!!(align & Align::TOP)) {
        pos.y = boundPos.y + offset->top;
    } else if(!!(align & Align::BOTTOM)) {
        if(boundSize.y > size.y)
            pos.y = (boundPos.y + boundSize.y) - size.y - offset->bottom;
    }
}

/**
 * 
 * @param align
 * @param pos
 * @param size
 * @param boundSize
 */
void gui::CStyleContent::applyPosAlign(const Align align,
                                       Vector2f& pos,
                                       const Vector2f& size,
                                       const Vector2f& boundPos,
                                       const Vector2f& boundSize,
                                       const fgBool isInside) {
    // Margin is outside of the border
    // Padding is inside of the border

    SMargin *offset = NULL;
    if(isInside) {
        offset = (SMargin *) & m_padding;
    } else {
        offset = (SMargin *) & m_margin;
    }

    if(align == Align::NONE) {
        pos.x += offset->left;
        pos.y += offset->top;
    }
    if(!!(align & Align::LEFT)) {
        pos.x = boundPos.x + offset->left;
    } else if(!!(align & Align::RIGHT)) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x - size.x - offset->right;
    } else if(!!(align & Align::CENTER)) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x / 2.0f - size.x / 2.0f;
    }
    if(!!(align & Align::MIDDLE)) {
        if(boundSize.y >= size.y)
            pos.y = boundPos.y + boundSize.y / 2.0f - size.y / 2.0f;
    } else if(!!(align & Align::TOP)) {
        pos.y = boundPos.y + offset->top;
    } else if(!!(align & Align::BOTTOM)) {
        if(boundSize.y >= size.y)
            pos.y = (boundPos.y + boundSize.y) - size.y - offset->bottom;
    }
}

/**
 * 
 * @param value
 * @return 
 */
fgColor4f gui::CStyleContent::parseColor(const char *value) {
    if(!value)
        return FG_GUI_DEFAULT_FG_COLOR;
    std::string colorStr = value;
    int r = 255, g = 255, b = 255, a = 255;
    fgColor4f retColor;
    colorStr = fgStrings::trim(colorStr);
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
 * @param value
 * @return 
 */
gui::SBorder::Style gui::CStyleContent::parseBorderStyle(const char *value) {
    if(!value)
        return SBorder::Style::NONE;
    SBorder::Style style = SBorder::Style::NONE;

    if(strcasecmp(value, "none") == 0) {
    } else if(strcasecmp(value, "dotted") == 0) {
        style = SBorder::Style::DOTTED;
    } else if(strcasecmp(value, "dashed") == 0) {
        style = SBorder::Style::DASHED;
    } else if(strcasecmp(value, "solid") == 0) {
        style = SBorder::Style::SOLID;
    }
    return style;
}

/**
 * 
 * @param value
 * @return 
 */
gui::SBorder gui::CStyleContent::parseBorder(const char *value) {
    SBorder border;
    if(!value)
        return border;
    fg::CStringVector parts;
    std::string borderStr = value;
    borderStr = fgStrings::trim(borderStr);
    fgStrings::split(borderStr, ' ', parts);
    if(parts.size() == 1) {
        parts[0] = fgStrings::trim(parts[0]);
        if(isdigit((int)parts[0].c_str()[0])) {
            border.width = (float)atof(parts[0].c_str());
        } else {
            border.style = parseBorderStyle(parts[0].c_str());
        }
    } else if(parts.size() == 2 || parts.size() == 3) {
        for(int i = 0; i < (int)parts.size(); i++) {
            parts[i] = fgStrings::trim(parts[i]);
            if(isdigit((int)parts[i].c_str()[0])) {
                border.width = (float)atof(parts[i].c_str());
            } else if(fgStrings::startsWith(parts[i].c_str(), "rgb", FG_FALSE) ||
                      fgStrings::startsWith(parts[i].c_str(), "#") ||
                      fgStrings::startsWith(parts[i].c_str(), "0x", FG_FALSE) ||
                      i == 2) {
                border.color = parseColor(parts[i].c_str());
            } else {
                border.style = parseBorderStyle(parts[i].c_str());
            }
        }
    }
    return border;
}

/**
 * 
 * @param value
 * @return 
 */
gui::SPosition::Style gui::CStyleContent::parsePositionStyle(const char *value) {
    if(!value)
        return SPosition::Style::STATIC;
    SPosition::Style style = SPosition::Style::STATIC;

    if(strcmp(value, "static") == 0) {
        style = SPosition::Style::STATIC;
    } else if(strcmp(value, "fixed") == 0) {
        style = SPosition::Style::FIXED;
    } else if(strcmp(value, "relative") == 0) {
        style = SPosition::Style::RELATIVE;
    } else if(strcmp(value, "absolute") == 0) {
        style = SPosition::Style::ABSOLUTE;
    }

    return style;
}

/**
 * 
 * @param value
 * @return 
 */
gui::Align gui::CStyleContent::parseAlign(const char *value) {
    Align align = Align::CENTER;
    if(!value)
        return align;
    align = Align::NONE;
    fg::CStringVector parts;
    fgStrings::split(std::string(value), ' ', parts);
    for(int i = 0; i < (int)parts.size(); i++) {
        if(parts[i].compare("left") == 0) {
            align |= Align::LEFT;
        } else if(parts[i].compare("right") == 0) {
            align |= Align::RIGHT;
        } else if(parts[i].compare("center") == 0) {
            align |= Align::CENTER;
        } else if(parts[i].compare("middle") == 0) {
            align |= Align::MIDDLE;
        } else if(parts[i].compare("top") == 0) {
            align |= Align::TOP;
        } else if(parts[i].compare("bottom") == 0) {
            align |= Align::BOTTOM;
        }
    }
    return align;
}

/**
 * 
 * @param value
 * @return 
 */
gui::SBackground::Style gui::CStyleContent::parseBackgroundStyle(const char *value) {
    SBackground::Style style = SBackground::Style::MAX;
    if(!value)
        return style;

    if(strcmp(value, "none") == 0) {
        style = SBackground::Style::NONE;
    } else if(strcmp(value, "normal") == 0) {
        style = SBackground::Style::NORMAL;
    } else if(strcmp(value, "max") == 0) {
        style = SBackground::Style::MAX;
    } else if(strcmp(value, "tiled") == 0) {
        style = SBackground::Style::TILED;
    }

    return style;
}

/**
 * Parses the length stored as string
 * @param value     Input length to parsed stored as C-like string
 * @param type      Type of the unit, can be percents, inches, blocks or pixels
 * @return          Floating point value of the parsed length
 */
float gui::CStyleContent::parseLength(const char *value, Unit &unit) {
    if(!value)
        return 0.0f;
    float length = 0.0f;
    std::string lengthStr;
    if(fgStrings::containsChars(value, "%")) {
        unit = Unit::PERCENTS;
        lengthStr = fgStrings::trim(std::string(value), std::string(" %"));
    } else if(fgStrings::containsChars(value, "b", FG_FALSE)) {
        unit = Unit::BLOCKS;
        lengthStr = fgStrings::trim(std::string(value), std::string(" bB"));
    } else if(fgStrings::containsChars(value, "i", FG_FALSE)) {
        unit = Unit::INCHES;
        lengthStr = fgStrings::trim(std::string(value), std::string(" iI"));
    } else {
        unit = Unit::PIXELS;
        lengthStr = fgStrings::trim(std::string(value), std::string(" fF"));
    }
    length = (float)atof(lengthStr.c_str());
    return length;
}

/**
 * Initializes the style content from ini style parameters
 * @param params    Style parameters from given section, taken directly from ini
 * @param merge     If true the styles will be merged, if false - overwritten
 * @return 
 */
fgBool gui::CStyleContent::initializeFromConfig(util::config::ParameterVec &params, fgBool merge) {
    if(params.empty())
        return FG_FALSE;

    util::config::ParameterVecItor begin, end, itor;
    begin = params.begin();
    end = params.end();
    itor = begin;

    // Iterate through all style parameters
    // Parameters are taken directly from ini config file
    for(; itor != end; itor++) {
        util::SCfgParameter *param = *itor;
        if(!param)
            continue;

        // BACKGROUND COLOR PARAMETER
        if(param->name.compare("bg-color") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_bg.color = parseColor(param->string);

            // FOREGROUND COLOR
        } else if(param->name.compare("fg-color") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_fg.color = parseColor(param->string);

            // BACKGROUND TEXTURE NAME
        } else if(param->name.compare("bg-texture") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_bg.texture = param->string;

            // BACKGROUND STYLE MODIFIER
        } else if(param->name.compare("bg-style") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_bg.style = parseBackgroundStyle(param->string);

            // TEXT SIZE PARAMETER
        } else if(param->name.compare("textSize") == 0) {
            Unit unit = Unit::PIXELS;
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_fg.textSize = param->float_val;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_fg.textSize = (float)param->int_val;
            } else if(param->type == util::SCfgParameter::STRING) {
                this->m_fg.textSize = parseLength(param->string, unit);
            }
            this->m_fg.unit = unit;

            // FONT NAME PARAMETER
        } else if(param->name.compare("font") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_fg.font = param->string;

            // MARGIN MODIFIER - APPLIES TO ALL
        } else if(param->name.compare("margin") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setMargin(SMargin::Which::ALL, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setMargin(SMargin::Which::ALL, (float)param->int_val);

            // LEFT MARGIN MODIFIER
        } else if(param->name.compare("margin-left") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setMargin(SMargin::Which::LEFT, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setMargin(SMargin::Which::LEFT, (float)param->int_val);

            // RIGHT MARGIN MODIFIER
        } else if(param->name.compare("margin-right") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setMargin(SMargin::Which::RIGHT, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setMargin(SMargin::Which::RIGHT, (float)param->int_val);

            // TOP MARGIN MODIFIER
        } else if(param->name.compare("margin-top") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setMargin(SMargin::Which::TOP, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setMargin(SMargin::Which::TOP, (float)param->int_val);

            // BOTTOM MARGIN MODIFIER
        } else if(param->name.compare("margin-bottom") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setMargin(SMargin::Which::BOTTOM, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setMargin(SMargin::Which::BOTTOM, (float)param->int_val);

            // PADDING MODIFIER - APPLIES TO ALL
        } else if(param->name.compare("padding") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setPadding(SPadding::Which::ALL, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setPadding(SPadding::Which::ALL, (float)param->int_val);

            // LEFT PADDING MODIFIER
        } else if(param->name.compare("padding-left") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setPadding(SPadding::Which::LEFT, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setPadding(SPadding::Which::LEFT, (float)param->int_val);

            // RIGHT PADDING MODIFIER
        } else if(param->name.compare("padding-right") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setPadding(SPadding::Which::RIGHT, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setPadding(SPadding::Which::RIGHT, (float)param->int_val);

            // TOP PADDING MODIFIER
        } else if(param->name.compare("padding-top") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setPadding(SPadding::Which::TOP, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setPadding(SPadding::Which::TOP, (float)param->int_val);

            // BOTTOM PADDING MODIFIER
        } else if(param->name.compare("padding-bottom") == 0) {
            if(param->type == util::SCfgParameter::FLOAT)
                this->setPadding(SPadding::Which::BOTTOM, param->float_val);
            else if(param->type == util::SCfgParameter::INT)
                this->setPadding(SPadding::Which::BOTTOM, (float)param->int_val);

            // BORDER PARAMETER - APPLIES TO ALL BORDERS
        } else if(param->name.compare("border") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                SBorder border = parseBorder(param->string);
                this->m_border.all = border;
                this->m_border.left = border;
                this->m_border.right = border;
                this->m_border.top = border;
                this->m_border.bottom = border;
            } else if(param->type == util::SCfgParameter::FLOAT) {
                this->setBorder(SBorder::Which::ALL, param->float_val);
                this->setBorder(SBorder::Which::ALL, SBorder::Style::SOLID);
            } else if(param->type == util::SCfgParameter::INT) {
                this->setBorder(SBorder::Which::ALL, (float)param->int_val);
                this->setBorder(SBorder::Which::ALL, SBorder::Style::SOLID);
            }

            // LEFT BORDER PARAMETER
        } else if(param->name.compare("border-left") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                SBorder border = parseBorder(param->string);
                this->m_border.left = border;
            } else if(param->type == util::SCfgParameter::FLOAT) {
                this->setBorder(SBorder::Which::LEFT, param->float_val);
                this->setBorder(SBorder::Which::LEFT, SBorder::Style::SOLID);
            } else if(param->type == util::SCfgParameter::INT) {
                this->setBorder(SBorder::Which::LEFT, (float)param->int_val);
                this->setBorder(SBorder::Which::LEFT, SBorder::Style::SOLID);
            }

            // RIGHT BORDER PARAMETER
        } else if(param->name.compare("border-right") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                SBorder border = parseBorder(param->string);
                this->m_border.right = border;
            } else if(param->type == util::SCfgParameter::FLOAT) {
                this->setBorder(SBorder::Which::RIGHT, param->float_val);
                this->setBorder(SBorder::Which::RIGHT, SBorder::Style::SOLID);
            } else if(param->type == util::SCfgParameter::INT) {
                this->setBorder(SBorder::Which::RIGHT, (float)param->int_val);
                this->setBorder(SBorder::Which::RIGHT, SBorder::Style::SOLID);
            }

            // TOP BORDER PARAMETER
        } else if(param->name.compare("border-top") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                SBorder border = parseBorder(param->string);
                this->m_border.top = border;
            } else if(param->type == util::SCfgParameter::FLOAT) {
                this->setBorder(SBorder::Which::TOP, param->float_val);
                this->setBorder(SBorder::Which::TOP, SBorder::Style::SOLID);
            } else if(param->type == util::SCfgParameter::INT) {
                this->setBorder(SBorder::Which::TOP, (float)param->int_val);
                this->setBorder(SBorder::Which::TOP, SBorder::Style::SOLID);
            }

            // BOTTOM BORDER PARAMETER
        } else if(param->name.compare("border-bottom") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                SBorder border = parseBorder(param->string);
                this->m_border.bottom = border;
            } else if(param->type == util::SCfgParameter::FLOAT) {
                this->setBorder(SBorder::Which::BOTTOM, param->float_val);
                this->setBorder(SBorder::Which::BOTTOM, SBorder::Style::SOLID);
            } else if(param->type == util::SCfgParameter::INT) {
                this->setBorder(SBorder::Which::BOTTOM, (float)param->int_val);
                this->setBorder(SBorder::Which::BOTTOM, SBorder::Style::SOLID);
            }

            // POSITON STYLE
        } else if(param->name.compare("position") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                this->setPosition(parsePositionStyle(param->string));

            // LEFT POSITION (X) LEFT
        } else if(param->name.compare("left") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_position.left = param->float_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_position.left = (float)param->int_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit = Unit::PIXELS;
                this->m_position.left = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // RIGHT POSITION (X) MODIFIER
        } else if(param->name.compare("right") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_position.right = param->float_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_position.right = (float)param->int_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit = Unit::PIXELS;
                this->m_position.right = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // TOP POSITION (Y) MODIFIER
        } else if(param->name.compare("top") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_position.top = param->float_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_position.top = (float)param->int_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit = Unit::PIXELS;
                this->m_position.top = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // BOTTOM POSITION (Y) MODIFIER
        } else if(param->name.compare("bottom") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_position.bottom = param->float_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_position.bottom = (float)param->int_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit = Unit::PIXELS;
                this->m_position.bottom = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // FRONT POSITION (Z) MODIFIER
        } else if(param->name.compare("front") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_position.front = param->float_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_position.front = (float)param->int_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit = Unit::PIXELS;
                this->m_position.front = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // BACK POSITION (Z) MODIFIER
        } else if(param->name.compare("back") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_position.back = param->float_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_position.back = (float)param->int_val;
                this->m_position.unit = Unit::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit = Unit::PIXELS;
                this->m_position.back = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // HORIZONTAL ALIGN
        } else if(param->name.compare("align") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                this->m_align = parseAlign(param->string);

            // VERTICAL ALIGN
        } else if(param->name.compare("valign") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                this->m_valign = parseAlign(param->string);

            // TEXT ALIGN
        } else if(param->name.compare("text-align") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                this->m_textAlign = parseAlign(param->string);

            // WIDTH
        } else if(param->name.compare("width") == 0) {
            // #FIXME
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_size.x = param->float_val;
                this->m_size.style = SSize::Style::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_size.x = (float)param->int_val;
                this->m_size.style = SSize::Style::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit = (Unit)SSize::Style::PIXELS;
                this->m_size.x = parseLength(param->string, unit);
                this->m_size.style = (SSize::Style)unit;
                if(this->m_size.x >= 100.0f && unit == Unit::PERCENTS)
                    this->m_size.style = SSize::Style::MAX;
                else if(this->m_size.x <= FG_EPSILON + 1.0f && unit == Unit::PERCENTS)
                    this->m_size.style = SSize::Style::MIN;
            }

            // HEIGHT
        } else if(param->name.compare("height") == 0) {
            // #FIXME
            if(param->type == util::SCfgParameter::FLOAT) {
                this->m_size.y = param->float_val;
                this->m_size.style = SSize::Style::PIXELS;
            } else if(param->type == util::SCfgParameter::INT) {
                this->m_size.y = (float)param->int_val;
                this->m_size.style = SSize::Style::PIXELS;
            } else if(param->type == util::SCfgParameter::STRING) {
                Unit unit;
                this->m_size.y = parseLength(param->string, unit);
                this->m_size.style = (SSize::Style)unit;
                if(this->m_size.y >= 100.0f && unit == Unit::PERCENTS)
                    this->m_size.style = SSize::Style::MAX;
                else if(this->m_size.y <= FG_EPSILON + 1.0f && unit == Unit::PERCENTS)
                    this->m_size.style = SSize::Style::MIN;
            }

            // USED SHADER FOR EFFECTS
        } else if(param->name.compare("shader") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_shader = param->string;

            // APPLIED EFFECT - SIMILAR TO PARTICLE EFFECT
        } else if(param->name.compare("effect") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_effect = param->string;
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
gui::SBackground& gui::CStyleContent::getBackground(void) {
    return m_bg;
}

/**
 * 
 * @return 
 */
gui::SForeground& gui::CStyleContent::getForeground(void) {
    return m_fg;
}

/**
 * 
 * @return 
 */
gui::SMargin& gui::CStyleContent::getMargin(void) {
    return m_margin;
}

/**
 * 
 * @return 
 */
gui::SPadding& gui::CStyleContent::getPadding(void) {
    return m_padding;
}

/**
 * 
 * @return 
 */
gui::SBorderGroup& gui::CStyleContent::getBorder(void) {
    return m_border;
}

/**
 * 
 * @return 
 */
gui::SPosition& gui::CStyleContent::getPosition(void) {
    return m_position;
}

/**
 * 
 * @return 
 */
gui::Align gui::CStyleContent::getAlign(void) const {
    return m_align;
}

/**
 * 
 * @return 
 */
gui::Align gui::CStyleContent::getVAlign(void) const {
    return m_valign;
}

/**
 * 
 * @return 
 */
gui::Align gui::CStyleContent::getTextAlign(void) const {
    return m_textAlign;
}

/**
 * 
 * @return 
 */
gui::SSize& gui::CStyleContent::getSize(void) {
    return m_size;
}

/**
 * 
 * @return 
 */
std::string& gui::CStyleContent::getShader(void) {
    return m_shader;
}

/**
 * 
 * @return 
 */
const char *gui::CStyleContent::getShaderStr(void) const {
    return m_shader.c_str();
}

/**
 * 
 * @return 
 */
std::string& gui::CStyleContent::getEffect(void) {
    return m_effect;
}

/**
 * 
 * @return 
 */
const char *gui::CStyleContent::getEffectStr(void) const {
    return m_effect.c_str();
}

/**
 * 
 * @param style
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBackground(const SBackground::Style style) {
    m_bg.style = style;
    return (*this);
}

/**
 * 
 * @param color
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBackground(const fgColor4f& color) {
    m_bg.color = color;
    return (*this);
}

/**
 * 
 * @param texture
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBackground(const std::string& texture) {
    m_bg.texture = texture;
    return (*this);
}

/**
 * 
 * @param texture
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBackground(const char *texture) {
    m_bg.texture = texture;
    return (*this);
}

/**
 * 
 * @param textSize
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setForeground(const float textSize) {
    m_fg.textSize = textSize;
    return (*this);
}

/**
 * 
 * @param color
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setForeground(const fgColor4f& color) {
    m_fg.color = color;
    return (*this);
}

/**
 * 
 * @param font
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setForeground(const std::string& font) {
    m_fg.font = font;
    return (*this);
}

/**
 * 
 * @param font
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setForeground(const char *font) {
    m_fg.font = font;
    return (*this);
}

/**
 * 
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setMargin(const float size) {
    return setMargin(SMargin::Which::ALL, size);
}

/**
 * 
 * @param which
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setMargin(const SMargin::Which which, const float size) {
    if(!!(which & SMargin::Which::LEFT))
        m_margin.left = size;
    if(!!(which & SMargin::Which::RIGHT))
        m_margin.right = size;
    if(!!(which & SMargin::Which::TOP))
        m_margin.top = size;
    if(!!(which & SMargin::Which::BOTTOM))
        m_margin.bottom = size;
    if(!!(which & SMargin::Which::ALL))
        m_margin.value = size;
    return (*this);
}

/**
 * 
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setPadding(const float size) {
    return setPadding(SPadding::Which::ALL, size);
}

/**
 * 
 * @param which
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setPadding(const SPadding::Which which, const float size) {
    if(!!(which & SPadding::Which::LEFT))
        m_padding.left = size;
    if(!!(which & SPadding::Which::RIGHT))
        m_padding.right = size;
    if(!!(which & SPadding::Which::TOP))
        m_padding.top = size;
    if(!!(which & SPadding::Which::BOTTOM))
        m_padding.bottom = size;
    if(!!(which & SPadding::Which::ALL))
        m_padding.value = size;
    return (*this);
}

/**
 * 
 * @param style
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBorder(const SBorder::Style style) {
    return setBorder(SBorder::Which::ALL, style);
}

/**
 * 
 * @param color
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBorder(const fgColor4f& color) {
    return setBorder(SBorder::Which::ALL, color);
}

/**
 * 
 * @param width
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBorder(const float width) {
    return setBorder(SBorder::Which::ALL, width);
}

/**
 * 
 * @param which
 * @param style
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBorder(const SBorder::Which which, const SBorder::Style style) {
    if(!!(which & SBorder::Which::LEFT))
        m_border.left.style = style;
    if(!!(which & SBorder::Which::RIGHT))
        m_border.right.style = style;
    if(!!(which & SBorder::Which::TOP))
        m_border.top.style = style;
    if(!!(which & SBorder::Which::BOTTOM))
        m_border.bottom.style = style;
    if(!!(which & SBorder::Which::ALL))
        m_border.all.style = style;
    return (*this);
}

/**
 * 
 * @param which
 * @param color
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBorder(const SBorder::Which which, const fgColor4f& color) {
    if(!!(which & SBorder::Which::LEFT))
        m_border.left.color = color;
    if(!!(which & SBorder::Which::RIGHT))
        m_border.right.color = color;
    if(!!(which & SBorder::Which::TOP))
        m_border.top.color = color;
    if(!!(which & SBorder::Which::BOTTOM))
        m_border.bottom.color = color;
    if(!!(which & SBorder::Which::ALL))
        m_border.all.color = color;
    return (*this);
}

/**
 * 
 * @param which
 * @param width
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setBorder(const SBorder::Which which, const float width) {
    if(!!(which & SBorder::Which::LEFT))
        m_border.left.width = width;
    if(!!(which & SBorder::Which::RIGHT))
        m_border.right.width = width;
    if(!!(which & SBorder::Which::TOP))
        m_border.top.width = width;
    if(!!(which & SBorder::Which::BOTTOM))
        m_border.bottom.width = width;
    if(!!(which & SBorder::Which::ALL))
        m_border.all.width = width;
    return (*this);
}

/**
 * 
 * @param style
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setPosition(const SPosition::Style style) {
    m_position.style = style;
    return (*this);
}

/**
 * 
 * @param style
 * @param modPos
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setPosition(const SPosition::Style style,
                                                    const Vector2f& modPos) {
    return setPosition(style).setPosition(modPos);
}

/**
 * 
 * @param modPos
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setPosition(const Vector2f& modPos) {
    if(m_position.style != SPosition::Style::STATIC) {
        if(modPos.x <= 0.0f)
            m_position.left = fabsf(modPos.x);
        else
            m_position.right = modPos.x;
        if(modPos.y <= 0.0f)
            m_position.top = fabsf(modPos.y);
        else
            m_position.bottom = modPos.y;
    }
    return (*this);
}

/**
 * 
 * @param style
 * @param modPos
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setPosition(const SPosition::Style style,
                                                    const Vector3f& modPos) {
    return setPosition(style).setPosition(modPos);
}

/**
 * 
 * @param modPos
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setPosition(const Vector3f& modPos) {
    if(m_position.style != SPosition::Style::STATIC) {
        if(modPos.x <= 0.0f)
            m_position.left = fabsf(modPos.x);
        else
            m_position.right = modPos.x;
        if(modPos.y <= 0.0f)
            m_position.top = fabsf(modPos.y);
        else
            m_position.bottom = modPos.y;
        if(modPos.z <= 0.0f)
            m_position.front = fabsf(modPos.z); // #FIXME
        else
            m_position.back = modPos.z;
    }
    return (*this);
}

/**
 * 
 * @param align
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setAlign(const Align align) {
    m_align = align;
    return (*this);
}

/**
 * 
 * @param vAlign
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setVAlign(const Align vAlign) {
    m_valign = vAlign;
    return (*this);
}

/**
 * 
 * @param textAlign
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setTextAlign(const Align textAlign) {
    m_textAlign = textAlign;
    return (*this);
}

/**
 * 
 * @param style
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const SSize::Style style) {
    m_size.style = style;
    return (*this);
}

/**
 * 
 * @param style
 * @param x
 * @param y
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const SSize::Style style,
                                                const float x,
                                                const float y) {
    return setSize(style).setSize(x, y);
}

/**
 * 
 * @param style
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const SSize::Style style,
                                                const Vector2f& size) {

    return setSize(style).setSize(size);
}

/**
 * 
 * @param style
 * @param x
 * @param y
 * @param z
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const SSize::Style style,
                                                const float x,
                                                const float y,
                                                const float z) {

    return setSize(style).setSize(x, y, z);
}

/**
 * 
 * @param style
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const SSize::Style style,
                                                const Vector3f& size) {
    return setSize(style).setSize(size);
}

/**
 * 
 * @param x
 * @param y
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const float x, const float y) {
    m_size.x = x;
    m_size.y = y;
    return (*this);
}

/**
 * 
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const Vector2f& size) {
    m_size.x = size.x;
    m_size.y = size.y;
    return (*this);
}

/**
 * 
 * @param x
 * @param y
 * @param z
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const float x,
                                                const float y,
                                                const float z) {
    m_size.x = x;
    m_size.y = y;
    m_size.z = z;
    return (*this);
}

/**
 * 
 * @param size
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setSize(const Vector3f& size) {
    m_size.x = size.x;
    m_size.y = size.y;
    m_size.z = size.z;
    return (*this);
}

/**
 * 
 * @param shader
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setShader(const std::string& shader) {
    m_shader = shader;
    return (*this);
}

/**
 * 
 * @param shader
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setShader(const char *shader) {
    m_shader = shader;
    return (*this);
}

/**
 * 
 * @param effect
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setEffect(const std::string& effect) {
    m_effect = effect;
    return (*this);
}

/**
 * 
 * @param effect
 * @return 
 */
gui::CStyleContent& gui::CStyleContent::setEffect(const char *effect) {
    m_effect = effect;
    return (*this);
}
