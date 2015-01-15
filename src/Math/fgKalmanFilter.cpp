/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgCommon.h"
#include "fgKalmanFilter.h"

#include "fgLog.h"

void KalmanFilter::init(float q, float r, float p, float intial_value) {
    m_state.q = q;
    m_state.r = r;
    m_state.p = p;
    m_state.x = intial_value;
}

void KalmanFilter::update(float MEASUREMENT) {
    // Prediction update
    // Omit x = x
    m_state.p += m_state.q;

    // Measurement update
    m_state.k = m_state.p / (m_state.p + m_state.r);
    m_state.x += m_state.k * (MEASUREMENT - m_state.x);
    m_state.p = (1 - m_state.k) * m_state.p;
}

void TripleKalman::update(float data_x, float data_y, float data_z) {
    fx.update(data_x);
    fy.update(data_y);
    fz.update(data_z);
}

void TripleKalman::update_one(int which, float data) {
    switch(which) {
        case FIRST:
            fx.update(data);
            break;
        case SECOND:
            fy.update(data);
            break;
        case THRID:
            fz.update(data);
            break;
        default:
            FG_LOG_WARNING("TripleKalman::update_one with unknown which:%d", which);
    }
}
