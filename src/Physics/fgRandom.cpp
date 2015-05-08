/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Implementation file for random number generation.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include <cstdlib>
#include <ctime>
#include "fgRandom.h"
#include "Math/fgMathLib.h"

using namespace fg;

physics::CRandom::CRandom() {
    seed(0);
}

physics::CRandom::CRandom(unsigned seed) {
    physics::CRandom::seed(seed);
}

void physics::CRandom::seed(unsigned s) {
    if(s == 0) {
        s = (unsigned)clock();
    }

    // Fill the buffer with some basic random numbers
    for(unsigned i = 0; i < 17; i++) {
        // Simple linear congruential generator
        s = s * 2891336453 + 1;
        m_buffer[i] = s;
    }

    // Initialize pointers into the buffer
    m_p1 = 0;
    m_p2 = 10;
}

unsigned physics::CRandom::rotl(unsigned n, unsigned r) {
    return (n << r) |
            (n >> (32 - r));
}

unsigned physics::CRandom::rotr(unsigned n, unsigned r) {
    return (n >> r) |
            (n << (32 - r));
}

unsigned physics::CRandom::randomBits() {
    unsigned result;

    // Rotate the buffer and store it back to itself
    result = m_buffer[m_p1] = rotl(m_buffer[m_p2], 13) + rotl(m_buffer[m_p1], 9);

    // Rotate pointers
    if(--m_p1 < 0) m_p1 = 16;
    if(--m_p2 < 0) m_p2 = 16;

    // Return result
    return result;
}

#ifdef SINGLE_PRECISION

physics::real physics::CRandom::randomReal() {
    // Get the random number
    unsigned bits = randomBits();

    // Set up a reinterpret structure for manipulation

    union
    {
        real value;
        unsigned word;
    } convert;

    // Now assign the bits to the word. This works by fixing the ieee
    // sign and exponent bits (so that the size of the result is 1-2)
    // and using the bits to create the fraction part of the float.
    convert.word = (bits >> 9) | 0x3f800000;

    // And return the value
    return convert.value - 1.0f;
}
#else

physics::real physics::CRandom::randomReal() {
    // Get the random number
    unsigned bits = randomBits();

    // Set up a reinterpret structure for manipulation

    union
    {
        real value;
        unsigned words[2];
    } convert;

    // Now assign the bits to the words. This works by fixing the ieee
    // sign and exponent bits (so that the size of the result is 1-2)
    // and using the bits to create the fraction part of the float. Note
    // that bits are used more than once in this process.
    convert.words[0] = bits << 20; // Fill in the top 16 bits
    convert.words[1] = (bits >> 12) | 0x3FF00000; // And the bottom 20

    // And return the value
    return convert.value - 1.0;
}
#endif

physics::real physics::CRandom::randomReal(real min, real max) {
    return randomReal() * (max - min) + min;
}

physics::real physics::CRandom::randomReal(real scale) {
    return randomReal() * scale;
}

unsigned physics::CRandom::randomInt(unsigned max) {
    return randomBits() % max;
}

physics::real physics::CRandom::randomBinomial(real scale) {
    return (randomReal() - randomReal())*scale;
}

Quaternionf physics::CRandom::randomQuaternion() {
    Quaternionf q(
                  randomReal(),
                  randomReal(),
                  randomReal(),
                  randomReal()
                  );
    q = math::normalize(q);
    //q.normalise();
    return q;
}

Vector3f physics::CRandom::randomVector(real scale) {
    return Vector3f(
                    randomBinomial(scale),
                    randomBinomial(scale),
                    randomBinomial(scale)
                    );
}

Vector3f physics::CRandom::randomXZVector(real scale) {
    return Vector3f(
                    randomBinomial(scale),
                    0,
                    randomBinomial(scale)
                    );
}

Vector3f physics::CRandom::randomVector(const Vector3f &scale) {
    return Vector3f(
                    randomBinomial(scale.x),
                    randomBinomial(scale.y),
                    randomBinomial(scale.z)
                    );
}

Vector3f physics::CRandom::randomVector(const Vector3f &min, const Vector3f &max) {
    return Vector3f(
                    randomReal(min.x, max.x),
                    randomReal(min.y, max.y),
                    randomReal(min.z, max.z)
                    );
}
