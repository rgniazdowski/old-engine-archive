/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * fgParticleSystem.cpp
 *
 *  Created on: 17-06-2012
 *      Author: Vigilant
 */

#include "fgParticleSystem.h"

#include <cmath>
#include <cstring>
#include <cstdlib>
#ifdef FG_USING_MARMALADE
#include "s3eTimer.h"
#endif

template <>
bool fgSingleton<fgParticleSystem>::instanceFlag = false;

template <>
fgParticleSystem *fgSingleton<fgParticleSystem>::instance = NULL;


fgParticleSystem::fgParticleSystem()
{
    /*
	 * GROUP MENU
	 */
	/*ObjectPulseEffect *object_pulse = new ObjectPulseEffect(OBJECT_PULSE_MAX);
	object_pulse->setAreaCheck(false);
	object_pulse->setAlphaActive(true);
	object_pulse->setDrawMode(ParticleEffect::MODE_2D);
	object_pulse->setLifeAsSize(true);
	object_pulse->setTexture(TEXTURE_PTR(Tex::PULSE_TEXTURE));
	object_pulse->setTextureXSize(1);
	object_pulse->setTextureYSize(1);
	addParticleEffect(EFFECT_MENU_PULSE, object_pulse);
	addEffectToGroup(GROUP_MENU_EFFECT, EFFECT_MENU_PULSE);
	*/


	/* Just testing, aktualnie dziala wyswietlanie efektow czasteczkowych w trybie 2D, 3D jeszcze w ogole nie testowane
	SequentialEffect *explosion_sequence = new SequentialEffect(OBJECT_SEQUENCE_MAX);
	explosion_sequence->setAreaCheck(false);
	explosion_sequence->setAlphaActive(true);
	explosion_sequence->setDrawMode(ParticleEffect::MODE_2D);
	explosion_sequence->setLifeAsSize(false);
	explosion_sequence->setTexture(TEXTURE_PTR(Tex::EXPLOSION_SEQUENCE_TEXTURE));
	explosion_sequence->setTextureXSize(8);
	explosion_sequence->setTextureYSize(8);
	addParticleEffect(EFFECT_SEQUENTIAL_EXPLOSION, explosion_sequence);
	addEffectToGroup(GROUP_MENU_EFFECT, EFFECT_SEQUENTIAL_EXPLOSION);
	*/
	/*
	 * EXPLOSION EFFECT
	 */
	/*
	ExplosionEffect *explosion_effect = new ExplosionEffect(ParticleEffect::MODE_2D, 1.0f);
	addSpecialEffect(EFFECT_EXPLOSION, explosion_effect);
	addEffectToGroup(GROUP_GAME_STAGE_EFFECT, EFFECT_EXPLOSION);
	*/
	/*
	 * FLYING DEBRIS EFFECT
	 */
/*	FlyingDebrisEffect *flying_debris_effect = new FlyingDebrisEffect(ParticleEffect::MODE_2D, 1.0f);
	flying_debris_effect->setRate(15);
	addSpecialEffect(EFFECT_FLYING_DEBRIS, flying_debris_effect);
	addEffectToGroup(GROUP_GAME_STAGE_EFFECT, EFFECT_FLYING_DEBRIS);
	*/
}

fgParticleSystem::~fgParticleSystem()
{
	// FIXME
	clearAll();
}

void fgParticleSystem::clearAll()
{
	// Removing all the particle effects from the database, calling destructors
	std::map<int, ParticleEffect *>::iterator particleIt;
	for(particleIt = m_particleEffects.begin(); particleIt != m_particleEffects.end(); particleIt++)
	{
		delete particleIt->second;
		m_particleEffects[particleIt->first] = NULL;
	}
	m_particleEffects.clear();

	/*
	// Removing all the flash effects from the database
	std::map<int, FlashEffect *>::iterator flashIt;
	for(flashIt = m_flashEffects.begin(); flashIt != m_flashEffects.end(); flashIt++)
	{
		delete flashIt->second;
		m_flashEffects[flashIt->first] = NULL;
	}
	m_flashEffects.clear();
	*/

	// Removing all the special effects from the database
	std::map<int, SpecialEffect *>::iterator specialIt;
	for(specialIt = m_specialEffects.begin(); specialIt != m_specialEffects.end(); specialIt++)
	{
		delete specialIt->second;
		m_specialEffects[specialIt->first] = NULL;
	}
	m_specialEffects.clear();

	// Clearing created effect groups
	clearGroups();
}

void fgParticleSystem::addParticleEffect(int effect_id, ParticleEffect *particle_effect)
{
	m_particleEffects[effect_id] = particle_effect;
}

/*
void fgParticleSystem::addFlashEffect(int effect_id, FlashEffect *flash_effect)
{
	m_flashEffects[effect_id] = flash_effect;
}
*/

void fgParticleSystem::addSpecialEffect(int effect_id, SpecialEffect *special_effect)
{
	m_specialEffects[effect_id] = special_effect;
}

