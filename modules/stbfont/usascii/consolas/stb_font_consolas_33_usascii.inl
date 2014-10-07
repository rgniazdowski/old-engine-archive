// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_consolas_33_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_consolas_33_usascii'.
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

#define STB_FONT_consolas_33_usascii_BITMAP_WIDTH         256
#define STB_FONT_consolas_33_usascii_BITMAP_HEIGHT        146
#define STB_FONT_consolas_33_usascii_BITMAP_HEIGHT_POW2   256

#define STB_FONT_consolas_33_usascii_FIRST_CHAR            32
#define STB_FONT_consolas_33_usascii_NUM_CHARS             95

#define STB_FONT_consolas_33_usascii_LINE_SPACING          22

static unsigned int stb__consolas_33_usascii_pixels[]={
    0x26a21551,0x40164000,0xaaaaaaa8,0x02a62001,0xaaa89620,0x7001aaaa,
    0x2e6003dd,0x0001bded,0x02660000,0x3ba60000,0x0005dd32,0x44013bae,
    0x754660aa,0x4400001e,0xed880009,0x3b6200de,0xff32ff9b,0xff7007ff,
    0xffffa803,0xfa804fff,0x74403fff,0xfffff75f,0xff1007ff,0xfff900df,
    0x0007ffff,0xd9800bf7,0x00ceffff,0x41ff9000,0xf90005fe,0x7fecc0bf,
    0x53ffffff,0x200005ff,0x02fffffc,0xffffff30,0x263ff203,0xffff32ff,
    0xfff980bf,0x3fffea01,0x7e404fff,0x2203ffff,0xfff71ffe,0x3007ffff,
    0x7440ffff,0xff951bff,0x04fc8007,0x3ffffee0,0x0001efff,0x3ee27fc4,
    0xffc8001f,0xfffff704,0x2a7fffff,0x440002ff,0xfffffffe,0xa8dfe804,
    0x2ffa85fe,0xeb985ff3,0x7fcc02ff,0x3fe2000f,0x33ffe604,0x22ffe801,
    0x20001ffb,0x3f604ffe,0x03ff701e,0xd801fec0,0xeb9acfff,0x20001fff,
    0x7fc41ffb,0x4ffc8004,0x20aeffb8,0xff53ffc9,0xffc80005,0x1fffb89d,
    0xfb87fe20,0xf32ff447,0x17fea05f,0x8017fea0,0x3f204ff8,0x7ff9003f,
    0x0001ffb8,0x1ff70154,0x2204fd80,0xcefffedb,0x03fff302,0x000bffd1,
    0xffc82ff4,0x27fe4000,0x5403bfe2,0x05ff53ff,0xc86ff800,0x1fea03ff,
    0x7fe41ff3,0xf80bfe60,0x5ffb006f,0x813fe200,0xf8800ffd,0x01ffb86f,
    0x3fe20000,0x887f9802,0xfffffffc,0x3ffb05ff,0x007ffc40,0x9817fcc0,
    0x7dc003ff,0x017fe44f,0x3fea7ff5,0x3fe20002,0x204ff985,0x3fe60ffa,
    0xf985ff30,0x01ff602f,0x88037fc4,0x1bfa04ff,0x5c0ffec0,0x4ccc01ff,
    0x09999999,0x3e005fc8,0x77ffec2f,0x85dcbffc,0xfc806ff9,0x7fd8004f,
    0x20037ec0,0x3ff44ffb,0x7d4ffea0,0x004d442f,0x3ea17fe2,0x8bfe202f,
    0x217fa7fb,0x3f202ff9,0x0fff2007,0xe813fe20,0x4ffa805f,0x4c03ff70,
    0xffffffff,0x17fc43ff,0x7dc7fb00,0x00ff50ef,0xf3007ff7,0xff8800df,
    0x00ffd403,0xff87ff70,0xa9ffd406,0xffff72ff,0x0fff809f,0x36007ff4,
    0x93ffccff,0x5ff301ff,0x1003fe40,0xff100dff,0x402ff409,0xff700ffd,
    0x7fffcc03,0x43ffffff,0x76e447fb,0x749f94cc,0x01bee2ff,0x7c003ff2,
    0x7fe4007f,0x005ff800,0xff88ffee,0xa9ffd405,0xffffcaff,0x3f605fff,
    0x07ffb14f,0x9ffffd30,0x7cc0ffe6,0x01ff202f,0x8803ffb0,0x17fa04ff,
    0x5c0dff10,0x4ccc01ff,0x3ffb9999,0xffd327ec,0x97ee9fff,0x17f20fff,
    0xe801ff60,0x2ffc007f,0x000ffb80,0x7fcc7ff7,0xa9ffd404,0x88bffeff,
    0xf101fffa,0x09fff9ff,0x3a1bca80,0x0bfe605f,0x54007fc8,0x7fc404ff,
    0x5017fa04,0x7fdc07ff,0x3fe60001,0xdfd17fc3,0x3ee7ff73,0xfd8fffa5,
    0x007fe804,0x54003ffa,0xff1001ff,0x8ffea009,0x7d405ff8,0x3dfff53f,
    0x5c0bff50,0x002fffff,0x401ff700,0x3ea02ff9,0x3fe2001f,0x027fc406,
    0xffd807ff,0x007fee00,0x263ff980,0x21ff50ff,0x4df52ff8,0x7fd2fffc,
    0x400dff00,0xfd001ffd,0x07fd800d,0xff87ff50,0xa9ffe406,0x3fe00fff,
    0xffff9107,0x3e600001,0x17fcc03f,0x800bff10,0x7fc407fe,0x801ff704,
    0x7fdc07fe,0x3fe60001,0x5fd9bee3,0x37d43fea,0x3ffbfffa,0x007ff802,
    0x26003ffa,0x7cc002ff,0x2ffa802f,0xfc807ff4,0x07ff53ff,0x7440ffc8,
    0x545fffff,0x3fa003ff,0x02ff9806,0x0d677fdc,0x8803ff60,0xfb7514ff,
    0x0dff009f,0x0001ffb8,0x5fc8ffe6,0x27fb8ffe,0x7fec45fb,0x7400cfff,
    0xffd000ff,0x001ff200,0x7d4037f4,0x427fdc2f,0xf53ffffb,0x1ffc805f,
    0x7fcdfff4,0x00bfee3f,0x3530ffdc,0x8802ff98,0x6c03fffd,0x3fe201ff,
    0x01bfff54,0xf7017fe0,0x7cc0003f,0x7cd3f23f,0xfb9bf21f,0xffffb505,
    0x3ffa019f,0x00dff000,0x20009ff1,0x7d401ffa,0x67ffc42f,0xffbffda9,
    0xb805ff53,0x93fea2ff,0xffb2fffa,0x27ff1003,0x30dffffa,0xfc8805ff,
    0x7e402eff,0x53fe201f,0x01dfffe9,0x2e02ffc4,0x260001ff,0x553f63ff,
    0xc97f60ff,0x7ffdc04f,0xffd82fff,0x05ff9802,0x0000ffb8,0xff3013fe,
    0xfffff505,0x27ff35ff,0x7e402ffa,0x903ffa1f,0x1ffd1fff,0x3e6dfb00,
    0xf35ffdef,0x1efe805f,0x803ff200,0xfe984ff8,0x037fc00f,0x80007fee,
    0x4ff63ff9,0x93fe0ffb,0x77dc03fd,0x541fffea,0xffc805ff,0x005fe802,
    0x3007fe40,0x3faa03dd,0x7ff31dff,0xfb00bfea,0xd837fc1f,0x806ffeff,
    0x4bfb1ffa,0x2ff99ffa,0x0007fe20,0x7c401ffb,0x05ff304f,0x7dc07ff8,
    0x3e60001f,0x7dcffa3f,0x7c7ff10f,0xb27e401f,0x3fff0bff,0x4037fc40,
    0x40002ffa,0x00003ff8,0x27ff5031,0x7f402ffa,0xe883ffc7,0x4403ffff,
    0xf0bfe4ff,0x405ff37f,0x74000ffa,0x27fc407f,0xfe809ff0,0x00ffdc07,
    0x6c7ff300,0x2e3ff53f,0x00df33ff,0x87ff87fb,0xe880fffc,0x6fd803ff,
    0x0dfb0000,0xffa80000,0x5405ff53,0x07ff44ff,0x00ffff98,0x0bfe37ec,
    0x05ff37fd,0x22003fe4,0x7fc405ff,0xb017fa04,0x7fdc03ff,0x3fe60001,
    0x7fcd3f23,0xe9dfefac,0x42fe803f,0x7f440fff,0xffcaacff,0x3ff8805f,
    0x5ff50000,0x0007ba60,0xffa9ffd4,0x81ffd102,0xfd105ffd,0x7fd405ff,
    0x3fe1ffc1,0x3202ff9a,0x7fd4007f,0x027fc403,0xffa80bfd,0x007fee04,
    0x323ff980,0x3bfffa5f,0x005ffff8,0x37fd43ff,0xfffffe88,0xf9004fff,
    0x7400001f,0x0ffff05f,0x54ffea00,0xb989beff,0xff883fff,0xffba9aef,
    0xf880ffff,0x70efd84f,0x05ff31ff,0x36003fe4,0x7fc400ff,0x2017fa04,
    0x3fee06ff,0x3fe60001,0xbd717ee3,0x1033b6a1,0xd30ff883,0x75c409ff,
    0x002dffff,0x000013fe,0xfff01ff7,0xff50001f,0x3ffffea7,0x203fffff,
    0xfffffffa,0x0effdbff,0x7cc07fe4,0xf33ffeff,0x03fe405f,0x100dff10,
    0x2ff409ff,0xb80ffec0,0x260001ff,0x01fea3ff,0x33bfe600,0xffffdffd,
    0x0bfee005,0x003ff700,0x84ff8800,0x50004ffc,0x7f6547ff,0x800cefff,
    0xceffffd8,0x54bffd10,0x3faa02ff,0x0bfe63ff,0x32007fc8,0xff8802ff,
    0x2017fa04,0xff706ff9,0x7fd40003,0x000bfe22,0xffffff30,0x019fffff,
    0x0037fc40,0x00001bfa,0x00883fe4,0x80732600,0x0c400018,0x04400000,
    0xf9017fcc,0x17fe600f,0xd027fc40,0x3ff600df,0x001ffb82,0xf907fee0,
    0xd950000b,0x17bdfffd,0x2fffa000,0xff303220,0x26000005,0x000003ff,
    0x00000000,0x4c000000,0x1ffa02ff,0x8007ff40,0x3f604ff8,0xfff8800f,
    0x000ffdc0,0xf981ffd0,0x6c00002f,0xf300004f,0xbffdbfff,0x00007fd8,
    0x00037f40,0x00000000,0x00000000,0x7cc0bfe6,0x4ffc805f,0x813fe200,
    0xf7002ffc,0x01ffb8bf,0x3ff6202e,0x405ffd04,0x0ffa0028,0xfffa8000,
    0x5544ffff,0x4c000001,0x0000002a,0x00000000,0x7cc00000,0x3ffd982f,
    0x002ffd40,0xfa813fe2,0xffb002ef,0xd00ffdc9,0xfffb9bdf,0x6fff440d,
    0x04fdcaab,0x0000bfe0,0x179d9710,0x00000000,0x00000000,0x00000000,
    0x5ff30000,0x1bffff22,0x980dff30,0x4ffccccc,0x67fffec0,0xb9ffec01,
    0x1ccccdff,0xfffffffd,0xfffb0019,0x005dffff,0x00003ba2,0x00000000,
    0x00000000,0x00000000,0x98000000,0xffff32ff,0x0efa801b,0x7ffffd40,
    0x7e4404ff,0x74403fff,0xfffff73f,0x332a27ff,0x44001bcd,0x001accba,
    0x00000000,0x00000000,0x00000000,0x00000000,0x5ff30000,0x8006af22,
    0xccc9800a,0x1002cccc,0x71003975,0x6666664c,0x0000001c,0x00000000,
    0x00000000,0x00000000,0x00000000,0x98000000,0x000002ff,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x000bfe60,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x1cc88000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x31000000,0x88ccc003,0x2200acce,0x009a8819,0x02ee9800,0x2666aa62,
    0x13ba0999,0x00f75400,0x76e44000,0x3bb24def,0x4005eeee,0x88002ee9,
    0x09980000,0x20000000,0x00000098,0x3f202a80,0x5ffa803f,0x19fffff1,
    0x3ee1ff50,0x0004ffff,0x6441ffd4,0xffffffff,0x017fe6ff,0x0017fd40,
    0x3fffee00,0x3ff67fff,0x4007ffff,0x3000ffff,0x260005fd,0x0ceffffd,
    0x3fffff60,0x204fffff,0x3effffd9,0xfeeca800,0x1bff606f,0x6c037fcc,
    0xffdd12ff,0xffa85fff,0xffffffc8,0x3ea0005f,0x77ffc43f,0xffffffdd,
    0x40017fe6,0x00002ffa,0x2b3fffea,0x3332a5cc,0x22007ffc,0x7001ffff,
    0xf70005ff,0xdfffffff,0x3ffff601,0x04ffffff,0xfffffff5,0x3fee00bf,
    0x306fffff,0x3a07ffff,0x3fe201ff,0x3fffaa07,0x3ffbfea2,0x1fffa88b,
    0x87ff5000,0x7ec43ffd,0x17fe09cf,0x017fd400,0x05ffd000,0x001ffa00,
    0x5c00dffb,0x7ec002ff,0xfeb9acff,0xaffd81ff,0x1aaaaaaa,0x89bfffa8,
    0x6c05ffea,0xaaccefff,0x7ffff302,0xa813fee0,0xffc804ff,0x07bffea7,
    0x40017fea,0x3fe23ffa,0xf0dff105,0x3ea000bf,0xf300002f,0x7f4000ff,
    0x002a8007,0x30017fdc,0x3fa01fff,0x006fd85f,0xd103fff0,0x3ff603ff,
    0xffe8001e,0x0fff100e,0xd800ffec,0x1fff53ff,0x8003ffc0,0x3fea3ffa,
    0xf03ff603,0x3ea000bf,0xf500002f,0x7f40009f,0x33000007,0x337ff933,
    0xfd813333,0x3ffa201f,0x40037ec0,0x3e603ffa,0x05ffa85f,0x6c015400,
    0x6ff882ff,0x557fee00,0x7fe403ff,0xa9aa8800,0x0bfee3ff,0x7fc0ffd8,
    0x504ccc05,0x4d5445ff,0x0bfee000,0x407fe800,0x19999998,0x3fffffe0,
    0xffffffff,0x201bfe64,0x37ec4ffc,0x007ff400,0xdfd03ffe,0x20000001,
    0xffb85ff9,0x5bfe6003,0x7e402ffa,0xfffb301f,0x547fffff,0x1bfe04ff,
    0xffc817fe,0x64bfea0e,0x003fffff,0x40005ff7,0x7fec07fe,0x3e07ffff,
    0xffffffff,0x2e4fffff,0xff9803ff,0x20037ec6,0x36205ff8,0x3fe61fff,
    0x40000003,0x7ff40ffe,0x57fe6000,0x7dc02ffa,0xffffb82f,0x43ffffff,
    0xffc82ffe,0xf905ff84,0xaffa81df,0xfffffffe,0x02ffb803,0xb01ffa00,
    0x0fffffff,0x7fe4cccc,0x0999999b,0x7c007ff2,0x0037ec7f,0x74c0ffe6,
    0x3ee2ffff,0x0000001f,0xff127fdc,0x3ffd800b,0xfb805ff5,0x577fdc1f,
    0x50fff260,0xfd97bfff,0x217fe0df,0xfa80effc,0xf912ffff,0x777641ff,
    0xeeeeffee,0x7f402eee,0x4cccc407,0x3ee007ff,0x1ffb002f,0xfb1ffa00,
    0x0159999f,0x3ee0ffea,0x363ffdff,0xbddd957f,0x88000019,0x0bfee7ff,
    0xffebaa98,0x900bfea6,0x77fc41ff,0xd87ff500,0xffffffff,0xc8bff00c,
    0xff500eff,0x5ffb01df,0x7fffffec,0xffffffff,0x003ff403,0xf7003ff4,
    0x1ffe005f,0x360ffe80,0xffffffff,0x117fdc1d,0xff15fffb,0x7ff7ff49,
    0x03ffffff,0x97fec000,0x7fdc07fe,0x3ea1efff,0x23ff402f,0x3ea02ffc,
    0x267fea3f,0x7c01accc,0x03bff25f,0x700fffa8,0x666547ff,0xcccdffec,
    0x7f401ccc,0x07fe8007,0x400bfee0,0x3f6007ff,0x3bbbb21f,0x21fffffe,
    0xffd31ffb,0xe97fe21d,0xbaacffff,0x2201fffd,0x33fea000,0x7dc04ff9,
    0xffa82cef,0xd17fe602,0x3ffa80ff,0xf8001bf6,0x01dff95f,0x2602ffa8,
    0x7fdc04ff,0x1ffa0002,0x801ffa00,0xff002ffb,0x07ff400f,0x27ffe980,
    0xfffb9ffb,0xff27fcc4,0x37fdc05f,0x2004ffc8,0x01ffcffe,0xf5007fdc,
    0x3ffa205f,0x2a037fc0,0x0bffa3ff,0x7e6ffc00,0xffa800ef,0x013fe602,
    0x40005ff7,0xfe8007fe,0x0bfee007,0xd003ff40,0xfe8800ff,0xffdff51f,
    0x47ff305f,0xffe807ff,0x17fffc41,0x6ffffb80,0x200ffa80,0x989aeffa,
    0x7c43fffb,0x1ffd405f,0xdddffff7,0x3fe0579d,0x5002fffe,0x7fcc05ff,
    0x017fdc04,0x000ffd00,0x7dc00ffd,0x1ffb002f,0x001bfe00,0x7fccffee,
    0xff500eff,0x6403ff45,0x7ffc42ff,0xfff1004f,0x1ff5005f,0x7ffffd40,
    0x983fffff,0x7fd404ff,0x7ffffec3,0x41efffff,0x1fff9dff,0x202ffa80,
    0x7dc04ff9,0x3fa0002f,0x07fe8007,0x400bfee0,0xf9802ffc,0xffa8005f,
    0x809fff14,0x3ff61ffc,0x41ffdc00,0x2005fffc,0xd3006ffd,0x7ffd401d,
    0x00ceffff,0xfa80bff1,0x33ffa23f,0xffffdccc,0x7d57fe0f,0x7fd401ff,
    0x013fe602,0x40005ff7,0xfe8007fe,0x0bfee007,0x402ffd40,0xb8002ffc,
    0x01ffe2ff,0x3ff91ffe,0xf01ffc80,0x7ec009ff,0x5400002f,0x400332ff,
    0x7fe406ff,0x8807ffa3,0x97fe3ffe,0x2a00fffb,0x3fe602ff,0x017fdc04,
    0x000ffd00,0x7d400ffd,0x3ffe005f,0x01bfe200,0xf707ff40,0x27fd407f,
    0xfd013fea,0x0fff601f,0x003ffcc0,0x017fd400,0x900ffe80,0x3fe67fff,
    0x25ffa804,0x77fe45ff,0x405ff500,0x7dc04ff9,0x3fa0002f,0x07fe8007,
    0x003ffe20,0x44077fdc,0xc8002ffe,0x7ffc45ff,0x80fff880,0xff701ffe,
    0x007ffc09,0x0017ff44,0x7d403bd5,0xff70002f,0x7ffff709,0x2e013fea,
    0x217fe3ff,0xfa80effd,0x13fe602f,0x0005ff70,0x74003ff4,0x7ff4007f,
    0x42a999cf,0xaacfffe8,0xb885ffec,0xffba9999,0x7fff906f,0x07fff733,
    0x4c2bffea,0xd880fffc,0xfe9803ff,0x3fe2004f,0x0bfea06f,0x67ffc400,
    0xffaffda9,0x405fff33,0x3fe1fff9,0x50bffd05,0x7fcc05ff,0x017fdc04,
    0x7d555544,0x11aaaaff,0xfff55555,0x4c035555,0xffffffff,0xffffd884,
    0xf104ffff,0xffffffff,0x7ffe401b,0x403fffff,0xfffffffb,0x7ff6c1ef,
    0x3ffba04f,0x7cc006ff,0x3fea06ff,0x3fea0002,0xf8afffff,0x3bfffa3f,
    0xfffecbcd,0xe882ffc2,0x17fd45ff,0xb809ff30,0xff9802ff,0xffffffff,
    0xffff35ff,0xffffffff,0xfffc880b,0x3ae03fff,0x202dffff,0xeffffff8,
    0xffd5001d,0x2a005bff,0x03effffe,0xf803dfff,0x0003ffff,0x7d405ffb,
    0x7540002f,0x3fe1dfff,0x3ffff623,0x82efffff,0x3fe605ff,0x80bfea4f,
    0x7dc04ff9,0xfff9802f,0xffffffff,0xfffff35f,0xbfffffff,0x004cc400,
    0x98800260,0x98000199,0x00cc0000,0xcc8004d4,0x4c0000ab,0x00e64c00,
    0x80018800,0xacddcca8,0x00000001,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x88000000,0x980001a9,0xa9880019,
    0x00000009,0x35300000,0x19a98801,0x00000000,0x00000000,0x00009988,
    0x00000000,0x00013300,0xffffb800,0x93001dff,0x7bfffffd,0x7ffff540,
    0xffd84fff,0xffffffff,0x7009ff30,0x76cc05ff,0x0befffff,0x3fffffae,
    0xffff01df,0xffffffff,0x27fec1ff,0xfb37fd40,0x7fdc00bf,0xfffec886,
    0x7ffb01ef,0x337fc400,0x7c4007ff,0x3ffea02f,0x3ffff602,0x0fffffff,
    0x3fffffe2,0x5c03ffff,0xffffffff,0xfffe887f,0x85ffffff,0xfffffffd,
    0x9ff30fff,0x205ff700,0xfffffffc,0x3ff61fff,0x3fffffff,0xfffffff8,
    0x0fffffff,0x8807ffe2,0x3fe21fff,0x3ffd001f,0xffffffa8,0xffa83fff,
    0x8ffee005,0x26003ff8,0xffea82ff,0x3ff602ff,0xffffffff,0x2b7ffa0f,
    0x1fffca88,0x57bfffb0,0xfd0fd953,0x533337df,0x55555099,0x21ffd555,
    0xfb804ff9,0x7fff442f,0xfeca9abd,0x2626b321,0x641fffdb,0xcccccccc,
    0xfb86ffec,0x13ff205f,0x2e01bff2,0x7ffcc5ff,0xfffda9ac,0x007ffc40,
    0x3e21ffd8,0x3fe6004f,0x3ffffaa1,0x3ff602ff,0xaaaaaaab,0x40dff50a,
    0xffa83ffd,0x3ee0c02f,0xb000006f,0x13fe61ff,0xfb0bfee0,0x009803ff,
    0x000fffa0,0x7407ffe2,0x6ff982ff,0x405fff10,0xec80fff8,0xb0bffb00,
    0xff1005ff,0x4009ff0d,0xfff91ffa,0x405ffb5f,0x2e001ffd,0x3fe602ff,
    0x001ffe85,0x0002ffd8,0x261ffb00,0xffb804ff,0x003bfe62,0x17fee000,
    0x813ff600,0x7f40fff9,0x1bfee02f,0x0004ffb8,0xff50dff1,0x07ff500b,
    0x7d4009ff,0x6c7ff50f,0x3ff602ff,0x0bfee001,0x7dc3ffa8,0xffd0005f,
    0x36000001,0x09ff30ff,0x7f45ff70,0x3000002f,0xfa8009ff,0x4ffc806f,
    0x3a017fee,0xfff883ff,0x1ffe0000,0xb003ffe2,0x0bfd03ff,0x02e3fdc0,
    0x7ec05ffb,0x3fe2001f,0xd03ff606,0x360003ff,0x000003ff,0x3fe61ffb,
    0x32ffb804,0x00000dff,0x10017fd4,0xf1003fff,0x1fff13ff,0x81fff500,
    0x40003ffc,0x5ffb07ff,0xe837fc40,0x1fee005f,0xd80bff60,0x7f4001ff,
    0x3ff621ef,0x0006ff85,0x000fffee,0x4c3ff600,0xffb804ff,0x0007ff72,
    0x003ff400,0xa8013ff2,0x02ffdeff,0xf893ff60,0x7c40006f,0x0bff506f,
    0xfd81ffd4,0x2e0ffc46,0x2ffd807f,0x0007ff60,0xf59fffb1,0xbff30bff,
    0xfffd8000,0x3600002e,0x09ff30ff,0x3f25ff70,0x4400002f,0x2001efea,
    0xd8006ffa,0x4005ffff,0xff90fff9,0xffb80005,0x40fff104,0xdfb01ffd,
    0x7e43ffa8,0x02ffd806,0x40007ff6,0x3ffffffc,0x0009ff50,0x9fffff90,
    0xffd80001,0x7009ff30,0x07ff65ff,0x3bbbbbb2,0xfffffd81,0x3fa2000d,
    0xff88001f,0xfc8000ff,0x005ff8cf,0x007ffc40,0x3fe05ffb,0xfb1ff206,
    0x806fc8df,0x3f602ffd,0xeeeeeeef,0xffff304e,0xff7019ff,0x36600009,
    0x00cfffff,0x261ffb00,0xffb804ff,0xfd01ffd2,0xb03fffff,0x3bffffff,
    0x013ff200,0x00fffe80,0xfdfff880,0x7ec0001f,0x27fd403f,0xf701ffd4,
    0x0ffffc4f,0xffb00bfb,0x7fffec05,0x85ffffff,0xffdcfffa,0x27fd41ff,
    0x3f260000,0x8001ffff,0x9ff30ffd,0x3a5ff700,0xcccb80ff,0x99881ffe,
    0x03fffeba,0x00037fcc,0x009ffff7,0x13fffee0,0x0bff9000,0xf90fff10,
    0x53fdc01f,0x7ec9ffdf,0x02ffd805,0x33337ff6,0x7e42cccc,0x3ffa61ef,
    0x017fe60f,0x7fdc4000,0x7ec000ff,0x009ff30f,0x3ff65ff7,0x01ffb801,
    0x807ffe60,0x10001ffe,0x03ffffff,0x03fffa00,0x06ffc800,0xff07ff60,
    0xb0ffa80d,0x7f4df97f,0x02ffd804,0x98007ff6,0xfe880eff,0x01bfe25f,
    0xffd10000,0x0ffd8009,0xf7009ff3,0x00bfee5f,0x70007fee,0x3ff209ff,
    0x3ffa0004,0x0006ffaa,0x40009ff7,0x2000effc,0x3fe64ffa,0xf87fd403,
    0xfd1ffa9f,0x05ffb009,0x9000ffec,0x7fc403ff,0x0007ffc7,0x1bfe6000,
    0x261ffd00,0xffb805ff,0x700bff51,0xf88003ff,0x06ff985f,0xd97fee00,
    0xfa8004ff,0xff90003f,0xff88001d,0x3003ff27,0x7cdf53ff,0xb007ff4f,
    0x7fec05ff,0x01ffa001,0xffd83ffa,0xf8000004,0x3fe2007f,0x6402ffc7,
    0x1fff10ff,0x001ffb80,0x7f427fcc,0xff10001f,0x0fffcc3f,0x00ffea00,
    0x003bff20,0xff8ffec0,0xdaff9806,0x7fdff24f,0x02ffd802,0xf8007ff6,
    0x3ffc00ff,0x0007ffe6,0x05ff8800,0xff1bfea0,0x47ff801f,0x7dc05ffc,
    0x7fdc001f,0x0027fe42,0xf909ffb0,0xffa800df,0x77fe4003,0x3fee0000,
    0x8803ff9c,0x261ffaff,0x802ffaff,0x3f602ffd,0x3ff6001f,0x21bfea03,
    0x0c02fffd,0x44ffd800,0x3ffd880b,0xf9027fe4,0xdfff887f,0x003ff700,
    0xf307ffcc,0x2a0001df,0xff880fff,0x3fea003f,0x37ff2003,0x7fc40000,
    0x8800ffce,0xff87fdff,0xfd801ffd,0x07ff602f,0x9dfffa80,0x2fffc999,
    0xceffff88,0x267fcbaa,0xa99aabdf,0x7c0efffb,0xfffcabcf,0xadfff886,
    0x06ffda99,0x379ffff5,0x223ffd53,0xda99999a,0x7ff41fff,0xccccccce,
    0x3fe21ccc,0x3ffea02f,0x07ff5000,0x333ffee0,0xcccccccc,0x7fffec00,
    0x3fffe006,0x1ffffc84,0x3b333322,0x24cccdff,0x5c001ffd,0xffffffff,
    0x3f6203ff,0xffffffff,0x3ffffe67,0x0effffff,0xfffffff8,0xfff501ef,
    0x3dffffff,0x7ffff4c0,0x51ffffff,0xffffffff,0xfff985df,0xffffffff,
    0x3ff62fff,0x05ffd805,0x2007ff50,0xfffffffc,0x01ffffff,0x01ffffdc,
    0x303ffff0,0x7c41ffff,0xffffffff,0x3ff67fff,0xffd98001,0x000cffff,
    0xbdfffdb5,0x7ffec457,0x02dfffff,0x3bffff6a,0xffec8804,0x2e003eff,
    0xdffffffe,0x3ffffea2,0xff302dff,0xffffffff,0x3ea5ffff,0xff9801ff,
    0x3ffa802f,0xfffff900,0xffffffff,0xffff8803,0x1fffa000,0x220fffe8,
    0xffffffff,0x3f67ffff,0x4c40001f,0x09800009,0x02666600,0x00006600,
    0x31000033,0x4ccc4013,0x00000001,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0xff100000,0x1ffb80df,
    0xa80bffe6,0x3fe22fff,0xffffffff,0xff70ffff,0x877fd405,0xfffffffc,
    0x5fffffff,0xfffffff3,0x265fffff,0xffb804ff,0xffffff32,0x3f6019df,
    0xffffffff,0xffff31ff,0x0059bdff,0x3fe87fa8,0xffffffb8,0xf8002def,
    0x80001fff,0xf705fffd,0xbdffffff,0x3fffe203,0x987fee02,0x3f605fff,
    0x3ffe22ff,0xffffffff,0x5ff70fff,0xc87ffe20,0xffffffff,0x35ffffff,
    0xffffffff,0x3e65ffff,0x2ffb804f,0xfffffff3,0xffb09fff,0xffffffff,
    0x3fffe63f,0x0dffffff,0xff0df700,0xfffff705,0x01dfffff,0x13fffea0,
    0xffff5000,0x3fffee0b,0x0effffff,0x037fffc4,0x7fcc3ff7,0xfff880ff,
    0x6666643f,0xffcccccc,0x205ff70f,0x554c2ffe,0xadffcaaa,0x5511aaaa,
    0x55bff955,0x13fe6155,0x7ccbfee0,0xffdbaadf,0x5ffec2ff,0xaaaaaaaa,
    0x555bff30,0x07ffffb9,0xff88bf90,0xaacffb81,0x06fffcba,0x0dffffb0,
    0x7fff4400,0x59ff705f,0xdfff9755,0x7ffffc41,0x543ff701,0xfb83feff,
    0x30003ffd,0x17fdc9ff,0x5001ffec,0xf50007ff,0x27fcc07f,0xf997fdc0,
    0x8fff904f,0x26000ffd,0xffb104ff,0x44fd801f,0xffb80ff9,0x03fff102,
    0x3ffbbff0,0x2bff2000,0x5ff705ff,0x897ffa20,0x705ffcff,0x677d43ff,
    0xffafe86f,0x3ffb0003,0x3ee17fdc,0x7fd4005f,0x3ffa8003,0x2013fe60,
    0x9ff32ffb,0xd83ffe20,0x3e6000ff,0x27fe404f,0xff313f60,0x405ff701,
    0x7d403ffb,0x004ffaaf,0xff8cff98,0x405ff705,0x3fe27ff8,0xfb81ffcc,
    0x3e7bee1f,0x3e3fe61f,0xff88004f,0xf317fdc5,0xff5000df,0x7ff50007,
    0x4027fcc0,0x9ff32ffb,0xfb0ffec0,0x7fcc001f,0x0fffc404,0xddffddd5,
    0xdddffddd,0xa80bfee5,0x7fec03ff,0x8006ff88,0x5ff88efe,0xd805ff70,
    0x39ff10ff,0x3ff70bff,0x24feb7dc,0x009fd5fc,0xfb83ffb0,0x01fff12f,
    0x007ff500,0x4c07ff50,0xffb804ff,0x7409ff32,0x03ff60ff,0x804ff980,
    0x3fee3ffc,0xffffffff,0xf73fffff,0x0ffe405f,0xffd97fe0,0x4bfee001,
    0xff705ff8,0x11ffc805,0x03ffa9ff,0xb7dc3ff7,0x74bfe6fc,0x7fc4004f,
    0xfd2ffb85,0x3ea0003f,0xffa8003f,0x013fe603,0x7fccbfee,0xd8dff304,
    0x3e6000ff,0x4ffa804f,0x2ffeeaa6,0xaaefdaaa,0x205ff70a,0x7d407ff8,
    0x013fee3f,0xff127fc4,0x00bfee0b,0x3fe21ffb,0xfb89ff54,0x7cdbf21f,
    0x3fa7fa9f,0x0ffe4005,0x7fe57fdc,0x3fea0002,0x3ffa8003,0x2677fe60,
    0xfc999999,0x309ff32f,0xffd85ffd,0x99999999,0x2013fe60,0xff305ff9,
    0xf704fd81,0x7fdcc45f,0x07fec01e,0x3600dff1,0x17fe20ff,0xf1017fdc,
    0xd27fc4ff,0x0ffdc1ff,0x667f4df9,0x8017fa4f,0xff706ff8,0x80009ffb,
    0xa8003ffa,0x3fe603ff,0xffffffff,0xff32ffff,0xfffdb99d,0xfffffb07,
    0x4cdfffff,0xff8804ff,0xfb0ff306,0x3fffee09,0x004fffff,0x3ffd0dff,
    0x442ffb80,0x5ff705ff,0xf11ffec0,0x727fd49f,0x737ec3ff,0x7ec3ffff,
    0x0bff2006,0x27ffffdc,0x0ffea000,0x80ffea00,0xfffffff9,0x2fffffff,
    0xfffffff3,0x3ff603bf,0xffffffff,0x2013fe66,0xff507ff8,0x3ee07fd0,
    0xffffffff,0x3fea00df,0x203ffb83,0xff885ff8,0x985ff705,0x7c46ffea,
    0xb87ff44f,0x897f61ff,0x37ec6fff,0x206ff880,0x2ffebffb,0x0ffea000,
    0x80ffea00,0xaaaadff9,0x2ffdaaaa,0xffb9dff3,0x4ffec07f,0x09999999,
    0x22013fe6,0x0df706ff,0x3fee05ff,0xffcbaaac,0x3ffb01ff,0x6c0dff30,
    0x5ff880ff,0xffffff70,0x881bffff,0x9ffdc4ff,0x17f61ffb,0x6fd87ffb,
    0x405ff900,0xfff9affb,0x7ff50001,0x07ff5000,0x5c027fcc,0x89ff32ff,
    0xffb04ffc,0x27fcc001,0xc82ffcc0,0x80ffc45f,0xfb102ffb,0x81bfe0df,
    0xffa81ffe,0x20bff102,0xfffffffb,0x9ff102ef,0xff76ff88,0x3ea2ff43,
    0x403fec0f,0x7dc06ff8,0x01dff72f,0x007ff500,0x4c07ff50,0xffb804ff,
    0xfd09ff32,0x01ffb03f,0x4027fcc0,0xfff34ffa,0xffffffff,0x7dc9ffff,
    0x07ffc02f,0x26677fea,0x43ffd999,0x9999eff8,0x99dffa99,0x2ab3fee1,
    0x4ff8801a,0xffbaffc8,0x02617fa1,0x3f201ff2,0x17fdc02f,0x5000bffb,
    0xf50007ff,0x27fcc07f,0xf997fdc0,0x86ffa84f,0x26000ffd,0xffd804ff,
    0xffffff32,0xffffffff,0x017fdc9f,0xffb07ff6,0xffffffff,0xfff98dff,
    0xffffffff,0xf71fffff,0xff10005f,0xf7dff109,0x002ffc3f,0xff880ff9,
    0x22ffb806,0x4003ffe8,0xa8003ffa,0x3fe603ff,0x32ffb804,0x3ffa09ff,
    0x0007fec1,0xf9809ff3,0x50ffa07f,0x17fdc0ff,0xff07ff60,0xffffffff,
    0x7cc1ffff,0xffffffff,0x1fffffff,0x10005ff7,0x3ff209ff,0x13fe1ffd,
    0x6407fc80,0xffb803ff,0x00fffcc2,0x0007ff50,0x7cc07ff5,0x2ffb804f,
    0x3ea09ff3,0x007fec5f,0x4409ff30,0x3fe03ffe,0xf7037dc2,0x3ffc405f,
    0x2aab7fea,0xffdaaaaa,0x2aaaaa23,0xeffbaaaa,0x5ff70aaa,0x09ff1000,
    0x87ffffe2,0x3f2004ff,0x0fff100f,0x2a0bfee0,0xf5000fff,0xff50007f,
    0x027fcc07,0xff997fdc,0xd87ffa04,0x3e6000ff,0xdfff504f,0x320ffc40,
    0x0bfee05f,0x3227fec4,0xff9801ff,0x5ff88006,0x0005ff70,0x7ec09ff1,
    0x9ff11fff,0x807fe400,0xf7003ffc,0x1bff205f,0x201ffd40,0xffcaaaa8,
    0xf30aaaad,0x5ff7009f,0xfb813fe6,0x2afff65f,0x0aaaaaaa,0xb955bff3,
    0x401dffff,0x27ec0ff9,0x5559ff70,0xf0dfff99,0x7ffc00ff,0x2ffc4000,
    0x8002ffb8,0x3e604ff8,0x9ff11fff,0x40ffdc00,0x2e007ff8,0x3ffa02ff,
    0x03ffa804,0x7fffffcc,0x32ffffff,0xff7009ff,0xf013fe65,0x3fff63ff,
    0xffffffff,0xffffff31,0x3009ffff,0x409fd0ff,0xfffffffb,0x7d40cfff,
    0x3ff2004f,0x2ffc4003,0x8002ffb8,0x7ec04ff8,0x09ff11ff,0x640ffdc0,
    0x3ee003ff,0x3ffe202f,0x01ffd402,0x3fffffe6,0x32ffffff,0xff7009ff,
    0x7013fe65,0x3fff69ff,0xffffffff,0xdfffff31,0x7d40059d,0x2e03fe87,
    0xdeffffff,0x03ff900b,0x0037fcc0,0x7dc17fe2,0x0000002f,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x4c006620,0x55000003,0x00355100,0x555300aa,0x55300015,
    0x2aa20013,0x54c40009,0x4cc409aa,0x9884cc00,0x8809a880,0x04d54419,
    0x105504c4,0x33260015,0x000cc401,0x20040333,0x20004ff9,0x1effffeb,
    0x0009ff30,0x302ffb80,0x1bfffffd,0xb31bff60,0xdfffffff,0xfffd9803,
    0xf700efff,0x01dfffff,0xfffffea8,0x0bfea2ff,0xdfb4ff98,0x1fffff5c,
    0x7fe43fea,0xa7e43fff,0xff71fffd,0x7ff5007f,0x803ffc80,0xffb05ffa,
    0x013fe605,0x3ffffa60,0xe884ffff,0x80000dff,0xfb81effd,0xffffeeff,
    0x1ffffcc1,0xfffffff7,0x3ee03fff,0xffffffff,0x7fffec40,0xb02fffff,
    0xfffdffff,0x017fd45f,0x5bf69ff3,0xfffffffc,0x3fa7fea3,0x23ffffff,
    0xffffbcfc,0x0fffff9c,0x201ffd40,0xfd806ff9,0xffffa81f,0x004ff980,
    0x511cffe8,0x3f605fff,0xd10001ef,0xff701dff,0x46ffb81d,0x2e3ffff9,
    0xfb5109bd,0x9fff70ff,0x3606d4c3,0x3f261dff,0x6ffd40ff,0x3ea0a881,
    0x53fe602f,0x12ffdefd,0x7fd4dff9,0xff932efe,0x57f7f21f,0xf88fdefb,
    0x1ffd402f,0x100fff40,0x3fe60dff,0x4ff983ff,0x81ffe400,0x3f206ff8,
    0x74c002ff,0x1bfe04ff,0x7f43ffb8,0x7fc000ef,0x07ffe21f,0x205ffa80,
    0x7fec5ffb,0x0bfea000,0xffb4ff98,0x3ffd01df,0x203bffea,0xfff92ffd,
    0xf8fffe61,0x1ffd403f,0x7027fdc0,0x7ff407ff,0x04ff984f,0x32037fc0,
    0x3fea02ff,0xfff5003f,0x017fdc07,0x00aa1bfe,0xfb17fe40,0xffe8007f,
    0xb07ff400,0x7d4001ff,0x53fe602f,0xf900effd,0x03bfea5f,0xffc9ffdc,
    0xfd1bfe64,0x03ffa80b,0x3a07ff88,0x3fe600ff,0x04ff983f,0x3017fe20,
    0xff9809ff,0x7ffdc04f,0x007fec02,0x00001ff6,0x37fc7ff5,0x017fe200,
    0xffc8bfee,0x5ff5001e,0xfda7fcc0,0x4ffea01f,0x3e602ffa,0x4c1ff94f,
    0x02ff43ff,0x6c00ffea,0x5ff882ff,0x981fff80,0x3ea004ff,0x05ff804f,
    0x80dffe88,0xe800effd,0xaaaaaaff,0x000ffeaa,0xdcccaa98,0x0bff13ff,
    0x803ff980,0x3fa23ffa,0x2a00bdff,0x3fe602ff,0x5000ffb4,0x7fcc05ff,
    0xff98ff94,0xffcaff42,0xffffffff,0x7d45ffff,0x02ffb85f,0xf9837fcc,
    0x3fe6004f,0x006ff805,0x7443bff6,0xff000dff,0xffffffff,0x4003ffff,
    0xffffffea,0x9ff53fff,0x02ffa800,0x6c44ff98,0x82dfffff,0x3e602ffa,
    0x000ffb4f,0x7cc05ff5,0xf98ff94f,0xfcaff42f,0xffffffff,0xe85fffff,
    0x03ff40ff,0x4c07ffa6,0x3e2004ff,0x07fe806f,0x54fffe60,0x3e002fff,
    0xeeeeeeff,0x000eeeee,0x99bdfff9,0x3ea7ffb9,0x7fdc003f,0x03ff9802,
    0xbfffffb5,0x3017fd41,0x01ff69ff,0x980bfea0,0x98ff94ff,0x9aff42ff,
    0xffcaaaaa,0x82aaaaad,0x3fe62ffb,0xfffee884,0x013fe603,0x5409ffb0,
    0xfa800fff,0x7ffcc2ff,0x00ffd004,0x3dff5000,0x7ccffea0,0x7fcc005f,
    0x02ffa803,0x25fffda8,0x3e602ffa,0x000ffb4f,0x7cc05ff5,0xf98ff94f,
    0x202ff42f,0x22003ffa,0x03ff25ff,0x0037ffe2,0x98009ff3,0xcaabefff,
    0xc807ffff,0xfd101fff,0x1ffb00bf,0xffc80000,0x44ffea02,0x7c4006ff,
    0x1ffc805f,0x47ffe600,0x3e603ffa,0x000ffb4f,0x7cc05ff5,0xf98ff94f,
    0x202ff42f,0x6c003ffa,0x05ff88ff,0x7cc00351,0xfea8004f,0xeeffffff,
    0x77fec06f,0x77fec400,0x00fff200,0xfb065c40,0x1ffdc01f,0xf8005ffd,
    0x3fe200ff,0x2ffc8007,0x3a20bff3,0x00ffb4ff,0x4c05ff50,0x98ff94ff,
    0x02ff42ff,0x5000ffea,0x05ff57ff,0x27fcc000,0xbdd97000,0x4417fa39,
    0x2000dffe,0xf101fffc,0xfd0003ff,0x07ff61ff,0xa8ffff62,0x2e001fff,
    0x3ff605ff,0x1ffe8002,0xfd10fff1,0x01ff69ff,0x980bfea0,0x98ff94ff,
    0x02ff42ff,0x2000ffea,0x207fdeff,0x88888888,0x027fcc08,0x3ff88000,
    0x004fff98,0x205fff70,0x109cfffc,0x7fd43753,0x5dff73ff,0xffffd731,
    0xacfffd87,0x740fca99,0xea89aeff,0x9acd86ff,0x6ffdb989,0x54d77ff4,
    0xfb4ffeff,0x5ff5000f,0xfca7fcc0,0x3a17fcc7,0x1ffd405f,0x7fffe400,
    0x3ffff604,0x7cc6ffff,0x5000004f,0xfffb85ff,0x7fd40002,0xffff904f,
    0x45ffffff,0x3a2ffff9,0xefffffff,0x7ec43ff9,0xffffffff,0x7ffff4c0,
    0xf80dffff,0xffffffff,0x7ffcc0ef,0xff8dffff,0x5000ffb4,0x7fcc05ff,
    0xff98ff94,0x2a02ff42,0xf98003ff,0x3f601fff,0x6fffffff,0x00027fcc,
    0x2a37f440,0x00001fff,0x2607ffd3,0xfffffffd,0x22ffe41d,0x3effffc8,
    0x7ed40ffe,0x204effff,0x2effffec,0x3fffff60,0x3a603eff,0x3fe3ffff,
    0x5000ffb4,0x7fcc05ff,0xff98ff94,0x0002ff42,0x037ff400,0x2eeeeeea,
    0x27fcc3bb,0x7fec0000,0x0000ec81,0x8802ec40,0x0c400999,0x40000620,
    0x01980019,0x04cccc40,0x00033100,0x00000000,0x00000000,0x4c000000,
    0x200004ff,0x0004ffea,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x7cc00000,0xaaaaaaef,0x65d542aa,0x00cfffee,
    0x88000000,0x4cc00099,0x26666660,0x22199999,0x99880199,0x000ee800,
    0x7776c000,0xeeeeeeee,0x417bb26e,0x9dd90000,0x75c2f75c,0x6ec000de,
    0xdddddddd,0xdddddddd,0x4c000000,0xffffffff,0x3fe26fff,0x01efffff,
    0x20000000,0x26002ff9,0xffff13ff,0xffffffff,0x80fffe21,0xf802fff8,
    0xffb8000f,0x7ffff403,0xffffffff,0xd91bff67,0x262019ff,0xfb93ff61,
    0x1fff706f,0x7fc7ff90,0xffffffff,0xffffffff,0x4c000000,0xffffffff,
    0x3fe26fff,0x0002bcde,0xf8800000,0x3fea003f,0xffffff12,0x41ffffff,
    0xfb00fffa,0x1fd0109f,0x7ffc4008,0x3332e00f,0xcccccccc,0xd97ff24c,
    0x81ffffff,0x93ff67fc,0x3e606ffb,0x3ffea0ff,0x9999991f,0x99999999,
    0x00019999,0x00000000,0x00000000,0x2004ff80,0x26660ffb,0xffc99999,
    0xa86ffc85,0x41bb06ff,0x901b627e,0x0009fdbf,0xaaffe400,0xfffdbeff,
    0xff937ec1,0x202ffd47,0xff90ffd8,0x000007ff,0x00000000,0x00000000,
    0x5fe80000,0x07fc8198,0x403bfe60,0x3fe23ffe,0x3fff880f,0x07ffeafb,
    0x7fd47fcc,0xf7000001,0xf71ff69f,0x9ff737ff,0xff51ffe4,0x5c22200b,
    0x0002ffff,0x00000000,0x00000000,0x6c000000,0x20ffc46f,0xfd1006fd,
    0x7ffc403f,0x4405ffb1,0xfdfedffb,0x93f600cf,0x333106fd,0x33333333,
    0xea7fdc33,0xffffa86f,0x3fee0fff,0x0013fe62,0x0005ffd8,0x00000000,
    0x00000000,0xc8000000,0x227fdc7f,0xffb005fe,0x5dff5007,0x2e2009ff,
    0x400cffff,0x3fe60ffa,0xfffffe83,0x7fffffff,0x165cffea,0x1ffffe98,
    0xff317fdc,0x00980009,0x00000000,0x00000000,0x00000000,0x7f41ff70,
    0x4027fc7f,0x32005ffc,0x4006ffff,0x803effea,0x0ffc83fe,0x7ffffff4,
    0x27ffffff,0x4c002ee9,0x43dd501a,0x00003ee8,0x00000000,0x00000000,
    0x00000000,0x447fea00,0x3fe2ffff,0x037fd403,0x00ffff40,0xefeefea8,
    0x0ff703ff,0x33113fe2,0x33333333,0x00000333,0x00000000,0x00000000,
    0x00000000,0x00000000,0x5cbfe200,0xff14fddf,0x07ffc405,0x3fffe200,
    0x9fff4401,0x43fff77d,0x3ee03ff8,0x0000001f,0x00000000,0x00000000,
    0x00000000,0x00000000,0x3fe00000,0x2ff55fb3,0x3fa00ff9,0xffe8002f,
    0x77400fff,0x46d89fa1,0x6fe806fc,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x233fa000,0xaaff88ff,0x13ff207f,0x2f3ff200,
    0x740406ff,0x004cc087,0x00000cc4,0x00000000,0x00000000,0x00000000,
    0x00000000,0xb0000000,0x7ecbf7bf,0xff506fbd,0xdff5000d,0x20027fec,
    0x000000ff,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x6f7e4000,0x3f7fea2f,0x00fff985,0x10fffcc0,0x74005fff,0x0000000e,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x7fffdc00,
    0x13fffe20,0x5559ffd1,0x44355555,0xffa83ffe,0x0000001f,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x7d400000,0xfffd85ff,
    0x7ffffd43,0x4fffffff,0xfc817ff6,0x000000ef,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x22000000,0xffa82fff,0x7fffd42f,
    0xffffffff,0x801fff74,0x00005ffe,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__consolas_33_usascii_x[95]={ 0,6,4,0,1,0,0,7,4,4,2,1,3,4,
6,1,1,2,2,2,0,2,1,1,1,1,6,4,2,2,3,4,0,0,2,1,1,3,3,1,1,2,2,2,
3,0,1,0,2,0,2,1,1,1,0,0,0,0,1,5,2,4,1,0,0,2,2,2,1,1,0,1,2,2,
2,2,2,1,2,1,2,1,3,2,1,2,1,0,1,0,2,2,7,3,1, };
static signed short stb__consolas_33_usascii_y[95]={ 24,1,1,2,-1,1,1,1,0,0,1,7,18,13,
18,1,2,2,2,2,2,2,2,2,2,2,7,7,6,11,6,1,1,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,1,0,2,28,1,7,1,7,1,7,1,7,1,1,
1,1,1,7,7,7,7,7,7,7,2,7,7,7,7,7,7,0,-3,0,11, };
static unsigned short stb__consolas_33_usascii_w[95]={ 0,6,10,18,16,18,19,4,10,10,14,16,9,10,
6,15,16,15,15,14,18,14,16,16,16,16,6,8,13,15,13,11,18,18,15,16,16,13,13,16,16,14,13,15,
13,18,16,18,15,19,15,16,16,16,19,18,18,19,16,9,15,9,16,19,11,14,15,14,15,16,17,16,14,14,
13,16,14,16,14,16,15,15,14,14,15,14,16,18,17,17,14,13,4,13,17, };
static unsigned short stb__consolas_33_usascii_h[95]={ 0,24,8,22,29,24,24,8,31,31,14,17,12,4,
7,27,23,22,22,23,22,23,23,22,23,22,18,23,19,9,19,24,30,22,22,23,22,22,22,23,22,22,23,22,
22,22,22,23,22,28,22,23,22,23,22,22,22,22,22,31,27,31,12,3,7,18,24,18,24,18,23,24,23,23,
30,23,23,17,17,18,24,24,17,18,23,18,17,17,17,24,17,31,34,31,8, };
static unsigned short stb__consolas_33_usascii_s[95]={ 178,178,183,166,109,237,217,160,55,20,112,
208,242,242,206,146,210,226,171,100,220,195,227,37,1,15,77,244,46,144,32,
19,90,201,185,18,149,135,242,83,102,87,52,54,1,18,1,176,239,126,119,
35,70,66,187,207,132,151,115,66,162,31,127,213,194,84,201,99,47,60,112,
63,97,145,76,80,130,191,176,114,31,185,161,131,160,146,225,60,94,1,79,
41,1,6,165, };
static unsigned short stb__consolas_33_usascii_t[95]={ 26,1,127,85,1,1,1,127,1,1,127,
108,108,121,127,1,36,61,61,61,85,36,36,85,61,108,108,36,108,127,108,
36,1,85,85,61,85,85,61,61,85,85,61,85,108,85,85,36,85,1,85,
61,85,61,61,61,61,61,61,1,1,1,127,127,127,108,1,108,36,108,36,
36,36,36,1,36,36,108,108,108,36,1,108,108,36,108,108,127,127,36,127,
1,1,1,127, };
static unsigned short stb__consolas_33_usascii_a[95]={ 290,290,290,290,290,290,290,290,
290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,
290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,
290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,
290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,
290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,290,
290,290,290,290,290,290,290, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_consolas_33_usascii_BITMAP_HEIGHT or STB_FONT_consolas_33_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_consolas_33_usascii(stb_fontchar font[STB_FONT_consolas_33_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_consolas_33_usascii_BITMAP_HEIGHT][STB_FONT_consolas_33_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__consolas_33_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_consolas_33_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_consolas_33_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_consolas_33_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_consolas_33_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_consolas_33_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__consolas_33_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__consolas_33_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__consolas_33_usascii_s[i] + stb__consolas_33_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__consolas_33_usascii_t[i] + stb__consolas_33_usascii_h[i]) * recip_height;
            font[i].x0 = stb__consolas_33_usascii_x[i];
            font[i].y0 = stb__consolas_33_usascii_y[i];
            font[i].x1 = stb__consolas_33_usascii_x[i] + stb__consolas_33_usascii_w[i];
            font[i].y1 = stb__consolas_33_usascii_y[i] + stb__consolas_33_usascii_h[i];
            font[i].advance_int = (stb__consolas_33_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__consolas_33_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__consolas_33_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__consolas_33_usascii_s[i] + stb__consolas_33_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__consolas_33_usascii_t[i] + stb__consolas_33_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__consolas_33_usascii_x[i] - 0.5f;
            font[i].y0f = stb__consolas_33_usascii_y[i] - 0.5f;
            font[i].x1f = stb__consolas_33_usascii_x[i] + stb__consolas_33_usascii_w[i] + 0.5f;
            font[i].y1f = stb__consolas_33_usascii_y[i] + stb__consolas_33_usascii_h[i] + 0.5f;
            font[i].advance = stb__consolas_33_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_consolas_33_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_consolas_33_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_consolas_33_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_consolas_33_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_consolas_33_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_consolas_33_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_consolas_33_usascii_LINE_SPACING
#endif

