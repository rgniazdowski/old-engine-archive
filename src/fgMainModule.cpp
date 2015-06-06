/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
#include "fgMainModule.h"
#include "Android/fgAndroid.h"

#include "Event/fgKeyboard.h"
#include "Event/fgEventManager.h"
#include "Event/fgInputHandler.h"
#include "Hardware/fgHardwareState.h"
#include "Util/fgProfiling.h"
#include "fgDebugConfig.h"
#include "fgLog.h"
#include "Util/fgStrings.h"

#if !defined(FG_STATIC_LIBRARY)
#if defined(FG_USING_MARMALADE)

/**
 * Focus lost HANDLER
 */
int32_t fgMarmaladeHandlers::pauseHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->focusLostEvent();
    return 0;
}

/**
 * Focus restored HANDLER
 */
int32_t fgMarmaladeHandlers::unpauseHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->focusGainedEvent();
    return 0;
}

/**
 * Focus lost HANDLER
 */
int32_t fgMarmaladeHandlers::suspendGfxHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->suspendGfxEvent();
    return 0;
}

/**
 * Focus restored HANDLER
 */
int32_t fgMarmaladeHandlers::resumeGfxHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    mainModule->resumeGfxEvent();
    return 0;
}

/**
 * Key state changed HANDLER
 */
