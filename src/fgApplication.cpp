/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgApplication.h"
#include "fgEngineMain.h"
#include "Util/fgProfiling.h"
#include "fgDebugConfig.h"

using namespace fg;
//------------------------------------------------------------------------------

fgBool CApplication::initProgram(void) {
    if(!customPreInitStep()) // CUSTOM
        return FG_FALSE;
    //timesys::init(); // # ??
#if defined(FG_DEBUG)
    profile::g_debugProfiling = new profile::CProfiling();
    profile::g_debugProfiling->initialize();
#endif
    float t1 = timesys::ms();
    FG_LOG_DEBUG("Init program main...");
    if(m_appInit) {
        // already initialized
        return FG_TRUE;
    }
    if(!m_engineMain) {
        FG_LOG_DEBUG("Creating game main object...");
        m_engineMain = new fg::CEngineMain(m_argc, m_argv);
    }
    // Well the whole configuration process should update the screen (swap buffers)
    // this is needed to display splash screens and show the game initialization
    // process by displaying the progress bar.
    if(!m_engineMain->loadConfiguration()) {
        return FG_FALSE;
    }
    // Initialize the main subsystems (gui, gfx and others)
    if(!m_engineMain->initialize()) {
        return FG_FALSE;
    }
    // Preload any required resources
    if(!m_engineMain->loadResources()) {
        return FG_FALSE;
    }
    m_engineMain->update(FG_TRUE);
    m_appInit = FG_TRUE;
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: Program initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    m_engineMain->update(FG_TRUE);

    customPostInitStep(); // CUSTOM
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CApplication::mainLoopStep(void) {
    if(!m_appInit) {
        FG_LOG_DEBUG("MainModule: Loop step - application not initialized...");
        return FG_FALSE;
    }
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Program::loopStep");
    }
#endif
    customPreLoopStep(); // CUSTOM
    if(m_isSuspend) {
        //FG_LOG_DEBUG("MainModule: Loop step - suspend...");
        return FG_TRUE;
    }

    if(m_isExit) {        
        FG_LOG_DEBUG("EXIT IS ACTIVATED - break loop main ! bye!");
        return FG_FALSE;
    }

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::update");
    }
#endif

    m_engineMain->update();

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::update");
        profile::g_debugProfiling->begin("Game::display");
    }
#endif
    if(!m_isFrameFreeze) {
        // well for now drawing and all update functions will be called in one place (one thread)
        // however it needs changing
        m_engineMain->preRender();
    }

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::display");
        profile::g_debugProfiling->begin("Game::render");
    }
#endif
    m_engineMain->render();
#if defined(FG_DEBUG)
    static int loopCount = 0;
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::render");
        profile::g_debugProfiling->end("Program::loopStep");
        profile::g_debugProfiling->updateHistory();

        loopCount++;
        if(loopCount > 150) {
            loopCount = 0;
            profile::g_debugProfiling->dumpToDefaultFile();
        }
    }
#endif
    customPostLoopStep(); // CUSTOM
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CApplication::closeProgram(void) {
    if(!m_appInit) {
        return;
    }
    FG_LOG_DEBUG("Closing program...");
    customPreQuitStep(); // CUSTOM
    if(m_engineMain) {
        m_engineMain->destroy();
        delete m_engineMain;
    }
    m_engineMain = NULL;
    m_appInit = FG_FALSE;
#if defined(FG_DEBUG)
    if(profile::g_debugProfiling)
        delete profile::g_debugProfiling;
    profile::g_debugProfiling = NULL;
#endif
    customPostQuitStep();
}
//------------------------------------------------------------------------------

void CApplication::suspendGfxEvent(void) {
    FG_LOG_DEBUG("MainModule: Suspending GFX Subsystem");
    if(m_engineMain)
        m_engineMain->getGfxMain()->suspendGFX();
}
//------------------------------------------------------------------------------

void CApplication::resumeGfxEvent(void) {
    FG_LOG_DEBUG("MainModule: Resuming GFX Subsystem...");
    if(m_engineMain)
        m_engineMain->getGfxMain()->resumeGFX();
}
//------------------------------------------------------------------------------
