/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgKeyboard.h
 * Author: vigilant
 *
 * Created on May 20, 2015, 7:50 PM
 */

#ifndef FG_INC_KEYBOARD
    #define FG_INC_KEYBOARD
    #define FG_INC_KEYBOARD_BLOCK

    #include "fgTypes.h"

namespace fg {
    namespace event {

        enum KeyVirtualCode {
            FG_KEY_UNKNOWN = 0,

            FG_KEY_NULL = 0,

            FG_KEY_SOH = 1, // SOH // Start of heading
            FG_KEY_STX = 2, // STX // Start of text
            FG_KEY_ETX = 3, // ETX // End of text
            FG_KEY_EOT = 4, // EOT // End of trans.
            FG_KEY_ENQ = 5, // ENQ // Enquiry
            FG_KEY_ENQUIRY = FG_KEY_ENQ, // ENQ
            FG_KEY_ACK = 6, // ACK // Ack.
            FG_KEY_BELL = 7, // BEL // Bell \a
            FG_KEY_BS = 8, // BS // Back space \b
            FG_KEY_BACKSPACE = FG_KEY_BS, // Back space \b
            FG_KEY_HT = 9, // HT // Horizontal tab \t
            FG_KEY_HORIZONTAL_TAB = FG_KEY_HT, // HT \t
            FG_KEY_TAB = FG_KEY_HT, // TAB \t
            FG_KEY_LF = 10, // LF // Line feed \n            
            FG_KEY_LINEFEED = FG_KEY_LF, // LF \n
            FG_KEY_VT = 11, // VT // Vertical tab \v
            FG_KEY_VERTICAL_TAB = FG_KEY_VT, // Vertical tab \v
            FG_KEY_FF = 12, // FF // Form feed \f
            FG_KEY_CR = 13, // CR // Carriage return \r
            FG_KEY_RETURN = FG_KEY_CR, // Carriage return \r
            FG_KEY_SO = 14, // SO // Shift out
            FG_KEY_SI = 15, // SI // Shift in
            FG_KEY_DLE = 16, // DLE // Data line escape
            FG_KEY_DC1 = 17, // DC1 // Device control 1
            FG_KEY_DC2 = 18, // DC2 // Device control 2
            FG_KEY_DC3 = 19, // DC3 // Device control 3
            FG_KEY_DC4 = 20, // DC4 // Device control 4
            FG_KEY_NAK = 21, // NAK // Negative ack.
            FG_KEY_SYN = 22, // SYN // Synchronous idle
            FG_KEY_ETB = 23, // ETB // End of block
            FG_KEY_CANCEL = 24, // CAN // Cancel
            FG_KEY_EM = 25, // EM // End of medium
            FG_KEY_SUB = 26, // SUB // Substitute
            FG_KEY_ESC = 27, // ESC // Escape
            FG_KEY_ESCAPE = FG_KEY_ESC, // Escape
            FG_KEY_FS = 28, // FS // File separator
            FG_KEY_GS = 29, // GS // Group separator
            FG_KEY_RS = 30, // RS // Record separator
            FG_KEY_US = 31, // US // Unit separator

            FG_KEY_SPACE = 32, // Space
            FG_KEY_EXCLAIM = 33, // !
            FG_KEY_QUOTEDBL = 34, // " 	&quot;
            FG_KEY_QUOTE_DOUBLE = FG_KEY_QUOTEDBL, // "
            FG_KEY_HASH = 35, // #
            FG_KEY_DOLLAR = 36, // $
            FG_KEY_PERCENT = 37, // %
            FG_KEY_AMPERSAND = 38, // & &amp;
            FG_KEY_QUOTE = 39, // '
            FG_KEY_QUOTE_SINGLE = FG_KEY_QUOTE, // '
            FG_KEY_LEFTPAREN = 40, // (
            FG_KEY_RIGHTPAREN = 41, // )
            FG_KEY_ASTERISK = 42, // *
            FG_KEY_PLUS = 43, // +
            FG_KEY_COMMA = 44, // ,
            FG_KEY_MINUS = 45, // -
            FG_KEY_PERIOD = 46, // .
            FG_KEY_SLASH = 47, // /
            FG_KEY_0 = 48, // 0
            FG_KEY_1 = 49, // 1
            FG_KEY_2 = 50, // 2
            FG_KEY_3 = 51, // 3
            FG_KEY_4 = 52, // 4
            FG_KEY_5 = 53, // 5
            FG_KEY_6 = 54, // 6
            FG_KEY_7 = 55, // 7
            FG_KEY_8 = 56, // 8
            FG_KEY_9 = 57, // 9
            FG_KEY_COLON = 58, // :
            FG_KEY_SEMICOLON = 59, // ;
            FG_KEY_LESS = 60, // < 	&lt;
            FG_KEY_EQUALS = 61, // =
            FG_KEY_GREATER = 62, // > 	&gt;
            FG_KEY_QUESTION = 63, // ?
            FG_KEY_AT = 64, // @
            // 65 - 90 - uppercase letters

