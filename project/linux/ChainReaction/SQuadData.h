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
            DOWN = 4
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
         *
         */
        void hide(void);
        /**
         *
         * @param shouldShow
         */
        void show(fgBool shouldShow = FG_TRUE);

        /**
         *
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
         * @param _oppoDir
         * @return
         */
        fgBool isOppositeRotation(RotationDirection _oppoDir) const;
    }; // struct SQuadData
} // namespace fg

    #undef FG_INC_QUAD_DATA_BLOCK
#endif	/* FG_INC_QUAD_DATA */
