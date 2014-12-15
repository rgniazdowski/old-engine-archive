/*******************************************************
* Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
*
* This file is part of FlexiGame: Flexible Game Engine
*
* FlexiGame source code and any related files can not be copied, modified
* and/or distributed without the express or written consent from the author.
*******************************************************/

#ifndef FG_INC_DEVICE_QUERY
#define FG_INC_DEVICE_QUERY
#define FG_INC_DEVICE_QUERY_BLOCK

#include "fgBuildConfig.h"
#include "fgTypes.h"

#if defined FG_USING_MARMALADE

enum fgDeviceClass {
    FG_DEVICE_CLASS_UNKNOWN,
    FG_DEVICE_CLASS_IPHONE,
    FG_DEVICE_CLASS_IPOD,
    FG_DEVICE_CLASS_IPAD,
    FG_DEVICE_CLASS_ANDROID,
    FG_DEVICE_CLASS_OSX,    
    FG_DEVICE_CLASS_QNX
};

enum fgDeviceModel {
    FG_DEVICE_MODEL_UNKNOWN = 0,

    FG_DEVICE_MODEL_IPAD = 1,
    FG_DEVICE_MODEL_IPAD_1 = 1,
    FG_DEVICE_MODEL_IPAD_2 = 2,
    FG_DEVICE_MODEL_IPAD_3 = 3,
    FG_DEVICE_MODEL_IPAD_4 = 4, // iPad Retina
    FG_DEVICE_MODEL_IPAD_AIR = 5,
    FG_DEVICE_MODEL_IPAD_AIR_2 = 6,

    FG_DEVICE_MODEL_IPAD_MINI = 7,
    FG_DEVICE_MODEL_IPAD_MINI_1 = 7, // iPad mini 1G
    FG_DEVICE_MODEL_IPAD_MINI_2 = 8, // iPad mini Retina / 2
    FG_DEVICE_MODEL_IPAD_MINI_3 = 9, // iPad mini 3

    FG_DEVICE_MODEL_IPHONE = 10,
    FG_DEVICE_MODEL_IPHONE_3G = 11,
    FG_DEVICE_MODEL_IPHONE_3GS = 12,
    FG_DEVICE_MODEL_IPHONE_4 = 13,
    FG_DEVICE_MODEL_IPHONE_4S = 14,
    FG_DEVICE_MODEL_IPHONE_5 = 15,
    FG_DEVICE_MODEL_IPHONE_5C = 16,
    FG_DEVICE_MODEL_IPHONE_5S = 17,
    FG_DEVICE_MODEL_IPHONE_6 = 18,
    FG_DEVICE_MODEL_IPHONE_6_PLUS = 19,

    FG_DEVICE_MODEL_IPOD_TOUCH = 20,
    FG_DEVICE_MODEL_IPOD_TOUCH_1G = 20,
    FG_DEVICE_MODEL_IPOD_TOUCH_2G = 21,
    FG_DEVICE_MODEL_IPOD_TOUCH_3G = 22,
    FG_DEVICE_MODEL_IPOD_TOUCH_4G = 23,
    FG_DEVICE_MODEL_IPOD_TOUCH_5G = 24,

    FG_DEVICE_MODEL_ANDROID_VARIA = 25,

    FG_DEVICE_MODEL_GALAXY_ACE = 26,
    FG_DEVICE_MODEL_GALAXY_S2 = 27,
    FG_DEVICE_MODEL_GALAXY_S3 = 28,
    FG_DEVICE_MODEL_GALAXY_S4 = 29
};

// 

enum fgDeviceGeneration {
    FG_DEVICE_GENERATION_UNKNOWN,
    FG_DEVICE_GENERATION_FIRST,
    FG_DEVICE_GENERATION_SECOND,
    FG_DEVICE_GENERATION_THIRD,
    FG_DEVICE_GENERATION_FOURTH,
    FG_DEVICE_GENERATION_FIFTH,
    FG_DEVICE_GENERATION_SIXTH,
    FG_DEVICE_GENERATION_SEVENTH,
    FG_DEVICE_GENERATION_EIGHTH,
    FG_DEVICE_GENERATION_NINTH,
    FG_DEVICE_GENERATION_TENTH
};

/*
* #FIXME
*/
class fgDeviceQuery {
private:
    /// Device string - raw data returned by DEVICE
    const char* m_deviceString;
    /// Device version (encoded in string returned by DEVICE)
    //int m_deviceVersion; // #NOPE!
    /// Device class (iPod, iPad, etc).
    fgDeviceClass m_deviceClass;
    /// Device generation (applies to Apple)
    fgDeviceGeneration m_deviceGeneration;
    /// Device model (applies mostly to Apple, however there will be enums for others)
    fgDeviceModel m_deviceModel;
    /// Is the device Android
    fgBool m_android;
    /// Is the device iOS
    fgBool m_iOS;
    /// Is the device OSX
    fgBool m_OSX;    
    /// Is the device Blackberry/QNX - Playbook
    fgBool m_QNX;
    /// Is information ready?
    fgBool m_computed;

public:
    fgDeviceQuery();
    virtual ~fgDeviceQuery();

protected:
    void computeGeneration(void);

public:
    /// Prepare all information
    void computeDevice();
    const char* deviceString() {
        computeDevice();
        return m_deviceString;
    }
    fgDeviceClass deviceClass() {
        computeDevice();
        return m_deviceClass;
    }
    fgDeviceGeneration deviceGeneration() {
        computeDevice();
        return m_deviceGeneration;
    }
    fgDeviceModel deviceModel(void) {
        computeDevice();
        return m_deviceModel;
    }
    fgBool android() {
        computeDevice();
        return m_android;
    }
    fgBool iOS() {
        computeDevice();
        return m_iOS;
    }
    fgBool OSX() {
        computeDevice();
        return m_OSX;
    }
    fgBool QNX() {
        computeDevice();
        return m_QNX;
    }
};

#endif // FG_USING_MARMALADE

#undef FG_INC_DEVICE_QUERY_BLOCK
#endif /* FG_INC_DEVICE_QUERY */
