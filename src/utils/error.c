#include "utils/error.h"

#include <SDL_messagebox.h>
#include <stdio.h>

static const char* error_message = 0;

bool has_errored()
{
    return error_message != 0;
}

void show_error()
{
    if(!has_errored())
        return;

    SDL_ShowMessageBox(&(SDL_MessageBoxData){
        .flags = SDL_MESSAGEBOX_ERROR,
        .title = "Error",
        .message = error_message,
        .window = 0,
    }, 0);

    clear_error();
}

void assert_error(bool condition, const char* message)
{
    if(condition)
        return;

    set_error(message);
    show_error();
}

void set_error(const char* message)
{
    error_message = message;
}

void clear_error()
{
    set_error(0);
}