int32_t fgMarmaladeHandlers::keyStateChangedHandler(void *systemData, void *userData) {
    if(!userData)
        return 0;
    fg::CMainModule *mainModule = (fg::CMainModule *)userData;
    s3eKeyboardEvent* event = (s3eKeyboardEvent*)systemData;
    mainModule->keyStateChangedEvent(event);
    return 0;
}
#elif defined(FG_USING_SDL) || defined(FG_USING_SDL2)
namespace fg {
    namespace event {
        static KeyVirtualCode
        KeyTranslate[] = {

                          FG_KEY_NULL, // SDL_SCANCODE_UNKNOWN = 0,

                          FG_KEY_NULL, // 1
                          FG_KEY_NULL, // 2
                          FG_KEY_NULL, // 3

                          FG_KEY_A, // SDL_SCANCODE_A = 4,
                          FG_KEY_B, // SDL_SCANCODE_B = 5,
                          FG_KEY_C, // SDL_SCANCODE_C = 6,
                          FG_KEY_D, // SDL_SCANCODE_D = 7,
                          FG_KEY_E, // SDL_SCANCODE_E = 8,
                          FG_KEY_F, // SDL_SCANCODE_F = 9,
                          FG_KEY_G, // SDL_SCANCODE_G = 10,
                          FG_KEY_H, // SDL_SCANCODE_H = 11,
                          FG_KEY_I, // SDL_SCANCODE_I = 12,
                          FG_KEY_J, // SDL_SCANCODE_J = 13,
                          FG_KEY_K, // SDL_SCANCODE_K = 14,
                          FG_KEY_L, // SDL_SCANCODE_L = 15,
                          FG_KEY_M, // SDL_SCANCODE_M = 16,
                          FG_KEY_N, // SDL_SCANCODE_N = 17,
                          FG_KEY_O, // SDL_SCANCODE_O = 18,
                          FG_KEY_P, // SDL_SCANCODE_P = 19,
                          FG_KEY_Q, // SDL_SCANCODE_Q = 20,
                          FG_KEY_R, // SDL_SCANCODE_R = 21,
                          FG_KEY_S, // SDL_SCANCODE_S = 22,
                          FG_KEY_T, // SDL_SCANCODE_T = 23,
                          FG_KEY_U, // SDL_SCANCODE_U = 24,
                          FG_KEY_V, // SDL_SCANCODE_V = 25,
                          FG_KEY_W, // SDL_SCANCODE_W = 26,
                          FG_KEY_X, // SDL_SCANCODE_X = 27,
                          FG_KEY_Y, // SDL_SCANCODE_Y = 28,
                          FG_KEY_Z, // SDL_SCANCODE_Z = 29,

                          FG_KEY_1, // SDL_SCANCODE_1 = 30,
                          FG_KEY_2, // SDL_SCANCODE_2 = 31,
                          FG_KEY_3, // SDL_SCANCODE_3 = 32,
                          FG_KEY_4, // SDL_SCANCODE_4 = 33,
                          FG_KEY_5, // SDL_SCANCODE_5 = 34,
                          FG_KEY_6, // SDL_SCANCODE_6 = 35,
                          FG_KEY_7, // SDL_SCANCODE_7 = 36,
                          FG_KEY_8, // SDL_SCANCODE_8 = 37,
                          FG_KEY_9, // SDL_SCANCODE_9 = 38,
                          FG_KEY_0, // SDL_SCANCODE_0 = 39,

                          FG_KEY_RETURN, // SDL_SCANCODE_RETURN = 40,
                          FG_KEY_ESCAPE, // SDL_SCANCODE_ESCAPE = 41,
                          FG_KEY_BACKSPACE, // SDL_SCANCODE_BACKSPACE = 42,
                          FG_KEY_TAB, // SDL_SCANCODE_TAB = 43,
                          FG_KEY_SPACE, // SDL_SCANCODE_SPACE = 44,

                          FG_KEY_MINUS, // SDL_SCANCODE_MINUS = 45,
                          FG_KEY_EQUALS, // SDL_SCANCODE_EQUALS = 46,
                          FG_KEY_LEFTBRACKET, // SDL_SCANCODE_LEFTBRACKET = 47,
                          FG_KEY_RIGHTBRACKET, // SDL_SCANCODE_RIGHTBRACKET = 48,
                          FG_KEY_BACKSLASH, // SDL_SCANCODE_BACKSLASH = 49,
                          FG_KEY_BACKSLASH, // SDL_SCANCODE_NONUSHASH = 50, // SDL_SCANCODE_BACKSLASH
                          FG_KEY_SEMICOLON, // SDL_SCANCODE_SEMICOLON = 51,
                          FG_KEY_NULL, // SDL_SCANCODE_APOSTROPHE = 52,
                          FG_KEY_TILDE, // SDL_SCANCODE_GRAVE = 53,
                          FG_KEY_COMMA, // SDL_SCANCODE_COMMA = 54,
                          FG_KEY_PERIOD, // SDL_SCANCODE_PERIOD = 55,
                          FG_KEY_SLASH, // SDL_SCANCODE_SLASH = 56,

                          FG_KEY_CAPSLOCK, // SDL_SCANCODE_CAPSLOCK = 57,

                          FG_KEY_F1, // SDL_SCANCODE_F1 = 58,
                          FG_KEY_F2, // SDL_SCANCODE_F2 = 59,
                          FG_KEY_F3, // SDL_SCANCODE_F3 = 60,
                          FG_KEY_F4, // SDL_SCANCODE_F4 = 61,
                          FG_KEY_F5, // SDL_SCANCODE_F5 = 62,
                          FG_KEY_F6, // SDL_SCANCODE_F6 = 63,
                          FG_KEY_F7, // SDL_SCANCODE_F7 = 64,
                          FG_KEY_F8, // SDL_SCANCODE_F8 = 65,
                          FG_KEY_F9, // SDL_SCANCODE_F9 = 66,
                          FG_KEY_F10, // SDL_SCANCODE_F10 = 67,
                          FG_KEY_F11, // SDL_SCANCODE_F11 = 68,
                          FG_KEY_F12, // SDL_SCANCODE_F12 = 69,

                          FG_KEY_PRINTSCREEN, // SDL_SCANCODE_PRINTSCREEN = 70,
                          FG_KEY_SCROLL_LOCK, // SDL_SCANCODE_SCROLLLOCK = 71,
                          FG_KEY_PAUSE, // SDL_SCANCODE_PAUSE = 72,
                          FG_KEY_INSERT, // SDL_SCANCODE_INSERT = 73,
                          FG_KEY_HOME, // SDL_SCANCODE_HOME = 74,
                          FG_KEY_PAGEUP, // SDL_SCANCODE_PAGEUP = 75,
                          FG_KEY_DELETE, // SDL_SCANCODE_DELETE = 76,
                          FG_KEY_END, // SDL_SCANCODE_END = 77,
                          FG_KEY_PAGEDOWN, // SDL_SCANCODE_PAGEDOWN = 78,
                          FG_KEY_RIGHT, // SDL_SCANCODE_RIGHT = 79,
                          FG_KEY_LEFT, // SDL_SCANCODE_LEFT = 80,
                          FG_KEY_DOWN, // SDL_SCANCODE_DOWN = 81,
                          FG_KEY_UP, // SDL_SCANCODE_UP = 82,

                          FG_KEY_NULL, // SDL_SCANCODE_NUMLOCKCLEAR = 83,
                          FG_KEY_NUM_DIVIDE, // SDL_SCANCODE_KP_DIVIDE = 84,
                          FG_KEY_NUM_MULTIPLY, // SDL_SCANCODE_KP_MULTIPLY = 85,
                          FG_KEY_NUM_MINUS, // SDL_SCANCODE_KP_MINUS = 86,
                          FG_KEY_NUM_PLUS, // SDL_SCANCODE_KP_PLUS = 87,
                          FG_KEY_NUM_ENTER, // SDL_SCANCODE_KP_ENTER = 88,
                          FG_KEY_NUM_1, // SDL_SCANCODE_KP_1 = 89,
                          FG_KEY_NUM_2, // SDL_SCANCODE_KP_2 = 90,
                          FG_KEY_NUM_3, // SDL_SCANCODE_KP_3 = 91,
                          FG_KEY_NUM_4, // SDL_SCANCODE_KP_4 = 92,
                          FG_KEY_NUM_5, // SDL_SCANCODE_KP_5 = 93,
                          FG_KEY_NUM_6, // SDL_SCANCODE_KP_6 = 94,
                          FG_KEY_NUM_7, // SDL_SCANCODE_KP_7 = 95,
                          FG_KEY_NUM_8, // SDL_SCANCODE_KP_8 = 96,
                          FG_KEY_NUM_9, // SDL_SCANCODE_KP_9 = 97,
                          FG_KEY_NUM_0, // SDL_SCANCODE_KP_0 = 98,
                          FG_KEY_NUM_PERIOD, // SDL_SCANCODE_KP_PERIOD = 99,

                          FG_KEY_BACKSLASH, // SDL_SCANCODE_NONUSBACKSLASH = 100,
                          FG_KEY_APPLICATION, // SDL_SCANCODE_APPLICATION = 101,
                          FG_KEY_NULL, // SDL_SCANCODE_POWER = 102,
                          FG_KEY_NUM_EQUALS, // SDL_SCANCODE_KP_EQUALS = 103,
                          FG_KEY_F13, // SDL_SCANCODE_F13 = 104,
                          FG_KEY_F14, // SDL_SCANCODE_F14 = 105,
                          FG_KEY_F15, // SDL_SCANCODE_F15 = 106,
                          FG_KEY_F16, // SDL_SCANCODE_F16 = 107,
                          FG_KEY_F17, // SDL_SCANCODE_F17 = 108,
                          FG_KEY_F18, // SDL_SCANCODE_F18 = 109,
                          FG_KEY_F19, // SDL_SCANCODE_F19 = 110,
                          FG_KEY_F20, // SDL_SCANCODE_F20 = 111,
                          FG_KEY_F21, // SDL_SCANCODE_F21 = 112,
                          FG_KEY_F22, // SDL_SCANCODE_F22 = 113,
                          FG_KEY_F23, // SDL_SCANCODE_F23 = 114,
                          FG_KEY_F24, // SDL_SCANCODE_F24 = 115,
                          FG_KEY_EXECUTE, // SDL_SCANCODE_EXECUTE = 116,
                          FG_KEY_HELP, // SDL_SCANCODE_HELP = 117,
                          FG_KEY_MENU, // SDL_SCANCODE_MENU = 118,
                          FG_KEY_SELECT, // SDL_SCANCODE_SELECT = 119,
                          FG_KEY_STOP, // SDL_SCANCODE_STOP = 120,
                          FG_KEY_NULL, // SDL_SCANCODE_AGAIN = 121,
                          FG_KEY_NULL, // SDL_SCANCODE_UNDO = 122,
                          FG_KEY_NULL, // SDL_SCANCODE_CUT = 123,
                          FG_KEY_NULL, // SDL_SCANCODE_COPY = 124,
                          FG_KEY_NULL, // SDL_SCANCODE_PASTE = 125,
                          FG_KEY_NULL, // SDL_SCANCODE_FIND = 126,
                          FG_KEY_NULL, // SDL_SCANCODE_MUTE = 127,
                          FG_KEY_VOLUMEUP, // SDL_SCANCODE_VOLUMEUP = 128,
                          FG_KEY_VOLUMEDOWN, // SDL_SCANCODE_VOLUMEDOWN = 129,

                          FG_KEY_NULL, // 130
                          FG_KEY_NULL, // 131
                          FG_KEY_NULL, // 132

                          FG_KEY_NUM_COMMA, // SDL_SCANCODE_KP_COMMA = 133,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_EQUALSAS400 = 134,

                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL1 = 135,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL2 = 136,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL3 = 137,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL4 = 138,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL5 = 139,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL6 = 140,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL7 = 141,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL8 = 142,
                          FG_KEY_NULL, // SDL_SCANCODE_INTERNATIONAL9 = 143,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG1 = 144,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG2 = 145,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG3 = 146,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG4 = 147,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG5 = 148,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG6 = 149,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG7 = 150,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG8 = 151,
                          FG_KEY_NULL, // SDL_SCANCODE_LANG9 = 152,

                          FG_KEY_NULL, // SDL_SCANCODE_ALTERASE = 153,
                          FG_KEY_NULL, // SDL_SCANCODE_SYSREQ = 154,
                          FG_KEY_CANCEL, // SDL_SCANCODE_CANCEL = 155,
                          FG_KEY_CLEAR, // SDL_SCANCODE_CLEAR = 156,
                          FG_KEY_NULL, // SDL_SCANCODE_PRIOR = 157,
                          FG_KEY_RETURN, // SDL_SCANCODE_RETURN2 = 158,
                          FG_KEY_NULL, // SDL_SCANCODE_SEPARATOR = 159,
                          FG_KEY_NULL, // SDL_SCANCODE_OUT = 160,
                          FG_KEY_NULL, // SDL_SCANCODE_OPER = 161,
                          FG_KEY_NULL, // SDL_SCANCODE_CLEARAGAIN = 162,
                          FG_KEY_NULL, // SDL_SCANCODE_CRSEL = 163,
                          FG_KEY_NULL, // SDL_SCANCODE_EXSEL = 164,

                          FG_KEY_NULL, // 165
                          FG_KEY_NULL, // 166
                          FG_KEY_NULL, // 167
                          FG_KEY_NULL, // 168
                          FG_KEY_NULL, // 169
                          FG_KEY_NULL, // 170
                          FG_KEY_NULL, // 171
                          FG_KEY_NULL, // 172
                          FG_KEY_NULL, // 173
                          FG_KEY_NULL, // 174
                          FG_KEY_NULL, // 175

                          FG_KEY_NULL, // SDL_SCANCODE_KP_00 = 176,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_000 = 177,
                          FG_KEY_NULL, // SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
                          FG_KEY_NULL, // SDL_SCANCODE_DECIMALSEPARATOR = 179,
                          FG_KEY_NULL, // SDL_SCANCODE_CURRENCYUNIT = 180,
                          FG_KEY_NULL, // SDL_SCANCODE_CURRENCYSUBUNIT = 181,
                          FG_KEY_LEFTPAREN, // SDL_SCANCODE_KP_LEFTPAREN = 182,
                          FG_KEY_RIGHTPAREN, // SDL_SCANCODE_KP_RIGHTPAREN = 183,
                          FG_KEY_LEFTBRACE, // SDL_SCANCODE_KP_LEFTBRACE = 184,
                          FG_KEY_RIGHTBRACE, // SDL_SCANCODE_KP_RIGHTBRACE = 185,
                          FG_KEY_TAB, // SDL_SCANCODE_KP_TAB = 186,
                          FG_KEY_BACKSPACE, // SDL_SCANCODE_KP_BACKSPACE = 187,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_A = 188,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_B = 189,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_C = 190,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_D = 191,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_E = 192,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_F = 193,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_XOR = 194,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_POWER = 195,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_PERCENT = 196,
                          FG_KEY_LESS, // SDL_SCANCODE_KP_LESS = 197,
                          FG_KEY_GREATER, // SDL_SCANCODE_KP_GREATER = 198,
                          FG_KEY_AMPERSAND, // SDL_SCANCODE_KP_AMPERSAND = 199,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_DBLAMPERSAND = 200,
                          FG_KEY_VERTICAL_BAR, // SDL_SCANCODE_KP_VERTICALBAR = 201,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
                          FG_KEY_COLON, // SDL_SCANCODE_KP_COLON = 203,
                          FG_KEY_HASH, // SDL_SCANCODE_KP_HASH = 204,
                          FG_KEY_SPACE, // SDL_SCANCODE_KP_SPACE = 205,
                          FG_KEY_AT, // SDL_SCANCODE_KP_AT = 206,
                          FG_KEY_EXCLAIM, // SDL_SCANCODE_KP_EXCLAM = 207,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_MEMSTORE = 208,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_MEMRECALL = 209,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_MEMCLEAR = 210,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_MEMADD = 211,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_MEMSUBTRACT = 212,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_MEMMULTIPLY = 213,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_MEMDIVIDE = 214,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_PLUSMINUS = 215,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_CLEAR = 216,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_CLEARENTRY = 217,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_BINARY = 218,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_OCTAL = 219,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_DECIMAL = 220,
                          FG_KEY_NULL, // SDL_SCANCODE_KP_HEXADECIMAL = 221,

                          FG_KEY_NULL, // 222
                          FG_KEY_NULL, // 223

                          FG_KEY_LCTRL, // SDL_SCANCODE_LCTRL = 224,
                          FG_KEY_LSHIFT, // SDL_SCANCODE_LSHIFT = 225,
                          FG_KEY_LALT, // SDL_SCANCODE_LALT = 226,
                          FG_KEY_LGUI, // SDL_SCANCODE_LGUI = 227,
                          FG_KEY_RCTRL, // SDL_SCANCODE_RCTRL = 228,
                          FG_KEY_RSHIFT, // SDL_SCANCODE_RSHIFT = 229,
                          FG_KEY_RALT, // SDL_SCANCODE_RALT = 230,
                          FG_KEY_RGUI, // SDL_SCANCODE_RGUI = 231,

                          FG_KEY_NULL, // 232
                          FG_KEY_NULL, // 233
                          FG_KEY_NULL, // 234
                          FG_KEY_NULL, // 235
                          FG_KEY_NULL, // 236
                          FG_KEY_NULL, // 237
                          FG_KEY_NULL, // 238
                          FG_KEY_NULL, // 239
                          FG_KEY_NULL, // 240
                          FG_KEY_NULL, // 241
                          FG_KEY_NULL, // 242
                          FG_KEY_NULL, // 243
                          FG_KEY_NULL, // 244
                          FG_KEY_NULL, // 245
                          FG_KEY_NULL, // 246
                          FG_KEY_NULL, // 247
                          FG_KEY_NULL, // 248
                          FG_KEY_NULL, // 249
                          FG_KEY_NULL, // 250
                          FG_KEY_NULL, // 251
                          FG_KEY_NULL, // 252
                          FG_KEY_NULL, // 253
                          FG_KEY_NULL, // 254
                          FG_KEY_NULL, // 255
                          FG_KEY_NULL, // 256

                          FG_KEY_NULL, // SDL_SCANCODE_MODE = 257,

                          FG_KEY_NULL, // SDL_SCANCODE_AUDIONEXT = 258,
                          FG_KEY_NULL, // SDL_SCANCODE_AUDIOPREV = 259,
                          FG_KEY_NULL, // SDL_SCANCODE_AUDIOSTOP = 260,
                          FG_KEY_NULL, // SDL_SCANCODE_AUDIOPLAY = 261,
                          FG_KEY_NULL, // SDL_SCANCODE_AUDIOMUTE = 262,
                          FG_KEY_NULL, // SDL_SCANCODE_MEDIASELECT = 263,
                          FG_KEY_NULL, // SDL_SCANCODE_WWW = 264,
                          FG_KEY_NULL, // SDL_SCANCODE_MAIL = 265,
                          FG_KEY_NULL, // SDL_SCANCODE_CALCULATOR = 266,
                          FG_KEY_NULL, // SDL_SCANCODE_COMPUTER = 267,
                          FG_KEY_NULL, // SDL_SCANCODE_AC_SEARCH = 268,
                          FG_KEY_APP_HOME, // SDL_SCANCODE_AC_HOME = 269,
                          FG_KEY_APP_BACK, // SDL_SCANCODE_AC_BACK = 270,
                          FG_KEY_NULL, // SDL_SCANCODE_AC_FORWARD = 271,
                          FG_KEY_NULL, // SDL_SCANCODE_AC_STOP = 272,
                          FG_KEY_NULL, // SDL_SCANCODE_AC_REFRESH = 273,
                          FG_KEY_NULL, // SDL_SCANCODE_AC_BOOKMARKS = 274,

                          FG_KEY_NULL, // SDL_SCANCODE_BRIGHTNESSDOWN = 275,
                          FG_KEY_NULL, // SDL_SCANCODE_BRIGHTNESSUP = 276,
                          FG_KEY_NULL, // SDL_SCANCODE_DISPLAYSWITCH = 277,
                          FG_KEY_NULL, // SDL_SCANCODE_KBDILLUMTOGGLE = 278,
                          FG_KEY_NULL, // SDL_SCANCODE_KBDILLUMDOWN = 279,
                          FG_KEY_NULL, // SDL_SCANCODE_KBDILLUMUP = 280,
                          FG_KEY_NULL, // SDL_SCANCODE_EJECT = 281,
                          FG_KEY_NULL, // SDL_SCANCODE_SLEEP = 282,

                          FG_KEY_NULL, // SDL_SCANCODE_APP1 = 283,
                          FG_KEY_NULL, // SDL_SCANCODE_APP2 = 284,
                          FG_KEY_NULL, // 285
                          FG_KEY_NULL, // 286
                          FG_KEY_NULL, // 287
                          FG_KEY_NULL, // 288
                          FG_KEY_NULL, // 289
                          FG_KEY_NULL // 290
        };
    } // namespace event
} // namespace fg
#endif /* FG_USING_MARMALADE */

