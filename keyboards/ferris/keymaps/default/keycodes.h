#pragma once
#include QMK_KEYBOARD_H


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
   CTL_VES ,
   TAB_BCK ,
   TAB_FWD ,
   UPDIR   ,
   CDDIR   ,
   REPEAT  ,
   OS_NAV  ,
   OS_SYM  ,
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
   TWM_H   ,
   TWM_J   ,
   TWM_K   ,
   TWM_L   ,
   TWM_C   ,
   TWM_SSQ ,
   TWM_SCSQ,
   SL_NUM  ,
};


enum layers {
    _ABC,
    _NAV,
    _SYM,
    _TWM,
    _NUM,
    _EXT,
};

