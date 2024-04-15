#include "emulators/chip8/core.h"

#include "utils/tui.h"

#include <stdint.h>

// TODO: make this support colors and stuff.

void chip8_emulator_init_display_tui(void* self)
{

}

void chip8_emulator_free_display_tui(void* self)
{

}

void chip8_emulator_draw_tui(void* self)
{
    const CHIP8Memory* memory = ((CHIP8Emulator*)self)->memory;
    for(uint8_t y = 0; y < 0x20; y++)
        for(uint8_t x = 0; x < 0x40; x++)
            if(memory->vram[y * 0x40 + x] == 0)
                tui_set(x, y, ' ');
            else
                tui_set(x, y, '#');
}