#include "ui/window.h"
#include "ui/selector.h"

int main(int argc, char* argv[])
{
    // Enable garbage collection at normal end of runtime.
    atexit(memfree_all);

    // Enable logging.
    FILE* log_file = fopen(LOGGING_DEFAULT_PATH, "w");
    assert_error(log_file != NULL, "Couldn't open log file.");
    logging_set_file(log_file);

    window_init();

    // CLI mode.
    if(argc > 2)
    {
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

    // Selection mode.
    rom_selector_main_loop();   
}