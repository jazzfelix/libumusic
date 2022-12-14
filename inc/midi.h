#ifndef MIDI_H
#define	MIDI_H

#include <stdint.h>

#define MIDI_SEND_BUFFER_SIZE 8

struct midi_s {
    uint8_t tmp;
    uint8_t channel;
    uint8_t rx_byte;
    uint8_t cmd;
    uint8_t stage;
    uint8_t note_tmp;
    uint8_t mask;
    uint8_t size;
    uint8_t offset;
    uint8_t var;
    uint8_t data[2];
    uint8_t velocity;
    uint8_t tick;
    uint8_t send_data[MIDI_SEND_BUFFER_SIZE];
    uint8_t send_n;
    uint8_t send_i;
    uint8_t sent_cc[128];
};

#endif	/* MIDI_H */

