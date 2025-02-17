/*
Copyright 2020 Terry Mathews

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "portico.h"

#ifdef RGB_MATRIX_ENABLE

const is31_led __flash g_is31_leds[DRIVER_LED_TOTAL] = {
    { 0, C2_1,  C3_1,  C4_1  },
    { 0, C1_1,  C3_2,  C4_2  },
    { 0, C1_2,  C2_2,  C4_3  },
    { 0, C1_3,  C2_3,  C3_3  },
    { 0, C1_4,  C2_4,  C3_4  },
    { 0, C1_5,  C2_5,  C3_5  },
    { 0, C1_6,  C2_6,  C3_6  },
    { 0, C1_7,  C2_7,  C3_7  },
    { 0, C1_8,  C2_8,  C3_8  },
    { 1, C2_1,  C3_1,  C4_1  },
    { 1, C1_1,  C3_2,  C4_2  },
    { 1, C1_2,  C2_2,  C4_3  },
    { 1, C1_3,  C2_3,  C3_3  },
    { 1, C1_4,  C2_4,  C3_4  },
    { 1, C1_5,  C2_5,  C3_5  },

    { 0, C9_1,  C8_1,  C7_1  },
    { 0, C9_2,  C8_2,  C7_2  },
    { 0, C9_3,  C8_3,  C7_3  },
    { 0, C9_4,  C8_4,  C7_4  },
    { 0, C9_5,  C8_5,  C7_5  },
    { 0, C9_6,  C8_6,  C7_6  },
    { 0, C9_7,  C8_7,  C6_6  },
    { 0, C9_8,  C7_7,  C6_7  },
    { 0, C8_8,  C7_8,  C6_8  },
    { 1, C9_1,  C8_1,  C7_1  },
    { 1, C9_2,  C8_2,  C7_2  },
    { 1, C9_3,  C8_3,  C7_3  },
    { 1, C9_4,  C8_4,  C7_4  },
    { 1, C9_5,  C8_5,  C7_5  },
    { 1, C9_6,  C8_6,  C7_6  },

    { 0, C1_9,  C3_10, C4_10 },
    { 0, C1_10, C2_10, C4_11 },
    { 0, C1_11, C2_11, C3_11 },
    { 0, C1_12, C2_12, C3_12 },
    { 0, C1_13, C2_13, C3_13 },
    { 0, C1_14, C2_14, C3_14 },
    { 0, C1_15, C2_15, C3_15 },
    { 0, C1_16, C2_16, C3_16 },
    { 1, C1_10, C2_10, C4_11 },
    { 1, C1_11, C2_11, C3_11 },
    { 1, C1_12, C2_12, C3_12 },
    { 1, C1_13, C2_13, C3_13 },
    { 1, C1_14, C2_14, C3_14 },
    { 1, C9_7,  C8_7,  C6_6  },

    { 0, C2_9,  C3_9,  C4_9  },
    { 0, C9_12, C8_12, C7_12 },
    { 0, C9_13, C8_13, C7_13 },
    { 0, C9_14, C8_14, C7_14 },
    { 0, C9_15, C8_15, C6_14 },
    { 0, C9_16, C7_15, C6_15 },
    { 1, C2_9,  C3_9,  C4_9  },
    { 1, C1_9,  C3_10, C4_10 },
    { 1, C9_9,  C8_9,  C7_9  },
    { 1, C9_10, C8_10, C7_10 },
    { 1, C9_11, C8_11, C7_11 },
    { 1, C9_14, C8_14, C7_14 },
    { 1, C1_15, C2_15, C3_15 },
    { 1, C1_16, C2_16, C3_16 },

    { 0, C9_9,  C8_9,  C7_9  },
    { 0, C9_10, C8_10, C7_10 },
    { 0, C9_11, C8_11, C7_11 },
    { 0, C8_16, C7_16, C6_16 },
    { 1, C9_12, C8_12, C7_12 },
    { 1, C9_13, C8_13, C7_13 },
    { 1, C9_15, C8_15, C6_14 },
    { 1, C9_16, C7_15, C6_15 },
    { 1, C8_16, C7_16, C6_16 }
};

led_config_t g_led_config = {
    {
        {  0,      1,  2,      3,      4,      5,  6,      7,      8,      9, 10, 11, 12,     13, 14 },
        { 15,     16, 17,     18,     19,     20, 21,     22,     23,     24, 25, 26, 27,     28, 29 },
        { 30,     31, 32,     33,     34,     35, 36,     37,     38,     39, 40, 41, 42, NO_LED, 43 },
        { 44, NO_LED, 45,     46,     47,     48, 49,     50,     51,     52, 53, 54, 55,     56, 57 },
        { 58,     59, 60, NO_LED, NO_LED, NO_LED, 61, NO_LED, NO_LED, NO_LED, 62, 63, 64,     65, 66 }
    }, {
        {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180,   0 }, { 203,   0 }, { 224,   0 },
        {   4,  16 }, {  23,  16 }, {  38,  16 }, {  53,  16 }, {  68,  16 }, {  83,  16 }, {  98,  16 }, { 113,  16 }, { 128,  16 }, { 143,  16 }, { 158,  16 }, { 173,  16 }, { 188,  16 }, { 206,  16 }, { 224,  16 },
        {   6,  32 }, {  26,  32 }, {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 },               { 201,  32 }, { 224,  32 },
        {   9,  48 },               {  34,  48 }, {  49,  48 }, {  64,  48 }, {  79,  48 }, {  94,  48 }, { 109,  48 }, { 124,  48 }, { 139,  48 }, { 154,  48 }, { 169,  48 }, { 189,  48 }, { 210,  48 }, { 224,  48 },
        {   2,  64 }, {  21,  64 }, {  39,  64 },                                           {  96,  64 },                                           { 152,  64 }, { 171,  64 }, { 195,  64 }, { 210,  64 }, { 224,  64 }
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4,
        4,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4,          4,          4, 4, 4, 4, 4
    }
};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

void rgb_matrix_indicators_kb(void) {
	if (host_keyboard_led_state().caps_lock) {
		rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
	}
	else { 
		rgb_matrix_set_color(30, 0x00, 0x00, 0x00);
	}
	if (!rgb_matrix_is_enabled()) {
		rgb_matrix_driver.flush();
    }
}
#endif
