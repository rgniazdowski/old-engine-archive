/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_EVENT_DEFINITIONS
    #define FG_INC_EVENT_DEFINITIONS
    #define FG_INC_EVENT_DEFINITIONS_BLOCK

    #include "fgBool.h"
    #include "fgKeyboard.h"

//
// This file will contain all basic events occurring in the game engine
// also defines standard event structures holding info about the event
//

namespace fg {

    namespace resource {
        class CResource;
    }

    namespace gui {
        class CMenu;
        class CWidget;
    }

    namespace event {

    #ifndef FG_EVENT_TYPE_DEFINED
        #define FG_EVENT_TYPE_DEFINED
        /// 
        typedef unsigned int EventType;
    #endif

        /// 
        const EventType INVALID = 0;

        /// 
        const EventType TOUCH_PRESSED = 1;
        /// 
        const EventType TOUCH_RELEASED = 2;
        /// 
        const EventType TOUCH_MOTION = 3;
        /// 
        const EventType TOUCH_TAP_FINISHED = 4;
        //const EventType TOUCH=5;

        /// 
        const EventType MOUSE_PRESSED = 6;
        /// 
        const EventType MOUSE_RELEASED = 7;
        /// 
        const EventType MOUSE_MOTION = 8;
        ///
        const EventType MOUSE_TAP_FINISHED = TOUCH_TAP_FINISHED;

        //const EventType MOUSE=9;

        /// 
        const EventType SWIPE_X = 10;
        /// 
        const EventType SWIPE_Y = 11;
        /// 
        const EventType SWIPE_XY = 12;
        /// 
        const EventType SWIPE_ANGLE = 12;

        /// 
        const EventType SWIPE_PINCH = 14;

        /// 
        const EventType MULTI_SWIPE_ROTATE = 15;

        /// 
        const EventType KEY_DOWN = 16;
        /// 
        const EventType KEY_UP = 17;
        ///
        const EventType KEY_PRESSED = 18;
        ///
        const EventType KEY_RELEASED = KEY_UP;

        /// 
        const EventType RESOURCE_CREATED = 30;
        /// 
        const EventType RESOURCE_REMOVED = 31;
        /// 
        const EventType RESOURCE_DISPOSED = 32;
        /// 
        const EventType RESOURCE_DESTROYED = 33;
        /// 
        const EventType RESOURCE_REQUESTED = 34;

        /// 
        const EventType PROGRAM_INIT = 40;
        ///
        const EventType PROGRAM_QUIT = 41;
        ///
        const EventType PROGRAM_SUSPEND = 42;
        ///
        const EventType PROGRAM_RESUME = 43;

        /// 
        const EventType LOADING_BEGIN = 50;
        /// 
        const EventType LOADING_FINISHED = 51;
        /// 
        const EventType SPLASHSCREEN = 52;
        ///
        const EventType SWAP_BUFFERS = 53;
        ///
        const EventType UPDATE_SHOT = 54;
        ///
        const EventType IDLE = UPDATE_SHOT;
        ///
        const EventType PRERENDER_SHOT = 55;
        ///
        const EventType RENDER_SHOT = 56;

        ///
        const EventType FRAME_FREEZE = 57;

        /// 
        const EventType VERTEX_STREAM_READY = 60;
        /// 
        const EventType CAMERA_CHANGED = 61;

        /// 
        const EventType SOUND_PLAYED = 70;

        /// 
        const EventType MENU_CHANGED = 80;
        /// 
        const EventType WIDGET_STATE_CHANGED = 81;

        /// 
        const EventType SENSORS_CHANGED = 90;

        /// 
        const EventType GAME_CONTROLLER_ADDED = 100;
        /// 
        const EventType GAME_CONTROLLER_REMOVED = 101;
        /// 
        const EventType GAME_CONTROLLER_BUTTON = 102;
        /// 
        const EventType GAME_CONTROLLER_AXIS = 103;

        /// 
        const EventType RESERVED1 = 110;
        /// 
        const EventType RESERVED2 = 111;
        /// 
        const EventType RESERVED3 = 112;

        /// 
        const EventType LAST_STANDARD_EVENT_CODE = RESERVED3;

        /**
         *
         */
        struct SEventBase {
            EventType eventType;
            unsigned long int timeStamp;
        };

