#ifndef LUM_POLY_H
#define	LUM_POLY_H

#include "lum.h"
#include <stdint.h>

struct lum_poly_s
{
	int8_t note_container[LUM_POLY_VOICES];
	int8_t trigger_container[LUM_POLY_VOICES];
	int8_t velocity_container[LUM_POLY_VOICES];
	int8_t associated_voice[LUM_POLY_VOICES];
	int8_t stolen_notes[128];
	int8_t stolen_velocities[128];
	int8_t num_stolen_notes;
};

struct lum_note_s
{
	uint8_t number;
	uint8_t velocity; /* velocity = 0 => note off */
};

struct lum_poly_s lum_init_poly (void)
{
	struct lum_poly_s lum_poly;
	uint8_t i;
	for (i = 0; i < LUM_POLY_VOICES; i++)
	{
		lum_poly.note_container[i] = -1;
		lum_poly.trigger_container[i] = -1;
		lum_poly.velocity_container[i] = 0;
		lum_poly.associated_voice[i] = -1;
	}
	for (i = 0; i < 128; i++)
	{
		lum_poly.stolen_notes[i] = -1;
		lum_poly.stolen_velocities[i] = -1;
	}
	lum_poly.num_stolen_notes = 0;
	return lum_poly;
}

void lum_poly (struct lum_poly_s *poly, struct lum_note_s note)
{
#ifdef BOTTOM2ND
	/* algorithm:
	 * this is tedious but efficient
	 * the inefficient way is much easier to implement
	 * steal the note second from bottom
	 * count leading zeros might be a shortcut
	 *
	 * note on:
	 * 1. compare from bottom to top:
	 *    while new note is higher, mark position for insertion (stops when note is not higher)
	 * 2. if marked position is not empty:
	 *    move old note from marked position to stolen_notes and sort stolen notes (highest first)
	 * 3. move middle notes 1 position down
	 * 4. insert new note at marked position
	 * 5. trigger adsr
	 *
	 * note off:
	 * 1. check if note is being played
	 * 2. remove note
	 * 3. move lower notes up
	 * 4. find highest stolen note
	 * 5. insert highest stolen note at 2nd lowest position without retriggering adsr
	 *
	 */
	uint8_t i;
	uint8_t marked_position;
	struct lum_note_s stolen_note;

	/* 1. compare from bottom to top */
	marked_position = 0;
	while (poly->note_container[marked_position] < note.number)
	{
		marked_position++;
		if (marked_position > LUM_POLY_VOICES)
		{
			break;
		}
	}
	/* 2. move old note to stolen notes */
	if (poly->note_container[marked_position] > -1)
	{ /* marked position is not empty */
		/* 2. sort stolen notes */
		
	}

#endif
}


#endif	/* LUM_POLY_H */
