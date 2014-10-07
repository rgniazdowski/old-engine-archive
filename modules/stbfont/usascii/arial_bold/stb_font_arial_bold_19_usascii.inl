// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_bold_19_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_bold_19_usascii'.
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

#define STB_FONT_arial_bold_19_usascii_BITMAP_WIDTH         128
#define STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT        110
#define STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_arial_bold_19_usascii_FIRST_CHAR            32
#define STB_FONT_arial_bold_19_usascii_NUM_CHARS             95

#define STB_FONT_arial_bold_19_usascii_LINE_SPACING          12

static unsigned int stb__arial_bold_19_usascii_pixels[]={
    0x00a98151,0x02a60153,0x442620a6,0x33000999,0x09998801,0x0d4c0030,
    0x800d4400,0x5403512a,0xffc89f11,0x7441fb83,0xe85e80ff,0x07fff93f,
    0x3ffffb26,0x5fffb04e,0xfb805f10,0x400dffff,0x0cfffffb,0x827d5be0,
    0xa83f63f9,0x0fdc0ffd,0xf7033fee,0x32a7fd05,0xdff983fe,0x0efca99b,
    0x910e6fec,0xfb03dfff,0x1ffffdff,0x3fbfff60,0x4f980eff,0x87ee05f7,
    0x40ff84fa,0x81fe41fb,0x3f6000ff,0x2202fcc3,0x20bf60ee,0x46fefefb,
    0xf711cffa,0x39ff709f,0x9893fee2,0x02fd9cfb,0x40ff88fb,0x20fdc1fe,
    0x05fa83fc,0x23fd85d9,0x27bb26f9,0x362f9beb,0xaf8fe82f,0x41bfa0cd,
    0x37f40ffb,0xffd0ffb8,0x03ffffff,0xe83fd0df,0x360fdc1f,0xd03fb82f,
    0x323fd87f,0xff9dfb0e,0x2fd9767f,0xf01f9fe8,0x0bfe207f,0x3fe207ff,
    0xf99ff972,0x84f8819d,0x21fec3fd,0x40ff41fb,0x87fd02fd,0x7dd3a3fd,
    0x3dc7fea5,0xfff905fb,0x405ff105,0x0bfe23ff,0x9b7c3ff8,0x905f504f,
    0x23ffa89f,0x0dfb31fb,0x1ff407fa,0xd97c4ff6,0x6b9fe60f,0x3fa20bf6,
    0x3fe20cff,0xf88ffe02,0x47ff103f,0x205f74f9,0x85fb80fc,0x5c7ee7fc,
    0x01ff01ff,0x27fb0ffa,0x547f88fa,0x2fd9366f,0x83fffea0,0x3ff303ff,
    0xff305ff8,0x3fbbfb63,0x83741eef,0x2ffcc4fb,0x1bfaa3f7,0x3fe80ffc,
    0x98fa9fec,0xf9a7e46f,0x7f00bf61,0x937f45fd,0xe81ff93b,0x0ffc80ff,
    0xfffffffd,0xc827c43f,0x2e27ec3f,0x207fe21f,0x87fd01fe,0x3e5f13fd,
    0xf15ff10f,0x5c42fd8d,0x4c9f53f3,0xfffaadff,0x2eff984f,0x7e89ffb3,
    0x0bea0bf1,0x07fa17ec,0x82fd83f7,0x87fd02fc,0x7e53a3fd,0xefefffce,
    0x7fc17ec0,0x641fd9fa,0xffffefff,0xfffff902,0x36f81dff,0x403f209f,
    0x20ff40ff,0x41fec1fb,0x87fd04fb,0x227f23fd,0xbdfb9deb,0x05fb0988,
    0x0dfffff9,0x3bbfffaa,0xffd505ff,0x29f307df,0x20dd02fb,0x40ff84f9,
    0x81fe41fb,0xd85fd06f,0x00bfa23f,0x17ec3ba6,0x00bfffb8,0x401fdc18,
    0x1884c401,0x07dc0260,0xfb81ff93,0x205f7dc1,0x3ff661fb,0xb07fd532,
    0x654c359f,0x2b3f60ef,0x00003f00,0x00000000,0x5ffc8bf0,0x7fc41fb8,
    0xf927c40f,0x3fff21df,0xffffd903,0xfd819dff,0x003b02ff,0x00000000,
    0x541c8800,0x1019502b,0x4c950195,0x2aaa60ac,0x01bb9800,0x00055554,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x003500c0,0x01310026,0x00100080,0x262026a6,0x00019880,0x3bf91000,
    0x2e7b63d9,0xfffb82ee,0x36007dc2,0xfd00dfff,0xffd71007,0x33ffae07,
    0xfffffb80,0x7dc27ec4,0x6c6fe447,0x7ffff41e,0x7fffd42f,0xfdfd2fff,
    0x8ee8dfff,0x2a027c5f,0xd04fcaef,0xdff9007f,0xdffa89ff,0x77fdc5ff,
    0x3f62fffd,0x3ea7fb84,0x41ffffff,0x42ffffff,0x5ff90dfe,0x7fd47ffa,
    0xb9fa9f12,0x8afe400f,0x007fd07f,0x83fee3ff,0x41ff12fe,0xb2fec4fd,
    0x7cff709f,0x987ff25f,0x209999ff,0x3fe62ff8,0x4fe8bfd2,0x5f9ba9f1,
    0xfdaffa80,0xdb37fd04,0x3e27f985,0x7c4bfa2f,0x8837f60f,0x2e13f62a,
    0x4c5ff17f,0x017ea1ff,0x2ff83ff3,0x25fd87fd,0x1f74fafd,0x17fff600,
    0xffefffe8,0xff89fe66,0x3f6fbea3,0x5efffcc5,0xfb84fd80,0x7c41ff37,
    0x3ffff21f,0x317fc40c,0xd17fa5ff,0x467ecc9f,0xff3005f8,0x7ff401ff,
    0x7f45ff51,0xfc89ff72,0xfff906ff,0x27ec1bff,0x45ff3fdc,0x3ff61ff9,
    0x7f40fffe,0x7f4bff25,0x807ff10f,0x0ceb88fb,0x6ffeffd4,0x22ff43d8,
    0x3ffee4ff,0x3fee4fff,0xb880efdb,0x3f66fffe,0x3f66fb85,0x21ffd88d,
    0x85fd12ca,0xfffeeffa,0xffbfffd2,0xf75f880d,0x54fe8bd7,0xfe8dfdff,
    0x3262fec3,0x3fe3fe9c,0x8830bfa1,0x0bfb1ffc,0x7ffd4df9,0x6401ffef,
    0xaffea85f,0xfb7fd2ff,0x1fb8017f,0x7c43f2dd,0x0ffff21f,0x04fe89fd,
    0x0ff997fc,0x17fc53f6,0x86fc9ffc,0x6ff545fc,0x90a61ff8,0x5ff040bf,
    0x88004ffa,0x0fe5be5f,0x7ffcc7fd,0xf98fff43,0x7d47fa2f,0x7c5ff10f,
    0x447bf61f,0x7ff71ffc,0x9a93fea1,0xfe83fe20,0x7c00bfa3,0x8007fd2f,
    0x3edf61fb,0x3ffbbfee,0x3ffa5fff,0x7e46ffdf,0x7ec3ffef,0x7cc6ffdf,
    0x45ffffff,0xfffffffe,0x326bbf60,0x7f7fd47f,0x5ff000ff,0xf8800ffa,
    0x427ffd45,0xb8cffffb,0x3f6bfa1f,0x7fe440bf,0x9ffd703f,0xdfffd501,
    0xffffb109,0xffff983b,0xffdb82ff,0x42aa000e,0x2a2001aa,0x4400a880,
    0x80040080,0x4c001000,0x88011000,0x0400abba,0x00000000,0x00000000,
    0x00000000,0x00000000,0x0cc000c0,0x0cc40010,0x88006a20,0x26003500,
    0x21a9801a,0x04c40098,0x33333333,0x3ee07301,0x3fe005ff,0x05f7fe41,
    0x2a03fea0,0x01dffffe,0xe83bffd3,0x7fffdc06,0x7ffe883f,0x9fb00ff6,
    0x3fffffe2,0x427dc6ff,0x04ffeff9,0x7fe43ff0,0x7d404ffd,0x77ffd40f,
    0x7c40effe,0x7e46feff,0xfdfffb00,0xbffa87ff,0xfb00ff63,0x3bbbba29,
    0x27e45ffe,0x0ffaa7ec,0x3fe1ff80,0xfa80ff52,0x877fe60f,0x2fe44ff9,
    0x417d45fd,0xfd10cffa,0xfd86fb8f,0xfe880003,0x3bfff21f,0x2ff8bfe1,
    0x7fc5f644,0x07fa8621,0xff907fd4,0xff837501,0x7427c402,0x90ac985f,
    0x7ec7dffd,0x320dfc8b,0x0bff603e,0x223ffffb,0xa8ffe1ff,0x1fffffff,
    0xa807ff70,0x017fa0ff,0x2db9ff88,0x07ff0dd0,0x93ffff60,0x6ffefefd,
    0x7fdc13f6,0xf989f904,0xff93fa1f,0x303ff90d,0xff500bff,0x990ffe21,
    0x3fe61999,0xfc86ffff,0x800bfe20,0x0ffd86fb,0x13f61ff5,0xfc817fea,
    0xfd0ffcc4,0xf98bfe29,0xefda881f,0xf83fea00,0x3fffe22f,0x11bff31f,
    0x22fa83fd,0x2e002ff8,0x225fd86f,0x889fb1ff,0x3f200eff,0xff0ffc44,
    0xf883fe67,0x01ff401f,0x27f41ff5,0x447ff732,0x113f23ff,0x503ff89f,
    0x9fb0df70,0x4fd8ffc4,0x9003ffa2,0x7c5ff09f,0x4c3ff12f,0xfb0aa1ff,
    0x7fb97ae9,0x7cc07fe4,0xfb8ffe1f,0x37ec6e85,0xdf707fdc,0x7fc47fb0,
    0x7fec9fb1,0xd85fc802,0x7c1ff34f,0xf87ff24f,0x263ff12f,0x46fd89ff,
    0xd30beff8,0x877ec3ff,0x4c7c82fe,0x9ff51dff,0x3fd86fb8,0xa7ec7fe2,
    0xf9003ffb,0x77fd43df,0x77fdc4ff,0x3ee1fffe,0x7fc6ffef,0xf982ffff,
    0xdfffffff,0x3ffffe60,0xfc83f507,0x40ffffff,0x23fd86fb,0x29fb1ff8,
    0xfffffffe,0x17ffc47f,0x5417ffea,0x41fe9ffd,0x4c0befeb,0x2603effc,
    0x02dfffec,0x2019ffd3,0xffea83f8,0x86fb81ce,0x47fe23fd,0xffffd4fd,
    0x060fffff,0x80020010,0x88001000,0x4c002000,0x00000400,0x00000000,
    0x00000000,0x00000000,0x00000000,0x30000000,0x88662013,0x4c133019,
    0x204cc409,0x004cc198,0x4cccc433,0x26219999,0x4cccc400,0x9884c401,
    0x13101999,0x02620262,0x3fa07ff2,0xf517fe66,0x2e2fec7f,0x237e45ff,
    0x1ff706fd,0x3ffffff2,0x00ffa7ff,0xfffffffb,0x3f69fb09,0x20dfffff,
    0x81ffb4fe,0x8dfd06fa,0x7fdc1ffb,0xff71bfa1,0x7ec7ffe8,0x740ffd44,
    0x3fbbae5f,0x3fa6eeef,0x777fec03,0x7ec4ffff,0xfffdffb4,0xfda7f4df,
    0xa837d44f,0x09ff13ff,0x0ffddbfa,0x7fc43fea,0x10bfe1ff,0x2ff889ff,
    0x7f40ffe0,0x6c2fec03,0xfda7ec7f,0xfe8ffdc5,0x543fffb4,0x23ff606f,
    0xff300ffc,0xff109ff9,0x4ff7bea5,0x6fd80ff9,0x3fe03fdc,0x3627fd03,
    0x2a17f63e,0x6d3f60ff,0xfd3ff85f,0xa9bfff69,0x37fe206f,0x7fe402ff,
    0x653fa06f,0xdf75fbcf,0xfe87fea0,0xe81ffc04,0x6c6fe8bf,0x17f6625f,
    0x517f69fb,0x6d3fa5ff,0xdf53ffdf,0x05fffb80,0x6405fff0,0xff35fd5f,
    0x4ff813f2,0xff803ff1,0xdfb7fd03,0xfffffd81,0xa7ec1eff,0xffedcefd,
    0x3f69fd0f,0x6fa8ffcb,0x800ffe80,0x2a04fffa,0xff0ff8ff,0x7e407fd3,
    0xff00ff77,0x3ffffa07,0xfffffd81,0x369fb03f,0x1fffffff,0xe9fed3fa,
    0xc806fadf,0xfff8806f,0x9ff102ff,0x7fdfecdf,0x367fe601,0x03ff804f,
    0xb0bffffd,0x03bfa2bf,0x577ed3f6,0xb4fe81aa,0x3f7fea7f,0x806fc806,
    0x0efe9ffd,0x5c9fffd0,0xfe807fff,0xff801ffd,0xff5ffd03,0x3e25fd83,
    0xfb4fd86f,0x369fd00b,0x1bfff63f,0xf501bf20,0x413fe69f,0x3e61fffc,
    0xffc805ff,0x07ff006f,0x237e4ffa,0x27fd45fd,0x02fed3f6,0x23fda7f4,
    0xc806fff8,0x1bfe206f,0xff705ff9,0x007fff0f,0x2007fff3,0x27fd03ff,
    0x17f62ff8,0x4fd87ff6,0x9fd00bfb,0xdff70ff6,0x640df900,0x77f441ff,
    0x6c2ffcc0,0xffd001ff,0x40ffe001,0x43fee3fe,0x6ff885fd,0x02fed3f6,
    0x83fda7f4,0x000006fe,0x00000000,0x00000000,0x00000000,0x01331000,
    0x88003331,0x01998809,0x74c4ec80,0x26202625,0x4cc43311,0x31099999,
    0x43333333,0x20099998,0x00999998,0x7ffec130,0xfdbfff40,0x222fec05,
    0x3fe62ffe,0xf55fffff,0x3f65fc8f,0xff77fb85,0x7fffffec,0xfffffb4f,
    0x3ff63fff,0x6c0cffff,0x3fffffff,0xffd97f60,0x5fffe22f,0x2fec05fd,
    0xff30bff6,0x7c9fffff,0xfd8bfe2f,0xff77fb85,0x77777fec,0xdddffb3e,
    0x3ff63ddd,0x20fffffe,0xffeeeffd,0x25ffb82f,0x3ea4fffd,0x80bfb7ff,
    0x0bff65fd,0x7fd4cccc,0x3fd57f20,0x5fee17f6,0x017f67fb,0xbfb00bfb,
    0x3f64ffa8,0xd32ff445,0x6fecbfff,0x5ff7f26f,0xafec05fd,0x36003ffc,
    0xfcbfcc2f,0x7dc2fec4,0x2fecff57,0x36017f60,0xb0ffb85f,0x649f90bf,
    0x3f65fddf,0xf7ff0ffb,0xfb017f6f,0x4009ff9b,0xf5fd05f9,0xaaefd83f,
    0xdf37fdaa,0x4cccefec,0x2aabbf60,0x217f62aa,0x5dfb1ff9,0x5c3ff955,
    0x5fecbf91,0xfaef9afd,0xfd80bfb7,0x000fffff,0x3bee03fd,0xffffd86f,
    0xbf37ffff,0x7fffffec,0x3fffff65,0x217f66ff,0xfffb2ff8,0x6407ffff,
    0x3eeff65f,0xb7facfbc,0xfffd80bf,0xfa804ffc,0x0fffe206,0x33333bf6,
    0x6cbf17fd,0x24eeeeff,0xcccccefd,0x3e217f63,0xd99dfb2f,0x3f207ffd,
    0x3be6ff65,0xfb7faafd,0x93ffd80b,0x3fd805ff,0x6c07fec0,0x3e7fb85f,
    0xfb017f64,0x30bfb00b,0x217f63ff,0x5fc80ffb,0x7fffcff6,0x0bfb7fa8,
    0x3fe25fd8,0x003fe00e,0x17f60bfb,0x362d9fee,0x02fec05f,0x7fdc2fec,
    0xff10bfb0,0x7ecbf905,0x3eadffb3,0xfd80bfb7,0x8827fd45,0xff95107f,
    0x2e17f605,0x7ec5517f,0x402fec05,0x3fea25fd,0xfb117f63,0x6cbf903f,
    0x2a9ff73f,0xfffffb7f,0x217f6dff,0x6fa81ffe,0x40bfff30,0x57fb85fd,
    0x202fecff,0xfffffffd,0xfffffb3f,0xfffd8dff,0x905fffff,0xf99fecbf,
    0x3f6ff52f,0xb6ffffff,0x0dff30bf,0x165c0bf7,0x3ee17f60,0x2fecff57,
    0x3fffff60,0xfffb3fff,0xffb07dff,0x407dffff,0x000005fc,0x00000000,
    0x00000000,0x00000000,0x01310000,0x02660008,0xbd500880,0x00000000,
    0x00000000,0x27f40000,0x01cffeb8,0x2a013fee,0x2a0beffd,0x37f6e27f,
    0xdefdb80c,0x1cefd981,0x05dfd910,0xdb13bf22,0x3ae7dd93,0x7ecf6c4f,
    0x427fe403,0x06ffeffc,0xf301fffa,0x4cbfd9bf,0x3b7bf64c,0x7f7fdc5f,
    0x3ffe60ff,0x7f440fff,0x7d44ffff,0x3fe5ffef,0xefeffefe,0x3fbfa4ff,
    0x3ffe603f,0xf897fc44,0xffff982f,0xff13f602,0x443fe203,0x447b20bc,
    0x437fa1ff,0x8f7f44fd,0x7ff11ffb,0x37fc7fe2,0x9bf23ffd,0x20099ffe,
    0x5444fefe,0x320ffa0c,0x2a06fddf,0xd01fec0b,0x44017bff,0xff12ffca,
    0x17fc4045,0x4ffcd3fe,0x7ff4fd99,0x4ff537e4,0xbfc804fe,0xff8804fd,
    0x7cd7fc42,0x3fee001f,0x3fffe601,0x77fecc4f,0x01ff32ff,0x7ec0ff98,
    0xffffff55,0xfc8bfebf,0x3fe9fea5,0x4fdb7cc0,0x5c37f440,0x4013fa7f,
    0x0aa22ffb,0x44bffb2a,0x25ff0cff,0x82622ff8,0xa7f42ff8,0x99999ff9,
    0x2fe45ff0,0x01ff4ff5,0x13f63fd1,0xe81ffe88,0x201ff24f,0xbfd42ffa,
    0x99ff45d9,0x45ff10ff,0xd17f24ff,0x8bfea1bf,0x7c7362ff,0xfa97f22f,
    0xfc80ffa7,0x84efecce,0xf981ffe8,0x2ffeeeef,0x7d41fec0,0x3f73bfa6,
    0x3af7fe0f,0x3ffee3ff,0x7fcc0ffe,0x7e45ffef,0xff0efddf,0xff52fe45,
    0xff901ff4,0xd0ffffff,0x3ff203ff,0x06ffffff,0x26a80f6c,0x41cffec8,
    0x5fccffea,0x816fffd4,0x903fffd9,0x7fc3bfff,0x7fa97f22,0xcca80ffa,
    0x644efecc,0x20999bff,0xb9999cff,0x02aa01ff,0x40040ba6,0x10002000,
    0x00000200,0x44fd8000,0xfffffff8,0xf101ff54,0x41ff409f,0x00000029,
    0x00000000,0x6c000000,0x7fffd44f,0x0bfb4fff,0x7fd03fe4,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x54000000,
    0x77445d90,0x80003300,0x4dd30028,0x93b61eea,0x897ae2ec,0x989d90ee,
    0xdddd50ee,0x01540bdd,0x20153053,0x7fd0ffb8,0x7c407fc4,0xfd73d907,
    0x01f7cc1b,0x2dfd1fea,0x97ee0ffc,0x4df70ffe,0x52fe47fa,0x0dffffff,
    0x35c0bfea,0x3f261fec,0x47fd0fff,0x7f880ff8,0xffdfdfb0,0x67fffc4d,
    0x7c44c980,0x7cc2ffdf,0x365fff17,0xff17fc3f,0x7e44cc45,0x8bffd02f,
    0x366becdb,0xbfffb53f,0x3e23fe85,0x3fe6660f,0x43ff6199,0x7ed40ffa,
    0xf5001dff,0x27fa09ff,0x1ff4fefa,0x0df55fc8,0xf981ffdc,0x3f261fee,
    0xff980cef,0x47fd00be,0xfff30ff8,0x363fffff,0x407fe24f,0x000fffb8,
    0x3f203ffd,0xfaefafcc,0xfd8ff886,0x409ff503,0x4c5fbbfd,0x3fe604ef,
    0x47fd00cf,0xfff30ff9,0x363fffff,0x407fe24f,0x800fffc8,0xf306fffb,
    0xfbfd1fdd,0x3ff3f607,0x205ff980,0x0ff88ff9,0x9807e73a,0x6c2dfffd,
    0x203fee5f,0x47fb07f8,0x7ed41ff8,0x0aa21dff,0x07ff9ff1,0x7fddbffe,
    0xbfff501f,0xd80bff10,0x0893f64f,0x3ff22001,0xbbff70ff,0xff101fff,
    0xff88ff60,0x19ffff11,0x6fe8ff50,0xff903ff7,0xf01bfe67,0xfffb05ff,
    0x4cc1ffff,0x00002620,0xfb07f5c4,0x101ff3df,0x88ff60ff,0x07df31ff,
    0x3fee7fa8,0x3ea1bfa0,0x9013fe1f,0x3fff60ff,0x0000ffff,0x202a0000,
    0x6c066000,0x447fe23f,0x00000002,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0xff980000,0x20ffffff,0x19833099,0x02a8854c,
    0x22088395,0x88888888,0x01999930,0x00000000,0x26000000,0xffffffff,
    0x3fe6ffe0,0x7f43ff30,0xfe98bf63,0x12eccfff,0xffffffff,0x3fffea7f,
    0x00000000,0x00000000,0x26666666,0x7fcdffc1,0x7f43ff30,0xbbf52f43,
    0x543fffff,0xaaaaaaaa,0x01bbbb30,0x00000000,0x22000000,0x19999999,
    0x87fc57fc,0x41740ff8,0x17950660,0x00000000,0x00000000,0x3fe60000,
    0x20ffffff,0x7e8ff0fd,0x00000364,0x00000000,0x00000000,0xffff3000,
    0x0441ffff,0x05408811,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__arial_bold_19_usascii_x[95]={ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,
1,-1,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,
1,1,1,0,1,0,1,0,0,1,-1,0,0,-1,0,1,-1,0,0,-1,0,0,1,0,0,0,0,0,1,1,
-1,1,1,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0, };
static signed short stb__arial_bold_19_usascii_y[95]={ 15,2,2,2,1,2,2,2,2,2,2,4,12,9,
12,2,2,2,2,2,2,2,2,2,2,2,6,6,4,6,4,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,16,2,5,2,5,2,5,2,5,2,2,
2,2,2,5,5,5,5,5,5,5,3,6,6,6,6,6,6,2,2,2,7, };
static unsigned short stb__arial_bold_19_usascii_w[95]={ 0,4,8,10,9,15,13,4,6,5,7,10,4,6,
3,6,9,6,9,9,10,9,9,9,9,9,4,3,10,10,10,10,17,13,11,12,11,10,9,13,10,3,9,12,
9,12,10,13,10,14,12,11,11,10,13,17,12,13,11,5,6,5,9,11,5,9,9,10,10,9,7,10,9,3,
5,9,3,14,9,10,9,10,6,9,6,9,10,14,10,10,9,7,3,7,10, };
static unsigned short stb__arial_bold_19_usascii_h[95]={ 0,13,6,14,16,14,14,6,17,17,7,10,6,3,
3,14,14,13,13,14,13,14,14,13,14,14,9,12,10,6,10,13,17,13,13,14,13,13,13,14,13,13,14,13,
13,13,13,14,13,15,13,14,13,14,13,13,13,13,13,17,14,17,8,3,4,11,14,11,14,11,13,14,13,13,
17,13,13,10,10,11,14,14,10,11,13,10,9,9,9,13,9,17,17,17,4, };
static unsigned short stb__arial_bold_19_usascii_s[95]={ 127,69,12,109,70,22,38,21,27,1,116,
22,26,60,124,120,1,119,12,22,1,116,56,37,72,62,54,47,1,1,43,
36,46,22,107,73,95,84,74,42,58,110,32,24,14,1,114,95,99,80,82,
82,60,94,46,28,15,1,108,64,66,40,106,48,31,61,52,71,11,93,86,
105,94,104,34,72,95,103,33,82,12,1,118,51,120,12,85,70,59,47,96,
19,15,7,37, };
static unsigned short stb__arial_bold_19_usascii_t[95]={ 1,63,102,1,1,19,19,102,1,1,91,
91,102,102,91,1,34,63,77,34,77,19,34,63,19,19,91,77,91,102,91,
77,1,77,63,34,63,63,63,34,63,49,34,63,63,63,49,1,49,1,49,
19,49,19,49,49,49,49,34,1,34,1,91,102,102,77,19,77,34,77,34,
19,34,34,1,49,49,77,91,77,19,19,77,77,34,91,91,91,91,63,91,
1,1,1,102, };
static unsigned short stb__arial_bold_19_usascii_a[95]={ 76,91,129,151,151,242,197,65,
91,91,106,159,76,91,76,76,151,151,151,151,151,151,151,151,
151,151,91,91,159,159,159,166,265,197,197,197,197,181,166,212,
197,76,151,197,166,227,197,212,181,212,197,181,166,197,181,257,
181,181,166,91,76,91,159,151,91,151,166,151,166,151,91,166,
166,76,76,151,76,242,166,166,166,166,106,151,91,166,151,212,
151,151,136,106,76,106,159, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT or STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_bold_19_usascii(stb_fontchar font[STB_FONT_arial_bold_19_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT][STB_FONT_arial_bold_19_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_bold_19_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_bold_19_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_bold_19_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_arial_bold_19_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_bold_19_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_bold_19_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_bold_19_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_bold_19_usascii_s[i] + stb__arial_bold_19_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_bold_19_usascii_t[i] + stb__arial_bold_19_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_bold_19_usascii_x[i];
            font[i].y0 = stb__arial_bold_19_usascii_y[i];
            font[i].x1 = stb__arial_bold_19_usascii_x[i] + stb__arial_bold_19_usascii_w[i];
            font[i].y1 = stb__arial_bold_19_usascii_y[i] + stb__arial_bold_19_usascii_h[i];
            font[i].advance_int = (stb__arial_bold_19_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_bold_19_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_bold_19_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_bold_19_usascii_s[i] + stb__arial_bold_19_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_bold_19_usascii_t[i] + stb__arial_bold_19_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_bold_19_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_bold_19_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_bold_19_usascii_x[i] + stb__arial_bold_19_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_bold_19_usascii_y[i] + stb__arial_bold_19_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_bold_19_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_bold_19_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_bold_19_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_bold_19_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_bold_19_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_bold_19_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_bold_19_usascii_LINE_SPACING
#endif

