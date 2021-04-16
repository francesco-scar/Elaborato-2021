// Keymaps and special definitions taken from https://github.com/PaulStoffregen/PS2Keyboard/blob/master/PS2Keyboard.h
// Thanks to https://github.com/PaulStoffregen/PS2Keyboard/ for his work (read that repository for more informations, credits and license)

#define PS2_TAB        9
#define PS2_ENTER     13
#define PS2_BACKSPACE     127
#define PS2_ESC       27
#define PS2_INSERT      0
#define PS2_DELETE      127
#define PS2_HOME      0
#define PS2_END       0
#define PS2_PAGEUP      25
#define PS2_PAGEDOWN      26
#define PS2_UPARROW     11
#define PS2_LEFTARROW     8
#define PS2_DOWNARROW     10
#define PS2_RIGHTARROW      21
#define PS2_F1        0
#define PS2_F2        0
#define PS2_F3        0
#define PS2_F4        0
#define PS2_F5        0
#define PS2_F6        0
#define PS2_F7        0
#define PS2_F8        0
#define PS2_F9        0
#define PS2_F10       0
#define PS2_F11       0
#define PS2_F12       0
#define PS2_SCROLL      0
#define PS2_EURO_SIGN     0

#define PS2_INVERTED_EXCLAMATION  161 // ¡
#define PS2_CENT_SIGN     162 // ¢
#define PS2_POUND_SIGN      163 // £
#define PS2_CURRENCY_SIGN   164 // ¤
#define PS2_YEN_SIGN      165 // ¥
#define PS2_BROKEN_BAR                  166 // ¦
#define PS2_SECTION_SIGN    167 // §
#define PS2_DIAERESIS     168 // ¨
#define PS2_COPYRIGHT_SIGN    169 // ©
#define PS2_FEMININE_ORDINAL    170 // ª
#define PS2_LEFT_DOUBLE_ANGLE_QUOTE 171 // «
#define PS2_NOT_SIGN      172 // ¬
#define PS2_HYPHEN      173
#define PS2_REGISTERED_SIGN   174 // ®
#define PS2_MACRON      175 // ¯
#define PS2_DEGREE_SIGN     176 // °
#define PS2_PLUS_MINUS_SIGN   177 // ±
#define PS2_SUPERSCRIPT_TWO   178 // ²
#define PS2_SUPERSCRIPT_THREE   179 // ³
#define PS2_ACUTE_ACCENT    180 // ´
#define PS2_MICRO_SIGN      181 // µ
#define PS2_PILCROW_SIGN    182 // ¶
#define PS2_MIDDLE_DOT      183 // ·
#define PS2_CEDILLA     184 // ¸
#define PS2_SUPERSCRIPT_ONE   185 // ¹
#define PS2_MASCULINE_ORDINAL   186 // º
#define PS2_RIGHT_DOUBLE_ANGLE_QUOTE  187 // »
#define PS2_FRACTION_ONE_QUARTER  188 // ¼
#define PS2_FRACTION_ONE_HALF   189 // ½
#define PS2_FRACTION_THREE_QUARTERS 190 // ¾
#define PS2_INVERTED_QUESTION_MARK  191 // ¿
#define PS2_A_GRAVE     192 // À
#define PS2_A_ACUTE     193 // Á
#define PS2_A_CIRCUMFLEX    194 // Â
#define PS2_A_TILDE     195 // Ã
#define PS2_A_DIAERESIS     196 // Ä
#define PS2_A_RING_ABOVE    197 // Å
#define PS2_AE        198 // Æ
#define PS2_C_CEDILLA     199 // Ç
#define PS2_E_GRAVE     200 // È
#define PS2_E_ACUTE     201 // É
#define PS2_E_CIRCUMFLEX    202 // Ê
#define PS2_E_DIAERESIS     203 // Ë
#define PS2_I_GRAVE     204 // Ì
#define PS2_I_ACUTE     205 // Í
#define PS2_I_CIRCUMFLEX    206 // Î
#define PS2_I_DIAERESIS     207 // Ï
#define PS2_ETH       208 // Ð
#define PS2_N_TILDE     209 // Ñ
#define PS2_O_GRAVE     210 // Ò
#define PS2_O_ACUTE     211 // Ó
#define PS2_O_CIRCUMFLEX    212 // Ô
#define PS2_O_TILDE     213 // Õ
#define PS2_O_DIAERESIS     214 // Ö
#define PS2_MULTIPLICATION    215 // ×
#define PS2_O_STROKE      216 // Ø
#define PS2_U_GRAVE     217 // Ù
#define PS2_U_ACUTE     218 // Ú
#define PS2_U_CIRCUMFLEX    219 // Û
#define PS2_U_DIAERESIS     220 // Ü
#define PS2_Y_ACUTE     221 // Ý
#define PS2_THORN     222 // Þ
#define PS2_SHARP_S     223 // ß
#define PS2_a_GRAVE     224 // à
#define PS2_a_ACUTE     225 // á
#define PS2_a_CIRCUMFLEX    226 // â
#define PS2_a_TILDE     227 // ã
#define PS2_a_DIAERESIS     228 // ä
#define PS2_a_RING_ABOVE    229 // å
#define PS2_ae        230 // æ
#define PS2_c_CEDILLA     231 // ç
#define PS2_e_GRAVE     232 // è
#define PS2_e_ACUTE     233 // é
#define PS2_e_CIRCUMFLEX    234 // ê
#define PS2_e_DIAERESIS     235 // ë
#define PS2_i_GRAVE     236 // ì
#define PS2_i_ACUTE     237 // í
#define PS2_i_CIRCUMFLEX    238 // î
#define PS2_i_DIAERESIS     239 // ï
#define PS2_eth       240 // ð
#define PS2_n_TILDE     241 // ñ
#define PS2_o_GRAVE     242 // ò
#define PS2_o_ACUTE     243 // ó
#define PS2_o_CIRCUMFLEX    244 // ô
#define PS2_o_TILDE     245 // õ
#define PS2_o_DIAERESIS     246 // ö
#define PS2_DIVISION      247 // ÷
#define PS2_o_STROKE      248 // ø
#define PS2_u_GRAVE     249 // ù
#define PS2_u_ACUTE     250 // ú
#define PS2_u_CIRCUMFLEX    251 // û
#define PS2_u_DIAERESIS     252 // ü
#define PS2_y_ACUTE     253 // ý
#define PS2_thorn     254 // þ
#define PS2_y_DIAERESIS     255 // ÿ

