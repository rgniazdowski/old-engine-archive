/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_EVENT_MANAGER
    #define FG_INC_EVENT_MANAGER
    #define FG_INC_EVENT_MANAGER_BLOCK

    #include "fgBuildConfig.h"
    #include "fgTypes.h"
    #include "fgManagerBase.h"

    #include "fgEventDefinitions.h"
    #include "fgEventHelper.h"
    #include "fgThrownEvent.h"
    #include "fgTimeoutCallback.h"
    #include "fgCyclicCallback.h"

    #include "fgCallback.h"

// #FIXME #TODO #P3 key codes standard mapping / translation
// #TODO #P2 change std::vector to standard FG shadow type
// #TODO #P4 make event manager thread friendly / multi-thread support

/* EXAMPLE OF USE 
        KeyboardEvent *event = new KeyboardEvent(keyCode);
        event->m_pressed = true;
        ArgumentList *argv = new ArgumentList();
        argv->pushArgument(POINTER, (void *)keyboardEvent);
        throwEvent(KEYBOARD_DOWN, argv);
        ArgumentList *argv = new ArgumentList();
        argv->pushArgument(POINTER, (void *)getWidgetByName("buttonNewGame"));
        throwEvent(BUTTON_CLICKED, argv);
 */

    #define FG_MANAGER_EVENT        0x00000008

namespace fg {
    namespace event {

        /**
         * Event manager main class definition.
         */
        class CEventManager : public fg::base::CManager {
        private:
            /// int - eventCode
            /// Binding for all global events
            fgCallbackBindingMap m_eventBinds;
            /// Events queue (message queue so to speak)
            fgEventsQueue m_eventsQueue;
            /// Special pool with timeout callbacks (timers)
            fgTimeoutCallbacksVec m_timeoutCallbacks;
            /// Pool with cyclic timeout callbacks (repeat timers, self reset)
            fgCyclicCallbacksVec m_cyclicCallbacks;

        public:
            /**
             * Default constructor for Event Manager object
             */
            CEventManager();
            /**
             * Default destructor for Event Manager object
             */
            virtual ~CEventManager();

        protected:
            /**
             * 
             */
            virtual void clear(void);

        public:

            /**
             * Initialize the Event Manager object
             * @return 
             */
            virtual fgBool initialize(void);

            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);

            /**
             * 
             * @param eventCode
             */
            void throwEvent(fgEventType eventCode);

            /**
             * This adds event to the waiting queue, the *list object needs to be allocated before,
             * after event callback execution argument list must be freed
             * @param eventCode
             * @param list
             */
            void throwEvent(fgEventType eventCode,
                            fgArgumentList *list);

            /**
             * 
             * @param eventCode
             * @param pSystemData
             */
            void throwEvent(fgEventType eventCode,
                            void *pSystemData);

            /**
             * 
             * @param eventCode
             * @param pCallback
             * @return 
             */
            fgFunctionCallback* addEventCallback(fgEventType eventCode,
                                                 fgFunctionCallback *pCallback);
            /**
             * 
             * @param eventCode
             * @param pFunction
             * @return 
             */
            fgFunctionCallback* addEventCallback(fgEventType eventCode,
                                                 fgFunctionCallback::fgFunction pFunction);

            /**
             * 
             * @param eventCode
             * @param pPlainFunction
             * @param pUserData
             * @return 
             */
            fgFunctionCallback* addEventCallback(fgEventType eventCode,
                                                 fgPlainFunctionCallback::fgPlainFunction pPlainFunction,
                                                 void *pUserData = NULL);
            /**
             * 
             * @param eventCode
             * @param method
             * @param class_instance
             * @return 
             */
            template < class Class >
            fgFunctionCallback* addEventCallback(
                                                 fgEventType eventCode,
                                                 typename fgClassCallback<Class>::fgClassMethod pMethod,
                                                 Class* pClassInstance);

            /**
             * 
             * @param eventCode
             * @param callback
             * @return 
             */
            fgBool removeEventCallback(fgEventType eventCode, fgFunctionCallback *pCallback);

            /**
             * 
             * @param callback
             * @param timeout
             * @param argList
             * @return 
             */
            fgFunctionCallback* addTimeoutCallback(fgFunctionCallback *pCallback,
                                                   const int timeout,
                                                   fgArgumentList *pArgList);

            /**
             * 
             * @param pCallback
             * @return 
             */
            fgBool removeTimeoutCallback(fgFunctionCallback *pCallback);

            /**
             * 
             * @param callback
             * @param repeats
             * @param interval
             * @param argList
             * @return 
             */
            fgFunctionCallback* addCyclicCallback(fgFunctionCallback *pCallback,
                                                  const int repeats = FG_CYCLIC_CALLBACK_INFINITE_REPEAT,
                                                  const int interval = FG_CYCLIC_CALLBACK_DEFAULT_INTERVAL,
                                                  fgArgumentList *pArgList = NULL);

            /**
             * 
             * @param pCallback
             * @return 
             */
            fgBool removeCyclicCallback(fgFunctionCallback *pCallback);

            /**
             * Execute (finalized) all events waiting in a queue
             * This function must be called in every frame in one of the threads
             * (or just the main thread)
             */
            void executeEvents(void);
        };
    };
};

/**
 * 
 * @param eventCode
 * @param method
 * @param class_instance
 * @return 
 */
template <class Class>
fgFunctionCallback* fg::event::CEventManager::addEventCallback(
                                                               fgEventType eventCode,
                                                               typename fgClassCallback<Class>::fgClassMethod pMethod,
                                                               Class* pClassInstance) {
    if(!pMethod || (int)eventCode < 0 || !pClassInstance)
        return NULL;
    fgFunctionCallback *callback = new fgClassCallback<Class>(pClassInstance, pMethod);
    m_eventBinds[eventCode].push_back(callback);
    return callback;
}

    #undef FG_INC_EVENT_MANAGER_BLOCK
#endif /* FG_INC_EVENT_MANAGER */
