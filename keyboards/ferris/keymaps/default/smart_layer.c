#include "smart_layer.h"
#include "custom_keycodes.h"

/* -------- Number Mode -------- */
static bool _num_mode_active = false;
static uint16_t num_mode_timer;
// Turn number mode on. To be called from a custom keycode
void num_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_NUM);
        num_mode_timer = timer_read();
    } else {
        if (timer_elapsed(num_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode
            _num_mode_active = true;
        } else {
            // Holding treats as a normal LT
            layer_off(_NUM);
        }
    }
}

// Turn number mode off.
void num_mode_disable(void) {
    _num_mode_active = false;
    layer_off(_NUM);
}

void num_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case KC_1 ... KC_0:
        case KC_BSPC:
            // process the code and stay in the mode *dabs*
            break;
        default:
            // All other keys disable the layer mode on keyup.
            if (!record->event.pressed) {
                num_mode_disable();
            }
            break;
    }
}


/* -------- TWM Mode -------- */
static bool _twm_mode_active = false;
static uint16_t twm_mode_timer;
// Turn twm mode on. To be called from a custom keycode
void twm_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_TWM);
        twm_mode_timer = timer_read();
    } else {
        if (timer_elapsed(twm_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode
            _twm_mode_active = true;
        } else {
            // Holding treats as a normal LT
            layer_off(_TWM);
        }
    }
}

// Turn twm mode off.
void twm_mode_disable(void) {
    _twm_mode_active = false;
    layer_off(_TWM);
}

void twm_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case TWM_S1:
        case TWM_S2:
        case TWM_S3:
        case TWM_S4:
        case TWM_S5:
        case TWM_S6:
        case TWM_S7:
        case TWM_S8:
        case TWM_S9:
        case TWM_H:
        case TWM_J:
        case TWM_K:
        case TWM_L:
        case TWM_C:
        case TWM_SCSQ:
        case KC_LSFT:
        case KC_LCTL:
            // process the code and stay in the mode *dabs*
            break;
        default:
            // All other keys disable the layer mode on keyup.
            if (!record->event.pressed) {
                twm_mode_disable();
            }
            break;
    }
}

/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record) {
    if (_num_mode_active) {
        num_mode_process(keycode, record);
    } else if (_twm_mode_active) {
        twm_mode_process(keycode, record);
    }
}