using namespace fg;

/**
 * Initialize main module
 */
CMainModule::CMainModule(int argc, char *argv[]) :
m_argc(argc),
m_argv(argv),
m_appInit(FG_FALSE),
m_slow(FG_FALSE),
m_isExit(FG_FALSE),
m_isSuspend(FG_FALSE),
m_isFrameFreeze(FG_FALSE),
#if defined(FG_USING_MARMALADE) // #FIXME
m_deviceQuery(),
#endif /* FG_USING_MARMALADE */
m_engineMain(NULL) { }

CMainModule::~CMainModule() { }

#if defined(FG_USING_SDL2)

int SDLCALL CMainModule::filterSDLEvents(void* userdata, SDL_Event* event) {
    if(!userdata)
        return 1;
    CMainModule *mainModule = (CMainModule *)userdata;
    switch(event->type) {
        case SDL_APP_WILLENTERBACKGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_WILL_ENTER_BACKGROUND");
            // Focus lost?
            mainModule->m_isSuspend = FG_TRUE;
            break;
        case SDL_APP_DIDENTERBACKGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_DID_ENTER_BACKGROUND");
            //suspendGfxEvent();
            mainModule->m_isSuspend = FG_TRUE;
            break;
        case SDL_APP_WILLENTERFOREGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_WILL_ENTER_FOREGROUND");
            //resumeGfxEvent();
            mainModule->m_isSuspend = FG_FALSE;
            break;
        case SDL_APP_DIDENTERFOREGROUND:
            FG_LOG_DEBUG("SDL2: FILTER: SDL_APP_DID_ENTER_FOREGROUND");
            mainModule->m_isSuspend = FG_FALSE;
            break;
        default:
            break;
    };
    return 1;
}

