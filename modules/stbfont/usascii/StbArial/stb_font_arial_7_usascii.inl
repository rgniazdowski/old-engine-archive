// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_7_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_7_usascii'.
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

#define STB_FONT_arial_7_usascii_BITMAP_WIDTH         128
#define STB_FONT_arial_7_usascii_BITMAP_HEIGHT         28
#define STB_FONT_arial_7_usascii_BITMAP_HEIGHT_POW2    32

#define STB_FONT_arial_7_usascii_FIRST_CHAR            32
#define STB_FONT_arial_7_usascii_NUM_CHARS             95

#define STB_FONT_arial_7_usascii_LINE_SPACING           5

static unsigned int stb__arial_7_usascii_pixels[]={
    0x46383146,0x837502a1,0x44082119,0x8260cc1b,0x88aa2098,0x5404a22c,
    0x86a05cc0,0x30260d41,0x8183b837,0x88a33189,0x21894462,0x38e2a89b,
    0x37398e47,0x2cdc3326,0x704d4937,0x2144dc33,0x51ca648b,0x45151491,
    0x85caa59b,0x20e6388b,0x3314a23c,0x4546271c,0xa98e2bab,0x4ce1c322,
    0x538e70ba,0x2d98eee1,0xc98226e6,0x8a498124,0x491ce3bb,0x2e179138,
    0x2a43c859,0x718a4712,0x21c53315,0x530b8e0d,0x2dcc36f2,0x10a84977,
    0x23ba8173,0x4218e173,0x854e310b,0x94c2e5b9,0x211d2911,0x98a311ac,
    0x2a3148e1,0x88e1bcc9,0x49791543,0x20e3818a,0x3132a3ba,0x11d54751,
    0x21dd4779,0x24d49532,0x3261d991,0x5dcb752b,0x71146a72,0x5c351aa4,
    0x042e3a8a,0x01040000,0x000000c0,0x08026000,0x02184000,0x81304223,
    0x00044098,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x86180000,0x81a83501,0x81506e61,0x20304c09,0x388618c1,
    0x26063775,0x5dcc61bb,0x43098210,0x50c0ca19,0x8e30ddcc,0x48b822e3,
    0x529941dc,0x49a8e2e1,0x54338e6e,0x6491ce39,0x208b86a1,0x91171923,
    0xb8e971ce,0x64e0e953,0xa9b8dc40,0x524ac8e3,0x0985b10a,0x645c2629,
    0x209cb750,0x42ef21ab,0x0dc51533,0x9724dc15,0x3aab9c77,0x23a9b8e7,
    0x2e0e773b,0x2e22982c,0x0a9c90ab,0x1e45c2e7,0x89d445c5,0x21b570ba,
    0x9832e3b9,0x143b8e4b,0x99c7382a,0x7504dce2,0x22e4b9c9,0x917073aa,
    0x2eea1c41,0x8eae3bc8,0x932ea3b9,0xba8e5e42,0x80938003,0x0a850ea3,
    0x386471ce,0x4e68e007,0x2177738d,0x15e6c913,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x40000000,
    0xbb983061,0x2e657731,0x3184c60b,0x22831057,0x86186a21,0x82155309,
    0x10606a09,0x085406a1,0x42333042,0x99822210,0x2e49a8e3,0x8b822e08,
    0x739dce48,0x4c3b8711,0x711ca29a,0x48885435,0x38a85422,0x4c3911d4,
    0x8441750c,0x5cea22ba,0x493719c9,0x4e5bcbbb,0x2e17970a,0xa85c71bc,
    0x97719bb8,0x2640ab83,0x1512a244,0x240a80d4,0x73188733,0xe805dc45,
    0x3bba9220,0x5471c1ce,0x8e0e0e4b,0x38ea6e23,0x4c3cca92,0x20cc8281,
    0x2613120a,0x0dbd8320,0x4c200462,0x9dec9170,0x41ce49d8,0x970700e3,
    0xb0ef2e77,0x23bbb962,0x85033124,0x8705490b,0x05e64260,0x0000310e,
    0x00000000,0x00000000,0x00000000,0x00000000,0x40840000,0x88444c41,
    0x28302221,0x218d6546,0x54222209,0x00000133,0x00000000,0x31ce0000,
    0x2766e17b,0x8554c593,0x21c3264a,0x4ccc0841,0x00000000,0x00000000,
    0x2154c000,0x8739ce0b,0x9c110bba,0x00000002,0x00000000,0x00000000,
    0x39ce0434,0x00000007,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__arial_7_usascii_x[95]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,
-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
static signed short stb__arial_7_usascii_y[95]={ 5,0,0,0,0,0,0,0,0,0,0,1,4,3,
4,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,1,0,1,0,1,0,1,0,0,
0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,2, };
static unsigned short stb__arial_7_usascii_w[95]={ 0,2,2,4,4,6,5,1,2,2,3,4,2,2,
2,2,4,3,4,4,4,4,4,4,4,4,2,2,4,4,4,4,7,6,4,5,5,4,4,5,5,2,3,5,
4,5,5,5,4,5,5,4,4,5,5,6,5,5,4,2,2,2,3,5,2,4,4,4,4,4,2,4,4,1,
2,4,1,5,4,4,4,4,3,3,2,4,4,5,4,4,3,2,2,2,4, };
static unsigned short stb__arial_7_usascii_h[95]={ 0,5,3,6,6,6,6,3,7,7,3,4,2,1,
1,6,6,5,5,6,5,6,6,5,6,6,4,5,4,3,4,5,7,5,5,6,5,5,5,6,5,5,6,5,
5,5,5,6,5,6,5,6,5,6,5,5,5,5,5,7,6,7,3,2,2,5,6,5,6,5,5,6,5,5,
7,5,5,4,4,5,6,6,4,5,6,5,4,4,4,6,4,7,7,7,2, };
static unsigned short stb__arial_7_usascii_s[95]={ 33,75,125,47,67,72,17,34,1,16,26,
6,44,53,56,23,12,88,78,90,83,62,98,67,79,32,102,72,97,21,92,
53,22,40,35,84,22,17,12,26,1,64,124,113,108,102,96,41,86,108,78,
114,68,1,59,28,58,47,119,30,95,19,30,47,41,37,7,42,119,52,65,
103,73,84,13,47,57,11,120,7,57,52,17,124,38,91,1,114,105,33,110,
10,7,4,36, };
static unsigned short stb__arial_7_usascii_t[95]={ 8,16,16,1,1,1,9,22,1,1,22,
22,22,22,22,9,9,16,16,1,16,1,1,16,1,9,16,16,16,22,16,
16,1,16,16,1,16,16,16,9,16,16,1,9,9,9,9,1,9,1,9,
1,9,9,9,16,16,16,9,1,1,1,22,22,22,9,9,9,1,9,9,
1,9,9,1,9,9,22,16,16,1,1,22,9,1,9,22,16,16,1,16,
1,1,1,22, };
static unsigned short stb__arial_7_usascii_a[95]={ 28,28,36,56,56,89,67,19,
33,33,39,59,28,33,28,28,56,56,56,56,56,56,56,56,
56,56,28,28,59,59,59,56,102,67,67,72,72,67,61,78,
72,28,50,67,56,84,72,78,67,78,72,67,61,72,67,95,
67,67,61,28,28,28,47,56,33,56,56,50,56,56,28,56,
56,22,22,50,22,84,56,56,56,56,33,50,28,56,50,72,
50,50,50,33,26,33,59, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_7_usascii_BITMAP_HEIGHT or STB_FONT_arial_7_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_7_usascii(stb_fontchar font[STB_FONT_arial_7_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_7_usascii_BITMAP_HEIGHT][STB_FONT_arial_7_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_7_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_7_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_7_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_7_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_arial_7_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_7_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_7_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_7_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_7_usascii_s[i] + stb__arial_7_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_7_usascii_t[i] + stb__arial_7_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_7_usascii_x[i];
            font[i].y0 = stb__arial_7_usascii_y[i];
            font[i].x1 = stb__arial_7_usascii_x[i] + stb__arial_7_usascii_w[i];
            font[i].y1 = stb__arial_7_usascii_y[i] + stb__arial_7_usascii_h[i];
            font[i].advance_int = (stb__arial_7_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_7_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_7_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_7_usascii_s[i] + stb__arial_7_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_7_usascii_t[i] + stb__arial_7_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_7_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_7_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_7_usascii_x[i] + stb__arial_7_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_7_usascii_y[i] + stb__arial_7_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_7_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_7_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_7_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_7_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_7_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_7_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_7_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_7_usascii_LINE_SPACING
#endif
