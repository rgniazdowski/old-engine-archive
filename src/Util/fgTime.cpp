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
        static float s_current[NUM_TICK_CATEGORIES] = {-1.0f, -1.0f, -1.0f};
        ///
        static float s_lastTick[NUM_TICK_CATEGORIES] = {-1.0f, -1.0f, -1.0f};

        const char * const g_TickCategoriesText[] = {
                                                     "UPDATE",
                                                     "PRERENDER",
                                                     "RENDER",
                                                     "UNKNOWN"
        };
    } // namespace timesys
} // namespace fg

#if defined(FG_USING_SDL2)
#include <SDL2/SDL_timer.h>
#include "fgUnistd.h"
#endif

using namespace fg;

//------------------------------------------------------------------------------

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
    timesys::s_current[0] = 0.0;
    timesys::s_current[1] = 0.0;
    timesys::s_current[2] = 0.0;
    timesys::s_lastTick[0] = MINIMUM_TICK;
    timesys::s_lastTick[1] = MINIMUM_TICK;
    timesys::s_lastTick[2] = MINIMUM_TICK;
}
//------------------------------------------------------------------------------

void timesys::markTick(TickCategory category) {
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

    timesys::s_lastTick[(unsigned int)category] = newTime - timesys::s_current[(unsigned int)category];
    timesys::s_current[(unsigned int)category] = newTime;

    if(timesys::s_lastTick[(unsigned int)category] <= 0.0f)
        timesys::s_lastTick[(unsigned int)category] = MINIMUM_TICK;
}
//------------------------------------------------------------------------------

float timesys::elapsed(TickCategory category) {
    return timesys::s_lastTick[(unsigned int)category];
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

float timesys::clockTicks(void) {
    clock_t curTime = clock() - timesys::g_clock_start;
    return float(curTime);
}
//------------------------------------------------------------------------------

float timesys::ms(void) {
    struct timeval newTime;
    gettimeofday(&newTime, NULL);
    return float(newTime.tv_sec - timesys::g_start.tv_sec)*1000.0f +
            float(newTime.tv_usec - timesys::g_start.tv_usec) / 1000.0f;
}
//------------------------------------------------------------------------------

long timesys::seconds(void) {
    return time(NULL);
}
//------------------------------------------------------------------------------

unsigned long int timesys::ticks(void) {
#if defined(FG_USING_MARMALADE)
    return (unsigned long int)s3eTimerGetMs();
#elif defined(FG_USING_SDL) || defined(FG_USING_SDL2)
    return (unsigned long int)SDL_GetTicks();
#else
    return (unsigned long int)(timesys::ms());
#endif
}
//------------------------------------------------------------------------------