            FG_KEY_LEFTBRACKET = 91, // [
            FG_KEY_BACKSLASH = 92, // Backslash
            FG_KEY_RIGHTBRACKET = 93, // ]
            FG_KEY_CARET = 94, // ^
            FG_KEY_UNDERSCORE = 95, // _
            FG_KEY_BACKQUOTE = 96, // `
            FG_KEY_A = 97, // a
            FG_KEY_B = 98, // b
            FG_KEY_C = 99, // c
            FG_KEY_D = 100, // d
            FG_KEY_E = 101, // e
            FG_KEY_F = 102, // f
            FG_KEY_G = 103, // g
            FG_KEY_H = 104, // h
            FG_KEY_I = 105, // i
            FG_KEY_J = 106, // j
            FG_KEY_K = 107, // k
            FG_KEY_L = 108, // l
            FG_KEY_M = 109, // m
            FG_KEY_N = 110, // n
            FG_KEY_O = 111, // o
            FG_KEY_P = 112, // p
            FG_KEY_Q = 113, // q
            FG_KEY_R = 114, // r
            FG_KEY_S = 115, // s
            FG_KEY_T = 116, // t
            FG_KEY_U = 117, // u
            FG_KEY_V = 118, // v
            FG_KEY_W = 119, // w
            FG_KEY_X = 120, // x
            FG_KEY_Y = 121, // y
            FG_KEY_Z = 122, // z
            FG_KEY_LEFTBRACE = 123, // {
            FG_KEY_VERTICAL_BAR = 124, // |
            FG_KEY_RIGHTBRACE = 125, // }
            FG_KEY_TILDE = 126, // ~
            FG_KEY_DELETE = 127, // Delete

            FG_KEY_CAPSLOCK,

            FG_KEY_F1,
            FG_KEY_F2,
            FG_KEY_F3,
            FG_KEY_F4,
            FG_KEY_F5,
            FG_KEY_F6,
            FG_KEY_F7,
            FG_KEY_F8,
            FG_KEY_F9,
            FG_KEY_F10,
            FG_KEY_F11,
            FG_KEY_F12,

            FG_KEY_F13,
            FG_KEY_F14,
            FG_KEY_F15,
            FG_KEY_F16,
            FG_KEY_F17,
            FG_KEY_F18,
            FG_KEY_F19,
            FG_KEY_F20,
            FG_KEY_F21,
            FG_KEY_F22,
            FG_KEY_F23,
            FG_KEY_F24,

            FG_KEY_PRINTSCREEN,
            FG_KEY_SCROLL_LOCK,
            FG_KEY_PAUSE,
            FG_KEY_INSERT,
            FG_KEY_HOME,
            FG_KEY_END,
            FG_KEY_PAGEUP,
            FG_KEY_PAGEDOWN,
            FG_KEY_RIGHT,
            FG_KEY_LEFT,
            FG_KEY_DOWN,
            FG_KEY_UP,

            FG_KEY_NUM_DIVIDE,
            FG_KEY_NUM_MULTIPLY,
            FG_KEY_NUM_MINUS,
            FG_KEY_NUM_PLUS,
            FG_KEY_NUM_ENTER,
            FG_KEY_NUM_1,
            FG_KEY_NUM_2,
            FG_KEY_NUM_3,
            FG_KEY_NUM_4,
            FG_KEY_NUM_5,
            FG_KEY_NUM_6,
            FG_KEY_NUM_7,
            FG_KEY_NUM_8,
            FG_KEY_NUM_9,
            FG_KEY_NUM_0,
            FG_KEY_NUM_PERIOD,
            FG_KEY_NUM_EQUALS,
            FG_KEY_NUM_COMMA,

            FG_KEY_LCTRL,
            FG_KEY_LSHIFT,
            FG_KEY_LALT,
            FG_KEY_LGUI,
            FG_KEY_LWINDOWS = FG_KEY_LGUI,
            FG_KEY_LAPPLE = FG_KEY_LGUI,

            FG_KEY_RCTRL,
            FG_KEY_RSHIFT,
            FG_KEY_RALT,
            FG_KEY_RGUI,
            FG_KEY_RWINDOWS = FG_KEY_RGUI,
            FG_KEY_RAPPLE = FG_KEY_RGUI,

            FG_KEY_EXECUTE,
            FG_KEY_HELP,
            FG_KEY_MENU,
            FG_KEY_SELECT,
            FG_KEY_STOP,
            FG_KEY_CLEAR,

            FG_KEY_APPLICATION, // the Application / Compose / Context Menu (Windows) key
            FG_KEY_CONTEXT = FG_KEY_APPLICATION, // the Application / Compose / Context Menu (Windows) key 
            FG_KEY_APP_HOME,
            FG_KEY_APP_BACK,

            FG_KEY_VOLUMEUP,
            FG_KEY_VOLUMEDOWN,

            FG_KEY_RESERVED1,
            FG_KEY_RESERVED2,
            FG_KEY_RESERVED3,
            FG_KEY_RESERVED4,

            FG_NUM_VIRTUAL_KEYS
        };

        enum KeyboardMod {
            FG_MOD_NONE = 0x0000,

            FG_MOD_LSHIFT = 0x0001,
            FG_MOD_RSHIFT = 0x0002,

            FG_MOD_LCTRL = 0x0040,
            FG_MOD_RCTRL = 0x0080,

            FG_MOD_LALT = 0x0100,
            FG_MOD_RALT = 0x0200,

            FG_MOD_LGUI = 0x0400,
            FG_MOD_RGUI = 0x0800,

            FG_MOD_NUM = 0x1000,
            FG_MOD_CAPS = 0x2000,
            FG_MOD_MODE = 0x4000,

            FG_MOD_RESERVED = 0x8000
        };

        FG_ENUM_FLAGS(KeyboardMod);
    } // namespace event
} // namespace fg


#endif	/* FG_INC_KEYBOARD */
