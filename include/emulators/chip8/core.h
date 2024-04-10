#pragma once

#include <stdio.h>

typedef struct
{
    char* path;
} CHIP8EmulatorConfig;

typedef struct 
{

} CHIP8Emulator;

CHIP8EmulatorConfig* chip8_config_parse(FILE*);
CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig*);
void chip8_config_free(void*);
void chip8_emulator_free(void*);
