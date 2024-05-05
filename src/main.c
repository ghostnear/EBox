#include "utils/all.h"
#include "emulators/all.h"

int main(int argc, char* argv[])
{
    // Argument parsing.
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

    // Enable garbage collection at normal end of runtime.
    atexit(memfree_all);

    // Enable logging.
    FILE* log_file = fopen(LOGGING_DEFAULT_PATH, "w");
    assert_error(log_file != NULL, "Couldn't open log file.");
    logging_set_file(log_file);

    // Emulator check.
    if(!strcmp(argv[1], "CHIP8"))
        return chip8_main_loop(argv[2]);
    else {
        set_error("Unknown emulator type has been selected.");
        show_error();
        log_print("[ERROR]: Unknown emulator type has been selected: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
}