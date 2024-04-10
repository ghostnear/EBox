#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "memory.h"

typedef struct
{
    char* path;
} CHIP8EmulatorConfig;

typedef struct 
{
    bool running;
    CHIP8Memory* memory;
} CHIP8Emulator;

CHIP8EmulatorConfig* chip8_config_parse(FILE*);
CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig*);
void chip8_emulator_update(CHIP8Emulator*, double);
void chip8_emulator_draw(CHIP8Emulator*);
void chip8_config_free(void*);
void chip8_emulator_free(void*);
