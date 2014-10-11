// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_times_23_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_times_23_usascii'.
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

#define STB_FONT_times_23_usascii_BITMAP_WIDTH         256
#define STB_FONT_times_23_usascii_BITMAP_HEIGHT         76
#define STB_FONT_times_23_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_times_23_usascii_FIRST_CHAR            32
#define STB_FONT_times_23_usascii_NUM_CHARS             95

#define STB_FONT_times_23_usascii_LINE_SPACING          15

static unsigned int stb__times_23_usascii_pixels[]={
    0x22008801,0x40200401,0x22000019,0x0000001a,0x0000aa00,0x00000000,
    0x00000000,0x40000000,0x05400001,0x44050000,0x202a600b,0x4405503a,
    0x74cff00c,0x5d401fee,0x02bb99bc,0x3bddb930,0x83bbbe60,0x00beeeb8,
    0x07777766,0x32aa0fd4,0xbdb900ce,0x406c5801,0x16200ccc,0x016eed40,
    0x8019bb50,0xbbb71039,0xfeb87359,0xbcc88000,0x06c40190,0x70750b30,
    0x2a02cc07,0x2203f302,0x2015402e,0x41fd41eb,0xa9f881f9,0x3d904d9a,
    0x4fc83f98,0x445f88ea,0x4c03f23e,0x7bae4344,0x3e600360,0x9a600f11,
    0x203200eb,0x3f260afa,0x4000fc84,0x403a82ea,0x2a0fc059,0x1d101e83,
    0x40fcc000,0x055001f9,0x27dc07f2,0x556e07e6,0x03f90932,0x47f913e6,
    0xf507ec3e,0x45504f88,0x3f33f858,0x1f600570,0x43f8803d,0x3ea1603e,
    0x3ee13603,0x803ee000,0xf102d805,0x17cc3a87,0x4c0005c8,0x0017c41f,
    0x80bf302e,0x207e61fe,0x261c557e,0x70ff405f,0x3ee2f45f,0x03f61761,
    0x7cc3a872,0x04987f12,0x80799fa0,0x407ec0fc,0x202fcc39,0x000fb858,
    0x00c805f3,0x1fcc07dc,0x107f10ea,0x2071005f,0xa81ec1f9,0x8330c9ac,
    0x2fe402fd,0x59f903f3,0x2017ec05,0x887ea5fb,0x6f887ec1,0xd5531fb8,
    0x4459b557,0x0d85f12f,0x362bf600,0xfc87d802,0x1fdc0c82,0x447dc0c0,
    0x201ba02a,0x417cc039,0x7c1d42fa,0x2200fb84,0x83f306fc,0x1fa65b07,
    0x5c01ff87,0x2207e66f,0x3fe02efe,0xf33fd401,0x3e1fc403,0xa99fdc0f,
    0x2beaaaeb,0x0e47a9f4,0x437bea00,0x37c2ded8,0x6c2c1fdc,0x3f70002f,
    0xfb85dffd,0x0b00bb8b,0x83f04f88,0x7e82e83a,0x3e60dd00,0x89361661,
    0x1ff1244f,0xf30ff980,0x07ffa203,0xf3003fe2,0xb803e21f,0x7dc2fc85,
    0x4c1a24c1,0x01263d9e,0xf70bfea0,0xfa86f881,0x0ffc1d44,0x70cfb800,
    0xbacfc8df,0x400c82ff,0x3a87705f,0x007f82c4,0xb87e60dd,0x0be63643,
    0x2007fc49,0x03f30ff8,0x7cc3ffc8,0x07fc400f,0xf980e80f,0x570fd51e,
    0x160602c4,0x9b101797,0x41ec1df7,0x44fa85f8,0x007fcc0c,0x7ec0fb80,
    0x0dd11fa0,0x207f8073,0x15c750b9,0xdd006f88,0x21d87e60,0x263dc2f8,
    0x2600ffc2,0x5007e67f,0x1ff87ff9,0x81a3fcc0,0x33b2201a,0x2b6625f9,
    0x0019cb99,0x45bb5c39,0x453fa4e8,0x3ea1be05,0x0ffc42c2,0x540fb800,
    0x3f21be3f,0x03f40581,0x2b8ea173,0x36c01be0,0xf71e1f98,0x6c0b8bf0,
    0x337d402f,0xe8aa803f,0x2a017f47,0x0070245f,0x3f2a3fb8,0x04cdeccc,
    0xf9a7c4a8,0xff983f21,0x21f600d9,0x7c0ea1fb,0x1f70003f,0x21be4f88,
    0x200c83fb,0x3a87706f,0x007e82cc,0xd87e60db,0x47f71760,0x404fb848,
    0x207e62fc,0x70fdcaa1,0x42fc809f,0xbd000a00,0x2001b160,0xf89fc458,
    0x3ff21fe3,0x3207dc03,0x5fb80647,0x40fb8080,0x261f62fa,0xf103981f,
    0x07507e0b,0x200f903d,0x5c3f306d,0x1fba97a2,0x807ec032,0x40fcc5f8,
    0x743d4aa5,0x00bf100f,0x98364000,0x83b00344,0x225f13f8,0x0efe81ff,
    0x742f9862,0x0bfe02c4,0x40fb8288,0x707ea0fc,0x3f982c0d,0x41d41f98,
    0x800fb84f,0x4c3f306d,0x26777f24,0x8511d9af,0x6ec40de8,0x9740fcc0,
    0xbd107b2a,0x540de881,0x801ea81e,0x445700ec,0x3a075004,0x77ec1f54,
    0x7dfd9b12,0x354b9095,0x5fd100ea,0x8bee0730,0x746d82e8,0x3ea07203,
    0x1d43f980,0x0be213e2,0x0fcc1b60,0x2e0bb89a,0x9d70241c,0x3e607d95,
    0xcccefc81,0x65e76402,0x705f703e,0x2eee607f,0x03a83200,0x23a60588,
    0x7ffec44d,0x0bbff61e,0x360ede64,0xdfec8800,0x3f2203cc,0xb9101cbc,
    0x839807b7,0xa87f104e,0x4b817cc3,0x3f305d80,0x398003b8,0x01ffec40,
    0x15c403f3,0x20026200,0x00080200,0x15001102,0x4c01b980,0x11003100,
    0x06200020,0x08002600,0x80d30200,0x0f41d41f,0x04e801d0,0x007703f3,
    0xff900254,0x3007e603,0x00000003,0x00000000,0x00000000,0x00000000,
    0x00000000,0x50d3006c,0x2cc07707,0xf301e8a2,0x2e00ee03,0x1fd98003,
    0x00001f98,0x00000000,0x00000000,0x00000000,0x00000000,0x19100000,
    0x1d405cc0,0xb8e202a8,0x66443adf,0x332a01fd,0x00cba99b,0x31e64c00,
    0x554199bf,0xaaaaaaaa,0x00000001,0x00000000,0x00000000,0x00000000,
    0x01000000,0x00620088,0x80a60801,0x22001999,0x000009aa,0x5c199980,
    0xbbbbbbbb,0x0000001b,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00001440,0x00260151,0x4c402ea0,
    0x00662099,0x88001300,0x1985eeed,0x42a00000,0xceeda82a,0x0bdeeb88,
    0x6d477b66,0xed982dee,0x7bddb52e,0x005bdb70,0x20000144,0x9cedddb8,
    0x57bdb504,0x1cccb887,0x306fc880,0xbc803bf9,0x0bfaa3fd,0xfe98db80,
    0x10ffa66f,0xa8d9007d,0x7dc002fe,0x07e83fff,0x7fd40160,0x4c2fffd9,
    0x82fe40ff,0x17fc40f9,0xff885f10,0x2a03ea01,0x41bf220e,0x9802dfb8,
    0x437dc43f,0x87f910cd,0x4003e22e,0xfbbd886f,0x36c7b03f,0x7c400bee,
    0x3ea07ee2,0x6fa80683,0x22002fa8,0x20055005,0xbf7001fa,0xfb03fee3,
    0x9507f883,0x59813f20,0x34401ff0,0x3e03ff22,0xffddf886,0x980fe605,
    0x1e407cc7,0x2009b0f3,0x3e20b86e,0x5402f886,0x43f7002f,0xa8fd04f9,
    0x4376c403,0x0ae002fa,0x17fa0000,0x3fa0fdc0,0x7f427d43,0xdf101d81,
    0x07e81640,0x80fc82c4,0x3a20b86e,0x807e881f,0x1cc07e45,0x005d81f7,
    0x217a00db,0x17cc01f9,0x3e23fb80,0x0747f502,0x261ba360,0x3bfe002f,
    0xdb300003,0x83f7001f,0x43fc44fc,0x6c0684fc,0x3f40d02f,0x07e41620,
    0x7d414374,0x0805fb84,0x30c077dc,0x880fc4df,0xd006d8ba,0x09afb983,
    0x06e65f30,0x80f72f44,0x3b80936e,0x4c5f30dd,0x7fecc199,0x007300ef,
    0x7007f739,0xd84f983f,0x2a37f41f,0x542fd403,0xb101fa03,0x1ba03f20,
    0x7f41fc40,0xffe88003,0x6cf7e403,0xfb15d501,0xa887500d,0xf301acfc,
    0x203fdb95,0x400bbde8,0x2201cafa,0x8be61ba5,0x3a600afb,0x037e446f,
    0x4037c5a2,0x41fcc1fb,0x3f72a4fa,0x3fa00361,0x0fd00741,0x01f90588,
    0x07e600dd,0x665403fe,0x3ffa22cc,0x0bff201e,0x0df10fc4,0x54077e4c,
    0x86fcc01f,0x001b05f8,0x0d80ddd0,0x44be61ba,0x0ff6000d,0x6c5701be,
    0x20fdc02f,0x6cff00fc,0x00d14fa9,0x405993ee,0xc82c407e,0x7006e80f,
    0x401ff309,0xff703ff8,0x3ff6e09f,0x06e87b81,0x503ffaa2,0x42f9803f,
    0xaabfa85e,0x03fb801a,0xf30dd0b2,0x88001b35,0x3406e84f,0x7f7017e6,
    0x4bf204e8,0x801d5fe6,0x80390ff8,0xc82c407e,0x8806e80f,0x805ff106,
    0x3f2201fe,0xffaa5c5f,0x036c2741,0x0fd42fc8,0x0dd0be60,0xdfffffd1,
    0x9300f803,0xf9f30dd0,0x21760003,0x2ab6a06e,0x2e00ffaa,0x404ebcdf,
    0x3f63adf9,0x3f2000da,0x0fe8068b,0x07e41260,0x00ec0374,0x0fe809fd,
    0x987fd402,0xf997ea0f,0xf1006d85,0x4c01fa89,0xa443742f,0x205ba998,
    0x3fff2049,0x264fffff,0x8000efbf,0x3606e83d,0x4fcaaaab,0x02627ee0,
    0xf506ffc0,0xef8800bb,0x01fd803b,0x407e40ea,0x2015c06e,0x07f406fa,
    0x64bf2019,0xff10fc86,0x0f400db0,0x5f3007ea,0x100e86e8,0x5300ec07,
    0x35dd5555,0x02fcd7cc,0x1ba03e20,0x07f882cc,0x320007ee,0x003ff86f,
    0xb800ffd8,0x640b603f,0x2a06e80f,0x409fd003,0x5c0b20fe,0xb1aa1ee7,
    0x1007d83f,0x9803f50d,0x3e63742f,0x7106440c,0x3a000975,0x9f72f986,
    0x16cc3320,0x403b06e8,0x03f703fc,0xf907f300,0x09f50001,0x2640fec0,
    0x0dd01f90,0x6c0620ea,0x641fd03f,0x3e23e81f,0x3bea1642,0x5c11ff52,
    0x3ee0b622,0x3a17d403,0xfeffeb87,0x037fcc1e,0x7f50dd00,0x7fe417ec,
    0x21ba00de,0x07fd4079,0xe8001fec,0x20005980,0x3b22001e,0x6403edcd,
    0xfa86e80f,0x00eccccc,0x3aeb3baa,0x6776642d,0xace983dd,0x7ffd502b,
    0x77f417fb,0xefeb81dd,0xaefe980b,0x880bffb8,0x006a01aa,0xfea8dd00,
    0x039ff92e,0xbffb8803,0x3039fd50,0x5545dffb,0x018002aa,0x00180006,
    0x71002620,0x3ee25bff,0xffff50bf,0x4400bfff,0x09882019,0x11000880,
    0x00018802,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x20000000,0x5028aba8,0x2e27bddb,0x3b6e04ee,
    0x77776c1d,0xddd932ee,0xed98379b,0x7bdb002e,0x0e77764c,0x2f7bb260,
    0x819ddb30,0xccdeeec9,0x6f764c02,0x9ddb710b,0x777774c3,0x3264eeee,
    0xeeeeeeee,0xddddd933,0xec98dddd,0x0accdeee,0x7764c080,0x881ccdee,
    0xeeeeeeee,0x3bb666ee,0x3bb222de,0x26faa00c,0x3fe206fd,0x203ff980,
    0xffffa87a,0x57f40fff,0xfe83fe98,0x01ffa806,0xfe8007fd,0x7402fc82,
    0x01df932f,0xbf702fe8,0xf9813d50,0x4c1fe80f,0x4c17ec4d,0x30bfe80e,
    0x15403ff7,0xf9512fe8,0x4ccf4c19,0x0fa99bfd,0x3f81ffdc,0xf81f34e8,
    0xf903fc06,0x3616203f,0x1fd86a81,0xffb07fa2,0x00ffe803,0xfd8005f9,
    0x6c0074c1,0x2027ec1f,0x09f501fd,0x40bfa035,0xfc8901fd,0x3fb01702,
    0xd105fd10,0x3607f605,0x5f906a3f,0x86fc80b8,0xdd5f884b,0x07f80dd0,
    0x2203ff72,0x83c80c45,0x227e41fd,0x32a05fbd,0x05f900fe,0x3a61fd80,
    0xa83f9000,0x80fe407f,0xf90184fa,0x080fec09,0x320017e4,0x43ff101f,
    0x6409bfe8,0x026f981f,0x6c010bf2,0xcf816a3f,0x406d83f8,0x3f2b207f,
    0x3e005886,0x7e41fd80,0x80ff4ec4,0xf900fe9d,0x31fd8005,0x0fe4001d,
    0x3f901bee,0x4c013ea0,0x07f600ef,0x060bf203,0x3f201fc8,0x06b3f2a3,
    0x0df303f9,0x22002fc8,0x200e89ff,0x6d83f9be,0x25903fc0,0x802c45fd,
    0xf83fb06a,0x27d46c1f,0x900feacc,0x9fd8005f,0x7e4000e9,0x3201ff41,
    0x009f501f,0xfd803ff1,0x82fc82c1,0xa807f205,0xc817d45f,0x403fd81f,
    0x7d4002fc,0x44e401ee,0x7c06d86f,0x7f44b207,0x1e401623,0xdf911fd8,
    0xb03fa1b0,0x7e403fa3,0x7e7ec002,0x99fc8003,0xfc802eeb,0xfcaaaaac,
    0x804fd804,0x07eccdfd,0xdd999bf9,0xf300fe40,0xf902fa8f,0x05fd9759,
    0xb0005f90,0x3615009f,0x3e03740f,0xff88b207,0x03e00b12,0x1eee6fec,
    0x449f70d8,0x7e403fa6,0x7e7ec002,0x6fe4002f,0x3f2006fc,0xfcaaaaac,
    0x8037d404,0x06a99afd,0xd53337f9,0xf100fe40,0xc817d41f,0xcfdba9cf,
    0x0017e400,0x7000ffdc,0x0dd737ff,0x50b207f8,0x300b11ff,0x800fec0d,
    0x321ff10d,0x7e403fa2,0x54fec002,0x3f2002ff,0x32007f91,0x409f501f,
    0xfb001ff8,0x05f90383,0x300fe407,0x902fa8ff,0x80ff703f,0x6cc002fc,
    0x8ba606fa,0x06d8effb,0x705903fc,0x7900b3df,0xd800fec0,0xd1a2ff20,
    0x00bf201f,0x3fea3fb0,0x743f9002,0x01fc801f,0x1fec09f5,0x0083fb00,
    0x640105f9,0x517ee01f,0x407f205f,0x0bf202fe,0x9fb0e880,0xd820fea0,
    0x59037c06,0x2017bf60,0x007f600f,0x77df106c,0x5f900fe8,0x87f604c0,
    0xfc802ffa,0x9003be61,0x413ea03f,0x360605fb,0x05f9001f,0xd00fe404,
    0x902fa83f,0x813f603f,0x876002fc,0x00101ff8,0x02fc30db,0x02ff4059,
    0x03fb01a6,0x0ff90760,0x0bf201fd,0x541fd848,0x0fec02ff,0x3fb017ee,
    0x3e613ea0,0x3f61600f,0x405f9001,0xf901fd85,0x8519f309,0x1ff881fd,
    0x6400bf20,0x0006fa83,0x3e5f71ba,0xf880f601,0x3a01e405,0x985d002f,
    0xb01ff84f,0xd07b107f,0x09ff705f,0x2fec17ec,0x3ee05fd0,0x7102fe85,
    0x2005fd0b,0xd07902fd,0x03fd883f,0x07fa17f6,0xfd809fb3,0x3a06c803,
    0xff88005f,0x40f3fe60,0x300befc9,0x9300f80b,0x26017dff,0x506c3efc,
    0x64c7dffb,0xffeeffff,0x3bff261f,0xdfffb10b,0x3bff2619,0x8fbfa20b,
    0x10beffc9,0x3237fff7,0xeeeeeeff,0x3ff263ff,0xff7300be,0x3ffddddf,
    0x777ffe4c,0x40800cdd,0xeeefffc9,0x3f2602ce,0xfea80bef,0xefffb83f,
    0x55551002,0x40000181,0x00000c00,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x80000000,0xb83deeda,
    0xdd732dee,0x200dc19d,0x5c400009,0x5dc406a1,0x229bb880,0x02662199,
    0x99880057,0x4c133311,0x41333109,0x15730198,0x4402b980,0x226a01ba,
    0x3731a81b,0x26133310,0x2e635019,0x4402ea21,0x80999999,0x10000018,
    0x7409ff30,0x444fc80d,0x000e406f,0x3e22dc98,0x3fa9db87,0x893a6326,
    0x8bf511fd,0x9800beb8,0x1bf912fe,0x4fd897d4,0x2be61744,0x39900fd9,
    0x53b507f9,0x57f541df,0x2bfaa7fd,0x6441ffec,0xa85f70ff,0xbffdcafe,
    0xe80ffdd8,0x84fdaaac,0x702c807b,0x5427cc5d,0x201d106f,0x402b83fb,
    0x66d4001c,0x47a85701,0x24c5b0fd,0x40bd07ea,0x7d401cea,0x87513e22,
    0x6d8584f9,0xb16a0fea,0x3e20fa8f,0x0cc6fd45,0x2fc4b7ea,0x203b2fd8,
    0x8ffa0dfa,0x7cc483fa,0x55aa3265,0xfb06d982,0x7fb06a8d,0x1fdc0590,
    0x8801c800,0xf8000beb,0x41dd1c44,0x17a0fd41,0xf80b7660,0x20b07ec5,
    0x15c15c7d,0x559d07f1,0x42f45fb5,0x80bea0fc,0x883742fa,0x3e603bef,
    0x13e23ec2,0x260fe882,0x85fbc9ef,0x0b103a8d,0x43ff1039,0x01fdc059,
    0x32201c80,0x3e20002e,0x067fdc02,0x017a0fd4,0xfc83ec88,0x1227fd10,
    0x880b1fd4,0x5fc44fcb,0xf1099999,0x7cc5f509,0xdb0bea02,0x26037d40,
    0x27c3e42f,0x2a20bf60,0x24a81bed,0x0104880d,0x400e9bea,0xaa9803fb,
    0xaaaabdaa,0x00039d30,0x74c027cc,0x20fd41ff,0x6ecc005e,0xe8c9fcc0,
    0x9b740376,0x3e237203,0x26027cc4,0x264f985f,0xb0bea02f,0x202fe80d,
    0x7c3e42f9,0x5c13ee04,0x220cedce,0x02e62cc6,0x0eeff600,0x2a00fee0,
    0xccdecccc,0x176cc0cc,0x1837c400,0x3ea3fe41,0xea803741,0x523ba00c,
    0x7dc059fb,0x44bb00c9,0x1837c44f,0x98bea1fe,0xb0bea02f,0x07f4e40d,
    0x43e42f98,0x20bf304f,0x5e8d9bfa,0x008b20b2,0x017fe200,0xc8001fdc,
    0x2fb22001,0x70bfa000,0xfa87ee24,0xd9103742,0x3bf70017,0xf100fbe2,
    0x88fe209b,0x543fe84f,0x1f907f21,0x5f5017cc,0x267506d8,0xc85f305f,
    0xfe884f87,0x45ae1140,0x01a20b30,0x002fc800,0x04f987f7,0xeb8000e4,
    0x3ea2740c,0x87e3daef,0x446fc469,0x6ecc0ffc,0x22fc4002,0x1fc800fd,
    0x3f663be0,0x3bfea0ad,0x22fcc4cb,0x501fd42e,0x5987e85f,0x1fd41fe4,
    0xb0bf03f2,0x5a84883f,0x00020088,0x7002fc80,0x01ffa87f,0xb5000072,
    0x3661be23,0x5e7f43ff,0xd5ffc81c,0x0072e17d,0x02d42d80,0x7fdc0698,
    0xd982fe8d,0xdf980bff,0x77f543db,0x8aefea83,0xdf50bffb,0x993ff621,
    0x9ff72efd,0x547ff933,0x4edcccef,0x00000000,0x2e005f90,0x201b983f,
    0x8800001c,0x09840200,0x00010440,0x00040200,0x10002001,0x00002200,
    0x00000000,0x00000000,0xfc800000,0x207f7002,0x00005405,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x1fec0000,
    0x5c43fc80,0x5c000001,0xeeeeeeee,0x2aaaa1ee,0x4056ecc2,0x00000009,
    0x00000000,0x00000000,0x00000000,0x00000000,0x64c00000,0x9300bfff,
    0x00217fff,0x6c87d400,0x7ffc4000,0x764ce47f,0x000488ad,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x3f47f200,
    0x44444000,0x3b6a02a0,0x0000000c,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x20000000,0x654fb0fb,0xcccccccc,0x0000001c,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0xc9e60000,0x26666625,0x00019999,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x40000000,0x00012a68,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00531c00,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__times_23_usascii_x[95]={ 0,2,1,0,1,0,0,0,0,0,1,0,1,0,
1,0,0,2,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,-1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,-1,1,0,-1,0,0,0,0,0,0,0,
-2,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0,0,2,1,1,0, };
static signed short stb__times_23_usascii_y[95]={ 18,3,3,3,3,3,3,3,3,3,3,5,15,12,
16,3,3,3,3,3,3,4,3,4,3,3,8,8,6,9,6,3,3,3,4,3,4,4,4,3,4,4,4,4,
4,4,4,3,4,3,4,3,4,4,4,4,4,4,4,3,3,3,3,21,3,8,3,8,3,8,3,8,3,3,
3,3,3,8,8,8,8,8,8,8,5,8,8,8,8,8,8,3,3,3,11, };
static unsigned short stb__times_23_usascii_w[95]={ 0,3,7,11,9,17,16,3,7,7,8,12,4,7,
3,6,10,6,10,9,10,10,10,10,9,10,4,4,12,12,12,9,19,15,13,14,15,13,11,15,15,7,8,16,
13,19,16,15,11,15,15,10,13,15,15,20,15,15,13,6,6,6,10,12,4,10,11,9,11,9,10,11,11,6,
7,11,6,17,11,10,11,11,8,7,6,11,11,15,11,11,9,7,2,7,12, };
static unsigned short stb__times_23_usascii_h[95]={ 0,16,7,16,17,16,16,7,20,20,9,12,7,3,
3,16,16,15,15,16,15,15,16,15,16,16,11,14,11,5,11,16,20,15,14,16,14,14,14,16,14,14,15,14,
14,14,15,16,14,20,14,16,14,15,15,15,14,14,14,20,16,20,9,2,5,11,16,11,16,11,15,15,15,15,
20,15,15,10,10,11,15,15,10,11,14,11,11,11,10,15,10,20,20,20,3, };
static unsigned short stb__times_23_usascii_s[95]={ 255,120,43,145,94,157,175,252,28,1,225,
30,245,64,252,203,192,229,243,50,107,130,237,39,28,134,56,25,43,51,91,
124,51,148,208,210,185,171,159,1,129,17,13,96,82,62,22,104,50,71,113,
17,222,213,197,176,236,1,145,87,248,44,234,94,250,132,225,61,38,143,60,
83,71,141,36,118,236,197,173,153,164,1,164,71,201,79,120,104,185,95,215,
20,17,9,72, };
static unsigned short stb__times_23_usascii_t[95]={ 1,1,67,1,1,1,1,39,1,1,55,
55,55,67,47,1,1,22,22,22,22,22,1,39,22,1,55,55,55,67,55,
1,1,22,39,1,39,39,39,22,39,55,39,39,39,39,39,1,39,1,39,
22,39,22,22,22,39,55,39,1,1,1,55,19,55,55,1,55,22,55,22,
22,22,22,1,22,22,55,55,55,22,39,55,55,39,55,55,55,55,22,55,
1,1,1,67, };
static unsigned short stb__times_23_usascii_a[95]={ 83,111,136,166,166,277,258,60,
111,111,166,187,83,111,83,92,166,166,166,166,166,166,166,166,
166,166,92,92,187,187,187,147,306,240,222,222,240,203,185,240,
240,111,129,240,203,295,240,240,185,240,222,185,203,240,240,314,
240,240,203,111,92,111,156,166,111,147,166,147,166,147,111,166,
166,92,92,166,92,258,166,166,166,166,111,129,92,166,166,240,
166,166,147,159,67,159,180, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_times_23_usascii_BITMAP_HEIGHT or STB_FONT_times_23_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_times_23_usascii(stb_fontchar font[STB_FONT_times_23_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_times_23_usascii_BITMAP_HEIGHT][STB_FONT_times_23_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__times_23_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_times_23_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_times_23_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_times_23_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_times_23_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_times_23_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__times_23_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__times_23_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__times_23_usascii_s[i] + stb__times_23_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__times_23_usascii_t[i] + stb__times_23_usascii_h[i]) * recip_height;
            font[i].x0 = stb__times_23_usascii_x[i];
            font[i].y0 = stb__times_23_usascii_y[i];
            font[i].x1 = stb__times_23_usascii_x[i] + stb__times_23_usascii_w[i];
            font[i].y1 = stb__times_23_usascii_y[i] + stb__times_23_usascii_h[i];
            font[i].advance_int = (stb__times_23_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__times_23_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__times_23_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__times_23_usascii_s[i] + stb__times_23_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__times_23_usascii_t[i] + stb__times_23_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__times_23_usascii_x[i] - 0.5f;
            font[i].y0f = stb__times_23_usascii_y[i] - 0.5f;
            font[i].x1f = stb__times_23_usascii_x[i] + stb__times_23_usascii_w[i] + 0.5f;
            font[i].y1f = stb__times_23_usascii_y[i] + stb__times_23_usascii_h[i] + 0.5f;
            font[i].advance = stb__times_23_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_times_23_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_times_23_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_times_23_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_times_23_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_times_23_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_times_23_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_times_23_usascii_LINE_SPACING
#endif

