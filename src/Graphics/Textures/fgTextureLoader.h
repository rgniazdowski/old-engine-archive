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

#include "../../fgFileStream.h"

// #FIXME - this texture loader should look a lot differently - neet to support various file formats: bmp, raw, jpg, png, tga
#include "png.h"
extern "C" {
#include "jpeglib.h"
}

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
	static unsigned char *loadJPEG(const char *path, int &width, int &height);
	static unsigned char *loadJPEG(fgFileStream *fileStream, int &width, int &height);
	
	static unsigned char *loadPNG(const char *path, int &width, int &height);
	static unsigned char *loadPNG(fgFileStream *fileStream, int &width, int &height);
	
	static unsigned char *loadTGA(const char *path, int &width, int &height);
	static unsigned char *loadTGA(fgFileStream *fileStream, int &width, int &height);
};

#endif