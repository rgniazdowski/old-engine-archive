// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_bold_16_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_bold_16_usascii'.
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

    typedef struct {
    // coordinates if using integer positioning
    float s0, t0, s1, t1;
    signed short x0, y0, x1, y1;
    int advance_int;
    // coordinates if using floating positioning
    float s0f, t0f, s1f, t1f;
    float x0f, y0f, x1f, y1f;
    float advance;
} stb_fontchar;
#endif

#define STB_FONT_arial_bold_16_usascii_BITMAP_WIDTH         128
#define STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT         84
#define STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_arial_bold_16_usascii_FIRST_CHAR            32
#define STB_FONT_arial_bold_16_usascii_NUM_CHARS             95

#define STB_FONT_arial_bold_16_usascii_LINE_SPACING          10

static unsigned int stb__arial_bold_16_usascii_pixels[] = {
                                                           0x50153051, 0x15015305, 0x0d440198, 0x40013310, 0xa9880999, 0x220aa809,
                                                           0x4d4c001a, 0x06666600, 0x982a22a2, 0x207fe41f, 0x20ffe45d, 0xd987f87b,
                                                           0x40dffeff, 0x84d85ffd, 0x7fd43fff, 0x1fdc3fff, 0x406c45f9, 0x83fffffa,
                                                           0xb87ffff9, 0x45e83f57, 0x22ec3fc8, 0x427c42ff, 0x0567cc4c, 0x7cc41db3,
                                                           0x87bffea5, 0x3fea09ef, 0x223ffdbe, 0x1fd1fa6f, 0xfdbeffa8, 0x7777d43f,
                                                           0x70f96d86, 0x6c3f983f, 0x0fdc2fc5, 0x267f3154, 0x46d9a89b, 0x377ba5f8,
                                                           0x3fa1be5f, 0xfd07fd43, 0x7fd49f31, 0xf30ffa0b, 0xb80fe41f, 0x43fecefc,
                                                           0x227cc4f8, 0x3617e25d, 0xba6cff07, 0xfabfeeef, 0x67c57e20, 0x11be08bc,
                                                           0x45ff01ff, 0x361fcbfa, 0x1ff13fff, 0x6fec5ff0, 0x777f6c2d, 0x445f84ef,
                                                           0x9f32ec5f, 0xf9fe0df0, 0x47fe5f89, 0xfe97e22e, 0x7d46f83e, 0x7c47fb06,
                                                           0x4ff446ee, 0x3f60df30, 0x17fbffe3, 0x205f33f5, 0x365fd86f, 0xf883fd55,
                                                           0x5de6ff05, 0x1743f60f, 0x7ffd4bf1, 0xff31be0c, 0xff90ff20, 0x7cc1fd09,
                                                           0x1547fb07, 0xfabdc1fd, 0xff30fd00, 0x42fe5761, 0x2eff04f9, 0xf16e8fb5,
                                                           0x7ec45f88, 0xff11be6f, 0x20ff4263, 0x0fe81ff9, 0xff107fe2, 0xfe9fe405,
                                                           0xf85fffff, 0x5761fe86, 0x05f83fd8, 0x33edaaff, 0xbf11769f, 0x3e1fb790,
                                                           0xbfb4fe86, 0x06f981ff, 0x0dfe81fd, 0x26c43fee, 0x2b7ea3fb, 0x45f82aee,
                                                           0xf12ec4f8, 0x5fe0dd09, 0xeacfa8f8, 0x7c40eddf, 0xf7799f35, 0x3fe61be1,
                                                           0x263fffcf, 0x9fd02ffc, 0x7efffcc3, 0x667ec2ff, 0x27cfe26f, 0x27cc3f98,
                                                           0xd85f8976, 0xba74ff07, 0x88ceeade, 0xefe97e20, 0x441be5fd, 0x4ffefffd,
                                                           0x7dc09ff3, 0x7ffec43f, 0xeffd881e, 0x0be27ea0, 0x21fcc3dc, 0x7cc37c5d,
                                                           0xbf337c41, 0x3e22fb80, 0x833ff665, 0x3620806f, 0x40088003, 0x86202000,
                                                           0xfd70fa01, 0x6ff45d85, 0xbfd526c0, 0xaabcee88, 0x3f2e2fec, 0xcff83c85,
                                                           0x00000001, 0x40000000, 0x427e40f9, 0x20ff4c5d, 0x03df70fa, 0x59dfb951,
                                                           0x984eec81, 0x002eed80, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                                           0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x30130000,
                                                           0x40035003, 0x14c00401, 0x02a60044, 0x40550b88, 0x20008809, 0x13009809,
                                                           0x3fb61980, 0xfa80be23, 0x7f5c06ff, 0x1f7ed41e, 0x7ff4cbb0, 0x7fff4c0d,
                                                           0x67ffd42e, 0x44bf306f, 0x4400cffc, 0x33ffe66f, 0x5fe037c0, 0x1b26b9f8,
                                                           0x05f51fd0, 0xd1bef7f2, 0x3e09fd7f, 0x13eeffa3, 0x1ff759fd, 0x37ec4ff4,
                                                           0x33f65f98, 0x37c404fc, 0xf87fb7ff, 0x9f9a6406, 0x402f88fb, 0x882fb9fe,
                                                           0x4f98a67f, 0x23f10ff1, 0xff1be5f8, 0x4bf11ec8, 0x2bf306f9, 0x221fe6f8,
                                                           0x5716f89b, 0x2adf17e2, 0x36fe2a82, 0xff500d95, 0x27be60bf, 0xff1fd41b,
                                                           0x57ec7a81, 0x67fe44fb, 0x3e65fa81, 0x3e6bf306, 0xffb83fa5, 0xfd986fef,
                                                           0x7fff7fc3, 0x9dea9fe1, 0xffc802f8, 0x3fffea07, 0x2a37e24f, 0x223641ff,
                                                           0xfd886fff, 0x9fe23fff, 0x2bf306fb, 0xe87fa5fa, 0xe86fd89f, 0xf73ff85f,
                                                           0x2d903fc9, 0x6fec1deb, 0x2a0dbcfe, 0xfc8fd0ff, 0x2741ffff, 0x417eeffa,
                                                           0x362ffec9, 0x306ffdef, 0xfe97eabf, 0x37d4bf11, 0x3fe2fdcc, 0x107f9fe0,
                                                           0x4bb5f15f, 0xffff16f8, 0x0bee6f98, 0x441fd151, 0xfd93e62f, 0x5fb85510,
                                                           0x57e2ff62, 0x26bf30a8, 0x7d43fa5f, 0xfd81be64, 0x21fd1fe1, 0x3ead907f,
                                                           0x997e67b8, 0x87fc45ff, 0x225710fc, 0xf307d46f, 0xff887f4b, 0x22a97ee0,
                                                           0x2e5f75f9, 0x3fcdf14f, 0xd36fb9be, 0x3ff07f49, 0x887f97e2, 0x8d93f32f,
                                                           0xfffebdfe, 0x37e77e44, 0x90ffaffa, 0xbf99fb0d, 0xffdcffc8, 0x3fb37f62,
                                                           0x5ffbff32, 0x21fee7ec, 0x26ffbefd, 0x7c4fdcfe, 0x3e3febff, 0x7f746c87,
                                                           0x67fff4c3, 0xcfea83ea, 0x40eff540, 0xcffd984e, 0x77ff5c40, 0x1f7f6442,
                                                           0x710fbfae, 0xff9107df, 0x7feccdf5, 0x7fdefc0c, 0x40d43fc3, 0x00204009,
                                                           0x02600801, 0x00002000, 0x00400004, 0x00000000, 0x00000000, 0x00000000,
                                                           0x00000000, 0x03500000, 0x98801a88, 0x1881980a, 0x00661a88, 0x26057155,
                                                           0x4c199999, 0x31098809, 0x20c43301, 0x304c4198, 0x8cc26203, 0xffff104d,
                                                           0x3ffea09f, 0xd03fe1df, 0xf3ffd43f, 0xffeef80f, 0x3fffe61f, 0x1bee1fff,
                                                           0x3fe61ff3, 0x2fd97f21, 0x2fd87ff2, 0x47fa0ff6, 0xff30d97f, 0x987ff77d,
                                                           0x27fdbdff, 0x90ff40ff, 0x203fc17f, 0x24fb8cff, 0xffdaaaa8, 0x7fd1ff40,
                                                           0x1ff36fb8, 0x7ffd1fdc, 0x8df507fc, 0x7d5fe6f9, 0x3a627ec0, 0x3ba1ff44,
                                                           0x1fe81ff1, 0xbfc37fd5, 0xf07fc1b9, 0x417fcc0f, 0x06fa8ff9, 0x987fd7fd,
                                                           0x2bfdf15f, 0x20ff86f8, 0x7c5fe4fc, 0x4400ffc2, 0x07fc00ff, 0x7fff47fa,
                                                           0x3fff7fe5, 0x01fd1fe2, 0x7e407ff1, 0xff301ffc, 0x2aff10df, 0x09f57ebf,
                                                           0xf0ff47f9, 0x4df3274f, 0xf30aaaa8, 0xe81ff00d, 0x415fb11f, 0x7cbf53ff,
                                                           0x3a0df11f, 0x7ffc405f, 0x80ffec04, 0xfc9fc8fe, 0x6f982fc9, 0x327f8df3,
                                                           0xff89fe26, 0x00ff31ff, 0x20fe81ff, 0x987fc1fd, 0x3afbfe5f, 0x006fd83f,
                                                           0xff880df5, 0xff5f903f, 0x403fafea, 0x7c3fb9ff, 0x2ff83ea7, 0x7c47fa66,
                                                           0xfe85d41f, 0x3fb07f40, 0xf97e27f8, 0x5c0bffbf, 0xbf3000ff, 0x1ffefd80,
                                                           0xf14fefa8, 0x5fe40dfb, 0xf13fc0fe, 0xd106fe45, 0xf127ec3f, 0xf88ff63f,
                                                           0x9fe0fec7, 0x501fe5f8, 0x7cc003ff, 0x323fea05, 0x2fff886f, 0xf9813ffa,
                                                           0x747f85ff, 0x7eefff44, 0x3ffe60ff, 0x3fea4ffd, 0x7ec4ffdd, 0x4bf13fc1,
                                                           0x77ff407f, 0xf302eeee, 0xe8ffe20b, 0x20ffe83f, 0x7f402ffc, 0x3647f82f,
                                                           0x33bffb22, 0xbeffd880, 0x67fffdc0, 0x9fe0fec0, 0xd017a5f8, 0x7fffffff,
                                                           0x7e417e60, 0x320ffcc6, 0x007fd46f, 0x1fe03fee, 0x20004031, 0x00001000,
                                                           0x00000000, 0x00000000, 0x00000000, 0x81980000, 0x86206618, 0x10998199,
                                                           0x98819803, 0x26666621, 0x9dc06609, 0x3333332a, 0x33311530, 0x0cc13333,
                                                           0x01333330, 0xf0266666, 0xff1fe81f, 0xfff0fd87, 0xfeb7fd43, 0xfa83fe00,
                                                           0x3fffea2f, 0xf51fe2ff, 0x3fedfbff, 0x321fffff, 0xfffffdaf, 0xf81fe3ff,
                                                           0x42ffffff, 0x24ffffff, 0xf8ff40ff, 0x7c3f60ff, 0x5bff24ff, 0x43fe00fe,
                                                           0x77542ff9, 0x1fe0ffee, 0x2dfb15fd, 0x6fdaabff, 0x36aa672a, 0x1fe0aacf,
                                                           0xfdbabff8, 0x32effe0f, 0xe81ff3ff, 0x6cbfff1f, 0x74ddff0f, 0x401fd6fe,
                                                           0x03ff98ff, 0x13fc3fa8, 0xffb7ccdf, 0x7e403fc0, 0x8554ff02, 0xf17f40ff,
                                                           0xffafd41f, 0xf1fe9999, 0x43f65fdf, 0xcf88fcff, 0x7c01fd6f, 0xd003ffaf,
                                                           0x2fccff0b, 0x267fedf1, 0xfc805fb9, 0x97f2ff02, 0x83fa20ff, 0x7d7ee0ff,
                                                           0x1fffffff, 0xfb1df3ff, 0x2abebfe1, 0x01fd6faf, 0x02fffffc, 0x23fc0fdc,
                                                           0x7fdbea7f, 0x800fffff, 0xf7ff02fc, 0xffffff8d, 0x6e67fc4f, 0x999ff3ff,
                                                           0x65fe3ff9, 0x1ff0fdcf, 0x2df1f99f, 0x3ffe00fe, 0x3e202ffc, 0xdfc8ff06,
                                                           0x99ff6ffb, 0x3f21dfb9, 0xff817e42, 0x777fc1ff, 0xffff80ff, 0xd03fe4ff,
                                                           0x7fc5fe3f, 0x3beff0fe, 0x03fadf6f, 0x1ff53ff8, 0x3fc0fe60, 0x5befff22,
                                                           0xc9fe40ff, 0xf817e41f, 0x87fc5fff, 0x19ff86fc, 0x1fe81ff0, 0x87ffdcff,
                                                           0x3e9ff97f, 0x7fc01fd6, 0x7dc17fa0, 0x4420ff01, 0xfd81ff6f, 0x05f903a3,
                                                           0xf8bf63fe, 0xff13fa0f, 0x3a07fc01, 0xffe8ff1f, 0x4bfeaff0, 0xddddfd6f,
                                                           0xf983fe3d, 0xf00fd82f, 0xff6f880f, 0x23ffdddd, 0xf02fc84c, 0x0ff9be2f,
                                                           0x0ff8bfe6, 0x3fd03fe0, 0x21ff31fe, 0x3e1ff17f, 0xffffffd6, 0xdf903fe5,
                                                           0x1fe07e81, 0x3ffebd10, 0x4021dfff, 0x64ff02fc, 0xfb81ff3f, 0x00003fe6,
                                                           0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                                           0x33333000, 0x4ccccc33, 0x33333099, 0x40033001, 0x10110098, 0x30031013,
                                                           0xa81bb981, 0x77306a22, 0x880dd405, 0xffee80ba, 0xff0fffff, 0x3e9fffff,
                                                           0x00cfffff, 0x3a007ff3, 0x6fff4c2f, 0xfd88bf61, 0x4fb80dff, 0xf0bffbfa,
                                                           0xff92fccf, 0xfffa89ff, 0x7fffcc4f, 0x2ffffe0d, 0x2ffe2aaa, 0x7ff1aaaa,
                                                           0x3209ff97, 0xffb806ff, 0x2fddff42, 0x4dfec5fb, 0xa7fdc4fb, 0xf85914f9,
                                                           0xa6457e67, 0x44fec7f8, 0x22ffe1fd, 0x00ff83fc, 0x0ff803fe, 0xdf107fe2,
                                                           0x7fcc03fd, 0xfe93a62f, 0x226c5f90, 0x93fbfa7e, 0x7f81cffe, 0xfb7117e6,
                                                           0xf302fc4f, 0x0ff86f8d, 0x26667fe0, 0x5f903fe1, 0x05facfb8, 0xf00bf3ba,
                                                           0xa807f21f, 0x93ea766f, 0x7c5fffd9, 0xefd97e67, 0x817e67fc, 0x207f45fa,
                                                           0x22ffffff, 0x1fffffff, 0x44fc81ff, 0x80ff89fe, 0x202fb9fb, 0x403ee4fd,
                                                           0x4fa80efa, 0x1fd51131, 0x2abf53fc, 0x4ff1fe4f, 0x44ff11da, 0xcccff85f,
                                                           0x2aaffe1c, 0xc81ff0aa, 0xfd9be63f, 0x2fba7cc3, 0x7d41df90, 0x500ef980,
                                                           0x2abbe69f, 0x75e7f46f, 0xf93df35f, 0x7defe41f, 0x3efbf60f, 0x200ff82f,
                                                           0x03fe00ff, 0x7ffe45fb, 0x77ec6fff, 0x7e43efee, 0xfb83cc0e, 0xea93ea02,
                                                           0x7fcc1dff, 0x3ff25fae, 0x3ae21fdd, 0xdffc82df, 0x7c01ff02, 0x883fe00f,
                                                           0x333fe0ff, 0x3f61ffcc, 0x2e4fffff, 0x302880ef, 0x427d4015, 0x00800800,
                                                           0xf8010010, 0x3bbfe00f, 0xddff4eee, 0x2fd47ffd, 0x5f702fdc, 0x77777fc4,
                                                           0x7f705f91, 0x00027d40, 0x00000000, 0x3fe00ff8, 0xff6fffff, 0xfd85bfff,
                                                           0x700ff882, 0x7fffdc5f, 0x705f91ff, 0x027d407f, 0x00000000, 0x00000000,
                                                           0x00000000, 0x00000000, 0x00000000, 0x55057000, 0x54550d44, 0x7006a20a,
                                                           0x40dcd549, 0x3732a84a, 0x46a0064c, 0x4c3950ba, 0x531aaaaa, 0x0a985543,
                                                           0x202a0298, 0x5dfff76f, 0x15fc8fe4, 0xf91fdcdf, 0x4bff9105, 0x7d83ffef,
                                                           0x2fffcef8, 0xf103bff5, 0xffbdffdd, 0x3fffee5f, 0xf53ff14f, 0x7fc17e4d,
                                                           0x7c09e842, 0x4ff11dd6, 0x2affd3fa, 0x7f9be23f, 0x05f7fecc, 0xfb0139ff,
                                                           0x97ee7ff0, 0x222effda, 0x2abfd1ff, 0xff73315f, 0x0fff7dc3, 0x6ffb8395,
                                                           0x107ef764, 0xfd55bf3d, 0x7f7c6fc3, 0x4fec1fc9, 0x33fea4fa, 0xff50ff01,
                                                           0x3febffff, 0xd710bf30, 0xfc9fe2bf, 0xff98bf33, 0x003ffd82, 0xfa83f7dd,
                                                           0x77dcf40e, 0x3f61eeee, 0x86fbfafb, 0x261fdcfa, 0x0ff02eff, 0x9ddffdd5,
                                                           0x985f89fe, 0x4df14ffc, 0x44bf12fc, 0x5ff703fe, 0xbf17f500, 0x421757c4,
                                                           0xf50265f9, 0x413ffaff, 0xfc886fef, 0x01fe1cff, 0x7c4ff0fb, 0x3bffd715,
                                                           0x25f937c4, 0x09fd15f8, 0x003fffe2, 0x187f61fd, 0xfbbff801, 0xfbaffc46,
                                                           0x07ff701f, 0x1be5feb8, 0x44ff0fb0, 0x019ff55f, 0x897e4df1, 0xddbff95f,
                                                           0x2fe57f4b, 0x110445f9, 0xffd30001, 0x267fb03b, 0x03fe207f, 0x80df1d40,
                                                           0x3e27f84a, 0x7c401735, 0xafc4bf26, 0x96fffffd, 0xfc9ff4bf, 0x00000002,
                                                           0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x2bbbbbb9, 0x3310cc66,
                                                           0x1a9841a8, 0xbb87332a, 0x003bbbbb, 0x00000000, 0x00000000, 0xffffffa8,
                                                           0xa9fedf15, 0x9dffd35f, 0xff736cd9, 0x3bbba23f, 0x00006eee, 0x00000000,
                                                           0x88000000, 0x11999999, 0x5fa9fedf, 0x9fffb7d7, 0x99988644, 0x00000000,
                                                           0x00000000, 0x22000000, 0x21aaaaaa, 0xa7c4dd5f, 0x00000980, 0x00000000,
                                                           0x00000000, 0x3fea0000, 0x46a5ffff, 0x0000d429, 0x00000000, 0x00000000,
                                                           0x10000000, 0x03555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                                           0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static signed short stb__arial_bold_16_usascii_x[95] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        1, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1,
                                                        1, 1, 1, 0, 1, 0, 1, 0, 0, 1, -1, 0, 0, -1, 0, 1, -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
                                                        -1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,};
