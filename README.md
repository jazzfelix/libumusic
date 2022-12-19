# libumusic - Microcontroller Music Library

Currently this is just a parser for MIDI messages. It is optimised for running on microcontrollers.
It is very fast and uses very low memory.

# Usage

Include `libumusic/inc/lum.h` in your C code:

`#include "libumusic/inc/lum.h"`

Declare an empty structure for MIDI data:

`struct midi_s midi = {};`

In Regular intervals of less then 1 ms call this function:

`lum_midi_rx (&midi)`

Implement the following functions:

`
ALWAYS_INLINE lum_process_note (struct midi_s* midi);  
ALWAYS_INLINE lum_process_cc (struct midi_s* midi);  
ALWAYS_INLINE lum_process_pc (uint8_t pc);  
ALWAYS_INLINE lum_process_bend (uint16_t bend);  
`

## Roadmap

I will provide example code and more detailed documentation in the future.
