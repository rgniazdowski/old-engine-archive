/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of #FLEXIGAME_PROJECT
 *
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_HARDWARE_STATE_H_
#define _FG_HARDWARE_STATE_H_

#include "fgSingleton.h"

// #FIXME
enum fgScreenOrientation {
	FG_SCREEN_ORIENTATION_PORTRAIT,
	FG_SCREEN_ORIENTATION_LANDSCAPE
};

#define FG_ORIENTATION_PORTRAIT		0
#define FG_ORIENTATION_LANDSCAPE	1

#define FG_FRAMES_COUNT_LIMIT		20

#define FG_DEVICE_ORIENTATION FG_ORIENTATION_LANDSCAPE

/** #FIXME
 * The class holds only SIMPLE states, i.e. it does not
 * hold GameLogic object. Reason: to avoid including EVERYTHING here.
 */
class fgHardwareState : public fgSingleton<fgHardwareState>
{
	friend class fgSingleton<fgHardwareState>;
private:
	// Timestamp (in miliseconds)
    unsigned long int m_TS;
	// Screen height
	int m_screenHeight;
	// Screen width
	int m_screenWidth;
	// Display area (WxH)
	int m_dispArea;
	// Delta time (duration of last frame, in ms)
	unsigned long int m_DT;
	// Delta time 2
	unsigned long int m_DT2;
	// Current FPS (frames per second)
	float m_fps;
	// DPI of the screen
    int m_dpi;
    // Coefficient DisplayArea / DPI
    float m_dpiAndAreaCoef;

protected:
	// Default constructor for Hardware State object
    fgHardwareState();
	// Default destructor for Hardware State object
    ~fgHardwareState();

public:
    // Inits DPI. Called from GL init code, when display is ready
    void initDPI();

    void deviceYield(int ms = 0);

	// FIXME
	// now in the engine there will be two (or more) main threads - one for calculation of
	// various thins (3d data, logic, scripts, events, callbacks, etc.) and another one for
	// calling proper drawing functions, so basically DT should be calculated in the way
	// that takes into account both threads - however calculation of FPS should be done only
	// in graphics thread (?)
	void calculateDT(void);
	// Calculate current FPS
	float calculateFPS(void);

    // Timestamp without possibly slow s3eTimerGetMs() call.
	// Used when ONE FRAME accuracy is sufficient.
    unsigned long int getTS(void) const {
        return m_TS;
    }

    // Returns delta-time
	unsigned long int getDelta(void) const {
		return m_DT;
	}

    // Returns delta-time 2
	unsigned long int getDelta2(void) const {
		return m_DT2;
	}

    // Returns FPS
	float getFPS(void) const {
		return m_fps;
	}

    // Returns screen height
	int getScreenHeight(void) const {
		return m_screenHeight;
	}

    // Returns screen width
	int getScreenWidth(void) const {
		return m_screenWidth;
	}

	// Returns display area
	int getDisplayArea(void) const {
		return m_dispArea;
	}

	// Returns screen DPI
    int getDPI(void) const {
        return m_dpi;
    }
	// Returns horizontal (X) screen DPI
    int getXDPI(void) const {
        int sum = m_screenWidth + m_screenHeight;
        return int(float(m_screenWidth) / sum * m_dpi);
    }
	// Returns vertical (Y) screen DPI
    int getYDPI(void) const {
        int sum = m_screenWidth + m_screenHeight;
        return int(float(m_screenHeight) / sum * m_dpi);
    }
	// Returns screen display coefficient
    float getDisplayCoefficient(void) const {
        return m_dpiAndAreaCoef;
    }

	// Convert inches to pixels (from screen DPI)
    int inchesToPixels(float inches) {
        return (int) (m_dpi * inches);
    }

	// Convert millimeters to pixels
    int millimeterToPixels(float mm) {
        return (int) (m_dpi * mm / 25.4f );
    }

	// Convert inches to pixels horizontally
    int inchesToPixelsX(float inches) {
        return (int) (getXDPI() * inches);
    }

	// Convert millimeters to pixels horizontally
    int millimeterToPixelsX(float mm) {
        return (int) (getXDPI() * mm / 25.4f );
    }

	// Convert inches to pixels vertically
    int inchesToPixelsY(float inches) {
        return (int) (getYDPI() * inches);
    }

	// Convert millimeters to pixels vertically
    int millimeterToPixelsY(float mm) {
        return (int) (getYDPI() * mm / 25.4f );
    }

    // Sets time stamp
    void setTS(unsigned long int ts) {
        m_TS = ts;
    }

    // Sets delta-time
	void setDelta(unsigned long int dt) {
		m_DT = dt;
	}

    // Sets delta-time 2
	void setDelta2(unsigned long int dt2) {
		m_DT2 = dt2;
	}

	// Set screen dimensions
	void setScreenDimensions(int screenWidth, int screenHeight) {
		if(FG_DEVICE_ORIENTATION == FG_ORIENTATION_LANDSCAPE) {
			if(screenWidth > screenHeight) {
				m_screenWidth = screenWidth;
				m_screenHeight = screenHeight;
			} else {
				m_screenWidth = screenHeight;
				m_screenHeight = screenWidth;
			}
		} else {
			if(screenWidth > screenHeight) {
				m_screenWidth = screenHeight;
				m_screenHeight = screenWidth;
			} else {
				m_screenWidth = screenWidth;
				m_screenHeight = screenHeight;
			}
		}
		m_dispArea = m_screenHeight * m_screenWidth;
	}
};

#define FG_HardwareState fgHardwareState::getInstance()

#endif /* _FG_HARDWARE_STATE_H_ */
