#include "emulators/chip8/core.h"

#include <stdlib.h>
#include <string.h>

#include "utils/inifile.h"

CHIP8EmulatorConfig* chip8_config_parse(FILE* file)
{
    CHIP8EmulatorConfig* config = calloc(1, sizeof(CHIP8EmulatorConfig));

    ini_file_data* input = ini_file_read(file);

    config->path = strdup(ini_file_get_string(input, "ROM", "Path"));

    ini_file_free(input);

    return config;
}

CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig* config)
{
    return 0;
}

void chip8_config_free(void* pointer)
{
    const CHIP8EmulatorConfig* config = (CHIP8EmulatorConfig*) pointer;
    free(config->path);
    free((void*)config);
}

void chip8_emulator_free(void* pointer)
{
    const CHIP8Emulator* emulator = (CHIP8Emulator*) pointer;
    free((void*)emulator);
}