/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgMessageSubsystem.h"

template <>
bool fgSingleton<fgMessageSubsystem>::instanceFlag = false;

template <>
fgMessageSubsystem *fgSingleton<fgMessageSubsystem>::instance = NULL;


/** \brief
 */
fgMessageSubsystem::fgMessageSubsystem()
{
}

/** \brief
 */
fgMessageSubsystem::~fgMessageSubsystem()
{
	destroy();
}

/** \brief
 */
void fgMessageSubsystem::clear(void) {
	flushAll();
}


/** \brief
 */
fgBool fgMessageSubsystem::destroy(void) 
{
	flushAll();

	m_logAll.close();
	m_logError.close();
	m_logDebug.close();
	return FG_TRUE;
}

/** \brief
 *
 * \return fgBool
 *
 */
fgBool fgMessageSubsystem::initialize(void) {
	return FG_TRUE;
}

/** \brief
 *
 * \param pathAll const char*
 * \param pathError const char*
 * \param pathDebug const char*
 * \return void
 *
 */
void fgMessageSubsystem::setLogPaths(const char *pathAll, const char *pathError, const char *pathDebug)
{
	setLogAllPath(pathAll);
	setLogErrorPath(pathError);
	setLogDebugPath(pathDebug);
}

/** \brief
 *
 * \param pathAll const char*
 * \return void
 *
 */
void fgMessageSubsystem::setLogAllPath(const char *pathAll)
{
	if(pathAll)
		m_logAll.setPath(pathAll);
	m_logAll.setMode(FG_FILE_MODE_APPEND);
}

/** \brief
 *
 * \param pathError const char*
 * \return void
 *
 */
void fgMessageSubsystem::setLogErrorPath(const char *pathError)
{
	if(pathError)
		m_logError.setPath(pathError);
	m_logError.setMode(FG_FILE_MODE_APPEND);
}

/** \brief
 *
 * \param pathDebug const char*
 * \return void
 *
 */
void fgMessageSubsystem::setLogDebugPath(const char *pathDebug)
{
	if(pathDebug)
		m_logDebug.setPath(pathDebug);
	m_logDebug.setMode(FG_FILE_MODE_APPEND);
}

/** \brief
 */
void fgMessageSubsystem::flushAll(void)
{
	while(!m_statusVec.empty()) {
		fgStatus *back = m_statusVec.back();
		back->clearMessage();
		delete back;
		m_statusVec.pop_back();
	}
	m_statusVec.clear_optimised();
}

/** \brief
 *
 * \param msg fgMessage*
 * \return fgBool
 *
 */
fgBool fgMessageSubsystem::pushMessage(fgMessage *msg)
{
	if(!msg)
		return FG_FALSE;

	msg->setManaged();
	fgStatus *newStatus = new fgStatus(msg);
	return pushStatus(newStatus);
}

/** \brief
 *
 * \param status fgStatus*
 * \return fgBool
 *
 */
fgBool fgMessageSubsystem::pushStatus(fgStatus *status)
{
	if(!status)
		return FG_FALSE;
	status->setManaged();
	m_statusVec.push_back(status);
	if(status->message)
	{
		fgFile *filePtr = NULL;
		switch (status->message->type)
		{
		case FG_MESSAGE_DEBUG:
			filePtr = &m_logDebug;
			break;
		case FG_MESSAGE_ERROR:
			filePtr = &m_logError;
			break;
		default:
			break;
		}

		FG_LOG::PrintStatus(status);
		// #FIXME #TODO - buffering messages, cyclic writing to log files (but always to console output)
		// Warning, Info, Debug, Error
		FG_LOG::PrintStatusToLog(&m_logAll, status);
		// Debug or Error
		if(filePtr)
			FG_LOG::PrintStatusToLog(filePtr, status);
	}
	return FG_TRUE;
}

/** \brief
 *
 * \return fgStatus *
 *
 */
fgStatus *fgMessageSubsystem::getLastStatus(void)
{
	if(!m_statusVec.empty()) {
		return m_statusVec.back();
	}
	return NULL;
}

/** \brief
 *
 * \return fgMessage *
 *
 */
fgMessage *fgMessageSubsystem::getLastMessage(void)
{
	if(!m_statusVec.empty()) {
		fgStatus *status = m_statusVec.back();
		if(status->message)
			return status->message;
	}
	return NULL;
}
