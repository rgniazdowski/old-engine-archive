/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include <map>

#include "../../fgCommon.h"
#include "../../Hardware/fgQualityManager.h"

#include "fgTextureCommon.h"
#include "fgTextureResource.h"
#include "fgTextureManager.h"


// FIXME
// This file is somehow retarded because the whole texture loading procedure is hardcoded - texture files and pointer holders are defined upfront - well in game engine it is
// unacceptable as file paths and string IDs need to be placed in configuration files (ie. XMLs)
//
// This file will be changed and fgTextureManager will hold handles (FG_RHANDLE) to texture resources placed in fgResourceManager
// well the question is this is really necessary - time will show


static fgTexture *tutorial_images[4] = { NULL, NULL, NULL, NULL };

static fgTexture *backgroundTex = NULL;
static fgTexture *arrow1Tex = NULL;
static fgTexture *blockTex = NULL;
static fgTexture *pulseTexture = NULL;
static fgTexture *font1Texture = NULL;
static fgTexture *font2Texture = NULL;
static fgTexture *levelTexture = NULL;

static fgTexture *skyboxTex = NULL;

static fgTexture *particleTextures[10] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
static fgTexture *hudTextures[5] = { NULL, NULL, NULL, NULL, NULL };

/*
 * The Texture Identifiers (TextureCommon.h) - the same as positions in allTex array:
 *
 */

#define LAST_TEX_ID (Tex::NUM_TEXTURES-1)

fgTexture **thumbnailTex = NULL;
static int numThumbnails = 0;

std::map<int, fgTexture **> allTex;

template <>
bool fgSingleton<fgTextureManager>::instanceFlag = false;

template <>
fgTextureManager *fgSingleton<fgTextureManager>::instance = NULL;

//
// MARK: -
// MARK: Initializers & destroyers
//

/**
 * Private constructor
 */
fgTextureManager::fgTextureManager() {
	FG_WriteLog("Preparing allTex array");
	allTex[Tex::BACKGROUND_TEXTURE]		= &backgroundTex;	// BACKGROUND_TEXTURE
    allTex[Tex::PULSE_TEXTURE]			= &pulseTexture;	// PULSE_TEXTURE (1x1)
	allTex[Tex::DEBRIS_SHEET_TEXTURE]	= &particleTextures[0];	// DEBRIS_SHEET_TEXTURE (3x3)
	allTex[Tex::FLAME_SHEET_TEXTURE]	= &particleTextures[1]; // FLAME_SHEET_TEXTURE (2x2)
	allTex[Tex::FLASH_SHEET_TEXTURE]	= &particleTextures[2];	// FLASH_SHEET_TEXTURE (2x2)
	allTex[Tex::SMOKETRAIL_TEXTURE]		= &particleTextures[3];	// SMOKETRAIL_TEXTURE  (1x1)
	allTex[Tex::ROUNDSPARK_TEXTURE]		= &particleTextures[4]; // ROUNDSPARK_TEXTURE	(1x1)
	allTex[Tex::SHOCKWAVE_TEXTURE]		= &particleTextures[5]; // SHOCKWAVE_TEXTURE	(1x1)
	allTex[Tex::SPARK_TEXTURE]			= &particleTextures[6];	// SPARK_TEXTURE (1x1)
	allTex[Tex::EXPLOSION_SEQUENCE_TEXTURE] = &particleTextures[7]; // EXPLOSION_SEQUENCE_TEXTURE (8x8 -> 8x6)
	allTex[Tex::FIRE_SEQUENCE_TEXTURE]	= &particleTextures[8];	// FIRE_SEQUENCE_TEXTURE (5x5)
	allTex[Tex::SKYBOX_TEXTURE]			= &skyboxTex;			// SKYBOX_TEXTURE (4x4)
	allTex[Tex::HUD_BOTTOM_TEXTURE]		= &hudTextures[0];		// HUD_BOTTOM_TEXTURE
	allTex[Tex::HUD_CENTER_TEXTURE]		= &hudTextures[1];		// HUD_CENTER_TEXTURE
	allTex[Tex::HUD_LINES_TEXTURE]		= &hudTextures[2];		// HUD_LINES_TEXTURE
	allTex[Tex::HUD_TOP_TEXTURE]		= &hudTextures[3];		// HUD_TOP_TEXTURE
	allTex[Tex::LEVEL_TEXTURE]			= &levelTexture;	// LEVEL_TEXTURE
    allTex[Tex::FONT_MAIN_TEXTURE]		= &font1Texture;	// FONT_MAIN_TEXTURE / FONT1
	allTex[Tex::FONT_SECONDARY_TEXTURE] = &font2Texture;	// FONT_SECONDARY_TEXTURE / FONT2

	//Tex::NUM_TEXTURES
}

/**
 * Set the number of thumbnails used in the game
 */
void fgTextureManager::setThumbnailsCount(int num_thumbnails)
{
	if(thumbnailTex)
	{
		delete [] thumbnailTex;
		thumbnailTex = NULL;
	}
	if(thumbnailTex == NULL)
	{
		thumbnailTex = new fgTexture *[num_thumbnails];
		numThumbnails = num_thumbnails;
		for(int i=0;i<num_thumbnails;i++)
		{
			thumbnailTex[i] = NULL;
			allTex[getThumbnailTextureID(i)] = &thumbnailTex[i];
			FG_WriteLog("allTex[%d] is %p", getThumbnailTextureID(i), allTex[getThumbnailTextureID(i)]);
		}
	}
}

