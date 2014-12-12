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

    #include "fgBuildConfig.h"
    #include "fgTypes.h"
    #include "fgSingleton.h"

    #if defined FG_USING_MARMALADE

enum fgDeviceClass {
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

/*
 * #FIXME
 */
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
    fgBool m_android;
    /// Is the device iOS
    fgBool m_iOS;
    /// Is the device OSX
    fgBool m_OSX;
    /// Is the device BADA
    fgBool m_BADA;
    /// Is the device BB
    fgBool m_BB;
    /// Is information ready?
    fgBool m_computed;

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
    fgBool BB() {
        computeDevice();
        return m_BB;
    }
    fgBool BADA() {
        computeDevice();
        return m_BADA;
    }
};

        #define FG_DeviceQuery		 fgDeviceQuery::getInstance()

    #endif // FG_USING_MARMALADE

#endif /* FG_INC_DEVICE_QUERY */
