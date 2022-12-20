# libumusic - Microcontroller Music Library

Currently this is just a parser for MIDI messages. It is optimised for running on microcontrollers.
It is very fast and uses very low memory.

# Usage

Include `libumusic/inc/lum.h` in your C code:

`#include "libumusic/inc/lum.h"`

Declare an empty structure for MIDI data:

`struct midi_s midi = {};`

In Regular intervals of less then 1 ms call this function:

`lum_midi_rx (&midi);`

Implement the following functions in your code:

```
ALWAYS_INLINE void* lum_process_note (struct midi_s* midi);
ALWAYS_INLINE void* lum_process_cc (struct midi_s* midi);
ALWAYS_INLINE void* lum_process_pc (uint8_t pc);
ALWAYS_INLINE void* lum_process_bend (uint16_t bend);
```

They always need to be present even if you don't need them.
At least implement them with an empty function body:

```
ALWAYS_INLINE void* lum_process_note (struct midi_s* midi) {}
ALWAYS_INLINE void* lum_process_cc (struct midi_s* midi) {}
ALWAYS_INLINE void* lum_process_pc (struct midi_s* midi) {}
ALWAYS_INLINE void* lum_process_bend (struct midi_s* midi) {}
```

In `lum_process_note ()` check if `midi->cmd` is a Note On (`0x90`) or
Note Off (`0x80`). You might also want to use `midi->note` and `midi->velocity`.
Receiving `midi->velocity == 0` and Command `0x90` means you have just
received a Note Off. Some keyboards or softwares send it like that.

`lum_process_cc ()` processes Control Change messages. You can read `midi->cc` (Controller number)
and `midi->cc_value` (Controller value) inside this function.

## Roadmap

This will contain handling of polyphony one day.

I will provide example code and more detailed documentation in the future.

## Disclaimer

I test all my code on dsPIC hardware. I might nonetheless push untested code.
I will add release or version tags to tested code though.
