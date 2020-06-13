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

enum custom_keycodes {
    RELEASE = SAFE_RANGE,
    GO_RIGHT_DESKTOP,
    GO_LEFT_DESKTOP,
    RESET_ZOOM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Zoom in/out     |            | Knob 2: Vol Dn/Up |
        | Press: Reset Zoom Level | Home       | Press: Mute       |
        | Previous Track          | Play/Pause | Next Track        |
        | Hold: Layer 2           | Calculator | RGB Mode          |
     */
    [0] = LAYOUT(
        RESET_ZOOM, KC_HOME, KC_MUTE, 
        KC_MPRV, KC_MPLY, KC_MNXT, 
        MO(1), KC_CALC, RGB_MOD),
    /*
        | RESET          | N/A                              | Media Stop                        |
        | Held: Layer 2  | Release from RDP                 | RGB Mode                          |
        | Held: Layer 2  | Go Left Through Virtual Desktops | Go Right Through Virtual Desktops |
     */
    [1] = LAYOUT(
        RESET, BL_STEP, KC_STOP,
        KC_TRNS, RELEASE, RGB_MOD, 
        KC_TRNS, GO_LEFT_DESKTOP, GO_RIGHT_DESKTOP),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            SEND_STRING(SS_LCTL(SS_TAP(X_EQUAL)));
        } else {
            SEND_STRING(SS_LCTL(SS_TAP(X_MINUS)));
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RELEASE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_HOME))));
            }
            break;
        case GO_RIGHT_DESKTOP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_RWIN(SS_TAP(X_RIGHT))));
            }
            break;
        case GO_LEFT_DESKTOP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_RWIN(SS_TAP(X_LEFT))));
            }
            break;
        case RESET_ZOOM:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_0)));
            }
            break;
    }
    return true;
};
