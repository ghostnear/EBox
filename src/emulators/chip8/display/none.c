#include "emulators/chip8/display/none.h"

#include <stdio.h>

#include "utils/logging.h"

void chip8_emulator_init_display_none(void* self)
{
    FILE* logging_file = logging_get_file();
    fprintf(logging_file, "[ WARN]: Display type NONE has been selected!\n");
}

void chip8_emulator_free_display_none(void* self)
{
    // Do nothing.
}

void chip8_emulator_draw_none(void* self)
{
    // Do nothing.
}