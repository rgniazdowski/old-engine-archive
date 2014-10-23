/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * fgParticleSystem.h
 *
 *  Created on: 17-06-2012
 *      Author: Vigilant
 */

#ifndef _FG_PARTICLE_SYSTEM_H_
    #define _FG_PARTICLE_SYSTEM_H_

    #include <map>

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
class fgParticleSystem {

private:
    std::map<int, ParticleEffect *> m_particleEffects;
    //std::map<int, FlashEffect *> m_flashEffects;
    std::map<int, SpecialEffect *> m_specialEffects;
    std::map<int, fgVector<int> > m_effectGroups;

public:
    fgParticleSystem();
    virtual ~fgParticleSystem();

public:
    void addParticleEffect(int effect_id, ParticleEffect *particle_effect);
    void addSpecialEffect(int effect_id, SpecialEffect *special_effect);

    ParticleEffect *particleEffect(int effect_id);
    SpecialEffect *specialEffect(int effect_id);

    void removeParticleEffect(int effect_id);
    void removeSpecialEffect(int effect_id);

    void addEffectToGroup(int group_id, int effect_id);
    void removeEffectFromGroup(int group_id, int effect_id);

    void calculateGroup(int group_id);
    void drawGroup(int group_id);

    void calculateParticleEffect(int effect_id);
    void calculateSpecialEffect(int effect_id);

    void drawParticleEffect(int effect_id);
    void drawSpecialEffect(int effect_id);

    void clearGroups();
    void clearAll();
};

#endif /* PARTICLESYSTEM_H_ */
