#include QMK_KEYBOARD_H
#include "flow.h"


enum keycodes {
   CTL_BS = SAFE_RANGE,
   CTL_A   ,
   CTL_C   ,
   CTL_L   ,
   CTL_R   ,
   CTL_S   ,
   CTL_T   ,
   CTL_V   ,
   CTL_W   ,
   TAB_BCK ,
   TAB_FWD ,
   UPDIR   ,
   CDDIR   ,
   OS_NAV  ,
   OS_NUM  ,
   OS_TWM  ,
   OS_EXT  ,
   OS_SFT  ,
   TWM_S1  ,
   TWM_S2  ,
   TWM_S3  ,
   TWM_S4  ,
   TWM_S5  ,
   TWM_S6  ,
   TWM_S7  ,
   TWM_S8  ,
   TWM_S9  ,
   TWM_TER ,
   TWM_RET ,
   TWM_RUN ,
   TWM_TAB ,
   TWM_H   ,
   TWM_J   ,
   TWM_K   ,
   TWM_L   ,
   TWM_C   ,
   TWM_SSQ ,
   TWM_SCSQ,
};


enum layers {
    _ABC,
    _NAV,
    _SYM,
    _TWM,
    _NUM,
    _EXT,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_ABC] = LAYOUT_split_3x5_2(
      KC_B, KC_L, KC_D, KC_W, KC_Z,                      KC_J, KC_F, KC_O  , KC_U   , KC_COMM,
      KC_N, KC_R, KC_T, KC_S, KC_G,                      KC_Y, KC_H, KC_A  , KC_E   , KC_I   ,
      KC_Q, KC_X, KC_M, KC_C, KC_V,                      KC_K, KC_P, KC_DOT, KC_QUOT, KC_SLSH,
      OS_NAV, KC_SPC, KC_BSPC, LT(_SYM, OS_SFT)),

   [_NAV] = LAYOUT_split_3x5_2(
      KC_ESC , CTL_W  , TAB_BCK, TAB_FWD, OS_EXT ,       KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_DEL,
      KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, CW_TOGG,       KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_ENT,
      CTL_S  , CTL_R  , CTL_C  , CTL_V  , CTL_A  ,       TWM_TAB, CTL_BS , KC_TAB , CTL_L  , CTL_T ,
      KC_TRNS, KC_TRNS, KC_LSFT, MO(_NUM)),

   [_SYM] = LAYOUT_split_3x5_2(
      KC_GRV , KC_LABK, KC_RABK, KC_DQUO, KC_PIPE,       KC_BSLS, KC_AT  , KC_LBRC, KC_RBRC, KC_TILD,
      KC_EXLM, KC_PLUS, KC_MINS, KC_EQL , KC_AMPR,       KC_HASH, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES,
      CDDIR  , KC_PERC, KC_ASTR, KC_UNDS, KC_CIRC,       KC_DLR , KC_SCLN, KC_LCBR, KC_RCBR, UPDIR  ,
      MO(_TWM), KC_TRNS, KC_TRNS, KC_TRNS),

   [_NUM] = LAYOUT_split_3x5_2(
      KC_NO  , KC_3  , KC_4   , KC_7, KC_NO,             KC_NO, KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
      KC_9   , KC_0  , KC_1   , KC_2, KC_NO,             KC_NO, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,
      KC_NO  , KC_5  , KC_6   , KC_8, KC_NO,             KC_NO, KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

   [_TWM] = LAYOUT_split_3x5_2(
      TWM_S1 , TWM_S2 , TWM_S3 , TWM_S4 , TWM_S5 ,       TWM_S6 , TWM_S7 , TWM_S8 , TWM_S9 , TWM_SCSQ,
      KC_NO  , TWM_TER, TWM_RET, TWM_RUN, KC_NO  ,       TWM_H  , TWM_J  , TWM_K  , TWM_L  , TWM_C   ,
      KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,       KC_NO  , KC_NO  , KC_NO  , KC_NO  , TWM_SSQ ,
      KC_TRNS, KC_TRNS, KC_LSFT, KC_LCTL),

   [_EXT] = LAYOUT_split_3x5_2(
      QK_BOOT, KC_NO, KC_NO, KC_NO, KC_TRNS,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO  , KC_NO, KC_NO, KC_NO, KC_NO  ,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO  , KC_NO, KC_NO, KC_NO, KC_NO  ,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_TRNS, KC_NO, KC_NO, KC_NO),
};


