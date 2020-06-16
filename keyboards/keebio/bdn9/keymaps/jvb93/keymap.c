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
    RELEASE_GO_LEFT = SAFE_RANGE,
    RELEASE_GO_RIGHT,
    CLEAN,
    REBUILD,
    SCREENSHOT,
    PULL,
    PUSH,
    STAGE_ALL,
    COMMIT,
    RESET_ZOOM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Zoom in/out     |                                  | Knob 2: Vol Dn/Up                 |
        | Press: Reset Zoom Level | Screenshot                       | Press: Mute                       |
        | Previous Track          | Play/Pause                       | Next Track                        |
        | Hold: Layer 2           | Go Left Through Virtual Desktops | Go Right Through Virtual Desktops |
     */
    [0] = LAYOUT(
        RESET_ZOOM, SCREENSHOT, KC_MUTE, 
        KC_MPRV, KC_MPLY, KC_MNXT, 
        MO(1), RELEASE_GO_LEFT, RELEASE_GO_RIGHT),
    /*
        | N/A            | Push      | N/A     |
        | Pull           | Stage All | Commit  |
        | Held: Layer 2  | Clean     | Rebuild |
     */
    [1] = LAYOUT(
        KC_NO, PUSH, KC_NO,
        PULL, STAGE_ALL, COMMIT, 
        KC_TRANSPARENT, CLEAN, REBUILD),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            SEND_STRING(SS_LCTL(SS_TAP(X_MINUS)));
        } else {
            SEND_STRING(SS_LCTL(SS_TAP(X_EQUAL)));
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RELEASE_GO_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_HOME))) SS_LCTL(SS_RWIN(SS_TAP(X_LEFT))));
            }
            break;
        case RELEASE_GO_RIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_HOME))) SS_LCTL(SS_RWIN(SS_TAP(X_RIGHT))));
            }
            break;
        case RESET_ZOOM:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_0)));
            }
            break;
        case SCREENSHOT:
            if (record->event.pressed) {
                SEND_STRING(SS_RWIN(SS_RSFT(SS_TAP(X_S))));
            }
            break;
        case CLEAN:
            if (record->event.pressed) {
                SEND_STRING(SS_RCTL(SS_RSFT(SS_TAP(X_C))));
            }
            break;
        case REBUILD:
            if (record->event.pressed) {
                SEND_STRING(SS_RCTL(SS_RSFT(SS_TAP(X_B))));
            }
            break;
        case PULL:
            if (record->event.pressed) {
                SEND_STRING(SS_RCTL(SS_RSFT(SS_LALT(SS_TAP(X_L)))));
            }
            break;
        case PUSH:
            if (record->event.pressed) {
                SEND_STRING(SS_RCTL(SS_RSFT(SS_LALT(SS_TAP(X_P)))));
            }
            break;
        case STAGE_ALL:
            if (record->event.pressed) {
                SEND_STRING(SS_RCTL(SS_RSFT(SS_LALT(SS_TAP(X_S)))));
            }
            break;
        case COMMIT:
            if (record->event.pressed) {
                SEND_STRING(SS_RCTL(SS_TAP(X_ENTER)));
            }
            break;
    }
    return true;
};
