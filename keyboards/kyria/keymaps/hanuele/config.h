/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    splitkb
#define PRODUCT         Kyria Keyboard

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//This is an extension of the accelerated mode.

#define MOUSEKEY_DELAY 12
#define MOUSEKEY_INTERVAL 24
#define MOUSEKEY_MOVE_DELTA 2
#define MOUSEKEY_MAX_SPEED 14
#define MOUSEKEY_TIME_TO_MAX 30
#define MOUSEKEY_WHEEL_DELAY 300
#define MOUSEKEY_WHEEL_INTERVAL 90
#define MOUSEKEY_WHEEL_MAX_SPEED 16
#define MOUSEKEY_WHEEL_TIME_TO_MAX 17


#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LIMIT_VAL 150
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_MAX_LAYERS 8
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 1000
// Here you find the flash statements for left and right side. This is not necessary for all changes: https://github.com/foureight84/sofle-keyboard-pimoroni
#define EE_HANDS

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2

#define TAPPING_TERM 175

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

#define IGNORE_MOD_TAP_INTERRUPT        

//next will be pimoroni trackball integration.