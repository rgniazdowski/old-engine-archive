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
 * File:   AdditionalTypes.h
 * Author: vigilant
 *
 * Created on July 22, 2015, 3:33 PM
 */

#ifndef FG_INC_ADDITIONAL_TYPES
    #define FG_INC_ADDITIONAL_TYPES
    #define FG_INC_ADDITIONAL_TYPES_BLOCK

    #include "fgVector.h"

namespace fg {

    /**
     *
     */
    enum RotationDirection {
        /// The block does not rotate (it's static)
        NO_ROTATION = 0,
        /// The block is rotating left (-x)
        LEFT = 1,
        /// The block is rotating right(+x)
        RIGHT = 2,
        /// The block is rotating up (-y)
        UP = 3,
        /// The block is rotating down (+y)
        DOWN = 4,
        /// The block is rotating up and left (-x-y)
        UP_LEFT = 5,
        /// The block is rotating up and right (+x-y)
        UP_RIGHT = 6,
        /// The block is rotating down and left (-x+y)
        DOWN_LEFT = 7,
        /// The block is rotating down and right (+x+y)
        DOWN_RIGHT = 8,
        /// Automatic rotation (detect)
        AUTO_ROTATION = 9,
        /// Opposite rotation
        OPPOSITE_ROTATION = 10
    };

    /**
     *
     */
    enum VColor : unsigned int {
        /// No color, empty block/cell
        INVALID_COLOR = 0,
        /// Black color
        BLACK = 1,
        /// White color
        WHITE = 2,
        /// Gray color
        GRAY = 3,
        ///
        RED = 4,
        ///
        GREEN = 5,
        ///
        BLUE = 6,
        ///
        CYAN = 7,
        ///
        MAGENTA = 8,
        ///
        YELLOW = 9,
        ///
        NUM_COLORS = 10
    };

    inline const char* getColorName(VColor color) {
        const char* returnValue = "invalid";
        switch(color) {
            case BLACK:
                returnValue = "black";
                break;
            case WHITE:
                returnValue = "white";
                break;
            case GRAY:
                returnValue = "gray";
                break;
            case RED:
                returnValue = "red";
                break;
            case GREEN:
                returnValue = "green";
                break;
            case BLUE:
                returnValue = "blue";
                break;
            case CYAN:
                returnValue = "cyan";
                break;
            case MAGENTA:
                returnValue = "magenta";
                break;
            case YELLOW:
                returnValue = "yellow";
                break;
        };
        return returnValue;
    }

    struct SBlockData;

    /**
     *
     */
    struct SNeighbourInfo {
        ///
        SBlockData* ptr;
        ///
        RotationDirection direction;
        /**
         *
         */
        SNeighbourInfo() : ptr(NULL), direction(NO_ROTATION) { }
        /**
         *
         * @param _ptr
         * @param _direction
         */
        SNeighbourInfo(SBlockData* _ptr,
                       RotationDirection _direction = NO_ROTATION) :
        ptr(_ptr), direction(_direction) { }
        /**
         *
         */
        virtual ~SNeighbourInfo() {
            clear();
        }
        /**
         *
         */
        void clear(void) {
            ptr = NULL;
            direction = NO_ROTATION;
        }
        /**
         *
         * @return
         */
        fgBool isValid(void) const {
            fgBool status = (fgBool)!!(ptr != NULL);
            status = (fgBool)!!(status && direction != NO_ROTATION);
            status = (fgBool)!!(status && direction != AUTO_ROTATION);
            status = (fgBool)!!(status && direction != OPPOSITE_ROTATION);
            return status;
        }
        /**
         *
         * @param other
         * @return
         */
        inline bool operator ==(const SNeighbourInfo& other) const {
            return (bool)(this->ptr == other.ptr && this->direction == other.direction);
        }
    }; // SNeighbourInfo
    
    typedef CVector<SNeighbourInfo> NeighbourInfoVec;
    typedef NeighbourInfoVec::iterator NeighbourInfoVecItor;
    typedef NeighbourInfoVec::const_iterator NeighbourInfoVecConstItor;

} // namespace fg

    #undef FG_INC_ADDITIONAL_TYPES_BLOCK
#endif	/* FG_INC_ADDITIONAL_TYPES */
