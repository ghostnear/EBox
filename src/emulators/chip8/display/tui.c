#include "emulators/chip8/core.h"

#include <curses.h>
#include <ncurses.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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
    curs_set(1);
}

void chip8_emulator_update_input(CHIP8Emulator* self)
{
    char input;

    memset(self->memory->keys, 0, 0x10 * sizeof(uint8_t));

    while((input = getch()) != ERR)
    {
        // TODO: replace this with a key map.
        if(input == 'x') self->memory->keys[0x0] = 1;
        if(input == '1') self->memory->keys[0x1] = 1;
        if(input == '2') self->memory->keys[0x2] = 1;
        if(input == '3') self->memory->keys[0x3] = 1;
        if(input == 'q') self->memory->keys[0x4] = 1;
        if(input == 'w') self->memory->keys[0x5] = 1;
        if(input == 'e') self->memory->keys[0x6] = 1;
        if(input == 'a') self->memory->keys[0x7] = 1;
        if(input == 's') self->memory->keys[0x8] = 1;
        if(input == 'd') self->memory->keys[0x9] = 1;
        if(input == 'z') self->memory->keys[0xA] = 1;
        if(input == 'c') self->memory->keys[0xB] = 1;
        if(input == '4') self->memory->keys[0xC] = 1;
        if(input == 'r') self->memory->keys[0xD] = 1;
        if(input == 'f') self->memory->keys[0xE] = 1;
        if(input == 'v') self->memory->keys[0xF] = 1;
    }
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
    addch('\n');
    refresh();
}