/*******************************************************************************
* Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
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
static fgBool isQNX();

static fgBool try_device(const char* dev_id, 
                         const char* base_name,
                         fgDeviceClass givenClass, 
                         fgDeviceClass& tryClass);

// enum DeviceClass { UNKNOWN, IPHONE, IPOD, IPAD, ANDROID };
static const char* class_to_name[5] = {"UNKNOWN", "IPHONE", "IPOD", "IPAD", "ANDROID"};

fgDeviceQuery::fgDeviceQuery() : 
    m_deviceString(NULL),
    m_deviceClass(FG_DEVICE_CLASS_UNKNOWN),
    m_deviceGeneration(FG_DEVICE_GENERATION_UNKNOWN),
    m_deviceModel(FG_DEVICE_MODEL_UNKNOWN),
    m_android(FG_FALSE),
    m_iOS(FG_FALSE), m_OSX(FG_FALSE), m_QNX(FG_FALSE),
    m_computed(FG_FALSE) {
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
    m_QNX = isQNX();

    /*
    ("SUPPORTS_SUSPEND_RESUME: %d", s3eDeviceGetInt(S3E_DEVICE_SUPPORTS_SUSPEND_RESUME));
    ("NUM_CPU_CORES          : %d", s3eDeviceGetInt(S3E_DEVICE_NUM_CPU_CORES));
    ("LOCALE                 : %s", s3eDeviceGetString(S3E_DEVICE_LOCALE));
    ("LANGUAGE CODE          : %d", s3eDeviceGetInt(S3E_DEVICE_LANGUAGE));
    ("LANGUAGE               : %s", s3eDeviceGetString(S3E_DEVICE_LANGUAGE));
    ("MEM_FREE               : %d", s3eDeviceGetInt(S3E_DEVICE_MEM_FREE));
    ("MEM_TOTAL              : %d", s3eDeviceGetInt(S3E_DEVICE_MEM_TOTAL));
    ("BATTERY_LEVEL          : %d", s3eDeviceGetInt(S3E_DEVICE_BATTERY_LEVEL));
    ("MAINS_POWER            : %d", s3eDeviceGetInt(S3E_DEVICE_MAINS_POWER));
    ("CHIPSET                : %s", s3eDeviceGetString(S3E_DEVICE_CHIPSET));
    ("IMSI                   : %s", s3eDeviceGetString(S3E_DEVICE_IMSI));
    ("PHONE_NUMBER           : %s", s3eDeviceGetString(S3E_DEVICE_PHONE_NUMBER));
    ("NAME                   : %s", s3eDeviceGetString(S3E_DEVICE_NAME));
    ("UNIQUE_ID              : %s", s3eDeviceGetString(S3E_DEVICE_UNIQUE_ID));
    ("ID                     : %s", s3eDeviceGetString(S3E_DEVICE_ID));
    ("ARCHITECTURE           : %s", s3eDeviceGetString(S3E_DEVICE_ARCHITECTURE));
    ("OS_VERSION             : %s", s3eDeviceGetString(S3E_DEVICE_OS_VERSION));
    ("OS                     : %s", s3eDeviceGetString(S3E_DEVICE_OS));
    */

    // Get the information – as one string!
    const char* dev_id = s3eDeviceGetString(S3E_DEVICE_ID);
    if(dev_id) {
        m_deviceString = dev_id;
    } else {
        return;
    }
    fgDeviceClass tryClass = FG_DEVICE_CLASS_UNKNOWN;

    if(try_device(dev_id, "iPhone", FG_DEVICE_CLASS_IPHONE, tryClass)) {
        // OK, found :]
    } else if(try_device(dev_id, "iPod", FG_DEVICE_CLASS_IPOD, tryClass)) {
        // OK, found :]
    } else if(try_device(dev_id, "iPad", FG_DEVICE_CLASS_IPAD, tryClass)) {
        // OK, found :]
    } else if(try_device(dev_id, "Android", FG_DEVICE_CLASS_ANDROID, tryClass)) {
        // OK, found :]
    } else {
        // NOT FOUND
        tryClass = FG_DEVICE_CLASS_UNKNOWN;
    }
    m_deviceClass = tryClass;
    
    // COMPUTE GENERATION
    computeGeneration();

    m_computed = FG_TRUE;
    FG_LOG_DEBUG("Detected [%s] DEVICE: %s, GENERATION: %d", dev_id, class_to_name[m_deviceClass], m_deviceGeneration);
}

