/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include <cstdlib>
#include <cmath>
#include <cstring>

#include "fgPsExplosionEffect.h"
#include "../Textures/fgTextureCommon.h"
#include "../Textures/fgTextureManager.h"

/*
 * The default constructor for the particle explosion special effect
 */
ExplosionEffect::ExplosionEffect(ParticleEffect::DrawMode drawMode, float scale)
{
	if(scale <= 0.0f)
		scale = 1.0f;
	m_scale = scale;
	/*
	 * Flame/Smoke Emitter
	 */
	m_flameEmitter = new ParticleEffectLimited();
	m_flameEmitter->setMaxCount(EXPLOSION_FLAME_EMITTER_MAX);
	m_flameEmitter->setAreaCheck(false);
	m_flameEmitter->setAlphaActive(true);
	m_flameEmitter->setDrawMode(drawMode);
	m_flameEmitter->setTexture(TEXTURE_PTR(Tex::FLAME_SHEET_TEXTURE));
	m_flameEmitter->setTextureXSize(2);
	m_flameEmitter->setTextureYSize(2);
	m_flameEmitter->setLifeAsSize(false);
	m_flameEmitter->setParamsActive(true);
	m_flameEmitter->setFacingVelocity(false);

	m_flameEmitter->setStartSize(100.0f*m_scale);
	m_flameEmitter->setEndSize(150.0f*m_scale);

	m_flameEmitter->setStartColor(255,75,0,255);
	m_flameEmitter->setEndColor(128,128,128,0);

	// Life 10.0f is equal to 1000ms TTL so if overall lifespan of the particles should be 500ms...
	m_flameEmitter->setLowLife(7.5f);
	m_flameEmitter->setHighLife(7.5f);

	m_flameEmitter->setSpreadSpeed(75.0f*m_scale);
	
	/*
	 * Flash Emitter
	 */

	m_flashEmitter = new ParticleEffectLimited();
	m_flashEmitter->setMaxCount(EXPLOSION_FLASH_EMITTER_MAX);
	m_flashEmitter->setAreaCheck(false);
	m_flashEmitter->setAlphaActive(true);
	m_flashEmitter->setDrawMode(drawMode);
	m_flashEmitter->setTexture(TEXTURE_PTR(Tex::FLASH_SHEET_TEXTURE));
	m_flashEmitter->setTextureXSize(2);
	m_flashEmitter->setTextureYSize(2);
	m_flashEmitter->setLifeAsSize(false);
	m_flashEmitter->setParamsActive(true);
	m_flashEmitter->setFacingVelocity(false);

	m_flashEmitter->setStartSize(250.0f*m_scale);
	m_flashEmitter->setEndSize(50.0f*m_scale);

	m_flashEmitter->setStartColor(255,255,255,255);
	m_flashEmitter->setEndColor(255,75,0,0);

	m_flashEmitter->setLowLife(1.5f);
	m_flashEmitter->setHighLife(2.5f);

	m_flashEmitter->setSpreadSpeed(0.0f*m_scale);

	/*
	 * Flying Sparks Emitter
	 */

	m_sparksEmitter = new ParticleEffectLimited();
	m_sparksEmitter->setMaxCount(EXPLOSION_SPARKS_EMITTER_MAX);

	m_sparksEmitter->setAreaCheck(false);
	m_sparksEmitter->setAlphaActive(true);
	m_sparksEmitter->setDrawMode(drawMode);
	m_sparksEmitter->setTexture(TEXTURE_PTR(Tex::SPARK_TEXTURE));
	m_sparksEmitter->setTextureXSize(1);
	m_sparksEmitter->setTextureYSize(1);
	m_sparksEmitter->setLifeAsSize(false);
	m_sparksEmitter->setParamsActive(true);
	m_sparksEmitter->setFacingVelocity(true);

	m_sparksEmitter->setStartSize(25.0f*m_scale);
	m_sparksEmitter->setEndSize(55.0f*m_scale);

	m_sparksEmitter->setStartColor(255,255,0,255);
	m_sparksEmitter->setEndColor(255,75,0,0);

	m_sparksEmitter->setLowLife(10.0f);
	m_sparksEmitter->setHighLife(10.0f);

	m_sparksEmitter->setSpreadSpeed(300.0f*m_scale);

	/*
	 * Smoke Trails Emitter
	 */

	m_smokeTrailsEmitter = new ParticleEffectLimited();
	m_smokeTrailsEmitter->setMaxCount(EXPLOSION_SMOKE_TRAILS_EMITTER_MAX);

	m_smokeTrailsEmitter->setAreaCheck(false);
	m_smokeTrailsEmitter->setAlphaActive(true);
	m_smokeTrailsEmitter->setDrawMode(drawMode);
	m_smokeTrailsEmitter->setTexture(TEXTURE_PTR(Tex::SMOKETRAIL_TEXTURE));
	m_smokeTrailsEmitter->setTextureXSize(1);
	m_smokeTrailsEmitter->setTextureYSize(1);
	m_smokeTrailsEmitter->setLifeAsSize(false);
	m_smokeTrailsEmitter->setParamsActive(true);
	m_smokeTrailsEmitter->setFacingVelocity(true);

	m_smokeTrailsEmitter->setStartSize(50.0f*m_scale);
	m_smokeTrailsEmitter->setEndSize(150.0f*m_scale);

	m_smokeTrailsEmitter->setStartColor(255,170,0,255);
	m_smokeTrailsEmitter->setEndColor(255,75,0,0);

	m_smokeTrailsEmitter->setLowLife(5.0f);
	m_smokeTrailsEmitter->setHighLife(7.5f);

	m_smokeTrailsEmitter->setSpreadSpeed(250.0f*m_scale);

	/*
	 * Round Sparks Emitter
	 */

	m_roundSparksEmitter = new ParticleEffectLimited();
	m_roundSparksEmitter->setMaxCount(EXPLOSION_ROUND_SPARKS_EMITTER_MAX);

	m_roundSparksEmitter->setAreaCheck(false);
	m_roundSparksEmitter->setAlphaActive(true);
	m_roundSparksEmitter->setDrawMode(drawMode);
	m_roundSparksEmitter->setTexture(TEXTURE_PTR(Tex::ROUNDSPARK_TEXTURE));
	m_roundSparksEmitter->setTextureXSize(1);
	m_roundSparksEmitter->setTextureYSize(1);
	m_roundSparksEmitter->setLifeAsSize(false);
	m_roundSparksEmitter->setParamsActive(true);
	m_roundSparksEmitter->setFacingVelocity(false);

	m_roundSparksEmitter->setStartSize(100.0f*m_scale);
	m_roundSparksEmitter->setEndSize(250.0f*m_scale);

	m_roundSparksEmitter->setStartColor(255,125,0,255);
	m_roundSparksEmitter->setEndColor(255,75,0,0);

	m_roundSparksEmitter->setLowLife(12.5f);
	m_roundSparksEmitter->setHighLife(12.5f);

	m_roundSparksEmitter->setSpreadSpeed(100.0f*m_scale);

	/* 
	 * Debris emitter
	 */

	m_debrisEmitter = new ParticleEffectLimited();
	m_debrisEmitter->setMaxCount(EXPLOSION_DEBRIS_EMITTER_MAX);

	m_debrisEmitter->setAreaCheck(false);
	m_debrisEmitter->setAlphaActive(true);
	m_debrisEmitter->setDrawMode(drawMode);
	m_debrisEmitter->setTexture(TEXTURE_PTR(Tex::DEBRIS_SHEET_TEXTURE));
	m_debrisEmitter->setTextureXSize(3);
	m_debrisEmitter->setTextureYSize(3);
	m_debrisEmitter->setLifeAsSize(false);
	m_debrisEmitter->setParamsActive(true);
	m_debrisEmitter->setFacingVelocity(false);
	m_debrisEmitter->setRandomAngle(true);

	m_debrisEmitter->setStartSize(15.0f*m_scale);
	m_debrisEmitter->setEndSize(35.0f*m_scale);

	m_debrisEmitter->setStartColor(255,255,255, 255);
	m_debrisEmitter->setEndColor(75,75,75,0);

	m_debrisEmitter->setLowLife(7.5f);
	m_debrisEmitter->setHighLife(12.5f);

	m_debrisEmitter->setSpreadSpeed(250.0f*m_scale);

	/*
	 * Shockwave Emitter
	 */
	m_shockwaveEmitter = new ParticleEffectLimited();
	m_shockwaveEmitter->setMaxCount(EXPLOSION_SHOCKWAVE_EMITTER_MAX);

	m_shockwaveEmitter->setAreaCheck(false);
	m_shockwaveEmitter->setAlphaActive(true);
	m_shockwaveEmitter->setDrawMode(drawMode);
	m_shockwaveEmitter->setTexture(TEXTURE_PTR(Tex::SHOCKWAVE_TEXTURE));
	m_shockwaveEmitter->setTextureXSize(1);
	m_shockwaveEmitter->setTextureYSize(1);
	m_shockwaveEmitter->setLifeAsSize(false);
	m_shockwaveEmitter->setParamsActive(true);
	m_shockwaveEmitter->setFacingVelocity(false);
	m_shockwaveEmitter->setRandomAngle(true);

	m_shockwaveEmitter->setStartSize(50.0f*m_scale);
	m_shockwaveEmitter->setEndSize(300.0f*m_scale);

	m_shockwaveEmitter->setStartColor(255,120,0,255);
	m_shockwaveEmitter->setEndColor(255,75,0,0);

	m_shockwaveEmitter->setLowLife(5.0f);
	m_shockwaveEmitter->setHighLife(7.5f);

	m_shockwaveEmitter->setSpreadSpeed(0.0f*m_scale);
}

