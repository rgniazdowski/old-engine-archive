/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef FG_INC_TEXTURE_TYPES_HEADER
    #define FG_INC_TEXTURE_TYPES_HEADER

    #ifndef FG_TEXTURE_ALPHA_FIX_VALUE
        #define FG_TEXTURE_ALPHA_FIX_VALUE(_R, _G, _B) \
            ((_G < 16 && _R < 16 && _B < 16) ? 0 : (_R + _G + _B) / 3)

        #define FG_TEXTURE_ALPHA_FIX_VALUE_LIMIT(_R, _G, _B, _LIMIT) \
            ((_G < _LIMIT && _R < _LIMIT && _B < _LIMIT) ? 0 : (_R + _G + _B) / 3)
    #endif

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

namespace fg {
    namespace gfx {
        namespace texture {

            enum CubeMapID {
                CUBE_MAP_POSITIVE_X_ID = 0,
                CUBE_MAP_NEGATIVE_X_ID = 1,
                CUBE_MAP_POSITIVE_Y_ID = 2,
                CUBE_MAP_NEGATIVE_Y_ID = 3,
                CUBE_MAP_POSITIVE_Z_ID = 4,
                CUBE_MAP_NEGATIVE_Z_ID = 5,
                NUM_CUBE_MAPS = 6
            }; // enum CubeMapID

            // Texture file type enumeration. Supported file formats (current & future):
            // bmp, raw, jpg, png, tga

            enum FileType {
                FILE_INVALID = 0,

                FILE_BMP,
                FILE_RAW,
                FILE_JPEG,
                FILE_PNG,
                FILE_TGA,
                FILE_DDS,
                FILE_OTHER,

                FG_NUM_TEXTURE_FILE_TYPES
            }; // enum FileType

            /**
             * Texture type enumeration, defines the type of the texture and
             * possible usage because of this,
             */
            enum Type {
                INVALID = -1,
                PLAIN = 0,
                T_2D = PLAIN,
                DIFFUSE = PLAIN,
                AMBIENT = 1,
                SPECULAR = 2,
                NORMAL = 3,
                BUMP = 4,
                ENVIRONMENT = 5,
                CUBE = 6,
                T_3D = 7,
                RAW = 8,
                FONT = 9,

                NUM_TEXTURE_TYPES = 10
            }; // enum Type

            /**
             * Texture unit slot number
             */
            enum UnitSlot {
                UNIT_DEFAULT = 0,
                UNIT_DIFFUSE = 0,
                UNIT_AMBIENT = 1,
                UNIT_SPECULAR = 2,
                UNIT_NORMAL = 3,
                UNIT_BUMP = 4,
                UNIT_ENVIRONMENT = 5,
                UNIT_CUBE = 6,
                UNIT_3D = 7,
                UNIT_FONT = 0 // ?
            }; // enum UnitSlot

            /**
             * Texture internal pixel format
             */
            enum InternalPixelFormat {
                INTERNAL_PIXEL_INVALID = 0,

    #if defined(FG_USING_OPENGL_ES)
                INTERNAL_PIXEL_ALPHA,
                INTERNAL_PIXEL_RGB,
                INTERNAL_PIXEL_RGBA,
                INTERNAL_PIXEL_LUMINANCE,
                INTERNAL_PIXEL_LUMINANCE_ALPHA,
    #elif defined(FG_USING_OPENGL)
                INTERNAL_PIXEL_DEPTH_COMPONENT,
                INTERNAL_PIXEL_DEPTH_STENCIL,
                INTERNAL_PIXEL_RED,
                INTERNAL_PIXEL_RG,
                INTERNAL_PIXEL_RGB,
                INTERNAL_PIXEL_RGBA,
    #endif

                FG_NUM_TEXTURE_INTERNAL_PIXEL_FORMATS
            }; // enum InternalPixelFormat

            /**
             * Texture pixel format (data storage)
             */
            enum PixelFormat {
                PIXEL_INVALID = 0,

    #if defined(FG_USING_OPENGL_ES)
                PIXEL_ALPHA,
                PIXEL_RGB,
                PIXEL_RGBA,
                PIXEL_LUMINANCE,
                PIXEL_LUMINANCE_ALPHA,
    #elif defined(FG_USING_OPENGL)
                PIXEL_DEPTH_COMPONENT,
                PIXEL_DEPTH_STENCIL,
                PIXEL_RED,
                PIXEL_RG,
                PIXEL_RGB,
                PIXEL_RGBA,
                PIXEL_BGR,
                PIXEL_BGRA,
                PIXEL_RED_INTEGER,
                PIXEL_RG_INTEGER,
                PIXEL_RGB_INTEGER,
                PIXEL_BGR_INTEGER,
                PIXEL_RGBA_INTEGER,
                PIXEL_BGRA_INTEGER,
                PIXEL_STENCIL_INDEX,
    #endif

                NUM_PIXEL_FORMATS
            }; // enum PixelFormat

        } // namespace texture
    } // namespace gfx
} // namespace fg

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
// The format of the texel data must match internal format.
//
// PIXEL DATA TYPE:
// Data type of the texel data. The following symbolic values are accepted:
// GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, 
// GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1
//
// ///////////////////////////////////////////////////////////////////////

    #define FG_TEXTURE_COMP_INVALID     0
    #define FG_TEXTURE_COMP_GRAYSCALE   1
    #define FG_TEXTURE_COMP_GRAYSCALE_ALPHA 2
    #define FG_TEXTURE_COMP_RGB         3
    #define FG_TEXTURE_COMP_RGBA        4

//#define FG_TEXTURE_DEFAULT_PIXEL_FORMAT FG_TEXTURE_PIXEL_RGBA

#endif /* FG_INC_TEXTURE_TYPES_HEADER */