/**
 * Getting the texture ID for the thumbnail
 */
int fgTextureManager::getThumbnailTextureID(int thumbnail_id)
{
	// The thumbnail ID is counted from zero so
	// the texture ID for given thumbnail is:
	return Tex::NUM_TEXTURES+thumbnail_id;
}

/**
 * Private destructor
 */
fgTextureManager::~fgTextureManager() {
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
        delete facadeReference( Tex::ID(i) );
        facadeReference( Tex::ID(i) ) = NULL;
    }
    // Deleting the thumbnails
	for(int i=0;i<numThumbnails;i++) {
		delete facadeReference( Tex::ID(getThumbnailTextureID(i)) );
        facadeReference( Tex::ID(getThumbnailTextureID(i)) ) = NULL;
	}

	delete [] thumbnailTex;
	thumbnailTex = NULL;
}

//
// MARK: -
// MARK: Business
//

/**
 * LOAD from disk
 */
bool fgTextureManager::allToRAM( bool force ) {
    bool result = true;

    // DISK -> RAM (fgTexture object)
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
        result &= loadTexture( Tex::ID(i), force );
    }
	for(int i=0;i<numThumbnails;i++) {
		result &= loadTexture( Tex::ID(getThumbnailTextureID(i)), force );
	}
    return result;
}

/**
 * UPLOAD to VRAM – skips reload from disk ONLY if possible
 */
bool fgTextureManager::allToVRAM( bool force ) {
    bool result = true;

    // Ensure textures are loaded into RAM
    allToRAM(force);

    // RAM -> VRAM
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
        result &= makeTexture( Tex::ID(i) );
    }
	for(int i=0;i<numThumbnails;i++) {
		result &= makeTexture( Tex::ID(getThumbnailTextureID(i)) );
	}

    return result;
}

/**
 * Releases all NonGl (i.e. non VRAM) data
 */
void fgTextureManager::allReleaseNonGl() {
    // RAM -> VRAM
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
        facadeReference ( Tex::ID(i) ) -> releaseNonGl();
        facadeReference ( Tex::ID(i) ) -> setAllowDoubleInit();
    }
	for(int i=0;i<numThumbnails;i++) {
		facadeReference ( Tex::ID(getThumbnailTextureID(i)) ) -> releaseNonGl();
        facadeReference ( Tex::ID(getThumbnailTextureID(i)) ) -> setAllowDoubleInit();
	}
}

/**
 * Releases all OpenGl (i.e. texture ids) data
 */
void fgTextureManager::allReleaseGl() {
    // RAM -> VRAM
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
        facadeReference ( Tex::ID(i) ) -> releaseGl();
    }
	for(int i=0;i<numThumbnails;i++) {
		facadeReference ( Tex::ID(getThumbnailTextureID(i)) ) -> releaseGl();
	}
}

/**
 * Load from DISK to RAM – if not loaded already – or if force = true
 */
bool fgTextureManager::loadTexture( Tex::ID TEX_ID, bool force ) {

    // This changes pointer-to-pointer, into
    // reference-to-pointer -> so that we can write
    // to backgroundTex, arrow1Tex, etc. variables
    PfgTexture & tex_facade = facadeReference ( TEX_ID );

    if ( NULL == tex_facade ) {
        tex_facade = new fgTexture();
    }

    if ( NULL == tex_facade ) {
        FG_ErrorLog("Allocating memory for texture [%d] failed", TEX_ID);
        return false;
    }

    // fgTexture has data loaded into RAM,
    // and force option demands its reload
    if ( force && tex_facade->hasOwnedRAM() ) {
        tex_facade->releaseNonGl();
    }

    if ( force || !tex_facade->hasOwnedRAM() ) {
        if ( isFont(TEX_ID) ) {
            /// FONT
            if ( !tex_facade->prepareTgaFromFile( fgQualityManager::getInstance()->getFileName(TEX_ID).c_str()) ) {
                FG_ErrorLog("Loading font [%d] UCDATA failed", TEX_ID);
                return false;
            }
        } else {
            /// REGULAR TEXTURE
            if ( !tex_facade->loadFromFile(fgQualityManager::getInstance()->getFileName(TEX_ID).c_str()) ) {
                FG_ErrorLog("Loading texture [%d] failed", TEX_ID);
                return false;
            }
        }
    }

    return true;
}

/**
 * Uploads to VRAM
 */
bool fgTextureManager::makeTexture( Tex::ID TEX_ID ) {
    PfgTexture & tex_facade = facadeReference ( TEX_ID );

    if ( NULL == tex_facade ) {
        FG_ErrorLog("Cannot makeTexture() - facade is NULL");
        return false;
    }

    // Supports creation of texture, and update of texture
	if ( !tex_facade->makeTexture() ) {
		FG_ErrorLog("Making texture [%d] failed", TEX_ID);
		return false;
	}

    // FIXME should truly do this
    if( 0 && tex_facade->mode() == fgTexture::TEXTURE )
        tex_facade->releaseNonGl();

    return true;
}

/**
 * Gets reference to THE variable holding texture (one and only for the TEX_ID)
 */
PfgTexture & fgTextureManager::facadeReference( Tex::ID TEX_ID ) {
    // This changes pointer-to-pointer, into
    // reference-to-pointer -> so that we can write
    // to backgroundTex, arrow1Tex, etc. variables
    PfgTexture & tex_facade = *allTex[TEX_ID];

    return tex_facade;
}

