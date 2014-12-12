/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGameLogic.h"
#include "Event/fgEventManager.h"

/**
 * 
 * @param pEventMgr
 */
fg::game::Logic::Logic(fg::base::Manager* pEventMgr) :
fg::base::Manager(),
m_status(GAME_INVALID),
m_currentStageID(0),
m_currentStageName(),
m_score(0),
m_stageScore(0),
m_playerName() {
    setEventManager(pEventMgr);
    m_managerType = FG_MANAGER_LOGIC;
    if(pEventMgr)
        initialize();
}

/**
 * 
 * @param orig
 */
fg::game::Logic::Logic(const Logic& orig) { 
    // ?? ?? ??
}

/**
 * 
 */
fg::game::Logic::~Logic() { 
    destroy();
}

/**
 * 
 */
void fg::game::Logic::clear(void) {
    // ?? ?? ?? 
}

/**
 * 
 * @return 
 */
fgBool fg::game::Logic::initialize(void) {
    m_init = FG_TRUE;
    m_managerType = FG_MANAGER_LOGIC;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fg::game::Logic::destroy(void) {
    m_init = FG_FALSE;
    return FG_TRUE;
}

/**
 * 
 * @param eventType
 * @return 
 */
fgBool fg::game::Logic::throwGameEvent(const fgEventType eventType) {
    if(!m_pEventMgr) {
        return FG_FALSE;
    }

    if(m_pEventMgr->getManagerType() != FG_MANAGER_EVENT)
        return FG_FALSE;

    static_cast<fgEventManager *>(m_pEventMgr)->throwEvent(eventType);
    return FG_TRUE;
}

/**
 * 
 */
void fg::game::Logic::startGameDefault(void) {
    //Elements are pushed into the "back" of the specific container and popped from its "front".
    m_statusQueue.push(GAME_ACTIVE); // #FIXME
}

/**
 * 
 * @param stageID
 */
void fg::game::Logic::startGame(const unsigned int stageID) {
    m_statusQueue.push(GAME_ACTIVE);
}

/**
 * 
 * @param stageName
 */
void fg::game::Logic::startGame(const std::string& stageName) {
    m_statusQueue.push(GAME_ACTIVE);
}

/**
 * 
 * @param stageName
 */
void fg::game::Logic::startGame(const char *stageName) {
    m_statusQueue.push(GAME_ACTIVE);
}

/**
 * 
 */
void fg::game::Logic::stopGame(void) {
    // There will be needed some additional checking
    // Also need to determine how to pass data (event structure)
    m_statusQueue.push(GAME_STOPPED);
}

/**
 * 
 */
void fg::game::Logic::pauseGame(void) {
    m_statusQueue.push(GAME_PAUSED);
}

/**
 * 
 */
void fg::game::Logic::restartGame(void) {
    m_statusQueue.push(GAME_RESTARTING);
}

/**
 * 
 */
void fg::game::Logic::update(void) {

    //while(!m_statusQueue.empty())
    if(!m_statusQueue.empty()) {
        // popped from front
        Status status = m_statusQueue.front();

        switch(status) {

            /// Game is active, normal gameplay
            case GAME_ACTIVE:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_STARTED);
                if(m_status == GAME_CONNECTING)
                    throwGameEvent(FG_EVENT_GAME_CONNECTED); // Are you sure?
                
                break;

                /// Game is paused, in most cases this displays pause menu
            case GAME_PAUSED:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_PAUSED);
                break;

                /// Game is not active/stopped - not even loading, normal nongame menu
            case GAME_STOPPED:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_STOPPED);
                break;

                /// Game is loading - loading, populating assets
            case GAME_LOADING:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_LOADING);
                break;

                /// Game is restarting - releasing any required data, then loading again
            case GAME_RESTARTING:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_RESTARTING);
                break;

                /// Game is stopping - releasing any required data, later back to nongame menu
            case GAME_STOPPING:
                break;

                /// Game is finishing - some midlevel presentation on level ending, showing
                /// game status, highscores etc, 
            case GAME_FINISHING:
                break;

                /// Game is finished, very similar to the FINISHING status, however this state
                /// is when level is unloaded (required data released)
            case GAME_FINISHED:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_FINISHED);
                break;

                /// Game is connecting to the server
            case GAME_CONNECTING:
                // ?
                break;

                /// Game is waiting for some external input (any kind)
            case GAME_WAITING:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_WAITING);
                break;

                /// Game disconnect from the server - any kind of reason
                /// This game state is for a very short period (in most cases max 1 frame)
            case GAME_DISCONNECTED:
                if(m_status != status)
                    throwGameEvent(FG_EVENT_GAME_DISCONNECTED);
                break;

                /// default - invalid/unknown
            default:
                break;
        }
        
        m_status = status; // Refresh current status
        m_statusQueue.pop();
    }
}
