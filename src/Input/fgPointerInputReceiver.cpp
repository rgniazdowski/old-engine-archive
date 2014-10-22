/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgCommon.h"
#include "fgPointerInputReceiver.h"
#include "fgLog.h"
#include "Util/fgMemory.h"
#include "Util/fgTime.h"
#include "Hardware/fgHardwareState.h"
#include "Event/fgEventManager.h"

#include <cstdlib>
#include <cmath>

#if defined(FG_USING_MARMALADE)
#ifndef lround
#define lround lroundf
#endif
#include "s3eTypes.h"
#include "s3ePointer.h"
#elif defined(FG_USING_SDL2)
#include <SDL2/SDL_events.h>
#endif


const unsigned int fgPointerInputReceiver::MAX_TOUCH_POINTS = FG_INPUT_MAX_TOUCH_POINTS;

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
fgPointerInputReceiver::fgPointerInputReceiver(fgEventManager *eventMgr) :
m_eventMgr(eventMgr),
m_init(FG_FALSE),
m_useMultitouch(FG_FALSE),
m_pointerAvailable(FG_FALSE) {
    memset((void *)m_rawTouches, 0, sizeof (m_rawTouches));
    memset((void *)m_rawTouchesProcessed, 0, sizeof (m_rawTouchesProcessed));
}

/*
 *
 */
void fgPointerInputReceiver::initialize(void) {
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

    int tap_size = lround(reference_tap_size * pfactor);
    int x_threshold = lround(reference_x_threshold * xpfactor);
    int y_threshold = lround(reference_y_threshold * ypfactor);

    // Not that large DPI, and large RESOLUTION ?
    if(pfactor < 1.8f && rfactor > 2.1f) {
        tap_size *= rfactor;
        x_threshold *= sqrt(rfactor);
        y_threshold *= sqrt(rfactor);
        FG_LOG::PrintDebug("TouchReceiver: <DPI, >RES bump used[rfactor:%f]", rfactor);
    } else if(pfactor > 1.4 && rfactor < 1.7) {
        // Quite high DPI - and quite low resolution
        x_threshold *= 1.2f;
        y_threshold *= 1.2f;
        FG_LOG::PrintDebug("TouchReceiver: <DPI, >RES bump used [1.2f]");
    }

    //
    // STORE COMPUTED VALUES
    //
    //if()

    MAX_OFFSET_FOR_TAP = tap_size;
    MIN_OFFSET_FOR_SWIPE_X = x_threshold;
    MIN_OFFSET_FOR_SWIPE_Y = y_threshold;
    MAX_MILLISECONDS_FOR_TAP = 260;

    PIXELS_PER_STEP_X = x_threshold;
    PIXELS_PER_STEP_Y = y_threshold;

    FG_LOG::PrintDebug("### pfactor: %f, xpfactor: %f, ypfactor: %f, dpi:%d, xdpi:%d, ydpi:%d",
                       pfactor, xpfactor, ypfactor, FG_HardwareState->getDPI(), FG_HardwareState->getXDPI(), FG_HardwareState->getYDPI());
    FG_LOG::PrintDebug("MAX_OFFSET_FOR_TAP: [%d], MIN SWIPE_X: [%d], MIN SWIPE_Y: [%d], PIXELS_PER_X: [%d], PIXELS_PER_Y: [%d]",
                       MAX_OFFSET_FOR_TAP, MIN_OFFSET_FOR_SWIPE_X, MIN_OFFSET_FOR_SWIPE_Y, PIXELS_PER_STEP_X, PIXELS_PER_STEP_Y);

#if defined(FG_USING_MARMALADE)
    m_pointerAvailable = s3ePointerGetInt(S3E_POINTER_AVAILABLE) ? FG_TRUE : FG_FALSE;
    // Register for touches
    m_useMultitouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? FG_TRUE : FG_FALSE;
    if(m_useMultitouch) {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, &fgPointerInputReceiver::multiTouchButtonHandler, (void *)this);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &fgPointerInputReceiver::multiTouchMotionHandler, (void *)this);
    } else {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, &fgPointerInputReceiver::singleTouchButtonHandler, (void *)this);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, &fgPointerInputReceiver::singleTouchMotionHandler, (void *)this);
    }
#elif defined(FG_USING_SDL2)
    m_pointerAvailable = FG_TRUE;
#endif
    m_init = FG_TRUE;
}

/**
 * Private Destructor
 */
