/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

// #FIXME - this actually needs small fixes - however the idea is quite good and will be useful for
// developing and creating interface - screen grid is just fixed a size of screen in blocks - where
// size of the particular block will depend on the screen resolution - fixes are needed for proper
// aspect ratio / orientation and dpi handling so the layout of menus will never broke when different
// resolution / platform is used

#ifndef _FG_GUI_SCREEN_GRID_H_
#define _FG_GUI_SCREEN_GRID_H_

#include "../Math/fgMathLib.h"
#include "../fgSingleton.h"

class fgGuiScreenGrid : fgSingleton<fgGuiScreenGrid>
{
	friend class fgSingleton<fgGuiScreenGrid>;
private:
	/* By default maximum screen grid height is 40
	   this makes positioning of the screen elements quite easier */
	static const float DEFAULT_GRID_H;
	/* This currently is just a dummy - game will support only portrait orientation */
	int screenOrientation;
	/* Aspect ratio - larger value divided by smaller value -  aspect > 1.0f */
	float aspectRatio;
	/* Reversed aspect ratio - smaller value divided by larger value (of the screen size in pixels) */
	float aspectRatioI;
	/* This holds the smaller size of the screen (if the orientation is portrait it will hold the screen width) */
	float minSize;
	/* This holds the larger size of the screen */
	float maxSize;
	/* Indicates the screen block size (the block is square) */
	float gridCellSize;
	/* Indicates the screen width in blocks */
	float screenGridW;
	/* Indicates the screen height in blocks (by default 40.0f) */
	float screenGridH;
	/* The same as above but stored as integer */
	int screenGridX;
	int screenGridY;

protected:
		fgGuiScreenGrid();
		~fgGuiScreenGrid();
public:

		float getAspectRatio(void) const {
			return aspectRatio;
		}
		float getScreenGridW(void) const {
			return screenGridW;
		}
		float getScreenGridH(void) const {
			return screenGridH;
		}
		float getMinSize(void) const {
			return minSize;
		}
		float getMaxSize(void) const {
			return maxSize;
		}
		float getGridCellSize(void) const {
			return gridCellSize;
		}
		float cellSize(void) const {
			return gridCellSize;
		}

		float transformToPixels(int grid_position) const;
		float transformToPixels(float grid_position) const;

		fgVector2f transform(fgVector2f grid_position) const;
		fgVector2f transform(float grid_position_x, float grid_position_y) const;
};

#define SCREEN_TRANSFORM(POS) fgGuiScreenGrid::getInstance()->transformToPixels(POS)
#define SCREEN_TRANSFORM_POS(STRUCT_) fgGuiScreenGrid::getInstance()->transform(STRUCT_)
#define SCREEN_TRANSFORM_2D(POSX, POSY) fgGuiScreenGrid::getInstance()->transform(POSX, POSY)

#define FG_GuiScreenGrid	fgGuiScreenGrid::getInstance();

#endif /* _FG_GUI_SCREEN_GRID_H_ */

