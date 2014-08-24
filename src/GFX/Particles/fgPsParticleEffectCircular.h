/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_PS_PARTICLE_EFFECT_CIRCULAR_H_
#define _FG_PS_PARTICLE_EFFECT_CIRCULAR_H_

#include <limits.h>
#include "fgPsParticleEffect.h"
#include "fgLog.h"

/*
 *
 */
class ParticleEffectCircular : public ParticleEffect {

protected:
    // The CIRCULAR insert index
    int m_current_insert_idx;

    // Dummy counter
    int m_dummy_count;

    /**
     * Changes one add() call: to overwrite
     * last Particle – instead of inserting!
     */
    bool m_overwrite_once_flag;

public:
    /**
     * Public constructor
     */
    ParticleEffectCircular();

    /**
     * Public destructor
     */
    ~ParticleEffectCircular();

    /**
     * Make add_custom() call to OVERWRITE last Particle
     * This will be used to solve the TRAIL - EDGE gap!
     */
    void setOverwriteOnce() {
        m_overwrite_once_flag = true;
    }

    /**
     * Sets m_maxCount, which implies resetting the object
     */
    void setMaxCount(int max_count);

    /**
     * Oblicza indeks pierwszej (czyli: najstarszej) Particle
     * Bufor jest cykliczny, i trzeba "zawijac" indeks
     */
    int firstAliveIdx() const {
        unsigned int ualive = (unsigned int) aliveCount();
        unsigned int uidx = (unsigned int) m_current_insert_idx;
        unsigned int umax_count = maxCount();

        uidx = (uidx - ualive) % umax_count;

        //FG_LOG::PrintDebug("firstAliveIdx computed: %d  [alive:%d, idx:%d, max:%d]", int(uidx), aliveCount(), m_current_insert_idx, maxCount() );

        return int(uidx);
    }

    /**
     * Returns n.of ALIVE cells
     */
    int aliveCount() const {
        return maxCount() - m_dummy_count;
    }

    /**
     * Checks if particle [idx] is INACTIVE FILLER
     */
    bool isDummy(int idx) const {
        return m_particles[idx].size > float(INT_MAX) / 2.0f;
    }

    /**
     * Sets particle [idx] to INACTIVE FILLER
     */
    bool setDummy(int idx) {
        if( int(m_particles.size()) != maxCount() || idx >= maxCount() ) {
            FG_LOG::PrintError("########## Inconsistent ParticleEffectCircular: size[%d], maxCount[%d], which[%d] ##########", m_particles.size(), maxCount(), idx);
            return false;
        }

        // DUMMY particle will be written, check if any ALIVE will be deleted
        if( !isDummy(idx) ) {
            m_dummy_count ++;
        }

        m_particles[idx].size = float(INT_MAX);

        return true;
    }

    /**
     * SETDUMMY ALIAS
     * Circular buffer does not remove elements
     */
    virtual void remove(int which) {
        setDummy(which);
    }

    /**
     * THIS IS CIRCULAR MODE:
     * -----------------
     * a. Number of Particles is constant (m_maxCount)
     * b. There is no FREE SPACE
     * c. Particles can be DEAD (::size == INT_MAX) or ALIVE (::size != INT_MAX)
     * d. Method add() overwrites DEAD or ALIVE cell under m_current_insert_idx
     * e. Then, m_current_index_idx ++ MODULO m_maxCount
     *
     */
    virtual fgBool add(Particle* particle);

    /**
     * Batch-add. Number of inserts is limited to maxCount()
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
