/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgCommon.h"
#include "fgTouchReceiver.h"

#include <cstdlib>
#include <cmath>

#include "Util/fgMemory.h"
#include "Util/fgTime.h"
#include "Hardware/fgHardwareState.h"
#include "Event/fgEventManager.h"

const unsigned int fgTouchReceiver::MAX_TOUCH_POINTS = 10;

template <>
bool fgSingleton<fgTouchReceiver>::instanceFlag = false;

template <>
fgTouchReceiver *fgSingleton<fgTouchReceiver>::instance = NULL;

/**
 * Private constructor
 * #low                                        BlockSize    TapSize
 * 240◊320      {[S3E]DispAreaQ==76800}          17.8f
 * 320x480      {[S3E]DispAreaQ==153600} iPod                  5
 * 400x800      {[S3E]DispAreaQ==320000}
 * 480x800      {[S3E]DispAreaQ==384000} Gx SII  46.1f         16
 *
 * #medium
 * 540x960      {[S3E]DispAreaQ==518400}         55.0f         19
 * 640x960      {[S3E]DispAreaQ==614400}
 * 600x1024     {[S3E]DispAreaQ==614400}         59.0f
 *
 * #upper medium
 * 768x1024     {[S3E]DispAreaQ==786432} iPad1/2               30 (reference)
 * 768x1280     {[S3E]DispAreaQ==983040}
 * 800x1280     {[S3E]DispAreaQ==1024000}        73.8f
 *
 * #high
 * 1200x1920	{[S3E]DispAreaQ==2304000}        110.7f
 * 1536x2048	{[S3E]DispAreaQ==3145728} iPad3  118.1f        120
 *
 */
fgTouchReceiver::fgTouchReceiver()  {
    // FIXME
	m_rawTouches.clear();
	m_rawTouchesProcessed.clear();
	m_touchActive.clear();
}

void fgTouchReceiver::initialize(void)
{
	int DispArea = FG_HardwareState->getDisplayArea();

    //
    // Reference DPI and RESOLUTION – of iPod 3Gen
    //

    float reference_dpi = 163.0f;
    float reference_xdpi = 65.0f;
    float reference_ydpi = 97.0f;
    float reference_res = 153600.0f;

    //
    // Reference TAP, X & Y thresholds – of iPod 3Gen
    //

    int reference_tap_size = 10;
    int reference_x_threshold = 10;
    int reference_y_threshold = 10;

    //
    // DPI and RESOLUTION bias of CURRENT device
    //

	float pfactor = FG_HardwareState->getDPI() / reference_dpi;
    float xpfactor = FG_HardwareState->getXDPI() / reference_xdpi;
    float ypfactor = FG_HardwareState->getYDPI() / reference_ydpi;
    float rfactor = sqrt(DispArea / reference_res);

    //
    // Values follow DPI and also RESOLUTION. DPI is used in straight-forward,
    // proportional FACTORS.
    //
    // RESOLUTION is a little hassle. The problem is, that iPad has small DPI,
    // but large RESOLUTION - and the observed TAP SIZE is twice as large
    // as on iPod – which has LARGER dpi!
    //
    // Therefore, if (smallDPI && largeRES) is observed, we use rfactor
    // to bump up the values. This is hoped to match 3rd iPad's RESOLUTION.
    //
    // Also, the opposite is possible: large DPI and small RESOLUTION. This
    // seems to require larger thresholds (Galaxy S2 gives this hint, as its
    // threshold precission varies a little - really a little, so it is not
    // that big deal - only 1.15f bump).
    // 

    int tap_size = lroundf(reference_tap_size * pfactor);
    int x_threshold = lroundf(reference_x_threshold * xpfactor);
    int y_threshold = lroundf(reference_y_threshold * ypfactor);

    // Not that large DPI, and large RESOLUTION ?
    if( pfactor < 1.8f && rfactor > 2.1f ) {
        tap_size *= rfactor;
        x_threshold *= sqrt(rfactor);
        y_threshold *= sqrt(rfactor);
        FG_WriteLog("TouchReceiver: <DPI, >RES bump used[rfactor:%f]", rfactor);
    } else if ( pfactor > 1.4 && rfactor < 1.7 ) {
        // Quite high DPI - and quite low resolution
        x_threshold *= 1.2f;
        y_threshold *= 1.2f;
        FG_WriteLog("TouchReceiver: <DPI, >RES bump used [1.2f]");
    }

    //
    // STORE COMPUTED VALUES
    //

    MAX_OFFSET_FOR_TAP = tap_size;    
    MIN_OFFSET_FOR_SWIPE_X = x_threshold;
    MIN_OFFSET_FOR_SWIPE_Y = y_threshold;    
    MAX_MILLISECONDS_FOR_TAP = 260;

    PIXELS_PER_STEP_X = x_threshold;
    PIXELS_PER_STEP_Y = y_threshold;

    FG_WriteLog("### pfactor: %f, xpfactor: %f, ypfactor: %f, dpi:%d, xdpi:%d, ydpi:%d",
		pfactor, xpfactor, ypfactor, FG_HardwareState->getDPI(), FG_HardwareState->getXDPI(), FG_HardwareState->getYDPI());
    FG_WriteLog("MAX_OFFSET_FOR_TAP: [%d], MIN SWIPE_X: [%d], MIN SWIPE_Y: [%d], PIXELS_PER_X: [%d], PIXELS_PER_Y: [%d]",
              MAX_OFFSET_FOR_TAP, MIN_OFFSET_FOR_SWIPE_X, MIN_OFFSET_FOR_SWIPE_Y, PIXELS_PER_STEP_X, PIXELS_PER_STEP_Y);
}

