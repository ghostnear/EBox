#pragma once

#include <stdint.h>
#include <stdbool.h>

void tui_clear_screen();
void tui_display_cursor(bool);
void tui_set_cursor_position(uint8_t, uint8_t);