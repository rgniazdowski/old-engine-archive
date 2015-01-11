/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_VECTOR
    #define FG_INC_VECTOR
    #define FG_INC_VECTOR_BLOCK
    
    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #if defined(FG_USING_MARMALADE)
        #include "IwUtil.h"

namespace fg {
	/**
	 *
	 */
	template <class X, class A = ::CIwAllocator<X>, class REALLOCATE = ::ReallocateDefault<X, A > >
	class CVector : public ::CIwArray<X, A, REALLOCATE> {
	public:
		/**
		 * @param i
		 * @return
		 */
		X & at(int const i) const {
			uint32 index = (uint32)i;
			if(index >= this->num_p) {
				return this->p[0];
			}
			return this->p[index];
		}
	};
};
    #else

        #include <vector>
        
namespace fg {

    /**
     * 
     */
    template <class T, class Alloc = std::allocator<T> >
    class CVector : public std::vector<T, Alloc> {
    public:
        /**
         * 
         */
        void clear_optimised() {
            //std::vector<T, Alloc>::clear();
            this->clear();
        }
        /**
         * 
         * @param value
         * @return 
         */
        int find(T const & value) const {
            int i = 0;
            for(typename std::vector<T, Alloc>::const_iterator it = std::vector<T, Alloc>::begin();
                    it != std::vector<T, Alloc>::end();
                    it++, i++) {
                if((*it) == value) {
                    return i;
                }
            }
            return -1;
        }
        /**
         * 
         * @param value
         * @return 
         */
        bool contains(T const & value) const {
            for(typename std::vector<T, Alloc>::const_iterator it = std::vector<T, Alloc>::begin();
                    it != std::vector<T, Alloc>::end(); it++) {
                if((*it) == value) {
                    return true;
                }
            }
            return false;
        }

    };

};
    #endif /* FG_USING_MARMALADE */

    #include <string>
namespace fg {
    typedef CVector<std::string> CStringVector;
};

    #undef FG_INC_VECTOR_BLOCK
#endif /* FG_INC_VECTOR */
