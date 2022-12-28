#ifndef LUM_UC_H
#define	LUM_UC_H

#include <stdint.h>

union keybits_u
{
	uint64_t keys64[2];
	uint32_t keys32[4];
	uint16_t keys16[8];
	uint8_t keys8[16];
};

/* UART receive buffer empty flag */
#define MIDI_DATA_AVAILABLE (U1STAHbits.URXBE == 0)

/* UART receive buffer register */
#define MIDI_RX_BYTE U1RXREG


uint8_t static __attribute__((always_inline, flatten)) inline
lum_ff1l (uint16_t x)
{
	asm ({});
	return 0;
}

uint8_t static __attribute__((always_inline, flatten)) inline
lum_ff1r (uint16_t x)
{
	return 0;
}

/* count leading zeros algorithm for lum_poly polyphony handler */
uint8_t static __attribute__((always_inline, flatten)) inline
lum_poly_ff1l (union keybits_u *keys)
{
	uint8_t i;
	uint8_t count = 0;
	for (i = 0; i < 8; i++)
	{
		keys->keys16[i];
	}
	return 0;
}

uint8_t static __attribute__((always_inline, flatten)) inline
lum_poly_ff1l (union keybits_u *keys, uint8_t *start)
{
	return 0;
}

#endif /* LUM_UC_H */
