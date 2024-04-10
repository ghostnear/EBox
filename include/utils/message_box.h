#pragma once

#include <SDL2/SDL.h>

/*
 *  Shows a simple messagebox for errors that has no parent, so it is not bound to any window.
 */
void show_simple_error_messagebox(const char*, const char*);