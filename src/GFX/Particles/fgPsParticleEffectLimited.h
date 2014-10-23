/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_PS_PARTICLE_EFFECT_LIMITED_H_
    #define _FG_PS_PARTICLE_EFFECT_LIMITED_H_

    #include "fgPsParticleEffect.h"

class ParticleEffectLimited : public ParticleEffect {
public:
    /**
     * Public constructor
     */
    ParticleEffectLimited();

    /**
     * Public destructor
     */
    virtual ~ParticleEffectLimited();

    /**
     * Removes given index. The element
     * is truly removed from array.
     * Order of elements might change.
     */
    virtual void remove(int which);

    /**
     * NORMAL MODE particle insert - can decline insertion
     */
    virtual fgBool add(fgParticle *particle);

    /**
     * Batch-add
     */
    virtual fgBool addGroup(fgParticle *particles, int count);

    /**
     * Adds random Particle, built upon values in [from->some_field, to->some_field]
     */
    virtual fgBool addRandom(fgParticle *from, fgParticle *to);

    /**
     * Batch-add with randomization
     */
    fgBool addRandomGroup(fgParticle *from, fgParticle *to, int count);

};

#endif
