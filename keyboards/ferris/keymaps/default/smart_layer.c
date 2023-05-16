#include "smart_layer.h"
#include "keycodes.h"

/* -------- Number Mode -------- */
static bool _num_mode_active = false;
// Turn number mode on. To be called from a custom keycode
void num_mode_enable(keyrecord_t *record) {
    _num_mode_active = true;
    layer_on(_NUM);
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

/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record) {
    if (_num_mode_active) {
        num_mode_process(keycode, record);
    }
}

