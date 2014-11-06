/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

// #FIXME/#TODO - this needs more options for handling larger range of devices and platforms
// also should be somewhat platform independent - usage of system libs is highly recommended for
// aquiring info about CPU/GPU/platform/tools/system version and managing video quality / threads

#include "fgCommon.h"
#include "fgDeviceQuery.h"

#include <cstring>

#if defined FG_USING_MARMALADE
#include "s3eDevice.h"
//#endif

#include "fgLog.h"

static fgBool isAndroid();
static fgBool isiOS();
static fgBool isOSX();
static fgBool isBADA();
static fgBool isBB();

static fgBool try_device(const char* dev_id, const char* base_name, fgDeviceClass givenClass, fgDeviceClass& tryClass, int& tryVersion);
static fgDeviceGeneration computeGeneration(const char* dev_id, fgDeviceClass dev_class, int dev_version);

// enum DeviceClass { UNKNOWN, IPHONE, IPOD, IPAD, ANDROID };
static const char* class_to_name[5] = {"UNKNOWN", "IPHONE", "IPOD", "IPAD", "ANDROID"};

template <>
bool fgSingleton<fgDeviceQuery>::instanceFlag = false;

template <>
fgDeviceQuery *fgSingleton<fgDeviceQuery>::instance = NULL;

fgDeviceQuery::fgDeviceQuery() : m_deviceString(NULL), m_deviceVersion(0),
m_deviceClass(FG_DEVICE_CLASS_UNKNOWN),
m_deviceGeneration(FG_DEVICE_GENERATION_UNKNOWN),
m_android(FG_FALSE), m_iOS(FG_FALSE), m_computed(FG_FALSE) {
    // Compute Device is not being called here - it is done at first query!
}

fgDeviceQuery::~fgDeviceQuery() { }

/**
 * Prepares every needed data
 */
void fgDeviceQuery::computeDevice() {
    if(m_computed) {
        return;
    }

    m_android = isAndroid();
    m_iOS = isiOS();
    m_OSX = isOSX();
    m_BADA = isBADA();
    m_BB = isBB();

    // Get the information – as one string!
    const char* dev_id = s3eDeviceGetString(S3E_DEVICE_ID);
    if(dev_id) {
        m_deviceString = dev_id;
    } else {
        return;
    }

    int tryVersion = 0;
    fgDeviceClass tryClass = FG_DEVICE_CLASS_UNKNOWN;

    if(try_device(dev_id, "iPhone", FG_DEVICE_CLASS_IPHONE, tryClass, tryVersion)) {
        // OK, found :]
    } else if(try_device(dev_id, "iPod", FG_DEVICE_CLASS_IPOD, tryClass, tryVersion)) {
        // OK, found :]
    } else if(try_device(dev_id, "iPad", FG_DEVICE_CLASS_IPAD, tryClass, tryVersion)) {
        // OK, found :]
    } else if(try_device(dev_id, "Android", FG_DEVICE_CLASS_ANDROID, tryClass, tryVersion)) {
        // OK, found :]
    } else {
        // NOT FOUND
        tryVersion = 0;
        tryClass = FG_DEVICE_CLASS_UNKNOWN;
    }

    // Store computed values!
    m_deviceVersion = tryVersion;
    m_deviceClass = tryClass;


    // GENERATION
    m_deviceGeneration = computeGeneration(dev_id, m_deviceClass, m_deviceVersion);

    m_computed = FG_TRUE;

    FG_LOG_DEBUG("Detected [%s] DEVICE: %s, VERSION: %d, GENERATION: %d", dev_id, class_to_name[m_deviceClass], m_deviceVersion, m_deviceGeneration);
}

/**
 * Detects generation of the device
 */