ParticleEffect *fgParticleSystem::particleEffect(int effect_id)
{
	std::map<int, ParticleEffect *>::iterator pointer = m_particleEffects.find(effect_id);
	if(pointer != m_particleEffects.end()) {
		return pointer->second;
	}
	return NULL;
}

/*
FlashEffect *fgParticleSystem::flashEffect(int effect_id)
{
	std::map<int, FlashEffect *>::iterator pointer = m_flashEffects.find(effect_id);
	if(pointer != m_flashEffects.end()) {
		return pointer->second;
	}
	return NULL;
}
*/

SpecialEffect *fgParticleSystem::specialEffect(int effect_id)
{
	std::map<int, SpecialEffect *>::iterator pointer = m_specialEffects.find(effect_id);
	if(pointer != m_specialEffects.end()) {
		return pointer->second;
	}
	return NULL;
}

void fgParticleSystem::removeParticleEffect(int effect_id)
{
	delete m_particleEffects[effect_id];
	m_particleEffects[effect_id] = NULL;
	m_particleEffects.erase(effect_id);
}

/*
void fgParticleSystem::removeFlashEffect(int effect_id)
{
	delete m_flashEffects[effect_id];
	m_flashEffects[effect_id] = NULL;
	m_flashEffects.erase(effect_id);
}
*/

void fgParticleSystem::removeSpecialEffect(int effect_id)
{
	delete m_specialEffects[effect_id];
	m_specialEffects[effect_id] = NULL;
	m_specialEffects.erase(effect_id);
}

void fgParticleSystem::addEffectToGroup(int group_id, int effect_id)
{
	/* FIXME Need to check if there already is such effect ID */
	m_effectGroups[group_id].push_back(effect_id);
}

void fgParticleSystem::removeEffectFromGroup(int group_id, int effect_id)
{
	std::map<int, fgVector<int> >::iterator pointer = m_effectGroups.find(group_id);
	if(pointer == m_effectGroups.end())
		return;

	for(fgVector<int>::iterator iter = (*pointer).second.begin();
		iter != (*pointer).second.end();
		iter ++
    ) {
		if((*iter) == effect_id)
		{
			(*pointer).second.erase(iter);
			return;
		}
	}
}

void fgParticleSystem::calculateGroup(int group_id)
{

	std::map<int, fgVector<int> >::iterator pointer = m_effectGroups.find(group_id);
	if(pointer == m_effectGroups.end())
		return;
	for(fgVector<int>::iterator iter = (*pointer).second.begin();
		iter != (*pointer).second.end();
		iter++) {
			calculateParticleEffect(*iter);
			//calculateFlashEffect(*iter);
			calculateSpecialEffect(*iter);
	}
}

void fgParticleSystem::drawGroup(int group_id)
{
	std::map<int, fgVector<int> >::iterator pointer = m_effectGroups.find(group_id);
	if(pointer == m_effectGroups.end())
		return;
	for(fgVector<int>::iterator iter = (*pointer).second.begin();
		iter != (*pointer).second.end();
		iter++) {
			drawParticleEffect(*iter);
			//drawFlashEffect(*iter);
			drawSpecialEffect(*iter);
	}
}

void fgParticleSystem::calculateParticleEffect(int effect_id)
{
	std::map<int, ParticleEffect *>::iterator pointer = m_particleEffects.find(effect_id);
	if(pointer != m_particleEffects.end()) {
		(*pointer).second->calculate();
	}
}

/*
void fgParticleSystem::calculateFlashEffect(int effect_id)
{
	std::map<int, FlashEffect *>::iterator pointer = m_flashEffects.find(effect_id);
	if(pointer != m_flashEffects.end()) {
		(*pointer).second->calculate();
	}
}
*/

void fgParticleSystem::calculateSpecialEffect(int effect_id)
{
	std::map<int, SpecialEffect *>::iterator pointer = m_specialEffects.find(effect_id);
	if(pointer != m_specialEffects.end()) {
		(*pointer).second->calculate();
	}
}

void fgParticleSystem::drawParticleEffect(int effect_id)
{
	std::map<int, ParticleEffect *>::iterator pointer = m_particleEffects.find(effect_id);
	if(pointer != m_particleEffects.end()) {
		(*pointer).second->draw();
	}
}

/*
void fgParticleSystem::drawFlashEffect(int effect_id)
{
	std::map<int, FlashEffect *>::iterator pointer = m_flashEffects.find(effect_id);
	if(pointer != m_flashEffects.end()) {
		(*pointer).second->draw();
	}
}
*/

void fgParticleSystem::drawSpecialEffect(int effect_id)
{
	std::map<int, SpecialEffect *>::iterator pointer = m_specialEffects.find(effect_id);
	if(pointer != m_specialEffects.end()) {
		(*pointer).second->draw();
	}
}

void fgParticleSystem::clearGroups()
{
	for(std::map<int, fgVector<int> >::iterator pointer = m_effectGroups.begin();
		pointer != m_effectGroups.end();
		pointer++) {
			(*pointer).second.clear();		
	}
	m_effectGroups.clear();
}
