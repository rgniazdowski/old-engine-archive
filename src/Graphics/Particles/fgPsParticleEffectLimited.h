/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
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
    ~ParticleEffectLimited();

    /**
     * Removes given index. The element
     * is truly removed from array.
     * Order of elements might change.
     */
    virtual void remove(int which);

    /**
     * NORMAL MODE particle insert - can decline insertion
     */
    virtual bool add(Particle *particle);

    /**
     * Batch-add
     */
    virtual bool addGroup(Particle *particles, int count);

    /**
     * Adds random Particle, built upon values in [from->some_field, to->some_field]
     */
    virtual bool addRandom(Particle *from, Particle *to);

    /**
     * Batch-add with randomization
     */
    bool addRandomGroup(Particle *from, Particle *to, int count);

};

#endif
