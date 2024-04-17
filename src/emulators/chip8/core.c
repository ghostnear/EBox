#include "emulators/chip8/core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/file.h"
#include "utils/inifile.h"
#include "utils/message_box.h"
#include "utils/logging.h"

void (*const chip8_draw_init_cache[])(void*) = {
    chip8_emulator_init_display_none,
    chip8_emulator_init_display_tui
};

void (*const chip8_draw_free_cache[])(void*) = {
    chip8_emulator_free_display_none,
    chip8_emulator_free_display_tui
};

void (*const chip8_draw_cache[])(void*) = {
    chip8_emulator_draw_none,
    chip8_emulator_draw_tui
};

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
    
    const char* display_type = ini_file_get_string(input, "System", "Display");
    if(display_type == NULL)
    {
        show_simple_error_messagebox("Error!", "Display type has not been specified in startup config!");
        chip8_config_free(config);
        exit(-1);
    }

    if(strcmp(display_type, "NONE") == 0)
        config->display_type = CHIP8_DISPLAY_NONE;
    else if(strcmp(display_type, "TUI") == 0)
        config->display_type = CHIP8_DISPLAY_TUI;
    else if(strcmp(display_type, "SDL") == 0)
        config->display_type = CHIP8_DISPLAY_SDL;
    else
    {
        show_simple_error_messagebox("Error!", "Invalid display type specified in startup config!");
        chip8_config_free(config);
        exit(-1);
    }

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
    const uint32_t mount_point = 0x200;
    const uint32_t memory_size = 0x10000;

    if(rom_size > memory_size - mount_point)
    {
        show_simple_error_messagebox("Error!", "File is too big to be a CHIP8 ROM!");
        fclose(rom);
        exit(-1);
    }

    FILE* log_file = logging_get_file();
    fprintf(log_file, "[ INFO]: ROM size: %d bytes.\n", rom_size);

    uint8_t* data = calloc(rom_size, sizeof(uint8_t));

    fread(data, sizeof(uint8_t), rom_size, rom);

    fclose(rom);

    emulator->memory->pc = mount_point;

    chip8_memory_load(emulator->memory, data, rom_size, mount_point);

    free(data);

    emulator->running = true;

    emulator->instruction_cache = calloc(memory_size, sizeof(void*));

    chip8_draw_init_cache[config->display_type]((void*)emulator);    
    emulator->display_function = chip8_draw_cache[config->display_type];
    emulator->free_display = chip8_draw_free_cache[config->display_type];

    return emulator;
}

void chip8_emulator_draw(CHIP8Emulator* self)
{
    self->display_function(self);
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
    emulator->free_display((void*)emulator);
    free((void*)emulator);
}