event::KeyVirtualCode CMainModule::translateKeyboardCode(const SDL_KeyboardEvent& event) {
    const unsigned int index = (unsigned int) event.keysym.scancode;
    const unsigned int maxIndex = sizeof(event::KeyTranslate)/sizeof(event::KeyVirtualCode);
    if(index >= maxIndex)
        return event::FG_KEY_NULL;
    const event::KeyVirtualCode keyCode = event::KeyTranslate[index];
    return keyCode;
}
/**
 * #FIXME - this needs to be maintained differently
 * - maybe add some SDL2 event watches?
 * @return 
 */
SDL_EventType CMainModule::checkSDLEvents(void) {
    SDL_Event event;
    SDL_EventType status = SDL_FIRSTEVENT;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
                /* Application events */
            case SDL_QUIT: /**< User-requested quit */
                FG_LOG_DEBUG("SDL2: The application is terminating, caught QUIT...");
                return SDL_QUIT;
                break;

                /* These application events have special meaning on iOS, see README-ios.txt for details */
            case SDL_APP_TERMINATING: /**< The application is being terminated by the OS
                                     Called on iOS in applicationWillTerminate()
                                     Called on Android in onDestroy()
                                    */
                FG_LOG_DEBUG("SDL2: The application is terminating...");
                return SDL_QUIT;
                break;

            case SDL_APP_LOWMEMORY: /**< The application is low on memory, free memory if possible.
                                     Called on iOS in applicationDidReceiveMemoryWarning()
                                     Called on Android in onLowMemory()
                                    */
                FG_LOG_DEBUG("SDL2: The application is low on memory...");
                break;

            case SDL_APP_WILLENTERBACKGROUND: /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()
                                    */
                FG_LOG_DEBUG("SDL2: The application is about to enter the background...");
                // Focus lost?
                m_isSuspend = FG_TRUE;
                break;

            case SDL_APP_DIDENTERBACKGROUND: /**< The application did enter the background and may not get CPU for some time
                                     Called on iOS in applicationDidEnterBackground()
                                     Called on Android in onPause()
                                    */
                FG_LOG_DEBUG("SDL2: The application did enter the background and may not get CPU for some time...");
                suspendGfxEvent();
                m_isSuspend = FG_TRUE;
                break;

            case SDL_APP_WILLENTERFOREGROUND: /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()
                                    */
                FG_LOG_DEBUG("SDL2: The application is about to enter the foreground...");
                resumeGfxEvent();
                m_isSuspend = FG_FALSE;
                // Focus gained?
                break;

            case SDL_APP_DIDENTERFOREGROUND: /**< The application is now interactive
                                     Called on iOS in applicationDidBecomeActive()
                                     Called on Android in onResume()
                                    */
                FG_LOG_DEBUG("SDL2: The application is now interactive...");
                m_isSuspend = FG_FALSE;
                break;


                /* Window events */
            case SDL_WINDOWEVENT: /**< Window state change */
                break;
            case SDL_SYSWMEVENT: /**< System specific event */
                break;

                /* Keyboard events */
            case SDL_KEYDOWN: /**< Key pressed */
                if(this->m_engineMain) {
                    this->m_engineMain->getInputHandler()->addKeyPressed(translateKeyboardCode(event.key));
                }
                break;
            case SDL_KEYUP: /**< Key released */
                if(this->m_engineMain) {                    
                    this->m_engineMain->getInputHandler()->addKeyUp(translateKeyboardCode(event.key));
                }
                break;
            case SDL_TEXTEDITING: /**< Keyboard text editing (composition) */
                break;
            case SDL_TEXTINPUT: /**< Keyboard text input */
                //printf("TEXT INPUT: '%s'\n", event.text.text);
                break;
#if defined(FG_USING_PLATFORM_LINUX) || defined(FG_USING_PLATFORM_WINDOWS)
                /* Mouse events */
            case SDL_MOUSEMOTION: /**< Mouse moved */
                if(!m_engineMain)
                    continue;
            {
                unsigned int mid = FG_DEFAULT_POINTER_ID;
                if(event.motion.state & SDL_BUTTON_LMASK)
                    mid = 1;
                if(event.motion.state & SDL_BUTTON_MMASK)
                    mid = 2;
                if(event.motion.state & SDL_BUTTON_RMASK)
                    mid = 3;
                if(event.motion.state & SDL_BUTTON_X1MASK)
                    mid = 4;
                if(event.motion.state & SDL_BUTTON_X2MASK)
                    mid = 5;
                //this->m_engineMain->getInputHandler()->singleTouchMotionHandler((void *)&event.motion, this->m_engineMain->getInputHandler());
                this->m_engineMain->getInputHandler()->handlePointerMoved(Vector2i(event.motion.x, event.motion.y),
                                                                          mid,
                                                                          event.motion.state);
            }
                break;
            case SDL_MOUSEBUTTONDOWN: /**< Mouse button pressed */
                if(!m_engineMain)
                    continue;
                //this->m_engineMain->getInputHandler()->singleTouchButtonHandler((void *)&event.button, this->m_engineMain->getInputHandler());
                this->m_engineMain->getInputHandler()->handlePointerPressed(Vector2i(event.button.x, event.button.y),
                                                                            event.button.button);
                break;
            case SDL_MOUSEBUTTONUP: /**< Mouse button released */
                if(!m_engineMain)
                    continue;
                //this->m_engineMain->getInputHandler()->singleTouchButtonHandler((void *)&event.button, this->m_engineMain->getInputHandler());
                this->m_engineMain->getInputHandler()->handlePointerReleased(Vector2i(event.button.x, event.button.y),
                                                                             event.button.button);
                break;
            case SDL_MOUSEWHEEL: /**< Mouse wheel motion */
                //guiScale += 0.05f * (float)event.wheel.y;
                break;
#endif /* PLATFORM SPECIFIC */

                /* Joystick events #FIXME */
            case SDL_JOYAXISMOTION: /**< Joystick axis motion */
                FG_LOG_DEBUG("SDL_JOYAXISMOTION");
                break;
            case SDL_JOYBALLMOTION: /**< Joystick trackball motion */
                FG_LOG_DEBUG("SDL_JOYBALLMOTION");
                break;
            case SDL_JOYHATMOTION: /**< Joystick hat position change */
                FG_LOG_DEBUG("SDL_JOYHATMOTION");
                break;
            case SDL_JOYBUTTONDOWN: /**< Joystick button pressed */
                FG_LOG_DEBUG("SDL_JOYBUTTONDOWN");
                break;
            case SDL_JOYBUTTONUP: /**< Joystick button released */
                FG_LOG_DEBUG("SDL_JOYBUTTONUP");
                break;
            case SDL_JOYDEVICEADDED: /**< A new joystick has been inserted into the system */
                FG_LOG_DEBUG("SDL_JOYDEVICEADDED");
                break;
            case SDL_JOYDEVICEREMOVED: /**< An opened joystick has been removed */
                FG_LOG_DEBUG("SDL_JOYDEVICEREMOVED");
                break;

                /* Game controller events */
#if 0
            case SDL_CONTROLLERAXISMOTION: /**< Game controller axis motion */
                FG_LOG_DEBUG("SDL_CONTROLLERAXISMOTION");
                break;
            case SDL_CONTROLLERBUTTONDOWN: /**< Game controller button pressed */
                FG_LOG_DEBUG("SDL_CONTROLLERBUTTONDOWN");
                break;
            case SDL_CONTROLLERBUTTONUP: /**< Game controller button released */
                FG_LOG_DEBUG("SDL_CONTROLLERBUTTONUP");
                break;
            case SDL_CONTROLLERDEVICEADDED: /**< A new Game controller has been inserted into the system */
                FG_LOG_DEBUG("SDL_CONTROLLERDEVICEADDED");
                break;
            case SDL_CONTROLLERDEVICEREMOVED: /**< An opened Game controller has been removed */
                FG_LOG_DEBUG("SDL_CONTROLLERDEVICEREMOVED");
            {
                if(!m_engineMain)
                    continue;
                CJoypadController *joypadController = this->m_engineMain->getJoypadController();
                if(joypadController) {
                    joypadController->processEvent(event);
                }
            }
                break;

            case SDL_CONTROLLERDEVICEREMAPPED: /**< The controller mapping was updated */
                FG_LOG_DEBUG("SDL_CONTROLLERDEVICEREMAPPED");
                break;
#endif
                /* Touch events */
            case SDL_FINGERDOWN:
            {
                if(!m_engineMain)
                    continue;
                int w = this->m_engineMain->getGfxMain()->getMainWindow()->getWidth();
                int h = this->m_engineMain->getGfxMain()->getMainWindow()->getHeight();
                /*SDL_MouseButtonEvent button;
                button.timestamp = event.tfinger.timestamp;
                button.button = event.tfinger.fingerId;
                button.clicks = 1;
                button.type = SDL_FINGERDOWN;
                button.state = SDL_PRESSED;
                button.x = (int)((float)w * event.tfinger.x);
                button.y = (int)((float)h * event.tfinger.y);*/
                int x = (int)((float)w * event.tfinger.x);
                int y = (int)((float)h * event.tfinger.y);
                this->m_engineMain->getInputHandler()->handlePointerPressed(Vector2i(x, y), event.tfinger.fingerId);
                //this->m_engineMain->getInputHandler()->singleTouchButtonHandler((void *)&button, this->m_engineMain->getInputHandler());
            }
                break;
            case SDL_FINGERUP:
            {
                int w = this->m_engineMain->getGfxMain()->getMainWindow()->getWidth();
                int h = this->m_engineMain->getGfxMain()->getMainWindow()->getHeight();
                /*SDL_MouseButtonEvent button;
                button.timestamp = event.tfinger.timestamp;
                button.button = event.tfinger.fingerId;
                button.clicks = 1;
                button.type = SDL_FINGERUP;
                button.state = SDL_RELEASED;
                button.x = (int)((float)w * event.tfinger.x);
                button.y = (int)((float)h * event.tfinger.y);*/
                int x = (int)((float)w * event.tfinger.x);
                int y = (int)((float)h * event.tfinger.y);
                this->m_engineMain->getInputHandler()->handlePointerReleased(Vector2i(x, y), event.tfinger.fingerId);
                //this->m_engineMain->getInputHandler()->singleTouchButtonHandler((void *)&button, this->m_engineMain->getInputHandler());
            }
                break;
            case SDL_FINGERMOTION:
            {
                int w = this->m_engineMain->getGfxMain()->getMainWindow()->getWidth();
                int h = this->m_engineMain->getGfxMain()->getMainWindow()->getHeight();
                /*SDL_MouseMotionEvent motion;
                motion.timestamp = event.tfinger.timestamp;
                //motion.button = event.tfinger.fingerId;
                //motion.clicks = 1;
                motion.type = SDL_FINGERMOTION;
                motion.state = SDL_PRESSED;
                motion.x = (int)((float)w * event.tfinger.x);
                motion.y = (int)((float)h * event.tfinger.y);*/
                int x = (int)((float)w * event.tfinger.x);
                int y = (int)((float)h * event.tfinger.y);
                this->m_engineMain->getInputHandler()->handlePointerMoved(Vector2i(x, y), event.tfinger.fingerId, SDL_PRESSED);
                //this->m_engineMain->getInputHandler()->singleTouchMotionHandler((void *)&motion, this->m_engineMain->getInputHandler());
            }
                break;

                /* Gesture events */
            case SDL_DOLLARGESTURE:
                break;
            case SDL_DOLLARRECORD:
                break;
            case SDL_MULTIGESTURE:
                break;

                /* Clipboard events */
            case SDL_CLIPBOARDUPDATE: /**< The clipboard changed */
                break;

                /* Drag and drop events */
            case SDL_DROPFILE: /**< The system requests a file open */
                break;

                /* Render events */
            case SDL_RENDER_TARGETS_RESET: /**< The render targets have been reset */
                break;

            default:
#if !defined(FG_USING_PLATFORM_ANDROID)
                if(event.type >= SDL_CONTROLLERAXISMOTION && event.type <= SDL_CONTROLLERDEVICEREMAPPED) {
                    if(!m_engineMain)
                        continue;
                    fg::event::CJoypadController *joypadController = this->m_engineMain->getJoypadController();
                    if(joypadController) {
                        joypadController->processEvent(event);
                    }
                }
#endif
                break;
        }
    }
    if(m_isExit)
        m_isSuspend = FG_TRUE;
    return status;
}
#endif

