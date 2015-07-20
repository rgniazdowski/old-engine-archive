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
        static const unsigned int MAX_COLOR_ID = 3;

    public:

        /**
         *
         */
        struct SSize {
            unsigned short x;
            unsigned short y;
            SSize(unsigned short _x = 0, unsigned short _y = 0) : x(_x), y(_y) { }
            virtual ~SSize() {
                zero();
            }
            void zero(void) {
                x = 0;
                y = 0;
            }
        }; // struct SSize

        /**
         *
         */
        enum QuadColor {
            EMPTY = 0,
            NONE = 0,
            BLACK = 1,
            WHITE = 2,
            GRAY = 3,
        };

        /**
         *
         */
        struct SQuadInfo {
            ///
            QuadColor color;

            /**
             *
             */
            SSize pos;
            /**
             *
             */
            SQuadInfo() : color(QuadColor::EMPTY) {
                pos.x = 0;
                pos.y = 0;
            }
            /**
             * 
             * @param x
             * @param y
             */
            SQuadInfo(unsigned short x, unsigned short y) : color(QuadColor::EMPTY) {
                pos.x = x;
                pos.y = y;
            }
            /**
             * 
             * @param _x
             * @param _y
             * @param _color
             */
            SQuadInfo(unsigned short _x,
                      unsigned short _y,
                      QuadColor _color) :
            color(_color) {
                pos.x = _x;
                pos.y = _y;
            }
            /**
             *
             */
            void zero(void) {
                color = QuadColor::EMPTY;
                pos.x = 0;
                pos.y = 0;
            }

            inline bool operator==(const SQuadInfo& other) const {
                return ((this->color == other.color) &&
                        (this->pos.x == other.pos.x) &&
                        (this->pos.y == other.pos.y));
            }
        };

        ///
        typedef CVector<SQuadInfo> QuadVec;
        ///
        typedef QuadVec::iterator QuadVecItor;

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
            valid = (fgBool)!!(valid && !m_quads.empty());
            return valid;
        }
        /**
         *
         * @return
         */
        fgBool isEmpty(void) {
            return (fgBool)m_quads.empty();
        }
        /**
         *
         * @return
         */
        unsigned int getQuadsCount(void) const {
            return (unsigned int)m_quads.size();
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
        QuadVec& getQuads(void) {
            return m_quads;
        }
        /**
         *
         * @return
         */
        QuadVec const& getQuads(void) const {
            return m_quads;
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
        QuadVec m_quads;
    }; // class CLevel
} // namespace fg

    #undef FG_INC_CR_LEVEL_FILE_BLOCK
#endif	/* FG_INC_CR_LEVEL_FILE */
