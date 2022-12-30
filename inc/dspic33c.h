#ifndef LUM_UC_H
#define	LUM_UC_H

#include <stdint.h>

typedef uint16_t keybits_t;

/* UART receive buffer empty flag */
#define MIDI_DATA_AVAILABLE (U1STAHbits.URXBE == 0)

/* UART receive buffer register */
#define MIDI_RX_BYTE U1RXREG

void static __attribute__((always_inline, flatten)) inline
lum_poly_fill_array (uint8_t note, keybits_t *keybits[128 / sizeof (keybits_t) / 8])
{
	int16_t i;
	i = 0;
	while (note > 15)
	{
		i++;
		note -= sizeof (keybits_t) * 8;
	}
	keybits[i] = *keybits[i] | (1 << (15 - note));
}

void static __attribute__((always_inline, flatten)) inline
lum_poly_clr_array (uint8_t note, keybits_t *keybits[128 / sizeof (keybits_t) / 8])
{
	int16_t i;
	i = 0;
	while (note > 15)
	{
		i++;
		note -= sizeof (keybits_t) * 8;
	}
	keybits[i] = *keybits[i] & !(1 << (15 - note));
}

uint16_t static __attribute__((always_inline, flatten)) inline
lum_ff1l (uint16_t x)
{
	uint16_t result;
	asm ("FF1L %0, %1"
		: "=r"(result)
		: "r"(x)
	);
	return result;
}

uint8_t static __attribute__((always_inline, flatten)) inline
lum_ff1r (uint16_t x)
{
	return 0;
}

/* count leading zeros algorithm for lum_poly polyphony handler */
uint8_t static __attribute__((always_inline, flatten)) inline
lum_poly_ff1l (keybits_t *keys)
{
	uint16_t i;
	int16_t count = 0;
	uint16_t tmp;
	for (i = 0; i < (128 / sizeof (keybits_t) / 8); i++)
	{
		tmp = lum_ff1l(keys[i]);
		if (tmp > 0)
		{
			count += tmp - 1;
			break;
		} else {
			count += sizeof (keybits_t) * 8;
		}
	}
	return count;
}

uint8_t static __attribute__((always_inline, flatten)) inline
lum_poly_ff1r (keybits_t *keys, uint8_t *start)
{
	return 0;
}

#endif /* LUM_UC_H */
