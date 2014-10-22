// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_arial_bold_21_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_arial_bold_21_usascii'.
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

#define STB_FONT_arial_bold_21_usascii_BITMAP_WIDTH         256
#define STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT         64
#define STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT_POW2    64

#define STB_FONT_arial_bold_21_usascii_FIRST_CHAR            32
#define STB_FONT_arial_bold_21_usascii_NUM_CHARS             95

#define STB_FONT_arial_bold_21_usascii_LINE_SPACING          14

static unsigned int stb__arial_bold_21_usascii_pixels[]={
    0x17950591,0x32e05930,0x54c1c883,0xacca8802,0x95554c00,0x7502aaa9,
    0x2f2ea200,0x2a200002,0x4c402bcb,0xa8019999,0x931ca82a,0x22057105,
    0x1cb8802c,0x200d4c00,0xcb800aa9,0x88015300,0xa981bcca,0x643fc002,
    0x27d40fff,0x7ec37ff4,0xc8837ec1,0xfffffffe,0x2dfff902,0xd886fffc,
    0x7ffdc02f,0x2601efff,0x7fffdc06,0xff901eff,0xd803ffff,0xf92fd87f,
    0x87fefb87,0x7fe401fc,0x74400fff,0x6c41efff,0x7c03ffff,0xdffffc87,
    0xfffffb80,0x01bf60df,0xfca87f90,0x2627d43f,0x37cc3dff,0x7fd437ec,
    0xeb988ace,0x6feca83f,0xfd879ff9,0xfc80efff,0xffffdfff,0x3207fb81,
    0xfffdffff,0xffffe81f,0x3fec01ff,0x41fe87fc,0x7c45f77d,0x4dffc405,
    0x7ffc04fd,0x7fe46ffd,0xf303fffd,0xfddff98b,0x6fffd43f,0x3f64fffd,
    0x83fcc006,0x227d44fd,0x07fb07fa,0x400ffcc0,0x2df703fc,0xdffa85fc,
    0x7fcc5ffe,0x1bff222e,0x7fcc1fee,0x1bff222e,0x06666ffe,0x4cc5ff60,
    0x21ff99ff,0x649f56f8,0x8ffd401f,0x3fee06fb,0x3e23ff31,0x5c1bfa4f,
    0xf72fec3f,0xff87fc8f,0x2001bf67,0x45fd83fe,0x43fd44fa,0x5ec80ff8,
    0x7644bfe2,0x0fb5eabe,0x42fe5bee,0x4eaebbfd,0xfc80ffec,0x3bffb22f,
    0xc80ffe44,0x03fe62ff,0x7f5ff600,0xffffffff,0x8a7d5fe1,0xdff8805f,
    0x3fa04ff9,0x70ffcc05,0x83fb03ff,0x91fea4fd,0x0aa981ff,0x7dfb1dfb,
    0xfc85fc80,0x3ee27d45,0xfb06fa86,0xfe89fd4d,0xf35fffef,0x3f2df703,
    0x06bbfe85,0xff881bfa,0x1bffff64,0x7fc40dfd,0x37f7fea4,0x3affb001,
    0xffffffff,0x3f67f61f,0x32003f91,0x200dffff,0x983c8cff,0x0bfea1ff,
    0x2ffea1fe,0x7fc44fea,0xffb00bdf,0x409fffff,0x46fc86fb,0x42fe44fa,
    0x4dfb05fb,0xfc93fa7c,0x3ee0fe4f,0xff70bf96,0x02ffc0dd,0xffd997fe,
    0x202ffc2a,0x3fff25ff,0xfd805fff,0x3fc97ec7,0xf15ffe98,0x7ffdc00b,
    0x7f7fc405,0x1ff43fff,0x5f887ff9,0x0bffff50,0x37fffff6,0x4ceffec2,
    0xff501ffe,0x7d45ff30,0x3613fe64,0x74dfb04f,0x7cc1ff15,0x3ee17e2f,
    0xff10bf96,0xff885bff,0x2e37fc04,0x04ff887f,0x5df937fc,0xd807ff93,
    0xfe87fc7f,0x1fc82601,0x3ff60551,0x88151fff,0x7fd9cfff,0x7fee7fdc,
    0x441fd43f,0x02fffffe,0x9fffffb3,0xff30ffec,0x207fe607,0x29f55ffd,
    0xfe80effb,0x3e2dfb03,0xff989f73,0xdf709f10,0x7e4417f2,0x2ffc4fff,
    0xfb89ff10,0x440bff07,0x7fc405ff,0xbabfec05,0xabffaaff,0xfaafc400,
    0x3ff20eff,0xffbeff9b,0xf89ffe20,0x3fff222f,0x0fe43ffc,0xffc877ec,
    0x3ff2a200,0xff0dfb1f,0x207fe609,0x29f55ffb,0x7ff04ffb,0x8fd5bf60,
    0x53fd43fd,0x32df705f,0x7f7dc05f,0x151ffa0f,0xff70ffea,0x5403ffa0,
    0x6fe803ff,0xd6fe8531,0xffffffff,0x91fc803f,0x7f45f73f,0x1bfffea5,
    0x0bfd17fe,0xd0bfe651,0x447ff10f,0x039513ff,0x1ff67ff5,0x3fcc17fe,
    0xfa8e7fcc,0xb07ff714,0x4dbf609f,0xfd87fd3f,0x3ee0df15,0x6b80bf96,
    0x9ffe47fd,0x1ffebff8,0xffc83fdc,0x21ffe884,0xca7fc2cb,0x5d7fe0ff,
    0xcefecdfe,0xf97e200c,0x3fe2bf37,0x417ffe44,0x327fc7fe,0x107fdc13,
    0x47ff10df,0xdff12ff8,0x3f67ff30,0x413fe60f,0x46fb86fa,0x42fec4fa,
    0x4dfb04fc,0x7d4df75f,0x702fe8cf,0xd117f2df,0x0bf6d73f,0xff55dffd,
    0x1ff709ff,0x26fbffa0,0x7e44fffc,0x2a3ff70f,0x4ffb9dff,0x017e4bf6,
    0x55fe1fc8,0x447ff64f,0x540efffd,0x47ff53ff,0x8bfd35fe,0x1dff04fa,
    0xffd83ff2,0x1ffea89c,0xf911bffb,0x217ee03f,0x227d45fc,0x05fb86fb,
    0xf8becdfb,0xfffffeef,0x65bee02f,0xecefd85f,0x7fcc0ff9,0xcfffffff,
    0x437ffd40,0xfffffff9,0x7ffc40df,0x7ff45fff,0x3fe0efff,0xf1003fd0,
    0x2fb9fc8b,0x3fffffe6,0x740fffff,0x546fffff,0x41ffffff,0xfff502fc,
    0xff889fff,0x24ffffff,0xfffffefd,0x320ff605,0x2e27d45f,0xb07f986f,
    0xc8a7dcdf,0x1cefb8ce,0x32df7031,0xffffa85f,0xfd9104ff,0x1fffbdff,
    0x9106ffd8,0x407dffff,0x884fffc9,0x221dfffe,0x6401fe6f,0x77ffcc1f,
    0x7ffff4c0,0xfb105f73,0xfd701bff,0x01fd03df,0x067ffed4,0x77fffec4,
    0x7fd67ec3,0x407fc05f,0x227d44fd,0x03fd07fa,0x05fe8bfb,0x3ee13f20,
    0x3660bf96,0x31002eff,0x01106fa8,0x02000620,0x20980620,0x40790009,
    0x0809801a,0x01100180,0x003000cc,0x002000c4,0xff7113ea,0x7d44fa87,
    0x327d41bf,0xff88bff7,0xfe9881ad,0xcb7e4c44,0x0d9009ef,0x00004000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x81fb0000,0x7d41fffc,
    0x437ffc44,0x0ffff27e,0x3bffff22,0xc84ffffe,0xfff96fff,0x00012a0d,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x37b213e2,
    0xd984fa82,0xf92fa86e,0xd973007d,0x2e017bdf,0xddd75eee,0x0000000b,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x40000000,0x980bccb9,0x2055302a,0x44001aa8,0x1aa880aa,0x2a200990,
    0xbec81bcc,0x54c3eec8,0x332e2002,0x45f76c42,0x776441ee,0x2aa1ee8b,
    0x2aaaaaaa,0xa9805554,0x1035510a,0x41554555,0x1aa81aa9,0xaa880aaa,
    0x2aa65530,0x2aaaaaaa,0x2a600aa6,0x1e545532,0x3fffffe6,0xc83fe43f,
    0xffffb87f,0x07fe6005,0xb0bffff9,0xfffb801f,0x3f60cfff,0x24fffffe,
    0x3fa006fc,0x3ffe24ff,0x221ffdff,0xffdffffe,0x3fffffe1,0x7fd46fff,
    0x746ff885,0x1ffe41ff,0xbffd0ffb,0x3f23ff98,0x21ff901f,0xffff97fc,
    0x21ffffff,0x7fc806fd,0x337ecffb,0xffdbffff,0xc83fe43f,0x6f7fc47f,
    0xff3003ff,0x7f77fdc3,0x7017dc2f,0xfffbdfff,0x4d77fec9,0x0df91ffe,
    0x86b7fe60,0xffb8bffd,0x273ff21f,0x3ba1fffb,0x6fffeeee,0x7ec1ffd8,
    0x337fcc2f,0x1ffb8dff,0xf71fffe2,0x827fcc3f,0x5dff26ff,0xeefffeee,
    0x00dfb0ee,0xd9ff6ff9,0x17fff16f,0xff937fd4,0xff91ff20,0x4c01bf61,
    0xd93fa1ff,0x8827cc6f,0x3fa22eff,0x4c3ffb0f,0x00df94ff,0x3fe07fea,
    0xff0ffe46,0x401ffc8d,0xf881fff9,0x417fe66f,0x3ffd3ffc,0x3ee3ff98,
    0x1ff21fff,0x3fea1ffe,0x03ff2003,0x7e4037ec,0x75c8ffb7,0x2b2e05ff,
    0x3f20ff90,0xff52ffc7,0x9beed883,0xd82621ff,0xf906f86f,0x217b503f,
    0x95ff87fd,0x89dd91df,0x10eeffec,0x1ffa87ff,0xffa89ff1,0x0bffe201,
    0xffd3ffb8,0x33ffe201,0x4bff04ff,0x3a3ffdfd,0x41ffc85f,0x17ae0ffc,
    0xfd807fe4,0xfc93baa6,0x97d4ffb7,0x7e4007fd,0xff8ff907,0xf88bfe64,
    0x1ffeffff,0xb07ff710,0x00dfd01f,0xaffc3fec,0xffffeffc,0x3fffff65,
    0xfa89ff10,0xa89ff11f,0x3ffa01ff,0xfcffe803,0x7ffd402f,0xf9bf606f,
    0xff15fdbf,0xf89ff307,0xc83fe45f,0x2dfb00ff,0xbfe46ff9,0xff8f27fd,
    0x4ccccc45,0x3f20ff90,0xf993fe27,0x22fff63f,0xfb01fffb,0x20bee07f,
    0x3f6005ff,0x653fe21f,0xffe88dff,0x835ff710,0x0ffec6fe,0x1ffc8dff,
    0x200bffb0,0x005ffff9,0x5c03fffb,0xa9ff98ff,0x203ff57f,0x0bfe67fe,
    0x3ff20ff9,0xff1dfb00,0xfb7fc81d,0x2a2ffc0f,0xf93fffff,0xf89ff20f,
    0xf8ffe23f,0x80ffec6f,0xf982ffed,0x2005ff84,0xfc88dffd,0x5c1ff92f,
    0x07fea0ff,0x3f273ff2,0x4bff61ff,0xfb81fff9,0x3f2000ef,0xffb000ff,
    0x57fcc03f,0x73ff17fb,0x8ffdc0ff,0x07fc87fc,0x3f601ff9,0xfc80efee,
    0x7f40ffb7,0x7ffffd46,0xf901ff93,0xf31ffc4f,0x70ffe25f,0xffb803ff,
    0x7fc37c40,0x3fff6006,0x3f25ffff,0xf50ffd47,0xffff103f,0x7c43ffdf,
    0x1fffffff,0x0007ffcc,0x54013fe2,0x2206ffff,0x3a5fdbff,0x2206fdbf,
    0x90bff4ff,0x03ff20ff,0x07ffffec,0x27fdbfe4,0x01ff93ca,0x7fdcffe6,
    0x7fc7fd80,0x7c4bfe64,0x00ffd43f,0x3fa0ffe2,0xd983fec0,0xff5dfb0b,
    0x546fc8bf,0x07fea1ff,0x7cdf7ec4,0x6ffe441f,0x3fe21ffa,0xff88001f,
    0xdfff8804,0x3bfa03ff,0x3fbf22ff,0x57ff404f,0x07fc82ff,0x3f601ff9,
    0xfc84ffff,0xb7e4ffb7,0xff504ffa,0x3a0bfee7,0xf52ff47f,0x322ffc3f,
    0x45d911ff,0x1fc82ff9,0x7ec1ffdc,0x804dfb1f,0x0ffd46fc,0x03303ff5,
    0x42201ff5,0xffd11ff9,0x3fe20007,0x8bffd804,0xff901fff,0x7ffd41ff,
    0x77fdc02f,0x20ff907f,0xffb00ffc,0xfc83ff73,0x37e4ffb7,0x9337fff9,
    0x3fe67fff,0x4ffc99bf,0x6fe8ffdc,0xff99ffec,0x223bf61f,0x07f507fd,
    0xf935bffd,0x4037ec9f,0x0ffd46fc,0xff903ff5,0x401ff665,0xdff91ff9,
    0x03333333,0x5404ff88,0x1bfea6ff,0x2237ffd4,0x4400ffff,0xf904ffff,
    0x403ff20f,0x91bfa6fd,0x201ff6ff,0xfffffffd,0x3fff20df,0x440fffff,
    0x42ffffff,0xfefffff9,0x3fffe61f,0x0bf104ff,0xfffffff3,0x4037ec1f,
    0x0ffd46fc,0xff103ff5,0x007fffff,0x7fec7fe6,0xffffffff,0x813fe200,
    0x7ec1fff8,0x4fff883f,0xb006ffe8,0x3f203fff,0x201ff907,0x8bfea6fd,
    0x00ffb7fc,0x37bfff6e,0xffffd702,0x3ffa201b,0xbfff302f,0xfd983ff1,
    0x83f401df,0x0bdfffc8,0x7e402f64,0xf50ffd46,0x3fb6603f,0x3a6001de,
    0xfffffb1e,0x401fffff,0x3f204ff8,0x1fff884f,0xfc82ffe8,0xdff5004f,
    0xfc83fe40,0xd8dfb00f,0x7edff26f,0x00088007,0x0110004c,0x01000220,
    0x02200620,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0xaaaa9800,0x553019aa,0x53055555,0x4c551015,
    0xaaa81aaa,0x8015530a,0x555302a9,0x99999998,0x26355109,0x6455302a,
    0x265eb85e,0xaaaaaaaa,0x55555531,0x2aa61555,0x5301aaaa,0x01555555,
    0xcc803dd1,0x00aaa801,0x2a2072e0,0x0a9802bc,0x77545ec8,0xf9171000,
    0xdfffffff,0xfffffc81,0x3ff21eff,0x3f27fb84,0xffff84ff,0xc801ff92,
    0x7ffcc0ff,0x3ffffe62,0x7ff34fff,0x3f203ff2,0xe83ff50f,0x3ffff25f,
    0xff94ffff,0x5fffffff,0x3ffffff2,0x7ffe41ef,0x4c5fffff,0x3fee02ff,
    0x1fffc402,0x5c2ffb80,0x81efffff,0x21dffffc,0x07fd46fd,0x323ff260,
    0xffeeeeff,0x777fe46f,0x3f27fffe,0x93fdc1ff,0xff98dfff,0x01ff92ff,
    0x3e60ffc8,0x7ffcc2ff,0xf34fffff,0x203ff27f,0x93fe0ffc,0x3ff22ff9,
    0x93eeeeee,0xddddddff,0x3bbff23d,0x321ffffe,0xffeeeeff,0x407ba24f,
    0x5c02fff9,0xf9806fff,0x3bfe22ff,0x7e45fecb,0x365ffdef,0x807fd46f,
    0xc8ffffda,0x7ff440ff,0xfb03ff20,0x1bfff25f,0x7ffe4ff7,0x3fffee0f,
    0xc801ff92,0x5fff10ff,0x36666660,0x27ff30ef,0xffc80ffc,0x7fc9ff20,
    0x32007fe4,0x7fc800ff,0x3f25ffb8,0x037fc40f,0x00bfffa0,0x203ffffd,
    0x22ffffd8,0x0ffcc6fc,0x8ffd4bff,0x07fd46fd,0x7dfffd71,0x2e03ff21,
    0x03ff21ff,0x3ff29ff3,0xc9fee3ff,0x3f63feef,0x1ff92ffd,0xe88ffc80,
    0x3e2003ff,0x64bfe61f,0x0ffc80ff,0x27f47fe6,0xf9003ff2,0x0ff9001f,
    0x7fe47ff2,0x2006fd80,0x202ffefb,0x05ffaff9,0x45ff9ff7,0x23ff82ca,
    0x4ffe22cc,0x87fd46fd,0x81cffff8,0x7fd80ffc,0x3ea07fe4,0xffdff93f,
    0xefc9fee1,0x3effe5fc,0x801ff92f,0x3ffe9ffc,0x221fe400,0x33ff91ff,
    0x81ff9333,0x41ff9cfe,0x7e400ffc,0x0999999f,0x7fd41ff2,0x3333ff92,
    0x26007ff7,0x202ff9ff,0x01ffb7fc,0x05ff1197,0xb803ff90,0xb8dfb1ff,
    0x5fff10ff,0x7777fe40,0x7e44fffe,0xfffcaabf,0x9ff3df91,0xaefc9fee,
    0xff3ff37f,0x9003ff25,0x09fffdff,0x7c07fcc0,0xfffff91f,0xb81fffff,
    0xfc86fcff,0x25ffffff,0xfffffffc,0x4c1ff26f,0xffff93ff,0x4007ffff,
    0x02ff8bfe,0x3fe69ff1,0x017fc403,0xd100fff2,0x2e3fecdf,0x3fff60ff,
    0x7ffe40cf,0xc81dffff,0xffffffff,0x7fedbf24,0x3bf27fb9,0x9dfb9ff8,
    0x01ff92ff,0xffffffc8,0x09fb001f,0x7ffe43fe,0x0fffffff,0x41ffffc4,
    0xfffffffc,0x3fffff25,0x1ff26fff,0xffca7fcc,0x1effffff,0x5fc87322,
    0x3ee05ff1,0x101bfe1f,0x7fe405ff,0x0fff4403,0x3fa23ff7,0x7ffe440f,
    0x77ff92df,0x3f205ffd,0x42deefff,0x7dff16fc,0xfeb7e4ff,0x2ff9bfeb,
    0xfc801ff9,0x06ff9bff,0xfd01ff98,0x4cccffe4,0xfd80ffc9,0x9ffc80ff,
    0x3f209999,0x07fc800f,0x3ff27ff3,0xffea9999,0x3e65ff30,0x205ff10f,
    0xfdaaaffe,0x0bfe201f,0x22027fc4,0x7fcc2ffe,0x00ffefef,0x91fffd71,
    0x1fff41ff,0x64007fe4,0x3fbfee6f,0x77e5bf27,0x92ff99ff,0xffc801ff,
    0x7013ff24,0xf93ec0df,0x01ff901f,0x3f20bff5,0x07fe400f,0xfa83fe40,
    0x301ff92f,0x4bfe67ff,0xfffffffc,0x7fffcc7f,0x205fffff,0xff502ff8,
    0x02ffe880,0xff39fff7,0x91fb5001,0x7ffc41ff,0x4007fe41,0x7fff46fc,
    0x7fd5bf27,0x325ff37f,0x7fe400ff,0x807ffe20,0xc8ea04fd,0x0ffc80ff,
    0xf902ffa8,0x0ffc801f,0xfd07fc80,0x203ff21f,0x47e23ffa,0xfffffffc,
    0x7fffe47f,0x00ffffff,0x32605ff1,0x0bffa203,0x46000060,0x7fdc0ffc,
    0x4007fe46,0x7ffcc6fc,0x7fc5bf27,0x325ff35f,0x99999aff,0xfb81ff90,
    0x40ffa06f,0x1ff91cc8,0x54c1ff90,0x3ff207fe,0x4cffe400,0xf9099999,
    0xffb5333f,0x4ccffe47,0xb11ffeba,0x54cccc4d,0x2ffc1bff,0xf103ffa8,
    0x0332605f,0x5556ffe4,0x4000001a,0xffd80ffc,0x2003ff23,0x7ffc86fc,
    0x3ffe9bf2,0x3ff25ff3,0x96ffffff,0x9ffd01ff,0x2603ff10,0x01ff92ff,
    0x3fe21ff9,0x3ff203ff,0x7fffe400,0xf94fffff,0xbfffffff,0xffffffc8,
    0x03625fff,0xfa85ff10,0x41bfe02f,0xff702ff8,0x3ffffe01,0xfff13fff,
    0x7fffffff,0x407fe400,0xff90fff8,0x10df9001,0x937e4fff,0x4bfe63ff,
    0xfffffffc,0x301ff96f,0xff983fff,0x325ff300,0x0ffc80ff,0xf900fbfa,
    0xfffc801f,0x94ffffff,0x5bdfffff,0xffffff90,0x220007df,0x07fec2ff,
    0xf103ff90,0x03fee05f,0x3fffffea,0xbbbb13ff,0x05bbbbbb,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x98001710,0x9304dfec,0xa98059dd,0xceeca801,0x2f7fae00,
    0x1deec880,0x8ef55f64,0x21f6c3ec,0x919d72ed,0x85ec89dd,0x5dd10eeb,
    0x37f66bb6,0x4c1bdb51,0x4eeeeeee,0xee98fbaa,0xd1079504,0xdddddddd,
    0x5dc1c881,0x0ddc7752,0x331080d4,0x07322133,0x67fc4000,0xffff9800,
    0x7ffdc6ff,0x3f603fff,0x7fffe404,0x7ff442ff,0x7fc45fff,0x3f62ffff,
    0xff71fffe,0xff337fcc,0x3ffbbf23,0x07fea5ff,0x97fc4bfd,0xfffffefe,
    0x50effffc,0xbfffffff,0xffd1ffe8,0x81fff101,0xfffffff8,0x20fc40ff,
    0x22ffd6ff,0xfff714ff,0x2a5b539d,0x3ee4ffff,0xff100005,0x7ec03bff,
    0x747fc88d,0xd817f22f,0x37fee04f,0x320ffeb9,0x2ffb8bff,0x3f62bbf6,
    0x95dffb0f,0xffb8ffcc,0x7e4df90f,0x0ffe88df,0x2ff993fe,0x7ff4bba2,
    0x8bfffa8b,0x55512ffc,0xf885fff7,0x702ffcef,0xbb887fff,0x0bbbbbbb,
    0x29d7f7d7,0x22ffd6ff,0xffff54ff,0x2a5fffff,0x7e44ffff,0xd7100001,
    0x2207dfff,0xfe87fee0,0x9fb001be,0x3ea37f40,0x571bfe3f,0xf88ffe21,
    0x201ffb2f,0x5fffb3fe,0x0ffc93fa,0x7fc83fee,0x3fa01bf2,0xff337fc7,
    0x40fff607,0x204ffffb,0x0007fdff,0x96fff64c,0x7cdfb5fe,0x9513b53f,
    0x55449fff,0x000081aa,0xffff9300,0xfffdb981,0x3fffea1f,0x3bba20be,
    0x10eeefff,0x2bff09ff,0x7cc03ff8,0x4ffeeeef,0xafe40ffb,0xff8cfcff,
    0xff51ff21,0xff97fcc3,0x7c6fe803,0x20ffe25f,0x7ec04ffc,0x7dfee06f,
    0x3bbba23f,0x220eeeee,0x4ff20fee,0x00bfa5fb,0x00000002,0x0fffa800,
    0x3f33ffee,0x7fff5c1f,0x3fffe66f,0xf10fffff,0x22bff07f,0x7fcc04ff,
    0xb3eeeeee,0x57fcc0df,0x7fbef9ef,0x3fea3fe4,0x7fd6fec1,0x7c5fe800,
    0x70ffe24f,0xffb00bff,0x64ffa01f,0x3fffe26f,0x3a0fffff,0x42a26e8f,
    0x002a61a8,0x00000000,0x3fffee20,0xfa93fe25,0xfda8841f,0xfd99912f,
    0x7f41999d,0xff27fcc6,0x3fe2cb8b,0x2037ec03,0xdff4feff,0x546fc89f,
    0x6ffd41ff,0x8bfd005f,0x8ffe24ff,0x5c00effa,0xfa85ffff,0x225ff10f,
    0xcccccccc,0x00cca20c,0x00000000,0x7ed40000,0x7cc0cfff,0x4c7ff22f,
    0x07fe22ff,0xffb027ec,0xd87ff667,0x47ff32ff,0x3df50efd,0xff901bf6,
    0x07fff65f,0x1ffa8df9,0x882ffff8,0xf8bfd1cc,0x4cffe24f,0x19999fff,
    0x7fdeffc4,0x32e1e5c3,0x00000003,0x00000000,0x3ffe2000,0x3ffa00be,
    0x322fffed,0x05ffdeff,0xfe8813f6,0x4c3fffff,0x46ffffff,0x5ffefffa,
    0xff501bf6,0x21ffea1f,0x0ffd46fc,0xf883ffe4,0xff8bfd2f,0x7ecffe24,
    0x47ffffff,0x3ffd0ffe,0x00000000,0x00000000,0x3e200000,0xffb3002d,
    0x5c49fd3d,0x200dfffe,0x764404fd,0xfd302eff,0xfd5039df,0x37ec19df,
    0xff137fc0,0xfa8df909,0x04ff981f,0x17fa5ff1,0x9ffc49ff,0xfffffffd,
    0xf98ffee7,0x0000006f,0x00000000,0x20000000,0x00110001,0x000000c4,
    0x80040011,0x00000008,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__arial_bold_21_usascii_x[95]={ 0,1,1,0,0,0,0,0,0,0,0,0,1,0,
1,-1,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,
1,1,1,0,1,0,1,0,0,1,-1,0,0,-1,0,1,-1,0,1,-1,0,0,1,0,0,0,0,0,1,1,
-1,1,1,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0, };
static signed short stb__arial_bold_21_usascii_y[95]={ 17,3,3,3,2,3,3,3,3,3,3,5,14,10,
14,3,3,3,3,3,3,3,3,3,3,3,7,7,5,7,5,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,19,3,7,3,7,3,7,3,7,3,3,
3,3,3,7,7,7,7,7,7,7,3,7,7,7,7,7,7,3,3,3,8, };
static unsigned short stb__arial_bold_21_usascii_w[95]={ 0,4,7,11,10,16,14,4,6,6,7,11,3,6,
3,7,10,7,10,10,11,10,10,10,10,10,4,4,11,11,11,11,19,14,12,13,12,11,10,14,12,4,9,13,
10,14,12,14,11,15,13,12,12,12,14,18,13,14,12,5,7,5,9,12,5,10,10,10,11,10,7,11,10,3,
5,10,3,15,10,11,10,11,7,10,7,10,11,15,11,11,10,7,3,7,11, };
static unsigned short stb__arial_bold_21_usascii_h[95]={ 0,14,6,15,17,15,15,6,18,18,7,11,7,4,
3,15,15,14,14,15,14,15,15,14,15,15,10,14,11,7,11,14,18,14,14,15,14,14,14,15,14,14,15,14,
14,14,14,15,14,16,14,15,14,15,14,14,14,14,14,18,15,18,8,2,4,11,15,11,15,11,14,14,14,14,
18,14,14,10,10,11,14,14,10,11,15,11,10,10,10,14,10,18,18,18,5, };
static unsigned short stb__arial_bold_21_usascii_s[95]={ 253,91,202,144,73,156,173,210,28,1,194,
35,252,227,252,210,29,202,222,52,175,123,188,80,218,199,128,170,244,182,1,
210,41,187,157,71,144,132,121,1,96,247,134,66,55,40,27,108,15,84,1,
229,219,16,200,181,167,152,139,67,63,61,172,233,234,13,242,59,40,70,107,
115,96,215,35,232,243,133,105,47,85,127,81,24,100,233,116,89,160,109,149,
20,16,8,215, };
static unsigned short stb__arial_bold_21_usascii_t[95]={ 1,36,51,1,1,1,1,51,1,1,51,
51,20,51,28,1,20,36,36,20,36,1,1,36,1,1,51,36,36,51,51,
36,1,36,36,20,36,36,36,20,36,20,1,36,36,36,36,1,36,1,36,
1,20,20,20,20,20,20,20,1,20,1,51,48,51,51,1,51,20,51,20,
20,20,20,1,20,20,51,51,51,20,20,51,51,1,36,51,51,51,36,51,
1,1,1,51, };
static unsigned short stb__arial_bold_21_usascii_a[95]={ 84,100,143,167,167,267,217,72,
100,100,117,176,84,100,84,84,167,167,167,167,167,167,167,167,
167,167,100,100,176,176,176,184,293,217,217,217,217,201,184,234,
217,84,167,217,184,251,217,234,201,234,217,201,184,217,201,284,
201,201,184,100,84,100,176,167,100,167,184,167,184,167,100,184,
184,84,84,167,84,267,184,184,184,184,117,167,100,184,167,234,
167,167,150,117,84,117,176, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT or STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_arial_bold_21_usascii(stb_fontchar font[STB_FONT_arial_bold_21_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT][STB_FONT_arial_bold_21_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__arial_bold_21_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_arial_bold_21_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_arial_bold_21_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_arial_bold_21_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_arial_bold_21_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__arial_bold_21_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__arial_bold_21_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__arial_bold_21_usascii_s[i] + stb__arial_bold_21_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__arial_bold_21_usascii_t[i] + stb__arial_bold_21_usascii_h[i]) * recip_height;
            font[i].x0 = stb__arial_bold_21_usascii_x[i];
            font[i].y0 = stb__arial_bold_21_usascii_y[i];
            font[i].x1 = stb__arial_bold_21_usascii_x[i] + stb__arial_bold_21_usascii_w[i];
            font[i].y1 = stb__arial_bold_21_usascii_y[i] + stb__arial_bold_21_usascii_h[i];
            font[i].advance_int = (stb__arial_bold_21_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__arial_bold_21_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__arial_bold_21_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__arial_bold_21_usascii_s[i] + stb__arial_bold_21_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__arial_bold_21_usascii_t[i] + stb__arial_bold_21_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__arial_bold_21_usascii_x[i] - 0.5f;
            font[i].y0f = stb__arial_bold_21_usascii_y[i] - 0.5f;
            font[i].x1f = stb__arial_bold_21_usascii_x[i] + stb__arial_bold_21_usascii_w[i] + 0.5f;
            font[i].y1f = stb__arial_bold_21_usascii_y[i] + stb__arial_bold_21_usascii_h[i] + 0.5f;
            font[i].advance = stb__arial_bold_21_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_arial_bold_21_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_arial_bold_21_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_arial_bold_21_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_arial_bold_21_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_arial_bold_21_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_arial_bold_21_usascii_LINE_SPACING
#endif
