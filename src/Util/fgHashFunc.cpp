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

using namespace fg;

//------------------------------------------------------------------------------

unsigned int util::hash::RS(const char *str) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hashValue = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue = hashValue * a + c;
        a = a * b;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::JS(const char *str) {
    unsigned int hashValue = 1315423911;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue ^= ((hashValue << 5) + c + (hashValue >> 2));
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::PJW(const char *str) {
    unsigned int BitsInUnsignedInt = (unsigned int)(sizeof (unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hashValue = 0;
    unsigned int test = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue = (hashValue << OneEighth) + c;

        if((test = hashValue & HighBits) != 0) {
            hashValue = ((hashValue ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::ELF(const char *str) {
    unsigned int hashValue = 0;
    unsigned int x = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue = (hashValue << 4) + c;
        if((x = hashValue & 0xF0000000L) != 0) {
            hashValue ^= (x >> 24);
        }
        hashValue &= ~x;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::BKDR(const char *str) {
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hashValue = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue = (hashValue * seed) + c;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::SDBM(const char *str) {
    unsigned int hashValue = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue = c + (hashValue << 6) + (hashValue << 16) - hashValue;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::DJB(const char *str) {
    unsigned int hashValue = 5381;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue = ((hashValue << 5) + hashValue) + c;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::DEK(const char *str) {
    unsigned int hashValue = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }
    hashValue = static_cast<unsigned int>(strlen(str));

    while((c = *str++)) {
        hashValue = ((hashValue << 5) ^ (hashValue >> 27)) ^ c;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::BP(const char *str) {
    unsigned int hashValue = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue = hashValue << 7 ^ c;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::FNV(const char *str) {
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hashValue = 0;
    unsigned int c = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        hashValue *= fnv_prime;
        hashValue ^= c;
    }

    return hashValue;
}
//------------------------------------------------------------------------------

unsigned int util::hash::AP(const char *str) {
    unsigned int hashValue = 0xAAAAAAAA;
    unsigned int c = 0;
    size_t i = 0;
    if(!str) {
        return hashValue;
    }

    while((c = *str++)) {
        i++;
        hashValue ^= ((i & 1) == 0) ? ((hashValue << 7) ^ c * (hashValue >> 3)) :
                (~((hashValue << 11) + (c ^ (hashValue >> 5))));
    }

    return hashValue;
}
//------------------------------------------------------------------------------
