/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_SENSORS_H_
#define _FG_SENSORS_H_

#include "s3eTypes.h"

#include "../Math/fgKalmanFilter.h"
#include "fgHardwareState.h"

#include "../fgSingleton.h"
#include "../fgCommon.h"

static int32 HarvestCallback(void* systemData, void* userData);

/**
 * Class fgSensors - management of sensors data (mobile).
 * 
 * Klasa definiuje symboliczne typy sensorow:
 * enum { NONE = 0,
 * 		ACCELEROMETER = 1,
 * 		COMPASS = 2
 * 	};
 *
 * Marmalade wspiera tylko te dwa typy. Chociaz pewnie tez podaje w jakis sposob
 * orientację (czyli wpiera orientation sensor).
 *
 * Gyroscope: mierzy(łby) ruch (przyspieszenie?) W OKÓŁ OSI.
 * Accelerometer: mierzy przyspieszenie WZDŁUŻ OSI.
 *
 */
class fgSensors : public fgSingleton<fgSensors> {    
    friend int32 HarvestCallback(void* systemData, void* userData);
	friend class fgSingleton<fgSensors>;
public:
    enum { FG_SENSORS_ACCELEROMETER = 0, FG_SENSORS_COMPASS = 1 };

private:
	// Are sensors running?
    fgBool m_isRunning;

	/// Number of supported sensors (includes the "NONE" sensor)
	enum { FG_SENSORS_TYPES = 2, FG_SENSORS_VALUES = 3 };

	enum { 
		FG_SENSORS_UNKNOWN = 0,
		FG_SENSORS_PORTRAIT = 1,
		FG_SENSORS_UPSIDE_DOWN = 2,
		FG_SENSORS_LANDSCAPE_LEFT = 3,
		FG_SENSORS_LANDSCAPE_RIGHT = 4,
		FG_SENSORS_FACE_UP = 5,
		FG_SENSORS_FACE_DOWN = 6 
	};
    
    enum { 
		FG_SENSORS_BASE_SIZE = 4 
	};
    
    // How long after accel-base unlock request, should the base remain locked
    enum { 
		FG_SENSORS_AFTER_UNLOCK_DELAY = 3000 
	};
    // List of available sensor names
	static const char* s_sensorsNames[FG_SENSORS_TYPES];
	// List with sensor errors
	int m_sensorsErrors[FG_SENSORS_TYPES];
	// Data harvested from sensors
	float m_sensorsValues[FG_SENSORS_TYPES][FG_SENSORS_VALUES];
	/// "Triple" Kalman filters for each sensor
	TripleKalman m_filters[FG_SENSORS_TYPES];
	// 5 last values used to compute REFERENCE BASE for accelerometer values
    float m_accelRawBase[FG_SENSORS_BASE_SIZE][FG_SENSORS_VALUES];
    // Actual circular index in m_accelRawBase
    int m_arbIdx;
    // Actual base, computed from the raw data
    float m_accelFinalBase[FG_SENSORS_VALUES];
	// When was base requested to unlock
    unsigned long int m_unlockTS;
    // Together with unlockTS, marks if the accelBase is locked
    fgBool m_accelBaseLocked;
    
protected:
	// Default constructor for Sensors object
	fgSensors();
	// Default destructor for Sensors object
	~fgSensors();

public:
	// Register to all sensors and get the error codes
	fgBool startSensors();

	// Unregister all the sensors
	void stopSensors();

	// Get the error message using the sensor error code.
	const char* errorCodeText(int errorCode);
    
    // Gets data processed by the filters
	void getAccelerometer(float *x, float *y, float *z);

    // Gets the reference, normal values
	void getAccelerometerBase(float *x, float *y);

    // Locks the base – called, when first MOD is activated,
    // because then user starts to rotate the device – so
    // accelerometer values are no longer normal, neutral
    void lockBase() {
        m_accelBaseLocked = FG_FALSE;
    }

    // Unlocks accelerometer base – called, when last
    // MOD is deactivated
    void unlockBase() {
        if( m_accelBaseLocked ) {
            m_accelBaseLocked = FG_FALSE;
            m_unlockTS = FG_HardwareState->getTS();
        }
    }

    // Accel-base is unlocked after unlockBase() call & after AFTER_UNLOCK_DELAY ms passed
    fgBool isBaseLocked() const {
        return m_accelBaseLocked || ( m_unlockTS > (FG_HardwareState->getTS() - FG_SENSORS_AFTER_UNLOCK_DELAY) );
    }

	// Harvests sensor data from given event.
	void harvestData( int type, float x, float y, float z );

};

#endif /* _FG_SENSORS_H_ */
