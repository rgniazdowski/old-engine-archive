/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFontDrawer.h"
#include "GFX/fgGFXPrimitives.h"
#include "GFX/Shaders/fgGFXShaderManager.h"

/*
 *
 */
fgFontDrawer::fgFontDrawer() :
	m_currentFont(NULL),
	m_color(1.0f, 1.0f, 1.0f, 1.0f),
	m_relMove(0.0f, 0.0f, 0.0f),
	m_printMode(FG_FONT_PRINT_MODE_ABSOLUTE)
{
}

/*
 *
 */
fgFontDrawer::~fgFontDrawer()
{
}

/*
 *
 */
void fgFontDrawer::setShaderManager(fgManagerBase *shaderMgr)
{
	fgGfxDrawingBatch::setShaderManager(shaderMgr);
}

/*
 *
 */
int fgFontDrawer::print(float x0, float y0, float charSize, const char *fmt, ...)
{
	if(!m_currentFont || !fmt)
		return 0;
	char buf[FG_FONT_DRAW_STRING_BUF_MAX];
	va_list args;

	va_start(args, fmt);
	vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX-1, fmt, args);
	va_end(args);
	buf[FG_FONT_DRAW_STRING_BUF_MAX-1] = '\0';

	return print(x0, y0, buf, charSize);
}

/*
 *
 */
int fgFontDrawer::print(float charSize, const char *fmt, ...)
{
	if(!m_currentFont || !fmt)
		return 0;
	char buf[FG_FONT_DRAW_STRING_BUF_MAX];
	va_list args;

	va_start(args, fmt);
	vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX-1, fmt, args);
	va_end(args);
	buf[FG_FONT_DRAW_STRING_BUF_MAX-1] = '\0';

	return print(0.0f, 0.0f, buf, charSize);
}

/*
 *
 */
int fgFontDrawer::print(const char *string, float charSize)
{
	return print(0.0f, 0.0f, string, charSize);
}

/*
 *
 */
int fgFontDrawer::print(float x0, float y0, const char *string, float charSize)
{
	if(!m_currentFont || !string)
		return 0;
	// main
	float scale;
	int n = 0;
	const char *s = NULL;
	float x=x0,y=y0;
	fgBool rewind = FG_FALSE;
	if(charSize <= 0.0f)
		charSize = (float)m_currentFont->getStep();
	scale = charSize/(float)m_currentFont->getStep(); // ? is it needed?
	if(m_printMode == FG_FONT_PRINT_MODE_ABSOLUTE && 0) {
		x+=m_relMove.x;
		y+=m_relMove.y;
		m_relMove.x = -x0;
		m_relMove.y = -y0;
	} else {
		m_relMove = fgVector3f(0.0f, 0.0f, 0.0f);
	}
	float w = 0.0f;
	for(s=string, n=0; *s; s++)
	{
		n++;
        if(*s == '\n') {
			y+=charSize/16.0f;
			rewind = FG_TRUE;
			x = 0.0f;
		} else if( *s == ' ' ) {
			x+=charSize/3.0f;
			w+=charSize/3.0f;
		} else {
			float xMove = placeChar(x, y, *s, rewind, charSize);
			w+=xMove;
			x+=xMove;
			//x=0.0f; y=0.0f;
			rewind = FG_FALSE;
		}
	}
	if(m_printMode == FG_FONT_PRINT_MODE_ABSOLUTE) {
		//m_relMove.x -= w;
	}
	return n;
}

/*
 * Clears the buffer (no drawing is performed)
 */
void fgFontDrawer::flush(void)
{
	fgGfxDrawingBatch::flush();
	m_relMove = fgVector3f(0.0f, 0.0f, 0.0f);
}

/*
 *
 */
void fgFontDrawer::render(void)
{
	fgGfxDrawingBatch::render();
}

/*
 *
 */
void fgFontDrawer::setColor(const fgColor4f &color)
{
	m_color = color;
	fgGfxDrawCall *drawCall = fgGfxDrawingBatch::getLastDrawCall();
	if(drawCall) {
		drawCall->setColor(m_color);
	}
}

/*
 *
 */
void fgFontDrawer::setColor(const fgColor3f &color)
{
	m_color = fgColor4f(color.r, color.g, color.g, 1.0f);
	fgGfxDrawCall *drawCall = fgGfxDrawingBatch::getLastDrawCall();
	if(drawCall) {
		drawCall->setColor(m_color);
	}
}

/*
 *
 */
void fgFontDrawer::setColor(void)
{
	m_color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	fgGfxDrawCall *drawCall = fgGfxDrawingBatch::getLastDrawCall();
	if(drawCall) {
		drawCall->setColor(m_color);
	}
}

/*
 *
 */
fgGfxDrawCall *fgFontDrawer::setupDrawCall(fgTextureResource *texture)
{
	int index;
	fgGfxDrawCall *drawCall = fgGfxDrawingBatch::createDrawCall(index);
	drawCall->setColor(m_color);
	drawCall->setTexture(texture);	
	drawCall->setPrimitiveMode(FG_GFX_TRIANGLES);
	drawCall->setComponentActive(0);
	drawCall->setComponentActive(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT);
	drawCall->setDrawAppendMode(FG_GFX_DRAW_APPEND_ABSOLUTE);
	return drawCall;
}

/*
 *
 */
fgBool fgFontDrawer::setFont(fgFontResource *font)
{
	if(!font)
		return FG_FALSE;
	if(m_currentFont != font) {
		m_currentFont = font;
		setupDrawCall(m_currentFont);
	}
	return FG_TRUE;
}

