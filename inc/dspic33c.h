#ifndef LUM_UC_H
#define	LUM_UC_H

#include <stdint.h>

typedef uint16_t keybits_t;

/* UART receive buffer empty flag */
#define MIDI_DATA_AVAILABLE (U1STAHbits.URXBE == 0)

/* UART receive buffer register */
#define MIDI_RX_BYTE U1RXREG

/*  Note storage for fast implementation of BOTTOM2ND note stealing algorithm
 *
 *  The array keybits is holding one bit for each of the 128 notes.
 *  The elements of the array keybits are 16 bit wide.
 *  The array can be visualised like a big 128 bit variable.
 *  It is starting left with bit number 0 and ending right at bit number 127.
 *  keybits[0]   [1]    [2]    [3]    ... [7]
 *         0..15 16..31 32..47 48..63 ... 112..127
 *  Bit ordering is a bit confusing because normally it is counted from
 *   right to left. See bit shift: 1 << 15
 *
 */

void static __attribute__((always_inline, flatten)) inline
lum_poly_fill_array (uint8_t note, keybits_t (keybits[]))
{
	int16_t i;
	i = 0;
	while (note > 15)
	{
		i++;
		note -= sizeof (keybits_t) * 8;
	}
	keybits[i] = keybits[i] | (1 << (15 - note));
}

void static __attribute__((always_inline, flatten)) inline
lum_poly_clr_array (uint8_t note, keybits_t keybits[])
{
	int16_t i;
	uint16_t bits;
	i = 0;
	while (note > 15)
	{
		i++;
		note -= sizeof (keybits_t) * 8;
	}
	bits       = keybits[i];
	bits       = bits & ~(1 << (15 - note));
	keybits[i] = bits;
}

/* the following 4 xxx_ff1x functions only work when compiled with O1, not O0 */

uint16_t static __attribute__((always_inline, flatten)) inline
lum_ff1l (uint16_t register x)
{
	uint16_t register result;
    	asm ("ff1l %0, %1" : "=r"(result) : "r"(x));
	return result;
}

uint8_t static __attribute__((always_inline, flatten)) inline
lum_ff1r (uint16_t register x)
{
	uint16_t result;
    	asm ("ff1r %0, %1" : "=r"(result) : "r"(x));
	return result;
}

/* count leading zeros algorithm for lum_poly polyphony handler */
uint8_t static __attribute__((always_inline, flatten)) inline
lum_poly_ff1l (keybits_t *keys)
{
	int16_t i;
	int16_t count = -1;
	uint16_t tmp;
	uint16_t register x;
	for (i = 0; i < (128 / sizeof (keybits_t) / 8); i++)
	{
		x = keys[i];
		tmp = lum_ff1l(x);
		if (tmp == 0)
		{
			count += sizeof (keybits_t) * 8;
		} else {
			count += tmp;
			break;
		}
	}
	return count;
}

uint8_t static __attribute__((always_inline, flatten)) inline
lum_poly_ff1r (keybits_t *keys, uint8_t *start)
{
	int16_t i;
	int16_t count;
	volatile uint16_t tmp;
	volatile uint16_t register x;
	volatile uint16_t mask;
	volatile uint16_t maskbit;
	volatile uint16_t segment;
	segment = (*start - 1) >> 4;
	maskbit = *start & 0xf; /* 0 .. 15 */
	// idea2:
	// use 0xffff and shift by masked start
	// in case of 128 it is not shifted
	maskbit = (16 - maskbit) & 0xf; /* adjust direction of counting */
	mask    = 0xffff >> maskbit;    /* generate mask */
	mask    = mask << maskbit;      /* shift mask into correct position */
	//
	// example detect bit 7, start = 13
	// maskbit = 13 & 0xf = 13
	// maskbit = (16 - 13) & 0xf = 3 & 0xf = 3
	// mask    = 0xffff >> 3 = 0x1fff
	// mask    = 0xffff << 3 = 0xfff8
	// count   = ((13 >> 3) << 3) + 15 = (1 << 3) + 15 = 8 + 15 = 23
	// for (i = 23-15 / sizeof (keybits_t) / 8 = 8 / 16 = 0; i >=0; i--)
	// 	x = keys[0] = 260
	// 	x = x & mask = 260 & 0xfff8 = 256 = 0x100
	// 	tmp = lum_ff1r(256) = 9 ?
	//	if (tmp == 0) => else
	//		count = count - tmp = 23 - 9 = 14
	//		count += 1 = 15
	// return 15!!!
	//
	//count   = ((*start >> 3) << 3) + 15; // die Zeile ist doof, wenn ... ja wenn?
	count   = segment * 16 + 15;
	for (i = segment; i >= 0; i--)
	{
		x = keys[i];
		x = x & mask;
		tmp = lum_ff1r(x);
		if (tmp == 0)
		{
			count -= sizeof (keybits_t) * 8;
			mask  = 0xffff; /* mask is not valid in the next segment */
		} else {
			count -= tmp;
			count += 1;
			break; /* found a note, end for loop */
		}
	}
	return count;
}

#endif /* LUM_UC_H */
