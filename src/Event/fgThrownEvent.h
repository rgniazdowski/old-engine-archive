/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_THROWN_EVENT
    #define FG_INC_THROWN_EVENT

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
    fgThrownEvent(fgEventType _eventCode = FG_EVENT_INVALID) :
    eventCode(_eventCode), 
    argList(NULL), 
    systemData(NULL) { }
    /**
     * 
     * @param _eventCode
     * @param _argList
     */
    fgThrownEvent(fgEventType _eventCode, fgArgumentList *_argList) :
    eventCode(_eventCode),
    argList(_argList),
    systemData(NULL) { }
    /**
     * 
     * @param _eventCode
     * @param _systemData
     */
    fgThrownEvent(fgEventType _eventCode, void *_systemData) :
    eventCode(_eventCode),
    argList(NULL),
    systemData(_systemData) { }
};

#endif /* FG_INC_THROWN_EVENT */
