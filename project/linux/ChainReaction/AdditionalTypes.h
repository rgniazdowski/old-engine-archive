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
}

    #undef FG_INC_ADDITIONAL_TYPES_BLOCK
#endif	/* FG_INC_ADDITIONAL_TYPES */
