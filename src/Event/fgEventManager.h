/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_EVENT_MANAGER_H_
#define _FG_EVENT_MANAGER_H_

#include "../fgSingleton.h"
#include "../fgBuildConfig.h"
#include "../fgCommon.h"

#include "fgEventHelper.h"
#include "fgThrownEvent.h"
#include "fgTimeoutCallback.h"
#include "fgCyclicCallback.h"

#include "fgEventDefinitions.h"


#include "fgCallback.h"

// #FIXME #TODO #P3 key codes standard mapping / translation
// #TODO #P2 change std::vector to standard FG shadow type
// #TODO #P4 make event manager thread friendly / multithread support

/* EXAMPLE OF USE 
	KeyboardEvent *event = new KeyboardEvent(keyCode);
	event->m_pressed = true;
	ArgumentList *argv = new ArgumentList();
	argv->pushArgument(POINTER, (void *)keyboardEvent);
	throwEvent(KEYBOARD_DOWN, argv);
	ArgumentList *argv = new ArgumentList();
	argv->pushArgument(POINTER, (void *)getWidgetByName("buttonNewGame"));
	throwEvent(BUTTON_CLICKED, argv);
*/

/*
 * Event manager main class definition.
 * 
 */
class fgEventManager : public fgSingleton<fgEventManager>
{
	friend class fgSingleton<fgEventManager>;

private:
	// 
	fgArrayVector<int> m_keysDownPool;
	// 
	fgArrayVector<int> m_keysUpPool;

	// int - keyCode, value - vector of callbacks to call
	// Binding for key down events
	fgCallbackBinding m_keyDownBinds;
	// Binding for key up binds - note that this will only work if
	// previously key was released
	fgCallbackBinding m_keyUpBinds;
	// int - eventCode
	// Binding for all global events
	fgCallbackBinding m_eventBinds;
	// Events queue (message queue so to speak)
	fgEventsQueue m_eventsQueue;
	// Special pool with timeout callbacks (timers)
	fgTimeoutCallbacksPool m_timeoutCallbacks;
	// Pool with cyclic timeout callbacks (repeat timers, self reset)
	fgCyclicCallbacksPool m_cyclicCallbacks;

protected:
	// Default constructor for Event Manager object
	fgEventManager();
	// Default destructor for Event Manager object
	~fgEventManager();

public:
	// Initialize the Event Manager object
	void initialize(void);

	// This adds event to the waiting queue, the *list object needs to be allocated before,
	// after event callback execution argument list must be freed
	void throwEvent(fgEventType eventCode, fgArgumentList *list);
	//
	void addKeyDownCallback(int keyCode, fgCallbackFunction *callback);
	//
	void addKeyUpCallback(int keyCode, fgCallbackFunction *callback);
	//
	void addEventCallback(fgEventType eventCode, fgCallbackFunction *callback);

	//
	void addTimeoutCallback(fgCallbackFunction *callback, int timeout, fgArgumentList *argList);
	// 
	void addCyclicCallback(fgCallbackFunction *callback, int repeats, int interval, fgArgumentList *argList);

	// This adds key code to the pool of pressed down keys
	void addKeyDown(int keyCode);
	// This adds key code to the pool of released (up) keys
	void addKeyUp(int keyCode);

	// Execute (finalized) all events waiting in a queue
	// This function must be called in every frame in one of the threads (or just the main thread)
	void executeEvents(void);
};

// Get singleton instance of the Event Manager class object
#define FG_EventManager fgEventManager::getInstance()

#endif /* _FG_EVENT_MANAGER_H_ */
