/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_TIME
    #define FG_INC_TIME

    #include <ctime>

    #define FG_TIME_MIN_TICK	0.001f
    #define FG_CLOCKS_PER_SEC	CLOCKS_PER_SEC

class fgTime {
private:
    // Time marking start (init function)
    static float s_start;
    static float s_current;
    static float s_lastTick;

    // Private constructor
    fgTime() { }
    // Private destructor
    ~fgTime() { }
public:
    // First initial time stamp
    static void init(void);
    // Mark current time
    static void markTick(void);

    // Return elapsed time since last tick (seconds)
    static float elapsed(void);
    // Get exact time since init (seconds)
    static float exact(void);
    // Get clock ticks
    static float ticks(void);
    // Get time since init in miliseconds
    static float ms(void);
    // Get the number of seconds since 00:00 hours, Jan 1, 1970 UTC
    // (i.e., the current unix timestamp). Uses time(null)
    static long seconds(void);
};

// Platform independent function for getting time in miliseconds
unsigned long int FG_GetTicks(void);

#endif