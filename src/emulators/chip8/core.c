#include "emulators/chip8/core.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emulators/chip8/display.h"
#include "utils/file.h"
#include "utils/inifile.h"
#include "utils/logging.h"

#include <SDL2/SDL.h>

CHIP8EmulatorConfig* chip8_config_parse(FILE* file)
{
    if(file == NULL)
    {
        fprintf(stderr, "Error: Inexistent file sent to CHIP8 config parser.\n");
        exit(-1);
    }

    CHIP8EmulatorConfig* config = calloc(1, sizeof(CHIP8EmulatorConfig));

    ini_file_data* input = ini_file_read(file);
    fclose(file);

    const char* path = ini_file_get_string(input, "ROM", "Path");
    if(path == NULL)
    {
        fprintf(stderr, "Error: Path has not been specified in startup config!\n");
        chip8_config_free(config);
        exit(-1);
    }
    config->path = strdup(path);

    const char* speed = ini_file_get_string(input, "ROM", "Speed");
    if(speed == NULL)
    {
        fprintf(stderr, "Error: Speed has not been specified in startup config!\n");
        chip8_config_free(config);
        exit(-1);
    }
    config->speed = atoi(speed);

    ini_file_free(input);

    return config;
}

CHIP8Emulator* chip8_emulator_initialize(CHIP8EmulatorConfig* config)
{
    srand(time(NULL));

    CHIP8Emulator* emulator = calloc(1, sizeof(CHIP8Emulator));

    emulator->memory = chip8_memory_initialize();

    FILE* rom = fopen(config->path, "rb");
    if(rom == NULL)
    {
        fprintf(stderr, "Error: The ROM file at path %s does not exist!\n", config->path);
        exit(-1);
    }

    uint32_t rom_size = file_size_get(rom);

    // TODO: maybe make this configurable?
    const uint32_t mount_point = 0x200;
    const uint32_t memory_size = 0x10000;

    if(rom_size > memory_size - mount_point)
    {
        fprintf(stderr, "Error: File is too big to be a CHIP8 ROM!\n");
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

    chip8_emulator_init_display_sdl((void*)emulator);

    emulator->speed = config->speed;
    emulator->timer = 0;
    emulator->extra_timer = 0;

    return emulator;
}

int chip8_main_loop(char* configPath)
{
    FILE* emuConfig = fopen(configPath, "r");
    if(emuConfig == NULL)
    {
        fprintf(stderr, "[ERROR]: Couldn't open config file %s.\n", configPath);
        return EXIT_FAILURE;
    }

    CHIP8EmulatorConfig* config = chip8_config_parse(emuConfig);

    CHIP8Emulator* emulator = chip8_emulator_initialize(config);
    memfree_add(emulator, chip8_emulator_free);

    chip8_config_free(config);

    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last = 0;
    double delta = 0;

    while(emulator->running || chip8_emulator_is_running_sdl())
    {
        last = now;
        now = SDL_GetPerformanceCounter();

        delta = (double)((now - last) / (double)SDL_GetPerformanceFrequency());

        chip8_emulator_update(emulator, delta);
        chip8_emulator_draw(emulator, delta);

        SDL_Delay(15);
    }
    
    return EXIT_SUCCESS;
}

void chip8_emulator_draw(CHIP8Emulator* self, double delta)
{
    chip8_emulator_draw_sdl(self, delta);
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
    chip8_emulator_free_display_sdl((void*)emulator);
    free((void*)emulator);
}