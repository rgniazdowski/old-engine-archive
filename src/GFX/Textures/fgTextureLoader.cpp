/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgTextureLoader.h"
#include "Util/fgPath.h"
#include "fgLog.h"
#include "Util/fgFile.h"
#include "Util/fgStrings.h"

//------------------------------------------------------------------------------

extern "C" {
#include "jerror.h"
}

typedef struct
{
    struct jpeg_source_mgr pub; /* public fields */
    FILE * infile; /* source stream */
    JOCTET * buffer; /* start of buffer */
    boolean start_of_file; /* have we gotten any data yet? */
} fg_jpeg_my_source_mgr;

typedef fg_jpeg_my_source_mgr * fg_jpeg_my_src_ptr;

#define INPUT_BUF_SIZE  4096    /* choose an efficiently fread'able size */
//------------------------------------------------------------------------------

/**
 *
 * @param cinfo
 */
static void fg_jpeg_init_source(j_decompress_ptr cinfo) {
    fg_jpeg_my_src_ptr src = (fg_jpeg_my_src_ptr)cinfo->src;

    /* We reset the empty-input-file flag for each image,
     * but we don't clear the input buffer.
     * This is correct behavior for reading a series of images from one source.
     */
    src->start_of_file = TRUE;
}
//------------------------------------------------------------------------------

/**
 *
 * @param cinfo
 * @return
 */
static boolean fg_jpeg_fill_input_buffer(j_decompress_ptr cinfo) {
    fg_jpeg_my_src_ptr src = (fg_jpeg_my_src_ptr)cinfo->src;
    size_t nbytes = 0;
    fg::util::base::CFile *file = NULL;
    //nbytes = JFREAD(src->infile, src->buffer, INPUT_BUF_SIZE);
    // This structure is used internally - the file pointer points
    // to object of base type: util::base::File - it can be ZipFile/RegularFile/DataFile/File

    if(src->infile) {
        file = (fg::util::base::CFile *) src->infile;
        // Some additional static check?
    }
    if(file) {
        nbytes = file->read(src->buffer, 1, INPUT_BUF_SIZE);
    }

    if(nbytes <= 0) {
        if(src->start_of_file) /* Treat empty input file as fatal error */
            ERREXIT(cinfo, JERR_INPUT_EMPTY);
        WARNMS(cinfo, JWRN_JPEG_EOF);
        /* Insert a fake EOI marker */
        src->buffer[0] = (JOCTET)0xFF;
        src->buffer[1] = (JOCTET)JPEG_EOI;
        nbytes = 2;
    }

    src->pub.next_input_byte = src->buffer;
    src->pub.bytes_in_buffer = nbytes;
    src->start_of_file = FALSE;

    return TRUE;
}
//------------------------------------------------------------------------------

static void fg_jpeg_skip_input_data(j_decompress_ptr cinfo, long num_bytes) {
    fg_jpeg_my_src_ptr src = (fg_jpeg_my_src_ptr)cinfo->src;
    fg::util::base::CFile *file = NULL;
    /* Just a dumb implementation for now.  Could use fseek() except
     * it doesn't work on pipes.  Not clear that being smart is worth
     * any trouble anyway --- large skips are infrequent.
     */
    if(src->infile) {
        file = (fg::util::base::CFile *) src->infile;
        // Some additional static check?
    }
    if(num_bytes > 0) {
        while(num_bytes > (long)src->pub.bytes_in_buffer) {
            num_bytes -= (long)src->pub.bytes_in_buffer;
            (void)fg_jpeg_fill_input_buffer(cinfo);
            /* note we assume that fill_input_buffer will never return FALSE,
             * so suspension need not be handled.
             */
        }
        src->pub.next_input_byte += (size_t)num_bytes;
        src->pub.bytes_in_buffer -= (size_t)num_bytes;
    }
}
//------------------------------------------------------------------------------

static boolean fg_jpeg_resync_to_restart(j_decompress_ptr cinfo, int desired) {
    return jpeg_resync_to_restart(cinfo, desired);
}
//------------------------------------------------------------------------------

static void fg_jpeg_term_source(j_decompress_ptr cinfo) {
    fg_jpeg_my_src_ptr src = (fg_jpeg_my_src_ptr)cinfo->src;
    fg::util::base::CFile *file = NULL;
    if(src->infile) {
        file = (fg::util::base::CFile *) src->infile;
        // Some additional static check?
    }
}
//------------------------------------------------------------------------------

