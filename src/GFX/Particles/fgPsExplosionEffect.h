/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_PS_EXPLOSION_EFFECT_H_
    #define _FG_PS_EXPLOSION_EFFECT_H_

// The limited-buffer (not circular-buffer) ParticleEffect* class
    #include "fgPsParticleEffectLimited.h"
    #include "fgPsSpecialEffect.h"

    #define EXPLOSION_FLAME_EMITTER_MAX				48
    #define EXPLOSION_FLASH_EMITTER_MAX				16
    #define EXPLOSION_SPARKS_EMITTER_MAX			48
    #define EXPLOSION_SMOKE_TRAILS_EMITTER_MAX		48
    #define EXPLOSION_ROUND_SPARKS_EMITTER_MAX		16
    #define EXPLOSION_DEBRIS_EMITTER_MAX			48
    #define EXPLOSION_SHOCKWAVE_EMITTER_MAX			16

/*
 * The special effect creating the particle effect of an explosion
 * Should support 2D and 3D drawing modes of the particles.
 */
class ExplosionEffect : public SpecialEffect {
private:
    /// Scale of the effect. 1.0f means that the effect is prepared for 2D display - will be quite big, 600x600px
    float m_scale;
protected:
    /*
     * This emitter should generate sprites that grow almost instantly at first, then drift apart with a slow rotation. 
     * The gravity setting on this emitter should be a negative value, but close to zero, so the smoke will slowly rise
     * over time, instead of falling. The color should start out bright yellow/orange and change to black quickly as the
     * flame turns to smoke. The overall lifespan of the sprites should be roughly .5 seconds. 
     * Used texture: flame0_sheet.tga (FLAME_SHEET_TEXTURE)
     */
    ParticleEffectLimited *m_flameEmitter;

    /*
     * This emitter uses the star-shaped textures (flash0_sheet.tga) and should grow almost instantly and fade just as 
     * quickly. It should be bright yellow- almost white and should last about .2 seconds. It�s possible to  get by with
     * just the Flash and Flame/Smoke Emitters, if you want to keep the overall effect simple. (FLASH_SHEET_TEXTURE)
     */
    ParticleEffectLimited *m_flashEmitter;

    /*
     * This emitter should be long and thin. Instead of facing the camera, the sprites should be oriented along the direction
     * of travel, to look like lines radiating from a central point. Adjust the color, like most of the other emitters, so it
     * looks gold. The speed should be around 10 meters per second. The lifetime can vary from .5 seconds to 1.5 seconds,
     * depending on how far you want the sparks to travel from the explosion. Used texture: spark0.tga (SPARK_TEXTURE)
     */
    ParticleEffectLimited *m_sparksEmitter;

    /*
     * Like the Flying Sparks emitter, the Smoke Trails Emitter should be long and thin and be oriented along a path radiating 
     * from the center. But unlike the Flying Sparks, which move away from the middle at a fast speed, the Smoke Trails sprites
     * should move slowly, and grow quickly from the center of the overall effect by changing the scale over time. The lifetime
     * should be about .4 seconds. Used texture: smoketrail0_sheet.tga (SMOKETRAIL_SHEET_TEXTURE)
     */
    ParticleEffectLimited *m_smokeTrailsEmitter;

    /*
     * This emitter is similar to the Flame/Smoke Emitter and once again, the sprites fall up instead of down by using a negative
     * number in the gravity setting (-0.2). The sprites from this emitter should drift apart slightly as they rise.
     * Used texture: roundspark0.tga (ROUNDSPARK_TEXTURE)
     */
    ParticleEffectLimited *m_roundSparksEmitter;

    /*
     * These fast moving sprites should fly out from the center of the overall emitter. If possible, aim for the camera for dramatic
     * impact. The color should start out bright orange, to look like reflected light from the explosion, then fade to a neutral gray
     * as the explosion dims. The sprites from this emitter should hang around longer than the others, with a lifetime of about 1.5
     * seconds. The speed should be around 10 meters per second. Set the emitter�s gravity to about .7 so the sprites look like they�re
     * falling slower than normal.
     * Used texture: debris0_sheet.tga (DEBRIS_SHEET_TEXTURE)
     */
    ParticleEffectLimited *m_debrisEmitter;

    /*
     * This emitter consists of only one sprite that lies parallel to the ground. The sprite should grow quickly from the center and
     * fade out just as quickly. It�s best when this sprite is kept very subtle and transparent. Used texture: shockwave0.tga (SHOCKWAVE_TEXTURE)
     */
    ParticleEffectLimited *m_shockwaveEmitter;
public:
    /*
     * Default constructor
     */
    ExplosionEffect(ParticleEffect::DrawMode drawMode, float scale);
    ~ExplosionEffect();
    /*
     * Returns the scale of the effect
     */
    float scale(void) const {
        return m_scale;
    }

    /*
     * Sets the scale of the effect
     */
    void setScale(float scale);

    /*
     * Adds a single animation
     */
    void add(float x, float y, float z);

    /*
     * Calculates the particles movement
     */
    void calculate(void);

    /*
     * Draws the particles
     */
    void draw(void);
};

#endif