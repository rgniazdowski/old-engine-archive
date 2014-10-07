// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_10_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_10_usascii'.
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

#define STB_FONT_arial_10_usascii_BITMAP_WIDTH         128
#define STB_FONT_arial_10_usascii_BITMAP_HEIGHT         40
#define STB_FONT_arial_10_usascii_BITMAP_HEIGHT_POW2    64

#define STB_FONT_arial_10_usascii_FIRST_CHAR            32
#define STB_FONT_arial_10_usascii_NUM_CHARS             95

#define STB_FONT_arial_10_usascii_LINE_SPACING           6

static unsigned int stb__arial_10_usascii_pixels[]={
    0x88620a8c,0x2ae20222,0x32a85440,0x40035101,0x04462622,0x36a0aaa8,
    0x51050d41,0x15102a03,0x102a2188,0xb10b8157,0x0cc3b1c4,0xa8b266f6,
    0x321cd10b,0x40e64b9c,0x1546a6a5,0x7930aae8,0x1c52a61b,0x27606ce4,
    0x41b5b10d,0x44b5b11a,0x96246aad,0x64331638,0x50caaca8,0x2c46e585,
    0xac076472,0x9754eceb,0x2ae05cc7,0x8245cd43,0x444cc4ac,0x248aa370,
    0x99263939,0x8e258730,0x3ab99545,0xb0aa737b,0x9d42a9cc,0x24a4b039,
    0x2f6a595a,0xb88bb20d,0x83f5038b,0x2750dcdb,0x8bdb123c,0x30aa1ceb,
    0x2a0e4e29,0x2721b352,0x26585519,0x732b8754,0x96d6d560,0x8750932a,
    0xcc8c82cb,0x21bd1950,0x5edc552b,0x2c9dc533,0xc8931d98,0x55122710,
    0x24b4366a,0x22752c2a,0x8e61d10e,0x7575588b,0x1a954ea1,0x0aae6e55,
    0x2e555373,0x2a94cd72,0x705c6e33,0x551d4aa3,0xb1c4b1a2,0x9b3912a8,
    0x9615439d,0x87b7a61d,0x23db31e8,0x336a1a9a,0xe8933624,0x199240dd,
    0xc8ef7762,0x4933625c,0x37226644,0x44b0ec5d,0x1e457163,0x96154762,
    0x08400006,0x02070000,0x02000001,0x2b944000,0x1933a8a2,0x20cdcd98,
    0x066b71da,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x2e600000,0x18857301,0x2201510c,0x30282a20,0x23cb9835,
    0x65c55008,0x446b2e1a,0x882a2aaa,0x228c4331,0x94142628,0x9cc81108,
    0x2d4de44c,0xad8ac493,0x3b12b80d,0x64de424b,0x2a9656a2,0x36750d88,
    0x54476752,0x1c92a6ba,0x864361d1,0x30e4366b,0x95154227,0x0a8931d8,
    0x73bac493,0x08966dc5,0x44986e1b,0xba9ccaa2,0x8647b23c,0x206e192a,
    0x224cec1d,0x6caa2cc9,0x1924cb1b,0x85715466,0x84cc573a,0xa8e56249,
    0xbd0b6753,0x540571c4,0x8e52a553,0xa964aa38,0x882c8392,0x488bb05d,
    0x25891739,0x77154aa5,0x2a2752c8,0xbac4932c,0x15c32751,0x21d49164,
    0x2a9736a0,0xcc88e255,0x43d9912d,0x220ae04a,0xd956c0dd,0x51555c1a,
    0x53588aa5,0x2b83a21d,0x739a54b1,0x1a964ae3,0x44b12455,0x54aa0aa5,
    0x1c84c712,0xb80b31a8,0x64598d81,0xb910990c,0xea8552a8,0x37660ded,
    0x3776e0ce,0xcd893720,0xa899b12d,0x983776a1,0x22552a81,0x540f3223,
    0x81bbbbb1,0x47715c1b,0x26416a59,0x0c0154aa,0x00000000,0x00000004,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x55400000,
    0x10110aaa,0xaa883555,0x8c188c0a,0x81894428,0x55446618,0x4155510a,
    0x51188c18,0x55544555,0x0155510a,0x02603011,0x556d4c71,0x55b30550,
    0x6d56cc79,0x583e6911,0x39ae43f3,0x261b3398,0x75932daa,0xac561ccb,
    0x3662aad9,0x55b30aaa,0x320f443d,0x90109b04,0x2638aa81,0x2a399623,
    0x59726913,0x39ae4793,0x880d9b98,0x730d8e65,0x40e6b158,0x2c473039,
    0x425cc379,0x0c800cb9,0x9d306d54,0x5d6cc3b9,0x2ee6910e,0x4d56e6b3,
    0x5db30735,0xdde98360,0x57bbba64,0x4599d348,0x0e64cce9,0x91911a8d,
    0x90073190,0x64c5ea81,0x0d6cc3b8,0x59d9cd22,0x4d691773,0x40e8d983,
    0x6445cc58,0x4d258731,0x4464c08c,0x1a8d0e60,0xcf81b559,0x0321226c,
    0x91cc5755,0x34881cc5,0x45cd7627,0x260e6b4c,0x4c2a8b33,0x961ccae3,
    0x40e60731,0x23512a39,0x2ea1ebba,0x320a1c88,0x730d9540,0x10398744,
    0x735b8e69,0xdde9ac7a,0x391dc733,0x265dde98,0x07348ac3,0x4cb777a6,
    0x81a84dde,0x009106c4,0x00000000,0x00000000,0x00000000,0x38000000,
    0x440b982a,0x8073220a,0x21edc010,0x3165c2ca,0x22ca8663,0xa99c471a,
    0x9c3332e4,0x1c181338,0x98f26615,0x731c9aca,0x32caa577,0x2b621b3b,
    0x2a0e370d,0x4c17b32d,0x8dce6392,0x54aa174a,0x6c472731,0x80ca842b,
    0x25ae324a,0xb52cae2c,0xb2da5472,0x6c426662,0x99542648,0x8b762550,
    0x27b302d9,0x9b71dcb8,0x4aa07259,0xa8e6191a,0x1660aa06,0x4cb17955,
    0x91912beb,0x2552a954,0x2eee6b0c,0x16207362,0x3444c362,0xcc883991,
    0x954ae591,0x542a5518,0x1d46a372,0x10aa059b,0x8b67360b,0x33609d98,
    0x2a954aa1,0x4ccc5619,0x206c1aa0,0x133661d8,0x20654ee2,0x3322dcd9,
    0xe893320d,0x1b9911cb,0x54886cae,0x20ccdd85,0x50901f2d,0x2a552a8d,
    0x26016192,0x00d88503,0x00000000,0x00000000,0x00000000,0x8b02d400,
    0x0002ddec,0x00000000,0x48830620,0x6cc26313,0x267b73ac,0x66645221,
    0x0000004c,0x00000000,0xc8000000,0x325136a5,0x5cc6395a,0x00007021,
    0x00000000,0x00000000,0x8d644000,0x271502c8,0x0000000a,0x00000000,
    0x00000000,0x58dc0000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,
};

