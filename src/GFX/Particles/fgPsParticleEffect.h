/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_PS_PARTICLE_EFFECT_H_
    #define _FG_PS_PARTICLE_EFFECT_H_

    #include "fgBool.h"
    #include "GFX/fgGFXTypes.h"

    #include "fgParticle.h"
    #include "Util/fgTag.h"
// #FIXME - maybe save particle effects (or any kind of effects)
// inside of a resource manager ? Particle System would be just 
// used for display routines? Well... whatever
    #include "Resource/fgResource.h"
    #include "Util/fgConfigStruct.h"

/**
 * PsParticleEffectLimited – implements container, that inserts objects in FREE SPACE, and
 *                           gets blocked if the FREE SPACE ends
 *
 * PsParticleEffectCircular – implements CIRCULAR container – that constantly overwrites
 *                            its tail, and never fully removes elements.
 *                            New element is always accepted.
 */

class fgParticleEffect;

    #define FG_TAG_PARTICLE_EFFECT_NAME     "ParticleEffect"
    #define FG_TAG_PARTICLE_EFFECT          FG_TAG_TYPE(fgParticleEffect)

FG_TAG_TEMPLATE_ID_AUTO(fgParticleEffect, FG_TAG_PARTICLE_EFFECT_NAME);

// Special tag type for particle effect
typedef FG_TAG_PARTICLE_EFFECT fgParticleEffectTag;
// Special handle type for particle effect
//typedef fgHandle<fgParticleEffectTag> fgParticleEffectHandle;
typedef fgResourceHandle fgParticleEffectHandle;

/**
 *
 */
enum fgParticleEffectFlags {
    /// No specific flags are specified
    FG_PARTICLE_FLAG_NONE = 0x00000000,
    /// Is velocity random or static? If random then it's from <-spreadSpeed, spreadSpeed>
    FG_PARTICLE_RANDOM_VELOCITY = 0x00000001,
    /// Does life of the particle sets the size?
    FG_PARTICLE_LIFE_AS_SIZE = 0x00000002,
    /// Do particles pitch in the direction they're flying
    FG_PARTICLE_FACING_VELOCITY = 0x00000004,
    /// The particle sprite is rotated at a random angle when it is emitted
    FG_PARTICLE_RANDOM_ANGLE = 0x00000008,
    /// Are parameters (start/end size, start/end color) taken into account 
    /// when calculating the particles. LifeAsSize will be overridden.
    FG_PARTICLE_PARAMS_ACTIVE = 0x00000010
};
FG_ENUM_FLAGS(fgParticleEffectFlags);

    #include <cfloat>
    #include <climits>

    #define FG_PARTICLE_FLOAT_UNIT_INVALID       (FLT_MAX/4.0f)
    #define FG_PARTICLE_FLOAT_UNIT_TEST_VALUE    (FLT_MAX/5.0f)
    #define FG_PARTICLE_CHECK_FLOAT(value)       (value < FG_PARTICLE_FLOAT_UNIT_TEST_VALUE)

    #define FG_PARTICLE_INT_UNIT_INVALID        (INT_MAX/4)
    #define FG_PARTICLE_INT_UNIT_TEST_VALUE     (INT_MAX/5)
    #define FG_PARTICLE_CHECK_INT(value)        (value < FG_PARTICLE_INT_UNIT_TEST_VALUE)

    #include "Resource/fgResourceFactoryTypes.h"

