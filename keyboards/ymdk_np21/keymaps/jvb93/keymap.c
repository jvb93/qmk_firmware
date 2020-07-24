#include QMK_KEYBOARD_H

#define _NP 0
#define _ML 1

enum custom_keycodes {
  NP = SAFE_RANGE,
  ML,
  RELEASE_GO_LEFT,
  RELEASE_GO_RIGHT,
  ZOOM_IN,
  ZOOM_OUT
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty */

  [_NP] = LAYOUT_ortho_6x4(
    KC_MUTE      ,   KC_MPRV, KC_MPLY, KC_MNXT,
    KC_NLCK      ,   KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7        ,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4        ,   KC_P5,   KC_P6,   KC_PPLS,
    KC_P1        ,   KC_P2,   KC_P3,   KC_PENT,
    LT(_ML, KC_0),   KC_DOT,  KC_PDOT, KC_PENT
  ),

  [_ML] = LAYOUT_ortho_6x4(
    _______        , _______, _______         , _______,
    _______        , _______, _______         , _______,
    ZOOM_OUT       , BL_INC , ZOOM_IN         , KC_VOLU,
    RELEASE_GO_LEFT, BL_TOGG, RELEASE_GO_RIGHT, KC_VOLU,
    _______        , BL_DEC , _______         , KC_VOLD,
    _______        , _______, _______         , KC_VOLD
  )

};

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
        case ZOOM_IN:
            if (record->event.pressed) {
              SEND_STRING(SS_LCTL(SS_TAP(X_EQUAL)));
            }
            break;
        case ZOOM_OUT:
            if (record->event.pressed) {
              SEND_STRING(SS_LCTL(SS_TAP(X_MINUS)));
            }
            break;
    }
    return true;
};