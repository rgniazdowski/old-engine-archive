/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _FG_EVENT_DEFINITIONS_H
#define _FG_EVENT_DEFINITIONS_H

//
// This file will contain all basic events occuring in the game engine
// also defines standard event structures holding info about the event
//

#define FG_EVENT_TOUCH_PRESSED			1
#define FG_EVENT_TOUCH_RELEASED			2
#define FG_EVENT_TOUCH_MOTION			3
#define FG_EVENT_TOUCH_TAP_FINISHED		4

#define FG_EVENT_MOUSE_PRESSED			5
#define FG_EVENT_MOUSE_RELEASED			6
#define FG_EVENT_MOUSE_MOTION			7

#define FG_EVENT_SWIPE_X				8
#define FG_EVENT_SWIPE_Y				9
#define FG_EVENT_SWIPE_XY				10
#define FG_EVENT_SWIPE_ANGLE			10

#define FG_EVENT_SWIPE_PINCH			12

#define FG_EVENT_MULTI_SWIPE_ROTATE		13

#define FG_EVENT_KEY_DOWN				14
#define FG_EVENT_KEY_UP					15

#define FG_EVENT_RESOURCE_LOADED		16
#define FG_EVENT_RESOURCE_RELEASED		17
#define FG_EVENT_RESOURCE_REQUESTED		18

#define FG_EVENT_PROGRAM_INIT			19

#define FG_EVENT_VERTEX_STREAM_READY	20
#define FG_EVENT_CAMERA_CHANGED			21

#define FG_EVENT_SOUND_PLAYED			22

#define FG_EVENT_MENU_CHANGED			23
#define FG_EVENT_WIDGET_STATE_CHANGED	24

#define FG_EVENT_SENSORS_CHANGED		25

enum fgSwipeDirection
{
	FG_SWIPE_LEFT,
	FG_SWIPE_RIGHT,
	FG_SWIPE_UP,
	FG_SWIPE_DOWN,
	FG_SWIPE_ANGLE
};

enum fgPinchDirection
{
	PINCH_IN,
	PINCH_OUT
};

// FIXME this should be declared in the ResourceManager header file - well I think so...
enum fgResourceStatus
{
	FG_RESOURCE_LOADED,
	FG_RESOURCE_RELEASED,
	FG_RESOURCE_REQUESTED
};

typedef struct fgTouchEvent {
	int m_x;
	int m_y;
	bool m_pressed;
	unsigned int m_touchId;
	unsigned long int m_timestamp;
}fgTouchEvent;

typedef struct fgMouseEvent {
	int m_x;
	int m_y;
	bool m_pressed;
	int m_buttonId;
	unsigned long int m_timestamp;
}fgMouseEvent;

typedef struct fgSwipeEvent {
	int m_xStart;
	int m_yStart;
	int m_xEnd;
	int m_yEnd;
	int m_swipeXOffset;
	int m_swipeYOffset;
	int m_swipeXSteps;
	int m_swipeYSteps;
	fgSwipeDirection m_swipeDirection;
	unsigned long int m_timestamp;
}fgSwipeEvent;

typedef struct fgSwipePinchEvent {
	int m_x;
	int m_y;
	int m_x2;
	int m_y2;
	int m_pinchXOffset;
	int m_pinchYOffset;
	int m_pinchSize;
	fgPinchDirection m_pinchDirection;
	unsigned long int m_timestamp;
}fgSwipePinchEvent;

typedef struct fgSwipeRotateEvent {
	int m_x;
	int m_y;
	int m_x2;
	int m_y2;
	float m_angle;
	unsigned long int m_timestamp;
}fgSwipeRotateEvent;

typedef struct fgKeyEvent {
	int m_keyCode;
	int m_pressed;
	unsigned long int m_timestamp;
}fgKeyEvent;

typedef struct fgResourceEvent {
	fgResourceStatus m_resourceStatus;
	unsigned long int m_timestamp;
	//fgResource *m_resourceHolder;
	//FG_RHANDLE m_resourceHandle;
}fgResourceEvent;

typedef struct fgVertexStreamEvent {
	//FG_GFXHANDLE m_vertexStreamHandle;
	//fgVertexStream *m_vertexStreamHolder;
	unsigned long int m_timestamp;
}FG_VertexStreamEvent;

typedef struct fgCameraEvent {
	//GfxCamera *m_cameraHolder;
	//FG_GFXHANDLE m_cameraHandle;
	unsigned long int m_timestamp;
}fgCameraEvent;

typedef struct fgSoundEvent {
	//FG_RHANDLE m_soundHandle;
	//fgResource *m_soundHolder;
	unsigned long int m_timestamp;
}fgSoundEvent;

typedef struct fgMenuChangedEvent {
	//GUIHANDLE m_
	//
	unsigned long int m_timestamp;
}fgMenuChangedEvent;

typedef struct fgWidgetEvent {
	//FG_GUIHANDLE m_widgetHandle;
	//fgWidget
	//fgResource
	unsigned long int m_timestamp;
}fgWidgetEvent;

typedef struct fgSensorsEvent {
	unsigned long int m_timestamp;
	// int m_type; or fgSensorType m_type;
	union {
		struct {
			float  m_x,m_y,m_z;
		};
		float m_data[3];
	};
}fgSensorsEvent;

#endif
