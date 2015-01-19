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
fg::event::CEventManager::CEventManager() {
    m_managerType = FG_MANAGER_EVENT;
}

/**
 * Destructor for Event Manager object
 */
fg::event::CEventManager::~CEventManager() {
    fg::event::CEventManager::destroy();
}

/**
 * 
 * @return 
 */
fgBool fg::event::CEventManager::destroy(void) {
    for(CallbackBindingMap::iterator it = m_eventBinds.begin(); it != m_eventBinds.end(); it++) {
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

    fg::event::CEventManager::clear();
    return FG_TRUE;
}

/**
 *
 */
void fg::event::CEventManager::clear(void) {
    m_eventBinds.clear();
    m_timeoutCallbacks.clear();
    m_cyclicCallbacks.clear();
    m_managerType = FG_MANAGER_EVENT;
}

/**
 * 
 * @return 
 */
fgBool fg::event::CEventManager::initialize(void) {
    return FG_TRUE;
}

/**
 * 
 * @param eventCode
 */
void fg::event::CEventManager::throwEvent(EventType eventCode) {
    SThrownEvent event(eventCode);
    m_eventsQueue.push(event);
}

/**
 * 
 * @param eventCode
 * @param list
 */
void fg::event::CEventManager::throwEvent(EventType eventCode, CArgumentList *list) {
    SThrownEvent event(eventCode, list);
    m_eventsQueue.push(event);
}

/**
 * 
 * @param eventCode
 * @param pSystemData
 */
void fg::event::CEventManager::throwEvent(EventType eventCode,
                                          void *pSystemData) {
    SThrownEvent event(eventCode, (void *)pSystemData);
    m_eventsQueue.push(event);
}

/**
 * 
 * @param eventCode
 * @param pCallback
 * @return 
 */
fg::event::CFunctionCallback* fg::event::CEventManager::addCallback(EventType eventCode,
                                                                    CFunctionCallback *pCallback) {
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
fg::event::CFunctionCallback* fg::event::CEventManager::addCallback(EventType eventCode,
                                                                    CFunctionCallback::fgFunction pFunction) {
    if(!pFunction || (int)eventCode < 0)
        return NULL;
    // !! !!
    // Need to check somehow for duplicates #FIXME
    CFunctionCallback *pCallback = new CFunctionCallback(pFunction);
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
fg::event::CFunctionCallback* fg::event::CEventManager::addCallback(EventType eventCode,
                                                                    CPlainFunctionCallback::fgPlainFunction pPlainFunction,
                                                                    void *pUserData) {
    if((int)eventCode < 0 || !pPlainFunction)
        return NULL;

    CFunctionCallback *pCallback = new CPlainFunctionCallback(pPlainFunction, pUserData);
    m_eventBinds[eventCode].push_back(pCallback);
    return pCallback;
}

/**
 * 
 * @param eventCode
 * @param pCallback
 * @return 
 */
fgBool fg::event::CEventManager::removeCallback(EventType eventCode, CFunctionCallback *pCallback) {
    if(!pCallback || (int)eventCode < 0)
        return FG_FALSE;

    CallbacksVec &callbacksVec = m_eventBinds[eventCode];
    if(callbacksVec.empty())
        return FG_FALSE;
    CallbacksVecItor cit = callbacksVec.begin(), end = callbacksVec.end();
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
fg::event::CFunctionCallback* fg::event::CEventManager::addTimeoutCallback(CFunctionCallback *pCallback,
                                                                           const int timeout,
                                                                           CArgumentList *pArgList) {
    if(!pCallback)
        return NULL;
    STimeoutCallback timeoutCallback(pCallback, timeout, pArgList);
    timeoutCallback.timeStamp = FG_GetTicks();
    m_timeoutCallbacks.push_back(timeoutCallback);
    return pCallback;
}

/**
 * 
 * @param pCallback
 * @return 
 */
fgBool fg::event::CEventManager::removeTimeoutCallback(CFunctionCallback *pCallback) {
    if(!pCallback)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    TimeoutCallbacksVecItor begin = m_timeoutCallbacks.begin();
    TimeoutCallbacksVecItor it = begin,
            end = m_timeoutCallbacks.end();
    for(; it != end; it++) {
        STimeoutCallback &timeout = (*it);
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
fg::event::CFunctionCallback* fg::event::CEventManager::addCyclicCallback(CFunctionCallback *pCallback,
                                                                          const int repeats,
                                                                          const int interval,
                                                                          CArgumentList *pArgList) {
    if(!pCallback)
        return NULL;
    SCyclicCallback cyclicCallback(pCallback, repeats, interval, pArgList);
    cyclicCallback.timeStamp = FG_GetTicks();
    m_cyclicCallbacks.push_back(cyclicCallback);
    return pCallback;
}

/**
 * 
 * @param pCallback
 * @return 
 */
fgBool fg::event::CEventManager::removeCyclicCallback(CFunctionCallback *pCallback) {
    if(!pCallback)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    CyclicCallbacksVecItor begin = m_cyclicCallbacks.begin();
    CyclicCallbacksVecItor it = begin,
            end = m_cyclicCallbacks.end();
    for(; it != end; it++) {
        SCyclicCallback &cyclic = (*it);
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

/* 
 * This function calls all callbacks from the triggered/thrown events
 * also executes callbacks from cyclical and timeouts
 */
void fg::event::CEventManager::executeEvents(void) {
    // Phase 1: execution of thrown events (now including the argument list).
    // Btw after calling the proper callback,
    // queue entry with argument list must be erased 
    while(!m_eventsQueue.empty()) {
        SThrownEvent &event = m_eventsQueue.front();
        int eventCode = event.eventCode;
        //FG_LOG_DEBUG("Event code thrown %d | list: %p", eventCode, event.argList);
        CallbackBindingMap::iterator found = m_eventBinds.find(eventCode);
        if(found == m_eventBinds.end()) {
            if(event.argList)
                delete event.argList;
            m_eventsQueue.pop();
            continue;
        }
        CallbacksVec &callbacks = (*found).second;
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

    // Phase 2: Timeouts
    unsigned long int TS = FG_HardwareState->getTS(); // #FIXME - hardware state TS

    // After timeout is executed it needs to be deleted from the timeouts pool - also the callback pointer must 
    // be freed with the argument list as they no longer needed
    for(TimeoutCallbacksVecItor it = m_timeoutCallbacks.begin(); it != m_timeoutCallbacks.end(); it++) {
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
    for(CyclicCallbacksVecItor it = m_cyclicCallbacks.begin(); it != m_cyclicCallbacks.end(); it++) {
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
