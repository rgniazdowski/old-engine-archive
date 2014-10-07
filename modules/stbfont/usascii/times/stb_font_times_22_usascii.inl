// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_times_22_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_times_22_usascii'.
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

#define STB_FONT_times_22_usascii_BITMAP_WIDTH         256
#define STB_FONT_times_22_usascii_BITMAP_HEIGHT         66
#define STB_FONT_times_22_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_times_22_usascii_FIRST_CHAR            32
#define STB_FONT_times_22_usascii_NUM_CHARS             95

#define STB_FONT_times_22_usascii_LINE_SPACING          14

static unsigned int stb__times_22_usascii_pixels[]={
    0xa80a2013,0x0a802a01,0x75100590,0x55440377,0x06aa202a,0x082aaa88,
    0x806aa200,0x00104028,0x220a0c00,0x30009802,0x40198005,0x929801a8,
    0x10099980,0x00003333,0x202b8066,0x3a82b81c,0x0bf00e40,0x32605e5c,
    0x87daa881,0x2edaade8,0xc82abfa8,0x2b36200a,0x1fc82fca,0x1ef6eec4,
    0x3bf23f26,0x4488e602,0xb101d9e9,0x3d59d100,0x2da9cb80,0x07754dcc,
    0x9806e190,0xbf5106fd,0x9bb57303,0xeabe8839,0x16603b00,0xd803a0ae,
    0x07700401,0x23dc0370,0x44fa82fa,0xbdcb80fa,0x417d40ee,0x117ec4f9,
    0x261fd43f,0x2ffabcfd,0x3e1d4570,0x00320d93,0x2205a9b6,0x43b07c47,
    0x499604f9,0x3604fe80,0x57f45f01,0x20d726c1,0xb81f3068,0x0b703cc2,
    0x70025c00,0x5f89ee01,0x0fa8bee0,0x43b0bb54,0x8bee05f8,0xf11761fc,
    0x7cc3f707,0x10e41905,0x7503ea5f,0x05a97e00,0x3f8be1ae,0x2c3a83f4,
    0xc81ffe40,0x3f20fb81,0x5f10fdc0,0x07ea0f60,0xf01fa857,0x0b702005,
    0x03884462,0x3017e4f7,0x3607d4df,0xfd86a175,0xfb9be202,0x3f887f10,
    0x83fc0fb8,0x4c7e62c6,0xf801620f,0x7d403d17,0x43b83e22,0x1b81906e,
    0x40ffd640,0x2e1fc81c,0x37c36c0f,0x07dc0fb8,0x705f30ae,0x68bd500f,
    0x45f73790,0x07fcf704,0x07d47fe0,0x2082e3f6,0x8ff400ff,0xf10be67a,
    0xfc81f707,0xdddfdd71,0x6b97c7df,0x7fb0006c,0x42aaaa3b,0x01d8afe8,
    0x885817c4,0x7fcc6404,0x1fcc0e40,0xfd0bf0bb,0x0f307ea0,0xe80f8857,
    0x32fcc407,0x07e45b0b,0x3fc5ee09,0x0fa97f40,0x4406ffd4,0x52fd807f,
    0x3e227c4f,0x3e40fb83,0x970911cc,0x4002a8f6,0x06fc47fa,0x2003bfa2,
    0x1607505c,0x91bee190,0x2ef3ea03,0x7ec2fc40,0x0e83f980,0x7c16615c,
    0x1dcbf006,0x048db172,0x201fe6f7,0x701f53fc,0x0ff307ff,0xd1a67f90,
    0xfb83f88f,0x50dc3740,0x5886ea05,0xedc80554,0x5c03e23f,0x074404ff,
    0x403700c8,0x1c97f20c,0x7cc01190,0xf880fd84,0x8ae1b884,0x00bf1029,
    0x3ea1d97a,0x5c121fc0,0xfb00ff17,0x74c03ea7,0x01fe20df,0x2e2c4bf6,
    0x83fc9aef,0x207e22fb,0xd800720d,0xb03a6b60,0x1d43fe69,0x05fd8ca8,
    0x2205802e,0x7fd03204,0x2afea072,0xd85f809a,0x260bf107,0x80644ae4,
    0x4bd005f8,0x87ea2e46,0x7f4f7038,0xfa8ff400,0x83bf6e00,0x0ff400ff,
    0x8dffb889,0xbbdfb83f,0x777f5c1c,0x5c03eefe,0x91fc3ea2,0x2c6fec1f,
    0x80fec798,0x0b00ea03,0x2bfa2064,0xffff981c,0x6c3745ff,0x5709f106,
    0xf815c2b8,0x234bd006,0x0323f43e,0x405f93dc,0x803ea6f8,0x3f23fc8b,
    0x031be202,0x5c1fc422,0x1620088f,0xf912200b,0xf88df2ec,0xf0b900ef,
    0x00c80a09,0x980c80dc,0x13981eff,0x3e43b533,0x43f982fc,0x3c42b878,
    0x4bd006d8,0x6dc7f11c,0x27b80aa5,0x87ee06e8,0x217040fa,0xb81be26e,
    0x3f88001f,0x39800fb8,0x206c0122,0x7fc5766c,0x4617fd40,0x8003c86c,
    0x1b048805,0xd107fea0,0x0fa82e01,0x0fd40be2,0x985703ee,0xd007c82f,
    0x99fd1d4b,0x828ee376,0x4c27cc7b,0x9607d42f,0x4f989b0b,0x06d42fa8,
    0x3f20fe20,0x0aa1b800,0x43ea0ae0,0x4c37f62f,0x2b9cffcd,0xa80e83f1,
    0xb002a80d,0x1fc80b60,0x9510e7cc,0x902647b0,0x2b83f50d,0x0fcc0fd4,
    0x44b12f40,0xb82f262c,0xdc887b81,0xfa81dcbb,0xf88b8fc0,0xdbbdd880,
    0x201fc80d,0x3661dfb8,0x906c00bf,0x36049803,0x3f660eaa,0xfff30dff,
    0x1bacea89,0x01b03f90,0xefc986e0,0x36e07603,0xb103ffff,0x82f80997,
    0x2a15c1f9,0xd007900f,0x44002c89,0x74c0f704,0x81f500ff,0x01cbddfc,
    0x40080198,0x26619998,0x02040099,0x055002e0,0x401100c4,0x01008008,
    0x00000080,0x40040026,0x570f105a,0x00740788,0x400b20fe,0x101ee048,
    0x03ea0dfb,0x0000064c,0x00000000,0x00000000,0x00000000,0x00000000,
    0x81620000,0x1d82b83a,0x7c511260,0x4a805900,0xea803dc0,0x5007d40d,
    0x2eeeee20,0x0003bbbb,0x00000000,0x00000000,0x00000000,0x00000000,
    0x05501cc0,0x101540ae,0x00d77d47,0x32eaf2e6,0xfddd301c,0x50bb9800,
    0x9800bddf,0x99999999,0x00000001,0x00000000,0x00000000,0x00000000,
    0x00000000,0x80000220,0x09880008,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x42aa2000,
    0x05910008,0x05a802a2,0x00999980,0x4ccc14c4,0x99981999,0x09a88099,
    0x800854c0,0x998860a9,0x4ccc4099,0x02666621,0x99886666,0x13333119,
    0x9804ccc4,0x266622dc,0x26662099,0x02666620,0xc9833331,0x33333001,
    0x4c133333,0x2f72000d,0x801deeb9,0xffc83fd9,0x007eb84f,0x017fffd4,
    0xfff303b9,0xf930ffff,0xcaea817f,0xdbbda81e,0xbdd880ee,0x3266deba,
    0x7d440cff,0x33ff662e,0x263fea80,0xff712ffd,0x06fd4419,0x712fb9d4,
    0x6c419fff,0x3ff661cf,0x0f7e441d,0xf3003fd5,0xd99ff99d,0x007faa7f,
    0x02f982ec,0x12a87f10,0x00f905fb,0x302aaad8,0x55ee405d,0xdf304daa,
    0x20fc8f30,0x207d40f8,0x41f705e8,0x816c07f8,0x20f201ff,0x02fd87f8,
    0x1b83e20d,0x1ec17fcc,0x1aa07fd0,0x1d400fd4,0x7dc931fa,0x5c07d801,
    0x187f1002,0x03e41fcc,0x7f100550,0x01e81c40,0x88b90bf1,0x06c1ae4f,
    0x07401dd1,0x203901be,0xd81a03fb,0x4c27d41f,0x5001f304,0x4c04a8df,
    0x500d80ff,0xe815003f,0x007ea387,0x003009f7,0x3f100fe2,0x67400f70,
    0x80036c02,0x217e2078,0x3f26f84f,0x0fee0b82,0x406f8350,0x20df101c,
    0x213ea04a,0xf701c86f,0x4d3f2001,0xa89f7005,0x0007ea03,0x87ea03f4,
    0x0002fd80,0x0ff33362,0x23ee0750,0xffa82efd,0x13fa81ef,0x2204b800,
    0x6c37c45f,0xb00ffea7,0x0df0003f,0x0bf201c8,0x98ff0036,0x644341ff,
    0xe801ccfe,0x3a000eaf,0xfa80d11f,0xd002f721,0xfa9fa80f,0x9807fc4f,
    0x0fc41999,0x0fd407f9,0xffbacfb8,0x1ffca882,0x1ff5dfe4,0x3e201e80,
    0x3f40fd85,0x7c0bbfee,0x06f8000f,0x8bf300e4,0x21fc8058,0x81264fcc,
    0x3e6000fb,0xb7cc002f,0x88fd401d,0x80fd001d,0x1fc8acfa,0x7ecc0ff3,
    0x3e23dc2e,0x07ffb703,0x02fc41f7,0x41dd13ea,0x03c402fc,0x8fee17e2,
    0xffe985f8,0x001fe60d,0x0072037c,0x4015c3fb,0x93fda4f9,0x0007dc03,
    0x320013f6,0x9fa804df,0x1fa000d8,0x97cc3f50,0x3ea01ff8,0x1fc44e84,
    0x1ee1fe60,0x83ee01fa,0x5c05f85f,0xb82fc404,0x202fcbee,0xff10fffb,
    0x80df0001,0xd27d401c,0x949bf400,0x1f701a5f,0x0ff6cc00,0x4007f400,
    0x4000ebfa,0x10fd407e,0x3017fc7f,0x443f889f,0x41fb803f,0x400fb87b,
    0x3a17e2f8,0x1007a00f,0x1f9080bf,0xf2fec404,0x0ff0003f,0x8fe800d8,
    0x2bf2003a,0x0739f31c,0xb1000fb8,0xd0003be6,0x3f3ea00f,0x203f4004,
    0xc8fe21fa,0x113e604f,0x803f88df,0x7c87b879,0x43741f00,0x201e206c,
    0x4f8804f8,0x326f8824,0x3f40803f,0x5fdc01a0,0x37e6000d,0x200eff46,
    0x41b000fb,0x3f4004fc,0x2fc9fa80,0xf501fa00,0xff11fc43,0x3613e605,
    0x200fe20f,0x5e87b84a,0x07dc5a80,0x204b80fa,0x9b007f10,0x893a0390,
    0x902a01ff,0x401a203f,0xe8005ff8,0x4037dc3f,0x82c800fb,0x1fa002fe,
    0x1fe8fd40,0xfa80fd00,0xfd10fe21,0xf709f303,0x3513ee1b,0x07dc0f44,
    0x30bc81f3,0x7c49d01b,0x7dc07600,0x2ec00f99,0x07cc0ec8,0x06e07be6,
    0x3d103ba2,0x0017e400,0x0fe207dc,0xb9007f20,0x4003fea0,0x1fa800ff,
    0xff001df1,0xf10fdc01,0x2afbb207,0xfd500cec,0x7f45bf5d,0xfb100dde,
    0xff901779,0x3322019d,0x81e201db,0x5302cef9,0x6f664057,0xfb101ddb,
    0x4403999d,0x01decded,0x880034c0,0x5c401d06,0xfea82dff,0x7ffecc2e,
    0x37ff2604,0x277faa02,0xb302efe8,0xfd305bff,0x05df933b,0x86000998,
    0x18001100,0x22000880,0x03001000,0x4c410018,0x00022000,0x03000062,
    0x00180400,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x26666200,
    0x33331000,0x71059001,0x00199887,0x4cc43331,0x26200999,0x26661999,
    0x33333009,0x26213333,0x26621999,0x26662199,0x220cc019,0x99999999,
    0x26666621,0x26209999,0xa8009999,0x8975c3ee,0x80099999,0x00011000,
    0x26030015,0xfb88a800,0x00cfecdf,0xdfbbff71,0xf9117e05,0x02ffb889,
    0x2e22efd8,0x2200adff,0x3e61cffa,0xcefa80cf,0x10efdccc,0x5443bff5,
    0x3ee21cff,0x0fe601cf,0x9999ff71,0x3fea21fd,0x24fccccc,0xecceffb8,
    0x83f901df,0x33fee249,0xf882efdc,0x2005b804,0xa80dfffc,0xf883b06e,
    0x07f49f14,0x47e80df7,0x27c004fd,0x7cc06fe8,0x003fd03f,0x07e607f4,
    0x03fd02a8,0x03fa05fb,0x3fa007f4,0x0360fd03,0xd09101fd,0x81fe981f,
    0x740e44f8,0x222fd40f,0x00fe803e,0x4fd99ca8,0x7dc37ccc,0x4f89f441,
    0x05fd03f6,0x01fe23ec,0x3f7a09f0,0x40bf7601,0x3f6000fd,0x07007a20,
    0x0fe413f2,0x0fd00fd8,0xfb03fac8,0x01fb0260,0x7403f60a,0xb10fc82f,
    0x3fa03f60,0x3fe98001,0x80fe8380,0x66ff5c6e,0x0fd8fe00,0x0fb01fec,
    0x3e0103ff,0x20bf3d04,0xfb02fbd8,0xd13ec001,0xdf301003,0xfd80fe40,
    0x6540fd00,0x00fb03f8,0xd80407ec,0x10df300f,0x7ec0ae9f,0x8003fc80,
    0x70006f9d,0xf50db03f,0x7ec3b003,0xd803fe20,0xd7137c47,0xdb413e09,
    0x2fbac81f,0x6c001fb0,0x20003d37,0x3f201ff8,0x3a01fb01,0x0fe2b107,
    0xfd81c3ec,0x0fd81c40,0x3f203fa0,0x203f6068,0xac4000fe,0x7b8002fc,
    0x03f50db0,0x987ec190,0x23ec03fd,0x13e623fc,0x9f56827c,0x205f7688,
    0x3f6000fd,0x360001f9,0x80fe403f,0x20fd00fd,0x3607f10d,0xb03c999f,
    0x07b5335f,0x2fd803f6,0x3604df88,0x2fda999f,0xbf32c800,0x3607b000,
    0x0801fa86,0x06ff67ec,0x6f667ec0,0x13e09f02,0x9dc1fd34,0x01fb02fb,
    0x02ff7ec0,0xc805fa80,0x999fb01f,0x750ff999,0xcfd81fc4,0x7fb03ecc,
    0x3607d955,0x40ff200f,0x33f601fc,0x000cfedc,0x0007ec68,0x5436c0b1,
    0x8fd8001f,0x7d800ff8,0x27c13e00,0x2693ea68,0x01fb02fb,0x2fec7ec0,
    0x003fe200,0x07ec07f2,0x222c47e8,0x070fb03f,0x207103f6,0x0bf600fd,
    0x03f602cc,0x1f4c3ff3,0xfb999ca8,0xd8036004,0x3d81fa86,0xa87ec3b3,
    0x007d805f,0x6827c13e,0xf71d47f4,0x8003f605,0x8017f67d,0x3f9002fd,
    0x3f403f60,0x3fbbbbb2,0x043ec1ee,0xb0080fd8,0x80ffc01f,0x407ec02b,
    0x03fee5fa,0x3f33333a,0xd8059007,0x7c41fa86,0x07ec5f55,0x07d807f9,
    0x827c13e0,0x7075fdc6,0x803f605f,0x17f63ec1,0x41817ee0,0x01fb01fc,
    0x999951fa,0x7d819bf9,0x0803f600,0x5fa807ec,0x03f601a0,0x81931fe2,
    0x805f7049,0x986d803a,0x810218bf,0x00ff40fd,0x13e001fb,0x7c46827c,
    0xd817dc4f,0xfd85300f,0xf302fec0,0xf90a601d,0x7403f603,0xd03f8807,
    0x03f6001f,0x203f614c,0x2f221fe8,0x80fd801d,0x0d8486fb,0x1d40df10,
    0xfe836c0c,0x20ff4004,0x3fd00ff9,0x2fc17e00,0x207e40f8,0x03fd03fc,
    0x80fe81d3,0x1fe80efe,0x2fd83d10,0x3fe01fd0,0xf81fc400,0x03fb000f,
    0x40fe81d1,0x7fcc1ee9,0xa81fd003,0x502e61ff,0xa83fe80d,0x85cbaaae,
    0x9300006e,0xffb85bff,0x5bff930c,0x11ffdc40,0x7e4c7ff7,0xfb89622d,
    0xff930bef,0x4bffdddf,0x2a2dffc9,0xf91cffff,0xfddddddf,0x177fe4cf,
    0x4c5bff93,0x2202dffc,0x6ffe4c3f,0x3bfee602,0x265feeee,0xcddeeffc,
    0x26002203,0xeedeeffc,0x7f54040c,0x4fffb80b,0x3fffffea,0x2ffee22f,
    0x00000001,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x80099998,0x01000000,0x12000800,0x00820000,
    0x77540002,0x2617db52,0x4c3b6a5d,0x33b6a2ec,0x001076e0,0xd9804040,
    0x41dc88de,0x1edccccd,0x101802a8,0x51eb84c5,0x77777777,0x7102e677,
    0x7fc46015,0x2ea805ff,0x87b50000,0xa80cdcb8,0x2c00becd,0x0f7664c0,
    0x2176de44,0x4c3ecbc8,0x323fc9fc,0x1b07ee0f,0x0be60fb8,0x263985f7,
    0x44ffb9fc,0x5ffa9fc9,0xf101dfd1,0x262c0f4f,0x880bb05f,0xbf0fc82f,
    0x4ccc57f6,0x10999999,0xdecbd89d,0x4ccc510a,0x33ae0019,0x5f5c4000,
    0x89f134c0,0xb00fe659,0x3f20e880,0xc8590e41,0xfc883f25,0x8fe62c9c,
    0x2e1224f8,0x3e0be20f,0xbf910645,0x6443fb19,0xbcfc8acf,0x9f505f98,
    0xee886057,0x2aee7ee0,0xc86ac82f,0xb115f88f,0x13344000,0x004dfc98,
    0x01dda800,0x9d016e4c,0x4cdf43c8,0x202c06e9,0x3e27c45d,0x547b0623,
    0xd017d41f,0x0173fd4d,0x417c41f7,0xf70910fc,0x3ea17cc3,0x0fb17e21,
    0xfd8027e4,0x76676441,0x44aa4c0b,0x3298fa7b,0x55555555,0x1000a855,
    0xc9800000,0x00e6d42d,0x7f100be2,0x58055555,0x236c1fc0,0xda801dfc,
    0x700fd41f,0x2cbeb61f,0x0be20fb8,0x540dd3e2,0xf50fe21f,0x03e44f83,
    0x7f700df1,0x02b7ae20,0x9660d836,0x554c552d,0x2aaaaaaa,0x00000000,
    0x7f74f980,0x300fe600,0xeeeb805f,0x34eeeefe,0xc81f909f,0x539704ff,
    0x201fa83f,0x3bd39bf8,0xf883ee05,0x5416fb02,0xf50fe21f,0x03e44f83,
    0x7cc09f59,0xb55bf505,0x9621d43f,0x00042e48,0x00000000,0x20e6d400,
    0x7c403ec8,0x217e2085,0xf8816008,0xfd307c86,0x07ea5c89,0x5ec803f5,
    0x1fa817ee,0x67cc0fe6,0x7c43f503,0x13e0fd43,0x7e4ae0f9,0x8c0ee881,
    0x442e9938,0x01045905,0x00000000,0x2fae0000,0x00cea800,0x7fc383ff,
    0xb01601c1,0x2245e81f,0xfa8be27d,0x2600fd41,0x9813e24f,0x409f934f,
    0x43f500fe,0x20fd43f8,0x24c3e44f,0x83fb03fa,0x1984d819,0x000000e0,
    0x00000000,0x4000b722,0x7fdc1dd9,0x7fdc1dac,0x02c02dad,0x40f88fea,
    0xdf892e0f,0x2a2afda8,0x6c0e801f,0x467fec01,0x409702df,0x50fe21fb,
    0x7e45f83f,0x74c37ea0,0x99df52ef,0x01103fb9,0x00000000,0x00000000,
    0x200003b7,0x77f545c8,0x07dfb502,0x7bf500b0,0x977ff03b,0xf8bffb81,
    0x05dfd50e,0x11000808,0xea804004,0x2efc99df,0xf913bfb3,0x033fee5f,
    0x00000000,0x00000000,0x00000000,0x01000000,0x00380020,0x01308022,
    0x00000204,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
};

