/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

// #include "s3eKeyboard.h" ??

#include "fgEventManager.h"
#include "../fgCommon.h"

#include "../Hardware/fgHardwareState.h"

template <>
bool fgSingleton<fgEventManager>::instanceFlag = false;

template <>
fgEventManager *fgSingleton<fgEventManager>::instance = NULL;

/*
 * Default constructor for Event Manager object
 */
fgEventManager::fgEventManager()
{
}

/*
 * Default destructor for Event Manager object
 */
fgEventManager::~fgEventManager()
{
	for(fgCallbackBinding::iterator it = m_keyDownBinds.begin(); it != m_keyDownBinds.end(); it++) {
		for(int i=0; i<(int)it->second.size(); i++) {
			delete it->second[i];
			it->second[i] = NULL;
		}
		it->second.clear();
	}
	m_keyDownBinds.clear();

	for(fgCallbackBinding::iterator it = m_keyUpBinds.begin(); it != m_keyUpBinds.end(); it++) {
		for(int i=0; i<(int)it->second.size(); i++) {
			delete it->second[i];
			it->second[i] = NULL;
		}
		it->second.clear();
	}
	m_keyUpBinds.clear();

	for(fgCallbackBinding::iterator it = m_eventBinds.begin(); it != m_eventBinds.end(); it++) {
		for(int i=0; i<(int)it->second.size(); i++) {
			delete it->second[i];
			it->second[i] = NULL;
		}
		it->second.clear();
	}
	m_eventBinds.clear();

	while (!m_eventsQueue.empty()) {
		if(m_eventsQueue.front().argList != NULL)
			delete m_eventsQueue.front().argList;
        m_eventsQueue.pop();
    }

	for(int i=0;i<(int)m_timeoutCallbacks.size();i++) {
		delete m_timeoutCallbacks[i].argList;
		m_timeoutCallbacks[i].argList = NULL;
		delete m_timeoutCallbacks[i].callback;
		m_timeoutCallbacks[i].callback = NULL;
	}
	m_timeoutCallbacks.clear();

	for(int i=0;i<(int)m_cyclicCallbacks.size();i++) {
		delete m_cyclicCallbacks[i].argList;
		m_cyclicCallbacks[i].argList = NULL;
		delete m_cyclicCallbacks[i].callback;
		m_cyclicCallbacks[i].callback = NULL;
	}
	m_cyclicCallbacks.clear();

	m_keysUpPool.clear();
	m_keysDownPool.clear();
}

/*
 *
 */
void fgEventManager::initialize(void)
{
	m_keyDownBinds.clear();
	m_keyUpBinds.clear();
	m_eventBinds.clear();
	m_timeoutCallbacks.clear();
	m_cyclicCallbacks.clear();

	m_keysUpPool.clear();
	m_keysDownPool.clear();
}

/*
 *
 */
void fgEventManager::throwEvent(fgEventType eventCode, fgArgumentList *list)
{
	fgThrownEvent event(eventCode, list);
	m_eventsQueue.push(event);
}

/*
 *
 */
void fgEventManager::addKeyDownCallback(int keyCode, fgCallbackFunction *callback)
{
	if(!callback || keyCode <= 0)
		return;
	m_keyDownBinds[keyCode].push_back(callback);
}

/*
 *
 */
void fgEventManager::addKeyUpCallback(int keyCode, fgCallbackFunction *callback)
{
	if(!callback || keyCode <= 0)
		return;
	m_keyUpBinds[keyCode].push_back(callback);
}

/*
 *
 */
void fgEventManager::addEventCallback(fgEventType eventCode, fgCallbackFunction *callback)
{
	if(!callback || (int)eventCode < 0)
		return;
	m_eventBinds[eventCode].push_back(callback);
}

/*
 *
 */
void fgEventManager::addTimeoutCallback(fgCallbackFunction *callback, int timeout, fgArgumentList *argList)
{
	if(!callback)
		return;
	fgTimeoutCallback timeoutCallback(callback, timeout, argList);
	timeoutCallback.timestamp = FG_GetTicks();
	m_timeoutCallbacks.push_back(timeoutCallback);
}

/*
 *
 */
void fgEventManager::addCyclicCallback(fgCallbackFunction *callback, int repeats, int interval, fgArgumentList *argList)
{
	if(!callback)
		return;
	fgCyclicCallback cyclicCallback(callback, repeats, interval, argList);
	cyclicCallback.timestamp = FG_GetTicks();
	m_cyclicCallbacks.push_back(cyclicCallback);
}

/*
 * This adds key code to the pool of pressed down keys
 */
void fgEventManager::addKeyDown(int keyCode)
{
	m_keysDownPool.push_back(keyCode);
}

/*
 * This adds key code to the pool of released (up) keys
 */
void fgEventManager::addKeyUp(int keyCode)
{
	m_keysUpPool.push_back(keyCode);
}

/* 
 * This function calls all callbacks from the triggered/thrown events
 * also executes callbacks from cyclics and timeouts
 */
void fgEventManager::executeEvents(void)
{
	// Phase 1: execute keyboard callbacks
	for(int i=0;i<(int)m_keysDownPool.size();i++) {
		int keyCode = m_keysDownPool[i];
		fgCallbackBinding::iterator found = m_keyDownBinds.find(keyCode);
		if(found == m_keyDownBinds.end())
			continue;
		for(int j=0;j<(int)m_keyDownBinds[keyCode].size();j++) {
			// There's no need for argument list
			m_keyDownBinds[keyCode][j]->Call();
		}
	}
	m_keysDownPool.clear();

	for(int i=0;i<(int)m_keysUpPool.size();i++) {
		int keyCode = m_keysUpPool[i];
		fgCallbackBinding::iterator found = m_keyUpBinds.find(keyCode);
		if(found == m_keyUpBinds.end())
			continue;
		for(int j=0;j<(int)m_keyUpBinds[keyCode].size();j++) {
			// There's no need for argument list
			m_keyUpBinds[keyCode][j]->Call();
		}
	}
	m_keysUpPool.clear();

	// Phase 2: execution of thrown events (now including the argument list). Btw after calling the proper callback,
	// queue entry with argument list must be erased 
	while(!m_eventsQueue.empty()) {
		fgThrownEvent event = m_eventsQueue.front();
		int eventCode = event.eventCode;

		printf("Event code thrown %d | list: %p\n", eventCode, event.argList);

		fgCallbackBinding::iterator found = m_eventBinds.find(eventCode);
		if(found == m_eventBinds.end()) {
			if(event.argList)
				delete event.argList;
			m_eventsQueue.pop();
			continue;
		}

		for(int j=0;j<(int)m_eventBinds[eventCode].size();j++) {
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
	for(fgTimeoutCallbacksPool::iterator it = m_timeoutCallbacks.begin(); it != m_timeoutCallbacks.end(); it++) {
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
	for(fgCyclicCallbacksPool::iterator it = m_cyclicCallbacks.begin(); it != m_cyclicCallbacks.end(); it++) {
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

