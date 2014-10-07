// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_courier_8_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_courier_8_usascii'.
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

#define STB_FONT_courier_8_usascii_BITMAP_WIDTH         128
#define STB_FONT_courier_8_usascii_BITMAP_HEIGHT         28
#define STB_FONT_courier_8_usascii_BITMAP_HEIGHT_POW2    32

#define STB_FONT_courier_8_usascii_FIRST_CHAR            32
#define STB_FONT_courier_8_usascii_NUM_CHARS             95

#define STB_FONT_courier_8_usascii_LINE_SPACING           4

static unsigned int stb__courier_8_usascii_pixels[]={
    0x4010408c,0x06022081,0x00003001,0x01886010,0x01880188,0x02662188,
    0x41840011,0x8314cc31,0x33506628,0x21830222,0xaa8e6622,0x20a33519,
    0x99884441,0x4d446262,0x4cc462a2,0x03046263,0x2a229a83,0x50c31833,
    0x05dc3062,0x71099833,0x28628615,0x2a310c26,0x233130c0,0x40630881,
    0x7714328a,0x0a6a2181,0x304c6013,0x8418a18a,0x10c10bb8,0x22860c13,
    0x26662998,0x82609860,0x11051989,0x26229946,0x26233312,0x41430c18,
    0x31831818,0x442214cc,0x42988661,0x0c666088,0x28818605,0x4418830a,
    0xa88aa19a,0x3102a629,0xa88604d4,0x20666639,0x00111832,0x00202201,
    0x0c4088a0,0x40418033,0x00200019,0x00000066,0x00000262,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x022000c0,0x09819831,0x40800003,0x11001009,0x80404330,0x94400880,
    0x33980043,0x4c413310,0x2a061843,0x1288a840,0x204cc133,0x21c2e180,
    0x4573329a,0x8826a609,0xa88cdc40,0x4c51351a,0xa982e208,0x23333029,
    0x82e06061,0x0826e09a,0x11aaa8c3,0x0c0d4333,0x261030c6,0x19882ae0,
    0x851826a2,0x28862661,0x94c1a818,0x41186309,0x19430301,0x266230c2,
    0x81853331,0x0cd40cc1,0x41530306,0x460d4308,0x80886630,0x35014c11,
    0x4426a233,0x884d4419,0x0866609a,0x3100026a,0x982e6217,0x9b873002,
    0x8998a530,0x4d441712,0x26251351,0x2994dc40,0x01ab8005,0x00260000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x01100000,0x04400022,0x02001022,0x00000002,0x40883306,0x81309818,
    0x80711539,0xb980c040,0x4d451510,0x2a653711,0x22337129,0x41353099,
    0x31c4542b,0x4a266513,0x2228871a,0x83062188,0x31029829,0x15106435,
    0x035302a6,0x26619a83,0x183506a0,0x15511863,0x06a660cc,0x26629853,
    0x04c0cc19,0x0a633506,0x26e0c8a6,0x221510e1,0x98301a83,0x4c333318,
    0x46304440,0x51110998,0x99986ae2,0x13154181,0x305d4433,0x40ba8301,
    0x00281309,0x29a88010,0x28a985cc,0x9a982e20,0x4c033712,0x98e1519a,
    0x331cc29a,0x5c1c2a71,0x5cc13530,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00188980,0x4c535100,0x10713508,0x10885d44,
    0x46662133,0x225308c0,0x00000999,0x00000000,0x23373184,0x0d5c1a9b,
    0x261bd853,0x86215409,0x26133139,0x098421aa,0x00000000,0xa8000000,
    0x3318c22a,0x314d4c18,0x41082983,0x0000619b,0x00000000,0x00000000,
    0x2a528998,0x00006e22,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__courier_8_usascii_x[95]={ 0,1,0,0,0,0,0,1,2,1,0,0,1,0,
1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0, };
static signed short stb__courier_8_usascii_y[95]={ 5,0,0,0,0,0,1,0,0,0,0,1,3,2,
4,0,0,0,0,0,0,0,0,0,0,0,2,2,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,1,0,1,0,1,0,1,0,0,
0,0,0,1,1,1,1,1,1,1,0,2,2,2,2,2,2,0,0,0,2, };
static unsigned short stb__courier_8_usascii_w[95]={ 0,2,4,4,4,4,4,2,2,2,3,4,2,4,
2,4,4,4,4,4,4,4,4,4,4,4,2,2,4,4,4,3,4,5,4,4,4,4,4,4,4,4,5,5,
4,5,4,4,4,4,5,4,4,4,5,5,4,4,4,2,3,2,4,5,2,4,4,4,5,4,4,4,4,4,
3,5,4,5,4,4,4,5,4,4,4,4,5,5,4,5,4,2,2,2,4, };
static unsigned short stb__courier_8_usascii_h[95]={ 0,6,3,6,6,6,5,3,6,6,4,4,4,2,
2,6,6,5,5,6,5,6,6,6,6,6,4,4,4,2,4,6,6,5,5,6,5,5,5,6,5,5,6,5,
5,5,5,6,5,6,5,6,5,6,5,5,5,5,5,6,6,6,3,1,2,5,6,5,6,5,5,6,5,5,
7,5,5,4,4,5,6,6,4,5,6,4,3,4,3,5,3,6,6,6,2, };
static unsigned short stb__courier_8_usascii_s[95]={ 126,23,27,26,31,36,90,48,49,67,122,
117,114,51,69,70,85,85,80,17,75,22,27,110,105,95,124,105,95,56,100,
63,75,47,42,80,32,27,22,90,12,7,11,118,113,69,102,14,92,6,81,
121,71,35,60,53,64,59,97,46,19,32,38,72,61,45,1,66,115,40,76,
100,87,50,1,1,55,11,6,37,58,52,17,17,41,1,32,108,22,107,43,
11,8,5,64, };
static unsigned short stb__courier_8_usascii_t[95]={ 1,1,22,1,1,1,16,22,1,1,16,
16,16,22,22,1,1,16,16,9,16,9,9,1,1,1,9,16,16,22,16,
1,1,16,16,1,16,16,16,1,16,16,9,9,9,16,9,1,9,9,9,
1,9,9,9,16,16,16,9,1,1,9,22,22,22,9,9,9,1,9,9,
1,9,9,1,16,9,22,22,16,1,1,22,16,1,22,22,16,22,9,22,
1,1,1,22, };
static unsigned short stb__courier_8_usascii_a[95]={ 68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_courier_8_usascii_BITMAP_HEIGHT or STB_FONT_courier_8_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_courier_8_usascii(stb_fontchar font[STB_FONT_courier_8_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_courier_8_usascii_BITMAP_HEIGHT][STB_FONT_courier_8_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__courier_8_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_courier_8_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_courier_8_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_courier_8_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_courier_8_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_courier_8_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__courier_8_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__courier_8_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__courier_8_usascii_s[i] + stb__courier_8_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__courier_8_usascii_t[i] + stb__courier_8_usascii_h[i]) * recip_height;
            font[i].x0 = stb__courier_8_usascii_x[i];
            font[i].y0 = stb__courier_8_usascii_y[i];
            font[i].x1 = stb__courier_8_usascii_x[i] + stb__courier_8_usascii_w[i];
            font[i].y1 = stb__courier_8_usascii_y[i] + stb__courier_8_usascii_h[i];
            font[i].advance_int = (stb__courier_8_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__courier_8_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__courier_8_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__courier_8_usascii_s[i] + stb__courier_8_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__courier_8_usascii_t[i] + stb__courier_8_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__courier_8_usascii_x[i] - 0.5f;
            font[i].y0f = stb__courier_8_usascii_y[i] - 0.5f;
            font[i].x1f = stb__courier_8_usascii_x[i] + stb__courier_8_usascii_w[i] + 0.5f;
            font[i].y1f = stb__courier_8_usascii_y[i] + stb__courier_8_usascii_h[i] + 0.5f;
            font[i].advance = stb__courier_8_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_courier_8_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_courier_8_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_courier_8_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_courier_8_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_courier_8_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_courier_8_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_courier_8_usascii_LINE_SPACING
#endif

