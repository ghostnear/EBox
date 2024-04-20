#include "emulators/chip8/core.h"

#include "utils/tui.h"

#include <stdint.h>

// TODO: make this support colors and stuff.

void chip8_emulator_init_display_tui(void* self)
{
    tui_clear_screen();
    tui_display_cursor(false);
}

void chip8_emulator_free_display_tui(void* self)
{   
    tui_display_cursor(true);
}

void chip8_emulator_draw_tui(void* self)
{
    tui_set_cursor_position(0, 0);

    for(int y_pos = 0; y_pos < 32; y_pos++)
    {
        for(int x_pos = 0; x_pos < 64; x_pos++)
        {
            if(((CHIP8Emulator*)self)->memory->vram[y_pos * 64 + x_pos])
                printf("\033[7m ");
            else
                printf("\033[0m ");
        }
        printf("\033[0m\n");
    }
}