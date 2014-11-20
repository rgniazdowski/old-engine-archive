/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_PS_SEQUENTIAL_EFFECT
    #define FG_INC_PS_SEQUENTIAL_EFFECT

// The limited-buffer (not circular-buffer) ParticleEffect* class
    //#include "fgPsParticleEffectLimited.h"

    #define OBJECT_SEQUENCE_MAX 16
    #if 0
class SequentialEffect : public fgParticleEffectLimited {
private:

    struct AdditionalData {
        int count_frames;
        int frame_duration;
        int64_t time_begin;
        int64_t time_last_frame;
        bool loop;
        bool delete_mark;
        AdditionalData() : count_frames(0), frame_duration(0), time_begin(0), time_last_frame(0), loop(false), delete_mark(false) { }
    };
    AdditionalData *m_data;
    int m_countData;
    int m_maxCountData;
public:
    SequentialEffect();
    SequentialEffect(int max_count);
    ~SequentialEffect();

    void setMaxCount(int max_count);
    void removeAll(void);
    void remove(int which);

    int addSequence(float x, float y, float z, float size, int count_frames, int frame_duration, bool loop);

    void calculate(void);
};
    #endif
#endif
