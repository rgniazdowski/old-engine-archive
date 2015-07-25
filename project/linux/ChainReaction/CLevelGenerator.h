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
 * File:   CLevelGenerator.h
 * Author: vigilant
 *
 * Created on July 23, 2015, 9:52 PM
 */

#ifndef FG_INC_CR_LEVEL_GENERATOR
    #define FG_INC_CR_LEVEL_GENERATOR
    #define FG_INC_CR_LEVEL_GENERATOR_BLOCK

    #include "fgTypes.h"

    #include "GameLogic/fgGrid.h"
    #include "CLevelDataHolder.h"
    #include "CLevelFile.h"

namespace fg {

    /**
     *
     */
    class CLevelGenerator {
    public:
        typedef CLevelGenerator self_type;
        typedef CLevelGenerator type;
        typedef CLevelFile::LevelType LevelType;

        typedef CVector<VColor> ColorTable;
        typedef ColorTable::iterator ColorTableItor;

    public:

        /**
         *
         */
        enum StateFlags {
            /// No flags are specified
            NO_FLAGS = 0x0000,
            /// Whether or not to use internal game grid
            USE_INTERNAL_GAME_GRID = 0x0001,
            /// Whether or not to use internal level data holder
            USE_INTERNAL_LEVEL_DATA = 0x0002,
            /// Whether or not this generator is standalone? Meaning that it
            // uses it's own level data and game grid
            STANDALONE = 0x0003, // 01 + 02
            /// The generator will use the gray color
            /// Gray color is tricky because it does not have opposite one,
            /// meaning that gray color wont create combo chain reactions 
            USE_GRAY_COLOR = 0x0004,
            /// The generator will use standard RGB colors
            USE_RGB_COLORS = 0x0008,
            /// The generator will use CMY colors (cyan, magenta, yellow)
            USE_CMY_COLORS = 0x0010,
            /// Will use the black/white colors
            USE_BW_COLORS = 0x0020,

            /// Fully random mode - will simply randomly choose positions and
            /// put blocks in proper places (avoiding color collisions)
            /// This mode is exclusionary with force clusters/no clusters flags
            FULLY_RANDOM = 0x0040,

            /// This mode forces generator to create clusters of blocks (grouping)
            FORCE_CLUSTERS = 0x0080,
            /// The same as FORCE_CLUSTERS but with more friendly name
            FORCE_GROUPS = 0x0080,
            /// The generator will create only one cluster of blocks
            NO_CLUSTERS = 0x0100,
            /// The same as NO_CLUSTERS
            NO_GROUPS = 0x0100,

            /// If true, this will fix any occurring orphans on the level after
            /// generation (in most cases used with fully random algorithm)
            FIX_ORPHANS = 0x0200,
            /// If true, this will remove every orphan on the stage after generation
            REMOVE_ORPHANS = 0x0400,
            /// Creating regular checkerboard will avoid conflicts where
            /// color from outside the color-table has to be used
            REGULAR_CHECKERBOARD = 0x0800
        }; // enum StateFlags

    public:
        /**
         *
         */
        CLevelGenerator(StateFlags stateFlags = NO_FLAGS);
        /**
         *
         * @param orig
         */
        CLevelGenerator(const CLevelGenerator& orig);
        /**
         *
         */
        virtual ~CLevelGenerator();

        //----------------------------------------------------------------------
        /**
         * 
         */
        void clear(void);

        /**
         *
         * @return
         */
        fgBool generate(void);
        /**
         * 
         * @param filePath
         * @return
         */
        fgBool generateAndSaveToFile(const std::string& filePath);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool generateAndSaveToFile(const char* filePath);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool saveToFile(const std::string& filePath);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool saveToFile(const char* filePath);

        //----------------------------------------------------------------------
        void setGrid(game::CGrid* pGrid) {
            m_pGrid = pGrid;
        }
        game::CGrid* getGrid(void) const {
            if(isUsingInternalGameGrid())
                return m_internalGrid;
            return m_pGrid;
        }
        game::CGrid* getInternalGrid(void) const {
            return m_internalGrid;
        }
        void setLevelData(CLevelDataHolder* pLevelData) {
            m_pLevelData = pLevelData;
        }
        CLevelDataHolder* getLevelData(void) const {
            if(isUsingInternalLevelData())
                return m_internalLevelData;
            return m_pLevelData;
        }
        /**
         * 
         * @return
         */
        CLevelDataHolder* getInternalLevelData(void) const {
            return m_internalLevelData;
        }
        /**
         *
         * @return
         */
        CLevelFile* getLevelFile(void) const {
            if(!getLevelData())
                return NULL;
            return getLevelData()->getLevelFile();
        }

