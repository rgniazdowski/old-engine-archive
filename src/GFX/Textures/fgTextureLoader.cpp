/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgTextureLoader.h"
#include "Util/fgPath.h"
#include "fgLog.h"

/*
 * This function is used for preloading given file for later processing
 */
static unsigned char *universalPreLoad(const char *path, int &width, int &height, const char *extType) {
    if(!path) {
        // #TODO error handling / reporting
        return NULL;
    }
    fgFile *fileStream = new fgFile(path);
    if(fileStream->open(FG_FILE_MODE_READ | FG_FILE_MODE_BINARY)) {
        unsigned char *data = NULL;
        if(strncasecmp(extType, "jpeg", 4) == 0) {
            data = fgTextureLoader::loadJPEG(fileStream, width, height);
        } else if(strncasecmp(extType, "png", 4) == 0) {
            data = fgTextureLoader::loadPNG(fileStream, width, height);
        } else if(strncasecmp(extType, "tga", 4) == 0) {
            data = fgTextureLoader::loadTGA(fileStream, width, height);
        }
        if(!fileStream->close()) {
            // #TODO error handling / reporting
        }
        delete fileStream;
        if(!data) {
            // #TODO error handling / reporting
            return NULL;
        }
        return data;
    } else {
        delete fileStream;
        // #TODO error handling / reporting
        return NULL;
    }
}

/*
 * Loads a JPEG file and returns unsigned char array with raw data
 */
unsigned char *fgTextureLoader::loadJPEG(const char *path, int &width, int &height) {
    return universalPreLoad(path, width, height, "jpeg");
}

/*
 * Loads a JPEG file and returns unsigned char array with raw data
 */
unsigned char *fgTextureLoader::loadJPEG(fgFile *fileStream, int &width, int &height) {
    if(!fileStream) {
        // #TODO error handling / reporting
        return NULL;
    } else if(!fileStream->isOpen()) {
        if(!fileStream->open(FG_FILE_MODE_READ | FG_FILE_MODE_BINARY)) {
            // #TODO error handling / reporting
            return NULL;
        }
    }

    unsigned char *data = NULL;
    int i = 0, j = 0, rowStride = -1;
    long cont = 0;
    struct jpeg_decompress_struct cinfo;
    struct fgJPEGErrorMgr jpegError;
    JSAMPARRAY buffer;
    JSAMPLE *dataBuffer = NULL;

    cinfo.err = jpeg_std_error(&jpegError.pub);
    jpegError.pub.error_exit = fgJPEGErrorExit;
    if(setjmp(jpegError.setjmp_buffer)) {
        // #TODO error handling / reporting
        jpeg_destroy_decompress(&cinfo);
        return NULL;
    }
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fileStream->getFilePtr());
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    rowStride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) & cinfo, JPOOL_IMAGE, rowStride, 1);
    dataBuffer = new JSAMPLE[cinfo.image_width * cinfo.image_height * cinfo.output_components];

    while(cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(dataBuffer + cinfo.image_width * cinfo.output_components * cont, buffer[0], rowStride);
        cont++;
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    width = cinfo.image_width;
    height = cinfo.image_height;
    data = new unsigned char[width * height * 4];

    switch(cinfo.output_components) {
        case 1:
            for(i = 0, j = 0; i < width * height; i++, j += 4) {
                data[j] = data[j + 1] = data[j + 2] = dataBuffer[i];
                data[j + 3] = 255;
            }
            break;
        case 3:
            for(i = 0, j = 0; i < width * height * 3; i += 3, j += 4) {
                data[j] = dataBuffer[i];
                data[j + 1] = dataBuffer[i + 1];
                data[j + 2] = dataBuffer[i + 2];
                data[j + 3] = 255;
            }
            break;
        default:
            // #TODO error handling / reporting
            delete [] data;
            delete [] dataBuffer;
            return NULL;
    }
    delete [] dataBuffer;
    FG_LOG::PrintInfo("JPEG LOAD: %s, %dx%d, data=%p;", fileStream->getPath(), width, height, data);
    return data;
}

/*
 * Loads a PNG file and returns unsigned char array with raw data
 */
unsigned char *fgTextureLoader::loadPNG(const char *path, int &width, int &height) {
    return universalPreLoad(path, width, height, "png");
}

/*
 * Loads a PNG file and returns unsigned char array with raw data
 */
