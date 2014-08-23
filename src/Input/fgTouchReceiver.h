/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_TOUCH_RECEIVER_H_
#define _FG_TOUCH_RECEIVER_H_

#include <map>

#include "../fgSingleton.h"
#include "../Math/fgMathLib.h"

#include "fgTouchRawData.h"

/*
 * TouchReceiver receives touch events directly from the MainModule object which contains callbacks hooked directly to the Marmalade subsystem
 * TouchReceiver also interprets touches/swipse and later calls (triggers/throws) proper events. It comunicates directly to the EventManager
 */
class fgTouchReceiver : public fgSingleton<fgTouchReceiver> {

	friend class fgSingleton<fgTouchReceiver>;

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
	std::map<int, fgTouchRawData> m_rawTouchesProcessed;
	std::map<int, fgTouchRawData> m_rawTouches;
	std::map<int, bool> m_touchActive;

	void interpretSwipes(int min_offset_for_swipe, int startPointer, int endPointer, int initialPointer, bool* minusSwipe, bool* plusSwipe, int* swipeSize);
protected:
	fgTouchReceiver();
    ~fgTouchReceiver();
public:
	void initialize(void);

	int pixelsPerStepX(void) const {
		return PIXELS_PER_STEP_X;
	}

	int pixelsPerStepY(void) const {
		return PIXELS_PER_STEP_Y;
	}

	int maxOffsetForTap(void) const {
		return MAX_OFFSET_FOR_TAP;
	}

	void handlePointerPressed(fgVector2i point, unsigned int touchID);
	void handlePointerMoved(fgVector2i point, unsigned int touchID);
	void handlePointerReleased(fgVector2i point, unsigned int touchID);

	// This function will probably be useful only in debugging
	// There's no need to check the data manually - proper events 
	// are being thrown from processData method
	fgTouchRawData getTouchData(unsigned int touchID);
	bool getTouchStatus(unsigned int touchID);

	void processData();

};

#define FG_TouchReceiver fgTouchReceiver::getInstance()

#endif /* TOUCHRECEIVER_H_ */