/**
 * Private Destructor
 */
fgTouchReceiver::~fgTouchReceiver() {
	m_rawTouches.clear();
	m_rawTouchesProcessed.clear();
	m_touchActive.clear();
}

/**
 * Screen touch event.
 * @param point Pointer position
 */
void fgTouchReceiver::handlePointerPressed(fgVector2i point, unsigned int touchID)
{
	if(touchID >= MAX_TOUCH_POINTS) {
		m_rawTouches.erase(touchID);
		return;
	} else if(touchID == 0) {
		m_rawTouches.clear();
	}

    fgTouchRawData & touchData = m_rawTouches[ touchID ];
	m_touchActive[ touchID ] = true;

	// Time stamp of contact with the screen
	touchData.m_pressedMilliseconds = (unsigned long int) FG_GetTicks();

    // Quasi-initial position - reset after each detected SWIPE
	touchData.m_pointerXSwipeInitial = point.x;
	touchData.m_pointerYSwipeInitial = point.y;

	// Initial position – reset after each *Pressed – used for detecting TAP
	touchData.m_pointerXInitial = point.x;
	touchData.m_pointerYInitial = point.y;

	touchData.m_moveX = point.x;
	touchData.m_moveY = point.y;

    //
	// Start & end points = (point.x, point.y)
    //
	touchData.m_pointerXStart = point.x;
	touchData.m_pointerXEnd = point.x;

	touchData.m_pointerYStart = point.y;
	touchData.m_pointerYEnd = point.y;

	//
	// Throwing the proper event
	//

	//fgTouchEvent *touchEvent = (fgTouchEvent *) fgMalloc(sizeof(fgTouchEvent));
	fgTouchEvent *touchEvent = new fgTouchEvent();
	touchEvent->timeStamp = FG_GetTicks();
	touchEvent->pressed = true;
	touchEvent->touchID = touchID;
	touchEvent->x = point.x;
	touchEvent->y = point.y;

	fgArgumentList *argList = new fgArgumentList();
	argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);

	FG_EventManager->throwEvent(FG_EVENT_TOUCH_PRESSED, argList);
}

/**
 * Pointer move event.
 * @param point Pointer position
 */
void fgTouchReceiver::handlePointerMoved(fgVector2i point, unsigned int touchID)
{
	if(touchID >= MAX_TOUCH_POINTS)
		return;
	
	m_touchActive[ touchID ] = true;

	// Essential swipe data
	m_rawTouches[touchID].m_pointerXEnd = point.x;
	m_rawTouches[touchID].m_pointerYEnd = point.y;
	m_rawTouches[touchID].m_moveX = point.x;
	m_rawTouches[touchID].m_moveY = point.y;

	//
	// Throwing the proper event
	//

	fgTouchEvent *touchEvent = (fgTouchEvent *) fgMalloc(sizeof(fgTouchEvent));
	touchEvent->timeStamp = FG_GetTicks();
	touchEvent->pressed = true;
	touchEvent->touchID = touchID;
	touchEvent->x = point.x;
	touchEvent->y = point.y;

	fgArgumentList *argList = new fgArgumentList();
	argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);

	FG_EventManager->throwEvent(FG_EVENT_TOUCH_MOTION, argList);
}

