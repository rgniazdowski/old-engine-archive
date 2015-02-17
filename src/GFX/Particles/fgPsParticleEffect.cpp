/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgPsParticleEffect.h"
#include "Util/fgConfig.h"
#include "Util/fgStringParser.h"

using namespace fg;

/**
 * 
 */
gfx::CParticleEffect::CParticleEffect() : CResource(),
m_maxCount(10),
m_flags(FG_PARTICLE_FLAG_NONE),
m_particleArea(),
m_isAreaSet(FG_FALSE),
m_isAreaCheck(FG_FALSE),
m_textureName(),
m_shaderName(),
m_shaderProgram(NULL),
m_textureGfxID(),
m_textureSheetSize(),
m_textureIDRange(),
m_startSize(),
m_endSize(),
m_spreadSpeed(),
m_lifeRange(),
m_ttlRange(),
m_fadeSpeedRange(),
m_startColor(),
m_endColor(),
m_burnoutDelay(),
m_burnRange() {
    m_resType = resource::PARTICLE_EFFECT;
    m_textureIDRange.x = 0;
    m_textureIDRange.y = 0;
    m_burnoutDelay = 0;
    m_burnRange.x = 1.0f;
    m_burnRange.y = 1.0f;
}

/**
 * 
 */
gfx::CParticleEffect::~CParticleEffect() {
    gfx::CParticleEffect::destroy();
}

/**
 * 
 */
void gfx::CParticleEffect::clear(void) {
    base_type::clear();
    m_resType = resource::PARTICLE_EFFECT;
}

/**
 * 
 * @param params
 * @return 
 */
