/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgBuildConfig.h"
#include "fgLog.h"

#include <cmath>
#include <cstring>

#ifdef FG_USING_MARMALADE_SENSORS
#include "s3eTypes.h"
#include "s3eAccelerometer.h"
#include "s3eTimer.h"
#endif

#include "fgSensors.h"

using namespace fg;

//------------------------------------------------------------------------------

static char const * const FG_NONE_TXT = "";
static char const * const FG_SENSOR_ACCELEROMETER_TXT = "Accelerometer";
static char const * const FG_SENSOR_COMPASS_TXT = "Compass";

static char const * const FG_UNKNOWN_TXT = "Unknown";
static char const * const FG_PORTRAIT_TXT = "Portrait";
static char const * const FG_UPSIDE_DOWN_TXT = "Portrait upside down";
static char const * const FG_LANDSCAPE_LEFT_TXT = "Landscape left";
static char const * const FG_LANDSCAPE_RIGHT_TXT = "Landscape right";
static char const * const FG_FACE_UP_TXT = "Face up";
static char const * const FG_FACE_DOWN_TXT = "Face down";

/// Names of the available sensors
const char* CSensors::s_sensorsNames[CSensors::FG_SENSORS_TYPES] = {
                                                                      FG_SENSOR_ACCELEROMETER_TXT,
                                                                      FG_SENSOR_COMPASS_TXT
};

int32_t HarvestCallback(void* systemData, void* userData) {
    CSensors *self = (CSensors *)userData;
#ifdef FG_USING_MARMALADE_SENSORS
    // Are sensors running?
    if(FG_FALSE == self->m_isRunning) {
        // If no, skip any operation (in
        // particular, do not reset the timer).
        return 0;
    }

    int32 x = s3eAccelerometerGetX();
    int32 y = s3eAccelerometerGetY();
    int32 z = s3eAccelerometerGetZ();

    // Adding epsilon to ensure no zero-division error
    float mag = 0.001f + sqrtf((x * x) + (y * y) + (z * z));

    self->harvestData(CSensors::FG_SENSORS_ACCELEROMETER, x / mag, y / mag, z / mag);

    int result = s3eTimerSetTimer(80, &HarvestCallback, (void *)self);
    if(result == S3E_RESULT_ERROR) {
        FG_LOG_ERROR("Setting continued sensors-callback failed!");
        return 0;
    }
#endif // FG_USING_MARMALADE_SENSORS
    return 0;
}
//------------------------------------------------------------------------------

CSensors::CSensors() : m_isRunning(false), m_arbIdx(0), m_unlockTS(0), m_accelBaseLocked(false) {
    memset(m_sensorsErrors, 0, sizeof (m_sensorsErrors));
    memset(m_sensorsValues, 0, sizeof (m_sensorsValues));
    memset(m_accelRawBase, 0, sizeof (m_accelRawBase));
    memset(m_accelFinalBase, 0, sizeof (m_accelFinalBase));
}
//------------------------------------------------------------------------------

CSensors::~CSensors() {
    stop();
}
//------------------------------------------------------------------------------

