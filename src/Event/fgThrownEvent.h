/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_THROWN_EVENT_H_
    #define _FG_THROWN_EVENT_H_

    #include "fgEventDefinitions.h"
    #include "fgArgumentList.h"

/**
 *
 */
struct fgThrownEvent {
    ///
    fgEventType eventCode;
    ///
    fgArgumentList *argList;
    ///
    void *systemData;
    
    /**
     * 
     */
    fgThrownEvent() : eventCode(FG_EVENT_INVALID), argList(NULL) { }
    
    /**
     * 
     * @param _eventCode
     * @param _argList
     */
    fgThrownEvent(fgEventType _eventCode, fgArgumentList *_argList) {
        eventCode = _eventCode;
        argList = _argList;
    }
    
    /**
     * 
     * @param _eventCode
     * @param _systemData
     */
    fgThrownEvent(fgEventType _eventCode, void *_systemData) {
        eventCode = _eventCode;
        argList = NULL;
        systemData = _systemData;
    }
};

#endif /* _FG_THROWN_EVENT_H_ */
