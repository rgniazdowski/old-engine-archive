/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_THREAD_LOCK
    #define FG_INC_THREAD_LOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #ifdef FG_USING_THREADS

        #include <pthread.h>
        #include <sched.h>

class fgThreadLock {
public:
        #if defined(FG_USING_PLATFORM_WINDOWS)
    typedef CRITICAL_SECTION nativeHandle;
        #else
    typedef pthread_mutex_t nativeHandle;
        #endif

public:
    fgThreadLock()
        #if defined(FG_USING_PLATFORM_WINDOWS)
    : m_alreadyLocked(false)
        #endif
    {
        #if defined(FG_USING_PLATFORM_WINDOWS)
        InitializeCriticalSection(&m_handle);
        #else
        pthread_mutex_init(&m_handle, NULL);
        #endif
    }
    ~fgThreadLock() {
        #if defined(FG_USING_PLATFORM_WINDOWS)
        DeleteCriticalSection(&m_handle);
        #else
        pthread_mutex_destroy(&m_handle);
        #endif
    }
    inline void lock() {
        #if defined(FG_USING_PLATFORM_WINDOWS)
        EnterCriticalSection(&m_handle);
        while(m_isLocked) Sleep(1000); // Simulate deadlock...
        m_isLocked = true;
        #else
        pthread_mutex_lock(&m_handle);
        #endif
    }
    inline fgBool tryLock() {
        #if defined(FG_USING_PLATFORM_WINDOWS)
        fgBool status = (TryEnterCriticalSection(&mHandle) ? FG_TRUE : FG_FALSE);
        if(ret && m_isLocked) {
            LeaveCriticalSection(&m_handle);
            status = FG_FALSE;
        }
        return status;
        #else
        return (pthread_mutex_trylock(&m_handle) == 0) ? FG_TRUE : FG_FALSE;
        #endif
    }
    inline void unlock() {
        #if defined(FG_USING_PLATFORM_WINDOWS)
        m_isLocked = FG_FALSE;
        LeaveCriticalSection(&m_handle);
        #else
        pthread_mutex_unlock(&m_handle);
        #endif
    }

    //_TTHREAD_DISABLE_ASSIGNMENT(mutex)

private:
        #if defined(FG_USING_PLATFORM_WINDOWS)
    fgBool m_isLocked;
        #endif
    nativeHandle m_handle;
};

template <class T>
class fgLockGuard {
public:
    typedef T lockType;
    fgLockGuard() : m_lock(0) { }

    // The constructor locks the mutex.
    explicit fgLockGuard(lockType &_lock) {
        m_lock = &_lock;
        m_lock->lock();
    }

    // The destructor unlocks the mutex
    ~fgLockGuard() {
        if(m_lock)
            m_lock->unlock();
    }

private:
    lockType *m_lock;
};

    #endif
#endif /* FG_INC_THREAD_LOCK */
