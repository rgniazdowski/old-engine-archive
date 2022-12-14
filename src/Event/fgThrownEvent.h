/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_THROWN_EVENT
    #define FG_INC_THROWN_EVENT
    #define FG_INC_THROWN_EVENT_BLOCK

    #include "fgEventDefinitions.h"
    #include "fgArgumentList.h"

namespace fg {
    namespace event {

        /**
         *
         */
        struct SThrownEvent {
            ///
            EventType eventCode;
            ///
            CArgumentList *argList;
            ///
            void *systemData;
            /**
             * 
             */
            SThrownEvent(EventType _eventCode = event::INVALID) :
            eventCode(_eventCode),
            argList(NULL),
            systemData(NULL) { }
            /**
             * 
             * @param _eventCode
             * @param _argList
             */
            SThrownEvent(EventType _eventCode, CArgumentList *_argList) :
            eventCode(_eventCode),
            argList(_argList),
            systemData(NULL) { }
            /**
             * 
             * @param _eventCode
             * @param _systemData
             */
            SThrownEvent(EventType _eventCode, void *_systemData) :
            eventCode(_eventCode),
            argList(NULL),
            systemData(_systemData) { }
        };

    };

};

    #undef FG_INC_THROWN_EVENT_BLOCK
#endif /* FG_INC_THROWN_EVENT */