static signed short stb__arial_bold_16_usascii_y[95] = {12, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 3, 10, 7,
                                                        10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 3, 4, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 13, 1, 4, 1, 4, 1, 4, 1, 4, 1, 1,
                                                        1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 5,};
static unsigned short stb__arial_bold_16_usascii_w[95] = {0, 3, 7, 8, 8, 13, 11, 3, 5, 5, 6, 8, 3, 5,
                                                          2, 5, 8, 5, 8, 8, 8, 8, 8, 8, 8, 8, 3, 3, 8, 8, 8, 9, 14, 11, 9, 10, 9, 8, 8, 11, 9, 4, 7, 10,
                                                          8, 10, 9, 11, 8, 11, 10, 9, 9, 9, 11, 14, 10, 11, 9, 4, 5, 4, 8, 10, 4, 8, 9, 8, 8, 8, 6, 8, 7, 2,
                                                          4, 8, 2, 12, 7, 9, 9, 8, 6, 8, 5, 8, 8, 12, 8, 8, 7, 6, 2, 6, 8,};
static unsigned short stb__arial_bold_16_usascii_h[95] = {0, 11, 5, 12, 14, 12, 12, 5, 15, 15, 6, 8, 5, 3,
                                                          2, 12, 12, 11, 11, 12, 11, 12, 12, 11, 12, 12, 8, 11, 8, 6, 8, 11, 15, 11, 11, 12, 11, 11, 11, 12, 11, 11, 12, 11,
                                                          11, 11, 11, 12, 11, 13, 11, 12, 11, 12, 11, 11, 11, 11, 11, 14, 12, 14, 7, 2, 3, 9, 12, 9, 12, 9, 11, 12, 11, 11,
                                                          15, 11, 11, 8, 8, 9, 11, 11, 8, 9, 12, 9, 8, 8, 8, 12, 8, 15, 15, 15, 4,};
