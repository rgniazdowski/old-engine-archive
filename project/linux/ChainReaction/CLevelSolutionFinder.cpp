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
m_maximalDepth(MAX_NUMBER_DEPTH),
m_forcedMaxDepth(MAX_NUMBER_DEPTH),
m_numCheckedSteps(0),
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
    this->m_numCheckedSteps = orig.m_numCheckedSteps;
    this->m_maximalDepth = orig.m_maximalDepth;
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
    if(pLevelData->getBlocksCount() < pLevelData->getLevelFile()->getBlocksCount())
        pLevelData->restart();
    m_root->clearSteps();
    m_root->prepareAsRoot();
    m_root->blockType = pLevelData->getBlockType();
    prepareStep(m_root);
    return FG_TRUE;
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
    m_numCheckedSteps = 0;
    m_reachedDepth = 0;
    clearSolutions();
    unsigned int rootIdx = m_searchRange.begin;
    unsigned int rootMax = m_searchRange.end;
    // reset maximal depth - if set to max, the search algorithm
    // will try to determine maximal depth itself
    // in most cases it will be too big and cause extreme computation time
    if(m_forcedMaxDepth >= MAX_NUMBER_DEPTH - 1)
        m_maximalDepth = MAX_NUMBER_DEPTH;
    else
        m_maximalDepth = m_forcedMaxDepth;
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
        if(!pSubStep || (pSubStep && pSubStep->moveDepth >= m_maximalDepth)) {
            if(!pSubStep && pPrevious->moveDepth == m_reachedDepth) {
                if(m_maximalDepth >= MAX_NUMBER_DEPTH - 1)
                    this->m_maximalDepth = m_reachedDepth;
            }
            stack.pop_back();
            if(stack.empty()) {
                break;
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
        int beforeCnt = pLevelData->getBlocksCount();
        int stepDiff = performStep(pSubStep);
        int balanceDiff = performBalance();
        int afterCnt = pLevelData->getBlocksCount();
        int allDiff = afterCnt - beforeCnt;
        
        pLevelData->convertTo(pSubStep->levelState);
        if(allDiff == 0) {
            // balanceStatus of 0 means that number of blocks did not change
            // need to skip such steps
            stack.pop_back();
            pSubStep = stack.back();
            pLevelData->restartFrom(pSubStep->levelState);
            continue;
        }

        // need some better heuristics
        // if after performing this step, the level state (number of blocks)
        // does not change - skip it
        if(pSubStep) {
            this->m_reachedDepth = math::max(m_reachedDepth, pSubStep->moveDepth);
            this->m_numCheckedSteps++;
        }
        // debug messages
#if defined(FG_DEBUG) || defined(DEBUG)
        {
            if(this->m_numCheckedSteps % 150000 == 0) {
                float t2 = timesys::ms();
                printf("[%.2fs] Already scanned: %d\n", (t2 - t1) / 1000.0f,
                       this->m_numCheckedSteps);
            }
            if(this->m_numCheckedSteps % 350000 == 0) {
                float t2 = timesys::ms();
                printf("[%.2fs] Stack size: %d | Current depth: %d\n",
                       (t2 - t1) / 1000.0f, stack.size(), pSubStep->moveDepth);
            }
            if(this->m_numCheckedSteps % 500000 == 0) {
                float t2 = timesys::ms();
                printf("[%.2fs] Stack size: %d | Current depth: %d | stack dump: \n",
                       (t2 - t1) / 1000.0f, stack.size(), pSubStep->moveDepth);
                dumpStack(stack);
            }
        } // debug messages
#endif // DEBUG
        if(checkCompletion()) {
            this->m_maximalDepth = math::min(m_maximalDepth, pSubStep->moveDepth);
            // stack contains the solution
            m_currentSolution = new CLevelSolution();
            m_solutions.push_back(m_currentSolution);
            printf("This step is in stack: %d\n", stack.find(pSubStep));
            m_currentSolution->setFromSearchSteps(stack);
#if defined(DEBUG)
            printf("-----------------------------------\n");
            m_currentSolution->dump();
            printf("-----------------------------------\n");
            dumpStack(stack, FG_TRUE);
            printf("-----------------------------------\n");
            printf("Already scanned: %d | Current depth: %d | Minimal: %d\n", m_numCheckedSteps,
                   pSubStep->moveDepth,
                   m_maximalDepth);
#endif
            if(pLevelData->isEmpty()) {
                stack.pop_back();
                pSubStep = stack.back();
                pLevelData->restartFrom(pSubStep->levelState);
            }
        }
    } // while(true))
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
        printf("The stage is CLEARED! [%d]\n", pLevelData->getBlocks().size());
    }
    return status;
}
//------------------------------------------------------------------------------

