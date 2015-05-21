/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgCommon.h"
#include "fgInputHandler.h"
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

///
const unsigned int fg::event::CInputHandler::MAX_TOUCH_POINTS = FG_INPUT_MAX_TOUCH_POINTS;

using namespace fg;

//------------------------------------------------------------------------------

/**
 * 
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
event::CInputHandler::CInputHandler(CEventManager *eventMgr) :
m_keysDownPool(),
m_keysUpPool(),
m_keyDownBinds(),
m_keyUpBinds(),
m_eventMgr(eventMgr),
m_init(FG_FALSE),
m_useMultitouch(FG_FALSE),
m_pointerAvailable(FG_FALSE) {
    memset((void *)m_rawTouches, 0, sizeof (m_rawTouches));
    memset((void *)m_rawTouchesProcessed, 0, sizeof (m_rawTouchesProcessed));
    memset((void *)m_keyRepeats, 0, sizeof (m_keyRepeats));
}
//------------------------------------------------------------------------------

void event::CInputHandler::initialize(const CHardwareState* pHardwareState) {
    int DispArea = pHardwareState->getDisplayArea();

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

    float pfactor = pHardwareState->getDPI() / reference_dpi;
    float xpfactor = pHardwareState->getXDPI() / reference_xdpi;
    float ypfactor = pHardwareState->getYDPI() / reference_ydpi;
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
        FG_LOG_DEBUG("InputHandler: <DPI> RES bump used[rfactor:%f]", rfactor);
    } else if(pfactor > 1.4 && rfactor < 1.7) {
        // Quite high DPI - and quite low resolution
        x_threshold *= 1.2f;
        y_threshold *= 1.2f;
        FG_LOG_DEBUG("InputHandler: <DPI> RES bump used [1.2f]");
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

    FG_LOG_DEBUG("InputHandler: ### pfactor: %f, xpfactor: %f, ypfactor: %f, dpi:%d, xdpi:%d, ydpi:%d",
                 pfactor, xpfactor, ypfactor, pHardwareState->getDPI(), pHardwareState->getXDPI(), pHardwareState->getYDPI());
    FG_LOG_DEBUG("InputHandler: MAX_OFFSET_FOR_TAP: [%d], MIN SWIPE_X: [%d], MIN SWIPE_Y: [%d], PIXELS_PER_X: [%d], PIXELS_PER_Y: [%d]",
                 MAX_OFFSET_FOR_TAP, MIN_OFFSET_FOR_SWIPE_X, MIN_OFFSET_FOR_SWIPE_Y, PIXELS_PER_STEP_X, PIXELS_PER_STEP_Y);

#if defined(FG_USING_MARMALADE)
    m_pointerAvailable = s3ePointerGetInt(S3E_POINTER_AVAILABLE) ? FG_TRUE : FG_FALSE;
    // Register for touches
    m_useMultitouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? FG_TRUE : FG_FALSE;
    if(m_useMultitouch) {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, &event::CInputHandler::multiTouchButtonHandler, (void *)this);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &event::CInputHandler::multiTouchMotionHandler, (void *)this);
    } else {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, &event::CInputHandler::singleTouchButtonHandler, (void *)this);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, &event::CInputHandler::singleTouchMotionHandler, (void *)this);
    }
#elif defined(FG_USING_SDL2)
    m_pointerAvailable = FG_TRUE;
#else
    m_pointerAvailable = FG_TRUE;
#endif
    m_init = FG_TRUE;
}
//------------------------------------------------------------------------------

event::CInputHandler::~CInputHandler() {
    for(CallbackBindingMap::iterator it = m_keyDownBinds.begin(); it != m_keyDownBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    for(CallbackBindingMap::iterator it = m_keyUpBinds.begin(); it != m_keyUpBinds.end(); it++) {
        for(int i = 0; i < (int)it->second.size(); i++) {
            delete it->second[i];
            it->second[i] = NULL;
        }
        it->second.clear();
    }

    memset((void *)m_rawTouches, 0, sizeof (m_rawTouches));
    memset((void *)m_rawTouchesProcessed, 0, sizeof (m_rawTouchesProcessed));
#if defined(FG_USING_MARMALADE)
    if(m_useMultitouch) {
        s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, &event::CInputHandler::multiTouchButtonHandler);
        s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &event::CInputHandler::multiTouchMotionHandler);
    } else {
        s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, &event::CInputHandler::singleTouchButtonHandler);
        s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, &event::CInputHandler::singleTouchMotionHandler);
    }
#endif
    m_keyDownBinds.clear();
    m_keyUpBinds.clear();
    m_keysUpPool.clear();
    m_keysDownPool.clear();
}
//------------------------------------------------------------------------------

void event::CInputHandler::handlePointerPressed(Vector2i point, unsigned int touchID) {
    if(touchID >= MAX_TOUCH_POINTS) {
        return;
    } else if(touchID == 0) {
        memset((void *)m_rawTouches, 0, sizeof (m_rawTouches));
    }

    SPointerRawData & touchData = m_rawTouches[ touchID ];
    touchData.m_touchID = touchID;

    // Time stamp of contact with the screen
    touchData.m_pressedMilliseconds = timesys::ticks();

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
#if defined(FG_USING_PLATFORM_MOBILE)
        STouch *touchEvent = (STouch *)m_eventMgr->requestEventStruct();
        CArgumentList *argList = m_eventMgr->requestArgumentList();
        touchEvent->eventType = event::TOUCH_PRESSED;
        touchEvent->timeStamp = timesys::ticks();
        touchEvent->pressed = FG_TRUE;
        touchEvent->touchID = touchID;
        touchEvent->x = point.x;
        touchEvent->y = point.y;

        argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)touchEvent);
        m_eventMgr->throwEvent(event::TOUCH_PRESSED, argList);
#else
        SMouse* mouseEvent = (SMouse*)m_eventMgr->requestEventStruct();
        CArgumentList* argList = m_eventMgr->requestArgumentList();
        mouseEvent->eventType = event::MOUSE_PRESSED;
        mouseEvent->timeStamp = timesys::ticks();
        mouseEvent->pressed = FG_TRUE;
        mouseEvent->buttonID = touchID;
        mouseEvent->x = point.x;
        mouseEvent->y = point.y;

        argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)mouseEvent);
        m_eventMgr->throwEvent(event::MOUSE_PRESSED, argList);
#endif

        // Throw also more general event
        //touchEvent = new fgTouchEvent(*touchEvent);
        //argList = new fgArgumentList();
        //argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        //m_eventMgr->throwEvent(event::TOUCH, argList);
    }
}
//------------------------------------------------------------------------------

void event::CInputHandler::handlePointerMoved(Vector2i point,
                                              unsigned int touchID,
                                              fgPointerState state) {
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
#if defined(FG_USING_PLATFORM_MOBILE)
        STouch *touchEvent = (STouch*)m_eventMgr->requestEventStruct();
        CArgumentList *argList = m_eventMgr->requestArgumentList();
        touchEvent->eventType = event::TOUCH_MOTION;
        touchEvent->timeStamp = timesys::ticks();
        touchEvent->pressed = m_rawTouches[touchID].m_pressed;
        touchEvent->touchID = touchID;
        touchEvent->x = point.x;
        touchEvent->y = point.y;

        argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)touchEvent);
        m_eventMgr->throwEvent(event::TOUCH_MOTION, argList);
#else
        SMouse *mouseEvent = (SMouse*)m_eventMgr->requestEventStruct();
        CArgumentList *argList = m_eventMgr->requestArgumentList();
        mouseEvent->eventType = event::MOUSE_MOTION;
        mouseEvent->timeStamp = timesys::ticks();
        mouseEvent->pressed = m_rawTouches[touchID].m_pressed;
        mouseEvent->buttonID = touchID;
        mouseEvent->x = point.x;
        mouseEvent->y = point.y;

        argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)mouseEvent);
        m_eventMgr->throwEvent(event::MOUSE_MOTION, argList);
#endif
        // Throw also more general event
        //touchEvent = new fgTouchEvent(*touchEvent);
        //argList = new fgArgumentList();
        //argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        //m_eventMgr->throwEvent(event::TOUCH, argList);
    }
}
//------------------------------------------------------------------------------

void event::CInputHandler::handlePointerReleased(Vector2i point, unsigned int touchID) {
    if(touchID >= MAX_TOUCH_POINTS)
        return;

    SPointerRawData & touchData = m_rawTouches[ touchID ];
    touchData.m_state = FG_POINTER_STATE_RELEASED;
    touchData.m_pressed = FG_FALSE;
    touchData.m_touchID = touchID;
    // Time stamp of contact with the screen
    touchData.m_releasedMilliseconds = timesys::ticks();

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
#if defined(FG_USING_PLATFORM_MOBILE)
        STouch* touchEvent = (STouch*)m_eventMgr->requestEventStruct();
        CArgumentList* argList = m_eventMgr->requestArgumentList();
        touchEvent->eventType = event::TOUCH_RELEASED;
        touchEvent->timeStamp = timesys::ticks();
        touchEvent->pressed = FG_FALSE; // Touch is released
        touchEvent->touchID = touchID;
        touchEvent->x = point.x;
        touchEvent->y = point.y;

        argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)touchEvent);
        m_eventMgr->throwEvent(event::TOUCH_RELEASED, argList);
#else
        SMouse* mouseEvent = (SMouse*)m_eventMgr->requestEventStruct();
        CArgumentList* argList = m_eventMgr->requestArgumentList();
        mouseEvent->eventType = event::MOUSE_RELEASED;
        mouseEvent->timeStamp = timesys::ticks();
        mouseEvent->pressed = FG_FALSE; // Touch is released
        mouseEvent->buttonID = touchID;
        mouseEvent->x = point.x;
        mouseEvent->y = point.y;

        argList->push(SArgument::Type::ARG_TMP_POINTER, (void*)mouseEvent);
        m_eventMgr->throwEvent(event::MOUSE_RELEASED, argList);
#endif

        // Throw also more general event
        //touchEvent = new fgTouchEvent(*touchEvent);
        //argList = new fgArgumentList();
        //argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
        //m_eventMgr->throwEvent(event::TOUCH, argList);
    }
}
//------------------------------------------------------------------------------

event::SPointerRawData *event::CInputHandler::getPointerRawData(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return NULL;

    return &m_rawTouchesProcessed[pointerID];
}
//------------------------------------------------------------------------------

event::SPointerData *event::CInputHandler::getPointerData(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return NULL;

    return ((SPointerData *)(&m_rawTouchesProcessed[pointerID]));
}
//------------------------------------------------------------------------------

fgPointerState event::CInputHandler::getPointerState(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return FG_FALSE;

    return m_rawTouchesProcessed[pointerID].m_state;
}
//------------------------------------------------------------------------------

int event::CInputHandler::getPointerX(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return 0;
    return m_rawTouchesProcessed[pointerID].m_x;
}
//------------------------------------------------------------------------------

int event::CInputHandler::getPointerY(fgPointerID pointerID) {
    if(pointerID >= MAX_TOUCH_POINTS)
        return 0;
    return m_rawTouchesProcessed[pointerID].m_y;
}
//------------------------------------------------------------------------------

event::CFunctionCallback* event::CInputHandler::addKeyDownCallback(KeyVirtualCode keyCode,
                                                                   CFunctionCallback *callback) {
    if(!callback)
        return NULL;
    if(keyCode == FG_KEY_NULL)
        return NULL;
    if((unsigned int)keyCode > (unsigned int)FG_NUM_VIRTUAL_KEYS)
        return NULL;
    if(m_keyDownBinds[(int)keyCode].find(callback) >= 0) {
        return NULL;
    }
    m_keyDownBinds[(int)keyCode].push_back(callback);
    return callback;
}
//------------------------------------------------------------------------------

event::CFunctionCallback* event::CInputHandler::addKeyUpCallback(KeyVirtualCode keyCode,
                                                                 CFunctionCallback *callback) {
    if(!callback)
        return NULL;
    if(keyCode == FG_KEY_NULL)
        return NULL;
    if((unsigned int)keyCode > (unsigned int)FG_NUM_VIRTUAL_KEYS)
        return NULL;
    if(m_keyUpBinds[(int)keyCode].find(callback) >= 0) {
        return NULL;
    }
    m_keyUpBinds[(int)keyCode].push_back(callback);
    return callback;
}
//------------------------------------------------------------------------------

void event::CInputHandler::addKeyPressed(KeyVirtualCode keyCode) {
    if(keyCode == FG_KEY_NULL)
        return;
    if((unsigned int)keyCode > (unsigned int)FG_NUM_VIRTUAL_KEYS)
        return;
    m_keysDownPool.push_back(keyCode);
    if(m_keysPressedPool.find(keyCode) < 0 && !m_keyRepeats[(unsigned int)keyCode])
        m_keysPressedPool.push_back(keyCode);
    m_keyRepeats[(unsigned int)keyCode]++;
    toggleKeyboardMod(keyCode, FG_TRUE);
}
//------------------------------------------------------------------------------

void event::CInputHandler::addKeyUp(KeyVirtualCode keyCode) {
    if(keyCode == FG_KEY_NULL)
        return;
    if((unsigned int)keyCode > (unsigned int)FG_NUM_VIRTUAL_KEYS)
        return;
    if(m_keysUpPool.find(keyCode) < 0)
        m_keysUpPool.push_back(keyCode);
    CVector<KeyVirtualCode>::iterator itor = m_keysDownPool.findItor(keyCode);
    if(itor != m_keysDownPool.end())
        m_keysDownPool.erase(itor);
    itor = m_keysPressedPool.findItor(keyCode);
    if(itor != m_keysPressedPool.end())
        m_keysPressedPool.erase(itor);
    m_keyRepeats[(unsigned int)keyCode] = 0;
    toggleKeyboardMod(keyCode, FG_FALSE);
}
//------------------------------------------------------------------------------

unsigned int event::CInputHandler::getKeyRepeats(KeyVirtualCode keyCode) const {
    if(keyCode == FG_KEY_NULL)
        return 0;
    if((unsigned int)keyCode > (unsigned int)FG_NUM_VIRTUAL_KEYS)
        return 0;
    return m_keyRepeats[(unsigned int)keyCode];
}
//------------------------------------------------------------------------------

fgBool event::CInputHandler::isKeyUp(KeyVirtualCode keyCode) const {
    return (fgBool)!!(getKeyRepeats(keyCode) == 0);
}
//------------------------------------------------------------------------------

fgBool event::CInputHandler::isKeyDown(KeyVirtualCode keyCode) const {
    return (fgBool)!!(getKeyRepeats(keyCode) != 0);
}
//------------------------------------------------------------------------------

void event::CInputHandler::toggleKeyboardMod(KeyboardMod mod, const fgBool toggle) {
    if(toggle) {
        m_keyboardMod |= mod;
    } else {
        m_keyboardMod |= mod;
        m_keyboardMod ^= mod;
    }
}
//------------------------------------------------------------------------------

void event::CInputHandler::toggleKeyboardMod(KeyVirtualCode keyCode, const fgBool toggle) {
    switch(keyCode) {
        case FG_KEY_LSHIFT:
            toggleKeyboardMod(FG_MOD_LSHIFT, toggle);
            break;
        case FG_KEY_RSHIFT:
            toggleKeyboardMod(FG_MOD_RSHIFT, toggle);
            break;
        case FG_KEY_LCTRL:
            toggleKeyboardMod(FG_MOD_LCTRL, toggle);
            break;
        case FG_KEY_RCTRL:
            toggleKeyboardMod(FG_MOD_RCTRL, toggle);
            break;
        case FG_KEY_LGUI:
            toggleKeyboardMod(FG_MOD_LGUI, toggle);
            break;
        case FG_KEY_RGUI:
            toggleKeyboardMod(FG_MOD_RGUI, toggle);
            break;
        case FG_KEY_LALT:
            toggleKeyboardMod(FG_MOD_LALT, toggle);
            break;
        case FG_KEY_RALT:
            toggleKeyboardMod(FG_MOD_RALT, toggle);
            break;
        case FG_KEY_CAPSLOCK:
            break;
        default:
            break;
    };
}
//------------------------------------------------------------------------------

fgBool event::CInputHandler::isKeyboardMod(KeyboardMod mod) const {
    return (fgBool)!!(m_keyboardMod & mod);
}
//------------------------------------------------------------------------------

fgBool event::CInputHandler::isAltDown(fgBool onlyAlt) const {
    if(onlyAlt && (isShiftDown() || isControlDown() || isGuiDown())) {
        return FG_FALSE;
    }
    if(isKeyboardMod(FG_MOD_LALT) || isKeyboardMod(FG_MOD_RALT)) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool event::CInputHandler::isControlDown(fgBool onlyControl) const {
    if(onlyControl && (isShiftDown() || isGuiDown() || isAltDown())) {
        return FG_FALSE;
    }
    if(isKeyboardMod(FG_MOD_LCTRL) || isKeyboardMod(FG_MOD_RCTRL)) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool event::CInputHandler::isShiftDown(fgBool onlyShift) const {
    if(onlyShift && (isGuiDown() || isControlDown() || isAltDown())) {
        return FG_FALSE;
    }
    if(isKeyboardMod(FG_MOD_LSHIFT) || isKeyboardMod(FG_MOD_RSHIFT)) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool event::CInputHandler::isGuiDown(fgBool onlyGui) const {
    if(onlyGui && (isShiftDown() || isControlDown() || isAltDown())) {
        return FG_FALSE;
    }
    if(isKeyboardMod(FG_MOD_LGUI) || isKeyboardMod(FG_MOD_RGUI)) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

void event::CInputHandler::processData(void) {
    //
    // Phase 1: execute keyboard callbacks - from active keys in the pool
    // Please note that these will come from external event queue (low level)
    // could be SDL2 event queue, or glu/freeglut/X, Marmalade...
    //

    // Throw events for keys that just had been pressed down
    // this is called once
    for(unsigned int i = 0; i < (unsigned int)m_keysPressedPool.size(); i++) {
        KeyVirtualCode keyCode = m_keysPressedPool[i];
        {
            SKey* keyEvent = (SKey*)m_eventMgr->requestEventStruct();
            CArgumentList* argList = m_eventMgr->requestArgumentList();
            keyEvent->eventType = event::KEY_PRESSED;
            keyEvent->timeStamp = timesys::ticks();
            keyEvent->pressed = FG_TRUE;
            keyEvent->repeats = 1;
            keyEvent->keyCode = keyCode;
            keyEvent->mod = m_keyboardMod;

            argList->push(SArgument::Type::ARG_TMP_POINTER, (void*)keyEvent);
            m_eventMgr->throwEvent(event::KEY_PRESSED, argList);
        }
    }
    m_keysPressedPool.clear();

    // Keys being still down - continuous callbacks
    for(unsigned int i = 0; i < (unsigned int)m_keysDownPool.size(); i++) {
        KeyVirtualCode keyCode = m_keysDownPool[i];
        {
            SKey* keyEvent = (SKey*)m_eventMgr->requestEventStruct();
            CArgumentList* argList = m_eventMgr->requestArgumentList();
            keyEvent->eventType = event::KEY_DOWN;
            keyEvent->timeStamp = timesys::ticks();
            keyEvent->pressed = FG_TRUE;
            keyEvent->repeats = m_keyRepeats[(unsigned int)keyCode];
            keyEvent->keyCode = keyCode;
            keyEvent->mod = m_keyboardMod;

            argList->push(SArgument::Type::ARG_TMP_POINTER, (void*)keyEvent);
            m_eventMgr->throwEvent(event::KEY_DOWN, argList);
        }
        CallbackBindingMap::iterator found = m_keyDownBinds.find((int)keyCode);
        if(found == m_keyDownBinds.end())
            continue;
        // This callbacks are for chosen keys
        // They do not need any arguments
        // Those callbacks are designed for continuous calling
        // if the key is pressed
        for(unsigned int j = 0; j < (unsigned int)m_keyDownBinds[(int)keyCode].size(); j++) {
            // There's no need for argument list
            m_keyDownBinds[(int)keyCode][j]->Call();
        }
    }
    m_keysDownPool.clear();

    // Keys that just had been released
    for(int i = 0; i < (int)m_keysUpPool.size(); i++) {
        KeyVirtualCode keyCode = m_keysUpPool[i];
        // Throw proper key release event
        {
            SKey* keyEvent = (SKey*)m_eventMgr->requestEventStruct();
            CArgumentList* argList = m_eventMgr->requestArgumentList();
            keyEvent->eventType = event::KEY_UP;
            keyEvent->timeStamp = timesys::ticks();
            keyEvent->pressed = FG_FALSE;
            keyEvent->repeats = 0;
            keyEvent->keyCode = keyCode;
            keyEvent->mod = m_keyboardMod;

            argList->push(SArgument::Type::ARG_TMP_POINTER, (void*)keyEvent);
            m_eventMgr->throwEvent(event::KEY_UP, argList);
        }
        CallbackBindingMap::iterator found = m_keyUpBinds.find((int)keyCode);
        if(found == m_keyUpBinds.end())
            continue;
        for(unsigned int j = 0; j < (unsigned int)m_keyUpBinds[(int)keyCode].size(); j++) {
            // There's no need for argument list
            m_keyUpBinds[(int)keyCode][j]->Call();
        }
    }
    m_keysUpPool.clear();

    //
    // Phase 2: Process pointer/touch data and throw proper events 
    //

    if(!m_pointerAvailable)
        return;
#if defined(FG_USING_MARMALADE)
    s3ePointerUpdate();
#endif
    for(unsigned int i = 0; i < MAX_TOUCH_POINTS; i++) {
        int touchID = i;
        SPointerRawData & touchPtr = m_rawTouches[i];
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
                    FG_LOG_DEBUG("InputHandler: Tap (x,y)=(%d,%d) ID:%d", touchPtr.m_tapX, touchPtr.m_tapY, touchPtr.m_pointerID);

                    //
                    // Throwing the proper event
                    //
                    if(m_eventMgr) {
#if defined(FG_USING_PLATFORM_MOBILE)
                        STouch* touchEvent = (STouch*)m_eventMgr->requestEventStruct();
                        CArgumentList* argList = m_eventMgr->requestArgumentList();
                        touchEvent->eventType = event::TOUCH_TAP_FINISHED;
                        touchEvent->timeStamp = timesys::ticks();
                        touchEvent->pressed = FG_FALSE;
                        touchEvent->touchID = touchPtr.m_touchID;
                        touchEvent->x = touchPtr.m_tapX;
                        touchEvent->y = touchPtr.m_tapY;

                        argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)touchEvent);
                        m_eventMgr->throwEvent(event::TOUCH_TAP_FINISHED, argList);
#else
                        SMouse* mouseEvent = (SMouse*)m_eventMgr->requestEventStruct();
                        CArgumentList* argList = m_eventMgr->requestArgumentList();
                        mouseEvent->eventType = event::MOUSE_TAP_FINISHED;
                        mouseEvent->timeStamp = timesys::ticks();
                        mouseEvent->pressed = FG_FALSE;
                        mouseEvent->buttonID = touchPtr.m_touchID;
                        mouseEvent->x = touchPtr.m_tapX;
                        mouseEvent->y = touchPtr.m_tapY;

                        argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)mouseEvent);
                        m_eventMgr->throwEvent(event::MOUSE_TAP_FINISHED, argList);
#endif

                        //touchEvent = new fgTouchEvent(*touchEvent);
                        //argList = new fgArgumentList();
                        //argList->pushArgument(FG_ARGUMENT_STRUCT, (void *)touchEvent);
                        //m_eventMgr->throwEvent(event::TOUCH, argList);
                    }

                } else {
                    FG_LOG_DEBUG("InputHandler: Space criterion NOT TRUE: x_delta = %d, y_delta = %d", abs(touchPtr.m_pointerXEnd - touchPtr.m_pointerXInitial),
                                 abs(touchPtr.m_pointerYEnd - touchPtr.m_pointerYInitial));
                }
            } else {
                FG_LOG_DEBUG("InputHandler: Time criterion NOT TRUE: delta_time = %d", delta_time);
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
                    //SSwipe *swipeEvent = fgMalloc<SSwipe>();
                    SSwipe *swipeEvent = (SSwipe*)m_eventMgr->requestEventStruct();
                    CArgumentList *argList = m_eventMgr->requestArgumentList();

                    swipeEvent->timeStamp = timesys::ticks();
                    fgBool X = FG_FALSE, Y = FG_FALSE;
                    if(touchPtr.m_swipeDown) {
                        swipeEvent->swipeDirection = SSwipe::DOWN;
                        Y = FG_TRUE;
                    } else if(touchPtr.m_swipeUp) {
                        swipeEvent->swipeDirection = SSwipe::UP;
                        Y = FG_TRUE;
                    }
                    if(touchPtr.m_swipeLeft) {
                        swipeEvent->swipeDirection = SSwipe::LEFT;
                        X = FG_TRUE;
                    } else if(touchPtr.m_swipeRight) {
                        swipeEvent->swipeDirection = SSwipe::RIGHT;
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

                    //CArgumentList *argList = new CArgumentList();
                    argList->push(SArgument::Type::ARG_TMP_POINTER, (void *)swipeEvent);

                    if(X && Y) {
                        swipeEvent->eventType = event::SWIPE_XY;
                        m_eventMgr->throwEvent(event::SWIPE_XY, argList);
                    } else if(X) {
                        swipeEvent->eventType = event::SWIPE_X;
                        m_eventMgr->throwEvent(event::SWIPE_X, argList);
                    } else if(Y) {
                        swipeEvent->eventType = event::SWIPE_Y;
                        m_eventMgr->throwEvent(event::SWIPE_Y, argList);
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
//------------------------------------------------------------------------------

void event::CInputHandler::interpretSwipes(int min_offset_for_swipe,
                                           int startPointer,
                                           int endPointer,
                                           int initialSwipePointer, // IN
                                           fgBool* minusSwipe,
                                           fgBool* plusSwipe,
                                           int* swipeSize) // OUT
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
//------------------------------------------------------------------------------

int32_t event::CInputHandler::multiTouchButtonHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    CInputHandler *inputHandler = (CInputHandler *)userData;
#if defined(FG_USING_MARMALADE)
    s3ePointerTouchEvent* event = (s3ePointerTouchEvent*)systemData;
    if(!inputHandler->m_init)
        return 0;
    if(event->m_Pressed) {
        inputHandler->handlePointerPressed(Vector2i(event->m_x, event->m_y), event->m_TouchID);
    } else {
        inputHandler->handlePointerReleased(Vector2i(event->m_x, event->m_y), event->m_TouchID);
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
//------------------------------------------------------------------------------

int32_t event::CInputHandler::multiTouchMotionHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    CInputHandler *inputHandler = (CInputHandler *)userData;
#if defined(FG_USING_MARMALADE)
    s3ePointerTouchMotionEvent* event = (s3ePointerTouchMotionEvent*)systemData;
    if(!inputHandler->m_init)
        return 0;
    inputHandler->handlePointerMoved(Vector2i(event->m_x, event->m_y), event->m_TouchID, FG_POINTER_STATE_PRESSED);
#elif defined(FG_USING_SDL2)
#endif
    return 0;
}
//------------------------------------------------------------------------------

int32_t event::CInputHandler::singleTouchButtonHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    CInputHandler *inputReceiver = (CInputHandler *)userData;
    if(!inputReceiver->m_init)
        return 0;
#if defined(FG_USING_MARMALADE)
    s3ePointerEvent* event = (s3ePointerEvent*)systemData;
    if(event->m_Pressed) {
        inputReceiver->handlePointerPressed(Vector2i(event->m_x, event->m_y));
    } else {
        inputReceiver->handlePointerReleased(Vector2i(event->m_x, event->m_y));
    }
#elif defined(FG_USING_SDL2)
    SDL_Event *sdlEvent = (SDL_Event *)systemData;

    if(sdlEvent->type == SDL_MOUSEBUTTONDOWN) {
        SDL_MouseButtonEvent *event = (SDL_MouseButtonEvent *)systemData;
        inputReceiver->handlePointerPressed(Vector2i(event->x, event->y), (unsigned int)event->button);
    } else if(sdlEvent->type == SDL_MOUSEBUTTONUP) {
        SDL_MouseButtonEvent *event = (SDL_MouseButtonEvent *)systemData;
        inputReceiver->handlePointerReleased(Vector2i(event->x, event->y), (unsigned int)event->button);
    } else if(sdlEvent->type == SDL_FINGERDOWN) {
        SDL_MouseButtonEvent *event = (SDL_MouseButtonEvent *)systemData;
        inputReceiver->handlePointerPressed(Vector2i(event->x, event->y), (unsigned int)event->button);
    } else if(sdlEvent->type == SDL_FINGERUP) {
        SDL_MouseButtonEvent *event = (SDL_MouseButtonEvent *)systemData;
        inputReceiver->handlePointerReleased(Vector2i(event->x, event->y), (unsigned int)event->button);
    }
#endif
    return 0;
}
//------------------------------------------------------------------------------

int32_t event::CInputHandler::singleTouchMotionHandler(void* systemData, void* userData) {
    if(!systemData || !userData)
        return 0;
    CInputHandler *inputReceiver = (CInputHandler *)userData;
    if(!inputReceiver->m_init)
        return 0;
#if defined(FG_USING_MARMALADE)
    s3ePointerMotionEvent* event = (s3ePointerMotionEvent*)systemData;

    inputReceiver->handlePointerMoved(Vector2i(event->m_x, event->m_y));
#elif defined(FG_USING_SDL2)
    SDL_MouseMotionEvent *event = (SDL_MouseMotionEvent *)systemData;
    inputReceiver->handlePointerMoved(Vector2i(event->x, event->y)/*, need ID? */, FG_DEFAULT_POINTER_ID, event->state);
#endif
    return 0;
}
//------------------------------------------------------------------------------
