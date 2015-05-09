/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/*
 * Game Programming Gems: Vol 6, General Programming
 * Gem:    BSP Techniques
 * Author: Octavian Marius Chincisan
 */

#ifndef FG_INC_GFX_BSP_TYPES
    #define FG_INC_GFX_BSP_TYPES
    #define FG_INC_GFX_BSP_TYPES_BLOCK
    #pragma pack(push, 8)

    #include "Math/fgMathLib.h"
    #include "fgBool.h"
    #include <cfloat>
    #include <cstdlib>
    #include <memory.h>
    #include <vector>
    #include <algorithm>

    #define ASSERT(...)

    #define POLY_DELETED	0x8
    #define POLY_BT_ISSPLITER	0x10
    #define POLY_PORTAL0        0x20
    #define POLY_PORTAL1        0x40
    #define POLY_PROCESSED      0x80
    #define POLY_HIDDEN         0x100
    #define POLY_DIRTY          0x800
    #define POLY_SELECTED       0x2000
    #define BRSH_SOLID          0x1
    #define BRSH_REV            0x2
    #define BRSH_DIRTY          0x8
    #define BRSH_TERRAIN        0x10

    #define FG_NO_FLAG(f_,v_)	(!(f_&v_))
    #define FG_HAS_FLAG(f_,v_)	(!!(f_&v_))
    #define FG_REM_FLAG(f_,v_)	(f_&=~v_)
    #define FG_ADD_FLAG(f_,v_)	(f_|=v_)
    #define FG_SET_FLAG(f_,v_)	(f_=v_)

    #define EPSILONBIG      0.0625F
    #define EPSILON         0.0009765625F
    #define SWITCHI(_x,_y)  ((_x)^=(_y)^=(_x)^=(_y))        // swithes 2 integers
/*
    #define FRAND(a,b)      (float)((float)(rand()%a)/b)
    #define FRANDPREC(nLow, nHigh) ( ( (1.0f / ( (rand() % 100) + 1) ) * ((nHigh) - (nLow ) ) ) + (nLow) )		
    #define IRAND(low,high) (rand() % ( (high) - (low) + 1) + (low) )
inline long R2I(float f) {
    #ifdef MS_WIN32
    static int i;
    ASM_ fld dword ptr [esp + 4]
            ASM_ fistp i
            ASM_ mov eax, i
            ASM_ ret
    #else
    return (long)f;
    #endif //
}
inline int Randval(int iMin, int iMax) {
    return ((rand() % (abs(iMax - iMin) + 1)) + iMin);
}
inline float Randval(float fMin, float fMax) {
    if(fMin == fMax) return (fMin);
    float fRandom = (float)rand() / (float)RAND_MAX;
    return ((fRandom * (float)fabs(fMax - fMin)) + fMin);
}
inline float Frand() {
 // QfRandomInt()
    static unsigned int x =  1234567;
    static unsigned int jflone = 0x40000000;
    static unsigned int jflmask = 0x007fffff;

    x = x * 1664525 + 1013904223;
    unsigned int t = jflone | (jflmask & x);
    return (*(float*)& t) - 3.0f;
}
 */
/*
inline float Asinr(float val) {
    if(-1.0 < val) {
        if(val < 1.0) {
            return float(::asin(val));
        } else {
            return -PIPE2;
        }
    } else {
        return PIPE2;
    }
}*/
/*inline fgBool IsZero(float a, float b = EPSILONBIG) {
    if(a == 0)return FG_TRUE;
    return ( a > -b && a < b);
}
inline fgBool IsZero(fg::Vector3f& a, float e = EPSILONBIG) {
    if(a.x<-e || a.x > e)return 0;
    if(a.y<-e || a.y > e)return 0;
    if(a.z<-e || a.z > e)return 0;
    return 1;
}*/
/*inline fg::Vector3f Getnormal(const fg::Vector3f& p0,
                              const fg::Vector3f& p1,
                              const fg::Vector3f& p2) {
    fg::Vector3f v = fg::math::cross(p0 - p1, p2 - p1);
    v = fg::math::normalize(v);
    return v;
}*/

