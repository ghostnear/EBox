#include "utils/tui.h"

#ifdef BUILD_PLATFORM_WINDOWS
#include <windows.h>
#endif
#ifdef BUILD_PLATFORM_UNIX
#include <stdio.h>
#endif

void tui_clear_screen()
{
#ifdef BUILD_PLATFORM_UNIX
    printf("\033[2J");
#endif
}

void tui_set_cursor_position(uint8_t x, uint8_t y)
{
    // Sets the current displayed character in the output to that value.
#ifdef BUILD_PLATFORM_WINDOWS
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
#ifdef BUILD_PLATFORM_UNIX
    printf("\033[%d;%dH", y, x);
#endif
}

void tui_display_cursor(bool value)
{
#ifdef BUILD_PLATFORM_WINDOWS
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    cursor_info.bVisible = value;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
#endif
#ifdef BUILD_PLATFORM_UNIX
    printf(value ? "\e[?25h" : "\e[?25l");
#endif
}