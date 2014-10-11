/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyleContent.h"
#include "Util/fgStrings.h"

/*
 *
 */
fgGuiStyleContent::fgGuiStyleContent()
{
}

/*
 *
 */
fgGuiStyleContent::~fgGuiStyleContent()
{
}

/*
 *
 */
void fgGuiStyleContent::applyPosAlign(const fgGuiAlign align, fgVector3f& pos, const fgVector3f& size, const fgVector3f& boundSize)
{
	if(align == FG_GUI_ALIGN_NONE) {
		pos.x += m_padding.left;
		pos.y += m_padding.top;
	}
	if(align & FG_GUI_ALIGN_LEFT) {
		pos.x += m_padding.left;
	} else if(align & FG_GUI_ALIGN_RIGHT) {
		pos.x += boundSize.x - size.x - m_padding.right;
	} else if(align & FG_GUI_ALIGN_CENTER) {
		pos.x += boundSize.x/2.0f - size.x/2.0f;
	}
	if(align & FG_GUI_ALIGN_MIDDLE) {
		pos.y += boundSize.y/2.0f - size.y/2.0f;
	} else if(align & FG_GUI_ALIGN_TOP) {
		pos.y += m_padding.top;
	} else if(align & FG_GUI_ALIGN_BOTTOM) {
		pos.y += boundSize.y - size.y - m_padding.bottom;
	}
}

/*
 *
 */
void fgGuiStyleContent::applyPosAlign(const fgGuiAlign align, fgVector2f& pos, const fgVector2f& size, const fgVector2f& boundSize)
{
	if(align == FG_GUI_ALIGN_NONE) {
		pos.x += m_padding.left;
		pos.y += m_padding.top;
	}
	if(align & FG_GUI_ALIGN_LEFT) {
		pos.x += m_padding.left;
	} else if(align & FG_GUI_ALIGN_RIGHT) {
		pos.x += boundSize.x - size.x - m_padding.right;
	} else if(align & FG_GUI_ALIGN_CENTER) {
		pos.x += boundSize.x/2.0f - size.x/2.0f;
	}
	if(align & FG_GUI_ALIGN_MIDDLE) {
		pos.y += boundSize.y/2.0f - size.y/2.0f;
	} else if(align & FG_GUI_ALIGN_TOP) {
		pos.y += m_padding.top;
	} else if(align & FG_GUI_ALIGN_BOTTOM) {
		pos.y += boundSize.y - size.y - m_padding.bottom;
	}
}

/*
 *
 */
fgColor4f fgGuiStyleContent::parseColor(const char *value)
{
	// NEED STANDARD COLOR CONST ARRAY ! ! ! ! ! WHERE?
	if(!value)
		return FG_GUI_DEFAULT_FG_COLOR;
	std::string colorStr = value;
	int r=255,g=255,b=255,a=255;
	fgColor4f retColor;
	colorStr = fgStrings::trim(colorStr);
	if(fgStrings::startsWith(colorStr.c_str(), "rgba", FG_TRUE)) {
		sscanf(colorStr.c_str(),"rgba(%d,%d,%d,%d)", &r, &g, &b, &a);
	} else if(fgStrings::startsWith(colorStr.c_str(), "rgb", FG_TRUE)) {
		sscanf(colorStr.c_str(),"rgb(%d,%d,%d)", &r, &g, &b);
	} else if(fgStrings::startsWith(colorStr.c_str(), "#", FG_TRUE)) {
		// HEX!
	} else {
		// readable human name !
	}
	retColor.r = (float)r/255.0f;
	retColor.g = (float)g/255.0f;
	retColor.b = (float)b/255.0f;
	retColor.a = (float)a/255.0f;
	return retColor;
}

/*
 *
 */
fgGuiBorderStyle fgGuiStyleContent::parseBorderStyle(const char *value)
{
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


/*
 *
 */
fgGuiBorder fgGuiStyleContent::parseBorder(const char *value)
{
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
		for(int i=0;i<(int)parts.size();i++) {
			parts[i] = fgStrings::trim(parts[i]);
			if(isdigit((int)parts[i].c_str()[0])) {
				border.width = (float)atof(parts[i].c_str());
			} else if(fgStrings::startsWith(parts[i].c_str(), "rgb", FG_FALSE)) {
				border.color = parseColor(parts[i].c_str());
			} else {
				border.style = parseBorderStyle(parts[i].c_str());
			}
		}
	} 
	return border;
}

/*
 *
 */
