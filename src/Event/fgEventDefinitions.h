/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_EVENT_DEFINITIONS
    #define FG_INC_EVENT_DEFINITIONS
    #define FG_INC_EVENT_DEFINITIONS_BLOCK

    #include "fgBool.h"
//
// This file will contain all basic events occurring in the game engine
// also defines standard event structures holding info about the event
//

namespace fg {

    namespace resource {
        class CResource;
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
        const EventType RESOURCE_CREATED = 18;
        /// 
        const EventType RESOURCE_REMOVED = 19;
        /// 
        const EventType RESOURCE_DISPOSED = 20;
        /// 
        const EventType RESOURCE_DESTROYED = 21;
        /// 
        const EventType RESOURCE_REQUESTED = 22;

        /// 
        const EventType PROGRAM_INIT = 23;
        /// 
        const EventType LOADING_BEGIN = 24;
        /// 
        const EventType LOADING_FINISHED = 25;
        /// 
        const EventType SPLASHSCREEN = 26;

        /// 
        const EventType VERTEX_STREAM_READY = 27;
        /// 
        const EventType CAMERA_CHANGED = 28;

        /// 
        const EventType SOUND_PLAYED = 29;

        /// 
        const EventType MENU_CHANGED = 30;
        /// 
        const EventType WIDGET_STATE_CHANGED = 31;

        /// 
        const EventType SENSORS_CHANGED = 32;

        /// 
        const EventType GAME_CONTROLLER_ADDED = 33;
        /// 
        const EventType GAME_CONTROLLER_REMOVED = 34;
        /// 
        const EventType GAME_CONTROLLER_BUTTON = 35;
        /// 
        const EventType GAME_CONTROLLER_AXIS = 36;

        /// 
        const EventType RESERVED1 = 37;
        /// 
        const EventType RESERVED2 = 38;
        /// 
        const EventType RESERVED3 = 39;

        /// 
        const EventType LAST_STANDARD_EVENT_CODE = 39;

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
            unsigned int touchID;
            fgBool pressed;
        };

        /**
         *
         */
        struct SMouse : SEventBase {
            int x;
            int y;
            unsigned int buttonID;
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
                int keyCode;
                int which;
            };
            fgBool pressed;
        };

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
         *
         */
        struct SMenuChanged : SEventBase {
            //GUIHANDLE 
            //
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
        };
    };
};

    #undef FG_INC_EVENT_DEFINITIONS_BLOCK
#endif /* FG_INC_EVENT_DEFINITIONS */
