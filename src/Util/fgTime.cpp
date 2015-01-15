/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgTime.h"

#if defined(FG_USING_PLATFORM_WINDOWS)
#include "windows.h"
#else
#include <sys/time.h>
#endif
#include <ctime>

#if defined(FG_USING_MARMALADE)
#include "s3eDebug.h"
#include "s3eTimer.h"
#endif

namespace fg {
    namespace timesys {
#if defined(FG_USING_PLATFORM_WINDOWS)
        static DWORD g_start;
#else
        static struct timeval g_start;
#endif
        ///
        static clock_t g_clock_start = 0L;
        ///
        static float s_start = -1.0;
        ///
        static float s_current = -1.0;
        ///
        static float s_lastTick = -1.0;
    };
};

#if defined(FG_USING_SDL2)
#include <SDL2/SDL_timer.h>
#include <unistd.h>
#endif

using namespace fg;

/*
 * First initial time stamp
 */
void timesys::init(void) {
#ifdef FG_USING_PLATFORM_WINDOWS
    //SYSTEMTIME time;
    //GetSystemTime(&time);
    //WORD millis = (time.wSeconds * 1000) + time.wMilliseconds;
    s_start = (float)timeGetTime() / 1000.0f;
    g_start = timeGetTime();
#else
    timesys::g_clock_start = clock();
    gettimeofday(&timesys::g_start, NULL);
    timesys::s_start = float(timesys::g_start.tv_sec) + float(timesys::g_start.tv_usec / 1000000.0f);
#endif
    timesys::s_current = 0.0;
    timesys::s_lastTick = MINIMUM_TICK;
}

/*
 *
 */
void timesys::markTick(void) {
#ifdef FG_USING_PLATFORM_WINDOWS
    //SYSTEMTIME time;
    //GetSystemTime(&time);
    //WORD millis = (time.wSeconds * 1000) + time.wMilliseconds;
    float newTime = (float)timeGetTime() / 1000.0f;
#else
    struct timeval dtime;
    gettimeofday(&dtime, NULL);
    float newTime = float(dtime.tv_sec - timesys::g_start.tv_sec +
                          dtime.tv_usec / 1000000.0f - timesys::g_start.tv_usec / 1000000.0f);
#endif

    timesys::s_lastTick = newTime - timesys::s_current;
    timesys::s_current = newTime;

    if(timesys::s_lastTick <= 0.0f)
        timesys::s_lastTick = MINIMUM_TICK;
}

/*
 *
 */
float timesys::elapsed(void) {
    return timesys::s_lastTick;
}

/*
 * Get time since init in seconds
 */
float timesys::exact(void) {
#ifdef FG_USING_PLATFORM_WINDOWS
    //SYSTEMTIME time;
    //GetSystemTime(&time);
    //WORD millis = (time.wSeconds * 1000) + time.wMilliseconds;
    return (float)timeGetTime() / 1000.0f;
#else
    struct timeval dtime;
    gettimeofday(&dtime, NULL);
    return float(dtime.tv_sec - timesys::g_start.tv_sec +
                 dtime.tv_usec / 1000000.0f - timesys::g_start.tv_usec / 1000000.0f);
#endif
}

/*
 * Get clock ticks
 */
float timesys::ticks(void) {
    clock_t curTime = clock() - timesys::g_clock_start;
    return float(curTime);
}

/*
 * Get time since init in miliseconds
 */
float timesys::ms(void) {
    struct timeval newTime;
    gettimeofday(&newTime, NULL);
    return float(newTime.tv_sec - timesys::g_start.tv_sec)*1000.0f +
            float(newTime.tv_usec - timesys::g_start.tv_usec) / 1000.0f;
}

/*
 *
 */
long timesys::seconds(void) {
    return time(NULL);
}

/*
 * This function gets time in miliseconds. It doesnt matter from what 
 * point in time this is calculated - it is used for delta time mostly.
 * This function is very similar in usage as the SDL_GetTicks().
 */
unsigned long int FG_GetTicks(void) {
#if defined FG_USING_MARMALADE
    return (unsigned long int)s3eTimerGetMs();
#elif defined FG_USING_SDL || defined FG_USING_SDL2
    return (unsigned long int)SDL_GetTicks();
#else
    return (unsigned long int)(timesys::ticks() / ((float)CLOCKS_PER_SEC / 1000.0f)); // FIXME - here needs to be proper function getting the miliseconds
#endif
}
