/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

// #TODO - this needs fixing (touch raw data, etc) - is this really necessary?
// possible fix - manage to detect swipe symbols and more in touch receiver and
// throw proper events - this will be however next layer taking care of something
// so simple like touch events (mouse events basically) - not a priority for now

#ifndef _FG_TOUCH_RAW_DATA_H_
#define _FG_TOUCH_RAW_DATA_H_

struct fgTouchRawData
{
	bool m_pressOccured;

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

	int m_moveX;
	int m_moveY;

	int m_tapX;
	int m_tapY;
    int m_basicSwipeXSize;
    int m_basicSwipeYSize;
	int m_swipeXSize;
	int m_swipeYSize;

	bool m_pointerTap;
	bool m_swipeLeft;
	bool m_swipeRight;
	bool m_swipeDown;
	bool m_swipeUp;

	int m_xSwipeSteps;
	int m_ySwipeSteps;

    // Ten konstruktor nie jest tak naprawde potrzebny, bo DOMYSLNY KONSTRUKTOR
    // w C++ dla struktur/klas/itp. ZERUJE POLA.
    // Gdy tylko utworzy sie wlasny konstruktor - trzeba te pola zerowac explicite
    //
    // UPDATE: niekoniecznie tak jest. Przywrocilem konstruktor. Trzeba doczytac.
    // http://stackoverflow.com/questions/1542892/two-ways-of-calling-default-constructor
    fgTouchRawData() : m_pressOccured(false), m_pressedMilliseconds(0), m_releasedMilliseconds(0),
                        m_pointerXSwipeInitial(0), m_pointerXInitial(0), m_pointerXStart(0), m_pointerXEnd(0),
                        m_pointerYSwipeInitial(0), m_pointerYInitial(0), m_pointerYStart(0), m_pointerYEnd(0),
                        m_tapX(0), m_tapY(0), m_basicSwipeXSize(0), m_basicSwipeYSize(0), m_swipeXSize(0), m_swipeYSize(0),
                        m_moveX(0), m_moveY(0), m_pointerTap(false), m_swipeLeft(false), m_swipeRight(false),
                        m_swipeDown(false), m_swipeUp(false), m_xSwipeSteps(0), m_ySwipeSteps(0)
    { }

};

#endif
