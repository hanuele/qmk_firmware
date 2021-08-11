/* Copyright 2021 Peter Linder
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
#include "oneshot.h"
//import own defined keycodes. this is a german layout. but importing the german header file did result in an error, so I skipped it and just translated the keys.
#include "hanuele.h"

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "pointing_device.h"
#include "pimoroni_trackball.h"
#endif

// My layers
enum layers {
    _NEO2 = 0,
    _MOUS,
    _NAV,
    _RSYM,
    _LSYM,
    _FUNC,
    _NUMB,
    _AACC,

};

enum keycodes {
    // Custom oneshot mod implementation with no timers (Code from https://github.com/precondition/dactyl-manuform-keymap).
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    // Keycode for caps word (Code from https://github.com/andrewjrae/kyria-keymap#caps-word).
    CAPS_WORD,
    MY_MOUSEBTN_1,
    MY_MOUSEBTN_2,
    MY_MOUSEBTN_3
};
// State for Caps word.     
bool caps_word_on;
void caps_word_enable(void);
void caps_word_disable(void);

uint8_t mod_state;


// Tap Dance declarations
enum {
    TD_Copy_Cut_Paste_WinPaste,
    TD_LParen_Parens_Func,
    TD_RParen_Parens_Func,
    TD_LBrace_Braces_Tag,
    TD_RBrace_Braces_Tag, 
    TD_Quotes,
    TD_TO_TM_TT,
    TD_F12_F5,
    TD_Tab_CtrlS,
    TD_Bspc_Del_Delwl_Delwr,
    TD_URL,
    TD_Period,
    TD_Comma,
    TD_Caps,
    TD_Find,
    TD_OneshotMode,
    TD_COMMENT 
};

// Trio Tap Dance (I did remove quad tap and triple hold)
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);

//my update routine to change rgb based on last activated mode
void update_mode_rgb(void);


// For the x tap dance. Put it here so it can be used in any keymap
void copy_finished(qk_tap_dance_state_t *state, void *user_data);
void copy_reset(qk_tap_dance_state_t *state, void *user_data);

void paren_finishedl(qk_tap_dance_state_t *state, void *user_data);
void paren_resetl(qk_tap_dance_state_t *state, void *user_data);

void braces_finishedl(qk_tap_dance_state_t *state, void *user_data);
void braces_resetl(qk_tap_dance_state_t *state, void *user_data);

void quotes_finished(qk_tap_dance_state_t *state, void *user_data);
void quotes_reset(qk_tap_dance_state_t *state, void *user_data);

void talon_finished(qk_tap_dance_state_t *state, void *user_data);

void del_finished(qk_tap_dance_state_t *state, void *user_data);
void del_reset(qk_tap_dance_state_t *state, void *user_data);

void url_finished(qk_tap_dance_state_t *state, void *user_data);
void url_reset(qk_tap_dance_state_t *state, void *user_data);

void period_finished(qk_tap_dance_state_t *state, void *user_data);
void period_reset(qk_tap_dance_state_t *state, void *user_data);

void comma_finished(qk_tap_dance_state_t *state, void *user_data);
void comma_reset(qk_tap_dance_state_t *state, void *user_data);

void caps_finished(qk_tap_dance_state_t *state, void *user_data);
void caps_reset(qk_tap_dance_state_t *state, void *user_data);

void find_finished(qk_tap_dance_state_t *state, void *user_data);
void find_reset(qk_tap_dance_state_t *state, void *user_data);

void save_finished(qk_tap_dance_state_t *state, void *user_data);
void save_reset(qk_tap_dance_state_t *state, void *user_data);

void oneshotMode_finished(qk_tap_dance_state_t *state, void *user_data);
void oneshotMode_reset(qk_tap_dance_state_t *state, void *user_data);

void browser_finished(qk_tap_dance_state_t *state, void *user_data);
void browser_reset(qk_tap_dance_state_t *state, void *user_data);

void comment_finished(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Layer 0: Base Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Play  |  X   |  V   |  L   |  C   |  W   |                              |   K  |   H  |   G  |   F  |   Q  |CtrlAltD|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ESC   |U-SHFT| I-LT5| A-LT1| E-LT3|  O   |                              |   S  |N-LT4 |R-LT2 |T-LT6 |D-SHFT|  Y de  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Play  |Ü-CTRL|Ö-ALT |  Ä   |  P   |  Z   |      |F12/F5|  | Talon|      |   B  |   M  |,-LALT|.-CTRL|   J  |  ß de  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Enpass|      | BSPC |      | Caps |  |      | Save |  LT7 |      |      |
 *                        |      |      |      |      |      |  |      |      |SPACE |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
     [_NEO2] = LAYOUT(
       KC_MPLY, KC_X,KC_V,KC_L,KC_C,KC_W,                                     KC_K,KC_H,KC_G,KC_F,KC_Q,C(A(KC_DEL)),
       KC_ESC, LSFT_T(KC_U), LT5, LT1, LT3, KC_O,                                     KC_S, LT4, LT2, LT6, LSFT_T(KC_D),KC_Z,
       KC_MPLY, LCTL_T(KC_LBRC), LALT_T(KC_SCLN), KC_QUOT,KC_P,KC_Y, _______, BROWSER, TALON,_______,  KC_B, KC_M, COMMA, PERIOD, KC_J,KC_MINS,
                                  C(A(KC_E)), _______, DELETE, _______, CAPSLOCK, ONESHOT, SAVE, LT7, _______, _______
     ),
 /*
  * Layer 1: Mouse
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |MOUSE1| W-UP |MOUSE2|      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |      |MOUSE1|      |MOUSE2|      |                              |      |M-LEFT|M-DOWN| M-UP |M-RGHT|        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |MOUSE3|      |      |      |  |      |      |      |W-LEFT|W-DOWN|W-RGHT|      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_MOUS] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, MY_MOUSEBTN_1, KC_WH_U, MY_MOUSEBTN_2, _______, _______,
       _______, _______, MY_MOUSEBTN_1, _______, MY_MOUSEBTN_2, _______,                                     _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
       _______, _______, _______, _______, MY_MOUSEBTN_3, _______, _______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),

 /*
  * Layer 2: Navigation
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |PAGEUP|      |      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        | LEFT |  UP  | DOWN | RIGHT|      |                              |      | LGUI |      |C_S_T |LCTL_T|        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      | HOME |PAGEDW|  END |      |      |      |  |      |      |      |      |      |      |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_NAV] = LAYOUT(
       _______, _______, _______, KC_PGUP, _______, _______,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT, _______,                                     _______, KC_LGUI, _______,C_S_T(KC_TAB),LCTL_T(KC_ENT), _______,
       _______, _______, _______, KC_PGDOWN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),
 /*
  * Layer 3: Right symbols
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |      |   =  |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |  &   |  ~   |  *   |      |      |                              |      |  (   |  )   |   -  |   @  |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |  |      |      |      |   +  |  %   |COMMEN|   €  |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |   "  |      |  |      |   _  |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_RSYM] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, _______, S(KC_0), _______, _______, _______,
       _______, S(KC_6), ALGR(KC_RBRC), S(KC_MINS), _______, _______,                                     _______, PARENS, PARENSR, KC_SLSH, ALGR(KC_Q),_______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RBRC, S(KC_5),COMMENT , ALGR(KC_E), _______,
                                  _______, _______, _______, S(KC_2), _______, _______, S(KC_SLSH), _______, _______, _______
     ),
 /*
  * Layer 4: Left symbols
  *
    ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |    `   |  \   |  /   |  {   |  }   |      |                              |      |      |  ?   |  !   |  ^   |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |  #   |  $   |  |   |  '   |  `   |      |      |  |      |      |      |      |      |      |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |   "  |      |  |      |   _  |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_LSYM] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
       ALGR(KC_MINS), S(KC_7), BRACES, BRACESR, S(KC_RBRC), _______,                                     _______, _______, S(KC_MINS), S(KC_1), KC_GRV, _______,
       KC_EQL, KC_NUHS, S(KC_4), ALGR(KC_NUBS), QUOTES, S(KC_EQL), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, S(KC_2), _______, _______, S(KC_SLSH), _______, _______, _______
     ),
 /*
  * Layer 5: Func keys
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |  F10 |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |      |CTLALT|      |      |      |                              |      |  F4  |  F5  |  F6  |  F11 |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |  F12 |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_FUNC] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, KC_F7, KC_F8, KC_F9, KC_F10, _______,
       _______, _______, C(KC_LALT), _______, _______, _______,                                  _______, KC_F4, KC_F5, KC_F6, KC_F11, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F1, KC_F2, KC_F3, KC_F12, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),
 /*
  * Layer 6: Numbers
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |  /   |  7   |  8   |  9   |  +   |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |  0   |  1   |  2   |  3   |  -   |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |  *   |  4   |  5   |  6   |  =   |      |      |  |      |      |      |      |      |      |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_NUMB] = LAYOUT(
       _______, KC_PSLS, KC_7, KC_8, KC_9, KC_RBRC,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_0, KC_1, KC_2, KC_3, KC_PMNS,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_PAST, KC_4, KC_5, KC_6, KC_PEQL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),
 /*
  * Layer 7: Always accessible
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      | Manic| URL  |      |      |                              |      |      | ReoT |DupTab|      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        | ESC  | UNDO | REDO |ENTER | Find |                              |      | DF1  | TabL | TabR |CloseT| Mute   |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |Screen|      |Co/Pa |      |      |      |  |      |      |      | DF0  |      |      | RESET |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      | TAB  |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_AACC] = LAYOUT(
       _______, _______, A(C(S(KC_W))), URL, _______, _______,                                     _______, _______, C(S(KC_T)), C(S(KC_K)), _______, _______,
       _______, KC_ESC, C(KC_Y), C(KC_Z), KC_ENT, FIND,                                     _______, DF(_MOUS), S(C(KC_TAB)), C(KC_TAB), C(KC_W), KC_MUTE,
       _______, _______, LSG(KC_S), _______, COPY, _______, _______, _______, _______, _______, _______, DF(_NEO2), _______, _______, _______, _______,
                                  _______, _______, KC_TAB, _______, _______, _______, _______, _______, _______, _______
     )
};

#ifdef PIMORONI_TRACKBALL_ENABLE
// {{{
#include "timer.h"
#include "quantum/quantum.h"
#include "i2c_master.h"

 //static int16_t mouse_auto_layer_timer = 0;
#define MOUSE_TIMEOUT 600
#define TRACKBALL_TIMEOUT 5

#define SIGN(x) ((x > 0) - (x < 0))

//static bool rgb_changed = false;
static uint8_t rgb_hue = 1;
static uint8_t rgb_brightness = 1;
static uint8_t rgb_sat = 255;

void matrix_init_user() {
    trackball_init();
}

void update_member(int8_t* member, int16_t* offset) {//{{{
    if (*offset > 127) {
        *member = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *member = -127;
        *offset += 127;
    } else {
        *member = *offset;
        *offset = 0;
    }
}

static int16_t x_offset = 0;
static int16_t y_offset = 0;
static int16_t v_offset = 0;
static int16_t h_offset = 0;

static int16_t tb_timer = 0;
void pointing_device_task() {
    report_mouse_t mouse = pointing_device_get_report();

    if (trackball_get_interrupt() && (!tb_timer || timer_elapsed(tb_timer) > TRACKBALL_TIMEOUT)) {
        tb_timer = timer_read() | 1;
        
        trackball_state_t state = trackball_get_state();

        if (state.button_triggered) {
            if(state.button_down) {
                mouse.buttons |= MOUSE_BTN1;
            } else {
                mouse.buttons &= ~MOUSE_BTN1;
            }  
            pointing_device_set_report(mouse);
            pointing_device_send();
        } else {
            if (layer_state_is(_LSYM) || layer_state_is(_RSYM)) {
                h_offset += state.x;
                v_offset -= state.y;
 
            } else if (layer_state_is(_NUMB) || layer_state_is(_FUNC)) {
                v_offset -= state.x;
            } else if ((state.x || state.y) && !state.button_down) {

               //  if (!mouse_auto_layer_timer) { 
                //     layer_on(_MOUS); 
               //  } 
               //  mouse_auto_layer_timer = timer_read() | 1;
                uint8_t scale = 3;
              
                x_offset += state.x * state.x * SIGN(state.x) * scale;
                y_offset += state.y * state.y * SIGN(state.y) * scale;

            }
        }

    }

    while (x_offset || y_offset || h_offset || v_offset) {
        update_member(&mouse.x, &x_offset);
        update_member(&mouse.y, &y_offset);

        update_member(&mouse.v, &v_offset);
        update_member(&mouse.h, &h_offset);

        pointing_device_set_report(mouse);
        pointing_device_send();
    }

}



#endif

// CAPS_WORD: A "smart" Caps Lock key that only capitalizes the next identifier you type
// and then toggles off Caps Lock automatically when you're done.
void caps_word_enable(void) {
    caps_word_on = true;
    if (!(host_keyboard_led_state().caps_lock)) {tap_code(KC_CAPS);}
}

void caps_word_disable(void) {
    caps_word_on = false;
    if (host_keyboard_led_state().caps_lock) {tap_code(KC_CAPS);}
}

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

void process_caps_word(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on) {
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) { return; }
                // Get the base tapping keycode of a mod- or layer-tap key
                keycode = GET_TAP_KC(keycode);
                break;
            default:
                break;
        }

        switch (keycode) {  
            // Keycodes to shift
            case KC_A ... KC_Z:
                if (record->event.pressed) {caps_word_enable();}
                break;
            // Keycodes that enable caps word but shouldn't get shifted
            case KC_MINS:
            case KC_BSPC:
            case S(KC_SLSH):
            case KC_PIPE:
            case CAPS_WORD:
                // If chording mods, disable caps word
                if (record->event.pressed && (get_mods() != MOD_LSFT) && (get_mods() != 0)) {caps_word_disable();}
                break;
            default:
                // Any other keycode should automatically disable caps
                if (record->event.pressed) {caps_word_disable();}
                break;
        }
    }
}

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LT7:
        case LT4:
        case LT3:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LT2:
        case LT5:
        case LT1:
        case ONESHOT_MOD:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD: 
            return true;
        default:
            return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

//main routine once a key is pressed.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT,keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL,keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT,keycode, record);
    update_oneshot(&os_cmd_state, KC_LGUI, OS_CMD,keycode, record);
    
    process_caps_word(keycode, record);
    #ifdef PIMORONI_TRACKBALL_ENABLE
    report_mouse_t currentReport = {};
    #endif
    switch (keycode) {
        case CAPS_WORD:
            // Toggle `caps_word_on`
            if (record->event.pressed) {
                if (caps_word_on) {caps_word_disable(); return false;} 
                else {caps_word_enable(); return false;}
            }
            break;
        case MY_MOUSEBTN_1:
            if(true){//!layer_state_is(_MOUS)){
                record->event.pressed?register_code(KC_BTN1):unregister_code(KC_BTN1);
            }else{
                #ifdef PIMORONI_TRACKBALL_ENABLE
                currentReport = pointing_device_get_report();
                if (record->event.pressed) {
                    currentReport.buttons |= MOUSE_BTN1;
                }
                else {
                    currentReport.buttons &= ~MOUSE_BTN1;
                }
                pointing_device_set_report(currentReport);
                #endif
                return false;
            }
            break;
        case MY_MOUSEBTN_2:
            if(true){//!layer_state_is(_MOUS)){
                record->event.pressed?register_code(KC_BTN2):unregister_code(KC_BTN2);
            }else{
                #ifdef PIMORONI_TRACKBALL_ENABLE
                currentReport = pointing_device_get_report();
                if (record->event.pressed) {
                    currentReport.buttons |= MOUSE_BTN2;
                }
                else {
                    currentReport.buttons &= ~MOUSE_BTN2;
                }
                pointing_device_set_report(currentReport);
                #endif
                return false;
            }
            break;
        case MY_MOUSEBTN_3:
            if(true){//!layer_state_is(_MOUS)){
                record->event.pressed?register_code(KC_BTN3):unregister_code(KC_BTN3);
            }else{
                #ifdef PIMORONI_TRACKBALL_ENABLE
                currentReport = pointing_device_get_report();
                if (record->event.pressed) {
                    currentReport.buttons |= MOUSE_BTN3;
                }
                else {
                    currentReport.buttons &= ~MOUSE_BTN3;
                }
                pointing_device_set_report(currentReport);
                #endif
                return false;
            }
            break;
    }
    update_mode_rgb();
    return true;
}

void update_mode_rgb(void) {
    uint8_t mods;
    #ifdef RGBLIGHT_LAYERS
    mods = mod_config(get_mods());
    rgblight_set_layer_state(8, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(9, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(10, mods & MOD_MASK_ALT);
    rgblight_set_layer_state(11, mods & MOD_MASK_GUI);
    #endif    
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    // #ifdef PIMORONI_TRACKBALL_ENABLE
  //   if (mouse_auto_layer_timer && timer_elapsed(mouse_auto_layer_timer) > MOUSE_TIMEOUT) {
    //      report_mouse_t rep = pointing_device_get_report();
    //      if (rep.buttons) { return; } 
    //      layer_off(_MOUS); 
    //      mouse_auto_layer_timer = 0; 
   //  } 
    // #endif  
}
 //#ifdef PIMORONI_TRACKBALL_ENABLE
 //bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  //   if ((keycode < KC_BTN1 || keycode > KC_BTN5) 
  //           && layer_state_is(_MOUS) 
 //            && record->event.pressed) { 
    //     layer_off(_MOUS); 
 //        mouse_auto_layer_timer = 0; 
  //    } 
   //  return true;
 //}
 //#endif  

#ifdef OLED_DRIVER_ENABLE
void suspend_power_down_user() {
    oled_clear();
    oled_off();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_status(void) {

    oled_write_P(PSTR("PLO\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _NEO2:
            oled_write_P(PSTR("Neo\n"), false);break;
        case _NAV:
            oled_write_P(PSTR("Nav\n"), false);break;
        case _LSYM:
        case _RSYM:
            oled_write_P(PSTR("Sym\n"), false);break;
        case _NUMB:
            oled_write_P(PSTR("Num\n"), false);break;
    }
    // Host Keyboard Mod Status
    uint8_t mods = get_mods() | get_weak_mods();
    oled_write_P((mods & MOD_MASK_GUI) ? PSTR("GUI ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("CTRL ") : PSTR("     "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SHFT ") : PSTR("     "), false);

    // Host Keyboard LED Status
    //uint8_t led_usb_state = host_keyboard_leds();
    //oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
       
    }
}
#endif

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM neo2_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_MAGENTA});
const rgblight_segment_t PROGMEM mous_layers[] = RGBLIGHT_LAYER_SEGMENTS({10, 20, HSV_BLUE});
const rgblight_segment_t PROGMEM nav_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_BLUE});
const rgblight_segment_t PROGMEM lsym_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_GREEN});
const rgblight_segment_t PROGMEM rsym_layers[] = RGBLIGHT_LAYER_SEGMENTS({10, 20, HSV_GREEN});
const rgblight_segment_t PROGMEM func_layers[] = RGBLIGHT_LAYER_SEGMENTS({10, 20, HSV_RED});
const rgblight_segment_t PROGMEM numb_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_RED});
const rgblight_segment_t PROGMEM aacc_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_WHITE});

const rgblight_segment_t PROGMEM shift_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_GOLD});
const rgblight_segment_t PROGMEM ctrl_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_ORANGE});
const rgblight_segment_t PROGMEM alt_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM gui_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_TURQUOISE});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    neo2_layers,
    mous_layers, 
    nav_layers,
    rsym_layers,
    lsym_layers,
    func_layers,
    numb_layers,
    aacc_layers,
    shift_layers,
    ctrl_layers,
    alt_layers,
    gui_layers
);

void keyboard_post_init_keymap(void) {
    rgblight_layers = my_rgb_layers;
}

#endif

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
#ifdef RGBLIGHT_LAYERS
    rgblight_layers = my_rgb_layers;
#else
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
#endif
#ifdef PIMORONI_TRACKBALL_ENABLE
    rgb_hue = rgblight_get_hue();
    rgb_brightness = rgblight_get_val();
    rgb_sat = rgblight_get_sat();
    trackball_set_hsv(rgb_hue, rgb_sat, rgb_brightness);
#endif
}
layer_state_t default_layer_state_set_user(layer_state_t state) {
    #ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, layer_state_cmp(state, _NEO2));
    rgblight_set_layer_state(1, layer_state_cmp(state, _MOUS));
    #endif

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {

#ifdef RGBLIGHT_LAYERS
    for (int i = _NAV; i < 8; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
#endif
#ifdef PIMORONI_TRACKBALL_ENABLE


        switch (get_highest_layer(state | default_layer_state)) {
        case _NEO2:
            trackball_set_rgbw(rgb_brightness, 0, rgb_brightness,0);
            break;
        case _MOUS:
            trackball_set_rgbw(0, 0, rgb_brightness,0);
            break;
        case _NAV:
            trackball_set_rgbw(0, 0, rgb_brightness,0);
            break;
        case _RSYM:
            trackball_set_rgbw(0, rgb_brightness, 0, 0);
            break;
        case _LSYM:
            trackball_set_rgbw(0, rgb_brightness, 0, 0);
            break;
        case _FUNC:
            trackball_set_rgbw(rgb_brightness,0,  0, 0);
            break;
        case _NUMB:
            trackball_set_rgbw(rgb_brightness,0,  0, 0);
            break;
        case _AACC:
            trackball_set_rgbw(0, 0, 0, rgb_brightness);
            break;
        default: //  for any other layers, or the default layer
            trackball_set_rgbw(0, 0, rgb_brightness,0);
            break;

    }
#endif

    return state;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise){
    mod_state = get_mods();
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _NEO2:
                if (!(mod_state & MOD_MASK_SHIFT)) {
                // History scrubbing.
                    if (clockwise) {
                        tap_code16(C(KC_Y));
                    } else {
                        tap_code16(C(KC_Z));
                    }
                } else {
                    //navigate word left and right
                    if (clockwise) {
                        tap_code16(C(KC_RIGHT));
                    } else {
                        tap_code16(C(KC_LEFT));
                    }
                }
                break;
            case _NAV:
                if (!(mod_state & MOD_MASK_SHIFT)) {
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
                } else {
                    //tab navigation in chromium based browsers
                    //as shift is activated, i deactivate it,  then tap ctrl tab then activate shift again.
                    set_mods(mod_state);
                    clear_weak_mods();
                    del_mods(MOD_MASK_SHIFT);
                    if (clockwise) {
                        tap_code16(C(S(KC_G)));
                    } else {
                        tap_code16(C(KC_G));
                    }
                    set_mods(mod_state);
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
                if (!clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            case _NAV:
                //using shift to enable more functionalit on the same layer
                if (!(mod_state & MOD_MASK_SHIFT)) {
                    // Zoom
                    if (!clockwise) {
                        tap_code16(C(KC_PPLS));
                    } else {
                        tap_code16(C(KC_PMNS));
                    }
                } else {
                    //tab navigation in chromium based browsers
                    if (!clockwise) {
                        tap_code16(C(KC_TAB));                       
                    } else {
                        //as shift is activated, i deactivate it,  then tap ctrl tab then activate shift again.
                        clear_weak_mods();
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(C(KC_TAB));
                        set_mods(mod_state);
                    }
                }
                break;    
            default:
                // Volume control.
                if (!clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
    return true;
}

#endif
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
*  Not a key that is used frequently to double tap,for example 'tab' is often double tapped in a terminal, or
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
        else return TD_UNKNOWN;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void copy_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        //use register_code for basic keys and register_code16 for nonbasic keys
        case TD_SINGLE_TAP: register_code16(C(KC_C)); break;//copy
        case TD_DOUBLE_HOLD: register_code16(LGUI(KC_V)); break;//win paste
        case TD_SINGLE_HOLD: register_code16(C(KC_X)); break;//cut
        case TD_DOUBLE_TAP:register_code16(C(KC_V)); break;//paste
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:break;
        case TD_TRIPLE_TAP:break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void copy_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(C(KC_C)); break;
        case TD_DOUBLE_HOLD: unregister_code16(LGUI(KC_V)); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_X)); break;
        case TD_DOUBLE_TAP: unregister_code16(C(KC_V)); break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void paren_finishedl(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("()" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_HOLD: register_code16(ALGR(KC_8)); break;
        case TD_SINGLE_HOLD: SEND_STRING("[]" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_8)); break; 
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_8)); register_code16(S(KC_8));break;
        case TD_TRIPLE_TAP:break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void paren_resetl(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: break;
        case TD_DOUBLE_HOLD: unregister_code16(ALGR(KC_8)); break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: unregister_code16(S(KC_8)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(S(KC_8)); break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void braces_finishedl(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("{}" SS_TAP(X_LEFT)); break;
        case TD_SINGLE_HOLD: SEND_STRING("<>" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_TAP: register_code16(ALGR(KC_7)); break;
        case TD_DOUBLE_HOLD: register_code16(KC_NUBS); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(ALGR(KC_7)); register_code16(ALGR(KC_7));break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void braces_resetl(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: unregister_code16(ALGR(KC_7)); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_NUBS); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(ALGR(KC_7)); break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void quotes_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("''" SS_TAP(X_LEFT)); break;
        case TD_SINGLE_HOLD: tap_code16(S(KC_2));tap_code16(S(KC_2));SEND_STRING(SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_NUHS)); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_2)); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_NUHS)); register_code16(S(KC_NUHS));break;
        case TD_TRIPLE_TAP: tap_code(KC_COMMA);tap_code16(S(KC_NUHS));tap_code16(C(KC_V));SEND_STRING("' --"); break;//custom code for packaging
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void quotes_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: unregister_code16(S(KC_NUHS)); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_2)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(S(KC_NUHS)); break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void talon_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(A(C(KC_COMM))); break;
        case TD_SINGLE_HOLD: register_code16(A(C(S(KC_0)))); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}     

void talon_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(A(C(KC_COMM))); break;
        case TD_SINGLE_HOLD: unregister_code16(A(C(S(KC_0)))); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
     xtap_state.state = TD_NONE;
}         

void del_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    mod_state = get_mods();
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: 
        case TD_SINGLE_HOLD: 
            //Shift+Backspace: Delete (https://github.com/precondition/dactyl-manuform-keymap)
            if (!(mod_state & MOD_MASK_SHIFT)) {
                register_code(KC_BSPC);

            } else {
                clear_weak_mods();
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                set_mods(mod_state);
            }
            break;
        case TD_DOUBLE_TAP: 
            //backward and forward delete word
            if (!(mod_state & MOD_MASK_SHIFT)) {
                register_code16(C(KC_BSPC));
            } else {
                clear_weak_mods();
                del_mods(MOD_MASK_SHIFT);
                register_code16(C(KC_DEL));
                set_mods(mod_state);
            }
            break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: 
            if (!(mod_state & MOD_MASK_SHIFT)) {
                tap_code(KC_BSPC); register_code(KC_BSPC);
            } else {
                clear_weak_mods();
                unregister_mods(MOD_BIT(KC_LSFT));
                tap_code(KC_DEL); register_code(KC_DEL);
                set_mods(mod_state);
            }
            break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void del_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:unregister_code(KC_BSPC);unregister_code(KC_DEL);break;
        case TD_DOUBLE_TAP: unregister_code16(C(KC_BSPC));unregister_code16(C(KC_DEL));break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_BSPC);unregister_code(KC_DEL);break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void url_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        //replace the last unique identifier from the url with the selected one.
        case TD_DOUBLE_TAP: break;// tap_code16(C(KC_C));tap_code16(C(KC_L));tap_code(KC_RIGHT);tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_V));tap_code(KC_ENTER);break;
        //extract the last unique identifier from the url. I use this for programming in my environment.
        case TD_SINGLE_TAP: tap_code16(C(KC_L));tap_code(KC_RIGHT);tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(KC_C));break;
        //go to the root page of the crossloom app.
        case TD_SINGLE_HOLD: tap_code16(C(KC_L));tap_code(KC_RIGHT);tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));SEND_STRING("2251c0e2-73da-4b44-9672-19a27e19d333/object/00000000-0000-0000-0000-000000000000" SS_TAP(X_ENTER));break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void period_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_DOT);break;
        //idea from https://github.com/precondition/dactyl-manuform-keymap. Ending a sentence with double clicked period will enter a space afterwards and trigger a oneshot mod for shift to start the next sentence with capitalized word.
        case TD_DOUBLE_TAP:
            /* Check that Shift is inactive */
            if (!(get_mods() & MOD_MASK_SHIFT)) {
                tap_code(KC_DOT);
                tap_code(KC_SPC);
                /* Internal code of OSM(MOD_LSFT) */
                add_oneshot_mods(MOD_BIT(KC_LSHIFT));
            } else {
                // send ": " (KC_DOT + shift → ": ")
                tap_code(KC_DOT);
                tap_code(KC_SPC);
            }
            break;
        case TD_SINGLE_HOLD: add_mods(MOD_MASK_CTRL);break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_DOT);register_code(KC_DOT);break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void period_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_DOT);break;
        case TD_SINGLE_HOLD: del_mods(MOD_MASK_CTRL);break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP:unregister_code(KC_DOT);break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void comma_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_DOUBLE_TAP: register_code(KC_COMMA);break;
        case TD_SINGLE_TAP:
            //I always enter space after comma for readability.
            if (!(get_mods() & MOD_MASK_SHIFT)) {
                tap_code(KC_COMMA);
                tap_code(KC_SPC);

            } else {
                // send ";" (KC_DOT + shift → ";")
                tap_code16(KC_COMMA);
            }
            break;
        case TD_SINGLE_HOLD: add_mods(MOD_MASK_ALT);break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_COMMA);register_code(KC_COMMA);break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void comma_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_DOUBLE_TAP: unregister_code(KC_COMMA);break;
        case TD_SINGLE_HOLD: del_mods(MOD_MASK_ALT);break;
        case TD_SINGLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP:unregister_code(KC_COMMA);break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        //smart caps lock
        case TD_SINGLE_TAP: 
            if (caps_word_on) {
                caps_word_disable();
            } else {
                caps_word_enable();
            }
            break;
        case TD_SINGLE_HOLD: register_code16(KC_CAPS);break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: break;
        case TD_DOUBLE_TAP: break;
        case TD_SINGLE_HOLD: unregister_code16(KC_CAPS);break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP:break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void find_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(C(KC_F));break;
        case TD_DOUBLE_TAP: register_code16(C(S(KC_NUBS)));break;//custom global search in my dev env 
        case TD_SINGLE_HOLD: tap_code16(C(KC_C));tap_code16(C(S(KC_NUBS)));tap_code16(C(KC_V));tap_code(KC_ENTER);break;//custom global search for selected text
        case TD_DOUBLE_HOLD: tap_code16(C(KC_C));tap_code16(C(KC_F));tap_code16(C(KC_V));tap_code(KC_ENTER);break;//search for selected text
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;// tap_code16(C(KC_F));SEND_STRING("/\\b[0-9a-f]{8}\\b-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-\\b[0-9a-f]{12}\\b/" SS_TAP(X_ENTER) );break;//search for unique identifier regex in codemirror search
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void find_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(C(KC_F));break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: unregister_code16(C(S(KC_NUBS)));break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP:break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void save_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_TAB);break;
        case TD_SINGLE_HOLD: tap_code16(C(KC_S));break;//save file
        case TD_DOUBLE_TAP: tap_code16(C(KC_DOT));break;//custom shortcut save test
        case TD_DOUBLE_HOLD: tap_code16(C(KC_A));tap_code16(S(KC_TAB));break;//custom shortcut make pretty
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_TAB);register_code(KC_TAB);break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void save_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_TAB);break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_TAB);break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}
//for key press simulation 
keyrecord_t pressed = {{{0,0},true,0}, {0,0,0,0,0}};
keyrecord_t released = {{{0,0},false,0}, {0,0,0,0,0}};