        //----------------------------------------------------------------------

        /**
         *
         * @param x
         * @param y
         */
        void setSize(unsigned short x, unsigned short y);
        /**
         * 
         * @param size
         */
        void setSize(const CLevelFile::SSize& size);
        /**
         *
         * @return
         */
        ColorTable& getColorTable(void) {
            return m_colorTable;
        }
        /**
         *
         * @return
         */
        ColorTable const& getColorTable(void) const {
            return m_colorTable;
        }
        /**
         *
         * @return
         */
        VColor getRandomColor(void) const;
        /**
         *
         * @param levelType
         */
        void setLevelType(LevelType levelType) {
            m_genLevelType = levelType;
            checkInternals();
        }
        /**
         *
         * @return
         */
        LevelType getLevelType(void) const {
            return m_genLevelType;
        }
        /**
         *
         * @param levelIndex
         */
        void setLevelIndex(int levelIndex) {
            m_genLevelIdx = levelIndex;
            checkInternals();
        }
        /**
         *
         * @return
         */
        int getLevelIndex(void) const {
            return m_genLevelIdx;
        }
        /**
         *
         * @param coverage
         */
        void setGridCoverage(float coverage) {
            if(coverage > 1.0f)
                coverage = 1.0f;
            if(coverage <= 0.01f)
                coverage = 0.01f;
            m_gridCoverage = coverage;
            checkInternals();
        }
        /**
         *
         * @param coverage
         */
        void setGridCoverage(int coverage) {
            if(coverage > 100)
                coverage = 100;
            if(coverage < 1)
                coverage = 1;
            m_gridCoverage = (float)coverage / 100.0f;
            checkInternals();
        }
        /**
         *
         * @return
         */
        float getGridCoverage(void) const {
            return m_gridCoverage;
        }
        /**
         * 
         * @return
         */
        int getGridCoveragePercents(void) const {
            int value = (int)(m_gridCoverage * 100);
            if(value > 100)
                value = 100;
            if(value < 1)
                value = 1;
            return value;
        }

        //----------------------------------------------------------------------