fgPointerInputReceiver::~fgPointerInputReceiver() {
    memset((void *)m_rawTouches, 0, sizeof (m_rawTouches));
    memset((void *)m_rawTouchesProcessed, 0, sizeof (m_rawTouchesProcessed));
#if defined(FG_USING_MARMALADE)
    if(m_useMultitouch) {
        s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, &fgPointerInputReceiver::multiTouchButtonHandler);
        s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &fgPointerInputReceiver::multiTouchMotionHandler);
    } else {
        s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, &fgPointerInputReceiver::singleTouchButtonHandler);
        s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, &fgPointerInputReceiver::singleTouchMotionHandler);
    }
#endif
}

/**
 * Screen touch event.
 * @param point Pointer position
 */
void fgPointerInputReceiver::handlePointerPressed(fgVector2i point, unsigned int touchID) {
    if(touchID >= MAX_TOUCH_POINTS) {
        return;
    } else if(touchID == 0) {
        memset((void *)m_rawTouches, 0, sizeof (m_rawTouches));
    }

    fgPointerRawData & touchData = m_rawTouches[ touchID ];
    touchData.m_touchID = touchID;

    // Time stamp of contact with the screen
    touchData.m_pressedMilliseconds = (unsigned long int)FG_GetTicks();

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

    touchData.m_pressed = FG_TRUE;
    touchData.m_state = FG_POINTER_STATE_PRESSED;
    //
    // Throwing the proper event
    //
    if(m_eventMgr) { // #FIXME
        fgTouchEvent *touchEvent = new fgTouchEvent();
        touchEvent->eventType = FG_EVENT_TOUCH_PRESSED;
        touchEvent->timeStamp = FG_GetTicks();
        touchEvent->pressed = FG_TRUE;
        touchEvent->touchID = touchID;
        touchEvent->x = point.x;
        touchEvent->y = point.y;

        fgArgumentList *argList = new fgArgumentList();
        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        m_eventMgr->throwEvent(FG_EVENT_TOUCH_PRESSED, argList);

        // Throw also more general event
        touchEvent = new fgTouchEvent(*touchEvent);
        argList = new fgArgumentList();
        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        m_eventMgr->throwEvent(FG_EVENT_TOUCH, argList);
    }
}

/**
 * Pointer move event.
 * @param point Pointer position
 */
void fgPointerInputReceiver::handlePointerMoved(fgVector2i point, unsigned int touchID, fgPointerState state) {
    if(touchID >= MAX_TOUCH_POINTS)
        return;

    m_rawTouches[touchID].m_touchID = touchID;
    m_rawTouches[touchID].m_pressed = (state ? FG_TRUE : FG_FALSE);
    m_rawTouches[touchID].m_state = state;
    // Essential swipe data
    m_rawTouches[touchID].m_pointerXEnd = point.x;
    m_rawTouches[touchID].m_pointerYEnd = point.y;
    m_rawTouches[touchID].m_moveX = point.x;
    m_rawTouches[touchID].m_moveY = point.y;

    //
    // Throwing the proper event
    //
    if(m_eventMgr) {
        fgTouchEvent *touchEvent = new fgTouchEvent();
        touchEvent->eventType = FG_EVENT_TOUCH_MOTION;
        touchEvent->timeStamp = FG_GetTicks();
        touchEvent->pressed = m_rawTouches[touchID].m_pressed;
        touchEvent->touchID = touchID;
        touchEvent->x = point.x;
        touchEvent->y = point.y;

        fgArgumentList *argList = new fgArgumentList();
        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        m_eventMgr->throwEvent(FG_EVENT_TOUCH_MOTION, argList);

        // Throw also more general event
        touchEvent = new fgTouchEvent(*touchEvent);
        argList = new fgArgumentList();
        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        m_eventMgr->throwEvent(FG_EVENT_TOUCH, argList);
    }
}

/**
 * Pointer released.
 * @param point Pointer position
 */
