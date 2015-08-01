/* 
 * File:   SOctData.h
 * Author: vigilant
 *
 * Created on July 28, 2015, 12:17 AM
 */

#ifndef FG_INC_CR_OCT_DATA
    #define FG_INC_CR_OCT_DATA
    #define FG_INC_CR_OCT_DATA_BLOCK

    #include "SBlockData.h"

namespace fg {

    /**
     *
     */
    struct SOctData : public SBlockData {
        typedef SBlockData base_type;
        typedef SOctData self_type;
        typedef SOctData type;

        constexpr static const float OCT_HALF_SIZE = 0.5f;
        static const unsigned int MATERIAL_INDEX = 2;

        /**
         *
         */
        SOctData(fgBool isNG = FG_FALSE);
        /**
         *
         * @param rewind
         * @return
         */
        virtual ~SOctData();

        //----------------------------------------------------------------------

        /**
         * Get the pointer to octagon data of the LEFT neighbour if exists
         * @param rewind
         * @return  Pointer to the valid octagon data of the LEFT neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         */
        virtual SBlockData* left(fgBool rewind = FG_FALSE);
        /**
         * Get the pointer to octagon data of the RIGHT neighbour if exists
         * @param rewind
         * @return  Pointer to the valid octagon data of the RIGHT neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         */
        virtual SBlockData* right(fgBool rewind = FG_FALSE);
        /**
         * Get the pointer to octagon data of the UP neighbour
         * @param rewind
         * @return  Pointer to the valid octagon data of the UP neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         *          The game grid coordinates for UP neighbour are reversed.
         *          Grid cell Y coordinate for UP neighbour is (this->Y - 1).
         */
        virtual SBlockData* up(fgBool rewind = FG_FALSE);
        /**
         * Get the pointer to octagon data of the DOWN neighbour
         * @param rewind
         * @return  Pointer to the valid octagon data of the DOWN neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         *          The game grid coordinates for UP neighbour are reversed.
         *          Grid cell Y coordinate for DOWN neighbour is (this->Y + 1).
         */
        virtual SBlockData* down(fgBool rewind = FG_FALSE);

        //----------------------------------------------------------------------

        /**
         *
         * @param rewind
         * @return
         */
        virtual SBlockData* upLeft(fgBool rewind = FG_FALSE);
        /**
         *
         * @param rewind
         * @return
         */
        virtual SBlockData* upRight(fgBool rewind = FG_FALSE);
        /**
         *
         * @param rewind
         * @return
         */
        virtual SBlockData* downLeft(fgBool rewind = FG_FALSE);
        /**
         *
         * @param rewind
         * @return
         */
        virtual SBlockData* downRight(fgBool rewind = FG_FALSE);

        //----------------------------------------------------------------------

        /**
         * 
         * @return
         */
        virtual unsigned int getMaterialIndex(void) const {
            return MATERIAL_INDEX;
        }

        /**
         *
         * @param neighbours
         * @return
         */
        virtual int getNeighbours(NeighbourInfoVec& neighbours, fgBool shouldRewind = FG_FALSE);

        /**
         * Rotate the scene node based on the give direction and amount
         * @param direction
         * @param amount
         * @param reverse
         */
        virtual void rotate(RotationDirection direction, float amount);

        /**
         * Return the position (grid coordinates) of the covered neighbour. This
         * always returns some value (based on rotation direction and current
         * coordinates)
         * @param x Coordinate X in game::CGrid
         * @param y Coordinate Y in game::CGrid
         */
        virtual void getCoveredNeighbourCoord(unsigned short& x, unsigned short& y);

        /**
         *
         * @param direction
         * @param x
         * @param y
         * @return
         */
        virtual fgBool getPotentialNeighbourCoord(RotationDirection direction,
                                                  unsigned short& x,
                                                  unsigned short& y);

        /**
         *
         * @param rotations
         */
        virtual int getValidRotations(CVector<RotationDirection>& rotations);

        /**
         * Get the CellHolder structure for the covered(overlay) neighbour
         * @return  Pointer to valid cell holder data of covered neighbour cell -
         *          NULL if there is no such neighbour or covered field is empty
         */
        virtual game::CGrid::SCellHolder* getCoveredNeighbourCellHolder(void);

        /**
         *
         * @param direction
         * @return
         */
        virtual fgBool isRotationValid(RotationDirection direction) const;

        /**
         *
         * @return
         */
        SOctData* getCoveredNeighbourOctData(void);

        /**
         *
         * @param direction
         * @param x
         * @param y
         * @param newX
         * @param newY
         */
        static void getCoveringCoord(RotationDirection direction,
                                     unsigned short x,
                                     unsigned short y,
                                     unsigned short& newX,
                                     unsigned short& newY);

        //----------------------------------------------------------------------

        fgBool isNG(void) const;

    }; // struct SOctData

} // namespace fg

    #undef FG_INC_CR_OCT_DATA_BLOCK
#endif	/* FG_INC_CR_OCT_DATA */
