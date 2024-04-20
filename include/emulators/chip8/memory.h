#pragma once

#include <stdint.h>

typedef struct
{
   uint16_t pc;
   uint16_t i;
   uint8_t sp;
   uint8_t sound_timer;
   uint8_t delta_timer;
   uint16_t* stack;
   uint8_t* memory;
   uint8_t* vram;
   uint8_t* v;
} CHIP8Memory;

CHIP8Memory* chip8_memory_initialize();
void chip8_memory_load(CHIP8Memory*, uint8_t*, uint32_t, uint32_t);
uint8_t chip8_memory_read_byte(const CHIP8Memory*, uint32_t);
uint16_t chip8_memory_read_word(const CHIP8Memory*, uint32_t);
void chip8_memory_free(void*);