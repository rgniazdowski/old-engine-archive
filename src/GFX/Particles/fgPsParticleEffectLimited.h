/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
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
    virtual fgBool add(Particle *particle);

    /**
     * Batch-add
     */
    virtual fgBool addGroup(Particle *particles, int count);

    /**
     * Adds random Particle, built upon values in [from->some_field, to->some_field]
     */
    virtual fgBool addRandom(Particle *from, Particle *to);

    /**
     * Batch-add with randomization
     */
    fgBool addRandomGroup(Particle *from, Particle *to, int count);

};

#endif