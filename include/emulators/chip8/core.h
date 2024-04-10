#pragma once

typedef struct
{

} CHIP8EmulatorConfig;

typedef struct 
{

} CHIP8Emulator;

CHIP8EmulatorConfig* parse_chip8_emulator_config(char*);
CHIP8Emulator* initialize_chip8_emulator(CHIP8EmulatorConfig*);
