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
 * File:   fgNamedHandle.h
 * Author: vigilant
 *
 * Created on January 19, 2015, 4:44 PM
 */

#ifndef FG_INC_NAMED_HANDLE
    #define FG_INC_NAMED_HANDLE
    #define FG_INC_NAMED_HANDLE_BLOCK

    #include <string>
    #include "fgHashFunc.h"
    #include "fgHandle.h"

namespace fg {
    namespace util {

        /**
         *
         */
        class CNamedHandle : public std::string {
        public:
            typedef std::string base_type;
            typedef CNamedHandle type;
            typedef CNamedHandle self_type;
            typedef CNamedHandle& self_ref;
            typedef base_type::traits_type traits_type;
            typedef base_type::value_type value_type;
            typedef base_type::allocator_type allocator_type;
            typedef base_type::size_type size_type;
            typedef base_type::difference_type difference_type;
            typedef base_type::reference reference;
            typedef base_type::const_reference const_reference;
            typedef base_type::pointer pointer;
            typedef base_type::const_pointer const_pointer;
            typedef base_type::iterator iterator;
            typedef base_type::const_iterator const_iterator;
            typedef base_type::const_reverse_iterator const_reverse_iterator;
            typedef base_type::reverse_iterator reverse_iterator;

            static const size_type npos = base_type::npos;

        public:
            /**
             * 
             */
            CNamedHandle() :
            base_type(),
            m_hash(0),
            m_stringHash(0),
            m_isIndexSet(FG_FALSE) { }
            /**
             * 
             * @param index
             */
            CNamedHandle(const unsigned int index) :
            base_type(),
            m_hash(0),
            m_stringHash(0),
            m_isIndexSet(FG_TRUE) {
                m_index = index;
            }
            /**
             * 
             * @param nameTag
             */
            CNamedHandle(const char *nameTag) :
            base_type(nameTag),
            m_hash(0),
            m_stringHash(0),
            m_isIndexSet(FG_FALSE) {
                calculateHash();
            }
            /**
             * 
             * @param nameTag
             */
            CNamedHandle(const std::string& nameTag) :
            base_type(nameTag),
            m_hash(0),
            m_stringHash(0),
            m_isIndexSet(FG_FALSE) {
                calculateHash();
            }
            /**
             * 
             * @param nameTag
             */
            CNamedHandle(const CNamedHandle& nameTag) :
            base_type(),
            m_hash(0),
            m_stringHash(0),
            m_isIndexSet(FG_FALSE) {
                set(nameTag);
            }
            /**
             * 
             */
            virtual ~CNamedHandle() {
                base_type::resize(0);
                base_type::reserve(0);
                std::string str;
                base_type::swap(str);
            }

