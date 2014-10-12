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

#if defined(FG_USING_MARMALADE)
#include "s3e.h"
#include "s3eTypes.h"
#include "IwUtil.h"
#include "s3eDevice.h"
#endif /* FG_USING_MARMALADE */

#include "fgLog.h"
#include "Event/fgEventManager.h"
#include "Input/fgPointerInputReceiver.h"
#include "Hardware/fgHardwareState.h"

class MainModule;
extern "C" int main();

#if defined FG_USING_MARMALADE
class fgMarmaladeHandlers
{
private:

    fgMarmaladeHandlers() { };

    ~fgMarmaladeHandlers() { };

public:
    static int32_t pauseHandler(void *systemData, void *userData);
    static int32_t unpauseHandler(void *systemData, void *userData);
    static int32_t suspendGfxHandler(void *systemData, void *userData);
    static int32_t resumeGfxHandler(void *systemData, void *userData);
    static int32_t keyStateChangedHandler(void *systemData, void *userData);
};
#endif /* FG_USING_MARMALADE */

/**
 *
 */
class MainModule
{
#if defined FG_USING_MARMALADE
    friend class fgMarmaladeHandlers;
#endif /* FG_USING_MARMALADE */
    friend int main();
protected:

    /**
     * Initialize rendering parameters.
     */
    MainModule() : 
    m_appInit(FG_FALSE),
    m_slow(FG_FALSE),
    m_isExit(FG_FALSE),
    m_gameMain(NULL),
    m_eventMgr(NULL) {
    }

protected:
#if defined(FG_USING_SDL2)
    SDL_EventType checkSDLEvents(void) {
        SDL_Event event;
        SDL_EventType status = SDL_FIRSTEVENT;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                    /* Application events */
                case SDL_QUIT: /**< User-requested quit */
                    return SDL_QUIT;
                    break;

                    /* These application events have special meaning on iOS, see README-ios.txt for details */
                case SDL_APP_TERMINATING: /**< The application is being terminated by the OS
                                     Called on iOS in applicationWillTerminate()
                                     Called on Android in onDestroy()
                                */
                    break;

                case SDL_APP_LOWMEMORY: /**< The application is low on memory, free memory if possible.
                                     Called on iOS in applicationDidReceiveMemoryWarning()
                                     Called on Android in onLowMemory()
                                */
                    break;

                case SDL_APP_WILLENTERBACKGROUND: /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()
                                */
                    break;

                case SDL_APP_DIDENTERBACKGROUND: /**< The application did enter the background and may not get CPU for some time
                                     Called on iOS in applicationDidEnterBackground()
                                     Called on Android in onPause()
                                */
                    break;

                case SDL_APP_WILLENTERFOREGROUND: /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()
                                */
                    break;

                case SDL_APP_DIDENTERFOREGROUND: /**< The application is now interactive
                                     Called on iOS in applicationDidBecomeActive()
                                     Called on Android in onResume()
                                */
                    break;


                    /* Window events */
                case SDL_WINDOWEVENT: /**< Window state change */
                    break;
                case SDL_SYSWMEVENT: /**< System specific event */
                    break;

                    /* Keyboard events */
                case SDL_KEYDOWN: /**< Key pressed */    
                    if(m_eventMgr) {
                        // #FIXME
                        if(!event.key.repeat)
                            m_eventMgr->addKeyDown((int)event.key.keysym.sym);
                    }
                    break;
                case SDL_KEYUP: /**< Key released */
                    if(m_eventMgr) {
                        // #FIXME
                        if(!event.key.repeat)
                            m_eventMgr->addKeyUp((int)event.key.keysym.sym);
                    }
                    break;
                case SDL_TEXTEDITING: /**< Keyboard text editing (composition) */
                    break;
                case SDL_TEXTINPUT: /**< Keyboard text input */
                    printf("TEXT INPUT: '%s'\n", event.text.text);
                    break;
#if defined(FG_USING_PLATFORM_LINUX) || defined(FG_USING_PLATFORM_WINDOWS)
                    /* Mouse events */
                case SDL_MOUSEMOTION: /**< Mouse moved */
                    if(!m_gameMain)
                        continue;
                    this->m_gameMain->getPointerInputReceiver()->singleTouchMotionHandler((void *)&event.motion, this->m_gameMain->getPointerInputReceiver());
                    break;
                case SDL_MOUSEBUTTONDOWN: /**< Mouse button pressed */
                    if(!m_gameMain)
                        continue;
                    this->m_gameMain->getPointerInputReceiver()->singleTouchButtonHandler((void *)&event.button, this->m_gameMain->getPointerInputReceiver());
                    break;
                case SDL_MOUSEBUTTONUP: /**< Mouse button released */
                    if(!m_gameMain)
                        continue;
                    this->m_gameMain->getPointerInputReceiver()->singleTouchButtonHandler((void *)&event.button, this->m_gameMain->getPointerInputReceiver());
                    break;
                case SDL_MOUSEWHEEL: /**< Mouse wheel motion */
                    break;
#endif /* PLATFORM SPECIFIC */
                    
                    /* Joystick events #FIXME */
                case SDL_JOYAXISMOTION: /**< Joystick axis motion */
                    printf("SDL_JOYAXISMOTION\n");
                    break;
                case SDL_JOYBALLMOTION: /**< Joystick trackball motion */
                    printf("SDL_JOYBALLMOTION\n");
                    break;
                case SDL_JOYHATMOTION: /**< Joystick hat position change */
                    printf("SDL_JOYHATMOTION\n");
                    break;
                case SDL_JOYBUTTONDOWN: /**< Joystick button pressed */
                    printf("SDL_JOYBUTTONDOWN\n");
                    break;
                case SDL_JOYBUTTONUP: /**< Joystick button released */
                    printf("SDL_JOYBUTTONUP\n");
                    break;
                case SDL_JOYDEVICEADDED: /**< A new joystick has been inserted into the system */
                    printf("SDL_JOYDEVICEADDED\n");
                    break;
                case SDL_JOYDEVICEREMOVED: /**< An opened joystick has been removed */
                    printf("SDL_JOYDEVICEREMOVED\n");
                    break;

                    /* Game controller events */
#if 0
                case SDL_CONTROLLERAXISMOTION: /**< Game controller axis motion */
                    printf("SDL_CONTROLLERAXISMOTION\n");
                    break;
                case SDL_CONTROLLERBUTTONDOWN: /**< Game controller button pressed */
                    printf("SDL_CONTROLLERBUTTONDOWN\n");
                    break;
                case SDL_CONTROLLERBUTTONUP: /**< Game controller button released */
                    printf("SDL_CONTROLLERBUTTONUP\n");
                    break;
                case SDL_CONTROLLERDEVICEADDED: /**< A new Game controller has been inserted into the system */
                    printf("SDL_CONTROLLERDEVICEADDED\n");
                    break;
                case SDL_CONTROLLERDEVICEREMOVED: /**< An opened Game controller has been removed */
                    printf("SDL_CONTROLLERDEVICEREMOVED\n");
                    {
                        if(!m_gameMain)
                            continue;
                        fgJoypadController *joypadController = this->m_gameMain->getJoypadController();
                        if(joypadController) {
                            joypadController->processEvent(event);
                        }
                    }
                    break;
                
                case SDL_CONTROLLERDEVICEREMAPPED: /**< The controller mapping was updated */
                    printf("SDL_CONTROLLERDEVICEREMAPPED\n");
                    break;
#endif
                    /* Touch events */
                case SDL_FINGERDOWN:
                    break;
                case SDL_FINGERUP:
                    break;
                case SDL_FINGERMOTION:
                    break;
                    
                    /* Gesture events */
                case SDL_DOLLARGESTURE:
                    break;
                case SDL_DOLLARRECORD:
                    break;
                case SDL_MULTIGESTURE:
                    break;

                    /* Clipboard events */
                case SDL_CLIPBOARDUPDATE: /**< The clipboard changed */
                    break;

                    /* Drag and drop events */
                case SDL_DROPFILE: /**< The system requests a file open */
                    break;

                    /* Render events */
                case SDL_RENDER_TARGETS_RESET: /**< The render targets have been reset */
                    break;
                    
                default:
                    if(event.type >= SDL_CONTROLLERAXISMOTION && event.type <= SDL_CONTROLLERDEVICEREMAPPED) {
                        if(!m_gameMain)
                            continue;
                        fgJoypadController *joypadController = this->m_gameMain->getJoypadController();
                        if(joypadController) {
                            joypadController->processEvent(event);
                        }
                    }
                    break;
            }
        }
        return status;
    }
