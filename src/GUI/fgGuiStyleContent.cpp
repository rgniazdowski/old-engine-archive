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

/*
 *
 */
fgGuiStyleContent::fgGuiStyleContent() { }

/*
 *
 */
fgGuiStyleContent::~fgGuiStyleContent() { }

/**
 * 
 * @param align
 * @param pos
 * @param size
 * @param boundSize
 */
void fgGuiStyleContent::applyPosAlign(const fgGuiAlign align,
                                      fgVector3f& pos,
                                      const fgVector3f& size,
                                      const fgVector3f& boundPos,
                                      const fgVector3f& boundSize,
                                      const fgBool isInside) {
    // Margin is outside of the border
    // Padding is inside of the border

    fgGuiMargin *offset = NULL;
    if(isInside) {
        offset = (fgGuiMargin *) & m_padding;
    } else {
        offset = (fgGuiMargin *) & m_margin;
    }

    if(align == FG_GUI_ALIGN_NONE) {
        pos.x = boundPos.x + offset->left;
        pos.y = boundPos.y + offset->top;
    }

    if(align & FG_GUI_ALIGN_LEFT) {
        pos.x = boundPos.x + offset->left;
    } else if(align & FG_GUI_ALIGN_RIGHT) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x - size.x - offset->right;
    } else if(align & FG_GUI_ALIGN_CENTER) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x / 2.0f - size.x / 2.0f;
    }
    if(align & FG_GUI_ALIGN_MIDDLE) {
        if(boundSize.y >= size.y)
            pos.y = boundPos.y + boundSize.y / 2.0f - size.y / 2.0f;
    } else if(align & FG_GUI_ALIGN_TOP) {
        pos.y = boundPos.y + offset->top;
    } else if(align & FG_GUI_ALIGN_BOTTOM) {
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
void fgGuiStyleContent::applyPosAlign(const fgGuiAlign align,
                                      fgVector2f& pos,
                                      const fgVector2f& size,
                                      const fgVector2f& boundPos,
                                      const fgVector2f& boundSize,
                                      const fgBool isInside) {
    // Margin is outside of the border
    // Padding is inside of the border

    fgGuiMargin *offset = NULL;
    if(isInside) {
        offset = (fgGuiMargin *) & m_padding;
    } else {
        offset = (fgGuiMargin *) & m_margin;
    }

    if(align == FG_GUI_ALIGN_NONE) {
        pos.x += offset->left;
        pos.y += offset->top;
    }
    if(align & FG_GUI_ALIGN_LEFT) {
        pos.x = boundPos.x + offset->left;
    } else if(align & FG_GUI_ALIGN_RIGHT) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x - size.x - offset->right;
    } else if(align & FG_GUI_ALIGN_CENTER) {
        if(boundSize.x >= size.x)
            pos.x = boundPos.x + boundSize.x / 2.0f - size.x / 2.0f;
    }
    if(align & FG_GUI_ALIGN_MIDDLE) {
        if(boundSize.y >= size.y)
            pos.y = boundPos.y + boundSize.y / 2.0f - size.y / 2.0f;
    } else if(align & FG_GUI_ALIGN_TOP) {
        pos.y = boundPos.y + offset->top;
    } else if(align & FG_GUI_ALIGN_BOTTOM) {
        if(boundSize.y >= size.y)
            pos.y = (boundPos.y + boundSize.y) - size.y - offset->bottom;
    }
}

/**
 * 
 * @param value
 * @return 
 */
