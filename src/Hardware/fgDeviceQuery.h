/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_DEVICE_QUERY_H_
#define _FG_DEVICE_QUERY_H_

#include "../fgSingleton.h"

enum fgDeviceClass 
{
	FG_DEVICE_CLASS_UNKNOWN,
	FG_DEVICE_CLASS_IPHONE,
	FG_DEVICE_CLASS_IPOD,
	FG_DEVICE_CLASS_IPAD,
	FG_DEVICE_CLASS_ANDROID,
	FG_DEVICE_CLASS_OSX,
	FG_DEVICE_CLASS_BADA,
	FG_DEVICE_CLASS_BB 
};

enum fgDeviceGeneration {
	FG_DEVICE_GENERATION_UNKNOWN,
	FG_DEVICE_GENERATION_FIRST,
	FG_DEVICE_GENERATION_SECOND,
	FG_DEVICE_GENERATION_THIRD,
	FG_DEVICE_GENERATION_FOURTH,
	FG_DEVICE_GENERATION_FIFTH
};

class fgDeviceQuery : public fgSingleton<fgDeviceQuery> {

	friend class fgSingleton<fgDeviceQuery>;

private:
    /// Device string - raw data returned by DEVICE
    const char* m_deviceString;
    /// Device version (encoded in string returned by DEVICE)
    int m_deviceVersion;
    /// Device class (iPod, iPad, etc).
    fgDeviceClass m_deviceClass;
    /// Device generation (applies to Apple)
    fgDeviceGeneration m_deviceGeneration;
    /// Is the device Android
    bool m_android;
    /// Is the device iOS
    bool m_iOS;
    /// Is the device OSX
    bool m_OSX;
    /// Is the device BADA
    bool m_BADA;
    /// Is the device BB
    bool m_BB;
    /// Is information ready?
    bool m_computed;

protected:
    fgDeviceQuery();
	~fgDeviceQuery();

public:
    /// Prepare all information
    void computeDevice();

    const char* deviceString() {
        computeDevice();
        return m_deviceString;
    }

    int deviceVersion() {
        computeDevice();
        return m_deviceVersion;
    }

    fgDeviceClass deviceClass() {
        computeDevice();
        return m_deviceClass;
    }

    fgDeviceGeneration deviceGeneration() {
        computeDevice();
        return m_deviceGeneration;
    }

    bool android() {
        computeDevice();
        return m_android;
    }

    bool iOS() {
        computeDevice();
        return m_iOS;
    }
    
    bool OSX() {
        computeDevice();
        return m_OSX;
    }
    
    bool BB() {
        computeDevice();
        return m_BB;
    }
    
    bool BADA() {
        computeDevice();
        return m_BADA;
    }
};

#define FG_DeviceQuery		 fgDeviceQuery::getInstance()

#endif
