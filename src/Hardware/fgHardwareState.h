/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_HARDWARESTATE_H_
#define _FG_HARDWARESTATE_H_

#include "s3eTypes.h"
#include "../fgSingleton.h"

#define FG_ORIENTATION_PORTRAIT		0
#define FG_ORIENTATION_LANDSCAPE	1

#define FG_FRAMES_COUNT_LIMIT		20

#define FG_DEVICE_ORIENTATION FG_ORIENTATION_LANDSCAPE

/**
 * The class holds only SIMPLE states, i.e. it does not
 * hold GameLogic object. Reason: to avoid including EVERYTHING here.
 *
 * Still, game_main/main do include everything :) Is it possible to avoid?
 */

class fgHardwareState : public fgSingleton<fgHardwareState> 
{
	friend class fgSingleton<fgHardwareState>;
private:
    unsigned long int m_TS;
	int m_screenHeight;
	int m_screenWidth;
	int m_dispArea;
	unsigned long int m_DT;
	unsigned long int m_DT2;
	float m_fps;
    int m_dpi;

    /// Coefficient DisplayArea / DPI
    float m_dpiAndAreaCoef;

protected:
    fgHardwareState();
    ~fgHardwareState();

public:

    // Inits DPI. Called from GL init code, when display is ready
    void initDPI();

	// FIXME
	// now in the engine there will be two (or more) main threads - one for calculation of various thins (3d data, logic, scripts, events, callbacks, etc.) and another one for calling proper drawing functions
	// so basically DT should be calculated in the way that takes into account both threads - however calculation of FPS should be done only in graphics thread (?)
	void calculateDT(void);
	float calculateFPS(void);

	//
	// Getters
	//
    /// Timestamp without possibly slow s3eTimerGetMs() call. Used when ONE FRAME accuracy is sufficient.
    unsigned long int TS(void) const {
        return m_TS;
    }

    /// Returns delta-time
	unsigned long int DT(void) const {
		return m_DT;
	}

    /// Returns delta-time 2
	unsigned long int DT2(void) const {
		return m_DT2;
	}

    /// Returns FPS
	float FPS(void) const {
		return m_fps;
	}

    /// Returns screen height
	int screenHeight(void) const {
		return m_screenHeight;
	}

    /// Returns screen width
	int screenWidth(void) const {
		return m_screenWidth;
	}

	int dispArea(void) const {
		return m_dispArea;
	}

    int dpi(void) const {
        return m_dpi;
    }

    int xdpi(void) const {
        int sum = m_screenWidth + m_screenHeight;
        return int(float(m_screenWidth) / sum * m_dpi);
    }

    int ydpi(void) const {
        int sum = m_screenWidth + m_screenHeight;
        return int(float(m_screenHeight) / sum * m_dpi);
    }

    float displayCoefficient(void) const {
        return m_dpiAndAreaCoef;
    }

    //
    // MARK: -
    // MARK: Lengths conversion methods
    //
    int inchesToPixels(float inches) {
        return (int) (m_dpi * inches);
    }

    int millimeterToPixels(float mm) {
        return (int) (m_dpi * mm / 25.4f );
    }

    int inchesToPixelsX(float inches) {
        return (int) (xdpi() * inches);
    }

    int millimeterToPixelsX(float mm) {
        return (int) (xdpi() * mm / 25.4f );
    }

    int inchesToPixelsY(float inches) {
        return (int) (ydpi() * inches);
    }

    int millimeterToPixelsY(float mm) {
        return (int) (ydpi() * mm / 25.4f );
    }

	//
	// Setters
	//

    /// Sets time stamp
    void setTS(unsigned long int ts) {
        m_TS = ts;
    }

    /// Sets delta-time
	void setDT(unsigned long int dt) {
		m_DT = dt;
	}

    /// Sets delta-time 2
	void setDT2(unsigned long int dt2) {
		m_DT2 = dt2;
	}

    /// Sets FPS
	void setFPS(float fps) {
		m_fps = fps;
	}

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

#endif /* _FG_HARDWARE_STATE_H */
