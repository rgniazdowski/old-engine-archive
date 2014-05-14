#pragma once

namespace DPI
{
	void dpiInit();
	void dpiTerminate();
	int32 dpiGetScreenDPI(int w, int h);
	//int32 dpiGetScreenDPI_iOS(int _w, int _h);
}
