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
 * File:   SBlockData.h
 * Author: vigilant
 *
 * Created on July 21, 2015, 9:28 AM
 */

#ifndef FG_INC_BLOCK_DATA
    #define FG_INC_BLOCK_DATA
    #define FG_INC_BLOCK_DATA_BLOCK

    #ifdef FG_INC_ADDITIONAL_TYPES_BLOCK
        #error "ERROR"
    #endif

    #include "fgBool.h"    
    #include "Game/fgGrid.h"
    #include "AdditionalTypes.h"

namespace fg {

    namespace gfx {
        class CSceneNode;
    }

    /**
     *
     */
    struct SBlockData {
        typedef SBlockData self_type;
        typedef SBlockData type;        

        ///
        gfx::CSceneNode* pSceneNode;
        ///
        game::CGrid::SCellHolder* pCellHolder;
        ///
        VColor color;
        ///
        fgBool isDragged;
        ///
        fgBool isValid;
        ///
        float rotation;
        ///
        RotationDirection rotDir;
        ///
        int internalIdx;
        ///
        int externalIdx;

    protected:
        ///
        BlockType blockType;

    public:

        //----------------------------------------------------------------------

        /**
         *
         */
        SBlockData();
        /**
         *
         */
        SBlockData(const SBlockData& orig);
        /**
         *
         */
        virtual ~SBlockData();

        //----------------------------------------------------------------------
        /**
         *
         * @return
         */
        BlockType getType(void) const {
            return blockType;
        }
        /**
         * 
         * @param newColor
         */
        void changeColor(VColor newColor) {
            if(/*newColor == VColor::INVALID_COLOR ||*/ newColor >= VColor::NUM_COLORS)
                return;
            this->color = newColor;
            if(pCellHolder) {
                pCellHolder->value = (unsigned short)newColor;
            }
        }

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

        //----------------------------------------------------------------------

        /**
         * 
         * @param scale
         */
        void setScale(float scale);
        /**
         *
         * @param xScale
         * @param yScale
         * @param zScale
         */
        void setScale(float xScale, float yScale, float zScale);
        /**
         *
         * @param xScale
         * @param yScale
         * @param zScale
         */
        void getScale(float& xScale, float& yScale, float& zScale);
        /**
         *
         * @param xScale
         * @param yScale
         * @param zScale
         */
        void getScale(float* xScale, float* yScale = NULL, float* zScale = NULL);

        //----------------------------------------------------------------------

        /**
         * Get the pointer to block data of the LEFT neighbour if exists
         * @param rewind
         * @return  Pointer to the valid block data of the LEFT neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         */
        virtual SBlockData* left(fgBool rewind = FG_FALSE) = 0;
        /**
         * Get the pointer to block data of the RIGHT neighbour if exists
         * @param rewind
         * @return  Pointer to the valid block data of the RIGHT neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         */
        virtual SBlockData* right(fgBool rewind = FG_FALSE) = 0;
        /**
         * Get the pointer to block data of the UP neighbour
         * @param rewind
         * @return  Pointer to the valid block data of the UP neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         *          The game grid coordinates for UP neighbour are reversed.
         *          Grid cell Y coordinate for UP neighbour is (this->Y - 1).
         */
        virtual SBlockData* up(fgBool rewind = FG_FALSE) = 0;
        /**
         * Get the pointer to block data of the DOWN neighbour
         * @param rewind
         * @return  Pointer to the valid block data of the DOWN neighbour.
         *          NULL if there is no neighbour (the selected field is empty).
         *          The game grid coordinates for UP neighbour are reversed.
         *          Grid cell Y coordinate for DOWN neighbour is (this->Y + 1).
         */
        virtual SBlockData* down(fgBool rewind = FG_FALSE) = 0;

        //----------------------------------------------------------------------
        /**
         *
         * @param rewind
         * @return
         */
        virtual SBlockData* upLeft(fgBool rewind = FG_FALSE) = 0;
        /**
         *
         * @param rewind
         * @return
         */
        virtual SBlockData* upRight(fgBool rewind = FG_FALSE) = 0;
        /**
         *
         * @param rewind
         * @return
         */
        virtual SBlockData* downLeft(fgBool rewind = FG_FALSE) = 0;
        /**
         * 
         * @param rewind
         * @return
         */
        virtual SBlockData* downRight(fgBool rewind = FG_FALSE) = 0;