/**
* Detects generation of the device
*/
void fgDeviceQuery::computeGeneration(void) {

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
    fgDeviceModel model = FG_DEVICE_MODEL_UNKNOWN;
    const char *dev_id = m_deviceString;
    switch(m_deviceClass) {
        //
        // APPLE IPHONE GENERAL CLASS CHECK
        //
    case FG_DEVICE_CLASS_IPHONE:
        if(NULL != strstr(dev_id, "iPhone1,1")) {
            // iPhone - first
            // A1203
            // 1G
            // Internal name: m68ap
            gen = FG_DEVICE_GENERATION_FIRST;
            model = FG_DEVICE_MODEL_IPHONE;
            FG_LOG_ERROR("Unsupported iPhone (first gen) detected!");
        } else if(NULL != strstr(dev_id, "iPhone1,2")) {
            // iPhone 3G
            // A1241 / A1324
            // Internal name: n82ap
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPHONE_3G;
            FG_LOG_ERROR("Unsupported iPhone 3G detected!");
        } else if(NULL != strstr(dev_id, "iPhone2,1")) {
            // iPhone 3GS
            // A1303 / A1325
            // Internal name: n88ap
            gen = FG_DEVICE_GENERATION_THIRD;
            model = FG_DEVICE_MODEL_IPHONE_3GS;
        } else if(NULL != strstr(dev_id, "iPhone3,1")) {
            // iPhone 4
            // A1332
            // Internal name: n90ap
            // Bootrom 574.4
            gen = FG_DEVICE_GENERATION_FOURTH;
            model = FG_DEVICE_MODEL_IPHONE_4;
        } else if(NULL != strstr(dev_id, "iPhone3,2")) {
            // iPhone 4
            // A1332
            // Internal name: n90bap
            // Bootrom 574.4
            gen = FG_DEVICE_GENERATION_FOURTH;
            model = FG_DEVICE_MODEL_IPHONE_4;
        } else if(NULL != strstr(dev_id, "iPhone3,3")) {
            // iPhone 4
            // A1349
            // Internal name: n92ap
            // Bootrom 574.4
            gen = FG_DEVICE_GENERATION_FOURTH;
            model = FG_DEVICE_MODEL_IPHONE_4;
        } else if(NULL != strstr(dev_id, "iPhone4,1")) {
            // iPhone 4S
            // A1387 / A1431
            // Internal name: n94ap
            // Bootrom 838.3
            gen = FG_DEVICE_GENERATION_FIFTH;
            model = FG_DEVICE_MODEL_IPHONE_4S;
        } else if(NULL != strstr(dev_id, "iPhone5,1")) {
            // iPhone 5
            // A1428
            // Internal name: n41ap
            // Bootrom 1145.3
            gen = FG_DEVICE_GENERATION_SIXTH;
            model = FG_DEVICE_MODEL_IPHONE_5;
        } else if(NULL != strstr(dev_id, "iPhone5,2")) {
            // iPhone 5
            // A1429 / A1442
            // Internal name: n42ap
            // Bootrom 1145.3
            gen = FG_DEVICE_GENERATION_SIXTH;
            model = FG_DEVICE_MODEL_IPHONE_5;
        } else if(NULL != strstr(dev_id, "iPhone5,3")) {
            // iPhone 5c
            // A1456 / A1532
            // Internal name: n48ap 
            // Bootrom 1145.3
            gen = FG_DEVICE_GENERATION_SEVENTH;
            model = FG_DEVICE_MODEL_IPHONE_5C;
        } else if(NULL != strstr(dev_id, "iPhone5,4")) {
            // iPhone 5c
            // A1507 / A1516 / A1526 / A1529
            // Internal name: n49ap
            // Bootrom 1145.3
            gen = FG_DEVICE_GENERATION_SEVENTH;
            model = FG_DEVICE_MODEL_IPHONE_5C;
        } else if(NULL != strstr(dev_id, "iPhone6,1")) {
            // iPhone 5s
            //  A1453 / A1533 
            // Internal name: n51ap
            // Bootrom 1704.10 
            gen = FG_DEVICE_GENERATION_SEVENTH;
            model = FG_DEVICE_MODEL_IPHONE_5S;
        } else if(NULL != strstr(dev_id, "iPhone6,2")) {
            // iPhone 5s
            // A1457 / A1518 / A15281 / A1530 
            // Internal name: n53ap
            // Bootrom 1704.10 
            gen = FG_DEVICE_GENERATION_SEVENTH;
            model = FG_DEVICE_MODEL_IPHONE_5S;
        } else if(NULL != strstr(dev_id, "iPhone7,2")) {
            // iPhone 6
            // A1549 / A1586
            // Internal name: n61ap
            // Bootrom 1992.0.0.1.19
            gen = FG_DEVICE_GENERATION_EIGHTH;
            model = FG_DEVICE_MODEL_IPHONE_6;
        } else if(NULL != strstr(dev_id, "iPhone7,1")) {
            // iPhone 6 Plus
            // A1522 / A1524 
            // Internal name: n56ap
            // Bootrom 1992.0.0.1.19
            gen = FG_DEVICE_GENERATION_EIGHTH;
            model = FG_DEVICE_MODEL_IPHONE_6_PLUS;
        } else {
            // iPhone 4S or newer - minimum
            gen = FG_DEVICE_GENERATION_FIFTH;
        }
        break;
        //
        // IPOD GENERAL CLASS CHECK
        //
    case FG_DEVICE_CLASS_IPOD:
        if(NULL != strstr(dev_id, "iPod1,1")) {
            // iPod 1G / iPod touch
            // A1213
            // Internal name: n45ap
            // Bootrom Rev. 2            
            gen = FG_DEVICE_GENERATION_FIRST;
            model = FG_DEVICE_MODEL_IPOD_TOUCH;
            FG_LOG_ERROR("Unsupported iPod 1G detected!");
        } else if(NULL != strstr(dev_id, "iPod2,1")) {
            // iPod touch 2G
            // A1288
            // Internal name: n72ap
            // Bootrom 240.4/240.5.1
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPOD_TOUCH_2G;
            FG_LOG_ERROR("Unsupported iPod 2G detected!");
        } else if(NULL != strstr(dev_id, "iPod3,1")) {
            // iPod touch 3G
            // A1318
            // Internal name: n18ap
            // Bootrom 359.5
            gen = FG_DEVICE_GENERATION_THIRD;
            model = FG_DEVICE_MODEL_IPOD_TOUCH_3G;
        } else if(NULL != strstr(dev_id, "iPod4,1")) {
            // iPod touch 4G
            // A1367
            // Internal name: n81ap
            // Bootrom 574.4
            gen = FG_DEVICE_GENERATION_FOURTH;
            model = FG_DEVICE_MODEL_IPOD_TOUCH_4G;
        } else if(NULL != strstr(dev_id, "iPod5,1")) {
            // iPod touch 5G
            // A1421
            // Internal name: n78ap
            // A1509 / n78aap
            gen = FG_DEVICE_GENERATION_FIFTH;
            model = FG_DEVICE_MODEL_IPOD_TOUCH_5G;
        } else {
            // iPod 4G or newer
            gen = FG_DEVICE_GENERATION_FOURTH;
        }
        break;
        //
        // APPLE IPAD / IPAD MINI GENERAL CLASS CHECK
        //
    case FG_DEVICE_CLASS_IPAD:
        //
        // Checking for the big iPad - 1,2,3,... gen
        //
        if(NULL != strstr(dev_id, "iPad1,1")) {
            // iPad 1G
            // A1219 / A1337
            gen = FG_DEVICE_GENERATION_FIRST;
            model = FG_DEVICE_MODEL_IPAD_1;
        } else if(NULL != strstr(dev_id, "iPad2,1")) {
            // iPad2
            // A1395
            // dual-core 1 GHz[1] S5L8940 CPU (A5 chip)
            // 132DPI / 512MB RAM / 1024x768
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPAD_2;
        } else if(NULL != strstr(dev_id, "iPad2,2")) { 
            // iPad2
            // A1396
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPAD_2;
        } else if(NULL != strstr(dev_id, "iPad2,3")) { 
            // iPad2
            // A1397
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPAD_2;
        } else if(NULL != strstr(dev_id, "iPad2,4")) { 
            // iPad2
            // A1395
            // S5L8942 - This is a revised version of the S5L8940 that is included in Apple TV 3G, iPod touch 5G, 
            // iPad 2 (iPad2,4) and the iPad mini 1G. The most notable difference is a switch to a 32 nm
            // manufacturing process, as opposed to 45 nm. 
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPAD_2;
        } else if(NULL != strstr(dev_id, "iPad3,1")) { 
            // iPad3
            // A1416
            // 264DPI / 1GB RAM / 2048x1536
            // S5L8945 / Apple A5X / Cortex-A9 - 950MHz
            // Architecture: armv7f
            gen = FG_DEVICE_GENERATION_THIRD;
            model = FG_DEVICE_MODEL_IPAD_3;
        } else if(NULL != strstr(dev_id, "iPad3,2")) { 
            // iPad3
            // A1403
            // 264DPI / 1GB RAM / 2048x1536
            gen = FG_DEVICE_GENERATION_THIRD;
        } else if(NULL != strstr(dev_id, "iPad3,3")) { 
            // iPad3
            // A1430
            // 264DPI / 1GB RAM / 2048x1536
            gen = FG_DEVICE_GENERATION_THIRD;
            model = FG_DEVICE_MODEL_IPAD_3;
        } else if(NULL != strstr(dev_id, "iPad3,4")) { 
            // iPad4
            // A1458
            // 264DPI / 1GB RAM / 2048x1536
            // S5L8955 / Apple A6X
            gen = FG_DEVICE_GENERATION_FOURTH;
            model = FG_DEVICE_MODEL_IPAD_4;
        } else if(NULL != strstr(dev_id, "iPad3,5")) { 
            // iPad4
            // A1459
            // 264DPI / 1GB RAM / 2048x1536
            gen = FG_DEVICE_GENERATION_FOURTH;
            model = FG_DEVICE_MODEL_IPAD_4;
        } else if(NULL != strstr(dev_id, "iPad3,6")) { 
            // iPad4
            // A1460
            // 264DPI / 1GB RAM / 2048x1536
            gen = FG_DEVICE_GENERATION_FOURTH;
            model = FG_DEVICE_MODEL_IPAD_4;
        } else if(NULL != strstr(dev_id, "iPad4,1")) { 
            // iPad Air
            // A1474
            // 264DPI / 1GB RAM / 2048x1536
            // S5L8965 / A7 Variant
            gen = FG_DEVICE_GENERATION_FIFTH;
            model = FG_DEVICE_MODEL_IPAD_AIR;
        } else if(NULL != strstr(dev_id, "iPad4,2")) { 
            // iPad Air
            // A1475
            // 264DPI / 1GB RAM / 2048x1536
            gen = FG_DEVICE_GENERATION_FIFTH;
            model = FG_DEVICE_MODEL_IPAD_AIR;
        } else if(NULL != strstr(dev_id, "iPad4,3")) { 
            // iPad Air
            // A1476
            // 264DPI / 1GB RAM / 2048x1536
            gen = FG_DEVICE_GENERATION_FIFTH;
            model = FG_DEVICE_MODEL_IPAD_AIR;
        } else if(NULL != strstr(dev_id, "iPad5,3")) {
            // iPad Air 2
            // A1566
            // 264DPI / 1GB RAM / 2048x1536
            // T7001 / Apple A8X / 64bit / 3core 1.5GHz
            gen = FG_DEVICE_GENERATION_SIXTH;
            model = FG_DEVICE_MODEL_IPAD_AIR_2;
        } else if(NULL != strstr(dev_id, "iPad5,4")) {
            // iPad Air 2
            // A1567
            // 264DPI / 1GB RAM / 2048x1536
            // T7001 / Apple A8X / 64bit / 3core 1.5GHz
            gen = FG_DEVICE_GENERATION_SIXTH;
            model = FG_DEVICE_MODEL_IPAD_AIR_2;
        }
        //
        // Checking for iPad mini ...
        //
        if(NULL != strstr(dev_id, "iPad2,5")) { 
            // iPad mini 1G
            // A1432
            // Internal name: p105ap
            // Normal display 1024x768 / 163 DPI
            gen = FG_DEVICE_GENERATION_FIRST;
            model = FG_DEVICE_MODEL_IPAD_MINI_1;
        } else if(NULL != strstr(dev_id, "iPad2,6")) { 
            // iPad mini 1G
            // A1454
            // Internal name: p106ap
            // Normal display 1024x768 / 163 DPI
            gen = FG_DEVICE_GENERATION_FIRST;
            model = FG_DEVICE_MODEL_IPAD_MINI_1;
        } else if(NULL != strstr(dev_id, "iPad2,7")) { 
            // iPad mini 1G
            // A1455
            // Internal name: p107ap
            // Normal display 1024x768 / 163 DPI
            gen = FG_DEVICE_GENERATION_FIRST;
            model = FG_DEVICE_MODEL_IPAD_MINI_1;
        } else if(NULL != strstr(dev_id, "iPad4,4")) { 
            // iPad mini 2
            // A1489
            // Internal name: j85ap
            // Retina display - 2048x1536 / 324 DPI
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPAD_MINI_2;
        } else if(NULL != strstr(dev_id, "iPad4,5")) { 
            // iPad mini 2
            // A1490
            // Internal name: j86ap
            // Retina display - 2048x1536 / 324 DPI
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPAD_MINI_2;
        } else if(NULL != strstr(dev_id, "iPad4,6")) { 
            // iPad mini 2
            // A1491
            // Internal name: j87ap
            // Retina display - 2048x1536 / 324 DPI
            gen = FG_DEVICE_GENERATION_SECOND;
            model = FG_DEVICE_MODEL_IPAD_MINI_2;
        } else if(NULL != strstr(dev_id, "iPad4,7")) { 
            // iPad mini 3
            // A1599
            // Internal name: j85map
            // Retina display - 2048x1536 / 324 DPI
            gen = FG_DEVICE_GENERATION_THIRD;
            model = FG_DEVICE_MODEL_IPAD_MINI_3;
        } else if(NULL != strstr(dev_id, "iPad4,8")) { 
            // iPad mini 3
            // A1600
            // Internal name: j86map
            // Retina display - 2048x1536 / 324 DPI
            gen = FG_DEVICE_GENERATION_THIRD;
            model = FG_DEVICE_MODEL_IPAD_MINI_3;
        } else if(NULL != strstr(dev_id, "iPad4,9")) { 
            // iPad mini 3
            // A1601
            // Internal name: j87map
            // Retina display - 2048x1536 / 324 DPI
            gen = FG_DEVICE_GENERATION_THIRD;
            model = FG_DEVICE_MODEL_IPAD_MINI_3;
        }
        break;
    }
    FG_LOG_DEBUG("Device [%s] generation is: %dG", dev_id, gen);
    m_deviceGeneration = gen;
}

/**
* Detects device and it's main version.
*
* The main version may be unusable in practice, as generation is what matters.
*/
fgBool try_device(const char* dev_id,
                  const char* base_name, 
                  fgDeviceClass givenClass, 
                  fgDeviceClass& tryClass) {
    FG_LOG_DEBUG("fg::device: Searching for '%s' VER in string: '%s'", base_name, dev_id);
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
            FG_LOG_DEBUG("fg::device: found name[%s] in devid=[%s]", name, dev_id);
            version_found = 1 + i;
            break;
        }
    }
    // FOUND
    if(version_found) {
        tryClass = givenClass;
        return FG_TRUE;
    }
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
* Detects if the current platform is OSX
*/
static fgBool isOSX() {
    return isPlatform(S3E_OS_ID_OSX);
}

/**
* Detects if the current platform is BB
*/
static fgBool isQNX() {
    return isPlatform(S3E_OS_ID_QNX);
}

#endif
