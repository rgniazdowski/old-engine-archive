#include <IwDebug.h>
#include <dpiInfo.h>
// #include <iwgx.h>
//#include <IwGL.h>
#include <dpiExt.h>

namespace DPI
{
	int initCounter = 0;
	bool g_dpiChached = false;
	int g_dpiChachedValue = 163;

	int32 dpiGetScreenDPI_Bada()
	{
		switch (s3eDeviceGetInt(S3E_DEVICE_ID))
		{
			case 754973890: //Wave 525 ("GT-S5250")
				return 146;
			case 755065988: //Bada Wave GT-S8500
				return 283;
			default:
				break;
		}
		return 146;
	}

	int32 dpiGetScreenDPI_iOS(int _w, int _h)
	{
		//uint32 w = IwGLGetInt(IW_GL_WIDTH);
		//uint32 h = IwGLGetInt(IW_GL_HEIGHT);
		uint32 w = (uint32) _w;
		uint32 h = (uint32) _h;
#ifdef IW_DEBUG
		printf("Inside DPI_ext, w[%d], h[%d]\n", w, h);
#else
		printf("DPI extension\n");
#endif

		// W is bigger
		if (w<h)
		{
			uint32 i = w;
			w=h;
			h=i;
		}

		if (w == 480)   // iPhone 3 and older
				return 163;
		if (w == 1024)  // iPad 1 & 2
				return 132;
		if (w == 960)   // iPhone 4
				return 326;
		if (w == 2048)  // iPad 3
				return 264;
		if (w == 1146 || w == 1136)  // New iPhone 640 x 1146
				return 326;
		if (w > 1000)
				return 240;
		if (w > 800)
				return 220;
		if (w > 700)
				return 200;
		if (w > 600)
				return 180;
		return 163;

		//const char* deviceID = s3eDeviceGetString(S3E_DEVICE_ID);
		//return 326; //Retina display 960x640
		//return 132; //iPad 1024x768
		//return 163; //old ipod/iphone; 480x320
	}

}

using namespace DPI;

void DPI::dpiInit()
{
	++initCounter;
	if (initCounter != 1)
		return;

	//IW_CLASS_REGISTER(CfthFont);
}

void DPI::dpiTerminate()
{
	--initCounter;
	if (initCounter < 0)
		IwAssertMsg(FREETYPE,false,("dpiTerminate doesn't match dpiInit"));
	if (initCounter != 0)
		return;
}

// General DPI
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
		break;
//	case S3E_OS_ID_BADA:
	//	g_dpiChachedValue = dpiGetScreenDPI_Bada();
		//break; // FIXME
	default:
		break;
	}
	if (dpiExtAvailable())
	{
		g_dpiChachedValue = dpiExtGetDeviceDPI();
		if (g_dpiChachedValue == 0)
			g_dpiChachedValue = 163;
	}
	return g_dpiChachedValue;
}