fgBool gfx::CParticleEffect::initializeFromConfig(util::config::ParameterVec& params) {
    if(params.empty())
        return FG_FALSE;

    util::config::ParameterVecItor begin, end, itor;
    begin = params.begin();
    end = params.end();
    itor = begin;

    // Iterate through all style parameters
    // Parameters are taken directly from ini config file
    for(; itor != end; itor++) {
        util::SCfgParameter *param = *itor;
        if(!param)
            continue;
        // name – string –
        if(param->name.compare("name") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                this->setName(param->string);

        } else if(param->name.compare("type") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                //this->setName(param->string);
                if(strcasecmp(param->string, "group") == 0) {
                    this->setFlag(FG_PARTICLE_GROUP_EFFECT, FG_TRUE);
                } else if(FG_FALSE && strcasecmp(param->string, "single") == 0) {

                }
            }
        } else if(param->name.compare("shader") == 0 || param->name.compare("shader-name") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                this->setShaderName(param->string);
            }
        } else if(param->name.compare("max-count") == 0) {
            // max - count – integer –
            if(param->type == util::SCfgParameter::INT)
                this->setMaxCount(param->int_val);
            else if(param->type == util::SCfgParameter::STRING)
                this->setMaxCount(atoi(param->string));

            // particle - area – boundingbox –
        } else if(param->name.compare("particle-area") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                fgStringParser::parseVector<BoundingBox3Df>(m_particleArea, param->string);
                this->m_isAreaSet = FG_TRUE;
            }

            // area - check – bool –
        } else if(param->name.compare("area-check") == 0) {
            if(param->type == util::SCfgParameter::BOOL)
                this->m_isAreaCheck = param->bool_val;

            // random - velocity – bool –
        } else if(param->name.compare("random-velocity") == 0) {
            if(param->type == util::SCfgParameter::BOOL)
                setFlag(FG_PARTICLE_RANDOM_VELOCITY, param->bool_val);

            // random - angle – bool –
        } else if(param->name.compare("random-angle") == 0) {
            if(param->type == util::SCfgParameter::BOOL)
                setFlag(FG_PARTICLE_RANDOM_ANGLE, param->bool_val);

            // life - as - size – bool –
        } else if(param->name.compare("life-as-size") == 0) {
            if(param->type == util::SCfgParameter::BOOL)
                setFlag(FG_PARTICLE_LIFE_AS_SIZE, param->bool_val);

            // facing - velocity – bool –
        } else if(param->name.compare("facing-velocity") == 0) {
            if(param->type == util::SCfgParameter::BOOL)
                setFlag(FG_PARTICLE_FACING_VELOCITY, param->bool_val);

            // facing - camera – bool –
        } else if(param->name.compare("facing-camera") == 0) {
            if(param->type == util::SCfgParameter::BOOL)
                setFlag(FG_PARTICLE_FACING_CAMERA, param->bool_val);

            // params - active – bool –
        } else if(param->name.compare("params-active") == 0) {
            if(param->type == util::SCfgParameter::BOOL)
                setFlag(FG_PARTICLE_PARAMS_ACTIVE, param->bool_val);

            // start - size – vector –
        } else if(param->name.compare("start-size") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector3f>(m_startSize, param->string);

            // end - size – vector –
        } else if(param->name.compare("end-size") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector3f>(m_endSize, param->string);

            // spread - speed – vector –
        } else if(param->name.compare("spread-speed") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector3f>(m_spreadSpeed, param->string);

            // life - range – vector –
        } else if(param->name.compare("life-range") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector2f>(m_lifeRange, param->string);

            // ttl - range – vector –
        } else if(param->name.compare("ttl-range") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector2i>(m_ttlRange, param->string);

            // fade - speed - range – vector –
        } else if(param->name.compare("fade-speed-range") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector2f>(m_fadeSpeedRange, param->string);

            // start - color – color –
        } else if(param->name.compare("start-color") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_startColor = fgStringParser::parseColor(param->string);

            // end - color – color –
        } else if(param->name.compare("end-color") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_endColor = fgStringParser::parseColor(param->string);

            // texture – string –
        } else if(param->name.compare("texture") == 0 ||
                  param->name.compare("texture-name") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                m_textureName = param->string;

            // textureSize – vector –
        } else if(param->name.compare("texture-size") == 0 ||
                  param->name.compare("texture-sheet-size") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector2i>(m_textureSheetSize, param->string);

            // textureIDRange – vector –
        } else if(param->name.compare("texture-id-range") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector2i>(m_textureIDRange, param->string);

            // Burnout delay (milliseconds)
        } else if(param->name.compare("burnout-delay") == 0) {
            if(param->type == util::SCfgParameter::INT) {
                if(param->int_val >= 0) {
                    this->m_burnoutDelay = (unsigned int)param->int_val;
                }
            } else if(param->type == util::SCfgParameter::FLOAT) {
                if(param->float_val >= 0.0f) {
                    this->m_burnoutDelay = (unsigned int)param->float_val;
                }
            }

            // Burnout range (floats, valid values 0.0f-1.0f)
        } else if(param->name.compare("burn-range") == 0 ||
                  param->name.compare("burnout-range") == 0) {
            if(param->type == util::SCfgParameter::STRING)
                fgStringParser::parseVector<Vector2f>(m_burnRange, param->string);
        }
    }
    if(this->getName().empty() || m_maxCount <= 0)
        return FG_FALSE;
    return FG_TRUE;
}

/**
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 * @return 
 */