static unsigned short stb__arial_bold_16_usascii_s[95] = {126, 59, 19, 117, 55, 1, 15, 27, 24, 1, 117,
                                                          48, 124, 45, 125, 45, 87, 73, 50, 105, 41, 108, 27, 91, 51, 36, 104, 124, 32, 10, 65,
                                                          63, 35, 29, 114, 19, 19, 10, 1, 7, 40, 100, 79, 80, 71, 60, 50, 96, 31, 69, 20,
                                                          60, 1, 30, 113, 98, 87, 75, 65, 64, 1, 50, 108, 51, 40, 97, 114, 106, 96, 1, 40,
                                                          70, 47, 124, 30, 11, 125, 74, 57, 115, 55, 105, 41, 79, 90, 88, 23, 10, 95, 81, 87,
                                                          17, 14, 7, 31,};
static unsigned short stb__arial_bold_16_usascii_t[95] = {1, 55, 76, 1, 1, 17, 17, 76, 1, 1, 67,
                                                          67, 67, 76, 55, 17, 17, 55, 55, 17, 55, 1, 17, 42, 17, 17, 67, 42, 67, 76, 67,
                                                          55, 1, 55, 42, 30, 55, 55, 55, 30, 42, 42, 17, 42, 42, 42, 42, 1, 43, 1, 43,
                                                          17, 43, 30, 30, 30, 30, 30, 30, 1, 30, 1, 67, 76, 76, 55, 17, 55, 17, 67, 30,
                                                          17, 30, 17, 1, 43, 30, 67, 67, 55, 30, 42, 67, 55, 1, 55, 67, 67, 67, 1, 67,
                                                          1, 1, 1, 76,};
