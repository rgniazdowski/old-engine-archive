/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include <cstdlib>
#include <cmath>
#include <cstring>

#include "fgPsSequentialEffect.h"
#include "Hardware/fgHardwareState.h"
#include "Util/fgMemory.h"

#if 0
SequentialEffect::~SequentialEffect() {
    fgFree(m_data);
    m_data = NULL;
    m_countData = 0;
}

SequentialEffect::SequentialEffect() : m_data(NULL), m_countData(0), m_maxCountData(0) { }

SequentialEffect::SequentialEffect(int max_count) : m_data(NULL), m_countData(0), m_maxCountData(0) {
    setMaxCount(max_count);
}

void SequentialEffect::setMaxCount(int max_count) {
    if(m_data == NULL) {
        CParticleEffect::setMaxCount(max_count);
        m_maxCountData = max_count;
        m_data = fgMalloc<AdditionalData>(max_count);
        m_countData = 0;
    }
}

void SequentialEffect::removeAll(void) {
    int l_count = m_countData;
    for(int i = 0; i < l_count; i++) {
        SequentialEffect::remove(0);
        fgParticleEffectLimited::remove(0);
    }
    m_countData = 0;
}

void SequentialEffect::remove(int which) {
    if(m_data == NULL || m_countData == 0)
        return;

    // Only one element -> no need of any moving
    if(m_countData == 1) {
        m_countData--;
    } else {
        // Copy from last & count --
        // This removal method can be used when
        // ORDER of elements is not important
        m_data[which] = m_data[m_countData - 1];
        m_countData--;
    }
    fgParticleEffectLimited::remove(which);
}

int SequentialEffect::addSequence(float x, float y, float z, float size, int count_frames, int frame_duration, bool loop) {
    int idx = 0;
    if(m_countData >= m_maxCountData)
        return -1;

    idx = m_countData;
    SParticle particle;

    m_countData++;

    m_data[idx].count_frames = count_frames;
    m_data[idx].frame_duration = frame_duration;
    m_data[idx].delete_mark = false;
    m_data[idx].loop = loop;
    m_data[idx].time_begin = FG_HardwareState->getTS();
    m_data[idx].time_last_frame = FG_HardwareState->getTS();

    fgColor color;
    //color.Set(255,255,255,255);
    //	particle.setColor(color);
    particle.data = &m_data[idx];
    particle.velocity.x = 0.0f;
    particle.velocity.y = 0.0f;
    particle.velocity.z = 0.0f;
    particle.fadeSpeed = 0.0f;
    particle.life = size;
    //particle.size = size;
    particle.bbox.size.x = size;
    particle.bbox.size.y = size;
    particle.bbox.size.z = size;
    particle.rotation.x = 0.0f;
    particle.rotation.y = 0.0f;
    particle.rotation.z = 0.0f;
    particle.angularVelocity.x = 0.0f;
    particle.angularVelocity.y = 0.0f;
    particle.angularVelocity.z = 0.0f;
    particle.bbox.pos.x = x;
    particle.bbox.pos.y = y;
    particle.bbox.pos.z = z;
    //particle.texture_id = 0;

    fgParticleEffectLimited::add(&particle);
    return idx;
}

void SequentialEffect::calculate(void) {
    return;
    SParticle *particle;
    for(int i = 0; i < m_countData; i++) {
        particle = &(particlesData()[i]);
        if((int64_t)FG_HardwareState->getTS() - m_data[i].time_last_frame >= m_data[i].frame_duration) {
#if 0
            particle->texture_id++;
            if(particle->texture_id >= m_data[i].count_frames) {
                if(m_data[i].loop == false) {
                    m_data[i].delete_mark = true;
                } else if(m_data[i].loop == true) {
                    particle->texture_id = 0;
                    m_data[i].delete_mark = false;
                }
            }
#endif
            m_data[i].time_last_frame = FG_HardwareState->getTS();
        }
        if(m_data[i].delete_mark) {
            SequentialEffect::remove(i);
        }
    }
    CParticleEffect::calculate();
}

#endif