/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgThread.h"
#include "fgLog.h"
#include "fgUnistd.h"

#if defined(FG_USING_MARMALADE)
#include "s3eDevice.h"
#endif

#if defined(FG_USING_THREADS)

using namespace fg;
//------------------------------------------------------------------------------

CThread::CThread() :
m_handle(0),
m_isValid(FG_FALSE)
#if defined(FG_USING_PLATFORM_WINDOWS)
, m_win32ID(0)
#endif
{ }
//------------------------------------------------------------------------------

CThread::~CThread() {
    if(isJoinable()) {
#if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
        //this->detach();
#elif defined(FG_USING_PLATFORM_WINDOWS)

#elif defined(FG_USING_MARMALADE)
        s3eDeviceRequestQuit();
#else
        std::terminate();
#endif
    }
}
//------------------------------------------------------------------------------

CThread::CThread(ThreadStartFuncPtr startFunction, void *arg) {
    setFunction(startFunction, arg);
}
//------------------------------------------------------------------------------

fgBool CThread::setFunction(ThreadStartFuncPtr startFunction, void* arg) {
    if(!startFunction)
        return FG_FALSE;
    // Serialize access to this thread structure
    CLockGuard<CThreadLock> guard(m_dataLock);

    SThreadStartInfo *info = new SThreadStartInfo();
    info->startFunction = startFunction;
    info->arg = arg;
    info->thread = this;
    m_isValid = FG_TRUE;

#if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
    m_handle = SDL_CreateThread(CThread::wrapperFunc, "newThreadFIXME", (void*)info);
    if(!m_handle) {
        FG_LOG_ERROR("Thread: Failed to create new thread: '%s'", SDL_GetError());
    }
#elif defined(FG_USING_PLATFORM_WINDOWS)
    mHandle = (HANDLE)_beginthreadex(0, 0, CThread::wrapperFunc, (void *)info, 0, &m_win32ID);
#else
    if(pthread_create(&m_handle, NULL, CThread::wrapperFunc, (void*)info) != 0) {
        m_handle = 0;
    }
#endif
    if(!m_handle) {
        m_isValid = FG_FALSE;
        delete info;
    }
    return m_isValid;
}
//------------------------------------------------------------------------------

void CThread::join(void) {
    if(isJoinable()) {
#if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
        int threadReturnVal;
        SDL_WaitThread(m_handle, &threadReturnVal);
#elif defined(FG_USING_PLATFORM_WINDOWS)
        WaitForSingleObject(m_handle, INFINITE);
        CloseHandle(m_handle);
#else
        pthread_join(m_handle, NULL);
#endif
    }
}
//------------------------------------------------------------------------------

fgBool CThread::isJoinable(void) const {
    m_dataLock.lock();
    fgBool result = m_isValid;
    m_dataLock.unlock();
    return result;
}
//------------------------------------------------------------------------------

void CThread::detach(void) {
    m_dataLock.lock();
    if(m_isValid) {
#if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
        SDL_DetachThread(m_handle);
#elif defined(FG_USING_PLATFORM_WINDOWS)
        CloseHandle(m_handle);
#else
        pthread_detach(m_handle);
#endif
        m_isValid = FG_FALSE;
    }
    m_dataLock.unlock();
}
//------------------------------------------------------------------------------

unsigned int CThread::hwConcurrency(void) {
#if defined(FG_USING_PLATFORM_WINDOWS)
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (int)si.dwNumberOfProcessors;
#elif defined(_SC_NPROCESSORS_ONLN)
    return (int)sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROC_ONLN)
    return (int)sysconf(_SC_NPROC_ONLN);
#else
    // The standard requires this function to return zero if the number of
    // hardware cores could not be determined.
    return 0;
#endif
}
//------------------------------------------------------------------------------

#if defined(FG_USING_SDL2) || defined(FG_USING_SDL)
int CThread::wrapperFunc(void *_arg)
#elif defined(FG_USING_PLATFORM_WINDOWS)
unsigned WINAPI CThread::wrapperFunc(void *_arg)
#else

void *CThread::wrapperFunc(void *_arg)
#endif
{
    if(!_arg)
        return NULL;
    SThreadStartInfo *info = (SThreadStartInfo*)_arg;
    if(!info->startFunction || !info->thread)
        return NULL;
    info->startFunction(info->arg);

    // The thread is no longer executing
    CLockGuard<CThreadLock> guard(info->thread->m_dataLock);
    info->thread->m_isValid = FG_FALSE;

    delete info;
    return NULL;
}
//------------------------------------------------------------------------------

#endif /* defined(FG_USING_THREADS) */ 