fgBool gfx::CParticleEffect::create(void) {
    if(m_isReady) {
        return FG_TRUE;
    }
    if(getFilePath().empty()) {
        FG_LOG_ERROR("GFX: Unable to create a ParticleEffect: the path is empty");
        return FG_FALSE;
    }
    util::CConfig config(getFilePathStr());
    if(!config.isLoaded()) {
        FG_LOG_ERROR("GFX: Failed to load particle effect config: '%s'", getFilePathStr());
        return FG_FALSE;
    }
    util::config::SectionMap &sections = config.getRefSectionMap();
    util::config::SectionMapItor sitor = sections.begin(), send = sections.end();

    if(sections.empty()) {
        FG_LOG_ERROR("GFX: Particle config file has no valid sections: '%s'", getFilePathStr());
        return FG_FALSE;
    }
    util::SCfgSection *mainSection = config.getSection(FG_RESOURCE_PARTICLE_EFFECT_TEXT);
    if(!mainSection) {
        FG_LOG_ERROR("GFX: Particle config is malformed: '%s'", getFilePathStr());
        return FG_FALSE;
    }

    // Initialize internal parameters from config parameter list
    if(!initializeFromConfig(mainSection->parameters)) {
        FG_LOG_ERROR("GFX: Failed to initialize ParticleEffect from config: '%s'", getFilePathStr());
        return FG_FALSE;
    }

    // Iterate through other effects #FIXME
    for(; sitor != send; sitor++) {
        // #FIXME
    }

    m_size = sizeof (CParticleEffect) + m_nameTag.length() + m_textureName.length();
    m_resType = resource::PARTICLE_EFFECT;
    m_isReady = FG_TRUE;
    return FG_TRUE;
}

/**
 * Destroy all loaded data including additional metadata (called with destructor)
 */
void gfx::CParticleEffect::destroy(void) {
    m_isReady = FG_FALSE;
    m_size = 0;
}

/**
 * Reloads any data, recreates the resource (refresh)
 * @return 
 */
fgBool gfx::CParticleEffect::recreate(void) {
    dispose();
    m_isReady = FG_FALSE;
    return create();
}

/**
 * Dispose completely of the all loaded data, free all memory
 */
void gfx::CParticleEffect::dispose(void) {
    m_isReady = FG_FALSE;
    m_size = 0;
}

/**
 * Check if resource is disposed (not loaded yet or disposed after)
 * @return 
 */
fgBool gfx::CParticleEffect::isDisposed(void) const {
    return !m_isReady;
}

/**
 * 
 * @param outputParticle
 * @param randomizePosition
 * @param position
 */
void gfx::CParticleEffect::initializeParticle(SParticle *outputParticle,
                                              const fgBool randomizePosition,
                                              const Vector3f & position) {
    if(!outputParticle)
        return;

    SParticle from, to;

    //
    // FROM
    //
    from.setColor(m_startColor);
    from.burn = m_burnRange.x;
    from.data = NULL;

    from.velocity = -m_spreadSpeed;
    from.bbox.size = m_startSize;

    // m_lowLife holds life for the particle where value 10.0f is equal to 1000ms TTL
    from.setTTL(m_lifeRange.x / 10.0f * 1000.0f);

    from.rotation.x = 0.0f;
    from.rotation.y = 0.0f;
    from.rotation.z = 0.0f;

    from.angularVelocity.x = 0.0f;
    from.angularVelocity.y = 0.0f;
    from.angularVelocity.z = 0.0f;

    if(randomizePosition) {
        from.bbox.pos = Vector3f(0.0f, 0.0f, 0.0f);
    } else {
        from.bbox.pos = position;
    }
    from.texIndex = m_textureIDRange.x;

    //
    // TO
    //
    to.setColor(m_startColor);
    to.burn = m_burnRange.x; // Y ?
    to.data = NULL;

    to.velocity = m_spreadSpeed;
    to.bbox.size = m_startSize;

    // m_highLife holds life for the particle where value 10.0f is equal to 1000ms TTL
    to.setTTL(m_lifeRange.y / 10.0f * 1000.0f);

    to.rotation.x = 0.0f;
    to.rotation.y = 0.0f;
    if(m_flags & FG_PARTICLE_RANDOM_ANGLE)
        to.rotation.z = 360.0f;
    else
        to.rotation.z = 0.0f;

    to.angularVelocity.x = 0.0f;
    to.angularVelocity.y = 0.0f;
    to.angularVelocity.z = 0.0f;

    to.bbox.pos = position;
    to.texIndex = m_textureIDRange.y;

    randomizeOnPair(&from, &to, outputParticle);
    if((m_flags & FG_PARTICLE_RANDOM_VELOCITY) == 0) {
        int r = FG_Rand(0, 1);
        if(r == 1) {
            if(outputParticle->velocity.x < 0.0f)
                outputParticle->velocity.x = -m_spreadSpeed.x;
            else
                outputParticle->velocity.x = m_spreadSpeed.x;
        } else {
            if(outputParticle->velocity.y < 0.0f)
                outputParticle->velocity.y = -m_spreadSpeed.y;
            else
                outputParticle->velocity.y = m_spreadSpeed.y;
        }
    }
    return;
}

