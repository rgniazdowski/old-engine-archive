/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"

#include "fgGameMain.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <map>

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
#include "IwUtil.h"
#include "s3eDevice.h"
#endif

#include "fgSingleton.h"
#include "fgLog.h"
#include "Event/fgEventManager.h"
#include "Input/fgTouchReceiver.h"
#include "Hardware/fgHardwareState.h"

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
	MainModule() : m_useMultitouch(FG_FALSE), m_appInit(FG_FALSE), m_slow(FG_FALSE), m_isExit(FG_FALSE) {
		memset(&m_touches, 0, sizeof(m_touches));
	}

public:
	fgBool isSlow(void) const {
		return m_slow;
	}

	void setSlow(fgBool slow) {
		m_slow = slow;
	}

	void setExit(fgBool exit) {
		m_isExit = exit;
	}

	fgBool isExit(void) const {
		return m_isExit;
	}

	/**
	 * Focus lost HANDLER
	 */
	static int32_t pauseHandler(void *systemData, void *userData) {
		MainModule::getInstance()->focusLostEvent();
		return 0;
	}

	/**
	 * Focus restored HANDLER
	 */
	static int32_t unpauseHandler(void *systemData, void *userData) {
		MainModule::getInstance()->focusGainedEvent();
		return 0;
	}

	/**
	* Key state changed HANDLER
	*/
	static int32_t keyStateChangedHandler(void *systemData, void *userData)
	{
#if defined FG_USING_MARMALADE
		s3eKeyboardEvent* event = (s3eKeyboardEvent*)systemData;
		MainModule::getInstance()->keyStateChangedEvent(event);
#endif // FG_USING_MARMALADE
		return 0;
	}

	/**
	 * Touch press/release HANDLER
	 */
	static int32_t multiTouchButtonHandler(void* systemData, void* userData)
	{
#if defined FG_USING_MARMALADE
		s3ePointerTouchEvent* event = (s3ePointerTouchEvent*) systemData;
		if(event->m_Pressed) {
			MainModule::getInstance()->multiTouchPressEvent(event->m_x, event->m_y, event->m_TouchID);
		} else {
			MainModule::getInstance()->multiTouchReleaseEvent(event->m_x, event->m_y, event->m_TouchID);
		}
#endif // FG_USING_MARMALADE
		return 0;
	}

	/**
	 * Touch motion HANDLER
	 */
	static int32_t multiTouchMotionHandler(void* systemData, void* userData)
	{
#if defined FG_USING_MARMALADE
		s3ePointerTouchMotionEvent* event = (s3ePointerTouchMotionEvent*) systemData;
		MainModule::getInstance()->multiTouchMoveEvent(event->m_x, event->m_y, event->m_TouchID);
#endif // FG_USING_MARMALADE
		return 0;
	}

	/**
	 * Single press/release HANDLER
	 */
	static int32_t singleTouchButtonHandler(void* systemData, void* userData)
	{
#if defined FG_USING_MARMALADE
		s3ePointerEvent* event = (s3ePointerEvent*) systemData;
		if(event->m_Pressed) {
			MainModule::getInstance()->multiTouchPressEvent(event->m_x, event->m_y, 0);
		} else {
			MainModule::getInstance()->multiTouchReleaseEvent(event->m_x, event->m_y, 0);
		}
#endif // FG_USING_MARMALADE
		return 0;
	}

	/**
	 * Single motion HANDLER
	 */
	static int32_t singleTouchMotionHandler(void* systemData, void* userData)
	{
#if defined FG_USING_MARMALADE
		s3ePointerMotionEvent* event = (s3ePointerMotionEvent*) systemData;
		MainModule::getInstance()->multiTouchMoveEvent(event->m_x, event->m_y, 0);
#endif // FG_USING_MARMALADE
		return 0;
	}

	/**
	 * Called when a fullscreen window with an OpenGL context
	 * has been created and is ready to be used.
	 */
	fgBool initProgram()
	{
#if defined FG_USING_MARMALADE
		s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, S3E_SURFACE_LANDSCAPE_FIXED);

		// Register for keyboard
		s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, &MainModule::keyStateChangedHandler, NULL);

		// Register for touches
		m_useMultitouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? FG_TRUE : FG_FALSE;
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