/**
 * Called when a fullscreen window with an OpenGL context
 * has been created and is ready to be used.
 * 
 * @return 
 */
fgBool CMainModule::initProgram(void) {
    timesys::init(); // #FIXME global time init?
#if defined(FG_DEBUG)
    profile::g_debugProfiling = new profile::CProfiling();
    profile::g_debugProfiling->initialize();
#endif
    float t1 = timesys::ms();
    FG_LOG_DEBUG("Init program main...");
    if(m_appInit) {
        // already initialized
        return FG_TRUE;
    }

#if defined(FG_USING_MARMALADE)
    m_deviceQuery.computeDevice();
    s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, S3E_SURFACE_LANDSCAPE_FIXED);
    // ?
    //s3eKeyboardSetInt(S3E_KEYBOARD_GET_CHAR, 1);
    // Register for keyboard
    s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, &fgMarmaladeHandlers::keyStateChangedHandler, (void *)this);

    // DEVICE FOCUS – called on any device
    s3eDeviceRegister(S3E_DEVICE_PAUSE, &fgMarmaladeHandlers::pauseHandler, (void *)this);
    s3eDeviceRegister(S3E_DEVICE_UNPAUSE, &fgMarmaladeHandlers::unpauseHandler, (void *)this);
    int32 mustSuspend = s3eGLGetInt(S3E_GL_MUST_SUSPEND); // S3E_GL_VERSION // S3E_EGL_VERSION
    s3eGLRegister(S3E_GL_SUSPEND, &fgMarmaladeHandlers::suspendGfxHandler, (void *)this);
    s3eGLRegister(S3E_GL_RESUME, &fgMarmaladeHandlers::resumeGfxHandler, (void *)this);