/**
 * Below is the list of the parameters that make changes (affect the particle) 
 * only when paramsActive flag is set:
 *  * start-size
 *  * end-size
 *  * start-color
 *  * end-color
 * 
 * Some of the above option will exclude each other. This important to know. TTL
 * integer value is  being stored for reference and should not be used directly.
 * TTL value manipulates the  life value of  the particle and fadeSpeed.  That's 
 * why ttl-range and fade-speed-range are exclusionary. If the two are specified
 * than ttl-range is used. 
 *      * Also when life-as-size is active there is slightly difference – the 
 *        size is set to life parameter value.
 *          * If paramsActive  is TRUE then the  size is carefully  decreased to
 *            reach end value in TTL milliseconds. With lifeAsSize and paramsActive
 *            triggered – the decreasing of the size in TTL wont work as expected.
 *      * Also setting life-range will indeed work and change the particles life 
 *        property on particle addition it does not affect the TTL or fadeSpeed.
 * 
 * List of parameters that work together, other combinations will not be valid:
 *  * life-as-size | life-range | ttl-range
 *  * life-as-size | life-range | fade-speed-range
 *  * start-size | end-size | ttl-range
 *  * start-size | end-size | fade-speed-range
 *  * start-size | end-size | start-color | end-color | ttl-range
 *  * start-size | end-size | start-color | end-color | fade-speed-range
 * 
 * Other parameters  just  work with these.  These are just different methods of
 * setting up  default  behavior  on particle addition and specify value ranges.
 * 
 * @extends fgConfig
 * @see     fgConfig
 */
class fgParticleEffect : public fgResource {
private:
    /// Maximum number of a particles displayed at one time
    int m_maxCount;
    /// Particle effect specific flags
    fgParticleEffectFlags m_flags;
    /// Particle area bounding box
    fgBoundingBox3Df m_particleArea;
    /// Is area set?
    fgBool m_isAreaSet;
    /// Is area going to be checked?
    fgBool m_isAreaCheck;
    /// Texture name to use
    std::string m_textureName;
    /// Texture ID
    fgGfxTextureID m_textureGfxID;
    /// Texture sprite sheet size
    fgVector2i m_textureSheetSize;
    /// Texture ID range
    fgVector2i m_textureIDRange;

    //
    // Particle parameters, used in automated particle addition
    // They're ignored when adding custom particles definitions
    // #FIXME   - adding particles in also moved to another place
    //          - the ParticleEmitter
    //

    /// The start size of the added particle. This will work if TTL is set
    fgVector3f m_startSize;
    /// The end size of the animated particle. The particle will reach the end size in TTL miliseconds
    fgVector3f m_endSize;

    /// How fast should the particles spread in all directions - 0.0f for static. Speed in units per second.
    fgVector3f m_spreadSpeed;

    /// The low life of the added particle. When the particle is added its life is set between start and end value
    /// Life = 10.0f equals TTL 1000ms
    /// The high life of the added particle. When the particle is added its life is set between start and end value
    fgVector2f m_lifeRange;

    /// TTL range
    fgVector2i m_ttlRange;

    /// Fade speed range
    fgVector2f m_fadeSpeedRange;

    /// The start color of the particle
    fgColor4f m_startColor;
    /// The end color of the animated particle. The particle will reach the end color in TTL miliseconds
    fgColor4f m_endColor;

protected:
    /**
     * 
     */
    virtual void clear(void);
public:
    /**
     * Empty constructor - no allocation made
     */
    fgParticleEffect();

    /**
     * 
     */
    virtual ~fgParticleEffect();

    FG_RESOURCE_FACTORY_CREATE_FUNCTION(fgParticleEffect);

