#pragma once

#include <SDL2/SDL.h>

void window_init();
SDL_Window* window_get_sdl();
SDL_Event* window_get_event();
SDL_Renderer* window_get_renderer();