        public:
            /**
             * 
             * @param str
             * @return 
             */
            self_ref operator =(const self_ref str) {
                base_type::assign(str);
                calculateHash();
                m_index = str.m_index;
                m_isIndexSet = str.m_isIndexSet;
                return (*this);
            }
            /**
             * 
             * @param str
             * @return 
             */
            self_ref operator =(const base_type& str) {
                base_type::assign(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @return 
             */
            self_ref operator =(const char* str) {
                base_type::assign(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param c
             * @return 
             */
            self_ref operator =(char c) {
                base_type::assign(1, c);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @return 
             */
            inline iterator begin(void) {
                return base_type::begin();
            }
            /**
             * 
             * @return 
             */
            inline const_iterator begin(void) const {
                return base_type::begin();
            }
            /**
             * 
             * @return 
             */
            inline iterator end(void) {
                return base_type::end();
            }
            /**
             * 
             * @return 
             */
            inline const_iterator end(void) const {
                return base_type::end();
            }
            /**
             * 
             * @return 
             */
            inline reverse_iterator rbegin(void) {
                return base_type::rbegin();
            }
            /**
             * 
             * @return 
             */
            inline const_reverse_iterator rbegin(void) const {
                return base_type::rbegin();
            }
            /**
             * 
             * @return 
             */
            inline reverse_iterator rend(void) {
                return base_type::rend();
            }
            /**
             * 
             * @return 
             */
            inline const_reverse_iterator rend(void) const {
                return base_type::rend();
            }

        public:
            /**
             * 
             * @return 
             */
            inline size_type size(void) const {
                return base_type::size();
            }
            /**
             * 
             * @return 
             */
            inline size_type length(void) const {
                return base_type::length();
            }
            /**
             * 
             * @return 
             */
            inline size_type max_size(void) const {
                return base_type::max_size();
            }
            /**
             * 
             * @param n
             * @param c
             */
            void resize(size_type n, char c) {
                base_type::resize(n, c);
                calculateHash();
            }
            /**
             * 
             * @param n
             */
            void resize(size_type n) {
                base_type::resize(n);
                calculateHash();
            }
            /**
             * 
             * @return 
             */
            inline size_type capacity(void) const {
                return base_type::capacity();
            }
            /**
             *
             * @param res_size
             */
            void reserve(size_type res_size) {
                base_type::reserve(res_size);
                calculateHash();
            }
            /**
             *
             */
            void clear(void) {
                base_type::clear();
                calculateHash();
            }
            /**
             *
             * @return
             */
            bool empty(void) const {
                return base_type::empty();
            }

        public:
            /**
             * 
             * @param pos
             * @return 
             */
            inline const_reference operator [](size_type pos) const {
                return base_type::operator [](pos);
            }
            /**
             * 
             * @param pos
             * @return 
             */
            inline reference operator [](size_type pos) {
                return base_type::operator [](pos);
            }
            /**
             * 
             * @param n
             * @return 
             */
            inline const_reference at(size_type n) const {
                return base_type::at(n);
            }
            /**
             * 
             * @param n
             * @return 
             */
            inline reference at(size_type n) {
                return base_type::at(n);
            }

    #if __cplusplus >= 201103L
            /**
             * Returns a read/write reference to the data at the first
             * element of the %string.
             * @return 
             */
            inline reference front(void) {
                return operator [](0);
            }
            /**
             * Returns a read-only (constant) reference to the data at the first
             * element of the %string.
             * @return
             */
            inline const_reference front(void) const {
                return operator [](0);
            }
            /**
             * Returns a read/write reference to the data at the last
             * element of the %string.
             * @return
             */
            inline reference back(void) {
                return operator [](base_type::size() - 1);
            }
            /**
             * Returns a read-only (constant) reference to the data at the
             * last element of the %string.
             * @return
             */
            inline const_reference back(void) const {
                return operator [](base_type::size() - 1);
            }
    #endif

        public:
            /**
             * 
             * @param str
             * @return 
             */
            self_ref operator +=(const self_ref str) {
                base_type::append(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @return 
             */
            self_ref operator +=(const std::string& str) {
                base_type::append(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @return 
             */
            self_ref operator +=(const char* str) {
                base_type::append(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param c
             * @return 
             */
            self_ref operator +=(char c) {
                base_type::push_back(c);
                calculateHash();
                return (*this);
            }

        public:
            /**
             * 
             * @param str
             * @return 
             */
            inline self_ref append(const self_ref str) {
                base_type::append(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @param pos
             * @param n
             * @return 
             */
            inline self_ref append(const self_ref str, size_type pos, size_type n) {
                base_type::append(str, pos, n);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @return 
             */
            inline self_ref append(const std::string& str) {
                base_type::append(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @param pos
             * @param n
             * @return 
             */
            inline self_ref append(const std::string& str, size_type pos, size_type n) {
                base_type::append(str, pos, n);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @param n
             * @return 
             */
            inline self_ref append(const char* str, size_type n) {
                base_type::append(str, n);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @return 
             */
            inline self_ref append(const char* str) {
                base_type::append(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param n
             * @param c
             * @return 
             */
            inline self_ref append(size_type n, char c) {
                base_type::append(n, c);
                calculateHash();
                return (*this);
            }

        public:
            /**
             * 
             * @param c
             */
            inline void push_back(char c) {
                base_type::push_back(c);
                calculateHash();
            }
            /**
             * 
             * @param str
             * @return 
             */
            inline self_ref assign(const self_ref str) {
                base_type::assign(str);
                calculateHash();
                return (*this);
            }
            /**
             * 
             * @param str
             * @return 
             */
            inline self_ref assign(const std::string& str) {
                base_type::assign(str);
                calculateHash();
                return (*this);
            }

        public:
            /**
             * 
             * @param str
             * @return 
             */
            inline int compare(const self_ref str) const {
                //return base_type::compare(str);
                return (this->m_stringHash == str.m_stringHash && this->m_index == str.m_index);
            }
            /**
             * 
             * @param str
             * @return 
             */
            inline int compare(const std::string& str) const {
                return base_type::compare(str);
            }
            /**
             * 
             * @param pos
             * @param n
             * @param str
             * @return 
             */
            inline int compare(size_type pos, size_type n, const std::string& str) const {
                return base_type::compare(pos, n, str);
            }
            /**
             * 
             * @param pos1
             * @param n1
             * @param str
             * @param pos2
             * @param n2
             * @return 
             */
            inline int compare(size_type pos1, size_type n1, const std::string& str,
                               size_type pos2, size_type n2) const {
                return base_type::compare(pos1, n1, str, pos2, n2);
            }
            /**
             * 
             * @param str
             * @return 
             */
            inline int compare(const char* str) const {
                return base_type::compare(str);
            }
            /**
             * 
             * @param pos
             * @param n
             * @param str
             * @return 
             */
            inline int compare(size_type pos, size_type n, const char* str) const {
                return base_type::compare(pos, n, str);
            }
            /**
             * 
             * @param pos1
             * @param n1
             * @param str
             * @param pos2
             * @param n2
             * @return 
             */
            inline int compare(size_type pos1, size_type n1, const char* str,
                               size_type pos2, size_type n2) const {
                return base_type::compare(pos1, n1, str, pos2, n2);
            }

        public:
            /**
             * 
             * @param nameTag
             */
            void set(const char *nameTag) {
                base_type::assign(nameTag);
                calculateHash();
            }
            /**
             * 
             * @param nameTag
             */
            void set(const std::string& nameTag) {
                base_type::assign(nameTag);
                calculateHash();
            }
            /**
             * 
             * @param nameTag
             */
            void set(const CNamedHandle& nameTag) {
                base_type::assign(nameTag);
                this->m_hash = nameTag.m_hash;
                this->m_index = nameTag.m_index;
                this->m_stringHash = nameTag.m_stringHash;
                this->m_isIndexSet = nameTag.m_isIndexSet;
            }
            /**
             * 
             * @return 
             */
            std::string& getString(void) {
                return (*this);
            }
            /**
             * 
             * @return 
             */
            std::string const& getString(void) const {
                return (*this);
            }
            /**
             * 
             * @return 
             */
            const char *c_str(void) const {
                return base_type::c_str();
            }
            /**
             * 
             * @return 
             */
            unsigned int getHash(void) const {
                return m_hash;
            }
            /**
             * 
             * @return 
             */
            unsigned int getStringHash(void) const {
                return m_stringHash;
            }
            /**
             * 
             * @return 
             */
            unsigned int getIndex(void) const {
                return m_index;
            }
            /**
             * 
             * @param index
             */
            void setIndex(unsigned int index) {
                m_index = index;
                m_isIndexSet = FG_TRUE;
            }
            /**
             * 
             * @return 
             */
            fgBool isIndexSet(void) const {
                return m_isIndexSet;
            }

        protected:
            /**
             * 
             */
            void calculateHash(void) {
                m_stringHash = hash::DJB(c_str());
                m_hash16 = (fgRawMagic)(m_stringHash & 0xFFFF);
            }

        private:

            enum {
                /// Size to use for index bit field
                MAX_BITS_INDEX = 16,
                /// Size to use for hash bit field
                MAX_BITS_HASH = 16,

                /// Maximum index value
                MAX_INDEX = (1 << MAX_BITS_INDEX) - 1,
                /// Maximum hash (16bit) value
                MAX_HASH = (1 << MAX_BITS_HASH) - 1,
            };

            union {

                struct {
                    /// index into resource array
                    fgRawIndex m_index : MAX_BITS_INDEX;
                    /// magic number to check
                    fgRawMagic m_hash16 : MAX_BITS_HASH;
                };
                ///
                unsigned int m_hash;
            };

        private:
            ///
            unsigned int m_stringHash;
            ///
            fgBool m_isIndexSet;
        };
    };
};

    #undef FG_INC_NAMED_HANDLE_BLOCK
#endif	/* FG_INC_NAMED_HANDLE */