fgColor4f fgGuiStyleContent::parseColor(const char *value) {
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
fgGuiBorderStyle fgGuiStyleContent::parseBorderStyle(const char *value) {
    if(!value)
        return FG_GUI_BORDER_NONE;
    fgGuiBorderStyle style = FG_GUI_BORDER_NONE;

    if(strcasecmp(value, "none") == 0) {
    } else if(strcasecmp(value, "dotted") == 0) {
        style = FG_GUI_BORDER_DOTTED;
    } else if(strcasecmp(value, "dashed") == 0) {
        style = FG_GUI_BORDER_DASHED;
    } else if(strcasecmp(value, "solid") == 0) {
        style = FG_GUI_BORDER_SOLID;
    }
    return style;
}

/**
 * 
 * @param value
 * @return 
 */
fgGuiBorder fgGuiStyleContent::parseBorder(const char *value) {
    fgGuiBorder border;
    if(!value)
        return border;
    fgStringVector parts;
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
fgGuiPositionStyle fgGuiStyleContent::parsePositionStyle(const char *value) {
    if(!value)
        return FG_GUI_POS_STATIC;
    fgGuiPositionStyle style = FG_GUI_POS_STATIC;

    if(strcmp(value, "static") == 0) {
        style = FG_GUI_POS_STATIC;
    } else if(strcmp(value, "fixed") == 0) {
        style = FG_GUI_POS_FIXED;
    } else if(strcmp(value, "relative") == 0) {
        style = FG_GUI_POS_RELATIVE;
    } else if(strcmp(value, "absolute") == 0) {
        style = FG_GUI_POS_ABSOLUTE;
    }

    return style;
}

/**
 * 
 * @param value
 * @return 
 */
fgGuiAlign fgGuiStyleContent::parseAlign(const char *value) {
    fgGuiAlign align = FG_GUI_ALIGN_CENTER;
    if(!value)
        return align;
    align = FG_GUI_ALIGN_NONE;
    fgStringVector parts;
    fgStrings::split(std::string(value), ' ', parts);
    for(int i = 0; i < (int)parts.size(); i++) {
        if(parts[i].compare("left") == 0) {
            align |= FG_GUI_ALIGN_LEFT;
        } else if(parts[i].compare("right") == 0) {
            align |= FG_GUI_ALIGN_RIGHT;
        } else if(parts[i].compare("center") == 0) {
            align |= FG_GUI_ALIGN_CENTER;
        } else if(parts[i].compare("middle") == 0) {
            align |= FG_GUI_ALIGN_MIDDLE;
        } else if(parts[i].compare("top") == 0) {
            align |= FG_GUI_ALIGN_TOP;
        } else if(parts[i].compare("bottom") == 0) {
            align |= FG_GUI_ALIGN_BOTTOM;
        }
    }
    return align;
}

/**
 * 
 * @param value
 * @return 
 */
fgGuiBackgroundStyle fgGuiStyleContent::parseBackgroundStyle(const char *value) {
    fgGuiBackgroundStyle style = FG_GUI_BACKGROUND_MAX;
    if(!value)
        return style;
    return style;
}

/**
 * Parses the length stored as string
 * @param value     Input length to parsed stored as C-like string
 * @param type      Type of the unit, can be percents, inches, blocks or pixels
 * @return          Floating point value of the parsed length
 */
float fgGuiStyleContent::parseLength(const char *value, fgGuiUnitType &type) {
    if(!value)
        return 0.0f;
    float length = 0.0f;
    std::string lengthStr;
    if(fgStrings::containsChars(value, "%")) {
        type = FG_GUI_PERCENTS;
        lengthStr = fgStrings::trim(std::string(value), std::string(" %"));
    } else if(fgStrings::containsChars(value, "b", FG_FALSE)) {
        type = FG_GUI_BLOCKS;
        lengthStr = fgStrings::trim(std::string(value), std::string(" bB"));
    } else if(fgStrings::containsChars(value, "i", FG_FALSE)) {
        type = FG_GUI_INCHES;
        lengthStr = fgStrings::trim(std::string(value), std::string(" iI"));
    } else {
        type = FG_GUI_PIXELS;
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
fgBool fgGuiStyleContent::initializeFromConfig(fgCfgTypes::parameterVec &params, fgBool merge) {
    if(params.empty())
        return FG_FALSE;

    fgCfgTypes::parameterVecItor begin, end, itor;
    begin = params.begin();
    end = params.end();
    itor = begin;

    // Iterate through all style parameters
    // Parameters are taken directly from ini config file
    for(; itor != end; itor++) {
        fgCfgParameter *param = *itor;
        if(!param)
            continue;

        // BACKGROUND COLOR PARAMETER
        if(param->name.compare("bg-color") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                m_bg.color = parseColor(param->string);

            // FOREGROUND COLOR
        } else if(param->name.compare("fg-color") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                m_fg.color = parseColor(param->string);

            // BACKGROUND TEXTURE NAME
        } else if(param->name.compare("bg-texture") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                m_bg.texture = param->string;

            // BACKGROUND STYLE MODIFIER
        } else if(param->name.compare("bg-style") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                m_bg.style = parseBackgroundStyle(param->string);

            // TEXT SIZE PARAMETER
        } else if(param->name.compare("textSize") == 0) {
            fgGuiUnitType unit = FG_GUI_PIXELS;
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_fg.textSize = param->float_val;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_fg.textSize = (float)param->int_val;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                this->m_fg.textSize = parseLength(param->string, unit);
            }
            this->m_fg.unit = unit;

            // FONT NAME PARAMETER
        } else if(param->name.compare("font") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                m_fg.font = param->string;

            // MARGIN MODIFIER - APPLIES TO ALL
        } else if(param->name.compare("margin") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setMargin(FG_GUI_MARGIN_ALL, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setMargin(FG_GUI_MARGIN_ALL, (float)param->int_val);

            // LEFT MARGIN MODIFIER
        } else if(param->name.compare("margin-left") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setMargin(FG_GUI_MARGIN_LEFT, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setMargin(FG_GUI_MARGIN_LEFT, (float)param->int_val);

            // RIGHT MARGIN MODIFIER
        } else if(param->name.compare("margin-right") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setMargin(FG_GUI_MARGIN_RIGHT, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setMargin(FG_GUI_MARGIN_RIGHT, (float)param->int_val);

            // TOP MARGIN MODIFIER
        } else if(param->name.compare("margin-top") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setMargin(FG_GUI_MARGIN_TOP, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setMargin(FG_GUI_MARGIN_TOP, (float)param->int_val);

            // BOTTOM MARGIN MODIFIER
        } else if(param->name.compare("margin-bottom") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setMargin(FG_GUI_MARGIN_BOTTOM, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setMargin(FG_GUI_MARGIN_BOTTOM, (float)param->int_val);

            // PADDING MODIFIER - APPLIES TO ALL
        } else if(param->name.compare("padding") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setPadding(FG_GUI_PADDING_ALL, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setPadding(FG_GUI_PADDING_ALL, (float)param->int_val);

            // LEFT PADDING MODIFIER
        } else if(param->name.compare("padding-left") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setPadding(FG_GUI_PADDING_LEFT, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setPadding(FG_GUI_PADDING_LEFT, (float)param->int_val);

            // RIGHT PADDING MODIFIER
        } else if(param->name.compare("padding-right") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setPadding(FG_GUI_PADDING_RIGHT, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setPadding(FG_GUI_PADDING_RIGHT, (float)param->int_val);

            // TOP PADDING MODIFIER
        } else if(param->name.compare("padding-top") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setPadding(FG_GUI_PADDING_TOP, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setPadding(FG_GUI_PADDING_TOP, (float)param->int_val);

            // BOTTOM PADDING MODIFIER
        } else if(param->name.compare("padding-bottom") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT)
                this->setPadding(FG_GUI_PADDING_BOTTOM, param->float_val);
            else if(param->type == FG_CFG_PARAMETER_INT)
                this->setPadding(FG_GUI_PADDING_BOTTOM, (float)param->int_val);

            // BORDER PARAMETER - APPLIES TO ALL BORDERS
        } else if(param->name.compare("border") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiBorder border = parseBorder(param->string);
                this->m_border.all = border;
                this->m_border.left = border;
                this->m_border.right = border;
                this->m_border.top = border;
                this->m_border.bottom = border;
            } else if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->setBorder(FG_GUI_BORDER_ALL, param->float_val);
                this->setBorder(FG_GUI_BORDER_ALL, FG_GUI_BORDER_SOLID);
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->setBorder(FG_GUI_BORDER_ALL, (float)param->int_val);
                this->setBorder(FG_GUI_BORDER_ALL, FG_GUI_BORDER_SOLID);
            }

            // LEFT BORDER PARAMETER
        } else if(param->name.compare("border-left") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiBorder border = parseBorder(param->string);
                this->m_border.left = border;
            } else if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->setBorder(FG_GUI_BORDER_LEFT, param->float_val);
                this->setBorder(FG_GUI_BORDER_LEFT, FG_GUI_BORDER_SOLID);
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->setBorder(FG_GUI_BORDER_LEFT, (float)param->int_val);
                this->setBorder(FG_GUI_BORDER_LEFT, FG_GUI_BORDER_SOLID);
            }

            // RIGHT BORDER PARAMETER
        } else if(param->name.compare("border-right") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiBorder border = parseBorder(param->string);
                this->m_border.right = border;
            } else if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->setBorder(FG_GUI_BORDER_RIGHT, param->float_val);
                this->setBorder(FG_GUI_BORDER_RIGHT, FG_GUI_BORDER_SOLID);
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->setBorder(FG_GUI_BORDER_RIGHT, (float)param->int_val);
                this->setBorder(FG_GUI_BORDER_RIGHT, FG_GUI_BORDER_SOLID);
            }

            // TOP BORDER PARAMETER
        } else if(param->name.compare("border-top") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiBorder border = parseBorder(param->string);
                this->m_border.top = border;
            } else if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->setBorder(FG_GUI_BORDER_TOP, param->float_val);
                this->setBorder(FG_GUI_BORDER_TOP, FG_GUI_BORDER_SOLID);
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->setBorder(FG_GUI_BORDER_TOP, (float)param->int_val);
                this->setBorder(FG_GUI_BORDER_TOP, FG_GUI_BORDER_SOLID);
            }

            // BOTTOM BORDER PARAMETER
        } else if(param->name.compare("border-bottom") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiBorder border = parseBorder(param->string);
                this->m_border.bottom = border;
            } else if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->setBorder(FG_GUI_BORDER_BOTTOM, param->float_val);
                this->setBorder(FG_GUI_BORDER_BOTTOM, FG_GUI_BORDER_SOLID);
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->setBorder(FG_GUI_BORDER_BOTTOM, (float)param->int_val);
                this->setBorder(FG_GUI_BORDER_BOTTOM, FG_GUI_BORDER_SOLID);
            }

            // POSITON STYLE
        } else if(param->name.compare("position") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                this->setPosition(parsePositionStyle(param->string));

            // LEFT POSITION (X) LEFT
        } else if(param->name.compare("left") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_position.left = param->float_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_position.left = (float)param->int_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit = FG_GUI_PIXELS;
                this->m_position.left = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // RIGHT POSITION (X) MODIFIER
        } else if(param->name.compare("right") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_position.right = param->float_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_position.right = (float)param->int_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit = FG_GUI_PIXELS;
                this->m_position.right = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // TOP POSITION (Y) MODIFIER
        } else if(param->name.compare("top") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_position.top = param->float_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_position.top = (float)param->int_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit = FG_GUI_PIXELS;
                this->m_position.top = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // BOTTOM POSITION (Y) MODIFIER
        } else if(param->name.compare("bottom") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_position.bottom = param->float_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_position.bottom = (float)param->int_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit = FG_GUI_PIXELS;
                this->m_position.bottom = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // FRONT POSITION (Z) MODIFIER
        } else if(param->name.compare("front") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_position.front = param->float_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_position.front = (float)param->int_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit = FG_GUI_PIXELS;
                this->m_position.front = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // BACK POSITION (Z) MODIFIER
        } else if(param->name.compare("back") == 0) {
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_position.back = param->float_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_position.back = (float)param->int_val;
                this->m_position.unit = FG_GUI_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit = FG_GUI_PIXELS;
                this->m_position.back = parseLength(param->string, unit);
                this->m_position.unit = unit;
            }

            // HORIZONTAL ALIGN
        } else if(param->name.compare("align") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                this->m_align = parseAlign(param->string);

            // VERTICAL ALIGN
        } else if(param->name.compare("valign") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                this->m_valign = parseAlign(param->string);

            // TEXT ALIGN
        } else if(param->name.compare("text-align") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                this->m_textAlign = parseAlign(param->string);

            // WIDTH
        } else if(param->name.compare("width") == 0) {
            // #FIXME
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_size.x = param->float_val;
                this->m_size.style = FG_GUI_SIZE_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_size.x = (float)param->int_val;
                this->m_size.style = FG_GUI_SIZE_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit = FG_GUI_PIXELS;
                this->m_size.x = parseLength(param->string, unit);
                this->m_size.style = (fgGuiSizeStyle)unit;
                if(this->m_size.x >= 100.0f && unit == FG_GUI_PERCENTS)
                    this->m_size.style = FG_GUI_SIZE_MAX;
                else if(this->m_size.x <= FG_EPSILON + 1.0f && unit == FG_GUI_PERCENTS)
                    this->m_size.style = FG_GUI_SIZE_MIN;
            }

            // HEIGHT
        } else if(param->name.compare("height") == 0) {
            // #FIXME
            if(param->type == FG_CFG_PARAMETER_FLOAT) {
                this->m_size.y = param->float_val;
                this->m_size.style = FG_GUI_SIZE_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_INT) {
                this->m_size.y = (float)param->int_val;
                this->m_size.style = FG_GUI_SIZE_PIXELS;
            } else if(param->type == FG_CFG_PARAMETER_STRING) {
                fgGuiUnitType unit;
                this->m_size.y = parseLength(param->string, unit);
                this->m_size.style = (fgGuiSizeStyle)unit;
                if(this->m_size.y >= 100.0f && unit == FG_GUI_PERCENTS)
                    this->m_size.style = FG_GUI_SIZE_MAX;
                else if(this->m_size.y <= FG_EPSILON + 1.0f && unit == FG_GUI_PERCENTS)
                    this->m_size.style = FG_GUI_SIZE_MIN;
            }

            // USED SHADER FOR EFFECTS
        } else if(param->name.compare("shader") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                m_shader = param->string;

            // APPLIED EFFECT - SIMILAR TO PARTICLE EFFECT
        } else if(param->name.compare("effect") == 0) {
            if(param->type == FG_CFG_PARAMETER_STRING)
                m_effect = param->string;
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgGuiBackground& fgGuiStyleContent::getBackground(void) {
    return m_bg;
}

/**
 * 
 * @return 
 */
fgGuiForeground& fgGuiStyleContent::getForeground(void) {
    return m_fg;
}

/**
 * 
 * @return 
 */
fgGuiMargin& fgGuiStyleContent::getMargin(void) {
    return m_margin;
}

/**
 * 
 * @return 
 */
fgGuiPadding& fgGuiStyleContent::getPadding(void) {
    return m_padding;
}

/**
 * 
 * @return 
 */
fgGuiBorderInfo& fgGuiStyleContent::getBorder(void) {
    return m_border;
}

/**
 * 
 * @return 
 */
fgGuiPosition& fgGuiStyleContent::getPosition(void) {
    return m_position;
}

/**
 * 
 * @return 
 */
fgGuiAlign fgGuiStyleContent::getAlign(void) const {
    return m_align;
}

/**
 * 
 * @return 
 */
fgGuiAlign fgGuiStyleContent::getVAlign(void) const {
    return m_valign;
}

/**
 * 
 * @return 
 */
fgGuiAlign fgGuiStyleContent::getTextAlign(void) const {
    return m_textAlign;
}

/**
 * 
 * @return 
 */
fgGuiSize& fgGuiStyleContent::getSize(void) {
    return m_size;
}

/**
 * 
 * @return 
 */
std::string& fgGuiStyleContent::getShader(void) {
    return m_shader;
}

/**
 * 
 * @return 
 */
const char *fgGuiStyleContent::getShaderStr(void) const {
    return m_shader.c_str();
}

/**
 * 
 * @return 
 */
std::string& fgGuiStyleContent::getEffect(void) {
    return m_effect;
}

/**
 * 
 * @return 
 */
const char *fgGuiStyleContent::getEffectStr(void) const {
    return m_effect.c_str();
}

/**
 * 
 * @param style
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBackground(const fgGuiBackgroundStyle style) {
    m_bg.style = style;
    return (*this);
}

/**
 * 
 * @param color
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBackground(const fgColor4f& color) {
    m_bg.color = color;
    return (*this);
}

/**
 * 
 * @param texture
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBackground(const std::string& texture) {
    m_bg.texture = texture;
    return (*this);
}

/**
 * 
 * @param texture
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBackground(const char *texture) {
    m_bg.texture = texture;
    return (*this);
}

/**
 * 
 * @param textSize
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setForeground(const float textSize) {
    m_fg.textSize = textSize;
    return (*this);
}

/**
 * 
 * @param color
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setForeground(const fgColor4f& color) {
    m_fg.color = color;
    return (*this);
}

/**
 * 
 * @param font
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setForeground(const std::string& font) {
    m_fg.font = font;
    return (*this);
}

/**
 * 
 * @param font
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setForeground(const char *font) {
    m_fg.font = font;
    return (*this);
}

/**
 * 
 * @param size
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setMargin(const float size) {
    return setMargin(FG_GUI_MARGIN_ALL, size);
}

/**
 * 
 * @param which
 * @param size
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setMargin(const fgGuiMarginWhich which, const float size) {
    if(which & FG_GUI_MARGIN_LEFT)
        m_margin.left = size;
    if(which & FG_GUI_MARGIN_RIGHT)
        m_margin.right = size;
    if(which & FG_GUI_MARGIN_TOP)
        m_margin.top = size;
    if(which & FG_GUI_MARGIN_BOTTOM)
        m_margin.bottom = size;
    if(which & FG_GUI_MARGIN_ALL)
        m_margin.value = size;
    return (*this);
}

/**
 * 
 * @param size
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setPadding(const float size) {
    return setPadding(FG_GUI_PADDING_ALL, size);
}

/**
 * 
 * @param which
 * @param size
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setPadding(const fgGuiPaddingWhich which, const float size) {
    if(which & FG_GUI_PADDING_LEFT)
        m_padding.left = size;
    if(which & FG_GUI_PADDING_RIGHT)
        m_padding.right = size;
    if(which & FG_GUI_PADDING_TOP)
        m_padding.top = size;
    if(which & FG_GUI_PADDING_BOTTOM)
        m_padding.bottom = size;
    if(which & FG_GUI_PADDING_ALL)
        m_padding.value = size;
    return (*this);
}

/**
 * 
 * @param style
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderStyle style) {
    return setBorder(FG_GUI_BORDER_ALL, style);
}

/**
 * 
 * @param color
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgColor4f& color) {
    return setBorder(FG_GUI_BORDER_ALL, color);
}

/**
 * 
 * @param width
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBorder(const float width) {
    return setBorder(FG_GUI_BORDER_ALL, width);
}

/**
 * 
 * @param which
 * @param style
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderWhich which, const fgGuiBorderStyle style) {
    if(which & FG_GUI_BORDER_LEFT)
        m_border.left.style = style;
    if(which & FG_GUI_BORDER_RIGHT)
        m_border.right.style = style;
    if(which & FG_GUI_BORDER_TOP)
        m_border.top.style = style;
    if(which & FG_GUI_BORDER_BOTTOM)
        m_border.bottom.style = style;
    if(which & FG_GUI_BORDER_ALL)
        m_border.all.style = style;
    return (*this);
}

/**
 * 
 * @param which
 * @param color
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderWhich which, const fgColor4f& color) {
    if(which & FG_GUI_BORDER_LEFT)
        m_border.left.color = color;
    if(which & FG_GUI_BORDER_RIGHT)
        m_border.right.color = color;
    if(which & FG_GUI_BORDER_TOP)
        m_border.top.color = color;
    if(which & FG_GUI_BORDER_BOTTOM)
        m_border.bottom.color = color;
    if(which & FG_GUI_BORDER_ALL)
        m_border.all.color = color;
    return (*this);
}

/**
 * 
 * @param which
 * @param width
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderWhich which, const float width) {
    if(which & FG_GUI_BORDER_LEFT)
        m_border.left.width = width;
    if(which & FG_GUI_BORDER_RIGHT)
        m_border.right.width = width;
    if(which & FG_GUI_BORDER_TOP)
        m_border.top.width = width;
    if(which & FG_GUI_BORDER_BOTTOM)
        m_border.bottom.width = width;
    if(which & FG_GUI_BORDER_ALL)
        m_border.all.width = width;
    return (*this);
}

/**
 * 
 * @param style
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgGuiPositionStyle style) {
    m_position.style = style;
    return (*this);
}

/**
 * 
 * @param style
 * @param modPos
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgGuiPositionStyle style,
                                                  const fgVector2f& modPos) {
    return setPosition(style).setPosition(modPos);
}

/**
 * 
 * @param modPos
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgVector2f& modPos) {
    if(m_position.style != FG_GUI_POS_STATIC) {
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
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgGuiPositionStyle style,
                                                  const fgVector3f& modPos) {
    return setPosition(style).setPosition(modPos);
}

/**
 * 
 * @param modPos
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgVector3f& modPos) {
    if(m_position.style != FG_GUI_POS_STATIC) {
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
fgGuiStyleContent& fgGuiStyleContent::setAlign(const fgGuiAlign align) {
    m_align = align;
    return (*this);
}

/**
 * 
 * @param vAlign
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setVAlign(const fgGuiAlign vAlign) {
    m_valign = vAlign;
    return (*this);
}

/**
 * 
 * @param textAlign
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setTextAlign(const fgGuiAlign textAlign) {
    m_textAlign = textAlign;
    return (*this);
}

/**
 * 
 * @param style
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgGuiSizeStyle style) {
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
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgGuiSizeStyle style,
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
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgGuiSizeStyle style,
                                              const fgVector2f& size) {

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
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgGuiSizeStyle style,
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
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgGuiSizeStyle style,
                                              const fgVector3f& size) {
    return setSize(style).setSize(size);
}

/**
 * 
 * @param x
 * @param y
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setSize(const float x, const float y) {
    m_size.x = x;
    m_size.y = y;
    return (*this);
}

/**
 * 
 * @param size
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgVector2f& size) {
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
fgGuiStyleContent& fgGuiStyleContent::setSize(const float x,
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
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgVector3f& size) {
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
fgGuiStyleContent& fgGuiStyleContent::setShader(const std::string& shader) {
    m_shader = shader;
    return (*this);
}

/**
 * 
 * @param shader
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setShader(const char *shader) {
    m_shader = shader;
    return (*this);
}

/**
 * 
 * @param effect
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setEffect(const std::string& effect) {
    m_effect = effect;
    return (*this);
}

/**
 * 
 * @param effect
 * @return 
 */
fgGuiStyleContent& fgGuiStyleContent::setEffect(const char *effect) {
    m_effect = effect;
    return (*this);
}
