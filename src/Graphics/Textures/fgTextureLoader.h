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

// #FIXME - this texture loader should look a lot differently - neet to support various file formats: bmp, raw, jpg, png, tga

#include "png.h"
extern "C" {
#include "jpeglib.h"
}

/* load jpeg image
*/
struct my_error_mgr {
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr *my_error_ptr;

static void my_error_exit(j_common_ptr cinfo) {
	my_error_ptr myerr = (my_error_ptr)cinfo->err;
	(*cinfo->err->output_message)(cinfo);
	longjmp(myerr->setjmp_buffer,1);
}

unsigned char *load_jpeg(const char *name,int &width,int &height) {
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;
	FILE *file;
	JSAMPARRAY buffer;
	int row_stride;
	long cont;
	JSAMPLE *data_buffer;
	int i,j;
	unsigned char *data;
	file = fopen(name,"rb");
	if(!file) {
		fprintf(stderr,"Texture::load_jpeg(): error open \"%s\" file\n",name);
		return NULL;
	}
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	if(setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(file);
		return NULL;
	}
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo,file);
	jpeg_read_header(&cinfo,TRUE);
	jpeg_start_decompress(&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,JPOOL_IMAGE,row_stride,1);
	data_buffer = new JSAMPLE[cinfo.image_width * cinfo.image_height * cinfo.output_components];
	cont = 0;
	while(cinfo.output_scanline < cinfo.output_height) {
		jpeg_read_scanlines(&cinfo,buffer,1);
		memcpy(data_buffer + cinfo.image_width * cinfo.output_components * cont,buffer[0],row_stride);
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
			data[j] = data[j + 1] = data[j + 2] = data_buffer[i];
			data[j + 3] = 255;
		}
		break;
	case 3:
		for(i = 0, j = 0; i < width * height * 3; i += 3, j += 4) {
			data[j] = data_buffer[i];
			data[j + 1] = data_buffer[i + 1];
			data[j + 2] = data_buffer[i + 2];
			data[j + 3] = 255;
		}
		break;
	default:
		delete data;
		delete data_buffer;
		return NULL;
	}
	delete data_buffer;
	fclose(file);
	return data;
}

#endif