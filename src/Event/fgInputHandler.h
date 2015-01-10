/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_INPUT_HANDLER
    #define FG_INC_INPUT_HANDLER
    #define FG_INC_INPUT_HANDLER_BLOCK

    #include "fgBuildConfig.h"

    #include "fgPointerRawData.h"
    #include "Math/fgMathLib.h"
    #include "Event/fgEventManager.h"

    #include <map>

    #define FG_INPUT_MAX_TOUCH_POINTS 10

    #if defined(FG_USING_MARMALADE)
        #include "s3eTypes.h"
        #define FG_DEFAULT_POINTER_ID 0
    #endif

    #if defined(FG_USING_SDL2)
class MainModule;

        #include "SDL2/SDL_events.h"
        #define FG_DEFAULT_POINTER_ID 1
    #endif /* FG_USING_SDL2 */

namespace fg {

    namespace event {

        /**
         * fgPointerInputReceiver receives touch events directly from the callbacks
         * hooked to the Marmalade subsystem or from SDL event queue.
         * TouchReceiver also interprets touches/swipe and later calls (triggers/throws)
         *  proper events. It communicates directly to the EventManager
         */
        class CInputHandler {
    #if defined(FG_USING_SDL2)
            friend class ::MainModule;
    #endif
        private:
            ///
            int MIN_OFFSET_FOR_SWIPE_X;
            ///
            int MIN_OFFSET_FOR_SWIPE_Y;

            /** 
             * Maximum difference between start and end
             * point, for an event to be interpreted as TAP.
             *
             * It does not necessary collide with above SWIPE_*
             * constants, because it is measured between "Press"
             * and "Release" events, while SWIPE_* are also used
             * after "Move" events.
             */
            int MAX_OFFSET_FOR_TAP;
            ///  Also, tap is required to be quick!
            int MAX_MILLISECONDS_FOR_TAP;
            ///
            int PIXELS_PER_STEP_X;
            ///
            int PIXELS_PER_STEP_Y;

        public:
            ///
            static const unsigned int MAX_TOUCH_POINTS;

        private:
            ///
            CVector<int> m_keysDownPool;
            ///
            CVector<int> m_keysUpPool;
            /// int - keyCode, value - vector of callbacks to call
            /// Binding for key down events
            fgCallbackBindingMap m_keyDownBinds;
            /// Binding for key up binds - note that this will only work if
            /// previously key was released
            fgCallbackBindingMap m_keyUpBinds;
            ///
            fgPointerRawData m_rawTouchesProcessed[FG_INPUT_MAX_TOUCH_POINTS + 1];
            ///
            fgPointerRawData m_rawTouches[FG_INPUT_MAX_TOUCH_POINTS + 1];
            ///
            CEventManager *m_eventMgr;
            ///
            fgBool m_init;
            ///
            fgBool m_useMultitouch;
            ///
            fgBool m_pointerAvailable;

            ///
            void interpretSwipes(int min_offset_for_swipe,
                                 int startPointer,
                                 int endPointer,
                                 int initialPointer,
                                 fgBool* minusSwipe,
                                 fgBool* plusSwipe,
                                 int* swipeSize);

        public:
            /**
             * 
             * @param eventMgr
             */
            CInputHandler(CEventManager *eventMgr = NULL);
            /**
             * 
             */
            virtual ~CInputHandler();

            /**
             * 
             */
            void initialize(void);
            /**
             * 
             */
            void processData(void);

            /**
             * 
             * @param keyCode
             * @param pCallback
             * @return 
             */
            fgFunctionCallback* addKeyDownCallback(int keyCode,
                                                   fgFunctionCallback *pCallback);
            /**
             * 
             * @param keyCode
             * @param pCallback
             * @return 
             */
            fgFunctionCallback* addKeyUpCallback(int keyCode,
                                                 fgFunctionCallback *pCallback);

            /**
             * Add key code to the pool of pressed down keys
             * @param keyCode
             */
            void addKeyDown(int keyCode);
            /**
             * Add key code to the pool of released (up) keys
             * @param keyCode
             */
            void addKeyUp(int keyCode);

        public:
            /**
             * 
             * @return 
             */
            CEventManager *getEventManager(void) const {
                return m_eventMgr;
            }
            /**
             * 
             * @param eventMgr
             */
            void setEventManager(CEventManager *eventMgr) {
                m_eventMgr = eventMgr;
            }

        public:
            /**
             * 
             * @return 
             */
            int pixelsPerStepX(void) const {
                return PIXELS_PER_STEP_X;
            }
            /**
             * 
             * @return 
             */
            int pixelsPerStepY(void) const {
                return PIXELS_PER_STEP_Y;
            }
            /**
             * 
             * @return 
             */
            int maxOffsetForTap(void) const {
                return MAX_OFFSET_FOR_TAP;
            }

            /**
             * This function will probably be useful only in debugging
             * There's no need to check the data manually - proper events 
             * are being thrown from processData method
             * @param pointerID
             * @return 
             */
            fgPointerRawData *getPointerRawData(fgPointerID pointerID = FG_DEFAULT_POINTER_ID);
            /**
             * 
             * @param pointerID
             * @return 
             */
            fgPointerData *getPointerData(fgPointerID pointerID = FG_DEFAULT_POINTER_ID);

            /**
             * 
             * @param pointerID
             * @return 
             */
            fgPointerState getPointerState(fgPointerID pointerID = FG_DEFAULT_POINTER_ID);
            /**
             * 
             * @param pointerID
             * @return 
             */
            int getPointerX(fgPointerID pointerID = FG_DEFAULT_POINTER_ID);
            /**
             * 
             * @param pointerID
             * @return 
             */
            int getPointerY(fgPointerID pointerID = FG_DEFAULT_POINTER_ID);

        protected:
            /**
             * 
             * @param point
             * @param touchID
             */
            void handlePointerPressed(fgVector2i point, unsigned int touchID = FG_DEFAULT_POINTER_ID);
            /**
             * 
             * @param point
             * @param touchID
             * @param state
             */
            void handlePointerMoved(fgVector2i point, unsigned int touchID = FG_DEFAULT_POINTER_ID, fgPointerState state = FG_POINTER_STATE_RELEASED);
            /**
             * 
             * @param point
             * @param touchID
             */
            void handlePointerReleased(fgVector2i point, unsigned int touchID = FG_DEFAULT_POINTER_ID);

        protected:
            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static int32_t multiTouchButtonHandler(void* systemData, void* userData);
            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static int32_t multiTouchMotionHandler(void* systemData, void* userData);
            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static int32_t singleTouchButtonHandler(void* systemData, void* userData);
            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static int32_t singleTouchMotionHandler(void* systemData, void* userData);

        };

    };
};

    #undef FG_INC_INPUT_HANDLER_BLOCK
#endif /* FG_INC_INPUT_HANDLER */
