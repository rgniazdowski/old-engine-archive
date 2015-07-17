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
 * File:   fgGrid.h
 * Author: vigilant
 *
 * Created on July 13, 2015, 12:27 PM
 */

#ifndef FG_INC_GAME_GRID
    #define FG_INC_GAME_GRID
    #define FG_INC_GAME_GRID_BLOCK

    #include "fgBool.h"
    #include <cstddef>    

namespace fg {
    namespace game {

        /**
         *
         */
        class CGrid {
        public:
            typedef CGrid self_type;
            typedef CGrid type;

        public:
            /// Maximum amount of data containing GameGrid in megabytes
            /// 48 * 48 * 48 * 48 * sizeof(SCellHolder) / 1024 / 1024 ~ 132MiB
            static const unsigned short MAX_DATA_SIZE_MB = 132;
            ///
            static const unsigned short MAX_SIZE_FOUR_DIMENSIONAL = 48;
            ///
            static const unsigned short MAX_SIZE_THREE_DIMENSIONAL = 174;
            ///
            static const unsigned short MAX_SIZE_TWO_DIMENSIONAL = 2300; //2272;
            ///
            static const unsigned short MAX_SIZE_ONE_DIMENSIONAL = 65534; //+1//5308416;

        public:

            /**
             *
             */
            struct SSize {
                int x;
                int y;
                int z;
                int w;
                /**
                 *
                 */
                SSize() : x(0), y(0), z(0), w(0) { }
                /**
                 * 
                 * @param _x
                 * @param _y
                 * @param _z
                 * @param _w
                 */
                SSize(int _x, int _y = 0, int _z = 0, int _w = 0) :
                x(_x), y(_y), z(_z), w(_w) { }
                /**
                 *
                 */
                virtual ~SSize() {
                    zero();
                }
                /**
                 *
                 */
                void zero(void) {
                    x = 0;
                    y = 0;
                    z = 0;
                    w = 0;
                }
            }; // struct SSize

            /**
             *
             */
            enum Dimension {
                ///
                NONE = 0,
                ///
                X = 1,
                ///
                XY = 2,
                ///
                XYZ = 3,
                ///
                XYZW = 4,
                ///
                SINGLE_DIMENSIONAL = 1,
                ///
                TWO_DIMENSIONAL = 2,
                ///
                THREE_DIMENSIONAL = 3,
                ///
                FOUR_DIMENSIONAL = 4
            }; // enum Dimension

            /**
             *
             */
            struct SCellHolder {
                ///
                unsigned short value;

                /**
                 * 
                 */
                struct {
                    ///
                    unsigned short x;
                    ///
                    unsigned short y;
                    ///
                    unsigned short z;
                    ///
                    unsigned short w;
                } pos;

                ///
                CGrid* pParent;
                ///
                void* pData;
                /**
                 * 
                 */
                SCellHolder(CGrid* _pParent = NULL) :
                value(0), pParent(_pParent), pData(NULL) {
                    pos.x = 0;
                    pos.y = 0;
                    pos.z = 0;
                    pos.w = 0;
                }
                /**
                 *
                 */
                virtual ~SCellHolder() {
                    clear();
                    pParent = NULL;
                }
                /**
                 * 
                 */
                void clear(void) {
                    value = 0;
                    pData = NULL;
                    setPosition(0, 0, 0, 0);
                }
                /**
                 * 
                 * @param _x
                 * @param _y
                 * @param _z
                 * @param _w
                 */
                void clear(unsigned short _x,
                           unsigned short _y = 0,
                           unsigned short _z = 0,
                           unsigned short _w = 0) {
                    value = 0;
                    pData = NULL;
                    setPosition(_x, _y, _z, _w);
                }
                /**
                 * 
                 * @param _x
                 * @param _y
                 * @param _z
                 * @param _w
                 */
                void setPosition(unsigned short _x,
                                 unsigned short _y = 0,
                                 unsigned short _z = 0,
                                 unsigned short _w = 0) {
                    pos.x = _x;
                    pos.y = _y;
                    pos.z = _z;
                    pos.w = _w;
                }

                //--------------------------------------------------------------

                /**
                 *
                 * @return
                 */
                /**
                 *
                 * @param rewind
                 * @return
                 */
                SCellHolder* left(fgBool rewind = FG_FALSE);
                /**
                 *
                 * @return
                 */
                SCellHolder* right(fgBool rewind = FG_FALSE);
                /**
                 *
                 * @return
                 */
                SCellHolder* front(fgBool rewind = FG_FALSE);
                /**
                 *
                 * @return
                 */
                SCellHolder* back(fgBool rewind = FG_FALSE);
                /**
                 *
                 * @return
                 */
                SCellHolder* up(fgBool rewind = FG_FALSE);
                /**
                 *
                 * @return
                 */
                SCellHolder* down(fgBool rewind = FG_FALSE);
                /**
                 *
                 * @return
                 */
                SCellHolder* forward(fgBool rewind = FG_FALSE);
                /**
                 *
                 * @return
                 */
                SCellHolder* backward(fgBool rewind = FG_FALSE);

