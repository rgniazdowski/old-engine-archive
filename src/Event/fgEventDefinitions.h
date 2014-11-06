/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_EVENT_DEFINITIONS_H_
    #define _FG_EVENT_DEFINITIONS_H_
    #define _FG_EVENT_DEFINITIONS_H_BLOCK_

    #ifndef _FG_RESOURCE_H_
        #include "Resource/fgResource.h"
    #endif

//
// This file will contain all basic events occuring in the game engine
// also defines standard event structures holding info about the event
//

// Event Type enumeration

enum fgEventType {
    FG_EVENT_INVALID = 0,

    FG_EVENT_TOUCH_PRESSED = 1,
    FG_EVENT_TOUCH_RELEASED = 2,
    FG_EVENT_TOUCH_MOTION = 3,
    FG_EVENT_TOUCH_TAP_FINISHED = 4,
    //FG_EVENT_TOUCH = 5,

    FG_EVENT_MOUSE_PRESSED = 6,
    FG_EVENT_MOUSE_RELEASED = 7,
    FG_EVENT_MOUSE_MOTION = 8,
    //FG_EVENT_MOUSE = 9,

    FG_EVENT_SWIPE_X = 10,
    FG_EVENT_SWIPE_Y = 11,
    FG_EVENT_SWIPE_XY = 12,
    FG_EVENT_SWIPE_ANGLE = 12,

    FG_EVENT_SWIPE_PINCH = 14,

    FG_EVENT_MULTI_SWIPE_ROTATE = 15,

    FG_EVENT_KEY_DOWN = 16,
    FG_EVENT_KEY_UP = 17,

    FG_EVENT_RESOURCE_CREATED = 18,
    FG_EVENT_RESOURCE_REMOVED = 19,
    FG_EVENT_RESOURCE_DISPOSED = 20,
    FG_EVENT_RESOURCE_DESTROYED = 21,
    FG_EVENT_RESOURCE_REQUESTED = 22,

    FG_EVENT_PROGRAM_INIT = 23,

    FG_EVENT_VERTEX_STREAM_READY = 24,
    FG_EVENT_CAMERA_CHANGED = 25,

    FG_EVENT_SOUND_PLAYED = 26,

    FG_EVENT_MENU_CHANGED = 27,
    FG_EVENT_WIDGET_STATE_CHANGED = 28,

    FG_EVENT_SENSORS_CHANGED = 29,

    FG_EVENT_GAME_CONTROLLER_ADDED = 30,
    FG_EVENT_GAME_CONTROLLER_REMOVED = 31,
    FG_EVENT_GAME_CONTROLLER_BUTTON = 32,
    FG_EVENT_GAME_CONTROLLER_AXIS = 33,

    FG_EVENT_RESERVED1,
    FG_EVENT_RESERVED2,
    FG_NUM_EVENT_TYPES
};

enum fgSwipeDirection {
    FG_SWIPE_INVALID,
    FG_SWIPE_LEFT,
    FG_SWIPE_RIGHT,
    FG_SWIPE_UP,
    FG_SWIPE_DOWN,
    FG_SWIPE_ANGLE
};

enum fgPinchDirection {
    FG_PINCH_INVALID,
    FG_PINCH_IN,
    FG_PINCH_OUT
};

// FIXME this should be declared in the ResourceManager header file - well I think so...

enum fgResourceStatus {
    FG_RESOURCE_CREATED,
    FG_RESOURCE_REMOVED,
    FG_RESOURCE_DISPOSED,
    FG_RESOURCE_DESTROYED,
    FG_RESOURCE_REQUESTED
};

/*
 *
 */
struct fgEventBase {
    fgEventType eventType;
    unsigned long int timeStamp;
};

/*
 *
 */
struct fgControllerDeviceEvent : fgEventBase {
    int which; // The joystick device index
};

/*
 *
 */
struct fgControllerButtonEvent : fgEventBase {
    int which; // The joystick instance id
    unsigned short button;
    unsigned short state;
};

/*
 *
 */
struct fgControllerAxisEvent : fgEventBase {
    int which; // The joystick instance id
    unsigned short axis; // Controller axis
    short int value;
};

/*
 *
 */
struct fgTouchEvent : fgEventBase {
    int x;
    int y;
    unsigned int touchID;
    fgBool pressed;

};

/*
 *
 */
struct fgMouseEvent : fgEventBase {
    int x;
    int y;
    unsigned int buttonID;
    fgBool pressed;

};

/*
 *
 */
struct fgSwipeEvent : fgEventBase {
    fgSwipeDirection swipeDirection;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int swipeXOffset;
    int swipeYOffset;
    int swipeXSteps;
    int swipeYSteps;
};

/*
 *
 */
struct fgSwipePinchEvent : fgEventBase {
    fgPinchDirection pinchDirection;
    int x;
    int y;
    int x2;
    int y2;
    int pinchXOffset;
    int pinchYOffset;
    int pinchSize;
};

/*
 *
 */
struct fgSwipeRotateEvent : fgEventBase { // Should extend SwipeEvent?
    int x;
    int y;
    int x2;
    int y2;
    float angle;
};

/*
 *
 */
struct fgKeyEvent : fgEventBase {

    union {
        int keyCode;
        int which;
    };
    fgBool pressed;
};

struct fgResourceEvent : fgEventBase {
    fgResourceStatus status; // ?
    fgResource *resource;
};

struct fgVertexStreamEvent : fgEventBase {
    //FG_GFXHANDLE vertexStreamHandle;
    //fgVertexStream *vertexStreamHolder;
};

struct fgCameraEvent : fgEventBase {
    //GfxCamera *cameraHolder;
    //FG_GFXHANDLE cameraHandle;
};

struct fgSoundEvent : fgEventBase {
    //FG_RHANDLE soundHandle;
    //fgResource *soundHolder;
};

struct fgMenuChangedEvent : fgEventBase {
    //GUIHANDLE 
    //
};

struct fgWidgetEvent : fgEventBase {
    //FG_GUIHANDLE widgetHandle;
    //fgWidget
    //fgResource
};

/*
 *
 */
struct fgSensorsEvent : fgEventBase {
    // int type; or fgSensorType type;

    union {

        struct {
            float x, y, z;
        };
        float data[3];
    };
};

/*
 *
 */
struct fgEvent {

    union {
        fgEventType eventType;

        fgTouchEvent touch;
        fgMouseEvent mouse;
        fgSwipeEvent swipe;
        fgSwipePinchEvent swipePinch;
        fgSwipeRotateEvent swipeRotate;
        fgKeyEvent key;
        fgResourceEvent resource;
        fgVertexStreamEvent vertexStream;
        fgCameraEvent camera;
        fgSoundEvent sound;
        fgMenuChangedEvent menuChanged;
        fgWidgetEvent widget;
        fgSensorsEvent sensors;
        fgControllerDeviceEvent controller;
        fgControllerButtonEvent controllerButton;
        fgControllerAxisEvent controllerAxis;
    };
};

    #undef _FG_EVENT_DEFINITIONS_H_BLOCK_

#endif /* _FG_EVENT_DEFINITIONS_H_ */
