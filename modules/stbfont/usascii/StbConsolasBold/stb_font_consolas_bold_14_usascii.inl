// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_consolas_bold_14_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_consolas_bold_14_usascii'.
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

#define STB_FONT_consolas_bold_14_usascii_BITMAP_WIDTH         128
#define STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT         70
#define STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_consolas_bold_14_usascii_FIRST_CHAR            32
#define STB_FONT_consolas_bold_14_usascii_NUM_CHARS             95

#define STB_FONT_consolas_bold_14_usascii_LINE_SPACING           9

static unsigned int stb__consolas_bold_14_usascii_pixels[]={
    0x75c00011,0x03fb300b,0x26e4402a,0x640bffe2,0x27ff4005,0x00164770,
    0x20000000,0x5c01d14e,0x740bee66,0x80f880ae,0x225ebdf8,0x1fd02fba,
    0xd06ffec4,0x8be6035b,0x107c806d,0x5fcbdffb,0x7ec41efe,0x7749d0df,
    0x5d84fa80,0xec882f88,0xf12ec1ef,0x1102f883,0x24fdbfe8,0x263e404e,
    0xe83ec02f,0x3fe5f9af,0x5ff46fbd,0x7c49d4fe,0x6c837c45,0x77c42f88,
    0x23e61ced,0x7c43eaaa,0xa9ffffe2,0x04e9f62f,0x417a0fe2,0x34fffffc,
    0x4bf2f47f,0x6c5f50fc,0x21fb89d6,0x30f700fb,0x4cbfa83f,0xddffbeb8,
    0x55517c44,0xf707e4fb,0x0fb813a3,0xea981fa8,0x43f71aaf,0x0fc93e5e,
    0x747dc1f9,0x0dd1fc44,0x6ec9774c,0xd84fff88,0x44dddbec,0x6cf902f8,
    0x04e97d47,0x204f817a,0xf12fa87d,0x6cfb27cb,0x42757d47,0xe8813e4f,
    0x2609fb3e,0x2fa0effe,0x443dcdaf,0x7dcf902f,0x8274bea1,0x03f201fa,
    0x577c43ec,0x2e77e5fe,0xfa87ee4f,0xf16e84e9,0x7d43e409,0xe9bf7e00,
    0x42ebeafb,0x54f902f8,0x2743f22f,0x1fc406d8,0xbff707d8,0x27fffcbd,
    0xe8fc8be6,0x817a5f84,0x102f886c,0xefbe9faf,0x17c40fef,0x33fe27c8,
    0x2613a4fc,0x906d802f,0x3a10337f,0xff8033e5,0x989d4fcc,0x6c81f23f,
    0x66d42f88,0x2b364fcf,0x2f881c8c,0xffd88f90,0x03e42744,0xfe882f98,
    0x4f97a04f,0x867ff4c0,0xf507e44e,0x1fc17605,0x70fbffa6,0x40be200f,
    0xe82bf06e,0xd0027c44,0x3600440b,0x40400fa4,0x3613ea4e,0x40ff6a0f,
    0x82640cfc,0x445baef8,0xb7b12fcc,0x3fbf209f,0x2a259dd3,0x000a6000,
    0x9d000000,0x37441be2,0x0da80595,0xbd9100d4,0x11eee887,0xca807ddb,
    0x000fbb63,0x00000000,0x00649d00,0x00000071,0x00000000,0x00000000,
    0x7b000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x0de40000,0x00000164,0x07902ca8,
    0xcc89dc00,0x000006e0,0xfd86f64c,0x3fae0fff,0x5ffea86f,0xfff897e2,
    0x3f2027c5,0x7ff4c4ff,0x3f7f61ff,0xfd32fc44,0xcaf401bf,0xd98d55ce,
    0x3f621fff,0x99df104f,0x43f6aa61,0x5c5bbdfd,0x3e64bbef,0x3e2fd887,
    0x7f555c04,0x0fee3ba2,0x97e1f27f,0x205fa9ef,0xf1d57b5e,0x1babff83,
    0x213eebfa,0x47dc02fa,0x1be205f9,0x8fe60350,0x201efdcf,0x7c53e2f9,
    0x42f46fc3,0x2f49f15f,0x2abfffb1,0x7cc4dcff,0x7f45f505,0x2e00fdc0,
    0x3331fb8f,0x4c001fcc,0x37fe1fda,0xeda986fb,0x03f6ff60,0x9f01bff7,
    0xd0fee7ec,0x4c4bf35f,0x1dff80ea,0x7fec47dc,0xffffff71,0x23f23ee0,
    0x0fea7ff8,0x2efb8370,0xf81f92fc,0x337a0dff,0x99ffd81c,0xffd127c4,
    0x8bd1fccb,0xffd302f8,0x3bebf21d,0x7f9511fc,0x323ee055,0x7d4fb31f,
    0xa83fe603,0x3f24f80f,0x3e2bf500,0x4fdc0aad,0xb2747cee,0x3ee9f93d,
    0xf99b17a1,0x5d7f660b,0xb83f74ff,0x547e401f,0x6f89f23f,0x03107f40,
    0x7407d93e,0x97ffff66,0x88bff16d,0xabec7f30,0x7d4bf12f,0x3e02eaf9,
    0x07e47f56,0x2ab207ee,0x36b3fa6f,0x25defec7,0xf03f71f2,0x9a89f73b,
    0x45f54fca,0xb37f90fc,0xbf14e8bf,0x3be2bf33,0x15f15fea,0x2b265f1f,
    0x2bbe4fca,0x81fb84fb,0x3621effd,0xffc85fff,0xc83fd54f,0x4fffe81f,
    0x2a4ffff8,0x226ebadf,0x13fceffd,0x6fffdcbf,0x5777fee0,0xf99bf25c,
    0x3a60cfff,0x03f704ff,0x02006004,0x02004033,0x776dc030,0x8040100c,
    0x20000400,0x00004008,0x00000000,0x00000000,0x00000000,0x00000000,
    0xf90f32e0,0x02c97d41,0x22ec0164,0x003f21fa,0x217fffec,0x2002fec9,
    0x07fffff8,0x43efff88,0x743fa2fb,0x65c27cc7,0xfb1fcc6f,0x013e02fc,
    0x643f51be,0x93ffaa0f,0x2a1cccfd,0x74c0acef,0x333224ff,0xfffd36fd,
    0x3faf7e21,0x24fab7c3,0x807ee1fc,0x9f16e86e,0x013e02fc,0x643f5022,
    0x3f6b7a0f,0x03740bb2,0x07f95df1,0x4cff47f6,0x3e29f10a,0x07f5fd45,
    0x203ec9f3,0xfb9fb86e,0x22fcd7e1,0x360efedf,0x90fd46ff,0x6d3e601f,
    0x37e20acf,0xf0fd42bb,0x7f47f70b,0xfba7c40b,0xf83ffe83,0x6e809f16,
    0x7c6ecf88,0x7fc0ef8d,0x3aaa4fbd,0x1f90fd46,0x7f64fea0,0xddff31ff,
    0xdd1fd49f,0x7f4c6f88,0xffff10df,0x203fee07,0x402fa8fc,0x87ffb06e,
    0x5f80eedf,0xf51ba17e,0x74407e43,0xf35f980e,0xdff13ec7,0x00fd8ffd,
    0x37e29f91,0x9fff04fb,0x00f95f50,0x21fe60dd,0x49f04fff,0x7d46e85e,
    0x0ff41f22,0xc93e5f88,0x3af2e20f,0x26e0fee6,0x29f13fb9,0x757dc0fd,
    0x05edf80f,0x07f506e8,0x9f05f9bf,0x223742f4,0xd85fa9ef,0x7ed4d41f,
    0x1beabf63,0x9ff14f98,0x3fffa999,0x3e69f10d,0x2fcdbe24,0x3301ffec,
    0x3f2a13dd,0x07fabf06,0xd332f49f,0x7ffd413d,0x666fec0d,0x887dfff4,
    0x5540dffc,0xfff30efc,0x440c4fff,0x7e43fa4f,0xff70bf62,0x7ffffc01,
    0xafc09d76,0xe93e0ef8,0x1bffffe5,0x7fffc402,0xf000027f,0x000019df,
    0x00000000,0x00000000,0x00000000,0x00000000,0x50000000,0xf987d4df,
    0x83e4ff15,0x6cbea0fd,0xffff3f85,0x7c8bea9f,0x001f7ffc,0x553ffff6,
    0x4002deff,0x703dfff8,0xfa8001ff,0x3ea1f52f,0x1f27fb8f,0x6cdd27cc,
    0xdf552f85,0x7c8bea35,0x22fedefc,0xfb0dfffb,0x33ea3555,0xfeb83feb,
    0xf95bf13f,0x107ffb07,0x3ea1bffb,0x3ea1f56f,0x1f27ddae,0x22fa8fd8,
    0xf0be115c,0x1f22fa8b,0x26a3ec9f,0x20fb4fa9,0xf71fa1fa,0x93e2575b,
    0x85fcf85f,0xf54faafd,0x2a1f53f9,0x90fbfdce,0x375fcc0f,0x41fa75b2,
    0x5567d45f,0x0fb27c7d,0x4fed7e66,0x643f5099,0x7c41ba1f,0x7d42fb9c,
    0x4e7c47d9,0xbf3f56d9,0x3ebae1f5,0x80f90f9e,0x475c2ffd,0x2fc1f8ff,
    0x1fffffea,0xb8bf73bf,0xffb5ffff,0xb87ea7ff,0x7c417e1f,0xbe41efff,
    0x3ffe62fb,0xf71f57ff,0x5fdae1f9,0x980f91f9,0xfdbeb86f,0x2a2fc0fa,
    0x7c7d99bf,0x3e20cfff,0xa83ed7e5,0x6f83f61f,0x1fe69f10,0x449f53dd,
    0xf11f503f,0x455b21ff,0xf00f91f8,0xbd5bf509,0x7d45f81f,0x01bf1f22,
    0x57f277e2,0x7c3f507d,0x95d6fe46,0x4c3f64f8,0x746fffff,0x1f5199af,
    0x22e43ff2,0x555f91f8,0xff509f05,0x2aa1ff71,0x45f51aef,0x32027c7c,
    0x5fb5ddff,0x333ea355,0xfffc82ff,0x9f75bf13,0x7e4ccfdc,0x4ffffa21,
    0x21ff10fa,0xfc97c45c,0x84f86fff,0x7cff15fa,0x5f54ffff,0x2013e3e4,
    0xffffd808,0x03bdff54,0x6fffc408,0x7f51b60b,0x00000060,0x00000000,
    0x00000000,0x00000000,0x20500000,0x01df14f8,0xffffb8a2,0x3ff600ff,
    0x2f9f43ff,0x7fcc7ea8,0x7fb87fff,0x00000000,0xffd88f20,0x2213ea0d,
    0x2203f94f,0xdf5510fe,0xd97e2155,0x97c1aaaf,0x1fffa21f,0x8df99991,
    0x76e47ff8,0x75fc5faf,0xff9bb0ef,0x2fc13a05,0xb8bf97fd,0x2b3e20df,
    0x03df304f,0xd9fe617e,0xfddfd307,0x03e4e45d,0xf9db0fea,0xfbffbfc8,
    0x53ef7fe0,0xd07eaefd,0x17d53e09,0x21df30fb,0xf506ecf8,0xa82fc01d,
    0x7dc41f61,0x7c80afcb,0x27ea3f40,0x8ceb647c,0xb5f97e1f,0xaa89ae1f,
    0x4f20aadf,0x203f21fb,0x7fff14fc,0xf805fd10,0xffffb005,0x207abcc5,
    0xd0fea07c,0x3ad91f29,0xe93e1f8c,0x7fdc0fb5,0xf500ffff,0x1fec3ec7,
    0x101fd9f1,0x82fc07fb,0x2aabf608,0x9fb9fb50,0x0fe81f20,0x27f267ee,
    0x3e33ad90,0xfb5e93e1,0x22013a00,0x224fbbff,0x4e7c42fe,0x413f205f,
    0x367f985f,0xdd9fd507,0x7d41f209,0x7ffffec3,0x233ad92f,0xb5e93e1f,
    0x4013a00f,0x260dfffa,0xf94f881e,0x7c075c05,0x1f66f985,0x550995c8,
    0x0fe855fd,0x4fe4ccc4,0x3e33ad90,0xfb5e93e1,0x1000ae00,0x229f1000,
    0x5f8000ff,0x3607d810,0xffff09b4,0x4027ccff,0x0000007c,0x00000000,
    0x00000000,0x00000000,0x00000000,0x3a4f8000,0x267d09d5,0x7f43b64f,
    0x42b84fff,0x70bea0fc,0x4ddddd83,0x4e4c2744,0x9906a0ca,0x2e201881,
    0x777773bb,0x3e000577,0x7c2ed7a4,0x8beebf22,0x2a2febba,0x7f31abd8,
    0x91fea3ec,0xdc879999,0x3e4fd41f,0x0ed88ff5,0x47a1dff1,0xddd7fff9,
    0x0007dddd,0x2d95e93e,0x7f41f8ce,0xc89f504f,0x5ba2feef,0x07f444f8,
    0xf9811111,0x5cfcc6b8,0x8441be67,0x0fdfe9eb,0xf8000000,0x7cfdd7a4,
    0x7fd40f9f,0xc886f880,0x54fdc3ff,0x7fc6d81f,0xe8fa5fff,0x116a3623,
    0x2dc86600,0xf0000000,0x6fd57e29,0xfee87dfd,0xde80fe84,0x33e23ecd,
    0x20f7546e,0x71199999,0x00000398,0x00000000,0x35feaef8,0xc8dfb5ff,
    0x3f22fc9f,0x1ec21bbd,0x0cc3ffc8,0x00000000,0x00000000,0x377fea00,
    0x97eaff15,0x7c3fa4fa,0x0984ffff,0x0001ff30,0x00000000,0x00000000,
    0x00000040,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__consolas_bold_14_usascii_x[95]={ 0,2,1,0,0,0,0,2,1,1,0,0,1,1,
2,0,0,0,0,0,0,1,0,0,0,0,2,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,3,1,0, };
static signed short stb__consolas_bold_14_usascii_y[95]={ 10,0,0,1,-1,0,0,0,-1,-1,0,2,7,5,
7,0,0,1,0,0,1,1,1,1,0,0,2,2,2,4,2,0,0,1,1,0,1,1,1,0,1,1,1,1,
1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,0,1,11,0,2,0,2,0,2,0,2,0,0,
0,0,0,2,2,2,2,2,2,2,0,3,3,3,3,3,3,0,-2,0,4, };
static unsigned short stb__consolas_bold_14_usascii_w[95]={ 0,3,6,8,8,8,8,3,6,5,7,8,5,5,
4,7,8,7,7,7,8,6,8,7,7,7,4,5,7,7,6,6,8,8,8,7,8,6,6,8,8,6,6,8,
6,8,8,8,8,8,8,7,8,8,8,8,8,8,7,4,8,5,8,8,5,7,8,7,7,7,8,8,7,7,
7,7,7,8,7,8,8,7,7,6,7,7,8,8,8,8,6,6,2,6,8, };
static unsigned short stb__consolas_bold_14_usascii_h[95]={ 0,11,4,9,13,11,11,4,14,14,7,8,6,3,
4,12,11,9,10,11,9,10,10,9,11,10,9,11,9,5,9,11,13,9,9,11,9,9,9,11,9,9,10,9,
9,9,9,11,9,13,9,11,9,10,9,9,9,9,9,13,12,13,5,2,4,9,11,9,11,9,10,11,10,10,
13,10,10,8,8,9,11,11,8,9,11,8,7,7,7,10,7,13,15,13,4, };
static unsigned short stb__consolas_bold_14_usascii_s[95]={ 94,66,74,55,31,86,57,123,10,4,34,
114,51,101,81,77,103,64,51,40,80,59,66,72,70,75,43,18,26,57,10,
24,40,110,101,10,84,77,48,1,51,44,121,17,19,10,1,119,60,63,98,
95,34,42,116,35,107,26,83,72,85,49,65,107,86,69,31,93,78,119,112,
48,26,34,55,18,1,89,98,1,110,102,106,91,94,1,42,9,18,9,27,
24,1,17,92, };
static unsigned short stb__consolas_bold_14_usascii_t[95]={ 13,17,60,50,1,17,17,50,1,1,60,
50,60,60,60,1,17,50,29,17,50,29,29,50,17,29,50,17,50,60,50,
17,1,40,40,17,40,40,50,17,40,40,17,50,40,40,40,1,40,1,29,
17,50,29,29,40,29,40,29,1,1,1,60,60,60,40,17,40,17,40,17,
17,29,29,1,29,29,50,50,50,1,1,50,29,1,60,60,60,60,29,60,
1,1,1,60, };
static unsigned short stb__consolas_bold_14_usascii_a[95]={ 123,123,123,123,123,123,123,123,
123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,
123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,
123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,
123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,
123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,
123,123,123,123,123,123,123, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT or STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_consolas_bold_14_usascii(stb_fontchar font[STB_FONT_consolas_bold_14_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT][STB_FONT_consolas_bold_14_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__consolas_bold_14_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_consolas_bold_14_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_consolas_bold_14_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_consolas_bold_14_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_consolas_bold_14_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__consolas_bold_14_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__consolas_bold_14_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__consolas_bold_14_usascii_s[i] + stb__consolas_bold_14_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__consolas_bold_14_usascii_t[i] + stb__consolas_bold_14_usascii_h[i]) * recip_height;
            font[i].x0 = stb__consolas_bold_14_usascii_x[i];
            font[i].y0 = stb__consolas_bold_14_usascii_y[i];
            font[i].x1 = stb__consolas_bold_14_usascii_x[i] + stb__consolas_bold_14_usascii_w[i];
            font[i].y1 = stb__consolas_bold_14_usascii_y[i] + stb__consolas_bold_14_usascii_h[i];
            font[i].advance_int = (stb__consolas_bold_14_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__consolas_bold_14_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__consolas_bold_14_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__consolas_bold_14_usascii_s[i] + stb__consolas_bold_14_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__consolas_bold_14_usascii_t[i] + stb__consolas_bold_14_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__consolas_bold_14_usascii_x[i] - 0.5f;
            font[i].y0f = stb__consolas_bold_14_usascii_y[i] - 0.5f;
            font[i].x1f = stb__consolas_bold_14_usascii_x[i] + stb__consolas_bold_14_usascii_w[i] + 0.5f;
            font[i].y1f = stb__consolas_bold_14_usascii_y[i] + stb__consolas_bold_14_usascii_h[i] + 0.5f;
            font[i].advance = stb__consolas_bold_14_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_consolas_bold_14_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_consolas_bold_14_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_consolas_bold_14_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_consolas_bold_14_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_consolas_bold_14_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_consolas_bold_14_usascii_LINE_SPACING
#endif