//one shot mode tap dance, my own invention (or better say hack)
void oneshotMode_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_DOUBLE_TAP: update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT,OS_SHFT, &pressed);break;
        case TD_SINGLE_HOLD: update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL,OS_CTRL, &pressed);break;
        case TD_SINGLE_TAP: update_oneshot(&os_alt_state, KC_LALT, OS_ALT,OS_ALT, &pressed);break;
        case TD_DOUBLE_HOLD: update_oneshot(&os_cmd_state, KC_LGUI, OS_CMD,OS_CMD, &pressed);break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL,OS_CTRL, &pressed);update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL,OS_CTRL, &pressed);break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    //update the rgb color
    update_mode_rgb();
}              

void oneshotMode_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_DOUBLE_TAP: update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT,OS_SHFT, &released);break;
        case TD_SINGLE_TAP: update_oneshot(&os_alt_state, KC_LALT, OS_ALT,OS_ALT, &released);break;
        case TD_SINGLE_HOLD: update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL,OS_CTRL, &released);break;
        case TD_DOUBLE_HOLD: update_oneshot(&os_cmd_state, KC_LGUI, OS_CMD,OS_CMD, &released);break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL,OS_CTRL, &released);update_oneshot(&os_ctrl_state, OS_SHFT, OS_SHFT,OS_CTRL, &released);break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void browser_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_F12);break;//dev tools in chromium
        case TD_DOUBLE_TAP: register_code(KC_F5);break;//reload page
        case TD_SINGLE_HOLD: register_code16(S(KC_F5));break;//reload page hard
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}              

