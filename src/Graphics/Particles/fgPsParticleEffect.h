/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_PS_PARTICLE_EFFECT_H_
#define _FG_PS_PARTICLE_EFFECT_H_

#include "IwArray.h"

#include "../../fgCommon.h"
#include "../fgGFXTypes.h"
#include "../../Math/fgMathLib.h"
#include "../Textures/fgTextureResource.h"

#include "fgParticle.h"

/**
 * Base class – that does not implement CONTAINER and its LOW LEVEL READ & WRITE methods
 *
 * PsParticleEffectLimited – implements container, that inserts objects in FREE SPACE, and
 *                           gets blocked if the FREE SPACE ends
 *
 * PsParticleEffectCircular – implements CIRCULAR container – that constantly overwrites
 *                            its tail, and never fully removes elements.
 *                            New element is always accepted.
 *
 */
class ParticleEffect
{   
public:
    enum Type { CIRCULAR, LIMITED };
	enum DrawMode { MODE_3D, MODE_2D };
private:
    /// Maximum number of a particles displayed at one time
	int m_maxCount;

protected:
	/// The particle area to check for collisions in 2D space
	Area m_particleArea; // FIXME
	/// Is area set?
	bool m_areaSet;
	/// Is area going to be checked? Only in 2D drawing mode.
	bool m_areaCheck;
	
	//
	// Particle parameters, used in automated particle addition, ignored when adding custom particles
	//

	/// Is velocity random or static (determined by the spreadSpeed value)
	bool m_randomVelocity;
	/// Is life of the particle sets the size?
	bool m_lifeAsSize;
	/// Do particles pitch in the direction they're flying?
	bool m_facingVelocity;
	/// true = The particle sprite is rotated at a random angle when it is emitted (e.g. explosion, debris).
	/// Only Z angle is randomized
	bool m_randomAngle;
	/// Are parameters (start/end size, start/end color) taken into account when calculating the particles. LifeAsSize will be overridden
	bool m_paramsActive;
	/// The start size of the added particle. This will work if TTL is set
	float m_startSize;
	/// The end size of the animated particle. The particle will reach the end size in TTL miliseconds
	float m_endSize;

	/// How fast should the particles spread in all directions - 0.0f for static. Speed in units per second.
	float m_spreadSpeed; 

	/// The low life of the added particle. When the particle is added its life is set between start and end value
	/// Life = 10.0f equals TTL 1000ms
	float m_lowLife;
	/// The high life of the added particle. When the particle is added its life is set between start and end value
	float m_highLife;

	/// The start color of the particle
	fgColor m_startColor;
	/// The end color of the animated particle. The particle will reach the end color in TTL miliseconds
	fgColor m_endColor;

protected:
    /// Array – serves as NORMAL or CIRCULAR buffer for Particle objects
    CIwArray<Particle> m_particles;
	/// The color stream
	fgColor *m_colorStream;
	/// The vertices stream in 2D space (XY)
	fgVector2i *m_vertStream2D;
	/// The vertices stream in 3D space (XYZ)
	fgVector3f *m_vertStream3D;
	/// The UV stream
	fgVector2f *m_UVStream;
	/// Marmalade material used for the effect
	//CIwMaterial* m_material; // FIXME
	void *m_material; // FIXME
	/// The texture used on the particles
	fgTextureResource *m_texture; 
	/// Matrix model used in 3D space particle rendering
	fgMatrix4f m_modelMatrix;
	/// Point in 2D or 3D space where the new particles are added
	/// Changing position will move all the particles in the current effect
	/// because positions stored in particle data are relative
	fgVector3f m_emitterOrigin;

	/// One texture file can hold for example 4 smaller textures (2x2)
	/// when adding a new particle to the effect, only one of them will 
	/// be used by a single particle
	/// These parameters will store the size of the texture array
	int m_textureXSize; // ImagesX
	int m_textureYSize; // ImagesY