/*
 * The destructor. Frees all particle emitters.
 */
ExplosionEffect::~ExplosionEffect()
{
	delete m_flameEmitter;
	m_flameEmitter = NULL;

	delete m_flashEmitter;
	m_flashEmitter = NULL;

	delete m_sparksEmitter;
	m_sparksEmitter = NULL;

	delete m_smokeTrailsEmitter;
	m_smokeTrailsEmitter = NULL;

	delete m_roundSparksEmitter;
	m_roundSparksEmitter = NULL;

	delete m_debrisEmitter;
	m_debrisEmitter = NULL;

	delete m_shockwaveEmitter;
	m_shockwaveEmitter = NULL;
}

/*
 * Sets the scale of the effect
 * 1.0f is quite big and it's used when 2D drawing mode is active
 */
void ExplosionEffect::setScale(float scale)
{
	if(scale <= 0.0f)
		scale = 1.0f;
	m_scale = scale;
	/*
	 * Flame/Smoke Emitter
	 */
	m_flameEmitter->setStartSize(100.0f*m_scale);
	m_flameEmitter->setEndSize(150.0f*m_scale);
	m_flameEmitter->setSpreadSpeed(75.0f*m_scale);
	
	/*
	 * Flash Emitter
	 */
	m_flashEmitter->setStartSize(250.0f*m_scale);
	m_flashEmitter->setEndSize(50.0f*m_scale);
	m_flashEmitter->setSpreadSpeed(0.0f*m_scale);

	/*
	 * Flying Sparks Emitter
	 */
	m_sparksEmitter->setStartSize(25.0f*m_scale);
	m_sparksEmitter->setEndSize(55.0f*m_scale);
	m_sparksEmitter->setSpreadSpeed(300.0f*m_scale);

	/*
	 * Smoke Trails Emitter
	 */
	m_smokeTrailsEmitter->setStartSize(50.0f*m_scale);
	m_smokeTrailsEmitter->setEndSize(150.0f*m_scale);
	m_smokeTrailsEmitter->setSpreadSpeed(250.0f*m_scale);

	/*
	 * Round Sparks Emitter
	 */
	m_roundSparksEmitter->setStartSize(100.0f*m_scale);
	m_roundSparksEmitter->setEndSize(250.0f*m_scale);
	m_roundSparksEmitter->setSpreadSpeed(100.0f*m_scale);

	/* 
	 * Debris emitter
	 */
	m_debrisEmitter->setStartSize(15.0f*m_scale);
	m_debrisEmitter->setEndSize(35.0f*m_scale);
	m_debrisEmitter->setSpreadSpeed(250.0f*m_scale);

	/*
	 * Shockwave Emitter
	 */
	m_shockwaveEmitter->setStartSize(50.0f*m_scale);
	m_shockwaveEmitter->setEndSize(300.0f*m_scale);
	m_shockwaveEmitter->setSpreadSpeed(0.0f*m_scale);
}

