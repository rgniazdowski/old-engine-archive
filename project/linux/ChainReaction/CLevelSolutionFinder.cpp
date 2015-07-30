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
m_pLevelData(pDataHolder),
m_levelSolver(NULL),
m_currentSolution(NULL),
m_currentBestSolution(NULL),
m_solutions(),
m_root(NULL),
m_reachedDepth(0),
m_minimalDepth(MAX_NUMBER_DEPTH),
m_numAllPossibleSteps(0),
m_isPrintMessages(FG_FALSE),
m_stepsIndexes(),
m_searchRange() {
    m_levelSolver = new CLevelSolver(m_pLevelData);
    //m_currentSolution = new CLevelSolution();
    m_solutions.reserve(16);
    m_root = new SBlockMoveStep();
    m_root->prepareAsRoot();
    if(m_pLevelData) {
        m_root->blockType = m_pLevelData->getBlockType();
    }
    m_searchRange.begin = 0;
    m_searchRange.end = 0;
    m_levelSolver->setSimulation(FG_TRUE);
}
//------------------------------------------------------------------------------

CLevelSolutionFinder::CLevelSolutionFinder(const CLevelSolutionFinder& orig) { }
//------------------------------------------------------------------------------

CLevelSolutionFinder::~CLevelSolutionFinder() {
    if(m_root) {
        m_root->clearSteps();
        delete m_root;
        m_root = NULL;
    }
    if(m_levelSolver) {
        m_levelSolver->setLevelDataHolder(NULL);
        delete m_levelSolver;
        m_levelSolver = NULL;
    }
    m_currentSolution = NULL;
    m_currentBestSolution = NULL;
    m_pLevelData = NULL;
    clearSolutions();
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::clear(void) {
    if(m_root)
        m_root->clear();
    if(m_pLevelData) {
        if(m_root)
            m_root->blockType = m_pLevelData->getBlockType();
    }
    m_currentSolution = NULL;
    clearSolutions();
    if(m_levelSolver)
        m_levelSolver->clear();
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
    if(!m_pLevelData) {
        return FG_FALSE;
    }
    if(m_pLevelData->isEmpty()) {
        return FG_FALSE;
    }
    if(m_pLevelData->getBlocksCount() < m_pLevelData->getLevelFile()->getBlocksCount())
        m_pLevelData->restart();
    m_root->clearSteps();
    m_root->prepareAsRoot();
    if(m_pLevelData) {
        m_root->blockType = m_pLevelData->getBlockType();
    }
    prepareStep(m_root);
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::prepareStep(SBlockMoveStep* pStep) {
    if(!pStep) {
        return FG_FALSE;
    }
    if(pStep->count() > 0)
        return FG_TRUE; // no need to add again
    CLevelDataHolder::BlockDataVec& blocks = m_pLevelData->getBlocks();
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
    if(!m_pLevelData)
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
        m_pLevelData->appendTo(pStep->levelState); // save the level state
        pStep->rewind();
        status = searchHelper(pStep);
        if(status) {
            //probably found solution
            //m_levelSolution->getMoves().insert(m_levelSolution->getMoves().begin(),
            //                                   *((SBlockMoveInfo*)pStep));
#if defined(DEBUG)
            if(m_currentBestSolution)
                m_currentBestSolution->dump();
            break;
#endif
        }
        // reset the game grid?
        m_pLevelData->restart();
    }

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelSolutionFinder::searchHelper(SBlockMoveStep* pMainStep) {
    if(!m_pLevelData)
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
            m_pLevelData->restartFrom(pSubStep->levelState);
            continue;
        } else {
            stack.push_back(pSubStep);
        }
#if defined(DEBUG)
        if(m_isPrintMessages)
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
            if(m_pLevelData->isEmpty()) {
                stack.pop_back();
                pSubStep = stack.back();
                m_pLevelData->restartFrom(pSubStep->levelState);

            }
        } else {
            m_pLevelData->appendTo(pSubStep->levelState);
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
    if(!m_pLevelData)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    if(m_pLevelData->getBlocksCount() == 0) {
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
    SBlockData* pBlockData = m_pLevelData->getBlockData(pStep->pos.x, pStep->pos.y);
    SBlockData* pNewBlock = m_pLevelData->moveBlockToNewPlace(pBlockData,
                                                              pStep->target.x,
                                                              pStep->target.y);
    if(!pNewBlock) {
        m_levelSolver->getOrphanBlocks().push_back(pBlockData);
    } else {
        m_levelSolver->setUserDisturbance(pNewBlock);
    }
}
//------------------------------------------------------------------------------

void CLevelSolutionFinder::performBalance(void) {
    if(!m_levelSolver)
        return;
    m_levelSolver->setChainReaction(); // now should animate
    m_levelSolver->setStepOn(FG_TRUE);
    while(m_levelSolver->isChainReaction()) {
        m_levelSolver->balance(10.0f);
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
