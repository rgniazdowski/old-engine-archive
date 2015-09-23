/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGameMain.h"
#include "Event/fgEventManager.h"

using namespace fg;

//------------------------------------------------------------------------------

game::CGameMain::CGameMain(fg::base::CManager* pEventMgr) :
fg::base::CManager(),
m_status(Status::INVALID),
m_currentStageID(0),
m_currentStageName(),
m_score(0),
m_stageScore(0),
m_playerName() {
    setEventManager(pEventMgr);
    m_managerType = FG_MANAGER_GAME_MAIN;
    if(pEventMgr)
        initialize(); 
}
//------------------------------------------------------------------------------

game::CGameMain::CGameMain(const CGameMain& orig) {
    // ?? ?? ??
}
//------------------------------------------------------------------------------

game::CGameMain::~CGameMain() {
    destroy();
}
//------------------------------------------------------------------------------

void game::CGameMain::clear(void) {
    // ?? ?? ?? 
}
//------------------------------------------------------------------------------

fgBool game::CGameMain::initialize(void) {
    m_init = FG_TRUE;
    m_managerType = FG_MANAGER_GAME_MAIN;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool game::CGameMain::destroy(void) {
    m_init = FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool game::CGameMain::throwGameEvent(const event::EventType eventType) {
    if(!m_pEventMgr) {
        return FG_FALSE;
    }

    if(m_pEventMgr->getManagerType() != FG_MANAGER_EVENT)
        return FG_FALSE;

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->throwEvent(eventType);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void game::CGameMain::startGameDefault(void) {
    //Elements are pushed into the "back" of the specific container and popped from its "front".
    m_statusQueue.push(Status::ACTIVE); // #FIXME
}
//------------------------------------------------------------------------------

void game::CGameMain::startGame(const unsigned int stageID) {
    m_statusQueue.push(Status::ACTIVE);
}
//------------------------------------------------------------------------------

void game::CGameMain::startGame(const std::string& stageName) {
    m_statusQueue.push(Status::ACTIVE);
}
//------------------------------------------------------------------------------

void game::CGameMain::startGame(const char *stageName) {
    m_statusQueue.push(Status::ACTIVE);
}
//------------------------------------------------------------------------------

void game::CGameMain::stopGame(void) {
    // There will be needed some additional checking
    // Also need to determine how to pass data (event structure)
    m_statusQueue.push(Status::STOPPED);
}
//------------------------------------------------------------------------------

void game::CGameMain::pauseGame(void) {
    m_statusQueue.push(Status::PAUSED);
}
//------------------------------------------------------------------------------

void game::CGameMain::restartGame(void) {
    m_statusQueue.push(Status::RESTARTING);
}
//------------------------------------------------------------------------------

void game::CGameMain::update(void) {

    //while(!m_statusQueue.empty())
    if(!m_statusQueue.empty()) {
        // popped from front
        Status status = m_statusQueue.front();

        switch(status) {

                /// Game is active, normal gameplay
            case Status::ACTIVE:
                if(m_status != status)
                    throwGameEvent(game::GAME_STARTED);
                if(m_status == Status::CONNECTING)
                    throwGameEvent(game::GAME_CONNECTED); // Are you sure?

                break;

                /// Game is paused, in most cases this displays pause menu
            case Status::PAUSED:
                if(m_status != status)
                    throwGameEvent(game::GAME_PAUSED);
                break;

                /// Game is not active/stopped - not even loading, normal nongame menu
            case Status::STOPPED:
                if(m_status != status)
                    throwGameEvent(game::GAME_STOPPED);
                break;

                /// Game is loading - loading, populating assets
            case Status::LOADING:
                if(m_status != status)
                    throwGameEvent(game::GAME_LOADING);
                break;

                /// Game is restarting - releasing any required data, then loading again
            case Status::RESTARTING:
                if(m_status != status)
                    throwGameEvent(game::GAME_RESTARTING);
                break;

                /// Game is stopping - releasing any required data, later back to nongame menu
            case Status::STOPPING:
                break;

                /// Game is finishing - some midlevel presentation on level ending, showing
                /// game status, highscores etc, 
            case Status::FINISHING:
                break;

                /// Game is finished, very similar to the FINISHING status, however this state
                /// is when level is unloaded (required data released)
            case Status::FINISHED:
                if(m_status != status)
                    throwGameEvent(game::GAME_FINISHED);
                break;

                /// Game is connecting to the server
            case Status::CONNECTING:
                // ?
                break;

                /// Game is waiting for some external input (any kind)
            case Status::WAITING:
                if(m_status != status)
                    throwGameEvent(game::GAME_WAITING);
                break;

                /// Game disconnect from the server - any kind of reason
                /// This game state is for a very short period (in most cases max 1 frame)
            case Status::DISCONNECTED:
                if(m_status != status)
                    throwGameEvent(game::GAME_DISCONNECTED);
                break;

                /// default - invalid/unknown
            default:
                break;
        }

        m_status = status; // Refresh current status
        m_statusQueue.pop();
    }
}
//------------------------------------------------------------------------------
