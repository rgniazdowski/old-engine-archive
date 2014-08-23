/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgTime.h"

#ifdef FG_USING_PLATFORM_WINDOWS
#include "windows.h"
static DWORD g_start;
#else
#include <sys/time.h>
static struct timeval g_start;
#endif

#ifdef FG_USING_MARMALADE
#include "s3eDebug.h"
#include "s3eTimer.h"
#endif

#include <ctime>
static clock_t g_clock_start = 0L;

float fgTime::s_start = -1.0;
float fgTime::s_current = -1.0;
float fgTime::s_lastTick = -1.0;

/*
 * First initial time stamp
 */
void fgTime::init(void)
{
#ifdef FG_USING_PLATFORM_WINDOWS
	//SYSTEMTIME time;
	//GetSystemTime(&time);
	//WORD millis = (time.wSeconds * 1000) + time.wMilliseconds;
	s_start = (float)timeGetTime()/1000.0f;
	g_start = timeGetTime();
#else
	g_clock_start = clock();
	gettimeofday(&g_start, NULL);
	s_start = float(g_start.tv_sec)+float(g_start.tv_usec/1000000.0f);
#endif
	s_current = 0.0;
	s_lastTick = FG_TIME_MIN_TICK;
}

/*
 *
 */
void fgTime::markTick(void)
{
#ifdef FG_USING_PLATFORM_WINDOWS
	//SYSTEMTIME time;
	//GetSystemTime(&time);
	//WORD millis = (time.wSeconds * 1000) + time.wMilliseconds;
	float newTime = (float)timeGetTime()/1000.0f;
#else
	struct timeval dtime;
	gettimeofday(&dtime, NULL);
	float newTime = float(dtime.tv_sec-g_start.tv_sec + 
		dtime.tv_usec/1000000.0f-g_start.tv_usec/1000000.0f);
#endif

	s_lastTick = newTime - s_current;
	s_current = newTime;

	if(s_lastTick <= 0.0f)
		s_lastTick = FG_TIME_MIN_TICK;
}

/*
 *
 */
float fgTime::elapsed(void)
{
	return s_lastTick;
}

/*
 *
 */
float fgTime::exact(void)
{
	#ifdef FG_USING_PLATFORM_WINDOWS
	//SYSTEMTIME time;
	//GetSystemTime(&time);
	//WORD millis = (time.wSeconds * 1000) + time.wMilliseconds;
	return (float)timeGetTime()/1000.0f;
#else
	struct timeval dtime;
	gettimeofday(&dtime, NULL);
	return float(dtime.tv_sec-g_start.tv_sec + 
		dtime.tv_usec/1000000.0f-g_start.tv_usec/1000000.0f);
#endif
}

/*
 * Get clock ticks
 */
float fgTime::ticks(void)
{
	clock_t curTime = clock() - g_clock_start;
	return float(curTime);
}

/*
 * Get time since init in miliseconds
 */
float fgTime::ms(void)
{
	struct timeval newTime;
	gettimeofday(&newTime, NULL);
	return float(newTime.tv_sec-g_start.tv_sec)*1000.0f +
		float(newTime.tv_usec-g_start.tv_usec)/1000.0f;
}

/*
 * This function gets time in miliseconds. It doesnt matter from what 
 * point in time this is calculated - it is used for delta time mostly.
 * This function is very similar in usage as the SDL_GetTicks().
 */
unsigned long int FG_GetTicks(void)
{
#ifdef FG_USING_MARMALADE
	return (unsigned long int)s3eTimerGetMs();
#else
	return (unsigned long int)(fgTime::ticks()/((float)CLOCKS_PER_SEC/1000.0f)); // FIXME - here needs to be proper function getting the miliseconds
#endif
}
