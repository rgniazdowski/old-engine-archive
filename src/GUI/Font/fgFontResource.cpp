/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFontResource.h"

#include "fgLog.h"
#include "Util/fgPath.h"
#include "GFX/Textures/fgTextureManager.h"
#include "Hardware/fgHardwareState.h"

/*
 * Base constructor of the font resource object
 */
fgFontResource::fgFontResource() :
fgTextureResource(),
m_fontType(FG_FONT_TYPE_TEXTURE),
m_info(),
m_step(0) {
    m_resType = FG_RESOURCE_FONT;
    FG_LOG::PrintDebug("fgFontResource::fgFontResource()");
}

/*
 * Constructor with additional parameter (path)
 */
fgFontResource::fgFontResource(const char *path) :
fgTextureResource(path),
m_fontType(FG_FONT_TYPE_TEXTURE),
m_info(),
m_step(0) {
    m_resType = FG_RESOURCE_FONT;
    FG_LOG::PrintDebug("fgFontResource::fgFontResource()");
}

/*
 * Constructor with additional parameter (path)
 */
fgFontResource::fgFontResource(std::string& path) :
fgTextureResource(path),
m_fontType(FG_FONT_TYPE_TEXTURE),
m_info(),
m_step(0) {
    m_resType = FG_RESOURCE_FONT;
    FG_LOG::PrintDebug("fgFontResource::fgFontResource()");
}

/*
 * Clears the class data, this actually does not free allocated memory, 
 * just resets base class attributes
 */
void fgFontResource::clear(void) {
    FG_LOG::PrintDebug("fgFontResource::clear();");
    fgTextureResource::clear();
    m_step = 0;
    m_resType = FG_RESOURCE_FONT;
    m_fontType = FG_FONT_TYPE_TEXTURE;
}

/*
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 */
fgBool fgFontResource::create(void) {
    FG_LOG::PrintDebug("fgFontResource::create();");
    m_textureType = FG_TEXTURE_FONT;
    if(!fgTextureResource::create()) {
        // #TODO error handling / reporting
        FG_LOG::PrintError("%s(%d): texture create function has failed - in function %s.", fgPath::fileName(__FILE__), __LINE__ - 1, __FUNCTION__);
        return FG_FALSE;
    }
    if(m_step)
        return FG_TRUE;
    m_step = m_width / 16;
    int i = 0, j = 0, k = 0;
    int x = 0, y = 0;
    float s, t, ds, dt;
    float space0 = 0.0f, space1 = 0.0f;
    unsigned char *ptr = NULL;
    dt = 1.0f / 16.0f;
    FG_LOG::PrintDebug("FONT CREATE 'Tex::ID=%s'; size=%dx%d; step=%d;", this->m_nameTag.c_str(), m_width, m_width, m_step);
    if(!m_info.charInfo) {
        m_info.charInfo = fgMalloc<fgFontCharInfo>(FG_FONT_STANDARD_ASCII_SIZE);
    }
    m_info.numChars = FG_FONT_STANDARD_ASCII_SIZE;
    for(y = 0, i = 0; y < 16; y++) {
        for(x = 0; x < 16; x++, i++) {
            space0 = 0.0f;
            space1 = 0.0f;
            for(j = 0; j < m_step; j++) {
                ptr = m_rawData + (m_width * y * m_step + x * m_step + j)*4;
                for(k = 0; k < m_step; k++) {
                    if(*(ptr + 3) != 0) break;
                    ptr += m_width * 4;
                }
                if(k != m_step)
                    break;
                space0 += 1.0f;
            }

            s = (float)x / 16.0f + (float)space0 / (float)m_width;
            t = (float)y / 16.0f;
            if(int(space0) == m_step)
                continue;
            for(j = m_step - 1; j >= 0; j--) {
                ptr = m_rawData + (m_width * y * m_step + x * m_step + j)*4;
                for(k = 0; k < m_step; k++) {
                    if(*(ptr + 3) != 0)
                        break;
                    ptr += m_width * 4;
                }
                if(k != m_step) break;
                space1 += 1.0f;
            }
            space1 = float(m_step) - space0 - space1;
            ds = space1 / (float)m_width;
            m_info.charInfo[i].p1f.x = space1;
            m_info.charInfo[i].p1f.y = (float)m_step;
            m_info.charInfo[i].uv1f.x = s;
            m_info.charInfo[i].uv1f.y = 1.0f - t;
            m_info.charInfo[i].uv2f.x = s + ds;
            m_info.charInfo[i].uv2f.y = 1.0f - (t + dt);
            m_info.charInfo[i].stepf = space1;

            m_info.charInfo[i].uv1i = m_info.charInfo[i].uv1f;
            m_info.charInfo[i].uv2i = m_info.charInfo[i].uv2f;
        }
    }
    return FG_TRUE;
}

/*
 * Destroy all loaded data including additional metadata (called with deconstructor)
 */
void fgFontResource::destroy(void) {
    fgTextureResource::destroy();
    m_info.destroy();
}

/*
 * Reloads any data, recreates the resource (refresh)
 */
