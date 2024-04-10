#include <stdio.h>
#include <stdlib.h>

#include "utils/inifile.h"
#include "utils/memfree_list.h"
#include "emulators/chip8/core.h"


int main()
{
    atexit(memfree_all);

    /*CHIP8EmulatorConfig* config = parse_chip8_emulator_config("defaults/chip8.cfg");
    memfree_add(config, NULL);

    CHIP8Emulator* emulator = initialize_chip8_emulator(config);
    memfree_add(emulator, NULL);*/

    FILE* file = fopen("defaults/chip8.cfg", "r");

    ini_file_data* ini = ini_file_read(file);

    fclose(file);

    ini_file_write(stdout, ini);

    memfree_add(ini, ini_file_free);
    
    return EXIT_SUCCESS;
}