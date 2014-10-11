// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_courier_bold_20_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_courier_bold_20_usascii'.
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

#define STB_FONT_courier_bold_20_usascii_BITMAP_WIDTH         256
#define STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT         56
#define STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT_POW2    64

#define STB_FONT_courier_bold_20_usascii_FIRST_CHAR            32
#define STB_FONT_courier_bold_20_usascii_NUM_CHARS             95

#define STB_FONT_courier_bold_20_usascii_LINE_SPACING           9

static unsigned int stb__courier_bold_20_usascii_pixels[]={
    0x0a200330,0x00002008,0x00833100,0x26202213,0x2000a209,0x0a9801ca,
    0x00002a60,0x99998000,0x00028809,0xa880054c,0x98001980,0x4400000a,
    0x33333102,0x40262033,0x20fb007f,0x03ff00fb,0x5db21fe4,0xb8fffec7,
    0xee9fcc0f,0xb8fffe40,0xfff9002f,0xffb103df,0xfffe885f,0xfebeec83,
    0x3fae202d,0x3fe3eebd,0x7fc3ffff,0xb80ffa63,0x2a05fffe,0xff12fffe,
    0xfffd800f,0xb9ff9104,0x7fecc3bd,0x7fffec4f,0x0dfd07ff,0x17e60132,
    0x702b3f62,0x077e60ff,0xc983f6fb,0xe81f91fe,0xfc89f71f,0x00df10bc,
    0xff935df7,0x1f70ec81,0x0ff5efe4,0x3bbffff6,0xefff986f,0x3fe4ffff,
    0x3e20cccc,0x07a2ba4f,0x3f6b3fe2,0xbacffa83,0xc801fae0,0x542fdbdf,
    0xeffffeff,0x3f6f3f61,0x33333f22,0x06ffa87f,0x2a0fe400,0xc85fffff,
    0xe81fc80f,0x47f20fb7,0x897e60fc,0x203f20ff,0x1fe201fc,0xf85d17ea,
    0x84f99be2,0x0bee1efc,0x17fcc5fb,0x4ffe01be,0x4140ee69,0x0077cc6e,
    0x47e801f6,0xf90fec7f,0x37c4f98f,0x445f8873,0xddb16fff,0x3e201ddd,
    0xfb9afe86,0xfc80fc85,0x20fd6e80,0x6c1f91fc,0xf91fe41f,0x540bf101,
    0x7c4ff04f,0x3e65f710,0x0fe43743,0x709f1374,0x1caef85f,0x55f47ff0,
    0x8df3001e,0xbfd801fb,0x8bf02dfe,0xf09f11fc,0x3e24f98f,0x3217dc06,
    0xffd36ebf,0x3f201fff,0x0662fc42,0x83f203f2,0xeffffffa,0x0fc8fe41,
    0xc97e61fe,0x203fb00f,0x21f901fc,0x25fdf56a,0x207e41fb,0x267e82fc,
    0x7c2fc84f,0x741effff,0x2ab7262f,0xffed80fd,0x177e7741,0xffefffd8,
    0x3fe27d86,0x0fd07f32,0x07fd9bfd,0xeb7c47e8,0x2203f206,0x59ffb06f,
    0x36217e40,0x3bff660f,0x8fe41dff,0x10df10fc,0x9807e4df,0x205f705f,
    0x536d70fd,0xfc83f92e,0xc9977e40,0x445ffc5f,0x5ee42ffb,0x0fec4fb9,
    0x017bfb51,0xf887fff6,0xd85fefff,0x85f911ef,0x3ffebefa,0x87fa83ba,
    0x00fffffa,0x23fb17e2,0x203f206e,0x3fee02fb,0x3ff981ff,0x53e21bfe,
    0x323f905f,0x3e0bf30f,0xfd803f27,0xf885f880,0x2e975ae7,0x40fc83f7,
    0xeffffffc,0x7ffffcc0,0x47d802ff,0x77bf70fc,0x8ff50039,0xb03f65ff,
    0xf70bf05f,0x7dc5fdff,0x447ffecf,0x05fdacff,0x9efa8bee,0x1f900ee9,
    0x2e200df0,0x20dfb85f,0x6fd447fb,0x1fc80df9,0x417e61f9,0xa803f27f,
    0x445fd04f,0x7ddea3fd,0xf89f33fd,0xcec9fc86,0x5deed401,0x21fb802f,
    0x5ee42249,0x21fc802e,0xb0bea0fe,0x540fb03f,0x7ed40fe8,0x1fd47eef,
    0x647e81fa,0x06ffffff,0x03fb81f9,0xc87d81f5,0x3a0fc80f,0x87ffffff,
    0x7c1f91fc,0x3f25f986,0x4c07f400,0x46ffcefe,0x45b931f9,0x320fe66f,
    0x7d40000f,0x01f60222,0xb00b50f8,0xf717e43f,0x7c44fd83,0x817f2204,
    0x2fa8fd08,0x45f983f4,0x1ffcccca,0x0fe81f90,0xf935df90,0xf901f90b,
    0x7eefecc1,0xf91fc82e,0x3ea07f41,0xf5003f24,0x3fffa207,0xfb807f04,
    0xfc80ffce,0x17d40000,0x9fd99bfb,0x325d0398,0x3b333f64,0x6e7fc46f,
    0x77ffe46f,0x66c0ffdc,0xb8806ffd,0x66ffc45f,0x05f705fe,0xc81ffed4,
    0xb80fea0f,0x81efffff,0x40fc80fc,0x903f9afa,0xfb83f23f,0x1f90ff44,
    0x3e60fd00,0x644a9bff,0xfc81711e,0xfffe82ff,0x7fd4000f,0xffdb35ff,
    0x81fd819f,0x3660efe9,0xa80dffff,0x7f41dffe,0x81cfffdf,0x2a02dffe,
    0x980fffff,0x2e04fffe,0x2fffdc06,0x03fa0fd8,0x03fd9988,0x07ee03f6,
    0x205f53f7,0x441f91fc,0xc8bf50ff,0x83fb800f,0xfffffffe,0x077f7f40,
    0x3332e018,0x664c000c,0x401882cc,0x02600400,0x18800440,0xc9800880,
    0x0c400bcc,0xf5000000,0x90027ccd,0x417fa01f,0x27ee3ff9,0x7ffdc1fb,
    0x3fb81f91,0xfffc83fb,0x5d437c01,0x300aba9a,0x00000015,0x00000000,
    0x00000000,0x00000000,0x26000000,0x2a1fffff,0x81ee000f,0x876600bc,
    0xdb509148,0x8e41261d,0x0deeb83b,0x00003540,0x00000000,0x00000000,
    0x00000000,0x00000000,0xcc880000,0x100000bc,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x40099800,0x00131008,0x99800262,0x2600d401,0xbdd50ded,
    0x2a003301,0x029800bc,0xaaa80098,0xcb980aaa,0x973009ac,0x2aa21339,
    0x5055550a,0x65c40599,0x2aaa219b,0x512aaaaa,0x54015555,0x2aaa22aa,
    0x54455511,0x88aaa22a,0x00cb82aa,0x6d40bff6,0x3ff25fff,0x06ff9803,
    0x00ffff88,0xdff501ba,0x103bfee1,0xfffc80ff,0xfff502ff,0x7fedc49f,
    0x7fffd401,0x7ffdc5ff,0xffc85fff,0xffb4ffff,0x5ffff1bf,0x3fffffe2,
    0x7ffffdc1,0xfffff30f,0x3ff2dfff,0x4c1dffff,0xff91ffff,0x43ffeedf,
    0xff70fffd,0x83fff23f,0x36602ff8,0xccff882f,0x00ff665e,0x5c01bee2,
    0x1ba00fec,0x1fd0fee0,0x7dc09910,0x40ffc9be,0x2febbef9,0x003ffff7,
    0x415bf753,0xfc98adfb,0x4c4f7dc5,0x15fb15fd,0xdf88ff26,0x3e24fa89,
    0x30ffa89d,0xf57fb5bf,0x2ab7ee2d,0x1ff985fc,0xfb837ee2,0xf707be66,
    0x540ffd4d,0xa82fa803,0x01fcc02f,0xfc800df0,0xeeffea80,0x50fe80de,
    0x3e20009f,0x7e45fa87,0xc8a97e21,0x13e2001f,0x3e1f41ba,0x1f64f886,
    0xd83d0bee,0x4f70bee7,0x3a1f93f9,0x3f70fe66,0x1fc83fb0,0x03fd2fd8,
    0x07fe33f2,0xcdfeb880,0x3bfb662f,0xedf985ee,0x65be04ff,0x1f900dee,
    0xffffff70,0x3a7f701d,0x0eeed80f,0x8ff04fa8,0x6437c418,0x13e2001f,
    0x3e6007f1,0x43ec1304,0x37cc02fb,0x10415df3,0x2ec3f25f,0x07f447f3,
    0x0df127cc,0x013f3fe2,0x4005fffb,0xffffeff9,0x3ffffa62,0xefff986f,
    0x3adf04ff,0x1f900eff,0xfd003740,0x3ffa09f7,0x901fc80f,0x83fd803f,
    0x3e2001fc,0xa8017d44,0x70fb002f,0x3ff6605f,0x677ffdc2,0x201f9040,
    0x3ffeeef9,0x1fdc3fa0,0x100dff50,0x1e4c0bff,0x17fd43fb,0x3e600fdc,
    0x77c1be0e,0x7e400efd,0xa801ba00,0x7e400fff,0xfb02fb80,0xc82fec01,
    0xf887b01f,0xffb17d44,0x00bea3ff,0x817dc3ec,0xb7100dfc,0x07e40dff,
    0x5fffff98,0x0fe9fdc0,0x5c017ec0,0x3f900fff,0x0bf613e2,0x7f3007ee,
    0xdfff07d8,0xe803f200,0x027f4006,0x2fd407e4,0xfe883fc4,0x7c07f205,
    0x3e627c45,0x47ffbae4,0x1f9005f8,0x0b301fb8,0x40bf2066,0x27f300fc,
    0x77c02ff9,0x0fc804f9,0x77d77d40,0x0bea5f80,0x07ee0bee,0x07d87f30,
    0x9007ffff,0x0c37401f,0xf9001ff0,0xd88bfa01,0x04fe983f,0x45f80fe4,
    0x80ff83fa,0x5c17f45f,0x0dd0fee4,0xf703fa00,0x4c03f205,0x807fe23f,
    0xc801fefc,0x43fe200f,0x207cc5fb,0xb82fe86f,0x21fcc01f,0xfd1df07d,
    0x200fc809,0x2ffdcdfc,0xf9003fb8,0x33bfe601,0x3ffa86ff,0xff01fc80,
    0x701df99d,0xbfd99dff,0xeccfff98,0x33bfa25f,0x02e602fe,0x3fb37ffa,
    0xdeffeb86,0x437bfaa1,0xff303ffa,0xeffeb80b,0x8f7fd41d,0x0550dffb,
    0xfffb9ff7,0x3bfb6a5d,0x77f4c3ee,0x6c4bff72,0x49dff16f,0xdeeffeda,
    0x7fffec40,0x3ffffee3,0xdffdd702,0xffb881bd,0xddfff04f,0x3fb66bdd,
    0x7ed44eef,0x3aa00dff,0x981dffff,0x884ffffd,0x7402dffd,0xffedc83f,
    0xfffd81cf,0x3ffee2ff,0xd817f20e,0x7ffec02f,0x7ffdc2ff,0x003fff92,
    0xffdfffb5,0x3ffffee9,0x9fffd45f,0xff30effd,0xc9bffa2d,0x1fffffff,
    0x33260260,0xff901ccc,0x403fffff,0x7ffffc01,0xffff57ff,0x004c0dff,
    0x08800660,0x02000880,0x00000620,0x00000000,0x98800000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x99555440,0x155542aa,0x2a215553,0x541aaaaa,0x435551aa,
    0x202aaaa9,0xaaaaaaa9,0x5555510a,0x2aa21555,0xaa880aaa,0x54c2aaaa,
    0x20aaaa0a,0x200aaaa8,0x0aa882a9,0x06aaaaa2,0x00337660,0x00000000,
    0x00000000,0x55555400,0x1ffff900,0x3e21fffd,0xfffd2fff,0x3ffffeeb,
    0x3bffe27f,0x3fa6fff8,0x40dfffff,0xffffffff,0xfffff92f,0x3ff25fff,
    0x2a0dffff,0x47ffffff,0xfff15fff,0xffffc85f,0x85fff104,0x3ff25ffd,
    0x502effff,0x7c43ffff,0x06a8000c,0x6449d500,0x7102dffe,0x7107bffd,
    0x32205dfd,0x3fe63dfe,0xf7104fff,0x707bf63b,0x7f5443bf,0x2aff6a60,
    0xe9867d40,0x2b3f220f,0x7f444fda,0x12fcaaab,0xf9555bf7,0x2eaff625,
    0x2b3ea5fd,0x7f445fda,0x107f932f,0x201fffb5,0x3fe26ffa,0x2b7ee20f,
    0x1fb06eba,0xcffe8833,0x003f2000,0x263ffd98,0x80ffeeff,0x47ffeefe,
    0x4ffeeffa,0x7ff7ff44,0x02b7ee64,0x5fd8bf98,0x47b29f30,0x201f906f,
    0x5c3ec3f9,0x7e43ec1f,0xf987ea50,0x643f5133,0xfa8fec0f,0xf901ff32,
    0xd017d4df,0x3e607f7f,0x0dff91ff,0x81fb87f3,0x7f5400fe,0x01f9003f,
    0x01bff910,0x7cc4f988,0xff89720c,0xfd87fa21,0xf98bf663,0xfecf9804,
    0x3e33e204,0x3f20bf5f,0x7d87f300,0x43f41fb8,0x852fb9fc,0x855e9cf9,
    0x8a7cc0fc,0x901fe88c,0x0bea9f9f,0x837c67cc,0xef8dfdf9,0x99cf986e,
    0x5fb80feb,0x05dff700,0x7dc00fc8,0x3f6a01ef,0xffe84fff,0x77fcc3de,
    0x3e4feeee,0x3e65f886,0xffff9804,0x7fd6fc02,0x1f904f9f,0x3ffffe60,
    0xbacfb87f,0xfffc85fe,0xffff302f,0x3e03f20b,0x3203fd85,0x2fa9fe8f,
    0x07f23f90,0x3f3f6fe6,0xfff986eb,0xff984fff,0x2202fcbf,0xfd11dffc,
    0x49ffffff,0x5c02effa,0x04feddff,0x4cbffd97,0xffffffff,0xbf109f15,
    0x7cc027cc,0x3a03febf,0x3fcfcfde,0x3e601f90,0xb87ecccd,0x904fffff,
    0x2605fb9f,0xf905fcdf,0x5fc8bf01,0x3e63f202,0xff882fae,0xf984fdcc,
    0x0dd7ffab,0xffd99bf3,0xefebfe87,0x3ff2201f,0xffddb10d,0x7f547ddd,
    0x31be203f,0xfd85a89f,0x3a003ba1,0xf31fe41f,0x9fcc3889,0xffb00ff8,
    0x205fff1d,0x87f300fc,0xaacfb87d,0x3a23f200,0x4f27f300,0xf303f22c,
    0x3f537d47,0xfdf90fc8,0xfffff705,0xd3f981ff,0x3e61ba9f,0x5be37c43,
    0xf9104ff9,0x0fc803df,0x8177fdc0,0xfffdccfe,0x3733bf64,0x66f7d46f,
    0x3fea4fec,0x260efecd,0xf307e44f,0xfc827d47,0x203ffd3f,0x87f300fc,
    0x001fb87d,0x7f3001f9,0x107e4bf0,0x83fe23fd,0x887e42fb,0x9fe82ffe,
    0x4c3fb999,0x1ba1953f,0x91fa0fe6,0x83dff9bf,0x9002effb,0xff91001f,
    0xfffe983b,0x3fae6ffd,0xfb81dfff,0x4c1dffff,0x4c0dfffe,0xea87e44f,
    0x077fa4ef,0x3fee1ff7,0x3bffb660,0x4fbfa64e,0x3fae5ffc,0x3ff204ee,
    0xdfd504ee,0x2abfdddd,0x4ffeeefe,0x3bbbbff2,0x4fbfea2f,0x3f622ffa,
    0x7ffb50df,0x4c37bf62,0x3faa3ffd,0x45ffeeee,0x3fffffd8,0x8007ffd1,
    0x362000fc,0x009883ff,0x26600330,0xd8818800,0xffeeeefe,0x21dfff70,
    0x37d43ffa,0xfffa8ff1,0x3fea6fff,0x0effe8cf,0x01dffffb,0x41bffffa,
    0xfffffffb,0xdffff75f,0xffffd85b,0x3fee2fff,0xf98bf64f,0xfff70eff,
    0x43bffa2b,0x3ee5fffb,0x0cefffff,0x33a20260,0x006a8000,0x00009b30,
    0x30000000,0xffffffff,0x0000001f,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x6dc00000,0x5dd50001,
    0x0001bb66,0x77774c00,0x1f7646ee,0x3b23bdb1,0x3bdd92ee,0x764bbb62,
    0x5500a03e,0x666665c4,0x64b2e3cc,0x6cc3d90c,0x8048820c,0xbbbbbbb8,
    0x3ba62bbb,0x0006eeee,0x00000000,0xced88000,0x80dfdbff,0xb9db13fe,
    0x7ff705df,0x7b81ffaa,0x3237b660,0x3ffe62ef,0x7fec7fff,0x2ffe898c,
    0x3f65fffb,0x7ffd12ff,0x7e413ffa,0x7dcbf501,0xffffffff,0xc9fa5f70,
    0x1dfff51f,0x9076c5f5,0x3ffff25f,0x1fffffff,0xddddddd3,0x00000000,
    0x76440000,0x3a21ddff,0xfefffeff,0xfd10a984,0x307ffdff,0x3207d87f,
    0xffff500f,0x97ccffdf,0xb6f81ffa,0xf987f35f,0x7ec1be24,0xf702ffbe,
    0x83f901ff,0x99999998,0x73ec7ea0,0x3ee3b61f,0xd3640eff,0x55554c7f,
    0x001aaaaa,0x00000000,0x7f440000,0x4c4fffef,0x1fa7f75f,0xdd077cc0,
    0x47d87f30,0x6dcfddfa,0x0625ffd0,0x6c07fea1,0x2fbdff9f,0x07f70fe8,
    0xa80f7fdc,0x5e86fbef,0x99999998,0x2e43e609,0x9b3044f5,0x00006001,
    0x00000000,0x64000000,0x30fee0cf,0x3f47ee9f,0x3ec3f980,0x31f61fcc,
    0x09fffffd,0x3ea003fa,0x3fbee00f,0xfa80feff,0x7e406f8c,0x0ff882ff,
    0x207c4bf7,0xfffffffb,0x254f10ff,0x000000d3,0x00000000,0x00000000,
    0x03203fa0,0x747ee9f3,0xd87f3007,0x3a24f987,0x01fff707,0x7fd403f4,
    0xfff10930,0x7f40dff7,0xbfb103fc,0x1fa87ff5,0x710733ec,0x57777777,
    0x00001800,0x00000000,0x00000000,0x400df000,0x3a3f74f9,0x3e62fc87,
    0x7fc43ec3,0x444fffcc,0x3a03fdff,0x777fd407,0x4ff80fee,0x7fd409ff,
    0x25ffd307,0x00045ffd,0x00000000,0x00000000,0x00000000,0xfd800000,
    0x3f621881,0xfe8dfb9e,0xfe99ff44,0x509ff52e,0x8dfddfff,0xd90dd2fa,
    0xb83bddff,0x1fffffff,0x05f91fd8,0xff503fe8,0x03bffa7f,0x00000000,
    0x00000000,0x00000000,0x00000000,0x3333bfe6,0x2bffa26f,0x85fe9efb,
    0x64fffea1,0x002606ff,0xffe80882,0x0002ffff,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x3fff6a00,0x000001de,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000130,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__courier_bold_20_usascii_x[95]={ 0,3,2,1,1,1,1,4,4,2,1,0,3,1,
3,1,1,1,0,1,1,1,1,1,1,1,3,3,-1,0,0,1,1,-1,0,0,0,0,0,0,0,1,0,0,
0,-1,-1,0,1,0,0,1,0,0,-1,-1,0,0,1,4,1,2,1,-1,3,0,-1,0,0,0,1,0,0,1,
1,0,1,-1,0,0,-1,0,0,1,1,0,0,-1,0,0,1,2,4,2,1, };
static signed short stb__courier_bold_20_usascii_y[95]={ 14,2,3,1,1,2,4,3,2,2,2,3,11,8,
11,1,2,2,2,2,2,2,2,2,2,2,6,6,3,6,3,3,2,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,1,2,2,17,2,5,2,5,2,5,2,5,2,2,
2,2,2,5,5,5,5,5,5,5,3,6,6,6,6,6,6,2,2,2,7, };
static unsigned short stb__courier_bold_20_usascii_w[95]={ 0,4,7,9,9,9,9,3,5,5,9,10,5,8,
4,9,9,9,9,9,8,9,9,8,9,9,4,5,11,11,11,9,8,12,11,10,10,10,11,11,11,9,11,11,
11,13,12,11,10,11,11,9,10,11,12,12,11,11,9,5,9,5,9,13,4,11,12,11,11,10,10,11,11,9,
8,11,9,13,11,10,12,11,11,9,10,11,11,12,11,11,9,6,3,6,9, };
static unsigned short stb__courier_bold_20_usascii_h[95]={ 0,13,6,15,16,13,11,6,15,15,9,11,6,2,
4,16,13,12,12,13,12,13,13,13,13,13,9,10,11,6,11,12,14,11,11,12,11,11,11,12,11,11,12,11,
11,11,11,12,11,14,11,12,11,12,11,11,11,11,11,15,15,15,7,3,4,10,13,10,13,10,12,13,12,12,
16,12,12,9,9,10,13,13,9,10,12,9,8,8,8,12,8,15,15,15,4, };
static unsigned short stb__courier_bold_20_usascii_s[95]={ 247,158,153,44,20,163,167,161,64,70,56,
189,135,199,180,10,113,113,103,173,247,148,183,238,228,206,27,250,200,141,177,
170,104,128,155,147,94,83,71,135,48,38,123,13,1,141,115,91,60,92,201,
180,190,158,213,25,238,226,105,76,82,54,125,185,175,212,193,1,1,234,13,
216,24,81,1,36,48,13,32,245,123,136,66,224,58,44,101,88,113,69,78,
37,60,30,165, };
static unsigned short stb__courier_bold_20_usascii_t[95]={ 14,1,43,1,1,1,31,43,1,1,43,
31,43,43,43,1,1,18,18,1,1,1,1,1,1,1,43,18,31,43,31,
18,1,31,31,18,31,31,31,18,31,31,18,31,32,31,31,18,31,1,18,
18,18,18,18,31,18,18,31,1,1,1,43,43,43,31,1,44,18,31,18,
1,18,18,1,18,18,43,43,31,1,1,43,31,18,43,43,43,43,18,43,
1,1,1,43, };
static unsigned short stb__courier_bold_20_usascii_a[95]={ 170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT or STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_courier_bold_20_usascii(stb_fontchar font[STB_FONT_courier_bold_20_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT][STB_FONT_courier_bold_20_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__courier_bold_20_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_courier_bold_20_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_courier_bold_20_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_courier_bold_20_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_courier_bold_20_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__courier_bold_20_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__courier_bold_20_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__courier_bold_20_usascii_s[i] + stb__courier_bold_20_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__courier_bold_20_usascii_t[i] + stb__courier_bold_20_usascii_h[i]) * recip_height;
            font[i].x0 = stb__courier_bold_20_usascii_x[i];
            font[i].y0 = stb__courier_bold_20_usascii_y[i];
            font[i].x1 = stb__courier_bold_20_usascii_x[i] + stb__courier_bold_20_usascii_w[i];
            font[i].y1 = stb__courier_bold_20_usascii_y[i] + stb__courier_bold_20_usascii_h[i];
            font[i].advance_int = (stb__courier_bold_20_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__courier_bold_20_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__courier_bold_20_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__courier_bold_20_usascii_s[i] + stb__courier_bold_20_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__courier_bold_20_usascii_t[i] + stb__courier_bold_20_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__courier_bold_20_usascii_x[i] - 0.5f;
            font[i].y0f = stb__courier_bold_20_usascii_y[i] - 0.5f;
            font[i].x1f = stb__courier_bold_20_usascii_x[i] + stb__courier_bold_20_usascii_w[i] + 0.5f;
            font[i].y1f = stb__courier_bold_20_usascii_y[i] + stb__courier_bold_20_usascii_h[i] + 0.5f;
            font[i].advance = stb__courier_bold_20_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_courier_bold_20_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_courier_bold_20_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_courier_bold_20_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_courier_bold_20_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_courier_bold_20_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_courier_bold_20_usascii_LINE_SPACING
#endif

