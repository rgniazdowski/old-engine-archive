/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgTextureResource.h"

#include <iostream>
#include "s3eFile.h"
#include "../../fgFileStream.h"
#include "../../fgMemory.h"

#include "../../fgCommon.h"

// FIXME - this class is screwed beyond recognition xD FUBAR

/**

 * Check for glGetError() and conditionally returns false
 * (but only for DEBUG builds)
 */
/*
bool fgTexture::checkGlError(const char* fname) {
    GLenum code;

    code = glGetError();
    if(GL_NO_ERROR != code) {
        FG_ErrorLog("%s() failed! Code=%d, TexId=%d",fname, code, m_texId);

#ifdef IW_DEBUG
        return false;
#endif

    }
    return true;
}
*/
//
// MARK: -
// MARK: Initializers & destroyers
//

/**
 * Constructor
 */
fgTexture::fgTexture() : m_mode(NOTYPE), m_width(0), m_height(0), m_comp(0), m_texId(0),
                                m_ucdata(NULL), m_img(NULL)
{
}

/**
 * Destructor
 */
fgTexture::~fgTexture() {
    releaseAll();
}

//
// MARK: -
// MARK: Business – initialize & destroy
//

/**
 * Loads texture using CIwImage. The image remains
 * in RAM until removed via releaseNonGl()
 */
bool fgTexture::loadFromFile(const char* file)
{
    if( m_mode != NOTYPE && !m_allowDoubleInit ) {
        FG_ErrorLog("Double initialization of fgTexture! %d/%d", m_mode, TEXTURE);
        return false;
    }
    m_allowDoubleInit = false;
    m_mode = TEXTURE;
    m_filename = file;

	if(m_img == NULL)
		m_img = new CIwImage();

	CIwImage loadImg;
	// Load image from file
	loadImg.LoadFromFile(file);
	// Convert to an OpenGL ES native format
	// result is stored in m_img structure
	m_img->SetFormat(CIwImage::ABGR_8888);
	loadImg.ConvertToImage(m_img);

	// Prepare data used by makeTexture, and call it!
	m_width = m_img->GetWidth();
    m_height = m_img->GetHeight();
    m_comp = 4; // CIwImage::ABGR_8888
    m_ucdata = (unsigned char*) m_img->GetTexels();

	FG_WriteLog("'%s': Width: %d, height: %d, m_ucdata: %p", file, m_width, m_height, m_ucdata);
    return true;
}


/*
 * Loads TGA image "by hand", with custom, non-Marmalade code.
 */
bool fgTexture::prepareTgaFromFile(const char* filename)
{
    if( m_mode != NOTYPE && !m_allowDoubleInit ) {
        FG_ErrorLog("Double initialization of fgTexture! %d/%d", m_mode, UCDATA);
        return false;
    }
    m_allowDoubleInit = false;
    m_mode = UCDATA;
    m_filename = filename;

	int i=0,j=0,k=0,l=0,w=0,h=0,components=0,size=0;
	unsigned char rep=0;
	unsigned char *data = NULL;
	unsigned char *buf = NULL;
	unsigned char *ptr = NULL;
	unsigned char info[18];
    s3eFile *file = NULL;

    // Reset the destination of the whole operation
    m_ucdata = NULL;

    // We use fseek() and dbg_pos - debug
    // position (fseek has its own position var)
    int dbg_pos = 0;

	m_width = -1;
	m_height = -1;
	m_comp = -1;

    memset(&info, 0, sizeof(info));

    // EXISTS
    if(!s3eFileCheckExists(filename)) {
        FG_ErrorLog("TGA file '%s' not found!", filename);
		return false;
    }

    // OPEN
    file = s3eFileOpen(filename, "rb");
	if(file == NULL) {
		FG_ErrorLog("Cannot open (existing) '%s' TGA file", filename);
		return false;
	}

    // SIZE
	int file_size = s3eFileGetSize(file);
    if(file_size < 10) {
        FG_ErrorLog("Very small TGA file size of %s: %d", filename, file_size);
        return false;
    }

    // FILE OP [1]
    s3eFileRead(&info,1,18,file);
	dbg_pos+=18;

	w=info[12] + info[13] * 256;
	h=info[14] + info[15] * 256;

	switch(info[16])
	{
		case 32:
			components=4;
			break;
		case 24:
			components=3;
			break;
		default:
            // FILE OP [2]
            s3eFileClose(file);
			return NULL;
	}
	size  = w * h * components;
    FG_WriteLog("Calculated size: %d, file system size + 18: %d", size, file_size + 18);

	// HEAP_USE +(malloc TGA buf)
	buf = (unsigned char *)fgMalloc(size);
	// HEAP_USE +(malloc TGA data)
	data = (unsigned char *)fgMalloc(w * h * 4);

	if(!data || !buf)
	{
		if(buf != NULL) {
			// HEAP_RELEASE +(!free TGA buf)
			fgFree(buf);
		}
		if(data != NULL) {
			// HEAP_RELEASE +(!free TGA data)
			fgFree(data);
		}
		// HEAP_RELEASE +(!free TGA info)
		return NULL;
	}
	/*
	 * int fseek ( FILE * stream, long int offset, int origin );
	 *
	 * stream		Pointer to a FILE object that identifies the stream.
	 * offset		Number of bytes to offset from origin.
	 * origin		Position from where offset is added. It is specified by one of the following constants defined in <cstdio>:
	 * 	SEEK_SET	Beginning of file
	 *	SEEK_CUR	Current position of the file pointer
	 *	SEEK_END	End of file
	 */

    // FILE OP [3]
	s3eFileSeek(file, info[0], S3E_FILESEEK_CUR);
   	dbg_pos+=info[0];

	switch(info[2])
	{
		case 2:
            // FILE OP [3]
            s3eFileRead(buf,1,size,file);
			dbg_pos+=size;
			break;

		case 10:
			i = 0;
			ptr = buf;
			while(i < size)
			{
                // FILE OP [4]
				s3eFileRead(&rep, 1, 1, file);
				dbg_pos++;
				if(rep & 0x80)
				{
					rep ^= 0x80;
                    // FILE OP [5]
					s3eFileRead(ptr,1,components,file);

					dbg_pos += components;
					ptr += components;

					for(j=0; j < rep * components; j++)
					{
						*ptr = *(ptr - components);
						ptr++;
					}
					i += components*(rep+1);
				}
				else
				{
					k=components *(rep+1);
                    // FILE OP [6]
					s3eFileRead(ptr,1,k,file);
					dbg_pos += k;
					ptr += k;
					i += k;
				}
			}
			break;
		default:
			// HEAP_RELEASE +(!free TGA buf)
			free(buf);
			// HEAP_RELEASE +(!free TGA data)
			free(data);
			return false;
	}
	for(i=0, j=0; i < size; i += components, j += 4)
	{
		data[j]=buf[i + 2];
		data[j + 1]=buf[i + 1];
		data[j + 2]=buf[i];
		if(components==4)
			data[j + 3]=buf[i + 3];
		else
			data[j + 3]=255;
	}
	if(!(info[17] & 0x20))
	{
		for(j=0, k=w * 4; j < h / 2; j ++)
		{
			for(i=0; i < w * 4; i ++)
			{
				l = data[j * k + i];
				data[j * k + i] = data[(h - j - 1) * k + i];
				data[(h - j - 1) * k + i] = l;
			}
		}
	}
	// HEAP_RELEASE +(free TGA buf)
	fgFree(buf);

	m_width = w;
	m_height = h;
	m_comp = components;
    m_ucdata = data;

    return true;
}