fgBool fgFontResource::recreate(void) {
    FG_LOG::PrintDebug("fgFontResource::recreate();");
    fgFontResource::dispose();
    return fgFontResource::create();
}

/*
 * Dispose completely of the all loaded data, free all memory
 */
void fgFontResource::dispose(void) {
    FG_LOG::PrintDebug("fgFontResource::~dispose();");
    fgTextureResource::dispose();
    m_step = 0;
    m_info.destroy();
}

/*
 * Check if resource is disposed (not loaded yet or disposed after)
 */
fgBool fgFontResource::isDisposed(void) const {
    return fgTextureResource::isDisposed();
}

#if 0

/*
 *
 */
void fgFontResource::setFontArea(Area *area) {
    m_fontArea.x = area->x;
    m_fontArea.y = area->y;
    m_fontArea.w = area->w;
    m_fontArea.h = area->h;
    m_isFontAreaDefault = false;
}

/*
 *
 */
void fgFontResource::setFontAreaDefault(void) {
    m_fontArea.x = 0;
    m_fontArea.y = 0;
    m_fontArea.w = FG_HardwareState->screenWidth();
    m_fontArea.h = FG_HardwareState->screenHeight();
    m_isFontAreaDefault = true;
}
#endif
#if 0

/*
 *
 */
bool fgFontResource::load(Tex::ID FONT_ID) {
 }

/**
 * Ustawia na ekranie pojedynczy znak o prawidlowym rozmiarze i teksturze
 * @param font		Czcionka do uzycia
 * @param char_size	Rozmiar jednego znaku (wysokosc)
 * @param letter	Znak do wypisania
 */
float fgFontResource::placeChar(float x0, float y0, float char_size, char letter, void *inmat) {
    int x, y, i, size;
    float s, t, ds, dt;
    float scale;
    size = m_texture->width();
    i = (int)letter;

    scale = char_size / (float)m_step;

    y = i / 16;
    x = i % 16;
    s = (float)x / 16.0f + (float)m_space[i][0] / (float)size;
    t = (float)y / 16.0f;
    ds = (float)m_space[i][1] / (float)size;
    dt = 1.0f / 16.0f;
    float size_x = m_space[i][1] * scale;
    float size_y = char_size;
    float italic_offset = char_size / 4.0f;
    //fgVec2f(0.0f,1.0f), fgVec2f(1.0f,0.0f),

    fgVec2f(s, t), fgVec2f(s + dt, t + dt),


            // Set this as the active material
            /*   IwGxSetMaterial( inmat );

               CIwSVec2* xy3 = IW_GX_ALLOC( CIwSVec2, 4 );
               xy3[0].x = x0, xy3[0].y = y0;
               xy3[1].x = x0, xy3[1].y = y0+size_y;
               xy3[2].x = x0+size_x, xy3[2].y = y0+size_y;
               xy3[3].x = x0+size_x, xy3[3].y = y0;
                   IwGxSetScreenSpaceOrg(&CIwSVec2::g_Zero);
               IwGxSetVertStreamScreenSpace(xy3, 4);

                   CIwFVec2* uvs = IW_GX_ALLOC( CIwFVec2, 4 );
                   uvs[0] = CIwFVec2(s, t);
                   uvs[1] = CIwFVec2(s, t+dt);
               uvs[2] = CIwFVec2(s+ds, t+dt);
               uvs[3] = CIwFVec2(s+ds, t);
                   IwGxSetUVStream(uvs);

                   IwGxSetColStream(NULL);

                   IwGxDrawPrims(IW_GX_QUAD_LIST, NULL, 4);*/
            //IwGxFlush();
    return m_space[i][1] * scale;
}

/**
 * OpenGL print text at given (x,y)
 *
 * @param font
 * @param x
 * @param y
 * @param size
 * @param string
 * @return
 */
