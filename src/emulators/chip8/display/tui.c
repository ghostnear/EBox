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
    tui_set_cursor_position(0, 0);

    // TODO: replace this with actual printing.
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 64; j++)
            printf("#");
        printf("\n");
    }
}