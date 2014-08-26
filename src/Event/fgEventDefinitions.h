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

//
// This file will contain all basic events occuring in the game engine
// also defines standard event structures holding info about the event
//

// Event Type enumeration
enum fgEventType {
	FG_EVENT_INVALID			=	0,

	FG_EVENT_TOUCH_PRESSED		=	1,
	FG_EVENT_TOUCH_RELEASED		=	2,
	FG_EVENT_TOUCH_MOTION		=	3,
	FG_EVENT_TOUCH_TAP_FINISHED	=	4,

	FG_EVENT_MOUSE_PRESSED		=	5,
	FG_EVENT_MOUSE_RELEASED		=	6,
	FG_EVENT_MOUSE_MOTION		=	7,

	FG_EVENT_SWIPE_X			=	8,
	FG_EVENT_SWIPE_Y			=	9,
	FG_EVENT_SWIPE_XY			=	10,
	FG_EVENT_SWIPE_ANGLE		=	10,

	FG_EVENT_SWIPE_PINCH		=	12,

	FG_EVENT_MULTI_SWIPE_ROTATE	=	13,

	FG_EVENT_KEY_DOWN			=	14,
	FG_EVENT_KEY_UP				=	15,

	FG_EVENT_RESOURCE_LOADED	=	16,
	FG_EVENT_RESOURCE_RELEASED	=	17,
	FG_EVENT_RESOURCE_REQUESTED	=	18,

	FG_EVENT_PROGRAM_INIT		=	19,

	FG_EVENT_VERTEX_STREAM_READY=	20,
	FG_EVENT_CAMERA_CHANGED		=	21,
	
	FG_EVENT_SOUND_PLAYED		=	22,

	FG_EVENT_MENU_CHANGED		=	23,
	FG_EVENT_WIDGET_STATE_CHANGED=	24,

	FG_EVENT_SENSORS_CHANGED	=	25,

	FG_EVENT_RESERVED1,
	FG_EVENT_RESERVED2,
	FG_NUM_EVENT_TYPES
};

enum fgSwipeDirection
{
	FG_SWIPE_INVALID,
	FG_SWIPE_LEFT,
	FG_SWIPE_RIGHT,
	FG_SWIPE_UP,
	FG_SWIPE_DOWN,
	FG_SWIPE_ANGLE
};

enum fgPinchDirection
{
	FG_PINCH_INVALID,
	FG_PINCH_IN,
	FG_PINCH_OUT
};

// FIXME this should be declared in the ResourceManager header file - well I think so...
enum fgResourceStatus
{
	FG_RESOURCE_LOADED,
	FG_RESOURCE_RELEASED,
	FG_RESOURCE_REQUESTED
};

struct fgTouchEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	int x;
	int y;
	fgBool pressed;
	unsigned int touchID;
};

struct fgMouseEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	int x;
	int y;
	fgBool pressed;
	unsigned int buttonID;
};

struct fgSwipeEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
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

struct fgSwipePinchEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	fgPinchDirection pinchDirection;
	int x;
	int y;
	int x2;
	int y2;
	int pinchXOffset;
	int pinchYOffset;
	int pinchSize;
};

struct fgSwipeRotateEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	int x;
	int y;
	int x2;
	int y2;
	float angle;
};

struct fgKeyEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	int keyCode;
	fgBool pressed;
};

struct fgResourceEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	fgResourceStatus resourceStatus;
	//fgResource *resourceHolder;
	//FG_RHANDLE resourceHandle;
};

struct fgVertexStreamEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	//FG_GFXHANDLE vertexStreamHandle;
	//fgVertexStream *vertexStreamHolder;
};

struct fgCameraEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	//GfxCamera *cameraHolder;
	//FG_GFXHANDLE cameraHandle;
};

struct fgSoundEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	//FG_RHANDLE soundHandle;
	//fgResource *soundHolder;
};

struct fgMenuChangedEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	//GUIHANDLE 
	//
};

struct fgWidgetEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	//FG_GUIHANDLE widgetHandle;
	//fgWidget
	//fgResource
};

struct fgSensorsEvent {
	fgEventType eventType;
	unsigned long int timeStamp;
	// int type; or fgSensorType type;
	union {
		struct {
			float  x,y,z;
		};
		float data[3];
	};
};

struct fgEvent {
	union {
		fgEventType eventType;
		unsigned long int timeStamp;

		fgTouchEvent touchEvent;
		fgMouseEvent mouseEvent;
		fgSwipeEvent swipeEvent;
		fgSwipePinchEvent swipePinchEvent;
		fgSwipeRotateEvent swipeRotateEvent;
		fgKeyEvent keyEvent;
		fgResourceEvent resourceEvent;
		fgVertexStreamEvent vertexStreamEvent;
		fgCameraEvent cameraEvent;
		fgSoundEvent soundEvent;
		fgMenuChangedEvent menuChangedEvent;
		fgWidgetEvent widgetEvent;
		fgSensorsEvent sensorsEvent;
	};
};

#endif /* _FG_EVENT_DEFINITIONS_H_ */
