#include "smart_layer.h"
#include "custom_keycodes.h"


/* -------- Number Mode -------- */
static bool _num_mode_active = false;
static uint16_t num_mode_timer;
// Turn number mode on. To be called from a custom keycode.
void num_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_NUM);
        num_mode_timer = timer_read();
    } else {
        if (timer_elapsed(num_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode.
            _num_mode_active = true;
        } else {
            // Holding treats as a normal LT.
            layer_off(_NUM);
        }
    }
}


// Turn number mode off.
void num_mode_disable(void) {
    layer_off(_NUM);
    _num_mode_active = false;
}


// Assess if we should exit layermode or continue processing normally.
void num_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Define what keys will exit num mode.
    switch (keycode) {
        case KC_1 ... KC_0:
	case KC_BSPC:
            // Process the code and stay in the mode *dabs*
            break;
        default:
            // All other keys disable the layer mode on keyup.
            if (!record->event.pressed) {
                num_mode_disable();
            }
            break;
    }
}


/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record) {
    if (_num_mode_active) {
        num_mode_process(keycode, record);
    }
}