int CLevelSolutionFinder::performStep(SBlockMoveStep* pStep) {
    if(!pStep)
        return 0;
    CLevelDataHolder* pLevelData = getLevelDataHolder();
    const int beforeCount = getLevelDataHolder()->getBlocksCount();
    SBlockData* pBlockData = pLevelData->getBlockData(pStep->pos.x, pStep->pos.y);
    SBlockData* pNewBlock = pLevelData->moveBlockToNewPlace(pBlockData,
                                                            pStep->target.x,
                                                            pStep->target.y);

    const int afterCount = getLevelDataHolder()->getBlocksCount();
    int diff = afterCount - beforeCount;
    if(!pNewBlock) {
        base_type::getOrphanBlocks().push_back(pBlockData);
        diff = -1;
    } else {
        base_type::setUserDisturbance(pNewBlock);
    }
    return diff;
}
//------------------------------------------------------------------------------

int CLevelSolutionFinder::performBalance(void) {
    base_type::setChainReaction(); // now should animate
    base_type::setStepOn(FG_TRUE);
    int beforeCount = getLevelDataHolder()->getBlocksCount();
    while(base_type::isChainReaction()) {
        base_type::balance(10.0f);
    }
    int afterCount = getLevelDataHolder()->getBlocksCount();
    return (afterCount - beforeCount);
}
//------------------------------------------------------------------------------
#if defined(FG_DEBUG) || defined(DEBUG)

void CLevelSolutionFinder::dumpStack(const StepsVec& stack, fgBool reallyVerbose) {
    unsigned int nStack = stack.size();
    unsigned int maxIdx = 0;
    for(unsigned int i = 0; i < nStack; i++) {
        SBlockMoveStep* pStep = stack[i];
        if(i == 0)
            maxIdx = m_root->count();
        else
            maxIdx = stack[i - 1]->count();
        printf("[%d][%p][idx:%d/%d]", i + 1, pStep, pStep->moveIdx, maxIdx);
        if(i < nStack - 1)
            printf("-> ");
    }
    printf("\n");
    if(!reallyVerbose)
        return;
    // with really verbose set to true, function will also dump grid state after
    // every step on the stack
    CLevelDataHolder* pDataHolder = base_type::getLevelDataHolder();
    BlockInfoVec backup;
    pDataHolder->appendTo(backup);
    pDataHolder->restart();
    pDataHolder->dumpGrid();
    for(unsigned int i = 0; i < nStack; i++) {
        SBlockMoveStep* pStep = stack[i];
        pStep->dump();
        pDataHolder->restartFrom(pStep->levelState);
        pDataHolder->dumpGrid();
    }
    pDataHolder->restartFrom(backup);
}
#endif
//------------------------------------------------------------------------------

void CLevelSolutionFinder::setLevelDataHolder(CLevelDataHolder* pDataHolder) {
    if(pDataHolder && base_type::getLevelDataHolder() != pDataHolder) {
        m_root->clearSteps();
    }
    base_type::setLevelDataHolder(pDataHolder);
    if(base_type::getLevelDataHolder()) {
        m_root->blockType = base_type::getLevelDataHolder()->getBlockType();
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
    solutions.reserve(solutions.size() + n + 1);
    for(; i < n; i++) {
        solutions.push_back(m_solutions[i]);
    }
    return i;
}
//------------------------------------------------------------------------------

unsigned int CLevelSolutionFinder::copyTo(SolutionsVec& solutions) {
    const unsigned int n = m_solutions.size();
    unsigned int i = 0;
    solutions.reserve(solutions.size() + n + 1);
    for(; i < n; i++) {
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

