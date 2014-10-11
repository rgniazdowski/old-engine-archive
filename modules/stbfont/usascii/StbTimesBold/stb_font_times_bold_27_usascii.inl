// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_times_bold_27_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_times_bold_27_usascii'.
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

#define STB_FONT_times_bold_27_usascii_BITMAP_WIDTH         256
#define STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT         96
#define STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_times_bold_27_usascii_FIRST_CHAR            32
#define STB_FONT_times_bold_27_usascii_NUM_CHARS             95

#define STB_FONT_times_bold_27_usascii_LINE_SPACING          17

static unsigned int stb__times_bold_27_usascii_pixels[]={
    0x98800530,0x32000aba,0xa8800371,0x20031801,0x33109999,0x55100133,
    0x0e200015,0x21999988,0x98801998,0x5300009a,0x4ccc4183,0x02980a61,
    0xa80a614c,0x5c0b2000,0x26aa2002,0x98075000,0xeda805ff,0x0cbba9ac,
    0x7eccfe20,0x00bfc802,0x00eccb66,0x2e9ffb51,0x2e00adff,0x3ffdbdff,
    0x7bfdb500,0x4ffffb81,0xfb80ffaa,0x03ffdbdf,0x5bb7dd50,0xfffd989d,
    0x5c3fffe9,0x91b604ff,0xdd9fc88d,0xc807dc01,0xbcfd8806,0x03f803fe,
    0xd303ffdc,0x01d8803b,0x02ff87f1,0x3f5013f2,0x7c402f88,0x403ff74f,
    0x7441ffe9,0x27f601ef,0x5c5fd8d9,0x825c1fff,0x7c41ffe8,0x3fea01ef,
    0x509fff10,0xfd33dfff,0x03fff43f,0x7dc5e89f,0x7cc0df75,0x8803ea02,
    0x07fe64ff,0x74401f98,0x007f503f,0x43f881b8,0x3ff105fc,0xfb827cc0,
    0x5d3fe202,0xfff101ff,0x03ffe605,0xdb2cd3ea,0x1d87fff0,0x502fff88,
    0xff301fff,0x984ffe8b,0x3fea1fff,0x441fffa6,0xfd0fe22f,0x7407feab,
    0x3203f805,0x02ffc2ff,0xf30000d9,0x10360003,0x307fd87f,0x3fe205ff,
    0x401ff100,0x03ff74ff,0xfd01fff6,0x26bfb0bf,0x3fee1a25,0x7fec1627,
    0x42ffec07,0x7fec4ffb,0x20fff984,0xff90fff8,0xf987ea0b,0x7d53fe21,
    0x800fb84f,0x17ffa05d,0x02740ffb,0xf1026662,0x4106a207,0x3e1fc429,
    0x09ff106f,0x9f9017f2,0xffba7fc0,0x04fffa81,0x3e17ffdc,0x4145acff,
    0x0552fff8,0xb809fff5,0x7fec2fff,0x4c27fec3,0x3fe20fff,0x4c7ff72f,
    0xcaabfdaa,0x2bff11bf,0x17cc2ffa,0xf900fa80,0x827f45ff,0x7f5401f9,
    0xe983646f,0x245fface,0x4ff88fe2,0x3e217fe0,0x07fdc03f,0x3ff74ff8,
    0x807fff90,0x7e44fffa,0xf9005eff,0x3f2036df,0x7fd403ff,0x217ffc4f,
    0xff984ffd,0x99fffc0f,0x3ffee1ff,0x5fffffff,0x07fd57f6,0x2f88017a,
    0x37ffff50,0x01ee03df,0x0be37fdc,0x7ffc3fea,0x88fe2243,0x17fa03ff,
    0xf300bfee,0x5d3fe09f,0xfffd81ff,0x37ffcc02,0x0bffffe6,0x12bffe60,
    0x2017ffec,0x7f46fff9,0x427fec3f,0x7fc0fff9,0x9883fe1f,0xde999df9,
    0x7ddbea09,0x20007dc5,0x3fff605d,0x13a00dff,0xf537fd40,0x7fc7ff10,
    0x7f10640f,0x3fa03fe8,0x401ffc83,0x9ff05ff8,0x3fe07fee,0x7fcc01ff,
    0xffff987f,0x7fec00df,0x3ffff01f,0x47fff980,0x7fec3ffc,0x20fff984,
    0x1b60fff8,0x07f117c4,0xf30b7326,0x80f70005,0x00effffd,0x3ea005f1,
    0x3fa1726f,0x121bfe27,0x05f987f1,0x3ff60bf1,0x837fc401,0x03ff74ff,
    0x9803ffff,0xfb107fff,0x5401dfff,0x3ffe06ff,0x7ffcc01f,0x3637fd47,
    0xfff984ff,0x991bfea0,0x1f987ea0,0xb88bd000,0x05f101cc,0x77ffffd4,
    0x2a007b80,0xf31366ff,0x427fd49f,0x6cc1fc44,0xf813ae1d,0x7fc401ff,
    0x3ee9ff07,0x2fffe81f,0x037ffcc0,0x013fffee,0x7fec07fd,0x7ffd402f,
    0x45fff446,0xf984fffb,0xffd88eff,0x32621d41,0x99fb999f,0x983ee000,
    0x3a09f96f,0xff37f904,0x00bb0bff,0x87d37fd4,0x3ffa1ffd,0x0fe21c42,
    0x019d1f4c,0x7c00fffc,0x74ff80ff,0xfff903ff,0x5fffa807,0x3fff74c0,
    0xfc803ee0,0x7fdc03ff,0xfffe885f,0xf984ffdb,0x2effeaff,0x7ffdc298,
    0x5fffffff,0xfc85f300,0x1ee0ff55,0x7f4c3ff2,0x0017c47f,0x216cdff5,
    0x1ffe67ff,0xb07f106a,0x207f501d,0x7c401ffe,0x2e9ff07f,0xfff981ff,
    0x0fffdc04,0xffd1b306,0x2602c403,0x7e404fff,0xd86201ff,0xfff984ff,
    0x98800330,0x9df999df,0xf0bd0009,0x20bfeabf,0x23ff41f9,0x3ea1fffb,
    0x9bfea000,0x45bfe24c,0x424c5ffd,0x027e43f8,0x3ffb03fd,0xf06ff880,
    0x407fee9f,0x3a00fffd,0x260d85ff,0x2081ff75,0x7ffc801b,0x002fff40,
    0x3e613ff6,0x053000ff,0x01fc45f1,0xff303ee0,0x7413fe6b,0xf11ffe24,
    0x002ec1ff,0x25a9bfea,0xfadafff8,0x7c41223f,0xfb017fc3,0x805ff909,
    0x9ff05ff9,0x74407fee,0xdff503ff,0xaacc5b01,0x058ffc5f,0x207ffd10,
    0x4000effb,0xff984ffd,0x4ffb800f,0x03f30fd4,0xfe817cc0,0x3203ff55,
    0x7fc3ff46,0x2a001fc6,0xfd1a66ff,0x27ff15ff,0x3f8960ca,0xfe80ffe2,
    0x403ff885,0x9ff02ffa,0xd8807fee,0x77f4c1ff,0x5663fb00,0x2ffe61fd,
    0x7fec002b,0x002ffc41,0xf985ffd8,0xffd800ff,0x03ee3dc6,0x3ee05e80,
    0x7cc0df76,0xf98bfea1,0x0003ea1f,0x22d8dff5,0x3bae1eea,0x7f10d41b,
    0xff105ff8,0x7013f609,0xba7fc0df,0xfda801ff,0x403efdcd,0xefedefeb,
    0x003ffd81,0xfd9bfb70,0xf510007b,0x7ec47fff,0x7d401cff,0x1b62ec3f,
    0x2200fb80,0x402ed8fd,0x667f543f,0x003641df,0x3a237fd4,0x11220000,
    0x306fe87f,0x3fe607ff,0xf80bfa00,0x003ff74f,0x0037ffcc,0x10036e62,
    0x05440000,0x26662000,0x26662199,0x80880099,0x9000d41a,0x00ae2005,
    0x099880cc,0xf5000350,0x000970df,0x87f10362,0x5ff306fd,0xf981fdc0,
    0xfba7fc05,0x7fd4001f,0x0388004f,0x00000000,0x00000000,0x00000000,
    0x00000000,0x3e67ea00,0x0019905f,0x1fc406c4,0x2fe80ff6,0x05d83640,
    0xffba7fc4,0xfffc8001,0x0000000b,0x00000000,0x00000000,0x00000000,
    0x00000000,0x07fe6fee,0x64402d98,0x547f100c,0x077cc05f,0x04d83720,
    0xff74ffb8,0x3f6e0007,0x0001deff,0x00000000,0x00000000,0x00000000,
    0x00000000,0x76f74400,0x59bb7003,0x88019997,0x2005b93f,0x9c402db8,
    0x5554401a,0x1555511a,0x00d4c000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x02200000,0x00013000,0x00000013,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x002aa600,0x20554400,0x99998808,0x53101999,0x26662013,0x26666019,
    0x13333001,0x4c405300,0x26000199,0x33333002,0x54c40033,0x4cccccc0,
    0x98800999,0x22141abb,0x09999999,0x40666662,0x8060aba8,0x753001a8,
    0x3b620015,0x50005ffc,0xbfd9dfd9,0xfd5103b7,0xf5039fff,0xbffff97f,
    0x13ffff26,0x00fbfb22,0x813ffee2,0x983fbcea,0x4000fffd,0x204fffec,
    0x7ffffffb,0x41cfd980,0xfffffff8,0x3fa602ff,0xbcefdbdf,0x7fff5446,
    0x3fae21bf,0x5efec42e,0xdb03cdfe,0x3a609fd7,0x802fffbb,0x05ff51fe,
    0x41dffb80,0x2601ffc9,0xff506fff,0x20d7fec9,0x302ffffb,0xffd8001f,
    0x7ecdf304,0x00fff982,0x3ffffee0,0xffffd02f,0x7ec409ff,0xffff500d,
    0x101fffff,0xb8819ff9,0xfff706ff,0x6c07cc09,0x41fecc2f,0x07ff13fd,
    0x03ffccdb,0x4ff83fea,0x03bfee00,0x3e201fd8,0x5ffd05ff,0x7cc17fe4,
    0x0f01ffff,0x209ffb00,0x03fee4fe,0x2001fff1,0xdfff50c9,0xffffff30,
    0x17fa203f,0xffffff90,0x3ff60bff,0xa837d406,0x1e204fff,0x1fc41fea,
    0xffd8bff2,0xff83fe62,0x87ff203f,0xff7001fe,0x01f8803f,0x7c17ffe2,
    0x13fee1ff,0x3bfffb26,0xfd800680,0x24ffa84f,0x7fc44ffa,0xf905000f,
    0x000790df,0x59d00dfd,0xfb82fb81,0x06d801ff,0x4407fff5,0x901ffc86,
    0x321ffe87,0x8bfea5ff,0x3f205ffe,0x4009f35f,0x37006fff,0x82fffc40,
    0x3ff22ffd,0xfff8c982,0xa880685f,0xf909ffb1,0x22ffd47f,0xa988fff8,
    0x0ffe6000,0x640026fa,0x203803ff,0x7ffc40fd,0x2a0b1005,0x1a203fff,
    0x2207fff2,0xf70fffc3,0x7f44b8ff,0x3ffee03f,0x3e6001ec,0x100004ff,
    0x3ea0bfff,0x203ffa4f,0x7ffff549,0x3ff62068,0xd84ffdde,0x1bfea3ff,
    0xfff5fff1,0x13f2007f,0x0fffffe6,0x0331fff0,0xf70bf100,0x804009ff,
    0x2203fffa,0xdffffa86,0x8bffe200,0x2200fffa,0x3e200eff,0xcccc86ff,
    0x01fffe43,0x5fff8800,0x3ea7bea0,0x7dc9301e,0xd81a2fff,0x9fff50ff,
    0x7d47ffd0,0x77ffc47f,0x402ffd89,0xffc82ffa,0x981effff,0x3fffffff,
    0x360bea00,0x80003fff,0x2203fffa,0xffffe886,0x7fff00cf,0x900fffd4,
    0x774c01df,0x7fc43fff,0x01fffe83,0xbfff1000,0x02ccdb80,0x3fff624c,
    0x3fea0d0f,0x7c27fec5,0x3ffea3ff,0xa83ffe21,0xffd307ff,0xffff89ff,
    0x5c0fffff,0xfffa8dff,0xd01fb003,0x00005fff,0x4407fff5,0xfffff106,
    0xbffb05ff,0xf103ffd4,0x4476440b,0x2f41ffff,0x002ffff8,0x0bfff100,
    0x1260026c,0x835bfffa,0x7fec4ffc,0x2a3fff84,0x3fe21fff,0x07ffe20f,
    0x0fffffd4,0x7fffe4cc,0xf727fec5,0x5f8801ff,0x005ffff0,0x07fff500,
    0xff910344,0xf985ffff,0x5ffc9cff,0x9fd012e0,0x9877ffd4,0x7fffb00e,
    0x3fe20000,0x35df505f,0x424c0333,0x06dffff8,0xffd87ffd,0x2a3fff84,
    0x7ffc47ff,0x2017ffc0,0x4403fffc,0x7ffc7ffd,0x007ffe63,0x3ff607f5,
    0xdddb703f,0xfffa85bd,0x2601a203,0x986ffffd,0x3ffeeffe,0xff980320,
    0xeafffe43,0x13ffee01,0x7ffc4000,0xfffff905,0x09309fff,0x41bfffe6,
    0x7fec3fff,0x2a3ffe84,0x7ffc46ff,0x4017ffc0,0xf9005ffd,0x127ffc1f,
    0xfd805fff,0x09fff700,0x407fffcc,0x2203fffa,0xffd50386,0x7fc2203f,
    0xfb00e01f,0xdfffd0df,0x6fff8809,0x10dd8800,0x3e609fff,0xffffffff,
    0xff7024c3,0x13ffa0df,0xff909ffb,0x222ffd47,0x7ffc0fff,0x03ffa800,
    0xffd8ff10,0x100fffc4,0x7ffcc0df,0x1bffe205,0x3027ffc4,0x3a201b0b,
    0x7fd403ff,0x7ffc0005,0x7fffcc1f,0x7ffec044,0x3ff21802,0x407fff14,
    0xfecccdec,0x32024c4f,0x9ff906ff,0xfa84ffd8,0x10ffea4f,0x7fc41fff,
    0x007fe007,0x2ffdc4e8,0x7f501ffe,0x00fffc80,0xff81bffe,0x3612e04f,
    0x00bfea03,0x54401ffb,0x3ffff600,0x77fffe41,0xdffb05a9,0x3fee7a80,
    0x205fff13,0x87f500fe,0x06fe805a,0xffe8dff5,0x7dc9fd05,0x07ffc40f,
    0x26c49ff3,0x0fae2fc4,0xfff107e2,0xb017fe21,0xbffd001f,0xb037ffc0,
    0x03a20dff,0x7fd407f6,0x007bf600,0x3e603ffd,0xfdcdffff,0x0ffffffc,
    0x82b7ff60,0x87f40dc9,0x3fa05ffa,0x7c81db02,0x3a06e880,0xffed9bff,
    0x3a6f980e,0x3fff883f,0xdff717f6,0x3fe07645,0x203911ef,0x1df53ff9,
    0x91006f80,0xfff019ff,0x6fff440d,0x7ec0ba60,0x817ec0bf,0x4400dfd8,
    0x3a603fff,0x263fffff,0xa802fffe,0x3efeffec,0x9ff9d930,0xcdefc880,
    0x7fed44dd,0x1034c03e,0xdfb5fffd,0x377a607b,0xf57f102f,0xfb109fbb,
    0x2a07ddff,0x01defffe,0x06f67ed4,0x3000fea0,0xfd99dffb,0xfd88015b,
    0x202effff,0xfccfebcd,0x1cfd981e,0x003ff600,0x198026a2,0x00351000,
    0x98800198,0x01800001,0x80022188,0x26044018,0x00133001,0x0c40004c,
    0x00015300,0x000cd4c4,0x30033510,0x31009a88,0x000c0001,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x44000000,0x81999999,0x31099999,0x4cc33333,0x4c099999,0x00a88199,
    0x33333300,0x33333333,0x26666621,0x26666099,0x26666219,0x4c001999,
    0x98800999,0x00199999,0x99815530,0x33100099,0x26003333,0x31099999,
    0x03333333,0x33333310,0x99998813,0x06666209,0x33333331,0x7ffff543,
    0xeffca82c,0x7ffffd50,0xfffff511,0x0cfeb837,0x07203ffc,0xffdffff1,
    0x5fffddff,0x3fffff66,0x37ff6a0b,0x3fffaa62,0x04efffee,0x00bfff22,
    0x3ffffaa2,0x4c03dfff,0x913ff9ee,0x22005fff,0x02ffffea,0x577fffcc,
    0xffffd510,0xfd510037,0xca837fff,0x3660bfff,0x3aa20fff,0x441bffff,
    0x7400ffff,0x86fffa84,0x2e07fff9,0x01fff985,0x1df883f5,0x5f91fffa,
    0x307fffd8,0x7ffdc07f,0x03bff663,0x0017ffc4,0x3669fff3,0xbfb00eff,
    0xfff897fe,0x7ff54002,0x7ff6405f,0xbfff502f,0xdfff3000,0x9806fd40,
    0xffa80fff,0x3fff205f,0x7403e202,0xffe81fff,0x3605901f,0x83ff305f,
    0x3fff40f8,0x3ffe216c,0x5404c84f,0x7fcc3fff,0x0bffe05f,0x24fff880,
    0xf885fffa,0xff81735f,0x764c002f,0x9d101fff,0x3e605fff,0xf98004ff,
    0x09f105ff,0x980fff88,0x3e604fff,0x812e06ff,0xfa84fffb,0x000d04ff,
    0x426bffe6,0x87ffe858,0xffffa82a,0x3e6016a1,0x7ffe83ff,0x800bffe0,
    0x7fc4fff8,0x05ffb87f,0x20017ffc,0x04fffac9,0x03fff977,0x0013ffe6,
    0x2617ffe2,0xfff8802e,0x04fff980,0xe80fffec,0x1fffe200,0x2543fffc,
    0x2a0cccc4,0x26ffffff,0x107ffe80,0x45bfff20,0xfff9800e,0x01fffc83,
    0x02a25fff,0x744fff88,0x7fecc7ff,0x5fff009d,0x4c04cccc,0xd01ffff4,
    0x203fff91,0x8004fff9,0x7545fff8,0x1fff1001,0x809fff30,0x4a85fffa,
    0x42fffc80,0x6c2ffff9,0x0fffd980,0x800fffc4,0x44007ffe,0x01ecfffe,
    0xd07fff30,0x3fe01fff,0x04fffcaf,0x7c49fff1,0x3ffe65ff,0xfff02fff,
    0x0b7fee25,0x1fffe526,0x0fffe52a,0x004fff98,0x325fff88,0x3fe2000d,
    0x4fff980f,0x40fffe80,0xfff9800d,0x2fffde45,0x7ffcc0d1,0x00fffc40,
    0x8007ffe8,0x003ffff9,0xf30fffe6,0x7ffc09ff,0x82fff9bf,0x3ee4fff8,
    0x5ffc81ff,0x3e17ffc0,0x7fc52603,0xffc8ec6f,0x9fff301f,0xbfff1000,
    0x88007fb1,0xff980fff,0xfffb804f,0xfe801663,0x7ff5a0ff,0x7c40570f,
    0x7ffc40ff,0x0fffd001,0x1bfff200,0x9cfff980,0x403fffba,0x3ff63fff,
    0xacfff883,0xf901effd,0x2fff80bf,0x6c9300f2,0x64b12fff,0xff301fff,
    0xff10009f,0x05fffddf,0x407ffc40,0x8804fff9,0x00727fff,0x774fffb8,
    0x0753ffee,0x881fff10,0xfd001fff,0x7f4000ff,0xff3004ff,0x1ffffbbf,
    0x6c5fff00,0xfff884ff,0x6402ccce,0x7ffc05ff,0x49300792,0x4575fff9,
    0xf301fffc,0xf10009ff,0xffff9dff,0x3ffe2001,0x04fff980,0xd15fff90,
    0x7fff8800,0x3fffe21d,0x7ffc4059,0x00fffc40,0x0007ffe8,0x03ffffd5,
    0x3a7fff30,0xff803fff,0x213ff22f,0x4004fff8,0x7fc05ffc,0x9806fcaf,
    0x34ffff44,0x4c07fff2,0x88004fff,0xfffb5fff,0x3ffe200d,0x04fff980,
    0x57dfff30,0x9fff9000,0x1efffd89,0x207ffc40,0xd001fff8,0xd1000fff,
    0x01dfff91,0xf13fff98,0xff803fff,0x213ff22f,0x4004fff8,0x7fc05ffc,
    0x403fffef,0x77ffd449,0x80fffe43,0x4404fff9,0x8afffc41,0x8805fffe,
    0xff980fff,0x3ff6004f,0xff30006f,0xfff983ff,0x0fff8806,0x800fffc4,
    0x44007ffe,0x13fffa1e,0x5c7fff30,0x7fc06fff,0x213ff22f,0x4004fff8,
    0x7fc05ffc,0x01fffbbf,0x3fffe126,0x80fffe40,0x6404fff9,0x32fffc41,
    0x8807ffff,0xff980fff,0x3fea004f,0x3fa0003f,0x07ffd06f,0xf01fff10,
    0xfd0063ff,0x42d800ff,0x202ffff9,0x7ec3fff9,0x3ffe04ff,0x2213ff22,
    0x64004fff,0x7ffc05ff,0x4c0dffd2,0xc85ffc84,0xff301fff,0x440f809f,
    0x7fd45fff,0x3fe201ff,0x4fff980f,0x007ff400,0x205ff700,0xf8800ffb,
    0xcffd80ff,0x7fff402c,0x3209b000,0xf500efff,0xfff887ff,0x45fff02f,
    0xff884ffd,0x7fe4004f,0x897ffc05,0x0b304fff,0xff903ff1,0x3ffe605f,
    0x3e61f204,0xfffc85ff,0x3fff101f,0x009fff30,0x40004fb8,0x1be207f8,
    0x40fffcc0,0xf803ffd8,0xfd800fff,0x17fffe02,0x5427ffdc,0x7c40ffff,
    0x17ffa3ff,0x0017ffe6,0x7c40dff9,0x3ffee3ff,0x0db06b81,0x540bfff6,
    0xfc986fff,0x86fff987,0x81fffff8,0xfa82fff9,0x7c4005ff,0x04c80000,
    0x7f4c016c,0x00101eff,0x7dffffb7,0x7dffd701,0x7fffecc1,0xfff931ef,
    0xffc859ff,0xfffb13ff,0x7ffff73d,0x3ffffb22,0x7fe4402c,0x7ec40dff,
    0xfff91eff,0x3bff267f,0x3f2a1cc4,0x731cffff,0xffffffff,0x5c4dffff,
    0x12dffffe,0x9ffffff9,0x3bfffa61,0xffffd731,0x000c005b,0x04c00880,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x98800000,0x99999999,0x26662099,0x33119999,
    0x22133333,0x81999999,0x31099998,0x33333333,0x4cc43333,0x99999999,
    0x4ccc4199,0x22000999,0x19999999,0x00008000,0x00066028,0x01550035,
    0x44003b80,0x883300aa,0x26219999,0x98666619,0x15c40999,0xeeeefff8,
    0x223ffffe,0x1bffffea,0x5dffff73,0x3ffff6a1,0xcffc982d,0xffffd510,
    0x1ffffddd,0x3ffffae2,0x47fffeee,0xeeffffb8,0x5300bcef,0xffddfffd,
    0x590005df,0x0ff71000,0x5c013fee,0xfff9105f,0x02ec007f,0x8bfd7f90,
    0x3fea4ffb,0x4ffa64ff,0xf71fffd8,0x4ffe89ff,0xffc81ef8,0xbfff306f,
    0x40bfff60,0x7403fffe,0x0bfff303,0xff981fd5,0x707fb84f,0x7fd47fff,
    0x3ffea03f,0x013ffee3,0x22006f88,0xfd07fffc,0xbff300df,0x3fffff20,
    0x00bb003f,0x1ffd53f2,0xffb8fffd,0x3e22dc1f,0x93ffa1ff,0x7c47fff8,
    0x1ffff980,0x20bfff30,0xf301fffc,0x034c0fff,0x7c0bfff3,0x827ffcc0,
    0x7fff5079,0x304fffa8,0xffd87fff,0x3ff7001f,0xffd57100,0x013fee0f,
    0x3a617ffa,0x07fffebb,0xff100bb0,0xff737fc5,0x43fff889,0x21fff80e,
    0x7fe44ffd,0x7f41261f,0x3fe604ff,0x3fff904f,0x81fffec0,0x3ffe201e,
    0xff303205,0x541a189f,0xffc83fff,0x3fff982f,0x801fffdc,0x64005fff,
    0x006607ff,0x1217fff2,0x2003fffa,0x1ffa805d,0x20530b6a,0x41626ffc,
    0x3ff61fff,0x04469884,0x007fffdc,0x3209fff3,0x3e201fff,0x025c0fff,
    0x1717ffe2,0x9fff3022,0x3ea051cc,0xfff983ff,0x43fff985,0xb802fffb,
    0x2000ffff,0x40007ffb,0x005ffbda,0x3600fff7,0x01ffd805,0x97ffc400,
    0x43fff01b,0x07704ffd,0x05ffff10,0x904fff98,0xfc803fff,0x003a24ff,
    0x0d8bfff1,0xb93ffe60,0x3fffa803,0xf30ffff0,0x7ffd87ff,0x9fff7d00,
    0x03ffdc00,0xff71d100,0x17fe600b,0xffddddd5,0x7c5ddddd,0xd80002ff,
    0x7fc0b5ff,0x213ff61f,0xffd800d9,0xfff9805f,0x03fff904,0x90ffff88,
    0xbfff1005,0xff3007dc,0x200fa69f,0xfd03fffa,0xfff983ff,0x019ffb33,
    0x3fffe950,0x0fff7000,0xffb8f400,0x85ff7005,0xffeeeeea,0x3e2eeeee,
    0x980004ff,0x3e03cfff,0x13ff61ff,0x3fe60075,0xff9800ff,0xfeeeeeff,
    0xfb801fff,0x10069dff,0xffd9dfff,0x77ffcc01,0xfa803ffe,0xfffb03ff,
    0xfffff987,0x36002fff,0x007fff91,0x5c41ffee,0x7fdc7902,0x00bfb005,
    0x7fec02ec,0x005dc00f,0x7c01fffd,0x13ff61ff,0x3fffe800,0x3bfff300,
    0xfffb3333,0x3fffe003,0xfff1001e,0x401ffb5b,0xfdadfff9,0x3fffa803,
    0x987fffb0,0xfc99bfff,0x12cc03ef,0x2e00dfff,0xbffd07ff,0x2ffdc6a8,
    0x0007fc40,0xfff500bb,0xbff90b8b,0x2027fd40,0xffd12ffe,0x3fee0009,
    0x3fe6006f,0x3fff904f,0x17ffee00,0x25fff880,0x3fe600f9,0x2a00f64f,
    0xffd03fff,0x3fff985f,0x902fffdc,0x02fffd85,0xf887ffb8,0x81d10fff,
    0xfc805ffb,0x802ec002,0x2ecefffd,0xff01fffa,0xadffd801,0x8005ffee,
    0x201ffff8,0x827ffcc3,0x1001fffc,0x4400bfff,0x00645fff,0x1d49fff3,
    0x81fffd40,0x7cc0ffff,0x7ffc43ff,0xaaaf880f,0x806fffca,0xff907ffb,
    0x3fffea3f,0x01ffffff,0xbb0005f3,0x77ffe400,0x201ffd42,0xffe8805b,
    0x03fffd9e,0x027ffec0,0x4fff98b3,0x003fff90,0x8017ffe2,0x05c5fff8,
    0x449fff30,0x3fea0643,0x6fff883f,0xe83fff98,0xacb82fff,0xfffeaaaa,
    0x03ffdc01,0x7ffd4d31,0x1fffffff,0x80283e88,0x0098005d,0x00220022,
    0x50000098,0x6c01ffff,0x827ffcc4,0x1001fffc,0x4400bfff,0x4c005fff,
    0x1e604fff,0x320fffea,0xff981fff,0x1ffff83f,0xfff50344,0x07ffb80b,
    0x5555125c,0x015dffb5,0xb533339b,0x00003500,0x00000000,0xffff1000,
    0x261fdc05,0xff905fff,0x3fe2003f,0x3fe6005f,0x7fcc005f,0x2a1ba05f,
    0x7fc43fff,0x7fff303f,0xc85fffa8,0x07fffc04,0x4c0fff90,0x5ffb800d,
    0xffffff90,0x0000009f,0x00000000,0x7ffe4000,0x2ffe9885,0xd82fffd4,
    0xf3002fff,0x7cc00dff,0x7d4006ff,0x7f64c6ff,0x24fffb84,0x2a02ffe9,
    0x3fea5fff,0x027cc0df,0xd817fff2,0x03a80fff,0x2a17fee0,0xffffffff,
    0x00000002,0x00000000,0xfffff300,0xffffffff,0x3ffae63f,0xff952dff,
    0x26037fff,0xadffffeb,0xfffd7100,0xeb9805bf,0xffefffff,0x3f263fff,
    0xceffffff,0x3fff2602,0x1ceeffff,0x41cfffb8,0xdfffffc9,0xffff9710,
    0x5c00017d,0x7ffcc5ff,0x01ffffff,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x40000000,0x33099998,0x26661333,0x00155100,0x51001551,0x05544063,
    0x22133330,0x3333301a,0x4cc13333,0x98866099,0x99889999,0x00017509,
    0x262b8800,0x03510999,0x05300153,0x06a014c0,0x20a88151,0xddddddda,
    0x912ddddd,0x00aa0199,0x5c05dc11,0xfc8affff,0x1bf71dff,0x05f97f90,
    0x06fde7ec,0x37f5f6c4,0x3bfaf762,0x57ffe441,0xff85fffc,0x1fffeccd,
    0x3a2fffee,0xfffb11ff,0x219fd33d,0x0001cffb,0x917fe4c0,0xfff77fff,
    0x7fffd11d,0xd001ff80,0x8bff201f,0x9bfe0ffe,0xeeeeeeea,0x2a2eeeee,
    0x7ffd42ff,0xf90c81cf,0x1fff209f,0x80e8bffd,0x207fe4fd,0x21bf26fd,
    0xf89f23fb,0x221bfe27,0xff9bffff,0xff10fc2f,0xb7fff09f,0xffe85fff,
    0x3f260ba6,0x540002ef,0xff81cffd,0xdffd8bff,0x00fffa9e,0x3ee003fe,
    0x27ffd05f,0xff31fff8,0x5c00001f,0x7655f45f,0x25cabeff,0xff106ffd,
    0x13ffec5f,0x745ff509,0x527fd45f,0x0efe89ff,0x3e3ffb9a,0x3fff80ff,
    0xd890fff6,0xffe80fff,0xf984b8af,0x4403bbff,0x000cffeb,0x017dff71,
    0xff727ff4,0x30fffc1f,0x16cd725b,0x40fe6fc4,0x3ffe2ffd,0x000fff10,
    0x41ccf700,0x21efffd9,0x3f203ffa,0x5fffb15f,0x83ff606e,0x1ffec7fd,
    0xffe8dff3,0x17fd432f,0xfff03fff,0x8227fec5,0xfd03fffa,0x3ff200df,
    0x7ecc005f,0xffb302df,0x3ffa003b,0xfd1ffea3,0x4effdc5f,0xfc85ffbb,
    0xffb86f88,0xbfd1bf60,0x77777754,0x02eeeeee,0x98802215,0xf9801101,
    0xffdab8ff,0x3bffa0d5,0x3e0fffee,0x3ffe62ff,0x0ffffee0,0x7ffecc22,
    0x362fff81,0x3ffa04ff,0x013ffa06,0x0027ffc4,0x31fffb88,0x80019ffd,
    0x3fea3ffe,0x2e1fff47,0x0bccedcc,0x85f727cc,0x227dc6f9,0x3332a3fc,
    0xcccccccc,0x0000002c,0x56fffe00,0xf04afffa,0xff8803ff,0x07ffe62f,
    0x309ffffb,0x03fff3dd,0x7fec5fff,0x03fff904,0x9001fff4,0x30001fff,
    0x3a63dff9,0x74000cff,0x1ffea3ff,0x36a07ffd,0xd03f603b,0x2f989f0d,
    0x80000fd4,0x3eeeeeea,0xf9000000,0x7fffc9ff,0x009ffd01,0x7fcc5fff,
    0xffffb80f,0x7fc3bee1,0x22fff81f,0xff984ffd,0x1fff404f,0x09fff300,
    0x0e7fed40,0x02dffda8,0x7d47ffd0,0x41fff47f,0x40ef9afd,0x43fa83fa,
    0x3c40f82d,0x4ccccccc,0xf5099999,0x007fffff,0x3fe60000,0x81bff21f,
    0x6c087ffb,0x1ffe63ff,0x99fffcc7,0x07ffe3ff,0xffd8bffe,0x20fffd84,
    0x01fff409,0x01fff9b0,0x05f7fdc4,0xbeffb880,0xa8fffa00,0x1fff47ff,
    0x17f43fe2,0x20fe81ba,0x88301809,0xffffffff,0x9932ffff,0x00059999,
    0x237f4000,0x3e603ff9,0x3ea243ff,0xd13fea3f,0xfd97fcc3,0x03fff34f,
    0x7fec5fff,0x21fffd44,0x01fff40e,0x0bfff2b8,0x005bffb3,0x1dffda80,
    0x3ea3ffe8,0x41fff47f,0x0003262b,0x4cc00000,0x99999999,0x00000099,
    0x41fdc000,0x7ff400fe,0xfd80ecef,0xdb03bf26,0x7ec3fe21,0xcfffdfff,
    0xe8fffe22,0x3ffa25ff,0xff03f226,0x5cd5007f,0x3fee2fff,0x4400000c,
    0x7ffc3ffc,0xf83ffee4,0x000004ff,0x00000000,0x00000000,0x6b80f880,
    0xdfffd880,0x3f37f201,0xedfed80d,0x4bbfa61f,0x3f625ffa,0xfffb9eff,
    0xddfff93f,0xffd8fffd,0xffb303ef,0x7ffffb15,0x000000aa,0xffffb154,
    0x1bfffd35,0x005ffffb,0x00000000,0x00000000,0x20300000,0x02620018,
    0x30401980,0x00000403,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__times_bold_27_usascii_x[95]={ 0,2,2,0,0,1,0,1,0,0,1,0,0,0,
1,0,0,1,0,0,0,0,0,0,0,0,2,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,1,-1,0,1,0,0,0,0,0,0,0,0,
-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0, };
static signed short stb__times_bold_27_usascii_y[95]={ 21,4,4,4,4,4,4,4,4,4,4,6,17,14,
17,4,4,4,4,4,4,4,4,4,4,4,9,9,7,10,7,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,24,4,9,4,9,4,9,4,9,4,4,
4,4,4,9,9,9,9,9,9,9,5,9,9,9,9,9,9,4,4,4,12, };
static unsigned short stb__times_bold_27_usascii_w[95]={ 0,5,10,12,12,22,20,5,8,8,10,14,6,8,
5,7,12,10,12,11,12,12,12,12,12,12,5,6,14,14,14,10,22,18,16,17,17,16,15,19,19,9,13,20,
16,23,18,19,15,19,18,12,16,18,18,25,18,18,16,6,7,6,12,14,6,11,13,11,14,11,10,12,13,7,
8,14,7,20,13,12,13,14,11,9,8,13,12,18,12,12,11,8,3,7,14, };
static unsigned short stb__times_bold_27_usascii_h[95]={ 0,18,9,18,19,18,18,9,22,22,10,14,9,3,
5,18,18,17,17,18,17,18,18,18,18,18,13,17,12,6,12,18,23,17,17,18,17,17,17,18,17,17,18,17,
17,17,18,18,17,22,17,18,17,18,18,18,17,17,17,22,18,22,10,3,5,13,18,13,18,13,17,18,17,17,
23,17,17,12,12,13,18,18,12,13,17,13,13,13,12,18,12,22,23,22,5, };
static unsigned short stb__times_bold_27_usascii_s[95]={ 252,181,193,187,106,200,1,204,54,63,169,
188,248,225,247,244,101,144,175,128,162,140,153,166,231,231,215,155,133,210,118,
244,10,125,108,22,90,73,57,179,18,244,40,215,198,174,67,132,132,86,99,
218,63,199,1,20,80,38,1,79,223,72,180,210,225,55,114,203,86,20,148,
54,118,46,1,159,236,148,67,32,167,152,93,45,54,234,221,1,105,119,81,
45,33,37,232, };
static unsigned short stb__times_bold_27_usascii_t[95]={ 1,1,81,1,1,1,25,81,1,1,81,
63,63,87,81,1,25,63,63,25,63,25,25,25,1,25,63,63,81,81,81,
25,1,63,63,25,63,63,63,25,63,44,25,44,44,44,25,1,44,1,44,
25,44,25,44,44,44,63,63,1,1,1,81,88,81,81,25,63,25,81,44,
25,44,44,1,44,44,81,81,81,1,1,81,81,44,63,63,81,81,1,81,
1,1,1,81, };
static unsigned short stb__times_bold_27_usascii_a[95]={ 98,130,217,195,195,390,325,108,
130,130,195,222,98,130,98,108,195,195,195,195,195,195,195,195,
195,195,130,130,222,222,222,195,363,282,260,282,282,260,238,303,
303,152,195,303,260,368,282,303,238,303,282,217,260,282,282,390,
282,282,260,130,108,130,227,195,130,195,217,173,217,173,130,195,
217,108,130,217,108,325,217,195,217,217,173,152,130,217,195,282,
195,195,173,154,86,154,203, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT or STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_times_bold_27_usascii(stb_fontchar font[STB_FONT_times_bold_27_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT][STB_FONT_times_bold_27_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__times_bold_27_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_times_bold_27_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_times_bold_27_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_times_bold_27_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_times_bold_27_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__times_bold_27_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__times_bold_27_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__times_bold_27_usascii_s[i] + stb__times_bold_27_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__times_bold_27_usascii_t[i] + stb__times_bold_27_usascii_h[i]) * recip_height;
            font[i].x0 = stb__times_bold_27_usascii_x[i];
            font[i].y0 = stb__times_bold_27_usascii_y[i];
            font[i].x1 = stb__times_bold_27_usascii_x[i] + stb__times_bold_27_usascii_w[i];
            font[i].y1 = stb__times_bold_27_usascii_y[i] + stb__times_bold_27_usascii_h[i];
            font[i].advance_int = (stb__times_bold_27_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__times_bold_27_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__times_bold_27_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__times_bold_27_usascii_s[i] + stb__times_bold_27_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__times_bold_27_usascii_t[i] + stb__times_bold_27_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__times_bold_27_usascii_x[i] - 0.5f;
            font[i].y0f = stb__times_bold_27_usascii_y[i] - 0.5f;
            font[i].x1f = stb__times_bold_27_usascii_x[i] + stb__times_bold_27_usascii_w[i] + 0.5f;
            font[i].y1f = stb__times_bold_27_usascii_y[i] + stb__times_bold_27_usascii_h[i] + 0.5f;
            font[i].advance = stb__times_bold_27_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_times_bold_27_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_times_bold_27_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_times_bold_27_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_times_bold_27_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_times_bold_27_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_times_bold_27_usascii_LINE_SPACING
#endif