                //--------------------------------------------------------------
                /**
                 *
                 * @return
                 */
                inline fgBool hasLeft(void) {
                    return (fgBool)!!(left());
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasRight(void) {
                    return (fgBool)!!(right());
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasFront(void) {
                    return (fgBool)!!(front());
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasBack(void) {
                    return (fgBool)!!(back());
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasUp(void) {
                    return (fgBool)!!(up());
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasDown(void) {
                    return (fgBool)!!(down());
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasForward(void) {
                    return (fgBool)!!(forward());
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasBackward(void) {
                    return (fgBool)!!(backward());
                }
                /**
                 * 
                 * @return
                 */
                inline fgBool hasNeighbours(void) {
                    fgBool status = hasLeft();
                    if(!status)
                        status = hasRight();
                    if(!status)
                        status = hasFront();
                    if(!status)
                        status = hasBack();
                    if(!status)
                        status = hasUp();
                    if(!status)
                        status = hasDown();
                    if(!status)
                        status = hasForward();
                    if(!status)
                        status = hasBackward();
                    return status;
                }
            }; // struct SCellHolder

        public:
            /**
             *
             */
            CGrid(Dimension dimension = Dimension::TWO_DIMENSIONAL);
            /**
             *
             * @param orig
             */
            CGrid(const CGrid& orig);
            /**
             *
             */
            virtual ~CGrid();

            /**
             * 
             */
            void clear(fgBool full = FG_FALSE);

            /**
             *
             */
            void release(void);
            /**
             *
             */
            inline void destroy(void) {
                release();
            }

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             * @return
             */
            SCellHolder& at(unsigned short x,
                            unsigned short y = 0,
                            unsigned short z = 0,
                            unsigned short w = 0);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             * @return
             */
            SCellHolder const& at(unsigned short x,
                                  unsigned short y = 0,
                                  unsigned short z = 0,
                                  unsigned short w = 0) const;

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             * @return
             */
            SCellHolder* atPtr(unsigned short x,
                               unsigned short y = 0,
                               unsigned short z = 0,
                               unsigned short w = 0);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             * @return
             */
            const SCellHolder* atPtr(unsigned short x,
                                     unsigned short y = 0,
                                     unsigned short z = 0,
                                     unsigned short w = 0) const;

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             * @return
             */
            void* getCellData(unsigned short x,
                              unsigned short y = 0,
                              unsigned short z = 0,
                              unsigned short w = 0);

            /**
             *
             * @param value
             * @param x
             * @param y
             * @param z
             * @param w
             * @return
             */
            fgBool setCellValue(unsigned short value,
                                unsigned short x,
                                unsigned short y = 0,
                                unsigned short z = 0,
                                unsigned short w = 0);

            /**
             *
             * @param pData
             * @param x
             * @param y
             * @param z
             * @param w
             * @return
             */
            fgBool setCellData(void* pData,
                               unsigned short x,
                               unsigned short y = 0,
                               unsigned short z = 0,
                               unsigned short w = 0);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void resize(unsigned short x,
                        unsigned short y = 1,
                        unsigned short z = 1,
                        unsigned short w = 1);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void reserve(unsigned short x,
                         unsigned short y = 1,
                         unsigned short z = 1,
                         unsigned short w = 1);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void setMaxSize(unsigned short x,
                            unsigned short y = 1,
                            unsigned short z = 1,
                            unsigned short w = 1);

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            Dimension getDimension(void) const {
                return m_dimension;
            }

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void getSize(unsigned short& x,
                         unsigned short& y,
                         unsigned short& z,
                         unsigned short& w);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void getSize(unsigned short* x,
                         unsigned short* y = NULL,
                         unsigned short* z = NULL,
                         unsigned short* w = NULL);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void getCapacity(unsigned short& x,
                             unsigned short& y,
                             unsigned short& z,
                             unsigned short& w);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void getCapacity(unsigned short* x,
                             unsigned short* y = NULL,
                             unsigned short* z = NULL,
                             unsigned short* w = NULL);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void getMaxSize(unsigned short& x,
                            unsigned short& y,
                            unsigned short& z,
                            unsigned short& w);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            void getMaxSize(unsigned short* x,
                            unsigned short* y = NULL,
                            unsigned short* z = NULL,
                            unsigned short* w = NULL);

            /**
             *
             * @param x
             * @param y
             * @param z
             * @param w
             */
            fgBool isValidAddress(unsigned short x,
                                  unsigned short y = 0,
                                  unsigned short z = 0,
                                  unsigned short w = 0) const;

    #if defined(DEBUG) || defined(FG_DEBUG)
            void dump(void);
    #endif

        protected:

            /**
             * 
             * @param x
             * @param y
             * @param z
             * @param w
             * @param dimension
             * @return
             */
            fgBool fixSize(unsigned short& x,
                           unsigned short& y,
                           unsigned short& z,
                           unsigned short& w,
                           Dimension dimension = Dimension::NONE);

            //------------------------------------------------------------------

        private:
            ///
            SSize m_size;
            ///
            SSize m_capacity;
            ///
            SSize m_maxSize;
            ///
            Dimension m_dimension;
            ///
            SCellHolder**** m_data;
            ///
            SCellHolder m_dummy;
        }; // class CGrid
    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_GRID_BLOCK
#endif	/* FG_INC_GAME_GRID */
