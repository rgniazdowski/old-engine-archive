#include <IwDebug.h>
#include <dpiInfo.h>
#include <dpiExt.h>
#include <cstring>

namespace DPI
{
    int initCounter = 0;
    bool g_dpiChached = false;
    int g_dpiChachedValue = 163;

    int32 dpiGetScreenDPI_iOS(int _w, int _h)
    {
        uint32 w = (uint32)_w;
        uint32 h = (uint32)_h;
#ifdef IW_DEBUG
        printf("Inside DPI_ext, w[%d], h[%d]\n", w, h);
#endif
        // Width is bigger
        if (w < h) {			
            w = _h;
            h = _w;
        }
        /////////////////////////////////////////////////////////////
        // Apple iPhone 6 Plus      5.5'	1080×1980   401	2.46
        // Apple iPhone 6           4.7'    1334x750    326	2
        // Apple iPhone 5           4.0'    1136x640    326	2
        // Apple iPhone 4, 4S       3.5'    960×640     326	2
        // Apple iPad mini Retina   7.9'    2048×1536   324	1
        // Apple iPad 3             9.7'    2048×1536   264	2
        // Apple iPad Retina        9.7'    2048×1536   264	2
        // Apple iPad Air           9.7'    2048×1536   264	2
        // Apple iPhone 1, 3G, 3GS  3.5'    480x320     163	1
        // Apple iPad mini          7.9'    1024×768    163	1
        // Apple iPad 1, 2          9.7'    1024×768    132	1
        /////////////////////////////////////////////////////////////
        const char* dev_id = s3eDeviceGetString(S3E_DEVICE_ID);

        // iPad 1 & 2
        if (w == 1024) {
            if(strstr(dev_id, "iPad1,1") != NULL ||
                strstr(dev_id, "iPad2,1") != NULL ||
                strstr(dev_id, "iPad2,2") != NULL ||
                strstr(dev_id, "iPad2,3") != NULL ||
                strstr(dev_id, "iPad2,4") != NULL) {
                    return 132;
            }
        }
        // iPad mini 1G
        if (w == 1024) {
            if(strstr(dev_id, "iPad2,5") != NULL ||
                strstr(dev_id, "iPad2,6") != NULL ||
                strstr(dev_id, "iPad2,7") != NULL) {
                    return 163;
            }
        }
        // iPhone 1, 3G, 3GS
        if (w == 480)
            return 163;        
        // iPad mini Retina (7.9')
        if (w == 2048) {
            // iPad4,4 | 4,5 | 4,6 | 4,7 | 4,8 | 4,9
            if(strstr(dev_id, "iPad4,4") != NULL ||
                strstr(dev_id, "iPad4,5") != NULL ||
                strstr(dev_id, "iPad4,6") != NULL ||
                strstr(dev_id, "iPad4,7") != NULL ||
                strstr(dev_id, "iPad4,8") != NULL ||
                strstr(dev_id, "iPad4,9") != NULL) {
                    return 324;
            }
        }
        // iPad Air / iPad Retina / iPad 3 (9.7')
        if (w == 2048) {
            return 264;
        }
        // iPhone 4 / 4S (3.5')
        if (w == 960) {
            return 326;
        }
        // New iPhone 640 x 1146 / iPhone 5
        if (w == 1146 || w == 1136) {
            return 326;
        }
        // iPhone 6
        if (w == 1334 || ( w > 1300 && w < 1360 )) {
            return 326;
        }
        // iPhone 6 Plus
        if (w > 1900 && w < 2000 && h > 1000) {
            return 401; // 1980x1080
        }
        return 160;
    }
}

using namespace DPI;

void DPI::dpiInit()
{
    ++initCounter;
    if (initCounter != 1)
        return;
}

void DPI::dpiTerminate()
{
    --initCounter;
    if (initCounter != 0)
        return;
}

int32 DPI::dpiGetScreenDPI(int w, int h)
{
    if (g_dpiChached)
        return g_dpiChachedValue;

    int32 os = s3eDeviceGetInt(S3E_DEVICE_OS);

    g_dpiChached = true;
    switch (os)
    {
    case S3E_OS_ID_IPHONE:
        g_dpiChachedValue = dpiGetScreenDPI_iOS(w, h);
        #if defined(IW_DEBUG)
        printf("DPI: CachedValue[%d] based on iOS product data and resolution.\n", g_dpiChachedValue);
        #endif
        break;
    case S3E_OS_ID_ANDROID:
        break;
    case S3E_OS_ID_OSX:
        break;
    case S3E_OS_ID_LINUX:
        break;
    case S3E_OS_ID_WINDOWS:
        break;
    case S3E_OS_ID_WP8:
        // Windows Phone 8
        break;
    case S3E_OS_ID_WP81:
        // Windows Phone 8.1
        break;
    case S3E_OS_ID_WS8:
        // Windows Store 8
        break;
    case S3E_OS_ID_WS81:
        // Windows Store 8.1
        break;
    case S3E_OS_ID_ARM_SEMIH:
        // ARM semihosted env (dev board)
        break;
    default:
        break;
    }
    if (dpiExtAvailable())
    {
        g_dpiChachedValue = dpiExtGetDeviceDPI();
        #if defined(IW_DEBUG)
            printf("DPI: special extension is available...\n");
            printf("DPI: Device DPI calculated via dpiExt: %d\n", g_dpiChachedValue);
        #endif
        if (g_dpiChachedValue == 0)
            g_dpiChachedValue = 163;
    }
    return g_dpiChachedValue;
}
