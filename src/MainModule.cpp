/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <map>

#include "fgBuildConfig.h"

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
#include "IwUtil.h"
#include "s3eDevice.h"
#endif

#include "fgSingleton.h"
#include "fgCommon.h"
#include "Event/fgEventManager.h"
#include "Input/fgTouchReceiver.h"

#include "fgGameMain.h"

class MainModule;

// FIXME - remove usage of singletons (at least to some acceptable level)
// Currently every major class / subsystem is a singleton - there is no 
// consistent structure / hierarchy - which is kinda retarded if U ask me.
template <>
bool fgSingleton<MainModule>::instanceFlag = false;

template <>
MainModule *fgSingleton<MainModule>::instance = NULL;

/**
 *
 */
class MainModule : public fgSingleton<MainModule>
{
	friend class fgSingleton<MainModule>;
protected:
	/**
	 * Initialize rendering parameters.
	 */
	MainModule() : m_useMultitouch(false), m_appInit(false), m_slow(false), m_isExit(false) {
		memset(&m_touches, 0, sizeof(m_touches));
	}

public:
	bool isSlow(void) const {
		return m_slow;
	}

	void setSlow(bool slow) {
		m_slow = slow;
	}

	void setExit(bool exit) {
		m_isExit = exit;
	}

	bool isExit(void) const {
		return m_isExit;
	}

	/**
	 * Focus lost HANDLER
	 */
	static int32 pauseHandler(void *systemData, void *userData) {
		MainModule::getInstance()->focusLostEvent();
		return 0;
	}

	/**
	 * Focus restored HANDLER
	 */
	static int32 unpauseHandler(void *systemData, void *userData) {
		MainModule::getInstance()->focusGainedEvent();
		return 0;
	}

	/**
	* Key state changed HANDLER
	*/
	static int32 keyStateChangedHandler(void *systemData, void *userData)
	{
		s3eKeyboardEvent* event = (s3eKeyboardEvent*)systemData;
		MainModule::getInstance()->keyStateChangedEvent(event);
		return 0;
	}

	/**
	 * Touch press/release HANDLER
	 */
	static int32 multiTouchButtonHandler(void* systemData, void* userData)
	{
		s3ePointerTouchEvent* event = (s3ePointerTouchEvent*) systemData;
		if(event->m_Pressed) {
			MainModule::getInstance()->multiTouchPressEvent(event->m_x, event->m_y, event->m_TouchID);
		} else {
			MainModule::getInstance()->multiTouchReleaseEvent(event->m_x, event->m_y, event->m_TouchID);
		}
		return 0;
	}

	/**
	 * Touch motion HANDLER
	 */
	static int32 multiTouchMotionHandler(void* systemData, void* userData)
	{
		s3ePointerTouchMotionEvent* event = (s3ePointerTouchMotionEvent*) systemData;
		MainModule::getInstance()->multiTouchMoveEvent(event->m_x, event->m_y, event->m_TouchID);
		return 0;
	}

	/**
	 * Single press/release HANDLER
	 */
	static int32 singleTouchButtonHandler(void* systemData, void* userData)
	{
		s3ePointerEvent* event = (s3ePointerEvent*) systemData;
		if(event->m_Pressed) {
			MainModule::getInstance()->multiTouchPressEvent(event->m_x, event->m_y, 0);
		} else {
			MainModule::getInstance()->multiTouchReleaseEvent(event->m_x, event->m_y, 0);
		}
		return 0;
	}

	/**
	 * Single motion HANDLER
	 */
	static int32 singleTouchMotionHandler(void* systemData, void* userData)
	{
		s3ePointerMotionEvent* event = (s3ePointerMotionEvent*) systemData;
		MainModule::getInstance()->multiTouchMoveEvent(event->m_x, event->m_y, 0);
		return 0;
	}

	/**
	 * Called when a fullscreen window with an OpenGL context
	 * has been created and is ready to be used.
	 */
	bool initProgram()
	{
		s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, S3E_SURFACE_LANDSCAPE_FIXED);

