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
    // Keycode for caps word (Code from https://github.com/andrewjrae/kyria-keymap#caps-word).
    CAPS_WORD = SAFE_RANGE,
    MY_MOUSEBTN_1,
    MY_MOUSEBTN_2,
    MY_MOUSEBTN_3,
    SELECT_ID,
    GO_CL,
    GO_ID,
    REPEAT,
};
// State for Caps word.     
bool caps_word_on;
void caps_word_enable(void);
void caps_word_disable(void);

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
uint8_t oneshot_mod_state;
uint16_t last_keycode;

// Tap Dance declarations
enum {
    TD_LParen_Parens_Func,
    TD_RParen_Parens_Func,
    TD_LBrace_Braces_Tag,
    TD_RBrace_Braces_Tag, 
    TD_Quotes,
    TD_Tab_CtrlS,
    TD_Bspc_Del_Delwl_Delwr,
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
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap

void paren_finishedl(qk_tap_dance_state_t *state, void *user_data);
void paren_resetl(qk_tap_dance_state_t *state, void *user_data);

void braces_finishedl(qk_tap_dance_state_t *state, void *user_data);
void braces_resetl(qk_tap_dance_state_t *state, void *user_data);

void quotes_finished(qk_tap_dance_state_t *state, void *user_data);
void quotes_reset(qk_tap_dance_state_t *state, void *user_data);

void del_finished(qk_tap_dance_state_t *state, void *user_data);
void del_reset(qk_tap_dance_state_t *state, void *user_data);

void find_finished(qk_tap_dance_state_t *state, void *user_data);
void find_reset(qk_tap_dance_state_t *state, void *user_data);

void save_finished(qk_tap_dance_state_t *state, void *user_data);
void save_reset(qk_tap_dance_state_t *state, void *user_data);

void comment_finished(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/*
 * Layer 0: Base Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Play  |  p   |  u   |  j   |   c  |  q   |                              |      |   g  |   l  |  m   |   f  |CtrlAltD|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ESC   |  h   |i-SHFT| e-LT1| a-LT3|  O   |                              |   d  |t-LT4 |r-LT2 |n-SHFT|   s  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Play  |  k   |y-CTRL| .-ALT|,-LT5 |  x   |  Cut |REPEAT|  |Screen|      |      |v-LT6 |w-RALT|b-CTRL|   z  |  ß de  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Enpass| Find | LT7  | Copy | Paste|  | Caps | Save | BSPC | F24  | F22  |
 *                        |      |      | SPACE|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 
      [_NEO2] = LAYOUT(
       KC_MPLY, KC_P,KC_U,KC_J,KC_C,KC_Q,                                     _______,KC_G,KC_L,KC_M,KC_F,C(A(KC_DEL)),
       KC_ESC, KC_H, LSFT_T(KC_I), LT1A, LT3A, KC_O,                                     _______, LT4A, LT2A, RSFT_T(KC_N), KC_S,_______,
       KC_MPLY, KC_K, LCTL_T(KC_Y), LALT_T(KC_DOT),LT5A,KC_X, C(KC_X), REPEAT,  LSG(KC_S),XXXXXXX, KC_J,LT6A , RALT_T(KC_W), RCTL_T(KC_B), KC_Z,KC_MINS,
                                  C(A(KC_E)), FIND, LT7, C(KC_C), C(KC_V), KC_CAPS, SAVE, DELETE, KC_F24, KC_F22
     ),
 */
/*
 * Layer 0: Base Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Play  |  X   |  V   |  L   |  C   |  W   |                              |   K  |   H  |   G  |   F  |   Q  |CtrlAltD|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ESC   |  U   |I-SHFT| A-LT1| E-LT3|  O   |                              |   S  |N-LT4 |R-LT2 |T-SHFT|   D  |  Y de  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Play  |  Ü   |Ö-CTRL| Ä-ALT|P-LT5 |  Z   |  Cut |REPEAT|  |Screen|      |   B  |M-LT6 |,-RALT|.-CTRL|   J  |  ß de  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Enpass| Find | LT7  | Copy | Paste|  | Caps | Save | BSPC | F24  | F22  |
 *                        |      |      | SPACE|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
     [_NEO2] = LAYOUT(
       KC_MPLY, KC_X,KC_V,KC_L,KC_C,KC_W,                                     KC_K,KC_H,KC_G,KC_F,KC_Q,C(A(KC_DEL)),
       KC_ESC, KC_U, LSFT_T(KC_I), LT1, LT3, KC_O,                                     KC_S, LT4, LT2, RSFT_T(KC_T), KC_D,KC_Z,
       KC_MPLY, KC_LBRC, LCTL_T(KC_SCLN), LALT_T(KC_QUOT),LT5,KC_Y,C(KC_X), REPEAT,  LSG(KC_S), XXXXXXX, KC_B,LT6 , LALT_T(KC_COMMA), RCTL_T(KC_DOT), KC_J,KC_MINS,
                                  C(A(KC_E)), FIND, LT7, C(KC_C), C(KC_V), KC_CAPS, SAVE, DELETE, KC_F24, KC_F22
     ),
 /*
  * Layer 1: Mouse
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |MOUSE1|MOUSE3|MOUSE2|      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |      |LSHIFT|      |MOUSE1|      |                              |W-LEFT|M-LEFT| M-UP |M-RGHT|W-RGHT|        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |MOUSE2|      |      |      |  |      |      |      |W-DOWN|M-DOWN|W-RGHT|      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_MOUS] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, MY_MOUSEBTN_1, MY_MOUSEBTN_3, MY_MOUSEBTN_2, _______, _______,
       _______, _______, KC_LSFT, _______, MY_MOUSEBTN_1, _______,                                     KC_WH_L, KC_MS_L, KC_MS_U, KC_MS_R, KC_WH_R, _______,
       _______, _______, _______, _______, MY_MOUSEBTN_2, _______, _______, _______, _______, XXXXXXX, _______, KC_WH_D, KC_MS_D, KC_WH_U, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),

 /*
  * Layer 2: Navigation
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |PAGEUP|      |PAGEDW|      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |      | LEFT |  UP  | RIGHT|      |                              |      | LGUI |      |      |C_S_T |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      | HOME | DOWN |  END |      |      |      |  |      |      |      |      |      |      |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_NAV] = LAYOUT(
       _______, _______, KC_PGUP, _______, KC_PGDOWN, _______,                                     _______, _______, _______, _______, _______, _______,
       _______, _______, KC_LEFT, KC_UP, KC_RIGHT, _______,                                     _______, KC_LGUI, _______,_______,C_S_T(KC_TAB),_______ ,
       _______, _______, KC_HOME, KC_DOWN, KC_END, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),
 /*
  * Layer 3: Right symbols
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |   <  |   =  |  >   |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |  &   |  $   |  *   |      |      |                              |      |  {   |  }   |  -   |   @  |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |  |      |      |      |COMMEN|  %   |  +   |   €  |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |   "  |      |      |  |      |      |   _  |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_RSYM] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, KC_NUBS, S(KC_0), S(KC_NUBS), _______, _______,
       _______, S(KC_6), S(KC_4), S(KC_RBRC), _______, _______,                                     _______, BRACES, BRACESR, KC_SLSH, ALGR(KC_Q),_______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, COMMENT, S(KC_5),KC_RBRC , ALGR(KC_E), _______,
                                  _______, _______,  S(KC_2),_______, _______, _______, _______,S(KC_SLSH), _______, _______
     ),
 /*
  * Layer 4: Left symbols
  *
    ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |  ^   |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |  \   |  /   |  (   |  )   |  `   |                              |      |      |  ?   |  !   |   #  |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |  ~   |  |   |  '   |  `   |      |      |  |      |      |      |      |      |      |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |   "  |      |      |  |      |      |   _  |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_LSYM] = LAYOUT(
       _______, _______, _______, _______, _______, KC_GRV,                                     _______, _______, _______, _______, _______, _______,
       _______,ALGR(KC_MINS), S(KC_7), PARENS, PARENSR,KC_EQL,                                     _______, _______, S(KC_MINS), S(KC_1), KC_NUHS, _______,
       _______, _______, ALGR(KC_RBRC), ALGR(KC_NUBS), QUOTES, S(KC_EQL), _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______,
                                  _______, _______,  S(KC_2),_______, _______, _______, _______,S(KC_SLSH), _______, _______
     ),
 /*
  * Layer 5: Func keys
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |  F10 |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |      |      |CTLALT|      |      |                              |      |  F4  |  F5  |  F6  |  F11 |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |  F12 |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      | F21  | F23  |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_FUNC] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, KC_F7, KC_F8, KC_F9, KC_F10, _______,
       _______, _______, _______,C(KC_LALT), _______, _______,                                  _______, KC_F4, KC_F5, KC_F6, KC_F11, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, KC_F1, KC_F2, KC_F3, KC_F12, _______,
                                  _______, _______, _______, _______, _______, _______, KC_F21, KC_F23, _______, _______
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
       _______, KC_PAST, KC_4, KC_5, KC_6, KC_PEQL, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),
 /*
  * Layer 7: Always accessible
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      | Manic|      |      |                              |      |CloseT|Go CL | ReoT |      | RESET  |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        | ESC  | UNDO |      | REDO |      |                              | Go ID| TabL |Sel ID| TabR |DupTab| Mute   |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |   TO1  |  TO0 |FindNe|      |FindPr|      |      |      |  |      |      |      | LAST |Go URL| NEXT |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      | TAB  |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
     [_AACC] = LAYOUT(
       _______, _______, _______, A(C(S(KC_W))), _______, _______,                                      _______,C(KC_W),GO_CL , C(S(KC_T)),_______, RESET,
       _______, KC_ESC, C(KC_Y), _______, C(KC_Z), _______,                                      GO_ID, S(C(KC_TAB)), SELECT_ID, C(KC_TAB), C(S(KC_K)), KC_MUTE,
       TO(_MOUS), TO(_NEO2),_______, LSG(KC_S), C(KC_G), _______, _______, _______, _______, XXXXXXX, _______, KC_WWW_BACK, GO_URL, KC_WWW_FORWARD, _______, _______,
                                  _______, _______, KC_TAB, _______, _______, _______, _______, _______, _______, _______
     )
};

#ifdef PIMORONI_TRACKBALL_ENABLE
// {{{
#include "timer.h"
#include "quantum/quantum.h"
#include "i2c_master.h"
static int16_t mouse_auto_layer_timer = 0;
bool is_trackball_active = false;
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
    if (*offset > 63) {
        *member = 63;
        *offset -= 63;
    } else if (*offset < -63) {
        *member = -63;
        *offset += 63;
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
    uint8_t scale = 4;
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
                if (!is_trackball_active) {
                    is_trackball_active = true;
                    tap_code16(KC_F22);
                }
                mouse_auto_layer_timer = timer_read();
            } else if (layer_state_is(_NUMB) || layer_state_is(_FUNC)) {

                v_offset -= state.x * state.x * SIGN(state.x) ;
                if (!is_trackball_active) {
                    is_trackball_active = true;
                    tap_code16(KC_F22);
                }
                mouse_auto_layer_timer = timer_read();
            } else if ((state.x || state.y) && !state.button_down) {
              
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

uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;
void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != REPEAT) {
        last_modifier = oneshot_mod_state > mod_state ? oneshot_mod_state : mod_state;
        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->event.pressed) {
                    last_keycode = GET_TAP_KC(keycode);
                }
                break;
            default:
                if (record->event.pressed) {
                    last_keycode = keycode;
                }
                break;
        }
    } else { // keycode == REPEAT
        if (record->event.pressed) {
            register_mods(last_modifier);
            register_code16(last_keycode);
        } else {
            unregister_code16(last_keycode);
            unregister_mods(last_modifier);
        }
    }
}

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
            case KC_SLSH:
            case KC_PIPE:
            case CAPS_WORD:
                // If chording mods, disable caps word
                if (record->event.pressed && (get_mods() != MOD_LSFT) && (get_mods() != 0)) {caps_word_disable();}
                break;
            case KC_SPC:
                if (record->event.pressed) {
                    tap_code(KC_BSPC);
                    caps_word_disable();
                }
                break;
            default:
                // Any other keycode should automatically disable caps
                if (record->event.pressed) {caps_word_disable();}
                break;
        }
    }
}
  //sn-sz, x zu ü, ux-ü, y zu ö, oz-ö,iy-j, q zu ä, aq-ä, f12 zu linksleer, cof12-winpaste, mouse3 zu obenrechtsleer, m1m2-m3, rcomma-semi, tdot-colon, gr-k, ft-h,   
#ifdef COMBO_ENABLE
enum combo_events {
  ZC_DF0,
  ZC_DF1,
  ZC_ENTER,
  ZC_ENTER1,
  ZC_MOUSE1,
  ZC_MOUSE2,
  ZC_MOUSE3,
  ZC_WINPASTE,
  ZC_PASTE,
  ZC_COMBO,
  ZC_OSLSFT,
  ZC_OSRSFT
};
const uint16_t PROGMEM df1_combo[] = {LALT_T(KC_QUOT),LT5, COMBO_END};
const uint16_t PROGMEM df0_combo[] = {LALT_T(KC_QUOT),MY_MOUSEBTN_2, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {LT6 , LALT_T(KC_COMMA), COMBO_END};
const uint16_t PROGMEM enter1_combo[] = {KC_WH_D, KC_MS_D, COMBO_END};
const uint16_t PROGMEM mouse2_combo[] = {LT1, LALT_T(KC_QUOT), COMBO_END};
const uint16_t PROGMEM mouse1_combo[] = {LT3, LT5, COMBO_END};
const uint16_t PROGMEM oneshotmod_rsft[] = {LT4, LT2, COMBO_END};
const uint16_t PROGMEM oneshotmod_lsft[] = {LT1, LT3, COMBO_END};
const uint16_t PROGMEM mouse3_combo[] = {KC_C, LT3, COMBO_END};
const uint16_t PROGMEM winpaste_combo[] = {LSG(KC_S),KC_CAPS, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {C(KC_X), C(KC_C), COMBO_END};
const uint16_t PROGMEM caps_combo [] = {LSFT_T(KC_I), LT3, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  [ZC_DF1] = COMBO_ACTION(df1_combo),
  [ZC_DF0] = COMBO_ACTION(df0_combo),
  [ZC_ENTER] = COMBO_ACTION(enter_combo),
  [ZC_ENTER1] = COMBO_ACTION(enter1_combo), 
  [ZC_MOUSE1] = COMBO_ACTION(mouse1_combo),
  [ZC_MOUSE2] = COMBO_ACTION(mouse2_combo),
  [ZC_MOUSE3] = COMBO_ACTION(mouse3_combo),
  [ZC_WINPASTE] = COMBO_ACTION(winpaste_combo),
  [ZC_PASTE] = COMBO_ACTION(paste_combo),
  [ZC_COMBO] = COMBO_ACTION(caps_combo),
  [ZC_OSLSFT] = COMBO_ACTION(oneshotmod_lsft),
  [ZC_OSRSFT] = COMBO_ACTION(oneshotmod_rsft)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
#ifdef PIMORONI_TRACKBALL_ENABLE
  report_mouse_t currentReport = {};
  mod_state = get_mods();
#endif
  switch(combo_index) {
    case ZC_DF0:
      if (pressed) {
        layer_move(_NEO2);
      }
      break;
    case ZC_DF1:
      if (pressed) {
        layer_move(_MOUS);
      }
      break;

    case ZC_ENTER:
    case ZC_ENTER1:
      if (pressed) {
        register_code(KC_ENT);
      }else{
        unregister_code(KC_ENT);
      }
      break;
    case ZC_MOUSE1:
      if (pressed) {
        register_code(KC_BTN1);
      }else{
        unregister_code(KC_BTN1);
      }
      break;
    case ZC_MOUSE2:
      if (pressed) {
        register_code(KC_BTN2);
      }else{
        unregister_code(KC_BTN2);
      }
      break;
    case ZC_MOUSE3:
        if(!layer_state_is(_NEO2)||(mod_state & MOD_MASK_SHIFT)){
            pressed?register_code(KC_BTN3):unregister_code(KC_BTN3);
        }else{
            #ifdef PIMORONI_TRACKBALL_ENABLE
            currentReport = pointing_device_get_report();
            if (pressed) {
                currentReport.buttons = MOUSE_BTN1;
            }
            else {
                currentReport.buttons &= ~MOUSE_BTN1;
            }
            pointing_device_set_report(currentReport);
            #endif
            }
      break;
    case ZC_WINPASTE:
      if (pressed) {
        tap_code16(LGUI(KC_V));
      }
      break;
    case ZC_PASTE:
      if (pressed) {
        tap_code16(C(KC_V));
      }
      break;
    //smart caps lock
    case ZC_COMBO:
        if (pressed) {
            if (caps_word_on) {
                caps_word_disable();
            } else {
                caps_word_enable();
            }
        }
        break;
    case ZC_OSLSFT:
        if (pressed) {
            set_oneshot_mods(MOD_BIT(KC_RSFT));
        }
        break;
    case ZC_OSRSFT:
        if (pressed) {
            set_oneshot_mods(MOD_BIT(KC_LSFT));
        }
        break;
  }
}
#endif
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;


//main routine once a key is pressed.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
    process_repeat_key(keycode, record);
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
            if(!layer_state_is(_AACC)){
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
            record->event.pressed?register_code(KC_BTN2):unregister_code(KC_BTN2);
            break;
        case MY_MOUSEBTN_3:
            record->event.pressed?register_code(KC_BTN3):unregister_code(KC_BTN3);
            break;
        case GO_CL:
            if (record->event.pressed) {
                //go to the root page of the crossloom app.
                tap_code16(C(KC_L));tap_code(KC_RIGHT);tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));SEND_STRING("2251c0e2-73da-4b44-9672-19a27e19d333/object/00000000-0000-0000-0000-000000000000" SS_TAP(X_ENTER));
            }
            break;
        case SELECT_ID:
            if (record->event.pressed) {
                //extract the last unique identifier from the url. I use this for programming in my environment.
                tap_code16(C(KC_L));tap_code(KC_RIGHT);tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(S(KC_LEFT)));tap_code16(C(KC_C));
            }
            break;
        case GO_ID:
            if (record->event.pressed) {
                //replace the last unique identifier from the url with the selected one
                tap_code16(C(KC_C));tap_code16(C(KC_L));tap_code(KC_RIGHT);tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_BSPC));tap_code16(C(KC_V));tap_code(KC_ENTER);
            }
            break;
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_caps_word(keycode, record);
}
void matrix_scan_keymap(void) {
    uint8_t mods = mod_config(get_mods());
    rgblight_set_layer_state(8, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(9, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(10, mods & MOD_MASK_ALT);
    rgblight_set_layer_state(11, mods & MOD_MASK_GUI);
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
#ifdef PIMORONI_TRACKBALL_ENABLE
    if (is_trackball_active && (!layer_state_is(_FUNC) && !layer_state_is(_RSYM))) {
        if (timer_elapsed(mouse_auto_layer_timer) > MOUSE_TIMEOUT) {
            tap_code16(KC_F22);
            is_trackball_active = false;
        }
    }    
#endif  

}

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
const rgblight_segment_t PROGMEM nav_layers[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_BLUE});
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
    for (int i = _NEO2; i < 12; i++) {
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
            case _AACC:
                // History scrubbing.
                if (clockwise) {
                    tap_code16(C(KC_Y));
                } else {
                    tap_code16(C(KC_Z));
                }
                break;
            case _LSYM:
                if (clockwise) {
                    tap_code16(C(S(KC_G)));
                } else {
                    tap_code16(C(KC_G));
                }
                break;
            case _NEO2:
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
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
            case _MOUS:
                if (clockwise) {
                    tap_code16(C(S(KC_TAB)));
                } else {
                    tap_code16(C(KC_TAB));
                }
                break;
            case _AACC:
                if (clockwise) {
                    tap_code16(KC_MPRV);
                } else {
                    tap_code16(KC_MNXT);
                }
                break;
            default:
            // Zoom
                if (!clockwise) {
                    tap_code16(C(KC_PPLS));
                } else {
                    tap_code16(C(KC_PMNS));
                }
                break;
        }
    }
    return true;
}

#endif

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

    return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void paren_finishedl(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("()" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_HOLD: register_code16(ALGR(KC_8)); break;
        case TD_SINGLE_HOLD: SEND_STRING("[]" SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_8)); break; 
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_8)); register_code16(S(KC_8));break;
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
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}
//tap_code(KC_COMMA);tap_code16(S(KC_NUHS));tap_code16(C(KC_V));SEND_STRING("' --"); break;//custom code for packaging
void quotes_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("''" SS_TAP(X_LEFT)); break;
        case TD_SINGLE_HOLD: tap_code16(S(KC_2));tap_code16(S(KC_2));SEND_STRING(SS_TAP(X_LEFT)); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_NUHS)); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_2)); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_NUHS)); register_code16(S(KC_NUHS));break;
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
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
    xtap_state.state = TD_NONE;
}


void del_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    mod_state = get_mods();
    switch (xtap_state.state) { 
        case TD_SINGLE_HOLD: 
            if(layer_state_is(_AACC)) {}
            else {layer_on(_AACC);}
            break;
        case TD_SINGLE_TAP:
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
                unregister_mods(MOD_BIT(KC_RSFT));
                tap_code(KC_DEL); register_code(KC_DEL);
                set_mods(mod_state);
            }
            break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void del_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:unregister_code(KC_BSPC);unregister_code(KC_DEL);break;
        case TD_SINGLE_HOLD:
            layer_off(_AACC);
            break;
        case TD_DOUBLE_TAP: unregister_code16(C(KC_BSPC));unregister_code16(C(KC_DEL));break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_BSPC);unregister_code(KC_DEL);break;
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
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}      

qk_tap_dance_action_t tap_dance_actions[] = {
[TD_LParen_Parens_Func] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, paren_finishedl, paren_resetl),
[TD_RParen_Parens_Func] = ACTION_TAP_DANCE_DOUBLE( S(KC_9),  ALGR(KC_9)),
[TD_RBrace_Braces_Tag] = ACTION_TAP_DANCE_DOUBLE(ALGR(KC_0),  S(KC_NUBS)),
[TD_LBrace_Braces_Tag] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, braces_finishedl, braces_resetl),
[TD_Quotes] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quotes_finished, quotes_reset),
[TD_Tab_CtrlS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, save_finished, save_reset),
[TD_Bspc_Del_Delwl_Delwr] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, del_finished, del_reset),
[TD_Find] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, find_finished, find_reset),
[TD_COMMENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,comment_finished, NULL)
};