#endif
    
public:

    fgBool isSlow(void) const {
        return m_slow;
    }

    fgBool isExit(void) const {
        return m_isExit;
    }
private:

    void setSlow(fgBool slow) {
        m_slow = slow;
    }

    void setExit(fgBool exit) {
        m_isExit = exit;
    }
    
    static fgBool eventSwipe(fgArgumentList *argv) {
        if(!argv)
            return FG_FALSE;
        fgEventBase *event = (fgEventBase *)argv->getArgumentValueByID(0);
        if(!event)
            return FG_FALSE;
        fgEventType type = event->eventType;
        static int lastx = 128000;
        static int lasty = 128000;
        int xRel = 0, yRel = 0;

        if(type == FG_EVENT_TOUCH_MOTION || 
            type == FG_EVENT_TOUCH_PRESSED || 
            type == FG_EVENT_TOUCH_RELEASED) {
            fgTouchEvent *touch = (fgTouchEvent *)argv->getArgumentValueByID(0);
            if(lastx > 100000 && lasty > 100000) {
                lastx = touch->x;
                lasty = touch->y;
            }
            xRel = -(lastx - touch->x);
            yRel = -(lasty - touch->y);
            lastx = touch->x;
            lasty = touch->y;
            //printf("TOUCH MOTION: X: %d Y: %d | xRel: %d | yRel: %d \n", touch->x, touch->y, xRel, yRel);
            if(touch->pressed)
                cameraAnim->update((float)xRel, (float)yRel);
            if(type == FG_EVENT_TOUCH_RELEASED) {
                lastx = 128000;
                lasty = 128000;
            }
        } else if(0) {
            fgSwipeEvent *swipe = (fgSwipeEvent *)argv->getArgumentValueByID(0);
            //printf("EVENT SWIPE: Xoff: %d | Yoff: %d | myX: %d | myY: %d | stepsX: %d | stepsY: %d\n",
            //swipe->swipeXOffset, 
            //swipe->swipeYOffset,
            //swipe->xStart-swipe->xEnd,
            //swipe->yStart-swipe->xEnd,
            //swipe->swipeXSteps,
            //swipe->swipeYSteps);
        }
        return FG_TRUE;
    }

    /**
     * Called when a fullscreen window with an OpenGL context
     * has been created and is ready to be used.
     */
    fgBool initProgram() {
        FG_LOG::PrintDebug("Init program main...");
        if(m_appInit) {
            // already initialized
            return FG_TRUE;
        }

#if defined FG_USING_MARMALADE
        s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, S3E_SURFACE_LANDSCAPE_FIXED);
        // ?
        //s3eKeyboardSetInt(S3E_KEYBOARD_GET_CHAR, 1);
        // Register for keyboard
        s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, &fgMarmaladeHandlers::keyStateChangedHandler, (void *)this);

        // DEVICE FOCUS – called on any device
        s3eDeviceRegister(S3E_DEVICE_PAUSE, &fgMarmaladeHandlers::pauseHandler, (void *)this);
        s3eDeviceRegister(S3E_DEVICE_UNPAUSE, &fgMarmaladeHandlers::unpauseHandler, (void *)this);
        int32 mustSuspend = s3eGLGetInt(S3E_GL_MUST_SUSPEND); // S3E_GL_VERSION // S3E_EGL_VERSION
        s3eGLRegister(S3E_GL_SUSPEND, &fgMarmaladeHandlers::suspendGfxHandler, (void *)this);
        s3eGLRegister(S3E_GL_RESUME, &fgMarmaladeHandlers::resumeGfxHandler, (void *)this);

