/* Copyright 2
019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "sendstring_german.h"

enum layers {
    _NAV = 0,
    _NEO2,
    _NAV2,
    _SYMB,
    _NUMB,
};

// Tap Dance declarations
enum {
    X_CTL,
    TD_Copy_Cut_Paste_WinPaste,
    TD_LParen_Parens_Func,
    TD_AL_WL,
    TD_AR_WR,
    TD_AD_PD,
    TD_AU_PU,
    TD_Quotes,
    TD_F12_F5,
    TD_Tab_CtrlS,
    TD_Enter_CtrlAltTab,
    TD_Copy_Paste,
};

// Quad Tap Dance
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);

void copy_finished(qk_tap_dance_state_t *state, void *user_data);
void copy_reset(qk_tap_dance_state_t *state, void *user_data);

void paren_finished(qk_tap_dance_state_t *state, void *user_data);
void paren_reset(qk_tap_dance_state_t *state, void *user_data);

void al_finished(qk_tap_dance_state_t *state, void *user_data);
void al_reset(qk_tap_dance_state_t *state, void *user_data);

void ar_finished(qk_tap_dance_state_t *state, void *user_data);
void ar_reset(qk_tap_dance_state_t *state, void *user_data);

void au_finished(qk_tap_dance_state_t *state, void *user_data);
void au_reset(qk_tap_dance_state_t *state, void *user_data);

void ad_finished(qk_tap_dance_state_t *state, void *user_data);
void ad_reset(qk_tap_dance_state_t *state, void *user_data);

void quotes_finished(qk_tap_dance_state_t *state, void *user_data);
void quotes_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 
 * Base Layer: Navigation
 * 
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |  Play  | Manic| Undo | URL  | Redo | Find |                              |CloseT| TabL |  MC  | TabR | ReoT |CtrlAltD|
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |  Esc   |SpaceS|  AL  |  AU  |  AR  | Bspc |                              |  WL  |  ML  |  MU  |  MR  |  WR  | Mute   |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |  Alt   |SpacCS| Cut  |  AD  | Co/Pa|SelAll|AcCall|F12/F5|  | ToTo | ToMo |Screen|  WD  |  MD  |  WU  |      | Logout |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        | GUI  |T B/N |  LC  |  RC  | Del  |  | ToSp |  Tab | Enter| Ctrl | Alt  |
//  *                        |      |      |      |      |      |  |      | Save | WinA |ToNeo2|      |
//  *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
       KC_MPLY, MEH(KC_W), C(KC_Y), C(KC_L), C(KC_Z), C(KC_F),                                     C(KC_W), S(C(KC_TAB)), KC_BTN3, C(KC_TAB), C(S(KC_T)), C(A(KC_DEL)),
       KC_ESC, MT(MOD_LSFT,KC_SPC), TD(TD_AL_WL), TD(TD_AU_PU),  TD(TD_AR_WR), KC_BSPC,                                     KC_WH_L, KC_MS_L, KC_MS_U, KC_MS_R, KC_WH_R, C(S(KC_M)),
       KC_LALT, MT(MOD_LCTL | MOD_LSFT, KC_SPC), C(KC_X), TD(TD_AD_PD), TD(TD_Copy_Cut_Paste_WinPaste), C(KC_A), C(S(KC_S)), TD(TD_F12_F5), A(C(S(KC_0))), A(C(KC_DOT)),LSG(KC_S), KC_WH_D, KC_MS_D, KC_WH_U, _______, LSG(KC_L),
                                  KC_LGUI, TG(1),KC_BTN1, KC_BTN2,KC_DEL, A(C(KC_COMM)), TD(TD_Tab_CtrlS),TD(TD_Enter_CtrlAltTab), LM(_NEO2, MOD_LCTL), KC_LALT
     ),
/*
 * Base Layer: NEO2
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Play  |   X  |   V  |   L  |   C  |   W  |                              |   K  |   H  |   G  |   F  |   Q  |  ß de  |
 * |--------+------+------+------+------|------|                              |------+------+------+------+------+--------|
 * |  Esc   |   U  |Shft/I|Ctrl/A|Alt/E |   O  |                              |   S  | Alt/N|Ctrl/R|Shft/T|   D  |  Y de  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Shft  | Ü de | Ö de | Ä de |   P  | Z de |Leader|F12/F5|  | ToTo | ToMo |   B  |   M  | ,  ; | .  : |   J  |  ß de  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | DEL  |      | Space| Bksp | CWIN |  | ToSp | Tab  | Enter|  LC  |  RC  |
 *                        |      |      | Symb | Numb | Numb |  |      | Nav2 | Symb |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NEO2] = LAYOUT(
      KC_MPLY, TD(X_CTL),KC_V,KC_L,KC_C,KC_W,KC_K,KC_H,KC_G,KC_F,KC_Q,KC_MINS,
      KC_ESC,KC_U,MT(MOD_LSFT,KC_I),MT(MOD_LCTL,KC_A),MT(MOD_LALT,KC_E),KC_O,KC_S,MT(MOD_LALT,KC_N),MT(MOD_RCTL,KC_R),MT(MOD_RSFT,KC_T),KC_D,KC_Z,
      KC_LSFT,KC_LBRC,KC_SCLN,KC_QUOT,KC_P,KC_Y,KC_LEAD,TD(TD_F12_F5),A(C(S(KC_0))),A(C(KC_DOT)),KC_B,KC_M,KC_COMM,KC_DOT,KC_J,KC_MINS,
      KC_DEL,_______,LT(_SYMB, KC_SPC),LT(_NUMB, KC_BSPC),LM(_NUMB,MOD_LGUI | MOD_LCTL),A(C(KC_COMM)),LT(_NAV2, KC_TAB),LT(_SYMB,KC_ENT),KC_BTN1,KC_BTN2
    ),
    
/* 
 * Nav Layer: Navigation 2
 *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |  Play  | Manic| Undo | URL  | Redo | Find |                              |CloseT| TabL |  MC  | TabR | ReoT |CtrlAltD|
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |  Esc   |SpaceS|  AL  |  AU  |  AR  | Bspc |                              |  WL  |  ML  |  MU  |  MR  |  WR  | Mute   |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |  Alt   |SpacCS| Cut  |  AD  | Co/Pa|SelAll|AcCall|F12/F5|  | ToTo | ToMo |Screen|  WD  |  MD  |  WU  |      | Logout |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        | GUI  |      |  LC  |  RC  | Del  |  | ToSp |      | Enter| Ctrl | Alt  |
//  *                        |      |      |      |      |      |  |      |      | WinA |      |      |
//  *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV2] = LAYOUT(
       KC_MPLY, MEH(KC_W), C(KC_Y), C(KC_L), C(KC_Z), C(KC_F),                                     C(KC_W), S(C(KC_TAB)), KC_BTN3, C(KC_TAB), C(S(KC_T)), C(A(KC_DEL)),
       KC_ESC, MT(MOD_LSFT,KC_SPC), TD(TD_AL_WL), TD(TD_AU_PU),  TD(TD_AR_WR), KC_BSPC,                                    KC_WH_L, KC_MS_L, KC_MS_U, KC_MS_R, KC_WH_R, C(S(KC_M)),
       KC_LALT, MT(MOD_LCTL | MOD_LSFT, KC_SPC), C(KC_X), KC_DOWN, TD(TD_Copy_Paste), C(KC_A), C(S(KC_S)), TD(TD_F12_F5), A(C(S(KC_0))), A(C(KC_DOT)),LSG(KC_S), KC_WH_D, KC_MS_D, KC_WH_U, _______, LSG(KC_L),
                                  KC_LGUI,_______,KC_BTN1, KC_BTN2,KC_DEL, A(C(KC_COMM)), TD(TD_Tab_CtrlS),TD(TD_Enter_CtrlAltTab), LM(_NEO2, MOD_LCTL), KC_LALT
     ),
/*
 * Symbol Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  `   |  _   |  [   |  ]   |  ^   |                              |   !  |  <   |   >  |   =  |   &  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  \   |  /   |  {   |  }   |  *   |                              |   ?  |  (   |  )   |   -  |   :  |   @    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  #   |  $   |  |   |  ~   |  `   |      |      |  |      |      |   +  |  %   |  "   |   '  |   ;  |   €    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |   _  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMB] = LAYOUT(
      _______, KC_EQL, S(KC_SLSH), ALGR(KC_8), ALGR(KC_9), KC_GRV,                                     S(KC_1), KC_NUBS, S(KC_NUBS), S(KC_0), S(KC_6), KC_BSLS,
      _______, ALGR(KC_MINS), S(KC_7),  ALGR(KC_7), ALGR(KC_0), KC_ASTR,                                    S(KC_MINS), TD(TD_LParen_Parens_Func), S(KC_9), KC_SLSH, S(KC_DOT), ALGR(KC_Q),
      _______, KC_NUHS, S(KC_4), ALGR(KC_NUBS), ALGR(KC_RBRC), S(KC_EQL), _______, _______, _______, _______, KC_RBRC, S(KC_5),  S(KC_2),TD(TD_Quotes), S(KC_COMM), ALGR(KC_E),
                                 _______, _______, _______, _______, _______,  _______,  _______, S(KC_SLSH), _______, _______
    ),

/*
 * Number Layer: Number keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |  -   |  7   |  8   |  9   |   /  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |  +   |  4   |  5   |  6   |   *  |   =    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |  (   |  1   |  2   |  3   |   )  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |  0   |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMB] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PMNS, KC_7, KC_8, KC_9, KC_PSLS, _______,
      _______, _______, _______, _______, _______, _______,                                     KC_PPLS, KC_4, KC_5, KC_6, KC_PAST, KC_PEQL,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, S(KC_8), KC_1, KC_2, KC_3, S(KC_9), _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_0, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

LEADER_EXTERNS();

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_C) { // Inline Code
            SEND_STRING("''" SS_TAP(X_LEFT));
        }
        
        SEQ_ONE_KEY(KC_R) { // Send root
            SEND_STRING("'00000000-00000000-0000-000000000000'");
        }
        
        SEQ_ONE_KEY(KC_N) { // Send NX user name 
            SEND_STRING("xlinderp");
        }
        
        SEQ_ONE_KEY(KC_U) { // Send unique
            SEND_STRING("/\\b[0-9a-f]{{8}}\\b-[0-9a-f]{{4}}-[0-9a-f]{{4}}-[0-9a-f]{{4}}-\\b[0-9a-f]{{12}}\\b/");
        }

        SEQ_TWO_KEYS(KC_E, KC_P) { // Email outlook
            SEND_STRING("linder.peter@outlook.de");
        }
    }
}



#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 
        0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 
        0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfc, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 
        0x0f, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x00, 0xe0, 
        0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfc, 0xff, 
        0xff, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
        0x1f, 0xbf, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
        0x1f, 0x1f, 0x1f, 0x1f, 0xff, 0xff, 0xfe, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xf8, 0xf8, 
        0xf8, 0xf8, 0xf8, 0xf0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0x80, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xf8, 0xf8, 0xf8, 0x38, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 
        0xf0, 0xff, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 
        0xd8, 0x18, 0x18, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xe7, 0xe3, 0xe1, 0xe0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xcc, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 
        0x01, 0x01, 0x01, 0x1b, 0x1f, 0x1f, 0x07, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x07, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0x7f, 0x3f, 0x3f, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
        0x4c, 0x00, 0x00, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0x7f, 0xe0, 0xc0, 0x8d, 0x8f, 0xc0, 
        0xc0, 0xe1, 0xc0, 0xf0, 0xc3, 0xc3, 0xf0, 0xc0, 0xc0, 0xcf, 0x81, 0xc1, 0xc3, 0xc3, 0x00, 0x00, 
        0x00, 0x06, 0x2f, 0x38, 0x10, 0x18, 0x34, 0x24, 0x3c, 0x00, 0x04, 0x3f, 0x05, 0x04, 0x3e, 0x26, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0x7f, 0xff, 
        0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf8, 
        0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xff, 
        0xfe, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 
        0x0f, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 
        0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _NEO2:
            oled_write_P(PSTR("Neo2\n"), false);
            break;
        case _NAV2:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _NUMB:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM nav_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_BLUE});
const rgblight_segment_t PROGMEM neo2_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_MAGENTA});
const rgblight_segment_t PROGMEM nav2_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_BLUE});
const rgblight_segment_t PROGMEM symb_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_GREEN});
const rgblight_segment_t PROGMEM num_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_RED});
 
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    nav_layers,
    neo2_layers,
    nav2_layers,
    symb_layers,
    num_layers
);

void keyboard_post_init_keymap(void) {
    rgblight_layers = my_rgb_layers;
}

#endif

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_BLUE);
#ifdef RGBLIGHT_LAYERS
    rgblight_layers = my_rgb_layers;
#else
    rgblight_sethsv_noeeprom(HSV_BLUE);
#endif
    /*debug_enable=true;*/
    /*debug_matrix=true;*/
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    for (int i = _NEO2; i < 5; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
#endif
    return state;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _NEO2:
                // History scrubbing.
                if (clockwise) {
                    tap_code16(C(KC_Y));
                } else {
                    tap_code16(C(KC_Z));
                }
                break;
            default:
                // Switch between windows on Windows with alt tab.
                if (clockwise) {
                    tap_code16(S(KC_TAB));
                } else {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    }
                    alt_tab_timer = timer_read();
                    tap_code16(KC_TAB);
                }
                break;
        }
    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case _NEO2:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            case _NAV:
                // Zoom
                if (clockwise) {
                    tap_code16(C(KC_PPLS));
                } else {
                    tap_code16(C(KC_PMNS));
                }
                break;    
            default:
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
    return true;
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_X); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTRL); break;
        case TD_DOUBLE_TAP: SEND_STRING("''" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);break;
        case TD_TRIPLE_TAP: register_code(KC_A); break;
        case TD_TRIPLE_HOLD: register_code(KC_B);break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTRL); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_TRIPLE_TAP: unregister_code(KC_A); break;
        case TD_TRIPLE_HOLD: unregister_code(KC_B);break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void copy_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(C(KC_C)); break;
        case TD_SINGLE_HOLD: register_code16(C(KC_X)); break;
        case TD_DOUBLE_TAP: register_code16(C(KC_V)); break;
        case TD_DOUBLE_HOLD: register_code16(LGUI(KC_V)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void copy_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(C(KC_C)); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_X)); break;
        case TD_DOUBLE_TAP: unregister_code16(C(KC_V)); break;
        case TD_DOUBLE_HOLD: unregister_code16(LGUI(KC_V)); break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void paren_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(S(KC_8)); break;
        case TD_SINGLE_HOLD: register_code16(ALGR(KC_8)); break;
        case TD_DOUBLE_TAP: SEND_STRING("()" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_HOLD: SEND_STRING("[]" SS_TAP(X_LEFT)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_8)); register_code16(S(KC_8));break;
        case TD_TRIPLE_TAP: SEND_STRING("(){" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "}" SS_TAP(X_LEFT) SS_TAP(X_UP) SS_TAP(X_TAB)); break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void paren_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(S(KC_8)); break;
        case TD_SINGLE_HOLD: unregister_code16(ALGR(KC_8)); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(S(KC_8)); break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void al_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_LEFT); break;
        case TD_SINGLE_HOLD: register_code16(C(KC_LEFT)); break;
        case TD_DOUBLE_TAP: register_code16(C(S(KC_LEFT))); break;
        case TD_DOUBLE_HOLD: register_code16(LGUI(KC_LEFT)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT);register_code16(KC_LEFT);break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void al_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LEFT); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_LEFT)); break;
        case TD_DOUBLE_TAP: unregister_code16(C(S(KC_LEFT))); break;
        case TD_DOUBLE_HOLD: unregister_code16(LGUI(KC_LEFT)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT); break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void ar_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_RIGHT); break;
        case TD_SINGLE_HOLD: register_code16(C(KC_RIGHT)); break;
        case TD_DOUBLE_TAP: register_code16(C(S(KC_RIGHT))); break;
        case TD_DOUBLE_HOLD: register_code16(LGUI(KC_RIGHT)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RIGHT);register_code16(KC_RIGHT);break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void ar_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_RIGHT); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_RIGHT)); break;
        case TD_DOUBLE_TAP: unregister_code16(C(S(KC_RIGHT))); break;
        case TD_DOUBLE_HOLD: unregister_code16(LGUI(KC_RIGHT)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RIGHT); break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void au_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_UP); break;
        case TD_SINGLE_HOLD: register_code16(KC_PGUP); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: register_code16(KC_HOME); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void au_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_UP); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_PGUP); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_HOME); break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void ad_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_DOWN); break;
        case TD_SINGLE_HOLD: register_code16(KC_PGDOWN); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: register_code16(KC_END); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void ad_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_DOWN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_PGDOWN); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_END); break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void quotes_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(S(KC_NUHS)); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_2)); break;
        case TD_DOUBLE_TAP: SEND_STRING("''" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_HOLD: tap_code16(S(KC_2));tap_code16(S(KC_2));SEND_STRING(SS_TAP(X_LEFT)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_NUHS)); register_code16(S(KC_NUHS));break;
        case TD_TRIPLE_TAP: tap_code16(S(KC_NUHS));tap_code16(C(KC_V));SEND_STRING("', --"); break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void quotes_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(S(KC_NUHS)); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_2)); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(S(KC_NUHS)); break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [TD_Copy_Cut_Paste_WinPaste] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_finished, copy_reset),
    [TD_LParen_Parens_Func] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, paren_finished, paren_reset),
    [TD_AL_WL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, al_finished, al_reset),
    [TD_AR_WR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ar_finished, ar_reset),
    [TD_AD_PD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ad_finished, ad_reset),
    [TD_AU_PU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, au_finished, au_reset),
    [TD_Quotes] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quotes_finished, quotes_reset),
    [TD_F12_F5] = ACTION_TAP_DANCE_DOUBLE(KC_F12, KC_F5),// Tap once for F12, twice for F5
    [TD_Tab_CtrlS] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, C(KC_S)),
    [TD_Enter_CtrlAltTab] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, A(C(KC_TAB))),
    [TD_Copy_Paste] = ACTION_TAP_DANCE_DOUBLE(C(KC_C), C(KC_V)),
};
#endif
