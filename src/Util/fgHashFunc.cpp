/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 ******************************************************************************/
/* 
 * File:   fgHashFunc.cpp
 * Author: vigilant
 * 
 * Created on November 7, 2014, 7:29 AM
 */

#include "fgHashFunc.h"
#include <cstring>

/**
 * 
 */
fgHashFunc::fgHashFunc() { }

/**
 * 
 * @param orig
 */
fgHashFunc::fgHashFunc(const fgHashFunc& orig) { }

/**
 * 
 */
fgHashFunc::~fgHashFunc() { }

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::RS(const char *str) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash = hash * a + c;
        a = a * b;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::JS(const char *str) {
    unsigned int hash = 1315423911;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash ^= ((hash << 5) + c + (hash >> 2));
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::PJW(const char *str) {
    unsigned int BitsInUnsignedInt = (unsigned int)(sizeof (unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash = (hash << OneEighth) + c;

        if((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::ELF(const char *str) {
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash = (hash << 4) + c;
        if((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::BKDR(const char *str) {
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash = (hash * seed) + c;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::SDBM(const char *str) {
    unsigned int hash = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::DJB(const char *str) {
    unsigned int hash = 5381;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::DEK(const char *str) {
    unsigned int hash = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }
    hash = static_cast<unsigned int>(strlen(str));

    while((c = *str++)) {
        hash = ((hash << 5) ^ (hash >> 27)) ^ c;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::BP(const char *str) {
    unsigned int hash = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash = hash << 7 ^ c;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::FNV(const char *str) {
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int c = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        hash *= fnv_prime;
        hash ^= c;
    }

    return hash;
}

/**
 * 
 * @param str
 * @return 
 */
unsigned int fgHashFunc::AP(const char *str) {
    unsigned int hash = 0xAAAAAAAA;
    unsigned int c = 0;
    size_t i = 0;
    if(!str) {
        return hash;
    }

    while((c = *str++)) {
        i++;
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ c * (hash >> 3)) :
                (~((hash << 11) + (c ^ (hash >> 5))));
    }

    return hash;
}
