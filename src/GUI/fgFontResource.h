/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_FONT_RESOURCE_H_
#define _FG_FONT_RESOURCE_H_

#include "../fgCommon.h"

#include "../Graphics/fgGFXTypes.h"

#include "../Graphics/Textures/fgTextureResource.h"
#include "../Graphics/Textures/fgTextureCommon.h"

class fgFont
{
private:
	fgTexture* m_texture;
	int m_step;
	bool m_isLoaded;
	int m_space[256][2];
	fgColor m_color; // FIXME
	Area m_fontArea;
	bool m_isFontAreaDefault;
public:
	fgFont();
	fgFont(Tex::ID FONT_ID); // FIXME
	~fgFont();

	int step(void) const {
		return m_step;
	}

	void setFontArea(Area *area);
	void setFontAreaDefault(void);

    void setColor(uint8 r, uint8 g, uint8 b) {
		m_color.r = r;
		m_color.g = g;
		m_color.b = b;
	}

	void setColor(fgColor color) {
		m_color.r = color.r;
		m_color.g = color.g;
		m_color.b = color.b;
	}

	void setColorDefault(void) {
		setColor(255, 255, 255);
		setAlphaDefault();
	}

    void setAlpha(uint8 alpha) {
		m_color.a = alpha;
	}
	void setAlphaDefault(void)
	{
		m_color.a = 255;
	}

    bool load(Tex::ID FONT_ID);

    float width(float size, const char *string, ...);
    float height(float size, const char *string, ...);

    float placeChar(float x0, float y0, float char_size, char letter, void *inmat);

    int print(float x, float y, float size, const char *string, ...);
    int printCenter(float y, float size, const char *string, ...);

    int printLeft(float y, float size, const char *string, ...);
    int printRight(float y, float size, const char *string, ...);

};

#endif /* _FONTFACADE_H */
