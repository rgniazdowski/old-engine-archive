/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_THREAD_H_
    #define _FG_THREAD_H_

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #ifdef FG_USING_THREADS

        #include "fgThreadLock.h"

//#ifdef FG_USING_MARMALADE_THREADS
//#include "s3eThread.h"
//#endif
        #if defined(FG_USING_PLATFORM_WINDOWS)
        #else
            #include <pthread.h>
            #include <sched.h>
        #endif

/*
 *
 */
class fgThread {
public:
        #if defined(FG_USING_PLATFORM_WINDOWS)
    typedef HANDLE nativeHandle;
        #else
    typedef pthread_t nativeHandle;
        #endif
        #if __cplusplus > 199711L
    using threadStartFuncPtr = void* (*)(void);
        #else
    typedef void* (*threadStartFuncPtr)(void*);
        #endif
protected:

    struct threadStartInfo {
        threadStartFuncPtr startFunction;
        fgThread *thread;
        void *arg;
        threadStartInfo() :
        startFunction(NULL),
        thread(NULL),
        arg(NULL) { }
    };
public:
    //
    fgThread();
    //
    virtual ~fgThread();

    //
    fgThread(threadStartFuncPtr startFunction, void *arg);


    //
    void join(void);
    //
    fgBool isJoinable(void) const;
    //
    void detach(void);

    //
    inline nativeHandle getHandle(void) {
        return m_handle;
    }

    //
    static unsigned int hwConcurrency();

private:
    ///
    nativeHandle m_handle;
    ///
    fgBool m_isValid;
    ///
    mutable fgThreadLock m_dataLock;
        #if defined(FG_USING_PLATFORM_WINDOWS)
    ///
    unsigned int m_win32ID;
    //
    static unsigned WINAPI wrapperFunc(void *_arg);
        #else
    //
    static void *wrapperFunc(void *_arg);
        #endif
};

    #endif
#endif /* _FG_THREAD_H_ */
