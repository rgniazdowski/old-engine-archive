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
 * File:   fgQueue.h
 * Author: vigilant
 *
 * Created on May 6, 2015, 2:43 PM
 */

#ifndef FG_INC_QUEUE
    #define FG_INC_QUEUE
    #define FG_INC_QUEUE_BLOCK

    #include <queue>

namespace fg {

    /**
     * Wrapper around the std::queue container with additional functions for
     * getting the constant iterators.
     */
    template<typename TValueType, typename TSequence = ::std::vector<TValueType>>
    class CQueue : public ::std::queue<TValueType, TSequence> {
    public:
        typedef CQueue self_type;
        typedef CQueue type;
        typedef ::std::queue<TValueType, TSequence> base_type;

    public:
        typedef typename TSequence::iterator iterator;
        typedef typename TSequence::const_iterator const_iterator;
        typedef typename TSequence::reverse_iterator reverse_iterator;
        typedef typename TSequence::const_reverse_iterator const_reverse_iterator;

    public:
        /**
         * 
         * @return
         */
        const_iterator begin(void) const {
            return this->c.begin();
        }
        /**
         *
         * @return
         */
        const_iterator end(void) const {
            return this->c.end();
        }
        /**
         *
         * @return
         */
        const_reverse_iterator rbegin(void) const {
            return this->c.rbegin();
        }
        /**
         *
         * @return
         */
        const_reverse_iterator rend(void) const {
            return this->c.rend();
        }
        /**
         * 
         */
        void clear(void) {
            while(!this->empty())
                this->pop();
        }
    };

    /**
     * A wrapper class around the std::priority_queue class with additional
     * functions for getting begin/end iterators. With these iterators it is
     * possible to traverse the queue without removing the top element every time.
     *
     */
    template<typename TValueType, typename TSequence = ::std::vector<TValueType>,
    typename TCompare = ::std::less<typename TSequence::value_type> >
    class CPriorityQueue : public ::std::priority_queue<TValueType, TSequence, TCompare> {
    public:
        typedef CPriorityQueue self_type;
        typedef CPriorityQueue type;
        typedef ::std::priority_queue<TValueType, TSequence, TCompare> base_type;

    public:
        typedef typename TSequence::iterator iterator;
        typedef typename TSequence::const_iterator const_iterator;
        typedef typename TSequence::reverse_iterator reverse_iterator;
        typedef typename TSequence::const_reverse_iterator const_reverse_iterator;

    public:
        iterator begin(void) {
            return this->c.begin();
        }
        iterator end(void) {
            return this->c.end();
        }
        /**
         * 
         * @return
         */
        const_iterator begin(void) const {
            return this->c.begin();
        }
        /**
         *
         * @return
         */
        const_iterator end(void) const {
            return this->c.end();
        }
        /**
         *
         * @return
         */
        const_reverse_iterator rbegin(void) const {
            return this->c.rbegin();
        }
        /**
         *
         * @return
         */
        const_reverse_iterator rend(void) const {
            return this->c.rend();
        }
        /**
         * 
         */
        void clear(void) {
            while(!this->empty())
                this->pop();

        }
    };

} // namespace fg

    #undef FG_INC_QUEUE_BLOCK
#endif	/* FG_INC_QUEUE */
