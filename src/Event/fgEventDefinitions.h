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

    #ifndef FG_INC_RESOURCE
        #include "Resource/fgResource.h"
    #endif

//
// This file will contain all basic events occurring in the game engine
// also defines standard event structures holding info about the event
//

    #ifndef FG_EVENT_TYPE_DEFINED
        #define FG_EVENT_TYPE_DEFINED
typedef unsigned int fgEventType;
    #endif
    

#define FG_EVENT_INVALID            0

#define FG_EVENT_TOUCH_PRESSED      1
#define FG_EVENT_TOUCH_RELEASED     2
#define FG_EVENT_TOUCH_MOTION       3
#define FG_EVENT_TOUCH_TAP_FINISHED 4
//#define FG_EVENT_TOUCH            5

#define FG_EVENT_MOUSE_PRESSED      6
#define FG_EVENT_MOUSE_RELEASED     7
#define FG_EVENT_MOUSE_MOTION       8
//#define FG_EVENT_MOUSE            9

#define FG_EVENT_SWIPE_X            10
#define FG_EVENT_SWIPE_Y            11
#define FG_EVENT_SWIPE_XY           12
#define FG_EVENT_SWIPE_ANGLE        12

#define FG_EVENT_SWIPE_PINCH        14

#define FG_EVENT_MULTI_SWIPE_ROTATE 15

#define FG_EVENT_KEY_DOWN           16
#define FG_EVENT_KEY_UP             17

#define FG_EVENT_RESOURCE_CREATED   18
#define FG_EVENT_RESOURCE_REMOVED   19
#define FG_EVENT_RESOURCE_DISPOSED  20
#define FG_EVENT_RESOURCE_DESTROYED 21
#define FG_EVENT_RESOURCE_REQUESTED 22

#define FG_EVENT_PROGRAM_INIT       23
#define FG_EVENT_LOADING_BEGIN      24
#define FG_EVENT_LOADING_FINISHED   25
#define FG_EVENT_SPLASHSCREEN       26

#define FG_EVENT_VERTEX_STREAM_READY    27
#define FG_EVENT_CAMERA_CHANGED         28

#define FG_EVENT_SOUND_PLAYED           29

#define FG_EVENT_MENU_CHANGED           30
#define FG_EVENT_WIDGET_STATE_CHANGED   31

#define FG_EVENT_SENSORS_CHANGED            32

#define FG_EVENT_GAME_CONTROLLER_ADDED      33
#define FG_EVENT_GAME_CONTROLLER_REMOVED    34
#define FG_EVENT_GAME_CONTROLLER_BUTTON     35
#define FG_EVENT_GAME_CONTROLLER_AXIS       36

#define FG_EVENT_RESERVED1          37
#define FG_EVENT_RESERVED2          38
#define FG_EVENT_RESERVED3          39

#define FG_EVENT_LAST_STANDARD_EVENT_CODE 39

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

/**
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

/**
 *
 */
struct fgSwipeRotateEvent : fgEventBase { // Should extend SwipeEvent?
    int x;
    int y;
    int x2;
    int y2;
    float angle;
};

/**
 *
 */
struct fgKeyEvent : fgEventBase {

    union {
        int keyCode;
        int which;
    };
    fgBool pressed;
};

/**
 *
 */
struct fgResourceEvent : fgEventBase {
    fgResourceStatus status; // ?
    CResource *resource;
};

//#define FG_EVENT_PROGRAM_INIT       23
//#define FG_EVENT_LOADING            24
//#define FG_EVENT_SPLASHSCREEN       26

struct fgProgramEvent : fgEventBase {
    
};

enum class fgLoadingStatus : unsigned char {
    BEGIN = 0,
    CONTINUE = 1,
    FINISH = 2
};

struct fgLoadingEvent : fgEventBase {
    fgLoadingStatus status;
};

/**
 *
 */
struct fgSplashScreenEvent : fgEventBase {
    /// Status of the splashscreen display - no additional data is required?
    /// If FG_TRUE - splashscreen is no longer displayed
    /// If FG_FALSE - splashscreen just started or in the middle
    fgBool finish;
};

/**
 *
 */
struct fgVertexStreamEvent : fgEventBase {
    //FG_GFXHANDLE vertexStreamHandle;
    //fgVertexStream *vertexStreamHolder;
};

/**
 *
 */
struct fgCameraEvent : fgEventBase {
    //GfxCamera *cameraHolder;
    //FG_GFXHANDLE cameraHandle;
};

/**
 *
 */
struct fgSoundEvent : fgEventBase {
    //FG_RHANDLE soundHandle;
    //fgResource *soundHolder;
};

/**
 *
 */
struct fgMenuChangedEvent : fgEventBase {
    //GUIHANDLE 
    //
};

/**
 *
 */
struct fgWidgetEvent : fgEventBase {
    //FG_GUIHANDLE widgetHandle;
    //fgWidget
    //fgResource
};

/**
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

/**
 *
 */
struct fgReservedEvent : fgEventBase {
    void *data1;
    void *data2;
    void *data3;
    int n_data;
};

/**
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
        
        fgReservedEvent reserved;
    };
};

    #undef FG_INC_EVENT_DEFINITIONS_BLOCK

#endif /* FG_INC_EVENT_DEFINITIONS */
