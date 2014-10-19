/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

/*
 * KalmanFilter.h
 *
 *  Created on: 12-06-2012
 *      Author: sgniazdowski
 */

#ifndef _FG_MATH_KALMAN_FILTER_H_
    #define _FG_MATH_KALMAN_FILTER_H_

struct KalmanState {
    /// Process noise covariance
    float q;
    /// Measurement noise covariance
    float r;
    /// Value
    float x;
    /// Estimation error covariance
    float p;
    /// Kalman gain
    float k;
};

class KalmanFilter {
    KalmanState m_state;

public:
    void init(float q, float r, float p, float intial_value);
    void update(float measurement);
    /**
     * Get estimated value
     * @return Value as float
     */
    float value() const {
        return float(m_state.x);
    }
};

/// Integrates three KalmanFilters

class TripleKalman {
    KalmanFilter fx;
    KalmanFilter fy;
    KalmanFilter fz;

public:

    enum {
        FIRST = 1, SECOND = 2, THRID = 3
    };
    void update(float data_x, float data_y, float data_z);
    void update_one(int which, float data);
    KalmanFilter & x() {
        return fx;
    }
    KalmanFilter & y() {
        return fy;
    }
    KalmanFilter & z() {
        return fz;
    }
};

#endif /* KALMANFILTER_H_ */
