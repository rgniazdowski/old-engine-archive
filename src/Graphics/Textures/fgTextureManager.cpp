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

static fgTextureResource *tutorial_images[4] = { NULL, NULL, NULL, NULL };

static fgTextureResource *backgroundTex = NULL;
static fgTextureResource *arrow1Tex = NULL;
static fgTextureResource *blockTex = NULL;
static fgTextureResource *pulseTexture = NULL;
static fgTextureResource *font1Texture = NULL;
static fgTextureResource *font2Texture = NULL;
static fgTextureResource *levelTexture = NULL;

static fgTextureResource *skyboxTex = NULL;

static fgTextureResource *particleTextures[10] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
static fgTextureResource *hudTextures[5] = { NULL, NULL, NULL, NULL, NULL };

#define LAST_TEX_ID (Tex::NUM_TEXTURES-1)

std::map<int, fgTextureResource **> allTex;
template <>
bool fgSingleton<fgTextureManager>::instanceFlag = false;
template <>
fgTextureManager *fgSingleton<fgTextureManager>::instance = NULL;

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
 * Private destructor
 */
fgTextureManager::~fgTextureManager() {
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
        delete facadeReference( Tex::ID(i) );
        facadeReference( Tex::ID(i) ) = NULL;
    }
}

/**
 * LOAD from disk
 */
bool fgTextureManager::allToRAM( bool force ) {
    bool result = true;

    // DISK -> RAM (fgTexture object)
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
        result &= loadTexture( Tex::ID(i), force );
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

    return result;
}

/**
 * Releases all NonGl (i.e. non VRAM) data
 */
void fgTextureManager::allReleaseNonGl() {
    // RAM -> VRAM
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
		facadeReference ( Tex::ID(i) ) -> releaseNonGFX();
       // facadeReference ( Tex::ID(i) ) -> setAllowDoubleInit();
    }
}

/**
 * Releases all OpenGl (i.e. texture ids) data
 */
void fgTextureManager::allReleaseGl() {
    // RAM -> VRAM
    for ( int i = 0; i <= LAST_TEX_ID; i++ ) {
		//facadeReference ( Tex::ID(i) ) -> releaseGFX();
		GLuint &idRef = facadeReference ( Tex::ID(i) )->getRefGLTextureID();
		if( idRef != 0 )
		{
			glDeleteTextures(1, &idRef);
			idRef = 0;
			facadeReference ( Tex::ID(i) )->setGLTextureID(0);
		}
		if( idRef ) {
			//FG_ErrorLog("Inconsistent data! [mode=%d] Non-NULL value in m_ucdata[%p] or m_img[%p] or m_texId[%d]", m_mode, m_ucdata, m_img, m_texId);
		}
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
        tex_facade = new fgTextureResource();
    }

    if ( NULL == tex_facade ) {
        FG_ErrorLog("Allocating memory for texture [%d] failed", TEX_ID);
        return false;
    }

    // fgTexture has data loaded into RAM,
    // and force option demands its reload
    if ( force && tex_facade->hasOwnedRAM() ) {
        tex_facade->releaseNonGFX();
    }
#if 0
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
#endif
    return true;
}

/**
 * Uploads image to VRAM as a texture
 *
 * TODO: mozliwa jest optymalizacja: gdy wymiary tekstury
 * uploadowanej drugi raz sa takie same, mozna uzyc
 * glTexSubImage2D zamiast glTexImage2D
 */
bool fgTextureManager::makeTexture( Tex::ID TEX_ID ) {
    PfgTexture & tex_facade = facadeReference ( TEX_ID );

    if ( NULL == tex_facade ) {
        FG_ErrorLog("Cannot makeTexture() - facade is NULL");
        return false;
    }

    // Supports creation of texture, and update of texture
	/*if ( !tex_facade->makeGFXTexture() ) {
		FG_ErrorLog("Making texture [%d] failed", TEX_ID);
		return false;
	}*/

	if( ! tex_facade->getRawData() ) {
        FG_ErrorLog("makeTexture() called when m_ucdata is NULL");
        return false;
    }
	GLuint &idRef = tex_facade->getRefGLTextureID();

    glEnable(GL_TEXTURE_2D);

    // Generate texture object ONLY IF NEEDED
	if( !idRef ) {
        glGenTextures(1, &idRef);
       // if(!checkGlError("glGenTextures")) {
       //     return false;
       // }
    }

    glBindTexture(GL_TEXTURE_2D, idRef);
    //if(!checkGlError("glBindTexture")) {
    //    return false;
    //}

    // Disable mipmapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //if(!checkGlError("[various GL]")) {
    //    return false;
    //}

	// #TODO
	// #FIXME check for quick pixel format in/out

    // Upload
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_facade->getWidth(), tex_facade->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_facade->getRawData());
    //if(!checkGlError("glTexImage2D")) {
    //    return false;
    //}

    // FIXME should truly do this
    //if( 0 && tex_facade->mode() == fgTextureResource::TEXTURE )
	//	tex_facade->releaseNonGFX();

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

