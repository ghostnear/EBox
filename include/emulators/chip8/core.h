#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "memory.h"
#include "display/all.h"

typedef enum {
    CHIP8_DISPLAY_NONE = 0,
    CHIP8_DISPLAY_TUI,
    CHIP8_DISPLAY_SDL
} CHIP8DisplayType;

typedef struct
{
// ROM
    char* path;

// System
    CHIP8DisplayType display_type;
} CHIP8EmulatorConfig;

typedef struct 
{
    bool running;
    void** instruction_cache;
    void (*display_function)(void*);
    void (*free_display)(void*);
    CHIP8Memory* memory;
} CHIP8Emulator;

CHIP8EmulatorConfig* chip8_config_parse(FILE*);
CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig*);
void chip8_emulator_update(CHIP8Emulator*, double);
void chip8_emulator_draw(CHIP8Emulator*);
void chip8_config_free(void*);
void chip8_emulator_free(void*);
