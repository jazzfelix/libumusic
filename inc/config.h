#ifndef LUM_CONFIG_H
#define	LUM_CONFIG_H

#include "lum.h"

/*********** hardware specific configuration ***********/

#include "dspic33c.h"

/*********** software specific configuration ***********/

/* MIDI send is not implemented yet */
#define MIDI_TX_BUFFER_SIZE 8

/* Number of polyphonic voices - must be between 1 and 128 */
#define LUM_POLY_VOICES 8

/* Polyphonic Voice Stealing Algorithm - BOTTOM2ND is the only implemented yet */
#define LUM_POLY_STEALING BOTTOM2ND

#endif	/* LUM_CONFIG_H */

