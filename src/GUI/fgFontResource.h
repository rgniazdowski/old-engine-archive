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
#include "../fgResource.h"

#include "../Graphics/fgGFXTypes.h"
#include "../Graphics/Textures/fgTextureResource.h"

// This is standard grid size (used for fonts based on textures)
#define FG_FONT_STANDARD_GRID_SIZE	16
#define FG_FONT_STANDARD_ASCII_SIZE	(FG_FONT_STANDARD_GRID_SIZE*FG_FONT_STANDARD_GRID_SIZE)

/*
 *
 */
class fgFontResource : public fgTextureResource
{
public:
	// Base constructor of the font resource object
	fgFontResource()	{  clear();  }
	// Base constructor with additional parameter (path)
	fgFontResource(const char *path) { clear(); setFilePath(path); };
	// Base constructor with additional parameter (path)
	fgFontResource(std::string& path) { clear(); setFilePath(path); };
	// Base destructor of the font resource object
	~fgFontResource()	{ destroy(); }

	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear(void);
	// Create function loads/interprets data from file in ROM and place it in RAM memory.
	virtual bool create(void);
	// Destroy all loaded data including additional metadata (called with deconstructor)
	virtual void destroy(void);
	// Reloads any data, recreates the resource (refresh)
	virtual bool recreate(void);
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose(void);
	// Check if resource is disposed (not loaded yet or disposed after)
	virtual bool isDisposed(void) const;

#if 0
	// #FIXME (!) well this should not be here
	// area and color are something dynamic - what's the point to
	// set those parameters at every frame draw? (! omg !)
	// This is font resource, drawing should be somewhere else - FontDrawer
	// Besides, there was an idea to create static fonts - something similar
	// to call lists in GL. Static definition of the test to be drawn later.
	// #TODO #P2
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
#endif
#if 0
	// #FIXME
    bool load(Tex::ID FONT_ID);

	/* ALL TO HELL ! ! ! ! #FIXME #TODO */
    float width(float size, const char *string, ...);
    float height(float size, const char *string, ...);

    float placeChar(float x0, float y0, float char_size, char letter, void *inmat);

    int print(float x, float y, float size, const char *string, ...);
    int printCenter(float y, float size, const char *string, ...);

    int printLeft(float y, float size, const char *string, ...);
    int printRight(float y, float size, const char *string, ...);
#endif 
	int getStep(void) const {
		return m_step;
	}
private:
	int m_step;
	int m_space[FG_FONT_STANDARD_ASCII_SIZE][2];
};

#endif /* _FG_FONT_RESOURCE_H_ */
