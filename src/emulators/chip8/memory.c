#include "emulators/chip8/memory.h"

#include <stdlib.h>

CHIP8Memory* chip8_memory_initialize()
{
    CHIP8Memory* memory = calloc(1, sizeof(CHIP8Memory));

    memory->memory = calloc(0x10000, sizeof(uint8_t));

    return memory;
}

void chip8_memory_free(void* pointer)
{
    const CHIP8Memory* memory = (CHIP8Memory*) pointer;

    free(memory->memory);
    free((void*)memory);
}