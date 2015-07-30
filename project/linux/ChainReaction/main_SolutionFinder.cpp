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
 * File:   main_SolutionFinder.cpp
 * Author: vigilant
 *
 * Created on July 30, 2015, 11:57 AM
 */

#include "fgBuildConfig.h"
#include "fgVector.h"
#include "fgLog.h"

#include "GameLogic/fgGrid.h"
#include "Util/fgTime.h"
#include "Util/fgStrings.h"
#include "Util/fgPath.h"
#include "Util/fgFile.h"
#include "Util/fgMemory.h"

#include "AdditionalTypes.h"
#include "CLevelSolution.h"
#include "CLevelSolutionFinder.h"
#include "CLevelSolver.h"

#include "Thread/fgThread.h"
//------------------------------------------------------------------------------

struct SFinderThreadData
{
    fg::CLevelSolutionFinder* pFinder;
    fg::game::CGrid* pGrid;
    fg::CLevelDataHolder* pLevelData;
    fg::CLevelFile* pLevelFile;
    fg::CLevelSolution* pBestSolution;

    fg::CVector<fg::CLevelSolution*> copiedSolutions;

    unsigned int begin;
    unsigned int end;
    unsigned int checkedSteps;
    float timeElapsed;
    fg::CThread* pThread;

    SFinderThreadData();
    SFinderThreadData(const SFinderThreadData& other);
    virtual ~SFinderThreadData();

    void clear(void);

    void destroy(void);

    inline void setRange(unsigned int _begin, unsigned int _end) {
        begin = _begin;
        end = _end;
    }

    inline void setRange(unsigned int _single) {
        begin = _single;
        end = _single;
    }
}; // struct SFinderThreadData
//------------------------------------------------------------------------------

SFinderThreadData::SFinderThreadData() :
pFinder(NULL),
pGrid(NULL),
pLevelData(NULL),
pLevelFile(NULL),
pBestSolution(NULL),
copiedSolutions(),
begin(0),
end(0),
checkedSteps(0),
timeElapsed(0.0f),
pThread(NULL) { }
//------------------------------------------------------------------------------

SFinderThreadData::SFinderThreadData(const SFinderThreadData& other) { }
//------------------------------------------------------------------------------

SFinderThreadData::~SFinderThreadData() { }
//------------------------------------------------------------------------------

void SFinderThreadData::clear(void) {
    unsigned int n = copiedSolutions.size();
    for(unsigned int i = 0; i < n; i++) {
        fg::CLevelSolution* pSolution = copiedSolutions[i];
        if(pSolution) {
            delete pSolution;
        }
        copiedSolutions[i] = NULL;
    }
    copiedSolutions.clear();
    timeElapsed = 0.0f;
    checkedSteps = 0;
    begin = 0;
    end = 0;
}

void SFinderThreadData::destroy(void) {
    if(pFinder)
        delete pFinder;
    if(pLevelData)
        delete pLevelData;
    if(pLevelFile)
        delete pLevelFile;
    if(pGrid)
        delete pGrid;
    pGrid = NULL;
    pLevelFile = NULL;
    pLevelData = NULL;
    pFinder = NULL;
    clear();
}

//------------------------------------------------------------------------------

struct SConfigSL
{
    std::string levelsDirPath;
    std::string solutionsDirPath;
    std::string levelFilePath;
    std::string solutionFilePath;
    std::string solutionFilePrefix;
    fgBool checkAllRanges;
    fgBool forceSearch;
    unsigned int numSimultaneousThreads;

    SConfigSL();
    virtual ~SConfigSL();
}; // struct SConfigSL
//------------------------------------------------------------------------------

SConfigSL::SConfigSL() :
levelsDirPath(),
solutionsDirPath(),
levelFilePath(),
solutionFilePath(),
solutionFilePrefix(),
checkAllRanges(FG_FALSE),
forceSearch(FG_FALSE),
numSimultaneousThreads(1) { //

    levelsDirPath = "levels";
    solutionsDirPath = "solutions";
    solutionFilePrefix = "solution_";
}
//------------------------------------------------------------------------------

