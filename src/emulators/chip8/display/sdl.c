#include "emulators/chip8/display/sdl.h"

#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "emulators/chip8/core.h"
#include "utils/logging.h"

int keybinds[] = {
    SDLK_x, SDLK_1, SDLK_2, SDLK_3,
    SDLK_q, SDLK_w, SDLK_e, SDLK_a,
    SDLK_s, SDLK_d, SDLK_z, SDLK_c,
    SDLK_4, SDLK_r, SDLK_f, SDLK_v
};
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Event event;

void chip8_emulator_init_display_sdl(void* self)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_CreateWindowAndRenderer(
        960, 540,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE,
        &window, &renderer
    );

    if(window == NULL || renderer == NULL)
    {
        FILE* log_file = logging_get_file();
        fprintf(log_file, "[ERROR]: SDL_CreateWindow failed: %s\n", SDL_GetError());
    }

    SDL_SetWindowTitle(window, "CHIP8 Emulator");
    SDL_SetWindowSize(window, 960, 540);
}

void chip8_emulator_free_display_sdl(void* self)
{
    SDL_DestroyWindow(window);
    SDL_Quit();

    FILE* log_file = logging_get_file();
    fprintf(log_file, "[ INFO]: SDL window destroyed.\n");
}

void chip8_emulator_draw_sdl(void* self, double delta)
{
    // Poll events and draw.
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    exit(0);

                for(uint8_t index = 0; index < 0x10; index++)
                    if(event.key.keysym.sym == keybinds[index])
                        ((CHIP8Emulator*)self)->memory->keys[index] = 1;
                break;

            case SDL_KEYUP:
                for(uint8_t index = 0; index < 0x10; index++)
                    if(event.key.keysym.sym == keybinds[index])
                        ((CHIP8Emulator*)self)->memory->keys[index] = 0;
                break;

            case SDL_QUIT:
                exit(0);
                break;
        }
    }

    SDL_RenderSetLogicalSize(renderer, 64, 32);

    SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    // TODO: replace this with an in memory texture and copy.

    for(uint8_t y_pos = 0; y_pos < 32; y_pos++)
        for(uint8_t x_pos = 0; x_pos < 64; x_pos++)
            if(((CHIP8Emulator*)self)->memory->vram[y_pos * 64 + x_pos])
            {
                SDL_Rect rect = {x_pos, y_pos, 1, 1};
                SDL_RenderFillRect(renderer, &rect);
            }

    SDL_RenderPresent(renderer);
}

bool chip8_emulator_is_running_sdl()
{
    return true;
}