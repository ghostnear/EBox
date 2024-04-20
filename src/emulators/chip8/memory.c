#include "emulators/chip8/memory.h"

#include <stdlib.h>
#include <string.h>

CHIP8Memory* chip8_memory_initialize()
{
    CHIP8Memory* memory = calloc(1, sizeof(CHIP8Memory));

    memory->memory = calloc(0x10000, sizeof(uint8_t));
    memory->vram = calloc(0x40 * 0x20, sizeof(uint8_t));
    memory->v = calloc(0x10, sizeof(uint8_t));
    memory->stack = calloc(0x10, sizeof(uint16_t));
    memory->keys = calloc(0x10, sizeof(uint8_t));

    return memory;
}

void chip8_memory_load(CHIP8Memory* self, uint8_t* data, uint32_t size, uint32_t offset)
{
    memcpy(self->memory + offset, data, size * sizeof(uint8_t));
}

uint8_t chip8_memory_read_byte(const CHIP8Memory* self, uint32_t address)
{
    return self->memory[address];
}

uint16_t chip8_memory_read_word(const CHIP8Memory* self, uint32_t address)
{
    return (self->memory[address] << 8) | self->memory[address + 1];
}

void chip8_memory_free(void* pointer)
{
    const CHIP8Memory* memory = (CHIP8Memory*) pointer;

    free(memory->memory);
    free(memory->vram);
    free(memory->v);
    free(memory->stack);
    free(memory->keys);
    free((void*)memory);
}