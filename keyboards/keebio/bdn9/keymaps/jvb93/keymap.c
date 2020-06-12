/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

enum encoder_names {
  _LEFT,
  _RIGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |            | Knob 2: Vol Dn/Up |
        | Press: Mute       | Home       | Press: Mute       |
        | Previous Track    | Play/Pause | Next Track        |
        | Hold: Layer 2     | Calculator | RGB Mode          |
     */
    [0] = LAYOUT(
        KC_MUTE, KC_HOME, KC_MUTE, 
        KC_MPRV, KC_MPLY, KC_MNXT, 
        MO(1), KC_CALC, RGB_MOD),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Held: Layer 2  | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET, BL_STEP, KC_STOP,
        KC_TRNS, KC_HOME, RGB_MOD, 
        KC_TRNS, KC_END, KC_MNXT),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
