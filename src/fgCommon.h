/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_COMMON_H_
#define _FG_COMMON_H_

// Global include needed (it defines the parameters of the build)
#include "fgBuildConfig.h"

#include <cstdlib>
#include <cstring>

#define FG_FILE_NAME_MAX	256
#define FG_PATH_MAX			256
#define FG_INVALID			-1

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif

#ifndef fgBool
typedef unsigned char fgBool;
#endif

#ifndef FG_FALSE
#define FG_FALSE 0
#endif

#ifndef FG_TRUE
#define FG_TRUE 1
#endif

#ifndef FG_SUCCESS
#define FG_SUCCESS 1
#endif

#if defined FG_USING_MARMALADE
#include "IwUtil.h"
template <class X, class A=CIwAllocator<X>, class REALLOCATE = ReallocateDefault<X, A > >
class fgArrayVector : public CIwArray<X, A, REALLOCATE> {
public:
	X & at(int const i) const {
		uint32 index = (uint32)i;
        if(index >= num_p) {
			return p[0];
		}
        return p[index];
	}
};
#else 
#include <vector>
template <class T, class Alloc = allocator<T> >
class fgArrayVector : public std::vector<T, Alloc> {
public:
	void clear_optimised()
	{
		clear();		
	}
		
	int find(T const & value) const
    {
        for (int i = 0, iterator it = begin(); it != end(); it++, i++) {
			if((*it) == value) {
				return i;
			}
		}
        return -1;
    }

    bool contains(T const & value) const
    {
		for (iterator it = begin(); it != end(); it++) {
			if((*it) == value) {
				return true;
			}
		}
        return false;
    }

};
#endif

// #FIXME this should not be in this file, but for now (just to compile the damn code) it'll be here
// #TODO #P2 this class needs modification so it will have the standard of all the fgVector*/fgColor* classes
struct Area
{
		int x;
		int y;
		int w;
		int h;
		Area(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
		Area() : x(0), y(0), w(0), h(0) {}

// MARK: Getters

        int left() const {
            return x;
        }

        int right() const {
            return x + w;
        }

        int top() const {
            return y;
        }

        int bottom() const {
            return y + h;
        }

        int width() const {
            return w;
        }

        int height() const {
            return h;
        }

// MARK: Setters

        void set_left(int l) {
            x = l;
        }

        void set_right(int r) {
            w = r - x;
        }

        void set_top(int t) {
            y = t;
        }

        void set_bottom(int b) {
            h = b - y;
        }

        void set_width(int _w) {
            w = _w;
        }

        void set_height(int _h) {
            h = _h;
        }
};


//FIXME
void FG_InfoLog(const char *fmt, ...);
void FG_ErrorLog(const char *fmt, ...);
void FG_WriteLog(const char *fmt, ...);

// Platform independent function for getting time in miliseconds
unsigned long int FG_GetTicks(void);

/**
 * Random int from [a,b]
 */
inline int FG_Rand(int a, int b) {
	return a +(int)(((float)(b-a+1))*rand()/(float(RAND_MAX)+1.0f));
}

inline const char *FG_FileExt(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return NULL;
    return dot + 1;
}

#endif /* _FG_COMMON_H_ */