    /**
     * Create function loads/interprets data from file in ROM and place it in RAM memory.
     * @return 
     */
    virtual fgBool create(void);
    /**
     * Destroy all loaded data including additional metadata (called with destructor)
     */
    virtual void destroy(void);
    /**
     * Reloads any data, recreates the resource (refresh)
     * @return 
     */
    virtual fgBool recreate(void);
    /**
     * Dispose completely of the all loaded data, free all memory
     */
    virtual void dispose(void);
    /**
     * Check if resource is disposed (not loaded yet or disposed after)
     * @return 
     */
    virtual fgBool isDisposed(void) const;
    /**
     * Limits number of particles the emitter will hold
     * Also limits number of the vertices, colors and UV binds
     */
    inline void setMaxCount(const int maxCount) {
        if(maxCount > 0) {
            m_maxCount = maxCount;
        }
    }
    /**
     * Maximum number of particles supported by the emitter
     */
    inline int getMaxCount(void) const {
        return m_maxCount;
    }
    /**
     * 
     * @return 
     */
    inline fgBool isAreaCheck(void) const {
        return m_isAreaCheck;
    }
    /**
     * 
     * @return 
     */
    inline fgBool isAreaSet(void) const {
        return m_isAreaSet;
    }
    /**
     * Unset the particle area
     */
    inline void unsetParticleArea() {
        m_particleArea.zero();
        m_isAreaSet = FG_FALSE;
        m_isAreaCheck = FG_FALSE;
    }
    /**
     * Set the particle area for checking collisions with
     * @param area
     */
    inline void setParticleArea(const fgBoundingBox3Df& area) {
        m_particleArea = area;
        m_isAreaSet = FG_TRUE;
        m_isAreaCheck = FG_TRUE;
    }
    /**
     * 
     * @param area
     */
    inline void setParticleArea(const fgBoundingBox3Df *area) {
        m_particleArea = *area;
        m_isAreaSet = FG_TRUE;
        m_isAreaCheck = FG_TRUE;
    }
    /**
     * Is area checking active?
     * Checking for collisions of the particles with area bounds (in 2D drawing)
     */
    inline void setAreaCheck(const fgBool active) {
        m_isAreaCheck = active;
    }
    /**
     * 
     * @param flags
     * @param toggle
     */
    inline void setFlag(const fgParticleEffectFlags flags, const fgBool toggle = FG_TRUE) {
        if(toggle) {
            m_flags |= flags;
        } else {
            m_flags |= flags;
            m_flags ^= flags;
        }
    }
    /**
     * Set texture array X size (number of columns)
     */
    inline void setTextureXSize(const int size) {
        if(size > 0)
            m_textureSheetSize.x = size;
        else
            m_textureSheetSize.x = 1;
    }
    /**
     * Set texture array Y size (number of rows)
     */
    inline void setTextureYSize(const int size) {
        if(size > 0)
            m_textureSheetSize.y = size;
        else
            m_textureSheetSize.y = 1;
    }
    /**
     * 
     * @param range
     */
    inline void setTextureIDRange(const fgVector2i& range) {
        m_textureIDRange = range;
    }
    /**
     * 
     * @param minimum
     * @param maximum
     */
    inline void setTextureIDRange(const int minimum, const int maximum) {
        if(minimum >= 0)
            m_textureIDRange.x = minimum;
        if(maximum >= 0)
            m_textureIDRange.y = maximum;
    }
    /**
     * Are parameters (start/end size, start/end color) taken into account when calculating the particles
     */
    inline void setParamsActive(const fgBool toggle = FG_TRUE) {
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, toggle);
    }
    /*
     * Is velocity random?
     */
    inline void setRandomVelocity(const fgBool toggle = FG_TRUE) {
        setFlag(FG_PARTICLE_RANDOM_VELOCITY, toggle);
    }
    /**
     * Is life of the particle describing also the size?
     */
    inline void setLifeAsSize(const fgBool toggle = FG_TRUE) {
        setFlag(FG_PARTICLE_LIFE_AS_SIZE, toggle);
    }
    /**
     * Do particles pitch in the direction they're flying?
     */
    inline void setFacingVelocity(const fgBool toggle = FG_TRUE) {
        setFlag(FG_PARTICLE_FACING_VELOCITY, toggle);
    }
    /**
     * Is the newly added particle randomly rotated?
     */
    inline void setRandomAngle(const fgBool toggle = FG_TRUE) {
        setFlag(FG_PARTICLE_RANDOM_ANGLE, toggle);
    }
    /**
     * 
     * @param speed
     */
    inline void setSpreadSpeed(const fgVector3f& spreadSpeed) {
        m_spreadSpeed = spreadSpeed;
    }
    /**
     * The start size of the added particle
     */
    inline void setStartSize(const float size) {
        m_startSize.x = size;
        m_startSize.y = size;
        m_startSize.z = size;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);
    }
    /**
     * 
     * @param size
     */
    inline void setStartSize(const fgVector3f& size) {
        m_startSize = size;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);
    }
    /**
     * The end size of the animated particle. The particle will reach the end size in TTL milliseconds
     */
    inline void setEndSize(const float size) {
        m_endSize.x = size;
        m_endSize.y = size;
        m_endSize.z = size;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);
    }
    /**
     * 
     * @param size
     */
    inline void setEndSize(const fgVector3f& size) {
        m_endSize = size;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);
    }
    /**
     * The start life of the added particle. When the particle is added its life is set between start and end value
     */
    inline void setLowLife(const float life) {
        m_lifeRange.x = life;
    }
    /**
     * The end life of the added particle. When the particle is added its life is set between start and end value
     */
    inline void setHighLife(const float life) {
        m_lifeRange.y = life;
    }
    /**
     * 
     * @param lifeRange
     */
    inline void setLifeRange(const fgVector2f& lifeRange) {
        m_lifeRange = lifeRange;
    }
    /**
     * 
     * @param minimum
     * @param maximum
     */
    inline void setLifeRange(const float minimum, const float maximum) {
        m_lifeRange.x = minimum;
        m_lifeRange.y = maximum;
    }
    /**
     * 
     * @param ttlRange
     */
    inline void setTTLRange(const fgVector2i& ttlRange) {
        m_ttlRange = ttlRange;
    }
    /**
     * 
     * @param minimum
     * @param maximum
     */
    inline void setTTLRange(const int minimum, const int maximum) {
        m_ttlRange.x = minimum;
        m_ttlRange.y = maximum;
    }
    /**
     * The start color of the particle
     */
    inline void setStartColor(const fgColor4f& color) {
        m_startColor = color;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);
    }
    /**
     * 
     * @param r
     * @param g
     * @param b
     * @param a
     */
    inline void setStartColor(const int r, const int g, const int b, const int a) {
        m_startColor.r = (float)r / 255.0f;
        m_startColor.g = (float)g / 255.0f;
        m_startColor.b = (float)b / 255.0f;
        m_startColor.a = (float)a / 255.0f;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);

    }
    /**
     * The end color of the animated particle. The particle will reach the end color in TTL miliseconds
     */
    inline void setEndColor(const fgColor4f& color) {
        m_endColor = color;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);
    }
    /**
     * 
     * @param r
     * @param g
     * @param b
     * @param a
     */
    inline void setEndColor(const int r, const int g, const int b, const int a) {
        m_endColor.r = (float)r / 255.0f;
        m_endColor.g = (float)g / 255.0f;
        m_endColor.b = (float)b / 255.0f;
        m_endColor.a = (float)a / 255.0f;
        setFlag(FG_PARTICLE_PARAMS_ACTIVE, FG_TRUE);
    }
    /**
     * 
     * @param fadeRange
     */
    inline void setFadeSpeedRange(const fgVector2f& fadeRange) {
        m_fadeSpeedRange = fadeRange;
    }
    /**
     * 
     * @param minimum
     * @param maximum
     */
    inline void setFadeSpeedRange(const float minimum, const float maximum) {
        m_fadeSpeedRange.x = minimum;
        m_fadeSpeedRange.y = maximum;
    }
    /**
     * 
     * @param texName
     */
    inline void setTextureName(const std::string& texName) {
        m_textureName = texName;
    }
    /**
     * 
     * @param texName
     */
    inline void setTextureName(const char *texName) {
        m_textureName = texName;
    }
    /**
     * 
     * @param texGfxID
     */
    inline void setTextureGfxID(const fgGfxTextureID& texGfxID) {
        m_textureGfxID = texGfxID;
    }
    /**
     * 
     * @return 
     */
    inline fgParticleEffectFlags getFlags(void) const {
        return m_flags;
    }
    /**
     * 
     * @return 
     */
    inline fgBoundingBox3Df& getParticleArea(void) {
        return m_particleArea;
    }
    /**
     * 
     * @return 
     */
    inline std::string& getTextureName(void) {
        return m_textureName;
    }
    /**
     * 
     * @return 
     */
    inline fgGfxTextureID& getTextureGfxID(void) {
        return m_textureGfxID;
    }
    /**
     * 
     * @return 
     */
    inline fgVector2i& getTextureSheetSize(void) {
        return m_textureSheetSize;
    }
    /**
     * 
     * @return 
     */
    inline fgVector2i& getTextureIDRange(void) {
        return m_textureIDRange;
    }
    /**
     * 
     * @return 
     */
    inline fgVector3f& getStartSize(void) {
        return m_startSize;
    }
    /**
     * 
     * @return 
     */
    inline fgVector3f& getEndSize(void) {
        return m_endSize;
    }
    /**
     * 
     * @return 
     */
    inline fgVector3f& getSpreadSpeed(void) {
        return m_spreadSpeed;
    }
    /**
     * 
     * @return 
     */
    inline fgVector2f& getLifeRange(void) {
        return m_lifeRange;
    }
    /**
     * 
     * @return 
     */
    inline fgVector2i& getTTLRange(void) {
        return m_ttlRange;
    }
    /**
     * 
     * @return 
     */
    inline fgVector2f& getFadeSpeedRange(void) {
        return m_fadeSpeedRange;
    }
    /**
     * 
     * @return 
     */
    inline fgColor4f& getStartColor(void) {
        return m_startColor;
    }
    /**
     * 
     * @return 
     */
    inline fgColor4f& getEndColor(void) {
        return m_endColor;
    }
    /**
     * 
     * @return 
     */
    inline fgBool isParamsActive(void) {
        return (fgBool)(m_flags & FG_PARTICLE_PARAMS_ACTIVE);
    }
    /**
     * 
     * @return 
     */
    inline fgBool isRandomVelocity(void) {
        return (fgBool)(m_flags & FG_PARTICLE_RANDOM_VELOCITY);
    }
    /**
     * 
     * @return 
     */
    inline fgBool isLifeAsSize(void) {
        return (fgBool)(m_flags & FG_PARTICLE_LIFE_AS_SIZE);
    }
    /**
     * 
     * @return 
     */
    inline fgBool isFacingVelocity(void) {
        return (fgBool)(m_flags & FG_PARTICLE_FACING_VELOCITY);
    }
    /**
     * 
     * @return 
     */
    inline fgBool isRandomAngle(void) {
        return (fgBool)(m_flags & FG_PARTICLE_RANDOM_ANGLE);
    }

    /**
     * 
     * @param params
     * @return 
     */
    fgBool initializeFromConfig(fgCfgTypes::parameterVec &params);

    /**
     * Initializes the given particle based on given parameters, it will be 
     * randomized based on those parameters.
     * @param outputParticle
     */
    void initializeParticle(fgParticle *outputParticle,
                            const fgBool randomizePosition = FG_FALSE,
                            const fgVector3f& position = fgVector3f(0.0f, 0.0f, 0.0f));

    /**
     * Takes two particles, does randomization on [from->some_val, to->some_val]
     * and stores new random values to *result
     */
    static void randomizeOnPair(const fgParticle* from,
                                const fgParticle* to,
                                fgParticle *result);
    
    /**
     * 
     * @param outputParticle
     */
    void basicCalculate(fgParticle *outputParticle);
};

#endif /* _FG_PS_PARTICLE_EFFECT_H_ */
