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
 * File:   CLevelSolution.h
 * Author: vigilant
 *
 * Created on July 28, 2015, 6:10 PM
 */

#ifndef FG_INC_CR_LEVEL_SOLUTION
    #define FG_INC_CR_LEVEL_SOLUTION
    #define FG_INC_CR_LEVEL_SOLUTION_BLOCK

    #include "AdditionalTypes.h"

namespace fg {

    /**
     *
     */
    class CLevelSolution {
    public:
        typedef CLevelSolution self_type;
        typedef CLevelSolution type;
        typedef CVector<SBlockMoveInfo> MoveInfoVec;
        typedef MoveInfoVec::iterator MoveInfoVecItor;
        typedef MoveInfoVec::const_iterator MoveInfoVecConstItor;
        typedef MoveInfoVec::value_type ElementType;

        typedef CVector<SBlockMoveStep*> MoveStepsVec;
        typedef MoveStepsVec::iterator MoveStepsVecItor;
        typedef MoveStepsVec::const_iterator MoveStepsVecConstItor;

    public:
        /**
         *
         */
        CLevelSolution();
        /**
         *
         * @param orig
         */
        CLevelSolution(const CLevelSolution& orig);
        /**
         *
         */
        virtual ~CLevelSolution();

        //----------------------------------------------------------------------

        /**
         *
         */
        void clear(void);

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
        fgBool load(const std::string& filePath);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool load(const char* filePath);

        //----------------------------------------------------------------------

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
        fgBool save(const std::string& filePath);
        /**
         *
         * @param filePath
         * @return
         */
        fgBool save(const char* filePath);

        /**
         * 
         * @param searchSteps
         * @return
         */
        fgBool setFromSearchSteps(const MoveStepsVec& searchSteps);

        //----------------------------------------------------------------------

        /**
         * 
         * @param levelType
         */
        void setLevelType(LevelType levelType) {
            m_levelType = levelType;
        }
        /**
         *
         * @return
         */
        LevelType getLevelType(void) const {
            return m_levelType;
        }
        /**
         * 
         * @param index
         */
        void setLevelIndex(int index) {
            m_levelIdx = index;
        }
        /**
         *
         * @return
         */
        int getLevelIndex(void) const {
            return m_levelIdx;
        }
        /**
         *
         * @param size
         */
        void setLevelSize(const SSize& size) {
            m_size = size;
        }
        /**
         *
         * @param x
         * @param y
         */
        void setLevelSize(unsigned short x, unsigned short y) {
            m_size.x = x;
            m_size.y = y;
        }
        /**
         *
         * @return
         */
        SSize& getLevelSize(void) {
            return m_size;
        }
        /**
         *
         * @return
         */
        SSize const& getLevelSize(void) const {
            return m_size;
        }
        /**
         *
         * @return
         */
        BlockType getBlockType(void) const;
        /**
         *
         * @return
         */
        fgBool isEmpty(void) const {
            return (fgBool)m_moves.empty();
        }
        /**
         *
         * @return
         */
        unsigned int count(void) const {
            return m_moves.size();
        }
        /**
         *
         * @param filePath
         */
        void setFilePath(const char* filePath) {
            if(filePath) {
                m_filePath.clear();
                m_filePath.append(filePath);
            }
        }
        /**
         *
         * @param filePath
         */
        void setFilePath(const std::string& filePath) {
            m_filePath.empty();
            m_filePath.append(filePath);
        }
        /**
         *
         * @return
         */
        std::string& getFilePath(void) {
            return m_filePath;
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
         * @param index
         * @return
         */
        inline SBlockMoveInfo& operator[](unsigned int index) {
            return m_moves[index];
        }
        /**
         *
         * @param index
         * @return
         */
        inline SBlockMoveInfo const& operator[](unsigned int index) const {
            return m_moves[index];
        }
        /**
         *
         * @param index
         * @return
         */
        inline SBlockMoveInfo& at(unsigned int index) {
            return m_moves.at(index);
        }
        /**
         *
         * @param index
         * @return
         */
        inline SBlockMoveInfo const& at(unsigned int index) const {
            return m_moves.at(index);
        }
        /**
         *
         * @return
         */
        MoveInfoVec& getMoves(void) {
            return m_moves;
        }
        /**
         *
         * @return
         */
        MoveInfoVec const& getMoves(void) const {
            return m_moves;
        }

    #if defined(DEBUG) || defined(FG_DEBUG)
        void dump(void);
    #endif

    private:
        ///
        LevelType m_levelType;
        ///
        int m_levelIdx;
        ///
        SSize m_size;
        ///
        std::string m_filePath;
        ///
        MoveInfoVec m_moves;
    }; // class CLevelSolution

} // namespace fg

    #undef FG_INC_CR_LEVEL_SOLUTION_BLOCK
#endif	/* FG_INC_CR_LEVEL_SOLUTION */
