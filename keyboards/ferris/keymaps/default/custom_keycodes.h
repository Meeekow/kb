#pragma once
#include QMK_KEYBOARD_H


enum keycodes {
   REPEAT = SAFE_RANGE,
   OS_UTL ,
   SL_NUM ,
   GUIALT ,
   PANIC  ,
};


enum layers {
    _ABC,
    _UTL,
    _SYM,
    _NUM,
    _IMP,
};


// CTRL + KEY
#define CTL_A C(KC_A)
#define CTL_C C(KC_C)
#define CTL_F C(KC_F)
#define CTL_I C(KC_I)
#define CTL_R C(KC_R)
#define CTL_V C(KC_V)
#define CTL_W C(KC_W)
#define CTL_Z C(KC_Z)
#define CTL_BS C(KC_BSPC)

// TAB
#define TAB_BCK C(S(KC_TAB))
#define TAB_FWD C(KC_TAB)

// ONE SHOT
#define _OSS OSM(MOD_LSFT)

// MOMENTARY
#define SYMB MO(_SYM)
#define IMPT MO(_IMP)

