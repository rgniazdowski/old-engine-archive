/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of #FLEXIGAME_PROJECT
 *
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgHardwareState.h"

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
bool fgSingleton<fgHardwareState>::instanceFlag = false;

template <>
fgHardwareState *fgSingleton<fgHardwareState>::instance = NULL;

/**
 * Private constructor
 */
fgHardwareState::fgHardwareState() : m_TS(0), m_screenHeight(0), m_screenWidth(0),
	m_dispArea(0), m_DT(0), m_DT2(0), m_fps(0.0f), m_dpi(0)
{
}

/**
 * Private destructor
 */
fgHardwareState::~fgHardwareState()
{
#if defined FG_USING_DPI_INFO
    if( 0 != m_dpi ) {
        DPI::dpiTerminate();
    }
#endif // FG_USING_DPI_INFO
}

/**
 * Inits DPI. Called from GL init code, when display is ready
 */
void fgHardwareState::initDPI()
{
#if defined FG_USING_DPI_INFO
    DPI::dpiInit();

    m_dpi = DPI::dpiGetScreenDPI(m_screenWidth, m_screenHeight);

    FG_LOG::PrintDebug("### SCREEN DPI IS: %d ###", m_dpi);

    if( 0 == m_dpi ) {
        FG_LOG::PrintError("DPI extension returned dpi=0. Overwriting with 163");
        m_dpi = 163;
    }
#else
    m_dpi = 163; // #FIXME
#endif // FG_USING_DPI_INFO

    if( 0 == m_screenWidth || 0 == m_screenHeight ) {
        FG_LOG::PrintError("initDPI called when no screen width & height being set!");
        exit(5);
    }
    int display_area = m_screenWidth * m_screenHeight;

    m_dpiAndAreaCoef = sqrtf(float(display_area)) / m_dpi;
}

void fgHardwareState::deviceYield(int ms)
{
#if defined FG_USING_MARMALADE
    s3eDeviceYield(ms);
#endif // FG_USING_MARMALADE
}

/**
 * Computes "DeltaTime" (the time flow)
 */
void fgHardwareState::calculateDT(void)
{
	static unsigned long int t1=FG_GetTicks(), t2=FG_GetTicks();
	t2 = FG_GetTicks();

    m_TS = t2;		// Time stamp update
	m_DT = t2-t1;	// Delta time (length of the single frame)
	m_DT2 = t2-t1;	// Delta time used in animations - easy pause -> just set to 0 and animations/movement will stop

	// #FIXME
	// This is some fallback when fps is lower than 30
	// Animation will be smoother but slower
	if( m_DT2 >= 30 )
		m_DT2 = 15;

	t1=t2;
}

/**
 * Compute FPS
 */
float fgHardwareState::calculateFPS(void)
{
	static int nframes = 0;
	static float fps_time = 0.0f;
	nframes++;
	if(nframes == FG_FRAMES_COUNT_LIMIT)
	{
		m_fps = ((float)FG_FRAMES_COUNT_LIMIT) / (((float)FG_GetTicks()) / 1000.0f - fps_time);
		fps_time = ((float)FG_GetTicks()) / 1000.0f;
		nframes = 0;
	}
	return m_fps;
}