fgBool CSensors::start(void) {
#ifdef FG_USING_MARMALADE_SENSORS
    m_sensorsErrors[ FG_SENSORS_ACCELEROMETER ] = s3eAccelerometerStart();
    if(m_sensorsErrors[ FG_SENSORS_ACCELEROMETER ] == S3E_RESULT_ERROR) {
        FG_LOG_ERROR("ERROR! Accelerometer did not activate!");
        return FG_FALSE;
    }

    // init(float q, float r, float initial_error, float intial_value)
    // q - process noise (covariance)
    // r - sensor noise (covariance)
    // initial_error - (covariance)
    // initial_value - (value)
    m_filters[FG_SENSORS_ACCELEROMETER].getX().init(0.8f, 0.2f, 0.05f, 0.1f);
    m_filters[FG_SENSORS_ACCELEROMETER].getY().init(0.8f, 0.2f, 0.05f, 0.1f);
    m_filters[FG_SENSORS_ACCELEROMETER].getZ().init(0.8f, 0.2f, 0.05f, 0.1f);

    m_isRunning = FG_TRUE;

    // Setup a timer that will harvest sensor data in periodic manner
    // The timer receives pointer to this object! :)
    int result = s3eTimerSetTimer(80, &HarvestCallback, (void *)this);
    if(result == S3E_RESULT_ERROR) {
        FG_LOG_ERROR("Setting sensors-callback failed!");
        m_isRunning = FG_FALSE;
        return FG_FALSE;
    }
#endif // FG_USING_MARMALADE_SENSORS
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CSensors::stop(void) {
    m_isRunning = FG_FALSE;
#ifdef FG_USING_MARMALADE_SENSORS
    s3eAccelerometerStop();
#endif // FG_USING_MARMALADE_SENSORS
}
//------------------------------------------------------------------------------

const char* CSensors::errorCodeText(int errorCode) {
    // TODO if needed
    FG_LOG_ERROR("Sensors::errorCodeText called (its TODO)");
    return "UNKNOWN";
}
//------------------------------------------------------------------------------

void CSensors::getAccelerometer(float *x, float *y, float *z) {
#if 1
    *x = m_filters[FG_SENSORS_ACCELEROMETER].getX().value();
    *y = m_filters[FG_SENSORS_ACCELEROMETER].getY().value();
    *z = m_filters[FG_SENSORS_ACCELEROMETER].getZ().value();
#else
    *x = m_sensorsValues[ACCELEROMETER][0];
    *y = m_sensorsValues[ACCELEROMETER][1];
    *z = m_sensorsValues[ACCELEROMETER][2];
#endif
}
//------------------------------------------------------------------------------

void CSensors::getAccelerometerBase(float *x, float *y) {
    *x = m_accelFinalBase[0];
    *y = m_accelFinalBase[1];
}
//------------------------------------------------------------------------------

void CSensors::harvestData(int type, float x, float y, float z) {
    // Shortcut for ACCEL
    if(type != FG_SENSORS_ACCELEROMETER)
        return;

    // Store values
    m_sensorsValues[type][0] = x;
    m_sensorsValues[type][1] = y;
    m_sensorsValues[type][2] = z;

    //
    // UPDATE ACCELEROMETER
    //

    m_filters[type].update(x, y, z);

    //
    // UPDATE BASE OF ACCELEROMETER
    // Only X & Y are computed
    //

    if(isBaseLocked())
        return;

    static int counter = 0;

    if(counter++ % 7)
        return;

    float prev_sum = m_accelRawBase[m_arbIdx][0] + m_accelRawBase[m_arbIdx][1];

    float fx = m_filters[type].getX().value();
    float fy = m_filters[type].getY().value();

    float new_sum = fx + fy;

    // Is difference between NEW & OLD larger, than the OLD?
    //
    // fabs( prev_sum - new_sum ) > fabs(prev_sum)
    //      - new_sum < 0, prev_sum < 0,    |new_sum - prev_sum| > 0.5 x |prev_sum|
    //                                          – gdy new_sum < 1.5 x prev_sum
    //                                          - gdy new_sum > 0.5 x prev_sum
    //
    //      - new_sum < 0, prev_sum > 0,    |new_sum - prev_sum| > 0.5 x |prev_sum|
    //                                          – zawsze, i dobrze – przejscie na
    //                                            przeciwny znak to zmiana o 100%
    //
    //      - new_sum > 0, prev_sum < 0,    |new_sum - prev_sum| > 0.5 x |prev_sum|
    //                                          – zawsze, i dobrze – przejscie na
    //                                            przeciwny znak to zmiana o 100%
    //
    //      - new_sum > 0, prev_sum > 0,    |new_sum - prev_sum| > 0.5 x |prev_sum|
    //                                          – gdy new_sum > 1.5 x prev_sum
    //                                          – gdy new_sum < 0.5 x prev_sum
    //
    // To zawiera w sobie 2x zwiekszenie wartosci bezwzglednej, oraz 2x zmniejszenie
    // wartosci bezwzglednej.

    // Jezeli zmiana jest drastyczna, jest uwzgledniana,
    // ale w mniejszym stopniu (tj. roznica jest dzielona)
    if(prev_sum < 0 && new_sum < 0) {
        if(new_sum < 1.45f * prev_sum) {
            // Nowy zbyt szybko powiekszyl sie
            // -> zmniejszenie wartosci bezwzglednej NOWYCH danych
            fx *= 0.8f;
            fy *= 0.8f;
        } else if(new_sum > 0.55f * prev_sum) {
            // Nowy zbyt szybko zmalal
            // -> zwiekszenie war. bezwz. NOWYCH danych
            fx *= 1.2f;
            fy *= 1.2f;
        }
    } else if(prev_sum > 0 && new_sum > 0) {
        if(new_sum > 1.45f * prev_sum) {
            // Nowy zbyt szybko powiekszyl sie
            // -> zmniejszenie wartosci bezwzglednej NOWYCH danych
            fx *= 0.8f;
            fy *= 0.8f;
        } else if(new_sum < 0.55f * prev_sum) {
            // Nowy zbyt szybko zmalal
            // -> zwiekszenie war. bezwz. NOWYCH danych
            fx *= 1.2f;
            fy *= 1.2f;
        }
    } else {
        // Zmiana znaku – wytracenie NOWYCH wartosci, tylko zmiana znaku
        fx *= 0.15f;
        fy *= 0.15f;
    }

    //
    // STORE RAW BASE
    //

    m_arbIdx = (m_arbIdx + 1) % FG_SENSORS_BASE_SIZE;
    m_accelRawBase[m_arbIdx][0] = fx;
    m_accelRawBase[m_arbIdx][1] = fy;

    //
    // COMPUTE FINAL BASE - srednia arytmetyczna
    //

    m_accelFinalBase[0] = m_accelRawBase[0][0] + m_accelRawBase[1][0] + m_accelRawBase[2][0] + m_accelRawBase[3][0];
    m_accelFinalBase[1] = m_accelRawBase[0][1] + m_accelRawBase[1][1] + m_accelRawBase[2][1] + m_accelRawBase[3][1];

    // Stlumienie wartosci X (+2)
    m_accelFinalBase[0] /= FG_SENSORS_BASE_SIZE + 2;
    m_accelFinalBase[1] /= FG_SENSORS_BASE_SIZE;
}
//------------------------------------------------------------------------------
