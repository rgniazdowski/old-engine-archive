/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgThread.h"
#if defined(FG_USING_MARMALADE)
#include "s3eDevice.h"
#endif

#if defined(FG_USING_THREADS)

/*
 *
 */
fgThread::fgThread() :
	m_handle(0),
	m_isValid(FG_FALSE)
#if defined(FG_USING_PLATFORM_WINDOWS)
	,m_win32ID(0)
#endif
{
}

/*
 *
 */
fgThread::~fgThread()
{
	if(isJoinable()) {
#if defined(FG_USING_MARMALADE)
		s3eDeviceRequestQuit();
#else
		std::terminate();
#endif
	}
}

/*
 *
 */
fgThread::fgThread(threadStartFuncPtr startFunction, void *arg)
{
	// Serialize access to this thread structure
	fgLockGuard<fgThreadLock> guard(m_dataLock);

	threadStartInfo *info = new threadStartInfo();
	info->startFunction = startFunction;
	info->arg = arg;
	info->thread = this;
	m_isValid = FG_TRUE;

#if defined(FG_USING_PLATFORM_WINDOWS)
	mHandle = (HANDLE)_beginthreadex(0, 0, fgThread::wrapperFunc, (void *)info, 0, &m_win32ID);
#else
	if(pthread_create(&m_handle, NULL, fgThread::wrapperFunc, (void *)info) != 0) {
		m_handle = 0;
	}
#endif

	if(!m_handle) {
		m_isValid = FG_FALSE;
		delete info;
	}
}

/*
 *
 */
void fgThread::join(void)
{
	if(isJoinable()) {
#if defined(FG_USING_PLATFORM_WINDOWS)
		WaitForSingleObject(m_handle, INFINITE);
		CloseHandle(m_handle);
#else
		pthread_join(m_handle, NULL);
#endif
	}
}

/*
 *
 */
fgBool fgThread::isJoinable(void) const
{
	m_dataLock.lock();
	fgBool result = m_isValid;
	m_dataLock.unlock();
	return result;
}

/*
 *
 */
void fgThread::detach(void)
{
	m_dataLock.lock();
	if(m_isValid)
	{
#if defined(FG_USING_PLATFORM_WINDOWS)
		CloseHandle(m_handle);
#else
		pthread_detach(m_handle);
#endif
		m_isValid = FG_FALSE;
	}
	m_dataLock.unlock();
}

/*
 *
 */
unsigned int fgThread::hwConcurrency()
{
#if defined(FG_USING_PLATFORM_WINDOWS)
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return (int) si.dwNumberOfProcessors;
#elif defined(_SC_NPROCESSORS_ONLN)
	return (int) sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROC_ONLN)
	return (int) sysconf(_SC_NPROC_ONLN);
#else
	// The standard requires this function to return zero if the number of
	// hardware cores could not be determined.
	return 0;
#endif
}

/*
 *
 */
#if defined(FG_USING_PLATFORM_WINDOWS)
unsigned WINAPI fgThread::wrapperFunc(void *_arg)
#else
void *fgThread::wrapperFunc(void *_arg)
#endif
{
	if(!_arg)
		return NULL;
	threadStartInfo *info = (threadStartInfo*) _arg;
	if(!info->startFunction || !info->thread)
		return NULL;
	info->startFunction(info->arg);

	// The thread is no longer executing
	fgLockGuard<fgThreadLock> guard(info->thread->m_dataLock);
	info->thread->m_isValid = FG_FALSE;

	delete info;
	return NULL;
}

#endif /* defined(FG_USING_THREADS) */ 