static unsigned short stb__arial_bold_16_usascii_a[95] = {64, 76, 109, 127, 127, 204, 165, 54,
                                                          76, 76, 89, 134, 64, 76, 64, 64, 127, 127, 127, 127, 127, 127, 127, 127,
                                                          127, 127, 76, 76, 134, 134, 134, 140, 223, 165, 165, 165, 165, 153, 140, 178,
                                                          165, 64, 127, 165, 140, 191, 165, 178, 153, 178, 165, 153, 140, 165, 153, 216,
                                                          153, 153, 140, 76, 64, 76, 134, 127, 76, 127, 140, 127, 140, 127, 76, 140,
                                                          140, 64, 64, 127, 64, 204, 140, 140, 140, 140, 89, 127, 76, 140, 127, 178,
                                                          127, 127, 115, 89, 64, 89, 134,};

#if 0
// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT or STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_bold_16_usascii(stb_fontchar font[STB_FONT_arial_bold_16_usascii_NUM_CHARS],
                                           unsigned char data[STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT][STB_FONT_arial_bold_16_usascii_BITMAP_WIDTH],
                                           int height) {
    int i, j;
    if(data != 0) {
        unsigned int *bits = stb__arial_bold_16_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for(i = 0; i < STB_FONT_arial_bold_16_usascii_BITMAP_WIDTH * height; ++i)
            data[0][i] = 0; // zero entire bitmap
        for(j = 1; j < STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT - 1; ++j) {
            for(i = 1; i < STB_FONT_arial_bold_16_usascii_BITMAP_WIDTH - 1; ++i) {
                unsigned int value;
                if(numbits == 0) bitpack = *bits++, numbits = 32;
                value = bitpack & 1;
                bitpack >>= 1, --numbits;
                if(value) {
                    if(numbits < 3) bitpack = *bits++, numbits = 32;
                    data[j][i] = (bitpack & 7) * 0x20 + 0x1f;
                    bitpack >>= 3, numbits -= 3;
                } else {
                    data[j][i] = 0;
                }
            }
        }
    }

    // build font description
    if(font != 0) {
        float recip_width = 1.0f / STB_FONT_arial_bold_16_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for(i = 0; i < STB_FONT_arial_bold_16_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_bold_16_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_bold_16_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_bold_16_usascii_s[i] + stb__arial_bold_16_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_bold_16_usascii_t[i] + stb__arial_bold_16_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_bold_16_usascii_x[i];
            font[i].y0 = stb__arial_bold_16_usascii_y[i];
            font[i].x1 = stb__arial_bold_16_usascii_x[i] + stb__arial_bold_16_usascii_w[i];
            font[i].y1 = stb__arial_bold_16_usascii_y[i] + stb__arial_bold_16_usascii_h[i];
            font[i].advance_int = (stb__arial_bold_16_usascii_a[i] + 8) >> 4;
            font[i].s0f = (stb__arial_bold_16_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_bold_16_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_bold_16_usascii_s[i] + stb__arial_bold_16_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_bold_16_usascii_t[i] + stb__arial_bold_16_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_bold_16_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_bold_16_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_bold_16_usascii_x[i] + stb__arial_bold_16_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_bold_16_usascii_y[i] + stb__arial_bold_16_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_bold_16_usascii_a[i] / 16.0f;
        }
    }
}
#endif

#ifndef STB_SOMEFONT_CREATE
    #define STB_SOMEFONT_CREATE              stb_font_arial_bold_16_usascii
    #define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_bold_16_usascii_BITMAP_WIDTH
    #define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT
    #define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_bold_16_usascii_BITMAP_HEIGHT_POW2
    #define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_bold_16_usascii_FIRST_CHAR
    #define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_bold_16_usascii_NUM_CHARS
    #define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_bold_16_usascii_LINE_SPACING
#endif

