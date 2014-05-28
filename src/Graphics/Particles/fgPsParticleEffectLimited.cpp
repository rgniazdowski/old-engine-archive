/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgPsParticleEffectLimited.h"

#include <cstdlib>

/**
 * Public constructor
 */
ParticleEffectLimited::ParticleEffectLimited() {
    m_type = LIMITED;
}

/**
 * Public destructor
 */
ParticleEffectLimited::~ParticleEffectLimited() {

}

/**
 * Removes given index
 */
void ParticleEffectLimited::remove(int which)
{
    if( which > int(m_particles.size())-1 ) {
        FG_ErrorLog("Invalid index [which:%d] given to Limited::remove! Size:%d", which, m_particles.size());
        return;
    }

    if( 1 == m_particles.size() ) {
            m_particles.pop_back();
    } else {
        m_particles[ which ] = m_particles.back();
        m_particles.pop_back();
    }
}

/**
 * NORMAL MODE particle insert - can decline insertion
 */
bool ParticleEffectLimited::add(Particle *particle)
{
    // Normal insert – only when there is free space
    if( int(m_particles.size()) >= maxCount() )
        return false;

    // Incorrect input
    if( particle == NULL )
        return false;

    m_particles.push_back( *particle );

	return true;
}

/**
 * Batch-add
 */
bool ParticleEffectLimited::addGroup(Particle *particles, int count)
{
	if( int(m_particles.size()) >= maxCount() || count <= 0 )
		return false;

	if( particles == NULL )
		return false;

	for( int i=0; i<count; i++ )
	{
		if( !add(&particles[i]) )
			return false;
		if( int(m_particles.size()) == maxCount() && i < count-1 )
			return false;
		else if( int(m_particles.size()) == maxCount() && i < count )
			return true;
	}
	return true;
}

/**
 * Adds random Particle, built upon values in [from->some_field, to->some_field]
 */
bool ParticleEffectLimited::addRandom(Particle *from, Particle *to)
{
	if( int(m_particles.size()) >= maxCount() )
		return false;

	if(from == NULL || to == NULL)
		return false;

	Particle result;

    randomizeOnPair(from, to, &result);

    return add(&result);
}

/**
 * Batch-add with randomization
 */
bool ParticleEffectLimited::addRandomGroup(Particle *from, Particle *to, int count)
{
	if( int(m_particles.size()) >= maxCount() || count <= 0)
		return false;
	if(from == NULL || to == NULL)
		return false;

	for(int i=0;i<count;i++)
	{
		addRandom(from, to);
		if( int(m_particles.size()) == maxCount() && i < count-1 )
			return false;
		else if( int(m_particles.size()) == maxCount() && i < count )
			return true;
	}

	return true;
}