//  64 bytes (pow of 2) should stay like this
/*inline void GetAnglesFromVector(fg::Vector3f &vec, float &yawAng, float &pitchAng, float& roll) {
    yawAng = atan2(vec.x, vec.y);
    roll = atan2(vec.z, vec.y);

    if(yawAng < 0.0) {
        yawAng += DOIPI;
    }
    if(roll < 0.0) {
        roll += DOIPI;
    }


    if(fabs(vec.x) > fabs(vec.y)) {
        pitchAng = atan2(fabs(vec.z), fabs(vec.x));
    } else {
        pitchAng = atan2(fabs(vec.z), fabs(vec.y));
    }

    if(vec.z < 0.0) {
        pitchAng = -pitchAng;
    }
    pitchAng = R2G(pitchAng);
    yawAng = R2G(yawAng);
    roll = R2G(roll);
}*/
////#define FOREACH(_xtype, _coll, it_begin)    for(_xtype::iterator it_begin = _coll.begin();it_begin!=_coll.end();it_begin++)
////#define _FOREACH(_xtype, _coll, it_begin)   for(it_begin = _coll.begin();it_begin!=_coll.end();it_begin++)
////#define RFOREACH(_xtype, _coll, it_begin)   _xtype::reverse_iterator it_begin = _coll.rbegin();
//_xtype::reverse_iterator it_begin##_End = _coll.rend();
//------------------------------------------------------------------------------------
/*template <class T>void reverse(T& t) {
    static T ret;
    ret.clear();
    ret = t;
    t.clear();
    TYPENAME T::reverse_iterator b = ret.rbegin();
    TYPENAME T::reverse_iterator e = ret.rend();
    for(; b != e; b++)
        t.push_back(*b);
}*/

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CBitArray {
        public:
            /**
             *
             */
            CBitArray() {
                m_storage = 0;
                m_size = 0;
            }
            /**
             *
             * @param size
             */
            CBitArray(unsigned int size) {
                //ASSERT(size > 0);
                initialize(size);
            }
            /**
             *
             */
            virtual ~CBitArray() {
                delete[] m_storage;
            }
            /**
             *
             * @param sz
             */
            void initialize(int sz) {
                m_size = (sz + 7) / 8; // byte align
                m_size = (m_size * 3 + 3) & 0xFFFFFFFC; // dw align
                m_storage = new unsigned char[m_size];
                ::memset(m_storage, 0, m_size);
            }
            /**
             *
             */
            void reset(void) {
                ::memset(m_storage, 0, m_size);
            }
            /**
             *
             */
            void destroy(void) {
                delete[] m_storage;
                m_storage = 0;
                m_size = 0;
            }
            /**
             *
             * @param i
             * @return
             */
            fgBool operator [](int i) {
                return (m_storage[ i >> 3 ] & (1 << (i & 7))) != 0;
            }
            /**
             *
             * @param i
             */
            void set(int i) {
                m_storage[ i >> 3 ] |= (1 << (i & 7));
            }
            /**
             *
             * @param i
             */
            void reset(int i) {
                m_storage[ i >> 3 ] &= ~(1 << (i & 7));
            }
            /**
             *
             * @return
             */
            int size(void) {
                return m_size;
            }
            /**
             *
             * @param bytes
             * @return
             */
            unsigned char* buffer(int& bytes) {
                bytes = m_size;
                return m_storage;
            }
            /**
             *
             * @param pByArr
             */
            void merge(CBitArray& pByArr) {
                int cnt;
                unsigned char* pDSrc = (unsigned char*)pByArr.buffer(cnt);
                unsigned char* pDDst = this->buffer(cnt);
                while(--cnt >= 0) {
                    *pDDst++ |= *pDSrc++;
                }
            }
        private:
            ///
            unsigned char* m_storage;
            ///
            int m_size;
        };
    }
}

    #define RB_BSP                          1012
    #define RB_PORTALS                      1014
    #define RB_PORTALSBSP                   1015

    #pragma pack(pop)
    #undef FG_INC_GFX_BSP_TYPES_BLOCK
#endif /* FG_INC_GFX_BSP_TYPES */