#if 0

void gfx::CParticleEffect::calculate(void) {
    if(m_particles[i].life <= 0.0f) {
        remove(i);
        // Checking the particle area which means checking and bouncing off particles of the area edges
    } else if(m_isAreaSet == FG_TRUE && m_isAreaCheck == FG_TRUE && m_drawMode == MODE_2D) {
        // Particle X position is within the boundaries so we can check the Y position
        if(m_particles[i].bbox.pos.x >= float(m_particleArea.x) && m_particles[i].bbox.pos.x + m_particles[i].bbox.size.x <= float(m_particleArea.x + m_particleArea.w)) {
            // The UPPER and LOWER boundary
            if(m_particles[i].bbox.pos.y <= float(m_particleArea.y) || m_particles[i].bbox.pos.y + m_particles[i].bbox.size.y >= float(m_particleArea.y + m_particleArea.h))
                m_particles[i].velocity.y *= -1.0f;
            // Particle X position is out of boundaries so we can change it's direction
        } else {
            m_particles[i].velocity.x *= -1.0f;
            // FIXME
        }

        if(m_particles[i].bbox.pos.y + m_particles[i].bbox.size.y > float(m_particleArea.y + m_particleArea.h)) {
            float diff = fabs(float(m_particleArea.y + m_particleArea.h) - (m_particles[i].bbox.pos.y + m_particles[i].bbox.size.y));
            m_particles[i].bbox.pos.y -= diff + m_particles[i].bbox.size.y / 4.0f;
        }

        if(m_particles[i].bbox.pos.x < float(m_particleArea.x))
            m_particles[i].bbox.pos.x += fabs(m_particles[i].bbox.pos.x - float(m_particleArea.x));

        if(m_particles[i].bbox.pos.x + m_particles[i].bbox.size.x > float(m_particleArea.x + m_particleArea.w)) {
            float diff = fabs(float(m_particleArea.x + m_particleArea.w) - (m_particles[i].bbox.pos.x + m_particles[i].bbox.size.x));
            m_particles[i].bbox.pos.x -= diff + m_particles[i].bbox.size.x / 4.0f;
        }
        // Deleting particles fully offscreen
    } else if(m_isAreaCheck == false && m_drawMode == MODE_2D) {
        if(m_particles[i].bbox.pos.x + m_particles[i].bbox.size.x / 2 >= float(screenArea.x) && m_particles[i].bbox.pos.x - m_particles[i].bbox.size.x / 2 <= float(screenArea.x + screenArea.w)) {
            // The UPPER and LOWER boundary
            if(m_particles[i].bbox.pos.y + m_particles[i].bbox.size.y / 2 <= float(screenArea.y) || m_particles[i].bbox.pos.y - m_particles[i].bbox.size.y / 2 >= float(screenArea.y + screenArea.h))
                remove(i);
            // Particle X position is out of boundaries so we can delete it
        } else {
            remove(i);
        }
    }
}
}
#endif

/**
 * Takes two particles, does randomization on [from->some_val, to->some_val]
 * and stores new random values to Particle* from
 * @param from
 * @param to
 * @param result
 */
