#include <stdlib.h>

#include "emulators/chip8/core.h"
#include "utils/memfree_list.h"

int main()
{
    atexit(memfree_all);

    CHIP8EmulatorConfig* config = parse_chip8_emulator_config("defaults/chip8.cfg");
    memfree_add(config);

    CHIP8Emulator* emulator = initialize_chip8_emulator(config);
    memfree_add(emulator);
    
    return EXIT_SUCCESS;
}