/*
 * Adds the single explosion animation
 */
void ExplosionEffect::add(float x, float y, float z)
{
	m_flameEmitter->addParameterized(x,y,z,15);

	m_flashEmitter->addParameterized(x,y,z,2);

	m_sparksEmitter->addParameterized(x,y,z,20);

	m_smokeTrailsEmitter->addParameterized(x,y,z,20);

	m_roundSparksEmitter->addParameterized(x,y,z,5);

	m_debrisEmitter->addParameterized(x,y,z,20);

	m_shockwaveEmitter->addParameterized(x,y,z,1);
}

/*
 * Calculates all the particle movement
 */
void ExplosionEffect::calculate(void)
{
	m_flameEmitter->calculate();
	m_flashEmitter->calculate();
	m_sparksEmitter->calculate();
	m_smokeTrailsEmitter->calculate();
	m_roundSparksEmitter->calculate();
	m_debrisEmitter->calculate();
	m_shockwaveEmitter->calculate();
}

/*
 * Draws all the particles creating the whole effect of an explosion
 */
void ExplosionEffect::draw(void)
{
	m_flameEmitter->draw();
	m_flashEmitter->draw();
	m_sparksEmitter->draw();
	m_smokeTrailsEmitter->draw();
	m_roundSparksEmitter->draw();
	m_debrisEmitter->draw();
	m_shockwaveEmitter->draw();
}