	/// Is blending mode activated?
	bool m_alphaActive;
	/// The draw mode of the particles
	DrawMode m_drawMode;
	/// Buffer type
	Type m_type;
public:
	/**
	 * Empty constructor - no allocation made
	 */
	ParticleEffect() : m_maxCount(0), m_areaSet(false), m_areaCheck(false), m_lifeAsSize(false), m_alphaActive(true), m_drawMode(MODE_2D), m_textureXSize(1), m_textureYSize(1)
    {
		m_colorStream = NULL;
		m_vertStream2D = NULL;
		m_vertStream3D = NULL;
		m_UVStream = NULL;
		m_material = NULL;
		m_texture = NULL;

		m_randomVelocity = true;
		m_paramsActive = false;
		m_facingVelocity = false;
		m_randomAngle = false;
		m_startSize = 1.0f;
		m_endSize = 1.0f;
		m_lowLife = 1.0f;
		m_highLife = 1.0f;
		fgColor color;
		
		//color.Set(255,255,255,255);
		m_startColor = color;
		m_endColor = color;
    }

	~ParticleEffect();

//
// MARK: -
// MARK: Getters
//

	/**
	 * Get the emitter origin position
	 */
	fgVector3f emitterOrigin(void) const {
		return m_emitterOrigin;
	}

	/**
	 * Material used with the particles
	 */
	void *material(void) const {
		return m_material;
	}

	/**
	 * Texture used in the effect
	 */
	fgTextureResource *texture(void) const {
		return m_texture;
	}

	/**
	 * Draw mode of the particles (2D/3D)
	 */
	DrawMode drawMode(void) const {
		return m_drawMode;
	}

	/**
	 * Is area being checked?
	 */
	bool areaCheck(void) const {
		return m_areaCheck;
	}

	/**
	 * Is blending active?
	 */
	bool alphaActive() const {
		return m_alphaActive;
	}

	/**
	 * Maximum number of particles supported by the emitter
	 */
	int maxCount(void) const {
		return m_maxCount;
	}

	/**
	 * The particle area (area for checking the collisions in 2D space)
	 */
	Area & particleArea(void) {
		return m_particleArea;
	}

	/**
	 * Number of particles currently being processsed
	 */
	int count(void) const {
		return m_particles.size();
	}

	/**
	 * Pointer to array storing the particle data
	 */
	Particle * particlesData(void)	{
        /// Marmalades IwArray<> should guaranteed to use continuous block of memory
		return &m_particles[0];
	}

    Type type() const {
        return m_type;
    }
//
// MARK: -
// MARK: Setters
//
	
	/**
	 * Setting the emitter origin position
	 */
	void setEmitterOrigin(float x, float y) {
		m_emitterOrigin = fgVector3f(x,y,0.0f);
	}

	void setEmitterOrigin(float x, float y, float z) {
		m_emitterOrigin = fgVector3f(x,y,z);
	}

	void setEmitterOrigin(fgVector3f origin) {
		m_emitterOrigin = origin;
	}

	/**
	 * Set texture array X size (number of columns)
	 */
	void setTextureXSize(int size) {
		if(size <= 0)
			size = 1;
		m_textureXSize = size;
	}

	/**
	 * Set texture array Y size (number of rows)
	 */
	void setTextureYSize(int size) {
		if(size <= 0)
			size = 1;
		m_textureYSize = size;
	}

	/**
	 * Setting texture for every particle displayed
	 */
	void setTexture(fgTextureResource *texture) {
		m_texture = texture;
		//if(m_material)
		//	m_material->SetTexture(m_texture->texture());
	}

	/**
	 * Draw mode of the particles, can be 2D or 3D
	 */
	void setDrawMode(DrawMode mode)	{
		m_drawMode = mode;
	}

	/**
	 * Are parameters (start/end size, start/end color) taken into account when calculating the particles
	 */
	void setParamsActive(bool active) {
		m_paramsActive = active;
	}

	/*
	 * Is velocity random?
	 */
	void setRandomVelocity(bool active) {
		m_randomVelocity = active;
	}

	/**
	 * Is life of the particle describing also the size?
	 */
	void setLifeAsSize(bool active) {
		m_lifeAsSize = active;
	}

	void setSpreadSpeed(float speed) {
		m_spreadSpeed = speed;
	}

	/**
	 * Do particles pitch in the direction they're flying?
	 */
	void setFacingVelocity(bool active) {
		m_facingVelocity = active;
	}

