/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_TIME
    #define FG_INC_TIME
    #define FG_INC_TIME_BLOCK

    #include <ctime>

namespace fg {

    namespace timesys {

        /**
         *
         */
        enum TickCategory {
            TICK_UPDATE = 0,
            TICK_PRERENDER = 1,
            TICK_RENDER = 2,
            NUM_TICK_CATEGORIES = 3
        };

        ///
        const float MINIMUM_TICK = 0.001f;
        ///
        const long int MINIMUM_CLOCKS_PER_SEC = CLOCKS_PER_SEC;
        ///
        const TickCategory DEFAULT_TICK_CATEGORY = TICK_PRERENDER;
        
        /**
         * First initial time stamp
         */
        void init(void);
        /**
         * Mark current time
         * @param category
         */
        void markTick(TickCategory category = DEFAULT_TICK_CATEGORY);

        /**
         * Return elapsed time since last tick (seconds)
         * @param category
         * @return
         */
        float elapsed(TickCategory category = DEFAULT_TICK_CATEGORY);
        /**
         * Get exact time since init (seconds)
         * @return 
         */
        float exact(void);
        /**
         * Get clock ticks
         * @return 
         */
        float clockTicks(void);
        /**
         * Platform independent function for getting time in milliseconds
         * as a unsigned long value (for more accurate float - use ms()
         * This function gets time in miliseconds. It doesnt matter from what
         * point in time this is calculated - it is used for delta time mostly.
         * This function is very similar in usage as the SDL_GetTicks().
         * @return 
         */
        unsigned long int ticks(void);
        /**
         * Get time since init in milliseconds
         * @return 
         */
        float ms(void);
        /**
         * Get the number of seconds since 00:00 hours, Jan 1, 1970 UTC
         * (i.e., the current unix timestamp). Uses time(null)
         * @return 
         */
        long seconds(void);

    } // namespace timesys
} // namespace fg

    #undef FG_INC_TIME_BLOCK
#endif /* FG_INC_TIME */
    