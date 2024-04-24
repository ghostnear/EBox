#pragma once

#include "none.h"
#include "tui.h"
#include "sdl.h"

typedef enum {
    CHIP8_DISPLAY_NONE = 0,
    CHIP8_DISPLAY_TUI,
    CHIP8_DISPLAY_SDL
} CHIP8DisplayType;