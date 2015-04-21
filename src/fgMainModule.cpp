/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
#include "fgMainModule.h"
#include "Android/fgAndroid.h"

#include "Event/fgEventManager.h"
#include "Event/fgInputHandler.h"
#include "Hardware/fgHardwareState.h"
#include "Util/fgProfiling.h"
#include "fgDebugConfig.h"
#include "fgLog.h"
#include "Util/fgStrings.h"

#if !defined(FG_STATIC_LIBRARY)
#if defined(FG_USING_MARMALADE)

/**
 * Focus lost HANDLER
 */
int32_t fgMarmaladeHandlers::pauseHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->focusLostEvent();
    return 0;
}

/**
 * Focus restored HANDLER
 */
int32_t fgMarmaladeHandlers::unpauseHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->focusGainedEvent();
    return 0;
}

/**
 * Focus lost HANDLER
 */
int32_t fgMarmaladeHandlers::suspendGfxHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->suspendGfxEvent();
    return 0;
}

/**
 * Focus restored HANDLER
 */
int32_t fgMarmaladeHandlers::resumeGfxHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->resumeGfxEvent();
    return 0;
}

/**
 * Key state changed HANDLER
 */
int32_t fgMarmaladeHandlers::keyStateChangedHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    s3eKeyboardEvent* event = (s3eKeyboardEvent*)systemData;
    mainModule->keyStateChangedEvent(event);
    return 0;
}
#endif /* FG_USING_MARMALADE */

using namespace fg;

/**
 * Initialize main module
 */
CMainModule::CMainModule(int argc, char *argv[]) :
m_argc(argc),
m_argv(argv),
m_appInit(FG_FALSE),
m_slow(FG_FALSE),
m_isExit(FG_FALSE),
m_isSuspend(FG_FALSE),
#if defined(FG_USING_MARMALADE) // #FIXME
m_deviceQuery(),
#endif /* FG_USING_MARMALADE */
m_gameMain(NULL) { }

CMainModule::~CMainModule() { }

#if defined(FG_USING_SDL2)

int SDLCALL CMainModule::filterSDLEvents(void* userdata, SDL_Event* event) {
    if(!userdata)
        return 1;
    CMainModule *mainModule = (CMainModule *)userdata;
    switch(event->type) {
        case SDL_APP_WILLENTERBACKGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_WILL_ENTER_BACKGROUND");
            // Focus lost?
            mainModule->m_isSuspend = FG_TRUE;
            break;
        case SDL_APP_DIDENTERBACKGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_DID_ENTER_BACKGROUND");
            //suspendGfxEvent();
            mainModule->m_isSuspend = FG_TRUE;
            break;
        case SDL_APP_WILLENTERFOREGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_WILL_ENTER_FOREGROUND");
            //resumeGfxEvent();
            mainModule->m_isSuspend = FG_FALSE;
            break;
        case SDL_APP_DIDENTERFOREGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_DID_ENTER_FOREGROUND");
            mainModule->m_isSuspend = FG_FALSE;
            break;
        default:
            break;
    };
    return 1;
}

/**
 * #FIXME - this needs to be maintained differently
 * - maybe add some SDL2 event watches?
 * @return 
 */
