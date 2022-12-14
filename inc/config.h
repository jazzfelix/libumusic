#ifndef LUM_CONFIG_H
#define	LUM_CONFIG_H

/* hardware specific configuration */

#define MIDI_DATA_AVAILABLE (U1STAHbits.URXBE == 0)

#define MIDI_SEND_BUFFER_SIZE 8

#endif	/* LUM_CONFIG_H */