static signed short stb__times_22_usascii_x[95]={ 0,2,1,0,1,0,0,0,0,0,1,0,1,0,
1,0,0,2,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,-1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,-1,1,0,-1,0,0,0,0,0,0,0,
-2,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,2,1,1,0, };
static signed short stb__times_22_usascii_y[95]={ 17,3,3,3,2,3,3,3,3,3,3,5,15,11,
15,3,3,3,3,3,3,3,3,3,3,3,7,7,5,8,5,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,20,3,7,3,7,3,7,3,7,3,3,
3,3,3,7,7,7,7,7,7,7,5,8,8,8,8,8,8,3,3,3,10, };
static unsigned short stb__times_22_usascii_w[95]={ 0,3,6,10,8,16,15,3,7,6,8,11,3,6,
3,6,10,6,10,9,10,9,10,10,8,10,3,4,11,11,11,9,18,15,13,13,14,12,11,15,14,7,8,15,
12,18,16,14,11,14,14,9,12,15,15,19,15,15,12,5,6,5,9,12,4,9,11,9,10,9,9,10,10,6,
6,11,6,16,10,10,11,10,7,8,6,10,10,15,10,10,9,7,2,7,11, };
static unsigned short stb__times_22_usascii_h[95]={ 0,15,7,15,17,15,15,7,19,19,9,11,6,3,
3,15,15,14,14,15,14,15,15,15,15,15,11,14,11,5,11,15,19,14,14,15,14,14,14,15,14,14,15,14,
14,14,15,15,14,18,14,15,14,15,15,15,14,14,14,18,15,18,8,2,4,11,15,11,15,11,14,15,14,14,
19,14,14,10,10,11,15,15,10,11,13,10,10,10,9,14,9,19,19,19,4, };
static unsigned short stb__times_22_usascii_s[95]={ 255,112,201,139,88,150,167,252,27,1,182,
45,208,241,252,202,244,234,223,28,126,50,60,71,183,91,248,202,13,212,1,
192,42,207,188,112,162,149,137,1,111,103,82,74,61,42,216,97,16,67,1,
102,232,126,142,158,188,204,90,82,209,61,191,97,224,77,38,25,17,35,178,
233,245,28,35,220,35,144,133,57,127,116,87,68,241,111,122,95,161,177,172,
19,16,8,229, };
static unsigned short stb__times_22_usascii_t[95]={ 1,1,52,1,1,1,1,37,1,1,52,
52,52,51,45,1,1,37,37,21,37,21,21,21,1,21,37,37,52,52,52,
1,1,37,37,21,37,37,37,21,37,37,21,37,37,37,1,1,37,1,37,
21,21,21,21,21,21,21,37,1,1,1,52,17,52,52,21,52,21,52,21,
1,21,37,1,21,37,52,52,52,1,1,52,52,37,52,52,52,52,37,52,
1,1,1,52, };
static unsigned short stb__times_22_usascii_a[95]={ 79,106,130,159,159,265,247,57,
106,106,159,179,79,106,79,88,159,159,159,159,159,159,159,159,
159,159,88,88,179,179,179,141,293,230,212,212,230,194,177,230,
230,106,124,230,194,283,230,230,177,230,212,177,194,230,230,300,
230,230,194,106,88,106,149,159,106,141,159,141,159,141,106,159,
159,88,88,159,88,247,159,159,159,159,106,124,88,159,159,230,
159,159,141,153,64,153,172, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_times_22_usascii_BITMAP_HEIGHT or STB_FONT_times_22_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_times_22_usascii(stb_fontchar font[STB_FONT_times_22_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_times_22_usascii_BITMAP_HEIGHT][STB_FONT_times_22_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__times_22_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_times_22_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_times_22_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_times_22_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_times_22_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_times_22_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__times_22_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__times_22_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__times_22_usascii_s[i] + stb__times_22_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__times_22_usascii_t[i] + stb__times_22_usascii_h[i]) * recip_height;
            font[i].x0 = stb__times_22_usascii_x[i];
            font[i].y0 = stb__times_22_usascii_y[i];
            font[i].x1 = stb__times_22_usascii_x[i] + stb__times_22_usascii_w[i];
            font[i].y1 = stb__times_22_usascii_y[i] + stb__times_22_usascii_h[i];
            font[i].advance_int = (stb__times_22_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__times_22_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__times_22_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__times_22_usascii_s[i] + stb__times_22_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__times_22_usascii_t[i] + stb__times_22_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__times_22_usascii_x[i] - 0.5f;
            font[i].y0f = stb__times_22_usascii_y[i] - 0.5f;
            font[i].x1f = stb__times_22_usascii_x[i] + stb__times_22_usascii_w[i] + 0.5f;
            font[i].y1f = stb__times_22_usascii_y[i] + stb__times_22_usascii_h[i] + 0.5f;
            font[i].advance = stb__times_22_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_times_22_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_times_22_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_times_22_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_times_22_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_times_22_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_times_22_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_times_22_usascii_LINE_SPACING
#endif