SDL_EventType CMainModule::checkSDLEvents(void) {
    SDL_Event event;
    SDL_EventType status = SDL_FIRSTEVENT;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
                /* Application events */
            case SDL_QUIT: /**< User-requested quit */
                FG_LOG_DEBUG("SDL2: The application is terminating, caught QUIT...");
                return SDL_QUIT;
                break;

                /* These application events have special meaning on iOS, see README-ios.txt for details */
            case SDL_APP_TERMINATING: /**< The application is being terminated by the OS
                                     Called on iOS in applicationWillTerminate()
                                     Called on Android in onDestroy()
                                    */
                FG_LOG_DEBUG("SDL2: The application is terminating...");
                return SDL_QUIT;
                break;

            case SDL_APP_LOWMEMORY: /**< The application is low on memory, free memory if possible.
                                     Called on iOS in applicationDidReceiveMemoryWarning()
                                     Called on Android in onLowMemory()
                                    */
                FG_LOG_DEBUG("SDL2: The application is low on memory...");
                break;

            case SDL_APP_WILLENTERBACKGROUND: /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()
                                    */
                FG_LOG_DEBUG("SDL2: The application is about to enter the background...");
                // Focus lost?
                m_isSuspend = FG_TRUE;
                break;

            case SDL_APP_DIDENTERBACKGROUND: /**< The application did enter the background and may not get CPU for some time
                                     Called on iOS in applicationDidEnterBackground()
                                     Called on Android in onPause()
                                    */
                FG_LOG_DEBUG("SDL2: The application did enter the background and may not get CPU for some time...");
                suspendGfxEvent();
                m_isSuspend = FG_TRUE;
                break;

            case SDL_APP_WILLENTERFOREGROUND: /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()
                                    */
                FG_LOG_DEBUG("SDL2: The application is about to enter the foreground...");
                resumeGfxEvent();
                m_isSuspend = FG_FALSE;
                // Focus gained?
                break;

            case SDL_APP_DIDENTERFOREGROUND: /**< The application is now interactive
                                     Called on iOS in applicationDidBecomeActive()
                                     Called on Android in onResume()
                                    */
                FG_LOG_DEBUG("SDL2: The application is now interactive...");
                m_isSuspend = FG_FALSE;
                break;


                /* Window events */
            case SDL_WINDOWEVENT: /**< Window state change */
                break;
            case SDL_SYSWMEVENT: /**< System specific event */
                break;

                /* Keyboard events */
            case SDL_KEYDOWN: /**< Key pressed */
                if(this->m_gameMain) {
                    // #FIXME
                    if(!event.key.repeat)
                        this->m_gameMain->getInputHandler()->addKeyDown((int)event.key.keysym.sym);
                }
                break;
            case SDL_KEYUP: /**< Key released */
                if(this->m_gameMain) {
                    // #FIXME
                    if(!event.key.repeat)
                        this->m_gameMain->getInputHandler()->addKeyUp((int)event.key.keysym.sym);
                }
                break;
            case SDL_TEXTEDITING: /**< Keyboard text editing (composition) */
                break;
            case SDL_TEXTINPUT: /**< Keyboard text input */
                //printf("TEXT INPUT: '%s'\n", event.text.text);
                break;
#if defined(FG_USING_PLATFORM_LINUX) || defined(FG_USING_PLATFORM_WINDOWS)
                /* Mouse events */
            case SDL_MOUSEMOTION: /**< Mouse moved */
                if(!m_gameMain)
                    continue;
                this->m_gameMain->getInputHandler()->singleTouchMotionHandler((void *)&event.motion, this->m_gameMain->getInputHandler());
                break;
            case SDL_MOUSEBUTTONDOWN: /**< Mouse button pressed */
                if(!m_gameMain)
                    continue;
                this->m_gameMain->getInputHandler()->singleTouchButtonHandler((void *)&event.button, this->m_gameMain->getInputHandler());
                break;
            case SDL_MOUSEBUTTONUP: /**< Mouse button released */
                if(!m_gameMain)
                    continue;
                this->m_gameMain->getInputHandler()->singleTouchButtonHandler((void *)&event.button, this->m_gameMain->getInputHandler());
                break;
            case SDL_MOUSEWHEEL: /**< Mouse wheel motion */
                //guiScale += 0.05f * (float)event.wheel.y;
                break;
#endif /* PLATFORM SPECIFIC */

                /* Joystick events #FIXME */
            case SDL_JOYAXISMOTION: /**< Joystick axis motion */
                FG_LOG_DEBUG("SDL_JOYAXISMOTION");
                break;
            case SDL_JOYBALLMOTION: /**< Joystick trackball motion */
                FG_LOG_DEBUG("SDL_JOYBALLMOTION");
                break;
            case SDL_JOYHATMOTION: /**< Joystick hat position change */
                FG_LOG_DEBUG("SDL_JOYHATMOTION");
                break;
            case SDL_JOYBUTTONDOWN: /**< Joystick button pressed */
                FG_LOG_DEBUG("SDL_JOYBUTTONDOWN");
                break;
            case SDL_JOYBUTTONUP: /**< Joystick button released */
                FG_LOG_DEBUG("SDL_JOYBUTTONUP");
                break;
            case SDL_JOYDEVICEADDED: /**< A new joystick has been inserted into the system */
                FG_LOG_DEBUG("SDL_JOYDEVICEADDED");
                break;
            case SDL_JOYDEVICEREMOVED: /**< An opened joystick has been removed */
                FG_LOG_DEBUG("SDL_JOYDEVICEREMOVED");
                break;

                /* Game controller events */
#if 0
            case SDL_CONTROLLERAXISMOTION: /**< Game controller axis motion */
                FG_LOG_DEBUG("SDL_CONTROLLERAXISMOTION");
                break;
            case SDL_CONTROLLERBUTTONDOWN: /**< Game controller button pressed */
                FG_LOG_DEBUG("SDL_CONTROLLERBUTTONDOWN");
                break;
            case SDL_CONTROLLERBUTTONUP: /**< Game controller button released */
                FG_LOG_DEBUG("SDL_CONTROLLERBUTTONUP");
                break;
            case SDL_CONTROLLERDEVICEADDED: /**< A new Game controller has been inserted into the system */
                FG_LOG_DEBUG("SDL_CONTROLLERDEVICEADDED");
                break;
            case SDL_CONTROLLERDEVICEREMOVED: /**< An opened Game controller has been removed */
                FG_LOG_DEBUG("SDL_CONTROLLERDEVICEREMOVED");
            {
                if(!m_gameMain)
                    continue;
                CJoypadController *joypadController = this->m_gameMain->getJoypadController();
                if(joypadController) {
                    joypadController->processEvent(event);
                }
            }
                break;

            case SDL_CONTROLLERDEVICEREMAPPED: /**< The controller mapping was updated */
                FG_LOG_DEBUG("SDL_CONTROLLERDEVICEREMAPPED");
                break;
#endif
                /* Touch events */
            case SDL_FINGERDOWN:
            {
                if(!m_gameMain)
                    continue;
                SDL_MouseButtonEvent button;
                int w = this->m_gameMain->getGfxMain()->getMainWindow()->getWidth();
                int h = this->m_gameMain->getGfxMain()->getMainWindow()->getHeight();
                button.timestamp = event.tfinger.timestamp;
                button.button = event.tfinger.fingerId;
                button.clicks = 1;
                button.type = SDL_FINGERDOWN;
                button.state = SDL_PRESSED;
                button.x = (int)((float)w * event.tfinger.x);
                button.y = (int)((float)h * event.tfinger.y);
                this->m_gameMain->getInputHandler()->singleTouchButtonHandler((void *)&button, this->m_gameMain->getInputHandler());
            }
                break;
            case SDL_FINGERUP:
            {
                SDL_MouseButtonEvent button;
                int w = this->m_gameMain->getGfxMain()->getMainWindow()->getWidth();
                int h = this->m_gameMain->getGfxMain()->getMainWindow()->getHeight();
                button.timestamp = event.tfinger.timestamp;
                button.button = event.tfinger.fingerId;
                button.clicks = 1;
                button.type = SDL_FINGERUP;
                button.state = SDL_RELEASED;
                button.x = (int)((float)w * event.tfinger.x);
                button.y = (int)((float)h * event.tfinger.y);
                this->m_gameMain->getInputHandler()->singleTouchButtonHandler((void *)&button, this->m_gameMain->getInputHandler());
            }
                break;
            case SDL_FINGERMOTION:
            {
                SDL_MouseMotionEvent motion;
                int w = this->m_gameMain->getGfxMain()->getMainWindow()->getWidth();
                int h = this->m_gameMain->getGfxMain()->getMainWindow()->getHeight();
                motion.timestamp = event.tfinger.timestamp;
                //motion.button = event.tfinger.fingerId;
                //motion.clicks = 1;
                motion.type = SDL_FINGERMOTION;
                motion.state = SDL_PRESSED;
                motion.x = (int)((float)w * event.tfinger.x);
                motion.y = (int)((float)h * event.tfinger.y);
                this->m_gameMain->getInputHandler()->singleTouchMotionHandler((void *)&motion, this->m_gameMain->getInputHandler());
            }
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
#if !defined(FG_USING_PLATFORM_ANDROID)
                if(event.type >= SDL_CONTROLLERAXISMOTION && event.type <= SDL_CONTROLLERDEVICEREMAPPED) {
                    if(!m_gameMain)
                        continue;
                    fg::event::CJoypadController *joypadController = this->m_gameMain->getJoypadController();
                    if(joypadController) {
                        joypadController->processEvent(event);
                    }
                }
#endif
                break;
        }
    }
    if(m_isExit)
        m_isSuspend = FG_TRUE;
    return status;
}
#endif

