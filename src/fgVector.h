/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_VECTOR
    #define FG_INC_VECTOR
    #define FG_INC_VECTOR_BLOCK

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #if defined(FG_USING_MARMALADE)
        #include "IwArray.h"

namespace fg {

    /**
     *
     */
    template <class X, class A = ::CIwAllocator<X>, class REALLOCATE = ::ReallocateDefault<X, A > >
    class CVector : public ::CIwArray<X, A, REALLOCATE> {
    public:
        typedef CVector<X, A, REALLOCATE> self_type;
        typedef ::CIwArray<X, A, REALLOCATE> base_type;

    public:
        /**
         * @param i
         * @return
         */
        X & at(int const i) const {
            unsigned int index = (unsigned int)i;
            if(index >= this->num_p) {
                return this->p[0];
            }
            return this->p[index];
        }
        X & operator [](int const i)const {
            const unsigned int index = (unsigned int)i;
            IwAssertMsgN(1731, CORE, i >= 0 && index<this->max_p, ("invalid index (%d) into array of capacity %u", i, (unsigned int)this->max_p));
            return this->p[index];
        }
        typename base_type::const_iterator findItor(X const & value) const {
            for(typename base_type::const_iterator it = base_type::begin();
                    it != base_type::end();
                    it++) {
                if((*it) == value) {
                    return it;
                }
            }
            return base_type::end();
        }
        typename base_type::iterator findItor(X const & value) {
            for(typename base_type::iterator it = base_type::begin();
                    it != base_type::end();
                    it++) {
                if((*it) == value) {
                    return it;
                }
            }
            return base_type::end();
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
        typedef CVector<T, Alloc> self_type;
        typedef std::vector<T, Alloc> base_type;
    public:
        /**
         * 
         */
        void clear_optimised(void) {
            //std::vector<T, Alloc>::clear();
            this->clear();
        }
        /**
         * 
         * @param other
         */
        void append(const base_type& other) {
            if(other.empty())
                return;
            this->reserve(this->size()+other.size()+1);
            const unsigned int n = other.size();
            for(unsigned int i =0;i<n;i++) {
                this->push_back(other.at(i));
            }
        }
        /**
         * 
         * @param index
         * @return
         */
        bool remove(typename base_type::size_type index) {
            typename base_type::size_type n = this->size();
            if(index >= n)
                return false;
            this->operator [](index) = this->operator [](n-1);
            this->resize(n-1);
            return true;
        }
        /**
         * 
         * @param index
         * @param numElements
         * @return 
         */
        bool remove(unsigned int& index, unsigned int& numElements) {
            typename base_type::size_type n = this->size();
            if(index >= n)
                return false;
            this->operator [](index) = this->operator [](n-1);
            this->resize(n-1);
            index = index - 1;
            numElements = n - 1;
            return true;
        }
        /**
         *
         * @param index
         * @param numElements
         * @return
         */
        bool remove(unsigned int* index, unsigned int* numElements) {
            typename base_type::size_type n = this->size();
            if(!index)
                return false;
            if(*index >= n)
                return false;
            this->operator [](*index) = this->operator [](n-1);
            this->resize(n-1);
            *index = *index - 1;
            if(numElements)
                *numElements = n - 1;
            return true;
        }
        /**
         * 
         * @param value
         * @return 
         */
        int find(T const & value) const {
            int i = 0;
            for(typename base_type::const_iterator it = std::vector<T, Alloc>::begin();
                    it != base_type::end();
                    it++, i++) {
                if((*it) == value) {
                    return i;
                }
            }
            return -1;
        }
        /**
         * 
         */
        void reverse(void) {
            self_type rev = *this;
            this->clear();
            typename self_type::reverse_iterator b = rev.rbegin();
            typename self_type::reverse_iterator e = rev.rend();
            for(; b != e; b++) {                
                this->push_back(*b);
            }
            rev.clear();
        }
        /**
         * 
         * @param value
         * @return
         */
        typename base_type::const_iterator findItor(T const & value) const {
            for(typename base_type::const_iterator it = base_type::begin();
                    it != base_type::end();
                    it++) {
                if((*it) == value) {
                    return it;
                }
            }
            return base_type::end();
        }
        /**
         * 
         * @param value
         * @return
         */
        typename base_type::iterator findItor(T const & value) {
            for(typename base_type::iterator it = base_type::begin();
                    it != base_type::end();
                    it++) {
                if((*it) == value) {
                    return it;
                }
            }
            return base_type::end();
        }
        /**
         * 
         * @param value
         * @return 
         */
        bool contains(T const & value) const {
            for(typename base_type::const_iterator it = base_type::begin();
                    it != base_type::end(); it++) {
                if((*it) == value) {
                    return true;
                }
            }
            return false;
        }

    }; // class CVector<>

} // namespace fg
    #endif /* FG_USING_MARMALADE */

    #include <string>
namespace fg {
    typedef CVector<std::string> CStringVector;
};

    #undef FG_INC_VECTOR_BLOCK
#endif /* FG_INC_VECTOR */