unsigned char *fgTextureLoader::loadPNG(fgFile *fileStream, int &width, int &height) {
    if(!fileStream) {
        // #TODO error handling / reporting
        return NULL;
    } else if(!fileStream->isOpen()) {
        if(!fileStream->open(FG_FILE_MODE_READ | FG_FILE_MODE_BINARY)) {
            // #TODO error handling / reporting
            return NULL;
        }
    }
    double gamma = 0.0;
    unsigned char *data = NULL;
    png_uint_32 w = 0, h = 0;
    int i, j, k, l, bit_depth, color_type;
    png_uint_32 channels, row_bytes;
    png_byte *img = NULL, **row = NULL, sig[8];
    png_structp png_ptr = 0;
    png_infop info_ptr = 0;

    fileStream->read(sig, 8, 1);
    if(!png_check_sig(sig, 8)) {
        // #TODO error handling / reporting
        return NULL;
    }
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    if(!png_ptr) {
        // #TODO error handling / reporting
        return NULL;
    }
    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) {
        // #TODO error handling / reporting
        png_destroy_read_struct(&png_ptr, 0, 0);
        return NULL;
    }
    png_init_io(png_ptr, fileStream->getFilePtr());
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, 0, 0, 0);

    if(bit_depth == 16)
        png_set_strip_16(png_ptr);
    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_expand(png_ptr);
    if(bit_depth < 8)
        png_set_expand(png_ptr);
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_expand(png_ptr);
    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png_ptr);
    }

    if(png_get_gAMA(png_ptr, info_ptr, &gamma)) {
        png_set_gamma(png_ptr, (double)2.2, gamma);
    }
    png_read_update_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, 0, 0, 0);

    row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    channels = png_get_channels(png_ptr, info_ptr);
    //img = (png_byte*)malloc(sizeof(png_byte) * row_bytes * h);
    img = new png_byte[row_bytes * h];
    //row = (png_byte**)malloc(sizeof(png_byte*) * h);
    row = new png_byte*[h];

    for(i = 0; i < (int)h; i++) {
        row[i] = img + row_bytes * i;
    }
    png_read_image(png_ptr, row);
    png_read_end(png_ptr, NULL);
    //data = (unsigned char*)malloc(sizeof(unsigned char) * w * h * 4);
    data = new unsigned char[w * h * 4];
    switch(channels) {
        case 4:
            for(j = 0, k = 0; j < (int)h; j++)
                for(i = 0; i < (int)w; i++, k += 4) {
                    l = row_bytes * j + i * 4;
                    data[k + 0] = img[l + 0];
                    data[k + 1] = img[l + 1];
                    data[k + 2] = img[l + 2];
                    data[k + 3] = img[l + 3];
                }
            break;
        case 3:
            for(j = 0, k = 0; j < (int)h; j++)
                for(i = 0; i < (int)w; i++, k += 4) {
                    l = row_bytes * j + i * 3;
                    data[k + 0] = img[l + 0];
                    data[k + 1] = img[l + 1];
                    data[k + 2] = img[l + 2];
                    data[k + 3] = 255;
                }
            break;
    }
    delete [] img;
    delete [] row;
    png_destroy_info_struct(png_ptr, &info_ptr);
    png_destroy_read_struct(&png_ptr, 0, 0);
    png_ptr = NULL;
    info_ptr = NULL;

    width = (int)w;
    height = (int)h;
    FG_LOG::PrintInfo("PNG LOAD: %s, %dx%d, data=%p;", fileStream->getPath(), w, h, data);
    return data;
}

/*
 * Loads a TGA file and returns unsigned char array with raw data
 */
unsigned char *fgTextureLoader::loadTGA(const char *path, int &width, int &height) {
    return universalPreLoad(path, width, height, "tga");
}

/*
 * Loads a TGA file and returns unsigned char array with raw data
 */
