/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_TEXTURE_COMMON_H_
#define _FG_TEXTURE_COMMON_H_

namespace Tex {

// FIXME this is a retarded file and shit

enum Quality { QUALITY_LOW, QUALITY_MEDIUM, QUALITY_HIGH };

enum ID {
    /*
	 * GUI / MENU TEXTURES
	 */
    BACKGROUND_TEXTURE = 0,	// background_512.jpg / background_1024.jpg
	//ARROW1_TEXTURE,			// arrow1_32.tga
	//BLOCK_TEXTURE,			// block0.tga
	/*
	 * SPECIAL EFFECTS AND PARTICLES TEXTURES
	 */
    PULSE_TEXTURE,			// shockwave1.tga
	DEBRIS_SHEET_TEXTURE,	// debris0_sheet.tga
	FLAME_SHEET_TEXTURE,	// flame0_sheet.tga
	FLASH_SHEET_TEXTURE,	// flash0_sheet.tga
	SMOKETRAIL_TEXTURE,		// smoketrail0.tga
	ROUNDSPARK_TEXTURE,		// roundspark0.tga
	SHOCKWAVE_TEXTURE,		// shockwave0.tga
	SPARK_TEXTURE,			// spark0.tga
	EXPLOSION_SEQUENCE_TEXTURE, // explosion1_1024.tga
	FIRE_SEQUENCE_TEXTURE,	// fire1_512.tga
	/*
	 * GAME TEXTURES / ENVIRONMENT
	 */
	SKYBOX_TEXTURE,			// galaxy_1024.jpg
	/*
	 * HUD TEXTURES
	 */
	HUD_BOTTOM_TEXTURE,		// hud_bottom_1024.tga	(1024x256)
	HUD_CENTER_TEXTURE,		// hud_center_512.tga	(512x512)
	HUD_LINES_TEXTURE,		// hud_lines_1024.tga	(1024x1024)
	HUD_TOP_TEXTURE,		// hud_top_1024.tga		(1024x128)
	/*
	 * MISC TEXTURES
	 */
    LEVEL_TEXTURE,			// ImageEmpty.tga

    // FONTS ARE DIFFERENT - this is a risky way of storing them
    // The fonts need to be recognized by TextureManager::isFont()
    FONT_MAIN_TEXTURE,
    FONT_SECONDARY_TEXTURE,

    NUM_TEXTURES	// automatic texture count
};

} /* NAMESPACE Tex */

#endif
