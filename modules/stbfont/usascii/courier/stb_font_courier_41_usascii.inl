// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_courier_41_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_courier_41_usascii'.
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

#define STB_FONT_courier_41_usascii_BITMAP_WIDTH         256
#define STB_FONT_courier_41_usascii_BITMAP_HEIGHT        144
#define STB_FONT_courier_41_usascii_BITMAP_HEIGHT_POW2   256

#define STB_FONT_courier_41_usascii_FIRST_CHAR            32
#define STB_FONT_courier_41_usascii_NUM_CHARS             95

#define STB_FONT_courier_41_usascii_LINE_SPACING          19

static unsigned int stb__courier_41_usascii_pixels[]={
    0x00c7f980,0x00800000,0x20008200,0x00099999,0x99800660,0x224c0199,
    0x0020003a,0x37bd9500,0x2b32a200,0x332ea000,0x9998801b,0x01999999,
    0x33330771,0x33333333,0x02aea013,0x23fcc000,0x6c00004e,0x0067f402,
    0x27b2fd98,0x3fffe06c,0x13e0007f,0xffffd4e8,0x363dc01f,0x7f64c006,
    0x32001cdf,0x02ffedff,0x7fff7fdc,0x77ff5401,0x3600cffe,0xffffffff,
    0x0ffb83ff,0x3fffffe6,0x2fffffff,0x17f67f4c,0x23fcc000,0x200000fb,
    0x1fe4404e,0x9d177cc0,0x56fc13ea,0xf70001aa,0x5447f201,0x3200fcaa,
    0xf9002ec6,0x5ffb779d,0xc985fd00,0x419f903f,0xbfb02fd9,0x6c0df703,
    0xaaaaaaae,0x1ffb80aa,0x2aaaafe6,0x2fbaaaaa,0x03f50be2,0x447f9800,
    0x3e00004f,0x900f7004,0x07f49d0d,0xe80001fc,0x540df105,0x9d1b200f,
    0x405fd100,0x07ea04fc,0x05f987d8,0x05f503f6,0x0bb04f98,0x30ffdc00,
    0x87e6001f,0x000b905c,0x0007e400,0xbffffb30,0x05f10533,0x2e4e83f8,
    0x0003f84f,0x7f901fa8,0xbb007d40,0x1fd804e8,0xbd04fb80,0x36c1fa80,
    0x0020fe60,0x005d83dc,0x0703fea0,0x40ba3e40,0x20000078,0xf70003f8,
    0xfffb55bf,0x7f00fe0d,0x07fc49d0,0x3a0000fe,0xa80ff105,0x7f17600f,
    0x2001fa80,0x007dc0fb,0x007f31fc,0x7cc000dd,0x20005d81,0x20000ffa,
    0x7880f44e,0x3e400000,0x8067d400,0x807f06fb,0x7e44e83f,0x20001fc3,
    0x09f702fa,0x13a00fa8,0x005e807f,0x01b62fc4,0x001f7274,0x2a0003f5,
    0x0005d80f,0x98001fea,0x6b82e42f,0xaaaaa880,0x4c1aaaaa,0x07f4003f,
    0x01fc1b60,0xf313a0fe,0x40003f8d,0x003fa06d,0x127c01f5,0x00fdc05f,
    0x09d0fdc0,0x03649d30,0xd0002f98,0x8001760d,0x2e0007f9,0x7cc2f887,
    0xffffc801,0x84ffffff,0x13e2006d,0x01fc0620,0x3a13a0fe,0x8000fe1f,
    0x0bf302f9,0x1fc01f50,0x036405f1,0x0fe2f880,0xb27fff54,0x00fe200b,
    0x2ec0fea0,0x98015553,0x17a0007f,0x1ff5f7d4,0x33333300,0xf309f333,
    0x00fe2005,0x3f807f00,0x24fc84e8,0x1b60003f,0xfa804fc8,0x37f332a0,
    0xbccdfdcc,0xe80013a0,0xdf905f14,0x02749d35,0x64c009f0,0x3f3b604f,
    0x00dfffff,0x22000df1,0x2f2a202f,0x001db881,0x00dd04f8,0xf00007fc,
    0x4e83f807,0x00fe6fb8,0xfd01fc40,0x6c1f5007,0xffffffff,0x3e1effff,
    0x4d760003,0x3a1fdc1f,0x4e800fe4,0x1ffffec0,0x46f7ff60,0xf881ffb8,
    0x01f70006,0x59fd7100,0x5413e000,0x3bf5001f,0x9813a000,0xfa84e82f,
    0x64000fe7,0x4017fc07,0x43f300fa,0x05f100fa,0x1f9b6400,0x7f27437c,
    0x26027400,0x4c04ffec,0xf8374401,0x00bb0005,0x00e7f5cc,0xbd027c00,
    0x6fff5400,0x0fd8009b,0x09d01f90,0x00fe1ff3,0xf880fe20,0x00fa800f,
    0x203dc3f3,0x5b60003f,0x20fe21f9,0xe800fe4e,0x06fd4004,0x20fe6000,
    0x3f88005f,0x0e7f5cc0,0x813e0000,0x5cc001fa,0x200dfffd,0xfd50cfe8,
    0x7fc13a07,0xf90007f1,0x803fcc01,0x41f500fa,0x0027407b,0x887e69d0,
    0x0fe4e82f,0x98004e80,0x6c0000ee,0xa8005f85,0xceec880f,0x3e000001,
    0x0002f404,0xd807fae6,0x03ffd1ff,0xf8ffc13a,0x027c4003,0x7d401fe6,
    0x06c8f500,0x7f0002ec,0xd0df07e6,0x9d002749,0x00be2000,0x07d0f900,
    0x2ea0db00,0x017b9501,0x5c04f800,0xd880000f,0x40bfb80f,0x109d07e9,
    0x000fe1ff,0xff8801f7,0x510fa800,0xb555fb55,0x7c81555d,0x265f3000,
    0xd16fd41f,0x7f0036c9,0x002f4000,0x00221ea0,0xb1000fe0,0x003dd79f,
    0x27c027c0,0x82f88000,0x207ea05e,0x3e7f984e,0x802fc003,0x0fa801ff,
    0xfffffff9,0x87ffffff,0x7d8003f8,0x3fee0be2,0x0f90ffff,0x80007e20,
    0x3dc0007b,0x01f98000,0x035c2e40,0xf7009f00,0x9d000201,0x1fc407f0,
    0xf37d4274,0x00fd4007,0xfa802fe8,0x05e8d900,0x26000fc8,0xa881fc2f,
    0x1f70cccc,0x0001f700,0x360003dc,0x0d900006,0x5d01f880,0x2013e000,
    0x007d03f8,0x201fc1fc,0xfc84e83f,0x5e800fe5,0x200ff600,0xe8bb00fa,
    0x005f8804,0x009d0dd1,0x3a013e20,0x02ec0006,0x0009f100,0xd30013a0,
    0xf80025c0,0x3e0f9004,0x81fb801f,0x741fc03f,0x0fe2fd84,0x7000fd40,
    0x01f500bf,0x2007f176,0x3a600efa,0x0007c81f,0x2f9803f6,0x45f50004,
    0x1f9000c9,0x1f980010,0x9903cc00,0x4013e000,0x1eff83f8,0x1fc13ee0,
    0x213a0fe0,0xe801fc7f,0x03fc4006,0x44e807d4,0x3fea003f,0x03bee61b,
    0x980017cc,0xb8df104f,0x2fd400cf,0xf700bbe6,0x005ff907,0x17c001ee,
    0xf80017c4,0x3e1b6004,0xccbdffec,0x00fe04ff,0xfa89d07f,0x7cc01fc4,
    0x02fc8002,0x24e807d4,0x64c002f8,0x04ffffff,0x70000ed8,0xfd5115bf,
    0x157ff703,0x2037f662,0x310adfe9,0xfff30bfb,0x0013a00d,0x0bb3175c,
    0x30027c00,0xd951a85f,0xf8037bff,0x2741fc03,0x007f07fa,0x3e6000db,
    0xf807d406,0x4000be23,0x2001befa,0x19100ef8,0x3ffffea0,0x3fb2200e,
    0x802fffff,0xffffffdb,0x017ffe02,0xf70000fc,0x0001bfbd,0x1b60027c,
    0x7f002740,0x24e83f80,0x403f86f9,0x3a0003f9,0x403ea01f,0x0007e62f,
    0x880677ee,0x9acffa81,0x4c00efba,0x544000ab,0x730001ab,0x05710035,
    0x98800000,0x7c40000a,0x017cc003,0x0f980274,0xb2742ec0,0xd807f05f,
    0x2fd40007,0x5f101f50,0xb1000fcc,0xbdffffff,0x260bfb57,0x0cfffffd,
    0x00000000,0x00000000,0x00000000,0x20007ee0,0x804e806e,0x2f9805d9,
    0xf06f8a74,0x001fc407,0xfa807f40,0x3e61f880,0x37bf2000,0xffecb9ab,
    0x0133003e,0x4ccccccc,0x99999999,0x99999930,0x99999999,0x05999999,
    0x00000000,0xfd000000,0x007ea000,0x1efd809d,0x3a3dfb00,0x3fe03f74,
    0x03f25fff,0x6cfe6000,0x100fffff,0x00100010,0xb0000011,0xffffffff,
    0x25ffffff,0xffffffea,0xffffffff,0x005fffff,0x00000000,0x1fe40000,
    0xe807b000,0x40015403,0x0a6150b8,0x23ccccc8,0x2a00002d,0x09999951,
    0x00000000,0xeec80000,0xeeeeeeee,0x0002eeee,0x00000000,0x20000000,
    0xfdccccca,0x8000002f,0x00000009,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x37bbbbae,0x0000001b,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x201bcb98,0x8801bca8,0x00000199,0x00199880,
    0x40159973,0x00001998,0x88002200,0x540aceca,0x4fc801aa,0x26666200,
    0x55530009,0x566e5441,0x6edd4000,0x2aaa20ab,0x055554c1,0x01555530,
    0xfd88004c,0x982ffeff,0x03efffff,0x003ffff1,0x7fcc0000,0x3f2200ff,
    0xa83ffeef,0x00007fff,0x7fffec40,0xffa81def,0xf14ffedf,0xfc803fff,
    0x3fffe004,0xff8804ff,0xbdff71ff,0x9801dffd,0xffedeffe,0x4cffff52,
    0x104fffff,0x10bfffff,0xfa80bffd,0x7d40c1bf,0x40bf6a0d,0x0001fba9,
    0x7e54c000,0x910ffa00,0x0fb5509f,0x7fd40000,0x2dccaabd,0x7d406fe4,
    0x8009bf9d,0x2a6004fc,0x1004faaa,0x19f93f53,0x2e01df50,0xbfd881ef,
    0x6c4099fa,0x64c4019e,0xfffc80af,0x01bfb02f,0x1f502fc0,0x0000fcc0,
    0x00fa8000,0x17dc01f9,0x000007b8,0x4c001df1,0x7f74404f,0x013f2002,
    0x98009d00,0x6c401fef,0x402fcc0e,0x2600fefa,0x817a002f,0xb82ffffd,
    0x07dc003f,0x1f981b60,0x50000000,0x007f101f,0x001ee0db,0x0017d400,
    0x7fcc01ba,0x80000002,0x7fcc004e,0xe8bf1003,0x03ff2006,0x3ea00db0,
    0x1bffe601,0x3a0013e6,0x302f9804,0x0000003f,0x3ea03ea0,0xb80fa800,
    0xd9000007,0x001fa800,0x00000bf2,0x30013a00,0x27a800df,0x7f4001f9,
    0x4017cc00,0x02b8805e,0x7f0001fd,0x7cc13a00,0x00000001,0x00f701f5,
    0x01ee07e6,0x00364000,0x5f5001ee,0xd0000000,0x03f98009,0x07b8fc40,
    0xd800fc80,0x000fd406,0x2000be60,0x0f7002f8,0xbb7307e6,0xda880037,
    0x407d41bd,0x06b800f8,0x676544f7,0xaaa8800b,0xaaaaaafd,0x2002ec0a,
    0x2aa602f9,0x40001aaa,0x17cc004e,0x06c9fc00,0x9800fb80,0x0017a01f,
    0xe8001ea0,0x301f9003,0x37ffea3f,0x4400dffe,0xfffdeffe,0x13a01f51,
    0x9bdc13a0,0x2ffedfff,0x7ffffec0,0x5fffffff,0x3e600364,0xfffff102,
    0x4e80009f,0x0017cc00,0x8006c9fc,0x0bb000fb,0x200007ea,0x4009885c,
    0x1ff9805c,0x0dfa9f98,0xd101ffa8,0x55fb105d,0x40fee01f,0x7f701fd8,
    0x2fc8839f,0x4f6cccc0,0xb8199999,0x017dc007,0x09d33331,0x4004e800,
    0x7c4004f9,0xd8001f52,0x03f3000f,0x3a0000bd,0x3bfff6e4,0xe803f501,
    0xfdf982fe,0x44374403,0x6fdc00de,0x2fbea00f,0x201efbaa,0x37c03ffb,
    0x9800d900,0x0bf6001f,0x80009d00,0x37cc004e,0x7cc3ee00,0x03fe2002,
    0x0fd45d80,0x41aaaa80,0x535bf92f,0x1dd107fb,0x20be3b60,0xf3004ff9,
    0xb000fd89,0xffb801ff,0x5c01ffff,0x00fb804f,0xdd000d90,0x00bfea00,
    0xe80009d0,0x27fcc004,0x7ec4f980,0x01ffb000,0x0bd0fcc0,0x03fffe60,
    0x3205f75f,0x8aee881f,0x07f0fea8,0x5c001df3,0x8800be0f,0x37ea00ff,
    0x00eeba9b,0x17c401ee,0x88006c80,0x37e600df,0x0274002f,0x30013a00,
    0xe9807fbf,0x400ef886,0x4000fdfc,0x2003f35e,0xde83fffc,0x9837402f,
    0x11dffffe,0x009f305f,0x00f31f98,0x3ee01fb0,0x5c07f202,0x005f1007,
    0x7d4001b2,0x33f260ae,0x274002f8,0x0013a000,0x13df73f3,0x980f7dcc,
    0x3aa21bff,0x4000faaf,0x2006d9f9,0xbfb06ffe,0x4403f300,0x417d40aa,
    0x3f8003f9,0x1f7000d7,0xdb007f10,0x7c401ee0,0x000d9002,0x7fffff44,
    0x8005f13f,0x2740004e,0x74c7e600,0x04ffffff,0xfffffc88,0x001f51ef,
    0x2005fdd0,0xf701fff9,0x005f1001,0x3e603ee0,0xbb4e8002,0x701f5000,
    0x203e200d,0x05f1007b,0x20001b20,0x7c41bca9,0x00274002,0xf30013a0,
    0x09bca883,0x55dd4400,0x40007d40,0x3ee006f9,0x801aa05f,0x0dd0003f,
    0x3e000fe6,0xf9000d72,0x7c00bb01,0xf1007b83,0x001b2005,0x00be2000,
    0xe80009d0,0x00fcc004,0xfa800000,0x02f98000,0x9803ffa0,0x02f8801f,
    0xf303fb80,0x31f98009,0x0fd8001f,0x13a004e8,0x17c401ee,0x00006c80,
    0x4001f980,0x2740004e,0x0007e600,0x07d40000,0x10036c00,0x07f007ff,
    0x88003f30,0x03fe605f,0x01fc7c80,0xd901ff30,0x2e0be200,0x005f1007,
    0x000001b2,0x13a001ee,0x8009d000,0x000001f9,0x8001f500,0x3ea002f9,
    0x801f7006,0x7f44006d,0x017fe600,0x07f217d4,0x5407ff40,0x80fc802f,
    0x05f1007b,0x00001b20,0xd000bf30,0x04e80009,0x0000fcc0,0x00fa8000,
    0x220036c0,0x0bf1000d,0xf50017d4,0xfcf9803f,0xd82fd404,0x33f6201e,
    0x403fb00f,0x00f703fa,0x36400be2,0xdf300000,0x009d0001,0x4c004e80,
    0x0000001f,0x4c001f50,0x8000002f,0xf930aef9,0x2e623509,0x2aa00dfd,
    0x0aef99fb,0xd8037f26,0x3baa21cf,0x442abfa8,0xfb311bfe,0x55fb550b,
    0x59f75301,0xfdaaaa85,0x02aaaaaa,0xfdcccca8,0x2aa200df,0xaadeaaaa,
    0x5510aaaa,0x55bf5555,0x66415555,0x02cccdfd,0x99970000,0x644799fb,
    0xccfecccc,0x4c000004,0x03fffffc,0x5bfffffd,0x1ffff880,0xffffffb1,
    0x3ffb2007,0xff50dfff,0x3ffee0df,0xfe882fff,0xfc83ffff,0x3e26ffff,
    0xffffffff,0x5c01ffff,0x02ceeeee,0xffffffb8,0xffffffff,0xffffff72,
    0xffffffff,0x3bbbb623,0x00003eee,0xdddddd90,0x7776c4bd,0x00deeeee,
    0x37300000,0x00ab8801,0x1bb98000,0x03771000,0x1ab98800,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000400,0x06200333,0x98002000,0x83cccccc,0x0ccccccc,
    0x40000530,0xccccccc9,0x3224cccc,0xcccccccc,0x000002bc,0x00026620,
    0x00001000,0x01000031,0x55e5cc00,0xfffd5000,0x8006a3bd,0xb880fffa,
    0x03effffe,0xdfff9510,0xdd30e63b,0xdb09dddf,0x201bdfdd,0x2a00006d,
    0xffeeeeee,0x3b665eee,0xeeeeeefe,0x44002eff,0x80cbefec,0x0006fffb,
    0x7fff64c0,0x3ae2001d,0xdb88004f,0x0a63deff,0x7ff7ffcc,0x37fa202f,
    0xecfecaab,0x3f37a004,0x55effe40,0x200dfdba,0xecaceffd,0xf306ddff,
    0x403dc001,0x0000006d,0x01ee009d,0x7c007fb3,0x80efdbdf,0x0006daa8,
    0x2ef7fee0,0x7100dfed,0x009fbffd,0xcabdffd8,0xa86c9efd,0x3f620bef,
    0x5c03fd03,0x1f7004ff,0x00df81f5,0x3fa217ea,0x1ffea00b,0xf70007cc,
    0x0000db00,0x5c013a00,0x003f9007,0x900183f7,0x3f60000d,0x203bea04,
    0x09d0adfe,0xb3017e40,0x05fa8ddf,0x07ee0fdc,0x22013f60,0x3f81f54f,
    0x7ec2fb80,0x20ff1001,0x1ee000f9,0x00001b60,0x7b802740,0x3a017a00,
    0x01b20004,0x200bf200,0x9d0085fa,0x4003f200,0x007ec6fc,0x4017636c,
    0x0fc804f9,0x002e81f5,0x001fd49f,0x007cc1b2,0x2aa60f70,0xaaaaaaee,
    0xe80000aa,0x400f7004,0x017c407b,0x8000d900,0x3ea003f9,0x7009d002,
    0x26f8005f,0x1f5002f8,0x07b00274,0x03ea3f98,0x1b65d800,0x7cc0a600,
    0x261ee000,0xffffffff,0x005fffff,0xf7004e80,0x7c036400,0x01b20003,
    0xd000dd00,0x2013a00f,0x46c8006e,0xd87e6001,0x37400005,0xd80003ea,
    0x00000fe5,0x3dc001f3,0x99ed9988,0x00199999,0x2e009d00,0x200fe007,
    0x1b20007c,0x06aaaaa2,0xf50005f5,0x8809d001,0x0188001f,0xfb87ea00,
    0x3f500001,0x10000fa8,0x0007e65f,0x4001f300,0x006d807b,0x009d0000,
    0x3f6201ee,0x003f8800,0xfff70d90,0x007b8fff,0x13a00ba0,0x00000f50,
    0x3fa1f600,0x85e80002,0xe98000fa,0x00001ee7,0x7b8003e6,0x00006d80,
    0x2e009d00,0x0bfee607,0x8000fd80,0x33df706c,0x20006c81,0x404e804d,
    0x0000006c,0xfc882fa8,0x20009bdf,0x00fa80fb,0xd87bee20,0xf9800005,
    0x201ee000,0x0000006d,0x3bee009d,0xdfffeeee,0xbffd1001,0x43640310,
    0x13a00dfa,0xe806c800,0x0002ec04,0x017e6000,0x9dfffb71,0xa827c403,
    0xffc8800f,0x0002ec0c,0x70007cc0,0x000db00f,0x009d0002,0x3bbbbbee,
    0x3ea002ff,0x7e42fa9e,0x4fc8d907,0x20003f80,0x404e807b,0x0000005d,
    0x22001be6,0xfb02feca,0x6c007d40,0x00bb00cf,0x13333333,0x5c001f30,
    0x0006d807,0x0274005d,0x3ff507b8,0x1db17600,0x26c80efc,0x09d003fd,
    0x7403dc00,0x0002ec04,0x00ef9800,0x4c3fc800,0x003ea02f,0x80d90176,
    0xfffffffc,0x0007cc2f,0x00db00f7,0x4e800fe0,0x7440f700,0x217c402f,
    0x403f54f8,0x002fe8ec,0x5c800176,0x36c04e80,0x7cc00000,0x3200000e,
    0x3ea03746,0x5c05c800,0x55554407,0x1f982fda,0x3601ee00,0x007f0006,
    0x07b80274,0x3ea00fd8,0x06c9fb80,0x007ff7e4,0x74000d90,0x5c04e803,
    0x4c000007,0x400000df,0x99bf30f9,0x9fb99999,0x20044019,0x7c8000fa,
    0x6e800be0,0xf0006d80,0x8027c007,0x06e8807b,0x7f7407ea,0x74f7e403,
    0x01f5000e,0xd003f100,0x001fa809,0x00bf5000,0x2f880099,0xddddddd1,
    0x01bdfddd,0x002f8800,0x013207c8,0x36c027c4,0x3003f800,0x01ee005f,
    0x4f981fcc,0xc801ff30,0x2003ba26,0xfc8004f8,0xe804e800,0xfa800004,
    0x800fb005,0x7d4001f9,0x3f600000,0x503e4000,0x03f7003f,0x3e000f90,
    0x001f9004,0x0fc801ee,0xff701fd0,0x7446c801,0x01fb800e,0x74017e20,
    0x002fa804,0x05fb80b8,0xd800bf60,0x00fa8007,0x5f880088,0x3603e400,
    0x013ee01e,0x1cc01fd4,0x7dc01bf9,0x801ee002,0x7ff105f8,0x5dd9f711,
    0x3a21b205,0x00ee800e,0x3a001fb0,0x001fb004,0x13ee0fec,0x003ffb00,
    0xf50005f7,0x77ff4401,0x006fd400,0xbfd807c8,0x00bf9510,0x2621cfe8,
    0x77d46feb,0x09f9511b,0x55fb5510,0xabfa8035,0x7ffff4c0,0x320dff34,
    0x801dd106,0x3a201ef9,0x013a002f,0x22017f44,0x027dc2fe,0x4efe76c0,
    0x013faa20,0xf5007d40,0xd3007fff,0xeb98359f,0xfffb006f,0x10007fff,
    0xfffffffb,0x3ff6205b,0x3002ffff,0x9fffffff,0x203ffd00,0x64000ab9,
    0x003ba206,0x5cc37fd1,0x274002fe,0x15bfd100,0x907bf2a2,0xb8fc007f,
    0xffffff54,0xaa8005df,0xf302bfca,0x64003fff,0xffffffff,0xbb98001d,
    0x54400009,0x4c001abb,0x000009bb,0x80000000,0x2a06daa8,0x200aaefc,
    0xdffffffc,0x2aaaa601,0xaaaaadfa,0x3fffee00,0xdf80cfff,0xaaaaaaaa,
    0x2202fbaa,0x0001abba,0x3ffffffd,0x00073260,0x04d65cc4,0x00000000,
    0x00000000,0x00000000,0x037ffd40,0x07fffffd,0x00157730,0xfffffffb,
    0x007fffff,0xf8035751,0xffffffff,0x002fffff,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0xa8000000,0x02cccccc,
    0x3333332e,0x99999930,0x99999999,0x33322199,0x99104ccc,0x66479999,
    0x33202ccc,0x33223ccc,0x442ccccc,0x643ccccc,0x2e02cccc,0x9973cccc,
    0x99999999,0x66644399,0xcccb83cc,0x3332a0cc,0xaccccccc,0x33333200,
    0xcccccccc,0x9910cccc,0x99999999,0x41999999,0xcccccccc,0x026001bc,
    0xeb9aaaa8,0x203eeefe,0x1eefeeed,0xddddddf7,0xddddddff,0x3bff621f,
    0xddb305ee,0x3f629dfd,0x3b603eef,0x3b664efe,0x443eeefe,0x224effed,
    0x203eefed,0xd94effed,0xddffdddd,0x76c45ddd,0xeed84eef,0x3bae0def,
    0xeeeeeeff,0xeed80cff,0xeeeeeeef,0x30feeeee,0xddddfddb,0xfddddddd,
    0x7777f6c1,0x04fffeee,0x2a17ffa2,0x3e61ffff,0x40fb8001,0x5413a07b,
    0x8002ec0f,0x04f982f8,0x7b80dd10,0xe809f700,0x009f1005,0x07b8013a,
    0x4e805f10,0x403fee20,0x3ea001f9,0x2a007b80,0x2603f80f,0xffc80efb,
    0x7ffe42ff,0xe8004e85,0x13a07b84,0x01b207d4,0xfa80fc40,0x400fd802,
    0x03fc807b,0x6d803f98,0xb8013a00,0x805f1007,0x05f8804e,0x7d4003f3,
    0x2a007b80,0x8803f80f,0xffffd86e,0x40ffff42,0x0fcc007b,0x209d03dc,
    0x003dc0fa,0x3f200f98,0x2007ee01,0x017ec07b,0x7d401f90,0x8013a001,
    0x05f1007b,0x3f5004e8,0x54003f30,0x2007b80f,0x003f80fa,0xfff987f1,
    0x82fffc46,0x1b2002f8,0x209d03dc,0x407d40fa,0x07a80ffb,0x3f980ee8,
    0x3620f700,0x05e8002f,0x4e8009f1,0x4401ee00,0x0027402f,0x003f307f,
    0x03dc07d4,0x07f01f30,0x2e207e40,0x00fffa82,0x03f80176,0xa82740f7,
    0x6c0fcc0f,0x807b82fe,0x02fc45f8,0x3fd10f70,0x20fe6000,0x274000fd,
    0x2200f700,0x0027402f,0x003f309d,0x800f7018,0xe8007f01,0x13ff6004,
    0xf5001f50,0x4e816601,0x03f10d10,0x0d90bd7f,0x0ee8fea0,0xdd11ee00,
    0x0fc80001,0x3a000bea,0x401ee004,0x027402f8,0x1f982f88,0x3dc00798,
    0x0fe005b8,0x7c00d900,0x03f800ff,0x3a0005d8,0x542f8004,0x05d87b9f,
    0x07f27f20,0x77ccf700,0x2bd00000,0x9d0005e8,0x8803dc00,0x8027402f,
    0x81f980fb,0x1ee000fa,0x07f00364,0xf3007b80,0x01b2007f,0x740005f1,
    0x643f8004,0x04e83f37,0x001ffec0,0x0dffabdc,0x95f30000,0x13a0001f,
    0xaaaafb80,0x2fbaaaaa,0x7e402740,0x5559f304,0x5c001f95,0x6daaaaaf,
    0x5000fe00,0x0ff7001f,0xf700fcc0,0x004e8000,0x7f2744e8,0x7cc003f8,
    0xf7f70007,0x0007ff7b,0x000bff20,0x3ee004e8,0xffffffff,0x27402fff,
    0x205fdb98,0xfffffff9,0x3fee000f,0x006fffff,0x1f3000fe,0x8005f900,
    0x0013a05e,0xbb0009d0,0xf8db17c4,0x27f74002,0x127fdc00,0x10000bfd,
    0x4e8000bf,0x4401ee00,0x7fff402f,0x01efffff,0x07d40fcc,0x1b20f700,
    0x4c003f80,0x0040440f,0x7cc07dc0,0x02740001,0x41f73640,0x003f10fa,
    0x017dcfe4,0x7dc0fee0,0x04e80002,0x70027400,0x00be200f,0x579999dd,
    0x207e6003,0x1ee000fa,0x07f00364,0x3fa27a80,0xf880005f,0x80006d83,
    0x27b8004e,0xf997c46d,0x6c5f7000,0x01ee000f,0xe80001f9,0x02740004,
    0x3e200f70,0x00027402,0x01c40fcc,0x014c1ee0,0x5c8007f0,0x00bffff2,
    0x7f11b200,0x009d0000,0x741fcf50,0xf3001f54,0x2006e889,0x02f4407b,
    0x00013a00,0x03dc009d,0x27402f88,0x00fcc000,0x4007b800,0x4003f849,
    0x3ffff63e,0x1f980002,0x200003ee,0x8f98004e,0xf77c81f9,0x260dd100,
    0x00f7004f,0x740003f5,0x02740004,0x3e200f70,0x00027402,0x80000fcc,
    0x43dc007b,0x8be6003f,0x0007fff9,0x005e93a0,0x10009d00,0x3e60f93f,
    0x0fd806c9,0x2e00fea0,0x000bd007,0x3a000274,0x401ee004,0x027402f8,
    0x000fcc00,0x64007b80,0xf1003f87,0x0005710d,0x05f37b80,0x0013a000,
    0x7f02f57c,0x02fb80bb,0x3dc01fc8,0x0000fb80,0x4e80009d,0x4401ee00,
    0x0027402f,0x0000fcc0,0x3e4007b8,0x7f4401fc,0x20000001,0x0007caf8,
    0x7c0013a0,0x3b7603fc,0x8013e604,0x01ee00ee,0xe8001fc4,0x02740004,
    0x3e200f70,0x00027402,0x80000fcc,0x43e4007b,0x3faa203f,0xaaaaa982,
    0x0aaaaaaa,0x013fb600,0x7d5554c0,0x800aaaad,0x3ea00ffe,0xafea883f,
    0x3eeaa02a,0x3f2aa22d,0x3b601aaa,0x555301aa,0x15555bd5,0xf5555530,
    0x4155555b,0x82aafcaa,0x22acfbaa,0xaaadeaa9,0xbaa801aa,0x02aaaacf,
    0x55fb5510,0x55555555,0x6fd54fb5,0xffdaaaaa,0xffff701e,0xffffffff,
    0x0ffd4005,0xffffb800,0x01ffffff,0x7c406fd8,0xffffa82f,0xffff306f,
    0x3ffe63ff,0x2604ffff,0xff704fff,0xffffffff,0xfffffb05,0x7fffffff,
    0x37fffff4,0x37fffff4,0xfffffff9,0xfe8807ff,0xffffffff,0xffff9801,
    0xffffffff,0xff17ffff,0xbfffffff,0x99fb8037,0xfa999999,0x0000000e,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x7b800000,0x6540ee80,0xcccccccc,0x33220ccc,0xcccccccc,0x991000ac,
    0x01999999,0x03cccc80,0x6666665c,0x00b33320,0x2a4ccca8,0xcccccccc,
    0x8000002c,0x00000262,0x500004c0,0x04379db7,0x5e765cc0,0x55554402,
    0xaaaa9800,0x1fd80f50,0xeeeeefc8,0x21feeeee,0xeeefeed9,0x04ffeeee,
    0xfeeeed88,0x76c003fe,0x3b602ffe,0xb10defee,0x7c00dffd,0x3baa5eff,
    0x3eeeefee,0x3aa00000,0x0019fb0f,0x004e8000,0xedeffe98,0x103e8dff,
    0xffdbdffb,0x3fffa01d,0x7ffcc07f,0xfc8024ff,0x3200f901,0x700f700f,
    0x3f3000bf,0x3e6000d9,0x01f5006f,0x200bebea,0x4c01fafa,0x8000001f,
    0x3221dfe9,0x000003ff,0xbf70013a,0x13ffaa03,0x7540bfea,0x9afa882f,
    0x1fc98800,0x6405f900,0x203f9807,0x07f7007b,0x03f36c80,0x09f5f300,
    0x3ea01f50,0x9de805e8,0x00fcc01f,0xdfb10000,0x177e4405,0x02740000,
    0xd1007f30,0x006f889f,0x00fe03fb,0x7dc01760,0x2203e403,0x003dc05e,
    0x23f800dd,0x9f98004e,0x07d400fb,0x00fa8fa8,0x007e67e6,0x000003f3,
    0x4007ff91,0x0001efd9,0x5e8013a0,0xdb13e600,0xd836c001,0x0fe05504,
    0x32013ea0,0x2007ec07,0x01ee007b,0x01ee0fa8,0x02f47e60,0x87d403ea,
    0x7cdb604e,0x000fcc01,0x013fee00,0x00dfea80,0x5004e800,0x22e8003f,
    0x7cc002f9,0xffa86c82,0x2600fc40,0x40d7005f,0x07b802fa,0x6d801b60,
    0x260017c4,0x5405f51f,0x2e1f500f,0xf32f880f,0x001f9803,0x019fd500,
    0x33fee000,0x013a0000,0x54000364,0x507d0007,0x42fec81f,0x17e200fa,
    0x13e20100,0xf8803dc0,0xb07f1004,0x21f9800b,0x403ea06d,0x907f10fa,
    0x2600fccf,0x74c0001f,0x800001df,0x0003ffc8,0x0136009d,0x3bbbf200,
    0xeeeeeeee,0x2f885fee,0x1b22edfc,0x2600ee88,0x400dd001,0x0ef9807b,
    0xf501f700,0x10fcc001,0x403ea07f,0x3e1b20fa,0xf3007e64,0x3f620003,
    0x8000002e,0x4002efc8,0x007f004e,0xddddf900,0xdddddddd,0xa8fa09dd,
    0x13a0fb8f,0x2ec00ee8,0x7000fdc0,0xb755555f,0x74001bff,0x9800fe05,
    0x5407e41f,0x441f500f,0xf983ea2f,0x000fcc01,0x0001ffdc,0x6ffcc000,
    0xffffff50,0xffffffff,0x0017a1ff,0x00001ee0,0x5f16c976,0x01fd817c,
    0x1fcc05d8,0x3fffee00,0x0dffffff,0x6405f100,0x107e6006,0x201f50bf,
    0xbd2ec0fa,0x7cc01f98,0x7ff70001,0x4c000000,0x55541dfe,0xaadfaaaa,
    0x1b22aaaa,0x007e6000,0x1fcf7000,0x3207e6bb,0xaaaaaacf,0x2205eaaa,
    0x07b8006e,0x00bf6ea6,0x03f301ee,0x3ea07e60,0xfa807d41,0x0fccfcc0,
    0x3f3007e6,0x77e44000,0x22000002,0xe8001efd,0x003f5004,0x0000bd00,
    0x20fa9f98,0xfd07b8fa,0xffffffff,0x7e40bfff,0x007b8000,0x5dd013ee,
    0xf5555555,0x407e6009,0xa807d46e,0x86dce80f,0x0fcc01f9,0xfb300880,
    0x4400003d,0x20002ffc,0x01ba004e,0x1fcc3b30,0x32be0000,0x02e5fc46,
    0x17d40000,0x01ee0710,0x7fcc0f70,0xffffffff,0x1f9800ff,0x07d47f30,
    0xffa80fa8,0x4c01f982,0x809b001f,0x0000dfea,0x0001ffdc,0xbf300274,
    0x81df9001,0xdd5003fc,0x6c1fef40,0x000004ed,0x1ea02fc4,0x3e2003dc,
    0x2200d902,0x01f9802f,0x807d43f2,0x20bb00fa,0x0fcc01f9,0xf7004e80,
    0xea80019f,0xd00000cf,0xbffa8009,0x37fae621,0x435df700,0x01dfeb98,
    0x3ea03ff2,0x4000002f,0x83d400ed,0x04e8007b,0x02ec007f,0x9f100fcc,
    0x07d403ea,0x200fcc00,0x09d001f9,0x01ffe440,0x000eff4c,0x20013a00,
    0xffffffd8,0xfe9801df,0x2effffff,0xf106fa80,0x4000001f,0x07a801fb,
    0x2f8800f7,0x2a000fa8,0x00fcc00f,0x403ea7ee,0xf98000fa,0x800fcc01,
    0xfc88004e,0x2efd882e,0x09d00000,0x565cc400,0xb9880009,0x000001ab,
    0xf9800000,0x2e0f5004,0x407e4007,0x03f8005d,0x77400fcc,0x01f500fa,
    0x9803f300,0x009d001f,0xf72fecc0,0x8000007f,0x0000004e,0x00000000,
    0x74000000,0x5c1ea006,0x20ff2007,0x6c8002f8,0x4c00fcc0,0x1f500fdf,
    0x803f3000,0x09d001f9,0x361b5000,0x70000003,0x00000005,0x00000000,
    0x7cc00000,0xaaaaaaac,0x2a27caaa,0xaaaaafda,0x43ffdbaa,0x1aabfca8,
    0x2ff2aaa0,0x33eea20a,0x3ff202aa,0x55fe5440,0x2eaa601a,0x55530abf,
    0x555559f7,0x009d5555,0x00000000,0x00000000,0x00000000,0x98000000,
    0xffffffff,0x267fffff,0xffffffff,0x81bdffff,0x4ffffffb,0x3fffffa0,
    0x3fffe61f,0x3fe206ff,0x7ffffd40,0x3fff605f,0xfff72fff,0xffffffff,
    0x009fffff,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x40000000,0x062cddb9,0x2f772a20,0x02aa9802,0x002aaaa2,0x39bdb751,
    0xa8555100,0x4c00acdc,0x77302aaa,0x2e2aa881,0x16dcc2cd,0x055554c0,
    0x10d55544,0x01555555,0x15555551,0x99880080,0x3bbba619,0x017bbae1,
    0xdddb0013,0xdddddddd,0x987ddddd,0xdeffd880,0x01fcfffe,0x3fb7ffee,
    0xfff301ef,0x3fff601f,0xfffb302f,0x01bfddbd,0xfe9bffe4,0x202fffdf,
    0x260fffff,0x2e5feffe,0xfefe9fff,0xffbff53f,0x3fffea01,0xffffd83f,
    0xfffffd0f,0xffffb07f,0x03e809ff,0x887fffd4,0x3ee1ffff,0x17e205ff,
    0x3bbbbb20,0xeeeeeeee,0xffd13eee,0x4417f44b,0xfb01ffda,0x07fd3019,
    0x9803ee62,0x7b502f99,0x3017ea03,0xa83bf7f7,0x733102fd,0xa8bbf21f,
    0x3ffee63f,0x893f3f20,0x2ffa603e,0x833f2601,0x019bfa98,0x0067f666,
    0xfff300fe,0x20ffff8f,0x3604fffa,0x000003ff,0x47ffff20,0x1fd803fa,
    0xfc802fc8,0x4003ea02,0x7dc0002f,0x027fd402,0x23ea01ba,0xa81303fd,
    0x2ffc41ff,0x0fec035c,0x5e809f70,0xf8013e00,0x37ffc403,0xff31fffa,
    0x2e7f207f,0x0000002f,0x2e5ffffb,0x40f9800f,0x3f6003fa,0x2001f500,
    0x4f80002f,0x5c02fd40,0x7f7d400f,0x80fd4002,0x003f306e,0x07f703fb,
    0xf5001f70,0x401fc001,0x7fec5fff,0x417ffc45,0x003f63fa,0x3fe60000,
    0x4017e27f,0x44005e80,0x001f504f,0x3a0000be,0x4007d404,0x77d402f8,
    0x00fa8001,0x007e60bb,0x07f70fec,0x2f4027c0,0x11fc1cc8,0x27ff43b5,
    0x3fe13fee,0x2227cc1f,0x5555506e,0x55555555,0x5c435555,0x09bdfc82,
    0x0005f100,0x003ea0bb,0x54c4017c,0x809d0aaa,0x05f1007a,0x50000fa8,
    0x4c17601f,0x2bf6001f,0x7dc003fc,0x640be600,0xacf9cfff,0x3f61effd,
    0x41ffd43f,0x1ba20ffe,0x3fe22fcc,0xffffffff,0x5fffffff,0x3fffaa00,
    0x3f302cef,0x2a0f7000,0x405f000f,0xffffffea,0x3d404fff,0x5402f880,
    0x1f50000f,0x0fcc1760,0x00bff200,0x6d80fe20,0xffffca80,0xffc81bef,
    0x6c17fcc2,0x5007ec7f,0x0000007f,0x36ea6200,0x07d40dfe,0x5407d400,
    0x205f000f,0x3109befd,0x7a809f73,0xa805f100,0x1f50000f,0x0fcc1760,
    0x00bff200,0x3f8836c0,0x017fec00,0xff103fee,0x7dcbf703,0x001fc802,
    0x20000000,0x07e61fe9,0x7d41f200,0xf905f000,0x5013a007,0x00be200f,
    0x2a0001f5,0x260bb00f,0x2bf6001f,0xf98003fc,0x4c007c82,0x7d406ecf,
    0x3a20bb07,0x3d800f62,0x000ef644,0x3a00000a,0x6c001fc4,0x2001f505,
    0x001fc42f,0x007a809d,0x0fa805f1,0x201f5000,0x003f305d,0x03fb8bf6,
    0x04f85d80,0x27cdba20,0x0000df10,0x3ba20000,0x87204fdc,0x01f300ef,
    0x01b63dc0,0x3ea07f30,0x542f8800,0x013a000f,0x0be200f5,0x20001f50,
    0x20bb00fa,0x1fd801f9,0x54003fb8,0x8003ea1f,0x807ee0fd,0x00000009,
    0x2e0ef880,0x260fd85f,0x02fa81ee,0x09f11b20,0x5f303740,0x542fe880,
    0x09f9001f,0x5f1007a8,0x0000fa80,0x417601f5,0x0fec01f9,0xe8009f70,
    0xfa8017a4,0x0000fe82,0x64000000,0xa9efa80e,0x1fe882fd,0x5400f7d4,
    0x404fb83f,0x3e201fd8,0x0bffe605,0xfe980bf1,0x803d404f,0x07d402f8,
    0xb00fa800,0x4407e60b,0x4fa801fd,0x3e63ee00,0x440ea001,0x0000000d,
    0x74400000,0x36201eff,0x2fffea2f,0x02fe4c09,0x5cc15df7,0xcfb802ff,
    0xf3bfb711,0x56fdc159,0xd3df9510,0x6554155b,0xf7501abf,0x2aaa6159,
    0xaaaaabfc,0xbfca880a,0x4c1aed82,0x3faa0abf,0xaa980aac,0xf8801cfd,
    0x000006dd,0x00000000,0x00660000,0x2e3a24c8,0xffffffff,0xfffe9803,
    0x2000dfff,0x2ffffffd,0xff70fffe,0x747fffff,0x3ffa2fff,0xff983fff,
    0xfffb2fff,0xffffffff,0xffff507f,0x45ffd83f,0xff11fff9,0xf905ffff,
    0x200bffff,0x00002ffc,0x00000000,0x00000000,0x2eea6200,0xba88001a,
    0x7300009b,0x51000159,0x00001577,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__courier_41_usascii_x[95]={ 0,8,4,3,4,3,4,8,10,5,0,2,5,3,
8,4,4,4,3,3,3,3,4,3,4,4,8,5,0,1,0,0,3,0,1,2,2,1,2,2,1,4,3,1,
2,0,0,0,3,1,1,3,2,1,0,0,1,1,3,0,0,0,4,1,7,2,0,3,2,2,3,2,1,3,
3,3,3,0,1,2,0,2,3,3,2,1,1,0,1,2,4,0,10,0,3, };
static signed short stb__courier_41_usascii_y[95]={ 30,7,8,6,5,7,10,7,7,7,7,10,24,18,
25,5,7,7,7,7,7,7,7,7,7,7,14,14,10,16,10,8,7,9,9,8,9,9,9,8,9,9,9,9,
9,9,9,8,9,8,9,8,9,9,9,9,9,9,9,7,5,7,7,38,6,14,7,14,7,14,7,14,7,7,
7,7,7,14,14,14,14,14,14,14,9,14,14,14,14,14,14,7,7,7,17, };
static unsigned short stb__courier_41_usascii_w[95]={ 0,6,13,16,14,16,15,6,7,7,14,18,8,16,
6,14,14,14,15,16,15,16,15,15,14,15,6,9,18,19,18,13,15,22,19,18,19,18,19,19,20,14,19,20,
18,22,21,19,17,19,21,16,18,20,22,21,20,19,16,7,14,7,14,23,7,18,20,17,20,17,17,19,20,16,
12,18,16,22,19,18,20,20,17,16,18,19,20,21,19,19,14,8,2,8,16, };
static unsigned short stb__courier_41_usascii_h[95]={ 0,24,11,27,29,24,21,12,28,28,14,19,12,3,
6,28,24,23,23,24,23,24,24,24,24,24,17,20,19,8,19,23,26,21,21,23,21,21,21,23,21,21,22,21,
21,21,21,23,21,27,21,23,21,22,21,21,21,21,21,28,29,28,10,2,6,17,24,17,24,17,23,23,23,23,
30,23,23,16,16,17,23,23,16,17,22,17,16,17,16,23,16,28,28,28,6, };
static unsigned short stb__courier_41_usascii_s[95]={ 254,214,200,112,29,237,239,193,96,65,178,
163,247,165,249,81,165,40,74,180,107,197,1,221,75,17,240,245,125,229,144,
123,149,38,18,55,220,201,181,137,142,127,197,86,106,83,61,20,163,129,217,
90,24,157,1,43,65,107,1,73,14,104,214,182,246,57,33,182,54,200,111,
129,90,149,1,1,166,114,76,18,183,204,96,1,178,37,157,218,137,225,240,
53,62,44,229, };
static unsigned short stb__courier_41_usascii_t[95]={ 1,1,125,1,1,1,56,125,1,1,125,
103,81,26,125,1,1,57,57,1,56,1,32,1,32,32,81,32,103,125,103,
56,1,103,103,57,81,81,81,56,81,81,56,81,103,103,103,57,81,1,56,
56,81,56,81,81,81,81,103,1,1,1,125,26,134,125,32,103,32,103,32,
32,32,32,1,57,32,125,125,125,32,32,125,125,56,125,125,103,125,32,99,
1,1,1,134, };
static unsigned short stb__courier_41_usascii_a[95]={ 348,348,348,348,348,348,348,348,
348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,
348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,
348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,
348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,
348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,
348,348,348,348,348,348,348, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_courier_41_usascii_BITMAP_HEIGHT or STB_FONT_courier_41_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_courier_41_usascii(stb_fontchar font[STB_FONT_courier_41_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_courier_41_usascii_BITMAP_HEIGHT][STB_FONT_courier_41_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__courier_41_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_courier_41_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_courier_41_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_courier_41_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_courier_41_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_courier_41_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__courier_41_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__courier_41_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__courier_41_usascii_s[i] + stb__courier_41_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__courier_41_usascii_t[i] + stb__courier_41_usascii_h[i]) * recip_height;
            font[i].x0 = stb__courier_41_usascii_x[i];
            font[i].y0 = stb__courier_41_usascii_y[i];
            font[i].x1 = stb__courier_41_usascii_x[i] + stb__courier_41_usascii_w[i];
            font[i].y1 = stb__courier_41_usascii_y[i] + stb__courier_41_usascii_h[i];
            font[i].advance_int = (stb__courier_41_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__courier_41_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__courier_41_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__courier_41_usascii_s[i] + stb__courier_41_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__courier_41_usascii_t[i] + stb__courier_41_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__courier_41_usascii_x[i] - 0.5f;
            font[i].y0f = stb__courier_41_usascii_y[i] - 0.5f;
            font[i].x1f = stb__courier_41_usascii_x[i] + stb__courier_41_usascii_w[i] + 0.5f;
            font[i].y1f = stb__courier_41_usascii_y[i] + stb__courier_41_usascii_h[i] + 0.5f;
            font[i].advance = stb__courier_41_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_courier_41_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_courier_41_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_courier_41_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_courier_41_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_courier_41_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_courier_41_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_courier_41_usascii_LINE_SPACING
#endif

