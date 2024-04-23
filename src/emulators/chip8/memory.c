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

    // Load the font.
    const uint8_t font[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    chip8_memory_load(memory, (uint8_t*)font, sizeof(font), 0);

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