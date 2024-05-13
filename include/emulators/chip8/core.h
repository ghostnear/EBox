#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>

#include "memory.h"

typedef struct
{
// ROM
    char* path;
    uint32_t speed; // In instructions per second.

// Display.
    SDL_Color foreground_color;
    SDL_Color background_color;
} CHIP8EmulatorConfig;

typedef struct 
{
    bool running;
    
    double timer;
    double extra_timer;
    uint32_t speed;

    void** instruction_cache;

    SDL_Color foreground_color;
    SDL_Color background_color;
    
    CHIP8Memory* memory;
} CHIP8Emulator;

CHIP8EmulatorConfig* chip8_config_parse(FILE*);
CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig*);
int chip8_main_loop(char*);
void chip8_emulator_update(CHIP8Emulator*, double);
void chip8_emulator_draw(CHIP8Emulator*, double);
void chip8_config_free(void*);
void chip8_emulator_free(void*);
