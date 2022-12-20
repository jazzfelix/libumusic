#ifndef LUM_CONFIG_H
#define	LUM_CONFIG_H

#include "lum.h"

/*********** hardware specific configuration ***********/

/* UART receive buffer empty flag */
#define MIDI_DATA_AVAILABLE (U1STAHbits.URXBE == 0)

/* UART receive buffer register */
#define MIDI_RX_BYTE U1RXREG

/* MIDI send is not implemented yet */
#define MIDI_TX_BUFFER_SIZE 8

#endif	/* LUM_CONFIG_H */