/**
 * Called when a fullscreen window with an OpenGL context
 * has been created and is ready to be used.
 * 
 * @return 
 */
fgBool CMainModule::initProgram() {
    timesys::init(); // #FIXME global time init?
#if defined(FG_DEBUG)
    profile::g_debugProfiling = new profile::CProfiling();
    profile::g_debugProfiling->initialize();
#endif
    float t1 = timesys::ms();
    FG_LOG_DEBUG("Init program main...");
    if(m_appInit) {
        // already initialized
        return FG_TRUE;
    }

#if defined(FG_USING_MARMALADE)
    m_deviceQuery.computeDevice();
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
    if(!m_gameMain) {
        FG_LOG_DEBUG("Creating game main object...");
        m_gameMain = new fg::CGameMain(m_argc, m_argv);
    }
    // Well the whole configuration process should update the screen (swap buffers)
    // this is needed to display splash screen (after marmalade splash screen) and
    // show the game initialization process by displaying the progress bar
    if(!m_gameMain->loadConfiguration()) {
        return FG_FALSE;
    }
    // Initialize the main subsystems (gui, gfx and others)
    if(!m_gameMain->initSubsystems()) {
        return FG_FALSE;
    }
    // Preload any required resources
    if(!m_gameMain->loadResources()) {
        return FG_FALSE;
    }
    m_gameMain->update();
    m_appInit = FG_TRUE;
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: Program initialized in %.2f seconds", (t2 - t1) / 1000.0f);

#if defined(FG_USING_SDL2) && defined(FG_USING_PLATFORM_ANDROID)
    SDL_AddEventWatch(filterSDLEvents, this);
#endif    
    return FG_TRUE;
}

