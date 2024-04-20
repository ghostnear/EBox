#include "emulators/chip8/core.h"

#include <curses.h>
#include <ncurses.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: make this support colors and stuff.

void chip8_emulator_init_display_tui(void* self)
{
    CHIP8Emulator* this = (CHIP8Emulator*)self;

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    curs_set(0);
    clear();

    this->memory->draw_flag = true;
}

void chip8_emulator_free_display_tui(void* self)
{   
    endwin();
    curs_set(1);
}

void chip8_emulator_update_input(CHIP8Emulator* self)
{
    char input = getch();

    if(input == 'q')
        self->running = false;
}

void chip8_emulator_draw_tui(void* self, double delta)
{
    CHIP8Emulator* this = (CHIP8Emulator*)self;

    chip8_emulator_update_input(this);

    if(!this->memory->draw_flag)
        return;

    for(int y_pos = 0; y_pos < 32; y_pos++)
    {
        move(y_pos, 0);
        for(int x_pos = 0; x_pos < 64; x_pos++)
            addch(' '| A_REVERSE * (this->memory->vram[y_pos * 64 + x_pos]));
    }

    refresh();
}