        /**
         *
         */
        struct SControllerDevice : SEventBase {
            int which; // The joystick device index
        };

        /**
         *
         */
        struct SControllerButton : SEventBase {
            int which; // The joystick instance id
            unsigned short button;
            unsigned short state;
        };

        /**
         *
         */
        struct SControllerAxis : SEventBase {
            int which; // The joystick instance id
            unsigned short axis; // Controller axis
            short int value;
        };

        /**
         *
         */
        struct STouch : SEventBase {
            int x;
            int y;
            int relX;
            int relY;

            union {
                unsigned int touchID;
                unsigned int buttonID;
                unsigned int pointerID;
            };
            fgBool pressed;
        };

        /**
         *
         */
        struct SMouse : SEventBase {
            int x;
            int y;
            int relX;
            int relY;

            union {
                unsigned int touchID;
                unsigned int buttonID;
                unsigned int pointerID;
            };
            fgBool pressed;
        };

        /**
         *
         */
        struct SSwipe : SEventBase {

            enum Direction {
                INVALID,
                LEFT,
                RIGHT,
                UP,
                DOWN,
                ANGLE
            } swipeDirection;
            int xStart;
            int yStart;
            int xEnd;
            int yEnd;
            int swipeXOffset;
            int swipeYOffset;
            int swipeXSteps;
            int swipeYSteps;
        };

        /**
         *
         */
        struct SSwipePinch : SEventBase {

            enum Direction {
                INVALID,
                IN,
                OUT
            } pinchDirection;
            int x;
            int y;
            int x2;
            int y2;
            int pinchXOffset;
            int pinchYOffset;
            int pinchSize;
        };

        /**
         *
         */
        struct SSwipeRotate : SEventBase { // Should extend SwipeEvent?
            int x;
            int y;
            int x2;
            int y2;
            float angle;
        };

        /**
         *
         */
        struct SKey : SEventBase {

            union {
                KeyVirtualCode keyCode;
                KeyVirtualCode which;
            };
            ///
            fgBool pressed;
            ///
            int repeats;
            ///
            KeyboardMod mod;
            /**
             * Check whether or not the currently reported key is a mod key
             * @return
             */
            inline fgBool isMod(void) const {
                if(keyCode == FG_KEY_LSHIFT ||
                        keyCode == FG_KEY_RSHIFT ||
                        keyCode == FG_KEY_LCTRL ||
                        keyCode == FG_KEY_RCTRL ||
                        keyCode == FG_KEY_LALT ||
                        keyCode == FG_KEY_RALT ||
                        keyCode == FG_KEY_LGUI ||
                        keyCode == FG_KEY_RGUI) {
                    return FG_TRUE;
                }
                return FG_FALSE;
            }
            /**
             *
             * @return
             */
            inline fgBool isAlpha(void) const {
                if(keyCode >= FG_KEY_A && keyCode <= FG_KEY_Z) {
                    return FG_TRUE;
                }
                return FG_FALSE;
            }
            /**
             * 
             * @return
             */
            inline fgBool isDigit(void) const {
                if((keyCode >= FG_KEY_0 && keyCode <= FG_KEY_9) ||
                        (keyCode >= FG_KEY_NUM_0 && keyCode <= FG_KEY_NUM_9)) {
                    return FG_TRUE;
                }
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline fgBool isAlphaNum(void) const {
                return (fgBool)!!(isAlpha() || isDigit());
            }
            /**
             *
             * @return
             */
            inline fgBool isSpace(void) const {
                if(keyCode == FG_KEY_FF ||
                        keyCode == FG_KEY_LINEFEED ||
                        keyCode == FG_KEY_CR ||
                        keyCode == FG_KEY_HORIZONTAL_TAB ||
                        keyCode == FG_KEY_VERTICAL_TAB) {
                    return FG_TRUE;
                }
                return FG_FALSE;
            }
            /**
             *
             * @return
             */
            inline fgBool isShiftDown(void) const {
                if((fgBool)!!(mod & FG_MOD_LSHIFT))
                    return FG_TRUE;
                if((fgBool)!!(mod & FG_MOD_RSHIFT))
                    return FG_TRUE;
                return FG_FALSE;
            }
            /**
             *
             * @return
             */
            inline fgBool isControlDown(void) const {
                if((fgBool)!!(mod & FG_MOD_LCTRL))
                    return FG_TRUE;
                if((fgBool)!!(mod & FG_MOD_RCTRL))
                    return FG_TRUE;
                return FG_FALSE;
            }
            /**
             *
             * @return
             */
            inline fgBool isAltDown(void) const {
                if((fgBool)!!(mod & FG_MOD_LALT))
                    return FG_TRUE;
                if((fgBool)!!(mod & FG_MOD_RALT))
                    return FG_TRUE;
                return FG_FALSE;
            }
            /**
             *
             * @return
             */
            inline fgBool isGuiDown(void) const {
                if((fgBool)!!(mod & FG_MOD_LGUI))
                    return FG_TRUE;
                if((fgBool)!!(mod & FG_MOD_RGUI))
                    return FG_TRUE;
                return FG_FALSE;
            }
        }; // struct SKey