SConfigSL::~SConfigSL() { }

//------------------------------------------------------------------------------

void CheckOptions(int argc, char **argv, SConfigSL& config) {
    if(!argv)
        return;
    const unsigned int n = argc;
    using namespace fg;
    for(unsigned int i = 0; i < n; i++) {
        std::string option = argv[i];
        if(strings::startsWith(argv[i], "--level-file=", FG_FALSE)) {
            CStringVector parts = strings::split(option, '=');
            if(parts.size() > 1)
                config.levelFilePath = parts[1];
        } else if(strings::startsWith(argv[i], "--levels-path=", FG_FALSE)) {
            CStringVector parts = strings::split(option, '=');
            if(parts.size() > 1)
                config.levelsDirPath = parts[1];
        } else if(strings::startsWith(argv[i], "--solution-prefix=", FG_FALSE)) {
            CStringVector parts = strings::split(option, '=');
            if(parts.size() > 1)
                config.solutionFilePrefix = parts[1];
        } else if(strings::startsWith(argv[i], "--force-search", FG_FALSE)) {
            config.forceSearch = FG_TRUE;
        }
    }
}
//------------------------------------------------------------------------------

void* SearchThreadWrapper(void *arg) {
    if(!arg)
        return NULL;
    SFinderThreadData* pData = (SFinderThreadData *)arg;
    if(!pData->pFinder || !pData->pLevelData) {
        FG_LOG_ERROR("CR: Invalid thread data passed...");
        return NULL;
    }
    using namespace fg;
    float t1 = timesys::ms();
    sleep(1); // LAG

    pData->pFinder->prepareRoot(); // #FIXME
    FG_LOG_INFO("CR: Thread: Root has %d steps", pData->pFinder->getRoot()->count());
    pData->pFinder->selectSearchRange(pData->begin, pData->end);
    pData->pFinder->getSearchRange(pData->begin, pData->end);

    FG_LOG_INFO("CR: Thread will begin to search range [%d;%d]", pData->begin, pData->end);
    fgBool isFound = pData->pFinder->search();

    float t2 = timesys::ms();
    FG_LOG_INFO("CR: Thread with range [%d;%d] finished. Found best solution.",
                pData->begin, pData->end);
    pData->pFinder->copyTo(pData->copiedSolutions);
    pData->pBestSolution = pData->pFinder->getBestSolutionFrom(pData->copiedSolutions);
#if defined(DEBUG) || defined(FG_DEBUG)
    //pData->pBestSolution->dump();
#endif
    pData->timeElapsed = t2 - t1;
    pData->checkedSteps = pData->pFinder->getNumCheckedSteps();

    FG_LOG_INFO("CR: Thread exiting after %.2f seconds (~%d minutes) and %d checked steps.",
                pData->timeElapsed / 1000.0f, (int)(math::ceil(pData->timeElapsed / 1000.0f / 60.0f)), pData->checkedSteps);
    return NULL;
}

//------------------------------------------------------------------------------

/*
 * 
 */
