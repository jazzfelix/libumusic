#ifndef MIDI_H
#define	MIDI_H

#include <stdint.h>

#define MIDI_SEND_BUFFER_SIZE 8

struct midi_s {
    uint8_t channel;
    uint8_t tmp;
    uint8_t stage;
    int note_wh;
    uint8_t note_tmp;
    uint8_t mask;
    uint8_t size;
    uint8_t offset;
    uint8_t var;
    uint8_t kmd_short;
    uint8_t kmd_long;
    uint8_t data[2];
    uint8_t velocity;
    uint8_t tick;
    uint8_t send_data[MIDI_SEND_BUFFER_SIZE];
    uint8_t send_n;
    uint8_t send_i;
    uint8_t sent_cc[128];
    int poly_notes[4];
    int assigned_voice[4];
    unsigned char poly_gate_bits;
};

#endif	/* MIDI_H */