#endif // FG_USING_MARMALADE

		// FIXME
		// Well the whole configuration process should update the screen (swap buffers)
		// this is needed to display splash screen (after marmalade splash screen) and
		// show the game initialization process by displaying the progress bar

		if(!FG_GameMain->initSubsystems()) {
			return FG_FALSE;
		}

		if(!FG_GameMain->loadConfiguration()) {
			return FG_FALSE;
		}

		if(!FG_GameMain->loadResources()) {
			return FG_FALSE;
		}

		m_appInit = FG_TRUE;
		return FG_TRUE;
	}

	/**
	 * Apps main loop step (one thread)
	 */
	fgBool mainLoopStep()
	{
#if defined FG_USING_MARMALADE
		if (s3eDeviceCheckQuitRequest()) {
			m_appInit = FG_FALSE;
			return FG_FALSE;
		}
		if (s3eKeyboardGetState(s3eKeyEnter) & S3E_KEY_STATE_PRESSED)	{
			m_appInit = FG_FALSE;
			FG_LOG::PrintDebug("ENTER PRESSED...");
			return FG_FALSE;
		}
#endif // FG_USING_MARMALADE
		if (m_isExit) {
			m_appInit = FG_FALSE;
			FG_LOG::PrintDebug("EXIT IS ACTIVATED - break loop main ! bye!");
			return FG_FALSE;
		}

		FG_HardwareState->deviceYield(0);
		FG_GameMain->update();
		FG_HardwareState->deviceYield(0);

		// well for now drawing and all update functions will be called in one place (one thread)
		// however it neads changing
		FG_GameMain->display();
		FG_HardwareState->deviceYield(0);

		FG_GameMain->render();
		FG_HardwareState->deviceYield(0);

		return FG_TRUE;
	}

	/**
	 * The way to exit from the app
	 */
	void closeProgram() {
		FG_LOG::PrintDebug("closeEvent()");
		FG_GameMain->releaseResources();

		// This frees all the data used by singletons and other nonresource data
		// after that only things left to free are FG_GameMain and MainModule
		FG_GameMain->closeSybsystems();
		FG_GameMain->deleteInstance();

		m_appInit = FG_FALSE;
	}

private:

	/**
	 * DEVICE PAUSE event
	 * (not the GL pause event)
	 */
	void focusLostEvent()
	{
		FG_LOG::PrintDebug("focusLostEvent()");

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
		FG_LOG::PrintDebug("focusGainedEvent()");
	}
#if defined FG_USING_MARMALADE
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
		FG_LOG::PrintDebug("FG_EventManager - keyboard - %d is pressed? - code: %d\n", (int)event->m_Pressed, (int)event->m_Key);
	}
#endif // FG_USING_MARMALADE

	/**
	 * This function is called with a coordinate when the screen is touched.
	 * The touch id will remain the same as long as this touch is active.
	 */
	void multiTouchPressEvent(int x, int y, unsigned int touchId)
	{
		if( !m_appInit )
			return;

		m_touches[touchId] = FG_TRUE;
		FG_TouchReceiver->handlePointerPressed(fgVector2i(x,y), touchId);
	}

	/**
	 *  This method is called with a coordinate when an active touch moves.
	 */
	void multiTouchMoveEvent(int x, int y, unsigned int touchId)
	{
		if( !m_appInit )
			return;

		if(m_touches[touchId] == FG_TRUE)
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

		m_touches[touchId] = FG_FALSE;
		FG_TouchReceiver->handlePointerReleased(fgVector2i(x,y),touchId);
	}

private:
	enum {NUM_TOUCHES = 10};

	/// Touches (using multitouch)
	fgBool m_touches[NUM_TOUCHES];

	/// Result of multitouch availability test
	fgBool m_useMultitouch;

	/// Is app fully initialized?
	fgBool m_appInit;

	/// Is the device slow?
	fgBool m_slow;

	/// Is exit activated?
	fgBool m_isExit;
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
		FG_LOG::PrintError("Setting Moblet::loop callback failed!");
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
#if defined FG_USING_MARMALADE
	IwUtilInit();
#endif // FG_USING_MARMALADE
	//IwMemBucketDebugSetBreakpoint(1964);
	//IwMemBucketDebugSetBreakpoint(177);
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
	FG_MainModule->initProgram();
	FG_HardwareState->deviceYield(0);

	/*if( FG_MainModule->isSlow() ) {
		// USE FPS LIMIT
		FG_LOG::PrintDebug("USING FPS LIMIT FOR DEVICE GEN: %d", dev->deviceGeneration());

		if(!set_allow_loop_handler()) {
			FG_LOG::PrintError("FATAL ERROR #1: EXITING");
			s3eDeviceExit(1);
		}
		while(1) {
			if ( g_allowLoop ) {
				g_allowLoop = false;
				FG_MainModule->mainLoopStep();
			}
			FG_HardwareState->deviceYield(10);
		}
	} else {
		// NO FPS LIMIT
		FG_LOG::PrintDebug("NO FPS LIMIT FOR DEVICE GEN: %d", dev->deviceGeneration());
		while(1) {
			FG_MainModule->mainLoopStep();
			FG_HardwareState->deviceYield(0);
		}
	}*/

	while(true)	{
		fgBool status = FG_MainModule->mainLoopStep();
		FG_HardwareState->deviceYield(1);
		if(status == FG_FALSE)
			break;
	}

	FG_MainModule->closeProgram();
	FG_MainModule->deleteInstance();
#if defined FG_USING_MARMALADE
	IwUtilTerminate();
	s3eDeviceExit(0);
#endif // FG_USING_MARMALADE
	return 0;
}
