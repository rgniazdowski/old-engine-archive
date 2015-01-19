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
            CallbackBindingMap m_eventBinds;
            /// Events queue (message queue so to speak)
            EventsQueue m_eventsQueue;
            /// Special pool with timeout callbacks (timers)
            TimeoutCallbacksVec m_timeoutCallbacks;
            /// Pool with cyclic timeout callbacks (repeat timers, self reset)
            CyclicCallbacksVec m_cyclicCallbacks;

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
            void throwEvent(EventType eventCode);

            /**
             * This adds event to the waiting queue, the *list object needs to be allocated before,
             * after event callback execution argument list must be freed
             * @param eventCode
             * @param list
             */
            void throwEvent(EventType eventCode,
                            CArgumentList *list);

            /**
             * 
             * @param eventCode
             * @param pSystemData
             */
            void throwEvent(EventType eventCode,
                            void *pSystemData);

            /**
             * 
             * @param eventCode
             * @param pCallback
             * @return 
             */
            CFunctionCallback* addCallback(EventType eventCode,
                                           CFunctionCallback *pCallback);
            /**
             * 
             * @param eventCode
             * @param pFunction
             * @return 
             */
            CFunctionCallback* addCallback(EventType eventCode,
                                           CFunctionCallback::fgFunction pFunction);

            /**
             * 
             * @param eventCode
             * @param pPlainFunction
             * @param pUserData
             * @return 
             */
            CFunctionCallback* addCallback(EventType eventCode,
                                           CPlainFunctionCallback::fgPlainFunction pPlainFunction,
                                           void *pUserData = NULL);
            /**
             * 
             * @param eventCode
             * @param method
             * @param class_instance
             * @return 
             */
            template < class Class >
            CFunctionCallback* addCallback(EventType eventCode,
                                           typename CMethodCallback<Class>::ClassMethod pMethod,
                                           Class* pClassInstance);

            /**
             * 
             * @param eventCode
             * @param callback
             * @return 
             */
            fgBool removeCallback(EventType eventCode, CFunctionCallback *pCallback);

            /**
             * 
             * @param callback
             * @param timeout
             * @param argList
             * @return 
             */
            CFunctionCallback* addTimeoutCallback(CFunctionCallback *pCallback,
                                                  const int timeout,
                                                  CArgumentList *pArgList);

            /**
             * 
             * @param pCallback
             * @return 
             */
            fgBool removeTimeoutCallback(CFunctionCallback *pCallback);

            /**
             * 
             * @param callback
             * @param repeats
             * @param interval
             * @param argList
             * @return 
             */
            CFunctionCallback* addCyclicCallback(CFunctionCallback *pCallback,
                                                 const int repeats = FG_CYCLIC_CALLBACK_INFINITE_REPEAT,
                                                 const int interval = FG_CYCLIC_CALLBACK_DEFAULT_INTERVAL,
                                                 CArgumentList *pArgList = NULL);

            /**
             * 
             * @param pCallback
             * @return 
             */
            fgBool removeCyclicCallback(CFunctionCallback *pCallback);

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
fg::event::CFunctionCallback* fg::event::CEventManager::addCallback(
                                                                    EventType eventCode,
                                                                    typename CMethodCallback<Class>::ClassMethod pMethod,
                                                                    Class* pClassInstance) {
    if(!pMethod || (int)eventCode < 0 || !pClassInstance)
        return NULL;
    CFunctionCallback *callback = new CMethodCallback<Class>(pClassInstance, pMethod);
    m_eventBinds[eventCode].push_back(callback);
    return callback;
}

    #undef FG_INC_EVENT_MANAGER_BLOCK
#endif /* FG_INC_EVENT_MANAGER */
