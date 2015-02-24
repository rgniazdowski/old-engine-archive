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

    #include <ctime>

namespace fg {

    namespace timesys {
        
        ///
        const float MINIMUM_TICK = 0.001f;
        ///
        const long int MINIMUM_CLOCKS_PER_SEC = CLOCKS_PER_SEC;
        
        /**
         * First initial time stamp
         */
        void init(void);
        /**
         * Mark current time
         */
        void markTick(void);

        /**
         * Return elapsed time since last tick (seconds)
         * @return 
         */
        float elapsed(void);
        /**
         * Get exact time since init (seconds)
         * @return 
         */
        float exact(void);
        /**
         * Get clock ticks
         * @return 
         */
        float ticks(void);
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
    };

};

// Platform independent function for getting time in milliseconds
unsigned long int FG_GetTicks(void);

#endif