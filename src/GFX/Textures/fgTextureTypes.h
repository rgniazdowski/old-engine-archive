/*******************************************************
* Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
* 
* This file is part of #FLEXIGAME_PROJECT
* 
* #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
* and/or distributed without the express or written permission from the author.
*******************************************************/

#ifndef _FG_TEXTURE_TYPES_H_
#define _FG_TEXTURE_TYPES_H_


// Extension (held as string) for BMP file format
#define FG_TEXTURE_FILE_EXTENSION_BMP	"bmp"
// Extension (held as string) for RAW file format
#define FG_TEXTURE_FILE_EXTENSION_RAW	"raw"
// Extension (held as string) for JPEG file format
#define FG_TEXTURE_FILE_EXTENSION_JPEG	"jpg"
// Extension (held as string) for PNG file format
#define FG_TEXTURE_FILE_EXTENSION_PNG	"png"
// Extension (held as string) for TGA file format
#define FG_TEXTURE_FILE_EXTENSION_TGA	"tga"

// Texture file type enumeration. Supported file formats (current & future):
// bmp, raw, jpg, png, tga
enum fgTextureFileType {
	FG_TEXTURE_FILE_BMP,
	FG_TEXTURE_FILE_RAW,
	FG_TEXTURE_FILE_JPEG,
	FG_TEXTURE_FILE_PNG,
	FG_TEXTURE_FILE_TGA,
	FG_TEXTURE_FILE_OTHER,
	
	FG_TEXTURE_FILE_INVALID,
	FG_NUM_TEXTURE_FILE_TYPES
};

// Texture type enumeration, defines the type of the texture and
// possible usage because of this
enum fgTextureType {
	FG_TEXTURE_PLAIN,
	FG_TEXTURE_BUMP,
	FG_TEXTURE_NORMAL,
	FG_TEXTURE_RAW,
	FG_TEXTURE_FONT,

	FG_TEXTURE_INVALID,
	FG_NUM_TEXTURE_TYPES
};

// Texture internal pixel format
enum fgTextureInternalPixelFormat {
#if defined(FG_USING_OPENGL_ES)
	FG_TEXTURE_INTERNAL_PIXEL_ALPHA,
	FG_TEXTURE_INTERNAL_PIXEL_RGB,
	FG_TEXTURE_INTERNAL_PIXEL_RGBA,
	FG_TEXTURE_INTERNAL_PIXEL_LUMINANCE,
	FG_TEXTURE_INTERNAL_PIXEL_LUMINANCE_ALPHA,
#elif defined(FG_USING_OPENGL)
	FG_TEXTURE_INTERNAL_PIXEL_DEPTH_COMPONENT,
	FG_TEXTURE_INTERNAL_PIXEL_DEPTH_STENCIL,
	FG_TEXTURE_INTERNAL_PIXEL_RED,
	FG_TEXTURE_INTERNAL_PIXEL_RG,
	FG_TEXTURE_INTERNAL_PIXEL_RGB,
	FG_TEXTURE_INTERNAL_PIXEL_RGBA,
#endif

	FG_TEXTURE_INTERNAL_PIXEL_INVALID,
	FG_NUM_TEXTURE_INTERNAL_PIXEL_FORMATS
};

