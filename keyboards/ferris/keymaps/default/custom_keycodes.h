#pragma once
#include QMK_KEYBOARD_H


enum keycodes {
   REPEAT = SAFE_RANGE,
   OS_NAV  ,
   OS_SYM  ,
   OS_EXT  ,
   CTL_BS  ,
   CTL_A   ,
   CTL_C   ,
   CTL_I   ,
   CTL_L   ,
   CTL_R   ,
   CTL_S   ,
   CTL_V   ,
   CTL_W   ,
   CTL_Z   ,
   TAB_BCK ,
   TAB_FWD ,
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
   TWM_H   ,
   TWM_J   ,
   TWM_K   ,
   TWM_L   ,
   TWM_C   ,
   TWM_SSQ ,
   TWM_SCSQ,
   PAREN   ,
   BRACE   ,
   ARROW   ,
   QUOTE   ,
   CDDIR   ,
   SL_NUMO ,
   SL_NUMX ,
   SL_UTLO ,
   SL_TWMO ,
   SL_TWMX ,
   PANIC   ,
};


enum layers {
    _ABC,
    _NAV,
    _UTL,
    _SYM,
    _NUM,
    _TWM,
    _EXT,
};


#define OS_SFT OSM(MOD_LSFT)

