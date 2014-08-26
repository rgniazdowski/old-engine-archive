/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgPsParticleEffectLimited.h"
#include "fgLog.h"

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
        FG_LOG::PrintError("Invalid index [which:%d] given to Limited::remove! Size:%d", which, m_particles.size());
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
fgBool ParticleEffectLimited::add(Particle *particle)
{
    // Normal insert – only when there is free space
    if( int(m_particles.size()) >= maxCount() )
        return FG_FALSE;

    // Incorrect input
    if( particle == NULL )
        return FG_FALSE;

    m_particles.push_back( *particle );

	return FG_TRUE;
}

/**
 * Batch-add
 */
fgBool ParticleEffectLimited::addGroup(Particle *particles, int count)
{
	if( int(m_particles.size()) >= maxCount() || count <= 0 )
		return FG_FALSE;

	if( particles == NULL )
		return FG_FALSE;

	for( int i=0; i<count; i++ )
	{
		if( !add(&particles[i]) )
			return FG_FALSE;
		if( int(m_particles.size()) == maxCount() && i < count-1 )
			return FG_FALSE;
		else if( int(m_particles.size()) == maxCount() && i < count )
			return FG_TRUE;
	}
	return FG_TRUE;
}

/**
 * Adds random Particle, built upon values in [from->some_field, to->some_field]
 */
fgBool ParticleEffectLimited::addRandom(Particle *from, Particle *to)
{
	if( int(m_particles.size()) >= maxCount() )
		return FG_FALSE;

	if(from == NULL || to == NULL)
		return FG_FALSE;

	Particle result;

    randomizeOnPair(from, to, &result);

    return add(&result);
}

/**
 * Batch-add with randomization
 */
fgBool ParticleEffectLimited::addRandomGroup(Particle *from, Particle *to, int count)
{
	if( int(m_particles.size()) >= maxCount() || count <= 0)
		return FG_FALSE;
	if(from == NULL || to == NULL)
		return FG_FALSE;

	for(int i=0;i<count;i++)
	{
		addRandom(from, to);
		if( int(m_particles.size()) == maxCount() && i < count-1 )
			return FG_FALSE;
		else if( int(m_particles.size()) == maxCount() && i < count )
			return FG_TRUE;
	}

	return FG_TRUE;
}
