/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_THREAD
    #define FG_INC_THREAD
    #define FG_INC_THREAD_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"

    #if defined(FG_USING_THREADS)

        #include "fgThreadLock.h"

//#ifdef FG_USING_MARMALADE_THREADS
//#include "s3eThread.h"
//#endif
        #if defined(FG_USING_SDL2)
            #include <SDL2/SDL_thread.h>
            #include <SDL2/SDL_mutex.h>
        #elif defined(FG_USING_SDL)
            #include <SDL/SDL_thread.h>
            #include <SDL/SDL_mutex.h>
        #elif defined(FG_USING_PLATFORM_WINDOWS)
        #else
            #include <pthread.h>
            #include <sched.h>
        #endif

namespace fg {
/**
 *
 */
class CThread {
public:
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
    typedef SDL_Thread* NativeHandle;
        #elif defined(FG_USING_PLATFORM_WINDOWS)
    typedef HANDLE NativeHandle;
        #else
    typedef pthread_t NativeHandle;
        #endif
        #if __cplusplus > 199711L
    using ThreadStartFuncPtr = void* (*)(void *);
        #else
    typedef void* (*ThreadStartFuncPtr)(void *);
        #endif
protected:

    /**
     *
     */
    struct SThreadStartInfo {
        ///
        ThreadStartFuncPtr startFunction;
        ///
        CThread *thread;
        ///
        void *arg;
        /**
         * 
         */
        SThreadStartInfo() :
        startFunction(NULL),
        thread(NULL),
        arg(NULL) { }
    };
public:
    /**
     * 
     */
    CThread();
    /**
     *
     */
    virtual ~CThread();

    /**
     *
     * @param startFunction
     * @param arg
     */
    CThread(ThreadStartFuncPtr startFunction, void *arg);

    //------------------------------------------------------------------------------

    /**
     * 
     * @param startFunction
     * @param arg
     * @return
     */
    fgBool setFunction(ThreadStartFuncPtr startFunction, void *arg);

    /**
     *
     */
    void join(void);
    /**
     *
     * @return
     */
    fgBool isJoinable(void) const;
    /**
     *
     */
    void detach(void);
    /**
     *
     * @return
     */
    inline NativeHandle getHandle(void) {
        return m_handle;
    }

    /**
     *
     * @return
     */
    static unsigned int hwConcurrency(void);

private:
    ///
    NativeHandle m_handle;
    ///
    fgBool m_isValid;
    ///
    mutable CThreadLock m_dataLock;
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
    static int wrapperFunc(void *_arg);
        #elif defined(FG_USING_PLATFORM_WINDOWS)
    ///
    unsigned int m_win32ID;
    //
    static unsigned WINAPI wrapperFunc(void *_arg);
        #else
    //
    static void *wrapperFunc(void *_arg);
        #endif
    };

} // namespace fg

    #endif /* FG_USING_THREADS */

    #undef FG_INC_THREAD_BLOCK
#endif /* FG_INC_THREAD */