/**
 * Applications main loop step (one thread)
 * @return
 */
fgBool CMainModule::mainLoopStep(void) {
    FG_HardwareState->deviceYield(0);
    if(!m_appInit) {
        FG_LOG_DEBUG("MainModule: Loop step - application not initialized...");
        return FG_FALSE;
    }
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Program::loopStep");
    }
#endif
    // #FIXME - This event checking should not be in here
#if defined(FG_USING_SDL2)
    if(checkSDLEvents() == SDL_QUIT) {
        m_isExit = FG_TRUE;
    }
#endif
    if(m_isSuspend) {
        //FG_LOG_DEBUG("MainModule: Loop step - suspend...");
        return FG_TRUE;
    }

#if defined(FG_USING_MARMALADE)
    s3eKeyboardUpdate();
    if(s3eDeviceCheckQuitRequest()) {
        m_appInit = FG_FALSE;
        m_isExit = FG_TRUE;
        return FG_FALSE;
    }
    if(s3eKeyboardGetState(s3eKeyEnter) & S3E_KEY_STATE_PRESSED) {
        m_appInit = FG_FALSE;
        m_isExit = FG_TRUE;
        FG_LOG_DEBUG("ENTER PRESSED...");
        return FG_FALSE;
    }
#endif /* FG_USING_MARMALADE */
    if(m_isExit) {
        m_appInit = FG_FALSE;
        FG_LOG_DEBUG("EXIT IS ACTIVATED - break loop main ! bye!");
        return FG_FALSE;
    }

#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::update");
    }
#endif
    FG_HardwareState->deviceYield(0);
    m_gameMain->update();
    FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::update");
        profile::g_debugProfiling->begin("Game::display");
    }
#endif
    // well for now drawing and all update functions will be called in one place (one thread)
    // however it needs changing
    m_gameMain->display();
    FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::display");
        profile::g_debugProfiling->begin("Game::render");
    }
#endif
    FG_HardwareState->deviceYield();
    m_gameMain->render();
    FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
    static int loopCount = 0;
    g_fgDebugConfig.isDebugProfiling = true;
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::render");
        profile::g_debugProfiling->end("Program::loopStep");
        profile::g_debugProfiling->updateHistory();

        loopCount++;
        if(loopCount > 20) {
            loopCount = 0;
            profile::g_debugProfiling->dumpToDefaultFile();
        }
    }
#endif
    return FG_TRUE;
}

/**
 * The way to exit from the application
 */
void CMainModule::closeProgram(void) {
    FG_LOG_DEBUG("Closing program...");
    if(m_gameMain) {
        m_gameMain->closeSybsystems();
        delete m_gameMain;
    }
    m_gameMain = NULL;
    m_appInit = FG_FALSE;
#if defined(FG_DEBUG)
    if(profile::g_debugProfiling)
        delete profile::g_debugProfiling;
    profile::g_debugProfiling = NULL;
#endif
}

/**
 * DEVICE PAUSE event
 */
void CMainModule::suspendGfxEvent(void) {
    FG_LOG_DEBUG("MainModule: Suspending GFX Subsystem");
    if(m_gameMain)
        m_gameMain->getGfxMain()->suspendGFX();
}

/**
 * DEVICE resume event
 */
