#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "flow.h"
#include "repeat_key.h"
#include "smart_layer.h"


combo_t key_combos[] = {};
uint16_t COMBO_LEN = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT_split_3x5_2(
      KC_B, KC_L, KC_D, KC_W, KC_Q,                     KC_J, KC_F, KC_O  , KC_U   , KC_COMM,
      KC_N, KC_R, KC_T, KC_S, KC_G,                     KC_Y, KC_H, KC_A  , KC_E   , KC_I   ,
      KC_Z, KC_X, KC_M, KC_C, KC_V,                     KC_K, KC_P, KC_DOT, KC_QUOT, KC_SCLN,
      OS_UTL, KC_SPC, KC_ESC, OS_SYM),

  [_UTL] = LAYOUT_split_3x5_2(
      CTL_R  , CTL_W  , TAB_BCK, TAB_FWD, CTL_S,        KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_DEL ,
      KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, STT  ,        KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, REPEAT ,
      CTL_Z  , CTL_A  , CTL_C  , CTL_V  , CTL_F,        CTL_I  , CTL_BS , KC_BSPC, KC_TAB , CW_TOGG,
      PANIC, CTSFA, KC_ENT, SL_NUM),

  [_SYM] = LAYOUT_split_3x5_2(
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_UNDS,      KC_AT  , KC_TILD, KC_LBRC, KC_RBRC, KC_CIRC,
      KC_EXLM, KC_DQUO, KC_MINS, KC_COLN, KC_QUES,      KC_AMPR, KC_EQL , KC_LSFT, KC_RABK, KC_LABK,
      KC_PERC, KC_ASTR, KC_PLUS, KC_SLSH, KC_DLR ,      KC_PIPE, KC_HASH, KC_BSLS, KC_BSLS, IMPT   ,
      KC_GRV, KC_LGUI, KC_PSCR, PANIC),

  [_NUM] = LAYOUT_split_3x5_2(
      KC_NO, KC_9, KC_8, KC_7, KC_NO,                   KC_NO, KC_NO  , MS_WHLU, KC_NO  , KC_NO,
      KC_NO, KC_3, KC_2, KC_1, KC_NO,                   KC_NO, MS_BTN1, MS_WHLD, MS_BTN2, KC_NO,
      KC_NO, KC_6, KC_5, KC_4, KC_NO,                   KC_NO, KC_NO  , KC_BSPC, KC_TAB , KC_NO,
      KC_0, KC_TRNS, KC_ENT, PANIC),

  [_IMP] = LAYOUT_split_3x5_2(
      PANIC  , PANIC, PANIC, PANIC, PANIC,              PANIC, PANIC, PANIC, PANIC, PANIC,
      PANIC  , PANIC, PANIC, PANIC, PANIC,              PANIC, PANIC, PANIC, PANIC, PANIC,
      QK_BOOT, PANIC, PANIC, PANIC, PANIC,              PANIC, PANIC, PANIC, PANIC, PANIC,
      PANIC, PANIC, PANIC, PANIC),
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
    case SL_NUM: // TURN ON SMART LAYER FOR _NUM LAYER
      num_mode_enable(record);
      return false;

    case GUIALT: // HOLD WIN + ALT FOR GNOME DE
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
      }
      return false;

    case GUICTL: // HOLD WIN + CTL FOR WINDOWS 11 DE
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
      }
      return false;

    case PANIC: // CLEAR EVERYTHING
      clear_oneshot_mods();
      clear_mods();
      if (get_oneshot_layer() != 0) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      }
      num_mode_disable();
      caps_word_off();
      default_layer_set(0x00000001);
      layer_move(0);
      return false;
  }

  return true;
}


void matrix_scan_user(void) {
  flow_matrix_scan();
}