void fgPointerInputReceiver::handlePointerReleased(fgVector2i point, unsigned int touchID) {
    if(touchID >= MAX_TOUCH_POINTS)
        return;

    fgPointerRawData & touchData = m_rawTouches[ touchID ];
    touchData.m_state = FG_POINTER_STATE_RELEASED;
    touchData.m_pressed = FG_FALSE;
    touchData.m_touchID = touchID;
    // Time stamp of contact with the screen
    touchData.m_releasedMilliseconds = (unsigned long int)FG_GetTicks();

    // 
    // Releasing the pointer means no actions should be
    // taken – i.e. endPoint == startPoint == swipeInitial
    //
    touchData.m_pointerXStart = touchData.m_pointerXEnd = point.x;
    touchData.m_pointerXSwipeInitial = point.x;

    touchData.m_pointerYStart = touchData.m_pointerYEnd = point.y;
    touchData.m_pointerYSwipeInitial = point.y;

    touchData.m_moveX = point.x;
    touchData.m_moveY = point.y;

    // Full press occured: touch + release
    touchData.m_pressOccured = FG_TRUE;

    //
    // Throwing the proper event
    //
    if(m_eventMgr) {
        fgTouchEvent *touchEvent = fgMalloc<fgTouchEvent>();
        touchEvent->eventType = FG_EVENT_TOUCH_RELEASED;
        touchEvent->timeStamp = FG_GetTicks();
        touchEvent->pressed = FG_FALSE; // Touch is released
        touchEvent->touchID = touchID;
        touchEvent->x = point.x;
        touchEvent->y = point.y;

        fgArgumentList *argList = new fgArgumentList();
        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        m_eventMgr->throwEvent(FG_EVENT_TOUCH_RELEASED, argList);

        // Throw also more general event
        touchEvent = new fgTouchEvent(*touchEvent);
        argList = new fgArgumentList();
        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        m_eventMgr->throwEvent(FG_EVENT_TOUCH, argList);
    }
}

/*
 *
 */
fgPointerRawData *fgPointerInputReceiver::getPointerRawData(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return NULL;

    return &m_rawTouchesProcessed[pointerID];
}

/*
 *
 */
fgPointerData *fgPointerInputReceiver::getPointerData(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return NULL;

    return ((fgPointerData *)(&m_rawTouchesProcessed[pointerID]));
}

/*
 *
 */
fgPointerState fgPointerInputReceiver::getPointerState(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return FG_FALSE;

    return m_rawTouchesProcessed[pointerID].m_state;
}

/*
 *
 */
int fgPointerInputReceiver::getPointerX(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return 0;
    return m_rawTouchesProcessed[pointerID].m_x;
}

/*
 *
 */
int fgPointerInputReceiver::getPointerY(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return 0;
    return m_rawTouchesProcessed[pointerID].m_y;
}

/*
 *
 */
