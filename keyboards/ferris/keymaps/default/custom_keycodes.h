#pragma once
#include QMK_KEYBOARD_H


enum keycodes {
   REPEAT = SAFE_RANGE,
   ALTREP ,
   OS_UTL ,
   OS_SYM ,
   OS_EXT ,
   SL_NUMO,
   SL_NUMX,
   SL_TWMO,
   SL_TWMX,
   CDDIR  ,
   PARENS ,
   CPYPSTA,
   UNDREDO,
   VI_VIW ,
   UPDOWN ,
   PANIC  ,
};


enum layers {
    _ABC,
    _UTL,
    _SYM,
    _NUM,
    _TWM,
    _EXT,
};


// CTRL + LETTER
#define CTL_A C(KC_A)
#define CTL_L C(KC_L)
#define CTL_S C(KC_S)
#define CTL_W C(KC_W)
#define CTL_R C(KC_R)
#define CTL_I C(KC_I)
#define CTL_BS C(KC_BSPC)

// TAB
#define TAB_BCK C(S(KC_TAB))
#define TAB_FWD C(KC_TAB)

// TWM
#define TWM_S1 G(KC_1)
#define TWM_S2 G(KC_2)
#define TWM_S3 G(KC_3)
#define TWM_S4 G(KC_4)
#define TWM_S5 G(KC_5)
#define TWM_S6 G(KC_6)
#define TWM_S7 G(KC_7)
#define TWM_S8 G(KC_8)
#define TWM_S9 G(KC_9)

#define TWM_TER G(S(KC_ENT))
#define TWM_RET G(KC_ENT)
#define TWM_RUN G(KC_P)

#define TWM_H G(KC_H)
#define TWM_J G(KC_J)
#define TWM_K G(KC_K)
#define TWM_L G(KC_L)

#define TWM_C G(S(KC_C))

#define TWM_SSQ G(S(KC_Q))
#define TWM_SCSQ G(C(S(KC_Q)))

