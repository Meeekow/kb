#pragma once
#include QMK_KEYBOARD_H


/* -------- Util Mode -------- */
// Turn util mode on. To be called from a custom keycode
void utl_mode_enable(keyrecord_t *record);

// Turn util mode off.
void utl_mode_disable(void);

// Handle each key for util mode.
void utl_mode_process(uint16_t keycode, keyrecord_t *record);


/* -------- Number Mode -------- */
// Turn number mode on. To be called from a custom keycode
void num_mode_enable(keyrecord_t *record);

// Turn number mode off.
void num_mode_disable(void);

// Handle each key for number mode.
void num_mode_process(uint16_t keycode, keyrecord_t *record);


/* -------- TWM Mode -------- */
// Turn twm mode on. To be called from a custom keycode
void twm_mode_enable(keyrecord_t *record);

// Turn twm mode off.
void twm_mode_disable(void);

// Handle each key for twm mode.
void twm_mode_process(uint16_t keycode, keyrecord_t *record);


/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record);

