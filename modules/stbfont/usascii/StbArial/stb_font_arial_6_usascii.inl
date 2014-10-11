// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_6_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_6_usascii'.
//
/* // Example usage:

static stb_fontchar fontdata[STB_SOMEFONT_NUM_CHARS];

static void init(void)
{
    // optionally replace both STB_SOMEFONT_BITMAP_HEIGHT with STB_SOMEFONT_BITMAP_HEIGHT_POW2
    static unsigned char fontpixels[STB_SOMEFONT_BITMAP_HEIGHT][STB_SOMEFONT_BITMAP_WIDTH];
    STB_SOMEFONT_CREATE(fontdata, fontpixels, STB_SOMEFONT_BITMAP_HEIGHT);
    ... create texture ...
    // for best results rendering 1:1 pixels texels, use nearest-neighbor sampling
    // if allowed to scale up, use bilerp
}

// This function positions characters on integer coordinates, and assumes 1:1 texels to pixels
// Appropriate if nearest-neighbor sampling is used
static void draw_string_integer(int x, int y, char *str) // draw with top-left point x,y
{
    ... use texture ...
    ... turn on alpha blending and gamma-correct alpha blending ...
    glBegin(GL_QUADS);
    while (*str) {
        int char_codepoint = *str++;
        stb_fontchar *cd = &fontdata[char_codepoint - STB_SOMEFONT_FIRST_CHAR];
        glTexCoord2f(cd->s0, cd->t0); glVertex2i(x + cd->x0, y + cd->y0);
        glTexCoord2f(cd->s1, cd->t0); glVertex2i(x + cd->x1, y + cd->y0);
        glTexCoord2f(cd->s1, cd->t1); glVertex2i(x + cd->x1, y + cd->y1);
        glTexCoord2f(cd->s0, cd->t1); glVertex2i(x + cd->x0, y + cd->y1);
        // if bilerping, in D3D9 you'll need a half-pixel offset here for 1:1 to behave correct
        x += cd->advance_int;
    }
    glEnd();
}

// This function positions characters on float coordinates, and doesn't require 1:1 texels to pixels
// Appropriate if bilinear filtering is used
static void draw_string_float(float x, float y, char *str) // draw with top-left point x,y
{
    ... use texture ...
    ... turn on alpha blending and gamma-correct alpha blending ...
    glBegin(GL_QUADS);
    while (*str) {
        int char_codepoint = *str++;
        stb_fontchar *cd = &fontdata[char_codepoint - STB_SOMEFONT_FIRST_CHAR];
        glTexCoord2f(cd->s0f, cd->t0f); glVertex2f(x + cd->x0f, y + cd->y0f);
        glTexCoord2f(cd->s1f, cd->t0f); glVertex2f(x + cd->x1f, y + cd->y0f);
        glTexCoord2f(cd->s1f, cd->t1f); glVertex2f(x + cd->x1f, y + cd->y1f);
        glTexCoord2f(cd->s0f, cd->t1f); glVertex2f(x + cd->x0f, y + cd->y1f);
        // if bilerping, in D3D9 you'll need a half-pixel offset here for 1:1 to behave correct
        x += cd->advance;
    }
    glEnd();
}
*/

#ifndef STB_FONTCHAR__TYPEDEF
#define STB_FONTCHAR__TYPEDEF
typedef struct
{
    // coordinates if using integer positioning
    float s0,t0,s1,t1;
    signed short x0,y0,x1,y1;
    int   advance_int;
    // coordinates if using floating positioning
    float s0f,t0f,s1f,t1f;
    float x0f,y0f,x1f,y1f;
    float advance;
} stb_fontchar;
#endif

#define STB_FONT_arial_6_usascii_BITMAP_WIDTH         128
#define STB_FONT_arial_6_usascii_BITMAP_HEIGHT         20
#define STB_FONT_arial_6_usascii_BITMAP_HEIGHT_POW2    32

