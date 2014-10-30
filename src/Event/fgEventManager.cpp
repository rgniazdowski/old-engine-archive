/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgEventManager.h"
#include "fgCommon.h"
#include "fgLog.h"
#include "Util/fgTime.h"

#include "Hardware/fgHardwareState.h"

/*
 * Default constructor for Event Manager object
 */
fgEventManager::fgEventManager() {
    m_managerType = FG_MANAGER_EVENT;
}

/*
 * Default destructor for Event Manager object
 */
fgEventManager::~fgEventManager() {
    fgEventManager::destroy();
}

/*
 *
 */
fgBool fgEventManager::destroy(void) {
    for(fgCallbackBinding::iterator it = m_keyDownBinds.begin(); it != m_keyDownBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    for(fgCallbackBinding::iterator it = m_keyUpBinds.begin(); it != m_keyUpBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    for(fgCallbackBinding::iterator it = m_eventBinds.begin(); it != m_eventBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            if(it->second[i])
                delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    while(!m_eventsQueue.empty()) {
        if(m_eventsQueue.front().argList != NULL)
            delete m_eventsQueue.front().argList;
        m_eventsQueue.pop();
    }

    for(int i = 0; i < (int)m_timeoutCallbacks.size(); i++) {
        if(m_timeoutCallbacks[i].argList)
            delete m_timeoutCallbacks[i].argList;
        if(m_timeoutCallbacks[i].callback)
            delete m_timeoutCallbacks[i].callback;
        m_timeoutCallbacks[i].argList = NULL;
        m_timeoutCallbacks[i].callback = NULL;
    }

    for(int i = 0; i < (int)m_cyclicCallbacks.size(); i++) {
        if(m_cyclicCallbacks[i].argList)
            delete m_cyclicCallbacks[i].argList;
        if(m_cyclicCallbacks[i].callback)
            delete m_cyclicCallbacks[i].callback;
        m_cyclicCallbacks[i].argList = NULL;
        m_cyclicCallbacks[i].callback = NULL;
    }

    fgEventManager::clear();

    return FG_TRUE;
}

/*
 *
 */
void fgEventManager::clear(void) {
    m_keyDownBinds.clear();
    m_keyUpBinds.clear();
    m_eventBinds.clear();
    m_timeoutCallbacks.clear();
    m_cyclicCallbacks.clear();

    m_keysUpPool.clear();
    m_keysDownPool.clear();
    m_managerType = FG_MANAGER_EVENT;
}

/*
 *
 */
fgBool fgEventManager::initialize(void) {
    return FG_TRUE;
}

/*
 *
 */
void fgEventManager::throwEvent(fgEventType eventCode, fgArgumentList *list) {
    fgThrownEvent event(eventCode, list);
    m_eventsQueue.push(event);
}

/*
 *
 */
fgFunctionCallback* fgEventManager::addKeyDownCallback(int keyCode, fgFunctionCallback *callback) {
    if(!callback || keyCode <= 0)
        return NULL;
    if(m_keyDownBinds[keyCode].find(callback) >= 0) {
        return NULL;
    }
    m_keyDownBinds[keyCode].push_back(callback);
    return callback;
}

/*
 *
 */
fgFunctionCallback* fgEventManager::addKeyUpCallback(int keyCode, fgFunctionCallback *callback) {
    if(!callback || keyCode <= 0)
        return NULL;
    if(m_keyUpBinds[keyCode].find(callback) >= 0) {
        return NULL;
    }
    m_keyUpBinds[keyCode].push_back(callback);
    return callback;
}

/*
 *
 */
fgFunctionCallback* fgEventManager::addEventCallback(fgEventType eventCode, fgFunctionCallback *callback) {
    if(!callback || (int)eventCode < 0)
        return NULL;
    // Duplicate callbacks are not allowed for the same event
    if(m_eventBinds[eventCode].find(callback) >= 0) {
        return NULL;
    }
    m_eventBinds[eventCode].push_back(callback);
    return callback;
}

/*
 *
 */
fgFunctionCallback* fgEventManager::addEventCallback(fgEventType eventCode, fgFunctionCallback::fgFunction function) {
    if(!function || (int)eventCode < 0)
        return NULL;
    // !! !!
    // Need to check somehow for duplicates #FIXME
    fgFunctionCallback *callback = new fgFunctionCallback(function);
    m_eventBinds[eventCode].push_back(callback);
    return callback;
}

/*
 *
 */
fgBool fgEventManager::removeEventCallback(fgEventType eventCode, fgFunctionCallback *callback) {
    if(!callback || (int)eventCode < 0)
        return FG_FALSE;
    
    fgCallbacksVec &callbacksVec = m_eventBinds[eventCode];
    if(callbacksVec.empty())
        return FG_FALSE;
    fgCallbacksPoolItor cit = callbacksVec.begin(), end = callbacksVec.end();
    for(; cit != end; cit++) {
        if(*cit == callback) {
            m_eventBinds[eventCode].erase(cit);
            return FG_TRUE;
            break;
        }
    }
    return FG_TRUE;
}

/*
 *
 */
fgFunctionCallback* fgEventManager::addTimeoutCallback(fgFunctionCallback *callback, int timeout, fgArgumentList *argList) {
    if(!callback)
        return NULL;
    fgTimeoutCallback timeoutCallback(callback, timeout, argList);
    timeoutCallback.timestamp = FG_GetTicks();
    m_timeoutCallbacks.push_back(timeoutCallback);
    return callback;
}

/*
 *
 */
fgFunctionCallback* fgEventManager::addCyclicCallback(fgFunctionCallback *callback, int repeats, int interval, fgArgumentList *argList) {
    if(!callback)
        return NULL;
    fgCyclicCallback cyclicCallback(callback, repeats, interval, argList);
    cyclicCallback.timestamp = FG_GetTicks();
    m_cyclicCallbacks.push_back(cyclicCallback);
    return callback;
}

/*
 * This adds key code to the pool of pressed down keys
 */
void fgEventManager::addKeyDown(int keyCode) {
    m_keysDownPool.push_back(keyCode);
}

/*
 * This adds key code to the pool of released (up) keys
 */
void fgEventManager::addKeyUp(int keyCode) {
    m_keysUpPool.push_back(keyCode);
}

/* 
 * This function calls all callbacks from the triggered/thrown events
 * also executes callbacks from cyclics and timeouts
 */
void fgEventManager::executeEvents(void) {
    static int yolo = 0;
    yolo ++;
    if(yolo < 3) {
        printf("###########################################################\n#################### EXECUTE EVENTS #######################\n###########################################################\n");
    }
    // Phase 1: execute keyboard callbacks
    for(int i = 0; i < (int)m_keysDownPool.size(); i++) {
        int keyCode = m_keysDownPool[i];
        fgCallbackBinding::iterator found = m_keyDownBinds.find(keyCode);
        if(found == m_keyDownBinds.end())
            continue;
        for(int j = 0; j < (int)m_keyDownBinds[keyCode].size(); j++) {
            // There's no need for argument list
            m_keyDownBinds[keyCode][j]->Call();
        }
    }
    m_keysDownPool.clear();

    for(int i = 0; i < (int)m_keysUpPool.size(); i++) {
        int keyCode = m_keysUpPool[i];
        fgCallbackBinding::iterator found = m_keyUpBinds.find(keyCode);
        if(found == m_keyUpBinds.end())
            continue;
        for(int j = 0; j < (int)m_keyUpBinds[keyCode].size(); j++) {
            // There's no need for argument list
            m_keyUpBinds[keyCode][j]->Call();
        }
    }
    m_keysUpPool.clear();

    // Phase 2: execution of thrown events (now including the argument list). Btw after calling the proper callback,
    // queue entry with argument list must be erased 
    while(!m_eventsQueue.empty()) {
        fgThrownEvent &event = m_eventsQueue.front();
        int eventCode = event.eventCode;
        //FG_LOG::PrintDebug("Event code thrown %d | list: %p", eventCode, event.argList);
        fgCallbackBinding::iterator found = m_eventBinds.find(eventCode);
        if(found == m_eventBinds.end()) {
            if(event.argList)
                delete event.argList;
            m_eventsQueue.pop();
            continue;
        }

        for(int j = 0; j < (int)m_eventBinds[eventCode].size(); j++) {
            if(m_eventBinds[eventCode][j])
                m_eventBinds[eventCode][j]->Call(event.argList);
        }

        // Free the argument list as it is no longer need - one allocation for one call
        if(event.argList)
            delete event.argList;
        m_eventsQueue.pop();
    }

    // Phase 3: Timeouts
    unsigned long int TS = FG_HardwareState->getTS();

    // After timeout is executed it needs to be deleted from the timeouts pool - also the callback pointer must 
    // be freed with the argument list as they no longer needed
    for(fgTimeoutCallbacksVec::iterator it = m_timeoutCallbacks.begin(); it != m_timeoutCallbacks.end(); it++) {
        if(TS - it->timestamp >= (unsigned long int)it->timeout) {
            if(it->callback) {
                it->callback->Call(it->argList);
                delete it->callback;
                it->callback = NULL;
            }
            if(it->argList)
                delete it->argList;
            it->argList = NULL;

            if(it->callback == NULL) {
                m_timeoutCallbacks.erase(it);
                it--;
            }
        }
    }

    // Phase 4: Cyclic callbacks
    for(fgCyclicCallbacksVec::iterator it = m_cyclicCallbacks.begin(); it != m_cyclicCallbacks.end(); it++) {
        if(TS - it->timestamp >= (unsigned long int)it->interval) {
            if(it->callback && (it->repeats || it->repeats == -1)) {
                it->callback->Call(it->argList);
                it->timestamp = TS;
                if(it->repeats != 0)
                    it->repeats--;
            }

            if(it->callback == NULL)
                it->repeats = 0;

            if(it->repeats == 0) {
                if(it->callback)
                    delete it->callback;
                it->callback = NULL;
                if(it->argList)
                    delete it->argList;
                it->argList = NULL;

                m_cyclicCallbacks.erase(it);
                it--;
            }
        }
    }
}