void CMainModule::resumeGfxEvent(void) {
    FG_LOG_DEBUG("MainModule: Resuming GFX Subsystem...");
    if(m_gameMain)
        m_gameMain->getGfxMain()->resumeGFX();
}

/**
 * DEVICE PAUSE event
 * (not the GL pause event)
 */
void CMainModule::focusLostEvent(void) {
    FG_LOG_DEBUG("MainModule: Focus lost event");

    // No focus means:
    // - displaying OS menu
    // - lower ipad menu visible
    // - minimized
    // - switching to another app
    // - need to turn on internal game pause switch
    // - quickly save the game/app state

    // it needs to be handled properly - for current moment if application losts
    // focus while loading game data etc (initialization) - it will crash
    // TODO pausing/un-pausing events need to handle initialization moments
    // properly - also be aware of the operations in other threads (?)
    // #TODO data loading procedures need to be sequential
    // and easy to abort/revert/quit/resume
}

/**
 * DEVICE un-pause event
 * (not the GL un-pause event)
 */
void CMainModule::focusGainedEvent(void) {
    FG_LOG_DEBUG("MainModule: Focus gained event");
}
#if defined(FG_USING_MARMALADE)

/**
 * Handle PRESSING and RELEASING keys
 */
void CMainModule::keyStateChangedEvent(s3eKeyboardEvent* event) {
    if(!m_appInit || !m_gameMain)
        return;
    if(event->m_Pressed) {
        m_gameMain->getInputHandler()->addKeyDown((int)event->m_Key);
    } else {
        m_gameMain->getInputHandler()->addKeyUp((int)event->m_Key);
    }
}
#endif /* FG_USING_MARMALADE */

/**
 * Main function that is called when the program starts.
 */
#if defined(FG_USING_MARMALADE)

extern "C" int main() {
    IwUtilInit();
    int argc = 0;
    char *argv[] = {NULL, NULL};
#elif defined(FG_USING_PLATFORM_ANDROID) && defined(FG_USING_SDL2)

extern "C" int SDL_main(int argc, char **argv) {
#else

/**
 * Main function that is called when the program starts.
 * @param argc Number of the arguments passed to the executable
 * @param argv Array containing the arguments
 * @return 
 */
extern "C" int main(int argc, char *argv[]) {
#endif /* FG_USING_MARMALADE */
    FG_LOG_DEBUG("%s: Starting up!", FG_PACKAGE_FULL_TEXT);
    FG_LOG_DEBUG("%s: build %s %s DEBUG", FG_PACKAGE_NAME, FG_BUILD_TIME, FG_BUILD_DATE);
#if defined(FG_RELEASE)
    FG_LOG_INFO("%s: build %s %s RELEASE", FG_PACKAGE_NAME, FG_BUILD_TIME, FG_BUILD_DATE);
#endif
#if defined(FG_DEBUG) && !defined(FG_USING_MARMALADE)
    FG_LOG_DEBUG("%s: Number of arguments: %d", FG_PACKAGE_NAME, argc);
    if(argc) {
        for(int i = 0; i < argc; i++) {
            FG_LOG_DEBUG("%s: ARGV[%d] = '%s'", FG_PACKAGE_NAME, i, argv[i]);
        }
    }
    
#endif
    CMainModule *mainModule = new CMainModule(argc, argv);
    if(!mainModule->initProgram()) {
        mainModule->closeProgram();
        FG_LOG_DEBUG("Deleting main module...");
        delete mainModule;
        FG_LOG_ERROR("Initialization failed, closing program with error");
#if defined(FG_USING_MARMALADE)
        IwUtilTerminate();
        s3eDeviceExit(0);
#endif /* FG_USING_MARMALADE */		
        return 1;
    }
    FG_HardwareState->deviceYield(0);

    while(FG_TRUE) {
        fgBool status = mainModule->mainLoopStep();
        FG_HardwareState->deviceYield(1);
#if defined(FG_USING_MARMALADE)
        s3eDeviceBacklightOn(); // #FIXME // need to wrap it in something else
#endif /* FG_USING_MARMALADE */
        if(status == FG_FALSE || mainModule->isExit()) {
            FG_LOG_DEBUG("Main loop break...");
            break;
        }
    }
    mainModule->closeProgram();
    FG_LOG_DEBUG("Deleting main module...");
    delete mainModule;

    FG_LOG_DEBUG("Successfully closed program");
#if defined FG_USING_MARMALADE
    IwUtilTerminate();
    s3eDeviceExit(0);
#endif /* FG_USING_MARMALADE */
    return 0;
}
#endif
