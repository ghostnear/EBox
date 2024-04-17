#include <stdio.h>
#include <stdlib.h>

#include "utils/logging.h"
#include "emulators/chip8/core.h"

int main(int argc, char* argv[])
{
    atexit(memfree_all);

    logging_set_file(fopen("last.log", "w"));

    CHIP8EmulatorConfig* config = chip8_config_parse(fopen("defaults/chip8.cfg", "r"));

    CHIP8Emulator* emulator = chip8_emulator_initialize(config);
    memfree_add(emulator, chip8_emulator_free);

    chip8_config_free(config);

    while(emulator->running)
    {
        chip8_emulator_update(emulator, 0);
        chip8_emulator_draw(emulator);
    }
    
    return EXIT_SUCCESS;
}