/**
 * Releases non-GPU side of resources – should be
 * used to free data after uploading int oVRAM
 */
void fgTexture::releaseNonGl(void) {
    if ( NOTYPE == m_mode ) {
        FG_ErrorLog("clearTexture(): INCONSISTENCY - called on already empty fgTexture! %d/%d", m_mode, UCDATA);
        return;
    }

    // FONT
    if( UCDATA == m_mode )
    {
        if( m_ucdata ) {
            free(m_ucdata);
            m_ucdata = NULL;
        }
    }
	
    // IMAGE
    if( TEXTURE == m_mode )
    {
        if( m_img )
        {
            delete m_img;
            m_img = NULL;
            m_ucdata = NULL;
        }
    }

    if( m_ucdata || m_img ) {
        FG_ErrorLog("Inconsistent data! [mode=%d] Non-NULL value in m_ucdata[%p] or m_img[%p]", m_mode, m_ucdata, m_img, m_texId);
    }
}

/**
 * Releases OpenGL structures (i.e. the texture id)
 */
void fgTexture::releaseGl(void) {
    // GL DATA
    if( m_texId != 0 )
    {
        glDeleteTextures(1, &m_texId);
        m_texId = 0;
    }
    if( m_texId ) {
        FG_ErrorLog("Inconsistent data! [mode=%d] Non-NULL value in m_ucdata[%p] or m_img[%p] or m_texId[%d]", m_mode, m_ucdata, m_img, m_texId);
    }
}

/**
 * Makes object fully EMPTY – structures in RAM
 * and in VRAM / OpenGL – all will get released,
 * and object's m_mode will be set to NOTYPE.
 */
void fgTexture::releaseAll(void) {
    releaseNonGl();
    releaseGl();

	m_width = 0;
	m_height = 0;
    m_comp = 0;
	m_mode = NOTYPE;    
}

//
// MARK: -
// MARK: Business
//

/**
 * Uploads image to VRAM as a texture
 *
 * TODO: mozliwa jest optymalizacja: gdy wymiary tekstury
 * uploadowanej drugi raz sa takie same, mozna uzyc
 * glTexSubImage2D zamiast glTexImage2D
 */
bool fgTexture::makeTexture() {
    if( ! m_ucdata ) {
        FG_ErrorLog("makeTexture() called when m_ucdata is NULL");
        return false;
    }

    glEnable(GL_TEXTURE_2D);

    // Generate texture object ONLY IF NEEDED
    if( !m_texId ) {
        glGenTextures(1, &m_texId);
       // if(!checkGlError("glGenTextures")) {
       //     return false;
       // }
    }

    glBindTexture(GL_TEXTURE_2D, m_texId);
    //if(!checkGlError("glBindTexture")) {
    //    return false;
    //}

    // Disable mipmapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //if(!checkGlError("[various GL]")) {
    //    return false;
    //}

    // Upload
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ucdata);
    //if(!checkGlError("glTexImage2D")) {
    //    return false;
    //}

    return true;
}