int fgFontResource::print(float x, float y, float size, const char *string, ...) {
    int n;
    char *s;
    char buf[BUFFF_SIZE];
    float scale;
    va_list args;

    va_start(args, string);
    vsnprintf(buf, BUFFF_SIZE - 1, string, args);
    va_end(args);
    // Index is zero based -> BUFFF_SIZE-1 points to last byte in buffer
    buf[BUFFF_SIZE - 1] = '\0';

    float pos_x, pos_y;
    pos_x = x;
    pos_y = y;

    scale = size / (float)m_step;

    //glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);

    // Rozmiar buffora to 1024 wiec zakladamy ze jest 512 linii maksymalnie (mozna smialo zmniejszyc)
    // Zmienne sa statyczne
    static unsigned short lines[BUFFF_SIZE / 3]; // Wspolrzedne konca danej linii
    static float line_space_size[BUFFF_SIZE / 3];
    int n_spaces = 0;
    int n_lines = 1;
    int current_line = 0;
    int last_space = 0;
    float last_size = 0.0f;
    float line_width = 0.0f;

    if(m_isFontAreaDefault == false) {
        memset(lines, 0, sizeof (lines));
        memset(line_space_size, 0, sizeof (line_space_size));
        int i = 0;
        for(s = buf; *s; s++, i++) {
            if(*s == '\t') {
                line_width += size * 2.0f;
            } else if(*s == ' ') {
                last_space = i;
                last_size = line_width;
                n_spaces++;
                line_width += size / 3.0f;
            } else if(*s != '\n') {
                line_width += (float)m_space[*(unsigned char*)s][1] * scale;
            } else if(*s == '\n') {
                lines[current_line] = i - 1;
                line_space_size[current_line] = size / 3.0f;
                n_lines++;
                n_spaces = 0;
                current_line++;
                line_width = 0.0f;
            }
            line_width += 1.0f;
            if(*(s + 1) == 0 || n_lines == BUFFF_SIZE / 2 - 1) {
                lines[current_line] = i;
                line_space_size[current_line] = size / 3.0f;
                n_lines++;
                break;
            }
            if(line_width >= (float)m_fontArea.w) {
                lines[current_line] = last_space - 1;
                line_space_size[current_line] = size / 3.0f + float(m_fontArea.w - last_size) / ((float)n_spaces - 1);
                n_lines++;
                n_spaces = 0;
                current_line++;
                line_width = 0.0f;
                s = buf + last_space;
                i = last_space;
            }
        }
    } else {
        lines[0] = strlen(buf);
        n_lines = 1;
        line_space_size[0] = size / 3.0f;
    }

    // FIXME

    /*// Use Texture on Material
    CIwMaterial* mat = IW_GX_ALLOC_MATERIAL();
    mat->SetColEmissive( m_color );
    mat->SetColAmbient( m_color );
    mat->SetTexture( m_texture->texture() );
    mat->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
     */
    current_line = 0;
    int i = 0;
    for(s = buf, n = 0; *s; s++, i++) {
        if(*s == '\n' || i > lines[current_line]) {
            n++;
            pos_x = x;
            pos_y = y + size * n;
            if(i > lines[current_line]) {
                current_line++;
            }
        } else if(*s == ' ') {
            pos_x += line_space_size[current_line];
        } else {
            pos_x += placeChar(pos_x, pos_y, size, (char)*s, NULL);
        }
        pos_x += 1.0f;
    }
    //glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    return current_line + 1;
}

/**
 * OpenGL print text on center (in X, y is still given)
 *
 * @param font
 * @param y
 * @param size
 * @param string
 * @return
 */
int fgFontResource::printCenter(float y, float size, const char *string, ...) {
    char buf[BUFFF_SIZE];
    int n = 0;
    char *token;
    va_list args;

    va_start(args, string);
    vsnprintf(buf, BUFFF_SIZE - 1, string, args);
    va_end(args);
    // Index is zero based -> BUFFF_SIZE-1 points to last byte in buffer
    buf[BUFFF_SIZE - 1] = '\0';

    token = strtok(buf, "\n");
    while(token != NULL) {
        print(FG_HardwareState->screenWidth() / 2 - width(size, token) / 2, y + size*n, size, token);
        token = strtok(NULL, "\n");
        n++;
    }
    return n;
}

/**
 *
 * @param font
 * @param y
 * @param size
 * @param fmt
 * @return
 */
int fgFontResource::printLeft(float y, float size, const char *string, ...) {
    char buf[BUFFF_SIZE];
    int n = 0;
    va_list args;

    va_start(args, string);
    vsnprintf(buf, BUFFF_SIZE - 1, string, args);
    va_end(args);
    // Index is zero based -> BUFFF_SIZE-1 points to last byte in buffer
    buf[BUFFF_SIZE - 1] = '\0';
    n = print(0, y, size, buf);
    return n;
}

/**
 * OpenGL print right-justified
 *
 * @param font
 * @param y
 * @param size
 * @param fmt
 * @return
 */
int fgFontResource::printRight(float y, float size, const char *string, ...) {
    char buf[BUFFF_SIZE];
    int n = 0;
    char *token;
    va_list args;

    va_start(args, string);
    vsnprintf(buf, BUFFF_SIZE - 1, string, args);
    va_end(args);
    // Index is zero based -> BUFFF_SIZE-1 points to last byte in buffer
    buf[BUFFF_SIZE - 1] = '\0';

    token = strtok(buf, "\n");
    while(token != NULL) {
        print(FG_HardwareState->screenWidth() - width(size, token), y + size*n, size, token);
        token = strtok(NULL, "\n");
        n++;
    }

    return n;
}

/**
 * Returns height of given text
 * @param font
 * @param size
 * @param fmt
 * @return
 */
float fgFontResource::height(float size, const char *string, ...) {
    char buf[BUFFF_SIZE];
    int i;
    float y = size;
    va_list args;
    float scale = size / (float)m_step;

    va_start(args, string);
    vsnprintf(buf, BUFFF_SIZE - 1, string, args);
    va_end(args);
    // Index is zero based -> BUFFF_SIZE-1 points to last byte in buffer
    buf[BUFFF_SIZE - 1] = '\0';

    int slen = strlen(buf);
    for(i = 0; i < slen; i++) {
        if(buf[i] == '\n')
            y += m_step;
    }
    y = y*scale;
    return y;
}
#endif