/**
 * Pointer released.
 * @param point Pointer position
 */
void fgTouchReceiver::handlePointerReleased(fgVector2i point, unsigned int touchID)
{
	if(touchID >= MAX_TOUCH_POINTS)
		return;

    fgTouchRawData & touchData = m_rawTouches[ touchID ];
	m_touchActive[ touchID ] = false;

	// Time stamp of contact with the screen
	touchData.m_releasedMilliseconds = (unsigned long int) FG_GetTicks();

    // 
	// Releasing releasing the pointer means no actions should be
    // taken – i.e. endPoint == startPoint == swipeInitial
    //
	touchData.m_pointerXStart = touchData.m_pointerXEnd = point.x;
    touchData.m_pointerXSwipeInitial = point.x;

	touchData.m_pointerYStart = touchData.m_pointerYEnd = point.y;
    touchData.m_pointerYSwipeInitial = point.y;

	touchData.m_moveX = point.x;
	touchData.m_moveY = point.y;

    // Full press occured: touch + release
	touchData.m_pressOccured = true;

	//
	// Throwing the proper event
	//
	//fgTouchEvent *touchEvent = (fgTouchEvent *) fgMalloc(sizeof(fgTouchEvent));
	fgTouchEvent *touchEvent = new fgTouchEvent();
	touchEvent->timeStamp = FG_GetTicks();
	touchEvent->pressed = false; // Touch is released
	touchEvent->touchID = touchID;
	touchEvent->x = point.x;
	touchEvent->y = point.y;

	fgArgumentList *argList = new fgArgumentList();
	argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);

	FG_EventManager->throwEvent(FG_EVENT_TOUCH_RELEASED, argList);
}

fgTouchRawData fgTouchReceiver::getTouchData(unsigned int touchID)
{
	fgTouchRawData empty;
	if(touchID >= m_rawTouchesProcessed.size())
		return empty;

	return m_rawTouchesProcessed[touchID];
}

bool fgTouchReceiver::getTouchStatus(unsigned int touchID)
{
	if(touchID >= m_touchActive.size())
		return false;

	return m_touchActive[touchID];
}