// flow_config should correspond to following format:
// * layer keycode
// * modifier keycode
const uint16_t flow_config[FLOW_COUNT][2] = {
    {OS_NAV, KC_LGUI},
    {OS_NAV, KC_LALT},
    {OS_NAV, KC_LSFT},
    {OS_NAV, KC_LCTL},
};


// for layers configuration follow this format:
// * custom layer key
// * layer name
const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_NAV, _NAV},
    {OS_EXT, _EXT},
};


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
   if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;

   switch (keycode) {
    case LT(_SYM, OS_SFT): // SHIFT on tap; Access SYM layer on hold
        if (record->tap.count > 0) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LSFT);
            }
            return false;
        }
        break;

    case CTL_BS: // CTRL + BACKSPACE
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_BSPC)));
        }
        break;

    case CTL_A: // CTRL + A
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_A)));
        }
        break;

    case CTL_C: // CTRL + C
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_C)));
        }
        break;

    case CTL_L: // CTRL + L
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_L)));
        }
        break;

    case CTL_R: // CTRL + R
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_R)));
        }
        break;

    case CTL_S: // CTRL + S
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_S)));
        }
        break;

    case CTL_T: // CTRL + T
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_T)));
        }
        break;

    case CTL_V: // CTRL + V
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_V)));
        }
        break;

    case CTL_W: // CTRL + W
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_W)));
        }
        break;

    case TAB_BCK: // CTRL + SHIFT + TAB
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))));
        }
        break;

    case TAB_FWD: // CTRL + TAB
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_TAB)));
        }
        break;

    case CDDIR: // MACRO FOR "~/"
        if (record->event.pressed) {
            SEND_STRING("~/");
        }
        break;

    case UPDIR: // MACRO FOR "../"
        if (record->event.pressed) {
            SEND_STRING("../");
        }
        break;

    case TWM_S1:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_1);
          unregister_code(KC_1);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S2:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_2);
          unregister_code(KC_2);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S3:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_3);
          unregister_code(KC_3);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S4:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_4);
          unregister_code(KC_4);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S5:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_5);
          unregister_code(KC_5);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S6:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_6);
          unregister_code(KC_6);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S7:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_7);
          unregister_code(KC_7);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S8:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_8);
          unregister_code(KC_8);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_S9:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_TER:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_LSFT);
          register_code(KC_ENT);
          unregister_code(KC_ENT);
          unregister_code(KC_LSFT);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_RET:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_ENT);
          unregister_code(KC_ENT);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_RUN:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_P);
          unregister_code(KC_P);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_TAB:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_TAB);
          unregister_code(KC_TAB);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_H:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_H);
          unregister_code(KC_H);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_J:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_J);
          unregister_code(KC_J);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_K:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_K);
          unregister_code(KC_K);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_L:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_L);
          unregister_code(KC_L);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_C:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_LSFT);
          register_code(KC_C);
          unregister_code(KC_C);
          unregister_code(KC_LSFT);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_SSQ:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_LSFT);
          register_code(KC_Q);
          unregister_code(KC_Q);
          unregister_code(KC_LSFT);
          unregister_code(KC_LGUI);
        }
        break;

    case TWM_SCSQ:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_LCTL);
          register_code(KC_LSFT);
          register_code(KC_Q);
          unregister_code(KC_Q);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCTL);
          unregister_code(KC_LGUI);
        }
        break;

   /*
    case VI_I: // TURN OFF VIM LAYER + HIT LETTER "I"
        if (record->event.pressed) {
            tap_code(KC_I);
            layer_off(_VIM);
        }
        return false;
        break;
   */

      }
  return true;
}


void matrix_scan_user(void) {
    flow_matrix_scan();
}

