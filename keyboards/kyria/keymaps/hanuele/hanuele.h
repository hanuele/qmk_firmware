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
 
 //German key codes (I did not import the official german header file because it did through an error in my environment)
 
 
 //Personal key codes for tab dances etc.
 #define LA_NUM1 LT(_NUMB, KC_BSPC)
 #define LA_NUM2 LT(_NUMB, KC_TAB)
 #define LA_NUM3 LT(_NUMB, KC_SCLN)
 #define LA_SYMB1 LT(_SYMB, KC_QUOT)
 #define LAYER_DANCE TD(TD_Layer)
 #define ONESHOT_LAYER TD(TD_OneshotLayer)
 #define ONESHOT_MOD TD(TD_OneshotMode)
 #define URL TD(TD_URL)
 #define FIND TD(TD_Find)
 #define LEFTA TD(TD_AL_WL)
 #define RIGHTA TD(TD_AR_WR)
 #define UPA TD(TD_AU_PU)
 #define DOWNA TD(TD_AD_PD)
 #define COPY TD(TD_Copy_Cut_Paste_WinPaste)
 #define BROWSER TD(TD_F12_F5)
 #define TALON TD(TD_TO_TM_TT)
 #define DELETE TD(TD_Bspc_Del_Delwl_Delwr)
 #define ONESHOT TD(TD_OneshotMode)
 #define SAVE TD(TD_Tab_CtrlS)
 #define ENTER TD(TD_Enter_CtrlAltTab)
 #define CAPSLOCK TD(TD_Caps)
 #define BRACES TD(TD_LBrace_Braces_Tag)
 #define PARENS TD(TD_LParen_Parens_Func)
 #define BRACESR TD(TD_RBrace_Braces_Tag)
 #define PARENSR TD(TD_RParen_Parens_Func)
 #define QUOTES TD(TD_Quotes)
 #define PERIOD TD(TD_Period)
 #define COMMA TD(TD_Comma)
 #define COMMENT TD(TD_COMMENT)