// Texture pixel format (data storage)
enum fgTexturePixelFormat {
#if defined(FG_USING_OPENGL_ES)
	FG_TEXTURE_PIXEL_ALPHA,
	FG_TEXTURE_PIXEL_RGB,
	FG_TEXTURE_PIXEL_RGBA,
	FG_TEXTURE_PIXEL_LUMINANCE,
	FG_TEXTURE_PIXEL_LUMINANCE_ALPHA,
#elif defined(FG_USING_OPENGL)
	FG_TEXTURE_PIXEL_DEPTH_COMPONENT,
	FG_TEXTURE_PIXEL_DEPTH_STENCIL,
	FG_TEXTURE_PIXEL_RED,
	FG_TEXTURE_PIXEL_RG,
	FG_TEXTURE_PIXEL_RGB,
	FG_TEXTURE_PIXEL_RGBA,
	FG_TEXTURE_PIXEL_BGR,
	FG_TEXTURE_PIXEL_BGRA,
	FG_TEXTURE_PIXEL_RED_INTEGER,
	FG_TEXTURE_PIXEL_RG_INTEGER,
	FG_TEXTURE_PIXEL_RGB_INTEGER,
	FG_TEXTURE_PIXEL_BGR_INTEGER, 
	FG_TEXTURE_PIXEL_RGBA_INTEGER, 
	FG_TEXTURE_PIXEL_BGRA_INTEGER,
	FG_TEXTURE_PIXEL_STENCIL_INDEX,
#endif

	FG_TEXTURE_PIXEL_INVALID,
	FG_NUM_TEXTURE_PIXEL_FORMATS
};

// ///////////////////////////////////////////////////////////////////////
// OPENGL 4.X - PIXEL DATA FORMATS:
//
// INTERNAL FORMAT:
// GL_DEPTH_COMPONENT, 
// GL_DEPTH_STENCIL,
// GL_RED,
// GL_RG,
// GL_RGB,
// GL_RGBA
//
// PIXEL FORMAT (DATA):
// The format of the pixel(texel) data. The following symbolic values are accepted:
// GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, 
// GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER,
// GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
// 
// ///////////////////////////////////////////////////////////////////////
// Pixel format determines the composition of each element in data. It can assume one of these symbolic values: 
//
// GL_RED
//		Each element is a single red component. The GL converts it to floating point and assembles it into an RGBA element by attaching 0 for green and blue,
//		and 1 for alpha. Each component is clamped to the range [0,1].
// GL_RG
//		Each element is a red/green double. The GL converts it to floating point and assembles it into an RGBA element by attaching 0 for blue, and 1 for alpha.
//		Each component is clamped to the range [0,1].
// GL_RGB, GL_BGR
//		Each element is an RGB triple. The GL converts it to floating point and assembles it into an RGBA element by attaching 1 for alpha. Each component is clamped to the range [0,1].
// GL_RGBA, GL_BGRA
//		Each element contains all four components. Each component is clamped to the range [0,1].
// GL_DEPTH_COMPONENT
//		Each element is a single depth value. The GL converts it to floating point and clamps to the range [0,1].
// GL_DEPTH_STENCIL
//		Each element is a pair of depth and stencil values. The depth component of the pair is interpreted as in GL_DEPTH_COMPONENT. 
//		The stencil component is interpreted based on specified the depth + stencil internal format. 
//
// ///////////////////////////////////////////////////////////////////////
//
// PIXEL DATA TYPE:
// The following symbolic values are accepted: GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, 
// GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV,
// GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4,
// GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, 
// GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, 
// GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2,
// and GL_UNSIGNED_INT_2_10_10_10_REV. 
//
// ///////////////////////////////////////////////////////////////////////
// OPENGL ES 2.X - PIXEL DATA FORMATS:
// 
// INTERNAL FORMAT:
// Must be one of the following symbolic constants:
// GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA.
//
// PIXEL FORMAT (DATA):
// The format of the texel data must match internalformat.
//
// PIXEL DATA TYPE:
// Data type of the texel data. The following symbolic values are accepted:
// GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, 
// GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1
//
// ///////////////////////////////////////////////////////////////////////

#define FG_TEXTURE_COMP_INVALID			0
#define FG_TEXTURE_COMP_GRAYSCALE		1
#define FG_TEXTURE_COMP_GRAYSCALE_ALPHA 2
#define FG_TEXTURE_COMP_RGB				3
#define FG_TEXTURE_COMP_RGBA			4

#define FG_TEXTURE_DEFAULT_PIXEL_FORMAT FG_TEXTURE_PIXEL_RGBA

#endif /* _FG_TEXTURE_TYPES_H_ */