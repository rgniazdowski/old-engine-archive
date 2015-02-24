/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgHardwareState.h"
#include "fgLog.h"

#include <cstdlib>
#include <cmath>

#if defined FG_USING_MARMALADE
#include "s3eDevice.h"
#endif // FG_USING_MARMALADE

#include "Util/fgTime.h"

#if defined FG_USING_DPI_INFO
#include "dpiInfo.h"
#endif // FG_USING_DPI_INFO

template <>
bool CSingleton<fgHardwareState>::instanceFlag = false;

template <>
fgHardwareState *CSingleton<fgHardwareState>::instance = NULL;

/**
 * Private constructor
 */
fgHardwareState::fgHardwareState() : m_screenHeight(0), m_screenWidth(0),
m_dispArea(0), m_fps(0.0f), m_dpi(0) { }

/**
 * Private destructor
 */
fgHardwareState::~fgHardwareState() {
#if defined FG_USING_DPI_INFO
    if(0 != m_dpi) {
        DPI::dpiTerminate();
    }
#endif // FG_USING_DPI_INFO
}

/**
 * Inits DPI. Called from GL init code, when display is ready
 */
void fgHardwareState::initDPI() {
#if defined FG_USING_DPI_INFO
    DPI::dpiInit();

    m_dpi = DPI::dpiGetScreenDPI(m_screenWidth, m_screenHeight);

    FG_LOG_DEBUG("### SCREEN DPI IS: %d ###", m_dpi);

    if(0 == m_dpi) {
        FG_LOG_ERROR("DPI extension returned dpi=0. Overwriting with 163");
        m_dpi = 163;
    }
#else
    m_dpi = 163; // #FIXME
#endif // FG_USING_DPI_INFO

    if(0 == m_screenWidth || 0 == m_screenHeight) {
        FG_LOG_ERROR("initDPI called when no screen width & height being set!");
        exit(5);
    }
    int display_area = m_screenWidth * m_screenHeight;

    m_dpiAndAreaCoef = sqrtf(float(display_area)) / m_dpi;
}

void fgHardwareState::deviceYield(int ms) {
#if defined FG_USING_MARMALADE
    s3eDeviceYield(ms);
#endif // FG_USING_MARMALADE
}

/**
 * Compute FPS
 */
float fgHardwareState::calculateFPS(void) {
    static int nframes = 0;
    static float fps_time = 0.0f;
    nframes++;
    if(nframes == FG_FRAMES_COUNT_LIMIT) {
        m_fps = ((float)FG_FRAMES_COUNT_LIMIT) / (((float)FG_GetTicks()) / 1000.0f - fps_time);
        fps_time = ((float)FG_GetTicks()) / 1000.0f;
        nframes = 0;
    }
    return m_fps;
}