void gfx::CParticleEffect::randomizeOnPair(const SParticle* from,
                                           const SParticle* to,
                                           SParticle * result) {
    int from_val, to_val;
    SParticle* target = result;

    // Burn parameter
    from_val = (int)(from->burn * 1000);
    to_val = (int)(to->burn * 1000);
    target->burn = FG_Rand(from_val, to_val) / 1000.0f;

    // Position X
    from_val = (int)(from->bbox.pos.x * 1000);
    to_val = (int)(to->bbox.pos.x * 1000);
    target->bbox.pos.x = FG_Rand(from_val, to_val) / 1000.0f;

    // Position Y
    from_val = (int)(from->bbox.pos.y * 1000);
    to_val = (int)(to->bbox.pos.y * 1000);
    target->bbox.pos.y = FG_Rand(from_val, to_val) / 1000.0f;

    // Position Z
    from_val = (int)(from->bbox.pos.z * 1000);
    to_val = (int)(to->bbox.pos.z * 1000);
    target->bbox.pos.z = FG_Rand(from_val, to_val) / 1000.0f;

    // Velocity X
    from_val = (int)(from->velocity.x * 1000);
    to_val = (int)(to->velocity.x * 1000);
    target->velocity.x = FG_Rand(from_val, to_val) / 1000.0f;

    // Velocity Y
    from_val = (int)(from->velocity.y * 1000);
    to_val = (int)(to->velocity.y * 1000);
    target->velocity.y = FG_Rand(from_val, to_val) / 1000.0f;

    // Velocity Z
    from_val = (int)(from->velocity.z * 1000);
    to_val = (int)(to->velocity.z * 1000);
    target->velocity.z = FG_Rand(from_val, to_val) / 1000.0f;

    // Fade speed
    from_val = (int)(from->fadeSpeed * 1000);
    to_val = (int)(to->fadeSpeed * 1000);
    target->fadeSpeed = FG_Rand(from_val, to_val) / 1000.0f;

    // Life
    from_val = (int)(from->life * 1000);
    to_val = (int)(to->life * 1000);
    target->life = FG_Rand(from_val, to_val) / 1000.0f;

    if(from->ttl != 0 || to->ttl != 0) {
        if(from->ttl < to->ttl) {
            from_val = from->ttl;
            to_val = to->ttl;
        } else {
            from_val = to->ttl;
            to_val = from->ttl;
        }
        int ttl = FG_Rand(from_val, to_val);
        target->setTTL(ttl);
    }

    // Size X
    from_val = (int)(from->bbox.size.x * 1000);
    to_val = (int)(to->bbox.size.x * 1000);
    target->bbox.size.x = FG_Rand(from_val, to_val) / 1000.0f;

    // Size Y
    from_val = (int)(from->bbox.size.y * 1000);
    to_val = (int)(to->bbox.size.y * 1000);
    target->bbox.size.y = FG_Rand(from_val, to_val) / 1000.0f;

    // Size Z
    from_val = (int)(from->bbox.size.z * 1000);
    to_val = (int)(to->bbox.size.z * 1000);
    target->bbox.size.z = FG_Rand(from_val, to_val) / 1000.0f;

    // Rotation X
    from_val = (int)(from->rotation.x * 1000);
    to_val = (int)(to->rotation.x * 1000);
    target->rotation.x = FG_Rand(from_val, to_val) / 1000.0f;

    // Rotation Y
    from_val = (int)(from->rotation.y * 1000);
    to_val = (int)(to->rotation.y * 1000);
    target->rotation.y = FG_Rand(from_val, to_val) / 1000.0f;

    // Rotation Z
    from_val = (int)(from->rotation.z * 1000);
    to_val = (int)(to->rotation.z * 1000);
    target->rotation.z = FG_Rand(from_val, to_val) / 1000.0f;

    // Angular Velocity X
    from_val = (int)(from->angularVelocity.x * 1000);
    to_val = (int)(to->angularVelocity.x * 1000);
    target->angularVelocity.x = FG_Rand(from_val, to_val) / 1000.0f;

    // Angular Velocity Y
    from_val = (int)(from->angularVelocity.y * 1000);
    to_val = (int)(to->angularVelocity.y * 1000);
    target->angularVelocity.y = FG_Rand(from_val, to_val) / 1000.0f;

    // Angular Velocity Z
    from_val = (int)(from->angularVelocity.z * 1000);
    to_val = (int)(to->angularVelocity.z * 1000);
    target->angularVelocity.z = FG_Rand(from_val, to_val) / 1000.0f;

    // Texture id
    from_val = (int)from->texIndex;
    to_val = (int)to->texIndex;
    target->texIndex = FG_Rand(from_val, to_val);

    // Data
    target->data = NULL;

    // Spawn Time
    //    target->spawn_time = FG_HardwareState->getTS();
    // #FIXME - time usage

    fgColor4f color;

    // Color R
    from_val = (int)(from->color.r * 1000);
    to_val = (int)(to->color.r * 1000);
    color.r = (float)FG_Rand(from_val, to_val) / 1000.0f;

    // Color G
    from_val = (int)(from->color.g * 1000);
    to_val = (int)(to->color.g * 1000);
    color.g = (float)FG_Rand(from_val, to_val) / 1000.0f;

    // Color B
    from_val = (int)(from->color.b * 1000);
    to_val = (int)(to->color.b * 1000);
    color.b = (float)FG_Rand(from_val, to_val) / 1000.0f;

    // Color A
    from_val = (int)(from->color.a * 1000);
    to_val = (int)(to->color.a * 1000);
    color.a = (float)FG_Rand(from_val, to_val) / 1000.0f;

    target->setColor(color);
}

