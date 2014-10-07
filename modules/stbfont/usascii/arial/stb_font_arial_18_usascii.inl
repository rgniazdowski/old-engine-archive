// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_18_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_18_usascii'.
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

#define STB_FONT_arial_18_usascii_BITMAP_WIDTH         128
#define STB_FONT_arial_18_usascii_BITMAP_HEIGHT         94
#define STB_FONT_arial_18_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_arial_18_usascii_FIRST_CHAR            32
#define STB_FONT_arial_18_usascii_NUM_CHARS             95

#define STB_FONT_arial_18_usascii_LINE_SPACING          12

static unsigned int stb__arial_18_usascii_pixels[]={
    0xa83973a8,0x9952dc44,0x19971c83,0xdb88006c,0x007000ab,0x50298298,
    0x54401799,0x7315298b,0x0b11c805,0x2e3ed43a,0xf9527e45,0x19dd3f85,
    0x3fb20254,0x204fecbd,0x5a81dfda,0x313a07d4,0x09fd9dfd,0x2bbfbdf3,
    0x00ffdfdf,0x12e1aa1f,0x3a2dc3f1,0xd0985f03,0x75c07a07,0xf509d101,
    0x5c81f9d7,0x43f11fc4,0x1fd41df8,0xff5f997a,0x93cc2f41,0x1f81f889,
    0x3e05d16e,0x703e8542,0x5541d50b,0x744e8988,0xee997ad3,0xc8d73642,
    0x223f700f,0x45faf42f,0x5d9550fb,0x835c3bd5,0x05f16e2f,0x0fa7f0be,
    0x21f30fc4,0x36ceeef9,0x90697c4d,0x87cc1dff,0xf1027c3e,0x2b903ea5,
    0xec8fcc3f,0x24efeeef,0x2dc5d05c,0x3e17c0be,0x717c07d3,0x4fc8fe2b,
    0x068de83e,0x7cdf4172,0x9d00fe20,0x3eb907e2,0x4ba07d43,0xb904d878,
    0x7c0f52dc,0x203e9fc2,0x2364f63e,0xf98ba2f9,0x05c80bff,0x2f88b9d7,
    0xe87d2f40,0xf87c8bf5,0x407f0d50,0x07eeb76d,0x3e9fc2f8,0x7d1f9760,
    0x203e1f98,0x2e41fffa,0x3f82ff88,0x15d71fc0,0x22ffebf9,0x2beea3fa,
    0x0fa1adda,0xd55ba7cc,0x4fe17c07,0x7c53603e,0x53dc2f88,0x236c740f,
    0x6c1f605c,0xd507e605,0x3b3ebbbf,0x77f643ff,0x1764eefe,0x7c4b71ec,
    0xd3f85f00,0x25d1fc07,0x2f8af44e,0x41f568a2,0x5413605c,0x206d882f,
    0x004feb90,0x35c0fc79,0x3f16e2f8,0x3a7f0be0,0xa643f103,0xbefe9afc,
    0x7697cc4e,0xf981ec8d,0x26fbee00,0x5c800efc,0x225d007f,0x87e0f307,
    0x2f817c5b,0xf303e9fc,0xefc87541,0x4112efb9,0x43e9e9ee,0x7ff11ff9,
    0x9dffb500,0x1fd72001,0x205a87c0,0x16e1f82e,0x7f0be05d,0x6c2640fa,
    0x21fb800e,0x003fffe8,0x0020006a,0x4004c220,0x46a80221,0x9d16e0f9,
    0xd1f88be0,0xd101f107,0xfca8837f,0x0000d102,0x00000000,0x2e5b0000,
    0x3ea2dc6f,0x7e4bff66,0x643ffd0e,0x77ff5403,0x1c00cffe,0x00000000,
    0x40000000,0x03305318,0x984cc453,0x00a0cc42,0x00013530,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x50000000,0x88095039,
    0x2ba800bb,0x00acb980,0x006e6072,0x8802b2e6,0x9950512a,0x015cc037,
    0x03730750,0x1e83d5b7,0x03f73e60,0x07fe7ec4,0x7feeff44,0x7f4c1f02,
    0xdff105fd,0xff307ff9,0x7f44dbdb,0xfe83ffde,0x4b9005fd,0x745fdef8,
    0x202dc972,0x7dc0fa5d,0x1bd11360,0x234c0fc8,0x887d10ec,0x21fdc1de,
    0xfb9be65e,0x1d907e40,0x97200fe6,0x1f8be25d,0x3600f4b5,0x0fe05f16,
    0x880fc853,0x0be2643e,0x3206d8d9,0x6e85f30f,0xf8ba2176,0x5d443643,
    0x9d06e5c8,0x0b73c96c,0x20bdbf30,0xd00a89f8,0x261e8009,0x0fa3d41f,
    0x70f52f88,0x10057dcd,0x7cc7a83f,0x2a05efdf,0x43b7a62f,0x0bfd000f,
    0x6ff7dfcc,0xf1001fc0,0x10fd87d0,0xf34f805f,0x7fec6c83,0x207cc1bd,
    0xf997a0fa,0x303fe985,0x982b8a5c,0x4151fdee,0x49d31efa,0x16a003f8,
    0x3fb26fee,0x4e803f30,0x710df0fe,0x07cc9ffd,0x217cc3e6,0x2fdb985e,
    0x2fe23e20,0x3fd2f45c,0x2e1fcc5f,0x790027c7,0x1e77faa0,0x323f807f,
    0x406fd9bf,0x83f33fb8,0xb903ea7a,0x52e06d80,0x3e21f16a,0xf11bfe22,
    0x1760fa83,0x4003e4e8,0xf302f47a,0x5caeec85,0x45b603d1,0x1f53541f,
    0x3ea025c8,0x4b70f880,0xfb87f11f,0x23e43e85,0x31fa83fa,0x8bb0b60d,
    0x3a7722fa,0x9d2640c6,0x6c4e9360,0x2bf0fe25,0xc83643f8,0x323c5a64,
    0x5fefa8bf,0x83fa97dc,0x5fc99cfc,0x44f6412e,0xaefb80fb,0x1f41ffe9,
    0x56fd47f3,0x3ea1fda9,0x7641fc8b,0x3b25fc8a,0xf882fb89,0x221f6f40,
    0x1f53fffd,0x204fffb8,0x20bdffdb,0xbff9102d,0x77fedc03,0x3fea2edc,
    0xffea84fe,0xefda81ef,0xb9dff902,0x816ff5c4,0x08013018,0x10002008,
    0x00040060,0x13307502,0x00200100,0x00004004,0x00000000,0x00000000,
    0x00000000,0x03900000,0x0aaaaaa0,0x402ccb98,0x103b81b9,0x0d9d4039,
    0x999136a0,0x2e199999,0x64472204,0x0ee19302,0xf92a0b26,0xffff8803,
    0xcdfe885f,0x7f440efd,0x882ec6fd,0x1e5b602f,0x7743dfa8,0x31ffeeee,
    0xf91ba09f,0x1ee4f881,0xf9761bf2,0x800f9803,0x237440ed,0x5d8be26b,
    0xb6c05f10,0x400d905a,0x20fe45f9,0x237441fb,0x3a0fcc5e,0x7f1fc0fc,
    0x01ae02aa,0x07cc03ee,0x1765d89b,0x2db017c4,0x0aeda878,0x6e837440,
    0x9fcc0fe2,0x223f80fc,0x87e62f9f,0x41efdedf,0xbb02b9cd,0xf30fb800,
    0x2f882ec7,0x6c2e9b60,0x7ec02eff,0x1b67f300,0x205f7f70,0x72edaa5d,
    0xbd11ff8d,0x1efdefe8,0x7e40027c,0x882ec3fe,0x4b9b602f,0x1fc806c8,
    0x007dfe40,0x4d7027f4,0x226cf54d,0x7907dc5f,0x87f12f44,0x2a2eeee9,
    0x361edbdf,0x6c05f105,0x01b21a66,0x3fa007f5,0x40bfd003,0x3e25f0f9,
    0x4c3f85f1,0xd07dc01f,0x3faaa88b,0x36cdb13e,0x1b601f98,0x2606c81f,
    0x01ee005f,0xf017dfe4,0x4df41f35,0x3ea1fc0f,0xc83e6020,0x1f99fc06,
    0x507b87cc,0x8bb0a21f,0xe883642d,0x403dc006,0x201fb2fa,0x5ee45bcd,
    0x13e44f86,0x7cc6c87f,0x17c7f104,0xc81fa9ae,0x44e83e67,0xfd83645a,
    0x203dc000,0x41be25f8,0x6f543dea,0xfb8cff83,0x7dc4f643,0xa9bdfa83,
    0x47b21ffc,0x4dff43ea,0x4e7c2fdb,0x323c42fb,0xaaacfb86,0x0f700aaa,
    0x1fcc0ed8,0x7fc0ffc4,0x2efcaf81,0x03ffeb88,0x33bffb66,0x1f7f5c40,
    0x1f7ffec4,0xe81fff54,0x3ff21b21,0x03ffffff,0x80fdc0f7,0xb07e81fc,
    0x0200100f,0x00400100,0x88010008,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x20000000,0x1c96403b,0x333332a0,0x2e392ccc,
    0x81abcccc,0x3332e01c,0x971c82ac,0x165c3220,0x00ae1990,0x4c32e057,
    0x522032a4,0x23f500fb,0x3bbae03f,0x7f2eeeff,0x3fbbbbf6,0xfb01fc3f,
    0x41ffdddd,0xf107fb3f,0x7cc1bfa3,0x5e80bd1f,0xc9ee2fc8,0x7f17d80f,
    0x003f9b60,0x4176017a,0xd80fe0fc,0x4fe5f985,0x8fc40ffd,0xfeb80fee,
    0x45e80bd1,0xf93dc2fc,0xdb3ff441,0xa9fc7f10,0x5417a00b,0x8be60bb1,
    0x2ec6a23f,0x6ecfe7c8,0xce8fc46e,0xd1fce83e,0x3f25e80b,0x43f27b82,
    0x3ea7bdf9,0xdbf07d40,0x17a03ffb,0xf505d9fc,0x25e89fc1,0x9fcbb05d,
    0x3e23f9dd,0xf98d79d1,0xe80bd1f9,0x9ee05f95,0x23d4a27b,0x3fe2743f,
    0x82f413a0,0x7555db3f,0xe8bf89f9,0x3ee62ec5,0xfcaecfe2,0x273a3f10,
    0x47e7320f,0x7e6f405e,0x07b9ee06,0x3e26c8f5,0x41b227c1,0x3f67f05e,
    0xf81dffee,0xfffd85ec,0xd9fc4fff,0xe8fc5ba5,0x7ccf47d4,0xffe80bd1,
    0x54f704fb,0x1f98f506,0x6c87f0d7,0x6cfe0bd0,0x7fc0fe45,0x5576c0ef,
    0xbb3f809a,0xe8fc5fcc,0x7cde6d74,0x1fe80bd1,0x4cf705f7,0x29d0f506,
    0x3643f83e,0x367f05e8,0x6fc0fd85,0x802ec4f8,0xafc8bb3f,0x23e69d1f,
    0x17a3f34c,0x40fd8bd0,0x3d41667b,0x7c07cf5c,0x05e83643,0x3e21767f,
    0x22fa9fc6,0x367f005d,0x9d1fee85,0x1f98fdf4,0x445e80bd,0x4023dc6f,
    0x05ef887a,0xbd06c87f,0xb82ecfe0,0x0ed8fe3f,0x6cfe00bb,0x9d1ff985,
    0x23f337dc,0x0aaaaaee,0x5c9f50bd,0x83d412a7,0xc87f01fc,0x4fe0bd06,
    0x7c3f605d,0x02ed3e23,0x320bb3f8,0x1fc49d1f,0x3fffa3f3,0x20bd2fff,
    0x3e4f72fc,0x000007a8,0x00000000,0x00000000,0x00000000,0xc881d400,
    0x99999951,0x666665c9,0x799972cc,0x55551035,0x332e1555,0xca800abc,
    0x201b9800,0x55002ca8,0x5302a298,0x360aba88,0x3f25f106,0xb0eeeeee,
    0x7ddddddf,0x3ffbbbf6,0x3fffe60d,0xddfd1fff,0xff805ffd,0x3f7fe603,
    0x75f7cc0e,0x913e601f,0xa9721fcf,0xdb2ffdef,0x0364be20,0x42ec02ec,
    0x25e804fa,0x2a07c85e,0xd17206bf,0x82ec5d89,0xf0c44fe8,0xd13a5c87,
    0x97c41b6b,0x805d806c,0x403f505d,0x2617a0ec,0x3f1bb01f,0x27b85b10,
    0xc83d41d8,0x21fc04dc,0x2db1025c,0x325f106d,0xd805d806,0x2607f105,
    0x3dc2f41f,0x00bd2f88,0x436c036c,0x7c04d8ea,0xfb712e43,0x3bbf6dff,
    0xf92feeee,0x6c199999,0x0ccccccf,0xe827c0bb,0xedccee85,0x7dcf701f,
    0x403f9800,0xd8fc41fc,0x5721fc04,0x2d91bee8,0xdcccccfd,0xddddf92f,
    0x7777ec3d,0x40bb0eee,0xe82f985e,0x04fedcce,0x201fc49d,0x0fdc05f9,
    0xf809b26c,0x40faaf43,0x3e20db6e,0x0bb00d92,0x427c0bb0,0xf30bd06c,
    0xeeeef987,0x013ea06f,0xd8d705f1,0x13fb2544,0x44fe2bf9,0x220db6fc,
    0xbb00d92f,0x3e60bb00,0x0bd03f83,0x999d91b6,0x9f503fb9,0xfb01f300,
    0x21ffffff,0x33ffa27c,0x33ffae5b,0xf106d8fa,0x17601b25,0x43ec1760,
    0x20bd01f9,0x5e81fc5e,0x03001fd4,0x37a66662,0x04004341,0x25f106d8,
    0xaaed806c,0x5db2aaaa,0x505fd755,0x2abba01f,0x3ea1fdba,0x3e21f900,
    0x302aaaae,0x51360019,0x6d800009,0x01b25f10,0x3ffffff6,0xdffffb6f,
    0xe81ae03b,0x41deffff,0x54fe205d,0x0fffffff,0x9b001fa8,0x00000008,
    0x00000000,0x00000000,0x00000000,0xa8000000,0x06e601ab,0x5c400b98,
    0x0bb88a80,0x442ae22a,0x85d4541b,0x541a8028,0xaaa88541,0x30330aaa,
    0x03502a65,0xddfd802a,0x7eff443f,0x6feff4c6,0x6fefec40,0x3fbbf3e0,
    0x5dfbf9f1,0x7e7cdfbf,0x017df12f,0x225f8976,0xddddd31f,0x4fa1ee5f,
    0x403f24f8,0x5c3f102f,0x2f886f46,0x2274437a,0xff97625e,0x987fd7a0,
    0x3e1f30ff,0x7f5c408f,0xff53d41c,0x49d103d4,0xa83e62f8,0x3e02f9af,
    0x203bf102,0xf98443f8,0x85f335c2,0x6c8bf0fa,0x97c4f89f,0xdfda804f,
    0x3f323f11,0x42f409b1,0x3b21725d,0xcfaaa84e,0x7ffd41aa,0xa803e60c,
    0xfa8fcc0f,0xf1ffffff,0xf87f6c87,0x003f97c3,0xfa6c7f91,0x3603f3d9,
    0x5f0fa80e,0x3fe21fe0,0x303fffff,0x07e61fd9,0x8fcc0fa8,0x19999afa,
    0x0fed90fe,0x07f2f87f,0x5c2efd98,0x0f3b779e,0xaaf803f2,0x03ffa80f,
    0x4449817c,0x4d87f12f,0x227c87f3,0x3f864c3f,0x1fc3fb64,0xeb81fcbe,
    0xb9f101cf,0x3ee173e6,0x426ee401,0x201fbbf8,0x2233e02f,0x22bb20fb,
    0x22bb61fa,0x997e44fb,0x2d90fe4f,0x4be1fc3f,0x00bf883f,0x0bfe3fe8,
    0x133339f5,0x6d81ff98,0x202f81b6,0xa81fffda,0xfea82efe,0x9dfb504f,
    0x3fb643f8,0x1fcbe1fc,0xb0fe4000,0xffffc81f,0xb86e85ff,0x4c13e20f,
    0x01001000,0x00020010,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00530000,0x440b6062,0x40888888,0x1712543a,
    0x2c8ea2e2,0x388676d4,0xddddddd3,0xea92a1dd,0x000005ee,0x407b8000,
    0x37d43fda,0xfffffff8,0x23175313,0x7cc7e67b,0x4c3ea7c9,0x4ffffdce,
    0x26666666,0xbb99ee19,0x0000003b,0xb8818800,0xfbd81cfe,0x99999981,
    0x5dfdd309,0x3e63f32c,0x088d46c9,0x0000b2a2,0x00000000,0x3bf20000,
    0xb71f300b,0x0f744000,0x1f07c475,0x000000b7,0x00000000,0x3e200000,
    0xf8ae401e,0x66666640,0x0966f21c,0x00289c38,0x00000000,0x00000000,
    0x20fbf260,0xbb1361f8,0x005bbbbb,0x00000000,0x00000000,0x20000000,
    0x930cffb8,0x00000498,0x00000000,0x00000000,0x09500000,0x00007b50,
    0x00000000,0x00000000,0x00000000,0x000001ee,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__arial_18_usascii_x[95]={ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,
1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,-1,1,0,1,1,1,0,1,1,0,1,
1,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,-1,0,0,1,0,0,0,0,0,1,1,
-1,1,1,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0, };
static signed short stb__arial_18_usascii_y[95]={ 14,2,2,2,1,2,2,2,2,2,2,4,12,9,
12,2,2,2,2,2,2,2,2,2,2,2,5,5,4,5,4,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,16,2,5,2,5,2,5,2,5,2,2,
2,2,2,5,5,5,5,5,5,5,2,5,5,5,5,5,5,2,2,2,7, };
static unsigned short stb__arial_18_usascii_w[95]={ 0,3,5,9,9,14,11,3,5,5,6,9,3,5,
3,5,9,6,9,9,9,9,9,9,9,9,3,3,9,9,9,9,16,12,9,11,10,9,9,12,10,3,7,10,
8,12,10,12,10,12,11,10,10,10,11,16,11,11,10,4,5,4,8,11,4,9,8,8,8,9,6,8,7,2,
4,7,2,12,7,9,8,8,5,8,5,7,8,12,8,8,8,6,2,5,9, };
static unsigned short stb__arial_18_usascii_h[95]={ 0,12,5,13,15,13,13,5,16,16,6,9,5,2,
2,13,13,12,12,13,12,13,13,12,13,13,9,12,9,6,9,12,16,12,12,13,12,12,12,13,12,12,13,12,
12,12,12,13,12,13,12,13,12,13,12,12,12,12,12,16,13,16,7,2,3,10,13,10,13,10,12,13,12,12,
16,12,12,9,9,10,13,13,9,10,13,10,9,9,9,13,9,16,16,16,3, };
static unsigned short stb__arial_18_usascii_s[95]={ 127,117,49,117,61,1,16,45,1,38,34,
116,41,86,82,50,99,121,76,118,96,10,28,43,33,56,1,106,5,24,66,
86,44,63,53,38,32,22,12,20,1,113,54,102,93,80,69,86,55,66,35,
88,21,43,1,110,98,86,75,33,62,23,15,70,55,118,1,10,109,29,68,
79,13,32,28,47,66,47,39,19,108,99,60,1,71,110,98,76,107,77,89,
16,13,7,60, };
static unsigned short stb__arial_18_usascii_t[95]={ 1,46,83,1,1,18,18,83,1,1,83,
72,83,83,83,18,18,46,59,18,59,32,18,59,32,18,83,59,83,83,72,
59,1,59,59,18,59,59,59,32,59,46,32,46,46,46,46,1,46,18,46,
18,46,32,46,32,32,32,32,1,32,1,83,83,83,59,32,72,18,72,32,
18,46,46,1,46,46,72,72,72,1,1,72,72,1,59,72,72,72,1,72,
1,1,1,83, };
static unsigned short stb__arial_18_usascii_a[95]={ 72,72,92,143,143,229,172,49,
86,86,100,151,72,86,72,72,143,143,143,143,143,143,143,143,
143,143,72,72,151,151,151,143,262,172,172,186,186,172,157,201,
186,72,129,172,143,215,186,201,172,201,186,172,157,186,172,243,
172,172,157,72,72,72,121,143,86,143,143,129,143,143,72,143,
143,57,57,129,57,215,143,143,143,143,86,129,72,143,129,186,
129,129,129,86,67,86,151, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_18_usascii_BITMAP_HEIGHT or STB_FONT_arial_18_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_18_usascii(stb_fontchar font[STB_FONT_arial_18_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_18_usascii_BITMAP_HEIGHT][STB_FONT_arial_18_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_18_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_18_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_18_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_18_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_arial_18_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_18_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_18_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_18_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_18_usascii_s[i] + stb__arial_18_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_18_usascii_t[i] + stb__arial_18_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_18_usascii_x[i];
            font[i].y0 = stb__arial_18_usascii_y[i];
            font[i].x1 = stb__arial_18_usascii_x[i] + stb__arial_18_usascii_w[i];
            font[i].y1 = stb__arial_18_usascii_y[i] + stb__arial_18_usascii_h[i];
            font[i].advance_int = (stb__arial_18_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_18_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_18_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_18_usascii_s[i] + stb__arial_18_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_18_usascii_t[i] + stb__arial_18_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_18_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_18_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_18_usascii_x[i] + stb__arial_18_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_18_usascii_y[i] + stb__arial_18_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_18_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_18_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_18_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_18_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_18_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_18_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_18_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_18_usascii_LINE_SPACING
#endif

