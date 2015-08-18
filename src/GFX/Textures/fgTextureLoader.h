/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 ******************************************************************************/

#ifndef FG_INC_TEXTURE_LOADER
    #define FG_INC_TEXTURE_LOADER
    #define FG_INC_TEXTURE_LOADER_BLOCK

    #include "Util/fgFileBase.h"

    #define PNG_NO_STDIO
//#define PNG_NO_READ_SUPPORTED
//#define PNG_NO_WRITE_SUPPORTED
    #include "png.h"
extern "C" {
    #include "jpeglib.h"
}

    #ifndef FG_TEXTURE_ALPHA_FIX_VALUE
        #define FG_TEXTURE_ALPHA_FIX_VALUE(_R, _G, _B) \
            ((_G < 16 && _R < 16 && _B < 16) ? 0 : (_R + _G + _B) / 3)
    #endif

/*
 * Namespace contains functions for loading image files as textures.
 * Every loading function returns an unsigned char array (1 dimension)
 * containing raw data compatible with OpenGL texture generation 
 * procedures (RGBA format #FIXME).
 */
namespace fg {
    namespace gfx {

        namespace texture {

            /**
             * 
             */
            struct SJPEGErrorMgr {
                struct jpeg_error_mgr pub;
                jmp_buf setjmp_buffer;
            };
            typedef struct SJPEGErrorMgr *SJPEGErrorMgrPtr;
            /**
             *
             * @param cinfo
             */
            inline void FuncJPEGErrorExit(j_common_ptr cinfo) {
                SJPEGErrorMgrPtr myerr = (SJPEGErrorMgrPtr)cinfo->err;
                (*cinfo->err->output_message)(cinfo);
                longjmp(myerr->setjmp_buffer, 1);
            }

            /**
             * Loads a JPEG file and returns unsigned char array with raw data
             * @param path
             * @param width
             * @param height
             * @return
             */
            unsigned char *loadJPEG(const char *path, int &width, int &height);
            /**
             * Loads a JPEG file and returns unsigned char array with raw data
             * @param fileStream
             * @param width
             * @param height
             * @return
             */
            unsigned char *loadJPEG(fg::util::base::CFile *fileStream, int &width, int &height);

            /**
             * Loads a PNG file and returns unsigned char array with raw data
             * @param path
             * @param width
             * @param height
             * @return
             */
            unsigned char *loadPNG(const char *path, int &width, int &height);
            /**
             * Loads a PNG file and returns unsigned char array with raw data
             * @param fileStream
             * @param width
             * @param height
             * @return
             */
            unsigned char *loadPNG(fg::util::base::CFile *fileStream, int &width, int &height);

            /**
             * Loads a TGA file and returns unsigned char array with raw data
             * @param path
             * @param width
             * @param height
             * @return
             */
            unsigned char *loadTGA(const char *path, int &width, int &height);
            /**
             * Loads a TGA file and returns unsigned char array with raw data
             * @param fileStream
             * @param width
             * @param height
             * @return
             */
            unsigned char *loadTGA(fg::util::base::CFile *fileStream, int &width, int &height);

            fgBool saveTGA(const char *path, const unsigned char* data, const int width, const int height);

        } // namespace texture
    } // namespace gfx
} // namespace fg

    #undef FG_INC_TEXTURE_LOADER_BLOCK
#endif // FG_INC_TEXTURE_LOADER