int main(int argc, char** argv) {
    using namespace fg;
    timesys::init();
    SConfigSL config;

    CheckOptions(argc, argv, config);

    if(config.levelFilePath.empty()) {
        FG_LOG_ERROR("CR: Empty level file path");
        return 1;
    }

    FG_LOG_INFO("CR: Level file:      '%s'", config.levelFilePath.c_str());
    FG_LOG_INFO("CR: Levels path:     '%s'", config.levelsDirPath.c_str());
    FG_LOG_INFO("CR: Solutions path:  '%s'", config.solutionsDirPath.c_str());
    FG_LOG_INFO("CR: Solution prefix: '%s'", config.solutionFilePrefix.c_str());

    const char *levelFileName = path::fileName(config.levelFilePath.c_str());
    if(!levelFileName) {
        FG_LOG_ERROR("CR: Unable to determine file name from level file path");
        return 1;
    }
    std::string solutionFileName;
    solutionFileName.append(config.solutionFilePrefix);
    solutionFileName.append(levelFileName);
    config.solutionFilePath.clear();

    config.solutionFilePath = path::join(config.solutionsDirPath, solutionFileName);
    FG_LOG_INFO("CR: Solution file:   '%s'", config.solutionFilePath.c_str());

    if(!util::CRegularFile::exists(config.levelFilePath)) {
        FG_LOG_ERROR("CR: Level file does not exist");
        return 1;
    }
    if(util::CRegularFile::exists(config.solutionFilePath)) {
        if(config.forceSearch) {
            FG_LOG_INFO("CR: The solution file already exists. Solution search is forced.");
        } else {
            FG_LOG_INFO("CR: The solution file already exists. Will quit now. Try --force-search flag.");
            return 0;
        }
    }

    const unsigned int nThreads = config.numSimultaneousThreads;
    // now need to create an array
    // with copies of level files, level data holders, game grids and solution finders
    SFinderThreadData **finderData = NULL;
    finderData = (SFinderThreadData **)fgMalloc<SFinderThreadData *>(nThreads);
    for(unsigned int i = 0; i < nThreads; i++) {
        finderData[i] = new SFinderThreadData();
        SFinderThreadData* pData = finderData[i];

        pData->pLevelFile = new CLevelFile(config.levelFilePath);
        pData->pLevelFile->load();
        pData->pGrid = new game::CGrid(); // by default two dimensions
        pData->pLevelData = new CLevelDataHolder(pData->pGrid, pData->pLevelFile);
        pData->pFinder = new CLevelSolutionFinder(pData->pLevelData);
        pData->begin = i * 10;
        pData->end = i * 10;

        unsigned int maxDepth = pData->pLevelFile->getBlocksCount();
        maxDepth = (unsigned int)(math::ceil(math::sqrt((float)maxDepth))) + 3; // testing
        if(maxDepth < 6)
            maxDepth = 6;
        pData->pFinder->setForcedMaximalDepth(maxDepth);
        FG_LOG_INFO("CR: Level file has %d blocks", pData->pLevelFile->getBlocksCount());
        FG_LOG_INFO("CR: Setting forced maximal depth for thread: %d", maxDepth);

        pData->pThread = new CThread();
        pData->pThread->setFunction(&SearchThreadWrapper, (void*)pData);
    }

    for(unsigned int i = 0; i < nThreads; i++) {
        finderData[i]->pThread->join();
    }

    FG_LOG_INFO("CR: All threads finished... will now find the best one of all solutions");
    CLevelSolution *pAllBestSolution = NULL;
    for(unsigned int i = 0; i < nThreads; i++) {
        SFinderThreadData* pData = finderData[i];
        if(!pData)
            continue;
        if(!pData->pBestSolution)
            continue;

        if(!pAllBestSolution) {
            pAllBestSolution = pData->pBestSolution;
            continue;
        }

        if(pAllBestSolution->count() > pData->pBestSolution->count()) {
            pAllBestSolution = pData->pBestSolution;
        }
    }

    if(pAllBestSolution) {
        FG_LOG_INFO("CR: Will now save solution to a proper path: '%s'", config.solutionFilePath.c_str());
        pAllBestSolution->save(config.solutionFilePath);
#if defined(DEBUG)
        pAllBestSolution->dump();
#endif
    }

    for(unsigned int i = 0; i < nThreads; i++) {
        SFinderThreadData* pData = finderData[i];
        delete pData->pThread;
        pData->pThread = NULL;
        pData->destroy();
        delete pData;
        finderData[i] = NULL;
    }
    fgFree<SFinderThreadData*>(finderData);
    return 0;
}
//------------------------------------------------------------------------------
