#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <SDL_timer.h>

#include "utils/logging.h"
#include "emulators/chip8/core.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));

    atexit(memfree_all);

    logging_set_file(fopen("last.log", "w"));

    CHIP8EmulatorConfig* config = chip8_config_parse(fopen("defaults/chip8.cfg", "r"));

    CHIP8Emulator* emulator = chip8_emulator_initialize(config);
    memfree_add(emulator, chip8_emulator_free);

    chip8_config_free(config);

    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last = 0;
    double delta = 0;

    while(emulator->running || emulator->window_is_running())
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