#define STB_FONT_arial_6_usascii_FIRST_CHAR            32
#define STB_FONT_arial_6_usascii_NUM_CHARS             95

#define STB_FONT_arial_6_usascii_LINE_SPACING           4

static unsigned int stb__arial_6_usascii_pixels[]={
    0x17289470,0x0d55418c,0x94a18c17,0x25531ba8,0x32a851aa,0x531a9865,
    0x54c2ee23,0x2a637711,0x2ee23732,0x0a3b9941,0x2628a373,0x4ca131ba,
    0x26514130,0x228e2ba9,0x38e1550c,0x5c539ce7,0x9885554b,0x508e5552,
    0x4e708e15,0xa99c70ab,0x8d641553,0x71328e73,0x4c729445,0x2e7538e0,
    0x588a38e1,0x3275538e,0x11de432a,0x9b9c4155,0x4e738473,0x9c27554a,
    0x71139d23,0x4e739ce1,0x099d4528,0x44e098a5,0x1c395552,0x114c2a17,
    0x30738377,0x235150aa,0x265552aa,0x225531bb,0x2a5553bb,0x2a79732a,
    0x2e17753a,0x2e65532a,0x1caee50b,0x2705c665,0x4755710a,0x0000510b,
    0x00000000,0x00400200,0x04100000,0x00080008,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x88000000,0x1a98cc1b,
    0x8c6a6555,0x9ca50a8a,0x32a35318,0x85ddc6a3,0xa985ddc2,0x48dca171,
    0x5d42e50a,0xb94a2850,0x5c2eee3b,0x5cb730bb,0x1981913b,0x439d4ce7,
    0x4a738b22,0x6438aae2,0x2ae53171,0x739c6a71,0x72c55ca7,0x42ea1bb8,
    0x2553709b,0x0cdc1373,0x4dc531c7,0x31989573,0x554eae75,0x75716472,
    0x22aa8ea2,0x9c937143,0x95543773,0x75572a8b,0xaa8aae1c,0x94cdc771,
    0x0cdc3373,0x4dc389c7,0x771caa8b,0x9c006aa1,0x06e00a8b,0x9c4e2870,
    0x54e00e73,0x5dc59172,0x4dc06a72,0x70739471,0x42eee177,0x02eee3bd,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0xb8000000,0x1a98cce0,0x43015250,0x51a98e02,0x54905477,
    0x95ca5299,0xa8e23aba,0xa865551b,0x21998319,0x5caa72b9,0xa8314113,
    0x2708ee23,0x737171b9,0x711c154c,0x854708e1,0x554910b8,0x38e1552b,
    0x382aa157,0x812c41ce,0x8cae6088,0x0aa63319,0x3838b750,0x2b9ccaa2,
    0x4c70c6ea,0x8e0b851c,0xcb98e2bc,0x2e71c910,0x8d642109,0x019b8673,
    0x06a00000,0x4507144e,0x23019480,0x790c10e0,0x1c330a23,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__arial_6_usascii_x[95]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,
-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
static signed short stb__arial_6_usascii_y[95]={ 4,0,0,0,-1,0,0,0,0,0,0,0,3,2,
3,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,0,1,0,1,0,1,0,0,
0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,1, };
static unsigned short stb__arial_6_usascii_w[95]={ 0,2,2,3,3,5,4,1,2,2,2,3,2,2,
2,2,3,3,3,3,3,3,3,3,3,3,2,2,3,3,3,3,6,5,4,4,4,4,4,4,4,2,3,4,
3,5,4,4,4,4,4,4,4,4,4,6,4,4,4,2,2,2,3,5,2,3,3,3,3,3,2,3,3,1,
2,3,1,5,3,3,3,3,2,3,2,3,3,4,3,3,3,2,1,2,3, };
static unsigned short stb__arial_6_usascii_h[95]={ 0,4,2,5,6,5,5,2,6,6,2,4,2,1,
1,5,5,4,4,5,4,5,5,4,5,5,3,4,4,2,4,4,6,4,4,5,4,4,4,5,4,4,5,4,
4,4,4,5,4,5,4,5,4,5,4,4,4,4,4,6,5,6,3,2,1,4,5,4,5,4,4,5,4,4,
6,4,4,3,3,4,5,5,3,4,5,4,3,3,3,5,3,6,6,6,2, };
static unsigned short stb__arial_6_usascii_s[95]={ 35,41,115,58,1,62,1,110,32,19,112,
37,97,122,125,125,116,56,44,68,52,94,81,48,72,10,90,31,27,106,16,
12,22,1,123,76,113,108,103,85,96,34,6,83,79,73,68,42,59,98,50,
107,42,120,33,20,24,7,118,29,55,13,78,100,122,14,112,18,103,38,47,
90,55,22,16,92,101,72,86,64,51,47,69,88,35,29,65,60,93,38,82,
10,8,5,118, };
static unsigned short stb__arial_6_usascii_t[95]={ 7,14,14,1,1,1,8,14,1,1,14,
14,14,16,14,1,1,14,14,1,14,1,1,14,1,8,14,14,14,14,14,
14,1,14,8,1,8,8,8,1,8,14,8,8,8,8,8,1,8,1,8,
1,8,1,8,14,8,14,8,1,1,1,14,14,14,8,1,8,1,8,8,
1,8,8,1,8,8,14,14,8,1,1,14,8,1,8,14,14,14,1,14,
1,1,1,14, };
static unsigned short stb__arial_6_usascii_a[95]={ 24,24,31,48,48,76,57,16,
29,29,33,50,24,29,24,24,48,48,48,48,48,48,48,48,
48,48,24,24,50,50,50,48,87,57,57,62,62,57,52,67,
62,24,43,57,48,72,62,67,57,67,62,57,52,62,57,81,
57,57,52,24,24,24,40,48,29,48,48,43,48,48,24,48,
48,19,19,43,19,72,48,48,48,48,29,43,24,48,43,62,
43,43,43,29,22,29,50, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_6_usascii_BITMAP_HEIGHT or STB_FONT_arial_6_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_6_usascii(stb_fontchar font[STB_FONT_arial_6_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_6_usascii_BITMAP_HEIGHT][STB_FONT_arial_6_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_6_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_6_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_6_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_6_usascii_BITMAP_WIDTH-1; ++i) {
                unsigned int value;
                if (numbits==0) bitpack = *bits++, numbits=32;
                value = bitpack & 1;
                bitpack >>= 1, --numbits;
                if (value) {
                    if (numbits < 3) bitpack = *bits++, numbits = 32;
                    data[j][i] = (bitpack & 7) * 0x20 + 0x1f;
                    bitpack >>= 3, numbits -= 3;
                } else {
                    data[j][i] = 0;
                }
            }
        }
    }

    // build font description
    if (font != 0) {
        float recip_width = 1.0f / STB_FONT_arial_6_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_6_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_6_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_6_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_6_usascii_s[i] + stb__arial_6_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_6_usascii_t[i] + stb__arial_6_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_6_usascii_x[i];
            font[i].y0 = stb__arial_6_usascii_y[i];
            font[i].x1 = stb__arial_6_usascii_x[i] + stb__arial_6_usascii_w[i];
            font[i].y1 = stb__arial_6_usascii_y[i] + stb__arial_6_usascii_h[i];
            font[i].advance_int = (stb__arial_6_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_6_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_6_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_6_usascii_s[i] + stb__arial_6_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_6_usascii_t[i] + stb__arial_6_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_6_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_6_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_6_usascii_x[i] + stb__arial_6_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_6_usascii_y[i] + stb__arial_6_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_6_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_6_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_6_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_6_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_6_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_6_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_6_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_6_usascii_LINE_SPACING
#endif