#define PS2_L_ALT 128
#define PS2_L_SHIFT 129


const PROGMEM char keymap[][132] = {
// without shift
//   00         01          02            03            04            05            06              07
    {0,         PS2_F9,     0,            PS2_F5,       PS2_F3,       PS2_F1,       PS2_F2,         PS2_F12,        // 00 h
     0,         PS2_F10,    PS2_F8,       PS2_F6,       PS2_F4,       PS2_TAB,      '\\',           0,              // 08 h
     0,         PS2_L_ALT,  PS2_L_SHIFT,  0,            0 /*Lctrl*/, 'q',           '1',            0,              // 10 h
     0,         0,          'z',          's',          'a',          'w',          '2',            0,              // 18 h
     0,         'c',        'x',          'd',          'e',          '4',          '3',            0,              // 20 h
     0,         ' ',        'v',          'f',          't',          'r',          '5',            0,              // 28 h
     0,         'n',        'b',          'h',          'g',          'y',          '6',            0,              // 30 h
     0,         0,          'm',          'j',          'u',          '7',          '8',            0,              // 38 h
     0,         ',',        'k',          'i',          'o',          '0',          '9',            0,              // 40 h
     0,         '.',        '-',          'l',          PS2_o_GRAVE,  'p',          '\'',           0,              // 48 h
     0,         0,          PS2_a_GRAVE,  0,            PS2_e_GRAVE,  PS2_i_GRAVE,  0,              0,              // 50 h
     0 /*CapsLock*/, 0 /*Rshift*/, PS2_ENTER /*Enter*/, '+', 0,       PS2_u_GRAVE,  0,              0,              // 58 h
     0,         '<',        0,            0,            0,            0,            PS2_BACKSPACE,  0,              // 60 h
     0,         '1',        0,            '4',          '7',          0,            0,              0,              // 68 h
     '0',       '.',        '2',          '5',          '6',          '8',          PS2_ESC,        0 /*NumLock*/,  // 70 h
     PS2_F11,   '+',        '3',          '-',          '*',          '9',          PS2_SCROLL,     0,              // 78 h
     0,         0,          0,            PS2_F7 },                                                                 // 80 h
     
    // with shift
    {0,         PS2_F9,     0,            PS2_F5,       PS2_F3,       PS2_F1,       PS2_F2,         PS2_F12,
     0, PS2_F10, PS2_F8, PS2_F6, PS2_F4, PS2_TAB, '|', 0,
     0, 0 /*Lalt*/, 0 /*Lshift*/, 0, 0 /*Lctrl*/, 'Q', '!', 0,
     0, 0, 'Z', 'S', 'A', 'W', '\"', 0,
     0, 'C', 'X', 'D', 'E', '$', PS2_POUND_SIGN, 0,
     0, ' ', 'V', 'F', 'T', 'R', '%', 0,
     0, 'N', 'B', 'H', 'G', 'Y', '&', 0,
     0, 0, 'M', 'J', 'U', '/', '(', 0,
     0, ';', 'K', 'I', 'O', '=', ')', 0,
     0, ':', '_', 'L', PS2_c_CEDILLA, 0, '?', 0,
     0, 0, PS2_DEGREE_SIGN, 0, PS2_e_ACUTE, '^', 0, 0,
     0 /*CapsLock*/, 0 /*Rshift*/, PS2_ENTER /*Enter*/, '*', 0, PS2_SECTION_SIGN, 0, 0,
     0, '>', 0, 0, 0, 0, PS2_BACKSPACE, 0,
     0, '1', 0, '4', '7', 0, 0, 0,
     '0', '.', '2', '5', '6', '8', PS2_ESC, 0 /*NumLock*/,
     PS2_F11, '+', '3', '-', '*', '9', PS2_SCROLL, 0,
     0, 0, 0, PS2_F7 },
    // with altgr
    {0, PS2_F9, 0, PS2_F5, PS2_F3, PS2_F1, PS2_F2, PS2_F12,
     0, PS2_F10, PS2_F8, PS2_F6, PS2_F4, PS2_TAB, PS2_NOT_SIGN, 0,
     0, 0 /*Lalt*/, 0 /*Lshift*/, 0, 0 /*Lctrl*/, 'q', PS2_SUPERSCRIPT_ONE, 0,
     0, 0, 'z', 's', 'a', 'w', PS2_SUPERSCRIPT_TWO, 0,
     0, 'c', 'x', 'd', PS2_EURO_SIGN, PS2_FRACTION_ONE_QUARTER, PS2_SUPERSCRIPT_THREE, 0,
     0, ' ', 'v', 'f', 't', 'r', PS2_FRACTION_ONE_HALF, 0,
     0, 'n', 'b', 'h', 'g', 'y', PS2_NOT_SIGN, 0,
     0, 0, 'm', 'j', 'u', '{', '[', 0,
     0, ',', 'k', 'i', 'o', '}', ']', 0,
     0, '.', '-', 'l', '@', 'p', '\'', 0,
     0, 0, '#', 0, '[', '~', 0, 0,
     0 /*CapsLock*/, 0 /*Rshift*/, PS2_ENTER /*Enter*/, ']', 0, 0, 0, 0,
     0, PS2_LEFT_DOUBLE_ANGLE_QUOTE, 0, 0, 0, 0, PS2_BACKSPACE, 0,
     0, '1', 0, '4', '7', 0, 0, 0,
     '0', '.', '2', '5', '6', '8', PS2_ESC, 0 /*NumLock*/,
     PS2_F11, '+', '3', '-', '*', '9', PS2_SCROLL, 0,
     0, 0, 0, PS2_F7 }
};
