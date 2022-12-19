#ifndef LUM_CONFIG_H
#define	LUM_CONFIG_H

#include "lum.h"

/* hardware specific configuration */

#define MIDI_DATA_AVAILABLE (U1STAHbits.URXBE == 0)

#define MIDI_TX_BUFFER_SIZE 8

#define MIDI_RX_BYTE U1RXREG

#endif	/* LUM_CONFIG_H */

