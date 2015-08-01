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
 * File:   CLevelFile.h
 * Author: vigilant
 *
 * Created on July 15, 2015, 9:57 PM
 */

#ifndef FG_INC_CR_LEVEL_FILE
    #define FG_INC_CR_LEVEL_FILE
    #define FG_INC_CR_LEVEL_FILE_BLOCK

    #include "fgVector.h"
    #include "fgBool.h"
    #include "AdditionalTypes.h"

    #ifndef MAX
        #define MAX(a,b) (((a) > (b)) ? (a) : (b))
    #endif

    #ifndef MIN
        #define MIN(a,b) (((a) < (b)) ? (a) : (b))
    #endif

namespace fg {

    namespace game {
        class CGameMain;
        class CGrid;
    }

    /**
     *
     */
    class CLevelFile {
    public:
        typedef CLevelFile self_type;
        typedef CLevelFile type;

        typedef CVector<VColor> ColorTable;
        typedef ColorTable::iterator ColorTableItor;

    public:

        static const unsigned int MIN_COLOR_ID = 0;
        static const unsigned int MAX_COLOR_ID = (VColor::NUM_COLORS - 1);

    public:
        /**
         *
         * @param filePath
         */
        CLevelFile(const char* filePath = NULL);
        /**
         *
         * @param filePath
         */
        explicit CLevelFile(const std::string& filePath);
        /**
         *
         * @param orig
         */
        CLevelFile(const CLevelFile& orig);
        /**
         *
         */
        virtual ~CLevelFile();

    public:
        /**
         *          
         * @return 
         */
        void refreshArea(void);
        /**
         * 
         * @return 
         */
        fgBool load(void);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool load(const char* filePath);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool load(const std::string& filePath);

        /**
         *
         * @return
         */
        fgBool save(void);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool save(const char* filePath);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool save(const std::string& filePath);

        /**
         *
         * @param pGrid
         * @return
         */
        fgBool applyToGrid(::fg::game::CGrid* pGrid);
        /**
         * 
         * @param blocks
         * @param pGrid
         * @return
         */
        fgBool applyToGrid(const BlockInfoVec& blocks, ::fg::game::CGrid* pGrid);

        /**
         *
         */
        void setSize(unsigned short x, unsigned short y);
        /**
         *
         */
        void setSize(const SSize& size);
        /**
         *
         * @param x
         * @param y
         */
        void getSize(unsigned short& x, unsigned short& y);
        /**
         *
         * @param x
         * @param y
         */
        void getSize(unsigned short* x, unsigned short* y = NULL);

        /**
         * 
         * @return
         */
        SSize& getSize(void) {
            return m_size;
        }
        /**
         *
         * @param x
         * @param y
         */
        SSize const& getSize(void) const {
            return m_size;
        }
        /**
         *
         * @param x
         * @param y
         */
        void getAreaSize(unsigned short& x, unsigned short& y);
        /**
         *
         * @param x
         * @param y
         */
        void getAreaSize(unsigned short* x = NULL, unsigned short* y = NULL);
        /**
         *
         * @param x
         * @param y
         */
        void getAreaMin(unsigned short& x, unsigned short& y);
        /**
         *
         * @param x
         * @param y
         */
        void getAreaMin(unsigned short* x = NULL, unsigned short* y = NULL);
        /**
         *
         * @param x
         * @param y
         */
        void getAreaMax(unsigned short& x, unsigned short& y);
        /**
         *
         * @param x
         * @param y
         */
        void getAreaMax(unsigned short* x = NULL, unsigned short* y = NULL);
        /**
         *
         * @return
         */
        fgBool isValid(void) {
            fgBool valid = (fgBool)!!((m_size.x != 0 && m_size.y != 0));
            valid = (fgBool)!!(valid && !m_blocks.empty());
            return valid;
        }
        /**
         *
         * @return
         */
        fgBool isEmpty(void) const {
            return (fgBool)m_blocks.empty();
        }
        /**
         *
         * @return
         */
        unsigned int getBlocksCount(void) const {
            return (unsigned int)m_blocks.size();
        }
        /**
         *
         */
        void clear(void);
        /**
         * 
         */
        void clearBlocks(void);
        /**
         * 
         * @param shouldResize
         * @return 
         */
        int appendBlocks(BlockInfoVec const& inBlocks, fgBool shouldResize = FG_FALSE);
        /**
         *
         * @param x
         * @param y
         * @return
         */
        fgBool contains(unsigned short x, unsigned short y) const;
        /**
         *
         * @param pos
         * @return
         */
        fgBool contains(const SSize& pos) const;
        /**
         *
         * @param blockInfo
         * @return
         */
        fgBool contains(const SBlockInfo& blockInfo) const;
        /**
         * 
         * @return
         */
        fgBool contains(VColor color) const;
        /**
         *
         */
        inline void reset(void) {
            m_filePath.clear();
            clear();
        }
        /**
         *
         * @return
         */
        BlockInfoVec& getBlocks(void) {
            return m_blocks;
        }
        /**
         *
         * @return
         */
        BlockInfoVec const& getBlocks(void) const {
            return m_blocks;
        }
        /**
         *
         * @return
         */
        std::string const& getFilePath(void) const {
            return m_filePath;
        }
        /**
         *
         * @return
         */
        const char* getFilePathStr(void) const {
            return m_filePath.c_str();
        }
        /**
         *
         * @param filePath
         */
        void setFilePath(const char* filePath);
        /**
         *
         * @param filePath
         */
        void setFilePath(const std::string& filePath);
        /**
         *
         * @param levelIdx
         */
        void setLevelIndex(int levelIdx) {
            m_levelIdx = levelIdx;
        }
        /**
         *
         * @return
         */
        inline int getLevelIndex(void) const {
            return m_levelIdx;
        }
        /**
         *
         * @param levelType
         */
        void setLevelType(LevelType levelType) {
            m_type = levelType;
        }
        /**
         * 
         * @return
         */
        inline LevelType getLevelType(void) const {
            return m_type;
        }
        /**
         * 
         * @return
         */
        inline BlockType getBlockType(void) const {
            return cr::getBlockTypeFromLevelType(m_type);
        }
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

    private:
        ///
        std::string m_filePath;
        ///
        BlockInfoVec m_blocks;
        ///
        ColorTable m_colorTable;
        ///
        int m_levelIdx;
        ///
        LevelType m_type;
        ///
        SSize m_size;
        /**
         *
         */
        struct {
            SSize min;
            SSize max;
            SSize size;
        } m_area;
        
    }; // class CLevel
} // namespace fg

    #undef FG_INC_CR_LEVEL_FILE_BLOCK
#endif	/* FG_INC_CR_LEVEL_FILE */
