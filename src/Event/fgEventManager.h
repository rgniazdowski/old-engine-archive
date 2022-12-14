/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

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

// #TODO #P4 make event manager thread friendly / multi-thread support

    #define FG_MANAGER_EVENT        0x00000008

namespace fg {
    namespace event {

        /**
         * Event manager main class definition.
         */
        class CEventManager : public fg::base::CManager {
        public:
            typedef fg::base::CManager base_type;
            typedef CEventManager self_type;
            typedef CEventManager type;

            typedef CVector<void*> EventsVoidPtrVec;
            typedef EventsVoidPtrVec::iterator EventsVoidPtrVecItor;

            typedef CVector<void*> ArgListVoidPtrVec;
            typedef ArgListVoidPtrVec::iterator ArgListVoidPtrVecItor;

        public:
            /// Maximum number of allocated internal event structures
            /// When number of event structures reaches MAX and 
            /// free slots are empty - this would mean that event queue is full
            static const unsigned int MAX_EVENT_STRUCTS = 256;
            /// Maximum number of thrown events
            static const unsigned int MAX_THROWN_EVENTS = 256;
            /// This is initial allocation for pointer vectors (initial capacity)
            static const unsigned int INITIAL_PTR_VEC_SIZE = 32;

        public:
            /**
             * Default constructor for Event Manager object
             */
            explicit CEventManager(unsigned int eventStructSize = sizeof (SEvent));
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
             * @return 
             */
            SEventBase* requestEventStruct(EventType eventType = event::INVALID,
                                           unsigned int eventStructSize = 0);

            /**
             * 
             * @return 
             */
            CArgumentList* requestArgumentList(void);
            /**
             * 
             * @param structSize
             */
            void setEventStructSize(const unsigned int structSize) {
                m_eventStructSize = structSize;
            }
            ////////////////////////////////////////////////////////////////////

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
                            void* pSystemData);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param eventCode
             * @param pCallback
             * @return
             */
            fgBool isRegistered(EventType eventCode,
                                CFunctionCallback* pCallback);
            /**
             *
             * @param eventCode
             * @param pFunction
             * @return
             */
            fgBool isRegistered(EventType eventCode,
                                const CFunctionCallback::Function pFunction);
            /**
             *
             * @param eventCode
             * @param pPlainFunction
             * @return
             */
            fgBool isRegistered(EventType eventCode,
                                const CPlainFunctionCallback::PlainFunction pPlainFunction);
            /**
             *
             * @param pCallback
             * @return
             */
            EventType isRegistered(CFunctionCallback* pCallback);
            /**
             *
             * @param pFunction
             * @return
             */
            EventType isRegistered(const CFunctionCallback::Function pFunction);
            /**
             *
             * @param pPlainFunction
             * @return
             */
            EventType isRegistered(const CPlainFunctionCallback::PlainFunction pPlainFunction);

            ////////////////////////////////////////////////////////////////////

            /**
             *
             * @param eventCode
             * @return
             */
            unsigned int executeEvent(EventType eventCode);

            /**
             *
             * @param thrownEvent
             * @return
             */
            unsigned int executeEvent(const SThrownEvent& thrownEvent);

            /**
             *
             * @param eventCode
             * @param list
             * @return
             */
            unsigned int executeEvent(EventType eventCode,
                                      CArgumentList *list);

            /**
             * 
             * @param eventCode
             * @param pSystemData
             * @return
             */
            unsigned int executeEvent(EventType eventCode,
                                      void* pSystemData);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param eventCode
             * @param pCallback
             * @return 
             */
            CFunctionCallback* addCallback(EventType eventCode,
                                           CFunctionCallback* pCallback);
            /**
             * 
             * @param eventCode
             * @param pFunction
             * @return 
             */
            CFunctionCallback* addCallback(EventType eventCode,
                                           CFunctionCallback::Function pFunction);

            /**
             * 
             * @param eventCode
             * @param pPlainFunction
             * @param pUserData
             * @return 
             */
            CFunctionCallback* addCallback(EventType eventCode,
                                           CPlainFunctionCallback::PlainFunction pPlainFunction,
                                           void* pUserData = NULL);
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
            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param eventCode
             * @param callback
             * @return 
             */
            fgBool removeCallback(EventType eventCode, CFunctionCallback* pCallback);

            /**
             * This will remove all callbacks bind to the given event. The destructors
             * will not be called.
             * @param eventCode
             * @return
             */
            fgBool removeCallbacks(EventType eventCode);

            /**
             * 
             * @param eventCode
             * @param pCallback
             * @return 
             */
            fgBool deleteCallback(EventType eventCode, CFunctionCallback*& pCallback);

            /**
             * 
             * @param eventCode
             * @return 
             */
            fgBool deleteCallbacks(EventType eventCode);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param callback
             * @param timeout
             * @param argList
             * @return 
             */
            CFunctionCallback* addTimeoutCallback(CFunctionCallback* pCallback,
                                                  const int timeout,
                                                  CArgumentList* pArgList);

            /**
             * 
             * @param pCallback
             * @return 
             */
            fgBool removeTimeoutCallback(CFunctionCallback* pCallback);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param callback
             * @param repeats
             * @param interval
             * @param argList
             * @return 
             */
            CFunctionCallback* addCyclicCallback(CFunctionCallback* pCallback,
                                                 const int repeats = FG_CYCLIC_CALLBACK_INFINITE_REPEAT,
                                                 const int interval = FG_CYCLIC_CALLBACK_DEFAULT_INTERVAL,
                                                 CArgumentList* pArgList = NULL);

            /**
             * 
             * @param pCallback
             * @return 
             */
            fgBool removeCyclicCallback(CFunctionCallback* pCallback);

            ////////////////////////////////////////////////////////////////////

            /**
             * Execute (finalized) all events waiting in a queue
             * This function must be called in every frame in one of the threads
             * (or just the main thread)
             */
            void executeEvents(void);

        private:

            /**
             * 
             * @param ptr
             */
            void pushToFreeSlot(SEventBase* ptr);
            /**
             * 
             * @param ptr
             */
            void pushToFreeSlot(CArgumentList* ptr);

        private:
            /// Size in bytes for event structure preallocation
            unsigned int m_eventStructSize;
            /// int - eventCode
            /// Binding for all global events
            CallbackBindingMap m_eventBinds;
            /// Events queue (message queue so to speak)
            EventsQueue m_eventsQueue;
            /// Special pool with timeout callbacks (timers)
            TimeoutCallbacksVec m_timeoutCallbacks;
            /// Pool with cyclic timeout callbacks (repeat timers, self reset)
            CyclicCallbacksVec m_cyclicCallbacks;
            ///
            EventsVoidPtrVec m_eventStructs;
            ///
            EventsVoidPtrVec m_eventStructsFreeSlots;
            ///
            ArgListVoidPtrVec m_argLists;
            ///
            ArgListVoidPtrVec m_argListsFreeSlots;
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
fg::event::CFunctionCallback* fg::event::CEventManager::addCallback(EventType eventCode,
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
