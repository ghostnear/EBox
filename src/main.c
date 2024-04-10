#include <stdio.h>
#include <stdlib.h>

#include "utils/memfree_list.h"
#include "emulators/chip8/core.h"

int main()
{
    atexit(memfree_all);

    FILE* file = fopen("defaults/chip8.cfg", "r");

    CHIP8EmulatorConfig* config = chip8_config_parse(file);

    CHIP8Emulator* emulator = chip8_emulator_initialize(config);
    memfree_add(emulator, chip8_emulator_free);
    chip8_config_free(config);

    // while(1);
    
    return EXIT_SUCCESS;
}