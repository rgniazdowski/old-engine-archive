/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_MESSAGE_SUBSYSTEM
    #define FG_INC_MESSAGE_SUBSYSTEM

    #include "fgCommon.h"
    #include "fgSingleton.h"
    #include "fgStatus.h"
    #include "fgManagerBase.h"

    #include <stack>    
    #include "fgVector.h"
    #include "Util/fgRegularFile.h"

    #include "fgLog.h"

/**
 *
 */
class fgMessageSubsystem : protected fg::base::CManager, public fgSingleton<fgMessageSubsystem> {
    friend class fgSingleton<fgMessageSubsystem>;
    
public:
    typedef fg::base::CManager base_type;
    
protected:
    ///
    typedef fg::CVector<fgStatus *> msStatusVec;
    ///
    typedef msStatusVec::iterator msStatusVecItor;

protected:
    /**
     * 
     */
    fgMessageSubsystem();
    /**
     * 
     */
    virtual ~fgMessageSubsystem();

public:
    /**
     * 
     * @return 
     */
    fgBool initialize(void);
    /**
     * 
     */
    void clear(void);
    /**
     * 
     * @return 
     */
    fgBool destroy(void);

    /**
     * 
     * @param pathAll
     * @param pathError
     * @param pathDebug
     */
    void setLogPaths(const char *pathAll, const char *pathError, const char *pathDebug);
    /**
     * 
     * @param pathAll
     */
    void setLogAllPath(const char *pathAll);
    /**
     * 
     * @param pathError
     */
    void setLogErrorPath(const char *pathError);
    /**
     * 
     * @param pathDebug
     */
    void setLogDebugPath(const char *pathDebug);
    /**
     * 
     */
    void flushAll(void);

    /**
     * 
     * @param msg
     * @return 
     */
    fgBool pushMessage(fgMessage *msg);
    /**
     * 
     * @param status
     * @return 
     */
    fgBool pushStatus(fgStatus *status);

    /**
     * 
     * @return 
     */
    fgStatus *getLastStatus(void);
    /**
     * 
     * @return 
     */
    fgMessage *getLastMessage(void);

    /**
     * 
     * @return 
     */
    msStatusVec const & getStatusVec(void) const {
        return m_statusVec;
    }
    
    /**
     * 
     * @param tagName
     * @param code
     * @param fmt     
     */
    void reportSuccess(const char *tagName, int code = FG_ERRNO_OK, const char *fmt = NULL, ...);
    /**
     * 
     * @param tagName
     * @param code
     * @param fmt     
     */
    void reportWarning(const char *tagName, int code = FG_ERRNO_OK, const char *fmt = NULL, ...);
    /**
     * 
     * @param tagName
     * @param code
     * @param fmt     
     */
    void reportError(const char *tagName, int code = FG_ERRNO_OK, const char *fmt = NULL, ...);
    /**
     * 
     * @param tagName
     * @param code
     * @param fmt     
     */
    void reportDebug(const char *tagName, int code = FG_ERRNO_OK, const char *fmt = NULL, ...);

protected:
    //
    msStatusVec m_statusVec;
    //
    fg::util::CRegularFile m_logAll;
    //
    fg::util::CRegularFile m_logError;
    //
    fg::util::CRegularFile m_logDebug;
};

// #FIXME - here we go again with the singletons... :)
    #define FG_MessageSubsystem fgMessageSubsystem::getInstance()

#endif /* FG_INC_MESSAGE_SUBSYSTEM */
