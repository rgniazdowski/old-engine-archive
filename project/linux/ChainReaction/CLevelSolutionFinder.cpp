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
 * File:   CLevelSolutionFinder.cpp
 * Author: vigilant
 * 
 * Created on July 27, 2015, 7:55 PM
 */

#include "CLevelSolutionFinder.h"
#include "Util/fgTime.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelSolutionFinder::CLevelSolutionFinder(CLevelDataHolder* pDataHolder) :
base_type(pDataHolder),
m_currentSolution(NULL),
m_currentBestSolution(NULL),
m_solutions(),
m_root(NULL),
m_reachedDepth(0),
m_minimalDepth(MAX_NUMBER_DEPTH),
m_numAllPossibleSteps(0),
m_stepsIndexes(),
m_searchRange() {
    //m_currentSolution = new CLevelSolution();
    m_solutions.reserve(16);
    m_root = new SBlockMoveStep();
    m_root->prepareAsRoot();
    if(getLevelDataHolder()) {
        m_root->blockType = getLevelDataHolder()->getBlockType();
    }
    m_searchRange.begin = 0;
    m_searchRange.end = 0;
    base_type::setSimulation(FG_TRUE);
}
//------------------------------------------------------------------------------

CLevelSolutionFinder::CLevelSolutionFinder(const CLevelSolutionFinder& orig) : base_type(orig) {
    this->m_searchRange.begin = orig.m_searchRange.begin;
    this->m_searchRange.end = orig.m_searchRange.end;
    this->m_numAllPossibleSteps = orig.m_numAllPossibleSteps;
    this->m_minimalDepth = orig.m_minimalDepth;
}
//------------------------------------------------------------------------------