		// Register for keyboard
		s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, &MainModule::keyStateChangedHandler, NULL);

		// Register for touches
		m_useMultitouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
		if(m_useMultitouch) {
			s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, &MainModule::multiTouchButtonHandler, NULL);
			s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &MainModule::multiTouchMotionHandler, NULL);
		} else {
			s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, &MainModule::singleTouchButtonHandler, NULL);
			s3ePointerRegister(S3E_POINTER_MOTION_EVENT, &MainModule::singleTouchMotionHandler, NULL);
		}

		// DEVICE FOCUS – called on any device
		s3eDeviceRegister (S3E_DEVICE_PAUSE, &MainModule::pauseHandler, NULL);
		s3eDeviceRegister (S3E_DEVICE_UNPAUSE, &MainModule::unpauseHandler, NULL);

		// FIXME
		// Well the whole configuration process should update the screen (swap buffers)
		// this is needed to display splash screen (after marmalade splash screen) and
		// show the game initialization process by displaying the progress bar

		if(!FG_GameMain->initSubsystems()) {
			return false;
		}
		
		if(!FG_GameMain->loadConfiguration()) {
			return false;
		}

		if(!FG_GameMain->loadResources()) {
			return false;
		}

		m_appInit = true;
		return true;
	}

	/**
	 * Apps main loop step (one thread)
	 */
	bool mainLoopStep() {
		if (s3eDeviceCheckQuitRequest()) {
			m_appInit = false;
			return false;
		}
		if (s3eKeyboardGetState(s3eKeyEnter) & S3E_KEY_STATE_PRESSED)	{
			m_appInit = false;
			FG_WriteLog("ENTER PRESSED...");
			return false;
		}
		if (m_isExit) {
			m_appInit = false;
			FG_WriteLog("EXIT IS ACTIVATED - break loop main ! bye!");
			return false;
		}

		s3eDeviceYield(0);
		FG_GameMain->update();
		s3eDeviceYield(0);

		// well for now drawing and all update functions will be called in one place (one thread)
		// however it neads changing
		FG_GameMain->display();
		s3eDeviceYield(0);

		FG_GameMain->render();	
		s3eDeviceYield(0);

		return true;
	}

	/**
	 * The way to exit from the app
	 */
	void closeProgram() {
		FG_WriteLog("closeEvent()");
		FG_GameMain->releaseResources();

		// This frees all the data used by singletons and other nonresource data
		// after that only things left to free are FG_GameMain and MainModule
		FG_GameMain->closeSybsystems();

		FG_GameMain->deleteInstance();

		m_appInit = false;
	}

private:

	/**
	 * DEVICE PAUSE event
	 * (not the GL pause event)
	 */
	void focusLostEvent()
	{
		FG_WriteLog("focusLostEvent()");

		// Brak focus czyli:
		// - wyswietlenie menu
		// - dolne menu ipada wysuniete
		// - minimalizacja
		// - przelaczenie sie do innej aplikacji
		// - nalezy wlaczyc pauze
		// - zapisanie stanu gry

		// it needs to be handled properly - for current moment if application losts focus while loading game data etc (initialization)
		// - it will crash
		// TODO pausing/unpausing events need to handle initialization moments properly - also be aware of the operations in other threads (?)
		// TODO data loading procedures need to be sequential and easy to abort/revert/quit/resume
	}

	/**
	 * DEVICE unpause event
	 * (not the GL unpause event)
	 */
	void focusGainedEvent()
	{
		FG_WriteLog("focusGainedEvent()");
	}

	/**
	 * Handle PRESSING and RELEASING keys
	 */
	void keyStateChangedEvent(s3eKeyboardEvent* event) {
		if( !m_appInit )
			return;
		if (event->m_Pressed) {
			FG_EventManager->addKeyDown((int)event->m_Key);
		} else {
			FG_EventManager->addKeyUp((int)event->m_Key);
		}
		FG_WriteLog("FG_EventManager - keyboard - %d is pressed? - code: %d\n", (int)event->m_Pressed, (int)event->m_Key);
	}

	/**
	 * This function is called with a coordinate when the screen is touched.
	 * The touch id will remain the same as long as this touch is active.
	 */
	void multiTouchPressEvent(int x, int y, unsigned int touchId)
	{
		if( !m_appInit )
			return;

		m_touches[touchId] = true;
		FG_TouchReceiver->handlePointerPressed(fgVector2i(x,y), touchId);
	}

	/**
	 *  This method is called with a coordinate when an active touch moves.
	 */
	void multiTouchMoveEvent(int x, int y, unsigned int touchId)
	{
		if( !m_appInit )
			return;

		if(m_touches[touchId] == true)
			FG_TouchReceiver->handlePointerMoved(fgVector2i(x,y), touchId);
	}

	/**
	 *  This method is called with a coordinate when the screen isn't touched
	 *  anymore. This touch id will be deleted and will be reused when a new
	 *  touch is initiated.
	 */
	void multiTouchReleaseEvent(int x, int y, int touchId)
	{
		if( !m_appInit )
			return;

		m_touches[touchId] = false;
		FG_TouchReceiver->handlePointerReleased(fgVector2i(x,y),touchId);
	}	