#endif /* FG_USING_MARMALADE */
    if(!m_engineMain) {
        FG_LOG_DEBUG("Creating game main object...");
        m_engineMain = new fg::CEngineMain(m_argc, m_argv);
    }
    // Well the whole configuration process should update the screen (swap buffers)
    // this is needed to display splash screen (after marmalade splash screen) and
    // show the game initialization process by displaying the progress bar
    if(!m_engineMain->loadConfiguration()) {
        return FG_FALSE;
    }
    // Initialize the main subsystems (gui, gfx and others)
    if(!m_engineMain->initialize()) {
        return FG_FALSE;
    }
    // Preload any required resources
    if(!m_engineMain->loadResources()) {
        return FG_FALSE;
    }
    m_engineMain->update(FG_TRUE);
    m_appInit = FG_TRUE;
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: Program initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    m_engineMain->update(FG_TRUE);
#if defined(FG_USING_SDL2) && defined(FG_USING_PLATFORM_ANDROID)
    SDL_AddEventWatch(filterSDLEvents, this);
#endif    
    return FG_TRUE;
}

/**
 * Applications main loop step (one thread)
 * @return
 */
fgBool CMainModule::mainLoopStep(void) {
    // DEVICE YIELD FUNCTION IN HERE
    if(!m_appInit) {
        FG_LOG_DEBUG("MainModule: Loop step - application not initialized...");
        return FG_FALSE;
    }
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Program::loopStep");
    }
