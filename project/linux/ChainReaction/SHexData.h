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
 * File:   SHexData.h
 * Author: vigilant
 *
 * Created on July 21, 2015, 9:28 AM
 */

#ifndef FG_INC_HEX_DATA
    #define FG_INC_HEX_DATA
    #define FG_INC_HEX_DATA_BLOCK

    #include "SBlockData.h"

namespace fg {

    /**
     *
     */
    struct SHexData : public SBlockData {
        typedef SHexData self_type;
        typedef SHexData type;
        typedef SBlockData base_type;
        
        constexpr static const float HEX_HALF_SIZE = 0.5f;

        /**
         *
         */
        SHexData();
        /**
         * 
         */
        virtual ~SHexData();

        //----------------------------------------------------------------------

        /**
         * Get the pointer to hexagon data of the LEFT neighbour if exists
         * @param rewind
         * @return  Pointer to the valid hexagon data of the LEFT neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         */
        virtual SBlockData* left(fgBool rewind = FG_FALSE);
        /**
         * Get the pointer to hexagon data of the RIGHT neighbour if exists
         * @param rewind
         * @return  Pointer to the valid hexagon data of the RIGHT neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         */
        virtual SBlockData* right(fgBool rewind = FG_FALSE);
        /**
         * Get the pointer to hexagon data of the UP neighbour
         * @param rewind
         * @return  Pointer to the valid hexagon data of the UP neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         *          The game grid coordinates for UP neighbour are reversed.
         *          Grid cell Y coordinate for UP neighbour is (this->Y - 1).
         */
        virtual SBlockData* up(fgBool rewind = FG_FALSE);
        /**
         * Get the pointer to hexagon data of the DOWN neighbour
         * @param rewind
         * @return  Pointer to the valid hexagon data of the DOWN neighbour.
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
        SHexData* getCoveredNeighbourHexData(void);

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

    }; // struct SHexData

} // namespace fg

    #undef FG_INC_HEX_DATA_BLOCK
#endif	/* FG_INC_HEX_DATA */