private:
	enum {NUM_TOUCHES = 10};

	/// Touches (using multitouch)
	bool m_touches[NUM_TOUCHES];

	/// Result of multitouch availability test
	bool m_useMultitouch;

	/// Is app fully initialized?
	bool m_appInit;

	/// Is the device slow?
	bool m_slow;

	/// Is exit activated?
	bool m_isExit;
};

#define FG_MainModule MainModule::getInstance()

#if 0

/// Sets FPS-limit HANDLER
static bool set_allow_loop_handler(void);

/// TRUE triggers MainModule::loop() call in the while (1)
bool g_allowLoop = true;

/**
* Sets g_allowLoop to true - next main's while(1)
* execution will call MainModule::loop() !
*/
static int32 allow_moblet_loop(void* systemData, void* userData) {
	g_allowLoop = true;
	// Renew the timer
	bool result = set_allow_loop_handler();
	s3eDeviceUnYield();

	return result;
}

/**
* Sets timeout - to delay MainModule::loop()
* execution - to obtain expected FPS!
*/
static bool set_allow_loop_handler(void) {
	float fps = 30.0;
	float milisec = (1.0f/fps) * 1000.0f;
	int result = s3eTimerSetTimer( milisec, &allow_moblet_loop, NULL );
	if ( result == S3E_RESULT_ERROR ) {
		FG_ErrorLog("Setting Moblet::loop callback failed!");
		return false;
	}
	return true;
}

#endif

/**
* Main function that is called when the program starts.
*/
extern "C" int main()
{
	IwUtilInit();

	/*fgDeviceQuery* dev = fgDeviceQuery::getInstance();

	if ( dev->iOS() &&
		( (dev->deviceClass() == FG_DEVICE_CLASS_IPAD && dev->deviceGeneration() == FG_DEVICE_GENERATION_FIRST) ||
		(dev->deviceClass() == FG_DEVICE_CLASS_IPOD && dev->deviceGeneration() < FG_DEVICE_GENERATION_FOURTH) ||
		(dev->deviceClass() == FG_DEVICE_CLASS_IPHONE && dev->deviceGeneration() < FG_DEVICE_GENERATION_FOURTH)
		)
		)
	{
		FG_MainModule->setSlow(true);
	} else {
		FG_MainModule->setSlow(false);
	}
	*/
	s3eDeviceYield(0);
	FG_MainModule->initProgram();
	s3eDeviceYield(0);

	/*if( FG_MainModule->isSlow() ) {
		// USE FPS LIMIT
		FG_WriteLog("USING FPS LIMIT FOR DEVICE GEN: %d", dev->deviceGeneration());

		if(!set_allow_loop_handler()) {
			FG_ErrorLog("FATAL ERROR #1: EXITING");
			s3eDeviceExit(1);
		}
		while(1) {
			if ( g_allowLoop ) {
				g_allowLoop = false;
				FG_MainModule->mainLoopStep();
			}
			s3eDeviceYield(10);
		}
	} else {
		// NO FPS LIMIT
		FG_WriteLog("NO FPS LIMIT FOR DEVICE GEN: %d", dev->deviceGeneration());
		while(1) {
			FG_MainModule->mainLoopStep();
			s3eDeviceYield(0);
		}
	}*/

	while(true)	{
		int status = FG_MainModule->mainLoopStep();
		s3eDeviceYield(1);
		if(!status)
			break;
	}

	FG_MainModule->closeProgram();
	FG_MainModule->deleteInstance();

	IwUtilTerminate();
	s3eDeviceExit(0);
	return 0;
}
