// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_bold_8_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_bold_8_usascii'.
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

#define STB_FONT_arial_bold_8_usascii_BITMAP_WIDTH         128
#define STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT         32
#define STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT_POW2    32

#define STB_FONT_arial_bold_8_usascii_FIRST_CHAR            32
#define STB_FONT_arial_bold_8_usascii_NUM_CHARS             95

#define STB_FONT_arial_bold_8_usascii_LINE_SPACING           5

static unsigned int stb__arial_bold_8_usascii_pixels[]={
    0x11044082,0x22044044,0x00804221,0x00421020,0x10408811,0x02000020,
    0x40020110,0x3a2a9325,0xdbca8aa2,0xbb5c36e4,0x98bbba21,0x4e762c83,
    0x33ef882b,0x22b2e3dd,0x6c44cd83,0x581bb31e,0x37a61dd3,0xb11776c5,
    0x52c4751b,0x5ccaa345,0x8773bcc9,0x68a5cb16,0x365903b6,0x43b975ef,
    0xb876e1da,0x3ce80cba,0xb9c84dd4,0x965dd222,0x452a29da,0x0aeaeae6,
    0x22d4aa3d,0x23ab393b,0xc9a68774,0x6425c3a3,0x32e19932,0x44f32668,
    0x573511ed,0x90cff443,0x93b6a5bb,0x5c1dd32a,0x8f4590ee,0x6c2cbaac,
    0x77132552,0x4a7a2eb2,0xad4d343b,0xc8b8ea68,0x4ee9fdb2,0x54d26266,
    0x92e4644b,0x4dd45f55,0x86457314,0x36553aac,0x21f53b32,0x223aabab,
    0x9dc68aa6,0x2e2ecdab,0x76458b43,0x7543a62d,0x6dcb190e,0x4c77a63e,
    0x2ece21ee,0x6c4bbdb3,0x2c1bd31d,0x3ba23bd3,0x43bfb20e,0x2a588dd8,
    0xb11e8aa5,0x964cd645,0x0aad50cb,0x00000000,0x00020811,0x30000000,
    0x4c151401,0x4c144661,0x542a60aa,0x00000052,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x20208808,0x2a040400,
    0x220221db,0x32297910,0x0811114c,0x10422084,0x21108104,0x22020888,
    0x11108808,0x1f76c088,0x4da12a77,0xdbb160ee,0x3b9a32e3,0x69bb8f4c,
    0x3b6ed377,0xa96cf20f,0x3ea3a3d5,0x9dc764a8,0x21bfd92a,0x176f5c2b,
    0x43b7ae77,0x2e292a3b,0x5af22953,0x4c321d88,0x734ee334,0x647b6599,
    0x8d15768a,0x6c5be83d,0x2b72b24d,0xa8752a2c,0x57571662,0x27725cee,
    0xc8ee5b3b,0x54ee1bb3,0x6ccd3774,0x5c1dcaa1,0x5a32e3ee,0x45b3624a,
    0x541326de,0x9507d40f,0x7c41d93d,0x4598ee68,0x37fae5db,0x7775cee0,
    0xf8ad4770,0x564ee950,0x44751368,0x15ceab34,0x4c9569dc,0x6bb445ab,
    0xb9d11a20,0xd86eafc4,0x4598ee3d,0xf1770edb,0xb84b9dc1,0xd1277643,
    0x5b7a61dd,0xd92c0de9,0x4ee0261d,0x80ba8956,0x883ddfd2,0x3a2d9e46,
    0x41f509b3,0x5571663b,0x772d4ee9,0x000ee0ee,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x84100000,
    0x10400208,0x10222088,0x22221041,0x88822220,0x80808100,0x08711939,
    0x180cc980,0x441bb103,0xa55aae60,0x752f99fb,0xec8fa750,0x23dbd74f,
    0x5d6a953b,0x377ae5de,0x5c1dbd71,0x2f983e25,0x32bbb844,0x8f74c99b,
    0x53ae0acb,0x79310bea,0x7f5111d4,0x3aef6e95,0x7b950752,0x6465c360,
    0x26971972,0x8cb81974,0xcaa54ee0,0x5cc83b65,0x8899b620,0x5c4ee266,
    0xd881d93e,0x3f279976,0xa5f5d45f,0x752cddbb,0x7507df50,0xeb8f6f5c,
    0x3ae934ed,0x4377ae3e,0xaac4b33b,0x3075a0db,0x20f426c9,0x43bb50e8,
    0x217d74ea,0x98ea4ddb,0x574fabac,0x20ea57dd,0x0640f8ca,0xa9dd6a77,
    0x2e0ee514,0x44973b83,0x3eabfdd5,0x74ca23fe,0x07a21c41,0x44001180,
    0x2e9b3a80,0xdf52bcca,0x22dcea1d,0xb9777dc6,0x1dd26953,0xfb9777dc,
    0x1b1620de,0x29834476,0x27fe4598,0x00000000,0x00000000,0x00000000,
    0x00000000,0x91000000,0xc82f221b,0xaba4aa1c,0x36e7952a,0x2a71191d,
    0xb5b752cb,0x26e90445,0x4ddb822a,0x109dc102,0x9998114c,0x00000ee1,
    0xcbb8cddc,0x5dcd1772,0x65cdd168,0x5ddcd510,0x2eed1972,0xc97268da,
    0x3b50dbea,0x76e46aa6,0x56466595,0x514c32e7,0x00000555,0x66462b20,
    0xbb9a591b,0x23b9ba68,0xb9ba20e9,0xb526aed3,0xb9b31cd8,0xccb86d4d,
    0x35015044,0x00000009,0x32ed8800,0x8b7a23bb,0x79796ce9,0x22efe8ae,
    0xabb4ee4c,0x8a666d49,0x00004d9f,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,
};

