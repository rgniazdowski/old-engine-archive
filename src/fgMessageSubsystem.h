/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_MESSAGE_SUBSYSTEM_H_
    #define _FG_MESSAGE_SUBSYSTEM_H_

    #include "fgCommon.h"
    #include "fgSingleton.h"
    #include "fgStatus.h"
    #include "fgManagerBase.h"

    #include <stack>
    #include <map>
    #include "fgVector.h"
    #include "Util/fgFile.h"

    #include "fgLog.h"

/*
 *
 */
class fgMessageSubsystem : protected fgManagerBase, public fgSingleton<fgMessageSubsystem> {
    friend class fgSingleton<fgMessageSubsystem>;
protected:
    typedef fgVector<fgStatus *> msStatusVec;
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
    fgBool destroy(void);

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
