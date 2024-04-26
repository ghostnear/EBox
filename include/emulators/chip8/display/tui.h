#pragma once

#ifndef BUILD_PLATFORM_VITA

#include <stdio.h>

void chip8_emulator_init_display_tui(void*);
void chip8_emulator_free_display_tui(void*);
void chip8_emulator_draw_tui(void*, double);

#endif