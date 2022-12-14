/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_INPUT_HANDLER
    #define FG_INC_INPUT_HANDLER
    #define FG_INC_INPUT_HANDLER_BLOCK

    #include "fgBuildConfig.h"

    #include "fgPointerRawData.h"
    #include "Math/fgVector2.h"
    #include "Event/fgEventManager.h"

    #define FG_INPUT_MAX_TOUCH_POINTS 10

    #if defined(FG_USING_SDL2)
namespace fg {
    class CMainModule;
} // namespace fg
        #include "SDL2/SDL_events.h"
        #if defined(FG_USING_PLATFORM_ANDROID)
            #define FG_DEFAULT_POINTER_ID 0
        #else
            #define FG_DEFAULT_POINTER_ID 1
        #endif
    #else
        #define FG_DEFAULT_POINTER_ID 1
    #endif /* FG_USING_SDL2 */

    #if !defined(FG_DEFAULT_POINTER_ID)
        #define FG_DEFAULT_POINTER_ID 0
    #endif

namespace fg {

    class CHardwareState;

    namespace event {

        /**
         * CInputHandler receives touch events directly from the callbacks hooked
         * to SDL event queue. TouchReceiver also interprets touches/swipe and
         * later calls (triggers/throws) proper events. It communicates directly
         * with the EventManager.
         */
        class CInputHandler {
    #if defined(FG_USING_SDL2)
            friend class fg::CMainModule;
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

            /**
             * 
             */
            struct InternalMousePosition {
                int x;
                int y;
            } m_lastMouse[FG_INPUT_MAX_TOUCH_POINTS + 1];
            ///
            CVector<KeyVirtualCode> m_keysDownPool;
            ///
            CVector<KeyVirtualCode> m_keysPressedPool;
            ///
            CVector<KeyVirtualCode> m_keysUpPool;
            ///
            unsigned int m_keyRepeats[FG_NUM_VIRTUAL_KEYS];
            /// int - keyCode, value - vector of callbacks to call
            /// Binding for key down events
            CallbackBindingMap m_keyDownBinds;
            /// Binding for key up binds - note that this will only work if
            /// previously key was released
            CallbackBindingMap m_keyUpBinds;
            ///
            SPointerRawData m_rawTouchesProcessed[FG_INPUT_MAX_TOUCH_POINTS + 1];
            ///
            SPointerRawData m_rawTouches[FG_INPUT_MAX_TOUCH_POINTS + 1];
            ///
            CEventManager *m_eventMgr;
            ///
            KeyboardMod m_keyboardMod;
            ///
            fgBool m_init;
            ///
            fgBool m_useMultitouch;
            ///
            fgBool m_pointerAvailable;

            /**
             * Detects if swipe occurred and computes its size.
             *
             * The initialPointer is used to detect occurrence,
             * startPointer to compute size.
             *
             * @param min_offset_for_swipe
             * @param startPointer
             * @param endPointer
             * @param initialSwipePointer
             * @param minusSwipe
             * @param plusSwipe
             * @param swipeSize
             */
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
            void initialize(const CHardwareState* pHardwareState);
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
            CFunctionCallback* addKeyDownCallback(KeyVirtualCode keyCode,
                                                  CFunctionCallback *pCallback);
            /**
             * 
             * @param keyCode
             * @param pCallback
             * @return 
             */
            CFunctionCallback* addKeyUpCallback(KeyVirtualCode keyCode,
                                                CFunctionCallback *pCallback);

            /**
             * Add key code to the pool of pressed down keys
             * @param keyCode
             */
            void addKeyPressed(KeyVirtualCode keyCode);
            /**
             * Add key code to the pool of released (up) keys
             * @param keyCode
             */
            void addKeyUp(KeyVirtualCode keyCode);

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
             * 
             * @param keyCode
             * @return
             */
            unsigned int getKeyRepeats(KeyVirtualCode keyCode) const;

            /**
             *
             * @param keyCode
             * @return
             */
            fgBool isKeyUp(KeyVirtualCode keyCode) const;
            /**
             *
             * @param keyCode
             * @return
             */
            fgBool isKeyDown(KeyVirtualCode keyCode) const;
            /**
             * 
             * @return
             */
            KeyboardMod getKeyboardMod(void) const {
                return m_keyboardMod;
            }

            /**
             *
             * @param mod
             * @param toggle
             */
            void toggleKeyboardMod(KeyboardMod mod, const fgBool toggle = FG_TRUE);
            /**
             * 
             * @param keyCode
             * @param toggle
             */
            void toggleKeyboardMod(KeyVirtualCode keyCode, const fgBool toggle = FG_TRUE);
            /**
             *
             * @param mod
             * @return
             */
            fgBool isKeyboardMod(KeyboardMod mod) const;

            /**
             *
             * @return
             */
            fgBool isAltDown(fgBool onlyAlt = FG_FALSE) const;
            /**
             *
             * @return
             */
            fgBool isControlDown(fgBool onlyControl = FG_FALSE) const;
            /**
             *
             * @return
             */
            fgBool isShiftDown(fgBool onlyShift = FG_FALSE) const;
            /**
             * 
             * @return
             */
            fgBool isGuiDown(fgBool onlyGui = FG_FALSE) const;

            /**
             * This function will probably be useful only in debugging
             * There's no need to check the data manually - proper events 
             * are being thrown from processData method
             * @param pointerID
             * @return 
             */
            SPointerRawData *getPointerRawData(fgPointerID pointerID = FG_DEFAULT_POINTER_ID);
            /**
             * 
             * @param pointerID
             * @return 
             */
            SPointerData *getPointerData(fgPointerID pointerID = FG_DEFAULT_POINTER_ID);

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

        public:
            /**
             * 
             * @param point
             * @param touchID
             */
            void handlePointerPressed(Vector2i point, unsigned int touchID = FG_DEFAULT_POINTER_ID);
            /**
             * 
             * @param point
             * @param touchID
             * @param state
             */
            void handlePointerMoved(Vector2i point, unsigned int touchID = FG_DEFAULT_POINTER_ID, fgPointerState state = FG_POINTER_STATE_RELEASED);
            /**
             * 
             * @param point
             * @param touchID
             */
            void handlePointerReleased(Vector2i point, unsigned int touchID = FG_DEFAULT_POINTER_ID);

        protected:
            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static int32_t multiTouchButtonHandler(void* systemData, void* userData);
            /**
             * Touch motion HANDLER
             *
             * @param systemData Pointer to the event structure
             * @param userData Pointer to the handling class - fgInputHandler
             * @return
             */
            static int32_t multiTouchMotionHandler(void* systemData, void* userData);
            /**
             * Single press/release HANDLER
             * @param systemData Pointer to the event structure
             * @param userData Pointer to the handling class - fgInputHandler
             * @return
             */
            static int32_t singleTouchButtonHandler(void* systemData, void* userData);
            /**
             * Single motion HANDLER
             * @param systemData Pointer to the event structure
             * @param userData Pointer to the handling class - fgInputHandler
             * @return
             */
            static int32_t singleTouchMotionHandler(void* systemData, void* userData);

        }; // class CInputHandler

    } // namespace event
} // namespace fg

    #undef FG_INC_INPUT_HANDLER_BLOCK
#endif /* FG_INC_INPUT_HANDLER */
