# libumusic - Library for Microcontroller Music
# short: lum / lµm

Currently this is just a parser for receiving and handling MIDI messages in C programs. It is optimised for running on microcontrollers.
It is very fast and uses very low memory. 

# Usage

Configure `lum` according to your hardware in `libumusic/inc/config.h`.

Include `libumusic/inc/lum.h` in your C code:

`#include "libumusic/inc/lum.h"`

Declare an empty structure for MIDI data:

`struct midi_s midi = {};`

In Regular intervals of less then 1 ms call this function:

`lum_midi_rx (&midi);`

Implement the following functions in your code:

```
ALWAYS_INLINE void lum_process_note (struct midi_s* midi);
ALWAYS_INLINE void lum_process_cc (struct midi_s* midi);
ALWAYS_INLINE void lum_process_pc (uint8_t pc);
ALWAYS_INLINE void lum_process_bend (uint16_t bend);
```

These functions will be called whenever a MIDI event of the according
type is received:
|  message type  |     function     |
|----------------|------------------|
|  note on/off   | lum_process_note |
| control change | lum_process_cc   |
| program change | lum_process_pc   |
| pitch bend     | lum_process_bend |

They always need to be present even if you don't need them.
At least implement them with an empty function body:

```
ALWAYS_INLINE void lum_process_note (struct midi_s* midi) {}
ALWAYS_INLINE void lum_process_cc (struct midi_s* midi) {}
ALWAYS_INLINE void lum_process_pc (uint8_t pc) {}
ALWAYS_INLINE void lum_process_bend (uint16_t bend) {}
```

To interact with the rest of your code you need to prepare global variables
which these functions can modify. If you want to change a variable `pitch` for
example `pitch` needs to be declared globally or in the same *.c file as the
function `lum_process_note`.

In `lum_process_note ()` check if `midi->cmd` is a Note On (`0x90`) or
Note Off (`0x80`). You might also want to use `midi->note` and `midi->velocity`.
Receiving `midi->velocity == 0` and Command `0x90` means you have just
received a Note Off. Some keyboards or softwares send it like that.

`lum_process_cc ()` processes Control Change messages. You can read `midi->cc` (Controller number)
and `midi->cc_value` (Controller value) inside this function.

Here is a simple example for an implementation of `lum_process_note`:

```
uint8_t pitch    = 0;
uint8_t velocity = 0;
bool trigger     = false;

ALWAYS_INLINE void lum_process_note (struct midi_s* midi)
{
	pitch    = midi->note;
	velocity = midi->velocity;
	trigger  = true;
}
```

## Roadmap

### Done

- [ ] MIDI parser

### To Do

- [ ] handler for polyphony
- [ ] example code
- [ ] documentation
- [ ] receive MIDI clock and transport commands (time code, song position/select, clock, play, stop, continue, reset)
- [ ] receive MIDI aftertouch
- [ ] receive MIDI polyphonic aftertouch
- [ ] basic scheduling

## Disclaimer

I test all my code on dsPIC hardware. I might nonetheless push untested code.
I will add release or version tags to tested code though.