#endif
    // #FIXME - This event checking should not be in here
#if defined(FG_USING_SDL2)
    if(checkSDLEvents() == SDL_QUIT) {
        m_isExit = FG_TRUE;
    }
#endif
    if(m_isSuspend) {
        //FG_LOG_DEBUG("MainModule: Loop step - suspend...");
        return FG_TRUE;
    }

#if defined(FG_USING_MARMALADE)
    s3eKeyboardUpdate();
    if(s3eDeviceCheckQuitRequest()) {
        m_appInit = FG_FALSE;
        m_isExit = FG_TRUE;
        return FG_FALSE;
    }
    if(s3eKeyboardGetState(s3eKeyEnter) & S3E_KEY_STATE_PRESSED) {
        m_appInit = FG_FALSE;
        m_isExit = FG_TRUE;
        FG_LOG_DEBUG("ENTER PRESSED...");
        return FG_FALSE;
    }
#endif /* FG_USING_MARMALADE */
    if(m_isExit) {
        m_appInit = FG_FALSE;
        FG_LOG_DEBUG("EXIT IS ACTIVATED - break loop main ! bye!");
        return FG_FALSE;
    }

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::update");
    }
#endif

    m_engineMain->update();

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::update");
        profile::g_debugProfiling->begin("Game::display");
    }
