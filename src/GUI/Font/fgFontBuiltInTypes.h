/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

/* // Example usage:

static stb_fontchar fontdata[STB_SOMEFONT_NUM_CHARS];

static void init(void)
{
    // optionally replace both STB_SOMEFONT_BITMAP_HEIGHT with STB_SOMEFONT_BITMAP_HEIGHT_POW2
    static unsigned char fontpixels[STB_SOMEFONT_BITMAP_HEIGHT][STB_SOMEFONT_BITMAP_WIDTH];
    STB_SOMEFONT_CREATE(fontdata, fontpixels, STB_SOMEFONT_BITMAP_HEIGHT);
    ... create texture ...
    // for best results rendering 1:1 pixels texels, use nearest-neighbor sampling
    // if allowed to scale up, use bilerp
}

// This function positions characters on integer coordinates, and assumes 1:1 texels to pixels
// Appropriate if nearest-neighbor sampling is used
static void draw_string_integer(int x, int y, char *str) // draw with top-left point x,y
{
    ... use texture ...
    ... turn on alpha blending and gamma-correct alpha blending ...
    glBegin(GL_QUADS);
    while (*str) {
        int char_codepoint = *str++;
        stb_fontchar *cd = &fontdata[char_codepoint - STB_SOMEFONT_FIRST_CHAR];
        glTexCoord2f(cd->s0, cd->t0); glVertex2i(x + cd->x0, y + cd->y0);
        glTexCoord2f(cd->s1, cd->t0); glVertex2i(x + cd->x1, y + cd->y0);
        glTexCoord2f(cd->s1, cd->t1); glVertex2i(x + cd->x1, y + cd->y1);
        glTexCoord2f(cd->s0, cd->t1); glVertex2i(x + cd->x0, y + cd->y1);
        // if bilerping, in D3D9 you'll need a half-pixel offset here for 1:1 to behave correct
        x += cd->advance_int;
    }
    glEnd();
}

// This function positions characters on float coordinates, and doesn't require 1:1 texels to pixels
// Appropriate if bilinear filtering is used
static void draw_string_float(float x, float y, char *str) // draw with top-left point x,y
{
    ... use texture ...
    ... turn on alpha blending and gamma-correct alpha blending ...
    glBegin(GL_QUADS);
    while (*str) {
        int char_codepoint = *str++;
        stb_fontchar *cd = &fontdata[char_codepoint - STB_SOMEFONT_FIRST_CHAR];
        glTexCoord2f(cd->s0f, cd->t0f); glVertex2f(x + cd->x0f, y + cd->y0f);
        glTexCoord2f(cd->s1f, cd->t0f); glVertex2f(x + cd->x1f, y + cd->y0f);
        glTexCoord2f(cd->s1f, cd->t1f); glVertex2f(x + cd->x1f, y + cd->y1f);
        glTexCoord2f(cd->s0f, cd->t1f); glVertex2f(x + cd->x0f, y + cd->y1f);
        // if bilerping, in D3D9 you'll need a half-pixel offset here for 1:1 to behave correct
        x += cd->advance;
    }
    glEnd();
}
*/

#ifndef _FG_FONT_BUILT_IN_TYPES_H_
#define _FG_FONT_BUILT_IN_TYPES_H_

#ifndef __cplusplus
#define NULL ((void *)0)
#else
#define NULL 0
#endif

#include "Util/fgMemory.h"
#include "Math/fgMathLib.h"
#include <string>

/*
 *
 */
struct fgFontBuiltInRawData {
	/// Name of the font - used in resource
	std::string name;
	/// X position data
	signed short *xPtr;
	/// X position data
	signed short *yPtr;
	/// X size data
	unsigned short *wPtr;
	/// Y size data
	unsigned short *hPtr;
	/// Texture coord data
	unsigned short *sPtr;
	/// Texture coord data
	unsigned short *tPtr;
	/// Advance/step data
	unsigned short *aPtr;
	/// Pixel raw data
	unsigned int *bitsPtr;
	/// Data width
	unsigned int width;
	/// Data height
	unsigned int height;
	/// Height POW2
	unsigned int heightPOW2;
	/// Offset of the first character in data
	unsigned int firstChar;
	/// Number of characters in data
	unsigned int numChars;
	

	//
	fgFontBuiltInRawData() :
		name(),
		xPtr(NULL),
		yPtr(NULL),
		wPtr(NULL),
		hPtr(NULL),
		sPtr(NULL),
		tPtr(NULL),
		aPtr(NULL),
		bitsPtr(NULL),
		width(0),
		height(0),
		heightPOW2(0),
		firstChar(0),
		numChars(0) {
	}
};

/*
 *
 */
struct fgFontCharInfo
{
    // coordinates if using floating positioning
	fgVec2f uv1f;
	fgVec2f uv2f;
	fgVec2f p0f;
	fgVec2f p1f;
    float stepf;

    // coordinates if using integer positioning
	fgVec2f uv1i;
	fgVec2f uv2i;
	fgVec2i p0i;
	fgVec2i p1i;
    int   stepi;
};



/*
 *
 */
struct fgFontDataInfo
{
	///
	fgFontCharInfo *charInfo;
	///
	unsigned int firstChar;
	///
	unsigned int numChars;

	fgFontDataInfo() : 
		charInfo(NULL),
		firstChar(0),
		numChars(0)
	{

	}

	void destroy(void) {
		if(charInfo) {
			fgFree(charInfo);
		}
		charInfo = NULL;
		numChars = 0;
		firstChar = 0;
	}
};

#endif /* _FG_FONT_BUILT_IN_TYPES_H_ */
