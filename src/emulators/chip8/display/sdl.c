#include "emulators/chip8/display/sdl.h"

#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "emulators/chip8/core.h"
#include "utils/logging.h"

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
            // TODO: this is kinda dogshit but hey the AI did it for me lol.
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    exit(0);

                if(event.key.keysym.sym == SDLK_1)
                    ((CHIP8Emulator*)self)->memory->keys[0x1] = 1;

                if(event.key.keysym.sym == SDLK_2)
                    ((CHIP8Emulator*)self)->memory->keys[0x2] = 1;

                if(event.key.keysym.sym == SDLK_3)
                    ((CHIP8Emulator*)self)->memory->keys[0x3] = 1;

                if(event.key.keysym.sym == SDLK_4)
                    ((CHIP8Emulator*)self)->memory->keys[0xC] = 1;

                if(event.key.keysym.sym == SDLK_q)
                    ((CHIP8Emulator*)self)->memory->keys[0x4] = 1;

                if(event.key.keysym.sym == SDLK_w)
                    ((CHIP8Emulator*)self)->memory->keys[0x5] = 1;

                if(event.key.keysym.sym == SDLK_e)
                    ((CHIP8Emulator*)self)->memory->keys[0x6] = 1;

                if(event.key.keysym.sym == SDLK_r)
                    ((CHIP8Emulator*)self)->memory->keys[0xD] = 1;

                if(event.key.keysym.sym == SDLK_a)
                    ((CHIP8Emulator*)self)->memory->keys[0x7] = 1;

                if(event.key.keysym.sym == SDLK_s)
                    ((CHIP8Emulator*)self)->memory->keys[0x8] = 1;

                if(event.key.keysym.sym == SDLK_d)
                    ((CHIP8Emulator*)self)->memory->keys[0x9] = 1;

                if(event.key.keysym.sym == SDLK_f)
                    ((CHIP8Emulator*)self)->memory->keys[0xE] = 1;
                
                if(event.key.keysym.sym == SDLK_z)
                    ((CHIP8Emulator*)self)->memory->keys[0xA] = 1;

                if(event.key.keysym.sym == SDLK_x)
                    ((CHIP8Emulator*)self)->memory->keys[0x0] = 1;

                if(event.key.keysym.sym == SDLK_c)
                    ((CHIP8Emulator*)self)->memory->keys[0xB] = 1;

                if(event.key.keysym.sym == SDLK_v)
                    ((CHIP8Emulator*)self)->memory->keys[0xF] = 1;

                break;

            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_1)
                    ((CHIP8Emulator*)self)->memory->keys[0x1] = 0;

                if(event.key.keysym.sym == SDLK_2)
                    ((CHIP8Emulator*)self)->memory->keys[0x2] = 0;

                if(event.key.keysym.sym == SDLK_3)
                    ((CHIP8Emulator*)self)->memory->keys[0x3] = 0;

                if(event.key.keysym.sym == SDLK_4)
                    ((CHIP8Emulator*)self)->memory->keys[0xC] = 0;

                if(event.key.keysym.sym == SDLK_q)
                    ((CHIP8Emulator*)self)->memory->keys[0x4] = 0;

                if(event.key.keysym.sym == SDLK_w)
                    ((CHIP8Emulator*)self)->memory->keys[0x5] = 0;

                if(event.key.keysym.sym == SDLK_e)
                    ((CHIP8Emulator*)self)->memory->keys[0x6] = 0;

                if(event.key.keysym.sym == SDLK_r)
                    ((CHIP8Emulator*)self)->memory->keys[0xD] = 0;

                if(event.key.keysym.sym == SDLK_a)
                    ((CHIP8Emulator*)self)->memory->keys[0x7] = 0;

                if(event.key.keysym.sym == SDLK_s)
                    ((CHIP8Emulator*)self)->memory->keys[0x8] = 0;

                if(event.key.keysym.sym == SDLK_d)
                    ((CHIP8Emulator*)self)->memory->keys[0x9] = 0;

                if(event.key.keysym.sym == SDLK_f)
                    ((CHIP8Emulator*)self)->memory->keys[0xE] = 0;
                
                if(event.key.keysym.sym == SDLK_z)
                    ((CHIP8Emulator*)self)->memory->keys[0xA] = 0;

                if(event.key.keysym.sym == SDLK_x)
                    ((CHIP8Emulator*)self)->memory->keys[0x0] = 0;

                if(event.key.keysym.sym == SDLK_c)
                    ((CHIP8Emulator*)self)->memory->keys[0xB] = 0;

                if(event.key.keysym.sym == SDLK_v)
                    ((CHIP8Emulator*)self)->memory->keys[0xF] = 0;

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