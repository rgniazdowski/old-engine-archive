/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/*
 * fgParticleSystem.h
 *
 *  Created on: 17-06-2012
 *      Author: Vigilant
 */
#ifndef _FG_PARTICLE_SYSTEM_H_
#define _FG_PARTICLE_SYSTEM_H_

#include "../../fgSingleton.h"

#include <map>
#include "IwArray.h"

#include "fgPsFlashEffect.h"
#include "fgPsSpecialEffect.h"
#include "fgPsExplosionEffect.h"
#include "fgPsSequentialEffect.h"
#include "fgPsParticleEffect.h"

// FIXME

// Efekt flasha na ekranie
#define EFFECT_FLASH_SCREEN	 			1
// Efekt przejscia miedzy ekranami menu
#define EFFECT_MENU_TRANSITION			2
// Efekt sekwencyjny ekslozji, klatkowa animacja
#define EFFECT_SEQUENTIAL_EXPLOSION		4
// Efekt specjalny zbudowany z roznych rodzajow particle emiterow
#define EFFECT_EXPLOSION				5


// Efekt dotyczy glownego ekranu menu (rowniez ekran w trakcie gry)
#define GROUP_MENU_EFFECT				0

// Efekt dotyczy tla glownego menu (bez ekranu w trakcie gry)
#define GROUP_BACKGROUND_MENU_EFFECT	1

// Efekt dotyczy tylko ekranu gry
#define GROUP_GAME_STAGE_EFFECT			2

/**
 *
 */
class fgParticleSystem : public fgSingleton<fgParticleSystem>
{
	friend class fgSingleton<fgParticleSystem>;

private:
	std::map<int, ParticleEffect *> m_particleEffects;
	//std::map<int, FlashEffect *> m_flashEffects;
	std::map<int, SpecialEffect *> m_specialEffects;
	std::map<int, CIwArray<int> > m_effectGroups;
	
protected:
	fgParticleSystem();
	~fgParticleSystem();

public:
	void addParticleEffect(int effect_id, ParticleEffect *particle_effect);
	//void addFlashEffect(int effect_id, FlashEffect *flash_effect);
	void addSpecialEffect(int effect_id, SpecialEffect *special_effect);

	ParticleEffect *particleEffect(int effect_id);
	//FlashEffect *flashEffect(int effect_id);
	SpecialEffect *specialEffect(int effect_id);

	void removeParticleEffect(int effect_id);
	//void removeFlashEffect(int effect_id);
	void removeSpecialEffect(int effect_id);

	void addEffectToGroup(int group_id, int effect_id);
	void removeEffectFromGroup(int group_id, int effect_id);

	void calculateGroup(int group_id);
	void drawGroup(int group_id);

	void calculateParticleEffect(int effect_id);
	//void calculateFlashEffect(int effect_id);
	void calculateSpecialEffect(int effect_id);

	void drawParticleEffect(int effect_id);
	//void drawFlashEffect(int effect_id);
	void drawSpecialEffect(int effect_id);

	void clearGroups();
	void clearAll();
};

#define PARTICLE(EFFECT_ID)					((ParticleEffect *)fgParticleSystem::getInstance()->particleEffect(EFFECT_ID))
//#define EXPLOSION(EFFECT_ID)				((ExplosionEffect *)fgParticleSystem::getInstance()->particleEffect(EFFECT_ID))
//#define ELLIPSE_FLAME(EFFECT_ID)			((EllipseFlameEffect*)fgParticleSystem::getInstance()->particleEffect(EFFECT_ID))
#define SEQUENCE(EFFECT_ID)					((SequentialEffect *)fgParticleSystem::getInstance()->particleEffect(EFFECT_ID))
//#define MENU_BACKGROUND(EFFECT_ID)			((MenuBackgroundEffect *)fgParticleSystem::getInstance()->particleEffect(EFFECT_ID))

//#define FLASH(EFFECT_ID)					((FlashEffect *)fgParticleSystem::getInstance()->flashEffect(EFFECT_ID))
//#define SCREEN_FLASH(EFFECT_ID)				((ScreenFlashEffect *)fgParticleSystem::getInstance()->flashEffect(EFFECT_ID))

#define SPECIAL(EFFECT_ID)					((SpecialEffect *)fgParticleSystem::getInstance()->specialEffect(EFFECT_ID))
#define EXPLOSION(EFFECT_ID)				((ExplosionEffect *)fgParticleSystem::getInstance()->specialEffect(EFFECT_ID))

#define FG_ParticleSystem fgParticleSystem::getInstance()

#endif /* PARTICLESYSTEM_H_ */