static void fg_png_custom_read(png_structp png_ptr, png_bytep data, png_size_t length) {
    png_size_t lenread = 0;
    if(length <= 0 || !data) {
        FG_LOG_ERROR("PNG.custom_read: Error occured on read: data is NULL or given length <= 0");
        return;
    }

    if(png_get_io_ptr(png_ptr) == NULL) {
        FG_LOG_ERROR("PNG.custom_read: Error occured on read: io_ptr is NULL");
        return;
    }

    fg::util::base::CFile *file = (fg::util::base::CFile *)png_get_io_ptr(png_ptr);
    lenread = file->read((void *)data, 1, length);
    if(lenread < length) {
        FG_LOG_WARNING("PNG.custom_read: Warning, did not read all data from file: path[%s], %d < %d", file->getPath(), lenread, length);
    }
}
//------------------------------------------------------------------------------

/*
 * This function is used for preloading given file for later processing
 */
static unsigned char *universalPreLoad(const char *path,
                                       int &width,
                                       int &height,
                                       const char *extType) {
    if(!path) {
        // #TODO error handling / reporting
        FG_LOG_DEBUG("GFX: universalPreLoad: No path specified! [RARE]");
        return NULL;
    }
    fg::util::CFile *fileStream = new fg::util::CFile(path);
    if(fileStream->open(fg::util::CFile::Mode::READ | fg::util::CFile::Mode::BINARY)) {
        unsigned char *data = NULL;
        if(strncasecmp(extType, "jpeg", 4) == 0) {
            data = fg::gfx::texture::loadJPEG(fileStream, width, height);
        } else if(strncasecmp(extType, "png", 4) == 0) {
            data = fg::gfx::texture::loadPNG(fileStream, width, height);
        } else if(strncasecmp(extType, "tga", 4) == 0) {
            data = fg::gfx::texture::loadTGA(fileStream, width, height);
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
//------------------------------------------------------------------------------

using namespace fg;
//------------------------------------------------------------------------------

unsigned char *gfx::texture::loadJPEG(const char *path, int &width, int &height) {
    return universalPreLoad(path, width, height, "jpeg");
}
//------------------------------------------------------------------------------

unsigned char *gfx::texture::loadJPEG(fg::util::base::CFile *fileStream, int &width, int &height) {
    if(!fileStream) {
        // #TODO error handling / reporting
        return NULL;
    } else if(!fileStream->isOpen()) {
        if(!fileStream->open(fg::util::CFile::Mode::READ | fg::util::CFile::Mode::BINARY)) {
            // #TODO error handling / reporting
            return NULL;
        }
    }
    unsigned char *data = NULL;
    int i = 0, j = 0, rowStride = -1;
    long cont = 0;
    struct jpeg_decompress_struct cinfo;
    struct SJPEGErrorMgr jpegError;
    JSAMPARRAY buffer;
    JSAMPLE *dataBuffer = NULL;

    cinfo.err = jpeg_std_error(&jpegError.pub);
    jpegError.pub.error_exit = FuncJPEGErrorExit;
    if(setjmp(jpegError.setjmp_buffer)) {
        // #TODO error handling / reporting
        FG_LOG_ERROR("JPEG LOAD: Error occurred while loading JPEG file: '%s'", fileStream->getPath());
        jpeg_destroy_decompress(&cinfo);
        return NULL;
    }
    jpeg_create_decompress(&cinfo);
    /*jpeg_stdio_src(&cinfo, fileStream->getFilePtr()); */
    jpeg_stdio_src(&cinfo, (FILE *)fileStream);
    cinfo.src->init_source = &fg_jpeg_init_source;
    cinfo.src->fill_input_buffer = &fg_jpeg_fill_input_buffer;
    cinfo.src->skip_input_data = &fg_jpeg_skip_input_data;
    cinfo.src->resync_to_restart = &fg_jpeg_resync_to_restart;
    cinfo.src->term_source = &fg_jpeg_term_source;
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
                //data[j + 3] = 255;
                data[j + 3] = FG_TEXTURE_ALPHA_FIX_VALUE(data[j], data[j], data[j]);
            }
            break;
        case 3:
            for(i = 0, j = 0; i < width * height * 3; i += 3, j += 4) {
                data[j] = dataBuffer[i];
                data[j + 1] = dataBuffer[i + 1];
                data[j + 2] = dataBuffer[i + 2];
                data[j + 3] = FG_TEXTURE_ALPHA_FIX_VALUE(data[j], data[j + 1], data[j + 2]);
            }
            break;
        default:
            // #TODO error handling / reporting
            delete [] data;
            delete [] dataBuffer;
            FG_LOG_ERROR("JPEG LOAD: Invalid number of components[%d]: '%s'", cinfo.output_components, fileStream->getPath());
            return NULL;
    }
    delete [] dataBuffer;
    FG_LOG_DEBUG("JPEG LOAD: path[%s], size[%dx%d], data[%p];", fileStream->getPath(), width, height, data);
    FG_LOG_DEBUG("JPEG LOAD: texture file[%s] converted to RGBA - alpha fixed as RGB average", fg::path::fileName(fileStream->getPath()));
    return data;
}
//------------------------------------------------------------------------------

unsigned char *gfx::texture::loadPNG(const char *path, int &width, int &height) {
    return universalPreLoad(path, width, height, "png");
}
//------------------------------------------------------------------------------

unsigned char *gfx::texture::loadPNG(fg::util::base::CFile *fileStream, int &width, int &height) {
    if(!fileStream) {
        // #TODO error handling / reporting
        FG_LOG_ERROR("PNG LOAD: FileStream specified is NULL!");
        return NULL;
    } else if(!fileStream->isOpen()) {
        if(!fileStream->open(fg::util::CFile::Mode::READ | fg::util::CFile::Mode::BINARY)) {
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
    //png_init_io(png_ptr, fileStream->getFilePtr());
    png_set_read_fn(png_ptr, (void *)fileStream, &fg_png_custom_read);
    //png_set_write_fn()
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
                    data[k + 3] = FG_TEXTURE_ALPHA_FIX_VALUE(data[k + 0], data[k + 1], data[k + 2]);
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
    FG_LOG_DEBUG("PNG LOAD: path[%s], size=[%dx%d], data=[%p], comp[%d];", fileStream->getPath(), w, h, data, (int)channels);
    if((int)channels != 4)
        FG_LOG_DEBUG("PNG LOAD: texture file[%s] converted to RGBA - alpha fixed as RGB average", fg::path::fileName(fileStream->getPath()));
    return data;
}
//------------------------------------------------------------------------------

unsigned char *gfx::texture::loadTGA(const char *path, int &width, int &height) {
    return universalPreLoad(path, width, height, "tga");
}
//------------------------------------------------------------------------------

unsigned char *gfx::texture::loadTGA(fg::util::base::CFile *fileStream, int &width, int &height) {
    if(!fileStream) {
        FG_LOG_ERROR("TGA LOAD: FileStream specified is NULL!");
        return NULL;
    } else if(!fileStream->isOpen()) {
        if(!fileStream->open(fg::util::CRegularFile::Mode::READ | fg::util::CRegularFile::Mode::BINARY)) {
            FG_LOG_ERROR("TGA LOAD: failed to open texture file: '%s'", fileStream->getPath());
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
        FG_LOG_ERROR("TGA LOAD: failed to allocate new data while loading texture file: '%s'", fileStream->getPath());
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
            data[j + 3] = FG_TEXTURE_ALPHA_FIX_VALUE(data[j], data[j + 1], data[j + 2]);
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
    FG_LOG_DEBUG("TGA LOAD: path[%s], size[%dx%d], data[%p], comp[%d];", fileStream->getPath(), w, h, data, components);
    if(components != 4)
        FG_LOG_DEBUG("TGA LOAD: texture file[%s] converted to RGBA - alpha fixed as RGB average", fg::path::fileName(fileStream->getPath()));
    return data;
}
//------------------------------------------------------------------------------

fgBool gfx::texture::saveTGA(const char *path, const unsigned char *data, const int width, const int height) {
    int i, j;
    unsigned char *buf;
    FILE *file = fopen(path, "wb");
    if(!file) {
        FG_LOG_ERROR("Texture::save_tga(): error create \"%s\" file\n", path);
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
//------------------------------------------------------------------------------
