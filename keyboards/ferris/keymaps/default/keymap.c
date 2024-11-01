#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "flow.h"
#include "repeat_key.h"
#include "smart_layer.h"


enum combos {
    COMBO_ENTER,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM ENTER_COMBO[] = {KC_C, KC_P, COMBO_END};
combo_t key_combos[] = {
    [COMBO_ENTER] = COMBO(ENTER_COMBO,        KC_ENT),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_ABC] = LAYOUT_split_3x5_2(
      KC_B, KC_L, KC_D, KC_W, KC_Q,                      KC_J, KC_F, KC_O   , KC_U   , KC_COMM,
      KC_N, KC_R, KC_T, KC_S, KC_G,                      KC_Y, KC_H, KC_A   , KC_E   , KC_I   ,
      KC_Z, KC_X, KC_M, KC_C, KC_V,                      KC_K, KC_P, KC_DOT , KC_QUOT, KC_SLSH,
      OS_UTL, KC_SPC, KC_ESC, OS_SYM),

   [_UTL] = LAYOUT_split_3x5_2(
      CTL_R  , CTL_W  , TAB_BCK, TAB_FWD, CTL_X ,        KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_DEL,
      KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, GUIALT,        KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, REPEAT,
      CTL_Z  , CTL_A  , CTL_C  , CTL_V  , CTL_S ,        CTL_I  , CTL_BS , KC_BSPC, KC_TAB , PANIC ,
      KC_TRNS, CW_TOGG, KC_ENT, SL_NUMO),

   [_SYM] = LAYOUT_split_3x5_2(
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE,       KC_HASH, KC_PERC, KC_LBRC, KC_RABK, KC_LABK,
      KC_COLN, KC_SLSH, KC_MINS, KC_DQUO, KC_TILD,       KC_UNDS, KC_DLR , KC_LSFT, KC_EXLM, KC_QUES,
      KC_SCLN, KC_PLUS, KC_ASTR, KC_EQL , KC_AMPR,       KC_CIRC, KC_AT  , KC_RBRC, KC_BSLS, PANIC  ,
      KC_GRV , KC_LGUI, QK_BOOT, KC_TRNS),

   [_NUM] = LAYOUT_split_3x5_2(
      KC_F7  , KC_F5  , KC_F3  , KC_F1  , KC_F9,         KC_F8 , KC_F10, KC_F2  , KC_F4 , KC_F6,
      KC_7   , KC_5   , KC_3   , KC_1   , KC_9 ,         KC_8  , KC_0  , KC_2   , KC_4  , KC_6 ,
      KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_F11,        KC_F12, CTL_BS, KC_BSPC, KC_TAB, PANIC,
      SL_NUMX, KC_TRNS, KC_ENT, KC_TRNS),
};


const uint16_t flow_config[FLOW_COUNT][2] = {
    {OS_UTL, KC_LGUI},
    {OS_UTL, KC_LALT},
    {OS_UTL, KC_LSFT},
    {OS_UTL, KC_LCTL},
    {OS_SYM, KC_LSFT},
};


const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_UTL, _UTL},
    {OS_SYM, _SYM},
};


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
   // DALLIUSD implementation of Callum Mods
   if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;

   // REPEAT KEY
   if (!process_repeat_key(keycode, record, REPEAT)) return false;

   // SMART LAYER
   process_layermodes(keycode, record);

   switch (keycode) {
    case SL_NUMO: // TURN ON SMART LAYER FOR _NUM LAYER
        num_mode_enable(record);
        return false;

    case SL_NUMX: // TURN OFF SMART LAYER FOR _NUM LAYER
        num_mode_disable();
        return false;

    case GUIALT:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LGUI);
            unregister_code(KC_LALT);
        }
        return false;

    case PANIC: // CLEAR EVERYTHING
        clear_oneshot_mods();
        clear_mods();
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
