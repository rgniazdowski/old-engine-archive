/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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
#include "Event/fgInputHandler.h"
#include "Hardware/fgHardwareState.h"
#include "Util/fgProfiling.h"
#include "fgDebugConfig.h"

#if defined(FG_USING_MARMALADE)
#include "Hardware/fgDeviceQuery.h"
#endif /* FG_USING_MARMALADE */

class MainModule;
extern float guiScale;
#if defined(FG_USING_MARMALADE)
extern "C" int main();

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
#else
extern "C" int main(int argc, char *argv[]);
#endif /* FG_USING_MARMALADE */

/**
 *
 */
class MainModule
{
#if defined FG_USING_MARMALADE
    friend class fgMarmaladeHandlers;
    friend int main();
#else
    friend int main(int argc, char *argv[]);
#endif /* FG_USING_MARMALADE */
protected:

    /**
     * Initialize main module
     */
    MainModule(int argc, char *argv[]) :
    m_argc(argc),
    m_argv(argv),
    m_appInit(FG_FALSE),
    m_slow(FG_FALSE),
    m_isExit(FG_FALSE),
#if defined(FG_USING_MARMALADE) // #FIXME
    m_deviceQuery(),
#endif /* FG_USING_MARMALADE */
    m_gameMain(NULL) { }

protected:
#if defined(FG_USING_SDL2)

    /**
     * #FIXME - this needs to be maintained differently
     * - maybe add some SDL2 event watches?
     * @return 
     */
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
                    guiScale += 0.05f * (float)event.wheel.y;
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
                    CJoypadController *joypadController = this->m_gameMain->getJoypadController();
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
                        fg::event::CJoypadController *joypadController = this->m_gameMain->getJoypadController();
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

    /**
     * 
     * @return 
     */
    fgBool isSlow(void) const {
        return m_slow;
    }

    /**
     * 
     * @return 
     */
    fgBool isExit(void) const {
        return m_isExit;
    }
private:

    /**
     * 
     * @param slow
     */
    void setSlow(fgBool slow) {
        m_slow = slow;
    }

    /**
     * 
     * @param exit
     */
    void setExit(fgBool exit) {
        m_isExit = exit;
    }

    /**
     * Called when a fullscreen window with an OpenGL context
     * has been created and is ready to be used.
     * 
     * @return 
     */
    fgBool initProgram() {
        fgTime::init(); // #FIXME global time init?
#if defined(FG_DEBUG)
        g_debugProfiling = new fgProfiling();
        g_debugProfiling->initialize();
#endif
        float t1 = fgTime::ms();
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
            m_gameMain = new fgGameMain(m_argc, m_argv);
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
        m_appInit = FG_TRUE;
        float t2 = fgTime::ms();
        FG_LOG_DEBUG("Main: Program initialized in %.2f seconds", (t2 - t1) / 1000.0f);
        return FG_TRUE;
    }

    /**
     * Applications main loop step (one thread)
     */
    fgBool mainLoopStep() {
        FG_HardwareState->deviceYield(0);
        if(!m_appInit) {
            return FG_FALSE;
        }
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->begin("Program::loopStep");
        }
#endif
        // #FIXME
#if defined(FG_USING_SDL2)
        if(checkSDLEvents() == SDL_QUIT) {
            return FG_FALSE;
        }
#endif

#if defined(FG_USING_MARMALADE)
        s3eKeyboardUpdate();
        if(s3eDeviceCheckQuitRequest()) {
            m_appInit = FG_FALSE;
            return FG_FALSE;
        }
        if(s3eKeyboardGetState(s3eKeyEnter) & S3E_KEY_STATE_PRESSED) {
            m_appInit = FG_FALSE;
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
            g_debugProfiling->begin("Game::update");
        }
#endif
        FG_HardwareState->deviceYield(0);
        m_gameMain->update();
        FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->end("Game::update");
            g_debugProfiling->begin("Game::display");
        }
#endif
        // well for now drawing and all update functions will be called in one place (one thread)
        // however it needs changing
        m_gameMain->display();
        FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->end("Game::display");
            g_debugProfiling->begin("Game::render");
        }
