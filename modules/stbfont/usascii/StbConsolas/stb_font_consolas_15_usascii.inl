// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_consolas_15_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_consolas_15_usascii'.
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

#define STB_FONT_consolas_15_usascii_BITMAP_WIDTH         128
#define STB_FONT_consolas_15_usascii_BITMAP_HEIGHT         76
#define STB_FONT_consolas_15_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_consolas_15_usascii_FIRST_CHAR            32
#define STB_FONT_consolas_15_usascii_NUM_CHARS             95

#define STB_FONT_consolas_15_usascii_LINE_SPACING          10

static unsigned int stb__consolas_15_usascii_pixels[]={
    0xc806e6b7,0x73028800,0x33261905,0xb81a880c,0x005b02cc,0x4c004c51,
    0x302982cc,0x80054535,0x3ee2b700,0xf900b903,0x641cfa85,0x2e0abae6,
    0x2aa0ddbe,0x0e7dc45d,0x405b96e0,0x645ebcfa,0x3f67f446,0xffe8807d,
    0x81aa2dc3,0x6c24403e,0x16e0fa84,0x2e0f2354,0x0f3f7ee5,0x007c43d0,
    0xd917c45f,0x3e9e64d8,0x20faae40,0xf303cc5b,0x82aaa981,0x2dc3e83d,
    0x5c3441e8,0x201e2be5,0xf504c86a,0x3e3649b0,0xa8be9e62,0x41f14d82,
    0x3a03cc5b,0x07f77643,0xb70f50b6,0x2336ab50,0x273e5b87,0x7983d806,
    0x64b90d70,0x27983e25,0x545fcece,0x42dc4e9f,0x8817200f,0x1b20f40f,
    0x3a6f216e,0x2dc0e8f9,0xf880bff5,0x0d705b00,0x3f12dcb7,0x221dd3dc,
    0x20ffe21f,0x506ea85b,0xec87c40d,0x85b84d83,0x1d78bd9d,0x77ec45b8,
    0x35409901,0xb72e435c,0x74ff54e8,0x9fbd1743,0x66c2dcfa,0x7c40f502,
    0x4d81d730,0x9e8e85b8,0x90b70f5a,0x03f01f77,0x207cc1f8,0xff316e3f,
    0x3a1f4f3b,0x3efe6d52,0x40788b72,0xd03e206b,0x85b86b85,0x68cb9e8e,
    0xf89d85b8,0x2dc02d41,0x23644774,0x7d3cc008,0x7dcb71f8,0x80f116e7,
    0xb03e204d,0x85b87987,0x2dedcdae,0x5d3515b8,0x802e81fb,0x7fec40f8,
    0x26025c0d,0x2a6c8fa7,0x2e1ff52f,0x3f103c45,0x0f607c40,0x7b0b70be,
    0x2e055171,0x19dffd15,0x0f600698,0x407d835c,0x37fff279,0x75fffdc0,
    0x20798b76,0x6c3d405d,0x16e0fa83,0x45b8016e,0x800f6069,0xb9bf1069,
    0x00000001,0x417625b8,0xbb1180eb,0x4b903d50,0x10cf885b,0x09316e01,
    0x03200064,0x0000e5c4,0xaadc0000,0x203b00df,0xd700dffe,0x3fee1b09,
    0x37ff620f,0x002fff40,0x00000000,0x2e000000,0x00000005,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x98000000,0x21982881,0x8a8a20a9,
    0x828802a8,0x331aaaa8,0x26000540,0x4055531a,0x300e6019,0xccca8599,
    0x22cb982c,0x07e22ffc,0xc9b3aa5f,0x17f3b3a3,0xccf98f30,0x740992ef,
    0x9bbf5003,0x7e81f726,0xcfa816e0,0x333ae5eb,0x75e7cc2c,0x49b0fdc4,
    0x547cb27a,0x1f887746,0x5c9b1e60,0x03e81325,0x03d407b0,0x5db53073,
    0x3e22f855,0x23e80972,0xf52ec0f9,0x1f19926c,0x1743e83d,0x8fa3dd4c,
    0x0a89325b,0x7c03517d,0x2a61ea01,0xefeea82a,0x9b0f50ee,0x20f8812e,
    0x3e1ec2fb,0x3b621f8a,0x7c3e84ca,0x1fb3fa22,0x645f77f7,0x76f4bd14,
    0x3e6623fc,0x43d4099a,0x16e07eea,0xfbae435c,0xd8bcc2ce,0x81db93ee,
    0x1a606adc,0x6c3f11f4,0x777b1e64,0x45e8cc83,0x754d50ee,0x542eeefe,
    0x5b81ea07,0x26b70b70,0x3ea4fcaa,0x0be9b4fa,0x3d01f7cc,0xbb13e811,
    0x9f1e62f8,0x4ecc8333,0x203e63e8,0xa81ea01f,0x35c16e07,0x267b8264,
    0x07cf62ff,0x33201fd0,0x3ffa3eeb,0x983e20cf,0x77f77e47,0x7d09db90,
    0x00fc07c4,0x703d40f5,0x7f03e60d,0x22f89ea0,0x4e8031f8,0xf33d1d30,
    0x43f101f4,0x7d07e27b,0x7d0fe732,0x00fc07c4,0x103d40f5,0x11bd025f,
    0x89d304d9,0xb16c88ec,0x00ec8883,0xe9a67a5d,0x7546f403,0x2f98be67,
    0x3e8be699,0x807e03e2,0x701ea07a,0x7ec41ffd,0x3fff60df,0x21bffb03,
    0x06fe42f9,0x8bbea5b8,0x6ffcc03e,0x77ffdc79,0xd2fa9323,0x0fc07c47,
    0x87ffffec,0x00fffffd,0x00088000,0x00000020,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x541e5440,
    0x02980bcc,0xc9817995,0x3332a2cc,0x0370911c,0x32617995,0xcccc81cc,
    0xb81931cc,0x51260ee2,0x882b8599,0xbf70530c,0xebbeb879,0x3a20ff86,
    0x3ee1dcce,0x332a3bac,0xe81f32fc,0x36f3ba23,0x85f95752,0x21fdcccc,
    0xfa83ea4e,0x97d92740,0x35c3645f,0x007d41ff,0x2e07cc7d,0x7f007644,
    0x0f997400,0x400bb1f4,0x2a27404d,0x4bd07d1f,0x4b9020fa,0x971f40f9,
    0x92e403d8,0xf00be00d,0xf9974009,0x00f99f40,0x0eb80f60,0xf306bdd8,
    0x8d700fa3,0xf003e23f,0xd883bdb9,0xf9800ede,0x0177d400,0x740f9974,
    0x05554f53,0x7cc09b73,0x403ff101,0x3e806add,0x880d72e4,0x40fb99df,
    0x1881eeec,0x322003e6,0x4cba01ef,0x26b9f40f,0x372a2fec,0xe809d02f,
    0x0bfe201f,0x21f30d90,0x741f803d,0x40fc9762,0x005f10fe,0x25d00fc8,
    0x7a9f40f9,0x81f502e8,0x37b200eb,0x32036406,0x1f15f00e,0xd0ba0fd8,
    0x70be0fc5,0x20027c5f,0x225f01f8,0x7c4be21f,0x0f981742,0x9f980be2,
    0x816e03f8,0x2f7200ec,0x3ae0fe86,0x527c1f50,0x2e0fa81f,0x310989df,
    0x89a9f221,0x6453a0fb,0x742bf20f,0x362ec412,0x3a09999d,0x2dc03ee4,
    0x0999afc8,0xb001f7cc,0xfe983dff,0x0ff222ef,0x443bffaa,0x2e1dffff,
    0x7f4c2eff,0xfffb81ef,0x19fffb1e,0x7fffffc4,0x05e81f72,0x3fffe0b7,
    0x00ff82ff,0x51000080,0x00080001,0x10110000,0x00000001,0x00000000,
    0x00000000,0x00000000,0x00000000,0x54000000,0x0ca83882,0x446e1644,
    0x6447221c,0x371ccccc,0xccc98644,0x99972ccc,0x46e12299,0x64c1bccb,
    0x99953ccc,0x2b332279,0xb8a65300,0x42640bcc,0x03ffa669,0x99741ff1,
    0x644ff25f,0x7d1fcccc,0xdd993274,0x3bb2e599,0x3e81f14c,0x5c7fb9db,
    0x9d73cccf,0x333e6799,0x793b82fd,0x71fe66f4,0x4decb509,0xd1f7c40f,
    0x6f43fa65,0x93e9aa03,0xb702dc0b,0xd9f40f88,0x706b9b23,0xfa83e60b,
    0x2f673660,0xb73d47d1,0x7cc2d462,0x5d3d7c40,0x336af36a,0xbbe8ba04,
    0xb816e00e,0x4fa07c45,0x06b9ae3d,0xd03e60b7,0x3fbbfa67,0x53547d5e,
    0x4c25db2b,0x9f47c40f,0x59d3b52e,0xbd1aa099,0x205b801f,0x6667c45b,
    0xf75bb3fc,0x8d5575c5,0xf33ccceb,0xe8f44d81,0x87b2b7a0,0x0973fd6a,
    0xa8f881f3,0xbf56a5d6,0xee87d04b,0x702dc00f,0xccccf88b,0x85fddb3f,
    0xd74eeefb,0x03e67999,0x41f0f89b,0x264fdcde,0x83cbcd9e,0xf87c40f9,
    0x4eeb72ea,0xbe87a85b,0x702dc06c,0x9f40f88b,0x06b8d73d,0xf03e60b7,
    0x3f33f2a9,0x8fc47d2c,0x3ce9bcf8,0x87c40f98,0x70972eeb,0x27d07d0b,
    0xb816e05e,0x4fa07c45,0x06b8fa3d,0xa83e60b7,0xf75f731f,0x2f88fa35,
    0x8bbe1df1,0x221afa98,0x325ff10f,0x07d45b84,0x703f89f4,0x33d9310b,
    0x367d03e2,0x706b9ee3,0x3e61333d,0xb4c4fc99,0xfc99f459,0x22fc9be0,
    0x11fffffd,0x4c97e41f,0xe82746a8,0x16e07ea3,0x45fffff6,0x43d9f40f,
    0x3ee0d73f,0xfff36fff,0x16ab505b,0x0019dffd,0x00000000,0x00000000,
    0x00000000,0xb8000000,0x20cb800c,0x4001bccb,0x2cc98048,0x01aa9800,
    0x2a203551,0x40d5441a,0x4150aaa8,0x214c6628,0x14c1a88a,0xf9805ff1,
    0x3f737a1f,0x3cc03a65,0x0feefae0,0x373aa3d8,0x7e6f444f,0x336efe43,
    0x7c49fbbf,0x447d2dcd,0xddbbb70f,0x91fe7674,0x202e75cd,0x98fa1fae,
    0x2607ee1f,0x7a87e207,0x3dc05e88,0xf50f9936,0x1f98fa03,0xf88fa0b7,
    0xe8fc7f70,0xb364d50e,0xfae40f57,0xa85f0fa1,0xf303cc3f,0x7f307c41,
    0x3e3dd440,0x9b1f999a,0x27d03e20,0x11f41cf9,0x21516e1f,0xadc3e63e,
    0xf305f1f8,0x2a3e87e1,0x264e980f,0xf88be207,0x3a605f51,0x3be27dcd,
    0x09b1eeee,0xd98f61e6,0x7c47d1ef,0x11f40b70,0x2ecd501f,0x6f43f174,
    0x9d103fdc,0x3bee03cc,0x05f51fee,0x1fc798f6,0x03e20d70,0x36d9105d,
    0x02dc3e63,0x6c07c47d,0x75c7b99d,0xbd0af999,0x0fe60359,0x133100f3,
    0x7c1fcc1f,0x1ec8fd33,0x430bf882,0x2089ae5e,0xfd31d76c,0x23e816e1,
    0x7ffc40f8,0x3bae2fff,0x07d5efee,0x07981fb8,0x2f442dc0,0x11ebbfea,
    0xc98dfff9,0x3ff625ff,0x3bfff20e,0x1f5dfb11,0x223e816e,0x2ec3540f,
    0x203e87e0,0x33f300e9,0xfc998833,0x0107b100,0x80000020,0x00001008,
    0x07a84d80,0x0007d0fc,0x0fffffcc,0x00019df9,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x80000000,0x20332898,0x19828839,
    0x2a651033,0x02a22aaa,0x54018835,0x11502603,0xd00dcc15,0x443ddddd,
    0x1110440a,0x54011111,0x82eebeed,0x7c1f885b,0x32d50992,0x36c6feee,
    0x204a81f7,0x1ff01ee8,0xf88fcdfc,0x4ccb73fd,0x76409999,0x7ffc3fe0,
    0x501fffff,0x0791f73f,0x7a9360b7,0x85b94d6e,0x45f441f9,0x2eeb6e1f,
    0x906abc85,0x8fc57c3f,0x45fbf35b,0x80999999,0x0003fa19,0xa656ed50,
    0x2cceecc9,0x5aa4d9ea,0x3f88996d,0xd307df30,0x16cd107f,0x3e2be3d4,
    0xee835100,0x0001eeee,0xaddaa000,0x9dd9934c,0x1f8af859,0x1ecf75e2,
    0x81fd0136,0x6c2dddd9,0x7e443e62,0x00000202,0x54000000,0x2e132b76,
    0x21af7205,0x21ecbcaf,0x36f6406c,0x10a2e62a,0x00054410,0x00033332,
    0x54000000,0x2e132b76,0x20bbe605,0x50ff8aee,0x44fd401f,0x0003984e,
    0x66664000,0x00000000,0x656ed500,0x3f403984,0xfd9fa7d8,0x7f10ffff,
    0x000017cc,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__consolas_15_usascii_x[95]={ 0,3,1,0,0,0,0,3,2,1,1,0,1,1,
2,0,0,0,1,1,0,1,0,0,0,0,3,1,1,0,1,2,0,0,1,0,0,1,1,0,0,1,1,1,
1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,2,1,2,0,0,0,0,1,1,0,0,0,0,1,1,
0,1,1,0,1,0,1,0,1,1,0,1,0,0,0,0,1,1,3,1,0, };
static signed short stb__consolas_15_usascii_y[95]={ 11,0,0,1,0,0,0,0,0,0,0,3,8,6,
8,0,1,1,1,1,1,1,1,1,1,1,3,3,2,5,2,0,0,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,12,0,3,0,3,0,3,0,3,0,0,
0,0,0,3,3,3,3,3,3,3,1,3,3,3,3,3,3,0,-1,0,5, };
static unsigned short stb__consolas_15_usascii_w[95]={ 0,3,6,8,8,9,9,2,5,6,7,8,5,6,
4,8,8,8,7,7,8,7,8,8,8,8,3,5,6,8,7,5,9,9,7,8,8,6,6,8,8,6,6,7,
7,8,8,8,7,9,7,8,8,8,9,8,9,9,8,5,7,4,8,9,5,8,7,6,8,8,8,8,7,7,
7,7,7,8,7,8,7,8,7,6,8,7,8,8,8,8,7,6,2,7,8, };
static unsigned short stb__consolas_15_usascii_h[95]={ 0,12,5,10,13,12,12,5,15,15,7,8,6,2,
4,13,11,10,10,11,10,11,11,10,11,10,9,11,10,4,10,12,15,10,10,11,10,10,10,11,10,10,11,10,
10,10,10,11,10,13,10,11,10,11,10,10,10,10,10,15,13,15,6,3,4,9,12,9,12,9,11,12,11,11,
15,11,11,8,8,9,12,12,8,9,11,9,8,8,8,12,8,15,16,15,4, };
static unsigned short stb__consolas_15_usascii_s[95]={ 97,97,77,110,61,16,118,125,34,12,54,
10,71,84,108,70,119,10,105,68,11,111,1,37,10,44,123,19,53,93,28,
1,46,1,119,25,101,94,87,59,70,63,43,46,36,28,19,102,20,87,79,
34,54,50,113,1,85,95,76,40,79,56,62,113,102,60,110,78,34,69,68,
43,60,85,19,52,77,1,117,85,26,101,109,94,93,101,19,28,45,7,37,
27,1,4,84, };
static unsigned short stb__consolas_15_usascii_t[95]={ 14,1,65,43,1,18,1,54,1,1,65,
65,65,70,65,1,18,43,31,31,54,18,31,43,31,54,31,31,54,65,54,
18,1,54,43,31,43,43,43,31,43,43,31,43,54,43,43,18,54,1,43,
31,43,31,31,43,31,31,31,1,1,1,65,65,65,54,1,54,18,54,18,
18,18,18,1,18,18,65,54,54,18,1,54,54,18,54,65,65,65,18,65,
1,1,1,65, };
static unsigned short stb__consolas_15_usascii_a[95]={ 132,132,132,132,132,132,132,132,
132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,
132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,
132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,
132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,
132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,
132,132,132,132,132,132,132, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_consolas_15_usascii_BITMAP_HEIGHT or STB_FONT_consolas_15_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_consolas_15_usascii(stb_fontchar font[STB_FONT_consolas_15_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_consolas_15_usascii_BITMAP_HEIGHT][STB_FONT_consolas_15_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__consolas_15_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_consolas_15_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_consolas_15_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_consolas_15_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_consolas_15_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_consolas_15_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__consolas_15_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__consolas_15_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__consolas_15_usascii_s[i] + stb__consolas_15_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__consolas_15_usascii_t[i] + stb__consolas_15_usascii_h[i]) * recip_height;
            font[i].x0 = stb__consolas_15_usascii_x[i];
            font[i].y0 = stb__consolas_15_usascii_y[i];
            font[i].x1 = stb__consolas_15_usascii_x[i] + stb__consolas_15_usascii_w[i];
            font[i].y1 = stb__consolas_15_usascii_y[i] + stb__consolas_15_usascii_h[i];
            font[i].advance_int = (stb__consolas_15_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__consolas_15_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__consolas_15_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__consolas_15_usascii_s[i] + stb__consolas_15_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__consolas_15_usascii_t[i] + stb__consolas_15_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__consolas_15_usascii_x[i] - 0.5f;
            font[i].y0f = stb__consolas_15_usascii_y[i] - 0.5f;
            font[i].x1f = stb__consolas_15_usascii_x[i] + stb__consolas_15_usascii_w[i] + 0.5f;
            font[i].y1f = stb__consolas_15_usascii_y[i] + stb__consolas_15_usascii_h[i] + 0.5f;
            font[i].advance = stb__consolas_15_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_consolas_15_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_consolas_15_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_consolas_15_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_consolas_15_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_consolas_15_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_consolas_15_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_consolas_15_usascii_LINE_SPACING
#endif