CLevelSolutionFinder::~CLevelSolutionFinder() {
    if(m_root) {
        m_root->clearSteps();
        delete m_root;
        m_root = NULL;
    }
    m_currentSolution = NULL;
    m_currentBestSolution = NULL;
    base_type::clear();
    clearSolutions();
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::clear(void) {
    if(m_root)
        m_root->clear();
    if(getLevelDataHolder()) {
        if(m_root)
            m_root->blockType = getLevelDataHolder()->getBlockType();
    }
    m_currentSolution = NULL;
    clearSolutions();
    base_type::clear();
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::clearSolutions(void) {
    const unsigned int n = m_solutions.size();
    for(unsigned int i = 0; i < n; i++) {
        CLevelSolution* pSolution = m_solutions[i];
        if(pSolution)
            delete pSolution;
        m_solutions[i] = NULL;
        pSolution = NULL;
    }
    m_solutions.clear();
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::prepareRoot(void) {
    CLevelDataHolder* pLevelData = base_type::getLevelDataHolder();
    if(!pLevelData) {
        return FG_FALSE;
    }
    if(pLevelData->isEmpty()) {
        return FG_FALSE;
    }
    if(pLevelData->getBlocksCount() < pLevelData->getLevelFile()->getBlocksCount())
        pLevelData->restart();
    m_root->clearSteps();
    m_root->prepareAsRoot();
    m_root->blockType = pLevelData->getBlockType();
    prepareStep(m_root);
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::prepareStep(SBlockMoveStep* pStep) {
    if(!pStep) {
        return FG_FALSE;
    }
    if(pStep->count() > 0)
        return FG_TRUE; // no need to add again
    CLevelDataHolder::BlockDataVec& blocks = getLevelDataHolder()->getBlocks();
    CVector<RotationDirection> rotations;
    rotations.reserve(8);
    const unsigned int n = blocks.size();
    if(!n) {
        return FG_FALSE;
    }
    blocks.at(0)->getValidRotations(rotations);
    const unsigned numRots = rotations.size();
    pStep->steps.reserve(n * rotations.size() + 1);
    SPosition position;
    for(unsigned int i = 0; i < n; i++) {
        SBlockData* pBlock = blocks[i];
        if(!pBlock)
            continue;
        if(!pBlock->pCellHolder) // ignore not bound nodes
            continue;
        for(unsigned int r = 0; r < numRots; r++) {
            position.x = pBlock->pCellHolder->pos.x;
            position.y = pBlock->pCellHolder->pos.y;
            pStep->addStep(position, rotations[r]);
        }
    }
    pStep->rewind();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::search(void) {
    if(!getLevelDataHolder())
        return FG_FALSE;
    if(!prepareRoot()) {
        return FG_FALSE;
    }
    fgBool status = FG_FALSE;
    m_numAllPossibleSteps = 0;
    m_reachedDepth = 0;
    clearSolutions();
    unsigned int rootIdx = m_searchRange.begin;
    unsigned int rootMax = m_searchRange.end;
    m_minimalDepth = MAX_NUMBER_DEPTH; // reset minimal depth
    for(; rootIdx <= rootMax; rootIdx++) {
        // take the current step (in root)
        SBlockMoveStep* pStep = m_root->at(rootIdx);
        if(!pStep)
            continue;
        if(!pStep->isValid())
            continue;
        // perform step -> use solver
        performStep(pStep);
        performBalance();
        m_currentBestSolution = NULL;
        getLevelDataHolder()->appendTo(pStep->levelState); // save the level state
        pStep->rewind();
        status = searchHelper(pStep);
        if(status) {
            //probably found solution
#if defined(DEBUG)
            if(m_currentBestSolution)
                m_currentBestSolution->dump();
            break;
#endif
        }
        // reset the game grid?
        getLevelDataHolder()->restart();
    }

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::searchHelper(SBlockMoveStep* pMainStep) {
    CLevelDataHolder* pLevelData = getLevelDataHolder();
    if(!pLevelData)
        return FG_FALSE;
    if(!pMainStep)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    SBlockMoveStep* pSubStep = pMainStep;
    SBlockMoveStep* pPrevious = NULL;
    StepsVec stack;
    stack.reserve(pMainStep->count());
    stack.push_back(pMainStep);
    float t1 = timesys::ms();
    while(true) {

        if(stack.empty())
            break;
        prepareStep(pSubStep);
        pPrevious = pSubStep;
        pSubStep = pSubStep->next(FG_TRUE); // this will clear previous
        if(!pSubStep || (pSubStep && pSubStep->moveDepth >= m_minimalDepth)) {
            if(!pSubStep && pPrevious->moveDepth == m_reachedDepth) {
                if(m_minimalDepth >= MAX_NUMBER_DEPTH)
                    this->m_minimalDepth = m_reachedDepth;
            }
            stack.pop_back();
            if(stack.empty()) {
                break;
            }
            if(pSubStep) {
                pPrevious->clearSteps(); // this one will be ignored
            }
            pSubStep = stack.back();
            pLevelData->restartFrom(pSubStep->levelState);
            continue;
        } else {
            stack.push_back(pSubStep);
        }
#if defined(DEBUG)
        if(base_type::isPrintMessages())
            pSubStep->dump();
#endif
        performStep(pSubStep);
        performBalance();
        if(pSubStep) {
            this->m_reachedDepth = math::max(m_reachedDepth, pSubStep->moveDepth);
            this->m_numAllPossibleSteps++;
        }
        if(this->m_numAllPossibleSteps % 150000 == 0) {
            float t2 = timesys::ms();
            printf("[%.2fs] Already scanned: %d\n", (t2 - t1) / 1000.0f, this->m_numAllPossibleSteps);
        }
        if(this->m_numAllPossibleSteps % 350000 == 0) {
            float t2 = timesys::ms();
            printf("[%.2fs] Stack size: %d | Current depth: %d\n", (t2 - t1) / 1000.0f, stack.size(), pSubStep->moveDepth);
        }
        if(this->m_numAllPossibleSteps % 500000 == 0) {
            float t2 = timesys::ms();
            printf("[%.2fs] Stack size: %d | Current depth: %d | stack dump: \n", (t2 - t1) / 1000.0f, stack.size(), pSubStep->moveDepth);
            unsigned int nStack = stack.size();
            for(unsigned int i = 0; i < nStack; i++) {
                SBlockMoveStep* pStep = stack[i];
                printf("[%d][%p][d:%d@idx:%d]", i, pStep, pStep->moveDepth, pStep->moveIdx);
                if(i < nStack - 1)
                    printf("-> ");
            }
            printf("\n");
        }
        if(checkCompletion()) {
            this->m_minimalDepth = math::min(m_minimalDepth, pSubStep->moveDepth);
            // stack contains the solution
            m_currentSolution = new CLevelSolution();
            m_solutions.push_back(m_currentSolution);
            m_currentSolution->setFromSearchSteps(stack);
#if defined(DEBUG)
            //if(m_isPrintMessages)
            m_currentSolution->dump();
            printf("Already scanned: %d | Current depth: %d | Minimal: %d\n", m_numAllPossibleSteps,
                   pSubStep->moveDepth,
                   m_minimalDepth);
#endif
            if(pLevelData->isEmpty()) {
                stack.pop_back();
                pSubStep = stack.back();
                pLevelData->restartFrom(pSubStep->levelState);

            }
        } else {
            pLevelData->appendTo(pSubStep->levelState);
        }
    }
    const unsigned int nSolutions = m_solutions.size();
    for(unsigned int i = 0; i < nSolutions; i++) {
        CLevelSolution* pSolution = m_solutions[i];
        if(!pSolution)
            continue;
        if(pSolution->isEmpty())
            continue;
        if(m_currentBestSolution == NULL) {
            m_currentBestSolution = pSolution;
            continue;
        }
        if(m_currentBestSolution->count() > pSolution->count()) {
            m_currentBestSolution = pSolution;
            status = FG_TRUE;
        }
    }
    pMainStep->clearSteps();
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::checkCompletion(void) {
    CLevelDataHolder* pLevelData = getLevelDataHolder();
    if(!pLevelData)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    if(pLevelData->getBlocksCount() == 0) {
        // the stage is cleared
        // probably passed level
        status = FG_TRUE;
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::performStep(SBlockMoveStep* pStep) {
    if(!pStep)
        return FG_FALSE;
    CLevelDataHolder* pLevelData = getLevelDataHolder();
    SBlockData* pBlockData = pLevelData->getBlockData(pStep->pos.x, pStep->pos.y);
    SBlockData* pNewBlock = pLevelData->moveBlockToNewPlace(pBlockData,
                                                              pStep->target.x,
                                                              pStep->target.y);
    if(!pNewBlock) {
        base_type::getOrphanBlocks().push_back(pBlockData);
    } else {
        base_type::setUserDisturbance(pNewBlock);
    }
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::performBalance(void) {
    base_type::setChainReaction(); // now should animate
    base_type::setStepOn(FG_TRUE);
    while(base_type::isChainReaction()) {
        base_type::balance(10.0f);
    }
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::selectSearchRange(void) {
    // this will set defaults
    if(!m_root->isEmpty()) {
        m_searchRange.set(0, m_root->count() - 1);
    }
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::selectSearchRange(unsigned int single) {
    m_searchRange.set(single);
    if(m_root->count()) {
        if(m_searchRange.end >= m_root->count())
            m_searchRange.end = m_root->count() - 1;
        if(m_searchRange.begin >= m_root->count())
            m_searchRange.begin = m_root->count() - 1;
    }
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::selectSearchRange(unsigned int begin, unsigned int end) {
    m_searchRange.set(begin, end);
    if(m_searchRange.end >= m_root->count())
        m_searchRange.end = m_root->count() - 1;
    if(m_searchRange.begin >= m_root->count())
        m_searchRange.begin = m_root->count() - 1;
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::getSearchRange(unsigned int& begin, unsigned int& end) const {
    begin = m_searchRange.begin;
    end = m_searchRange.end;

}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::getSearchRange(unsigned int* begin, unsigned int* end) const {
    if(begin)
        *begin = m_searchRange.begin;
    if(end)
        *end = m_searchRange.end;
}
//------------------------------------------------------------------------------

unsigned int CLevelSolutionFinder::appendTo(SolutionsVec& solutions) {
    const unsigned int n = m_solutions.size();
    unsigned int i = 0;
    solutions.reserve(solutions.size()+n+1);
    for(;i<n;i++) {        
        solutions.push_back(m_solutions[i]);
    }
    return i;
}
//------------------------------------------------------------------------------

unsigned int CLevelSolutionFinder::copyTo(SolutionsVec& solutions) {
    const unsigned int n = m_solutions.size();
    unsigned int i = 0;
    solutions.reserve(solutions.size()+n+1);
    for(;i<n;i++) {
        CLevelSolution* pOriginal = m_solutions[i];
        CLevelSolution* pCopy = new CLevelSolution(*pOriginal);
        solutions.push_back(pCopy);
    }
    return i;
}
//------------------------------------------------------------------------------

CLevelSolution* CLevelSolutionFinder::getBestSolutionFrom(const SolutionsVec& solutions,
                                                          CLevelSolution* pOtherBest) {
    const unsigned int nSolutions = solutions.size();
    CLevelSolution* pCurrentBest = pOtherBest;
    for(unsigned int i = 0; i < nSolutions; i++) {
        CLevelSolution* pSolution = solutions[i];
        if(!pSolution)
            continue;
        if(pSolution->isEmpty())
            continue;
        if(pCurrentBest == NULL) {
            pCurrentBest = pSolution;
            continue;
        }
        if(pCurrentBest->count() > pSolution->count()) {
            pCurrentBest = pSolution;
        }
    }
    return pCurrentBest;
}
//------------------------------------------------------------------------------