        /**
         *
         */
        struct SResource : SEventBase {

            enum Status {
                CREATED,
                REMOVED,
                DISPOSED,
                DESTROYED,
                REQUESTED
            } status;
            fg::resource::CResource *resource;
        };

        //#define FG_EVENT_PROGRAM_INIT       23
        //#define FG_EVENT_LOADING            24
        //#define FG_EVENT_SPLASHSCREEN       26

        struct SProgram : SEventBase {
        };

        struct SLoading : SEventBase {

            enum Status {
                BEGIN = 0,
                CONTINUE = 1,
                FINISH = 2
            } status;
        };

        /**
         *
         */
        struct SSplashScreen : SEventBase {
            /// Status of the splashscreen display - no additional data is required?
            /// If FG_TRUE - splashscreen is no longer displayed
            /// If FG_FALSE - splashscreen just started or in the middle
            fgBool finish;
        };

        /**
         *
         */
        struct SVertexStream : SEventBase {
            //FG_GFXHANDLE vertexStreamHandle;
            //fgVertexStream *vertexStreamHolder;
        };

        /**
         *
         */
        struct SCamera : SEventBase {
            //GfxCamera *cameraHolder;
            //FG_GFXHANDLE cameraHandle;
        };

        /**
         *
         */
        struct SSound : SEventBase {
            //FG_RHANDLE soundHandle;
            //fgResource *soundHolder;
        };

        /**
         * Event structure for changing GUI menu events
         */
        struct SMenuChanged : SEventBase {
            /// Pointer to previous menu (can be NULL)
            fg::gui::CWidget* prevMenu;
            /// Pointer to the next menu (current)
            fg::gui::CWidget* nextMenu;
            /// Previous menu name
            const char* prevMenuName;
            /// Next menu name
            const char* nextMenuName;
            /// Set to TRUE if the changing did finished or to FALSE if the
            // changing is already in motion (animated)
            fgBool didChange;
        };

        /**
         *
         */
        struct SWidget : SEventBase {
            //FG_GUIHANDLE widgetHandle;
            //fgWidget
            //fgResource
        };

        /**
         *
         */
        struct SSensors : SEventBase {
            // int type; or fgSensorType type;

            union {

                struct {
                    float x, y, z;
                };
                float data[3];
            };
        };

        /**
         *
         */
        struct SReserved : SEventBase {
            void *data1;
            void *data2;
            void *data3;
            int n_data;
        };

        /**
         *
         */
        struct SEvent {

            union {
                EventType code;

                STouch touch;
                SMouse mouse;
                SSwipe swipe;
                SSwipePinch swipePinch;
                SSwipeRotate swipeRotate;
                SKey key;
                SResource resource;
                SVertexStream vertexStream;
                SCamera camera;
                SSound sound;
                SMenuChanged menuChanged;
                SWidget widget;
                SSensors sensors;
                SSplashScreen splash;
                SLoading loading;
                SProgram program;
                SControllerDevice controller;
                SControllerButton controllerButton;
                SControllerAxis controllerAxis;

                SReserved reserved;
            };
        }; // struct SEvent
    } // namespace event
} // namespace fg

    #undef FG_INC_EVENT_DEFINITIONS_BLOCK
#endif /* FG_INC_EVENT_DEFINITIONS */
