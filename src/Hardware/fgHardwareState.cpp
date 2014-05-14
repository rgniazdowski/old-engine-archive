/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include "fgHardwareState.h"
#include "../fgCommon.h"

#include <cstdlib>
#include <cmath>
#include "dpiInfo.h"

template <>
bool fgSingleton<fgHardwareState>::instanceFlag = false;

template <>
fgHardwareState *fgSingleton<fgHardwareState>::instance = NULL;

/**
 * Private constructor
 */
fgHardwareState::fgHardwareState() : m_TS(0), m_screenHeight(0), m_screenWidth(0), m_dispArea(0), m_DT(0), m_DT2(0), m_fps(0.0f), m_dpi(0) {
}

/**
 * Private destructor
 */
fgHardwareState::~fgHardwareState() {
    if( 0 != m_dpi ) {
        DPI::dpiTerminate();
    }
}

/**
 * Inits DPI. Called from GL init code, when display is ready
 */
void fgHardwareState::initDPI() {
    DPI::dpiInit();

    m_dpi = DPI::dpiGetScreenDPI(m_screenWidth, m_screenHeight);
    
    FG_WriteLog("### SCREEN DPI IS: %d ###", m_dpi);
    
    if( 0 == m_dpi ) {
        FG_ErrorLog("DPI extension returned dpi=0. Overwriting with 163");
        m_dpi = 163;
    }

    if( 0 == m_screenWidth || 0 == m_screenHeight ) {
        FG_ErrorLog("initDPI called when no screen width & height being set!");
        exit(5);
    }
    int display_area = m_screenWidth * m_screenHeight;

    m_dpiAndAreaCoef = sqrtf(float(display_area)) / m_dpi;
}

/**
 * Computes "DeltaTime" (the time flow)
 */
void fgHardwareState::calculateDT(void)
{
	static unsigned long int t1=FG_GetTicks(), t2=FG_GetTicks();
	t2 = FG_GetTicks();
    setTS( t2 );		// Time stamp
	setDT( t2 - t1 );	// Delta time (length of the single frame)	
	setDT2( t2 -t1 );	// Delta time used in animations - easy pause -> just set to 0 and animations/movement will stop

	// FIXME
	// This is some fallback when fps is lower than 30
	// Animation will be smoother but slower
	if( FG_HardwareState->DT2() >= 30 )
		FG_HardwareState->setDT2( 15 );

	t1=t2;
}

/**
 * Compute FPS
 * @return FPS
 */
float fgHardwareState::calculateFPS(void)
{
	static int nframes = 0;
	static float fps_time = 0.0f;
	nframes++;
	if(nframes == FG_FRAMES_COUNT_LIMIT)
	{
		setFPS(((float)FG_FRAMES_COUNT_LIMIT) / (((float)FG_GetTicks()) / 1000.0f - fps_time));
		fps_time = ((float)FG_GetTicks()) / 1000.0f;
		nframes = 0;
	}
	return FPS();
}