#endif /* FG_USING_MARMALADE */
        if(!m_eventMgr) {
            FG_LOG::PrintDebug("Creating event manager...");
            m_eventMgr = new fgEventManager();
            if(!m_eventMgr->initialize()) {
                // Should check?
            }
        }
        if(!m_gameMain) {
            FG_LOG::PrintDebug("Creating game main object...");
            m_gameMain = new fgGameMain(m_eventMgr);
        }
        //m_gameMain->setEventManager(m_eventMgr);

        // Well the whole configuration process should update the screen (swap buffers)
        // this is needed to display splash screen (after marmalade splash screen) and
        // show the game initialization process by displaying the progress bar
        if(!m_gameMain->loadConfiguration()) {
            return FG_FALSE;
        }

        if(!m_gameMain->initSubsystems()) {
            return FG_FALSE;
        }

        if(!m_gameMain->loadResources()) {
            return FG_FALSE;
        }
        //FG_EventManager->addEventCallback(FG_EVENT_SWIPE_X, &MainModule::eventSwipe);
        //FG_EventManager->addEventCallback(FG_EVENT_SWIPE_Y, &MainModule::eventSwipe);
        //FG_EventManager->addEventCallback(FG_EVENT_SWIPE_XY, &MainModule::eventSwipe);
        m_eventMgr->addEventCallback(FG_EVENT_TOUCH_MOTION, &MainModule::eventSwipe);
        m_eventMgr->addEventCallback(FG_EVENT_TOUCH_PRESSED, &MainModule::eventSwipe);
        m_eventMgr->addEventCallback(FG_EVENT_TOUCH_RELEASED, &MainModule::eventSwipe);
        m_appInit = FG_TRUE;
        return FG_TRUE;
    }

    /**
     * Apps main loop step (one thread)
     */
    fgBool mainLoopStep() {
        FG_HardwareState->deviceYield(0);
        if(!m_appInit) {
            return FG_FALSE;
        }
        
        // #FIXME
#if defined(FG_USING_SDL2)
        if(checkSDLEvents() == SDL_QUIT) {
            return FG_FALSE;
        }
        //if(SDL_QuitRequested() == SDL_TRUE) {
        //return FG_FALSE;
        //}
#endif

#if defined(FG_USING_MARMALADE)
        s3eKeyboardUpdate();
        if(s3eDeviceCheckQuitRequest()) {
            m_appInit = FG_FALSE;
            return FG_FALSE;
        }
        if(s3eKeyboardGetState(s3eKeyEnter) & S3E_KEY_STATE_PRESSED) {
            m_appInit = FG_FALSE;
            FG_LOG::PrintDebug("ENTER PRESSED...");
            return FG_FALSE;
        }
		// #TODELETE - camera animation test
		if(s3eKeyboardGetState(s3eKeyW) & S3E_KEY_STATE_DOWN) {
			cameraAnim->moveForward();
		}
		if(s3eKeyboardGetState(s3eKeyS) & S3E_KEY_STATE_DOWN) {
			cameraAnim->moveBackward();
		}
		if(s3eKeyboardGetState(s3eKeyA) & S3E_KEY_STATE_DOWN) {
			cameraAnim->moveLeft();
		}
		if(s3eKeyboardGetState(s3eKeyD) & S3E_KEY_STATE_DOWN) {
			cameraAnim->moveRight();
		}
#endif /* FG_USING_MARMALADE */
        if(m_isExit) {
            m_appInit = FG_FALSE;
            FG_LOG::PrintDebug("EXIT IS ACTIVATED - break loop main ! bye!");
            return FG_FALSE;
        }

        FG_HardwareState->deviceYield(0);
        m_gameMain->update();
        FG_HardwareState->deviceYield(0);

        // well for now drawing and all update functions will be called in one place (one thread)
        // however it neads changing
        m_gameMain->display();
        FG_HardwareState->deviceYield(0);

        m_gameMain->render();
        FG_HardwareState->deviceYield(0);

        return FG_TRUE;
    }

    /**
     * The way to exit from the app
     */
    void closeProgram() {
        FG_LOG::PrintDebug("closeEvent()");
        if(m_gameMain)
            m_gameMain->releaseResources();

        // This frees all the data used by singletons and other nonresource data
        // after that only things left to free are FG_GameMain and MainModule
        if(m_gameMain) {
            m_gameMain->closeSybsystems();
            delete m_gameMain;
        }
        m_gameMain = NULL;
        if(m_eventMgr) {
            delete m_eventMgr;
            m_eventMgr = NULL;
        }
        m_appInit = FG_FALSE;
    }

