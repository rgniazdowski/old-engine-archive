/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

#include <vector>

#include "fgEventHelper.h"
#include "fgThrownEvent.h"
#include "fgTimeoutCallback.h"
#include "fgCyclicCallback.h"

#include "fgEventDefinitions.h"

#include "../fgSingleton.h"
#include "fgCallback.h"

class fgEventManager : public fgSingleton<fgEventManager>
{
	friend class fgSingleton<fgEventManager>;

private:
	std::vector<int> m_keysDownPool;
	std::vector<int> m_keysUpPool;

	// int - keyCode, value - vector of callbacks to call
	fgCallbackBinding m_keyDownBinds;
	fgCallbackBinding m_keyUpBinds;
	// int - eventCode
	fgCallbackBinding m_eventBinds;
	fgEventsQueue m_eventsQueue;
	fgTimeoutCallbacksPool m_timeoutCallbacks;
	fgCyclicCallbacksPool m_cyclicCallbacks;

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

protected:
	fgEventManager();
	~fgEventManager();

public:
	void initialize(void);

	// This adds event to the waiting queue, the *list object needs to be allocated before,
	// after event callback execution argument list must be freed
	void throwEvent(int eventCode, fgArgumentList *list);

	void addKeyDownCallback(int keyCode, fgCallbackFunction *callback);

	void addKeyUpCallback(int keyCode, fgCallbackFunction *callback);

	void addEventCallback(int eventCode, fgCallbackFunction *callback);

	void addTimeoutCallback(fgCallbackFunction *callback, int timeout, fgArgumentList *argList);

	void addCyclicCallback(fgCallbackFunction *callback, int repeats, int interval, fgArgumentList *argList);

	void addKeyDown(int keyCode);

	void addKeyUp(int keyCode);

	// this function must be called in every frame in one of the threads (or just the main thread)
	void executeEvents(void);
};

#define FG_EventManager fgEventManager::getInstance()

#endif /* _EVENT_MANAGER_H */
