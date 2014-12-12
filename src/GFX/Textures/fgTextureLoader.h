/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef FG_INC_TEXTURE_LOADER
    #define FG_INC_TEXTURE_LOADER

    #include "Util/fgFile.h"

    #include "png.h"
extern "C" {
    #include "jpeglib.h"
}

    #ifndef FG_TEXTURE_ALPHA_FIX_VALUE
    #define FG_TEXTURE_ALPHA_FIX_VALUE(_R, _G, _B) \
            ((_G < 16 && _R < 16 && _B < 16) ? 0 : (_R + _G + _B) / 3)
    #endif

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
        longjmp(myerr->setjmp_buffer, 1);
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

    static fgBool saveTGA(const char *path, const unsigned char* data, const int width, const int height);
};

#endif
