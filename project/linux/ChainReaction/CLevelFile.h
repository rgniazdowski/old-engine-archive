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

    public:

        static const unsigned int MIN_COLOR_ID = 0;
        static const unsigned int MAX_COLOR_ID = (VColor::NUM_COLORS-1);

    public:

        /**
         *
         */
        enum LevelType {
            INVALID_LEVEL = 0,
            LEVEL_QUADS = 1,
            LEVEL_HEXAGONS = 2,
            LEVEL_OCTAGONS = 3
        };

        /**
         *
         */
        struct SSize {
            ///
            unsigned short x;
            ///
            unsigned short y;
            /**
             *
             * @param _x
             * @param _y
             */
            SSize(unsigned short _x = 0, unsigned short _y = 0) : x(_x), y(_y) { }
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
            }
        }; // struct SSize

        /**
         *
         */
        struct SBlockInfo {
            ///
            VColor color;

            /**
             *
             */
            SSize pos;
            /**
             *
             */
            SBlockInfo() : color(VColor::INVALID_COLOR) {
                pos.x = 0;
                pos.y = 0;
            }
            /**
             * 
             * @param x
             * @param y
             */
            SBlockInfo(unsigned short x, unsigned short y) : color(VColor::INVALID_COLOR) {
                pos.x = x;
                pos.y = y;
            }
            /**
             * 
             * @param _x
             * @param _y
             * @param _color
             */
            SBlockInfo(unsigned short _x,
                      unsigned short _y,
                      VColor _color) :
            color(_color) {
                pos.x = _x;
                pos.y = _y;
            }
            /**
             *
             */
            void zero(void) {
                color = VColor::INVALID_COLOR;
                pos.x = 0;
                pos.y = 0;
            }
            /**
             *
             * @param other
             * @return
             */
            inline bool operator ==(const SBlockInfo& other) const {
                return ((this->color == other.color) &&
                        (this->pos.x == other.pos.x) &&
                        (this->pos.y == other.pos.y));
            }
        }; // struct SBlockInfo

        ///
        typedef CVector<SBlockInfo> BlockInfoVec;
        ///
        typedef BlockInfoVec::iterator BlockInfoVecItor;

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
         * @param pGrid
         * @return
         */
        fgBool applyToGrid(::fg::game::CGrid* pGrid);

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
        void getSize(unsigned short* x = NULL, unsigned short* y = NULL);
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
        
    protected:
        /**
         *
         * @param levelIdx
         */
        void setLevelIndex(int levelIdx) {
            m_levelIdx = levelIdx;
        }

    private:
        ///
        int m_levelIdx;
        ///
        LevelType m_type;
        ///
        std::string m_filePath;
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
        ///
        BlockInfoVec m_blocks;
    }; // class CLevel
} // namespace fg

    #undef FG_INC_CR_LEVEL_FILE_BLOCK
#endif	/* FG_INC_CR_LEVEL_FILE */
