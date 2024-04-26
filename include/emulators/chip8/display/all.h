#pragma once

#include "none.h"
#include "tui.h"
#include "sdl.h"

typedef enum {
    CHIP8_DISPLAY_NONE = 0,
#ifndef BUILD_PLATFORM_VITA
    CHIP8_DISPLAY_TUI,
#endif
    CHIP8_DISPLAY_SDL
} CHIP8DisplayType;