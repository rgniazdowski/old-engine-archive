//
//  PsParticleEffectCircular.cpp
//  blocks
//
//  Created by Sebastian Gniazdowski on 18.08.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "fgPsParticleEffectCircular.h"

#include <cstdlib>

/**
 * Public constructor
 */
ParticleEffectCircular::ParticleEffectCircular() : m_current_insert_idx(0), m_dummy_count(0), m_overwrite_once_flag(0) {
    m_type = CIRCULAR;
}

/**
 * Public destructor
 */
ParticleEffectCircular::~ParticleEffectCircular() { }

/**
 * Sets m_maxCount, which implies resetting the object
 */
void ParticleEffectCircular::setMaxCount(int max_count) {
    ParticleEffect::setMaxCount(max_count);
    Particle dummy_particle = Particle();

    // Size == INT_MAX -> object is DUMMY and
    // should not be removed – but overwritten
    dummy_particle.size = float(INT_MAX);

    // ALL FIELDS ARE DUMMIES AT START
    m_particles.resize(max_count);
    for(fgVector<Particle>::iterator it = m_particles.begin(); it != m_particles.end(); it++)
        *it = dummy_particle;

    m_dummy_count = maxCount();

    m_current_insert_idx = 0;
}

/**
 * CIRCULAR MODE particle insert - always accepts new particle (deleting old if needed)
 */
fgBool ParticleEffectCircular::add(Particle* particle) {
    // OVERWRITE LAST STORED PARTICLE?
    if(m_overwrite_once_flag) {
        m_overwrite_once_flag = false;
        if(m_current_insert_idx == 0)
            m_current_insert_idx = maxCount() - 1;
        else
            m_current_insert_idx--;
    }

    // ALIVE particle will be written, check if a DUMMY will be deleted
    if(isDummy(m_current_insert_idx)) {
        m_dummy_count--;

        if(m_dummy_count < 0) {
            FG_LOG::PrintError("INCONSISTENCY! m_dummy_count[%d] < 0!", m_dummy_count);
        }
    }

    m_particles[ m_current_insert_idx ] = *particle;

    // Move to new insert position
    m_current_insert_idx = (m_current_insert_idx + 1) % maxCount();

    return FG_TRUE;
}

/**
 * Batch-add of particles. Number of inserts is limited to maxCount
 */
fgBool ParticleEffectCircular::addGroup(Particle *particles, int count) {
    if(count <= 0)
        return FG_FALSE;

    if(particles == NULL)
        return FG_FALSE;

    // There is no point in adding > maxCount() elements
    for(int i = 0; i < count && i < maxCount(); i++) {
        if(!add(&particles[i]))
            return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * Adds random Particle, built upon values in [from->some_field, to->some_field]
 */
fgBool ParticleEffectCircular::addRandom(Particle *from, Particle *to) {
    if(from == NULL || to == NULL)
        return FG_FALSE;

    Particle result;

    randomizeOnPair(from, to, &result);

    return add(&result);
}

/**
 * Batch-add with randomization
 */
fgBool ParticleEffectCircular::addRandomGroup(Particle *from, Particle *to, int count) {
    if(from == NULL || to == NULL) {
        return FG_FALSE;
    }

    for(int i = 0; i < count && i < maxCount(); i++) {
        addRandom(from, to);
    }

    // Polityka: true wtedy, gdy dodano tyle, ile zlecono
    if(count > maxCount()) {
        return FG_FALSE;
    }

    return FG_TRUE;
}
