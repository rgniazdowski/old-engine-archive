// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_35_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_35_usascii'.
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

#define STB_FONT_arial_35_usascii_BITMAP_WIDTH         256
#define STB_FONT_arial_35_usascii_BITMAP_HEIGHT        144
#define STB_FONT_arial_35_usascii_BITMAP_HEIGHT_POW2   256

#define STB_FONT_arial_35_usascii_FIRST_CHAR            32
#define STB_FONT_arial_35_usascii_NUM_CHARS             95

#define STB_FONT_arial_35_usascii_LINE_SPACING          23

static unsigned int stb__arial_35_usascii_pixels[]={
    0x37a65550,0x07ba200c,0xd809db50,0x5555510d,0x2aaaaaa3,0x00003760,
    0x67766554,0x880000ac,0x2e60000a,0x001bcedc,0x31001331,0xb7510013,
    0x2000599d,0x30cc1bb9,0x00ddcc13,0xeb82ec80,0x7bb95003,0x57fe0001,
    0x101ffff9,0x7fec03ff,0xa93ee05f,0xfd4fffff,0x7d43ffff,0x3ae20005,
    0xffffffff,0x20002dff,0xea8003f9,0xffffffff,0x2ffcc02e,0x1007fe40,
    0xfffffffb,0x3b2007df,0xf99fffff,0xfd19ff0f,0x001bffff,0x1ff417fc,
    0x3ffff620,0xff8002ff,0x0bffd915,0x7d407fe2,0xff303eff,0x7ff77541,
    0x1dddffd4,0xc8002fe8,0xacceffff,0xdffffdcb,0xffd91000,0xf90015bf,
    0xffddffff,0xfe80bfff,0x02ffc00f,0xddfffff5,0x01bfffff,0x766fffdc,
    0xff0ffcff,0xfd9bffdb,0x3fe200bf,0x200ffc40,0xffeceffe,0x276c000f,
    0x7c407fe4,0x01ff901f,0x3e203fe8,0x980dfd4f,0x3f6000ff,0xda800bff,
    0x7d401eff,0xffffffff,0x37fff602,0x7ffed441,0x80ffee06,0xff702ffa,
    0xfca883df,0xffa80eff,0x7fffdc0d,0x90bffff0,0xdf5009ff,0xfb80ff30,
    0x027fdc4f,0x03ff3000,0x3fa03ff1,0x203fd405,0x0dfd4ff8,0xd1009fb0,
    0x2e0009ff,0xff300fff,0xffb9f7bf,0x5fff703f,0x09fff500,0xfd81bfe2,
    0x07fff307,0x88bfff30,0x3fee07ff,0x40bfff0f,0x7e401ffd,0x6c06fb85,
    0x37fc40ff,0x5ff30000,0x3e03ff10,0x027f404f,0x37f53fe2,0x2007fd40,
    0x40002ffd,0xffd05ff8,0x7fdcbe65,0x00fffc46,0x203fff70,0xff880ffd,
    0x007ffb04,0xf317ffd4,0x0fff807f,0x7cc03fff,0x41fec03f,0x7fec04fc,
    0x4005ff80,0x2ff88099,0xff01ff88,0x00ffcc09,0x37f53fe2,0x501ffc40,
    0x0dcc03ff,0x7fcc2662,0xf337fc43,0xf907ffc5,0xff9000bf,0x20ffea0b,
    0xffa81ffb,0x6ffb8006,0xf9003fee,0x201bfe1f,0x266625fe,0x9999bff9,
    0xf7019cfe,0x02ffa89f,0x7c42ffc0,0x01ff882f,0x3fec09ff,0xfea7fc40,
    0x20dfb006,0xec884ff8,0xff72ffff,0x3e637e43,0xcb8be63f,0x003ffa0b,
    0x403ffe20,0x06fe86ff,0x20005ffb,0x1ff91fff,0xff0ffb80,0x64dfb00b,
    0xffffffff,0x7fffffff,0x263fff10,0x7c000fff,0x83ff885f,0x9ff01ff8,
    0x44027fc0,0x00dfd4ff,0x3f207fea,0xfdfffd06,0xa8ffb5ff,0x8ffe61ff,
    0x7fcc02f9,0x3ffa0006,0x4c3ff902,0x0fff03ff,0xea7fec00,0x0ffa807f,
    0xffb009ff,0x3fffff21,0xffffffff,0x3fee07ff,0x001fffcf,0xff885ff8,
    0xf01ff883,0x0bfe607f,0x7f53fe20,0x05ff1006,0x7ffb05ff,0x2ffffdc4,
    0xdff127fc,0x3ea017cc,0x3f60005f,0x49ff304f,0xff880ffc,0x3ff20007,
    0xf500ffb5,0x2013fe1f,0x17f207fd,0xfd801bee,0x0000dfff,0x13fe0bff,
    0x3e207fe2,0x03ff503f,0x3fa9ff10,0x50ffe006,0x07ff70ff,0x3613fff2,
    0x467ff45f,0x7fdc02f9,0x3fee0004,0xfe9ffa04,0x00bff305,0xfcb7fd40,
    0x87fdc00f,0x6fe805ff,0x3f60ff60,0xfffb1004,0x5ff8000d,0xff10bfb0,
    0x203ff503,0xf8800ffb,0x400dfd4f,0x227ec5ff,0x3e606ff9,0x46fb82ff,
    0x2fcffff9,0x001ffe40,0x5c0bff50,0x02ff99ff,0x40009ff5,0x3ff77ff8,
    0xff0ffc80,0x409ff00d,0x02fe81ff,0xfffffe98,0x17fe0003,0x3e217fdc,
    0x206fe81f,0xff1007fd,0xe801bfa9,0x2e17fc6f,0x7ffc02ff,0xf986fb80,
    0x02ceffff,0x40007ff9,0x3e204ffa,0x2a07fbcf,0x260004ff,0x0bff36ff,
    0xfff0fff8,0x817fdc03,0x7fc40ff9,0x57ffdc01,0x2a22fffa,0x205ff801,
    0xff11dffb,0x00fff643,0x3e200dfd,0x400dfd4f,0x20ffc7fd,0x7fe806fd,
    0x2e209fb0,0x1efffffe,0x00027fdc,0xfd807ff7,0x3e204fee,0x3ea0005f,
    0x407ff65f,0xfff0fffc,0x03ffa20b,0x3fcc37d4,0xc83bfee0,0x7ff90fff,
    0x5405ff80,0x23ff14ff,0x7c00eff8,0x9ff1005f,0xfc801bfa,0xf81ff11f,
    0x05ff804f,0xff5007ff,0x7d45ffff,0x3f60005f,0x7ffd402f,0x03ffc01f,
    0x44bff700,0xf910bfff,0x3ffe1fff,0x3ffa61ef,0x77ed54c1,0xaefdaaaa,
    0x07ff42aa,0xffeb7fec,0x202ffc00,0x3ff14ffd,0xf007bfe2,0x3fe200df,
    0x6400dfd4,0x98ff31ff,0x7fcc03ff,0x801ff883,0xfffd9af9,0x000fff10,
    0x7c007ff4,0xffd806ff,0x7ff90000,0xffffff98,0xff0ffdef,0xffffffdd,
    0xffff905f,0xffffffff,0x7fc4ffff,0xfdffd105,0x0bff009f,0x442fbfa2,
    0x3ff6a1ff,0x401ffe01,0x0dfd4ff8,0xf887fec0,0x2017fd47,0x7fb82ffb,
    0x7e45f300,0x00bff63f,0x401ffe60,0xfb803ffc,0xff88004f,0xfffd880f,
    0xf0ffc8df,0x3ffff2df,0xffdd702c,0xdffddddd,0x7fdcdddd,0x3fffe602,
    0x05ff801f,0xff883ff5,0x3a07fd81,0xff8800ff,0x7c00dfd4,0xf107fc7f,
    0x7ffc40bf,0x8017fd40,0x97fe62f9,0xd500fffa,0x003ffe85,0xf3001ff7,
    0xfd8001ff,0x6419805f,0x98dff0ff,0x03fe6001,0x7dc01ff1,0x7ffd404f,
    0x20bff006,0x1ff885fd,0xfb01ff98,0x9ff1003f,0x7c401bfa,0x3e0fec7f,
    0x1bff207f,0x9730bff3,0x37fc2f98,0x7ec13ffa,0x05ffcaef,0xc8017fa0,
    0x3ea005ff,0xf90001ff,0x001bfe1f,0xff50df50,0x407ffa80,0x802ffff9,
    0x07ff05ff,0xff103ff1,0x00bfee07,0x37f53fe2,0x5c5ff980,0x417fec3f,
    0x3e65fffc,0x2ffc80ff,0x6ff88be6,0x2077ffc4,0xffffffc8,0x05ff5000,
    0x0f7ff440,0x00ffff20,0xff0ffc80,0x4fc8000d,0xfe805fb8,0xffff303f,
    0x5ff805ff,0xf883ff88,0x207ff01f,0xf8804ff9,0x200dfd4f,0x3fd42ffa,
    0x2eb7ffe2,0xecfffefe,0xff501eff,0xff717cc9,0x9ffff309,0xfffb7337,
    0x544c40bf,0xe88006ff,0xa99bdfff,0x004fffec,0xff87fe40,0x1ff40006,
    0x7d4027ec,0xfda89cff,0x2fffecff,0x3e217fe0,0x01ff882f,0x2ffc09ff,
    0xfea7fc40,0x81ff7006,0x7fcc2ff8,0xfff3ffff,0x4401bfff,0x45f31fff,
    0xfd102ffe,0xffffffff,0x303dffff,0x003fffff,0x3ffff620,0x2fffffff,
    0x0ffc8000,0xf8000dff,0x002ff81f,0xfffffff7,0x3ff625ff,0x2217fe06,
    0x1ff882ff,0x7e409ff0,0xd4ff8807,0x1bf600df,0x326077ec,0x3fa61cfe,
    0x209982ce,0xbf9cfffc,0xa805ffea,0xeffffffd,0x0dfffb8a,0x00bfffe2,
    0x3fff6600,0x000befff,0x3e1ff900,0x3e60006f,0x007fc40f,0xfffffb30,
    0x403fb03b,0x2ff885ff,0xff01ff88,0x01ffc409,0x37f53fe2,0x8817fcc0,
    0x800005fe,0x7fe40efd,0xefffffff,0x4d54c000,0xa86fd880,0x800000ac,
    0x00009a99,0x26619880,0x0aa20000,0x98000aa2,0x7c01800a,0x82ff985f,
    0x9fd01ff8,0x4406fc80,0x00dfd4ff,0xff980bfb,0xd880000d,0xffd701ff,
    0x0007ffff,0x00053000,0x00000000,0x00000000,0x00000000,0x4c2ffc00,
    0x1ff881ff,0xf880bfd0,0x53fe202f,0x7fc406fe,0x3fffa801,0x3ffea000,
    0x1cfb8802,0x00000000,0x00000000,0x00000000,0x00000000,0x9ff70000,
    0xf107fd88,0x07ff203f,0x7c40df70,0xc80dfd4f,0x3faa004f,0xc9801cef,
    0x2001effe,0x6ed402f9,0xdddddddd,0x4ddddddd,0x00000000,0x00000000,
    0x00000000,0x3be00000,0xffd31fff,0x07fe20bf,0x027fffcc,0x7ffd43fd,
    0xffffd4ff,0x007fc43f,0x7ffffd40,0xffeeddef,0x98003fff,0x7ffdc02f,
    0xffffffff,0x05ffffff,0x00000000,0x00000000,0x00000000,0xfff30000,
    0x77ffcc7f,0x403ff100,0x2605fffb,0x3fffea5f,0xfffffd4f,0x0001fe43,
    0x3fffffae,0x0cefffff,0x10026000,0x33333333,0x33333333,0x00000013,
    0x00000000,0x00000000,0x20000000,0x6441bca8,0x0664402b,0x700f2a60,
    0x26666219,0x33333109,0x400004c8,0xaabcba98,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x016764c0,
    0x88005e98,0x22000aba,0x2e0000ba,0xd995003e,0x3000157b,0x10003575,
    0x04cc1377,0x59bb7510,0x57510003,0x2a600001,0x06ea600a,0x0000aaa0,
    0x26666666,0x22001999,0x01bcddcb,0x7fdc1554,0xfd805fff,0x3ffee003,
    0x2600cfff,0x0ceffffe,0x1017f400,0xfffffff9,0xd3001dff,0x05dfffff,
    0xfffffd90,0x3205ff35,0xffffffff,0xffd8801f,0x0000efff,0x75407fe4,
    0x00dfffff,0x88000bff,0xffffffff,0x6cc00fff,0xffffffff,0x98dfd01d,
    0x3ffc9cff,0xc801be60,0xffffffff,0xffffb80e,0x000efffe,0x3e601ff1,
    0xfeefffff,0x2603ffff,0xfffeffff,0x3ffee03f,0xffdfffde,0x7fffec42,
    0x2fffffee,0x7f7fff40,0x20001fff,0x7fdc0ffc,0x0efffeff,0x40005ff8,
    0xfffffffa,0x2e00ffff,0xfeefffff,0xfe82ffff,0x3ee2fec6,0x400bfa07,
    0x36a1dffc,0x7ffcc5ff,0x8037f4c3,0xfff505fa,0xffb3015d,0x9fff107f,
    0x07ffee23,0xf703bfea,0xffe85fff,0xfffc881d,0xa87ff703,0x90000fff,
    0x77fcc1ff,0x1fff710b,0x40005ff8,0xcccccffb,0x3f204ccc,0x6dc40cff,
    0x276c2fff,0x1ff10bfe,0x2200df50,0xffd00eff,0x8817ff41,0x3fd804ff,
    0x004fff88,0xff70fff5,0x117fee0b,0x7fd40dff,0x01ffe22f,0x3e61bfea,
    0x07ff504f,0xe83ff200,0x5ff902ff,0x40005ff8,0x2a0007fd,0xfc802fff,
    0x1ff8807f,0x2fe82ff8,0x403ff900,0xbff32ffb,0x401ffb80,0x4ffd81ff,
    0x21ffe400,0xff101ffc,0x402ffa8f,0x3fee2ffe,0x81ffb003,0x3fa00ffe,
    0x1ff90006,0xf981bfe2,0x002ffc4f,0x40017fa0,0x2004fff8,0x7c403ffd,
    0x542ff81f,0x9ff1006f,0x7fdc3300,0x01ffcc02,0xfff30ff3,0x6ff88001,
    0xfd007fec,0x400ffb8f,0x3ff22ffb,0x45ff5001,0x7dc05ff8,0x86ee602f,
    0x59710ffc,0x7fc6ff80,0x002b2e65,0x20009ff1,0x54006ffb,0xf02625ff,
    0x41ff885f,0xff3002fe,0x3ff90005,0x205ff880,0x3ffc84fb,0xf7035000,
    0x17fe207f,0xff500ffb,0x002ffd45,0x300ffe60,0xffd909ff,0x1ff93dff,
    0x44ff9800,0xfffd8dff,0x3fe605ff,0x5ffd0002,0xfe815000,0x3ea27f46,
    0x801bea0f,0x2ea20ffa,0x01ff900a,0x3a06ff88,0x02ffe82f,0x77fc4000,
    0x7c3ffc80,0x2ff9806f,0x0033ffe2,0x2017fdc0,0x7fdc5ff8,0xfefffdef,
    0x7fec000f,0x7ff77fc1,0x80efffdd,0xedc98ffb,0x3ffe202c,0xdfd00000,
    0xfd52ffa8,0x2002fe89,0xfffd17fb,0x5ff709ff,0x107ff980,0xfff881ff,
    0xfa800000,0xffebacff,0xa807fe84,0x7ffe42ff,0x32001bdf,0x7fc402ff,
    0x703bfea6,0x3001ffff,0xff07ffd9,0xbffb0bff,0xfffbff90,0xf303dfff,
    0x740000ff,0xffffd86f,0x01bee0ef,0xffd1ff90,0x41dfffff,0x7e405ff9,
    0x10df507f,0x00000fff,0x7fffff44,0x00ffb02f,0xff505ff7,0x17bfffff,
    0x400ffe40,0x0fff16ff,0x2007ffdc,0xf01fffff,0x7fec0bff,0x77ffff41,
    0x42ffffdc,0x00006ffa,0x7f5c1bfa,0x002fe84e,0x067fffec,0xfe89ffd3,
    0xffff302f,0x3e613f20,0xaaaa805f,0xb80aaaaa,0xdfffffff,0x401ffc80,
    0xfb302ffc,0xbfffffff,0x001ff901,0x0ffe6dff,0x200fff88,0x0dfffff8,
    0x2601fff8,0x6fffc4ff,0x20fffc80,0x00004ffa,0x5c001bfa,0x6ffecc6f,
    0x01fffec1,0x7fd43ffd,0xdff731cf,0x207fe0ff,0x7c405ff9,0xffffffff,
    0x473ffa62,0x4c1effb9,0x3fe205ff,0xfec9802f,0x641effff,0x6ff800ff,
    0xfc801ff7,0x2626200f,0x7fc3fffb,0x5c6ff806,0x27fec04c,0x0000bff3,
    0xf80037f4,0x3fffe61f,0x1bff63ff,0xfb89ff50,0x9fffffff,0x07f986fd,
    0xf880dff1,0xffffffff,0x4407ffa2,0x7fec0ffe,0x2fffd883,0x7fed4400,
    0x07fee1ff,0x3fe5bfe0,0x0007fdc0,0xff83ffe2,0x007fe805,0x7c4dff10,
    0x3a00007f,0x5fb8006f,0x7e44eff4,0x007ff90f,0xffd30bff,0x1bfa3bff,
    0x7ff817ee,0x99999980,0x9ff12ffc,0x442ffa80,0xebabdfff,0x0002ffff,
    0xfb93ffa6,0xaffc401f,0xffa807fe,0x2ffa8000,0x3f6013fe,0xfff0000f,
    0x0000ffe8,0x8800dfd0,0x03fea1ff,0x0bfee9fd,0xa881ffa0,0xfd85ff81,
    0x00bffa03,0xfa97fdc0,0x85ff801f,0xffffffe8,0x5311ffbd,0x37fc4001,
    0xf8805ff5,0x500ffd5f,0xf10001ff,0x4027fcbf,0x360007fd,0x07ff20ff,
    0x742b3200,0x2fdc006f,0x57f21bee,0xfe803ffa,0x3ff88006,0x3ee00ff8,
    0xff70005f,0x2003ff25,0xdb7107fe,0x47fee5bd,0x6c003ffa,0x07ff30ff,
    0xff93ff98,0x20ffb801,0x4fff0018,0x6fe805ff,0x71ffa000,0xf88007ff,
    0x00dfd0ff,0x3f20ffc4,0xff36fb85,0x4c9ff00b,0x0ffdc01a,0xff101bea,
    0xff70007f,0x200bfee5,0xf90006ff,0x01bfe21f,0x7fc4ffb0,0xa8ffe405,
    0x7fe401ff,0x8805ff90,0x01bfe5ff,0x3ffb97fe,0x7cc6ff80,0x7fdc006f,
    0xc801bfa5,0xb85fc85f,0x803ff66f,0xbff12ffa,0xfc86fe80,0x3fffb804,
    0x4bff6200,0x7c404ffa,0x002ae64f,0x2ffd8ffb,0xc8bff100,0x9ffa00ff,
    0x3e204ff9,0x09ff30ff,0x3fe4ffa8,0x8ffee01f,0x7dc06ffa,0x04ffd84f,
    0x745fff30,0x3ff1006f,0xbf90df70,0xe882ffcc,0x07ffa0ff,0x7f417fe4,
    0x7fffb002,0xffffb801,0x405fff12,0x3fe62ffe,0x717fea04,0xe9809fff,
    0x27fc42ff,0x7f42ffb8,0x1fff901f,0xf880fffc,0x1bffe1ff,0x3e237fc4,
    0xfff102ff,0x19fff101,0x22fff4c0,0xbf9006fe,0xfd03fe60,0x21dffe87,
    0x7d42ffe9,0xffb30bef,0x400ff10d,0xceffffd8,0xffffecaa,0x5fffd42f,
    0x213ffa60,0x2a20afff,0xffb81fff,0xdcaabdff,0xffb04fff,0x17fee21b,
    0x442bffa2,0x2a0ffffc,0xf511cfff,0xffff87ff,0x0bffea1d,0x4473ffea,
    0x2a03fffa,0x99beffff,0xe86fffda,0x1ff8806f,0x366bbf60,0xfffd886f,
    0x902fffff,0xffffffff,0x00bf501d,0xffffff70,0x19ffffff,0x3ffffee0,
    0xa80dffff,0xffeeffff,0x3fea01ff,0xffffffff,0x3ffa203f,0x00ffffff,
    0xfffffff3,0xfb81ff7d,0xffffffff,0xffdcff84,0x203fffff,0xfffffffc,
    0xff9802ff,0xffffffff,0x06fe80df,0x74405fc8,0x201fffff,0x2dffffeb,
    0x7ffff540,0x00ff603f,0x7fff5c40,0x800cdfff,0xffffffd8,0x7fff5402,
    0x9801efff,0xefffffec,0xfff9002c,0xc9801bff,0xfa8dfffe,0xfffe980f,
    0x9ff01eff,0x07bffff2,0x3ffffa60,0x2e2001df,0xeffffffe,0x101bfa01,
    0x36e001dd,0x331000bd,0x03531000,0x00001550,0x00015531,0x40009a98,
    0x0001bca9,0x00004cc4,0x30001351,0x2a620003,0x02660001,0x002a6200,
    0x06aa6200,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x554caaa0,0x01554000,0xed8554c0,
    0x00155401,0x1e765440,0x2aaaaaaa,0xaaaaaaaa,0x000aaa62,0x5530d554,
    0x2aa88005,0x54006aa6,0x555001aa,0x80005554,0x55511aa8,0x55555555,
    0x23555555,0xa98002aa,0xaaaaaaaa,0xaa800aaa,0x3eedff11,0x7ff4002f,
    0x8ffec000,0x37fc04fc,0x3ffe2000,0x7fffc4ff,0xffffffff,0x3fe67fff,
    0x7fd4001f,0x0bffe60f,0x2a2ffe80,0xff9804ff,0x4fff006f,0xb0005ffb,
    0x3ffe63ff,0xffffffff,0xd3ffffff,0xff7000df,0xffffffff,0x7c05ffff,
    0x2edff15f,0x7f4002ff,0x7fec000f,0xff80df51,0x7ff40006,0x7ffc2eef,
    0xffffffff,0x7e47ffff,0x3fe2006f,0x0fffb82f,0x444ffc80,0xffb806ff,
    0x7fcc00ff,0x001ffe25,0xff99bfe2,0xffffffff,0x3fffffff,0xf7000dfd,
    0xffffffff,0x07ffffff,0xb7fc57fe,0x74002ffb,0x7ec000ff,0x401ff11f,
    0x220006ff,0x26600eff,0x99999999,0xe85ffe99,0xffb004ff,0x02ffec09,
    0x7f41bfea,0x7f7ec00f,0x17fdc03f,0x7000bff6,0x999987ff,0x99ffe999,
    0xfd099999,0x5ff7000d,0xfffd9980,0xff15ff83,0x000bfeed,0xd8001ffd,
    0x80bfa1ff,0x260006ff,0x200004ff,0xf980effc,0x7fd401ff,0x1fffc406,
    0x901fff88,0xbff805ff,0x7fec05fe,0x002ffd40,0xe8003ffa,0x6fe800ff,
    0x02ffb800,0x3e17ff20,0x2edff15f,0x7f4002ff,0x7fec000f,0xff817ee1,
    0x3fe60006,0xff700003,0x37fe401f,0x003fff10,0xfd01fff5,0x27fd405f,
    0xff93ff30,0xff06ff80,0x3fe6001f,0x07ff4005,0x40037f40,0x26002ffb,
    0x15ff87ff,0x0bfeedff,0x001ffd00,0x3e61ffd8,0xa89bfe07,0xf53101bc,
    0x0001339f,0x100bffea,0x3f607ffd,0x3ff2004f,0x402ffe46,0x5ff205ff,
    0xff301ffa,0x00fff209,0x20017fe4,0xfe800ffe,0xb8266206,0x7ec002ff,
    0xf8affc2f,0x005ff76f,0x4000ffe8,0x0ffc1ffd,0xfff96ff8,0xffd83fff,
    0x004fffff,0x003fff98,0xfa83fff3,0xffe8006f,0x001dff53,0xa7f40ffb,
    0xff704ff8,0x01bfe205,0x74003ffc,0x6fe800ff,0x5c3fff50,0x7f4002ff,
    0xf8affc1f,0x005ff76f,0x4000ffe8,0x1fec1ffd,0xfffeeff8,0x321ffffe,
    0x3eeeffee,0x2fff4400,0xd1bff200,0xf30003ff,0x03fff3ff,0x2207fee0,
    0x41bfa2ff,0x7ff407fd,0x027fd400,0x4007ff40,0xfffa86fe,0x0017fdc1,
    0xff81fff3,0x3eedff15,0x7ff4002f,0x0ffec000,0x7ffc1bea,0x3ff661df,
    0x003ff985,0x003bff60,0x325ffd10,0x2e0003ff,0x003fffff,0x3ea0ffe6,
    0x203fee0f,0x7fd405ff,0x007fec03,0x4007ff40,0x77fd46fe,0x002ffb80,
    0xff09fff5,0x7ddbfe2b,0x7ff4002f,0x0ffec000,0x3fe03fe2,0x21ffa05f,
    0x90003ff9,0x20001fff,0x5ff9fffa,0xfffd8000,0x85ff8005,0x17fcc6fd,
    0x3e00ffe2,0x17fe206f,0x007ff400,0xdff537f4,0x337fee01,0xedcccccc,
    0xff80efff,0x3eedff15,0x7ff4002f,0x0ffec000,0x7ffc17f4,0x303ff201,
    0xf50007ff,0xc80005ff,0x000fffff,0x03fffa80,0xff87fd80,0x7dc5ff84,
    0x1ffc801f,0x0005ff50,0x3a003ffa,0x01dff56f,0x7fffffdc,0xffffffff,
    0x7c57fe04,0x005ff76f,0x4000ffe8,0x4fc81ffd,0x7dc07ff8,0x01ffcc1f,
    0x00fffe20,0x3fffa200,0xff880003,0x5c001fff,0x07fe60ff,0x0ffb1ff6,
    0x7413fe60,0x3fa0007f,0x9efe800f,0x7dc00eff,0xffffffff,0x7c00bdff,
    0x2edff15f,0x7f4002ff,0x7fec000f,0xff86f981,0x20ffdc06,0x22003ff9,
    0x00005ffe,0x0001bfea,0x37ff7fec,0xb8bfe600,0x43ff707f,0x3fa005ff,
    0x004ff887,0x2003ffa0,0x1ffffffe,0x4c17fdc0,0xf802effc,0x2edff15f,
    0x7fc003ff,0x1ffd8007,0x6ff83ff0,0x260ffdc0,0x3f6003ff,0x4c00006f,
    0xb80005ff,0x09ffd5ff,0x3fa4ff80,0x225ff105,0x3ee002ff,0x00ffdc1f,
    0x001ffd00,0xdffffffd,0x202ffb80,0x7c02fffa,0x2adff15f,0x7fc003ff,
    0x1ffd8007,0x6ff87fb0,0x260ffdc0,0xff7003ff,0x9800001f,0x4c0005ff,
    0xfff30fff,0x8b7ec003,0x53fa03ff,0x22000ffa,0x037f44ff,0x003ffa00,
    0x3f63bffa,0x0bfee03f,0x403fff70,0x2dff15ff,0x22004ffa,0x016546ff,
    0x3ee01ffb,0x2e037fc5,0x1ffcc1ff,0x00fffd40,0x2ffcc000,0x5fff1000,
    0x000fffc8,0x1ff51ff5,0x6fcb7e40,0x267fd800,0x740002ff,0xefe800ff,
    0x203fff10,0xfd802ffb,0x2bff00ef,0xdff16ff8,0x22ffd400,0x3ffa05ff,
    0xff8ff100,0x20ffdc06,0x7c403ff9,0x000003ff,0x4000bff3,0xffd04ffd,
    0x27fe200b,0xbfd406fc,0xfa8004fe,0x000ff92f,0xd001ffd0,0x06ffa8df,
    0xf1005ff7,0x57fe0bff,0x3ffa6ff8,0x87ffd003,0x1ffe06fe,0x37fc3fd0,
    0xf307fee0,0x7ff4407f,0x26000004,0xf70005ff,0x3fe201df,0xd7fd003f,
    0xaff8809f,0xff0002ff,0x00013feb,0x3a003ffa,0x83ffd86f,0xf5002ffb,
    0x2bff05ff,0x3fee6ff8,0x3ff2202f,0x41ffec0e,0x7e405ffc,0xf701bfe4,
    0x03ff983f,0x00017ff6,0x00bff300,0x803fff30,0xc800fffb,0xe802ffef,
    0x20007fdf,0x01ffaffc,0x00ffe800,0xff886fe8,0x017fdc1f,0xf81dffb0,
    0xe8dff15f,0xbabcefff,0x982ffffc,0xfdaaefff,0x37d401ff,0xffb80dff,
    0xa81ffcc1,0xcccccfff,0xcccccccc,0xbff3001c,0x3ffe8800,0x00dffb00,
    0x200ffff5,0x0005fffb,0x01bfbfe2,0x007ff400,0xffb837f4,0x0017fdc6,
    0xff89fff1,0xd88dff15,0xffffffff,0x3f202fff,0x2fffffff,0xff0ff880,
    0x41ffb80d,0xff503ff9,0xffffffff,0x5fffffff,0x017fe600,0x400bffb0,
    0x4404fff8,0xf3005fff,0xd80007ff,0x00003fff,0xfd001ffd,0x71fff40d,
    0xfb8005ff,0x457fe1ff,0xffb506ff,0x019fffff,0xbfffff50,0xf97ec005,
    0x0ffdc06f,0x7d40ffe6,0xffffffff,0xffffffff,0x0bff3002,0x007ffdc0,
    0x007ffea0,0x7c007ffd,0x540001ff,0x00000fff,0xfd001ffd,0x8fffcc0d,
    0xe8002ffb,0x017fe6ff,0x066aa620,0x000d4400,0x00001a98,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x80000000,0xaaaaaaa9,0x20009aaa,0x01aa981a,0x55315540,0x55100055,
    0x002aa635,0x8002aa60,0x5510aaaa,0x000d54c5,0x32200aaa,0x55555512,
    0x55555555,0x2aaaaa63,0xaaaaaaaa,0xa98001aa,0x99999882,0x99999999,
    0x2aaaaa61,0x00009aaa,0x8026aea6,0xffffc899,0xffffffff,0x07fa202d,
    0x8003fff2,0x3fff27fd,0x7fe4000f,0x003ffb5f,0x2003ffb0,0x3e63fffb,
    0x07ff70ff,0x200ffe80,0xfff54fe8,0xffffffff,0x3feebfff,0xffffffff,
    0x005fffff,0x7dc37fc4,0xffffffff,0x3f67ffff,0xffffffff,0xd5001dff,
    0x07ffffff,0xfff9dff3,0xffffffff,0x3ea09fff,0x5fffc81f,0xfc9ff600,
    0x74002fff,0x3ffb5fff,0x03ffb000,0x985fff70,0x7ff70fff,0x00ffe800,
    0x7fd53ff6,0xffffffff,0xff75ffff,0xffffffff,0x00bfffff,0xfb86ffd8,
    0xffffffff,0x3f67ffff,0xffffffff,0x6401ffff,0xfffeffff,0x3bfe60ef,
    0x9999bffc,0xfffeaa99,0xc81ffa82,0xb002ffff,0x7fffe4ff,0x3ffe6005,
    0x003ffb5f,0xb803ffb0,0xff982fff,0x007ff70f,0xf900ffe8,0x33fea9ff,
    0x99999999,0x7ff70999,0x33333333,0x40013333,0xca86fffa,0xcccccccc,
    0x3f64ffec,0x999999af,0x501fffea,0x75c45dff,0x37ba25ff,0xf9002ffc,
    0x03ff50ff,0x01fffff9,0x7fe4ffb0,0xf9000ffd,0x3ff6bffd,0x1ffd8001,
    0x40bffee0,0xff70fff9,0x0ffe8007,0xa7ffff4c,0x70003ffa,0x000007ff,
    0x037fffc4,0xd8bff300,0xffc801ff,0x401ffd04,0xff901fff,0x87ffc005,
    0x19bffb98,0x17ffbff2,0xffc9ff60,0xff002ffb,0x3ff6bff7,0x1ffd8001,
    0x405fff70,0xff70fff9,0x0ffe8007,0x3ff7fff2,0x0007ff54,0x0000ffee,
    0x6fedfe80,0x03bfa000,0xf1003ffb,0x09ff10df,0xf903ffc8,0x7fec005f,
    0xffffff72,0x7fcffe4f,0x93fec02f,0x00bff3ff,0x2bff3ff3,0xd8001ffd,
    0xfffb81ff,0x73ffcc02,0xfe8007ff,0x17fff90f,0x0ffea9ff,0x01ffdc00,
    0x8ffb8000,0xf70006fe,0x03ffb05f,0x3ea1ffa0,0x2ffcc02f,0x2002ffc8,
    0xfdd53ffc,0x7fe4dddf,0x200fffa9,0x23ff27fd,0x7e400ffc,0xffb5ff8d,
    0x3ffb0003,0x801fffb8,0x3fee7ff8,0x87ff4003,0x9ff11dfc,0x4000ffea,
    0x00003ffb,0xdfd2ff98,0x0bff3000,0x7c007ff6,0x5002605f,0x3ff209ff,
    0x07ff6002,0xff903ff5,0xd817ff63,0x263ff27f,0x57fc02ff,0x3ffb5ff8,
    0x43ffb000,0x1001fffb,0x1ffdcdff,0x543ffa00,0xfaa7fc41,0xff70003f,
    0xfd000007,0x40037f4b,0xffb00ffe,0x07ff5003,0x02ffe800,0x26005ff9,
    0x7fd40fff,0xf11ffc81,0x9ff605ff,0x0bfd0ffc,0x5ff8bfd4,0xb0003ffb,
    0x3ffee3ff,0x737fc001,0x333339ff,0xfd333333,0xa7fc401f,0x70003ffa,
    0x800007ff,0x1bfa0ffc,0x409ff700,0x93101ffd,0x88000bff,0xff900fff,
    0x9fff7005,0xf903ff50,0x07ffd43f,0x1ff93fec,0x7e403ff2,0x3f6bff15,
    0xffd8001f,0x04ffffb9,0xff72ffc0,0xffffffff,0x1fffffff,0xfaa7fc40,
    0xeeeeeeef,0x7fdc6eee,0xffffffff,0x2a06ffff,0x037f41ff,0xd803ffa0,
    0xffffffff,0x0004ffff,0x3202ffe8,0xeeeeeeff,0x06ffffee,0xff903ff5,
    0xd85ffd83,0x4c3ff27f,0x25ff02ff,0x3ffb5ff8,0xfbffb000,0x005fffdf,
    0xfff72ff4,0xffffffff,0x01ffffff,0xffaa7fc4,0xffffffff,0x7ffdc7ff,
    0xffffffff,0xff106fff,0x400dfd09,0x7ec05ffa,0xffffffff,0x40004fff,
    0x7e405ffd,0xffffffff,0x500cffff,0x3ff903ff,0x6c2fff88,0xe83ff27f,
    0x227fa85f,0x03ffb5ff,0xdffffb00,0x001fff71,0xdffb93fa,0xaaaaaaaa,
    0x00fffaaa,0x7fd53fe2,0xeeeeeeee,0x77fdc6ee,0xeeeeeeee,0xdfb05eee,
    0xd801bfa0,0x7fec02ff,0xeecccccd,0x8001efff,0x6400effd,0xeeeeeeff,
    0x5401bcde,0x1ffc81ff,0x360fffa8,0xc83ff27f,0x127ec0ff,0x07ff6bff,
    0x3bfff600,0x401bff60,0x0ffee4fd,0x401ffd00,0x7ff54ff8,0x0ffee000,
    0x07fee000,0xf88037f4,0x1ffd806f,0x01fffc80,0x01dffd10,0x0bff2266,
    0x0ffd4000,0xfd80ffe4,0xfc9ff65f,0xf0bfe60f,0xdaffc43f,0xfd8001ff,
    0x7ffc40ef,0x2e3fd803,0x7f4003ff,0x53fe200f,0x70003ffa,0x880007ff,
    0x1bfa03ff,0x401ffdc0,0xf7001ffd,0xffd1009f,0x3bfe601b,0x00002ffc,
    0xff903ff5,0x4bffe203,0x03ff27fd,0x23fd4bfd,0x3ffb5ff8,0x03ffb000,
    0x9007ffea,0x01ffdc7f,0x8803ffa0,0x07ff54ff,0x00ffee00,0xdddff900,
    0xdfffdddd,0x07ff40bd,0x800ffec0,0x7cc06ff8,0x7fcc05ff,0x0002ffce,
    0xf903ff50,0x7ffd403f,0x3ff27fd8,0xfd87fe40,0xfdaffc44,0xffd8001f,
    0x03fff201,0x3fee2fc8,0x07ff4003,0x3ea9ff10,0xff70003f,0xffc80007,
    0xffffffff,0xf306ffff,0x3ff6009f,0x03ffa001,0x4027ffcc,0x2ffceff9,
    0x5ff50000,0xd803ff90,0x327fddff,0x5ffcc0ff,0x7fc41ff8,0x0003ffb5,
    0xfe803ffb,0xb82a605f,0x7f4003ff,0x53fe200f,0x70003ffa,0xa80007ff,
    0xcccccccc,0x03ccfffc,0x36005ff7,0xff1001ff,0x0bffe60f,0x5ff9db00,
    0x3fea0000,0x401ffc82,0x27fffff8,0xdfe80ffc,0x5ff886fa,0xb0003ffb,
    0xff9803ff,0x3fee003f,0x07ff4003,0x3ea9ff10,0xff70003f,0x20000007,
    0xffd806fe,0x03ffb001,0x2217fea0,0xf8002fff,0x0002ffcc,0x457dff30,
    0xfa801ffc,0x3ff27fff,0x4fdffc80,0xffb5ff88,0x3ffb0003,0x03fff700,
    0x1ffdc333,0x803ffa00,0x7ff54ff8,0x0ffee000,0x7f400000,0x007ff806,
    0x2a007ff6,0xffd83fff,0xcafb8003,0x100002ff,0x323fffff,0xffb001ff,
    0x407fe4ff,0x881ffff9,0x9bffb5ff,0x99999999,0x007ff619,0xf1077ff4,
    0x01ffdcff,0x8803ffa0,0x07ff54ff,0x337fee00,0xcccccccc,0x4000cccc,
    0x7fc406fe,0x37ff6006,0xfecccccc,0xffa85fff,0xcccccccf,0x27f13ccc,
    0x00002ffc,0x64bfffa6,0xff1001ff,0x807fe4ff,0xff106ffe,0x3fffff6b,
    0xffffffff,0x2003ffb1,0x3e25fff8,0x00ffee7f,0x4401ffd0,0x07ff54ff,
    0x3fffee00,0xffffffff,0x4001ffff,0x7fcc06fe,0x3fff6005,0xffffffff,
    0xffe80dff,0xffffffff,0xfc825fff,0x3000002f,0x000ffe41,0x7fe4fff5,
    0x207ff700,0xfffb5ff8,0xffffffff,0x07ff63ff,0x12fffb80,0x1ffdcfff,
    0x803ffa00,0x7ff54ff8,0x3ffee000,0xffffffff,0x001fffff,0x3ea037f4,
    0x3ff6003f,0xefffffff,0x3ffe00cd,0xffffffff,0x00005fff,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x98000000,0x260002aa,0x302bdecb,0x55555555,0x13300335,0x22019880,
    0x009abca9,0x13597510,0x4de54c00,0x5e544000,0x32a6000a,0x4266009b,
    0x0ccc0bb8,0x99880333,0x4ccccc40,0x09999999,0x5e544133,0x98033101,
    0x42662009,0x35531aa9,0x07ffec00,0x3fff2200,0x641effff,0xffffffff,
    0x3e02efff,0x07fe405f,0x7fffffdc,0x7fe402ff,0x403fffff,0xffffffea,
    0xfffea803,0x74c03fff,0x03ffffff,0xffff37ff,0xfd9ffe29,0x0fff604f,
    0xfffffffb,0x3e7fffff,0xfffffb3f,0x00ffc83d,0x7dc0fff3,0x2e9ff90f,
    0xff1004ff,0xfe8007ff,0xfffdceff,0x3ffff21f,0xffffffff,0x05ff82ff,
    0xfd107fe4,0xffffbdff,0x3fff205f,0x06fffede,0xfdbdfff9,0x3e601dff,
    0xfffedeff,0xbdfff704,0xf81bfffd,0x2ffffecf,0x7fc4fff1,0x85ffb81f,
    0xfffffffd,0xff2fffff,0xffdfffb9,0x17fd43ff,0xd00fffb8,0xba7fe4df,
    0xff7004ff,0x7e400ffb,0x7fe441ef,0x337ff90f,0xff953333,0x05ff81ff,
    0xff907fe4,0x6ffc9819,0x440dff88,0x7fd41ffe,0x2ffec41e,0x260fffcc,
    0x7fcc2ffe,0x44ffd81e,0x5aadffff,0xff517ba2,0x00eff98d,0x7cbff900,
    0x3622dfff,0x17fe25ff,0x441ffff4,0x53ff23ff,0xfd004ffb,0x2005ff59,
    0x3fa00fff,0x005ff93f,0xff8bfff3,0xf07fe405,0x7ffc01ff,0x980ffdc0,
    0x3ffe24ff,0xd07ff600,0x3fea01ff,0xb00fff45,0x2fffc1ff,0x49ffb000,
    0x70001ffe,0x5fff8dff,0xfd83ffa0,0x5ffff887,0x3ee1ffa8,0x009ff53f,
    0x17fe5ff3,0x5013fe60,0x0bff29ff,0xf1fff440,0x0ffc80bf,0xfd805971,
    0x017fdc0f,0x04ffa813,0xff12ffcc,0x264ed809,0x7fd404ff,0x0007ffe4,
    0xfc9ffe88,0xff50003f,0x01fff81d,0xffb83ff6,0x3fe7fd41,0x3fea37ec,
    0xb007ff32,0x03ff61ff,0x8805fd50,0x05ff95ff,0xf87ffc40,0x07fe405f,
    0x07ff2200,0x0039fff3,0x3a003ff2,0x00bfe67f,0x100bfee0,0x07ffcbff,
    0x3bfe6000,0xf30005ff,0x0fff03ff,0x3e21ffc8,0x7d6fe43f,0x2227fc1f,
    0x03ff11ff,0x3ea5ff88,0x2600004f,0x05ff93ff,0xff1ffd80,0x00ffc80b,
    0x3ffb2ea6,0xfffc81ff,0xfb00adff,0x43ff600f,0xc8001ffb,0xccccccff,
    0x3e7ffccc,0xf900007f,0x10001fff,0x3fe05ffd,0x20ffdc06,0x45ff45fe,
    0x07fe63ff,0x801ff1fe,0x3ffc2ffb,0x3ffb0000,0x7000bff2,0x017fe5ff,
    0xfd981ff9,0xffffffff,0xffff701f,0xfe83bfff,0x23ff9007,0xd8000ffc,
    0xffffffff,0x3e7fffff,0x3e00006f,0xe88004ff,0x1bfe03ff,0xfc83ff70,
    0x7f47fe27,0x1dc1ff25,0x1ffa012e,0x0000bff2,0xffc97ff2,0xa7fcc002,
    0x7fe405ff,0x3ffffea0,0x1ffc8ace,0x3fff6a20,0x1ffa2fff,0xfd87fe40,
    0xffd8000f,0xcccccccc,0xbff0cccc,0x3fee0000,0x7ec000ff,0x037fc04f,
    0xff307fee,0x7fc9fee5,0x000013fa,0xff309ff3,0xffc8000b,0x00bff20e,
    0x3febff30,0x987fec05,0xf901bfff,0x75cc003f,0x01ff67ff,0xffc87fec,
    0x0ffc8001,0x00bff000,0xffdff300,0x2ffe400d,0x2e037fc0,0xb4ff81ff,
    0x44ffcc9f,0xbbb982ff,0x07ff2000,0x80007ff4,0x7e40effc,0x7fc4002f,
    0xfe80dff6,0x807ff90f,0x00881ffe,0xffc8fff4,0x2a7fe801,0x6f5c02ff,
    0x1005ff70,0x0000bff0,0x9ff93ffd,0x01dff700,0xfb80dff0,0xff6fc81f,
    0x7fbbff85,0x800fff60,0x3fee06ff,0xeffb8004,0x002ffc80,0x6feb7fcc,
    0x6c3ffe20,0x3fe200ff,0x007ff41f,0x3fea5ff7,0x327fd404,0x7ff80bff,
    0xf3017fe6,0x002ffcdf,0xfe93ff20,0x3ffea01f,0x80dff000,0xffa81ffb,
    0x6fec0ffa,0x3fa205fd,0x39ff5007,0xff333333,0xeff8800f,0x005ff900,
    0xffb5ffa8,0x43fff607,0x3fa03ffd,0x27fe41ff,0x7f41ffd0,0x3ffd101f,
    0xf701ffd8,0x02ffd8bf,0x5ff8fffa,0x7cc19980,0x837fcc6f,0x2001fff9,
    0x7fdc06ff,0x0dfdff01,0x805ffff7,0xfd803ff8,0xffffffff,0x2002ffff,
    0x3f202ffb,0x7fdc002f,0x117fff54,0x21ffdfb5,0x2a22effb,0x4c2ffffd,
    0x9512cfff,0xfff98bff,0x5fff510b,0x217fff10,0x4c0fffc9,0xb510cfff,
    0x05ff8dff,0xfd13ffc4,0x89ff903f,0xaa9bfff8,0xf2aaaaaa,0x1ffb80df,
    0x309fffb0,0x3001ffff,0xfff8809b,0xffffffff,0x32006fff,0x17fe407f,
    0xd8fff200,0xdfffffff,0x3ffa0ffa,0xadfffeff,0xfffa83ff,0x0dffffff,
    0xffffffa8,0x3ea03fff,0xffffffff,0xfffff502,0xf81dffff,0x3ffc405f,
    0x7f409ffb,0x3fffea2f,0xffffffff,0xb80dff7f,0xfff701ff,0x017ffe05,
    0x37ff7000,0x33333333,0x36003fff,0x17fe407f,0x83fff100,0x34effffb,
    0x7fe441ff,0x3fa2efff,0xffffb306,0xfd8809df,0x802cefff,0xdfffffd8,
    0x7ffe4400,0xff80bfff,0xabffc405,0x7fcc06ff,0xfffff50f,0xffffffff,
    0xf701bfef,0x3ffe203f,0x007ffb00,0x00ffe800,0x2009ff90,0x7fe402aa,
    0x17ff2002,0x98000a88,0x4c40001a,0x1510001a,0x00d44000,0x00099880,
    0x00000000,0x00000000,0x00000000,0x88017fe6,0x400007ff,0xf3002ffc,
    0x000003ff,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0xffc80000,0x17fec002,0x3200ccc0,0xffb802ff,0x004cc45f,0x41330cc4,
    0x7300aca8,0x00510159,0x00554000,0x40198000,0x3ba603ed,0xeeeeeeee,
    0x3a03eeee,0x4355300e,0x55cc4099,0x82220801,0xbbbbbbbb,0x3fe00001,
    0x6ffa8007,0x200fff80,0xccccdffc,0x5fffffed,0xe804ffa8,0x7ecffe7f,
    0x3e64ffff,0x4c2fffff,0x00000bef,0x0000ffe2,0x5409fb50,0x3fe607ff,
    0xffffffff,0x3e04ffff,0x4cfff207,0x3ffee6ff,0x6a80beff,0x7ffcfff1,
    0x002fffff,0x009ff500,0xf007ffe0,0x7fe401ff,0xffffffff,0x3fe04fff,
    0xf27fc406,0xffdffd9f,0xdfff37ff,0x7cc3ffff,0x0001cfff,0x0003ff88,
    0x4ffffb88,0x40ffff60,0xeeeeeee9,0x3eeeeeee,0x8627f822,0xdff33ffc,
    0x3ffffff2,0xfecbdfff,0x7fcfff17,0x02ffffff,0x03ffb000,0x013ff200,
    0x7e401fff,0xefffffff,0x7e400bce,0x87fee01f,0x710cffff,0x219fffff,
    0x7545ffc8,0x002dffff,0x000ffe20,0xfffffc98,0xfdff300b,0xc800000d,
    0xfdaee9df,0x7ccfff25,0xb79df96f,0xffffffff,0x99ffe2df,0x09999999,
    0x00000000,0x00000000,0x04ff9800,0xbfff1bfa,0x407fff60,0xff9306ff,
    0x80017fff,0xa8003ff8,0x02dffffe,0x2ff8efc8,0x3f600000,0x6fffffff,
    0x2db0fff2,0xfff9304c,0x00001bff,0x00000000,0x00000000,0x41ffa000,
    0x7ffc3ff9,0x40bff701,0x75c407fe,0x001cffff,0x22007ff1,0x0cfffffc,
    0x367ff100,0x8000005f,0xa81dffd9,0x00a7c1ff,0x000aa988,0x00000000,
    0x00000000,0x7dc00000,0x40ffc82f,0xff300fff,0x003fec09,0x3dffffb3,
    0x2eaaaaa2,0xaaaaacff,0xdffffb11,0x1ff70005,0x00007fea,0x3fddf300,
    0x7dc1ff30,0x00000002,0x00000000,0x00000000,0x3fe20000,0xff85ff85,
    0x80ffe607,0xb88007fc,0xfff34fff,0xffffffff,0x3fe69fff,0x3e0001cf,
    0x2627fc4f,0xffffffff,0x44ffffff,0x0ffaafe8,0x07f13fc4,0x00000000,
    0x00000000,0x00000000,0x41ffb000,0x6ff82ffa,0xc80ffe60,0xfc98007f,
    0xffff34ff,0xffffffff,0x3ffe69ff,0xff50002d,0x260ffb83,0xffffffff,
    0x44ffffff,0x213f65fb,0x0000043c,0x00000000,0x00000000,0x80000000,
    0x1ff62ff9,0xff3037fc,0x003fe407,0x19ffffd5,0x7d4ccccc,0x099999bf,
    0x7fffff71,0x437f4001,0x33223ff8,0xcccccccc,0x0a82cccc,0x000000e2,
    0x00000000,0x00000000,0x00000000,0xff8aff40,0x4c0dff04,0x1ff203ff,
    0xfffff910,0x3fe20017,0x3ffaa003,0x7cc01dff,0x00ffb03f,0x00000000,
    0x00000000,0x00000000,0x00000000,0x3ff20000,0xff01ffa8,0x01ffcc0d,
    0x3f6a0ff9,0x8002dfff,0x98003ff8,0x0beffffc,0xf500ffd8,0x0000005f,
    0x00000000,0x00000000,0x00000000,0x00000000,0x0dfb5ff1,0xff3037fc,
    0x2e3fe407,0x01cfffff,0x00ffe200,0xffffb880,0x00aaa0cf,0x00000355,
    0x00000000,0x00000000,0x00000000,0x00000000,0x0fffbfa0,0x3e606ff8,
    0x99ff203f,0x000befff,0x003ff880,0x9fffd500,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x1ffff500,0xf3037fc0,0x33fe407f,
    0x800005bf,0x00003ff8,0x00027e4c,0x00000000,0x00000000,0x00000000,
    0x00000000,0x44000000,0x7fc05fff,0x80ffe606,0x000627fc,0x000aa800,
    0x00031000,0x00000000,0x00000000,0x00000000,0x00000000,0x20000000,
    0x7fc02ffd,0x80ffe606,0x000007fc,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__arial_35_usascii_x[95]={ 0,2,1,0,1,1,1,1,1,1,0,1,2,0,
2,0,1,3,0,1,0,1,1,1,1,1,2,2,1,1,1,1,1,-1,2,1,2,2,2,1,2,2,0,2,
2,2,2,1,2,1,2,1,0,2,0,0,0,0,0,2,0,0,0,-1,1,1,2,1,1,1,0,1,2,2,
-2,2,2,2,2,1,2,1,2,0,0,2,0,0,0,0,0,0,2,0,1, };
static signed short stb__arial_35_usascii_y[95]={ 28,5,5,5,3,5,5,5,5,5,5,9,24,18,
24,5,5,5,5,5,5,5,5,5,5,5,11,11,9,12,9,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,32,5,11,5,11,5,11,5,11,5,5,
5,5,5,11,11,11,11,11,11,11,6,11,11,11,11,11,11,5,5,5,14, };
static unsigned short stb__arial_35_usascii_w[95]={ 0,5,9,18,15,25,20,4,9,9,12,16,4,10,
4,9,15,9,16,16,16,16,15,16,16,16,4,4,16,16,16,15,30,22,18,21,19,18,16,22,19,4,14,19,
15,22,19,22,18,23,21,19,19,19,21,30,21,21,19,7,9,7,14,19,7,16,15,15,15,16,10,15,14,3,
7,14,3,23,14,16,15,15,9,15,9,14,16,23,16,16,15,10,4,10,16, };
static unsigned short stb__arial_35_usascii_h[95]={ 0,23,9,24,29,24,24,9,30,30,10,16,9,4,
4,24,24,23,23,24,23,24,24,23,24,24,17,22,16,10,16,23,30,23,23,24,23,23,23,24,23,23,24,23,
23,23,23,24,23,25,23,24,23,24,23,23,23,23,23,30,24,30,13,3,5,18,24,18,24,18,23,24,23,23,
30,23,23,17,17,18,24,24,17,18,23,18,17,17,17,24,17,30,30,30,6, };
static unsigned short stb__arial_35_usascii_s[95]={ 255,109,245,215,103,1,234,197,36,62,184,
118,202,229,224,60,146,135,234,178,181,211,27,198,93,43,168,251,135,167,101,
24,72,1,215,228,40,162,145,70,115,250,21,89,73,50,30,160,1,119,224,
126,189,1,167,136,114,92,72,54,36,46,152,119,245,75,195,125,162,141,61,
110,46,250,1,209,246,77,206,108,199,183,158,92,20,60,60,221,173,143,190,
25,20,9,207, };
static unsigned short stb__arial_35_usascii_t[95]={ 1,82,106,1,1,32,1,125,1,1,125,
125,125,125,125,32,32,82,82,32,82,32,32,82,32,32,106,82,125,125,125,
106,1,106,82,32,106,82,82,32,82,56,57,82,82,82,82,1,82,1,57,
32,57,57,57,57,57,57,57,1,57,1,125,27,116,106,32,106,32,106,57,
32,57,32,1,57,57,125,106,106,1,1,106,106,82,106,125,106,106,1,106,
1,1,1,125, };
static unsigned short stb__arial_35_usascii_a[95]={ 139,139,178,279,279,446,334,96,
167,167,195,293,139,167,139,139,279,279,279,279,279,279,279,279,
279,279,139,139,293,293,293,279,509,334,334,362,362,334,306,390,
362,139,251,334,279,418,362,390,334,390,362,334,306,362,334,473,
334,334,306,139,139,139,235,279,167,279,279,251,279,279,139,279,
279,111,111,251,111,418,279,279,279,279,167,251,139,279,251,362,
251,251,251,167,130,167,293, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_35_usascii_BITMAP_HEIGHT or STB_FONT_arial_35_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_35_usascii(stb_fontchar font[STB_FONT_arial_35_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_35_usascii_BITMAP_HEIGHT][STB_FONT_arial_35_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_35_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_35_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_35_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_35_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_arial_35_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_35_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_35_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_35_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_35_usascii_s[i] + stb__arial_35_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_35_usascii_t[i] + stb__arial_35_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_35_usascii_x[i];
            font[i].y0 = stb__arial_35_usascii_y[i];
            font[i].x1 = stb__arial_35_usascii_x[i] + stb__arial_35_usascii_w[i];
            font[i].y1 = stb__arial_35_usascii_y[i] + stb__arial_35_usascii_h[i];
            font[i].advance_int = (stb__arial_35_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_35_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_35_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_35_usascii_s[i] + stb__arial_35_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_35_usascii_t[i] + stb__arial_35_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_35_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_35_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_35_usascii_x[i] + stb__arial_35_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_35_usascii_y[i] + stb__arial_35_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_35_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_35_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_35_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_35_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_35_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_35_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_35_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_35_usascii_LINE_SPACING
#endif

