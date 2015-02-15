/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Interface file for the random number generator.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

/**
 * @file
 *
 * This file contains the definitions for a random number generator.
 */
#ifndef FG_INC_PHYSICS_RANDOM
    #define FG_INC_PHYSICS_RANDOM
    #define FG_INC_PHYSICS_RANDOM_BLOCK

    #include "fgCycloneCoreMath.h"

namespace fg {
    namespace physics {

        /**
         * Keeps track of one random stream: i.e. a seed and its output.
         * This is used to get random numbers. Rather than a function, this
         * allows there to be several streams of repeatable random numbers
         * at the same time. Uses the RandRotB algorithm.
         */
        class CRandom {
        public:
            /**
             * left bitwise rotation
             */

            unsigned rotl(unsigned n, unsigned r);
            /**
             * right bitwise rotation
             */
            unsigned rotr(unsigned n, unsigned r);

            /**
             * Creates a new random number stream with a seed based on
             * timing data.
             */
            CRandom();

            /**
             * Creates a new random stream with the given seed.
             */
            CRandom(unsigned seed);

            /**
             * Sets the seed value for the random stream.
             */
            void seed(unsigned seed);

            /**
             * Returns the next random bitstring from the stream. This is
             * the fastest method.
             */
            unsigned randomBits();

            /**
             * Returns a random floating point number between 0 and 1.
             */
            real randomReal();

            /**
             * Returns a random floating point number between 0 and scale.
             */
            real randomReal(real scale);

            /**
             * Returns a random floating point number between min and max.
             */
            real randomReal(real min, real max);

            /**
             * Returns a random integer less than the given value.
             */
            unsigned randomInt(unsigned max);

            /**
             * Returns a random binomially distributed number between -scale
             * and +scale.
             */
            real randomBinomial(real scale);

            /**
             * Returns a random vector where each component is binomially
             * distributed in the range (-scale to scale) [mean = 0.0f].
             */
            Vector3f randomVector(real scale);

            /**
             * Returns a random vector where each component is binomially
             * distributed in the range (-scale to scale) [mean = 0.0f],
             * where scale is the corresponding component of the given
             * vector.
             */
            Vector3f randomVector(const Vector3f &scale);

            /**
             * Returns a random vector in the cube defined by the given
             * minimum and maximum vectors. The probability is uniformly
             * distributed in this region.
             */
            Vector3f randomVector(const Vector3f &min, const Vector3f &max);

            /**
             * Returns a random vector where each component is binomially
             * distributed in the range (-scale to scale) [mean = 0.0f],
             * except the y coordinate which is zero.
             */
            Vector3f randomXZVector(real scale);

            /**
             * Returns a random orientation (i.e. normalized) quaternion.
             */
            Quaternionf randomQuaternion();

        private:
            // Internal mechanics
            int m_p1;
            int m_p2;
            unsigned m_buffer[17];
        };

    } // namespace physics
} // namespace fg

    #undef FG_INC_PHYSICS_RANDOM_BLOCK
#endif /* FG_INC_PHYSICS_RANDOM */
