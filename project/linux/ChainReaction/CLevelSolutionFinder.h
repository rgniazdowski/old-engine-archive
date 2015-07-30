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
 * File:   CLevelSolutionFinder.h
 * Author: vigilant
 *
 * Created on July 27, 2015, 7:55 PM
 */

#ifndef FG_INC_CR_LEVEL_SOLUTION_FINDER
    #define FG_INC_CR_LEVEL_SOLUTION_FINDER
    #define FG_INC_CR_LEVEL_SOLUTION_FINDER_BLOCK

    #include "CLevelSolver.h"
    #include "CLevelDataHolder.h"
    #include "CLevelSolution.h"

namespace fg {

    /**
     *
     */
    class CLevelSolutionFinder : protected CLevelSolver {
    public:
        typedef CLevelSolver base_type;
        typedef CLevelSolutionFinder self_type;
        typedef CLevelSolutionFinder type;

    public:
        typedef CVector<SBlockMoveStep*> StepsVec;
        typedef StepsVec::iterator StepsVecItor;
        typedef StepsVec::const_iterator StepsVecConstItor;
        typedef StepsVec::value_type ElementType;

        typedef CVector<CLevelSolution*> SolutionsVec;
        typedef SolutionsVec::iterator SolutionsVecItor;
        typedef SolutionsVec::const_iterator SolutionsVecConstItor;

    public:
        /**
         *
         * @param pDataHolder
         */
        CLevelSolutionFinder(CLevelDataHolder* pDataHolder = NULL);
        /**
         *
         * @param orig
         */
        CLevelSolutionFinder(const CLevelSolutionFinder& orig);
        /**
         *
         */
        virtual ~CLevelSolutionFinder();

        //----------------------------------------------------------------------

        /**
         *
         */
        void clear(void);

        /**
         * 
         * @return 
         */
        fgBool prepareRoot(void);
        /**
         * 
         * @return
         */
        fgBool search(void);

    #if defined(FG_DEBUG) || defined(DEBUG)
        void dumpStack(const StepsVec& stack, fgBool reallyVerbose = FG_FALSE);
    #endif

    protected:

        /**
         * 
         */
        void clearSolutions(void);

        /**
         *
         * @param pStep
         * @return
         */
        fgBool prepareStep(SBlockMoveStep* pStep);

        /**
         * 
         */
        fgBool searchHelper(SBlockMoveStep* pMainStep);

        /**
         * 
         * @return
         */
        fgBool checkCompletion(void);

        /**
         * 
         * @param pStep
         * @return
         */
        int performStep(SBlockMoveStep* pStep);
        /**
         *
         */
        int performBalance(void);

    public:

        //----------------------------------------------------------------------
        /**
         *
         * @param pDataHolder
         */
        void setLevelDataHolder(CLevelDataHolder* pDataHolder);
        /**
         *
         */
        void selectSearchRange(void);
        /**
         *
         * @param single
         */
        void selectSearchRange(unsigned int single);
        /**
         *
         * @param begin
         * @param end
         */
        void selectSearchRange(unsigned int begin, unsigned int end);

        /**
         *
         * @param begin
         * @param end
         */
        void getSearchRange(unsigned int& begin, unsigned int& end) const;
        /**
         *
         * @param begin
         * @param end
         */
        void getSearchRange(unsigned int* begin, unsigned int* end) const;
        /**
         * 
         * @return 
         */
        unsigned int getMaximalDepth(void) const {
            return m_maximalDepth;
        }
        /**
         *
         * @return 
         */
        unsigned int getForcedMaximalDepth(void) const {
            return m_forcedMaxDepth;
        }
        /**
         *
         * @param maxDepth
         */
        void setForcedMaximalDepth(unsigned int maxDepth) {
            m_forcedMaxDepth = maxDepth;
        }
        /**
         * 
         * @return
         */
        unsigned int getNumCheckedSteps(void) const {
            return m_numCheckedSteps;
        }
        /**
         *
         * @return
         */
        SBlockMoveStep* getRoot(void) const {
            return m_root;
        }
        /**
         *
         * @return
         */
        StepsVec& getInitialSteps(void) {
            return m_root->steps;
        }
        /**
         * 
         * @return
         */
        StepsVec const& getInitialSteps(void) const {
            return m_root->steps;
        }
        /**
         * 
         * @return
         */
        unsigned int count(void) const {
            return m_solutions.size();
        }
        /**
         * 
         * @return
         */
        SolutionsVec& getSolutions(void) {
            return m_solutions;
        }
        /**
         *
         * @return
         */
        SolutionsVec const& getSolutions(void) const {
            return m_solutions;
        }
        /**
         * 
         * @return 
         */
        CLevelSolution* getCurrentBestSolution(void) const {
            return m_currentBestSolution;
        }
        /**
         * 
         * @param solutions
         * @return 
         */
        unsigned int appendTo(SolutionsVec& solutions);
        /**
         * 
         * @param solutions
         * @return 
         */
        unsigned int copyTo(SolutionsVec& solutions);
        /**
         * 
         * @param solutions
         * @return
         */
        static CLevelSolution* getBestSolutionFrom(const SolutionsVec& solutions,
                                                   CLevelSolution* pOtherBest = NULL);

    public:
        static const unsigned int MAX_NUMBER_DEPTH = UINT_MAX - 1;

    private:
        ///
        CLevelSolution* m_currentSolution;
        ///
        CLevelSolution* m_currentBestSolution;
        ///
        SolutionsVec m_solutions;
        ///
        SBlockMoveStep* m_root;
        ///
        unsigned int m_reachedDepth;
        ///
        unsigned int m_maximalDepth;
        ///
        unsigned int m_forcedMaxDepth;
        ///
        unsigned int m_numCheckedSteps;
        ///
        CVector<unsigned int> m_stepsIndexes;

        /**
         *
         */
        struct SRange {
            ///
            unsigned int begin;
            ///
            unsigned int end;
            /**
             * 
             * @param one
             */
            SRange() : begin(0), end(0) { }
            /**
             *
             * @param one
             */
            void set(unsigned int one) {
                begin = one;
                end = one;
            }
            /**
             *
             * @param _begin
             * @param _end
             */
            void set(unsigned int _begin, unsigned int _end) {
                begin = _begin;
                end = _end;
            }
            /**
             * 
             * @return
             */
            fgBool isSingle(void) const {
                return (fgBool)!!(begin == end);
            }
        } m_searchRange;
    }; // class CLevelSolutionFinder

} // namespace fg

    #undef FG_INC_CR_LEVEL_SOLUTION_FINDER_BLOCK
#endif	/* FG_INC_CR_LEVEL_SOLUTION_FINDER */