private:

    /**
     * DEVICE PAUSE event
     */
    void suspendGfxEvent(void) {
        FG_LOG::PrintDebug(">>> SUSPEND GFX SUBSYSTEM()");
        if(m_gameMain)
            m_gameMain->getGfxMain()->suspendGFX();
    }

    /**
     * DEVICE unpause event
     */
    void resumeGfxEvent(void) {
        FG_LOG::PrintDebug(">>> RESUME GFX SUBSYSTEM()");
        if(m_gameMain)
            m_gameMain->getGfxMain()->resumeGFX();
    }

    /**
     * DEVICE PAUSE event
     * (not the GL pause event)
     */
    void focusLostEvent(void) {
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
    void focusGainedEvent(void) {
        FG_LOG::PrintDebug("focusGainedEvent()");
    }
#if defined FG_USING_MARMALADE

    /**
     * Handle PRESSING and RELEASING keys
     */
    void keyStateChangedEvent(s3eKeyboardEvent* event) {
        if(!m_appInit || !m_eventMgr)
            return;
#if 0
        char dst[100];
        s3eWChar wchar1 = s3eKeyboardGetChar();
        int printable = (int)wchar1;
        if(printable < 255) {
            printf("printable: '%c'\n", (char)printable);
        }
        s3eKeyboardGetDisplayName(dst, event->m_Key);
        printf("'%s'\n", dst);
#endif
        if(event->m_Pressed) {
            m_eventMgr->addKeyDown((int)event->m_Key);
        } else {
            m_eventMgr->addKeyUp((int)event->m_Key);
        }
        //FG_LOG::PrintDebug("FG_EventManager - keyboard - %d is pressed? - code: %d", (int)event->m_Pressed, (int)event->m_Key);
    }
#endif /* FG_USING_MARMALADE */

private:
    /// Is app fully initialized?
    fgBool m_appInit;

    /// Is the device slow?
    fgBool m_slow;

    /// Is exit activated?
    fgBool m_isExit;

    /// Game main class - this is for initialization procedures
    /// contains also functions for handling events, drawing, etc #TODO
    /// Needs refactoring, some level of merging within main module or
    /// changing name to fgApplication - or extending fgApplication class
    /// #TODO - support threads
    fgGameMain *m_gameMain;
    /// Main event manager, it's going to be initialized in main module class
    /// then passed down to the GameMain class
    fgEventManager *m_eventMgr;
};

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
    float milisec = (1.0f / fps) * 1000.0f;
    int result = s3eTimerSetTimer(milisec, &allow_moblet_loop, NULL);
    if(result == S3E_RESULT_ERROR) {
        FG_LOG::PrintError("Setting Moblet::loop callback failed!");
        return false;
    }
    return true;
}

