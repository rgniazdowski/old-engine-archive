/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgEventManager.h"
#include "fgCommon.h"
#include "fgLog.h"
#include "Util/fgTime.h"

#include "Hardware/fgHardwareState.h"
#include "Util/fgMemory.h"

using namespace fg;

//------------------------------------------------------------------------------

event::CEventManager::CEventManager(unsigned int eventStructSize) :
m_eventStructSize(eventStructSize),
m_eventBinds(),
m_eventsQueue(),
m_timeoutCallbacks(),
m_cyclicCallbacks(),
m_eventStructs(),
m_eventStructsFreeSlots(),
m_argLists(),
m_argListsFreeSlots() {
    m_managerType = FG_MANAGER_EVENT;
}
//------------------------------------------------------------------------------

event::CEventManager::~CEventManager() {
    event::CEventManager::destroy();
}
//------------------------------------------------------------------------------

void event::CEventManager::pushToFreeSlot(SEventBase* ptr) {
    if(!ptr)
        return;
    m_eventStructsFreeSlots.push_back((void*)ptr);
}
//------------------------------------------------------------------------------

void event::CEventManager::pushToFreeSlot(CArgumentList* ptr) {
    if(!ptr)
        return;
    int count = ptr->getCount();
    for(int i = 0; i < count; i++) {
        SArgument& arg = ptr->getStructByID(i);
        if(arg.type == SArgument::Type::ARG_TMP_POINTER) {
            pushToFreeSlot((SEventBase *)arg.custom_pointer);
            arg.custom_pointer = NULL;
            arg.reset();
        }
    }
    ptr->clear();
    m_argListsFreeSlots.push_back((void *)ptr);
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::destroy(void) {
    for(CallbackBindingMap::iterator it = m_eventBinds.begin(); it != m_eventBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            if(it->second[i])
                delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    while(!m_eventsQueue.empty()) {
        if(m_eventsQueue.front().argList != NULL) {
            //delete m_eventsQueue.front().argList;
            pushToFreeSlot(m_eventsQueue.front().argList);
            m_eventsQueue.front().argList = NULL;
        }
        m_eventsQueue.pop();
    }

    for(int i = 0; i < (int)m_timeoutCallbacks.size(); i++) {
        if(m_timeoutCallbacks[i].argList) {
            pushToFreeSlot(m_timeoutCallbacks[i].argList);
            //delete m_timeoutCallbacks[i].argList;
        }
        if(m_timeoutCallbacks[i].callback) {
            delete m_timeoutCallbacks[i].callback;
        }
        m_timeoutCallbacks[i].argList = NULL;
        m_timeoutCallbacks[i].callback = NULL;
    }

    for(int i = 0; i < (int)m_cyclicCallbacks.size(); i++) {
        if(m_cyclicCallbacks[i].argList) {
            pushToFreeSlot(m_cyclicCallbacks[i].argList);
            //delete m_cyclicCallbacks[i].argList;
        }
        if(m_cyclicCallbacks[i].callback) {
            delete m_cyclicCallbacks[i].callback;
        }
        m_cyclicCallbacks[i].argList = NULL;
        m_cyclicCallbacks[i].callback = NULL;
    }

    int n = m_eventStructs.size();
    while(m_eventStructsFreeSlots.size()) {
        void* ptr = m_eventStructsFreeSlots.back();
        int index = m_eventStructs.find(ptr);
        if(index != -1) {
            m_eventStructs[index] = m_eventStructs[n - 1];
            m_eventStructs[n - 1] = NULL;
            m_eventStructs.resize(n - 1);
            n--;
        }
        fgFree(ptr);
        m_eventStructsFreeSlots.pop_back();
    }
    while(m_eventStructs.size()) {
        void* ptr = m_eventStructs.back();
        if(ptr) {
            fgFree(ptr);
        }
        m_eventStructs.pop_back();
    }

    n = m_argLists.size();
    while(m_argListsFreeSlots.size()) {
        void* ptr = m_argListsFreeSlots.back();
        int index = m_argLists.find(ptr);
        if(index != -1) {
            m_argLists[index] = m_argLists[n - 1];
            m_argLists[n - 1] = NULL;
            m_argLists.resize(n - 1);
            n--;
        }
        //fgFree(ptr);
        CArgumentList *argList = (CArgumentList*)ptr;
        delete argList;
        m_argListsFreeSlots.pop_back();
    }
    while(m_argLists.size()) {
        CArgumentList* ptr = (CArgumentList*)m_argLists.back();
        //fgFree(ptr);
        if(ptr) {
            delete ptr;
        }
        m_argLists.pop_back();
    }

    event::CEventManager::clear();
    m_init = FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void event::CEventManager::clear(void) {
    m_eventBinds.clear();
    m_timeoutCallbacks.clear();
    m_cyclicCallbacks.clear();
    m_managerType = FG_MANAGER_EVENT;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::initialize(void) {
    m_eventStructs.reserve(INITIAL_PTR_VEC_SIZE);
    m_argLists.reserve(INITIAL_PTR_VEC_SIZE);
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

event::SEventBase* event::CEventManager::requestEventStruct(void) {
    SEventBase* ptr = NULL;
    if(m_eventStructsFreeSlots.empty()) {
        ptr = (SEventBase *)fgMalloc<void>(m_eventStructSize, FG_TRUE);
        m_eventStructs.push_back((void *)ptr);
        ptr->timeStamp = timesys::ticks();
    } else {
        ptr = (SEventBase *)m_eventStructsFreeSlots.back();
        memset(ptr, 0, m_eventStructSize);
        ptr->timeStamp = timesys::ticks();
        m_eventStructsFreeSlots.pop_back();
    }
    return ptr;
}
//------------------------------------------------------------------------------

event::SEventBase* event::CEventManager::requestEventStruct(const unsigned int eventStructSize) {
    if(!eventStructSize) {
        return requestEventStruct();
    }
    SEventBase* ptr = NULL;
    if(m_eventStructsFreeSlots.empty()) {
        ptr = (SEventBase *)fgMalloc<void>(eventStructSize, FG_TRUE);
        m_eventStructs.push_back((void *)ptr);
        ptr->timeStamp = timesys::ticks();
    } else {
        ptr = (SEventBase *)m_eventStructsFreeSlots.back();
        ptr = (SEventBase *)fgRealloc<void>(ptr, eventStructSize, FG_TRUE);
        ptr->timeStamp = timesys::ticks();
        m_eventStructsFreeSlots.pop_back();
    }
    return ptr;
}
//------------------------------------------------------------------------------

event::CArgumentList* event::CEventManager::requestArgumentList(void) {
    CArgumentList* ptr = NULL;
    if(m_argListsFreeSlots.empty()) {
        ptr = new CArgumentList();
        m_argLists.push_back((void *)ptr);
    } else {
        ptr = (CArgumentList *)m_argListsFreeSlots.back();
        ptr->clear();
        m_argListsFreeSlots.pop_back();
    }
    return ptr;
}
//------------------------------------------------------------------------------

void event::CEventManager::throwEvent(EventType eventCode) {
    SThrownEvent event(eventCode);
    m_eventsQueue.push(event);
}
//------------------------------------------------------------------------------

void event::CEventManager::throwEvent(EventType eventCode, CArgumentList *list) {
    SThrownEvent event(eventCode, list);
    // Should check in here whether or not the argument list in
    // allocated arg list pointers - if not -> add it
    // The same should happen with one of the arguments - if it is event struct...
    // Maybe need some additional functions/options for argument list
    // arg type - tmp pointer - will be reused inside of event manager
    m_eventsQueue.push(event);
}
//------------------------------------------------------------------------------

void event::CEventManager::throwEvent(EventType eventCode,
                                      void* pSystemData) {
    SThrownEvent event(eventCode, (void *)pSystemData);
    m_eventsQueue.push(event);
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::isRegistered(EventType eventCode,
                                          CFunctionCallback* pCallback) {
    if(eventCode == event::INVALID || !pCallback) {
        return FG_FALSE;
    }

    int idx = m_eventBinds[eventCode].find(pCallback);
    if(idx < 0)
        return FG_FALSE;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::isRegistered(EventType eventCode,
                                          const CFunctionCallback::Function pFunction) {
    fgBool status = FG_FALSE;
    if(eventCode == event::INVALID || !pFunction) {
        return status;
    }
    const unsigned int n = m_eventBinds[eventCode].size();
    if(!n) {
        return status;
    }
    CallbacksVec const& callbacks = m_eventBinds[eventCode];
    for(unsigned int i = 0; i < n; i++) {
        if(callbacks[i]->getFunction() == pFunction) {
            status = FG_TRUE;
            break;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::isRegistered(EventType eventCode,
                                          const CPlainFunctionCallback::PlainFunction pPlainFunction) {
    fgBool status = FG_FALSE;
    if(eventCode == event::INVALID || !pPlainFunction) {
        return status;
    }
    const unsigned int n = m_eventBinds[eventCode].size();
    if(!n) {
        return status;
    }
    CallbacksVec const& callbacks = m_eventBinds[eventCode];
    for(unsigned int i = 0; i < n; i++) {
        const CFunctionCallback* pCallback = callbacks[i];
        if(!pCallback)
            continue;
        if(pCallback->getCallbackType() == event::PLAIN_FUNCTION_CALLBACK) {
            const CPlainFunctionCallback* pPlainCB = dynamic_cast<const CPlainFunctionCallback*>(pCallback);
            if(pPlainCB->getPlainFunction() == pPlainFunction) {
                status = FG_TRUE;
                break;
            }
        }
    }
    return status;
}
//------------------------------------------------------------------------------

event::EventType event::CEventManager::isRegistered(CFunctionCallback* pCallback) {
    if(!pCallback)
        return event::INVALID;
    EventType foundEvent = event::INVALID;
    CallbackBindingMapItor it = m_eventBinds.begin();
    CallbackBindingMapItor end = m_eventBinds.end();

    for(; it != end; it++) {
        const EventType eventCode = it->first;
        if(isRegistered(eventCode, pCallback)) {
            foundEvent = eventCode;
            break;
        }
    }

    return foundEvent;
}
//------------------------------------------------------------------------------

event::EventType event::CEventManager::isRegistered(const CFunctionCallback::Function pFunction) {
    if(!pFunction)
        return event::INVALID;
    EventType foundEvent = event::INVALID;
    CallbackBindingMapItor it = m_eventBinds.begin();
    CallbackBindingMapItor end = m_eventBinds.end();

    for(; it != end; it++) {
        const EventType eventCode = it->first;
        if(isRegistered(eventCode, pFunction)) {
            foundEvent = eventCode;
            break;
        }
    }

    return foundEvent;
}
//------------------------------------------------------------------------------

event::EventType event::CEventManager::isRegistered(const CPlainFunctionCallback::PlainFunction pPlainFunction) {
    if(!pPlainFunction)
        return event::INVALID;
    EventType foundEvent = event::INVALID;
    CallbackBindingMapItor it = m_eventBinds.begin();
    CallbackBindingMapItor end = m_eventBinds.end();

    for(; it != end; it++) {
        const EventType eventCode = it->first;
        if(isRegistered(eventCode, pPlainFunction)) {
            foundEvent = eventCode;
            break;
        }
    }
    return foundEvent;
}
//------------------------------------------------------------------------------

unsigned int event::CEventManager::executeEvent(EventType eventCode) {
    unsigned int count = 0;
    CallbackBindingMap::iterator found = m_eventBinds.find(eventCode);
    if(found != m_eventBinds.end()) {
        CallbacksVec &callbacks = (*found).second;
        for(int j = 0; j < (int)callbacks.size(); j++) {
            if(callbacks[j]) {
                callbacks[j]->Call();
                count++;
            }
        }
    }
    return count;
}
//------------------------------------------------------------------------------

unsigned int event::CEventManager::executeEvent(const SThrownEvent& thrownEvent) {
    unsigned int count = 0;
    CallbackBindingMap::iterator found = m_eventBinds.find(thrownEvent.eventCode);
    if(found != m_eventBinds.end()) {
        CallbacksVec &callbacks = (*found).second;
        for(int j = 0; j < (int)callbacks.size(); j++) {
            if(callbacks[j]) {
                if(thrownEvent.argList) {
                    callbacks[j]->Call(thrownEvent.argList);
                } else if(thrownEvent.systemData) {
                    callbacks[j]->Call((void*)thrownEvent.systemData);
                } else {
                    callbacks[j]->Call();
                }
                count++;
            }
        }
    }
    if(thrownEvent.argList) {
        pushToFreeSlot(thrownEvent.argList);
    }
    return count;
}
//------------------------------------------------------------------------------

unsigned int event::CEventManager::executeEvent(EventType eventCode,
                                                CArgumentList* list) {
    unsigned int count = 0;
    CallbackBindingMap::iterator found = m_eventBinds.find(eventCode);
    if(found != m_eventBinds.end()) {
        CallbacksVec &callbacks = (*found).second;
        for(int j = 0; j < (int)callbacks.size(); j++) {
            if(callbacks[j]) {
                if(list) {
                    callbacks[j]->Call(list);
                } else {
                    callbacks[j]->Call();
                }
                count++;
            }
        }
    }
    if(list) {
        pushToFreeSlot(list);
    }
    return count;
}
//------------------------------------------------------------------------------

unsigned int event::CEventManager::executeEvent(EventType eventCode,
                                                void* pSystemData) {
    unsigned int count = 0;
    CallbackBindingMap::iterator found = m_eventBinds.find(eventCode);
    if(found != m_eventBinds.end()) {
        CallbacksVec &callbacks = (*found).second;
        for(int j = 0; j < (int)callbacks.size(); j++) {
            if(callbacks[j]) {
                if(pSystemData) {
                    callbacks[j]->Call((void*)pSystemData);
                } else {
                    callbacks[j]->Call();
                }
                count++;
            }
        }
    }
    return count;
}
//------------------------------------------------------------------------------

event::CFunctionCallback* event::CEventManager::addCallback(EventType eventCode,
                                                            CFunctionCallback* pCallback) {
    if(!pCallback || (int)eventCode < 0)
        return NULL;
    // Duplicate callbacks are not allowed for the same event
    if(isRegistered(eventCode, pCallback)) {
        return NULL;
    }
    m_eventBinds[eventCode].push_back(pCallback);
    return pCallback;
}
//------------------------------------------------------------------------------

event::CFunctionCallback* event::CEventManager::addCallback(EventType eventCode,
                                                            CFunctionCallback::Function pFunction) {
    if(!pFunction || (int)eventCode < 0)
        return NULL;
    if(isRegistered(eventCode, pFunction)) {
        return NULL;
    }
    CFunctionCallback* pCallback = new CFunctionCallback(pFunction);
    m_eventBinds[eventCode].push_back(pCallback);
    return pCallback;
}
//------------------------------------------------------------------------------

event::CFunctionCallback* event::CEventManager::addCallback(EventType eventCode,
                                                            CPlainFunctionCallback::PlainFunction pPlainFunction,
                                                            void* pUserData) {
    if((int)eventCode < 0 || !pPlainFunction)
        return NULL;
    if(isRegistered(eventCode, pPlainFunction)) {
        return NULL;
    }
    CFunctionCallback* pCallback = new CPlainFunctionCallback(pPlainFunction, pUserData);
    m_eventBinds[eventCode].push_back(pCallback);
    return pCallback;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::removeCallback(EventType eventCode, CFunctionCallback* pCallback) {
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
//------------------------------------------------------------------------------

fgBool event::CEventManager::removeCallbacks(EventType eventCode) {
    if((int)eventCode < 0)
        return FG_FALSE;

    CallbacksVec &callbacksVec = m_eventBinds[eventCode];
    if(callbacksVec.empty())
        return FG_FALSE;
    CallbacksVecItor cit = callbacksVec.begin(), end = callbacksVec.end();
    for(; cit != end; cit++) {
        *cit = NULL;
    }
    callbacksVec.clear_optimised();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::deleteCallback(EventType eventCode, CFunctionCallback*& pCallback) {
    if(!pCallback || (int)eventCode < 0)
        return FG_FALSE;

    CallbacksVec &callbacksVec = m_eventBinds[eventCode];
    if(callbacksVec.empty())
        return FG_FALSE;
    CallbacksVecItor cit = callbacksVec.begin(), end = callbacksVec.end();
    for(; cit != end; cit++) {
        if(*cit == pCallback) {
            m_eventBinds[eventCode].erase(cit);
            delete pCallback;
            pCallback = NULL;
            return FG_TRUE;
            break;
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::deleteCallbacks(EventType eventCode) {
    if((int)eventCode < 0)
        return FG_FALSE;

    CallbacksVec &callbacksVec = m_eventBinds[eventCode];
    if(callbacksVec.empty())
        return FG_FALSE;
    CallbacksVecItor cit = callbacksVec.begin(), end = callbacksVec.end();
    for(; cit != end; cit++) {
        CFunctionCallback* pCallback = *cit;
        delete pCallback;
        *cit = NULL;
        pCallback = NULL;
    }
    callbacksVec.clear_optimised();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

event::CFunctionCallback* event::CEventManager::addTimeoutCallback(CFunctionCallback* pCallback,
                                                                   const int timeout,
                                                                   CArgumentList* pArgList) {
    if(!pCallback)
        return NULL;
    STimeoutCallback timeoutCallback(pCallback, timeout, pArgList);
    timeoutCallback.timeStamp = timesys::ticks();
    m_timeoutCallbacks.push_back(timeoutCallback);
    return pCallback;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::removeTimeoutCallback(CFunctionCallback* pCallback) {
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
//------------------------------------------------------------------------------

event::CFunctionCallback* event::CEventManager::addCyclicCallback(CFunctionCallback* pCallback,
                                                                  const int repeats,
                                                                  const int interval,
                                                                  CArgumentList* pArgList) {
    if(!pCallback)
        return NULL;
    SCyclicCallback cyclicCallback(pCallback, repeats, interval, pArgList);
    cyclicCallback.timeStamp = timesys::ticks();
    m_cyclicCallbacks.push_back(cyclicCallback);
    return pCallback;
}
//------------------------------------------------------------------------------

fgBool event::CEventManager::removeCyclicCallback(CFunctionCallback* pCallback) {
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
//------------------------------------------------------------------------------

void event::CEventManager::executeEvents(void) {

    ////////////////////////////////////////////////////////////////////////////
    // Phase 1: Timeouts
    unsigned long int TS = timesys::ticks();

    // After timeout is executed it needs to be deleted from the timeouts pool - also the callback pointer must 
    // be freed with the argument list as they no longer needed
    for(TimeoutCallbacksVecItor it = m_timeoutCallbacks.begin(); it != m_timeoutCallbacks.end(); it++) {
        if(TS - it->timeStamp >= (unsigned long int)it->timeout) {
            if(it->callback) {
                it->callback->Call(it->argList);
                delete it->callback;
                it->callback = NULL;
            }
            if(it->argList) {
                //delete it->argList;
                pushToFreeSlot(it->argList);
                it->argList = NULL;
            }
            if(it->callback == NULL) {
                m_timeoutCallbacks.erase(it);
                it--;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Phase 2: Cyclic callbacks
    unsigned int numCyclic = m_cyclicCallbacks.size();

    //for(CyclicCallbacksVecItor it = m_cyclicCallbacks.begin(); it != m_cyclicCallbacks.end(); it++) {
    for(unsigned i = 0; i < numCyclic; i++) {

        if(TS - m_cyclicCallbacks[i].timeStamp >= (unsigned long int)m_cyclicCallbacks[i].interval) {
            if(m_cyclicCallbacks[i].callback && (m_cyclicCallbacks[i].repeats || m_cyclicCallbacks[i].repeats == -1)) {
                m_cyclicCallbacks[i].callback->Call(m_cyclicCallbacks[i].argList);
                m_cyclicCallbacks[i].timeStamp = TS;
                if(m_cyclicCallbacks[i].repeats != 0)
                    m_cyclicCallbacks[i].repeats--;
            }

            if(m_cyclicCallbacks[i].callback == NULL)
                m_cyclicCallbacks[i].repeats = 0;

            if(m_cyclicCallbacks[i].repeats == 0) {
                if(m_cyclicCallbacks[i].callback) {
                    delete m_cyclicCallbacks[i].callback;
                    m_cyclicCallbacks[i].callback = NULL;
                }
                if(m_cyclicCallbacks[i].argList) {
                    //delete m_cyclicCallbacks[i].argList;
                    pushToFreeSlot(m_cyclicCallbacks[i].argList);
                    m_cyclicCallbacks[i].argList = NULL;
                }

                //m_cyclicCallbacks.erase(it);
                unsigned int n = m_cyclicCallbacks.size();
                m_cyclicCallbacks[i] = m_cyclicCallbacks[n - 1];
                memset(&m_cyclicCallbacks[n - 1], 0, sizeof (SCyclicCallback));
                m_cyclicCallbacks.resize(n - 1);
                numCyclic = n - 1;
                i--;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Phase 3: execution of thrown events (now including the argument list).
    // Btw after calling the proper callback,
    // queue entry with argument list must be erased 
    while(!m_eventsQueue.empty()) {
        SThrownEvent &event = m_eventsQueue.front();
        executeEvent(event);
        m_eventsQueue.pop();
    }
}
//------------------------------------------------------------------------------