unsigned char *fgTextureLoader::loadTGA(fgFile *fileStream, int &width, int &height) {
    if(!fileStream) {
        FG_LOG::PrintError("%s(%d): fileStream is NULL - failed to load texture - in function %s.", fgPath::fileName(__FILE__), __LINE__ - 1, __FUNCTION__);
        // #TODO error handling / reporting
        return NULL;
    } else if(!fileStream->isOpen()) {
        if(!fileStream->open(FG_FILE_MODE_READ | FG_FILE_MODE_BINARY)) {
            FG_LOG::PrintError("%s(%d): failed to open texture file - in function %s.", fgPath::fileName(__FILE__), __LINE__ - 1, __FUNCTION__);
            // #TODO error handling / reporting
            return NULL;
        }
    }
    unsigned char rep, *data = NULL, *buffer = NULL;
    unsigned char *ptr = NULL, info[18];
    int w = 0, h = 0, components = 0, size = 0;
    int i = 0, j = 0, k = 0, l = 0;
    fileStream->read(&info, 1, 18);
    w = info[12] + info[13] * 256;
    h = info[14] + info[15] * 256;
    // Read only 32 && 24 bit per pixel
    switch(info[16]) {
        case 32:
            components = 4; // 32 bit per pixel (RGBA)
            break;
        case 24:
            components = 3; // 24 bit per pixel (RGB)
            break;
        default:
            // #TODO error handling / reporting
            return NULL;
    }
    size = w * h * components;
    //buffer = (unsigned char*)malloc(Size);
    //data = (unsigned char*)malloc(w * h * 4);
    // FIXME - while using operator new for allocating arrays there needs to be a check for an exception
    // however operator new is overloaded (when using Marmalade), so when 'new' fails it will return NULL
    // NOTE: while compiling without marmalade there needs to be a proper check or at least use of std::nothrow
    // Buffer for RGB or RGBA image
    buffer = new unsigned char[size];
    // Output RGBA image
    data = new unsigned char[w * h * 4];
    if(!data || !buffer) {
        FG_LOG::PrintError("%s(%d): failed to allocate new data  - in function %s.", fgPath::fileName(__FILE__), __LINE__ - 1, __FUNCTION__);
        // #TODO error handling / reporting
        return NULL;
    }
    fileStream->setPosition(info[0], SEEK_CUR);
    i = 0;
    ptr = buffer;
    switch(info[2]) {
            // Unmapped RGB image
        case 2:
            fileStream->read(buffer, 1, size);
            break;
            // Run length encoded file
        case 10:
            while(i < size) {
                fileStream->read(&rep, 1, 1);
                if(rep & 0x80) {
                    rep ^= 0x80;
                    fileStream->read(ptr, 1, components);
                    ptr += components;
                    for(j = 0; j < rep * components; j++) {
                        *ptr = *(ptr - components);
                        ptr++;
                    }
                    i += components * (rep + 1);
                } else {
                    k = components * (rep + 1);
                    fileStream->read(ptr, 1, k);
                    ptr += k;
                    i += k;
                }
            }
            break;
        default:
            delete [] buffer;
            delete [] data;
            return 0;
    }
    // Conversion from BGR to RGBA
    for(i = 0, j = 0; i < size; i += components, j += 4) {
        data[j] = buffer[i + 2];
        data[j + 1] = buffer[i + 1];
        data[j + 2] = buffer[i];
        if(components == 4) {
            data[j + 3] = buffer[i + 3];
        } else {
            data[j + 3] = 255;
        }
    }
    if(!(info[17] & 0x20)) {
        for(j = 0, k = w * 4; j < h / 2; j++) {
            for(i = 0; i < w * 4; i++) {
                l = data[j * k + i];
                data[j * k + i] = data[(h - j - 1) * k + i];
                data[(h - j - 1) * k + i] = l;
            }
        }
    }
    delete [] buffer;
    width = w;
    height = h;
    FG_LOG::PrintInfo("TGA LOAD: %s, %dx%d, data=%p;", fileStream->getPath(), w, h, data);
    return data;
}

/*
 *
 */
fgBool fgTextureLoader::saveTGA(const char *path, const unsigned char *data, const int width, const int height) {
    int i, j;
    unsigned char *buf;
    FILE *file = fopen(path, "wb");
    if(!file) {
        fprintf(stderr, "Texture::save_tga(): error create \"%s\" file\n", path);
        return 0;
    }
    buf = new unsigned char[18 + width * height * 4];
    memset(buf, 0, 18);
    buf[2] = 2;
    buf[12] = width % 256;
    buf[13] = width / 256;
    buf[14] = height % 256;
    buf[15] = height / 256;
    buf[16] = 32;
    buf[17] = 0x28;
    fgBool yolo1 = FG_FALSE;
    if(!yolo1) {
        memcpy(buf + 18, data, width * height * 4);
    } else {
        int k = 0;
        for(i = 0; i < width * height; i++, k += 4) {
            buf[k + 0 + 18] = data[i];
            buf[k + 1 + 18] = data[i];
            buf[k + 2 + 18] = data[i];
            buf[k + 3 + 18] = 255;
        }
    }
    for(i = 18; i < 18 + width * height * 4; i += 4) {
        j = buf[i];
        buf[i] = buf[i + 2];
        buf[i + 2] = j;
    }
    fwrite(buf, 1, 18 + width * height * 4, file);
    fclose(file);
    delete buf;
    return 1;
}