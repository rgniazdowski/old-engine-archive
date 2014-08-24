/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_MESSAGE_SUBSYSTEM_H_
#define _FG_MESSAGE_SUBSYSTEM_H_

#include "fgCommon.h"
#include "fgSingleton.h"
#include "fgManagerBase.h"

#include "fgStatus.h"

#include <stack>
#include <map>
#include "fgArrayVector.h"
#include "Util/fgFile.h"

#include "fgLog.h"

/*
 *
 */
class fgMessageSubsystem : public fgManagerBase, public fgSingleton<fgMessageSubsystem>
{
	friend class fgSingleton<fgMessageSubsystem>;
protected:
	typedef fgArrayVector<fgStatus *> msStatusVec;
	typedef msStatusVec::iterator msStatusVecItor;

protected:
	// 
	fgMessageSubsystem();
	// 
	virtual ~fgMessageSubsystem();

public:
	// 
	fgBool initialize(void);
	// 
	void clear(void);
	// 
	void destroy(void);

	//
	void setLogPaths(const char *pathAll, const char *pathError, const char *pathDebug);
	// 
	void setLogAllPath(const char *pathAll);
	// 
	void setLogErrorPath(const char *pathError);
	// 
	void setLogDebugPath(const char *pathDebug);
	// 
	void flushAll(void);

	// 
	fgBool pushMessage(fgMessage *msg);
	// 
	fgBool pushStatus(fgStatus *status);

	// 
	fgStatus *getLastStatus(void);
	// 
	fgMessage *getLastMessage(void);

protected:
	//
	msStatusVec m_statusVec;
	//
	fgFile m_logAll;
	//
	fgFile m_logError;
	//
	fgFile m_logDebug;
};

// #FIXME - here we go again with the singletons... :)
#define FG_MessageSubsystem fgMessageSubsystem::getInstance()

#endif /* _FG_MESSAGE_SUBSYSTEM_H_ */
