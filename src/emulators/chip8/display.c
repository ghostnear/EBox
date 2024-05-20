#include "emulators/chip8/display.h"

#include "ui/window.h"
#include "emulators/chip8/core.h"

int keybinds[] = {
    SDLK_x, SDLK_1, SDLK_2, SDLK_3,
    SDLK_q, SDLK_w, SDLK_e, SDLK_a,
    SDLK_s, SDLK_d, SDLK_z, SDLK_c,
    SDLK_4, SDLK_r, SDLK_f, SDLK_v
};

void chip8_emulator_draw(void* self, double delta)
{
    const CHIP8Emulator* this = self;
    SDL_Event* event = window_get_event();

    // Poll events and draw.
    while(SDL_PollEvent(event))
    {
        switch(event->type)
        {
            case SDL_KEYDOWN:
                if(event->key.keysym.sym == SDLK_ESCAPE)
                    exit(0);

                for(uint8_t index = 0; index < 0x10; index++)
                    if(event->key.keysym.sym == keybinds[index])
                        this->memory->keys[index] = 1;
                break;

            case SDL_KEYUP:
                for(uint8_t index = 0; index < 0x10; index++)
                    if(event->key.keysym.sym == keybinds[index])
                        this->memory->keys[index] = 0;
                break;

            case SDL_QUIT:
                exit(0);
                break;
        }
    }

    SDL_Renderer* renderer = window_get_renderer();

    SDL_RenderSetLogicalSize(renderer, 64, 32);

    SDL_SetRenderDrawColor(renderer, this->background_color.r, this->background_color.g, this->background_color.b, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, this->foreground_color.r, this->foreground_color.g, this->foreground_color.b, 255);

    // TODO: replace this with an in memory texture and copy.

    for(uint8_t y_pos = 0; y_pos < 32; y_pos++)
        for(uint8_t x_pos = 0; x_pos < 64; x_pos++)
            if(this->memory->vram[y_pos * 64 + x_pos])
            {
                SDL_Rect rect = {x_pos, y_pos, 1, 1};
                SDL_RenderFillRect(renderer, &rect);
            }

    SDL_RenderPresent(renderer);
}