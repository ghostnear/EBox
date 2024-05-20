#include "ui/window.h"

#include "utils/logging.h"

static SDL_Event event;
static SDL_Renderer* renderer = NULL;
static SDL_Window* window = NULL;

void window_free()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    FILE* log_file = logging_get_file();
    fprintf(log_file, "[ INFO]: SDL window destroyed.\n");
}

void window_init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");

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

#ifdef BUILD_PLATFORM_VITA
    SDL_SetWindowSize(window, 960, 544);
    SDL_setenv("VITA_DISABLE_TOUCH_BACK", "1", 1);
#endif

    atexit(window_free);
}

SDL_Window* window_get_sdl()
{
    return window;
}

SDL_Event* window_get_event()
{
    return &event;
}

SDL_Renderer* window_get_renderer()
{
    return renderer;
}