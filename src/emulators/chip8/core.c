#include "emulators/chip8/core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/file.h"
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
        exit(-1);
    }
    config->path = strdup(path);

    ini_file_free(input);

    return config;
}

CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig* config)
{
    CHIP8Emulator* emulator = calloc(1, sizeof(CHIP8Emulator));

    emulator->memory = chip8_memory_initialize();

    FILE* rom = fopen(config->path, "rb");
    if(rom == NULL)
    {
        show_simple_error_messagebox("Error!", "The ROM file does not exist!");
        exit(-1);
    }

    uint32_t rom_size = file_size_get(rom);

    // TODO: maybe make this configurable?
    const uint32_t mount_point = 0x100;
    const uint32_t memory_size = 0x10000;

    if(rom_size > memory_size - mount_point)
    {
        show_simple_error_messagebox("Error!", "File is too big to be a CHIP8 ROM!");
        fclose(rom);
        exit(-1);
    }

    printf("[ INFO]: ROM size: %d bytes.\n", rom_size);

    uint8_t* data = calloc(rom_size, sizeof(uint8_t));

    fread(data, sizeof(uint8_t), rom_size, rom);

    fclose(rom);

    emulator->memory->PC = mount_point;

    chip8_memory_load(emulator->memory, data, rom_size, mount_point);

    free(data);

    emulator->running = true;

    emulator->instruction_cache = calloc(memory_size, sizeof(void*));

    return emulator;
}

void chip8_emulator_draw(CHIP8Emulator* self)
{

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
    free(emulator->instruction_cache);
    free((void*)emulator);
}