#pragma once

#include <stdbool.h>

void chip8_emulator_init_display_sdl(void*);
void chip8_emulator_free_display_sdl(void*);
void chip8_emulator_draw_sdl(void*, double);
bool chip8_emulator_is_running_sdl();