/**
 * 
 * @param outputParticle
 */
void gfx::CParticleEffect::basicCalculate(SParticle* outputParticle) {
    // MOVEMENT
    outputParticle->bbox.pos.x += outputParticle->velocity.x * timesys::elapsed();
    outputParticle->bbox.pos.y += outputParticle->velocity.y * timesys::elapsed();
    outputParticle->bbox.pos.z += outputParticle->velocity.z * timesys::elapsed();

    // ROTATION
    outputParticle->rotation.x += outputParticle->angularVelocity.x * timesys::elapsed();
    outputParticle->rotation.y += outputParticle->angularVelocity.y * timesys::elapsed();
    outputParticle->rotation.z += outputParticle->angularVelocity.z * timesys::elapsed();

    // FADING
    outputParticle->life -= outputParticle->fadeSpeed * timesys::elapsed();

    // LIFE AS SIZE
    if(isLifeAsSize()) {
        outputParticle->bbox.size.x = fabs(outputParticle->life);
        outputParticle->bbox.size.y = fabs(outputParticle->life);
        outputParticle->bbox.size.z = fabs(outputParticle->life);
    }

    if(isParamsActive()) {
        // This actions will work properly only if the particle TTL parameter is set
        // Size
        float elapsed = timesys::elapsed();
        float ttl = (float)outputParticle->ttl / 1000.0f;
        outputParticle->bbox.size += (m_endSize - m_startSize) / ttl * elapsed;
        fgColor4f &color = outputParticle->color;
        color += (m_endColor - m_startColor) / ttl * elapsed;
        if(color.r < 0.0f)
            color.r = 0.0f;
        if(color.r > 1.0f)
            color.r = 1.0f;

        if(color.g < 0.0f)
            color.g = 0.0f;
        if(color.g > 1.0f)
            color.g = 1.0f;

        if(color.b < 0.0f)
            color.b = 0.0f;
        if(color.b > 1.0f)
            color.b = 1.0f;

        if(color.a < 0.0f)
            color.a = 0.0f;
        if(color.a > 1.0f)
            color.a = 1.0f;
    }
}