void fgPointerInputReceiver::processData(void) {
    if(!m_pointerAvailable)
        return;
#if defined(FG_USING_MARMALADE)
    s3ePointerUpdate();
#endif
    for(unsigned int i = 0; i < MAX_TOUCH_POINTS; i++) {
        int touchID = i;
        fgPointerRawData & touchPtr = m_rawTouches[i];
        //
        // DETECT TAP
        //
        touchPtr.m_pointerTap = FG_FALSE;
        if(touchPtr.m_pressOccured) {
            // TIME CRITERION
            int delta_time = touchPtr.m_releasedMilliseconds - touchPtr.m_pressedMilliseconds;
            if(delta_time < MAX_MILLISECONDS_FOR_TAP) {
                // SPACE CRITERION
                if(abs(touchPtr.m_pointerXEnd - touchPtr.m_pointerXInitial) <= MAX_OFFSET_FOR_TAP &&
                   abs(touchPtr.m_pointerYEnd - touchPtr.m_pointerYInitial) <= MAX_OFFSET_FOR_TAP) {
                    touchPtr.m_pointerTap = FG_TRUE;
                    touchPtr.m_tapX = (touchPtr.m_pointerXInitial + touchPtr.m_pointerXEnd) / 2;
                    touchPtr.m_tapY = (touchPtr.m_pointerYInitial + touchPtr.m_pointerYEnd) / 2;
                    FG_LOG::PrintDebug("TouchRcvr:: Tap (x,y)=(%d,%d)", touchPtr.m_tapX, touchPtr.m_tapY);

                    //
                    // Throwing the proper event
                    //
                    if(m_eventMgr) {
                        fgTouchEvent *touchEvent = fgMalloc<fgTouchEvent>();
                        touchEvent->eventType = FG_EVENT_TOUCH_TAP_FINISHED;
                        touchEvent->timeStamp = FG_GetTicks();
                        touchEvent->pressed = FG_FALSE;
                        touchEvent->touchID = touchPtr.m_touchID;
                        touchEvent->x = touchPtr.m_tapX;
                        touchEvent->y = touchPtr.m_tapY;

                        fgArgumentList *argList = new fgArgumentList();
                        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
                        m_eventMgr->throwEvent(FG_EVENT_TOUCH_TAP_FINISHED, argList);

                        touchEvent = new fgTouchEvent(*touchEvent);
                        argList = new fgArgumentList();
                        argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
                        m_eventMgr->throwEvent(FG_EVENT_TOUCH, argList);
                    }

                } else {
                    FG_LOG::PrintDebug("TouchRcvr:: Space criterion NOT TRUE: x_delta = %d, y_delta = %d", abs(touchPtr.m_pointerXEnd - touchPtr.m_pointerXInitial),
                                       abs(touchPtr.m_pointerYEnd - touchPtr.m_pointerYInitial));
                }
            } else {
                FG_LOG::PrintDebug("TouchRcvr:: Time criterion NOT TRUE: delta_time = %d", delta_time);
            }

            // After processing press, erase collected data
            touchPtr.m_pressedMilliseconds = 0;
            touchPtr.m_releasedMilliseconds = 0;
            // ...and also extra data allowing to detect tap:
            touchPtr.m_pressOccured = FG_FALSE;
        }

        if(touchPtr.m_pointerTap) {
            // No simultaneous tap & swipe
            touchPtr.m_swipeXSize = 0;
            touchPtr.m_swipeLeft = FG_FALSE;
            touchPtr.m_swipeRight = FG_FALSE;

            touchPtr.m_swipeYSize = 0;
            touchPtr.m_swipeUp = FG_FALSE;
            touchPtr.m_swipeDown = FG_FALSE;

            touchPtr.m_xSwipeSteps = 0;
            touchPtr.m_ySwipeSteps = 0;
            touchPtr.m_swipeXSize = 0;
            touchPtr.m_swipeYSize = 0;
        } else {
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
            if(touchPtr.m_swipeLeft || touchPtr.m_swipeRight || touchPtr.m_swipeUp || touchPtr.m_swipeDown) {
                if(m_eventMgr) {
                    fgSwipeEvent *swipeEvent = fgMalloc<fgSwipeEvent>();
                    swipeEvent->timeStamp = FG_GetTicks();
                    fgBool X = FG_FALSE, Y = FG_FALSE;
                    if(touchPtr.m_swipeDown) {
                        swipeEvent->swipeDirection = FG_SWIPE_DOWN;
                        Y = FG_TRUE;
                    } else if(touchPtr.m_swipeUp) {
                        swipeEvent->swipeDirection = FG_SWIPE_UP;
                        Y = FG_TRUE;
                    }
                    if(touchPtr.m_swipeLeft) {
                        swipeEvent->swipeDirection = FG_SWIPE_LEFT;
                        X = FG_TRUE;
                    } else if(touchPtr.m_swipeRight) {
                        swipeEvent->swipeDirection = FG_SWIPE_RIGHT;
                        X = FG_TRUE;
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

                    if(X && Y) {
                        swipeEvent->eventType = FG_EVENT_SWIPE_XY;
                        m_eventMgr->throwEvent(FG_EVENT_SWIPE_XY, argList);
                    } else if(X) {
                        swipeEvent->eventType = FG_EVENT_SWIPE_X;
                        m_eventMgr->throwEvent(FG_EVENT_SWIPE_X, argList);
                    } else if(Y) {
                        swipeEvent->eventType = FG_EVENT_SWIPE_Y;
                        m_eventMgr->throwEvent(FG_EVENT_SWIPE_Y, argList);
                    }
                }
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
        if(touchPtr.m_swipeLeft || touchPtr.m_swipeRight || touchPtr.m_swipeUp || touchPtr.m_swipeDown) {
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
void fgPointerInputReceiver::interpretSwipes(int min_offset_for_swipe, int startPointer, int endPointer, int initialSwipePointer, // IN
                                             fgBool* minusSwipe, fgBool* plusSwipe, int* swipeSize) // OUT
{
    // This is physical swipe lenght - not necesarily
    // software swipe (it will become software swipe
    // if min_offset_for_swipe threshold will be fulfilled).
    int offset = endPointer - initialSwipePointer;

    // Store the basic-size of physical swipe
    *swipeSize = offset;

    // Is there any swipe?
    if(abs(offset) < min_offset_for_swipe) {
        // No swipe
        *minusSwipe = *plusSwipe = FG_FALSE;
        return;
    }

    //
    // SWIPE DETECTED
    //
    if(offset < 0) {
        // LEFT or UP swipe
        *minusSwipe = FG_TRUE;
        *plusSwipe = FG_FALSE;
    } else {
        // RIGHT or DOWN swipe
        *minusSwipe = FG_FALSE;
        *plusSwipe = FG_TRUE;
    }
}

/**
 * Touch press/release HANDLER / systemData is event struct / userData - pointer to class
 */
int32_t fgPointerInputReceiver::multiTouchButtonHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    fgPointerInputReceiver *inputReceiver = (fgPointerInputReceiver *)userData;
#if defined(FG_USING_MARMALADE)
    s3ePointerTouchEvent* event = (s3ePointerTouchEvent*)systemData;
    if(!inputReceiver->m_init)
        return 0;
    if(event->m_Pressed) {
        inputReceiver->handlePointerPressed(fgVector2i(event->m_x, event->m_y), event->m_TouchID);
    } else {
        inputReceiver->handlePointerReleased(fgVector2i(event->m_x, event->m_y), event->m_TouchID);
    }
#elif defined(FG_USING_SDL2)
    SDL_TouchFingerEvent *event = (SDL_TouchFingerEvent *)systemData;
    if(event->type != SDL_FINGERMOTION) {
        //        if(event->state == SDL_PRESSED) { 
        //          inputReceiver->handlePointerPressed(fgVector2i(event->x, event->y), (unsigned int)event->button);
        //    } else {
        //      inputReceiver->handlePointerReleased(fgVector2i(event->x, event->y), (unsigned int)event->button);
        // }
    }
#endif
    return 0;
}

/**
 * Touch motion HANDLER / systemData is event struct / userData - pointer to class
 */
int32_t fgPointerInputReceiver::multiTouchMotionHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    fgPointerInputReceiver *inputReceiver = (fgPointerInputReceiver *)userData;
#if defined(FG_USING_MARMALADE)
    s3ePointerTouchMotionEvent* event = (s3ePointerTouchMotionEvent*)systemData;
    if(!inputReceiver->m_init)
        return 0;
    inputReceiver->handlePointerMoved(fgVector2i(event->m_x, event->m_y), event->m_TouchID, FG_POINTER_STATE_PRESSED);
#elif defined(FG_USING_SDL2)
#endif
    return 0;
}

/**
 * Single press/release HANDLER / systemData is event struct / userData - pointer to class
 */
int32_t fgPointerInputReceiver::singleTouchButtonHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    fgPointerInputReceiver *inputReceiver = (fgPointerInputReceiver *)userData;
    if(!inputReceiver->m_init)
        return 0;
#if defined(FG_USING_MARMALADE)
    s3ePointerEvent* event = (s3ePointerEvent*)systemData;
    if(event->m_Pressed) {
        inputReceiver->handlePointerPressed(fgVector2i(event->m_x, event->m_y));
    } else {
        inputReceiver->handlePointerReleased(fgVector2i(event->m_x, event->m_y));
    }
#elif defined(FG_USING_SDL2)
    SDL_MouseButtonEvent *event = (SDL_MouseButtonEvent *)systemData;
    //if(event->type == SDL_PRESSED) { 
    if(event->type == SDL_MOUSEBUTTONDOWN) {
        inputReceiver->handlePointerPressed(fgVector2i(event->x, event->y)); //, (unsigned int)event->button);
    } else {
        inputReceiver->handlePointerReleased(fgVector2i(event->x, event->y)); //, (unsigned int)event->button);
    }
#endif
    return 0;
}

/**
 * Single motion HANDLER / systemData is event struct / userData - pointer to class
 */
int32_t fgPointerInputReceiver::singleTouchMotionHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    fgPointerInputReceiver *inputReceiver = (fgPointerInputReceiver *)userData;
    if(!inputReceiver->m_init)
        return 0;
#if defined(FG_USING_MARMALADE)
    s3ePointerMotionEvent* event = (s3ePointerMotionEvent*)systemData;

    inputReceiver->handlePointerMoved(fgVector2i(event->m_x, event->m_y));
#elif defined(FG_USING_SDL2)
    SDL_MouseMotionEvent *event = (SDL_MouseMotionEvent *)systemData;

    inputReceiver->handlePointerMoved(fgVector2i(event->x, event->y)/*, need ID? */, 0, event->state);
#endif
    return 0;
}