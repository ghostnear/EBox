#include "emulators/chip8/core.h"

#include <stdlib.h>
#include <string.h>

#include "utils/inifile.h"
#include "utils/message_box.h"

CHIP8EmulatorConfig* chip8_config_parse(FILE* file)
{
    CHIP8EmulatorConfig* config = calloc(1, sizeof(CHIP8EmulatorConfig));

    ini_file_data* input = ini_file_read(file);
    fclose(file);

    const char* path = ini_file_get_string(input, "ROM", "Path");
    if(path == NULL)
    {
        show_simple_error_messagebox("Error!", "Path has not been specified in startup config!");
        chip8_config_free(config);
        exit(0);
    }
    config->path = strdup(path);

    ini_file_free(input);

    return config;
}

CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig* config)
{
    CHIP8Emulator* emulator = calloc(1, sizeof(CHIP8Emulator));

    emulator->memory = chip8_memory_initialize();

    return emulator;
}

void chip8_config_free(void* pointer)
{
    const CHIP8EmulatorConfig* config = (CHIP8EmulatorConfig*) pointer;

    if(config->path != NULL)
        free(config->path);
    
    free((void*)config);
}

void chip8_emulator_free(void* pointer)
{
    const CHIP8Emulator* emulator = (CHIP8Emulator*) pointer;
    chip8_memory_free(emulator->memory);
    free((void*)emulator);
}