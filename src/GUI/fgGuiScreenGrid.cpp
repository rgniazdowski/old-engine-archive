/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "Hardware/fgHardwareState.h"

#include "fgGuiScreenGrid.h"

const float fg::gui::CScreenGrid::DEFAULT_GRID_H = 40.0f;

template <>
bool CSingleton<fg::gui::CScreenGrid>::instanceFlag = false;

template <>
fg::gui::CScreenGrid *CSingleton<fg::gui::CScreenGrid>::instance = NULL;

using namespace fg;

gui::CScreenGrid::CScreenGrid() {
    /**
     * The most common resolutions for smartphones old and new ones, including tablets
     *
     * 240x320		0,75		Width < height -> PORTRAIT else LANDSCAPE -> a way to discover orientation (not perfect)
     * 320x480		0,6666666
     * 480x640		0,75
     * 480x800		0,6
     * 480x848		0,566
     * 480x854		0,562060
     * 640x960		0,6666666
     * 600x1024		0,5859375
     * 728x1024		0,7109375
     * 720x1280		0,5625
     * 2048�1536	1,3333333
     * 1536x2048	0,75
     *
     * Default orientation for the game is PORTRAIT
     * Now there are some problems with changes of orientation when using OpenGL with Moblet
     * (experienced crash after enabling dynamic orientation)
     *
     * Possible solution is to display the game always in PORTRAIT orientation and change the display (positions and sizes of elements)
     * and GL viewport after checking the gyroscope and accelerator data so the game appears in LANDSCAPE orientation
     *
     * It would work and no reload/reprocessing of textures would be needed (? if it's normally needed while changing orientation - no info on this in mosync docs
     * however not reloading/reinit of gl after change of orientation could be the reason of the crash mentioned before, not sure)
     */
    if(FG_HardwareState->getScreenWidth() < FG_HardwareState->getScreenHeight()) {
        minSize = (float)FG_HardwareState->getScreenWidth();
        maxSize = (float)FG_HardwareState->getScreenHeight();
        aspectRatio = maxSize / minSize;
        aspectRatioI = minSize / maxSize;
        // FIXME
        // screenOrientation = SCREEN_FG_ORIENTATION_PORTRAIT;

        screenGridH = DEFAULT_GRID_H;
        gridCellSize = maxSize / screenGridH;
        screenGridW = minSize / gridCellSize;
        screenGridW = floorf((float)screenGridW);
        screenGridX = (int)screenGridW;
        screenGridY = (int)screenGridH;
    } else {
        minSize = (float)FG_HardwareState->getScreenHeight();
        maxSize = (float)FG_HardwareState->getScreenWidth();
        aspectRatio = maxSize / minSize;
        aspectRatioI = minSize / maxSize;
        // FIXME
        // screenOrientation = SCREEN_FG_ORIENTATION_LANDSCAPE;

        gridCellSize = maxSize / screenGridH;

        /*
         * For now application is for PORTRAIT orientation only ! (FIXME)
         */
    }
}

float gui::CScreenGrid::transformToPixels(int grid_position) const {
    if(grid_position < 0)
        grid_position = 0;
    return (float)grid_position * gridCellSize;
}

float gui::CScreenGrid::transformToPixels(float grid_position) const {
    if(grid_position < 0.0f)
        grid_position = 0.0f;
    return (float)grid_position * gridCellSize;
}

Vector2f gui::CScreenGrid::transform(Vector2f grid_position) const {
    return CScreenGrid::transform(grid_position.x, grid_position.y);
}

Vector2f gui::CScreenGrid::transform(float grid_position_x, float grid_position_y) const {
    Vector2f transformed;
    transformed.x = (float)transformToPixels(grid_position_x);
    transformed.y = (float)transformToPixels(grid_position_y);
    return transformed;
}
