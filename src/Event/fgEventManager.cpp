/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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

/**
 * Default constructor for Event Manager object
 */
fgEventManager::fgEventManager() {
    m_managerType = FG_MANAGER_EVENT;
}

/**
 * Default destructor for Event Manager object
 */
fgEventManager::~fgEventManager() {
    fgEventManager::destroy();
}

/**
 * 
 * @return 
 */
fgBool fgEventManager::destroy(void) {
    for(fgCallbackBindingMap::iterator it = m_keyDownBinds.begin(); it != m_keyDownBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    for(fgCallbackBindingMap::iterator it = m_keyUpBinds.begin(); it != m_keyUpBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    for(fgCallbackBindingMap::iterator it = m_eventBinds.begin(); it != m_eventBinds.end(); it++) {
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

/**
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

/**
 * 
 * @return 
 */
fgBool fgEventManager::initialize(void) {
    return FG_TRUE;
}

/**
 * 
 * @param eventCode
 */
void fgEventManager::throwEvent(fgEventType eventCode) {
    fgThrownEvent event(eventCode);
    m_eventsQueue.push(event);
}

/**
 * 
 * @param eventCode
 * @param list
 */
void fgEventManager::throwEvent(fgEventType eventCode, fgArgumentList *list) {
    fgThrownEvent event(eventCode, list);
    m_eventsQueue.push(event);
}

/**
 * 
 * @param eventCode
 * @param pSystemData
 */
void fgEventManager::throwEvent(fgEventType eventCode,
                                void *pSystemData) {
    fgThrownEvent event(eventCode, (void *)pSystemData);
    m_eventsQueue.push(event);
}

/**
 * 
 * @param keyCode
 * @param callback
 * @return 
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

/**
 * 
 * @param keyCode
 * @param callback
 * @return 
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

/**
 * 
 * @param eventCode
 * @param pCallback
 * @return 
 */
fgFunctionCallback* fgEventManager::addEventCallback(fgEventType eventCode,
                                                     fgFunctionCallback *pCallback) {
    if(!pCallback || (int)eventCode < 0)
        return NULL;
    // Duplicate callbacks are not allowed for the same event
    if(m_eventBinds[eventCode].find(pCallback) >= 0) {
        return NULL;
    }
    m_eventBinds[eventCode].push_back(pCallback);
    return pCallback;
}

/**
 * 
 * @param eventCode
 * @param pFunction
 * @return 
 */
fgFunctionCallback* fgEventManager::addEventCallback(fgEventType eventCode,
                                                     fgFunctionCallback::fgFunction pFunction) {
    if(!pFunction || (int)eventCode < 0)
        return NULL;
    // !! !!
    // Need to check somehow for duplicates #FIXME
    fgFunctionCallback *pCallback = new fgFunctionCallback(pFunction);
    m_eventBinds[eventCode].push_back(pCallback);
    return pCallback;
}

/**
 * 
 * @param eventCode
 * @param pPlainFunction
 * @param pUserData
 * @return 
 */
fgFunctionCallback* fgEventManager::addEventCallback(fgEventType eventCode,
                                                     fgPlainFunctionCallback::fgPlainFunction pPlainFunction,
                                                     void *pUserData) {
    if((int)eventCode < 0 || !pPlainFunction)
        return NULL;

    fgFunctionCallback *pCallback = new fgPlainFunctionCallback(pPlainFunction, pUserData);
    m_eventBinds[eventCode].push_back(pCallback);
    return pCallback;
}

/**
 * 
 * @param eventCode
 * @param pCallback
 * @return 
 */
fgBool fgEventManager::removeEventCallback(fgEventType eventCode, fgFunctionCallback *pCallback) {
    if(!pCallback || (int)eventCode < 0)
        return FG_FALSE;

    fgCallbacksVec &callbacksVec = m_eventBinds[eventCode];
    if(callbacksVec.empty())
        return FG_FALSE;
    fgCallbacksVecItor cit = callbacksVec.begin(), end = callbacksVec.end();
    for(; cit != end; cit++) {
        if(*cit == pCallback) {
            m_eventBinds[eventCode].erase(cit);
            return FG_TRUE;
            break;
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @param pCallback
 * @param timeout
 * @param pArgList
 * @return 
 */
fgFunctionCallback* fgEventManager::addTimeoutCallback(fgFunctionCallback *pCallback,
                                                       const int timeout,
                                                       fgArgumentList *pArgList) {
    if(!pCallback)
        return NULL;
    fgTimeoutCallback timeoutCallback(pCallback, timeout, pArgList);
    timeoutCallback.timeStamp = FG_GetTicks();
    m_timeoutCallbacks.push_back(timeoutCallback);
    return pCallback;
}

/**
 * 
 * @param pCallback
 * @return 
 */
fgBool fgEventManager::removeTimeoutCallback(fgFunctionCallback *pCallback) {
    if(!pCallback)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    fgTimeoutCallbacksVecItor begin = m_timeoutCallbacks.begin();
    fgTimeoutCallbacksVecItor it = begin,
            end = m_timeoutCallbacks.end();
    for(; it != end; it++) {
        fgTimeoutCallback &timeout = (*it);
        if(timeout.callback == pCallback) {
            timeout.callback = NULL;
            timeout.argList = NULL;
            status = FG_TRUE;
            m_timeoutCallbacks.erase(it);
            it--;
            end = m_timeoutCallbacks.end();
        }
    }
    return status;
}

/**
 * 
 * @param pCallback
 * @param repeats
 * @param interval
 * @param pArgList
 * @return 
 */
fgFunctionCallback* fgEventManager::addCyclicCallback(fgFunctionCallback *pCallback,
                                                      const int repeats,
                                                      const int interval,
                                                      fgArgumentList *pArgList) {
    if(!pCallback)
        return NULL;
    fgCyclicCallback cyclicCallback(pCallback, repeats, interval, pArgList);
    cyclicCallback.timeStamp = FG_GetTicks();
    m_cyclicCallbacks.push_back(cyclicCallback);
    return pCallback;
}

/**
 * 
 * @param pCallback
 * @return 
 */
fgBool fgEventManager::removeCyclicCallback(fgFunctionCallback *pCallback) {
    if(!pCallback)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    fgCyclicCallbacksVecItor begin = m_cyclicCallbacks.begin();
    fgCyclicCallbacksVecItor it = begin,
            end = m_cyclicCallbacks.end();
    for(; it != end; it++) {
        fgCyclicCallback &cyclic = (*it);
        if(cyclic.callback == pCallback) {
            cyclic.callback = NULL;
            cyclic.argList = NULL;
            status = FG_TRUE;
            m_cyclicCallbacks.erase(it);
            it--;
            end = m_cyclicCallbacks.end();
        }
    }
    return status;
}

/**
 * This adds key code to the pool of pressed down keys
 * @param keyCode
 */
void fgEventManager::addKeyDown(int keyCode) {
    m_keysDownPool.push_back(keyCode);
}

/**
 * This adds key code to the pool of released (up) keys
 * @param keyCode
 */
void fgEventManager::addKeyUp(int keyCode) {
    m_keysUpPool.push_back(keyCode);
}

/* 
 * This function calls all callbacks from the triggered/thrown events
 * also executes callbacks from cyclical and timeouts
 */
void fgEventManager::executeEvents(void) {
    // Phase 1: execute keyboard callbacks
    for(int i = 0; i < (int)m_keysDownPool.size(); i++) {
        int keyCode = m_keysDownPool[i];
        fgCallbackBindingMap::iterator found = m_keyDownBinds.find(keyCode);
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
        fgCallbackBindingMap::iterator found = m_keyUpBinds.find(keyCode);
        if(found == m_keyUpBinds.end())
            continue;
        for(int j = 0; j < (int)m_keyUpBinds[keyCode].size(); j++) {
            // There's no need for argument list
            m_keyUpBinds[keyCode][j]->Call();
        }
    }
    m_keysUpPool.clear();

    // Phase 2: execution of thrown events (now including the argument list).
    // Btw after calling the proper callback,
    // queue entry with argument list must be erased 
    while(!m_eventsQueue.empty()) {
        fgThrownEvent &event = m_eventsQueue.front();
        int eventCode = event.eventCode;
        //FG_LOG_DEBUG("Event code thrown %d | list: %p", eventCode, event.argList);
        fgCallbackBindingMap::iterator found = m_eventBinds.find(eventCode);
        if(found == m_eventBinds.end()) {
            if(event.argList)
                delete event.argList;
            m_eventsQueue.pop();
            continue;
        }
        fgCallbacksVec &callbacks = (*found).second;
        for(int j = 0; j < (int)callbacks.size(); j++) {
            if(callbacks[j]) {
                if(event.argList) {
                    callbacks[j]->Call(event.argList);
                } else if(event.systemData) {
                    callbacks[j]->Call((void*)event.systemData);
                } else {
                    callbacks[j]->Call();
                }
            }
        }

        // Free the argument list as it is no longer need - one allocation for one call
        if(event.argList)
            delete event.argList;
        m_eventsQueue.pop();
    }

    // Phase 3: Timeouts
    unsigned long int TS = FG_HardwareState->getTS(); // #FIXME - hardware state TS

    // After timeout is executed it needs to be deleted from the timeouts pool - also the callback pointer must 
    // be freed with the argument list as they no longer needed
    for(fgTimeoutCallbacksVecItor it = m_timeoutCallbacks.begin(); it != m_timeoutCallbacks.end(); it++) {
        if(TS - it->timeStamp >= (unsigned long int)it->timeout) {
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
    for(fgCyclicCallbacksVecItor it = m_cyclicCallbacks.begin(); it != m_cyclicCallbacks.end(); it++) {
        if(TS - it->timeStamp >= (unsigned long int)it->interval) {
            if(it->callback && (it->repeats || it->repeats == -1)) {
                it->callback->Call(it->argList);
                it->timeStamp = TS;
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