static signed short stb__arial_bold_8_usascii_x[95]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,-1,0,0,-1,0,0,0,0,0,0,0,0,0,0,
-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
static signed short stb__arial_bold_8_usascii_y[95]={ 6,0,0,0,0,0,0,0,0,0,0,1,5,3,
5,0,0,0,0,0,0,0,0,0,0,0,2,2,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,2,0,2,0,2,0,2,0,0,
0,0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,0,2, };
static unsigned short stb__arial_bold_8_usascii_w[95]={ 0,2,4,4,4,7,6,2,3,3,3,4,2,3,
2,3,4,3,4,4,4,4,4,4,4,4,2,2,4,4,4,5,7,6,5,5,5,5,5,6,5,2,4,6,
5,6,5,6,5,6,6,5,5,5,6,7,5,6,5,3,3,2,4,6,2,4,5,4,4,4,3,4,4,2,
3,4,2,6,4,5,5,4,3,4,3,4,4,6,4,4,4,3,2,3,4, };
static unsigned short stb__arial_bold_8_usascii_h[95]={ 0,6,3,7,7,7,7,3,8,8,4,5,3,2,
1,7,7,6,6,7,6,7,7,6,7,7,4,6,5,3,5,6,8,6,6,7,6,6,6,7,6,6,7,6,
6,6,6,7,6,7,6,7,6,7,6,6,6,6,6,8,7,8,4,2,2,5,7,5,7,5,6,6,6,6,
8,6,6,4,4,5,6,6,4,5,7,5,4,4,4,6,4,8,8,8,3, };
static unsigned short stb__arial_bold_8_usascii_s[95]={ 39,44,85,55,71,76,84,79,1,35,65,
120,82,90,104,101,123,65,95,19,69,66,91,27,105,96,125,81,105,69,110,
89,20,74,32,28,59,53,47,1,38,123,50,20,14,7,1,39,117,116,107,
110,96,8,86,78,72,65,59,28,24,32,53,97,94,115,60,1,14,6,45,
49,40,93,16,102,114,46,41,11,34,54,27,100,46,17,36,58,22,84,31,
12,9,5,74, };
static unsigned short stb__arial_bold_8_usascii_t[95]={ 9,18,25,1,1,1,1,25,1,1,25,
18,25,25,25,1,1,18,18,10,18,1,1,18,1,1,18,18,18,25,18,
18,1,18,18,10,18,18,18,10,18,10,1,18,18,18,18,1,10,1,10,
1,10,10,10,10,10,10,10,1,10,1,25,25,25,18,1,25,10,25,10,
10,10,10,1,10,10,25,25,25,10,10,25,18,1,25,25,25,25,18,25,
1,1,1,25, };
static unsigned short stb__arial_bold_8_usascii_a[95]={ 32,38,54,64,64,102,83,27,
38,38,45,67,32,38,32,32,64,64,64,64,64,64,64,64,
64,64,38,38,67,67,67,70,112,83,83,83,83,76,70,89,
83,32,64,83,70,95,83,89,76,89,83,76,70,83,76,108,
76,76,70,38,32,38,67,64,38,64,70,64,70,64,38,70,
70,32,32,64,32,102,70,70,70,70,45,64,38,70,64,89,
64,64,57,45,32,45,67, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT or STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_bold_8_usascii(stb_fontchar font[STB_FONT_arial_bold_8_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT][STB_FONT_arial_bold_8_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_bold_8_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_bold_8_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_bold_8_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_arial_bold_8_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_bold_8_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_bold_8_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_bold_8_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_bold_8_usascii_s[i] + stb__arial_bold_8_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_bold_8_usascii_t[i] + stb__arial_bold_8_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_bold_8_usascii_x[i];
            font[i].y0 = stb__arial_bold_8_usascii_y[i];
            font[i].x1 = stb__arial_bold_8_usascii_x[i] + stb__arial_bold_8_usascii_w[i];
            font[i].y1 = stb__arial_bold_8_usascii_y[i] + stb__arial_bold_8_usascii_h[i];
            font[i].advance_int = (stb__arial_bold_8_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_bold_8_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_bold_8_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_bold_8_usascii_s[i] + stb__arial_bold_8_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_bold_8_usascii_t[i] + stb__arial_bold_8_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_bold_8_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_bold_8_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_bold_8_usascii_x[i] + stb__arial_bold_8_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_bold_8_usascii_y[i] + stb__arial_bold_8_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_bold_8_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_bold_8_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_bold_8_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_bold_8_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_bold_8_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_bold_8_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_bold_8_usascii_LINE_SPACING
#endif