        /**
         *
         * @param flags
         * @param toggle
         */
        void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
        /**
         *
         * @param toggle
         */
        void useInternalGameGrid(fgBool toggle = FG_TRUE) {
            setFlag(USE_INTERNAL_GAME_GRID, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isUsingInternalGameGrid(void) const {
            return (fgBool)!!(m_stateFlags & USE_INTERNAL_GAME_GRID);
        }
        /**
         *
         * @param toggle
         */
        void useInternalLevelData(fgBool toggle = FG_TRUE) {
            setFlag(USE_INTERNAL_LEVEL_DATA, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isUsingInternalLevelData(void) const {
            return (fgBool)!!(m_stateFlags & USE_INTERNAL_LEVEL_DATA);
        }
        /**
         *
         * @param toggle
         */
        void setStandalone(fgBool toggle = FG_TRUE) {
            setFlag(STANDALONE, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isStandalone(void) const {
            return (fgBool)!!(m_stateFlags & STANDALONE);
        }
        /**
         *
         * @param toggle
         */
        void useGrayColor(fgBool toggle = FG_TRUE) {
            setFlag(USE_GRAY_COLOR, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isUsingGrayColor(void) const {
            return (fgBool)!!(m_stateFlags & USE_GRAY_COLOR);
        }
        /**
         *
         * @param toggle
         */
        void useRgbColors(fgBool toggle = FG_TRUE) {
            setFlag(USE_RGB_COLORS, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isUsingRgbColors(void) const {
            return (fgBool)!!(m_stateFlags & USE_RGB_COLORS);
        }
        /**
         *
         * @param toggle
         */
        void useCmyColors(fgBool toggle = FG_TRUE) {
            setFlag(USE_CMY_COLORS, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isUsingCmyColors(void) const {
            return (fgBool)!!(m_stateFlags & USE_CMY_COLORS);
        }
        /**
         *
         * @param toggle
         */
        void useBlackAndWhiteColors(fgBool toggle = FG_TRUE) {
            setFlag(USE_BW_COLORS, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isUsingBlackAndWhiteColors(void) const {
            return (fgBool)!!(m_stateFlags & USE_BW_COLORS);
        }
        /**
         *
         * @param toggle
         */
        void setFullyRandom(fgBool toggle = FG_TRUE) {
            setFlag(FULLY_RANDOM, toggle);
            if(toggle) {
                setFlag(FORCE_CLUSTERS, FG_FALSE);
                setFlag(NO_CLUSTERS, FG_FALSE);
                setFlag(REGULAR_CHECKERBOARD, FG_FALSE);
            }
        }
        /**
         * 
         * @return
         */
        fgBool isFullyRandom(void) const {
            return (fgBool)!!(m_stateFlags & FULLY_RANDOM);
        }
        /**
         *
         * @param toggle
         */
        void setForceClusters(fgBool toggle = FG_TRUE) {
            setFlag(FORCE_CLUSTERS, toggle);
            if(toggle) {
                setFlag(FULLY_RANDOM, FG_FALSE);
                setFlag(NO_CLUSTERS, FG_FALSE);
            }
        }
        /**
         *
         * @return
         */
        fgBool isForceClusters(void) const {
            return (fgBool)!!(m_stateFlags & FORCE_CLUSTERS);
        }
        /**
         *
         * @param toggle
         */
        void setNoClusters(fgBool toggle = FG_TRUE) {
            setFlag(NO_CLUSTERS, toggle);
            if(toggle) {
                setFlag(FULLY_RANDOM, FG_FALSE);
                setFlag(FORCE_CLUSTERS, FG_FALSE);
            }
        }
        /**
         *
         * @return
         */
        fgBool isNoClusters(void) const {
            return (fgBool)!!(m_stateFlags & NO_CLUSTERS);
        }
        /**
         * 
         * @param toggle
         */
        void setFixOrphans(fgBool toggle = FG_TRUE) {
            setFlag(FIX_ORPHANS, toggle);
            if(toggle) {
                setFlag(REMOVE_ORPHANS, FG_FALSE);
            }
        }
        /**
         *
         * @return
         */
        fgBool isFixOrphans(void) const {
            return (fgBool)!!(m_stateFlags & FIX_ORPHANS);
        }
        /**
         *
         * @param toggle
         */
        void setRemoveOrphans(fgBool toggle = FG_TRUE) {
            setFlag(REMOVE_ORPHANS, toggle);
            if(toggle) {
                setFlag(FIX_ORPHANS, FG_FALSE);
            }
        }
        /**
         *
         * @return
         */
        fgBool isRemoveOrphans(void) const {
            return (fgBool)!!(m_stateFlags & REMOVE_ORPHANS);
        }
        /**
         * 
         * @param toggle
         */
        void setRegularCheckerboard(fgBool toggle = FG_TRUE) {
            setFlag(REGULAR_CHECKERBOARD, toggle);
            if(toggle) {
                setFlag(FULLY_RANDOM, FG_FALSE);
            }
        }
        /**
         *
         * @return
         */
        fgBool isRegularCheckerboard(void) const {
            return (fgBool)!!(m_stateFlags & REGULAR_CHECKERBOARD);
        }

        //----------------------------------------------------------------------
    protected:
        /**
         *
         */
        void checkInternals(void);
        /**
         *
         */
        void refreshColorTable(void);

        //----------------------------------------------------------------------
    private:
        /// External game grid
        game::CGrid* m_pGrid;
        /// Internal game grid (only for generator use)
        game::CGrid* m_internalGrid;
        /// External level data holder
        CLevelDataHolder* m_pLevelData;
        /// Internal level data (only for generator use)
        CLevelDataHolder* m_internalLevelData;
        /// Internal object for saving generated map
        CLevelFile* m_internalLevelFile;
        /// Table with current list of usable (valid) colors
        CVector<VColor> m_colorTable;
        /// Which level type to generate?
        LevelType m_genLevelType;
        /// Generated level index (id to save)
        int m_genLevelIdx;
        ///
        float m_gridCoverage;
        /// Current state flags of the generator
        StateFlags m_stateFlags;

    }; // class CLevelGenerator

    FG_ENUM_FLAGS(CLevelGenerator::StateFlags);

    //--------------------------------------------------------------------------
    inline void CLevelGenerator::setFlag(const StateFlags flags, const fgBool toggle) {
        if(toggle) {
            m_stateFlags |= flags;
        } else {
            m_stateFlags |= flags;
            m_stateFlags ^= flags;
        }
    }

} // namespace fg

    #undef FG_INC_LEVEL_GENERATOR_BLOCK
#endif	/* FG_INC_LEVEL_GENERATOR */
