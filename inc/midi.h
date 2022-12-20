#ifndef LUM_MIDI_H
#define	LUM_MIDI_H

#include <stdint.h>
#include "lum.h"

#define LUM_OMNI 17

struct midi_s {
    uint8_t channel;
    uint8_t rx_byte;
    uint8_t cmd;
    uint8_t stage;
    uint8_t velocity;
    uint8_t note;
    uint8_t cc;
    uint8_t cc_value;
    uint8_t bend1;
    uint8_t send_data[MIDI_TX_BUFFER_SIZE];
    uint8_t send_n;
    uint8_t send_i;
};

ALWAYS_INLINE uint8_t lum_midi_rx_byte (void)
{
	return MIDI_RX_BYTE;
}

ALWAYS_INLINE void lum_process_note (struct midi_s* midi);
ALWAYS_INLINE void lum_process_cc (struct midi_s* midi);
ALWAYS_INLINE void lum_process_pc (uint8_t pc);
ALWAYS_INLINE void lum_process_bend (uint16_t bend);

ALWAYS_INLINE void lum_midi_rx (struct midi_s* midi)
{
	if (MIDI_DATA_AVAILABLE) {
		/* store midi byte */
		midi->rx_byte = lum_midi_rx_byte ();
		/* check if byte is a command */
		if (midi->rx_byte > 127)
		{
			/* check if we are in omni mode or it is our channel */
			if ((midi->channel == LUM_OMNI) | ((midi->channel - 1) == (midi->rx_byte & 0xf)))
			{
                        	midi->cmd   = midi->rx_byte & 0xf0;
                        	midi->stage = 0;
			/* the data is not for us */
			} else {
				midi->cmd   = 0;
			}
		/* received byte is data */
		} else {
			midi->stage++;
			switch (midi->cmd)
			{
				case 0: /* the data was not for us */
					break;
				case 0x80: /* note off */
				case 0x90: /* note on */
					switch (midi->stage)
					{
						case 1:
							midi->velocity = midi->rx_byte;
							break;
						case 2:
							midi->note     = midi->rx_byte;
							midi->stage    = 0;
							lum_process_note (midi);
							break;
						default:
							break;
					}
					break;
				case 0xA0: /* polyphonic aftertouch */
					break;
				case 0xB0: /* control change */
					switch (midi->stage)
					{
						case 1:
							midi->cc       = midi->rx_byte;
							break;
						case 2:
							midi->cc_value = midi->rx_byte;
							midi->stage    = 0;
							lum_process_cc (midi);
							break;
						default:
							break;
					}
					break;
				case 0xC0: /* program change */
					midi->stage = 0;
					lum_process_pc (midi->rx_byte);
					break;
				case 0xD0: /* aftertouch */
					break;
				case 0xE0: /* pitch bend */
					switch (midi->stage)
					{
						case 1:
							midi->bend1 = midi->rx_byte; /* low byte */
							break;
						case 2:
							midi->stage = 0;
							lum_process_bend (((uint16_t)midi->rx_byte << 7) + midi->bend1);
							break;
						default:
							break;
					}
					break;
				case 0xF0: /* system common / real time */
					midi->cmd   = 0;
					midi->stage = 0;
					switch (midi->rx_byte)
					{
						case 0xF1: /* midi time code */
							break;
						case 0xF2: /* song position */
							break;
						case 0xF3: /* song select */
							break;
						case 0xF8: /* clock tick (24 times per quarter note) */
							break;
						case 0xFA: /* start */
							break;
						case 0xFB: /* continue */
							break;
						case 0xFC: /* stop */
							break;
						case 0xFF: /* reset */
							break;
					}
					break;
				default:
					break;
			}
		}
	}
}

#endif	/* LUM_MIDI_H */
