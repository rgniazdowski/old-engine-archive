/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_VECTOR_H_
#define _FG_VECTOR_H_

#ifndef _FG_BUILD_CONFIG_H_
#include "fgBuildConfig.h"
#endif

#if defined FG_USING_MARMALADE
#include "IwUtil.h"
template <class X, class A=CIwAllocator<X>, class REALLOCATE = ReallocateDefault<X, A > >
class fgVector : public CIwArray<X, A, REALLOCATE> {
public:
	X & at(int const i) const {
		uint32 index = (uint32)i;
        if(index >= this->num_p) {
			return this->p[0];
		}
        return this->p[index];
	}
};
#else

#include <vector>

template <class T, class Alloc = std::allocator<T> >
class fgVector : public std::vector<T, Alloc> {
public:
	void clear_optimised()
	{
            //std::vector<T, Alloc>::clear();
            this->clear();
	}

	int find(T const & value) const
    {
		int i=0;
        for (typename std::vector<T, Alloc>::const_iterator it = std::vector<T, Alloc>::begin();
             it != std::vector<T, Alloc>::end();
             it++, i++) {
			if((*it) == value) {
				return i;
			}
		}
        return -1;
    }

    bool contains(T const & value) const
    {
		for (typename std::vector<T, Alloc>::const_iterator it = std::vector<T, Alloc>::begin();
		     it != std::vector<T, Alloc>::end(); it++) {
			if((*it) == value) {
				return true;
			}
		}
        return false;
    }

};
#endif /* FG_USING_MARMALADE */

#include <string>
typedef fgVector<std::string> fgStringVector;

#endif /* _FG_VECTOR_H_ */