void fgTouchReceiver::processData()
{
	for(std::map<int, fgTouchRawData>::iterator touchIt = m_rawTouches.begin();
			touchIt != m_rawTouches.end();
			touchIt++)
	{
		int touchID = touchIt->first;
		fgTouchRawData & touchPtr = touchIt->second;
        //
		// DETECT TAP
        //
		touchPtr.m_pointerTap = false;
		if( touchPtr.m_pressOccured )
		{
			// TIME CRITERION
			int delta_time = touchPtr.m_releasedMilliseconds - touchPtr.m_pressedMilliseconds;
			if( delta_time < MAX_MILLISECONDS_FOR_TAP)
			{
				// SPACE CRITERION
				if( abs(touchPtr.m_pointerXEnd - touchPtr.m_pointerXInitial) <= MAX_OFFSET_FOR_TAP &&
					abs(touchPtr.m_pointerYEnd - touchPtr.m_pointerYInitial) <= MAX_OFFSET_FOR_TAP)
				{
					touchPtr.m_pointerTap = true;
					touchPtr.m_tapX = (touchPtr.m_pointerXInitial + touchPtr.m_pointerXEnd) / 2;
					touchPtr.m_tapY = (touchPtr.m_pointerYInitial + touchPtr.m_pointerYEnd) / 2;
					FG_WriteLog("TouchRcvr:: Tap (x,y)=(%d,%d)", touchPtr.m_tapX, touchPtr.m_tapY);

					//
					// Throwing the proper event
					//
					//fgTouchEvent *touchEvent = (fgTouchEvent *) fgMalloc(sizeof(fgTouchEvent));
					fgTouchEvent *touchEvent = new fgTouchEvent();
					touchEvent->timeStamp = FG_GetTicks();
					touchEvent->pressed = false;
					touchEvent->touchID = touchID;
					touchEvent->x = touchPtr.m_tapX;
					touchEvent->y = touchPtr.m_tapY;

					fgArgumentList *argList = new fgArgumentList();
					argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);

					FG_EventManager->throwEvent(FG_EVENT_TOUCH_TAP_FINISHED, argList);

				} else {
                    FG_WriteLog("TouchRcvr:: Space criterion NOT TRUE: x_delta = %d, y_delta = %d", abs(touchPtr.m_pointerXEnd - touchPtr.m_pointerXInitial), 
                                                                                                    abs(touchPtr.m_pointerYEnd - touchPtr.m_pointerYInitial) );
                }
			} else {
                FG_WriteLog("TouchRcvr:: Time criterion NOT TRUE: delta_time = %d", delta_time);
            }

			// After processing press, erase collected data
			touchPtr.m_pressedMilliseconds = 0;
			touchPtr.m_releasedMilliseconds = 0;
			// ...and also extra data allowing to detect tap:
			touchPtr.m_pressOccured = false;
		}

		if( touchPtr.m_pointerTap ) {
			// No simultaneous tap & swipe
			touchPtr.m_swipeXSize = 0;
			touchPtr.m_swipeLeft = false;
			touchPtr.m_swipeRight = false;

			touchPtr.m_swipeYSize = 0;
			touchPtr.m_swipeUp = false;
			touchPtr.m_swipeDown = false;

			touchPtr.m_xSwipeSteps = 0;
			touchPtr.m_ySwipeSteps = 0;
			touchPtr.m_swipeXSize = 0;
			touchPtr.m_swipeYSize = 0;
		}
		else
		{
            //
			// NO TAP – MAYBE SWIPES
            //
            
            // Basic swipe – always reported
            touchPtr.m_basicSwipeXSize = touchPtr.m_pointerXEnd - touchPtr.m_pointerXStart;
            touchPtr.m_basicSwipeYSize = touchPtr.m_pointerYEnd - touchPtr.m_pointerYStart;

            // Advanced, logical swipes
			interpretSwipes(MIN_OFFSET_FOR_SWIPE_X, touchPtr.m_pointerXStart, touchPtr.m_pointerXEnd, touchPtr.m_pointerXSwipeInitial, // IN
								&touchPtr.m_swipeLeft, &touchPtr.m_swipeRight, &touchPtr.m_swipeXSize); // OUT

			interpretSwipes(MIN_OFFSET_FOR_SWIPE_Y, touchPtr.m_pointerYStart, touchPtr.m_pointerYEnd, touchPtr.m_pointerYSwipeInitial, // IN
								&touchPtr.m_swipeUp, &touchPtr.m_swipeDown, &touchPtr.m_swipeYSize); // OUT

			touchPtr.m_xSwipeSteps = touchPtr.m_swipeXSize / PIXELS_PER_STEP_X;
			touchPtr.m_ySwipeSteps = touchPtr.m_swipeYSize / PIXELS_PER_STEP_Y;
			touchPtr.m_swipeXSize %= PIXELS_PER_STEP_X;
			touchPtr.m_swipeYSize %= PIXELS_PER_STEP_Y;

			//
			// Throwing the proper event
			//
			if (touchPtr.m_swipeLeft || touchPtr.m_swipeRight || touchPtr.m_swipeUp || touchPtr.m_swipeDown) {
				//fgSwipeEvent *swipeEvent = (fgSwipeEvent *) fgMalloc(sizeof(fgSwipeEvent));
				fgSwipeEvent *swipeEvent = new fgSwipeEvent();
				swipeEvent->timeStamp = FG_GetTicks();
				bool X=false, Y=false;
				if(touchPtr.m_swipeDown) {
					swipeEvent->swipeDirection = FG_SWIPE_DOWN;
					Y = true;
				} else if(touchPtr.m_swipeUp) {
					swipeEvent->swipeDirection = FG_SWIPE_UP;
					Y = true;
				} 
				if(touchPtr.m_swipeLeft) {
					swipeEvent->swipeDirection = FG_SWIPE_LEFT;
					X = true;
				} else if(touchPtr.m_swipeRight) {
					swipeEvent->swipeDirection = FG_SWIPE_RIGHT;
					X = true;
				}
				swipeEvent->swipeXOffset = touchPtr.m_basicSwipeXSize;
				swipeEvent->swipeYOffset = touchPtr.m_basicSwipeYSize;

				swipeEvent->swipeXSteps = touchPtr.m_xSwipeSteps;
				swipeEvent->swipeYSteps = touchPtr.m_ySwipeSteps;

				swipeEvent->xStart = touchPtr.m_pointerXStart;
				swipeEvent->yStart = touchPtr.m_pointerYStart;

				swipeEvent->xEnd = touchPtr.m_pointerXEnd;
				swipeEvent->yEnd = touchPtr.m_pointerYEnd;

				fgArgumentList *argList = new fgArgumentList();
				argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)swipeEvent);

				if(X && Y)
					FG_EventManager->throwEvent(FG_EVENT_SWIPE_XY, argList);
				else if(X)
					FG_EventManager->throwEvent(FG_EVENT_SWIPE_X, argList);
				else if(Y)
					FG_EventManager->throwEvent(FG_EVENT_SWIPE_Y, argList);
			}

			// If swipe in Y is much larger than
			// swipe in X, then discard swipe in X // FIXME
			/*if( fabsf(touchPtr.m_swipeYSize) >= fabsf(touchPtr.m_swipeXSize * 1.3f) )
			{
				touchPtr.m_swipeXSize = 0;
				touchPtr.m_swipeLeft = false;
				touchPtr.m_swipeRight = false;
			}
			else
			{
				// The same for X!
				if( fabsf(touchPtr.m_swipeXSize) >= fabsf(touchPtr.m_swipeYSize * 1.3f) )
				{
					touchPtr.m_swipeYSize = 0;
					touchPtr.m_swipeUp = false;
					touchPtr.m_swipeDown = false;
				}
			}*/ // FIXME
		}

		// COPIES DATA
		m_rawTouchesProcessed[touchID] = touchPtr;

        //
        // Forget some part of POINTER DATA
        // (we may be inside serie of Move events,
        // so data should be in general preserved)
        //
        touchPtr.m_pointerXStart = touchPtr.m_pointerXEnd;
        touchPtr.m_pointerYStart = touchPtr.m_pointerYEnd;

        // Reset the swipe-initial position, so that swipe detection will be harder again
        if (touchPtr.m_swipeLeft || touchPtr.m_swipeRight || touchPtr.m_swipeUp || touchPtr.m_swipeDown) {
            //
            // Reset X and Y – whichever of them won - it took all!
            // (For example, if X swipe occured, it will reset
            // YSwipeInitial, making Y swipe harder)
            //
            touchPtr.m_pointerXSwipeInitial = touchPtr.m_pointerXEnd;
            touchPtr.m_pointerYSwipeInitial = touchPtr.m_pointerYEnd;
        }
	}
}

/**
 * Detects if swipe occured and computes its size.
 *
 * The initialPointer is used to detect occurence,
 * startPointer to compute size.
 */
void fgTouchReceiver::interpretSwipes(int min_offset_for_swipe, int startPointer, int endPointer, int initialSwipePointer, // IN
                                    bool* minusSwipe, bool* plusSwipe, int* swipeSize) // OUT
{    
    // This is physical swipe lenght - not necesarily
    // software swipe (it will become software swipe
    // if min_offset_for_swipe threshold will be fulfilled).
    int offset = endPointer - initialSwipePointer;
	
    // Store the basic-size of physical swipe
	*swipeSize = offset;
    
	// Is there any swipe?
	if( abs(offset) < min_offset_for_swipe ) {
			// No swipe
			*minusSwipe = *plusSwipe = false;
			return;
	}

	//
	// SWIPE DETECTED
	//

	if (offset < 0)
	{
		// LEFT or UP swipe
		*minusSwipe = true;
		*plusSwipe = false;
	}
	else
	{
		// RIGHT or DOWN swipe
		*minusSwipe = false;
		*plusSwipe = true;
	}
}
