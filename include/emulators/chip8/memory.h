#pragma once

#include <stdint.h>

typedef struct
{
   uint8_t* memory;
} CHIP8Memory;

CHIP8Memory* chip8_memory_initialize();
void chip8_memory_load(CHIP8Memory*, uint8_t*, uint32_t, uint32_t);
void chip8_memory_free(void*);