#endif

#if defined FG_USING_MARMALADE

/**
 * Focus lost HANDLER
 */
int32_t fgMarmaladeHandlers::pauseHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    MainModule *mainModule = (MainModule *)userData;
    mainModule->focusLostEvent();
    return 0;
}

/**
 * Focus restored HANDLER
 */
int32_t fgMarmaladeHandlers::unpauseHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    MainModule *mainModule = (MainModule *)userData;
    mainModule->focusGainedEvent();
    return 0;
}

/**
 * Focus lost HANDLER
 */
int32_t fgMarmaladeHandlers::suspendGfxHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    MainModule *mainModule = (MainModule *)userData;
    mainModule->suspendGfxEvent();
    return 0;
}

/**
 * Focus restored HANDLER
 */
int32_t fgMarmaladeHandlers::resumeGfxHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    MainModule *mainModule = (MainModule *)userData;
    mainModule->resumeGfxEvent();
    return 0;
}

/**
 * Key state changed HANDLER
 */
int32_t fgMarmaladeHandlers::keyStateChangedHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    MainModule *mainModule = (MainModule *)userData;
    s3eKeyboardEvent* event = (s3eKeyboardEvent*)systemData;
    mainModule->keyStateChangedEvent(event);
    return 0;
}

#endif /* FG_USING_MARMALADE */

/**
 * Main function that is called when the program starts.
 */
extern "C" int main() {
#if defined FG_USING_MARMALADE
    IwUtilInit();
#endif /* FG_USING_MARMALADE */

    //IwMemBucketDebugSetBreakpoint(580);
    //IwMemBucketDebugSetBreakpoint(580);
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
    FG_LOG::PrintDebug("%s: Start up", FG_PACKAGE_FULL_TEXT);
    MainModule *mainModule = new MainModule();

    if(!mainModule->initProgram()) {
        mainModule->closeProgram();
        delete mainModule;
#if defined FG_USING_MARMALADE
        IwUtilTerminate();
        s3eDeviceExit(0);
#endif /* FG_USING_MARMALADE */		
        return 1;
    }
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

    while(true) {
        fgBool status = mainModule->mainLoopStep();
        FG_HardwareState->deviceYield(1);
#if defined FG_USING_MARMALADE
        s3eDeviceBacklightOn(); // #FIXME // need to wrap it in something else
#endif /* FG_USING_MARMALADE */
        if(status == FG_FALSE)
            break;
    }

    mainModule->closeProgram();
    delete mainModule;

#if defined FG_USING_MARMALADE
    IwUtilTerminate();
    s3eDeviceExit(0);
#endif /* FG_USING_MARMALADE */
    return 0;
}