        //----------------------------------------------------------------------

        /**
         *
         * @return
         */
        virtual unsigned int getMaterialIndex(void) const = 0;

        /**
         *
         * @param neighbours
         * @return
         */
        virtual int getNeighbours(NeighbourInfoVec& neighbours, fgBool shouldRewind = FG_FALSE) = 0;

        /**
         * 
         * @param direction
         * @param amount
         */
        virtual void rotate(RotationDirection direction, float amount) = 0;
        /**
         * Return the position (grid coordinates) of the covered neighbour. This
         * always returns some value (based on rotation direction and current
         * coordinates)
         * @param x     Coordinate X in game::CGrid
         * @param y     Coordinate Y in game::CGrid
         */
        virtual void getCoveredNeighbourCoord(unsigned short& x, unsigned short& y) {
            x = 0;
            y = 0;
        }
        /**
         * 
         * @param direction
         * @param x
         * @param y
         * @return 
         */
        virtual fgBool getPotentialNeighbourCoord(RotationDirection direction,
                                                  unsigned short& x,
                                                  unsigned short& y) {
            x = 0;
            y = 0;
            return FG_FALSE;
        }
        /**
         * 
         * @param rotations
         */
        virtual int getValidRotations(CVector<RotationDirection>& rotations) { return 0; }
        /**
         * 
         * @return 
         */
        RotationDirection getRandomValidRotation(void);
        /**
         * 
         * @return 
         */
        VColor getOppositeColor(void) const;
        /**
         * 
         * @param color
         * @return 
         */
        static VColor getOppositeColor(VColor color);
        /**
         * Check whether or not this block is currently rotating
         * @return
         */
        fgBool isRotating(void) const;
        /**
         * Check if this block finished rotating (rot <= 180.0 (M_PI))
         * @return
         */
        fgBool isRotationFinished(void) const;

        /**
         * Checks if this block after rotation does cover some neighbour
         * @return  FG_TRUE if this block does indeed already cover some existing
         *          neighbour, FG_FALSE if otherwise
         */
        fgBool doesCoverNeighbour(void);

        /**
         * Checks if this block after rotation does cover an empty field
         * @return  FG_TRUE if this block does indeed already cover an empty field,
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
        void getCoveredNeighbourCoord(unsigned short* x, unsigned short* y);

        /**
         * Get the QuadData structure for the covered neighbour
         * @return  Pointer to valid block data of covered neighbour - NULL if
         *          there is no such neighbour or covered field is empty
         */
        SBlockData* getCoveredNeighbourBlockData(void);
        /**
         * Get the CellHolder structure for the covered(overlay) neighbour
         * @return  Pointer to valid cell holder data of covered neighbour cell -
         *          NULL if there is no such neighbour or covered field is empty
         */
        virtual game::CGrid::SCellHolder* getCoveredNeighbourCellHolder(void) {
            return NULL;
        }
        /**
         * Get the SceneNode associated with the covered neighbour grid cell
         * @return  Pointer to the valid and managed scene node data of covered
         *          neighbour cell - NULL if there is no such neighbour
         */
        gfx::CSceneNode* getCoveredNeighbourNode(void);

        //----------------------------------------------------------------------

        /**
         * Hide the scene node associated with this block/cell data
         */
        void hide(void);
        /**
         * Show or hide the scene node associated with this block/cell data
         * @param shouldShow    Optional parameter for showing or hiding
         */
        void show(fgBool shouldShow = FG_TRUE);

        /**
         * Deactivate the scene node associated with this block/cell data
         */
        void deactivate(void);
        /**
         *
         * @param shouldActivate
         */
        void activate(fgBool shouldActivate = FG_TRUE);

        /**
         *
         * @return
         */
        virtual fgBool isOrphan(void);

        /**
         *
         * @return
         */
        fgBool isBound(void) const;
        /**
         * Check if scene node associated with this block/cell data is selected
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
        virtual fgBool isRotationValid(RotationDirection direction) const = 0;

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
        RotationDirection getOppositeRotation(RotationDirection direction = AUTO_ROTATION);

    }; // struct SBlockData

} // namespace fg

    #undef FG_INC_BLOCK_DATA_BLOCK
#endif	/* FG_INC_BLOCK_DATA */