void browser_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_F12);break;
        case TD_SINGLE_HOLD: unregister_code16(C(S(KC_DEL)));break;
        case TD_DOUBLE_TAP: unregister_code(KC_F5);break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: unregister_code16(C(S(KC_DEL)));break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}

void comment_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING(SS_TAP(X_HOME)"//");break;
        case TD_DOUBLE_TAP: SEND_STRING(SS_TAP(X_HOME)"--");break;
        case TD_SINGLE_HOLD: SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_DELETE) SS_TAP(X_DELETE));break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}      

qk_tap_dance_action_t tap_dance_actions[] = {
[TD_Copy_Cut_Paste_WinPaste] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_finished, copy_reset),
[TD_LParen_Parens_Func] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, paren_finishedl, paren_resetl),
[TD_RParen_Parens_Func] = ACTION_TAP_DANCE_DOUBLE( S(KC_9),  ALGR(KC_9)),
[TD_RBrace_Braces_Tag] = ACTION_TAP_DANCE_DOUBLE(ALGR(KC_0),  S(KC_NUBS)),
[TD_LBrace_Braces_Tag] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, braces_finishedl, braces_resetl),
[TD_Quotes] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quotes_finished, quotes_reset),
[TD_TO_TM_TT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, talon_finished, talon_reset),
[TD_Tab_CtrlS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, save_finished, save_reset),
[TD_Bspc_Del_Delwl_Delwr] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, del_finished, del_reset),
[TD_URL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, url_finished, NULL),
[TD_Period] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, period_finished, period_reset),
[TD_Comma] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comma_finished, comma_reset),
[TD_Caps] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_finished, caps_reset),
[TD_Find] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, find_finished, find_reset),
[TD_OneshotMode] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, oneshotMode_finished, oneshotMode_reset),
[TD_F12_F5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,browser_finished, browser_reset),
[TD_COMMENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,comment_finished, NULL)
};