static signed short stb__arial_10_usascii_x[95]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,
-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
static signed short stb__arial_10_usascii_y[95]={ 8,1,1,1,1,1,1,1,1,1,1,2,7,5,
7,1,1,1,1,1,1,1,1,1,1,1,3,3,2,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,1,3,1,3,1,3,1,3,1,1,
1,1,1,3,3,3,3,3,3,3,1,3,3,3,3,3,3,1,1,1,4, };
static unsigned short stb__arial_10_usascii_w[95]={ 0,2,3,5,5,8,6,2,3,3,4,5,2,3,
2,3,5,4,5,5,5,5,5,5,5,5,2,2,5,5,5,5,9,7,6,7,6,6,6,7,6,2,4,6,
5,7,6,7,6,7,7,6,6,6,6,9,6,6,6,3,3,2,4,7,3,5,5,5,5,5,3,5,5,2,
3,5,2,7,5,5,5,5,4,5,3,5,5,7,5,5,5,3,2,3,5, };
static unsigned short stb__arial_10_usascii_h[95]={ 0,7,3,8,8,8,8,3,9,9,4,5,3,2,
1,8,8,7,7,8,7,8,8,7,8,8,5,7,6,4,6,7,9,7,7,8,7,7,7,8,7,7,8,7,
7,7,7,8,7,8,7,8,7,8,7,7,7,7,7,9,8,9,4,1,2,6,8,6,8,6,7,7,7,7,
9,7,7,5,5,6,7,7,5,6,8,6,5,5,5,7,5,9,9,9,2, };
static unsigned short stb__arial_10_usascii_s[95]={ 127,80,80,58,76,82,91,84,1,37,72,
95,77,93,101,110,24,104,13,36,109,70,98,60,114,104,73,123,25,121,31,
7,20,115,66,46,97,90,83,9,73,29,53,53,47,39,32,41,22,1,14,
120,1,17,113,103,96,89,82,30,42,34,67,104,97,37,64,49,30,43,66,
70,60,120,16,8,123,113,107,61,54,76,76,19,49,55,101,87,67,1,81,
12,9,5,87, };
static unsigned short stb__arial_10_usascii_t[95]={ 1,20,34,1,1,1,1,34,1,1,34,
28,34,34,34,1,11,20,28,11,20,1,1,20,1,1,28,20,28,28,28,
28,1,20,20,11,20,20,20,11,20,20,1,20,20,20,20,1,20,11,20,
1,20,11,11,11,11,11,11,1,11,1,34,34,34,28,1,28,11,28,11,
11,11,11,1,20,11,28,28,28,11,11,28,28,1,28,28,28,28,28,28,
1,1,1,34, };
static unsigned short stb__arial_10_usascii_a[95]={ 40,40,51,80,80,127,96,27,
48,48,56,84,40,48,40,40,80,80,80,80,80,80,80,80,
80,80,40,40,84,84,84,80,145,96,96,103,103,96,87,111,
103,40,72,96,80,119,103,111,96,111,103,96,87,103,96,135,
96,96,87,40,40,40,67,80,48,80,80,72,80,80,40,80,
80,32,32,72,32,119,80,80,80,80,48,72,40,80,72,103,
72,72,72,48,37,48,84, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_10_usascii_BITMAP_HEIGHT or STB_FONT_arial_10_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_10_usascii(stb_fontchar font[STB_FONT_arial_10_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_10_usascii_BITMAP_HEIGHT][STB_FONT_arial_10_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_10_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_10_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_10_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_10_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_arial_10_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_10_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_10_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_10_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_10_usascii_s[i] + stb__arial_10_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_10_usascii_t[i] + stb__arial_10_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_10_usascii_x[i];
            font[i].y0 = stb__arial_10_usascii_y[i];
            font[i].x1 = stb__arial_10_usascii_x[i] + stb__arial_10_usascii_w[i];
            font[i].y1 = stb__arial_10_usascii_y[i] + stb__arial_10_usascii_h[i];
            font[i].advance_int = (stb__arial_10_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_10_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_10_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_10_usascii_s[i] + stb__arial_10_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_10_usascii_t[i] + stb__arial_10_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_10_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_10_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_10_usascii_x[i] + stb__arial_10_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_10_usascii_y[i] + stb__arial_10_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_10_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_10_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_10_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_10_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_10_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_10_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_10_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_10_usascii_LINE_SPACING
#endif

