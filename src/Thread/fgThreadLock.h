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
    #define FG_INC_THREAD_LOCK_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"

    #if defined(FG_USING_THREADS)

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
    class CThreadLock {
    public:
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
        typedef SDL_mutex* NativeHandle;
        #elif defined(FG_USING_PLATFORM_WINDOWS)
        typedef CRITICAL_SECTION NativeHandle;
        #else
        typedef pthread_mutex_t NativeHandle;
        #endif

    public:
        /**
         *
         */
        CThreadLock()
        #if defined(FG_USING_PLATFORM_WINDOWS)
        : m_alreadyLocked(false)
        #endif
        {
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
            m_handle = SDL_CreateMutex();
            if(!m_handle) {
                // ?
            }
        #elif defined(FG_USING_PLATFORM_WINDOWS)
            InitializeCriticalSection(&m_handle);
        #else
            pthread_mutex_init(&m_handle, NULL);
        #endif
        }
        /**
         *
         */
        virtual ~CThreadLock() {
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
            SDL_DestroyMutex(m_handle);
            m_handle = NULL;
        #elif defined(FG_USING_PLATFORM_WINDOWS)
            DeleteCriticalSection(&m_handle);
        #else
            pthread_mutex_destroy(&m_handle);
        #endif
        }
        /**
         *
         */
        inline void lock(void) {
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
            // return: 0, or -1 on error.
            SDL_LockMutex(m_handle);
        #elif defined(FG_USING_PLATFORM_WINDOWS)
            EnterCriticalSection(&m_handle);
            while(m_isLocked) Sleep(1000); // Simulate deadlock...
            m_isLocked = true;
        #else
            pthread_mutex_lock(&m_handle);
        #endif
        }
        /**
         *
         * @return
         */
        inline fgBool tryLock(void) {
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
            // return: 0, SDL_MUTEX_TIMEDOUT, or -1 on error
            return (SDL_TryLockMutex(m_handle) == 0) ? FG_TRUE : FG_FALSE;
        #elif defined(FG_USING_PLATFORM_WINDOWS)
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
        /**
         *
         */
        inline void unlock(void) {
        #if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
            // return: 0, or -1 on error.
            SDL_UnlockMutex(m_handle);
        #elif defined(FG_USING_PLATFORM_WINDOWS)
            m_isLocked = FG_FALSE;
            LeaveCriticalSection(&m_handle);
        #else
            pthread_mutex_unlock(&m_handle);
        #endif
        }

        //_TTHREAD_DISABLE_ASSIGNMENT(mutex)

    private:
        #if defined(FG_USING_PLATFORM_WINDOWS)
        ///
        fgBool m_isLocked;
        #endif
        ///
        NativeHandle m_handle;
    };

    /**
     *
     */
    template <class T>
    class CLockGuard {
    public:
        ///
        typedef T LockType;

    public:
        CLockGuard() : m_lock(0) { }
        /**
         * The constructor locks the mutex
         * @param _lock
         */
        explicit CLockGuard(LockType &_lock) {
            m_lock = &_lock;
            m_lock->lock();
        }
        /**
         * The destructor unlocks the mutex
         */
        ~CLockGuard() {
            if(m_lock)
                m_lock->unlock();
        }

    private:
        ///
        LockType *m_lock;
    };

} // namespace fg

    #endif /* FG_USING_THREADS */

    #undef FG_INC_THREAD_LOCK_BLOCK
#endif /* FG_INC_THREAD_LOCK */