	/**
	 * Is the newly added particle randomly rotated?
	 */
	void setRandomAngle(bool active) {
		m_randomAngle = active;
	}

	/**
	 * The start size of the added particle
	 */
	void setStartSize(float size) {
		m_startSize = size;
		m_paramsActive = true;
	}

	/**
	 * The end size of the animated particle. The particle will reach the end size in TTL miliseconds
	 */
	void setEndSize(float size) {
		m_endSize = size;
		m_paramsActive = true;
	}

	/**
	 * The start life of the added particle. When the particle is added its life is set between start and end value
	 */
	void setLowLife(float life) {
		m_lowLife = life;
	}

	/**
	 * The end life of the added particle. When the particle is added its life is set between start and end value
	 */
	void setHighLife(float life) {
		m_highLife = life;
	}

	/**
	 * The start color of the particle
	 */
	void setStartColor(fgColor color) {
		m_startColor = color;
		m_paramsActive = true;
	}

	void setStartColor(int r, int g, int b, int a) {
		m_startColor.r = (uint8)r;
		m_startColor.g = (uint8)g;
		m_startColor.b = (uint8)b;
		m_startColor.a = (uint8)a;
		m_paramsActive = true;
	}

	/**
	 * The end color of the animated particle. The particle will reach the end color in TTL miliseconds
	 */
	void setEndColor(fgColor color) {
		m_endColor = color;
		m_paramsActive = true;
	}

	void setEndColor(int r, int g, int b, int a) {
		m_endColor.r = (uint8)r;
		m_endColor.g = (uint8)g;
		m_endColor.b = (uint8)b;
		m_endColor.a = (uint8)a;
		m_paramsActive = true;
	}

	/**
	 * Unset the particle area
	 */
	void unsetParticleArea() {
		m_particleArea = Area();
		m_areaSet = false;
		m_areaCheck = false;
	}

	/**
	 * Set the particle area for checking collisions with
	 */
	void setParticleArea(Area area) {
		m_particleArea = area;
		m_areaSet = true;
		m_areaCheck = true;
	}

	void setParticleArea(Area *area) {
		m_particleArea = *area;
		m_areaSet = true;
		m_areaCheck = true;
	}

	/**
	 * Is area checking active? 
	 * Checking for collisions of the particles with area bounds (in 2D drawing)
	 */
	void setAreaCheck(bool active)	{
		m_areaCheck = active;
	}

    /**
     * Turns on the BLEND that is then set in the current material options
     */
	void setAlphaActive(bool active) {
		m_alphaActive = active;
		/*if(m_material) {
			if(active)
				m_material->SetAlphaMode(CIwMaterial::ALPHA_ADD);
			else
				m_material->SetAlphaMode(CIwMaterial::ALPHA_NONE);
		}*/
	}

    /**
     * Limits number of particles the emitter will hold
	 * Also limits number of the vertices, colors and UV binds
     */
	virtual void setMaxCount(int max_count);

//
// MARK: -
// MARK: Business
//

    /**
     * Computes new state of the system
     */
	virtual void calculate(void);

    /**
     * Draws current state of the system
     */
	virtual void draw(void);

    /**
     * Removes given particle
     */
	virtual void remove(int which) = 0;

	/**
	 * Adds random particles by taking into account previosly set parameters
	 */
	bool addParameterized(float x, float y, float z, int count);

    /**
     * Add prepare particle
     */
    virtual bool add(Particle* particle) = 0;

    /**
     * Does the same as above, but multiple (count) times
     */
	virtual bool addGroup(Particle *particles, int count) = 0;

    /**
     * Adds ONE particle, with fields set to RANDOM on interval [from.the_field, to_the_field]
     */
	virtual bool addRandom(Particle *from, Particle *to) = 0;

    /**
     * Does the same as above, but multiple times
     */
	virtual bool addRandomGroup(Particle *from, Particle *to, int count) = 0;

    /**
     * Takes two particles, does randomization on [from->some_val, to->some_val]
     * and stores new random values to *from
     */
    virtual void randomizeOnPair(Particle* from, Particle* to, Particle *result);
};

#endif