#endif
    if(!m_isFrameFreeze) {
        // well for now drawing and all update functions will be called in one place (one thread)
        // however it needs changing
        m_engineMain->preRender();
    }

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::display");
        profile::g_debugProfiling->begin("Game::render");
    }
#endif    
    m_engineMain->render();
#if defined(FG_DEBUG)
    static int loopCount = 0;
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::render");
        profile::g_debugProfiling->end("Program::loopStep");
        profile::g_debugProfiling->updateHistory();

        loopCount++;
        if(loopCount > 150) {
            loopCount = 0;
            profile::g_debugProfiling->dumpToDefaultFile();
        }
    }
#endif
    return FG_TRUE;
}

/**
 * The way to exit from the application
 */
void CMainModule::closeProgram(void) {
    FG_LOG_DEBUG("Closing program...");
    if(m_engineMain) {
        m_engineMain->destroy();
        delete m_engineMain;
    }
    m_engineMain = NULL;
    m_appInit = FG_FALSE;
#if defined(FG_DEBUG)
    if(profile::g_debugProfiling)
        delete profile::g_debugProfiling;
    profile::g_debugProfiling = NULL;
#endif
}

/**
 * DEVICE PAUSE event
 */
void CMainModule::suspendGfxEvent(void) {
    FG_LOG_DEBUG("MainModule: Suspending GFX Subsystem");
    if(m_engineMain)
        m_engineMain->getGfxMain()->suspendGFX();
}

/**
 * DEVICE resume event
 */
void CMainModule::resumeGfxEvent(void) {
    FG_LOG_DEBUG("MainModule: Resuming GFX Subsystem...");
    if(m_engineMain)
        m_engineMain->getGfxMain()->resumeGFX();
}

/**
 * DEVICE PAUSE event
 * (not the GL pause event)
 */
void CMainModule::focusLostEvent(void) {
    FG_LOG_DEBUG("MainModule: Focus lost event");

    // No focus means:
    // - displaying OS menu
    // - lower ipad menu visible
    // - minimized
    // - switching to another app
    // - need to turn on internal game pause switch
    // - quickly save the game/app state

    // it needs to be handled properly - for current moment if application losts
    // focus while loading game data etc (initialization) - it will crash
    // TODO pausing/un-pausing events need to handle initialization moments
    // properly - also be aware of the operations in other threads (?)
    // #TODO data loading procedures need to be sequential
    // and easy to abort/revert/quit/resume
}

/**
 * DEVICE un-pause event
 * (not the GL un-pause event)
 */
void CMainModule::focusGainedEvent(void) {
    FG_LOG_DEBUG("MainModule: Focus gained event");
}
#if defined(FG_USING_MARMALADE)

/**
 * Handle PRESSING and RELEASING keys
 */
void CMainModule::keyStateChangedEvent(s3eKeyboardEvent* event) {
    if(!m_appInit || !m_engineMain)
        return;
    if(event->m_Pressed) {
        m_engineMain->getInputHandler()->addKeyDown((int)event->m_Key);
    } else {
        m_engineMain->getInputHandler()->addKeyUp((int)event->m_Key);
    }
}
#endif /* FG_USING_MARMALADE */

/**
 * Main function that is called when the program starts.
 */
#if defined(FG_USING_MARMALADE)

extern "C" int main() {
    IwUtilInit();
    int argc = 0;
    char *argv[] = {NULL, NULL};
#elif defined(FG_USING_PLATFORM_ANDROID) && defined(FG_USING_SDL2)

extern "C" int SDL_main(int argc, char **argv) {
#else

/**
 * Main function that is called when the program starts.
 * @param argc Number of the arguments passed to the executable
 * @param argv Array containing the arguments
 * @return 
 */
extern "C" int main(int argc, char *argv[]) {
#endif /* FG_USING_MARMALADE */
    FG_LOG_DEBUG("%s: Starting up!", FG_PACKAGE_FULL_TEXT);
    FG_LOG_DEBUG("%s: build %s %s DEBUG", FG_PACKAGE_NAME, FG_BUILD_TIME, FG_BUILD_DATE);
#if defined(FG_RELEASE)
    FG_LOG_INFO("%s: build %s %s RELEASE", FG_PACKAGE_NAME, FG_BUILD_TIME, FG_BUILD_DATE);
#endif
#if defined(FG_DEBUG) && !defined(FG_USING_MARMALADE)
    FG_LOG_DEBUG("%s: Number of arguments: %d", FG_PACKAGE_NAME, argc);
    if(argc) {
        for(int i = 0; i < argc; i++) {
            FG_LOG_DEBUG("%s: ARGV[%d] = '%s'", FG_PACKAGE_NAME, i, argv[i]);
        }
    }
    
#endif
    CMainModule *mainModule = new CMainModule(argc, argv);
    if(!mainModule->initProgram()) {
        mainModule->closeProgram();
        FG_LOG_DEBUG("Deleting main module...");
        delete mainModule;
        FG_LOG_ERROR("Initialization failed, closing program with error");
#if defined(FG_USING_MARMALADE)
        IwUtilTerminate();
        s3eDeviceExit(0);
#endif /* FG_USING_MARMALADE */		
        return 1;
    }
    // DEVICE YIELD FUNCTION IN HERE

    while(FG_TRUE) {
        fgBool status = mainModule->mainLoopStep();
        // DEVICE YIELD FUNCTION IN HERE
#if defined(FG_USING_MARMALADE)
        s3eDeviceBacklightOn(); // #FIXME // need to wrap it in something else
#endif /* FG_USING_MARMALADE */
        if(status == FG_FALSE || mainModule->isExit()) {
            FG_LOG_DEBUG("Main loop break...");
            break;
        }
    }
    mainModule->closeProgram();
    FG_LOG_DEBUG("Deleting main module...");
    delete mainModule;

    FG_LOG_DEBUG("Successfully closed program");
#if defined FG_USING_MARMALADE
    IwUtilTerminate();
    s3eDeviceExit(0);
#endif /* FG_USING_MARMALADE */
    return 0;
}
#endif
