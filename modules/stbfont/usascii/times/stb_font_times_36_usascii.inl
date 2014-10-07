// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_times_36_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_times_36_usascii'.
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

#define STB_FONT_times_36_usascii_BITMAP_WIDTH         256
#define STB_FONT_times_36_usascii_BITMAP_HEIGHT        146
#define STB_FONT_times_36_usascii_BITMAP_HEIGHT_POW2   256

#define STB_FONT_times_36_usascii_FIRST_CHAR            32
#define STB_FONT_times_36_usascii_NUM_CHARS             95

#define STB_FONT_times_36_usascii_LINE_SPACING          23

static unsigned int stb__times_36_usascii_pixels[]={
    0x0000dc40,0x03579533,0x9800a880,0x20015003,0x00000221,0x00000000,
    0x00000260,0x00000000,0x00000000,0x00000000,0x001ffb00,0x4d667644,
    0x000cfedb,0x06b809d5,0x4b80175c,0x7ff4016c,0x4400ffff,0x1bdefdca,
    0xfffffa80,0x0016404f,0xdefdca88,0x05d7001b,0x37ffb2a0,0x75c1260b,
    0x2001cefe,0x9305f04d,0xb90009dd,0x07fec000,0x401f6c40,0x32003ea8,
    0x6c0d700e,0x209d3005,0x4ccc404d,0x3ea00ffa,0xffdb9bcf,0x27fea00d,
    0xdb880999,0x5001cdef,0xd75359ff,0x7fc401bf,0x6fff5407,0xecfeb99a,
    0xda85f444,0x05d003ff,0x8df981f1,0x3ea005fa,0x0ae20000,0x4000fea0,
    0x0bf1005c,0x00fe41ae,0x1b201fc4,0x880ff980,0x3f600efd,0x00ff501e,
    0xd77b9fd5,0x3f6205df,0x07bf200e,0xc807ffd4,0x7fdc02ff,0xffd82f45,
    0x540fc401,0xfb07f447,0x005f1003,0x0bf20000,0x20097000,0x886b82fd,
    0x00bd006f,0x3e6007f1,0x006fe80f,0xff505ffd,0x8b26f980,0x0dfd04fb,
    0x260bfee0,0xffd80fff,0x4cbf7001,0x09ff505f,0xa8b90798,0x4027d46f,
    0x0000005d,0x200003f9,0x84fd801d,0x806fa86b,0x3f5002fc,0xc81ff300,
    0xff1002ff,0x407fa81d,0x9d0b23fe,0x4005ff90,0x7fc40fff,0x003ffb87,
    0x01ff7364,0x6b80fff1,0x45fc87b0,0x07d406fa,0x7cc00000,0x16600002,
    0x1ae17fa0,0xdf501ff2,0x9806f800,0x1bfe60ff,0xa89ff700,0x87fe207f,
    0x3e62542c,0x7fdc006f,0x7cc6ff84,0x2798006f,0xffd02ff9,0x85f04c80,
    0x07fcc5fd,0x00002f88,0x2005f880,0x007c0880,0x21ae13fe,0x3f600ffb,
    0x01fe4003,0xffe83fe6,0x7ffc4002,0xf981fea1,0x8910b24f,0x44002ffe,
    0x37fc1fff,0x4000fff6,0xff807645,0x7cc1f405,0x3e62fec0,0x0009b01f,
    0x7e43e4c0,0x6e75c400,0x1ec0ff9b,0xd707ff10,0x2603ff50,0x7d4000ff,
    0x43fe600f,0x8001fff9,0x1fea4ffe,0x0b21fff0,0x01fff882,0x744ffe80,
    0x07ffe25f,0xf3000c00,0x7777547f,0xfeeeeeef,0xa8df73ee,0x000d707f,
    0x21fffaa0,0x067cc04f,0x0970df99,0x35c17fcc,0xfc817fcc,0x2ff88007,
    0x7d43fe60,0xfc8000ff,0x901fea5f,0x80593dff,0x8000fffa,0x27ec5ffd,
    0x0000fff5,0x511bf200,0x5555f955,0x2a355db5,0x4437dc7f,0x3300001f,
    0x01fa8fff,0x3fea1bea,0x3e205984,0xff06b81f,0x001bfe01,0xff3027fc,
    0x001ffee1,0xff53ffe4,0xeffff980,0x03ffdc02,0x647ffc80,0x01fff23f,
    0x3fe20000,0x3d82e400,0x0ff43fb0,0x40000274,0x303747fc,0x3ff503ff,
    0x0fc80d10,0x20df06b8,0xf0005ff8,0x87fcc0bf,0x70006ffd,0x1fea1fff,
    0x13fffe60,0x000dffb0,0xfb83ffee,0x001bff62,0x00bf2000,0x8817c136,
    0xb83fd9ee,0xf9000006,0x3fa03f8f,0x2a0ff904,0x5c1fcc04,0xf302fa86,
    0x3fa0009f,0x6c3fe607,0xf50006ff,0x01fea1ff,0x077fff44,0x0006ffd8,
    0x7d41fff7,0x001bff61,0x4013e000,0x400f982f,0x1f980bb9,0x0002ca88,
    0x817c4ff9,0x9fd00ffb,0x3a600b20,0x0b6235c0,0x0003ffb8,0x3e601ffb,
    0x00fff90f,0xfa9ffee0,0x7ffdc007,0x07ffc82f,0x98fff700,0x01fff60f,
    0x00b70000,0x01ea03e2,0x3e60fa00,0x4000eead,0x407e67fc,0x0bfe02ff,
    0xcc88006c,0x03322d70,0x0005ff90,0x7cc0bff2,0x00fff50f,0xfa9bff20,
    0xfffd8007,0x03ffdc3f,0x4c6ffc80,0x007ffdc7,0x001d0000,0x002e41ea,
    0x9be21b20,0x7e4005f8,0x3ea03ea7,0x01ff700f,0x27d1001a,0x9005f56b,
    0x320007ff,0x1ff303ff,0x0003ffe6,0x7fa97ff6,0xffdac800,0x03ffea3f,
    0x113ff600,0x02fffa8f,0x80b10000,0xfffffffa,0x4fffffff,0x3203e600,
    0x0017f44f,0xd83d4ff9,0x0dff106f,0x0bb80166,0x401971ae,0x90003ffa,
    0x3fe605ff,0x0007ffe0,0x7fa8bffa,0xff72c800,0x00fffc4d,0x3417ff40,
    0x000fffe2,0x2201cc00,0x9999ce99,0x00999af9,0x1ff40fa0,0xfc8013f6,
    0x3fe03e67,0x207ff904,0x84e8802e,0x300eb86b,0x360009ff,0x1ff301ff,
    0x20027fec,0x3fd46ff8,0xff916400,0x002ffe43,0x40c1bfe2,0x20005ffc,
    0xf8006a00,0x0000f982,0x217fc0b9,0x3f2006fc,0xff107e27,0x03ff9707,
    0x07ee00b5,0x813e21ae,0xfd0005ff,0x107fcc0f,0x64001ffd,0x03fd42ff,
    0x7cc59011,0x03ffe23f,0x001ffc80,0x000fffe2,0x44000072,0x0006a80f,
    0x3fe201f3,0x90037e42,0xfe82f8ff,0x07fce5c5,0x7f4003aa,0x0ff06b80,
    0xf8002ff4,0x03fe607f,0x22009ff3,0x07fa85ff,0xff0b2126,0x004ffa87,
    0x90009ff1,0x5c003fff,0x1ea00003,0x744002e4,0x321ff403,0x1ff2005f,
    0x7bff909b,0x443fe69d,0xf982c0ec,0xf886b81f,0x00df902f,0xf9813fe0,
    0x02ffa80f,0xfa82fec4,0x8b21a607,0xffc81ff8,0x02ff4402,0x3fee07f9,
    0x405c801f,0x5c801ee9,0xb90007d0,0xfd87fb00,0x51ff2004,0xfffe981f,
    0x5eef7f43,0xff981dc0,0xff986b83,0x001ff702,0x2601ff88,0x9ff500ff,
    0xa813fa60,0x90be607f,0xd3027e45,0x5ff5019f,0x503ffcc0,0x2237bfff,
    0xfc803eb9,0xf04d804f,0x00fa8003,0x3fe26f98,0x21ff2000,0x5403503f,
    0x440d100a,0xa86b84ff,0x0bfa01ff,0x980bf700,0x7fdc00ff,0x01cffdce,
    0xff303fd4,0x0efb9647,0x6f7f6440,0x4400dffe,0x764c06ff,0x1dffffff,
    0x005ff700,0x001f105f,0xf50017c4,0x8005fb17,0x00ea87fc,0x403c8000,
    0xc86b85ff,0x13e600ff,0x9805fd00,0xfd8800ff,0xf5004fff,0xdffdb80f,
    0x8003ffee,0x4000aa98,0xaa980028,0x01980009,0x00510150,0xc98004b8,
    0xfc8001ce,0x0000bb06,0x4fd805b8,0x07fb86b8,0x3e6007c8,0x00ff9805,
    0x07fffee0,0x4401fea0,0x0000cea9,0x00000000,0x00000000,0x00000000,
    0x417f2000,0x900003e8,0x20ff200b,0x806f986b,0x1db003e8,0x001ff300,
    0x806fffa8,0x2c8007fa,0x00736a00,0x55510144,0x55555555,0x26155555,
    0x1bbbbbbb,0x00000000,0x80000000,0x37a202fc,0x01720000,0x06b80fe8,
    0x03ea00fd,0x26003f30,0xc88000ff,0x3ea00eff,0x80098007,0xbeffefe8,
    0x77443200,0xffffff31,0xffffffff,0x3fff27ff,0x0003ffff,0x00000000,
    0x83762000,0x05d9006d,0x001f5c40,0x41ae05f3,0x1d5002f9,0x9800be60,
    0x220000ff,0xfa80aefc,0x36000007,0x37ff260c,0xffc96a0a,0xfc800005,
    0x03ffffff,0x00000000,0x3ea00000,0x001ebbff,0x88673f66,0x000ceca9,
    0x06b80bae,0x6c400fa6,0x32006d41,0x00ffeeee,0xdedb8800,0x3bbbfea2,
    0x0d00003e,0xefeffea8,0x000ffea2,0x00000000,0x00000000,0x37fae000,
    0x32e20003,0x0acdeffe,0x002f6200,0x1db880d7,0x801c4700,0x0aaaaaaa,
    0x21880000,0x1aaaaaa8,0x00288000,0x06605973,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x12600e60,0x5c910000,0x00000001,0x9801b880,0x000dc404,0x01ceda80,
    0x1333332e,0x9813332a,0x5000cdfc,0x09999999,0x82edca80,0xcccccccb,
    0x73003ccc,0x400017dd,0x21bdfeda,0x7f5c4005,0x0ffd7106,0x325b8000,
    0xec980005,0x161ceffe,0x5403ff60,0xffb307fe,0xef980005,0xb103fc9a,
    0x2e019fff,0xfff981ef,0x4401efff,0x4fffffff,0x015dd300,0x3fffffe2,
    0x804fffff,0x1feaaefe,0x67fec400,0x06effeba,0x837fee40,0x0007ffcc,
    0x00f31740,0x5677f4c0,0x7dffca99,0xc80ffd80,0xeca87ffc,0x260002ff,
    0x01fec0ff,0x7d405ffd,0xfb35bd01,0xffc80bff,0x801fffff,0xffb804fc,
    0xffffffff,0x22fec02f,0x7ec005f8,0x00dff504,0xfb01bfa0,0x7cc0000f,
    0x5c001740,0x7ec404ff,0x00dc400f,0xffb81ff6,0x0ffa0002,0x7cc03fe2,
    0x641b204f,0x00fff882,0x333335f1,0x03fe9801,0x74035bd0,0x417fc407,
    0xff7000fd,0x0037cc01,0x7e406fd8,0x16e00007,0xff900172,0x00ff4007,
    0x207fc800,0x50002ffa,0x13f601ff,0x5f00ffd8,0x7fe40710,0x4000b902,
    0x0d5005fe,0xfa809f10,0x2007e81f,0x06c804fd,0xc80dfb00,0x3a00007f,
    0x2a007982,0x7d4003ff,0xff900001,0x0017fd40,0x3ee06fe8,0x07ff300f,
    0x3e6000f5,0x001f880f,0x2001df90,0x02fb800a,0x3e617fdc,0x01bfa004,
    0x7ec001a6,0x003fe406,0x5d00f980,0x01fff100,0x00005b00,0xffa81ff2,
    0x5ff88002,0xd80ffe60,0x0004e87f,0x37f20df3,0x3fea001b,0x7e800001,
    0x6c5ffa80,0x3ff6001f,0xb0006803,0x07fc80df,0x640b7000,0x04ffc805,
    0x00005300,0xffa81ff2,0x4ffa8002,0x9813fe20,0x003e63ff,0x7c407dc0,
    0x402effff,0x00006ff8,0xf8804f88,0x02fe88ff,0x027ffdc0,0x7dd95006,
    0xfc80dfb1,0x00f7b267,0x01e602e8,0x00007ffa,0x6407c980,0x0bfea07f,
    0x45999995,0x3e203ffc,0x93ff405f,0x07a2000b,0x7fffffdc,0x4ffee04f,
    0x0000aca9,0x7ec00bee,0x3a60dfdf,0x220deeee,0x002efffe,0xfc89dfc8,
    0xbfe406ff,0x0dfffffb,0x3a007cc0,0x03ffe202,0x3faa0000,0x03fe407f,
    0xffb05ff5,0x03ffc837,0xf501bfe2,0x2000be7f,0x54c00ef8,0xb06ffffc,
    0xfffdd7ff,0x1fa0007f,0x02fffa80,0x2603fff5,0x00dfffff,0xff905fb0,
    0xebffc80d,0x05fffcab,0x02e402dc,0x0000fff5,0x01ffe660,0x7fd40ff9,
    0xd806f442,0x3ffc02ff,0x03df7f40,0x3ffff6a0,0xfffb1001,0x41bfff07,
    0x4003ffe9,0xfd3005f8,0x0ffc09ff,0x3ffffa60,0x17ea00cf,0x32037fc4,
    0xfff984ff,0x2600ba02,0x0dff900f,0x3bbbba60,0x0ffb05ee,0x3ea07fc8,
    0xb017a22f,0x7ff803ff,0x04fffa80,0x7ffedd40,0x3ff2002f,0x417fe20f,
    0x2000fff9,0xdfc802fb,0xf981fffb,0x3ffee004,0x5ff02fff,0x32037f40,
    0x17fee07f,0x2e8007cc,0x800fffb0,0x202ffff9,0x3fe407fc,0x3a25ff50,
    0x02ffd804,0x7401ffe2,0x260000ff,0x5c006ffe,0x13fea2ff,0x2004ffd8,
    0x1ff4407e,0x1f70dffd,0xfffd8800,0x0ffd43ff,0xfc80dfb0,0xc837fc07,
    0x6c16e005,0x64000fff,0x3fe406ff,0xfa81ff20,0x9004f9af,0x7fc405ff,
    0x00bf7006,0x003ffa00,0x3ee4ff88,0x17fee03f,0xd102fc40,0x4fffa87f,
    0xd3000174,0x7e43ffff,0x2037ec07,0x3ff407fc,0x3e6002e8,0x02fffb80,
    0x2027fe40,0x3fe407fc,0x3ff9ff50,0x80ffee00,0xf1006ff8,0x3ea00005,
    0x2fec003f,0x7cc07ff5,0x05f7007f,0x7ec07fe4,0x000b91ff,0xd9bffee0,
    0x037ec07f,0xffb01ff2,0x5d000f30,0x007fff50,0x6404ffb8,0x03fe407f,
    0x1dff9ff5,0x407ff500,0xf7003ffa,0x7fc40000,0x31fdc003,0x6ff809ff,
    0xff80fb00,0x3dfff105,0x2009001f,0xffd0fffb,0x2037ec01,0x37e407fc,
    0x2dc002e4,0x002fffc4,0xf9013fee,0x207fc80f,0x5ffbaffa,0x5c0bff00,
    0x07d001ff,0x01fe8000,0xff10fd40,0x805fe80b,0x3fea05f8,0x3fffea04,
    0x2003b002,0x3ffb1ffe,0x32037ec0,0x42fec07f,0x0f98002e,0x000fffb8,
    0xf9013fee,0x207fc80f,0x9ff92ffa,0x640ff900,0x01f5006f,0x07fc4000,
    0x3fa1b200,0x401ffc06,0x3ff602fa,0x1fffec06,0xc8026c10,0x09ff90ff,
    0x3f2037ec,0x261ff407,0x20ba0007,0x2004fff8,0x7e404ffb,0x503fe407,
    0x17ff45ff,0x7c07fe60,0x1f44102f,0x0fee0000,0xf303f100,0x01fe203f,
    0x3ff203ec,0x3ffe601f,0x3b61b04f,0x266fe800,0xffb00fff,0x2607fc80,
    0x0005c86f,0x7ffd416e,0x09ff7001,0x7e407fc8,0x88bfea07,0x7dc01fff,
    0xfb06fb85,0x8800bfbf,0x88dd101a,0x04e880dd,0x17e41bf2,0x2a02fc40,
    0xfb80dfff,0x12dfffec,0x0077ec79,0xffd85ff5,0x07ff440e,0x3601ff90,
    0x0002e81f,0x7f4c03e2,0x4ffb801f,0xb007fec0,0x3fea01ff,0x0077fd42,
    0x0ef98bf2,0x01ffffd0,0x8aeffb80,0xff984fc8,0x03fcabdf,0x1fdc3fe8,
    0xd802fa80,0xecbcffff,0xffffb11e,0xeffd8dff,0x13fae20a,0x2affffa2,
    0x0deffeec,0x6c1effb8,0x0007982f,0x7fec02e8,0xffea80ac,0x00fff402,
    0x3f203ffd,0x0effd84f,0x5f7775c0,0x02fbaa00,0x3fffe200,0x3f202eff,
    0x000cefff,0x0bbf3ff2,0x2e007d80,0x0cffffff,0x1dffffc8,0x7ffedd6c,
    0x2201effe,0xd8dffffd,0x7ecc02ef,0x900dfeff,0x0b700009,0x9bffd950,
    0x4017dffd,0x0dffffeb,0x37ffffae,0xbffffb71,0x3ffffea5,0x000cc01c,
    0x554c0000,0x0054c000,0x00133100,0x98800550,0x153000aa,0x2aaa6060,
    0x82aa2001,0x9a980019,0x00005400,0x54c00144,0x000009aa,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x10000000,0x2e000017,
    0x2001beed,0x002ceeca,0xb800aa88,0x400bdfed,0xcccccccb,0x9999931c,
    0x33326005,0x332a4ccc,0x931ccccc,0x09999999,0x47333332,0xccccccca,
    0x66665404,0x33332e4c,0x9301cccc,0x01999999,0x64c00000,0xcccccccc,
    0xcccccc82,0x3ffb502c,0x2ee88000,0x9fffffb3,0xfd739fb0,0x37766009,
    0xee880dff,0x02feb88b,0x5ffffe4c,0x7fff5cc0,0xdff71001,0xfffe9885,
    0x7ffecc1d,0xff5100af,0x7ff5443d,0x54401bff,0x64c2dffe,0x400cffff,
    0x003fffb8,0x540003a0,0xaefffffc,0xdfffa880,0xfffcb809,0x1ff40001,
    0x20d577f4,0x05fe81fd,0xbff717c4,0xff103fd0,0x07ffd001,0x00fffe88,
    0xf8807f20,0x3ffa02ff,0x201fb006,0x4005fff8,0x7ff406fa,0x017e4004,
    0x0007f300,0x03fffe88,0xf7003fe8,0x7dc0003f,0x707fb81f,0x07fea09f,
    0x3fe43744,0x4fd817ee,0x802ffd80,0x2006fff9,0x7fec00fb,0x01bfea03,
    0x3fee0274,0x00fdc007,0x7000fff6,0x7ec0001f,0xfe880007,0x01fcc07f,
    0x0003ff50,0xffa83fec,0xd00ffc42,0x417ea0df,0x5027e40a,0x5ffb00df,
    0x9ffff100,0x2a01ea00,0x7ffc06ff,0x200fc401,0x2001fff8,0x2ffd805e,
    0x0003d400,0x0005fff1,0x207fff30,0x7d4004e8,0x3f60001f,0xa87ff307,
    0x3ff200ff,0x2005fb81,0x13f206fd,0x200bff20,0x03fffcf8,0xfff007a8,
    0x01ffe401,0x7fe401ee,0x005f1004,0xa8005ffb,0x3fee0007,0xf500005f,
    0x00db01ff,0x0003ff50,0x7d407fdc,0x007fdc2f,0xbfb07ff5,0x81ffd400,
    0xffc801fe,0xfc9f8802,0x03d401ff,0x2a03ffc8,0x026c06ff,0x800fff98,
    0x5ffb006c,0x0007a800,0x007fff3e,0x237fec00,0xfa8000fc,0x3e60001f,
    0x40ffc83f,0x3e601ffc,0x005fe84f,0xf50bffe2,0x0bff2009,0x7fec7e20,
    0x401ea00f,0x3ee06ff9,0x03f101ff,0x401ffec0,0x5ffb003f,0x0007a800,
    0x09ff91f5,0x3ffe2000,0x20003f53,0xdb711ffa,0x3ff70017,0x7e417f44,
    0x57fe602f,0xcceffccb,0x7ffdc01c,0x64009f54,0x1f8802ff,0x540dffd1,
    0x07ffe007,0xb827fff4,0x37fd4006,0x6c003ea0,0x3d4002ff,0xff14e800,
    0x2a00001f,0x003fafff,0x3a67fea0,0x5005ffff,0x03df9bff,0xf9813fee,
    0xdff9975f,0xf9003999,0x8005fbff,0xf8802ffc,0x417ffe21,0x3ff2007a,
    0x7ffbf884,0xfd0009d0,0x002ec05f,0xa8005ffb,0x21f98007,0x00003ffd,
    0x0017fff6,0x15d7ff50,0x8805ffb1,0x9801989d,0xff500fff,0x000bfd09,
    0x003bffee,0x1005ff90,0x3fffa83f,0x3e6007a8,0xffd6b86f,0x8001f883,
    0x3f105ffb,0x017fec00,0x32001ea0,0x0037fd46,0x07fff100,0x0effa800,
    0x3a02ffc4,0xbff90004,0xd07ffb10,0x3e6000bf,0x2001ffff,0xf8802ffc,
    0x42fffb81,0x7ff4007a,0x4ffb9f41,0xf880035c,0x006c81ff,0x20017fec,
    0x17c4007a,0x0000fff4,0x003fff90,0xe80ffd40,0x2bbea06f,0xe8801999,
    0xfecabdff,0x05fe82ff,0xff9afa80,0xff9001ff,0x203f1005,0x1ea1fffd,
    0x4c9ff700,0xe8fff11f,0x3ff20003,0x6c003f84,0x3d4002ff,0x7dc1ee00,
    0xf300005f,0x4000dffd,0xdfb01ffa,0x7ffffdc0,0x202effff,0xf8beffec,
    0x00bfd07f,0x3fa24fa8,0xffc800ff,0x201f8802,0x0f50effe,0x2e7ff880,
    0xf897fec6,0x3fe60001,0x0003ea0f,0xa8005ff9,0x881fc007,0x40000fff,
    0x4fff8cf8,0x03ff5000,0xff901bf6,0xffffffff,0x7fe4080b,0x400bfd04,
    0xffe887f8,0x02ffc803,0x3e201f88,0x000f55ff,0x70fa3ffb,0x001aebff,
    0x4e8fff60,0x02ffc800,0xf5003dc0,0xd5555557,0xd80007ff,0x007ffea5,
    0x6c07fea0,0x9996c06f,0x0febaaa9,0x01fff100,0xfb8017fa,0x00dfd105,
    0xf1003ff9,0xcfff9803,0xffb8007a,0x7fc40f9c,0x80003e8f,0x03f36ffa,
    0x007ff900,0x3ba006b8,0xeeeeeeee,0x320006ff,0x037fec0e,0xd80ffd40,
    0x4013206f,0xff7002e8,0x002ff407,0x7fd407fd,0x007fe401,0x7d400fc4,
    0x88007dff,0xfb05cfff,0x00001f9f,0x01b2bffa,0x0027fdc0,0x0fcc0176,
    0x0017ff40,0x7fc40fd4,0x7fd4004f,0x2a0dfb01,0x03f1002f,0xe80bfd10,
    0x13fa005f,0x6401ff88,0x03f1007f,0x01ffff20,0x81fffec0,0x0006fffa,
    0x0ffbfee0,0x037fcc00,0x36400fe0,0x005ffa80,0xff501fcc,0x7fd4003f,
    0x3a0dfb01,0x00b9005f,0xe801dfd1,0x1bee005f,0x20b98ff0,0x3f3006fc,
    0x03ffec00,0x00fffa80,0x0007fff1,0x07fffc40,0x03ffb000,0x22003f20,
    0x3ffe002f,0x00bf1001,0x2001dffb,0xdfb01ffa,0x02b7ff20,0xd1003b66,
    0x17fe00bf,0x501ff880,0xb27fc49f,0x07ea005f,0x007fe880,0xfb017fe0,
    0xc800001f,0x440004ff,0x7e400efe,0x800f9001,0xe8805ffc,0xfff9800f,
    0x05ff5005,0xffd81ff6,0x3fffffff,0x003fe880,0xf70017fe,0x446e983b,
    0x009f1fff,0x260027e4,0x3f20007f,0x0037d402,0x00ffc400,0x577fcc00,
    0x00ff6e60,0x2a002fc4,0x3ee01fff,0xfff1007f,0xffc801bf,0x401fff03,
    0xbceffec9,0x33fb2a00,0x3ffea000,0x77f4c000,0xff703fec,0xf91009bf,
    0x0019ffff,0x798001ea,0x00007f00,0x80001b60,0xffffffd9,0x3f6002ef,
    0x7ffd4005,0x7fff5c0e,0xff9104ef,0x50dfffff,0x25bffffb,0x04efffec,
    0x0d544000,0x3fff6a00,0x44004dff,0x1a8800a9,0x30000000,0x30028000,
    0x22000001,0x98800001,0x2000aaba,0x05fffffb,0x7fffff4c,0x0000006f,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x6666664c,0x001aaacc,0x3333332a,0x999301cc,
    0xccb89999,0xcccccccc,0x83cccccc,0xccccccc8,0xcccccccc,0x79999932,
    0xcccc8000,0x999930cc,0x00399999,0x6666664c,0x666642cc,0x5c403ccc,
    0x0137b266,0x4677ee4c,0xcccc986b,0x64c3cccc,0x3ccccccc,0x99999993,
    0x64401357,0x4ccccccc,0x77fffdc4,0x02effede,0xfffffa88,0x7ff4c01d,
    0x7fff40af,0xeefffeee,0x986fffee,0xeeeeefff,0x0efffeee,0x03fffee6,
    0x77ffd400,0x7ff5c40b,0x88001adf,0x80cffffa,0x0aefffa8,0x26fffb50,
    0x00efffff,0x3ee66fee,0xff5106ff,0x2a2019ff,0x441cffff,0xfefffffb,
    0x3a603fff,0x2e02efff,0xffe984ff,0xfffd1004,0x03bea001,0x7fe40f74,
    0xfa86f983,0x1fff9803,0x009fffb0,0x00ffff60,0x0000fff7,0xf301bff2,
    0xff33007f,0xffd79d3f,0x207f60bf,0x7dc06ffa,0xdff7006f,0x4c4ffc80,
    0xf300effd,0xffa801ff,0x07fff104,0x00fffe60,0x03d00fec,0x3cc0fff2,
    0x7f44025c,0x3ffee04f,0x7fcc000f,0x7fcc01ff,0xff700006,0x002fd80b,
    0x2a06ffe4,0x27d42fff,0xfb80dff0,0xbff5005f,0xd04ffa80,0x3fe20fff,
    0x04ffa807,0xc801bff2,0x7c400fff,0xff903403,0x015c2c07,0x2a037fec,
    0x4003ffdf,0x400ffeed,0x00006ff9,0x7ec09ff5,0x0ffc8001,0x7c4bff90,
    0x01bf600f,0x2a00bff5,0x7fd405ff,0x03fff104,0xf500fff1,0x7ffd409f,
    0x13ffa000,0x40500db0,0x20a03ffc,0x1fffa803,0x37fcfd40,0xffd5f100,
    0x05ff9801,0x09ff5000,0x640007f2,0x9bfe607f,0x37ec07fb,0x4013fea0,
    0x7d405ffa,0x13ffe04f,0x2a01ffe2,0x3fe604ff,0x3fe6001f,0x003f501f,
    0x003ffc80,0x1fffc400,0x2ffebd40,0x3ffad900,0x02ffcc00,0x84ffa800,
    0x320001fc,0x93ffc07f,0x06fd80df,0xa8027fd4,0x7fd405ff,0x21bff604,
    0xfa807ff8,0x3ffee04f,0x37fe4000,0x40001f44,0x00003ffc,0xa802ffec,
    0x100dff57,0x003ffa7f,0x0000bff3,0x5fb13fea,0x07fc8000,0x5fd87ff4,
    0x2a037ec0,0xff5004ff,0x04ffa80b,0x3e217ffa,0x4ffa807f,0x0013ffa0,
    0xd913ffa2,0x3ff20000,0x3ee00003,0x4f5000ff,0x7dc02ffe,0x9801ffd0,
    0x500005ff,0x017ec9ff,0x203fe400,0x01bfa7fd,0xffa80dfb,0x0bff5004,
    0x3e04ffa8,0x7ff883ff,0x884ffa80,0x0000effd,0x3e63fff5,0xff900001,
    0x3e600007,0x9ea002ff,0x27c05ffb,0xf9801ffd,0xf500005f,0x005fb19f,
    0xb01ff200,0x203fecbf,0x7fd406fd,0x0bff5004,0xf704ffa8,0xfff101ff,
    0x269ff500,0x004fffb9,0x9d6ffc80,0x7fe40000,0xffd00003,0x7c7a800b,
    0x41f501ff,0x7cc00ffe,0xf500005f,0x003ffdbf,0x803ff200,0x0bff24fe,
    0x7d406fd8,0xccccccef,0x05ffdccc,0x32627fd4,0xff102fff,0xffff500f,
    0x0007ffff,0x7f7ffc40,0x3f200000,0xfc80003f,0x3d4000ef,0x27417fee,
    0xf3003ffa,0x2a0000bf,0x1fffedff,0x0ffc8000,0x7d41ff10,0x0dfd00ef,
    0xccceffa8,0xfdcccccc,0x7ffd405f,0x0dfffdde,0x201ffe20,0x3ff24ffa,
    0x7d400005,0x400002ff,0x40003ffc,0x8001fff9,0x07ffc47a,0x1ffd07ea,
    0x005ff980,0xd19ff500,0x80003fff,0x7f902ffc,0x443dffd0,0x7d406fed,
    0xbff5004f,0x534ffa80,0x3fe20035,0x44ffa807,0x00003ffe,0x00007ff4,
    0x000fff20,0x004ffe88,0x9ff90f50,0x0ffe85d8,0x002ffcc0,0xd14ffa80,
    0x40003fff,0x7dc0fffc,0xfffff305,0x80dfb3fd,0xf5004ffa,0x4ffa80bf,
    0x1ffe2000,0xf313fea0,0x400003ff,0x00000ffe,0x0001ffe4,0x4000dff9,
    0x0fff887a,0x1ffd03f3,0x005ff980,0x449ff500,0x0001fffe,0xf9df7ff9,
    0xffe9807f,0x80dfb0ef,0xf5004ffa,0x4ffa80bf,0x1ffe2000,0x2e13fea0,
    0x200006ff,0x00000ffe,0x8001ffe4,0x0001fffa,0x9ffec1ea,0x01ffd06d,
    0x0005ff98,0xe889ff50,0xc8001fff,0x0035317f,0x37ec0a98,0x4013fea0,
    0x7d405ffa,0x3e20004f,0x4ffa807f,0x0009ffb0,0x0003ffa0,0x007ff900,
    0x007fff10,0xf983d41c,0xfd02f9ff,0x5ff9801f,0xffa82400,0x1fffe884,
    0x003fe400,0x80dfb000,0xf5004ffa,0x4ffa80bf,0x1ffe2000,0x4413fea0,
    0x80002fff,0x00000ffe,0x4001ffe4,0x22005ffd,0x3f607a85,0x3ffa06ef,
    0x02ffcc00,0x3fea0b10,0x3fffd104,0x003fe400,0x80dfb000,0xf5004ffa,
    0x4ffa80bf,0x1ffe2000,0xa817fea0,0x40000fff,0x00000fff,0x2001ffe4,
    0x2000fffb,0x2607b84b,0x3fa03fff,0x37fcc00f,0x3ea05b00,0x3ffa205f,
    0x0ff9002f,0x37ec0000,0x4017fea0,0x7d405ffa,0x3e20005f,0x5ffb807f,
    0x0077fe40,0x01fff880,0x1ffec000,0x05fff100,0x3e417d40,0xf803ffa0,
    0x7fdc01ff,0x00fd8807,0xf880bff7,0xfc804fff,0xd000000f,0x6ffb80ff,
    0x80dff500,0x20005ffb,0x6c407ff9,0x7f400fff,0x54000aef,0x00004fff,
    0x003bffe2,0x55577ff4,0xecaaaaaa,0x17f441ff,0x7d409f50,0x3f6204ff,
    0xaaaaadff,0xb106ffca,0xfe801fff,0x3a01dfff,0x800002ff,0xb100fff8,
    0xd8801fff,0xfd100fff,0x320001ff,0xfd982fff,0x03dfffff,0x0bfffff1,
    0xfffffd90,0x2a00019f,0xdffffffd,0x3fffee01,0xffffffff,0x3667ffff,
    0xd04effff,0xffffd701,0x3f2619ff,0xffffffff,0x43ffffff,0xffffffd9,
    0x7fff4c2d,0x363fffff,0x01effffe,0xfffdb000,0x3ff661bf,0x4c3dffff,
    0xdffffffd,0xfffffb33,0xf91007bf,0x09bfffff,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x30000000,
    0x99999999,0x59999999,0x33333326,0xcccccccc,0x6664c0cc,0xaabccccc,
    0x3326001a,0xaccccccc,0x6cc0019a,0xfe800004,0xefec8801,0x0011000c,
    0x0cc00660,0x80000000,0x99999728,0x333332a1,0x3333260c,0x99999970,
    0x5c999970,0x7fd4404e,0xecccccef,0x3aa24fff,0xcccccfff,0x881ffedc,
    0xdefffffb,0x03dffffd,0xeffffb88,0xcfffeccc,0x13ff6600,0x2e001f64,
    0x7fdc01ff,0x803fffff,0x0b70001c,0x000b7ea0,0x7e4c0000,0x45fffb14,
    0x81dfffa8,0x3ee22ff9,0xbf500dff,0x4c7ffe21,0x04ffc85e,0x7fd427dc,
    0x202fa805,0xf5105ffb,0xf7003dff,0x3ff220bf,0xffecd81f,0x00fff884,
    0x403fff30,0xffcbeff9,0x07e202ff,0x3002dc00,0x00007dfb,0x077f6a00,
    0x7fdc1ffa,0x7e40be02,0xd03e603f,0x0bff21ff,0x99009ff7,0x200bff30,
    0x17fea02c,0x03fffb10,0x5c05ffa8,0x3fe606ff,0x400dff04,0x3a01ffee,
    0x7ffec40d,0x0003fb00,0x3220016e,0x00000cff,0x0067f5c4,0xff103ff5,
    0xf881a609,0x2213205f,0x50bff20b,0x0b1009ff,0x2a00bff3,0x017fea03,
    0x5007ffec,0xffb00bff,0x413fe203,0x5d9000a8,0x03e603ff,0xfc82ffe8,
    0x0b70001f,0x1dfeb800,0x77e44000,0x0bff000b,0x0f603ff6,0x3e01ff90,
    0x83ff7000,0x01004ffa,0x0400bff3,0x200bff50,0x2a06fff8,0xffb805ff,
    0x009ff104,0xff51f500,0xf500ae03,0x7ffec47f,0x2e002ccd,0xfb500005,
    0xfda8005d,0xffc8002d,0x443ffe80,0x27fcc00f,0xff5002dc,0x004ffa81,
    0x0017fe60,0x002ffd40,0x2a03fff7,0xffb805ff,0x0013fe05,0x3fea5f10,
    0xff300101,0x6ffee545,0x16e002cc,0xff930000,0x67f5c017,0x3fe60001,
    0x237f7542,0x0ffb005b,0x37c4005d,0x09027fd4,0x4c05ff98,0x05ffa803,
    0xa827ffc0,0xffd805ff,0x0013fe03,0x0ffd4bb0,0x01ff3000,0x20003ff5,
    0x1000005b,0x32239ff7,0x00000bff,0xfbae8bfd,0x5400ba1f,0x001e62ff,
    0x13fea17e,0x3fe603c4,0x5401e405,0x7f4005ff,0x0bff506f,0x200fff98,
    0x2a0004ff,0x007fea0f,0xf507fa80,0x2aaa203f,0xaaedaaaa,0x001aaaaa,
    0xf99ffd40,0x200000cf,0x22d30ffb,0x800f14ff,0x000f26ff,0x13fea0fa,
    0xff301f22,0x00fe620b,0x90017fea,0x3fea0fff,0x0bffea05,0x20009ff0,
    0x0ffd42f8,0x207f9000,0xdd501ffa,0xdfdddddd,0x09dddddd,0x19ff7100,
    0x003bfd50,0x367ff100,0x0265ff63,0x3e27fee0,0xa82c8000,0xfeeeefff,
    0x7ffcc07f,0xfffeeeee,0x05ffa803,0x407ffdc0,0xdccdfffa,0x800dfffe,
    0x9b0004ff,0x0003ff50,0xffa81be2,0x00b70001,0x1f7e4c00,0x02efd980,
    0x7c77ec00,0x07ebfe60,0xb7bff100,0x7d402000,0xfcaaaadf,0x577fcc07,
    0x3fdbaaaa,0x005ffa80,0x5407ffd4,0xecbbceff,0xf802dfff,0x06b8004f,
    0x20003ff5,0x3fea02fb,0x00b70001,0x05bfb500,0x33ff2200,0xeffa8000,
    0x006ffe84,0x003dffb0,0x04ffa800,0x5ff980f1,0x7d401e40,0x7fe4005f,
    0x40bff507,0x201efffa,0x260204ff,0x03ff501f,0xa807f100,0xb70001ff,
    0x3fae2000,0x7100000c,0xf80039fd,0x3ffb80ff,0x0dff3000,0x2a009f90,
    0x301604ff,0x03a80bff,0x4005ffa8,0xff506ffd,0xfffe880b,0xd109ff00,
    0x2a03e89f,0x5d8001ff,0x001ffa80,0xc8800b70,0x00000bef,0x00bbf6a0,
    0xff8827e4,0x0ffa0000,0x003fff10,0x00c09ff5,0x31017fe6,0x00bff500,
    0xf505ffe8,0xfff300bf,0x3213fe09,0xfff72fff,0xffffffff,0xd9001fff,
    0x03ff5001,0x44016e00,0x00002dfd,0x177e4c00,0x4d807e60,0x007d4000,
    0xfa803ff4,0x3e60004f,0xf500005f,0x7fc400bf,0x0bff502f,0x7c17ffe0,
    0x5fffb84f,0xfffffff7,0x1fffffff,0x5000eb80,0x2e0003ff,0x00395005,
    0xb8800000,0x04402804,0x50014000,0x13fea001,0x05ff9800,0x5ffa80c0,
    0x817ff600,0xfd005ffa,0x413fe0bf,0x55536aa9,0xff955555,0x0e980557,
    0x00bfea00,0x00002dc0,0x00000000,0x00000000,0xff500000,0x7fcc0009,
    0x54162005,0xff5005ff,0x2ffd403f,0xf03fff80,0x003c809f,0x26007fea,
    0x3e60401e,0x4a800e3f,0x00000000,0x00000000,0x00000000,0x0017fea0,
    0x2006ff98,0x0bff503d,0x807ffd30,0xfb805ffa,0x09ff00ff,0x3ea000f8,
    0x00fd401f,0x37ffe126,0x0000000e,0x00000000,0x00000000,0x2e000000,
    0x2a0005ff,0x1f9006ff,0x7017fee0,0xf7003dff,0xfffa80bf,0x209ff103,
    0x7d4003d8,0x2b3ea01f,0xfdbaaaaa,0x02effa81,0x00000000,0x00000000,
    0x00000000,0x3ff62000,0xff90000f,0x3333335f,0x3a20bfd5,0xa99aaeff,
    0x1004ffec,0x3357dffd,0x03fffb53,0x75437fcc,0x1ffa8002,0xffffff50,
    0x80ffffff,0x00000000,0x00000000,0x00000000,0x36600000,0x3dffffff,
    0xfffec980,0xffffffff,0x7ecc3fff,0xffffffff,0x9800abce,0xfffffffd,
    0x0bdeffff,0xdffffb70,0xa800061b,0xfff981ff,0xffffffff,0x0000004f,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x80000000,0x220ccccc,
    0xa803cccc,0xb800beec,0x2602deed,0x82cbdeed,0x0bceeeb8,0x7bdb7300,
    0x31eb8801,0x666543bb,0x99950ccc,0x45d71039,0x5c41cedb,0x32200bee,
    0xcccccccc,0x8fdc43cc,0x000bedb8,0x0f4000a6,0x00040000,0x80444000,
    0x4c0fff98,0x36205ffc,0x05ffa9cf,0xff935dd3,0x7117f309,0xaff985ff,
    0x400efea8,0xefd98aed,0x9fffd981,0x2a26fffa,0x3222fffe,0x7fecc1ef,
    0xffffe8af,0xfffff50f,0x6677cc0b,0x4fffcccc,0xd13fffb3,0x400bffff,
    0x7dc001ff,0x2e27d405,0x50f7e43f,0xffffffff,0xffffffff,0x9027fe4b,
    0x17fe01ff,0x3ee077c4,0x641fc42f,0x4c26c3ff,0x221ff42f,0x07f204ff,
    0xd330bff2,0xbfb5b5ff,0xd85fff10,0xffd9980e,0xbff912eb,0x3ff663d5,
    0x7d40d503,0x3ffa665f,0xffd98aea,0x005ff002,0xb017dfc4,0x13ffc1ff,
    0x4cc4dfff,0x99999999,0x40999999,0x3fee06fd,0x320bfd00,0x46ff881f,
    0x1fff00fd,0x316413e2,0x0dfd05ff,0x7fc413ee,0x41dff506,0xa9bfe600,
    0x6ffd401f,0xf04ffe80,0x440ea0bf,0xffb80fff,0x427fc40e,0x4c3f63d9,
    0x35db202d,0x7fc3ffd0,0x00ffffc7,0x1fd10000,0x7403fee0,0x207f985f,
    0x817e62db,0x3ff31ffe,0x80ff8530,0x2ff886fd,0x2a0fff20,0x7dc002ff,
    0xa802f8cf,0x1ff902ff,0x0441bfa0,0xf501ffe8,0x217fe03f,0x2ad94ffb,
    0x43f306ff,0xe8ffb03e,0x1745447f,0x3e200000,0x201ff703,0x06fb85fe,
    0x7ffffdc0,0x22ffffff,0x01003fff,0xff30dfd5,0x437fcc03,0xe8001ffa,
    0xf3004eff,0x03fee05f,0x32003fec,0x3fea03ff,0xd10dfb01,0xff5b5bff,
    0xf513a05f,0xfd8df701,0x0000f106,0x7dc16600,0xb0bfd00f,0x3fc800bf,
    0xffffc800,0xd9d91003,0x01ff70df,0x7d43ffc4,0xff88001f,0x0bfe6007,
    0xfc807fdc,0x17fea007,0x3603ff50,0x3b6a206f,0x3ee01bee,0x5fa85d80,
    0x24b827e4,0xeeeeeeea,0xeeeeeeee,0x7dc0604e,0xd0bfd00f,0x4fd800df,
    0xffff7000,0x2ff2203d,0xffb0dfb0,0x40fff801,0x90001ffa,0x3e6009ff,
    0x01ff702f,0x7c401ff2,0x7fd400ff,0x440dfb01,0x00bdeeda,0x0be205f1,
    0x83fa87f1,0x2aaa20eb,0xaaaaaaaa,0x001aaaaa,0xfd00ffb8,0x800ffb0b,
    0x220006fd,0x442ffffd,0x437ec1ee,0x7f401ffe,0x001ffa86,0x01ffef88,
    0xf702ff98,0x01ff201f,0x5400fff4,0x0dfb01ff,0x795bffb1,0x06c83bff,
    0x2617c364,0x0033621f,0x5c000000,0x0bfd00ff,0x09803ff9,0x18803ff9,
    0x89fffa60,0x86fd81ff,0x7f402ffc,0x001ffa84,0x06ff8cd8,0xf702ff98,
    0x01ff201f,0x5400fff2,0x0dfb01ff,0x55b29ff9,0x007e65ff,0x1f01d0fa,
    0x00000044,0x03fea000,0x7fdc2ff4,0xbff53405,0x20550d80,0x0ff92ffd,
    0x3fee1bf6,0x5417fc05,0x35c001ff,0xf9809ff5,0x01ff702f,0xff501ff2,
    0x3fea0c0b,0xb30dfb01,0x2da87f47,0x07d4013a,0x00000201,0x3ea00000,
    0x86ff881f,0xb703fff8,0xa827ffc4,0x7fc41aa4,0xfb01ffb2,0x403ffa0d,
    0xffa80ff8,0xb03e6001,0x7fcc05ff,0x201ff702,0x3fe207fd,0xfa89100f,
    0x00dfb01f,0x054407fe,0x00003500,0x00000000,0xdd313fe6,0x3ffee0ff,
    0x40feb89c,0xa9befffb,0x40bea0fd,0x87ff71ff,0x54337ffc,0x03f905ff,
    0x4400bfea,0x0fff882f,0x2e05ff50,0x0ffb01ff,0x9300fff4,0xfb02ffb8,
    0x007fe00f,0x00000000,0x80000000,0x8edceffd,0xfd85dffe,0x02ffffff,
    0xfffffffb,0x542efa89,0x3bffe24f,0x5effcbfd,0x3224ffb8,0x17ff202f,
    0xfd81fa20,0x4ffc80ef,0x3a05ffb0,0x3ffc81ff,0xfd87f530,0x0fff883f,
    0x00003980,0x00000000,0x74400000,0xbfd0dfff,0x7fffe405,0x7ffdc01e,
    0xfffa83ff,0xea82ddcf,0xbff31eff,0x7efff540,0xfffd502d,0x3fe607df,
    0x7ffec0ef,0xfffb34ff,0x3ffae5bf,0xffd92dff,0x3fe61bff,0xffffffff,
    0xfffd53ff,0x3ffb25bf,0x000004ff,0x00000000,0x20000000,0x000540a9,
    0xa9800353,0x54c42201,0x08808800,0x00035100,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__times_36_usascii_x[95]={ 0,3,2,0,1,1,1,1,1,0,2,0,1,1,
2,0,1,3,0,1,0,1,1,1,1,1,2,2,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,
0,0,-1,1,0,1,0,2,0,0,0,0,0,0,0,2,0,1,0,-1,1,1,-1,1,1,1,1,0,0,0,
-3,0,0,0,0,1,-1,1,0,1,0,0,0,0,0,0,0,4,2,2,0, };
static signed short stb__times_36_usascii_y[95]={ 28,5,5,5,4,5,5,5,5,5,5,8,24,19,
24,5,6,6,6,6,6,6,6,6,6,6,13,12,9,13,9,5,5,5,6,5,6,6,6,5,6,6,6,6,
6,6,6,5,6,5,6,5,6,6,6,6,6,6,6,5,5,5,6,33,5,13,5,13,5,13,5,13,5,5,
5,5,5,13,13,13,13,13,13,13,8,13,13,13,13,13,13,5,5,5,17, };
static unsigned short stb__times_36_usascii_w[95]={ 0,5,10,16,14,25,24,4,10,10,12,18,6,9,
4,10,15,10,15,13,16,14,15,14,14,14,5,5,18,18,18,13,29,24,20,20,23,20,17,23,23,11,13,24,
20,29,25,22,17,22,22,15,20,24,24,31,24,24,19,8,10,8,15,18,7,14,17,13,16,13,14,16,17,9,
10,17,9,26,17,15,17,16,12,11,10,17,16,24,16,17,14,10,2,10,18, };
static unsigned short stb__times_36_usascii_h[95]={ 0,24,11,24,27,24,24,11,30,30,14,18,10,3,
5,24,23,22,22,23,22,23,23,23,23,23,16,22,17,8,17,24,31,23,22,24,22,22,22,24,22,22,23,22,
22,22,23,24,22,30,22,24,22,23,23,23,22,22,22,30,24,30,12,3,7,16,24,16,24,16,23,23,23,23,
31,23,23,15,15,16,22,22,15,16,21,16,16,16,15,23,15,31,31,31,5, };
static unsigned short stb__times_36_usascii_s[95]={ 252,168,209,209,130,226,1,251,67,78,180,
146,220,188,164,77,161,85,119,195,102,209,224,240,66,36,245,96,184,227,165,
195,12,203,64,174,40,19,1,99,201,243,81,141,120,90,95,145,225,98,1,
26,49,178,153,121,228,24,70,121,88,89,193,169,246,59,59,19,42,33,51,
19,1,123,1,143,133,120,162,74,166,184,90,47,135,1,228,203,103,177,147,
56,53,42,145, };
static unsigned short stb__times_36_usascii_t[95]={ 1,1,128,1,1,1,33,105,1,1,128,
105,128,26,26,33,33,105,105,33,105,33,33,33,58,58,105,105,105,128,105,
1,1,58,105,1,105,105,105,33,82,82,58,82,82,82,58,1,82,1,82,
33,82,58,58,58,58,82,82,1,33,1,128,26,128,128,33,128,33,128,58,
58,58,33,1,33,33,128,128,128,82,82,128,128,105,128,105,105,128,33,128,
1,1,1,26, };
static unsigned short stb__times_36_usascii_a[95]={ 130,173,212,260,260,433,405,94,
173,173,260,293,130,173,130,145,260,260,260,260,260,260,260,260,
260,260,145,145,293,293,293,231,479,376,347,347,376,318,289,376,
376,173,202,376,318,462,376,376,289,376,347,289,318,376,376,491,
376,376,318,173,145,173,244,260,173,231,260,231,260,231,173,260,
260,145,145,260,145,405,260,260,260,260,173,202,145,260,260,376,
260,260,231,250,104,250,281, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_times_36_usascii_BITMAP_HEIGHT or STB_FONT_times_36_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_times_36_usascii(stb_fontchar font[STB_FONT_times_36_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_times_36_usascii_BITMAP_HEIGHT][STB_FONT_times_36_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__times_36_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_times_36_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_times_36_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_times_36_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_times_36_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_times_36_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__times_36_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__times_36_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__times_36_usascii_s[i] + stb__times_36_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__times_36_usascii_t[i] + stb__times_36_usascii_h[i]) * recip_height;
            font[i].x0 = stb__times_36_usascii_x[i];
            font[i].y0 = stb__times_36_usascii_y[i];
            font[i].x1 = stb__times_36_usascii_x[i] + stb__times_36_usascii_w[i];
            font[i].y1 = stb__times_36_usascii_y[i] + stb__times_36_usascii_h[i];
            font[i].advance_int = (stb__times_36_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__times_36_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__times_36_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__times_36_usascii_s[i] + stb__times_36_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__times_36_usascii_t[i] + stb__times_36_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__times_36_usascii_x[i] - 0.5f;
            font[i].y0f = stb__times_36_usascii_y[i] - 0.5f;
            font[i].x1f = stb__times_36_usascii_x[i] + stb__times_36_usascii_w[i] + 0.5f;
            font[i].y1f = stb__times_36_usascii_y[i] + stb__times_36_usascii_h[i] + 0.5f;
            font[i].advance = stb__times_36_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_times_36_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_times_36_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_times_36_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_times_36_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_times_36_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_times_36_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_times_36_usascii_LINE_SPACING
#endif

