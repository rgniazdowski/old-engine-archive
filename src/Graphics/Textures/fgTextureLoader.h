/*******************************************************
* Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
* 
* This file is part of #FLEXIGAME_PROJECT
* 
* #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
* and/or distributed without the express or written permission from the author.
*******************************************************/

#ifndef _FG_TEXTURE_LOADER_H_
#define _FG_TEXTURE_LOADER_H_

#include "Util/fgFile.h"

#include "png.h"
extern "C" {
#include "jpeglib.h"
}

/*
 * Class contains static functions for loading image files as textures.
 * Every loading function returns an unsigned char array (1 dimension)
 * containing raw data compatible with OpenGL texture generation 
 * procedures (RGBA format #FIXME).
 */
class fgTextureLoader {
protected:
	struct fgJPEGErrorMgr {
		struct jpeg_error_mgr pub;
		jmp_buf setjmp_buffer;
	};
	typedef struct fgJPEGErrorMgr *fgJPEGErrorMgrPtr;

	static void fgJPEGErrorExit(j_common_ptr cinfo) {
		fgJPEGErrorMgrPtr myerr = (fgJPEGErrorMgrPtr)cinfo->err;
		(*cinfo->err->output_message)(cinfo);
		longjmp(myerr->setjmp_buffer,1);
	}
public:
	// Loads a JPEG file and returns unsigned char array with raw data
	static unsigned char *loadJPEG(const char *path, int &width, int &height);
	// Loads a JPEG file and returns unsigned char array with raw data
	static unsigned char *loadJPEG(fgFile *fileStream, int &width, int &height);
	
	// Loads a PNG file and returns unsigned char array with raw data
	static unsigned char *loadPNG(const char *path, int &width, int &height);
	// Loads a PNG file and returns unsigned char array with raw data
	static unsigned char *loadPNG(fgFile *fileStream, int &width, int &height);
	
	// Loads a TGA file and returns unsigned char array with raw data
	static unsigned char *loadTGA(const char *path, int &width, int &height);
	// Loads a TGA file and returns unsigned char array with raw data
	static unsigned char *loadTGA(fgFile *fileStream, int &width, int &height);
};

#endif
