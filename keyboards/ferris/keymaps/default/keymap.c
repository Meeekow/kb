#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "flow.h"
#include "repeat_key.h"
#include "smart_layer.h"


enum combos {
    COMBO_PANIC,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM PANIC_COMBO[] = {KC_C, KC_P, COMBO_END};

combo_t key_combos[] = {
    [COMBO_PANIC] = COMBO(PANIC_COMBO, PANIC),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_ABC] = LAYOUT_split_3x5_2(
      KC_B  , KC_L, KC_D, KC_W, KC_Q,                    KC_J, KC_F, KC_O  , KC_U   , KC_COMM,
      KC_N  , KC_R, KC_T, KC_S, KC_G,                    KC_Y, KC_H, KC_A  , KC_E   , KC_I   ,
      LSHIFT, KC_X, KC_M, KC_C, KC_V,                    KC_K, KC_P, KC_DOT, KC_QUOT, RSHIFT ,
      OS_UTL, KC_SPC, KC_ESC, OS_SYM),

   [_UTL] = LAYOUT_split_3x5_2(
      CTL_R  , CTL_W  , TAB_BCK, TAB_FWD, CDDIR,         KC_HOME, KC_PGDN, KC_PGUP, KC_END , CW_TOGG,
      KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, CTL_S,         KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_ENT ,
      CTL_Z  , CTL_A  , CTL_C  , CTL_V  , CTL_L,         CTL_I  , CTL_BS , KC_BSPC, KC_TAB , KC_DEL ,
      KC_TRNS, PANIC, REPEAT, SL_NUMO),

   [_SYM] = LAYOUT_split_3x5_2(
      KC_UNDS, KC_LPRN, KC_RPRN, KC_DLR , KC_RBRC,       KC_AT  , KC_DQUO, KC_AMPR, KC_PIPE, KC_CIRC,
      KC_EXLM, KC_PLUS, KC_MINS, KC_EQL , KC_LBRC,       KC_SLSH, KC_COLN, PARENS , KC_GRV , KC_QUES,
      KC_BSLS, KC_LABK, KC_RABK, KC_LCBR, KC_RCBR,       KC_TILD, KC_ASTR, BRACES , KC_PERC, KC_HASH,
      SL_TWMO, KC_TRNS, OS_EXT, KC_TRNS),

   [_NUM] = LAYOUT_split_3x5_2(
      KC_1   , KC_2   , KC_3   , KC_4   , KC_5 ,         KC_6 , KC_7   , KC_8   , KC_9   , KC_0   ,
      KC_7   , KC_5   , KC_3   , KC_1   , KC_9 ,         KC_8 , KC_0   , KC_2   , KC_4   , KC_6   ,
      KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_NO,         KC_NO, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,
      SL_NUMX, KC_TRNS, KC_BSPC, KC_TRNS),

   [_TWM] = LAYOUT_split_3x5_2(
      TWM_S1, TWM_S2 , TWM_S3 , TWM_S4 , TWM_S5,         TWM_S6, TWM_S7, TWM_S8, TWM_S9, TWM_SCSQ,
      KC_NO , TWM_TER, TWM_RET, TWM_RUN, KC_NO ,         TWM_H , TWM_J , TWM_K , TWM_L , TWM_C   ,
      KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO ,         KC_NO , KC_NO , KC_NO , KC_NO , TWM_SSQ ,
      KC_TRNS, KC_LSFT, KC_LCTL, SL_TWMX),

   [_EXT] = LAYOUT_split_3x5_2(
      QK_BOOT, KC_NO  , KC_NO  , KC_NO  , KC_NO ,        KC_NO , KC_NO  , KC_NO  , KC_INS , KC_PSCR,
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5 ,        KC_F6 , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
      KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_F11,        KC_F12, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,
      KC_NO, KC_NO, KC_TRNS, KC_NO),
};


const uint16_t flow_config[FLOW_COUNT][2] = {
    {OS_UTL, KC_LGUI},
    {OS_UTL, KC_LALT},
    {OS_UTL, KC_LSFT},
    {OS_UTL, KC_LCTL},
};


const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_UTL, _UTL},
    {OS_SYM, _SYM},
    {OS_EXT, _EXT},
};


bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSHIFT:
        case RSHIFT:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t* record) {

   // DALLIUSD implementation of Callum Mods
   if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;

   // REPEAT KEY
   if (!process_repeat_key(keycode, record, REPEAT)) return false;

   // SMART LAYER
   process_layermodes(keycode, record);

   switch (keycode) {

    /*
    case LT(_NUM, KC_F15): // SHIFT on tap; Access NUM layer on hold
        if (record->tap.count > 0) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LSFT);
            }
            return false;
        }
        break;

    case OS_WRK: // Sets default layer to _WRK;
        if (record->event.pressed) {
            default_layer_set(0x00000002); // Increment by 2 any succeeding alt layer
        }
        break;
    */

    case SL_NUMO: // TURN ON SMART LAYER FOR _NUM LAYER
        num_mode_enable(record);
        return false;

    case SL_NUMX: // TURN OFF SMART LAYER FOR _NUM LAYER
        num_mode_disable();
        return false;

    case SL_TWMO: // TURN ON SMART LAYER FOR _TWM LAYER
        twm_mode_enable(record);
        return false;

    case SL_TWMX: // TURN OFF SMART LAYER FOR _TWM LAYER
        twm_mode_disable();
        return false;

    case CDDIR:
        if (record->event.pressed) {
            SEND_STRING("cd ~/");
        }
        return false;

    case PARENS:
        if (record->event.pressed) {
            SEND_STRING("()" SS_TAP(X_LEFT));
        }
        return false;

    case BRACES:
        if (record->event.pressed) {
            SEND_STRING("{}" SS_TAP(X_LEFT));
        }
        return false;

    case PANIC: // CLEAR EVERYTHING
        clear_mods();
        clear_oneshot_mods();
        if (get_oneshot_layer() != 0) {
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        }
        default_layer_set(0x00000001);
        layer_move(0);
        caps_word_off();
        return false;
      }

  return true;
}


void matrix_scan_user(void) {
    flow_matrix_scan();
}

