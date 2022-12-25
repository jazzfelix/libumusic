#ifndef LUM_POLY_H
#define	LUM_POLY_H

#include "lum.h"
#include <stdint.h>

struct lum_poly_s
{
};

struct lum_poly_s lum_init_poly (void)
{
	struct lum_poly_s lum_poly;
	return lum_poly;
}

void lum_poly (struct lum_poly_s *poly, struct lum_note_s note)
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
	 * Have two arrays of a total of 128 bits to store each keypress.
	 * The first of them is "little endian" the second is "big endian".
	 * These arrays serve as a shortcut for finding the lowest and topmost notes.
	 * Thus we can make use of a "count leading zeros" instruction if available on our hardware.
	 * We also want to know how many keys are pressed at ant moment.
	 * We need to consider checking if we accidentally received a note on or off twice.
	 *
	 * Pseudo Code:
	 * If Note On:
	 * 	1. Check the note array (do we retrigger?).
	 * 	2. If the last question was answered with "no" add 1 to the keypress counter.
	 * 	3. Update the note array.
	 * 	4. Update the keypress bit arrays.
	 * Else (Note Off):
	 * 	1. Check the note array (is the key already off?).
	 * 	2. If the last question was answered with "no" subtract 1 from the keypress counter.
	 * 	3. Update the note array.
	 * 	4. Update the keypress bit arrays.
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
	 * I think this description of the algorithm is sufficient to the point it can
	 * be just implemented. :)
	 *
	 */

#endif
}


#endif	/* LUM_POLY_H */
