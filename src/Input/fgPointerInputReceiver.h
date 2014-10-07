/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_POINTER_INPUT_RECEIVER_H_
#define _FG_POINTER_INPUT_RECEIVER_H_

#include "fgBuildConfig.h"

#include "fgPointerRawData.h"
#include "Math/fgMathLib.h"
#include "Event/fgEventManager.h"

#include <map>

#define FG_INPUT_MAX_TOUCH_POINTS 10

#if defined(FG_USING_MARMALADE)
#include "s3eTypes.h"
#endif

/*
 * TouchReceiver receives touch events directly from the callbacks
*  hooked directly to the Marmalade subsystem.
 * TouchReceiver also interprets touches/swipse and later calls 
 * (triggers/throws) proper events. It comunicates directly to the EventManager
 */
class fgPointerInputReceiver
{
private:
    int MIN_OFFSET_FOR_SWIPE_X;
	int MIN_OFFSET_FOR_SWIPE_Y;

    /** Maximum difference between start and end
     *  point, for an event to be interpreted as TAP.
     *
     *  It does not necessary collide with above SWIPE_*
     *  constants, because it is measured between "Press"
     *  and "Release" events, while SWIPE_* are also used
     *  after "Move" events.
     *
     */
    int MAX_OFFSET_FOR_TAP;

	///  Also, tap is required to be quick!
	int MAX_MILLISECONDS_FOR_TAP;

    int PIXELS_PER_STEP_X;
    int PIXELS_PER_STEP_Y;

public:
  	static const unsigned int MAX_TOUCH_POINTS;

private:
	//
	fgPointerRawData m_rawTouchesProcessed[FG_INPUT_MAX_TOUCH_POINTS+1];
	//
	fgPointerRawData m_rawTouches[FG_INPUT_MAX_TOUCH_POINTS+1];
	//
	fgEventManager	*m_eventMgr;
	//
	fgBool	m_init;
	//
	fgBool  m_useMultitouch;
	//
	fgBool	m_pointerAvailable;

	//
	void interpretSwipes(int min_offset_for_swipe,
		int startPointer,
		int endPointer,
		int initialPointer,
		fgBool* minusSwipe,
		fgBool* plusSwipe,
		int* swipeSize);

public:
	//
	fgPointerInputReceiver(fgEventManager *eventMgr = NULL);
	//
    virtual ~fgPointerInputReceiver();

	//
	void initialize(void);

	//
	int pixelsPerStepX(void) const {
		return PIXELS_PER_STEP_X;
	}

	//
	int pixelsPerStepY(void) const {
		return PIXELS_PER_STEP_Y;
	}

	//
	int maxOffsetForTap(void) const {
		return MAX_OFFSET_FOR_TAP;
	}

	// This function will probably be useful only in debugging
	// There's no need to check the data manually - proper events 
	// are being thrown from processData method
	fgPointerRawData *getPointerRawData(fgPointerID pointerID = 0);
	//
	fgPointerData *getPointerData(fgPointerID pointerID = 0);

	//
	fgPointerState getPointerState(fgPointerID pointerID = 0);
	//
	int getPointerX(fgPointerID pointerID = 0);
	//
	int getPointerY(fgPointerID pointerID = 0);

	//
	void processData(void);

	//
	fgEventManager *getEventManager(void) const {
		return m_eventMgr;
	}

	//
	void setEventManager(fgEventManager *eventMgr) {
		m_eventMgr = eventMgr;
	}

protected:
	//
	void handlePointerPressed(fgVector2i point, unsigned int touchID = 0);
	//
	void handlePointerMoved(fgVector2i point, unsigned int touchID = 0);
	//
	void handlePointerReleased(fgVector2i point, unsigned int touchID = 0);

protected:
	//
	static int32_t multiTouchButtonHandler(void* systemData, void* userData);
	//
	static int32_t multiTouchMotionHandler(void* systemData, void* userData);
	//
	static int32_t singleTouchButtonHandler(void* systemData, void* userData);
	//
	static int32_t singleTouchMotionHandler(void* systemData, void* userData);

};

#endif /* _FG_POINTER_INPUT_RECEIVER_H_ */
