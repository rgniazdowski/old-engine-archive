/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

// #TODO - this needs fixing (touch raw data, etc) - is this really necessary?
// possible fix - manage to detect swipe symbols and more in touch receiver and
// throw proper events - this will be however next layer taking care of something
// so simple like touch events (mouse events basically) - not a priority for now

#ifndef FG_INC_POINTER_RAW_DATA
    #define FG_INC_POINTER_RAW_DATA

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #ifndef FG_INC_BOOL
        #include "fgBool.h"
    #endif

    #include "fgPointerData.h"

/*
 *
 */
struct fgPointerRawData : fgPointerData {
    fgBool m_pressOccured;

    unsigned long int m_pressedMilliseconds;
    unsigned long int m_releasedMilliseconds;

    int m_pointerXSwipeInitial;
    int m_pointerXInitial;
    int m_pointerXStart;
    int m_pointerXEnd;

    int m_pointerYSwipeInitial;
    int m_pointerYInitial;
    int m_pointerYStart;
    int m_pointerYEnd;

    int m_tapX;
    int m_tapY;
    int m_basicSwipeXSize;
    int m_basicSwipeYSize;
    int m_swipeXSize;
    int m_swipeYSize;

    fgBool m_swipeLeft;
    fgBool m_swipeRight;
    fgBool m_swipeDown;
    fgBool m_swipeUp;

    int m_xSwipeSteps;
    int m_ySwipeSteps;

    // Ten konstruktor nie jest tak naprawde potrzebny, bo DOMYSLNY KONSTRUKTOR
    // w C++ dla struktur/klas/itp. ZERUJE POLA.
    // Gdy tylko utworzy sie wlasny konstruktor - trzeba te pola zerowac explicite
    //
    // UPDATE: niekoniecznie tak jest. Przywrocilem konstruktor. Trzeba doczytac.
    // http://stackoverflow.com/questions/1542892/two-ways-of-calling-default-constructor
    fgPointerRawData() :
    m_pressOccured(FG_FALSE),
    m_pressedMilliseconds(0), m_releasedMilliseconds(0),
    m_pointerXSwipeInitial(0), m_pointerXInitial(0),
    m_pointerXStart(0), m_pointerXEnd(0),
    m_pointerYSwipeInitial(0), m_pointerYInitial(0),
    m_pointerYStart(0), m_pointerYEnd(0),
    m_tapX(0), m_tapY(0),
    m_basicSwipeXSize(0), m_basicSwipeYSize(0),
    m_swipeXSize(0), m_swipeYSize(0),
    m_swipeLeft(FG_FALSE), m_swipeRight(FG_FALSE),
    m_swipeDown(FG_FALSE), m_swipeUp(FG_FALSE),
    m_xSwipeSteps(0), m_ySwipeSteps(0) { }

};

#endif /* FG_INC_POINTER_RAW_DATA */