#endif
        FG_HardwareState->deviceYield();
        m_gameMain->render();
        FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
        static int loopCount = 0;
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->end("Game::render");
            g_debugProfiling->end("Program::loopStep");
            g_debugProfiling->updateHistory();

            loopCount++;
            if(loopCount > 20) {
                loopCount = 0;
                g_debugProfiling->dumpToDefaultFile();
            }
        }
#endif
        return FG_TRUE;
    }

    /**
     * The way to exit from the application
     */
    void closeProgram() {
        FG_LOG_DEBUG("Closing program...");
        // This frees all the data used by singletons and other nonresource data
        // after that only things left to free are FG_GameMain and MainModule
        if(m_gameMain) {
            m_gameMain->closeSybsystems();
            delete m_gameMain;
        }
        m_gameMain = NULL;
        m_appInit = FG_FALSE;
#if defined(FG_DEBUG)
        if(g_debugProfiling)
            delete g_debugProfiling;
        g_debugProfiling = NULL;
        //g_debugProfiling->clear();
#endif
    }

private:

    /**
     * DEVICE PAUSE event
     */
    void suspendGfxEvent(void) {
        FG_LOG_DEBUG(">>> SUSPEND GFX SUBSYSTEM <<<");
        if(m_gameMain)
            m_gameMain->getGfxMain()->suspendGFX();
    }

    /**
     * DEVICE unpause event
     */
    void resumeGfxEvent(void) {
        FG_LOG_DEBUG(">>> RESUME GFX SUBSYSTEM <<<");
        if(m_gameMain)
            m_gameMain->getGfxMain()->resumeGFX();
    }

    /**
     * DEVICE PAUSE event
     * (not the GL pause event)
     */
    void focusLostEvent(void) {
        FG_LOG_DEBUG(">>> FOCUS LOST EVENT <<<");

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
        FG_LOG_DEBUG(">>> FOCUS GAINED EVENT <<<");
    }
#if defined(FG_USING_MARMALADE)

    /**
     * Handle PRESSING and RELEASING keys
     */
    void keyStateChangedEvent(s3eKeyboardEvent* event) {
        if(!m_appInit || !m_gameMain)
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
			m_gameMain->getInputHandler()->addKeyDown((int)event->m_Key);
        } else {
			m_gameMain->getInputHandler()->addKeyUp((int)event->m_Key);
        }
        //FG_LOG_DEBUG("FG_EventManager - keyboard - %d is pressed? - code: %d", (int)event->m_Pressed, (int)event->m_Key);
    }
#endif /* FG_USING_MARMALADE */

private:
    /// Number of arguments passed to program
    int m_argc;
    /// Array of arguments passed to program
    char **m_argv;
    /// Is app fully initialized?
    fgBool m_appInit;
    /// Is the device slow?
    fgBool m_slow;
    /// Is exit activated?
    fgBool m_isExit;
#if defined(FG_USING_MARMALADE) // #FIXME
    ///
    fgDeviceQuery m_deviceQuery;
#endif /* FG_USING_MARMALADE */
    /// Game main class - this is for initialization procedures
    /// contains also functions for handling events, drawing, etc #TODO
    /// Needs refactoring, some level of merging within main module or
    /// changing name to fgApplication - or extending fgApplication class
    /// #TODO - support threads
    fgGameMain *m_gameMain;
};

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
#if defined FG_USING_MARMALADE

extern "C" int main() {
    IwUtilInit();
    int argc = 0;
    char *argv[] = {NULL, NULL};
#else

extern "C" int main(int argc, char *argv[]) {
#endif /* FG_USING_MARMALADE */
    //IwMemBucketDebugSetBreakpoint(1551);
    FG_LOG_DEBUG("%s: Start up", FG_PACKAGE_FULL_TEXT);
#if defined(FG_DEBUG) && !defined(FG_USING_MARMALADE)
    char str_args[2048];
    FG_LOG_DEBUG("%s: Number of arguments: %d", FG_PACKAGE_NAME, argc);
#endif
    MainModule *mainModule = new MainModule(argc, argv);
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
        if(status == FG_FALSE) {
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
