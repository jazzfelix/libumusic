#ifndef LUM_POLY_H
#define	LUM_POLY_H

#include "lum.h"
#include <stdint.h>

union keybits_u
{
	uint64_t keys64[2];
	uint32_t keys32[4];
	uint16_t keys16[8];
	uint8_t keys8[16];
};

struct lum_poly_s
{
	uint8_t num_keys;
	union keybits_u keyboard;
	union keybits_u keyboard_reversed;
	uint8_t playing_notes[LUM_POLY_VOICES]
	uint8_t playing_velocities[LUM_POLY_VOICES]
	uint8_t playing_triggers[LUM_POLY_VOICES]
	uint8_t velocity[128];
};

struct lum_poly_s lum_init_poly (void)
{
	struct lum_poly_s lum_poly;
	uint8_t i;
	for (i = 0; i < 128; i++)
	{
		lum_poly.velocity[i] = 0;
	}
	lum_poly.keyboard.keys64[0] = 0;
	lum_poly.keyboard.keys64[1] = 0;
	lum_poly.keyboard_reversed.keys64[0] = 0;
	lum_poly.keyboard_reversed.keys64[1] = 0;
	lum_poly.num_keys = 0;
	for (i = 0; i < LUM_POLY_VOICES; i++)
	{
		playing_notes[i] = 0;
		playing_velocities[i] = 0;
		playing_triggers[i] = 0;
	}
	return lum_poly;
}

void lum_poly (struct lum_poly_s *poly, uint8_t note_num, uint8_t velocity)
{
#ifdef BOTTOM2ND
	/* Algorithm:
	 * Always steal the 2nd note from bottom if there are more keys pressed then voices available.
	 * In other words:
	 * Play the bottom note, play (number of voices - 1) notes from top.
	 *
	 * This is how we do it:
	 * Mirror the whole keyboard in an array[128].
	 * In there store velocity and aftertouch as well as trigger information.
	 * Have an array of a total of 128 bits to store each keypress.
	 * This array serves as a shortcut for finding the lowest and topmost notes.
	 * Thus we can make use of a "count leading zeros" instruction if available on our hardware.
	 * We also want to know how many keys are pressed at any moment.
	 * We need to consider checking if we accidentally received a note on or off twice.
	 *
	 * Pseudo Code:
	 * If Note On:
	 * 	1. Check if note is already playing.
	 * 		2. Add 1 to the keypress counter.
	 * 		3. Update the keypress bit array.
	 * Else (Note Off):
	 * 	1. Check if note is already off.
	 * 		2. Subtract 1 from the keypress counter.
	 * 		3. Update the keypress bit array.
	 * 4. Update the note array.
	 * 5. Set a variable x = number of keys pressed.
	 * 	if x > 0:
	 * 		find bottom note, play it
	 * 		x = x - 1
	 * 	while x > 1: // makes sure we have 1 extra note
	 * 		find next note from top, play it
	 * 		x = x - 1
	 * 	play the new note // makes sure we trigger the new note and steal from somewhere top
	 * 6. Done.
	 * To play a note means to assign it to a voice.
	 */

	uint8_t utmp8;
	uint8_t note_count;
	uint8_t start;

	if (velocity > 0) /* If Note On: */
	{
	 	/* 1. Check if note is already playing. */
		if (poly->velocity[note] < 0)
		{
	 		/* 2. Add 1 to the keypress counter. */
			poly->num_keys += 1;
			/* 3. Update the keypress bit array. */
			utmp8 = note;
			if (utmp8 > 63)
			{
				utmp8 -= 64;
				poly->keyboard.keys64[1] |= (uint64_t)1 << utmp8;
			} else {
				poly->keyboard.keys64[0] |= (uint64_t)1 << utmp8;
			}
		}
	} else { /* Else (Note Off): */
		/* 1. Check if note is already off. */
		if (poly->velocity[note] == 0)
		{
			/* 2. Subtract 1 from the keypress counter. */
			poly->num_keys -= 1;
			/* 3. Update the keypress bit array. */
			utmp8 = note;
			if (utmp8 > 63)
			{
				utmp8 -= 64;
				poly->keyboard.keys64[1] &= !((uint64_t)1 << utmp8);
			} else {
				poly->keyboard.keys64[0] &= !((uint64_t)1 << utmp8);
			}
	}
	/* 4. Update the note array. */
	poly->velocity[note] = velocity;
	/* 5. Set a variable x = number of keys pressed. */
	utmp8 = poly->num_keys;
	/* if x > 0: */
	if (utmp8 > 0)
	{
		/* find bottom note */
		/* count leading zeros in keyboard bit array */
		note_count = lum_poly_ff1l (&poly->keyboard);
		/* play it, make sure we don't retrigger */
		/* x = x - 1 */
		utmp8 -= 1;
		/* while x > 1: // makes sure we have 1 extra note */
		start = 128;
		while (utmp8 > 1)
		{
			/* find next note from top */
			note_count = lum_poly_ff1r (&poly->keyboard, &start);
			/* play it, make sure we don't retrigger */
			/* x = x - 1 */
			utmp8 -= 1;
		}
		/* play the new note // makes sure we trigger the new note, steal from somewhere top */
	}

#endif
}


#endif	/* LUM_POLY_H */