static fgDeviceGeneration computeGeneration(const char* dev_id, fgDeviceClass dev_class, int dev_version) {

    /*
     * iOS Devices:
     * iPhone3G "iPhone1,2" -565348713 480x320
     * iPhone3GS "iPhone2,1" -565347625 480x320
     * iPhone4 "iPhone3,1" -565346536 960x640
     * iTouch 1st gen "iPod1,1" 1494189823 480x320
     * iTouch 2nd gen "iPod2,1" 1494190912 480x320
     * iPad1 wifi "iPad1,1" 1477586929 1024x768
     */

    // Default is fourth
    fgDeviceGeneration gen = FG_DEVICE_GENERATION_FOURTH;

    switch(dev_class) {
        case FG_DEVICE_CLASS_IPHONE:
            if(NULL != strstr(dev_id, "iPhone1,2")) {
                // iPhone 3G
                gen = FG_DEVICE_GENERATION_SECOND;
                FG_LOG::PrintError("Unsupported iPhone 3G detected!");
            } else if(NULL != strstr(dev_id, "iPhone2,1")) {
                // iPhone 3GS
                gen = FG_DEVICE_GENERATION_THIRD;
            } else if(NULL != strstr(dev_id, "iPhone3,1")) {
                // iPhone 4
                gen = FG_DEVICE_GENERATION_FOURTH;
            } else {
                // iPhone 4S or newer
                gen = FG_DEVICE_GENERATION_FIFTH;
            }
            break;
        case FG_DEVICE_CLASS_IPOD:
            if(NULL != strstr(dev_id, "iPod1,1")) {
                // iPod 1G
                gen = FG_DEVICE_GENERATION_FIRST;
                FG_LOG::PrintError("Unsupported iPod 1G detected!");
            } else if(NULL != strstr(dev_id, "iPod2,1")) {
                // iPod 2G
                gen = FG_DEVICE_GENERATION_SECOND;
                FG_LOG::PrintError("Unsupported iPod 2G detected!");
            } else if(NULL != strstr(dev_id, "iPod3,1")) {
                // iPod 3G
                gen = FG_DEVICE_GENERATION_THIRD;
            } else {
                // iPod 4G or newer
                gen = FG_DEVICE_GENERATION_FOURTH;
            }
            break;
        case FG_DEVICE_CLASS_IPAD:
            if(NULL != strstr(dev_id, "iPad1,1")) {
                // iPad 1G
                gen = FG_DEVICE_GENERATION_FIRST;
            } else {
                gen = FG_DEVICE_GENERATION_SECOND;
            }
            break;
    }

    FG_LOG_DEBUG("Device [%s] generation is: %dG", dev_id, gen);
    return gen;
}

/**
 * Detects device and it's main version.
 *
 * The main version may be unusable in practice, as generation is what matters.
 */
fgBool try_device(const char* dev_id, const char* base_name, fgDeviceClass givenClass, fgDeviceClass& tryClass, int& tryVersion) {
    FG_LOG_DEBUG("try_device(): Searching for %s VER in string: %s", base_name, dev_id);

    // Copy  the base name. Ensure there are two free bytes at the end.
    char name[20];
    strncpy(name, base_name, 18);
    name[18] = '\0';
    name[19] = '\0';
    int base_len = strlen(name);
    name[base_len + 1] = '\0';

    int version_found = 0;

    // Search for e.g. iPad1, iPad2, ...,
    for(int i = 0; i < 6; i++) {
        name[base_len] = '1' + i;
        if(NULL != strstr(dev_id, name)) {
            FG_LOG_DEBUG("try_device(): FOUND name=%s in dev_id=%s", name, dev_id);
            version_found = 1 + i;
            break;
        }
    }

    // FOUND
    if(version_found) {
        tryVersion = version_found;
        tryClass = givenClass;
        return FG_TRUE;
    }

    tryVersion = 0;
    tryClass = FG_DEVICE_CLASS_UNKNOWN;
    return FG_FALSE;
}

/**
 * Can query any OS - basic function
 */
static fgBool isPlatform(s3eDeviceOSID os) {
    return (fgBool)(os == s3eDeviceGetInt(S3E_DEVICE_OS));
}

/**
 * Detects if the current platform is Android.
 * @return true if the platform is Android, false otherwise.
 */
static fgBool isAndroid() {
    return isPlatform(S3E_OS_ID_ANDROID);
}

/**
 * Detects if the current platform is iOS.
 * @return true if the platform is iOS, false otherwise.
 */
static fgBool isiOS() {
    return isPlatform(S3E_OS_ID_IPHONE);
}

/**
 * Detects if the current platform is BADA
 */
static fgBool isBADA() {
    //    return isPlatform( S3E_OS_ID_BADA );
    return false;
}

/**
 * Detects if the current platform is OSX
 */
static fgBool isOSX() {
    return isPlatform(S3E_OS_ID_OSX);
}

/**
 * Detects if the current platform is BB
 */
static fgBool isBB() {
    return isPlatform(S3E_OS_ID_QNX);
}

#endif