fgGuiPositionStyle fgGuiStyleContent::parsePositionStyle(const char *value)
{
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

/*
 *
 */
fgGuiAlign fgGuiStyleContent::parseAlign(const char *value)
{
	fgGuiAlign align = FG_GUI_ALIGN_CENTER;
	if(!value)
		return align;
	align = FG_GUI_ALIGN_NONE;
	fgStringVector parts;
	fgStrings::split(std::string(value), ' ', parts);
	for(int i=0;i<(int)parts.size();i++) {
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

/*
 *
 */
fgGuiBackgroundStyle fgGuiStyleContent::parseBackgroundStyle(const char *value)
{
	fgGuiBackgroundStyle style = FG_GUI_BACKGROUND_MAX;
	if(!value)
		return style;
	return style;
}

/*
 *
 */
fgBool fgGuiStyleContent::initializeFromConfig(fgCfgTypes::parameterVec &params, fgBool merge)
{
	if(params.empty())
		return FG_FALSE;

	fgCfgTypes::parameterVecItor begin, end, itor;
	begin = params.begin(); end = params.end(); itor = begin;

	for(;itor!=end;itor++) {
		fgCfgParameter *param = *itor;
		if(!param)
			continue;

		if(param->name.compare("bg-color") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				m_bg.color = parseColor(param->string);

		} else if(param->name.compare("fg-color") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				m_fg.color = parseColor(param->string);

		} else if(param->name.compare("bg-texture") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				m_bg.texture = param->string;

		} else if(param->name.compare("bg-style") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				m_bg.style = parseBackgroundStyle(param->string);

		} else if(param->name.compare("textSize") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				m_fg.textSize = param->float_val;
			else if(param->type == FG_CFG_PARAMETER_INT)
				m_fg.textSize = (float)param->int_val;

		} else if(param->name.compare("font") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				m_fg.font = param->string;

		} else if(param->name.compare("margin") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setMargin(FG_GUI_MARGIN_ALL, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setMargin(FG_GUI_MARGIN_ALL, (float)param->int_val);

		} else if(param->name.compare("margin-left") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setMargin(FG_GUI_MARGIN_LEFT, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setMargin(FG_GUI_MARGIN_LEFT, (float)param->int_val);

		} else if(param->name.compare("margin-right") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setMargin(FG_GUI_MARGIN_RIGHT, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setMargin(FG_GUI_MARGIN_RIGHT, (float)param->int_val);

		} else if(param->name.compare("margin-top") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setMargin(FG_GUI_MARGIN_TOP, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setMargin(FG_GUI_MARGIN_TOP, (float)param->int_val);

		} else if(param->name.compare("margin-bottom") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setMargin(FG_GUI_MARGIN_BOTTOM, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setMargin(FG_GUI_MARGIN_BOTTOM, (float)param->int_val);

		} else if(param->name.compare("padding") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setPadding(FG_GUI_PADDING_ALL, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setPadding(FG_GUI_PADDING_ALL, (float)param->int_val);

		} else if(param->name.compare("padding-left") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setPadding(FG_GUI_PADDING_LEFT, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setPadding(FG_GUI_PADDING_LEFT, (float)param->int_val);

		} else if(param->name.compare("padding-right") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setPadding(FG_GUI_PADDING_RIGHT, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setPadding(FG_GUI_PADDING_RIGHT, (float)param->int_val);

		} else if(param->name.compare("padding-top") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setPadding(FG_GUI_PADDING_TOP, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setPadding(FG_GUI_PADDING_TOP, (float)param->int_val);

		} else if(param->name.compare("padding-bottom") == 0) {
			if(param->type == FG_CFG_PARAMETER_FLOAT)
				this->setPadding(FG_GUI_PADDING_BOTTOM, param->float_val);
			else if(param->type == FG_CFG_PARAMETER_INT)
				this->setPadding(FG_GUI_PADDING_BOTTOM, (float)param->int_val);

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
		
		} else if(param->name.compare("position") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				this->setPosition(parsePositionStyle(param->string));
		
		} else if(param->name.compare("left") == 0) {
		
		} else if(param->name.compare("right") == 0) {
		
		} else if(param->name.compare("top") == 0) {
		
		} else if(param->name.compare("bottom") == 0) {
		
		} else if(param->name.compare("front") == 0) {
		
		} else if(param->name.compare("back") == 0) {
		
		} else if(param->name.compare("align") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				this->m_align = parseAlign(param->string);

		} else if(param->name.compare("valign") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				this->m_valign = parseAlign(param->string);

		} else if(param->name.compare("text-align") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				this->m_textAlign = parseAlign(param->string);

		} else if(param->name.compare("width") == 0) {
			// #FIXME
			if(param->type == FG_CFG_PARAMETER_FLOAT) {
				this->m_size.x = param->float_val;
			} else if(param->type == FG_CFG_PARAMETER_INT) {
				this->m_size.x = (float)param->int_val;
			} else if(param->type == FG_CFG_PARAMETER_STRING) {
			}

		} else if(param->name.compare("height") == 0) {
			// #FIXME
			if(param->type == FG_CFG_PARAMETER_FLOAT) {
				this->m_size.y = param->float_val;
			} else if(param->type == FG_CFG_PARAMETER_INT) {
				this->m_size.y = (float)param->int_val;
			} else if(param->type == FG_CFG_PARAMETER_STRING) {
			}

		} else if(param->name.compare("shader") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				m_shader = param->string;
		
		} else if(param->name.compare("effect") == 0) {
			if(param->type == FG_CFG_PARAMETER_STRING)
				m_effect = param->string;
		}
	}

	return FG_TRUE;
}

//
fgGuiBackground& fgGuiStyleContent::getBackground(void)
{
	return m_bg;
}

//
fgGuiForeground& fgGuiStyleContent::getForeground(void)
{
	return m_fg;
}

//
fgGuiMargin& fgGuiStyleContent::getMargin(void) 
{
	return m_margin;
}

//
fgGuiPadding& fgGuiStyleContent::getPadding(void)
{
	return m_padding;
}

//
fgGuiBorderInfo& fgGuiStyleContent::getBorder(void)
{
	return m_border;
}

//
fgGuiPosition& fgGuiStyleContent::getPosition(void)
{
	return m_position;
}

//
fgGuiAlign fgGuiStyleContent::getAlign(void) const
{
	return m_align;
}

//
fgGuiAlign fgGuiStyleContent::getVAlign(void) const
{
	return m_valign;
}

//
fgGuiAlign fgGuiStyleContent::getTextAlign(void) const
{
	return m_textAlign;
}

//
fgVector2f& fgGuiStyleContent::getSize(void)
{
	return m_size;
}

//
std::string& fgGuiStyleContent::getShader(void)
{
	return m_shader;
}

//
std::string& fgGuiStyleContent::getEffect(void)
{
	return m_effect;
}
	
//
fgGuiStyleContent& fgGuiStyleContent::setBackground(const fgGuiBackgroundStyle style)
{
	m_bg.style = style;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setBackground(const fgColor4f& color)
{
	m_bg.color = color;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setBackground(const std::string& texture) 
{
	m_bg.texture = texture;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setForeground(const float textSize) 
{
	m_fg.textSize = textSize;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setForeground(const fgColor4f& color) 
{
	m_fg.color = color;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setForeground(const std::string& font) 
{
	m_fg.font = font;
	return (*this);
}
	
//
fgGuiStyleContent& fgGuiStyleContent::setMargin(const float size) 
{
	return setMargin(FG_GUI_MARGIN_ALL, size);
}

//
fgGuiStyleContent& fgGuiStyleContent::setMargin(const fgGuiMarginWhich which, const float size) 
{
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

//
fgGuiStyleContent& fgGuiStyleContent::setPadding(const float size) 
{
	return setPadding(FG_GUI_PADDING_ALL, size);
}

//
fgGuiStyleContent& fgGuiStyleContent::setPadding(const fgGuiPaddingWhich which, const float size) 
{
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

//
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderStyle style) 
{
	return setBorder(FG_GUI_BORDER_ALL, style);
}

//
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgColor4f& color) 
{
	return setBorder(FG_GUI_BORDER_ALL, color);
}

//
fgGuiStyleContent& fgGuiStyleContent::setBorder(const float width) 
{
	return setBorder(FG_GUI_BORDER_ALL, width);
}

//
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderWhich which, const fgGuiBorderStyle style) 
{
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

//
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderWhich which, const fgColor4f& color) 
{
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

//
fgGuiStyleContent& fgGuiStyleContent::setBorder(const fgGuiBorderWhich which, const float width) 
{
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

//
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgGuiPositionStyle style) 
{
	m_position.style = style;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgGuiPositionStyle style, const fgVector2f& modPos) 
{
	return setPosition(style).setPosition(modPos);
}

//
fgGuiStyleContent& fgGuiStyleContent::setPosition(const fgVector2f& modPos) 
{
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

//
fgGuiStyleContent& fgGuiStyleContent::setAlign(const fgGuiAlign align) 
{
	m_align = align;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setVAlign(const fgGuiAlign vAlign) 
{
	m_valign = vAlign;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setTextAlign(const fgGuiAlign textAlign) 
{
	m_textAlign = textAlign;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setSize(const float x, const float y) 
{
	m_size.x = x;
	m_size.y = y;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setSize(const fgVector2f& size) 
{
	m_size = size;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setShader(const std::string& shader) 
{
	m_shader = shader;
	return (*this);
}

//
fgGuiStyleContent& fgGuiStyleContent::setEffect(const std::string& effect) 
{
	m_effect = effect;
	return (*this);
}
