#include "emulators/chip8/memory.h"

#include <stdlib.h>
#include <string.h>

CHIP8Memory* chip8_memory_initialize()
{
    CHIP8Memory* memory = calloc(1, sizeof(CHIP8Memory));

    memory->memory = calloc(0x10000, sizeof(uint8_t));

    return memory;
}

void chip8_memory_load(CHIP8Memory* self, uint8_t* data, uint32_t size, uint32_t offset)
{
    memcpy(data, self->memory + offset, size * sizeof(uint8_t));
}

void chip8_memory_free(void* pointer)
{
    const CHIP8Memory* memory = (CHIP8Memory*) pointer;

    free(memory->memory);
    free((void*)memory);
}