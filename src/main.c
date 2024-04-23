#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <SDL_timer.h>

#include "utils/logging.h"
#include "emulators/chip8/core.h"

int main(int argc, char* argv[])
{
    atexit(memfree_all);

    if(argc < 2)
    {
        fprintf(stderr, "No ROM file specified or emulator type.\n");
        fprintf(stderr, "Usage: %s <emulator type> <emulator config file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if(argc < 3)
    {
        fprintf(stderr, "No emulator config file specified.\n");
        fprintf(stderr, "Usage: %s <emulator type> <emulator config file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    srand(time(NULL));

    logging_set_file(fopen("last.log", "w"));

    if(!strcmp(argv[1], "CHIP8"))
        return chip8_main_loop(argv[2]);
    else {
        fprintf(stderr, "Unknown emulator type %s.\n", argv[1]);
        return EXIT_FAILURE;
    }
}