/*
 *
 */
fgFontResource *fgFontDrawer::getFont(void) const
{
	return m_currentFont;
}

/*
 * This will flush the data, reset the fontHandle, clear cache etc
 */
void fgFontDrawer::reset(void)
{
	fgFontDrawer::flush();
	m_currentFont = NULL;
	m_relMove = fgVector3f(0.0f, 0.0f, 0.0f);
}

/*
 *
 */
float fgFontDrawer::placeChar(char letter, fgBool rewind, float charSize)
{
	if(!m_currentFont)
		return 0.0f;
	return placeChar(0.0f, 0.0f, letter, charSize);
}

/*
 *
 */
float fgFontDrawer::placeChar(float xRel0, float yRel0, char letter, fgBool rewind, float charSize)
{
	if(!m_currentFont)
		return 0.0f;
	int x, y, i, size;
	float s,t,ds,dt;
	float scale;
	size = m_currentFont->getWidth();
	i = (int) letter;
	if(charSize <= 0.0f)
		charSize = (float)m_currentFont->getStep();
	scale = charSize/(float)m_currentFont->getStep();

	y = i/16;
	x = i%16;
	s  = (float)x/16.0f+(float)m_currentFont->getSpace(i,0)/(float)size;
	t  = (float)y/16.0f;
	ds = (float)m_currentFont->getSpace(i,1)/(float)size;
	dt = 1.0f/16.0f;
	float size_x = (float)m_currentFont->getSpace(i,1)*scale;
	float size_y = charSize;
	fgVec2f relPos(xRel0, yRel0);
	fgVec2f uv1(s,1.0-t);
	fgVec2f uv2(s+ds,1.0-(t+dt));
	fgVec2f rectSize(size_x, size_y);
	fgGfxDrawCall *drawCall = fgGfxDrawingBatch::getLastDrawCall();
	if(!drawCall) {
		drawCall = setupDrawCall(m_currentFont);
	}
	drawCall->appendRect2D(relPos, rectSize, uv1, uv2, rewind);
	
	//fgGfxPrimitives::appendRect2D(m_buffer, relPos, rectSize, uv1, uv2, FG_GFX_TRIANGLES, rewind);
	return size_x;
}

/*
 *
 */
float fgFontDrawer::width(float charSize, const char *fmt, ...)
{
	if(!m_currentFont)
		return 0.0f;
	char buf[FG_FONT_DRAW_STRING_BUF_MAX];
	va_list args;

	va_start(args, fmt);
	vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX-1, fmt, args);
	va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX-1] = '\0';
	return fgFontDrawer::width(buf, charSize);
}

/*
 *
 */
float fgFontDrawer::width(const char *string, float charSize)
{
	if(!m_currentFont)
		return 0.0f;
	float x = 0.0f;
	const char *s = NULL;
	float scale;
	if(charSize <= 0.0f)
		charSize = (float)m_currentFont->getStep();
	scale = charSize/(float)m_currentFont->getStep();

    // Longest line seen
    float max_x = 0.0f;
	for(s=string; *s; s++) {
		if(*s == ' ') {
            x += 1.0f;
			x += charSize / 3.0f;
		} else if( *s != '\n' ) {
            // Adds size of char
            x += 1.0f;
			x += (float)m_currentFont->getSpace(*(unsigned char*)s, 1)*scale;
		} else {
            x += 1.0f;
            // Processed a new line. Remember its length if long enough
            if( x > max_x ) {
                max_x = x;
            }
            // Prepare for the new line!
            x = 0.0f;
        }
	}
    // Grabs x into max_x if there was no explicit '\n'
    if( x > max_x ) {
        max_x = x;
    }
	return max_x;
}

/*
 *
 */
float fgFontDrawer::height(float charSize, const char *fmt, ...)
{
	if(!m_currentFont)
		return 0.0f;
	char buf[FG_FONT_DRAW_STRING_BUF_MAX];
	va_list args;
	float y = 0.0f;
	if(charSize <= 0.0f)
		charSize = (float)m_currentFont->getStep();

	va_start(args, fmt);
	vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX-1, fmt, args);
	va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX-1] = '\0';

	return fgFontDrawer::height(buf, charSize);
}

/*
 *
 */
float fgFontDrawer::height(const char *string, float charSize)
{
	if(charSize <= 0.0f)
		charSize = (float)m_currentFont->getStep();
	float y = charSize;

    int slen = strlen(string);
	for(int i=0; i<slen; i++)
	{
		if(string[i] == '\n')
			y += charSize;
	}
	return y;
}

/*
 *
 */
fgVector2f fgFontDrawer::size(float charSize, const char *fmt, ...)
{
	if(!m_currentFont)
		return fgVector2f();
	char buf[FG_FONT_DRAW_STRING_BUF_MAX];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, FG_FONT_DRAW_STRING_BUF_MAX-1, fmt, args);
	va_end(args);
    // Index is zero based -> MAX-1 points to last byte in buffer
    buf[FG_FONT_DRAW_STRING_BUF_MAX-1] = '\0';
	return size(buf, charSize);
}

/*
 *
 */
fgVector2f fgFontDrawer::size(const char *string, float charSize)
{
	if(!string)
		return fgVector2f();
	fgVector2f textSize;

	textSize.x = width(string, charSize);
	textSize.y = height(string, charSize);
	return textSize;
}
