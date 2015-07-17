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
 * File:   SQuadData.h
 * Author: vigilant
 *
 * Created on July 16, 2015, 11:28 AM
 */

#ifndef FG_INC_QUAD_DATA
    #define FG_INC_QUAD_DATA
    #define FG_INC_QUAD_DATA_BLOCK

    #include "fgBool.h"
    #include "GameLogic/fgGrid.h"

namespace fg {

    namespace gfx {
        class CSceneNode;
    }
    
    /**
     * 
     */
    struct SQuadData {
        constexpr static const float QUAD_HALF_SIZE = 0.5f;
        /**
         * 
         */
        enum QuadColor {
            EMPTY = 0,
            NONE = 0,
            BLACK = 1,
            WHITE = 2,
            GRAY = 3
        };
        /**
         *
         */
        enum RotationDirection {
            STATIC = 0,
            LEFT = 1,
            RIGHT = 2,
            UP = 3,
            DOWN = 4,
            AUTO = 5,
            OPPOSITE = 6
        };
        ///
        gfx::CSceneNode* pSceneNode;
        ///
        game::CGrid::SCellHolder* pCellHolder;
        ///
        QuadColor color;
        ///
        fgBool isDragged;
        ///
        fgBool isValid;
        ///
        float rotation;
        ///
        RotationDirection rotDir;
        /**
         *
         */
        SQuadData();
        /**
         *
         * @param orig
         */
        SQuadData(const SQuadData& orig);
        /**
         *
         */
        virtual ~SQuadData();

        /**
         *
         */
        void invalidate(void);

        /**
         *
         */
        void unbind(void);

        /**
         *
         * @param _pCell
         */
        void bind(game::CGrid::SCellHolder* _pCell);

        /**
         * Rotate the scene node based on the give direction and amount
         * @param direction
         * @param amount
         * @param reverse
         */
        void rotate(RotationDirection direction, float amount);

        /**
         * Check if this quad finished rotating (rot <= 180.0 (M_PI))
         * @return
         */
        fgBool isRotationFinished(void) const;

        /**
         * Checks if this quad after rotation does cover some neighbour
         * @return  FG_TRUE if this quad does indeed already cover some existing
         *          neighbour, FG_FALSE if otherwise
         */
        fgBool doesCoverNeighbour(void);

        /**
         * Checks if this quad after rotation does cover an empty field
         * @return  FG_TRUE if this quad does indeed already cover an empty field,
         *          FG_FALSE if otherwise
         */
        fgBool doesCoverEmpty(void);

        /**
         * Return the position (grid coordinates) of the covered neighbour. This
         * always returns some value (based on rotation direction and current
         * coordinates)
         * @param x Coordinate X in game::CGrid
         * @param y Coordinate Y in game::CGrid
         */
        void getCoveredNeighbourCoord(unsigned short& x, unsigned short& y);
        /**
         * Return the position (grid coordinates) of the covered neighbour. This
         * always returns some value (based on rotation direction and current
         * coordinates)
         * @param x Coordinate X in game::CGrid
         * @param y Coordinate Y in game::CGrid
         */
        void getCoveredNeighbourCoord(unsigned short* x, unsigned short* y);

        /**
         * Get the QuadData structure for the covered neighbour
         * @return  Pointer to valid quad data of covered neighbour - NULL if
         *          there is no such neighbour or covered field is empty
         */
        SQuadData* getCoveredNeighbourQuadData(void);
        /**
         * Get the CellHolder structure for the covered(overlay) neighbour
         * @return  Pointer to valid cell holder data of covered neighbour cell -
         *          NULL if there is no such neighbour or covered field is empty
         */
        game::CGrid::SCellHolder* getCoveredNeighbourCellHolder(void);
        /**
         * Get the SceneNode associated with the covered neighbour grid cell
         * @return  Pointer to the valid and managed scene node data of covered
         *          neighbour cell - NULL if there is no such neighbour
         */
        gfx::CSceneNode* getCoveredNeighbourNode(void);

        /**
         * Hide the scene node associated with this quad/cell data
         */
        void hide(void);
        /**
         * Show or hide the scene node associated with this quad/cell data
         * @param shouldShow    Optional parameter for showing or hiding 
         */
        void show(fgBool shouldShow = FG_TRUE);

        /**
         * Deactivate the scene node associated with this quad/cell data
         */
        void deactivate(void);
        /**
         *
         * @param shouldActivate
         */
        void activate(fgBool shouldActivate = FG_TRUE);

        /**
         * Check if scene node associated with this quad/cell data is selected
         * @return  FG_TRUE if current scene node is selected (via pick selection)
         *          FG_FALSE otherwise
         */
        fgBool isSelected(void) const;
        /**
         *
         * @return
         */
        fgBool isActive(void) const;
        /**
         * 
         * @return
         */
        fgBool isVisible(void) const;
        /**
         *
         * @param direction
         * @return
         */
        fgBool isOppositeRotation(RotationDirection direction) const;
        /**
         *
         * @param direction
         * @return
         */
        RotationDirection getOppositeRotation(RotationDirection direction = AUTO);
    }; // struct SQuadData
} // namespace fg

    #undef FG_INC_QUAD_DATA_BLOCK
#endif	/* FG_INC_QUAD_DATA */
